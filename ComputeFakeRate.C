#include "HttStylesNew.cc"
#include "TStyle.h"
#include "TF2.h"
#include "settings.h"

void ComputeFakeRate() {

  loadWorkingPoints();
  initCuts();

  TString dir("NTuples/");
  SetStyle();
  TH1::SetDefaultSumw2();
  TH2::SetDefaultSumw2();
  const int nBinsRatio =4;
  double binsRatio[nBinsRatio+1] = { 0.0 , 0.75 , 0.825 , 0.9 , 2. };
  const int nBinsJetPt = 3;
  double binsJetPt[nBinsJetPt+1] = {100 , 150 , 200 , 1200};
  TH2D* h_fakerate_2d = new TH2D("h_fakerate_2d","h_fakerate_2d",nBinsRatio,binsRatio,nBinsJetPt,binsJetPt);
  TH2D* h_fakerate_2d_woTrig = new TH2D("h_fakerate_2d_woTrig","h_fakerate_2d_woTrig",nBinsRatio,binsRatio,nBinsJetPt,binsJetPt);

  std::vector< std::pair<TString,std::vector<TString>> > samples;
  std::vector<TString> data_SingleMuon;
  data_SingleMuon.push_back("SingleMuon_Run2016");
  std::vector<TString> data_JetHT;
  data_JetHT.push_back("JetHT_Run2016");
  std::vector<TString> wjets;
  wjets.push_back("WJetsToLNu_HT-70To100_13TeV-madgraphMLM-pythia8");
  wjets.push_back("WJetsToLNu_HT-100To200_13TeV-madgraphMLM-pythia8");
  wjets.push_back("WJetsToLNu_HT-200To400_13TeV-madgraphMLM-pythia8");
  wjets.push_back("WJetsToLNu_HT-400To600_13TeV-madgraphMLM-pythia8");
  wjets.push_back("WJetsToLNu_HT-600To800_13TeV-madgraphMLM-pythia8");
  wjets.push_back("WJetsToLNu_HT-800To1200_13TeV-madgraphMLM-pythia8");

  std::vector<TString> genuineTaus;
  genuineTaus.push_back("TTJets_13TeV-powheg");
  genuineTaus.push_back("ST_t-channel_top_4f_inclusiveDecays_13TeV-powheg");
  genuineTaus.push_back("ST_t-channel_antitop_4f_inclusiveDecays_13TeV-powheg");
  genuineTaus.push_back("ST_tW_top_5f_inclusiveDecays_13TeV-powheg");
  genuineTaus.push_back("ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg");
  genuineTaus.push_back("VVTo2L2Nu_13TeV_amcatnloFXFX");
  genuineTaus.push_back("WWToLNuQQ_13TeV_powheg");
  genuineTaus.push_back("WZTo1L1Nu2Q_13TeV_amcatnloFXFX");
  genuineTaus.push_back("WZTo1L3Nu_13TeV_amcatnloFXFX");
  genuineTaus.push_back("WZTo2L2Q_13TeV_amcatnloFXFX");
  genuineTaus.push_back("DYJetsToLL_M-50_13TeV-madgraphMLM");
  genuineTaus.push_back("ZJetsToNuNu_HT-100To200_13TeV-madgraph");
  genuineTaus.push_back("ZJetsToNuNu_HT-200To400_13TeV-madgraph");
  genuineTaus.push_back("ZJetsToNuNu_HT-400To600_13TeV-madgraph");
  genuineTaus.push_back("ZJetsToNuNu_HT-600To800_13TeV-madgraph");

  samples.push_back(make_pair("GenuineTausBkg" , genuineTaus));
  samples.push_back(make_pair("WJetsToLNu_13TeV-madgraphMLM" , wjets));
  samples.push_back(make_pair("SingleMuon_Run2016" , data_SingleMuon));
  samples.push_back(make_pair("JetHT_Run2016" , data_JetHT));

  std::map<TString,TH2D*> histoMap;

  for (unsigned int i=0; i<samples.size(); ++i) {

    TFile *fileOutput     = new TFile("output/"+samples[i].first+"_fakeRate.root","recreate");
    TFile *fileOutputUp   = new TFile("output/"+samples[i].first+"_fakeRate_Up.root","recreate");
    TFile *fileOutputDown = new TFile("output/"+samples[i].first+"_fakeRate_Down.root","recreate");

    for(unsigned int idx_iso=0; idx_iso<iso.size(); idx_iso++){

      cout<<endl<<"Process "<<iso[idx_iso]<<" : "<<endl;
      
      // filling histograms
      TH2D* h_den = new TH2D(samples[i].first+"_"+iso[idx_iso]+"_den",samples[i].first+"_"+iso[idx_iso]+"_den",nBinsRatio,binsRatio,nBinsJetPt,binsJetPt);
      TH2D* h_num = new TH2D(samples[i].first+"_"+iso[idx_iso]+"_num",samples[i].first+"_"+iso[idx_iso]+"_num",nBinsRatio,binsRatio,nBinsJetPt,binsJetPt);
      TH2D* h_den_woTrig = new TH2D(samples[i].first+"_"+iso[idx_iso]+"_den_woTrig",samples[i].first+"_"+iso[idx_iso]+"_den_woTrig",nBinsRatio,binsRatio,nBinsJetPt,binsJetPt);
      TH2D* h_num_woTrig = new TH2D(samples[i].first+"_"+iso[idx_iso]+"_num_woTrig",samples[i].first+"_"+iso[idx_iso]+"_num_woTrig",nBinsRatio,binsRatio,nBinsJetPt,binsJetPt);

      TString var1 = "tauPt";
      TString var2 = "tauJetPt";
      TString var3 = "tauJetPt";
      for(unsigned int idx_list=0; idx_list<samples[i].second.size(); idx_list++){
	cout<<"---------- Sample "<<samples[i].second[idx_list]<<" processing. ---------- "<<endl;
	selectionCuts select = cr_fakerate_num;
	cr_fakerate_dijet_num.pfJetTrigger = true;
	if(samples[i].second[idx_list].Contains("JetHT")) select =  cr_fakerate_dijet_num;
	if(samples[i].first.Contains("Genuine")){
	  select.tauGenMatchDecayLow   = 0;
	  select.tauGenMatchDecayHigh  = 100000;
	}
	makeSelection(dir+samples[i].second[idx_list]+".root","NTuple",getXSec(samples[i].second[idx_list]),iso[idx_iso],select,h_num,var1,var2,var3);
	select = cr_fakerate_den;
	cr_fakerate_dijet_den.pfJetTrigger = true;
	if(samples[i].second[idx_list].Contains("JetHT")) select =  cr_fakerate_dijet_den;
	if(samples[i].first.Contains("Genuine")){
	  select.tauGenMatchDecayLow   = 0;
	  select.tauGenMatchDecayHigh  = 100000;
	}
	makeSelection(dir+samples[i].second[idx_list]+".root","NTuple",getXSec(samples[i].second[idx_list]),iso[idx_iso],select,h_den,var1,var2,var3);

	// wo Trigger
	cr_fakerate_dijet_num.pfJetTrigger = false;
	if(samples[i].second[idx_list].Contains("JetHT")) select =  cr_fakerate_dijet_num;
	makeSelection(dir+samples[i].second[idx_list]+".root","NTuple",getXSec(samples[i].second[idx_list]),iso[idx_iso],select,h_num_woTrig,var1,var2,var3);
	select = cr_fakerate_den;
	cr_fakerate_dijet_den.pfJetTrigger = false;
 	if(samples[i].second[idx_list].Contains("JetHT")) select =  cr_fakerate_dijet_den;
	makeSelection(dir+samples[i].second[idx_list]+".root","NTuple",getXSec(samples[i].second[idx_list]),iso[idx_iso],select,h_den_woTrig,var1,var2,var3);
      }

      histoMap[samples[i].first + "_" + iso[idx_iso]] = (TH2D*) h_num -> Clone();
      histoMap[samples[i].first + "_" + iso[idx_iso]] -> SetDirectory(0);

      double numE = 0;
      double denE = 0;
      double num  = h_num -> IntegralAndError(1,h_num->GetNbinsX(),1,h_num->GetNbinsY(),numE);
      double den  = h_den -> IntegralAndError(1,h_den->GetNbinsX(),1,h_den->GetNbinsY(),denE);

      cout<<samples[i].first<<" : "<<num<<"/"<<den<<" = "<<num/den<<" +/- "<<numE/den<<" (nevents = "<<h_num->GetEntries()<<"/"<<h_den->GetEntries()<<")"<<endl<<endl;
      
      // Subtract genuine taus
      if(samples[i].first.Contains("SingleMu"))	h_num -> Add(histoMap["GenuineTausBkg_"+iso[idx_iso]],-1);

      // Statistical precision of fakerate:
      for(int i=1; i<=h_num->GetNbinsX(); i++)
	{for(int j=1; j<=h_num->GetNbinsY(); j++)
	    {
	      double numE_bin = 0;
	      double num_bin = h_num -> IntegralAndError(i,i,j,j,numE_bin);
	      cout<<"Numerator of "<<i<<". x-bin and "<<j<<". y-bin : "<<num_bin<<" +/- "<<numE_bin<<endl;	      
	    }
	}

      h_fakerate_2d -> Divide(h_num,h_den);
      h_fakerate_2d_woTrig -> Divide(h_num_woTrig,h_den_woTrig);

      h_fakerate_2d->GetXaxis()->SetTitle("pt (tau) / pt (jet faking the tau)");
      h_fakerate_2d->GetYaxis()->SetTitle("pt (jet faking the tau)");
      h_fakerate_2d->GetZaxis()->SetTitle("fake rate");
      h_fakerate_2d->SetTitle("");
      h_fakerate_2d->SetMarkerSize(2);
      h_fakerate_2d->SetMaximum(1);
      h_fakerate_2d->SetMinimum(0);

      // Fit TH2D with double exp function
      /*
      TF2* f2d = new TF2("f2d","[0]*exp([1]*x)*exp([2]*y)");
      h_fakerate_2d->Fit("f2d");
      cout<<endl;
      cout<<"chi2 = "<<f2d->GetChisquare()<<endl;
      cout<<"ndof = "<<f2d->GetNDF()<<endl;
      cout<<"par0 = "<<f2d->GetParameter(0)<<" +/- "<<f2d->GetParError(0)<<endl;
      cout<<"par1 = "<<f2d->GetParameter(1)<<" +/- "<<f2d->GetParError(1)<<endl;
      cout<<"par2 = "<<f2d->GetParameter(2)<<" +/- "<<f2d->GetParError(2)<<endl;
      cout<<endl;
      */
      // Fit the fakerate
      /*
      TF1* f = new TF1("func","expo(0)");
      h_fakerate_2d -> FitSlicesX(f,1,h_fakerate_2d->GetNbinsY(),0,"");
      TH1D *par0 = (TH1D*)gDirectory->Get("h_fakerate_2d_0");
      par0->SetName("par0");
      TH1D *par1 = (TH1D*)gDirectory->Get("h_fakerate_2d_1");
      par1->SetName("par1");
      TH1D *chi2 = (TH1D*)gDirectory->Get("h_fakerate_2d_chi2");
      chi2->SetName("chi2OverNDF");
      f->SetLineColor(kRed);
      */
     
      gStyle -> SetPadBottomMargin(0.17);
      gStyle -> SetPadLeftMargin(0.17);
      gStyle -> SetPadTopMargin(0.12);
      gStyle -> SetPadRightMargin(0.20);

      TCanvas * canv = new TCanvas("canv","",700,600);
      h_fakerate_2d->Draw("COLZ");

      TLegend * leg = new TLegend(0.25,0.7,0.85,0.9);
      SetLegendStyle(leg);
      leg->SetHeader(iso[idx_iso]);
      leg->AddEntry(h_fakerate_2d,samples[i].first,"lp");
      leg->Draw();
      canv->Update();
      canv->Print("figures/fakerate_"+samples[i].first+"_"+iso[idx_iso]+".png");

      // Make 1d plots dependent on tauPt/tauJetPt 
      //TH1D* h = h_fakerate_2d -> ProjectionX("fakerate_projection_withTrig",1,nBinsJetPt);
      TH1D* h = h_fakerate_2d -> ProjectionY("fakerate_projection_withTrig",1,nBinsRatio);
      //TF1* f1 = new TF1("f1","[0]*exp([1]*x)");
      //h->Fit("f1");
      h->SetMaximum(1.);
      h->SetMinimum(0.00001);
      //TH1D* h_woTrig = h_fakerate_2d_woTrig -> ProjectionX("fakerate_projection_woTrig",1,nBinsJetPt);
      TH1D* h_woTrig = h_fakerate_2d_woTrig -> ProjectionY("fakerate_projection_woTrig",1,nBinsRatio);
      h_woTrig->SetMaximum(1.);
      h_woTrig->SetMinimum(0.0001);
      h_woTrig->SetLineColor(kRed);
      h_woTrig->SetMarkerColor(kRed);
      h->Draw();
      //h_woTrig->Draw("same");
      canv->SetLogy();
      TLegend * leg1 = new TLegend(0.45,0.2,0.89,0.4);
      SetLegendStyle(leg1);
      leg1->SetHeader(iso[idx_iso]);
      leg1->AddEntry(h,"with Trigger","lp");
      leg1->AddEntry(h_woTrig,"without Trigger","lp");
      leg1->Draw();
      canv->Print("figures/fakerate_"+samples[i].first+"_"+iso[idx_iso]+"_projectionY.png");

      fileOutput->cd("");
      h_fakerate_2d->SetName(iso[idx_iso]);
      h_fakerate_2d->Write(iso[idx_iso]);
      delete canv;
      cout<<endl;

      // Save also up- and downward variations
      TH1D* h_fakerate_2d_up = (TH1D*) h_fakerate_2d->Clone();
      TH1D* h_fakerate_2d_down = (TH1D*) h_fakerate_2d->Clone();
      for(int i=1; i<=h_fakerate_2d->GetNbinsX(); i++){
	for(int j=1; j<=h_fakerate_2d->GetNbinsY(); j++){
	  h_fakerate_2d_up->SetBinContent(i,j , h_fakerate_2d->GetBinContent(i,j) + h_fakerate_2d->GetBinError(i,j) );
	  h_fakerate_2d_down->SetBinContent(i,j , h_fakerate_2d->GetBinContent(i,j) - h_fakerate_2d->GetBinError(i,j) );
	}
      }
      fileOutputUp->cd("");
      h_fakerate_2d_up->SetName(iso[idx_iso]);
      h_fakerate_2d_up->Write(iso[idx_iso]);
      fileOutputDown->cd("");
      h_fakerate_2d_down->SetName(iso[idx_iso]);
      h_fakerate_2d_down->Write(iso[idx_iso]);

    }
    fileOutput->Close();
  }
}
