#include "HttStylesNew.cc"
#include "CMS_lumi.C"
int PlotWTauNuBkgd() {

  TString dir = "NTuples";
  //TString dir = "/nfs/dust/cms/user/rasp/Run/Run2016/TauID_2016/";
  TString DataFile = "MET_Run2016";
  //TString DataFile = "MET_Run2016BCD";  // Re-Reco
  //TString DataFile = "MET_Run2016BCD-PromptReco";   // PromptReco
  TString Variable = "tauPt";
  TString iso("TightMva");
  int nBins  =     3;
  float bins[4] = {100,150,200,1000};

  TString Weight = "puWeight*genWeight*trigWeight*";

  TString cutsTrigger("trigger>0.5&&");
  TString cutsTopology("Selection==3&&recoilRatio<1.2&&recoilRatio>0.75&&recoilDPhi>2.4&&met>120&&tauPt>100&&");
  TString cutsLeptonVeto("nMuon==0&&nElec==0&&");
  TString cutsJetVeto("nSelTaus==1&&nJetsCentral30<=1&&nJetsForward30==0&&");
  TString cutsTauIso   ("tauDM>0.5&&tauAntiMuonLoose3>0.5&&tauAntiElectronLooseMVA6>0.5&&tau"+iso+"Iso>0.5");
  TString cutsTauInvIso("tauDM>0.5&&tauAntiMuonLoose3>0.5&&tauAntiElectronLooseMVA6>0.5&&tau"+iso+"Iso<0.5");
  TString  cutsTauDecayMode("&&tauGenMatchDecay<0");
  TString cutsTauDecayModeX("&&tauGenMatchDecay>=0");
  
  TString Cuts       = cutsTopology+cutsLeptonVeto+cutsJetVeto+cutsTauIso;
  TString CutsInvIso = cutsTopology+cutsLeptonVeto+cutsJetVeto+cutsTauInvIso;
  TString xtitle = "m_{T} [GeV]";
  TString ytitle = "Events / bin";

  SetStyle();
  bool logY = false;
  //  double lumi = 12980;
  double lumi = 36800;

  TH1::SetDefaultSumw2();
  TH2::SetDefaultSumw2();

  TString sampleNames[18] = {
    DataFile, // data (signal region) (0)
    "WJetsToLNu_13TeV-madgraphMLM", // WToTauNu (1)
    "TTJets_13TeV-powheg",               // TTJets (2) 
    "ST_t-channel_top_4f_inclusiveDecays_13TeV-powheg",     // t-channel_top     (3)
    "ST_t-channel_antitop_4f_inclusiveDecays_13TeV-powheg", // t-channel_antitop (4)
    "ST_tW_top_5f_inclusiveDecays_13TeV-powheg",         // topW              (5)
    "ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg",     // antitopW          (6)
    "VVTo2L2Nu_13TeV_amcatnloFXFX",   // VVTo2L2Nu    (7)
    "WWTo1L1Nu2Q_13TeV_amcatnloFXFX", // WWTo1L1Nu2Q  (8)
    "WZTo1L1Nu2Q_13TeV_amcatnloFXFX", // WZTo1L1Nu2Q  (9)
    "WZTo1L3Nu_13TeV_amcatnloFXFX",   // WZTo1L3Nu    (10)
    "WZTo2L2Q_13TeV_amcatnloFXFX",    // WZTo2L2Q     (11)
    "DYJetsToLL_M-50_13TeV-madgraphMLM", // DYJetsToLL (12)
    "ZJetsToNuNu_HT-100To200_13TeV-madgraph", // ZNuNu-HT100to200 (13)
    "ZJetsToNuNu_HT-200To400_13TeV-madgraph", // ZNuNu-HT200to400 (14)
    "ZJetsToNuNu_HT-400To600_13TeV-madgraph", // ZNuNu-HT400to600 (15)
    "ZJetsToNuNu_HT-600To800_13TeV-madgraph", // ZNuNu-HT600to800 (16)
    ""
  };

  double xsec[18] = {1, // data (signal region)    (0)
		     61526.7,    // WJets (1)
 		     831.76,     // TTJets (2)
		     136.02, // t-channel_top     (3)
		     80.95,  // t-channel_antitop (4)
		     35.6,           // topW              (5)
		     35.6,           // antitopW          (6)
		     11.95,  // VVTo2L2Nu   (7)
		     49.997, // WWTo1L1Nu2Q (8)
		     10.71,  // WZTo1L1Nu2Q (9)
		     3.05,   // WZTo1L3Nu  (10)
		     5.595,  // WZTo2L2Q   (11)
		     5765,   // DYJets     (12)
		     1.164*280.4, // ZNuNu-HT100to200 (13) 
		     1.164*77.67, // ZNuNu-HT200to400 (14)
		     1.164*10.73, // ZNuNu-HT400to600 (15) 
		     1.164*4.116, // ZNuNu-HT600to800 (16)
		     0
  };

  TString  cuts[30];
  TString cutsX[30];
  TString cutsInvIso[30];
  cuts[0]  = cutsTrigger+Cuts+"&&metFilters"; // data
  cutsX[0] = cutsTrigger+Cuts+"&&metFilters"; // data
  cutsInvIso[0] = cutsTrigger+CutsInvIso+"&&metFilters"; // data
  for (int i=1; i<30; ++i) { // MC samples
    cuts[i]       = Weight+"("+cutsTrigger+Cuts+cutsTauDecayMode+")";
    cutsX[i]      = Weight+"("+cutsTrigger+Cuts+cutsTauDecayModeX+")";
    cutsInvIso[i] = Weight+"("+cutsTrigger+CutsInvIso+cutsTauDecayMode+")";
  }
  cuts[1]       = Weight+"("+cutsTrigger+Cuts+cutsTauDecayMode+")";
  cutsX[1]      = Weight+"("+cutsTrigger+Cuts+cutsTauDecayModeX+")";
  cutsInvIso[1] = Weight+"("+cutsTrigger+CutsInvIso+cutsTauDecayMode+")";
 

  TH1D * hist[40];
  TH1D * histX[40];
  TH1D * histInvIso[40];

  TCanvas * dummy = new TCanvas("dummy","",400,400);

  // filling histograms
  float ewkNorm = 0;
  for (int i=0; i<17; ++i) {
    std::cout << sampleNames[i] << std::endl;
    TFile * file = new TFile(dir+"/"+sampleNames[i]+".root");
    TH1D * histWeightsH = (TH1D*)file->Get("histWeightsH");
    TTree * tree = (TTree*)file->Get("NTuple");
    double norm = xsec[i]*lumi/histWeightsH->GetSumOfWeights();
    TString histName = sampleNames[i];
    TString histNameX = sampleNames[i]+"X";
    TString histNameInvIso = sampleNames[i]+"InvIso";
    hist[i] = new TH1D(histName,"",nBins,bins);
    histX[i] = new TH1D(histNameX,"",nBins,bins);
    histInvIso[i] = new TH1D(histNameInvIso,"",nBins,bins);
    hist[i]->Sumw2();
    histX[i]->Sumw2();
    histInvIso[i]->Sumw2();
    tree->Draw(Variable+">>"+histName,cuts[i]);
    tree->Draw(Variable+">>"+histNameX,cutsX[i]);
    tree->Draw(Variable+">>"+histNameInvIso,cutsInvIso[i]);
    if (i>0) {
      hist[i] -> Scale(norm);
      histX[i] -> Scale(norm);
      histInvIso[i] -> Scale(norm);
    }
  }

  delete dummy;

  // adding up top samples
  for (int i=3; i<=6; ++i) {
    hist[2]->Add(hist[2],hist[i]);
    histInvIso[2]->Add(histInvIso[2],histInvIso[i]);
  }

  // adding up electroweak samples (DY+VV)
  for (int i=8; i<=16; ++i) {
    hist[7]->Add(hist[7],hist[i]);
    histInvIso[7]->Add(histInvIso[7],histInvIso[i]);
  }

  // adding up genuine taus
  for (int i=2; i<=16; ++i)
    histX[1]->Add(histX[1],histX[i]);


  float errW = 0.1*histInvIso[1] ->GetSumOfWeights();
  float errZ = 0.1*histInvIso[11]->GetSumOfWeights();
  float errX = histX[1]->GetSumOfWeights();

  std::cout << std::endl;
  std::cout << "Anti-isolated region -> " << std::endl;
  std::cout << "Data    = " << histInvIso[0]->GetSumOfWeights() << std::endl;
  std::cout << "Top     = " << histInvIso[2]->GetSumOfWeights() << std::endl;
  std::cout << "WJets   = " << histInvIso[1]->GetSumOfWeights() << std::endl;
  std::cout << "DY+VV   = " << histInvIso[7]->GetSumOfWeights() << std::endl;
  std::cout << "genuine = " << histX[1]->GetSumOfWeights() << std::endl;
  std::cout << std::endl;
  std::cout << "Isolated region -> " << std::endl;
  std::cout << "Data    = " << hist[0]->GetSumOfWeights() << std::endl;
  std::cout << "Top     = " << hist[2]->GetSumOfWeights() << std::endl;
  std::cout << "WJets   = " << hist[1]->GetSumOfWeights() << std::endl;
  std::cout << "DY+VV   = " << hist[7]->GetSumOfWeights() << std::endl;
  std::cout << std::endl;

  histInvIso[1]->Add(histInvIso[1],histInvIso[7]); // adding DY+VV and W+Jets

  TH1D* h_fEWK = new TH1D("fEWK","fEWK",nBins,bins);
  h_fEWK = (TH1D*) histInvIso[1]->Clone();
  h_fEWK->Divide(histInvIso[0]);
  h_fEWK->SetName("h_fEWK");
  double nEWK_err = 0 ;
  double nData_err = 0;
  double fEWK_err = 0;
  double nData = histInvIso[0]->IntegralAndError(1,nBins,nData_err);
  double nEWK  = histInvIso[1]->IntegralAndError(1,nBins,nEWK_err);
  double fEWK  = histInvIso[1]->IntegralAndError(1,nBins,fEWK_err);

  std::cout << "Fraction of electroweak events in antiisolated region -> " << std::endl;
  std::cout << "EWK (from MC)     = " << nEWK  << " +/- " << nEWK_err << std::endl;
  std::cout << "Total (from data) = " << nData << " +/- " << nData_err << std::endl;
  std::cout << "EWK/Total         = " << fEWK  << " +/- " << fEWK_err << std::endl;
  std::cout << "  pt > 100 GeV    = " << h_fEWK->GetBinContent(1) << " +/- " << h_fEWK->GetBinError(1) << endl;
  std::cout << "  pt > 150 GeV    = " << h_fEWK->GetBinContent(2) << " +/- " << h_fEWK->GetBinError(2) << endl;
  std::cout << "  pt > 200 GeV    = " << h_fEWK->GetBinContent(3) << " +/- " << h_fEWK->GetBinError(3) << endl;
  std::cout << std::endl;

  // Save fraction of EWK events in root file
  TFile* out = new TFile("output/fraction_EWK.root","RECREATE");
  out->cd();
  h_fEWK->Write();
  out->Close();

  return 0;
}
