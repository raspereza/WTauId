#include "HttStylesNew.cc"
#include "CMS_lumi.C"
#include "settings.h"
#include "TStyle.h"
#include "THStack.h"
#include "TLegend.h"

void make2D_mtmuon_ptmuon_Reweighting() {

  SetStyle();
  TH1::SetDefaultSumw2();
  TH2::SetDefaultSumw2();

  initCuts();

  std::vector< std::pair<TString,std::vector<TString>> > samples;
  std::vector<TString> data;
  data.push_back("SingleMuon_Run2016");

  std::vector<TString> nonW;
  nonW.push_back("VVTo2L2Nu_13TeV_amcatnloFXFX");
  nonW.push_back("WWToLNuQQ_13TeV_powheg");
  nonW.push_back("WZTo1L1Nu2Q_13TeV_amcatnloFXFX");
  nonW.push_back("WZTo1L3Nu_13TeV_amcatnloFXFX");
  nonW.push_back("WZTo2L2Q_13TeV_amcatnloFXFX");
  nonW.push_back("DYJetsToLL_M-50_13TeV-madgraphMLM");
  nonW.push_back("ZJetsToNuNu_HT-100To200_13TeV-madgraph");
  nonW.push_back("ZJetsToNuNu_HT-200To400_13TeV-madgraph");
  nonW.push_back("ZJetsToNuNu_HT-400To600_13TeV-madgraph");
  nonW.push_back("ZJetsToNuNu_HT-600To800_13TeV-madgraph");
  nonW.push_back("WZJToLLLNu_13TeV_amcatnloFXFX");
  nonW.push_back("ZZTo2L2Q_13TeV_amcatnloFXFX");
  nonW.push_back("ZZTo4L_13TeV_powheg");
  nonW.push_back("TTJets_13TeV-powheg");
  nonW.push_back("ST_t-channel_top_4f_inclusiveDecays_13TeV-powheg");
  nonW.push_back("ST_t-channel_antitop_4f_inclusiveDecays_13TeV-powheg");
  nonW.push_back("ST_tW_top_5f_inclusiveDecays_13TeV-powheg");
  nonW.push_back("ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg");

  std::vector<TString> WToMuNu;
  WToMuNu.push_back("WToMuNu_M-200_13TeV-pythia8");

  samples.push_back(make_pair("data_obs" , data));
  samples.push_back(make_pair("nonW" , nonW));
  samples.push_back(make_pair("W" , WToMuNu));

  TString var1 = "muonPt";
  TString var2 = "mtmuon";
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
      selectionCuts select = sr_munu;
      makeSelection(dir+"/"+samples[i].second[idx_list]+".root","NTuple",getXSec(samples[i].second[idx_list]),"Tight",select,histo,var1,var1,var2);
      histoSamples->Add(histo);
    }

    histoMap[samples[i].first] = histoSamples;
    cout<<samples[i].first<<" = "<<histoSamples->GetSumOfWeights()<<" ( Entries = "<<histoSamples->GetEntries()<<" )"<<endl<<endl;
  }


  //Subtract non-W background from data
  for(unsigned int i=1; i<=histoMap["data_obs"]->GetNbinsX(); i++){
    for(unsigned int j=1; j<=histoMap["data_obs"]->GetNbinsY(); j++){
      cout<<"data bin content ("<<i<<","<<j<<") = "<<histoMap["data_obs"]->GetBinContent(i,j)<<endl;
      cout<<"nonW bin content ("<<i<<","<<j<<") = "<<histoMap["nonW"]->GetBinContent(i,j)<<endl;
    }
  }
  histoMap["data_obs"] -> Add(histoMap["nonW"],-1);
  histoMap["data_obs"]->Scale(1./histoMap["data_obs"]->Integral());
  histoMap["W"]->Scale(1./histoMap["W"]->Integral());


  TCanvas * canv = new TCanvas("canv","",1000,700);
  canv->SetRightMargin(0.17);
  
  TH2D *weights = 0;
  weights = (TH2D*) histoMap["data_obs"]->Clone("weights");
  weights->Divide((TH2D*)histoMap["W"]);
  weights->SetTitle("");
  weights->GetXaxis()->SetTitle(var1);
  weights->GetYaxis()->SetTitle(var2);

  gStyle->SetPaintTextFormat( "1.3f" ); 
  gStyle->SetTextFont(42);
  //weights->SetMarkerStyle(20);
  weights->SetMarkerSize(1.2);
  weights->Draw("TEXT E COLZ");
  canv->Print("figures/ReweightingWeights_" + var1 + "_" + var2 + "_WToMuNu.pdf");

  // Save histogram in file
  TFile *out = new TFile("output/ReweightingWeights_" + var1 + "_" + var2 + "_WToMuNu.root","RECREATE");
  out->cd();
  weights->Write("weights");
}
