# WTauId

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

The directory datacards contains all datacards for
statistical inference and results of the fits.
 