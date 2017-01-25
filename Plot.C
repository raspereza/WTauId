#include "HttStylesNew.cc"
#include "CMS_lumi.C"
void Plot() {

  TString dir = "/nfs/dust/cms/user/rasp/Run/Run2016/TauID_2016/";

  TString DataFile = "SingleMuon_Run2016";
  TString Variable = "met";
  int nBins  =  25;
  float xmin =  0;
  float xmax =  500;
  TString Weight("puWeight*genWeight*mueffweight*mutrigweight*");
  //  TString   Cuts("Selection==1&&nMuon==1&&nElec==0&&nJetsCentral30<=1&&nJetsForward30==0&&nSelTaus==1&&tauPt>100&&recoilRatio>0.8&&recoilRatio<1.3&&recoilDPhi>2.4&&mtmuon>40");
  TString   Cuts("Selection==1&&nMuon==1&&nElec==0&&nJetsCentral30<=1&&nJetsForward30==0&&recoilDPhi>2.4&&mtmuon>40");
  //  TString Cuts("Selection==1&&nMuon==1&&nElec==0&&nSelTaus==1&&recoilRatio>0.7&&recoilRatio<1.3&&recoilDPhi>2.4&&mtmuon>40&&tauDM>0.5&&tauAntiMuonLoose3&&tauAntiElectronLooseMVA5");
  //    TString Cuts("Selection==10&&nMuon<=1&&nElec==0&&muonPt>100");
  //  TString cuts("Selection==1&&nMuon==1&&nElec==0&&(nJetsCentral20+nJetsForward30)<=1&&recoilRatio>0.7&&recoilRatio<1.3&&recoilDPhi>2.4&&mtmuon>40");

  TString wnorm("");


  TString xtitle = "";
  TString ytitle = "";

  SetStyle();

  bool logY = true;

  double lumi = 36000;
  //  double lumi = 12892;

  TH1::SetDefaultSumw2();
  TH2::SetDefaultSumw2();
  TString sampleNames[30] = {
    DataFile, // data (0)
    "WJetsToLNu_13TeV-madgraphMLM", // WJets (1)
    "WJetsToLNu_13TeV-madgraphMLM", // WJets (2) (cut on decay mode)
    "WJetsToLNu_13TeV-madgraphMLM", // WJets (3) (JES Up)
    "WJetsToLNu_13TeV-madgraphMLM", // WJets (4) (JES Down)
    "WJetsToLNu_13TeV-madgraphMLM", // WJets (5) (Uncl. E Down)
    "WJetsToLNu_13TeV-madgraphMLM", // WJets (6) (Uncl. E )
    "TTJets_13TeV-powheg",                       // TTJets (7) 
    "ST_t-channel_top_4f_leptonDecays_13TeV-powheg",     // t-channel_top     (8)
    "ST_t-channel_antitop_4f_leptonDecays_13TeV-powheg", // t-channel_antitop (9)
    "ST_tW_top_5f_inclusiveDecays_13TeV-powheg",            // topW              (10)
    "ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg",        // antitopW          (11)
    "VVTo2L2Nu_13TeV_amcatnloFXFX", // WW (12)
    "WWTo1L1Nu2Q_13TeV_amcatnloFXFX", // WZ (13)
    "WZTo1L1Nu2Q_13TeV_amcatnloFXFX", // ZZ (14)
    "DYJetsToLL_M-50_13TeV-madgraphMLM", // DYJets (15)
    "ZJetsToNuNu_HT-100To200_13TeV-madgraph", // ZNuNu-HT100to200 (16)
    "ZJetsToNuNu_HT-200To400_13TeV-madgraph", // ZNuNu-HT200to400 (17)
    "ZJetsToNuNu_HT-400To600_13TeV-madgraph", // ZNuNu-HT400to600 (18)
    "ZJetsToNuNu_HT-600To800_13TeV-madgraph", // ZNuNu-HT600toInf (19)
    "QCD_Pt-20toInf_MuEnrichedPt15_13TeV_pythia8", // QCD Mu-enriched (20)
    "QCD_Pt_50to80_13TeV_pythia8",       // QCD_Pt_50to80    (21)
    "QCD_Pt_80to120_13TeV_pythia8",      // QCD_Pt_80to120   (22)
    "QCD_Pt_120to170_13TeV_pythia8",     // QCD_Pt_120to170  (23)
    "QCD_Pt_170to300_13TeV_pythia8",     // QCD_Pt_170to300  (24)
    "QCD_Pt_300to470_13TeV_pythia8",     // QCD_Pt_300to470  (25) 
    "QCD_Pt_470to600_13TeV_pythia8",     // QCD_Pt_470to600  (26)
    "QCD_Pt_600to800_13TeV_pythia8",     // QCD_Pt_600to800  (27)
    "QCD_Pt_800to1000_13TeV_pythia8",    // QCD_Pt_800to1000 (28)
    "QCD_Pt_15to7000Flat_13TeV_pythia8" // QCD_Pt_15to7000Flat (29)
  };

  double xsec[30] = {1, // data (0)
		     61526.7, // WJets (1)
		     61526.7, // WJets (2) (cut on decay mode)
		     61526.7, // WJets (3) (JES Up)
		     61526.7, // WJets (4) (JES Down)
		     61526.7, // WJets (5) (Uncl. E Up)
		     61526.7, // WJets (6) (Uncl. E Down)
		     831.76, // TTJets (7)
		     136.95*3*0.108, // t-channel_top (8)
		     80.95*3*0.108,  // t-channel_antitop (9)
		     35.6, // topW (10)
		     35.6, // antitopW (11)
		     11.95,  // VV (12)
		     49.997,  // WW (13)
		     10.32,  // WZ (14)
		     5765, // DYJets (15)
		     1.23*280.4, // ZNuNu-HT100to200 (16) 
		     1.23*77.67, // ZNuNu-HT200to400 (17)
		     1.23*10.73,  // ZNuNu-HT400to600 (18) 
		     1.23*4.116, // ZNuNu-HT600toInf (19)
		     1 * 720648000 * 0.0008, // QCD (20)
		     22110000, // QCD_Pt_50to80    (21) 
		     3116000,  // QCD_Pt_80to120   (22) 
		     493200,   // QCD_Pt_120to170  (23)
		     12030,    // QCD_Pt_170to300  (24)
		     7475,     // QCD_Pt_300to470  (25)
		     587.1,    // QCD_Pt_470to600  (26)
		     167,      // QCD_Pt_600to800  (27)
		     28.25,    // QCD_Pt_800to1000 (28)
		     1      // QCD_Pt_15to7000Flat (29)
  };

  TString cuts[30];
  for (int i=0; i<30; ++i) {
    cuts[i] = Weight+"("+Cuts+")";
  }
  cuts[0] = Cuts;
  cuts[1] = Weight+wnorm+"("+Cuts+")";
  cuts[2] = Weight+wnorm+"("+Cuts+"&&WDecay==2)";
  cuts[3] = Weight+wnorm+"("+Cuts+")";
  cuts[4] = Weight+wnorm+"("+Cuts+")";
  cuts[5] = Weight+wnorm+"("+Cuts+")";
  cuts[6] = Weight+wnorm+"("+Cuts+")";

  TH1D * hist[25];

  TCanvas * dummy = new TCanvas("dummy","",400,400);
  
  float bins[7] = {0,100,150,200,300,500,1000};
  if (xmax<0) {
    nBins = 5;
    if (Variable=="mtmuon") {
      nBins = 5;
      bins[0] = 0;
      bins[1] = 200;
      bins[2] = 350;
      bins[3] = 500;
      bins[4] = 750;
      bins[5] = 1000;
    }
  }
  // filling histograms
  for (int i=0; i<20; ++i) {
    TFile * file = new TFile(dir+"/"+sampleNames[i]+".root");
    TH1D * histWeightsH = (TH1D*)file->Get("histWeightsH");
    TTree * tree = (TTree*)file->Get("NTuple");
    double norm = xsec[i]*lumi/histWeightsH->GetSumOfWeights();
    TString histName = sampleNames[i];
    if (i==0) norm = 1;
    if (xmax>0)
      hist[i] = new TH1D(histName,"",nBins,xmin,xmax);
    else {
      hist[i] = new TH1D(histName,"",nBins,bins);
    }
    hist[i]->Sumw2();
    tree->Draw(Variable+">>"+histName,cuts[i]);
    std::cout << sampleNames[i] 
	      << "  events :  " << hist[i]->GetSumOfWeights()*norm 
	      << "(" << hist[i]->GetEntries() << ")"
	      << " ; initial events = " << histWeightsH->GetSumOfWeights() 
	      << " ; weight = " << norm << std::endl;
    if (i>0) {
      float totNorm = 0;
      for (int iB=1; iB<=nBins; ++iB) {
	double x = hist[i]->GetBinContent(iB);
	double e = hist[i]->GetBinError(iB);
    	hist[i]->SetBinContent(iB,norm*x);
    	hist[i]->SetBinError(iB,norm*e);
	if (i==1&&iB==nBins&&x==0) { 
	  hist[i]->SetBinError(iB,norm);
	  hist[i]->SetBinContent(iB,norm);
	}
	totNorm +=  hist[i]->GetBinContent(iB);
      }
    }
  }
  delete dummy;
  
  //  hist[1]->Add(hist[1],hist[2]);

  // adding up top samples
  for (int i=8; i<=11; ++i) 
    hist[7]->Add(hist[7],hist[i]);

  // adding up electroweak samples
  for (int i=13; i<=19; ++i) 
    hist[12]->Add(hist[12],hist[i]);
  
  // adding up QCD samples
  //  for (int i=21; i<=27; ++i) 
  //    hist[20]->Add(hist[20],hist[i]);


  TH1D * histData = (TH1D*)hist[0]->Clone("data_obs");
  //  TH1D * QCD      = (TH1D*)hist[20]->Clone("QCD");
  TH1D * W        = (TH1D*)hist[1]->Clone("W");
  TH1D * WFake    = (TH1D*)hist[2]->Clone("WFake");
  TH1D * TT       = (TH1D*)hist[7]->Clone("TT");
  TH1D * EWK      = (TH1D*)hist[12]->Clone("EWK");

  std::cout << "Top : " << TT->GetSumOfWeights() << std::endl;
  std::cout << "EWK : " << EWK->GetSumOfWeights() << std::endl;
  //  std::cout << "QCD : " << QCD->GetSumOfWeights() << std::endl;
  std::cout << "W   : " << W->GetSumOfWeights() << "  ( non-tau : " << WFake->GetSumOfWeights() << " )" << std::endl;

  float nonW = EWK->GetSumOfWeights()+TT->GetSumOfWeights();
  float Wmeas = histData->GetSumOfWeights() - nonW;
  float scale = Wmeas/W->GetSumOfWeights();

  for (int iB=1; iB<=nBins; ++iB) {
    float TTstat = TT->GetBinError(iB);
    float TTsys = 0.1*TT->GetBinContent(iB);
    float TTtot = TMath::Sqrt(TTstat*TTstat+TTsys*TTsys);
    TT->SetBinError(iB,TTtot);
    EWK->SetBinError(iB,0.2*EWK->GetBinContent(iB));
    //    QCD->SetBinError(iB,0.2*QCD->GetBinContent(iB));
    WFake->SetBinError(iB,0);
    float Wstat = W->GetBinError(iB);
    float Wsys = 0.15*W->GetBinContent(iB);
    float Wtot = TMath::Sqrt(Wstat*Wstat+Wsys*Wsys);
    W->SetBinError(iB,Wtot);
  }
  EWK->Add(EWK,TT);
  //  QCD->Add(QCD,EWK);
  //  W->Add(W,QCD);
  W->Add(W,EWK);
  WFake->Add(WFake,EWK);
  std::cout << "BKG : " << W->GetSumOfWeights() << std::endl;
  std::cout << "DAT : " << histData->GetSumOfWeights() << std::endl;
  std::cout << "Scale W = " << scale << std::endl;

  TH1D * bkgdErr = (TH1D*)W->Clone("bkgdErr");
  bkgdErr->SetFillStyle(3013);
  bkgdErr->SetFillColor(1);
  bkgdErr->SetMarkerStyle(21);
  bkgdErr->SetMarkerSize(0);  
  
  for (int iB=1; iB<=nBins; ++iB) {
    TT->SetBinError(iB,0);
    EWK->SetBinError(iB,0);
    //    QCD->SetBinError(iB,0);
    WFake->SetBinError(iB,0);
    W->SetBinError(iB,0);
  }
  InitData(histData);
  InitHist(TT,"","",TColor::GetColor("#9999CC"),1001);
  InitHist(EWK,"","",TColor::GetColor("#6F2D35"),1001);
  //  InitHist(QCD,"","",TColor::GetColor("#FFCCFF"),1001);
  InitHist(WFake,"","",TColor::GetColor("#FFDD00"),1001);
  InitHist(W,"","",TColor::GetColor("#FFCC66"),1001);
  histData->GetXaxis()->SetTitle(xtitle);
  histData->GetYaxis()->SetTitle(ytitle);
  histData->GetYaxis()->SetTitleOffset(1.3);
  histData->GetYaxis()->SetTitleSize(0.06);
  float yUpper = histData->GetMaximum();
  histData->GetYaxis()->SetRangeUser(0,1.2*yUpper);
  if (logY)
    histData->GetYaxis()->SetRangeUser(10,3*yUpper);

  histData->SetMarkerSize(1.2);
  histData->GetXaxis()->SetLabelSize(0);
  histData->GetYaxis()->SetLabelSize(0.06);

  //  nData = histData->GetSum();
  //  float nMC   = TT->GetSum();
  //  float eData = TMath::Sqrt(nData);


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

  histData->Draw("e1");
  W->Draw("sameh");
  //  WFake->Draw("sameh");
  //  QCD->Draw("sameh");
  EWK->Draw("sameh");
  TT->Draw("sameh");
  histData->Draw("e1same");
  bkgdErr->Draw("e2same");
  float chi2 = 0;
  for (int iB=1; iB<=nBins; ++iB) {
    float xData = histData->GetBinContent(iB);
    float xMC = W->GetBinContent(iB);
    if (xMC>1e-1) {
      float diff2 = (xData-xMC)*(xData-xMC);
      chi2 += diff2/xMC;
    }
  }
  std::cout << std::endl;
  std::cout << "Chi2 = " << chi2 << std::endl;
  std::cout << std::endl;

  TLegend * leg = new TLegend(0.6,0.4,0.82,0.78);
  SetLegendStyle(leg);
  leg->SetTextSize(0.05);
  leg->AddEntry(histData,"Data","lp");
  leg->AddEntry(W,"W#rightarrow#mu#nu","f");
  //  leg->AddEntry(WFake,"W(Fake)","f");
  //  leg->AddEntry(QCD,"QCD","f");
  leg->AddEntry(EWK,"electroweak","f");
  leg->AddEntry(TT,"t#bar{t}+single top","f");
  leg->Draw();
  writeExtraText = true;
  extraText = "Preliminary";
  CMS_lumi(upper,4,33); 
  plotchannel("#mu#nu");

  if (logY) upper->SetLogy(true);
    
  upper->Draw("SAME");
  upper->RedrawAxis();
  upper->Modified();
  upper->Update();
  canv1->cd();

  TH1D * ratioH = (TH1D*)histData->Clone("ratioH");
  TH1D * ratioErrH = (TH1D*)bkgdErr->Clone("ratioErrH");
  ratioH->SetMarkerColor(1);
  ratioH->SetMarkerStyle(20);
  ratioH->SetMarkerSize(1.2);
  ratioH->SetLineColor(1);
  ratioH->GetYaxis()->SetRangeUser(0.2,1.8);
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

  for (int iB=1; iB<=nBins; ++iB) {
    float x1 = histData->GetBinContent(iB);
    float x2 = W->GetBinContent(iB);
    ratioErrH->SetBinContent(iB,1.0);
    ratioErrH->SetBinError(iB,0.0);
    float xBkg = bkgdErr->GetBinContent(iB);
    float errBkg = bkgdErr->GetBinError(iB);
    if (xBkg>0) {
      float relErr = errBkg/xBkg;
      ratioErrH->SetBinError(iB,relErr);

    }
    if (x1>0&&x2>0) {
      float e1 = histData->GetBinError(iB);
      float ratio = x1/x2;
      float eratio = e1/x2;
      ratioH->SetBinContent(iB,ratio);
      ratioH->SetBinError(iB,eratio);
    }
    else {
      ratioH->SetBinContent(iB,1000);
    }
  }

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
  ratioErrH->Draw("e2same");

  lower->Modified();
  lower->RedrawAxis();
  canv1->cd();
  canv1->Modified();
  canv1->cd();
  canv1->SetSelected(canv1);
  canv1->Update();
  canv1->Print("figure/control_"+Variable+".png");


  

}
