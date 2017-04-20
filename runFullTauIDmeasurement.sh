#!bin/sh

# Make trigger efficiency curve for met trigger (afterwards you need to redo met ntuple)
root -l -b -q PlotTrigger.C

# Compute fake rates in W+jets and dijets events and combine them 
root -l -b -q ComputeFakeRate.C
root -l -b -q CalculateEWKfraction.C   # This script calculates the EWK fraction and combines the SingleMu and JetHT fake rates

# Run W -> tau nu and W -> mu nu measurements and create a root file including all relevant systematics
root -l -b -q WToTauNuMeasurement.C
root -l -b -q WToMuNuMeasurement.C

# Make datacards and run Combine
root -l -b -q DatacardProducer_WToTauNu.C
root -l -b -q DatacardProducer_WToMuNu.C
iniCMSSW_7_4_7
cd datacards
source RunCombine.sh
cd ..

# Make postfit plots 
root -l -b -q MakePostFitPlots.C

# In case you want to do a measurement seperately in the tau decay modes, you need to specify the tau decay mode in setting.h (variable tauDecayMode) and in RunCombine.sh
# Afterwards run all relevant steps again.

# If you want to do a closure test for different fake rates, please run makeClosure.sh
# If you have already the fake rate file and only want to change the tested variable please run only "root -l -b -q ClosureTest_FakeRate.C".
