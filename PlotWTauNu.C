#include "HttStylesNew.cc"
#include "CMS_lumi.C"
void PlotWTauNu() {

  std::vector<TString> iso;
  iso.push_back("VTightMva");
  iso.push_back("TightMva");
  iso.push_back("MediumMva");
  iso.push_back("LooseMva");
  iso.push_back("Tight");
  iso.push_back("Medium");
  iso.push_back("Loose");

  TString DataFile = "MET_Run2016";
  TString Variable = "mttau"; // mT(tau,MET)
  TString dir = "NTuples/"; 
  //TString dir = "/nfs/dust/cms/user/rasp/Run/Run2016/TauID_2016/"; 
  float yUpper = 2000;

  for(unsigned int idx_iso=0; idx_iso<iso.size(); idx_iso++){

    cout<<endl<<endl<<"Processing "<<iso[idx_iso]<<endl<<endl;

    if (iso[idx_iso]=="Tight")
      yUpper = 1200;
    if (iso[idx_iso]=="Medium")
      yUpper = 1600;
    if (iso[idx_iso]=="Loose")
      yUpper = 2200;
    if (iso[idx_iso]=="TightMva")
      yUpper = 1200;
    if (iso[idx_iso]=="MediumMva")
      yUpper = 1600;
    if (iso[idx_iso]=="LooseMva")
      yUpper = 2200;

    bool plotLegend = true;
    bool equidistant = true;

    // Binning and titles of axis
    int nBins  =     10;
    float xmin =      0;
    float xmax =   1000;
    TString xtitle = "m_{T} [GeV]";
    TString ytitle = "Events / 100 GeV";

    TString Weight = "puWeight*genWeight*trigWeight*";
    TString wnorm("1.3*"); // W* K-factor (PYTHIA8 -> NNLO) 
    TString cutsTrigger("trigger>0.5&&");
    //  TString cutsTrigger("");
    TString cutsTopology("Selection==3&&recoilRatio<1.2&&recoilRatio>0.75&&recoilDPhi>2.4&&met>120&&tauPt>100&&");
    //  TString cutsPhi("TMath::Abs(tauPhi)>0.5&&TMath::Abs(tauPhi)<2.6&&");
    TString cutsPhi("");
    TString cutsLeptonVeto("nMuon==0&&nElec==0&&");
    //  TString cutsLeptonVeto("nMuon==0&&");
    TString cutsJetVeto("nSelTaus==1&&nJetsCentral30<=1&&nJetsForward30==0&&");
    TString         cutsTauId("tauDM>0.5&&tauAntiMuonLoose3>0.5&&tauAntiElectronLooseMVA6>0.5&&tau"+iso[idx_iso]+"Iso>0.5");
    TString cutsInverseTauIso("tauDM>0.5&&tauAntiMuonLoose3>0.5&&tauAntiElectronLooseMVA6>0.5&&tau"+iso[idx_iso]+"Iso<0.5");
  
    TString CutsBkg = cutsTopology+cutsPhi+cutsLeptonVeto+cutsJetVeto+cutsInverseTauIso;
    TString CutsSig = cutsTopology+cutsPhi+cutsLeptonVeto+cutsJetVeto+cutsTauId;

    SetStyle();
    bool logY = false;
    double lumi = 36800;

    TH1::SetDefaultSumw2();
    TH2::SetDefaultSumw2();

    TString sampleNames[30] = {
      DataFile, // data (signal region) (0)
      DataFile, // data (bkgd sideband) (1)
      DataFile, // data (fake sys 1 up) (2)
      DataFile, // data (fake sys 2 up) (3)
      DataFile, // data (fake sys 3 up) (4)
      "WToTauNu_M-200_13TeV-pythia8",
      "WJetsToLNu_13TeV-madgraphMLM",           // (6)  WJets (fake taus)
      "WToTauNu_M-200_13TeV-pythia8_tauesUp",   // (7)  W->TauNu (tauES Up) 
      "WToTauNu_M-200_13TeV-pythia8_tauesDown", // (8)  W->TauNu (tauES Down)
      "WToTauNu_M-200_13TeV-pythia8_jesUp",     // (9)  W->TauNu (JES Up)
      "WToTauNu_M-200_13TeV-pythia8_jesDown",   // (10) W->TauNu (JES Down)
      "WToTauNu_M-200_13TeV-pythia8_uesUp",     // (11) 
      "WToTauNu_M-200_13TeV-pythia8_uesDown",   // (12)
      "TTJets_13TeV-powheg",               // TTJets (13) 
      "ST_t-channel_top_4f_inclusiveDecays_13TeV-powheg",     // t-channel_top     (14)
      "ST_t-channel_antitop_4f_inclusiveDecays_13TeV-powheg", // t-channel_antitop (15)
      "ST_tW_top_5f_inclusiveDecays_13TeV-powheg",         // topW              (16)
      "ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg",     // antitopW          (17)
      "VVTo2L2Nu_13TeV_amcatnloFXFX",   // VVTo2L2Nu     (18)
      "WWTo1L1Nu2Q_13TeV_amcatnloFXFX", // WWTo1L1Nu2Q   (19)
      "WZTo1L1Nu2Q_13TeV_amcatnloFXFX", // WZTo1L1Nu2Q   (20)
      "WZTo1L3Nu_13TeV_amcatnloFXFX",   // WZTo1L3Nu     (21)
      "WZTo2L2Q_13TeV_amcatnloFXFX",    // WZTo2L2Q      (22)
      "DYJetsToLL_M-50_13TeV-madgraphMLM", // DYJetsToLL (23)
      "ZJetsToNuNu_HT-100To200_13TeV-madgraph", // ZNuNu-HT100to200 (24)
      "ZJetsToNuNu_HT-200To400_13TeV-madgraph", // ZNuNu-HT200to400 (25)
      "ZJetsToNuNu_HT-400To600_13TeV-madgraph", // ZNuNu-HT400to600 (26)
      "ZJetsToNuNu_HT-600To800_13TeV-madgraph", // ZNuNu-HT600to800 (27)
      "",
      ""
    };

    double xsec[30] = {1, // data (signal region)    (0)
		       1, // data (sideband region)  (1)
		       1, // data (fake nuisance 1)  (2)
		       1, // data (fake nuisance 2)  (3)
		       1, // data (fake nuisance 3)  (4)
		       6.37, //    (5) W->TauNu              (5)
		       61526.7, // (6) WJets (Fakes)         (6)
		       6.37,    // (7) W->TauNu (TauES Up)   (7)
		       6.37,    // (8) W->TauNu (TauES Down) (8)
		       6.37,    // (9) W->TauNu (JES Up)     (9) 
		       6.37,   // (10) W->TauNu (JES Down)   (10)
		       6.37,   // (11) W->TauNu (UES Up)     (11)
		       6.37,   // (12) W->TauNu (UES Down)   (12)
		       831.76,     // TTJets                 (13)
		       136.95*3*0.108, // t-channel_top      (14)
		       80.95*3*0.108,  // t-channel_antitop  (15)
		       35.6,           // topW               (16)
		       35.6,           // antitopW           (17)
		       11.95,  // VVTo2L2Nu   (18)
		       49.997, // WWTo1L1Nu2Q (19)
		       10.71,  // WZTo1L1Nu2Q (20)
		       3.05,   // WZTo1L3Nu   (21)
		       5.595,  // WZTo2L2Q    (22)
		       5765,   // DYJets      (23)
		       1.164*280.4, // ZNuNu-HT100to200 (24) 
		       1.164*77.67, // ZNuNu-HT200to400 (25)
		       1.164*10.73, // ZNuNu-HT400to600 (26) 
		       1.164*4.116, // ZNuNu-HT600toInf (27)
		       0,
		       0
    };

    TString cuts[40];
    for (int i=0; i<40; ++i) {
      cuts[i] = Weight+"("+CutsSig+")&&tauGenMatchDecay>=0";
    }
  
    cuts[0] = cutsTrigger+CutsSig+"&&metFilters";
    cuts[1] = "fakeAntiL"+iso[idx_iso]+"*("+cutsTrigger+CutsBkg+"&&metFilters)";
    cuts[2] = "fakeAntiL"+iso[idx_iso]+"Up1*("+cutsTrigger+CutsBkg+"&&metFilters)";
    cuts[3] = "fakeAntiL"+iso[idx_iso]+"Up2*("+cutsTrigger+CutsBkg+"&&metFilters)";
    cuts[4] = "fakeAntiL"+iso[idx_iso]+"Up3*("+cutsTrigger+CutsBkg+"&&metFilters)";

    cuts[5]  = Weight+wnorm+"("+cutsTrigger+CutsSig+"&&tauGenMatchDecay>=0)";
    cuts[6]  = Weight+wnorm+"("+cutsTrigger+CutsSig+"&&tauGenMatchDecay<0)";
    cuts[7]  = Weight+wnorm+"("+cutsTrigger+CutsSig+"&&tauGenMatchDecay>=0)";
    cuts[8]  = Weight+wnorm+"("+cutsTrigger+CutsSig+"&&tauGenMatchDecay>=0)";
    cuts[9]  = Weight+wnorm+"("+cutsTrigger+CutsSig+"&&tauGenMatchDecay>=0)";
    cuts[10] = Weight+wnorm+"("+cutsTrigger+CutsSig+"&&tauGenMatchDecay>=0)";
    cuts[11] = Weight+wnorm+"("+cutsTrigger+CutsSig+"&&tauGenMatchDecay>=0)";
    cuts[12] = Weight+wnorm+"("+cutsTrigger+CutsSig+"&&tauGenMatchDecay>=0)";

    TH1D * hist[40];

    TCanvas * dummy = new TCanvas("dummy","",400,400);

    float bins[50];
    if (!equidistant) {
      nBins = 8;
      bins[0] = 0;
      bins[1] = 200;
      bins[2] = 250;
      bins[3] = 300;
      bins[4] = 350;
      bins[5] = 400;
      bins[6] = 500;
      bins[7] = 800;
      bins[8] = 1200;
    }

    // filling histograms
    float ewkNorm = 0;
    int nSamples = 27;
    for (int i=0; i<=nSamples; ++i) {
      //    std::cout << sampleNames[i] << std::endl;
      TFile * file = new TFile(dir+"/"+sampleNames[i]+".root");
      TH1D * histWeightsH = (TH1D*)file->Get("histWeightsH");
      TTree * tree = (TTree*)file->Get("NTuple");
      double norm = xsec[i]*lumi/histWeightsH->GetSumOfWeights();
      TString histName = sampleNames[i];
      if (equidistant)
	hist[i] = new TH1D(histName,"",nBins,xmin,xmax);
      else {
	hist[i] = new TH1D(histName,"",nBins,bins); 
      }
      hist[i]->Sumw2();
      tree->Draw(Variable+">>"+histName,cuts[i]);
      std::cout << sampleNames[i] << "  :  " << hist[i]->GetSumOfWeights()*norm << "(" << hist[i]->GetEntries() << ")" << std::endl;
      if (i==6) ewkNorm +=  hist[i]->GetSumOfWeights()*norm;
      if (i>=18&&i<=28) ewkNorm +=  hist[i]->GetSumOfWeights()*norm;
      if (i>4) {
	for (int iB=1; iB<=nBins; ++iB) {
	  double x = hist[i]->GetBinContent(iB);
	  double e = hist[i]->GetBinError(iB);
	  hist[i]->SetBinContent(iB,norm*x);
	  hist[i]->SetBinError(iB,norm*e);
	}
      }
    }

    std::cout << " ewkNorm = " << ewkNorm << std::endl; 

    delete dummy;
  

    // adding up top samples
    for (int i=14; i<=17; ++i) 
      hist[13]->Add(hist[13],hist[i]);

    // adding up electroweak samples
    for (int i=19; i<=27; ++i) 
      hist[18]->Add(hist[18],hist[i]);
  
    TH1D * histData = NULL; 
    histData = (TH1D*)hist[0]->Clone("data_obs");
  
    TH1D * QCD = (TH1D*)hist[1]->Clone("Fakes");
    TH1D * QCDN1Up = (TH1D*)hist[2]->Clone("Fakes_N1Up");
    TH1D * QCDN2Up = (TH1D*)hist[3]->Clone("Fakes_N2Up");
    TH1D * QCDN3Up = (TH1D*)hist[4]->Clone("Fakes_N3Up");
    TH1D * QCDN1Down = (TH1D*)hist[2]->Clone("Fakes_N1Down");
    TH1D * QCDN2Down = (TH1D*)hist[3]->Clone("Fakes_N2Down");
    TH1D * QCDN3Down = (TH1D*)hist[4]->Clone("Fakes_N3Down");
    TH1D * W   = (TH1D*)hist[5]->Clone("W");
    TH1D * WFake = (TH1D*)hist[6]->Clone("WFake");
    TH1D * TT  = (TH1D*)hist[13]->Clone("TT");
    TH1D * EWK  = (TH1D*)hist[18]->Clone("EWK");
    TH1D * Bkgd = (TH1D*)hist[18]->Clone("Bkgd");
    Bkgd->Add(Bkgd,TT);

    TH1D * WTauESUp   = (TH1D*)hist[7]->Clone("W_TauESUp");
    TH1D * WTauESDown = (TH1D*)hist[8]->Clone("W_TauESDown");
    TH1D * WJESUp     = (TH1D*)hist[9]->Clone("W_JESUp");
    TH1D * WJESDown   = (TH1D*)hist[10]->Clone("W_JESDown");
    TH1D * WUESUp     = (TH1D*)hist[11]->Clone("W_UESUp");
    TH1D * WUESDown   = (TH1D*)hist[12]->Clone("W_UESDown");

    for (int iB=1; iB<=nBins; ++iB) {

      float xc = QCD->GetBinContent(iB);
      float xup = QCDN1Up->GetBinContent(iB);
      float xdown = 2*xc - xup;
      QCDN1Down->SetBinContent(iB,xdown);

      xc = QCD->GetBinContent(iB);
      xup = QCDN2Up->GetBinContent(iB);
      xdown = 2*xc - xup;
      QCDN2Down->SetBinContent(iB,xdown);

      xc = QCD->GetBinContent(iB);
      xup = QCDN3Up->GetBinContent(iB);
      xdown = 2*xc - xup;
      QCDN3Down->SetBinContent(iB,xdown);

    }

    // ***************
    // Creating inputs
    // *************** 
    TString BaseName = Variable+"_"+iso[idx_iso]+"Iso_WTauNu";
    TString rootFileName = BaseName+".root";
    TFile * fileInputs = new TFile("output/" + rootFileName,"recreate"); 
    fileInputs->cd("");
    histData->Write("data_obs");
    W->Write("W");
    QCD->Write("Fakes");
    Bkgd->Write("Bkgd");
    QCDN1Up->Write("Fakes_N1Up");
    QCDN2Up->Write("Fakes_N2Up");
    QCDN3Up->Write("Fakes_N3Up");
    QCDN1Down->Write("Fakes_N1Down");
    QCDN2Down->Write("Fakes_N2Down");
    QCDN3Down->Write("Fakes_N3Down");
    WTauESUp->Write("W_TauESUp");
    WTauESDown->Write("W_TauESDown");
    WJESUp->Write("W_JESUp");
    WJESDown->Write("W_JESDown");
    WUESUp->Write("W_UESUp");
    WUESDown->Write("W_UESDown");

    TString binName[31] = {"0","1","2","3","4","5","6","7","8","9","10","11","12","13","14","15","16","17","18","19","20",
			   "","","","","","","","","",""};

    for (int iB=3; iB<=nBins; ++iB) {
      TH1D * WUp = (TH1D*)W->Clone("W_WTauNuBin"+binName[iB]+"Up");
      TH1D * WDown = (TH1D*)W->Clone("W_WTauNuBin"+binName[iB]+"Down");
      float xW = WUp->GetBinContent(iB);
      float eW = WUp->GetBinError(iB);
      WUp->SetBinContent(iB,xW+eW);
      WDown->SetBinContent(iB,xW-eW);
      WUp->Write("W_WTauNuBin"+binName[iB]+"Up");
      WDown->Write("W_WTauNuBin"+binName[iB]+"Down");
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
    textFile << "bin             WtoTauNu  WtoTauNu  WtoTauNu" << std::endl;
    textFile << "process              W       Fakes      Bkgd" << std::endl;
    textFile << "process              0         1          2 " << std::endl;
    textFile << "rate    " << W->GetSumOfWeights() << " " << QCD->GetSumOfWeights() << " " << Bkgd->GetSumOfWeights() << std::endl;
    textFile << "-----------------" << std::endl;
    textFile << "TauES       shape   1.00       -          - " << std::endl;
    textFile << "JES         shape   1.00       -          - " << std::endl;
    textFile << "UES         shape   1.00       -          - " << std::endl;
    textFile << "N1          shape    -       1.00         - " << std::endl;
    textFile << "N2          shape    -       1.00         - " << std::endl;
    textFile << "N3          shape    -       1.00         - " << std::endl;
    textFile << "BkgdNorm      lnN    -         -        1.30" << std::endl;
    for (int iB=3; iB<=nBins; ++iB) {
      textFile << "WTauNuBin" << binName[iB] << "     shape  1.00   -    -  " << std::endl;
    }
    textFile << "tauId  rateParam  WtoTauNu W  1  [0.5,1.0]" << std::endl;
  
    // *******************
    // end creating inputs
    // *******************

    std::cout << "Top : " << TT->GetSumOfWeights() << std::endl;
    std::cout << "EWK : " << EWK->GetSumOfWeights() << std::endl;
    std::cout << "QCD : " << QCD->GetSumOfWeights() << std::endl;
    std::cout << "W   : " << W->GetSumOfWeights() << "( fake taus = " << WFake->GetSumOfWeights() << ")" << std::endl;

    // proper computation of errors
    for (int iB=1; iB<=nBins; ++iB) {
      // fake background
      double x  = hist[1]->GetBinContent(iB);
      double x1 = hist[2]->GetBinContent(iB);
      double x2 = hist[3]->GetBinContent(iB);
      double x3 = hist[4]->GetBinContent(iB);
      double estat = hist[1]->GetBinError(iB);
      double ex1 = x1-x;
      double ex2 = x2-x;
      double ex3 = x3-x;
      double err = TMath::Sqrt(ex1*ex1+ex2*ex2+ex3*ex3+estat*estat);
      QCD->SetBinError(iB,err);
      // W MC
      x  = hist[5]->GetBinContent(iB);
      x1 = hist[7]->GetBinContent(iB);
      x2 = hist[9]->GetBinContent(iB);
      ex1 = x1 - x;
      ex2 = x2 - x;
      estat = hist[5]->GetBinError(iB);
      err = TMath::Sqrt(ex1*ex1+ex2*ex2+estat*estat);
      W->SetBinError(iB,err);    
    }

    EWK->Add(EWK,TT);
    QCD->Add(QCD,EWK);
    W->Add(W,QCD);
    std::cout << "BKG : " << W->GetSumOfWeights() << std::endl;
    std::cout << "DAT : " << histData->GetSumOfWeights() << std::endl;

    TH1D * bkgdErr = (TH1D*)W->Clone("bkgdErr");
    bkgdErr->SetFillStyle(3013);
    bkgdErr->SetFillColor(1);
    bkgdErr->SetMarkerStyle(21);
    bkgdErr->SetMarkerSize(0);  
    if (Variable=="mttau")
      bkgdErr->SetBinError(1,0);
  
    for (int iB=1; iB<=nBins; ++iB) {
      TT->SetBinError(iB,0);
      EWK->SetBinError(iB,0);
      QCD->SetBinError(iB,0);
      W->SetBinError(iB,0);
    }

    InitData(histData);
    InitHist(TT,"","",TColor::GetColor("#9999CC"),1001);
    InitHist(EWK,"","",TColor::GetColor("#6F2D35"),1001);
    InitHist(QCD,"","",TColor::GetColor("#FFCCFF"),1001);
    InitHist(W,"","",TColor::GetColor("#FFCC66"),1001);
    histData->GetXaxis()->SetTitle(xtitle);
    histData->GetYaxis()->SetTitle(ytitle);
    histData->GetYaxis()->SetTitleOffset(1.3);
    histData->GetYaxis()->SetTitleSize(0.06);
    histData->GetYaxis()->SetRangeUser(0,yUpper);

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
    QCD->Draw("sameh");
    EWK->Draw("sameh");
    //  TT->Draw("sameh");
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

    TLegend * leg = new TLegend(0.55,0.4,0.85,0.78);
    SetLegendStyle(leg);
    leg->SetTextSize(0.047);
    leg->SetHeader(iso[idx_iso]+"Iso");
    leg->AddEntry(histData,"Data","lp");
    leg->AddEntry(W,"W#rightarrow#tau#nu","f");
    leg->AddEntry(QCD,"bkgd (fake taus)","f");
    leg->AddEntry(EWK,"bkgd (true taus)","f");
    if (plotLegend)
      leg->Draw();
    writeExtraText = true;
    extraText = "Internal";
    CMS_lumi(upper,4,33); 
    plotchannel("#tau#nu");

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

    for (int iB=1; iB<=nBins; ++iB) {
      float X1 = histData->GetBinContent(iB);
      float X2 = W->GetBinContent(iB);
      ratioErrH->SetBinContent(iB,1.0);
      ratioErrH->SetBinError(iB,0.0);
      float xBkg = bkgdErr->GetBinContent(iB);
      float errBkg = bkgdErr->GetBinError(iB);
      if (xBkg>0) {
	float relErr = errBkg/xBkg;
	ratioErrH->SetBinError(iB,relErr);

      }
      if (X1>0&&X2>0) {
	float e1 = histData->GetBinError(iB);
	float ratio = X1/X2;
	float eratio = e1/X2;
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
    canv1->Print("figures/"+Variable+"_"+iso[idx_iso]+"Iso_WTauNu.png");
    std::cout << std::endl;
    std::cout << "Mean tau pt = " << W->GetMean() << std::endl;
    std::cout << std::endl;

  }

}
