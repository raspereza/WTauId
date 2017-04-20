#!/bin/bash
tauDecayMode=""
#tauDecayMode="_3prong0pizeros"
#tauDecayMode="_1prong0pizeros"
#tauDecayMode="_1prongUpTo4pizeros"

# Combine datacards
combineCards.py ../output/datacard_mtmuon_WToMuNu.txt ../output/datacard_mttau_LooseMva_WToTauNu${tauDecayMode}.txt > datacard_LooseMva_Combined${tauDecayMode}.txt
combineCards.py ../output/datacard_mtmuon_WToMuNu.txt ../output/datacard_mttau_MediumMva_WToTauNu${tauDecayMode}.txt > datacard_MediumMva_Combined${tauDecayMode}.txt
combineCards.py ../output/datacard_mtmuon_WToMuNu.txt ../output/datacard_mttau_TightMva_WToTauNu${tauDecayMode}.txt > datacard_TightMva_Combined${tauDecayMode}.txt
combineCards.py ../output/datacard_mtmuon_WToMuNu.txt ../output/datacard_mttau_VTightMva_WToTauNu${tauDecayMode}.txt > datacard_VTightMva_Combined${tauDecayMode}.txt
combineCards.py ../output/datacard_mtmuon_WToMuNu.txt ../output/datacard_mttau_Loose_WToTauNu${tauDecayMode}.txt > datacard_Loose_Combined${tauDecayMode}.txt
combineCards.py ../output/datacard_mtmuon_WToMuNu.txt ../output/datacard_mttau_Medium_WToTauNu${tauDecayMode}.txt > datacard_Medium_Combined${tauDecayMode}.txt
combineCards.py ../output/datacard_mtmuon_WToMuNu.txt ../output/datacard_mttau_Tight_WToTauNu${tauDecayMode}.txt > datacard_Tight_Combined${tauDecayMode}.txt

# Run Combine
echo -e  "\n\n\n\n"
./Fitting.csh VTightMva | tee output_VTightMva${tauDecayMode}.txt
echo -e  "\n\n\n\n"
./Fitting.csh TightMva | tee output_TightMva${tauDecayMode}.txt
echo -e  "\n\n\n\n"
./Fitting.csh MediumMva | tee output_MediumMva${tauDecayMode}.txt
echo -e  "\n\n\n\n"
./Fitting.csh LooseMva | tee output_LooseMva${tauDecayMode}.txt
echo -e  "\n\n\n\n"
./Fitting.csh Tight | tee output_Tight${tauDecayMode}.txt
echo -e  "\n\n\n\n"
./Fitting.csh Medium | tee output_Medium${tauDecayMode}.txt
echo -e  "\n\n\n\n"
./Fitting.csh Loose | tee output_Loose${tauDecayMode}.txt

# Read results and output it on the screen
echo -e  "\n\n\n"
echo -e " ------------- RESULTS --------------------------------------------------------------------------------------"
printf "VTightMva : " 
grep "tauId" output_VTightMva.txt | tail -1
printf "TightMva  : " 
grep "tauId" output_TightMva.txt | tail -1
printf "MediumMva : " 
grep "tauId" output_MediumMva.txt | tail -1
printf "LooseMva  : " 
grep "tauId" output_LooseMva.txt | tail -1
printf "Tight     : " 
grep "tauId" output_Tight.txt | tail -1
printf "Medium    : " 
grep "tauId" output_Medium.txt | tail -1
printf "Loose     : " 
grep "tauId" output_Loose.txt | tail -1
echo -e " --------------------- --------------------------------------------------------------------------------------"
echo -e  "\n\n\n"

