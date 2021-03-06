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
#include "TLorentzVector.h"

TString dir = "NTuples/";

TString tauDecayMode = "";
//TString tauDecayMode = "_3prong0pizeros";
//TString tauDecayMode = "_1prong0pizeros";
//TString tauDecayMode = "_1prongUpTo4pizeros";

double luminosity = 35890;
//double luminosity = 1.;
//double luminosity = 36800;

std::vector<TString> iso;
map<TString,TH2D>* h_fakerate = 0;
//TF2* fakerateFunc;

map<TString, double> xsecs = {
{"W1JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8", 1.221*9644.5}, 
{"W2JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8", 1.221*3144.5}, 
{"W3JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8", 1.221*954.8},
{"W4JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8", 1.221*485.6},
{"WJetsToLNu_13TeV-madgraphMLM"                      , 61526.7},
{"WJetsToLNu_13TeV-madgraphMLM-v1"                   , 61526.7},
{"ZJetsToNuNu_HT-100To200_13TeV-madgraph"            , 1.164*280.4},
{"ZJetsToNuNu_HT-200To400_13TeV-madgraph"            , 1.164*77.67},
{"ZJetsToNuNu_HT-400To600_13TeV-madgraph"            , 1.164*10.73},
{"ZJetsToNuNu_HT-600To800_13TeV-madgraph"            , 1.164*4.116},
{"WJetsToLNu_HT-70To100_13TeV-madgraphMLM-pythia8"   , 1.221*2589},
{"WJetsToLNu_HT-100To200_13TeV-madgraphMLM-pythia8"  , 1.221*1345},
{"WJetsToLNu_HT-200To400_13TeV-madgraphMLM-pythia8"  , 1.221*359.7},
{"WJetsToLNu_HT-400To600_13TeV-madgraphMLM-pythia8"  , 1.221*48.91},
{"WJetsToLNu_HT-600To800_13TeV-madgraphMLM-pythia8"  , 1.221*12.05},
{"WJetsToLNu_HT-800To1200_13TeV-madgraphMLM-pythia8" , 1.221*5.501},
{"VVTo2L2Nu_13TeV_amcatnloFXFX"                      , 11.95},
{"WWToLNuQQ_13TeV_powheg"                            , 49.997},
{"WZTo1L1Nu2Q_13TeV_amcatnloFXFX"                    , 10.71},
{"WZTo1L3Nu_13TeV_amcatnloFXFX"                      , 3.05},
{"WZTo2L2Q_13TeV_amcatnloFXFX"                       , 5.595},
{"DYJetsToLL_M-50_13TeV-madgraphMLM"                 , 5765},
{"TTJets_13TeV-powheg"                               , 831.76},
{"ST_t-channel_top_4f_inclusiveDecays_13TeV-powheg"  , 136.95*3*0.108},
{"ST_t-channel_antitop_4f_inclusiveDecays_13TeV-powheg", 80.95*3*0.108},
{"ST_tW_top_5f_inclusiveDecays_13TeV-powheg"         , 35.6},
{"ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg"     , 35.6},
{"WToTauNu_M-200_13TeV-pythia8"                      , 1.3*6.37},
{"WToTauNu_M-200_13TeV-pythia8_jesUp"                , 1.3*6.37},
{"WToTauNu_M-200_13TeV-pythia8_jesDown"              , 1.3*6.37},
{"WToTauNu_M-200_13TeV-pythia8_taues_1prong0pizerosUp"       , 1.3*6.37},
{"WToTauNu_M-200_13TeV-pythia8_taues_1prong0pizerosDown"     , 1.3*6.37},
{"WToTauNu_M-200_13TeV-pythia8_taues_1prongUpTo4pizerosUp"   , 1.3*6.37},
{"WToTauNu_M-200_13TeV-pythia8_taues_1prongUpTo4pizerosDown" , 1.3*6.37},
{"WToTauNu_M-200_13TeV-pythia8_taues_3prong0pizerosUp"       , 1.3*6.37},
{"WToTauNu_M-200_13TeV-pythia8_taues_3prong0pizerosDown"     , 1.3*6.37},
{"WToTauNu_M-200_13TeV-pythia8_uesUp"                , 1.3*6.37},
{"WToTauNu_M-200_13TeV-pythia8_uesDown"              , 1.3*6.37},
{"WToMuNu_M-200_13TeV-pythia8"                       , 1.3*6.32},
{"WToMuNu_M-200_13TeV-pythia8_jesUp"                 , 1.3*6.32},
{"WToMuNu_M-200_13TeV-pythia8_jesDown"               , 1.3*6.32},
{"WToMuNu_M-200_13TeV-pythia8_muUp"                  , 1.3*6.32},
{"WToMuNu_M-200_13TeV-pythia8_muDown"                , 1.3*6.32},
{"WToMuNu_M-200_13TeV-pythia8_uesUp"                 , 1.3*6.32},
{"WToMuNu_M-200_13TeV-pythia8_uesDown"               , 1.3*6.32},
{"WZJToLLLNu_13TeV_amcatnloFXFX"                     , 4.708},
{"ZZTo2L2Q_13TeV_amcatnloFXFX"                       , 3.22},
{"ZZTo4L_13TeV_powheg"                               , 1.212}
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
  bool pfJetTrigger = false;
  float muonAbsEtaHigh = 5.0;
  float muonPtLow = 0.;
} sr, sr_trueTaus, cr_antiiso, cr_fakerate_den, cr_fakerate_num,cr_fakerate_dijet_den, cr_fakerate_dijet_num, cr_ewkFraction, sr_munu;
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

  // sr for true taus
  sr_trueTaus = sr;
  sr_trueTaus.name = "sr_trueTaus";
  sr_trueTaus.tauGenMatchDecayLow  = 0;
  sr_trueTaus.tauGenMatchDecayHigh = 1000000000;
  
  // sr for W->munu selection
  sr_munu = sr;
  sr_munu.name = "sr_munu";
  sr_munu.selection = 2;
  sr_munu.nSelTausLow = 0;
  sr_munu.nSelTausHigh = 0;
  sr_munu.nMuonLow = 1;
  sr_munu.nMuonHigh = 1;
  sr_munu.metLow = 100;
  sr_munu.muonAbsEtaHigh = 2.1;
  sr_munu.muonPtLow = 120;
  sr_munu.trigger = false;
  sr_munu.nJetsCentral30Low  = 0;
  sr_munu.nJetsCentral30High = 0;
  sr_munu.tauPtLow = 0;
   
  // antiiso region
  cr_antiiso = sr;
  cr_antiiso.name = "cr_antiiso";
  cr_antiiso.tauIso = false;

  // cr for ewk fraction
  cr_ewkFraction = cr_antiiso;
  cr_ewkFraction.name = "cr_ewkFraction"; 

  // cr_fakerate_den
  cr_fakerate_den = sr;
  cr_fakerate_den.name = "cr_fakerate_den";
  cr_fakerate_den.selection = 1;
  cr_fakerate_den.nMuonLow  = 1;
  cr_fakerate_den.nMuonHigh = 1;
  cr_fakerate_den.nElecLow  = 0;
  cr_fakerate_den.nElecHigh = 0;
  cr_fakerate_den.nJetsCentral30Low  = 1;
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
  cr_fakerate_dijet_den.nJetsCentral30Low  = 2;
  cr_fakerate_dijet_den.nJetsCentral30High = 2;
  cr_fakerate_dijet_den.nJetsForward30Low  = 0;
  cr_fakerate_dijet_den.nJetsForward30High = 1000000.;
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
  cr_fakerate_dijet_den.pfJetTrigger  = true;
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
  int nevents = histWeightsH->GetSumOfWeights();
  file->Close();
  delete file;
  return nevents;
}
// ----------------------------------------------------------------------------------------------------
void loadFakeRates(TString filename)
{
  h_fakerate = new map<TString,TH2D>();
  TFile *f1 = new TFile(filename,"READ");
  if(!f1){
    cout<<"File "<<filename<<" does not exists. Exiting."<<endl;
    exit(-1);
  }

  TIter next(f1->GetListOfKeys());
  TKey *key = 0;

  while ((key = (TKey*)next())) 
    {
      TClass *c = gROOT->GetClass(key->GetClassName());
      if (!c->InheritsFrom("TH2")) continue;
      TH2D *h = (TH2D*) key->ReadObj();
      h->SetDirectory(0);
      //fakerateFunc = (TF2*) h->GetFunction("f2d");
      h_fakerate -> insert( std::make_pair(h->GetName(),*h) );
      delete h;
    }
  delete key;
}
// ----------------------------------------------------------------------------------------------------
double getFakeRates(float ratio, float jetPt, TString iso, TString err)
{
  for(int i=1; i<= h_fakerate->at(iso).GetNbinsX(); i++){
    if( ratio > h_fakerate->at(iso).GetXaxis()->GetBinLowEdge(i) && ratio < h_fakerate->at(iso).GetXaxis()->GetBinUpEdge(i)){
      for(int j=1; j<= h_fakerate->at(iso).GetNbinsY(); j++){
	if( jetPt > h_fakerate->at(iso).GetYaxis()->GetBinLowEdge(j) && jetPt < h_fakerate->at(iso).GetYaxis()->GetBinUpEdge(j)){
	  if( err == Form("%i%iUp",i,j))         return h_fakerate->at(iso).GetBinContent(i,j) + h_fakerate->at(iso).GetBinError(i,j);
	  else if( err == Form("%i%iDown",i,j) ) return h_fakerate->at(iso).GetBinContent(i,j) - h_fakerate->at(iso).GetBinError(i,j);
	  else                                   return h_fakerate->at(iso).GetBinContent(i,j);
	}
      }
    }
  }
  return 0;

  //if(ratio<0.5 || ratio>1.0 || jetPt<100 || jetPt>1200) return 0;
  //else return fakerateFunc->Eval(ratio,jetPt);
}
// ----------------------------------------------------------------------------------------------------
void makeSelection(TString filename, TString treename, double xsec, TString iso, selectionCuts sel, TH1* histo, TString variableToFill_1, TString variableToFill_2, TString variableToFill_3)
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
  //TTreeReaderValue< Float_t >  mtgen(            *myReader,       "mtgen");
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
  //TTreeReaderValue< Float_t >  genTauWPt(        *myReader,       "genTauWPt");
  //TTreeReaderValue< Float_t >  genTauWEta(       *myReader,       "genTauWEta");
  //TTreeReaderValue< Float_t >  genTauWPhi(       *myReader,       "genTauWPhi");
  //TTreeReaderValue< Float_t >  genTauWE(         *myReader,       "genTauWE");
  TTreeReaderValue< Float_t >  lepWPt(           *myReader,       "lepWPt");
  TTreeReaderValue< Float_t >  lepWEta(          *myReader,       "lepWEta");
  TTreeReaderValue< Float_t >  lepWPhi(          *myReader,       "lepWPhi");
  //TTreeReaderValue< Float_t >  lepWE(            *myReader,      "lepWE");
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
  TTreeReaderValue< Bool_t  >  pfJet40(          *myReader,       "pfJet40");
  TTreeReaderValue< Bool_t  >  pfJet60(          *myReader,       "pfJet60");
  TTreeReaderValue< Bool_t  >  pfJet80(          *myReader,       "pfJet80");
  TTreeReaderValue< Bool_t  >  pfJet140(         *myReader,       "pfJet140");
  
  TTreeReaderValue< Bool_t  >  *pfJet200 = NULL;
  TTreeReaderValue< Bool_t  >  *pfJet260 = NULL;
  TTreeReaderValue< Bool_t  >  *pfJet320 = NULL;
  TTreeReaderValue< Bool_t  >  *pfJet400 = NULL;
  TTreeReaderValue< Bool_t  >  *pfJet450 = NULL;
  TTreeReaderValue< Bool_t  >  *pfJet500 = NULL;
  if(filename.Contains("JetHT")){
    pfJet200 = new TTreeReaderValue<Bool_t>(*myReader,"pfJet200");
    pfJet260 = new TTreeReaderValue<Bool_t>(*myReader,"pfJet260");
    pfJet320 = new TTreeReaderValue<Bool_t>(*myReader,"pfJet320");
    pfJet400 = new TTreeReaderValue<Bool_t>(*myReader,"pfJet400");
    pfJet450 = new TTreeReaderValue<Bool_t>(*myReader,"pfJet450");
    pfJet500 = new TTreeReaderValue<Bool_t>(*myReader,"pfJet500");
  }
  
  TTreeReaderValue< Float_t >  var1(             *myReader,       variableToFill_1);
  TTreeReaderValue< Float_t >  var2(             *myReader,       variableToFill_2);
  TTreeReaderValue< Float_t >  var3(             *myReader,       variableToFill_3);

  // Read Met reweighting histo
  //TH1D* h_met = 0;
  //TFile *f_met = new TFile("output/met_"+iso+"_WToTauNu_closure.root");
  //if(f_met) f_met->GetObject("ratioH",h_met);

  TH2D* h_weights = 0;
  TFile *f_weights = new TFile("output/ReweightingWeights_muonPt_mtmuon_WToMuNu.root");
  if(f_weights) f_weights->GetObject("weights",h_weights);
  else cout<<"File not available"<<endl;

  int nevtsProcessed = getNEventsProcessed(filename);
  double norm = xsec*luminosity/nevtsProcessed;

  bool isData = filename.Contains("SingleMuon") || filename.Contains("JetHT") || filename.Contains("MET");
  while(myReader->Next()){

    if(*trig != sel.trigger && sel.selection == 3) continue;
    if(sel.selection == 4 && (*pfJet40 != sel.pfJetTrigger && *pfJet60 != sel.pfJetTrigger && *pfJet80 != sel.pfJetTrigger && *pfJet140 != sel.pfJetTrigger && *(*pfJet200) != sel.pfJetTrigger && *(*pfJet260) != sel.pfJetTrigger && *(*pfJet320) != sel.pfJetTrigger && *(*pfJet400) != sel.pfJetTrigger && *(*pfJet450) != sel.pfJetTrigger && *(*pfJet500) != sel.pfJetTrigger)) continue;

    if(*Selection != sel.selection) continue;
    if(*recoilRatio < sel.recoilRatioLow || *recoilRatio > sel.recoilRatioHigh) continue;
    if(*recoilDPhi < sel.recoilDPhiLow) continue;
    if(*met < sel.metLow) continue;
    if((*tauPt < sel.tauPtLow || *tauPt > sel.tauPtHigh) && sel.selection!=2) continue;
    if(*metFilters != sel.metFilters) continue;

    if(*nMuon<sel.nMuonLow || *nMuon>sel.nMuonHigh) continue;
    if(*nElec<sel.nElecLow || *nElec>sel.nElecHigh) continue;
    if(*nSelTaus<sel.nSelTausLow || *nSelTaus>sel.nSelTausHigh) continue;
    if(*nJetsCentral30<sel.nJetsCentral30Low || *nJetsCentral30>sel.nJetsCentral30High) continue;
    if(*nJetsForward30<sel.nJetsForward30Low || *nJetsForward30>sel.nJetsForward30High) continue;

    if(*tauDM != sel.tauDM && sel.selection!=2) continue;
    if(*tauAntiMuonLoose3 != sel.tauAntiMuonLoose3 && sel.selection!=2) continue;
    if(*tauAntiElectronLooseMVA6 != sel.tauAntiElectronLooseMVA6 && sel.selection!=2) continue;
    if(*tauIso != sel.tauIso && sel.selection!=2) continue;
    if((*tauGenMatchDecay<sel.tauGenMatchDecayLow || *tauGenMatchDecay>sel.tauGenMatchDecayHigh) && !isData && sel.selection!=2) continue;

    if(*mtmuon < sel.mtmuonLow || *mtmuon > sel.mtmuonHigh ) continue;
    if(abs(*muonEta) > sel.muonAbsEtaHigh && sel.selection == 2) continue;
    if(*muonPt < sel.muonPtLow && sel.selection == 2) continue;

    Float_t fakerate = 1;
    if(sel.name.Contains("cr_antiiso")){
      fakerate = getFakeRates( *tauPt/(*tauJetPt),*tauJetPt,iso, sel.name(11,sel.name.Length()) );
    }
    if(sel.name.Contains("cr_fakerate") || sel.name.Contains("sr_munu")) *trigWeight = 1;
    if(!sel.name.Contains("cr_fakerate") && !sel.name.Contains("sr_munu")){*mueffweight=1;*mutrigweight=1;}

    // Stitching only for wjets MC
    if(filename.Contains("W") && filename.Contains("JetsToLNu") && !filename.Contains("HT")){
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
    if(isData && sel.name.Contains("cr_antiiso")) weight = fakerate;

    if((*tauDecay < 1 || *tauDecay>4) && sel.selection != 2 && tauDecayMode == "_1prongUpTo4pizeros") continue;
    if(*tauDecay != 0 && sel.selection != 2 && tauDecayMode == "_1prong0pizeros") continue;
    if(*tauDecay != 10 && sel.selection != 2 && tauDecayMode == "_3prong0pizeros") continue;

    // Reweight according to MET distribution
    //if(sel.name.Contains("cr_antiiso") && isData){
    //weight = weight*h_met->GetBinContent(h_met->FindBin(*met));
    //}

    
    // Reweight mtmuon-muontPt
    /*
    if(filename.Contains("WToTauNu") && !isData){
      double rew_weight = h_weights->GetBinContent(h_weights->GetXaxis()->FindBin(*genTauWPt),h_weights->GetYaxis()->FindBin(*mtgen));
      if(rew_weight != 0) weight = weight*rew_weight;
      //else{
      //	cout<<"weight is zero"<<endl;
      //cout<<"mttau = "<<*mttau<<endl;
      //}
      //cout<<"weight = "<<weight<<endl<<endl;
    }
    */
    /*
    TLorentzVector genTau;
    genTau.SetPtEtaPhiE(*genTauWPt,*genTauWEta,*genTauWPhi,*genTauWE);
    TLorentzVector genVisTau;
    genVisTau.SetPtEtaPhiE(*lepWPt,*lepWEta,*lepWPhi,*lepWE);
    TLorentzVector genNu;
    genNu = genTau - genVisTau;
    TVector3 tauBoost = genTau.Vect();
    tauBoost = (1./genTau.E()) * tauBoost;
    //genNu.Boost(-1.*tauBoost);
    //double angle = genNu.Vect().Angle(tauBoost);
    //double angle = genNu.Vect()*tauBoost/(genNu.Vect().Mag() * tauBoost.Mag());
    double angle = genNu.Pt()/genVisTau.Pt();
    *var1 = angle;
    *var2 = angle;
    *var3 = angle;
    */
    
    //if(*genTauWPt>400 && *genTauWPt<500) continue;
    //if(isData) continue;

    if( histo->InheritsFrom("TH2") ){
      if(variableToFill_1==variableToFill_2) ((TH2*) histo) -> Fill(abs(*var1), abs(*var3), weight);
      else                                   ((TH2*) histo) -> Fill(abs(*var1)/abs(*var2),abs(*var3), weight);
    }
    else{
      if(variableToFill_1==variableToFill_2) histo    -> Fill( abs(*var1), weight );
      else                                   histo    -> Fill( abs(*var1)/abs(*var2), weight );
    }
  }

  file->Close();
  delete file;
  delete myReader;

}

// ----------------------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------------------
#endif

