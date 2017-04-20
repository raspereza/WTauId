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
  //double binsRatio[nBinsRatio+1] = { 0.0 , 0.70 , 0.75 , 0.8 , 0.85 , 0.9 , 0.95 , 2. };
  const int nBinsJetPt = 5;
  //double binsJetPt[nBinsJetPt+1] = {100 , 190 , 240 , 1200};
  double binsJetPt[nBinsJetPt+1] = {100 , 150 , 200 , 350 , 500 , 1200};
  //double binsJetPt[nBinsJetPt+1] = {100 , 170 , 240 , 310 , 390 , 480 , 540 , 600 , 1200};
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
  //samples.push_back(make_pair("WJetsToLNu_13TeV-madgraphMLM" , wjets));
  samples.push_back(make_pair("SingleMuon_Run2016" , data_SingleMuon));
  //samples.push_back(make_pair("JetHT_Run2016" , data_JetHT));

  std::map<TString,TH2D*> histoMap;

  for (unsigned int idx_sample=0; idx_sample<samples.size(); ++idx_sample) {

    TFile *fileOutput     = new TFile("output/"+samples[idx_sample].first+"_fakeRate.root","recreate");
    TFile *fileOutputUp   = new TFile("output/"+samples[idx_sample].first+"_fakeRate_Up.root","recreate");
    TFile *fileOutputDown = new TFile("output/"+samples[idx_sample].first+"_fakeRate_Down.root","recreate");

    for(unsigned int idx_iso=0; idx_iso<iso.size(); idx_iso++){

      cout<<endl<<"Process "<<iso[idx_iso]<<" : "<<endl;
      
      // filling histograms
      TH2D* h_den = new TH2D(samples[idx_sample].first+"_"+iso[idx_iso]+"_den",samples[idx_sample].first+"_"+iso[idx_iso]+"_den",nBinsRatio,binsRatio,nBinsJetPt,binsJetPt);
      TH2D* h_num = new TH2D(samples[idx_sample].first+"_"+iso[idx_iso]+"_num",samples[idx_sample].first+"_"+iso[idx_iso]+"_num",nBinsRatio,binsRatio,nBinsJetPt,binsJetPt);
      TH2D* h_den_woTrig = new TH2D(samples[idx_sample].first+"_"+iso[idx_iso]+"_den_woTrig",samples[idx_sample].first+"_"+iso[idx_iso]+"_den_woTrig",nBinsRatio,binsRatio,nBinsJetPt,binsJetPt);
      TH2D* h_num_woTrig = new TH2D(samples[idx_sample].first+"_"+iso[idx_iso]+"_num_woTrig",samples[idx_sample].first+"_"+iso[idx_iso]+"_num_woTrig",nBinsRatio,binsRatio,nBinsJetPt,binsJetPt);

      TString var1 = "tauPt";
      TString var2 = "tauJetPt";
      TString var3 = "tauJetPt";
      for(unsigned int idx_list=0; idx_list<samples[idx_sample].second.size(); idx_list++){
	cout<<"---------- Sample "<<samples[idx_sample].second[idx_list]<<" processing. ---------- "<<endl;
	selectionCuts select = cr_fakerate_num;
	cr_fakerate_dijet_num.pfJetTrigger = true;
	if(samples[idx_sample].second[idx_list].Contains("JetHT")) select =  cr_fakerate_dijet_num;
	if(samples[idx_sample].first.Contains("Genuine")){
	  select.tauGenMatchDecayLow   = 0;
	  select.tauGenMatchDecayHigh  = 100000;
	}
	makeSelection(dir+samples[idx_sample].second[idx_list]+".root","NTuple",getXSec(samples[idx_sample].second[idx_list]),iso[idx_iso],select,h_num,var1,var2,var3);
	select = cr_fakerate_den;
	cr_fakerate_dijet_den.pfJetTrigger = true;
	if(samples[idx_sample].second[idx_list].Contains("JetHT")) select =  cr_fakerate_dijet_den;
	if(samples[idx_sample].first.Contains("Genuine")){
	  select.tauGenMatchDecayLow   = 0;
	  select.tauGenMatchDecayHigh  = 100000;
	}
	makeSelection(dir+samples[idx_sample].second[idx_list]+".root","NTuple",getXSec(samples[idx_sample].second[idx_list]),iso[idx_iso],select,h_den,var1,var2,var3);

	// wo Trigger
	//cr_fakerate_dijet_num.pfJetTrigger = false;
	if(samples[idx_sample].second[idx_list].Contains("JetHT")) select =  cr_fakerate_dijet_num;
	select.selection = 5;
	makeSelection(dir+samples[idx_sample].second[idx_list]+".root","NTuple",getXSec(samples[idx_sample].second[idx_list]),iso[idx_iso],select,h_num_woTrig,var1,var2,var3);
	select = cr_fakerate_den;
	//cr_fakerate_dijet_den.pfJetTrigger = false;
 	if(samples[idx_sample].second[idx_list].Contains("JetHT")) select =  cr_fakerate_dijet_den;
	select.selection = 5;
	makeSelection(dir+samples[idx_sample].second[idx_list]+".root","NTuple",getXSec(samples[idx_sample].second[idx_list]),iso[idx_iso],select,h_den_woTrig,var1,var2,var3);
      }

      histoMap[samples[idx_sample].first + "_" + iso[idx_iso]] = (TH2D*) h_num -> Clone();
      histoMap[samples[idx_sample].first + "_" + iso[idx_iso]] -> SetDirectory(0);
      
      double numE = 0;
      double denE = 0;
      double num  = h_num -> IntegralAndError(1,h_num->GetNbinsX(),1,h_num->GetNbinsY(),numE);
      double den  = h_den -> IntegralAndError(1,h_den->GetNbinsX(),1,h_den->GetNbinsY(),denE);

      cout<<samples[idx_sample].first<<" : "<<num<<"/"<<den<<" = "<<num/den<<" +/- "<<numE/den<<" (nevents = "<<h_num->GetEntries()<<"/"<<h_den->GetEntries()<<")"<<endl<<endl;
      
      // Subtract genuine taus and get correct error estimates
      if(samples[idx_sample].first.Contains("SingleMu")) h_num -> Add(histoMap["GenuineTausBkg_"+iso[idx_iso]],-1);

      // Ckeck negative or zero values
      for(int i=1; i<=h_num->GetNbinsX(); i++){
	for(int j=1; j<=h_num->GetNbinsY(); j++){

	      if(samples[idx_sample].first.Contains("Genuine")) continue;
	      if(h_num->GetBinContent(i,j)==0) h_num->SetBinError(i,j,1);
	      if(h_num->GetBinContent(i,j)<0){
		//cout<<endl<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! Attention: There is a negative value in the numerator. Bin "<<i<<" " <<j<<"."<<endl<<endl;
		if(h_num->GetBinContent(i,j) == (-1)*histoMap["GenuineTausBkg_"+iso[idx_iso]]->GetBinContent(i,j)){
		  //cout<<"data was zero"<<endl<<endl;
		  h_num->SetBinContent(i,j,0);
		  h_num->SetBinError(i,j, sqrt(1+pow(h_num->GetBinError(i,j),2)) );
		}
		else{
		  h_num->SetBinContent(i,j,0);
		  h_num->SetBinError(i,j, h_num->GetBinError(i,j) );
		}
	      }

	}
      }
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


      // %%%%%%%%%%%%%%%%%% Plotting %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
      h_fakerate_2d->GetXaxis()->SetTitle("pt (tau) / pt (jet faking the tau)");
      h_fakerate_2d->GetYaxis()->SetTitle("pt (jet faking the tau)");
      h_fakerate_2d->GetZaxis()->SetTitle("fake rate");
      h_fakerate_2d->SetTitle("");
      h_fakerate_2d->SetMarkerSize(2);
      h_fakerate_2d->SetMaximum(1);
      h_fakerate_2d->SetMinimum(0);

      gStyle -> SetPadBottomMargin(0.17);
      gStyle -> SetPadLeftMargin(0.17);
      gStyle -> SetPadTopMargin(0.12);
      gStyle -> SetPadRightMargin(0.20);

      TCanvas * canv = new TCanvas("canv","",700,600);
      h_fakerate_2d->Draw("COLZ");

      TLegend * leg = new TLegend(0.25,0.7,0.85,0.9);
      SetLegendStyle(leg);
      leg->SetTextSize(0.05);
      leg->SetHeader(iso[idx_iso]);
      leg->AddEntry(h_fakerate_2d,samples[idx_sample].first,"lp");
      leg->Draw();
      canv->Update();
      canv->Print("figures/fakerate_"+samples[idx_sample].first+"_"+iso[idx_iso]+".png");

      // Make 1d plots dependent on tauPt/tauJetPt 
      TH1D* h_num_1D_x        = h_num -> ProjectionX("fakerate_projection_withTrig_num_x",1,nBinsJetPt);
      TH1D* h_den_1D_x        = h_den -> ProjectionX("fakerate_projection_withTrig_den_x",1,nBinsJetPt);
      TH1D* h_num_woTrig_1D_x = h_num_woTrig -> ProjectionX("fakerate_projection_woTrig_num_x",1,nBinsJetPt);
      TH1D* h_den_woTrig_1D_x = h_den_woTrig -> ProjectionX("fakerate_projection_woTrig_den_x",1,nBinsJetPt);
      TH1D* h_num_1D_y        = h_num -> ProjectionY("fakerate_projection_withTrig_num_y",1,nBinsJetPt);
      TH1D* h_den_1D_y        = h_den -> ProjectionY("fakerate_projection_withTrig_den_y",1,nBinsJetPt);
      TH1D* h_num_woTrig_1D_y = h_num_woTrig -> ProjectionY("fakerate_projection_woTrig_num_y",1,nBinsJetPt);
      TH1D* h_den_woTrig_1D_y = h_den_woTrig -> ProjectionY("fakerate_projection_woTrig_den_y",1,nBinsJetPt);

      TH1D* h_x = (TH1D*) h_num_1D_x->Clone();
      h_x->Divide(h_den_1D_x);
      TH1D* h_woTrig_x = (TH1D*) h_num_woTrig_1D_x->Clone();
      h_woTrig_x->Divide(h_den_woTrig_1D_x);
      TH1D* h_y = (TH1D*) h_num_1D_y->Clone();
      h_y->Divide(h_den_1D_y);
      TH1D* h_woTrig_y = (TH1D*) h_num_woTrig_1D_y->Clone();
      h_woTrig_y->Divide(h_den_woTrig_1D_y);

      h_x->SetMaximum(1.);
      h_x->SetMinimum(0.0001);
      h_y->SetMaximum(1.);
      h_y->SetMinimum(0.0001);
      h_woTrig_x->SetLineColor(kRed);
      h_woTrig_x->SetMarkerColor(kRed);
      h_woTrig_y->SetLineColor(kRed);
      h_woTrig_y->SetMarkerColor(kRed);
      h_x->Draw();
      h_woTrig_x->Draw("same");
      canv->SetLogy();
      TLegend * leg1 = new TLegend(0.35,0.2,0.89,0.4);
      SetLegendStyle(leg1);
      leg1->SetHeader(iso[idx_iso]);
      leg1->AddEntry(h_x,"low pt triggers","lp");
      leg1->AddEntry(h_woTrig_x,"all triggers","lp");
      leg1->Draw();
      canv->Print("figures/fakerate_"+samples[idx_sample].first+"_"+iso[idx_iso]+"_projectionX.png");

      canv->cd();
      h_y->Draw();
      h_woTrig_y->Draw("same");
      leg1->Draw();
      canv->Print("figures/fakerate_"+samples[idx_sample].first+"_"+iso[idx_iso]+"_projectionY.png");

       TH1D* h_unrolled = new TH1D("h_unrolled_"+samples[idx_sample].first+"_"+iso[idx_iso],"unrolled distribution",nBinsRatio*nBinsJetPt,1,nBinsRatio*nBinsJetPt+1);
       TH1D* h_unrolled_woTrig = (TH1D*) h_unrolled->Clone("h_unrolled_woTrig_"+samples[idx_sample].first+"_"+iso[idx_iso]);

       int index=1;
      for(int i=1; i<=nBinsRatio; i++){
	for(int j=1; j<=nBinsJetPt; j++){
	  double a    = h_fakerate_2d_woTrig->GetBinContent(i,j);
	  double b    = h_fakerate_2d->GetBinContent(i,j);
	  double aErr = h_fakerate_2d_woTrig->GetBinError(i,j);
	  double bErr = h_fakerate_2d->GetBinError(i,j);

	  h_unrolled_woTrig -> SetBinContent(index,a);
	  h_unrolled_woTrig -> SetBinError(index,aErr);
	  h_unrolled        -> SetBinContent(index,b);
	  h_unrolled        -> SetBinError(index,bErr);

	  index += 1;
	}
      }
      canv->cd();
      canv->Clear();
      TPad * upper = new TPad("upper", "pad",0,0.29,1,1);
      upper->Draw();
      upper->cd();
      h_unrolled->GetYaxis()->SetTitle("fake rate");
      h_unrolled->GetXaxis()->SetTitle("bin number");
      h_unrolled->Draw();
      h_unrolled_woTrig->SetLineColor(kRed);
      h_unrolled_woTrig->SetMarkerColor(kRed);
      h_unrolled_woTrig->Draw("same");
      leg1->Draw("same");
      upper->SetLogy();
      upper->Draw("same");
      upper->RedrawAxis();
      upper->Modified();
      upper->Update();
      canv->cd();
      TH1D* ratio = (TH1D*) h_unrolled->Clone("ratio_"+samples[idx_sample].first+"_"+iso[idx_iso]);
      ratio->Divide(h_unrolled_woTrig);
      ratio->GetYaxis()->SetTitle("low pt/all");
      ratio->GetXaxis()->SetTitle("");
      ratio->GetYaxis()->CenterTitle();
      ratio->GetYaxis()->SetRangeUser(0,4);
      TPad * lower = new TPad("lower", "pad",0,0,1,0.29);
      lower->Draw();
      lower->cd();
      lower->SetGridy();
      ratio->SetLineColor(kBlack);
      ratio->SetMarkerColor(kBlack);
      ratio->Draw();
      lower->Modified();
      lower->RedrawAxis();
      canv->cd();
      canv->Modified();
      canv->cd();
      canv->SetSelected(canv);
      canv->Update();
      canv->Print("figures/Unrolled_fakerate_differences_" + iso[idx_iso] + ".png");

      // %%%%%%%%%%%%%%%%%%%%%%%%%  Write fake rates to root file %%%%%%%%%%%%%%%%%%%%%%%%%%%%%
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
