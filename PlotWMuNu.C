#include "HttStylesNew.cc"
#include "CMS_lumi.C"
void PlotWMuNu() {

  TString dir = "NTuples";
  TString DataFile = "SingleMuon_Run2016";
  TString Variable = "mtmuon";
  int nBins  =   10;
  float xmin =    0;
  float xmax = 1000;
  TString Weight("genWeight*puWeight*mueffweight*mutrigweight*");
  TString wnorm("1.3*"); // K factor for W PYTHIA8 !
  float yUpper = 18000;
  TString Cuts = "Selection==2&&recoilDPhi>2.8&&nSelTaus==0&&met>100&&TMath::Abs(muonEta)<2.1&&muonPt>120&&nElec==0&&nMuon==1&&nJetsCentral30==0&&nJetsForward30==0";
  TString xtitle = "m_{T} [GeV]";
  TString ytitle = "Events / 100 GeV";

  SetStyle();

  bool logY = false;

  double lumi = 35867;
  //  double lumi = 12892; // RunBCD
  //  double lumi = 23808; // RunEFGH
  //  double lumi = 4117; // RunE 
  //  double lumi = 3479; // RunF
  //  double lumi = 7721; // RunG
  //  double lumi = 8857; // RunH

  TH1::SetDefaultSumw2();
  TH2::SetDefaultSumw2();
  TString sampleNames[27] = {
    DataFile, // data (0)
    "WToMuNu_M-200_13TeV-pythia8",         // (1) W->MuNu
    "WToTauNu_M-200_13TeV-pythia8",        // (2) W->TauNu->MuNuNu
    "WToMuNu_M-200_13TeV-pythia8_jesUp",   // (3) W->MuNu (JES Up)
    "WToMuNu_M-200_13TeV-pythia8_jesDown", // (4) W->MuNu (JES Down)
    "WToMuNu_M-200_13TeV-pythia8_uesUp",   // (5) W->MuNu (UES Up)
    "WToMuNu_M-200_13TeV-pythia8_uesDown", // (6) W->MuNu (UES Down)
    "WToMuNu_M-200_13TeV-pythia8_muUp",    // (7) W->MuNu (MuES Up)
    "WToMuNu_M-200_13TeV-pythia8_muDown",  // (8) W->MuNu (MuES Down)
    "TTJets_13TeV-powheg",               // TTJets (9) 
    "ST_t-channel_top_4f_inclusiveDecays_13TeV-powheg",     // t-channel_top     (10)
    "ST_t-channel_antitop_4f_inclusiveDecays_13TeV-powheg", // t-channel_antitop (11)
    "ST_tW_top_5f_inclusiveDecays_13TeV-powheg",         // topW              (12)
    "ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg",     // antitopW          (13)
    "VVTo2L2Nu_13TeV_amcatnloFXFX",   // VVTo2L2Nu    (14)
    "WWToLNuQQ_13TeV_powheg", // WWTo1L1Nu2Q  (15)
    "WZTo1L1Nu2Q_13TeV_amcatnloFXFX", // WZTo1L1Nu2Q  (16)
    "WZTo1L3Nu_13TeV_amcatnloFXFX",   // WZTo1L3Nu    (17)
    "WZTo2L2Q_13TeV_amcatnloFXFX",    // WZTo2L2Q     (18)
    "WZJToLLLNu_13TeV_amcatnloFXFX",  // WZTo3L1Nu     (19) 
    "ZZTo2L2Q_13TeV_amcatnloFXFX",    // ZZTo2L2Q      (20)
    "ZZTo4L_13TeV_powheg",            // ZZTo4L        (21)
    "DYJetsToLL_M-50_13TeV-madgraphMLM", // DYJetsToLL (22)
    "ZJetsToNuNu_HT-100To200_13TeV-madgraph", // ZNuNu-HT100to200 (23)
    "ZJetsToNuNu_HT-200To400_13TeV-madgraph", // ZNuNu-HT200to400 (24)
    "ZJetsToNuNu_HT-400To600_13TeV-madgraph", // ZNuNu-HT400to600 (25)
    "ZJetsToNuNu_HT-600To800_13TeV-madgraph"  // ZNuNu-HT600to800 (26)
  };

  double xsec[27] = {1, // data (0)
		     6.32, // (1) (W->MuNu)
		     6.37, // (2) (W->TauNu->MuNuNu)
		     6.32, // (3) (W->MuNu JES Up)
		     6.32, // (4) (W->MuNu JES Down)
		     6.32, // (5) (W->MuNu UES Up)
		     6.32, // (6) (W->MuNu UES Down)
		     6.32, // (7) (W->MuNu MuonES Up)
		     6.32, // (8) (W->MuNu MuonES Down)
 		     831.76, // TTJets (9)
		     136.95, // t-channel_top     (10)
		     80.95,  // t-channel_antitop (11)
		     35.6,   // topW              (12)
		     35.6,   // antitopW          (13)
		     11.95,  // VVTo2L2Nu   (14)
		     49.997, // WWTo1L1Nu2Q (15)
		     10.71,  // WZTo1L1Nu2Q (16)
		     3.05,   // WZTo1L3Nu   (17)
		     5.595,  // WZTo2L2Q    (18)
		     4.708,  // WZTo3L1Nu   (19)
		     3.22,   // ZZTo2L2Q    (20)
		     1.212,  // ZZTo4L      (21)
		     5765, // DYJets        (22)
		     1.164*280.4, // ZNuNu-HT100to200 (23) 
		     1.164*77.67, // ZNuNu-HT200to400 (24)
		     1.164*10.73, // ZNuNu-HT400to600 (25) 
		     1.164*4.116  // ZNuNu-HT600toInf (26)
  };

  TString cuts[31];
  cuts[0] = Cuts + "&&metFilters";
  //  cuts[0] = Cuts;
  for (int i=1; i<31; ++i) 
    cuts[i] = Weight+"("+Cuts+"&&metFilters)"; // No PU weight
  for (int i=1; i<9; ++i) 
    cuts[i] = Weight+wnorm+"("+Cuts+"&&metFilters)";

  TH1D * hist[31];

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

  int nSamples = 27;

  // filling histograms
  for (int i=0; i<nSamples; ++i) {
    std::cout << sampleNames[i] << std::endl;
    TFile * file = new TFile(dir+"/"+sampleNames[i]+".root");
    TH1D * histWeightsH = (TH1D*)file->Get("histWeightsH");
    TTree * tree = (TTree*)file->Get("NTuple");
    double norm = xsec[i]*lumi/histWeightsH->GetSumOfWeights();
    TString histName = sampleNames[i];
    if (xmax>0)
      hist[i] = new TH1D(histName,"",nBins,xmin,xmax);
    else {
      hist[i] = new TH1D(histName,"",nBins,bins);
    }
    hist[i]->Sumw2();
    tree->Draw(Variable+">>"+histName,cuts[i]);
    std::cout << sampleNames[i] << "  :  " << hist[i]->GetSumOfWeights()*norm << "(" << hist[i]->GetEntries() << ")" << std::endl;
    if (i>0) {
      float totNorm = 0;
      for (int iB=1; iB<=nBins; ++iB) {
	double x = hist[i]->GetBinContent(iB);
	double e = hist[i]->GetBinError(iB);
    	hist[i]->SetBinContent(iB,norm*x);
    	hist[i]->SetBinError(iB,norm*e);
	totNorm +=  hist[i]->GetBinContent(iB);
      }
      //      std::cout << totNorm << std::endl;
    }
  }

  delete dummy;
  
  // adding up top samples
  for (int i=10; i<=13; ++i) 
    hist[9]->Add(hist[9],hist[i]);

  // adding up electroweak samples
  for (int i=15; i<=26; ++i) 
    hist[14]->Add(hist[14],hist[i]);
  
  hist[1]->Add(hist[1],hist[2]); // adding W->TauNu->MuNuNu and W->MuNu
  for (int i=3; i<9; ++i)
    hist[i]->Add(hist[i],hist[2]);

  TH1D * histData = (TH1D*)hist[0]->Clone("data_obs");
  TH1D * W   = (TH1D*)hist[1]->Clone("W");
  TH1D * TT  = (TH1D*)hist[9]->Clone("TT");
  TH1D * EWK  = (TH1D*)hist[14]->Clone("EWK");

  TH1D * WJESUp     = (TH1D*)hist[3]->Clone("W_JESUp");
  TH1D * WJESDown   = (TH1D*)hist[4]->Clone("W_JESDown");
  TH1D * WUESUp     = (TH1D*)hist[5]->Clone("W_UESUp");
  TH1D * WUESDown   = (TH1D*)hist[6]->Clone("W_UESDown");
  TH1D * WMUUp     = (TH1D*)hist[7]->Clone("W_MuUp");
  TH1D * WMUDown   = (TH1D*)hist[8]->Clone("W_MuDown");

  // ***************
  // Creating inputs
  // *************** 
  TString BaseName = Variable+"_WMuNu";
  TString rootFileName = BaseName+".root";
  TFile * fileInputs = new TFile("output/" + rootFileName,"recreate"); 
  fileInputs->cd("");
  histData->Write("data_obs");
  W->Write("W");
  TT->Write("TT");
  EWK->Write("EWK");
  WJESUp->Write("W_JESUp");
  WJESDown->Write("W_JESDown");
  WUESUp->Write("W_UESUp");
  WUESDown->Write("W_UESDown");
  WMUUp->Write("W_MuUp");
  WMUDown->Write("W_MuDown");

  TString binName[31] = {"0","1","2","3","4","5","6","7","8","9","10",
			 "11","12","13","14","15","16","17","18","19","20",
			 "21","22","23","24","25","26","27","28","29","30"};

  for (int iB=3; iB<=nBins; ++iB) {
    TH1D * WUp = (TH1D*)W->Clone("W_WTauNuBin"+binName[iB]+"Up");
    TH1D * WDown = (TH1D*)W->Clone("W_WTauNuBin"+binName[iB]+"Down");
    float xW = WUp->GetBinContent(iB);
    float eW = WUp->GetBinError(iB);
    WUp->SetBinContent(iB,xW+eW);
    WDown->SetBinContent(iB,xW-eW);
    WUp->Write("W_WMuNuBin"+binName[iB]+"Up");
    WDown->Write("W_WMuNuBin"+binName[iB]+"Down");
  }
  fileInputs->Close();

  ostringstream str;
  str << "output/" << BaseName << ".txt";
  string nn = str.str();
  const char * p = nn.c_str();

  std::ofstream textFile(p);
  textFile << "imax 1   number of channels" << std::endl;
  textFile << "jmax *   number of backgrounds" << std::endl;
  textFile << "kmax *   number of nuisance parameters" << std::endl;
  textFile << "-----------------" << std::endl;
  textFile << "observation " << histData->GetSumOfWeights() << std::endl;
  textFile << "-----------------" << std::endl;
  textFile << "shapes * * " << rootFileName << "  $PROCESS    $PROCESS_$SYSTEMATIC " << std::endl;
  textFile << "-----------------" << std::endl;
  textFile << "bin             WtoMuNu    WtoMuNu   WtoMuNu" << std::endl;
  textFile << "process              W          TT       EWK" << std::endl;
  textFile << "process              0          1          2" << std::endl;
  textFile << "rate    " << W->GetSumOfWeights() << " " << TT->GetSumOfWeights() << " " << EWK->GetSumOfWeights() << std::endl;
  textFile << "-----------------" << std::endl;
  textFile << "MuEff         lnN   1.04      1.04      1.04" << std::endl;
  textFile << "JES          shape  1.00       -         -  " << std::endl;
  textFile << "UES          shape  1.00       -         -  " << std::endl;
  textFile << "Mu           shape  1.00       -         -  " << std::endl;
  textFile << "TTnorm         lnN   -        1.15       -  " << std::endl;
  textFile << "EWKnorm        lnN   -         -        1.15" << std::endl;
  for (int iB=3; iB<=nBins; ++iB) {
    textFile << "WMuNuBin" << binName[iB] << "     shape  1.00   -   -  " << std::endl;
  }
  // *******************
  // end creating inputs
  // *******************

  std::cout << "Top : " << TT->GetSumOfWeights() << std::endl;
  std::cout << "EWK : " << EWK->GetSumOfWeights() << std::endl;
  std::cout << "W   : " << W->GetSumOfWeights() << "(W->TauNu = " << hist[2]->GetSumOfWeights() << ")" << std::endl;

  float nonW = EWK->GetSumOfWeights()+TT->GetSumOfWeights();
  float Wmeas = histData->GetSumOfWeights() - nonW;
  float scale = Wmeas/W->GetSumOfWeights();

  for (int iB=1; iB<=nBins; ++iB) {
    float estat =  hist[1]->GetBinError(iB);
    float x0  = hist[1]->GetBinContent(iB);
    float x1 = hist[3]->GetBinContent(iB);
    float x2 = hist[7]->GetBinContent(iB);
    float ex1 = x0 - x1;
    float ex2 = x0 - x2;
    float esys = 0.04*hist[1]->GetBinContent(iB);
    float toterr = TMath::Sqrt(estat*estat+ex1*ex1+ex2*ex2+esys*esys);
    W->SetBinError(iB,toterr);
  }

  EWK->Add(EWK,TT);
  W->Add(W,EWK);
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
    W->SetBinError(iB,0);
  }

  InitData(histData);
  InitHist(TT,"","",TColor::GetColor("#9999CC"),1001);
  InitHist(EWK,"","",TColor::GetColor("#6F2D35"),1001);
  InitHist(W,"","",TColor::GetColor("#FFCC66"),1001);
  histData->GetXaxis()->SetTitle(xtitle);
  histData->GetYaxis()->SetTitle(ytitle);
  //histData->GetYaxis()->SetTitleOffset(1.3);
  //histData->GetYaxis()->SetTitleSize(0.06);
  if (yUpper<0) histData->GetYaxis()->SetRangeUser(0.,1.2*histData->GetMaximum());
  else  histData->GetYaxis()->SetRangeUser(0,yUpper);

  histData->SetMarkerSize(1.2);
  //histData->GetXaxis()->SetLabelSize(0);
  //histData->GetYaxis()->SetLabelSize(0.06);

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

  TLegend * leg = new TLegend(0.62,0.4,0.92,0.78);
  SetLegendStyle(leg);
  leg->SetTextSize(0.05);
  leg->AddEntry(histData,"Data","lp");
  leg->AddEntry(W,"W#rightarrow#mu#nu","f");
  leg->AddEntry(EWK,"electroweak","f");
  leg->AddEntry(TT,"t#bar{t}+single top","f");
  leg->Draw();
  writeExtraText = true;
  extraText = "Internal";
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
  ratioH->GetYaxis()->SetRangeUser(0.401,1.599);
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
  canv1->Print("figures/"+Variable+"_WMuNu.png");
  //  canv1->Print("figures/"+Variable+"_WMuNu.pdf","portrait pdf");

}
