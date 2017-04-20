# $1 working point (e.g. VTightMva)
# $2 tauDecayMode (_3prong0pizeros, _1prong0pizeros, _1prongUpTo4pizeros or empty)

combine -M MaxLikelihoodFit --plots --saveNormalizations --saveShapes --saveWithUncertainties --saveNLL --robustFit=1 --rMin=-2 --rMax=2 -m 81 datacard_$1_Combined$2.txt -v2
mv mlfit.root  mlfit_Combined_$1$2.root
