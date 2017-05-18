#include "HttStylesNew.cc"
#include "CMS_lumi.C"
#include "settings.h"
#include "TStyle.h"
#include "THStack.h"
#include "TLegend.h"

void make2D_mttau_pttau_Reweighting() {

  SetStyle();
  TH1::SetDefaultSumw2();
  TH2::SetDefaultSumw2();

  initCuts();

  std::vector< std::pair<TString,std::vector<TString>> > samples;

  std::vector<TString> WToTauNu;
  WToTauNu.push_back("WToTauNu_M-200_13TeV-pythia8");

  samples.push_back(make_pair("W" , WToTauNu));

  TString var1 = "genTauWPt";
  TString var2 = "mtgen";
  const int nbins1 = 6;
  const int nbins2 = 4;
  double bins1[nbins1+1] = {100,200,300,400,500,600,1000};
  double bins2[nbins2+1] = {200,400,600,1000,2000};

  std::map<TString,TH2D*> histoMap;

  for (unsigned int i=0; i<samples.size(); ++i) {
    
    cout<<"Process "<<samples[i].first<<endl;
    
    TH2D* histoSamples = new TH2D(samples[i].first,samples[i].first,nbins1,bins1,nbins2,bins2);
    
    for(unsigned int idx_list=0; idx_list<samples[i].second.size(); idx_list++){

      cout<<".............. Sample : "<<samples[i].second[idx_list]<<endl;

      TH2D* histo = new TH2D(samples[i].second[idx_list],samples[i].second[idx_list],nbins1,bins1,nbins2,bins2);
      selectionCuts select = sr_trueTaus;
      makeSelection(dir+"/"+samples[i].second[idx_list]+".root","NTuple",getXSec(samples[i].second[idx_list]),"Tight",select,histo,var1,var1,var2);
      histoSamples->Add(histo);
    }

    histoMap[samples[i].first] = histoSamples;
    cout<<samples[i].first<<" = "<<histoSamples->GetSumOfWeights()<<" ( Entries = "<<histoSamples->GetEntries()<<" )"<<endl<<endl;
  }


  TCanvas * canv = new TCanvas("canv","",1000,700);
  canv->SetRightMargin(0.17);
  
  TH2D *weights = 0;
  weights = (TH2D*) histoMap["W"]->Clone("weights");
  weights->SetTitle("");
  weights->GetXaxis()->SetTitle(var1);
  weights->GetYaxis()->SetTitle(var2);

  gStyle->SetPaintTextFormat( "1.3f" ); 
  gStyle->SetTextFont(42);
  //weights->SetMarkerStyle(20);
  weights->SetMarkerSize(1.2);
  weights->Draw("TEXT E COLZ");
  canv->Print("figures/ReweightingWeights_" + var1 + "_" + var2 + "_WToTauNu.pdf");

  // Save histogram in file
  TFile *out = new TFile("output/ReweightingWeights_" + var1 + "_" + var2 + "_WToTauNu.root","RECREATE");
  out->cd();
  weights->Write("weights");
}
