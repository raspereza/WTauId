#include "ComputeFakeRate.C"
void ComputeFakeRateSeq() {

  TString iso[6] = {"LooseIso","MediumIso","TightIso","LooseMvaIso","MediumMvaIso","TightMvaIso"};
  bool sample[2] = {true,false};

  for (int iSample=0; iSample<1; ++iSample) {
    for (int iIso=0; iIso<6; ++iIso) {
      ComputeFakeRate(iso[iIso],sample[iSample]);
    }
  }

}
