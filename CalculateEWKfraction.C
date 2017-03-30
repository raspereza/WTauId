#include "HttStylesNew.cc"
#include "TStyle.h"
#include "settings.h"

void CalculateEWKfraction() {

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
  const int nBins  = 3;
  float bins[nBins+1] = {100,150,200,1000};  // tauPt binning
	
  for(unsigned int idx_iso=0; idx_iso<iso.size(); idx_iso++){

    cout<<endl<<"Process "<<iso[idx_iso]<<" : "<<endl;
    
    for (unsigned int i=0; i<samples.size(); ++i) {

      TFile *fileOutput   = new TFile("output/"+samples[i].first+"_fakeRate.root","recreate");
      
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
}
