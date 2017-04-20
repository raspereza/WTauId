tauDecayMode=""
combine -M MaxLikelihoodFit --plots --saveNormalizations --saveShapes --saveWithUncertainties --saveNLL --robustFit=1 --rMin=-2 --rMax=2 -m 81 datacard_$1_Combined${tauDecayMode}.txt -v2
mv mlfit.root  mlfit_Combined_$1${tauDecayMode}.root
