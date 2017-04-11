#include "HttStylesNew.cc"
#include "CMS_lumi.C"
#include "settings.h"
#include <sstream> 

void DatacardProducer_WToMuNu() {

  loadWorkingPoints();
  TString Variable = "mtmuon";

  // ***************
  // Creating datacard inputs
  // *************** 
  TString BaseName = "datacard_"+Variable+"_WToMuNu";
  TString rootFileName =  Variable+"_WToMuNu_shapes.root";

  ostringstream str;
  str << "output/" << BaseName << ".txt";
  string nn = str.str();
  const char * p = nn.c_str();

  // Open histogram with all information
  TFile *in = new TFile("output/" + rootFileName,"READ");
  TH1D* h_data     = 0;
  TH1D* h_WToMuNu = 0;
  TH1D* h_FakeTaus = 0;
  TH1D* h_TrueTaus = 0;
  if(in){
    in -> GetObject("data_obs",h_data);
    in -> GetObject("WToMuNu",h_WToMuNu);
    in -> GetObject("TT",h_FakeTaus);
    in -> GetObject("EWK",h_TrueTaus);
  }

  std::ofstream textFile(p);
  textFile << left;

  textFile << "imax 1   number of channels" << endl;
  textFile << "jmax *   number of backgrounds" << endl;
  textFile << "kmax *   number of nuisance parameters" << endl;
  textFile << "-----------------" << endl;
  textFile << "observation " << h_data->Integral() << endl;
  textFile << "-----------------" << endl;
  textFile << "shapes * * " <<rootFileName << "  $PROCESS    $PROCESS_$SYSTEMATIC " << endl;
  textFile << "-----------------" << endl;
  textFile << setw(30) << "bin"     << setw(15) << "WMuNu" << setw(15) << "WMuNu"    << setw(15) << "WMuNu" << endl;
  textFile << setw(30) << "process" << setw(15) << "W"     << setw(15) << "TT"       << setw(15) << "EWK"   << endl;
  textFile << setw(30) << "process" << setw(15) << "0"     << setw(15) << "1"        << setw(15) << "2"     << endl;
  textFile << setw(30) << "rate"    << setw(15) << h_WToMuNu->Integral() << setw(15) << h_FakeTaus->Integral() << setw(15) << h_TrueTaus->Integral() << endl;
  textFile << "-----------------" << endl;
  textFile << setw(15) << "mu"  << setw(15) << "shape" << setw(15) << "1.00" << setw(15) << "-" << setw(15) << "-" << endl;
  textFile << setw(15) << "jes" << setw(15) << "shape" << setw(15) << "1.00" << setw(15) << "-" << setw(15) << "-" << endl;
  textFile << setw(15) << "ues" << setw(15) << "shape" << setw(15) << "1.00" << setw(15) << "-" << setw(15) << "-" << endl;
  for (int iB=3; iB<=h_data->GetNbinsX(); ++iB) {
    textFile << setw(15) << Form("Bin%i_WToMuNu",iB) << setw(15) << "shape" << setw(15) << "1.00" << setw(15) << "-"    << setw(15) << "-"    << endl;
    textFile << setw(15) << Form("Bin%i_TT",iB)      << setw(15) << "shape" << setw(15) << "-"    << setw(15) << "1.00" << setw(15) << "-"    << endl;
    textFile << setw(15) << Form("Bin%i_EWK",iB)     << setw(15) << "shape" << setw(15) << "-"    << setw(15) << "-"    << setw(15) << "1.00" << endl;
  }
  textFile << setw(15) << "TTNorm"  << setw(15) << "lnN" << setw(15) << "-"    << setw(15) << "1.15" << setw(15) << "-"    << endl;
  textFile << setw(15) << "EWKNorm" << setw(15) << "lnN" << setw(15) << "-"    << setw(15) << "-"    << setw(15) << "1.15" << endl;
  textFile << setw(15) << "MuEff"   << setw(15) << "lnN" << setw(15) << "1.04" << setw(15) << "1.04" << setw(15) << "1.04" << endl;
  
  // *******************
  // end creating datacard inputs
  // *******************
}
