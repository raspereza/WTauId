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

  std::vector<TString> obs;
  obs.push_back("W1JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8");
  obs.push_back("W2JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8");
  obs.push_back("W3JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8");
  obs.push_back("W4JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8");
  std::vector<double> obs_xsec;
  for(unsigned int i=0; i<obs.size(); i++) obs_xsec.push_back( getXSec(obs[i]) );
  
  std::vector<TString> pred;
  pred.push_back("W1JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8");
  pred.push_back("W2JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8");
  pred.push_back("W3JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8");
  pred.push_back("W4JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8");
  std::vector<double> pred_xsec;
  for(unsigned int i=0; i<pred.size(); i++) pred_xsec.push_back( getXSec(pred[i]) );

  TString dir      = "NTuples/"; 
  double wnorm = 1.3; // W* K-factor (PYTHIA8 -> NNLO) 

  // Binning and titles of axis
  int nBins  =     10;
  float xmin =      0;
  float xmax =   1000;
  TString xtitle = "m_{T} [GeV]";
  TString ytitle = "Events / 100 GeV";
  
  for(unsigned int idx_iso=0; idx_iso<iso.size(); idx_iso++){

    cout<<endl<<endl<<"Processing "<<iso[idx_iso]<<endl<<endl;

    SetStyle();
    bool logY = false;
    double lumi = 35867;

    TH1::SetDefaultSumw2();
    TH2::SetDefaultSumw2();

    TH1D * hist[40];

    float bins[50];
    nBins = 8;
    bins[0] = 0;
    bins[1] = 200;
    bins[2] = 250;
    bins[3] = 300;
    bins[4] = 350;
    bins[5] = 400;
    bins[6] = 500;
    bins[7] = 800;
    bins[8] = 10000;
    
    TH1D * observation = new TH1D("observation","",nBins,xmin,xmax); 
    TH1D * prediction  = new TH1D("prediction","",nBins,xmin,xmax); 

    // filling histograms (obs)
    for (unsigned int i=0; i<obs.size(); ++i) {

      TTree* tree = readTree(dir+"/"+obs[i]+".root", "NTuple", iso[idx_iso]);
      int nevtsProcessed = getNEventsProcessed(dir+"/"+obs[i]+".root");
      double norm = obs_xsec[i]*lumi/nevtsProcessed;
      TString histName = obs[i];
      hist[i] = new TH1D(histName,"",nBins,xmin,xmax);
      hist[i]->Sumw2();

      // Loop over tree and fill histogram after cuts
      cout<<"start loop"<<endl;
      for(unsigned int j=0; j<tree->GetEntries(); j++){

	tree->GetEntry(j);
	bool passed = applyCuts(sr);
	if(!passed) continue;

	double weight = puWeight*trigWeight*genWeight*norm*wnorm;
	hist[i]->Fill(mttau, weight);
      }
      cout<<"nEvents = "<<hist[i]->GetSumOfWeights()<<endl;
      observation->Add(hist[i]);
      delete hist[i];
    }
    for (unsigned int i=0; i<pred.size(); ++i) {

      TTree* tree = readTree(dir+"/"+pred[i]+".root", "NTuple", iso[idx_iso]);
      int nevtsProcessed = getNEventsProcessed(dir+"/"+pred[i]+".root");
      double norm = pred_xsec[i]*lumi/nevtsProcessed;
      TString histName = pred[i];
      hist[i] = new TH1D(histName,"",nBins,xmin,xmax);
      hist[i]->Sumw2();

      // Loop over tree and fill histogram after cuts
      for(unsigned int j=0; j<tree->GetEntries(); j++){

	tree->GetEntry(j);
	bool passed = applyCuts(cr_antiiso);
	if(!passed) continue;

	double weight = puWeight*trigWeight*genWeight*norm*wnorm*fakeAntiLiso;

	hist[i]->Fill(mttau, weight);
      }
      prediction->Add(hist[i]);
      delete hist[i];
    }


    std::cout << "Observation : " << observation->GetSumOfWeights() << " (nevents = " << observation->GetEntries() << ") "<<std::endl;
    std::cout << "Prediction : " << prediction->GetSumOfWeights() << " (nevents = " << prediction->GetEntries() << ") "<<std::endl;

    TCanvas * canv1 = MakeCanvas("canv1", "", 700, 800);
    TPad * upper = new TPad("upper", "pad",0,0.31,1,1);
    upper->Draw();
    upper->cd();
    upper->SetFillColor(0);
    upper->SetBorderMode(0);
    upper->SetBorderSize(10);
    upper->SetTickx(1);
    upper->SetTicky(1);
    upper->SetLeftMargin(0.17);
    upper->SetRightMargin(0.05);
    upper->SetBottomMargin(0.02);
    upper->SetFrameFillStyle(0);
    upper->SetFrameLineStyle(0);
    upper->SetFrameLineWidth(2);
    upper->SetFrameBorderMode(0);
    upper->SetFrameBorderSize(10);
    upper->SetFrameFillStyle(0);
    upper->SetFrameLineStyle(0);
    upper->SetFrameLineWidth(2);
    upper->SetFrameBorderMode(0);
    upper->SetFrameBorderSize(10);


    prediction->SetLineColor(kRed);
    prediction->SetMarkerColor(kRed);


    observation->Draw("e1");
    prediction->Draw("sameh");

    TLegend * leg = new TLegend(0.55,0.4,0.85,0.78);
    SetLegendStyle(leg);
    leg->SetTextSize(0.047);
    leg->SetHeader(iso[idx_iso]+"Iso");
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
    ratioH->GetYaxis()->SetRangeUser(0.201,1.799);
    ratioH->GetYaxis()->SetNdivisions(505);
    ratioH->GetXaxis()->SetLabelFont(42);
    ratioH->GetXaxis()->SetLabelOffset(0.04);
    ratioH->GetXaxis()->SetLabelSize(0.14);
    ratioH->GetXaxis()->SetTitleSize(0.13);
    ratioH->GetXaxis()->SetTitleOffset(1.2);
    ratioH->GetYaxis()->SetTitle("obs/exp");
    ratioH->GetYaxis()->SetLabelFont(42);
    ratioH->GetYaxis()->SetLabelOffset(0.015);
    ratioH->GetYaxis()->SetLabelSize(0.13);
    ratioH->GetYaxis()->SetTitleSize(0.14);
    ratioH->GetYaxis()->SetTitleOffset(0.5);
    ratioH->GetXaxis()->SetTickLength(0.07);
    ratioH->GetYaxis()->SetTickLength(0.04);
    ratioH->GetYaxis()->SetLabelOffset(0.01);

    // ------------>Primitives in pad: lower
    TPad * lower = new TPad("lower", "pad",0,0,1,0.30);
    lower->Draw();
    lower->cd();
    lower->SetFillColor(0);
    lower->SetBorderMode(0);
    lower->SetBorderSize(10);
    lower->SetGridy();
    lower->SetTickx(1);
    lower->SetTicky(1);
    lower->SetLeftMargin(0.17);
    lower->SetRightMargin(0.05);
    lower->SetTopMargin(0.026);
    lower->SetBottomMargin(0.35);
    lower->SetFrameFillStyle(0);
    lower->SetFrameLineStyle(0);
    lower->SetFrameLineWidth(2);
    lower->SetFrameBorderMode(0);
    lower->SetFrameBorderSize(10);
    lower->SetFrameFillStyle(0);
    lower->SetFrameLineStyle(0);
    lower->SetFrameLineWidth(2);
    lower->SetFrameBorderMode(0);
    lower->SetFrameBorderSize(10);

    ratioH->Draw("e1");

    lower->Modified();
    lower->RedrawAxis();
    canv1->cd();
    canv1->Modified();
    canv1->cd();
    canv1->SetSelected(canv1);
    canv1->Update();
    canv1->Print("figures/mttau_"+iso[idx_iso]+"Iso_WTauNu.png");
    delete canv1;
    std::cout << std::endl;

  }

}
