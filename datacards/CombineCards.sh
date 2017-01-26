#!/bin/sh
combineCards.py mtmuon_WMuNu.txt mttau_LooseMvaIso_WTauNu.txt > tauId_LooseMvaIso.txt
combineCards.py mtmuon_WMuNu.txt mttau_MediumMvaIso_WTauNu.txt > tauId_MediumMvaIso.txt
combineCards.py mtmuon_WMuNu.txt mttau_TightMvaIso_WTauNu.txt > tauId_TightMvaIso.txt
combineCards.py mtmuon_WMuNu.txt mttau_LooseIso_WTauNu.txt > tauId_LooseIso.txt
combineCards.py mtmuon_WMuNu.txt mttau_MediumIso_WTauNu.txt > tauId_MediumIso.txt
combineCards.py mtmuon_WMuNu.txt mttau_TightIso_WTauNu.txt > tauId_TightIso.txt

