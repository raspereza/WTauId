#include "HttStylesNew.cc"
#include "settings.h"

void ComputeFakeRate() {

  loadWorkingPoints();
  initCuts();

  TString dir("NTuples/");
  SetStyle();
  TH1::SetDefaultSumw2();
  TH2::SetDefaultSumw2();
  int nBins = 3;
  double bins[4] = {100,150,200,500};

  std::vector<TString> samples;
  //samples.push_back("SingleMuon_Run2016");
  //samples.push_back("JetHT_Run2016");
  samples.push_back("WJetsToLNu_13TeV-madgraphMLM");

  std::vector<double> xsec;
  for(unsigned int i=0; i<samples.size(); i++) xsec.push_back( getXSec(samples[i]) );


  /*
    if (isDijet) {
    // ****************** Cuts for dijet events ************************
    selCuts = "Selection==4&&nMuon==0&&nElec==0&&nSelTaus==1&&nJetsCentral30==2&&tauPt>100&&recoilDPhi>2.6&&recoilRatio>0.8&&recoilRatio<1.2&&(pfJet80>0.5||pfJet140>0.5)&&tauPt>100";
    selCutsMC = "Selection==4&&nMuon==0&&nElec==0&&nSelTaus==1&&nJetsCentral30==2&&tauPt>100&&recoilDPhi>2.6&&recoilRatio>0.8&&recoilRatio<1.2&&(pfJet80>0.5||pfJet140>0.5)&&tauPt>100";
    }
  */
  //TString numCuts("&&tauDM>0.5&&tauAntiMuonLoose3&&tauAntiElectronLooseMVA6&&tau"+iso[idx_iso]+">0.5");
  //TString denCuts("&&tauDM>0.5&&tauAntiMuonLoose3&&tauAntiElectronLooseMVA6&&tau"+iso[idx_iso]+"<0.5");

  for (unsigned int i=0; i<samples.size(); ++i) {

    cout<<endl<<"---------- Sample "<<samples[i]<<" processing. ---------- "<<endl<<endl;
    TFile *fileOutput   = new TFile("output/"+samples[i]+"_fakeRate.root","recreate");
      
    for(unsigned int idx_iso=0; idx_iso<iso.size(); idx_iso++){

      cout<<endl<<"Process "<<iso[idx_iso]<<" : "<<endl;
	
      // filling histograms
      TH1D* h_den = new TH1D(samples[i]+"_"+iso[idx_iso]+"_den",samples[i]+"_"+iso[idx_iso]+"_den",nBins,bins);
      TH1D* h_num = new TH1D(samples[i]+"_"+iso[idx_iso]+"_num",samples[i]+"_"+iso[idx_iso]+"_num",nBins,bins);
      makeSelection(dir+"/"+samples[i]+".root","NTuple",xsec[i],iso[idx_iso],cr_fakerate_num,h_num,"tauPt");
      makeSelection(dir+"/"+samples[i]+".root","NTuple",xsec[i],iso[idx_iso],cr_fakerate_den,h_den,"tauPt");
      double numE = 0;
      double denE = 0;
      double num  = h_num -> IntegralAndError(1,h_num->GetNbinsX(),numE);
      double den  = h_den -> IntegralAndError(1,h_den->GetNbinsX(),denE);
      //num = h_num -> GetEntries();
      //den = h_den -> GetEntries();

      cout<<samples[i]<<" : "<<num<<"/"<<den<<" = "<<num/den<<" +/- "<<numE/den<<endl;
      
      h_num->Divide(h_den);
      TGraphErrors * eff = new TGraphErrors(h_num);
      eff->SetMarkerStyle(20+i);
      eff->SetMarkerColor(20+i);
      eff->SetMarkerSize(2);

      TCanvas * canv = new TCanvas("canv","",700,600);
      TH2F * frame = new TH2F("frame","",2,99,501,2,0,0.2);
      frame->GetYaxis()->SetTitle("Fake Rate");
      frame->GetXaxis()->SetTitle("fake tau p_{T} [GeV/c]");
      frame->Draw();
      eff->Draw("epsame");

      TLegend * leg = new TLegend(0.6,0.7,0.85,0.9);
      SetLegendStyle(leg);
      leg->SetHeader(iso[idx_iso]);
      leg->AddEntry(eff,samples[i],"lp");
      leg->Draw();
      canv->Update();
      canv->Print("figures/fakerate_"+samples[i]+"_"+iso[idx_iso]+".png");

      fileOutput->cd("");
      TGraphErrors * fakeRate   = (TGraphErrors*)eff->Clone(samples[i]+"_fakeRate");
      fakeRate->SetName(iso[idx_iso]+"Iso");
      fakeRate->Write(iso[idx_iso]+"Iso");
      delete canv;
    }
    fileOutput->Close();
  }
}
