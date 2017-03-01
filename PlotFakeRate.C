#include "HttStylesNew.cc"

void PlotFakeRate(bool ratioMethod = true) {

  SetStyle();

  std::vector<TString> iso;
  iso.push_back("VTightMvaIso");
  iso.push_back("TightMvaIso");
  iso.push_back("MediumMvaIso");
  iso.push_back("LooseMvaIso");
  iso.push_back("TightIso");
  iso.push_back("MediumIso");
  iso.push_back("LooseIso");

  // 80X (Run2016B)
  //float ratio[3]  = {0.49, 0.66, 0.43};
  //float eratio[3] = {0.04, 0.09, 0.09};

  TFile* file = new TFile("output/fraction_EWK.root","READ");
  TH1D* h_fEWK = 0;
  file->GetObject("h_fEWK", h_fEWK);
  double *ratio  = new double[h_fEWK->GetNbinsX()];
  double *eratio = new double[h_fEWK->GetNbinsX()];
  for(int i=0; i<h_fEWK->GetNbinsX(); i++){
    ratio[i]  = h_fEWK->GetBinContent(i+1); 
    eratio[i] = h_fEWK->GetBinError(i+1); 
  }

  TFile* out = new TFile("output/fakerates.root","RECREATE");
    
  for(unsigned int idx_iso=0; idx_iso<iso.size(); idx_iso++){

    cout<<endl<<"Processing "<<iso[idx_iso]<<endl;

    TFile * DataFileJetHT = new TFile("output/JetHT_Run2016_fakeRate.root");
    TFile * DataFileSingleMu = new TFile("output/SingleMuon_Run2016_fakeRate.root");
  
    TGraphAsymmErrors * effJetHT = (TGraphAsymmErrors*)DataFileJetHT->Get(iso[idx_iso]);
    effJetHT->SetMarkerStyle(22);
    effJetHT->SetMarkerColor(2);
    effJetHT->SetLineColor(2);
    effJetHT->SetLineWidth(2);
    effJetHT->SetMarkerSize(1.5);

    TGraphAsymmErrors * effSingleMu = (TGraphAsymmErrors*)DataFileSingleMu->Get(iso[idx_iso]);
    effSingleMu->SetMarkerStyle(21);
    effSingleMu->SetMarkerColor(4);
    effSingleMu->SetLineColor(4);
    effSingleMu->SetLineWidth(2);
    effSingleMu->SetMarkerSize(1.5);

    int nPoints = effJetHT->GetN();

    double x[10];
    double y[10];
    double ex[10];
    double ey[10];
    for (int i=0; i<nPoints; ++i) {
      double y1 = effJetHT->GetY()[i];
      double e1 = effJetHT->GetErrorY(i);
      double y2 = effSingleMu->GetY()[i];
      double e2 = effSingleMu->GetErrorY(i);
      double sumInvError   = 1/(e1*e1) + 1/(e2*e2);
      double sumWeightMean = y1/(e1*e1) + y2/(e2*e2);
      x[i] = effJetHT->GetX()[i];
      ex[i] = effJetHT->GetErrorX(i);;
      if (ratioMethod) {
	y[i] = (1-ratio[i])*y1 + ratio[i]*y2;   
	float err1 = (1-ratio[i])*e1;
	float err2 = ratio[i]*e2;
	float errR = (y2-y1)*eratio[i];
	ey[i] = TMath::Sqrt(err1*err1+err2*err2+errR*errR);
      }
      else {
	y[i] = sumWeightMean/sumInvError;
	double error = 1/TMath::Sqrt(sumInvError);
	float average = 0.5*(y1+y2);
	float diff = fabs(y[i]-y2);
	ey[i] = TMath::Sqrt(error*error+diff*diff);
      }
      if (ey[i]>y[i]) ey[i]=y[i];
      cout << y[i] << " +/- " << ey[i] << "( " << 100*ey[i]/y[i] << "% )" << endl;
      effJetHT->SetPointEYlow(i,e1*1.3);
      effJetHT->SetPointEYhigh(i,e1*1.3);
    }
      
    TGraphErrors * graph = new TGraphErrors(nPoints,x,y,ex,ey);
    graph->SetMarkerStyle(20);
    graph->SetMarkerColor(1);
    graph->SetLineColor(1);
    graph->SetLineWidth(3);
    graph->SetMarkerSize(1.1);

    TCanvas * canv = new TCanvas("canv","",700,600);
    TH2F * frame = new TH2F("frame","",2,99,501,2,0,0.2);
    frame->GetYaxis()->SetTitle("F^{iso}");
    frame->GetYaxis()->SetTitleOffset(1.4);
    frame->GetYaxis()->SetNdivisions(507);
    frame->GetXaxis()->SetTitle("fake tau p_{T} [GeV/c]");
    frame->Draw();
    effJetHT->Draw("epsame");
    effSingleMu->Draw("epsame");
    graph->Draw("epsame");

    TLegend * leg = new TLegend(0.7,0.7,0.95,0.92);
    leg->SetFillColor(0);
    leg->SetHeader(iso[idx_iso]);
    leg->AddEntry(effSingleMu,"W#rightarrow#mu#nu+jet","lp");
    leg->AddEntry(effJetHT,"di-jets","lp");
    leg->AddEntry(graph,"combined","lp");
    leg->Draw();
    canv->Update();
    if (ratioMethod) {
      canv->Print("figures/FakeRate_"+iso[idx_iso]+"_ratio.png");
      canv->Print("figures/FakeRate_"+iso[idx_iso]+"_ratio.pdf","Portrait pdf");
    }
    else {
      canv->Print("figures/FakeRate_"+iso[idx_iso]+".png");
      canv->Print("figures/FakeRate_"+iso[idx_iso]+".pdf","Portrait pdf");
    }
    
    out->cd();
    graph->SetName(iso[idx_iso]);
    graph->Write(iso[idx_iso]);
    delete canv;
  }// end loop over iso vector
}
