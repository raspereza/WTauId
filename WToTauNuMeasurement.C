#include "HttStylesNew.cc"
#include "CMS_lumi.C"
#include "settings.h"
#include "TStyle.h"
#include "THStack.h"
#include "TLegend.h"

void WToTauNuMeasurement() {

  SetStyle();
  TH1::SetDefaultSumw2();
  TH2::SetDefaultSumw2();

  loadWorkingPoints();
  initCuts();
  loadFakeRates("output/FakeRates_FinerBinning/fakerates" + tauDecayMode + "_FinerBinning.root");
  //loadFakeRates("output/fakerates_GenuineTauSubtraction.root");
  //loadFakeRates("output/fakerates_FINAL.root");

  std::vector< std::pair<TString,std::vector<TString>> > samples;
  std::vector<TString> data_MET;
  data_MET.push_back("MET_Run2016");

  std::vector<TString> trueTaus;
  trueTaus.push_back("TTJets_13TeV-powheg");
  trueTaus.push_back("ST_t-channel_top_4f_inclusiveDecays_13TeV-powheg");
  trueTaus.push_back("ST_t-channel_antitop_4f_inclusiveDecays_13TeV-powheg");
  trueTaus.push_back("ST_tW_top_5f_inclusiveDecays_13TeV-powheg");
  trueTaus.push_back("ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg");
  trueTaus.push_back("VVTo2L2Nu_13TeV_amcatnloFXFX");
  trueTaus.push_back("WWToLNuQQ_13TeV_powheg");
  trueTaus.push_back("WZTo1L1Nu2Q_13TeV_amcatnloFXFX");
  trueTaus.push_back("WZTo1L3Nu_13TeV_amcatnloFXFX");
  trueTaus.push_back("WZTo2L2Q_13TeV_amcatnloFXFX");
  trueTaus.push_back("DYJetsToLL_M-50_13TeV-madgraphMLM");
  trueTaus.push_back("ZJetsToNuNu_HT-100To200_13TeV-madgraph");
  trueTaus.push_back("ZJetsToNuNu_HT-200To400_13TeV-madgraph");
  trueTaus.push_back("ZJetsToNuNu_HT-400To600_13TeV-madgraph");
  trueTaus.push_back("ZJetsToNuNu_HT-600To800_13TeV-madgraph");

  std::vector<TString> fakeTaus;
  fakeTaus.push_back("MET_Run2016");

  std::vector<TString> WToTauNu;
  WToTauNu.push_back("WToTauNu_M-200_13TeV-pythia8");

  std::vector<TString> WToTauNu_jesUp;
  WToTauNu_jesUp.push_back("WToTauNu_M-200_13TeV-pythia8_jesUp");
  std::vector<TString> WToTauNu_jesDown;
  WToTauNu_jesDown.push_back("WToTauNu_M-200_13TeV-pythia8_jesDown");
  std::vector<TString> WToTauNu_taues_1prong0pizerosUp;
  WToTauNu_taues_1prong0pizerosUp.push_back("WToTauNu_M-200_13TeV-pythia8_taues_1prong0pizerosUp");
  std::vector<TString> WToTauNu_taues_1prong0pizerosDown;
  WToTauNu_taues_1prong0pizerosDown.push_back("WToTauNu_M-200_13TeV-pythia8_taues_1prong0pizerosDown");
  std::vector<TString> WToTauNu_taues_1prongUpTo4pizerosUp;
  WToTauNu_taues_1prongUpTo4pizerosUp.push_back("WToTauNu_M-200_13TeV-pythia8_taues_1prongUpTo4pizerosUp");
  std::vector<TString> WToTauNu_taues_1prongUpTo4pizerosDown;
  WToTauNu_taues_1prongUpTo4pizerosDown.push_back("WToTauNu_M-200_13TeV-pythia8_taues_1prongUpTo4pizerosDown");
  std::vector<TString> WToTauNu_taues_3prong0pizerosUp;
  WToTauNu_taues_3prong0pizerosUp.push_back("WToTauNu_M-200_13TeV-pythia8_taues_3prong0pizerosUp");
  std::vector<TString> WToTauNu_taues_3prong0pizerosDown;
  WToTauNu_taues_3prong0pizerosDown.push_back("WToTauNu_M-200_13TeV-pythia8_taues_3prong0pizerosDown");
  std::vector<TString> WToTauNu_uesUp;
  WToTauNu_uesUp.push_back("WToTauNu_M-200_13TeV-pythia8_uesUp");
  std::vector<TString> WToTauNu_uesDown;
  WToTauNu_uesDown.push_back("WToTauNu_M-200_13TeV-pythia8_uesDown");

  for(int i=1; i<=h_fakerate->at("TightMva").GetNbinsX(); i++){
    for(int j=1; j<=h_fakerate->at("TightMva").GetNbinsY(); j++){
      std::vector<TString> fakeTaus_FRUp;
      fakeTaus_FRUp.push_back("MET_Run2016");
      std::vector<TString> fakeTaus_FRDown;
      fakeTaus_FRDown.push_back("MET_Run2016");
      samples.push_back(make_pair(Form("FakeTaus_FR%i%iUp",i,j) , fakeTaus_FRUp));
      samples.push_back(make_pair(Form("FakeTaus_FR%i%iDown",i,j) , fakeTaus_FRDown));
    }
  }
  samples.push_back(make_pair("TrueTaus" , trueTaus));
  samples.push_back(make_pair("FakeTaus" , fakeTaus));
  samples.push_back(make_pair("W" , WToTauNu));
  samples.push_back(make_pair("data_obs" , data_MET));
  samples.push_back(make_pair("W_jesUp" , WToTauNu_jesUp));
  samples.push_back(make_pair("W_jesDown" , WToTauNu_jesDown));
  samples.push_back(make_pair("W_taues_1prong0pizerosUp" , WToTauNu_taues_1prong0pizerosUp));
  samples.push_back(make_pair("W_taues_1prong0pizerosDown" , WToTauNu_taues_1prong0pizerosDown));
  samples.push_back(make_pair("W_taues_1prongUpTo4pizerosUp" , WToTauNu_taues_1prongUpTo4pizerosUp));
  samples.push_back(make_pair("W_taues_1prongUpTo4pizerosDown" , WToTauNu_taues_1prongUpTo4pizerosDown));
  samples.push_back(make_pair("W_taues_3prong0pizerosUp" , WToTauNu_taues_3prong0pizerosUp));
  samples.push_back(make_pair("W_taues_3prong0pizerosDown" , WToTauNu_taues_3prong0pizerosDown));
  samples.push_back(make_pair("W_uesUp" , WToTauNu_uesUp));
  samples.push_back(make_pair("W_uesDown" , WToTauNu_uesDown));

  TString var = "mttau";

  const int nbins = 10;
  double bins[nbins+1] = { 0 , 100 , 200 , 300 , 400 , 500 , 600 , 700 , 800 , 900 , 1000 };

  for(unsigned int idx_iso=0; idx_iso<iso.size(); idx_iso++){

    cout<<endl<<endl<<"--------------------------------------  "<<iso[idx_iso]<<"  ------------------------------------"<<endl;

    THStack *stack = new THStack(iso[idx_iso],"");
    TH1D* h_data = 0;
    std::map<TString,TH1D*> histoMap;

    for (unsigned int i=0; i<samples.size(); ++i) {

      cout<<"Process "<<samples[i].first<<endl;

      TH1D* histoSamples = new TH1D(samples[i].first + "_" + iso[idx_iso],"",nbins,bins);

      for(unsigned int idx_list=0; idx_list<samples[i].second.size(); idx_list++){

	cout<<".............. Sample : "<<samples[i].second[idx_list]<<endl;

	TH1D* histo = new TH1D(samples[i].second[idx_list],samples[i].second[idx_list],nbins,bins);
	selectionCuts select = sr_trueTaus;
	if( samples[i].first.Contains("FakeTaus") ){
	  select =  cr_antiiso;
	  select.name = "cr_antiiso_" + samples[i].first(11,samples[i].first.Length()); 
	}
	makeSelection(dir+"/"+samples[i].second[idx_list]+".root","NTuple",getXSec(samples[i].second[idx_list]),iso[idx_iso],select,histo,var,var,var);
	//cout<<"------------------------------------------------------------- Mean "<<var<<" = "<<histo->GetMean()<<endl;
	histoSamples->Add(histo);
	histoSamples->SetFillStyle(1001);
	if(samples[i].first.Contains("FakeTaus")) histoSamples->SetFillColor(TColor::GetColor("#FFCCFF"));
	else if(samples[i].first.Contains("TrueTaus")) histoSamples->SetFillColor(TColor::GetColor("#6F2D35"));
	else if(samples[i].first.Contains("W")) histoSamples->SetFillColor(TColor::GetColor("#FFCC66"));
	delete histo;
      }

      histoMap[samples[i].first] = histoSamples;
      if(!samples[i].first.Contains("data_obs") && !samples[i].first.Contains("Up") && !samples[i].first.Contains("Down")){
	stack->Add(histoSamples);
      }
      else if(samples[i].first.Contains("data_obs")){
	h_data = (TH1D*) histoSamples->Clone(); 
	h_data -> SetDirectory(0);
      }
      cout<<samples[i].first<<" = "<<histoSamples->Integral()<<" ( Entries = "<<histoSamples->GetEntries()<<" ) "<<endl<<endl;
    }

    // ------------------ Computation of all uncertainties : START  -------
    TH1D * bkgdErr = (TH1D*)stack->GetStack()->Last()->Clone("bkgdErr");
    bkgdErr->SetFillStyle(3013);
    bkgdErr->SetFillColor(1);
    bkgdErr->SetMarkerStyle(21);
    bkgdErr->SetMarkerSize(0);
    double addErr = 0;
    for(int i=1; i<=bkgdErr->GetNbinsX(); i++){
      // 1.) Uncertainty on JES, TauES, UES
      addErr = histoMap["W_jesUp"]->GetBinContent(i) - histoMap["W"]->GetBinContent(i); 
      bkgdErr->SetBinError(i,sqrt( pow(bkgdErr->GetBinError(i),2) + pow(addErr,2)));      
      addErr = histoMap["W_taues_1prong0pizerosUp"]->GetBinContent(i) - histoMap["W"]->GetBinContent(i); 
      bkgdErr->SetBinError(i,sqrt( pow(bkgdErr->GetBinError(i),2) + pow(addErr,2)));
      addErr = histoMap["W_taues_1prongUpTo4pizerosUp"]->GetBinContent(i) - histoMap["W"]->GetBinContent(i); 
      bkgdErr->SetBinError(i,sqrt( pow(bkgdErr->GetBinError(i),2) + pow(addErr,2)));
      addErr = histoMap["W_taues_3prong0pizerosUp"]->GetBinContent(i) - histoMap["W"]->GetBinContent(i); 
      bkgdErr->SetBinError(i,sqrt( pow(bkgdErr->GetBinError(i),2) + pow(addErr,2)));
      addErr = histoMap["W_uesUp"]->GetBinContent(i) - histoMap["W"]->GetBinContent(i); 
      bkgdErr->SetBinError(i,sqrt( pow(bkgdErr->GetBinError(i),2) + pow(addErr,2)));
      // 2.) Tau normalization uncertainty
      addErr = 0.3*histoMap["TrueTaus"]->GetBinContent(i);
      bkgdErr->SetBinError(i,sqrt( pow(bkgdErr->GetBinError(i),2) + pow(addErr,2)));
      // 3.) Fake rate uncertainty
      map<TString,TH1D*>::iterator it;
      for ( it = histoMap.begin(); it != histoMap.end(); it++ )
	{
	  if(it->first.Contains("FR") && it->first.Contains("Up")){
	    addErr = it->second->GetBinContent(i) - histoMap["FakeTaus"]->GetBinContent(i);
	    bkgdErr->SetBinError(i,sqrt( pow(bkgdErr->GetBinError(i),2) + pow(addErr,2)));
	  }
	}
    }
    // ------------------ Computation of all uncertainties : END  -------
    TCanvas * canv = new TCanvas("canv","",700,800);
    TPad* upper = new TPad("upper","pad",0,0.19,1,1);
    upper->Draw();
    upper->cd();

    if(stack->GetMaximum()>h_data->GetMaximum()){    
      h_data->SetMaximum(stack->GetMaximum()*1.2);
    }
    h_data->GetXaxis()->SetTitle("");
    h_data->GetYaxis()->SetTitle("Events");
    h_data->GetXaxis()->SetLabelSize(0.);
    //h_data->SetMaximum(1400);
    h_data->Draw("e1");
    stack->Draw("hist same");
    gPad->Modified(); 
    if(h_data){
      h_data->Draw("e1 same");
      bkgdErr->Draw("e2same");
    }

    TLegend * leg = new TLegend(0.56,0.49,0.83,0.83);
    SetLegendStyle(leg);
    leg->SetHeader(iso[idx_iso]);
    if(h_data)               leg->AddEntry(h_data,"Data","lp");
    if(histoMap["W"])        leg->AddEntry(histoMap["W"],"W#rightarrow#tau#nu","f");
    if(histoMap["FakeTaus"]) leg->AddEntry(histoMap["FakeTaus"],"bkgd (fake taus)","f");
    if(histoMap["TrueTaus"]) leg->AddEntry(histoMap["TrueTaus"],"bkgd (true taus)","f");
    writeExtraText = true;
    extraText = "Preliminary";
    CMS_lumi(upper,4,33); 
    leg->Draw("same");

    TH1D * ratioH = 0;
    if(h_data){
      ratioH = (TH1D*) h_data->Clone("ratioH");
      ratioH->Divide((TH1D*)stack->GetStack()->Last());
      ratioH->GetYaxis()->SetTitle("Obs./Exp.");
      ratioH->GetXaxis()->SetTitle("m_{T} [GeV]");
      //ratioH->GetXaxis()->SetTitle(var);
      ratioH->GetXaxis()->SetTitleOffset(3.5);
      ratioH->GetYaxis()->SetNdivisions(505);
      ratioH->GetYaxis()->SetRangeUser(0.4,1.6);
      ratioH->GetYaxis()->CenterTitle();
      ratioH->GetXaxis()->SetLabelSize(30);
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
    TPad * lower = new TPad("lower", "pad",0,0.0,1,0.31);
    lower->SetBottomMargin(0.32);
    lower->SetGridy();
    lower->Draw();
    lower->cd();
    if(h_data) ratioH->Draw("e1");
    ratioErrH->Draw("e2 same");
    //ratioErrH->Draw("same");
    canv->cd();
    canv->Modified();
    canv->SetSelected(canv);
    canv->Update();
    canv->Print("figures/" + var + "_" + iso[idx_iso] + "_WToTauNu" + tauDecayMode + "_prefit.pdf");

    // Get bin-by-bin uncertainties for WTauNu
    TH1D* histo = 0;
    for(int i =1; i<=histoMap["W"]->GetNbinsX(); i++){
      histo = (TH1D*) histoMap["W"]->Clone();
      histo->SetBinContent(i,histoMap["W"]->GetBinContent(i)+histoMap["W"]->GetBinError(i));
      histo->SetName(Form("W_Bin%i_WToTauNuUp",i));
      histoMap[histo->GetName()] = histo;
      histo = (TH1D*) histoMap["W"]->Clone();
      histo->SetBinContent(i,histoMap["W"]->GetBinContent(i)-histoMap["W"]->GetBinError(i));
      histo->SetName(Form("W_Bin%i_WToTauNuDown",i));
      histoMap[histo->GetName()] = histo;
    }
    for(int i =1; i<=histoMap["FakeTaus"]->GetNbinsX(); i++){
      histo = (TH1D*) histoMap["FakeTaus"]->Clone();
      histo->SetBinContent(i,histoMap["FakeTaus"]->GetBinContent(i)+histoMap["FakeTaus"]->GetBinError(i));
      histo->SetName(Form("FakeTaus_Bin%i_FakeTausUp",i));
      histoMap[histo->GetName()] = histo;
      histo = (TH1D*) histoMap["FakeTaus"]->Clone();
      histo->SetBinContent(i,histoMap["FakeTaus"]->GetBinContent(i)-histoMap["FakeTaus"]->GetBinError(i));
      histo->SetName(Form("FakeTaus_Bin%i_FakeTausDown",i));
      histoMap[histo->GetName()] = histo;
    }
    for(int i =1; i<=histoMap["TrueTaus"]->GetNbinsX(); i++){
      histo = (TH1D*) histoMap["TrueTaus"]->Clone();
      histo->SetBinContent(i,histoMap["TrueTaus"]->GetBinContent(i)+histoMap["TrueTaus"]->GetBinError(i));
      histo->SetName(Form("TrueTaus_Bin%i_TrueTausUp",i));
      histoMap[histo->GetName()] = histo;
      histo = (TH1D*) histoMap["TrueTaus"]->Clone();
      histo->SetBinContent(i,histoMap["TrueTaus"]->GetBinContent(i)-histoMap["TrueTaus"]->GetBinError(i));
      histo->SetName(Form("TrueTaus_Bin%i_TrueTausDown",i));
      histoMap[histo->GetName()] = histo;
    }

    // Save all histograms in one file
    TFile *out = new TFile("output/" + var + "_" + iso[idx_iso] + "_WToTauNu_shapes" + tauDecayMode + ".root","RECREATE");
    out->cd();

    map<TString,TH1D*>::iterator it;
    for ( it = histoMap.begin(); it != histoMap.end(); it++ )
      {
	histoMap[it->first]    ->Write(it->first);
      }    
    delete canv;
  }
}
