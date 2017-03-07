#!/bin/sh

# 1.) First make ntuples for measuring trigger eff SF and fake rate: SingleMuon (needed for trigger eff and fake rate), WJets (needed for trigger eff. and fake rate), JetHT (needed for fake rate only)
#     e.g. ./qsub_seq.sh AnalysisNTupleProducer analysisNTupleProducer_MC.conf WJetsToLNu 5

# 2.) 
# root -l -b -q PlotTrigger.C"()" #(used samples: SingleMuon_Run2016.root andWJetsToLNu_13TeV-madgraphMLM.root )

# 3.) Calculate Fake rate in dijet (JetHT) and W+jet->mu nu +jet (SingleMuon) events with data (WJets MC sample only needed for comparison - but is not used for later results)
#root -l -b -q ComputeFakeRate.C"(true)"
#root -l -b -q ComputeFakeRate.C"(false)"

# 4.) Make all MC and data samples with trigger efficiency scale factors included

# 5.) Calculate n_EWK in antiiso region with n_EWK = n_EWK^MC / n^data
#root -l -b -q PlotWTauNuBkgd.C"()"

# 6.) Calculate combined fake rate
#root -l -b -q PlotFakeRate.C"()"

# 7.) Make MET (data) ntuple again with fake rate included

# 8.) Make datacards with final selection for tau id measurement
#root -l -b -q PlotWTauNu.C"()"
#root -l -b -q PlotWMuNu.C"()"

# 9.) Run combine
#cd datacards
#iniCMSSW_7_4_7()
#source CombineCards.sh
#./Fitting.csh VTightMvaIso
#./Fitting.csh TightMvaIso
#./Fitting.csh MediumMvaIso
#./Fitting.csh LooseMvaIso
#./Fitting.csh TightIso
#./Fitting.csh MediumIso
#./Fitting.csh LooseIso
 cd ..

# 10.) Make postfit plots
#root -l -b -q PlotWTauNuPostFit.C"()"
#root -l -b -q PlotWMuNuPostFit.C"()"

# Example for Ntuple production 
# AnalysisNTupleProducer analysisNTupleProducer_jesUp.conf WToTauNu_M-200_13TeV-pythia8_jesUp