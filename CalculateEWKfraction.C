#include "HttStylesNew.cc"
#include "TStyle.h"
#include "settings.h"

void CalculateEWKfraction() {

  bool recalculateEWKfraction = true;

  loadWorkingPoints();
  initCuts();

  TString dir("NTuples/");
  SetStyle();
  TH1::SetDefaultSumw2();
  TH2::SetDefaultSumw2();

  std::vector< std::pair<TString,std::vector<TString>> > samples;
  std::vector<TString> data_MET;
  data_MET.push_back("MET_Run2016");
  std::vector<TString> ewk;
  ewk.push_back("WJetsToLNu_HT-70To100_13TeV-madgraphMLM-pythia8");
  ewk.push_back("WJetsToLNu_HT-100To200_13TeV-madgraphMLM-pythia8");
  ewk.push_back("WJetsToLNu_HT-200To400_13TeV-madgraphMLM-pythia8");
  ewk.push_back("WJetsToLNu_HT-400To600_13TeV-madgraphMLM-pythia8");
  ewk.push_back("WJetsToLNu_HT-600To800_13TeV-madgraphMLM-pythia8");
  ewk.push_back("WJetsToLNu_HT-800To1200_13TeV-madgraphMLM-pythia8");
  ewk.push_back("ZJetsToNuNu_HT-100To200_13TeV-madgraph");
  ewk.push_back("ZJetsToNuNu_HT-200To400_13TeV-madgraph");
  ewk.push_back("ZJetsToNuNu_HT-400To600_13TeV-madgraph");
  ewk.push_back("ZJetsToNuNu_HT-600To800_13TeV-madgraph");
  ewk.push_back("VVTo2L2Nu_13TeV_amcatnloFXFX");
  ewk.push_back("WWToLNuQQ_13TeV_powheg");
  ewk.push_back("WZTo1L1Nu2Q_13TeV_amcatnloFXFX");
  ewk.push_back("WZTo1L3Nu_13TeV_amcatnloFXFX");
  ewk.push_back("WZTo2L2Q_13TeV_amcatnloFXFX");
  ewk.push_back("DYJetsToLL_M-50_13TeV-madgraphMLM");

  samples.push_back(make_pair("EWK_MC" , ewk));
  samples.push_back(make_pair("MET_Run2016" , data_MET));

  TH1D* histo[2] = {0};  
  const int nBins  = 1;
  float bins[nBins+1] = {100,1000};  // tauPt binning
	
  for(unsigned int idx_iso=0; idx_iso<iso.size(); idx_iso++){

    if(!recalculateEWKfraction) continue;
    if(iso[idx_iso] != "TightMva") continue;

    cout<<endl<<"Process "<<iso[idx_iso]<<" : "<<endl;
    
    for (unsigned int i=0; i<samples.size(); ++i) {

      // filling histograms
      histo[i]  = new TH1D("h_" + samples[i].first,"",nBins,bins); 

      TString var = "tauPt";
      for(unsigned int idx_list=0; idx_list<samples[i].second.size(); idx_list++){
	cout<<"---------- Sample "<<samples[i].second[idx_list]<<" processing. ---------- "<<endl;

	makeSelection(dir+samples[i].second[idx_list]+".root","NTuple",getXSec(samples[i].second[idx_list]),iso[idx_iso],cr_ewkFraction,histo[i],var,var,var);
      }
    }
    double nEWK_err;
    double nEWK  = histo[0] -> IntegralAndError(1,nBins,nEWK_err);
    double nData_err;
    double nData = histo[1] -> IntegralAndError(1,nBins,nData_err);
      
    TH1D *h_fEWK = (TH1D*) histo[0]->Clone();
    h_fEWK->Divide(histo[1]);
    h_fEWK->SetName("h_fEWK");
      
    std::cout << "Fraction of electroweak events in antiisolated region -> " << std::endl;
    std::cout << "EWK (from MC)     = " << nEWK       << " +/- " << nEWK_err << std::endl;
    std::cout << "Total (from data) = " << nData      << " +/- " << nData_err << std::endl;
    std::cout << "EWK/Total         = " << nEWK/nData << " +/- " << nEWK_err/nData << std::endl;
    std::cout << "  pt > 100 GeV    = " << h_fEWK->GetBinContent(1) << " +/- " << h_fEWK->GetBinError(1) << endl;
    std::cout << "  pt > 150 GeV    = " << h_fEWK->GetBinContent(2) << " +/- " << h_fEWK->GetBinError(2) << endl;
    std::cout << "  pt > 200 GeV    = " << h_fEWK->GetBinContent(3) << " +/- " << h_fEWK->GetBinError(3) << endl;
    std::cout << std::endl;
      
    // Save fraction of EWK events in root file
    TFile* out = new TFile("output/fraction_EWK.root","RECREATE");
    out->cd();
    h_fEWK->Write();
    out->Close();
  }

  TFile* file = new TFile("output/fraction_EWK.root","READ");
  TH1D* h_fEWK = 0;
  file->GetObject("h_fEWK", h_fEWK);
  double *ratio  = new double[h_fEWK->GetNbinsX()];
  double *eratio = new double[h_fEWK->GetNbinsX()];
  for(int i=0; i<h_fEWK->GetNbinsX(); i++){
    ratio[i]  = h_fEWK->GetBinContent(i+1); 
    eratio[i] = h_fEWK->GetBinError(i+1); 
  }

  // Read single fake rates
  TFile *DataFileJetHT = new TFile("output/JetHT_Run2016_fakeRate.root");
  TFile *DataFileSingleMu = new TFile("output/SingleMuon_Run2016_fakeRate.root");
  
  TFile* out = new TFile("output/fakerates.root","RECREATE");

  cout<<endl<<endl<<"Calculation of combined fake rate"<<endl<<endl;
  for(unsigned int idx_iso=0; idx_iso<iso.size(); idx_iso++){
    
    TH2D *effJetHT    = (TH2D*) DataFileJetHT->Get(iso[idx_iso]);
    TH2D *effSingleMu = (TH2D*) DataFileSingleMu->Get(iso[idx_iso]);
    TH2D *effCombined = (TH2D*) effJetHT->Clone();

    for(int i=1; i<=effJetHT->GetNbinsX(); i++){
      for(int j=1; j<=effJetHT->GetNbinsY(); j++){
 
	double FRJetHT       = effJetHT->GetBinContent(i,j);
	double FRJetHTErr    = effJetHT->GetBinError(i,j);
	double FRSingleMu    = effSingleMu->GetBinContent(i,j);
	double FRSingleMuErr = effSingleMu->GetBinError(i,j);

	double comb = (1-ratio[0])*FRJetHT+ratio[0]*FRSingleMu;
	double combErr = sqrt( pow(FRSingleMu-FRJetHT,2)*pow(eratio[0],2) + pow(ratio[0],2)*(pow(FRSingleMuErr,2) + pow(FRJetHTErr,2)) );

	effCombined->SetBinContent(i , j , comb);
	effCombined->SetBinError(i , j , combErr);
      }
    }

    cout<<"Used EWK fraction = "<<ratio[0]<<endl;
    
    out->cd();
    effCombined -> SetName(iso[idx_iso]);
    effCombined -> Write(iso[idx_iso]);
  }
}
