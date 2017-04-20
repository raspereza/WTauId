#include "HttStylesNew.cc"
#include "CMS_lumi.C"
#include "settings.h"
#include <sstream> 

void DatacardProducer_WToTauNu() {

  loadWorkingPoints();
  TString Variable = "mttau";

  for(unsigned int idx_iso=0; idx_iso<iso.size(); idx_iso++){

    // ***************
    // Creating datacard inputs
    // *************** 
    TString BaseName = "datacard_"+Variable+"_"+iso[idx_iso]+"_WToTauNu";
    TString rootFileName =  Variable+"_"+iso[idx_iso]+"_WToTauNu_shapes" + tauDecayMode + ".root";

    ostringstream str;
    str << "output/" << BaseName << tauDecayMode << ".txt";
    string nn = str.str();
    const char * p = nn.c_str();

    // Open histogram with all information
    TFile *in = new TFile("output/" + rootFileName,"READ");
    TH1D* h_data     = 0;
    TH1D* h_WToTauNu = 0;
    TH1D* h_FakeTaus = 0;
    TH1D* h_TrueTaus = 0;
    if(in){
      in -> GetObject("data_obs",h_data);
      in -> GetObject("W"       ,h_WToTauNu);
      in -> GetObject("FakeTaus",h_FakeTaus);
      in -> GetObject("TrueTaus",h_TrueTaus);
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
    textFile << setw(30) << "bin"     << setw(15) << "WTauNu" << setw(15) << "WTauNu"   << setw(15) << "WTauNu"   << endl;
    textFile << setw(30) << "process" << setw(15) << "W"      << setw(15) << "FakeTaus" << setw(15) << "TrueTaus" << endl;
    textFile << setw(30) << "process" << setw(15) << "0"      << setw(15) << "1"        << setw(15) << "2"        << endl;
    textFile << setw(30) << "rate"    << setw(15) << h_WToTauNu->Integral() << setw(15) << h_FakeTaus->Integral() << setw(15) << h_TrueTaus->Integral() << endl;
    textFile << "-----------------" << endl;
    textFile << setw(15) << "taues" << setw(15) << "shape" << setw(15) << "1.00" << setw(15) << "-" << setw(15) << "-" << endl;
    textFile << setw(15) << "jes"   << setw(15) << "shape" << setw(15) << "1.00" << setw(15) << "-" << setw(15) << "-" << endl;
    textFile << setw(15) << "ues"   << setw(15) << "shape" << setw(15) << "1.00" << setw(15) << "-" << setw(15) << "-" << endl;
    for (int iB=3; iB<=h_data->GetNbinsX(); ++iB) {
      textFile << setw(15) << Form("Bin%i_WToTauNu",iB) << setw(15) << "shape" << setw(15) << "1.00" << setw(15) << "-"    << setw(15) << "-"    << endl;
      textFile << setw(15) << Form("Bin%i_FakeTaus",iB) << setw(15) << "shape" << setw(15) << "-"    << setw(15) << "1.00" << setw(15) << "-"    << endl;
      textFile << setw(15) << Form("Bin%i_TrueTaus",iB) << setw(15) << "shape" << setw(15) << "-"    << setw(15) << "-"    << setw(15) << "1.00" << endl;
    }
    for (int i=1; i<=4; ++i) {
      for (int j=1; j<=3; ++j) {
	textFile << setw(15) << Form("FR%i%i",i,j) << setw(15) << "shape" << setw(15) << "-" << setw(15) << "1.00" << setw(15) << "-" << endl;
      }
    }
    textFile << setw(15) << "BkgdNorm" << setw(15) << "lnN" << setw(15) << "-"     << setw(15) << "-"     << setw(15) << "1.30"  << endl;
    textFile << setw(15) << "lumi"     << setw(15) << "lnN" << setw(15) << "1.027" << setw(15) << "1.027" << setw(15) << "1.027" << endl;
    textFile << "tauId  rateParam WTauNu W  1  [0.0,1.5]" << endl;
  
    // *******************
    // end creating datacard inputs
    // *******************
  }
}
