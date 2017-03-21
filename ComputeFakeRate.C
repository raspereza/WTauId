#include "HttStylesNew.cc"
#include "settings.h"

void ComputeFakeRate() {

  loadWorkingPoints();
  initCuts();

  TString dir("NTuples/");
  SetStyle();
  TH1::SetDefaultSumw2();
  TH2::SetDefaultSumw2();
  const int nBinsRatio = 7;
  double binsRatio[nBinsRatio+1] = {0,0.4,0.5,0.6,0.7,0.8,0.9,2.};
  const int nBinsJetPt = 1;
  double binsJetPt[nBinsJetPt+1] = {0,10000};
  TH2D* h_fakerate_2d = new TH2D("h_fakerate_2d","h_fakerate_2d",nBinsRatio,binsRatio,nBinsJetPt,binsJetPt);

  std::vector< std::pair<TString,std::vector<TString>> > samples;
  std::vector<TString> data_SingleMuon;
  data_SingleMuon.push_back("SingleMuon_Run2016");
  std::vector<TString> data_JetHT;
  data_JetHT.push_back("JetHT_Run2016");
  std::vector<TString> wjets;
  wjets.push_back("WJetsToLNu_13TeV-madgraphMLM");
  wjets.push_back("W1JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8");
  wjets.push_back("W2JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8");
  wjets.push_back("W3JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8");
  wjets.push_back("W4JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8");

  samples.push_back(make_pair("WJetsToLNu_13TeV-madgraphMLM" , wjets));
  //samples.push_back(make_pair("SingleMuon_Run2016" , data_SingleMuon));
  //samples.push_back(make_pair("JetHT_Run2016" , data_JetHT));

  for (unsigned int i=0; i<samples.size(); ++i) {

    TFile *fileOutput   = new TFile("output/"+samples[i].first+"_fakeRate.root","recreate");
      
    for(unsigned int idx_iso=0; idx_iso<iso.size(); idx_iso++){

      cout<<endl<<"Process "<<iso[idx_iso]<<" : "<<endl;
      
      // filling histograms
      TH2D* h_den = new TH2D(samples[i].first+"_"+iso[idx_iso]+"_den",samples[i].first+"_"+iso[idx_iso]+"_den",nBinsRatio,binsRatio,nBinsJetPt,binsJetPt);
      TH2D* h_num = new TH2D(samples[i].first+"_"+iso[idx_iso]+"_num",samples[i].first+"_"+iso[idx_iso]+"_num",nBinsRatio,binsRatio,nBinsJetPt,binsJetPt);

      TString var1 = "tauPt";
      TString var2 = "tauJetPt";
      TString var3 = "tauJetPt";
      for(unsigned int idx_list=0; idx_list<samples[i].second.size(); idx_list++){
	cout<<"---------- Sample "<<samples[i].second[idx_list]<<" processing. ---------- "<<endl;
	selectionCuts select = cr_fakerate_num;
	if(samples[i].second[idx_list].Contains("JetHT")) select =  cr_fakerate_dijet_num;
	makeSelection(dir+samples[i].second[idx_list]+".root","NTuple",getXSec(samples[i].second[idx_list]),iso[idx_iso],select,h_num,var1,var2,var3);
	select = cr_fakerate_den;
	if(samples[i].second[idx_list].Contains("JetHT")) select =  cr_fakerate_dijet_den;
	makeSelection(dir+samples[i].second[idx_list]+".root","NTuple",getXSec(samples[i].second[idx_list]),iso[idx_iso],select,h_den,var1,var2,var3);
      }

      double numE = 0;
      double denE = 0;
      double num  = h_num -> IntegralAndError(1,h_num->GetNbinsX(),1,h_num->GetNbinsY(),numE);
      double den  = h_den -> IntegralAndError(1,h_den->GetNbinsX(),1,h_den->GetNbinsY(),denE);

      cout<<samples[i].first<<" : "<<num<<"/"<<den<<" = "<<num/den<<" +/- "<<numE/den<<" (nevents = "<<h_num->GetEntries()<<"/"<<h_den->GetEntries()<<")"<<endl<<endl;
      
      h_fakerate_2d -> Divide(h_num,h_den);

      h_fakerate_2d->GetXaxis()->SetTitle("pt (tau) / pt (jet faking the tau)");
      h_fakerate_2d->GetYaxis()->SetTitle("pt (jet faking the tau)");
      h_fakerate_2d->GetZaxis()->SetTitle("fake rate");
      h_fakerate_2d->SetTitle("");
      h_fakerate_2d->SetMarkerSize(2);
      h_fakerate_2d->SetMaximum(1);
      h_fakerate_2d->SetMinimum(0);

      // Fit the fakerate
      /*
      TF1* f = new TF1("func","expo(0)");
      eff->Fit("func","IR","",0.5,1);
      cout<<"Chi2 = "<<f->GetChisquare()<<endl;
      cout<<"NFD  = "<<f->GetNDF()<<endl;
      f->SetLineColor(kRed);
      */
      TCanvas * canv = new TCanvas("canv","",700,600);
      h_fakerate_2d->Draw("COLZ");

      TLegend * leg = new TLegend(0.25,0.7,0.85,0.9);
      gStyle->SetLegendTextSize(0.04);
      SetLegendStyle(leg);
      leg->SetHeader(iso[idx_iso]);
      leg->AddEntry(h_fakerate_2d,samples[i].first,"lp");
      leg->Draw();
      canv->Update();
      canv->Print("figures/fakerate_"+samples[i].first+"_"+iso[idx_iso]+".png");
      
      fileOutput->cd("");
      h_fakerate_2d->SetName(iso[idx_iso]+"Iso");
      h_fakerate_2d->Write(iso[idx_iso]+"Iso");
      delete canv;
      cout<<endl;
    }
    fileOutput->Close();
  }
}
