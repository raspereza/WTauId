#!/bin/sh
combineCards.py ../output/mtmuon_WMuNu.txt ../output/mttau_LooseMvaIso_WTauNu.txt > tauId_LooseMvaIso.txt
combineCards.py ../output/mtmuon_WMuNu.txt ../output/mttau_MediumMvaIso_WTauNu.txt > tauId_MediumMvaIso.txt
combineCards.py ../output/mtmuon_WMuNu.txt ../output/mttau_TightMvaIso_WTauNu.txt > tauId_TightMvaIso.txt
combineCards.py ../output/mtmuon_WMuNu.txt ../output/mttau_VTightMvaIso_WTauNu.txt > tauId_VTightMvaIso.txt
combineCards.py ../output/mtmuon_WMuNu.txt ../output/mttau_LooseIso_WTauNu.txt > tauId_LooseIso.txt
combineCards.py ../output/mtmuon_WMuNu.txt ../output/mttau_MediumIso_WTauNu.txt > tauId_MediumIso.txt
combineCards.py ../output/mtmuon_WMuNu.txt ../output/mttau_TightIso_WTauNu.txt > tauId_TightIso.txt

