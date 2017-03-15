#include "HttStylesNew.cc"
#include "settings.h"

void ComputeFakeRate() {

  loadWorkingPoints();
  initCuts();

  TString dir("NTuples/");
  SetStyle();
  TH1::SetDefaultSumw2();
  TH2::SetDefaultSumw2();
  int nBins = 10;
  double bins[11] = {100,110,120,130,140,150,160,180,200,300,1000};

  std::vector< std::pair<TString,std::vector<TString>> > samples;
  //samples.push_back("SingleMuon_Run2016");
  //samples.push_back("JetHT_Run2016");
  std::vector<TString> wjets;
  wjets.push_back("WJetsToLNu_13TeV-madgraphMLM");
  wjets.push_back("W1JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8");
  wjets.push_back("W2JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8");
  wjets.push_back("W3JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8");
  wjets.push_back("W4JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8");
  samples.push_back(make_pair("WJetsToLNu_13TeV-madgraphMLM" , wjets));


  for (unsigned int i=0; i<samples.size(); ++i) {

    TFile *fileOutput   = new TFile("output/"+samples[i].first+"_fakeRate.root","recreate");
      
    for(unsigned int idx_iso=0; idx_iso<iso.size(); idx_iso++){

      cout<<endl<<"Process "<<iso[idx_iso]<<" : "<<endl;
      
      // filling histograms
      TH1D* h_den = new TH1D(samples[i].first+"_"+iso[idx_iso]+"_den",samples[i].first+"_"+iso[idx_iso]+"_den",nBins,bins);
      TH1D* h_num = new TH1D(samples[i].first+"_"+iso[idx_iso]+"_num",samples[i].first+"_"+iso[idx_iso]+"_num",nBins,bins);
      
      for(unsigned int idx_list=0; idx_list<samples[i].second.size(); idx_list++){
	cout<<"---------- Sample "<<samples[i].second[idx_list]<<" processing. ---------- "<<endl;
	makeSelection(dir+samples[i].second[idx_list]+".root","NTuple",getXSec(samples[i].second[idx_list]),iso[idx_iso],cr_fakerate_num,h_num,"tauJetPt");
	makeSelection(dir+samples[i].second[idx_list]+".root","NTuple",getXSec(samples[i].second[idx_list]),iso[idx_iso],cr_fakerate_den,h_den,"tauJetPt");
      }

      double numE = 0;
      double denE = 0;
      double num  = h_num -> IntegralAndError(1,h_num->GetNbinsX(),numE);
      double den  = h_den -> IntegralAndError(1,h_den->GetNbinsX(),denE);

      cout<<samples[i].first<<" : "<<num<<"/"<<den<<" = "<<num/den<<" +/- "<<numE/den<<" (nevents = "<<h_num->GetEntries()<<"/"<<h_den->GetEntries()<<")"<<endl<<endl;
      
      h_num->Divide(h_den);
      TGraphErrors * eff = new TGraphErrors(h_num);
      eff->SetMarkerStyle(20+i);
      eff->SetMarkerColor(20+i);
      eff->SetMarkerSize(2);

      TCanvas * canv = new TCanvas("canv","",700,600);
      TH2F * frame = new TH2F("frame","",2,99,1001,2,0,0.2);
      frame->GetYaxis()->SetTitle("Fake Rate");
      frame->GetXaxis()->SetTitle("fake tau p_{T} [GeV/c]");
      frame->Draw();
      eff->Draw("epsame");

      TLegend * leg = new TLegend(0.6,0.7,0.85,0.9);
      SetLegendStyle(leg);
      leg->SetHeader(iso[idx_iso]);
      leg->AddEntry(eff,samples[i].first,"lp");
      leg->Draw();
      canv->Update();
      canv->Print("figures/fakerate_"+samples[i].first+"_"+iso[idx_iso]+".png");

      fileOutput->cd("");
      TGraphErrors * fakeRate   = (TGraphErrors*)eff->Clone(samples[i].first+"_fakeRate");
      fakeRate->SetName(iso[idx_iso]+"Iso");
      fakeRate->Write(iso[idx_iso]+"Iso");
      delete canv;
      cout<<endl;
    }
    fileOutput->Close();
  }
}
