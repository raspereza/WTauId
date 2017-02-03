#include "HttStylesNew.cc"

void PlotFakeRate(TString iso = "TightMvaIso", bool ratioMethod = true) {

  SetStyle();

  //  float ratio[3]  = {0.76, 0.79, 0.63};
  //  float eratio[3] = {0.07, 0.08, 0.12};

  // old ->
  //  float ratio[3]  = {0.53, 0.60, 0.62};
  //  float eratio[3] = {0.05, 0.07, 0.12};

  // PAS ->
  //  float ratio[3]  = {0.58, 0.63, 0.63};
  //  float eratio[3] = {0.06, 0.08, 0.12};

  // 80X (Run2016B)
  float ratio[3]  = {0.49, 0.66, 0.43};
  float eratio[3] = {0.04, 0.09, 0.09};

  TFile * DataFileJetHT = new TFile("JetHT_Run2016_fakeRate"+iso+".root");
  TFile * DataFileSingleMu = new TFile("SingleMuon_Run2016_fakeRate"+iso+".root");

  TGraphAsymmErrors * effJetHT = (TGraphAsymmErrors*)DataFileJetHT->Get("JetHT_Run2016_fakeRate");
  effJetHT->SetMarkerStyle(22);
  effJetHT->SetMarkerColor(2);
  effJetHT->SetLineColor(2);
  effJetHT->SetLineWidth(2);
  effJetHT->SetMarkerSize(1.5);

  TGraphAsymmErrors * effSingleMu = (TGraphAsymmErrors*)DataFileSingleMu->Get("SingleMuon_Run2016_fakeRate");
  effSingleMu->SetMarkerStyle(21);
  effSingleMu->SetMarkerColor(4);
  effSingleMu->SetLineColor(4);
  effSingleMu->SetLineWidth(2);
  effSingleMu->SetMarkerSize(1.5);


  int nPoints = effJetHT->GetN();
  
  cout << nPoints << endl;
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
  leg->SetHeader(iso);
  leg->AddEntry(effSingleMu,"W#rightarrow#mu#nu+jet","lp");
  leg->AddEntry(effJetHT,"di-jets","lp");
  leg->AddEntry(graph,"combined","lp");
  leg->Draw();
  canv->Update();
  if (ratioMethod) {
    canv->Print("figures/FakeRate_"+iso+"_ratio.png");
    canv->Print("figures/FakeRate_"+iso+"_ratio.pdf","Portrait pdf");
  }
  else {
    canv->Print("figures/FakeRate_"+iso+".png");
    canv->Print("figures/FakeRate_"+iso+".pdf","Portrait pdf");
  }
}
