#!/bin/sh
tauDecayMode=""
combineCards.py ../output/datacard_mtmuon_WToMuNu.txt ../output/datacard_mttau_LooseMva_WToTauNu${tauDecayMode}.txt > datacard_LooseMva_Combined${tauDecayMode}.txt
combineCards.py ../output/datacard_mtmuon_WToMuNu.txt ../output/datacard_mttau_MediumMva_WToTauNu${tauDecayMode}.txt > datacard_MediumMva_Combined${tauDecayMode}.txt
combineCards.py ../output/datacard_mtmuon_WToMuNu.txt ../output/datacard_mttau_TightMva_WToTauNu${tauDecayMode}.txt > datacard_TightMva_Combined${tauDecayMode}.txt
combineCards.py ../output/datacard_mtmuon_WToMuNu.txt ../output/datacard_mttau_VTightMva_WToTauNu${tauDecayMode}.txt > datacard_VTightMva_Combined${tauDecayMode}.txt
combineCards.py ../output/datacard_mtmuon_WToMuNu.txt ../output/datacard_mttau_Loose_WToTauNu${tauDecayMode}.txt > datacard_Loose_Combined${tauDecayMode}.txt
combineCards.py ../output/datacard_mtmuon_WToMuNu.txt ../output/datacard_mttau_Medium_WToTauNu${tauDecayMode}.txt > datacard_Medium_Combined${tauDecayMode}.txt
combineCards.py ../output/datacard_mtmuon_WToMuNu.txt ../output/datacard_mttau_Tight_WToTauNu${tauDecayMode}.txt > datacard_Tight_Combined${tauDecayMode}.txt

