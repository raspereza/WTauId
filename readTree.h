#include "TTree.h"
#include "TTreeReader.h"
#include "TTreeReaderArray.h"
#include<iostream>


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
void makeSelection(TString filename, TString treename, TString iso, selectionCuts)
{

  TFile * file = new TFile(filename);
  if(!file){
    cout<<"The following tree does not exit: "<<filename<<" .   Please Check."<<endl;
  }
  TTreeReader *myReader = new TTreeReader(treename, file);
  
  TTreeReaderValue< Float_t >  mttau(*myReader,       "mttau");
  TTreeReaderValue< Float_t >  puWeight(*myReader,    "puWeight");
  TTreeReaderValue< Float_t >  genWeight(*myReader,       "genWeight");
  TTreeReaderValue< Float_t >  trigWeight(*myReader,       "trigWeight");
  TTreeReaderValue< Bool_t  >  trig(*myReader,       "trigger");
  TTreeReaderValue< Int_t   >  Selection(*myReader,       "Selection");
  TTreeReaderValue< Float_t >  recoilRatio(*myReader,       "recoilRatio");
  TTreeReaderValue< Float_t >  recoilDPhi(*myReader,       "recoilDPhi");
  TTreeReaderValue< Float_t >  met(*myReader,       "met");
  TTreeReaderValue< Float_t >  tauPt(*myReader,       "tauPt");
  TTreeReaderValue< Bool_t  >  metFilters(*myReader,       "metFilters");
  TTreeReaderValue< UInt_t  >  nMuon(*myReader,       "nMuon");
  TTreeReaderValue< UInt_t  >  nElec(*myReader,       "nElec");
  TTreeReaderValue< UInt_t  >  nSelTaus(*myReader,       "nSelTaus");
  TTreeReaderValue< UInt_t  >  nJetsCentral30(*myReader,       "nJetsCentral30");
  TTreeReaderValue< UInt_t  >  nJetsForward30(*myReader,       "nJetsForward30");
  TTreeReaderValue< Bool_t  >  tauDM(*myReader,       "tauDM");
  TTreeReaderValue< Bool_t  >  tauAntiMuonLoose3(*myReader,       "tauAntiMuonLoose3");
  TTreeReaderValue< Bool_t  >  tauAntiElectronLooseMVA6(*myReader,       "tauAntiElectronLooseMVA6");
  TTreeReaderValue< Bool_t  >  tauIso(*myReader,       "tau"+iso+"Iso");
  TTreeReaderValue< Float_t >  fakeAntiL(*myReader,       "fakeAntiL"+iso);
  TTreeReaderValue< Int_t   >  tauGenMatchDecay(*myReader,       "tauGenMatchDecay");

  while(myReader->Next()){

    if(*trig != sel.trigger) continue;
    if(*Selection != sel.selection) continue;
    if(*recoilRatio < sel.recoilRatioLow || *recoilRatio > sel.recoilRatioHigh) continue;
    if(*recoilDPhi < sel.recoilDPhiLow) continue;
    if(*met < sel.metLow) continue;
    if(*tauPt < sel.tauPtLow) continue;
    if(*metFilters != sel.metFilters) continue;
  
    if(*nMuon<sel.nMuonLow || *nMuon>sel.nMuonHigh) continue;
    if(*nElec<sel.nElecLow || *nElec>sel.nElecHigh) continue;
    if(*nSelTaus<sel.nSelTausLow || nSelTaus>sel.nSelTausHigh) continue;
    if(*nJetsCentral30<sel.nJetsCentral30Low || *nJetsCentral30>sel.nJetsCentral30High) continue;
    if(*nJetsForward30<sel.nJetsForward30Low || *nJetsForward30>sel.nJetsForward30High) continue;
  
    if(*tauDM != sel.tauDM) continue;
    if(*tauAntiMuonLoose3 != sel.tauAntiMuonLoose3) continue;
    if(*tauAntiElectronLooseMVA6 != sel.tauAntiElectronLooseMVA6) continue;
    if(*tauIso != sel.tauIso) continue;
    if(*tauGenMatchDecay < sel.tauGenMatchDecayLow || *tauGenMatchDecay > sel.tauGenMatchDecayHigh ) continue;

  }

}
// ----------------------------------------------------------------------------------------------------
