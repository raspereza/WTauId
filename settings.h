#ifndef SETTINGS_H
#define SETTINGS_H

#include <vector>
#include <map>
#include "TString.h"
#include "TTree.h"
#include "TFile.h"
#include "readTree.h"


std::vector<TString> iso;

map<TString, double> xsecs = {
{"W1JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8", 9644.5}, 
{"W2JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8", 3144.5}, 
{"W3JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8", 954.8}, 
{"W4JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8", 485.6}
};
// ----------------------------------------------------------------------------------------------------
void loadWorkingPoints()
{
  iso.push_back("VTightMva");
  //iso.push_back("TightMva");
  //iso.push_back("MediumMva");
  //iso.push_back("LooseMva");
  //iso.push_back("Tight");
  //iso.push_back("Medium");
  //iso.push_back("Loose");
}
// ----------------------------------------------------------------------------------------------------
double getXSec(TString sampleName)
{
  return xsecs[sampleName];
}
// ----------------------------------------------------------------------------------------------------
struct selectionCuts {
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
} sr, cr_antiiso;
// ----------------------------------------------------------------------------------------------------
void initCuts()
{
  // signal region
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

  // antiiso region
  cr_antiiso = sr;
  cr_antiiso.tauIso = false;
}
// ----------------------------------------------------------------------------------------------------
int getNEventsProcessed(TString filename)
{
  TFile * file = new TFile(filename);
  TH1D * histWeightsH = (TH1D*)file->Get("histWeightsH");
  return histWeightsH->GetSumOfWeights();
}
// ----------------------------------------------------------------------------------------------------
bool applyCuts(selectionCuts sel)
{
  
  if(trig != sel.trigger) return false;
  if(Selection != sel.selection) return false;
  if(recoilRatio < sel.recoilRatioLow || recoilRatio > sel.recoilRatioHigh) return false;
  if(recoilDPhi < sel.recoilDPhiLow) return false;
  if(met < sel.metLow) return false;
  if(tauPt < sel.tauPtLow) return false;
  if(metFilters != sel.metFilters) return false;
  
  if(nMuon<sel.nMuonLow || nMuon>sel.nMuonHigh) return false;
  if(nElec<sel.nElecLow || nElec>sel.nElecHigh) return false;
  if(nSelTaus<sel.nSelTausLow || nSelTaus>sel.nSelTausHigh) return false;
  if(nJetsCentral30<sel.nJetsCentral30Low || nJetsCentral30>sel.nJetsCentral30High) return false;
  if(nJetsForward30<sel.nJetsForward30Low || nJetsForward30>sel.nJetsForward30High) return false;
  
  if(tauDM != sel.tauDM) return false;
  if(tauAntiMuonLoose3 != sel.tauAntiMuonLoose3) return false;
  if(tauAntiElectronLooseMVA6 != sel.tauAntiElectronLooseMVA6) return false;
  if(tauIso != sel.tauIso) return false;
  if(tauGenMatchDecay < sel.tauGenMatchDecayLow || tauGenMatchDecay > sel.tauGenMatchDecayHigh ) return false;
  
  return true;
}
// ----------------------------------------------------------------------------------------------------
#endif

