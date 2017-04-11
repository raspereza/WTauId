#include "HttStylesNew.cc"
#include "CMS_lumi.C"
#include "settings.h"
#include "TStyle.h"
#include "THStack.h"
#include "TLegend.h"

void WToMuNuMeasurement() {

  TString dir("NTuples/");

  SetStyle();
  TH1::SetDefaultSumw2();
  TH2::SetDefaultSumw2();

  initCuts();

  std::vector< std::pair<TString,std::vector<TString>> > samples;
  std::vector<TString> data;
  data.push_back("SingleMuon_Run2016");

  std::vector<TString> ewk;
  ewk.push_back("VVTo2L2Nu_13TeV_amcatnloFXFX");
  ewk.push_back("WWToLNuQQ_13TeV_powheg");
  ewk.push_back("WZTo1L1Nu2Q_13TeV_amcatnloFXFX");
  ewk.push_back("WZTo1L3Nu_13TeV_amcatnloFXFX");
  ewk.push_back("WZTo2L2Q_13TeV_amcatnloFXFX");
  ewk.push_back("DYJetsToLL_M-50_13TeV-madgraphMLM");
  ewk.push_back("ZJetsToNuNu_HT-100To200_13TeV-madgraph");
  ewk.push_back("ZJetsToNuNu_HT-200To400_13TeV-madgraph");
  ewk.push_back("ZJetsToNuNu_HT-400To600_13TeV-madgraph");
  ewk.push_back("ZJetsToNuNu_HT-600To800_13TeV-madgraph");
  ewk.push_back("WZJToLLLNu_13TeV_amcatnloFXFX");
  ewk.push_back("ZZTo2L2Q_13TeV_amcatnloFXFX");
  ewk.push_back("ZZTo4L_13TeV_powheg");

  std::vector<TString> tt;
  tt.push_back("TTJets_13TeV-powheg");
  tt.push_back("ST_t-channel_top_4f_inclusiveDecays_13TeV-powheg");
  tt.push_back("ST_t-channel_antitop_4f_inclusiveDecays_13TeV-powheg");
  tt.push_back("ST_tW_top_5f_inclusiveDecays_13TeV-powheg");
  tt.push_back("ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg");

  std::vector<TString> WToMuNu;
  WToMuNu.push_back("WToMuNu_M-200_13TeV-pythia8");

  std::vector<TString> WToMuNu_jesUp;
  WToMuNu_jesUp.push_back("WToMuNu_M-200_13TeV-pythia8_jesUp");
  std::vector<TString> WToMuNu_jesDown;
  WToMuNu_jesDown.push_back("WToMuNu_M-200_13TeV-pythia8_jesDown");
  std::vector<TString> WToMuNu_muUp;
  WToMuNu_muUp.push_back("WToMuNu_M-200_13TeV-pythia8_muUp");
  std::vector<TString> WToMuNu_muDown;
  WToMuNu_muDown.push_back("WToMuNu_M-200_13TeV-pythia8_muDown");
  std::vector<TString> WToMuNu_uesUp;
  WToMuNu_uesUp.push_back("WToMuNu_M-200_13TeV-pythia8_uesUp");
  std::vector<TString> WToMuNu_uesDown;
  WToMuNu_uesDown.push_back("WToMuNu_M-200_13TeV-pythia8_uesDown");

  samples.push_back(make_pair("Data" , data));
  samples.push_back(make_pair("EWK" , ewk));
  samples.push_back(make_pair("TT" , tt));
  samples.push_back(make_pair("WToMuNu" , WToMuNu));
  samples.push_back(make_pair("WToMuNu_jesUp" , WToMuNu_jesUp));
  samples.push_back(make_pair("WToMuNu_jesDown" , WToMuNu_jesDown));
  samples.push_back(make_pair("WToMuNu_muUp" , WToMuNu_muUp));
  samples.push_back(make_pair("WToMuNu_muDown" , WToMuNu_muDown));
  samples.push_back(make_pair("WToMuNu_uesUp" , WToMuNu_uesUp));
  samples.push_back(make_pair("WToMuNu_uesDown" , WToMuNu_uesDown));

  TString var = "mtmuon";

  THStack *stack = new THStack("stack_mtmuon","");
  TH1D* h_data = 0;
  std::map<TString,TH1D*> histoMap;

  for (unsigned int i=0; i<samples.size(); ++i) {
    
    cout<<"Process "<<samples[i].first<<endl;
    
    TH1D* histoSamples = new TH1D(samples[i].first,"",10,0,1000);
    
    for(unsigned int idx_list=0; idx_list<samples[i].second.size(); idx_list++){

      cout<<".............. Sample : "<<samples[i].second[idx_list]<<endl;

      TH1D* histo = new TH1D(samples[i].second[idx_list],samples[i].second[idx_list],10,0,1000);
      selectionCuts select = sr_munu;
      makeSelection(dir+"/"+samples[i].second[idx_list]+".root","NTuple",getXSec(samples[i].second[idx_list]),"Tight",select,histo,var,var,var);
      histoSamples->Add(histo);
      histoSamples->SetFillStyle(1001);
      if(samples[i].first.Contains("TT")) histoSamples->SetFillColor(TColor::GetColor("#FFCCFF"));
      else if(samples[i].first.Contains("EWK")) histoSamples->SetFillColor(TColor::GetColor("#6F2D35"));
      else if(samples[i].first.Contains("WToMuNu")) histoSamples->SetFillColor(TColor::GetColor("#FFCC66"));
    }

    histoMap[samples[i].first] = histoSamples;
    if(!samples[i].first.Contains("Data") && !samples[i].first.Contains("Up") && !samples[i].first.Contains("Down")){
      stack->Add(histoSamples);
    }
    else if(samples[i].first.Contains("Data")) h_data = (TH1D*) histoSamples->Clone(); 
    cout<<samples[i].first<<" = "<<histoSamples->GetSumOfWeights()<<" ( Entries = "<<histoSamples->GetEntries()<<" )"<<endl<<endl;
  }

  // ------------------ Computation of all uncertainties : START  -------
  TH1D * bkgdErr = (TH1D*)stack->GetStack()->Last()->Clone("bkgdErr");
  bkgdErr->SetFillStyle(3013);
  bkgdErr->SetFillColor(1);
  bkgdErr->SetMarkerStyle(21);
  bkgdErr->SetMarkerSize(0);  
  double addErr = 0;
  for(int i=1; i<=bkgdErr->GetNbinsX(); i++){
    // 1.) Uncertainty on JES, Mu, UES
    addErr = histoMap["WToMuNu_jesUp"]->GetBinContent(i) - histoMap["WToMuNu"]->GetBinContent(i); 
    bkgdErr->SetBinError(i,sqrt( pow(bkgdErr->GetBinError(i),2) + pow(addErr,2)));      
    addErr = histoMap["WToMuNu_muUp"]->GetBinContent(i) - histoMap["WToMuNu"]->GetBinContent(i); 
    bkgdErr->SetBinError(i,sqrt( pow(bkgdErr->GetBinError(i),2) + pow(addErr,2)));
    addErr = histoMap["WToMuNu_uesUp"]->GetBinContent(i) - histoMap["WToMuNu"]->GetBinContent(i); 
    bkgdErr->SetBinError(i,sqrt( pow(bkgdErr->GetBinError(i),2) + pow(addErr,2)));
  }
  // ------------------ Computation of all uncertainties : END  -------

  TCanvas * canv = new TCanvas("canv","",700,800);
  TPad* upper = new TPad("upper","pad",0,0.29,1,1);
  upper->Draw();
  upper->cd();

  stack->Draw("hist");
  stack->SetMaximum(stack->GetMaximum()*1.4);
  stack->GetXaxis()->SetTitle("m_{T} [GeV]");
  stack->GetYaxis()->SetTitle("Events");
  gPad->Modified(); 
  if(h_data){
    h_data->Draw("e1 same");
    bkgdErr->Draw("e2same");
  }

  TLegend * leg = new TLegend(0.55,0.4,0.85,0.78);
  SetLegendStyle(leg);
  leg->SetTextSize(0.047);
  if(h_data) leg->AddEntry(h_data,"Data","lp");
  if(histoMap["WToMuNu"]) leg->AddEntry(histoMap["WToMuNu"],"W#rightarrow#mu#nu","f");
  if(histoMap["TT"])      leg->AddEntry(histoMap["TT"],"tt + single top","f");
  if(histoMap["EWK"])     leg->AddEntry(histoMap["EWK"],"electroweak","f");
  writeExtraText = true;
  extraText = "Internal";
  CMS_lumi(upper,4,33); 
  leg->Draw("same");

  TH1D * ratioH = 0;
  if(h_data){
    ratioH = (TH1D*) h_data->Clone("ratioH");
    ratioH->Divide((TH1D*)stack->GetStack()->Last());
    ratioH->GetYaxis()->SetTitle("obs/exp");
    ratioH->GetXaxis()->SetTitle("");
    ratioH->GetYaxis()->SetRangeUser(0.4,1.6);
  }
  TH1D * ratioErrH = (TH1D*)bkgdErr->Clone("ratioErrH");
  for(int i=1; i<=bkgdErr->GetNbinsX(); i++){
    ratioErrH->SetBinError(i,bkgdErr->GetBinError(i)/bkgdErr->GetBinContent(i));
    if(bkgdErr->GetBinContent(i)==0) ratioErrH->SetBinError(i,0);
    ratioErrH->SetBinContent(i,1);
  }
  ratioErrH->SetFillStyle(3013);
  ratioErrH->SetFillColor(1);
  ratioErrH->SetMarkerStyle(21);
  ratioErrH->SetMarkerSize(0);  

  canv->cd();
  TPad * lower = new TPad("lower", "pad",0,0,1,0.30);
  lower->SetGridy();
  lower->Draw();
  lower->cd();
  if(h_data) ratioH->Draw("e1");
  ratioErrH->Draw("e2 same");
  canv->cd();
  canv->Modified();
  canv->SetSelected(canv);
  canv->Update();
  canv->Print("figures/" + var + "_WToMuNu.png");


  // Get bin-by-bin uncertainties for WMuNu
  TH1D* histo = 0;
  for(int i =1; i<=histoMap["WToMuNu"]->GetNbinsX(); i++){
    histo = (TH1D*) histoMap["WToMuNu"]->Clone();
    histo->SetBinContent(i,histoMap["WToMuNu"]->GetBinContent(i)+histoMap["WToMuNu"]->GetBinError(i));
    histo->SetName(Form("WToMuNu_Bin%iUp",i));
    histoMap[histo->GetName()] = histo;
    histo = (TH1D*) histoMap["WToMuNu"]->Clone();
    histo->SetBinContent(i,histoMap["WToMuNu"]->GetBinContent(i)-histoMap["WToMuNu"]->GetBinError(i));
    histo->SetName(Form("WToMuNu_Bin%iDown_WToMuNu",i));
    histoMap[histo->GetName()] = histo;
  }

  // Save all histograms in one file
  TFile *out = new TFile("output/" + var + "_WToMuNu_shapes.root","RECREATE");
  out->cd();

  map<TString,TH1D*>::iterator it;
  for ( it = histoMap.begin(); it != histoMap.end(); it++ )
    {
      histoMap[it->first]    ->Write(it->first);
    }    
}
