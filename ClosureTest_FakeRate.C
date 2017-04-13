#include "HttStylesNew.cc"
#include "CMS_lumi.C"
#include "settings.h"

#include <iostream>
#include "TTree.h" 
#include "TFile.h" 
#include "TH2.h"
#include "TH1.h"

using namespace std;

void ClosureTest_FakeRate() {

  loadWorkingPoints();
  initCuts();
  loadFakeRates("output/WJetsToLNu_13TeV-madgraphMLM_fakeRate.root");

  std::vector<TString> obs;
  std::vector<TString> pred;

  obs.push_back("ZJetsToNuNu_HT-100To200_13TeV-madgraph");
  obs.push_back("ZJetsToNuNu_HT-200To400_13TeV-madgraph");
  obs.push_back("ZJetsToNuNu_HT-400To600_13TeV-madgraph");
  obs.push_back("ZJetsToNuNu_HT-600To800_13TeV-madgraph");

  pred.push_back("ZJetsToNuNu_HT-100To200_13TeV-madgraph");
  pred.push_back("ZJetsToNuNu_HT-200To400_13TeV-madgraph");
  pred.push_back("ZJetsToNuNu_HT-400To600_13TeV-madgraph");
  pred.push_back("ZJetsToNuNu_HT-600To800_13TeV-madgraph");

  obs.push_back("WJetsToLNu_HT-70To100_13TeV-madgraphMLM-pythia8");
  obs.push_back("WJetsToLNu_HT-100To200_13TeV-madgraphMLM-pythia8");
  obs.push_back("WJetsToLNu_HT-200To400_13TeV-madgraphMLM-pythia8");
  obs.push_back("WJetsToLNu_HT-400To600_13TeV-madgraphMLM-pythia8");
  obs.push_back("WJetsToLNu_HT-600To800_13TeV-madgraphMLM-pythia8");
  obs.push_back("WJetsToLNu_HT-800To1200_13TeV-madgraphMLM-pythia8");

  pred.push_back("WJetsToLNu_HT-70To100_13TeV-madgraphMLM-pythia8");
  pred.push_back("WJetsToLNu_HT-100To200_13TeV-madgraphMLM-pythia8");
  pred.push_back("WJetsToLNu_HT-200To400_13TeV-madgraphMLM-pythia8");
  pred.push_back("WJetsToLNu_HT-400To600_13TeV-madgraphMLM-pythia8");
  pred.push_back("WJetsToLNu_HT-600To800_13TeV-madgraphMLM-pythia8");
  pred.push_back("WJetsToLNu_HT-800To1200_13TeV-madgraphMLM-pythia8");

  std::vector<double> obs_xsec;
  for(unsigned int i=0; i<obs.size(); i++) obs_xsec.push_back( getXSec(obs[i]) );
  
  std::vector<double> pred_xsec;
  for(unsigned int i=0; i<pred.size(); i++) pred_xsec.push_back( getXSec(pred[i]) );

  TString dir      = "NTuples/"; 

  // Binning and titles of axis
  TString xtitle = "m_{T} [GeV]";
  TString ytitle = "Events / 100 GeV";
  
  for(unsigned int idx_iso=0; idx_iso<iso.size(); idx_iso++){

    cout<<endl<<endl<<"........................... Processing "<<iso[idx_iso]<<endl;

    SetStyle();
    TH1::SetDefaultSumw2();
    TH2::SetDefaultSumw2();

    TString var = "mttau";

    //const int nBins = 10;
    //double bins[nBins+1] = {0 , 0.4 , 0.5 , 0.6 , 0.7 , 0.75 , 0.8 , 0.85 , 0.9 , 0.95 , 2.};
    const int nBins  = 5;
    //float bins[nBins+1] = {100,150,200,250,300,500};  // tauPt binning
    //float bins[nBins+1] = {100,200,300,400,500,700};  // met binning
    //float bins[nBins+1] = {100,170,240,310,400,700};  // tauJetPt binning
    float bins[nBins+1] = {200,300,400,500,600,800};  // mttau binning
    //float bins[nBins+1] = {0,0.5,1.1,2.3}; //tauEta binning
    TH1D * observation = new TH1D("observation_"+iso[idx_iso],"",nBins,bins); 
    TH1D * prediction  = new TH1D("prediction_"+iso[idx_iso],"",nBins,bins); 

    // Make selection and fill histograms for sr and cr
    for (unsigned int i=0; i<obs.size(); ++i) {
      TH1D* histo = new TH1D("obs_" + obs[i],"",nBins,bins);
      makeSelection(dir+"/"+obs[i]+".root", "NTuple", obs_xsec[i],iso[idx_iso],sr,histo,var,var,var);
      observation->Add(histo);
      observation->SetName(histo->GetName());
    }
    for (unsigned int i=0; i<pred.size(); ++i) {

      loadFakeRates("output/WJetsToLNu_13TeV-madgraphMLM_fakeRate.root");
      TH1D* histo = new TH1D("pred_" + pred[i],"",nBins,bins);
      makeSelection(dir+"/"+pred[i]+".root","NTuple",pred_xsec[i],iso[idx_iso],cr_antiiso,histo,var,var,var);

      loadFakeRates("output/WJetsToLNu_13TeV-madgraphMLM_fakeRate_Up.root");
      TH1D* histoUp = new TH1D("pred_" + pred[i] + "_Up","",nBins,bins);
      makeSelection(dir+"/"+pred[i]+".root","NTuple",pred_xsec[i],iso[idx_iso],cr_antiiso,histoUp,var,var,var);

      loadFakeRates("output/WJetsToLNu_13TeV-madgraphMLM_fakeRate_Down.root");
      TH1D* histoDown = new TH1D("pred_" + pred[i] + "_Down","",nBins,bins);
      makeSelection(dir+"/"+pred[i]+".root","NTuple",pred_xsec[i],iso[idx_iso],cr_antiiso,histoDown,var,var,var);

      // Set correct uncertainties
      for(int i=1; i<histo->GetNbinsX(); i++){
	histo->SetBinError(i , sqrt( pow(histo->GetBinError(i),2) + pow(abs(histoUp->GetBinContent(i) - histoDown->GetBinContent(i))/2,2)) );
      }

      prediction->Add(histo);
    }

    double obsE, predE;
    double nObs  = observation -> IntegralAndError(1,observation->GetNbinsX(),obsE);
    double nPred = prediction  -> IntegralAndError(1,prediction->GetNbinsX(),predE);

    cout<<"Observation : "<<nObs<< " +/- "<<obsE<< " (nevents = "<<observation->GetEntries()<<") "<<endl;
    cout<<"Prediction  : "<<nPred<<" +/- "<<predE<<" (nevents = "<<prediction ->GetEntries()<<") "<<endl;

    TCanvas * canv1 = MakeCanvas("canv1", "", 700, 800);
    TPad * upper = new TPad("upper", "pad",0,0.29,1,1);
    upper->Draw();
    upper->cd();
    observation->GetYaxis()->SetTitle("Events");
    prediction->SetLineColor(kRed);
    prediction->SetMarkerColor(kRed);
    prediction->SetFillStyle(0);

    observation->SetMinimum(0);
    observation->GetXaxis()->SetTitle(observation->GetName());
    observation->Draw("e1");
    prediction->Draw("sameh");
    if(prediction->GetMaximum()>observation->GetMaximum()){
      observation->SetMaximum(prediction->GetMaximum()*1.2);
    }

    TLegend * leg = new TLegend(0.55,0.4,0.85,0.78);
    SetLegendStyle(leg);
    leg->SetTextSize(0.047);
    leg->SetHeader(iso[idx_iso]);
    leg->AddEntry(observation,"observation","lp");
    leg->AddEntry(prediction,"prediction","lp");
    leg->Draw();
    writeExtraText = true;
    
    upper->Draw("SAME");
    upper->RedrawAxis();
    upper->Modified();
    upper->Update();
    canv1->cd();

    TH1D * ratioH = (TH1D*)observation->Clone("ratioH");
    ratioH->Divide(prediction);
    ratioH->SetMarkerColor(1);
    ratioH->SetMarkerStyle(20);
    ratioH->SetMarkerSize(1.2);
    ratioH->SetLineColor(1);
    ratioH->GetYaxis()->SetRangeUser(0.0,2.);
    ratioH->GetYaxis()->SetTitle("obs/exp");
    ratioH->GetXaxis()->SetTitle("");
    ratioH->GetYaxis()->CenterTitle();
    // ------------>Primitives in pad: lower
    TPad * lower = new TPad("lower", "pad",0,0,1,0.30);
    lower->Draw();
    lower->cd();
    lower->SetGridy();
    ratioH->Draw("e1");
    TLine *line = new TLine(bins[0],1,bins[nBins],1);
    line->Draw("same");

    lower->Modified();
    lower->RedrawAxis();
    canv1->cd();
    canv1->Modified();
    canv1->cd();
    canv1->SetSelected(canv1);
    canv1->Update();
    canv1->Print("figures/"+(TString)observation->GetName()+"_"+iso[idx_iso]+"_WToTauNu_closure.png");
    delete canv1;

    // Save ratio plot as root file
    TFile *outFile = new TFile("output/"+(TString)observation->GetName()+"_"+iso[idx_iso]+"_WToTauNu_closure.root","RECREATE");
    outFile -> cd();
    ratioH  -> Write();
    outFile -> Close();
    delete outFile;

    std::cout << std::endl;

  }
}
