# WTauId

##########################################################
#########################################################

IMPORTANT: To run the updated analysis code, run  runFullTauIDmeasurement.sh

##########################################################
#########################################################


This is collection of RooT macros used to perform measurements
of the tauId efficiency with W*->tau+v events.

PlotTrigger.C - macro to compute trigger turn on curves for
MET trigger. The macro produces as an output RooT file 
trigger_eff.root with functions describing efficiency of
the MET trigger in dependence of offline MET and 
MHT variable. The newly created file should be placed in the
directory $CMSSW_BASE/src/src/DesyTauAnalyses/NTupleMaker/data
and specified in the configuration file 

ComputeFakeRate.C - computes fake rate as 
a function of tau Pt. One can analyze
either W(->mu+v)+Jets or dijet samples.
The macro produces as an output the RooT file
${dataset}_fakeRate${tauIsolation}.root
where ${dataset} is either SingleMuon_Run2016 or 
JetHT_Run2016, and ${tauIsolation} is tauId
working point : LooseIso, MediumIso, TightIso,
LooseMvaIso, MediumMvaIso or TightMvaIso.

PlotWTauNuBkgd.C - computes fraction of electroweak
events in the anti-isolated tau region of the 
W*->tau+v selection.

PlotFakeRate.C - plot fake rates and compute
combined fake rate for measurements in
W(->mu+v)+Jets or dijet samples. The macro prints out
combined fake for different fake tau pT bins.
The numbers are currently cut and pasted in
the AnalysisNTupleProducer.cc macro. TODO : save 
results in the form of TH1D or TGraphAssymErrors 
to the RooT file, which can be used by the analysis macro 
to apply fake rate to data events in the anti-isolated region.

PlotWMuNu.C - plots mT(mu,MET) (or any other distribution)
in the selected W*->mu+v sample and creates
datacards for statistical inference.

PlotWTauNu.C - plots mT(tau,MET) (or any other distribution)
in the selected sample of W*->tau+v events and
creates datacards for statistical inference.

PlotWMuNuPostfit.C - plots postfit distribution of mT
in the W*->mu+v sample given results of the fit
with combine tool

PlotWTauNuPostfit.C - plots postfit distribution of mT
in the W*->tau+v sample given results of the fit
with combine tool.

All ntuples are located in
/nfs/dust/cms/user/rasp/Run/Run2016/TauID_2016


# Instructions for running AnalysisNTupleProducer macro.

The macro AnalysisNTupleProducer is executed with two
arguments, configuration file and filelist.

Examples of configuration files are

- analysisNTupleProducer.conf (to run on data) 

- analysisNTupleProducer_MC.conf (to run on MC)


Examples of filelists :

MET_Run2016G

WToTauNu_M-200_13TeV-pythia8

WToMuNu_M-200_13TeV-pythia8


Examples of running macro

> AnalysisNTupleProducer analysisNTupleProducer.conf MET_Run2016G

> AnalysisNTupleProducer analysisNTupleProducer_MC.conf WToMuNu_M-200_13TeV-pythia8

Useful scripts :

qsub.sh - submits job to batch system. This script
requires three arguments :

1) code name

2) config file

3) filelist

Example :

> qsub.sh AnalysisNTupleProducer analysisNTupleProducer.conf MET_Run2016G


qsub_seq.sh - submits several jobs per filelist. The script requires
four arguments :

1) code name

2) config file

3) filelist

4) files per job

The script creates directory named $filelis_files.
The directory will contain all RooT and output files
created by separate jobs. Once all jobs are finished,
all RooT files can be merged by executing script hadd.sh

> hadd.sh $filelist.
 
# Instruction to run fits

The directory datacards contains all datacards for
statistical inference and results of the fits.

The datacards from two regions - signal (W*->tau+v) 
and control region (W*->mu+v) are combined using script
CombineCards.sh. This will produce datacards for various
tau ID working points

tauId_LooseMvaIso.txt

tauId_MediumMvaIso.txt

tauId_TightMvaIso.txt

tauId_LooseIso.txt

tauId_MediumIso.txt

tauId_TightIso.txt


To run computation of the tauId, one needs to execute script 

Fitting.csh

and pass as an argument tau isolation working point
(LooseMvaIso, MediumMvaIso, TightMvaIso, LooseIso, MediumIso or TightIso)

Example :

./Fitting.sh MediumIso

This will create mlfit_tauId_MediumIso.root. This file
is then used to plot posfit distributions of fitted variables
(mT(mu,MET) in the W*->mu+v control region and mT(tau,MET) 
in the W*->tau+v signal region).
