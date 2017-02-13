#include "HttStylesNew.cc"

void ComputeFakeRate(bool isDijet = true) {

  std::vector<TString> iso;
  iso.push_back("VTightMvaIso");
  iso.push_back("TightMvaIso");
  iso.push_back("MediumMvaIso");
  iso.push_back("LooseMvaIso");
  iso.push_back("TightIso");
  iso.push_back("MediumIso");
  iso.push_back("LooseIso");

  TString dir("NTuples/");

  TString DataFile("SingleMuon_Run2016");
  TString suffix("_wjets");
  if (isDijet) {
      DataFile="JetHT_Run2016";
      suffix = "_dijet";
  }

  TString sampleNames[30] = {DataFile,
			     "WJetsToLNu_13TeV-madgraphMLM"
  };
  double xsec[30] = {1, // data (0)
		     61526.7    // WJets (1)
  }; 


  for(unsigned int idx_iso=0; idx_iso<iso.size(); idx_iso++){

    cout<<endl<<endl<<"Process "<<iso[idx_iso]<<endl;

    // ****************** Cuts for W->muv+jet ************************
    TString   selCuts("Selection==1&&nMuon==1&&nElec==0&&nJetsCentral30<=1&&nJetsForward30==0&&nSelTaus==1&&tauPt>100&&recoilRatio>0.7&&recoilRatio<1.3&&recoilDPhi>2.4&&mtmuon>40"); 
    TString selCutsMC("Selection==1&&nMuon==1&&nElec==0&&nJetsCentral30<=1&&nJetsForward30==0&&nSelTaus==1&&tauPt>100&&recoilRatio>0.7&&recoilRatio<1.3&&recoilDPhi>2.4&&mtmuon>40");
    
    if (isDijet) {
      // ****************** Cuts for dijet events ************************
      selCuts = "Selection==4&&nMuon==0&&nElec==0&&nSelTaus==1&&nJetsCentral30<=2&&tauPt>100&&recoilDPhi>2.6&&recoilRatio>0.8&&recoilRatio<1.2&&(pfJet80>0.5||pfJet140>0.5)&&tauPt>100";
      selCutsMC = "Selection==4&&nMuon==0&&nElec==0&&nSelTaus==1&&nJetsCentral30<=2&&tauPt>100&&recoilDPhi>2.6&&recoilRatio>0.8&&recoilRatio<1.2&&(pfJet80>0.5||pfJet140>0.5)&&tauPt>100";
    }
    
    TString numCuts("&&tauDM>0.5&&tauAntiMuonLoose3&&tauAntiElectronLooseMVA6&&tau"+iso[idx_iso]+">0.5");
    TString denCuts("&&tauDM>0.5&&tauAntiMuonLoose3&&tauAntiElectronLooseMVA6&&tau"+iso[idx_iso]+"<0.5");
    TString mcCuts("&&tauGenMatchDecay<0");
    //  TString mcCuts("");
    
    SetStyle();
    TH1::SetDefaultSumw2();
    TH2::SetDefaultSumw2();

    bool logY = false;
    double lumi = 36800;

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

    double wjetsNum = histNum[1]->GetSumOfWeights();
    double wjetsDen = histDen[1]->GetSumOfWeights();
    double wjetsE2 = 0;
    for (int iB=1;iB<nBins;++iB) {
      double error = histNum[1]->GetBinError(iB);
      wjetsE2 += error*error;
    }
    double wjetsE = TMath::Sqrt(wjetsE2);
    
    delete dummy;

    std::cout << std::endl;
    std::cout << "Fake rates -> " << std::endl;
    std::cout << "Data      : " << int(dataNum) << "/" << int(dataDen) << " = " << dataNum/(dataDen+1e-4) 
	      << "+/-" << TMath::Sqrt(dataNum)/(dataDen+1e-4) << std::endl;
    std::cout << "W->lv     : " << int(wjetsNum)<< "/" << int(wjetsDen) << " = " << wjetsNum/(wjetsDen+1e-4) 
	      << " +/- " << wjetsE/(wjetsDen+1e-4) << std::endl;
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
    leg->SetHeader(iso[idx_iso]);
    leg->AddEntry(eff,"Data","lp");
    leg->AddEntry(effMC,"Simulation","lp");
    leg->Draw();
    canv->Update();
    canv->Print("figures/fakerate_data_mc_"+iso[idx_iso]+suffix+".png");

    TFile * fileOutput = new TFile("output/"+DataFile+"_fakeRate"+iso[idx_iso]+".root","recreate");
    fileOutput->cd("");
    TGraphAsymmErrors * fakeRate = (TGraphAsymmErrors*)eff->Clone(DataFile+"_fakeRate");
    fakeRate->Write(DataFile+"_fakeRate");
    fileOutput->Close();
  }
}
