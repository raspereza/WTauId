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
echo -e  "\n\n\n ----------------------------- VTightMva ${tauDecayMode} \n"
./Fitting.csh VTightMva | tee output_VTightMva${tauDecayMode}.txt
echo -e  "\n\n\n ----------------------------- TightMva ${tauDecayMode} \n"
./Fitting.csh TightMva | tee output_TightMva${tauDecayMode}.txt
echo -e  "\n\n\n ----------------------------- MediumMva ${tauDecayMode} \n"
./Fitting.csh MediumMva | tee output_MediumMva${tauDecayMode}.txt
echo -e  "\n\n\n ----------------------------- LooseMva ${tauDecayMode} \n"
./Fitting.csh LooseMva | tee output_LooseMva${tauDecayMode}.txt
echo -e  "\n\n\n ----------------------------- Tight ${tauDecayMode} \n"
./Fitting.csh Tight | tee output_Tight${tauDecayMode}.txt
echo -e  "\n\n\n ----------------------------- Medium ${tauDecayMode} \n"
./Fitting.csh Medium | tee output_Medium${tauDecayMode}.txt
echo -e  "\n\n\n ----------------------------- Loose ${tauDecayMode} \n"
./Fitting.csh Loose | tee output_Loose${tauDecayMode}.txt

# Read results and output it on the screen
echo -e  "\n\n\n"
echo -e " ------------- RESULTS ${tauDecayMode} --------------------------------------------------------------------------------------"
printf "VTightMva : " 
grep "tauId" output_VTightMva${tauDecayMode}.txt | tail -1
printf "TightMva  : " 
grep "tauId" output_TightMva${tauDecayMode}.txt | tail -1
printf "MediumMva : " 
grep "tauId" output_MediumMva${tauDecayMode}.txt | tail -1
printf "LooseMva  : " 
grep "tauId" output_LooseMva${tauDecayMode}.txt | tail -1
printf "Tight     : " 
grep "tauId" output_Tight${tauDecayMode}.txt | tail -1
printf "Medium    : " 
grep "tauId" output_Medium${tauDecayMode}.txt | tail -1
printf "Loose     : " 
grep "tauId" output_Loose${tauDecayMode}.txt | tail -1
echo -e " --------------------- --------------------------------------------------------------------------------------"
echo -e  "\n\n\n"

