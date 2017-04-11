#!/bin/sh
combineCards.py ../output/datacard_mtmuon_WToMuNu.txt ../output/datacard_mttau_LooseMva_WToTauNu.txt > datacard_LooseMva_Combined.txt
combineCards.py ../output/datacard_mtmuon_WToMuNu.txt ../output/datacard_mttau_MediumMva_WToTauNu.txt > datacard_MediumMva_Combined.txt
combineCards.py ../output/datacard_mtmuon_WToMuNu.txt ../output/datacard_mttau_TightMva_WToTauNu.txt > datacard_TightMva_Combined.txt
combineCards.py ../output/datacard_mtmuon_WToMuNu.txt ../output/datacard_mttau_VTightMva_WToTauNu.txt > datacard_VTightMva_Combined.txt
combineCards.py ../output/datacard_mtmuon_WToMuNu.txt ../output/datacard_mttau_Loose_WToTauNu.txt > datacard_Loose_Combined.txt
combineCards.py ../output/datacard_mtmuon_WToMuNu.txt ../output/datacard_mttau_Medium_WToTauNu.txt > datacard_Medium_Combined.txt
combineCards.py ../output/datacard_mtmuon_WToMuNu.txt ../output/datacard_mttau_Tight_WToTauNu.txt > datacard_Tight_Combined.txt

