#include "HttStylesNew.cc"

void ComputeFakeRate(TString iso="TightMvaIso",
		     bool isDijet = true) {

  //  TString iso("VTightMvaIso");
  //  TString iso("TightMvaIso");
  //  TString iso("MediumMvaIso");
  //  TString iso("LooseMvaIso");
  //  TString iso("TightIso");
  //  TString iso("MediumIso");
  //  TString iso("LooseIso");

  TString dir("/nfs/dust/cms/user/rasp/Run/Run2016/TauID_2016/");

  //  TString DataFile("JetHT_Run2016");
  TString DataFile("SingleMuon_Run2016");
  TString suffix("_wjets");
  if (isDijet) {
      DataFile="JetHT_Run2016";
      suffix = "_dijet";
  }

  // ****************** Cuts for W->muv+jet ************************
  TString   selCuts("Selection==1&&nMuon==1&&nElec==0&&nJetsCentral30<=1&&nJetsForward30==0&&nSelTaus==1&&tauPt>100&&recoilRatio>0.7&&recoilRatio<1.3&&recoilDPhi>2.4&&mtmuon>40"); 
  TString selCutsMC("Selection==1&&nMuon==1&&nElec==0&&nJetsCentral30<=1&&nJetsForward30==0&&nSelTaus==1&&tauPt>100&&recoilRatio>0.7&&recoilRatio<1.3&&recoilDPhi>2.4&&mtmuon>40");

  if (isDijet) {
  // ****************** Cuts for dijet events ************************
    selCuts = "Selection==4&&nMuon==0&&nElec==0&&nSelTaus==1&&nJetsCentral30<=2&&tauPt>100&&recoilDPhi>2.6&&recoilRatio>0.8&&recoilRatio<1.2&&(pfJet80>0.5||pfJet140>0.5)&&tauPt>100";
    selCutsMC = "Selection==4&&nMuon==0&&nElec==0&&nSelTaus==1&&nJetsCentral30<=2&&tauPt>100&&recoilDPhi>2.6&&recoilRatio>0.8&&recoilRatio<1.2&&(pfJet80>0.5||pfJet140>0.5)&&tauPt>100";
  }

  //  TString numCuts("&&tauDM>0.5&&tauLeadingTrackPt>4&&tauAntiMuonLoose3&&tauAntiElectronLooseMVA6&&tau"+iso+">0.5");
  //  TString denCuts("&&tauDM>0.5&&tauLeadingTrackPt>4&&tauAntiMuonLoose3&&tauAntiElectronLooseMVA6&&tau"+iso+"<0.5");
  TString numCuts("&&tauDM>0.5&&tauAntiMuonLoose3&&tauAntiElectronLooseMVA6&&tau"+iso+">0.5");
  TString denCuts("&&tauDM>0.5&&tauAntiMuonLoose3&&tauAntiElectronLooseMVA6&&tau"+iso+"<0.5");
  TString mcCuts("&&tauGenMatchDecay<0");
  //  TString mcCuts("");

  SetStyle();
  TH1::SetDefaultSumw2();
  TH2::SetDefaultSumw2();

  bool logY = false;
  double lumi = 36800;
    
  TString sampleNames[30] = {
    DataFile, // data (0)
    "WJetsToLNu_13TeV-madgraphMLM",
    //    "WJetsToLNu_HT-Lt100_13TeV-madgraphMLM-pythia8", // WJets (HT<100) (1)
    "WJetsToLNu_HT-100To200_13TeV-madgraphMLM-pythia8", // WJets (100<HT<200) (2)
    "WJetsToLNu_HT-200To400_13TeV-madgraphMLM-pythia8", // WJets (100<HT<200) (3)
    "WJetsToLNu_HT-400To600_13TeV-madgraphMLM-pythia8", // WJets (100<HT<200) (4)
    "WJetsToLNu_HT-600ToInf_13TeV-madgraphMLM-pythia8", // WJets (100<HT<200) (5)
    "DYJetsToLL_M-50_13TeV-madgraphMLM-pythia8", // DYJets (6)
    "TTJets_13TeV-powheg", // TTJets (7) 
    "ST_t-channel_top_13TeV_powheg_pythia8", // t-channel_top (8)
    "ST_t-channel_antitop_13TeV_powheg_pythia8", // t-channel_antitop (9)
    "ST_tW_top_13TeV_powheg_pisoythia8", // topW (10)
    "ST_tW_antitop_13TeV_powheg_pythia8", // antitopW (11)
    "WW_13TeV_pythia8", // WW (12)
    "WZ_13TeV_pythia8", // WZ (13)
    "ZZ_13TeV_pythia8", // ZZ (14)
    "ZJetsToNuNu_HT-100To200_13TeV-madgraph", // ZNuNu-HT100to200 (15)
    "ZJetsToNuNu_HT-200To400_13TeV-madgraph", // ZNuNu-HT200to400 (16)
    "ZJetsToNuNu_HT-400To600_13TeV-madgraph", // ZNuNu-HT400to600 (17)
    "ZJetsToNuNu_HT-600ToInf_13TeV-madgraph", // ZNuNu-HT600toInf (18)
    "QCD_Pt_50to80_13TeV_pythia8", // QCD_Pt_50to80 (19)
    "QCD_Pt_80to120_13TeV_pythia8", // QCD_Pt_80to120 (20)
    "QCD_Pt_120to170_13TeV_pythia8", // QCD_Pt_120to170 (21)
    "QCD_Pt_170to300_13TeV_pythia8", // QCD_Pt_170to300 (22)
    "QCD_Pt_300to470_13TeV_pythia8", // QCD_Pt_300to470 (23) 
    "QCD_Pt_470to600_13TeV_pythia8", // QCD_Pt_470to600 (24)
    "QCD_Pt_600to800_13TeV_pythia8", // QCD_Pt_600to800 (25)
    "QCD_Pt_800to1000_13TeV_pythia8", // QCD_Pt_800to1000 (26)
    "",
    "",
    ""
  };

  double xsec[30] = {1, // data (0)
		     61526.7,    // WJets (1)
		     1.22*1345,  // WJets (2)
		     1.22*359.7, // WJets (3)
		     1.22*48.91, // WJets (4)
		     1.22*18.77, // WJets (5)
		     6025.2, // DYJets (6)
		     831.76, // TTJets (7)
		     136.95*3*0.108, // t-channel_top     (8)
		     80.95*3*0.108,  // t-channel_antitop (9)
		     35.6,           // topW             (10)
		     35.6,          // antitopW          (11)
		     63.21, // WW (12)
		     22.82, // WZ (13)
		     10.32, // ZZ (14)
		     1.23*280.4, // ZNuNu-HT100to200  (15) 
		     1.23*77.67, // ZNuNu-HT200to400  (16)
		     1.23*10.73,  // ZNuNu-HT400to600  (17) 
		     1.23*4.116, // ZNuNu-HT600toInf  (18)
		     22110000, // QCD_Pt_50to80  (19) 
		     3116000, // QCD_Pt_80to120  (20) 
		     493200, // QCD_Pt_120to170  (21)
		     12030, // QCD_Pt_170to300   (22)
		     7475,   // QCD_Pt_300to470    (23)
		     587.1, // QCD_Pt_470to600   (24)
		     167,    // QCD_Pt_600to800  (25)
		     28.25, // QCD_Pt_800to1000  (26)
		     0,
		     0,
		     0}; 
  
  TString cutsNum[30];
  TString cutsDen[30];
  for (int i=1; i<30; ++i) {
    cutsNum[i] = "puWeight*genWeight*("+selCutsMC+numCuts+mcCuts+")";
    cutsDen[i] = "puWeight*genWeight*("+selCutsMC+denCuts+mcCuts+")";
  }
  cutsNum[0] = selCuts+numCuts;
  cutsDen[0] = selCuts+denCuts;

  TH1D * histNum[25];
  TH1D * histDen[25];

  int nBins = 3;
  double bins[4] = {100,150,200,500};

  TCanvas * dummy = new TCanvas("dummy","",500,500);

  int nSamples = 2;
  // filling histograms

  for (int i=0; i<nSamples; ++i) {
    TFile * file = new TFile(dir+"/"+sampleNames[i]+".root");
    TH1D * histWeightsH = (TH1D*)file->Get("histWeightsH");
    TTree * tree = (TTree*)file->Get("NTuple");
    double norm = xsec[i]*lumi/histWeightsH->GetSumOfWeights();
    TString histNameNum = sampleNames[i] + "_Num";
    TString histNameDen = sampleNames[i] + "_Den";
    histNum[i] = new TH1D(histNameNum,"",nBins,bins);
    histDen[i] = new TH1D(histNameDen,"",nBins,bins);
    histNum[i]->Sumw2();
    histDen[i]->Sumw2();
    tree->Draw("tauPt>>"+histNameNum,cutsNum[i]);
    tree->Draw("tauPt>>"+histNameDen,cutsDen[i]);
    std::cout << sampleNames[i] << " : " <<  histNum[i]->GetEntries() << " vs. " << histDen[i]->GetEntries() << std::endl;
    if (i==0) norm = 1;
    if (i>0&&i<23) {
      for (int iB=1; iB<=nBins; ++iB) {
	double x = histNum[i]->GetBinContent(iB);
	double e = histNum[i]->GetBinError(iB);
    	histNum[i]->SetBinContent(iB,norm*x);
    	histNum[i]->SetBinError(iB,norm*e);
	x = histDen[i]->GetBinContent(iB);
	e = histDen[i]->GetBinError(iB);
    	histDen[i]->SetBinContent(iB,norm*x);
    	histDen[i]->SetBinError(iB,norm*e);
      }
    }
  }

  double dataNum = histNum[0]->GetSumOfWeights();
  double dataDen = histDen[0]->GetSumOfWeights();

  /*
  for (int i=2; i<=5; ++i) {
    histNum[1]->Add(histNum[1],histNum[i]);
    histDen[1]->Add(histDen[1],histDen[i]);
  }
  */

  double wjetsNum = histNum[1]->GetSumOfWeights();
  double wjetsDen = histDen[1]->GetSumOfWeights();
  double wjetsE2 = 0;
  for (int iB=1;iB<nBins;++iB) {
    double error = histNum[1]->GetBinError(iB);
    wjetsE2 += error*error;
  }
  double wjetsE = TMath::Sqrt(wjetsE2);

  /*
  double zjetsNum = histNum[6]->GetSumOfWeights();
  double zjetsDen = histDen[6]->GetSumOfWeights();

  double tjetsNum = 0;
  double tjetsDen = 0;
  for (int iS=7; iS<=11; ++iS) {
    tjetsNum += histNum[iS]->GetSumOfWeights();
    tjetsDen += histDen[iS]->GetSumOfWeights();
  }

  double vvNum = 0;
  double vvDen = 0;
  for (int iS=12; iS<=14; ++iS) {
    vvNum += histNum[iS]->GetSumOfWeights();
    vvDen += histDen[iS]->GetSumOfWeights();
  }

  double zvvNum = 0;
  double zvvDen = 0;
  for (int iS=15; iS<=18; ++iS) {
    zvvNum += histNum[iS]->GetSumOfWeights();
    zvvDen += histDen[iS]->GetSumOfWeights();
  }
  */
  delete dummy;

  std::cout << std::endl;
  std::cout << "Fake rates -> " << std::endl;
  std::cout << "Data      : " << int(dataNum) << "/" << int(dataDen) << " = " << dataNum/(dataDen+1e-4) 
	    << "+/-" << TMath::Sqrt(dataNum)/(dataDen+1e-4) << std::endl;
  std::cout << "W->lv     : " << int(wjetsNum)<< "/" << int(wjetsDen) << " = " << wjetsNum/(wjetsDen+1e-4) 
	    << " +/- " << wjetsE/(wjetsDen+1e-4) << std::endl;
  //  std::cout << "Z->ll     : " << int(zjetsNum) << "/" << int(zjetsDen) << " = " << zjetsNum/(zjetsDen+1e-4) << std::endl;
  //  std::cout << "Top       : " << int(tjetsNum) << "/" << int(tjetsDen) << " = " << tjetsNum/(tjetsDen+1e-4) << std::endl;
  //  std::cout << "VV        : " << int(vvNum) << "/" << int(vvDen) << " = " << vvNum/(vvDen+1e-4) << std::endl;
  //  std::cout << "Z->vv     : " << int(zvvNum) << "/" << int(zvvDen) << " = " << zvvNum/(zvvDen+1e-4) << std::endl;
  std::cout << std::endl;

  TGraphAsymmErrors * eff = new TGraphAsymmErrors();
  eff->Divide(histNum[0],histDen[0]);
  eff->SetMarkerStyle(20);
  eff->SetMarkerColor(1);
  eff->SetMarkerSize(2);

  TGraphAsymmErrors * effMC = new TGraphAsymmErrors();
  effMC->Divide(histNum[1],histDen[1]);
  effMC->SetMarkerStyle(21);
  effMC->SetMarkerColor(2);
  effMC->SetLineColor(2);
  effMC->SetMarkerSize(2);

  TCanvas * canv = new TCanvas("canv","",700,600);
  TH2F * frame = new TH2F("frame","",2,99,501,2,0,0.2);
  frame->GetYaxis()->SetTitle("Fake Rate");
  frame->GetXaxis()->SetTitle("fake tau p_{T} [GeV/c]");
  frame->Draw();
  eff->Draw("epsame");
  effMC->Draw("epsame");
  //  canv->SetLogx(true);
  //  canv->SetLogy(true);
  TLegend * leg = new TLegend(0.6,0.7,0.85,0.9);
  SetLegendStyle(leg);
  leg->SetHeader(iso);
  leg->AddEntry(eff,"Data","lp");
  leg->AddEntry(effMC,"Simulation","lp");
  leg->Draw();
  canv->Update();
  canv->Print("figures/fakerate_data_mc_"+iso+suffix+".png");

  TFile * fileOutput = new TFile(DataFile+"_fakeRate"+iso+".root","recreate");
  fileOutput->cd("");
  TGraphAsymmErrors * fakeRate = (TGraphAsymmErrors*)eff->Clone(DataFile+"_fakeRate");
  fakeRate->Write(DataFile+"_fakeRate");
  fileOutput->Close();

}
