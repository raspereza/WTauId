#ifndef SETTINGS_H
#define SETTINGS_H

#include <vector>
#include <map>
#include <math.h>

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
#include "TVector2.h"

double luminosity = 35867;
//double luminosity = 1.;
//double luminosity = 36800;
int nBins  = 4;
float bins[5] = {100,150,200,250,400};
//float bins[5] = {0,0.5,1.1,1.5,2.3};

std::vector<TString> iso;
map<std::pair<TString,int>, double>* fakerate  = 0;
map<std::pair<TString,int>, double>* fakerateE = 0;
//TF1* fakerateFunc = 0;

map<TString, double> xsecs = {
{"W1JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8", 1.221*9644.5}, 
{"W2JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8", 1.221*3144.5}, 
{"W3JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8", 1.221*954.8},
{"W4JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8", 1.221*485.6},
{"WJetsToLNu_13TeV-madgraphMLM"                      , 61526.7},
{"WJetsToLNu_13TeV-madgraphMLM-v1"                   , 61526.7}
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
  bool trigger = false;
  float recoilRatioLow, recoilRatioHigh;
  float recoilDPhiLow;
  float metLow = 0;
  float tauPtLow,tauPtHigh;
  bool metFilters;
  unsigned int nMuonLow, nMuonHigh;
  unsigned int nElecLow, nElecHigh;
  unsigned int nSelTausLow, nSelTausHigh;
  unsigned int nJetsCentral30Low, nJetsCentral30High;
  unsigned int nJetsForward30Low, nJetsForward30High;
  bool tauDM, tauAntiMuonLoose3, tauAntiElectronLooseMVA6, tauIso;
  int tauGenMatchDecayLow, tauGenMatchDecayHigh;
  float mtmuonLow=0;
  float mtmuonHigh=10000.;
  float mttauLow=0;
  float mttauHigh = 1000.;
  float recoilPtLow = 0.;
} sr, cr_antiiso, cr_fakerate_den, cr_fakerate_num,cr_fakerate_dijet_den, cr_fakerate_dijet_num;
// ----------------------------------------------------------------------------------------------------
void initCuts()
{
  // signal region
  sr.name = "sr";
  sr.selection = 3;
  sr.trigger   = true;
  sr.recoilRatioLow  = 0.00;
  sr.recoilRatioHigh = 100000.;
  sr.recoilDPhiLow = 2.8;
  sr.metLow = 120;
  sr.tauPtLow = 100;
  sr.tauPtHigh = 10000000;
  sr.metFilters = true;
  sr.nMuonLow  = 0; 
  sr.nMuonHigh = 0; 
  sr.nElecLow  = 0; 
  sr.nElecHigh = 0; 
  sr.nSelTausLow  = 1; 
  sr.nSelTausHigh = 1; 
  sr.nJetsCentral30Low  = 1;
  sr.nJetsCentral30High = 1;
  sr.nJetsForward30Low  = 0;
  sr.nJetsForward30High = 0;
  sr.tauDM = true;
  sr.tauAntiMuonLoose3 = true;
  sr.tauAntiElectronLooseMVA6 = true;
  sr.tauIso = true;
  sr.tauGenMatchDecayLow  = -10000000;
  sr.tauGenMatchDecayHigh = -1;
  sr.mtmuonLow  = 0;
  sr.mtmuonHigh = 100000000;
  sr.mttauLow  = 0;
  sr.mttauHigh = 100000000;

  // antiiso region
  cr_antiiso = sr;
  cr_antiiso.name = "cr_antiiso";
  cr_antiiso.tauIso = false;
  
  // cr_fakerate_den
  cr_fakerate_den = sr;
  cr_fakerate_den.name = "cr_fakerate_den";
  cr_fakerate_den.selection = 1;
  cr_fakerate_den.nMuonLow  = 1;
  cr_fakerate_den.nMuonHigh = 1;
  cr_fakerate_den.nElecLow  = 0;
  cr_fakerate_den.nElecHigh = 0;
  cr_fakerate_den.nJetsCentral30Low  = 0;
  cr_fakerate_den.nJetsCentral30High = 1;
  cr_fakerate_den.recoilRatioLow  = 0.0;
  cr_fakerate_den.recoilRatioHigh = 10000.;
  cr_fakerate_den.mtmuonLow = 40;
  cr_fakerate_den.metLow = 0;
  cr_fakerate_den.tauIso = false;
  cr_fakerate_den.mttauLow = 0;
  cr_fakerate_den.recoilDPhiLow = 2.8;
  cr_fakerate_den.tauPtLow = 100;
  cr_fakerate_den.recoilPtLow = 120.;
  // cr_fakerate_num
  cr_fakerate_num = cr_fakerate_den;
  cr_fakerate_num.name = "cr_fakerate_num";
  cr_fakerate_num.tauIso = true;

  // cr_fakerate_dijet_den
  cr_fakerate_dijet_den.name = "cr_fakerate_dijet_den";
  cr_fakerate_dijet_den.selection = 4;
  cr_fakerate_dijet_den.nMuonLow  = 0;
  cr_fakerate_dijet_den.nMuonHigh = 0;
  cr_fakerate_dijet_den.nElecLow  = 0;
  cr_fakerate_dijet_den.nElecHigh = 0;
  cr_fakerate_dijet_den.nSelTausLow  = 1; 
  cr_fakerate_dijet_den.nSelTausHigh = 1; 
  cr_fakerate_dijet_den.nJetsCentral30Low  = 0;
  cr_fakerate_dijet_den.nJetsCentral30High = 2;
  cr_fakerate_dijet_den.nJetsForward30Low  = cr_fakerate_den.recoilRatioLow;
  cr_fakerate_dijet_den.nJetsForward30High = cr_fakerate_den.recoilRatioHigh;
  cr_fakerate_dijet_den.tauPtLow = 100;
  cr_fakerate_dijet_den.tauPtHigh = 10000000;
  cr_fakerate_dijet_den.recoilDPhiLow = 2.8;
  cr_fakerate_dijet_den.recoilRatioLow  = 0.0;
  cr_fakerate_dijet_den.recoilRatioHigh = 100000.;
  cr_fakerate_dijet_den.metFilters = true;  
  cr_fakerate_dijet_den.tauDM = true;
  cr_fakerate_dijet_den.tauAntiMuonLoose3 = true;
  cr_fakerate_dijet_den.tauAntiElectronLooseMVA6 = true;
  cr_fakerate_dijet_den.tauIso = false;
  cr_fakerate_dijet_den.tauGenMatchDecayLow  = -10000000;
  cr_fakerate_dijet_den.tauGenMatchDecayHigh = -1;
  cr_fakerate_dijet_den.recoilPtLow = 120.;
  // cr_fakerate_num
  cr_fakerate_dijet_num = cr_fakerate_dijet_den;
  cr_fakerate_dijet_num.name = "cr_fakerate_dijet_num";
  cr_fakerate_dijet_num.tauIso = true;
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
  
  //TGraphErrors* graph = 0;
  //f1->GetObject("LooseIso",graph);
  //fakerateFunc = graph->GetFunction("func");

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
double getFakeRates(float tauPt, TString iso, TString err)
{

  int ptBin = -1;
  if(tauPt<0.4)                    ptBin = 0;
  else if(tauPt<0.5 && tauPt>0.4 ) ptBin = 1;
  else if(tauPt<0.6 && tauPt>0.5 ) ptBin = 2;
  else if(tauPt<0.7 && tauPt>0.6 ) ptBin = 3;
  else if(tauPt<0.8 && tauPt>0.7 ) ptBin = 4;
  else if(tauPt<0.9 && tauPt>0.8 ) ptBin = 5;
  else if(tauPt<1.0 && tauPt>0.9 ) ptBin = 6;
  else                             ptBin = 7;

  return fakerate->at(std::make_pair(iso, ptBin));

}
// ----------------------------------------------------------------------------------------------------
void makeSelection(TString filename, TString treename, double xsec, TString iso, selectionCuts sel, TH1D* histo, TString variableToFill_1, TString variableToFill_2)
{
  if(variableToFill_1 == variableToFill_2) histo->SetName(variableToFill_1);
  else                                     histo->SetName(variableToFill_1 + "_" + variableToFill_2);

  TFile * file = new TFile(filename);
  if(!file){
    cout<<"The following tree does not exit: "<<filename<<" .   Please Check."<<endl;
  }
  TTreeReader *myReader = new TTreeReader(treename, file);
  
  TTreeReaderValue< UInt_t  >  event(            *myReader,       "event");
  TTreeReaderValue< UInt_t  >  run(              *myReader,       "run");
  TTreeReaderValue< UInt_t  >  lumi(             *myReader,       "luminosityBlock");
  TTreeReaderValue< Float_t >  mttau(            *myReader,       "mttau");
  TTreeReaderValue< Float_t >  puWeight(         *myReader,       "puWeight");
  TTreeReaderValue< Float_t >  genWeight(        *myReader,       "genWeight");
  TTreeReaderValue< Float_t >  trigWeight(       *myReader,       "trigWeight");
  TTreeReaderValue< Bool_t  >  trig(             *myReader,       "trigger");
  TTreeReaderValue< Float_t >  mutrigweight(     *myReader,       "mutrigweight");
  TTreeReaderValue< Float_t >  mueffweight(      *myReader,       "mueffweight");
  TTreeReaderValue< Int_t   >  Selection(        *myReader,       "Selection");
  TTreeReaderValue< Float_t >  recoilRatio(      *myReader,       "recoilRatio");
  TTreeReaderValue< Float_t >  recoilDPhi(       *myReader,       "recoilDPhi");
  TTreeReaderValue< Float_t >  met(              *myReader,       "met");
  TTreeReaderValue< Float_t >  metphi(           *myReader,       "metphi");
  TTreeReaderValue< Float_t >  tauPt(            *myReader,       "tauPt");
  TTreeReaderValue< Float_t >  tauEta(           *myReader,       "tauEta");
  TTreeReaderValue< Float_t >  tauPhi(           *myReader,       "tauPhi");
  TTreeReaderValue< Float_t >  tauJetPt(         *myReader,       "tauJetPt");
  TTreeReaderValue< Float_t >  tauJetEta(        *myReader,       "tauJetEta");
  TTreeReaderValue< Bool_t  >  tauJetTightId(    *myReader,       "tauJetTightId");
  TTreeReaderValue< Float_t >  muonPt(           *myReader,       "muonPt");
  TTreeReaderValue< Float_t >  muonEta(          *myReader,       "muonEta");
  TTreeReaderValue< Float_t >  muonPhi(          *myReader,       "muonPhi");
  TTreeReaderValue< Bool_t  >  metFilters(       *myReader,       "metFilters");
  TTreeReaderValue< UInt_t  >  nMuon(            *myReader,       "nMuon");
  TTreeReaderValue< UInt_t  >  nElec(            *myReader,       "nElec");
  TTreeReaderValue< UInt_t  >  nSelTaus(         *myReader,       "nSelTaus");
  TTreeReaderValue< UInt_t  >  nJetsCentral30(   *myReader,       "nJetsCentral30");
  TTreeReaderValue< UInt_t  >  nJetsForward30(   *myReader,       "nJetsForward30");
  TTreeReaderValue< Bool_t  >  tauDM(            *myReader,       "tauDM");
  TTreeReaderValue< Bool_t  >  tauAntiMuonLoose3(*myReader,       "tauAntiMuonTight3");
  TTreeReaderValue< Bool_t  >  tauAntiElectronLooseMVA6(*myReader,"tauAntiElectronVTightMVA6");
  TTreeReaderValue< Bool_t  >  tauIso(           *myReader,       "tau"+iso+"Iso");
  TTreeReaderValue< Float_t >  fakeAntiL(        *myReader,       "fakeAntiL"+iso);
  TTreeReaderValue< Int_t   >  tauGenMatchDecay( *myReader,       "tauGenMatchDecay");
  TTreeReaderValue< UInt_t  >  tauGenMatch(      *myReader,       "tauGenMatch");
  TTreeReaderValue< Int_t   >  tauDecay(         *myReader,       "tauDecay");
  TTreeReaderValue< Float_t >  mtmuon(           *myReader,       "mtmuon");
  TTreeReaderValue< Float_t >  jetPt(            *myReader,       "jetPt");
  TTreeReaderValue< Float_t >  jetEta(           *myReader,       "jetEta");
  TTreeReaderValue< Float_t >  jetPhi(           *myReader,       "jetPhi");
  TTreeReaderValue< Float_t >  recoilPt(         *myReader,       "recoilPt");
  TTreeReaderValue< UInt_t  >  npartons(         *myReader,       "npartons");
  TTreeReaderValue< Float_t >  Ht(               *myReader,       "Ht");
  TTreeReaderValue< Float_t >  mhtNoMu(          *myReader,       "mhtNoMu");
  TTreeReaderValue< Float_t >  metNoMu(          *myReader,       "metNoMu");
  TTreeReaderValue< Float_t >  variable1(        *myReader,       variableToFill_1);
  TTreeReaderValue< Float_t >  variable2(        *myReader,       variableToFill_2);
  
  int nevtsProcessed = getNEventsProcessed(filename);
  double norm = xsec*luminosity/nevtsProcessed;

  bool isData = filename.Contains("SingleMuon") || filename.Contains("JetHT");

  while(myReader->Next()){

    if(*trig != sel.trigger && sel.selection != 1  && sel.selection != 4) continue;
    
    if(*Selection != sel.selection) continue;
    if(*recoilRatio < sel.recoilRatioLow || *recoilRatio > sel.recoilRatioHigh) continue;
    if(*recoilDPhi < sel.recoilDPhiLow) continue;
    if(*met < sel.metLow) continue;
    if(*tauPt < sel.tauPtLow || *tauPt > sel.tauPtHigh) continue;
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
    if((*tauGenMatchDecay<sel.tauGenMatchDecayLow || *tauGenMatchDecay>sel.tauGenMatchDecayHigh) && !isData) continue;
    
    if(*mtmuon < sel.mtmuonLow || *mtmuon > sel.mtmuonHigh ) continue;
        
    Float_t fakerate = 1;
    if(sel.name.Contains("cr_antiiso")) fakerate = getFakeRates(*tauPt/(*tauJetPt), iso + "Iso","");
    if(sel.name.Contains("cr_fakerate")) *trigWeight = 1;
    if(!sel.name.Contains("cr_fakerate")){*mueffweight=1;*mutrigweight=1;}

    // Stitching only for wjets MC
    if(filename.Contains("W") && filename.Contains("JetsToLNu")){
      double xsecIncl = xsecs["WJetsToLNu_13TeV-madgraphMLM"];
      double xsec1Jet = xsecs["W1JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8"];
      double xsec2Jet = xsecs["W2JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8"];
      double xsec3Jet = xsecs["W3JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8"];
      double xsec4Jet = xsecs["W4JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8"];
      double nevtsProcessedIncl = 86731806;
      double nevtsProcessed1Jet = 45367044;
      double nevtsProcessed2Jet = 29878415;
      double nevtsProcessed3Jet = 17548117;
      double nevtsProcessed4Jet = 9020576;

      if(*npartons == 0)       norm = luminosity/( nevtsProcessedIncl/xsecIncl );
      else if (*npartons == 1) norm = luminosity/( nevtsProcessed1Jet/xsec1Jet + nevtsProcessedIncl/xsecIncl );
      else if (*npartons == 2) norm = luminosity/( nevtsProcessed2Jet/xsec2Jet + nevtsProcessedIncl/xsecIncl );
      else if (*npartons == 3) norm = luminosity/( nevtsProcessed3Jet/xsec3Jet + nevtsProcessedIncl/xsecIncl );
      else if (*npartons == 4) norm = luminosity/( nevtsProcessed4Jet/xsec4Jet + nevtsProcessedIncl/xsecIncl );
      else                     norm = luminosity/( nevtsProcessedIncl/xsecIncl );
    }

    if(*recoilPt<sel.recoilPtLow) continue;

    double weight = (*mueffweight)*(*mutrigweight)*(*puWeight)*(*trigWeight)*(*genWeight)*norm*fakerate;
    if(isData) weight =1;
    if(variableToFill_1==variableToFill_2) histo    -> Fill( abs(*variable1), weight );
    else                                   histo    -> Fill( abs(*variable1)/abs(*variable2), weight );
  }

  delete myReader;

}

// ----------------------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------------------
#endif
