#include "TTree.h"


// ----------------------------------------------------------------------------------------------------
// Global variables
float mttau;
float puWeight;
float genWeight;
float trigWeight;
bool  trig;
int   Selection;
float recoilRatio;
float recoilDPhi;
float met;
float tauPt;
bool  metFilters;
unsigned int nMuon;
unsigned int nElec;
unsigned int nSelTaus;
unsigned int nJetsCentral30;
unsigned int nJetsForward30;
bool  tauDM;
bool  tauAntiMuonLoose3;
bool  tauAntiElectronLooseMVA6;
bool  tauIso;
float fakeAntiLiso;
int tauGenMatchDecay;
// ----------------------------------------------------------------------------------------------------
TTree* readTree(TString filename, TString treename, TString iso)
{

  TFile * file = new TFile(filename);
  if(!file){
    cout<<"The following tree does not exit: "<<filename<<" .   Please Check."<<endl;
  }
  TTree * tree = (TTree*)file->Get(treename);
  
  tree->SetBranchStatus("*",0);
  tree->SetBranchStatus("mttau",1);
  tree->SetBranchAddress("mttau",&mttau);
  tree->SetBranchStatus("puWeight",1);
  tree->SetBranchAddress("puWeight",&puWeight);
  tree->SetBranchStatus("genWeight",1);
  tree->SetBranchAddress("genWeight",&genWeight);
  tree->SetBranchStatus("trigWeight",1);
  tree->SetBranchAddress("trigWeight",&trigWeight);
  tree->SetBranchStatus("trigger",1);
  tree->SetBranchAddress("trigger",&trig);
  tree->SetBranchStatus("Selection",1);
  tree->SetBranchAddress("Selection",&Selection);
  tree->SetBranchStatus("recoilRatio",1);
  tree->SetBranchAddress("recoilRatio",&recoilRatio);
  tree->SetBranchStatus("recoilDPhi",1);
  tree->SetBranchAddress("recoilDPhi",&recoilDPhi);
  tree->SetBranchStatus("met",1);
  tree->SetBranchAddress("met",&met);
  tree->SetBranchStatus("tauPt",1);
  tree->SetBranchAddress("tauPt",&tauPt);
  tree->SetBranchStatus("metFilters",1);
  tree->SetBranchAddress("metFilters",&metFilters);
  tree->SetBranchStatus("nMuon",1);
  tree->SetBranchAddress("nMuon",&nMuon);
  tree->SetBranchStatus("nElec",1);
  tree->SetBranchAddress("nElec",&nElec);
  tree->SetBranchStatus("nSelTaus",1);
  tree->SetBranchAddress("nSelTaus",&nSelTaus);
  tree->SetBranchStatus("nJetsCentral30",1);
  tree->SetBranchAddress("nJetsCentral30",&nJetsCentral30);
  tree->SetBranchStatus("nJetsForward30",1);
  tree->SetBranchAddress("nJetsForward30",&nJetsForward30);
  tree->SetBranchStatus("tauDM",1);
  tree->SetBranchAddress("tauDM",&tauDM);
  tree->SetBranchStatus("tauAntiMuonLoose3",1);
  tree->SetBranchAddress("tauAntiMuonLoose3",&tauAntiMuonLoose3);
  tree->SetBranchStatus("tauAntiElectronLooseMVA6",1);
  tree->SetBranchAddress("tauAntiElectronLooseMVA6",&tauAntiElectronLooseMVA6);
  tree->SetBranchStatus("tau"+iso+"Iso",1);
  tree->SetBranchAddress("tau"+iso+"Iso",&tauIso);
  tree->SetBranchStatus("fakeAntiL"+iso,1);
  tree->SetBranchAddress("fakeAntiL"+iso,&fakeAntiLiso);
  tree->SetBranchStatus("tauGenMatchDecay",1);
  tree->SetBranchAddress("tauGenMatchDecay",&tauGenMatchDecay);

  return tree;

}
// ----------------------------------------------------------------------------------------------------
