#!bin/sh

# Make trigger efficiency curve for met trigger (afterwards you need to redo met ntuple)
root -l -b -q PlotTrigger.C

# Compute fake rates in W+jets and dijets events and combine them 
root -l -b -q ComputeFakeRate.C
root -l -b -q CalculateEWKfraction.C

# Run W -> tau nu and W -> mu nu measurements and create a root file with all relevant systematics
root -l -b -q WToTauNuMeasurement.C
root -l -b -q WToMuNuMeasurement.C

# Make datacards and combine them
iniCMSSW_7_4_7
root -l -b -q DatacardProducer_WToTauNu.C
root -l -b -q DatacardProducer_WToMuNu.C
cd datacards
source CombineCards.sh
./Fitting.csh VTightMva
./Fitting.csh TightMva
./Fitting.csh MediumMva
./Fitting.csh LooseMva
./Fitting.csh Tight
./Fitting.csh Medium
./Fitting.csh Loose
cd ..

# Make postfit plots 
root -l -b -q MakePostFitPlots.C
