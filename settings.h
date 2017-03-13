#ifndef SETTINGS_H
#define SETTINGS_H

#include <vector>
#include <map>

#include "TString.h"
#include "TTree.h"
#include "TFile.h"
#include "TTreeReader.h"
#include "TROOT.h"
#include "TKey.h"
#include "TGraphErrors.h"
#include "TGraphAsymmErrors.h"
#include "TH1.h"
#include "TH2.h"

double luminosity = 35867;
int nBins  =      8;
float xmin =      0;
float xmax =   1000;

std::vector<TString> iso;
map<std::pair<TString,int>, double>* fakerate  = 0;
map<std::pair<TString,int>, double>* fakerateE = 0;

map<TString, double> xsecs = {
{"W1JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8", 9644.5}, 
{"W2JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8", 3144.5}, 
{"W3JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8", 954.8}, 
{"W4JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8", 485.6},
{"WJetsToLNu_13TeV-madgraphMLM"                      , 61526.7}
};
// ----------------------------------------------------------------------------------------------------
void loadWorkingPoints()
{
  iso.push_back("VTightMva");
  iso.push_back("TightMva");
  iso.push_back("MediumMva");
  iso.push_back("LooseMva");
  iso.push_back("Tight");
  iso.push_back("Medium");
  iso.push_back("Loose");
}
// ----------------------------------------------------------------------------------------------------
double getXSec(TString sampleName)
{
  if( xsecs.find(sampleName) == xsecs.end() ) return 1;
  return xsecs[sampleName];
}
// ----------------------------------------------------------------------------------------------------
struct selectionCuts {
  TString name;
  int  selection;
  bool trigger;
  float recoilRatioLow, recoilRatioHigh;
  float recoilDPhiLow;
  float metLow;
  float tauPtLow;
  bool metFilters;
  unsigned int nMuonLow, nMuonHigh;
  unsigned int nElecLow, nElecHigh;
  unsigned int nSelTausLow, nSelTausHigh;
  unsigned int nJetsCentral30Low, nJetsCentral30High;
  unsigned int nJetsForward30Low, nJetsForward30High;
  bool tauDM, tauAntiMuonLoose3, tauAntiElectronLooseMVA6, tauIso;
  int tauGenMatchDecayLow, tauGenMatchDecayHigh;
  float mtmuonLow, mtmuonHigh;
} sr, cr_antiiso, cr_fakerate_den, cr_fakerate_num;
// ----------------------------------------------------------------------------------------------------
void initCuts()
{
  // signal region
  sr.name = "sr";
  sr.selection = 3;
  sr.trigger   = true;
  sr.recoilRatioLow  = 0.75;
  sr.recoilRatioHigh = 1.20;
  sr.recoilDPhiLow = 2.4;
  sr.metLow = 120; 
  sr.tauPtLow = 100;
  sr.metFilters = true;
  sr.nMuonLow  = 0; 
  sr.nMuonHigh = 0; 
  sr.nElecLow  = 0; 
  sr.nElecHigh = 0; 
  sr.nSelTausLow  = 1; 
  sr.nSelTausHigh = 1; 
  sr.nJetsCentral30Low  = 0; 
  sr.nJetsCentral30High = 1; 
  sr.nJetsForward30Low  = 0; 
  sr.nJetsForward30High = 0; 
  sr.tauDM = true;
  sr.tauAntiMuonLoose3 = true;
  sr.tauAntiElectronLooseMVA6 = true;
  sr.tauIso = true;
  sr.tauGenMatchDecayLow  = -10000000;
  sr.tauGenMatchDecayHigh = -1;
  sr.mtmuonLow  = -1;
  sr.mtmuonHigh = 100000000;

  // antiiso region
  cr_antiiso = sr;
  cr_antiiso.name = "cr_antiiso";
  cr_antiiso.tauIso = false;

  // cr_fakerate_den
  cr_fakerate_den = sr;
  cr_fakerate_den.name = "cr_fakerate_den";
  cr_fakerate_den.selection = 1;
  cr_fakerate_den.trigger = true; // trigger already applied on ntuple level
  cr_fakerate_den.nMuonLow  = 1;
  cr_fakerate_den.nMuonHigh = 1;
  cr_fakerate_den.nJetsCentral30Low  = 1;
  cr_fakerate_den.nJetsCentral30High = 1;
  cr_fakerate_den.recoilRatioLow  = 0.70;
  cr_fakerate_den.recoilRatioHigh = 1.30;
  cr_fakerate_den.mtmuonLow = 40;
  cr_fakerate_den.metLow = -1;
  cr_fakerate_den.tauIso = false;

  // cr_fakerate_num
  cr_fakerate_num = cr_fakerate_den;
  cr_fakerate_num.name = "cr_fakerate_num";
  cr_fakerate_num.tauIso = true;


}
// ----------------------------------------------------------------------------------------------------
int getNEventsProcessed(TString filename)
{
  TFile * file = new TFile(filename);
  TH1D * histWeightsH = (TH1D*)file->Get("histWeightsH");
  return histWeightsH->GetSumOfWeights();
}
// ----------------------------------------------------------------------------------------------------
void loadFakeRates(TString filename)
{

  fakerate  = new map<std::pair<TString,int>, double>();
  fakerateE = new map<std::pair<TString,int>, double>();

  TFile *f1 = TFile::Open(filename);
  if(!f1){
    cout<<"File "<<filename<<" does not exists. Exiting."<<endl;
    exit(-1);
  }

  TIter next(f1->GetListOfKeys());
  TKey *key;
  
  while ((key = (TKey*)next())) {
    TClass *cl = gROOT->GetClass(key->GetClassName());
    
    if (!cl->InheritsFrom("TGraphErrors")) continue;
    
    TGraphErrors *g = (TGraphErrors*) key->ReadObj();
    
    for(int i = 0; i<g->GetN(); i++){
      fakerate  -> insert( std::make_pair( std::make_pair( g->GetName() , i ) , g->GetY()[i] ) );
      fakerateE -> insert( std::make_pair( std::make_pair( g->GetName() , i ) , g->GetEY()[i] ) );
    }
  }
  f1->Close();
  delete f1;

  if(fakerate && fakerateE) cout<<endl<<"---------  Fakerates succesfully loaded. --------"<<endl;
}
// ----------------------------------------------------------------------------------------------------
double getFakeRates(float tauPt, TString iso)
{

  int ptBin = -1;
  if(tauPt<150)                    ptBin = 0;
  else if(tauPt<200 && tauPt>150 ) ptBin = 1;
  else                             ptBin = 2;

  return fakerate->at(std::make_pair(iso, ptBin));

}
// ----------------------------------------------------------------------------------------------------
void makeSelection(TString filename, TString treename, double xsec, TString iso, selectionCuts sel, TH1D* histo, TString variableToFill)
{

  TFile * file = new TFile(filename);
  if(!file){
    cout<<"The following tree does not exit: "<<filename<<" .   Please Check."<<endl;
  }
  TTreeReader *myReader = new TTreeReader(treename, file);
  
  TTreeReaderValue< UInt_t  >  event(            *myReader,       "event");
  TTreeReaderValue< Float_t >  mttau(            *myReader,       "mttau");
  TTreeReaderValue< Float_t >  puWeight(         *myReader,       "puWeight");
  TTreeReaderValue< Float_t >  genWeight(        *myReader,       "genWeight");
  TTreeReaderValue< Float_t >  trigWeight(       *myReader,       "trigWeight");
  TTreeReaderValue< Bool_t  >  trig(             *myReader,       "trigger");
  TTreeReaderValue< Int_t   >  Selection(        *myReader,       "Selection");
  TTreeReaderValue< Float_t >  recoilRatio(      *myReader,       "recoilRatio");
  TTreeReaderValue< Float_t >  recoilDPhi(       *myReader,       "recoilDPhi");
  TTreeReaderValue< Float_t >  met(              *myReader,       "met");
  TTreeReaderValue< Float_t >  tauPt(            *myReader,       "tauPt");
  TTreeReaderValue< Bool_t  >  metFilters(       *myReader,       "metFilters");
  TTreeReaderValue< UInt_t  >  nMuon(            *myReader,       "nMuon");
  TTreeReaderValue< UInt_t  >  nElec(            *myReader,       "nElec");
  TTreeReaderValue< UInt_t  >  nSelTaus(         *myReader,       "nSelTaus");
  TTreeReaderValue< UInt_t  >  nJetsCentral30(   *myReader,       "nJetsCentral30");
  TTreeReaderValue< UInt_t  >  nJetsForward30(   *myReader,       "nJetsForward30");
  TTreeReaderValue< Bool_t  >  tauDM(            *myReader,       "tauDM");
  TTreeReaderValue< Bool_t  >  tauAntiMuonLoose3(*myReader,       "tauAntiMuonLoose3");
  TTreeReaderValue< Bool_t  >  tauAntiElectronLooseMVA6(*myReader,"tauAntiElectronLooseMVA6");
  TTreeReaderValue< Bool_t  >  tauIso(           *myReader,       "tau"+iso+"Iso");
  TTreeReaderValue< Float_t >  fakeAntiL(        *myReader,       "fakeAntiL"+iso);
  TTreeReaderValue< Int_t   >  tauGenMatchDecay( *myReader,       "tauGenMatchDecay");
  TTreeReaderValue< Float_t >  mtmuon(           *myReader,       "mtmuon");
  TTreeReaderValue< Float_t >  variable(         *myReader,       variableToFill);


  int nevtsProcessed = getNEventsProcessed(filename);
  double norm = xsec*luminosity/nevtsProcessed;

  while(myReader->Next()){

    if(*trig != sel.trigger && sel.selection != 1) continue;
    if(*Selection != sel.selection) continue;
    if(*recoilRatio < sel.recoilRatioLow || *recoilRatio > sel.recoilRatioHigh) continue;
    if(*recoilDPhi < sel.recoilDPhiLow) continue;
    if(*met < sel.metLow) continue;
    if(*tauPt < sel.tauPtLow) continue;
    if(*metFilters != sel.metFilters) continue;
    
    if(*nMuon<sel.nMuonLow || *nMuon>sel.nMuonHigh) continue;
    if(*nElec<sel.nElecLow || *nElec>sel.nElecHigh) continue;
    if(*nSelTaus<sel.nSelTausLow || *nSelTaus>sel.nSelTausHigh) continue;
    if(*nJetsCentral30<sel.nJetsCentral30Low || *nJetsCentral30>sel.nJetsCentral30High) continue;
    if(*nJetsForward30<sel.nJetsForward30Low || *nJetsForward30>sel.nJetsForward30High) continue;
    
    if(*tauDM != sel.tauDM) continue;
    if(*tauAntiMuonLoose3 != sel.tauAntiMuonLoose3) continue;
    if(*tauAntiElectronLooseMVA6 != sel.tauAntiElectronLooseMVA6) continue;
    if(*tauIso != sel.tauIso) continue;
    if(*tauGenMatchDecay < sel.tauGenMatchDecayLow || *tauGenMatchDecay > sel.tauGenMatchDecayHigh ) continue;
    
    if(*mtmuon < sel.mtmuonLow || *mtmuon > sel.mtmuonHigh ) continue;
    
    Float_t scale = 1;
    if(sel.name.Contains("cr_antiiso")) scale = getFakeRates(*tauPt,iso + "Iso");
    if(sel.name.Contains("cr_fakerate")) *trigWeight = 1;
    //cout<<"tau pt = "<<*tauPt<<endl;
    //cout<<"*puWeight   = "<<*puWeight<<endl;
    //cout<<"*genWeight  = "<<*genWeight<<endl;
    //cout<<"*trigWeight = "<<*trigWeight<<endl;
    //cout<<"norm        = "<<norm<<endl;
    ///cout<<"scale       = "<<scale<<endl;
    //cout<<"weight = "<<(*puWeight)*(*trigWeight)*(*genWeight)*norm*scale<<endl;
    histo->Fill( *variable,  (*puWeight)*(*trigWeight)*(*genWeight)*norm*scale );
  }

  delete myReader;

}

// ----------------------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------------------
#endif

