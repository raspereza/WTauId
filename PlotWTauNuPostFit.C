#include "HttStylesNew.cc"
#include "CMS_lumi.C"
void PlotWTauNuPostFit(TString iso="LooseIso") {

  SetStyle();
  //  gStyle->SetErrorX(0);

  TString dir = "/nfs/dust/cms/user/rasp/Run/Run2016/TauID_2016/";

  TString xtitle = "m_{T} (GeV)";
  TString ytitle = "Events / 100 GeV";

  TString inputFileName = "mttau_"+iso+"_WTauNu";
  TString mlfitFileName = "mlfit_tauId_"+iso;
  float yUpper = 2200;
  float uncert = 0.02;
  TString legHeader = iso;

  if (inputFileName.Contains("MediumIso")) {
    uncert = 0.02;
    yUpper = 1600;
  }
  else if (inputFileName.Contains("TightIso")) {
    uncert = 0.02;
    yUpper = 1200;
  }
  else if (inputFileName.Contains("LooseMvaIso")) {
    uncert = 0.02;
    yUpper = 2200;
  }
  else if (inputFileName.Contains("MediumMvaIso")) {
    uncert = 0.02;
    yUpper = 1600;
  }
  else if (inputFileName.Contains("TightMvaIso")) {
    uncert = 0.02;
    yUpper = 1200;
  }
  else if (inputFileName.Contains("VTightMvaIso")) {
    uncert = 0.08;
    yUpper = 1200;
  }

  TFile * inputs = new TFile(dir+"/datacards/"+inputFileName+".root");
  TFile * mlfit  = new TFile(dir+"/datacards/"+mlfitFileName+".root"); 

  bool logY = false;
  
  TH1F * histData = (TH1F*)inputs->Get("data_obs");
  TH1F * QCD   = (TH1F*)inputs->Get("Fakes");
  TH1F * W     = (TH1F*)inputs->Get("W");
  TH1F * Bkgd  = (TH1F*)inputs->Get("Bkgd");
  TH1F * QCDx  = (TH1F*)mlfit->Get("shapes_fit_s/ch2/Fakes");
  TH1F * Bkgdx = (TH1F*)mlfit->Get("shapes_fit_s/ch2/Bkgd");
  TH1F * Wx    = (TH1F*)mlfit->Get("shapes_fit_s/ch2/W");
  TH1F * tot   = (TH1F*)mlfit->Get("shapes_fit_s/ch2/total");

  float total  = QCDx->GetSumOfWeights()+Wx->GetSumOfWeights()+Bkgdx->GetSumOfWeights();
  float scale = histData->GetSumOfWeights()/tot->GetSumOfWeights();

  std::cout << "QCD  : " << scale*QCDx->GetSumOfWeights() << std::endl;
  std::cout << "W    : " << scale*Wx->GetSumOfWeights() << std::endl;
  std::cout << "Bkgd : " << scale*Bkgdx->GetSumOfWeights() << std::endl;
  std::cout << "SUM  : " << scale*total << std::endl;
  std::cout << "Tot  : " << scale*tot->GetSumOfWeights() << std::endl;
  std::cout << "DAT  : " << histData->GetSumOfWeights() << std::endl;

  TH1F * bkgdErr = (TH1F*)W->Clone("bkgdErr");
  bkgdErr->SetFillStyle(3013);
  bkgdErr->SetFillColor(1);
  bkgdErr->SetMarkerStyle(21);
  bkgdErr->SetMarkerSize(0);  
  
  int nBins = histData->GetNbinsX();

  for (int iB=1; iB<=nBins; ++iB) {
    float QDC_E = scale*QCDx->GetBinError(iB);
    float W_E   = scale*Wx->GetBinError(iB);

    float QCD_X  = scale*QCDx->GetBinContent(iB); 
    float W_X    = scale*Wx->GetBinContent(iB); 
    float Bkgd_X = scale*Bkgdx->GetBinContent(iB);
    float total_X = QCD_X + W_X + Bkgd_X;

    QCD->SetBinError(iB,0);
    W->SetBinError(iB,0);
    Bkgd->SetBinError(iB,0);

    float errSubtr = uncert*W_X;
    float fitErr = tot->GetBinError(iB);

    float error = TMath::Sqrt(fitErr*fitErr-errSubtr*errSubtr);
    //    float error = fitErr;

    Bkgd->SetBinContent(iB,Bkgd_X);
    QCD->SetBinContent(iB,QCD_X+Bkgd_X);
    W->SetBinContent(iB,total_X);

    bkgdErr->SetBinContent(iB,total_X);
    bkgdErr->SetBinError(iB,error);

  }
  bkgdErr->SetBinError(1,0);
  bkgdErr->SetBinError(2,0);

  InitData(histData);
  InitHist(Bkgd,"","",TColor::GetColor("#6F2D35"),1001);
  InitHist(QCD,"","",TColor::GetColor("#FFCCFF"),1001);
  InitHist(W,"","",TColor::GetColor("#FFCC66"),1001);
  histData->GetXaxis()->SetTitle(xtitle);
  histData->GetYaxis()->SetTitle(ytitle);
  histData->GetYaxis()->SetTitleOffset(1.3);
  histData->GetYaxis()->SetTitleSize(0.06);
  histData->GetYaxis()->SetRangeUser(0,yUpper);

  histData->SetMarkerSize(1.2);
  histData->GetXaxis()->SetLabelSize(0);
  histData->GetYaxis()->SetLabelSize(0.06);

  //  nData = histData->GetSum();
  //  float nMC   = TT->GetSum();
  //  float eData = TMath::Sqrt(nData);


  TCanvas * canv1 = MakeCanvas("canv1", "", 700, 800);
  TPad * upper = new TPad("upper", "pad",0,0.31,1,1);
  upper->Draw();
  upper->cd();
  upper->SetFillColor(0);
  upper->SetBorderMode(0);
  upper->SetBorderSize(10);
  upper->SetTickx(1);
  upper->SetTicky(1);
  upper->SetLeftMargin(0.17);
  upper->SetRightMargin(0.05);
  upper->SetBottomMargin(0.02);
  upper->SetFrameFillStyle(0);
  upper->SetFrameLineStyle(0);
  upper->SetFrameLineWidth(2);
  upper->SetFrameBorderMode(0);
  upper->SetFrameBorderSize(10);
  upper->SetFrameFillStyle(0);
  upper->SetFrameLineStyle(0);
  upper->SetFrameLineWidth(2);
  upper->SetFrameBorderMode(0);
  upper->SetFrameBorderSize(10);

  histData->Draw("e1");
  W->Draw("sameh");
  QCD->Draw("sameh");
  Bkgd->Draw("sameh");
  histData->Draw("e1same");
  bkgdErr->Draw("e2same");
  float chi2 = 0;
  for (int iB=1; iB<=nBins; ++iB) {
    float xData = histData->GetBinContent(iB);
    float xMC = W->GetBinContent(iB);
    if (xMC>1e-1) {
      float diff2 = (xData-xMC)*(xData-xMC);
      chi2 += diff2/xMC;
    }
  }
  std::cout << std::endl;
  std::cout << "Chi2 = " << chi2 << std::endl;
  std::cout << std::endl;

  TLegend * leg = new TLegend(0.55,0.4,0.85,0.78);
  SetLegendStyle(leg);
  leg->SetTextSize(0.047);
  leg->SetHeader(legHeader);
  leg->AddEntry(histData,"Observed","lp");
  leg->AddEntry(W,"W#rightarrow#tau#nu","f");
  leg->AddEntry(QCD,"bkgd (fake taus)","f");
  leg->AddEntry(Bkgd,"bkgd (true taus)","f");
  leg->Draw();
  writeExtraText = true;
  extraText = "Preliminary";
  CMS_lumi(upper,4,33); 
  //  plotchannel("#tau#nu");

  if (logY) upper->SetLogy(true);
    
  upper->Draw("SAME");
  upper->RedrawAxis();
  upper->Modified();
  upper->Update();
  canv1->cd();

  TH1F * ratioH = (TH1F*)histData->Clone("ratioH");
  TH1F * ratioErrH = (TH1F*)bkgdErr->Clone("ratioErrH");
  ratioH->SetMarkerColor(1);
  ratioH->SetMarkerStyle(20);
  ratioH->SetMarkerSize(1.2);
  ratioH->SetLineColor(1);
  ratioH->GetYaxis()->SetRangeUser(0.201,1.799);
  ratioH->GetYaxis()->SetNdivisions(505);
  ratioH->GetXaxis()->SetLabelFont(42);
  ratioH->GetXaxis()->SetLabelOffset(0.04);
  ratioH->GetXaxis()->SetLabelSize(0.14);
  ratioH->GetXaxis()->SetTitleSize(0.13);
  ratioH->GetXaxis()->SetTitleOffset(1.2);
  ratioH->GetYaxis()->SetTitle("Obs./Exp.");
  ratioH->GetYaxis()->SetLabelFont(42);
  ratioH->GetYaxis()->SetLabelOffset(0.015);
  ratioH->GetYaxis()->SetLabelSize(0.13);
  ratioH->GetYaxis()->SetTitleSize(0.14);
  ratioH->GetYaxis()->SetTitleOffset(0.5);
  ratioH->GetXaxis()->SetTickLength(0.07);
  ratioH->GetYaxis()->SetTickLength(0.04);
  ratioH->GetYaxis()->SetLabelOffset(0.01);

  for (int iB=1; iB<=nBins; ++iB) {
    float x1 = histData->GetBinContent(iB);
    float x2 = W->GetBinContent(iB);
    ratioErrH->SetBinContent(iB,1.0);
    ratioErrH->SetBinError(iB,0.0);
    float xBkg = bkgdErr->GetBinContent(iB);
    float errBkg = bkgdErr->GetBinError(iB);
    if (xBkg>0) {
      float relErr = errBkg/xBkg;
      ratioErrH->SetBinError(iB,relErr);

    }
    if (x1>0&&x2>0) {
      float e1 = histData->GetBinError(iB);
      float ratio = x1/x2;
      float eratio = e1/x2;
      ratioH->SetBinContent(iB,ratio);
      ratioH->SetBinError(iB,eratio);
    }
    else {
      ratioH->SetBinContent(iB,1000);
    }
  }

  // ------------>Primitives in pad: lower
  TPad * lower = new TPad("lower", "pad",0,0,1,0.30);
  lower->Draw();
  lower->cd();
  lower->SetFillColor(0);
  lower->SetBorderMode(0);
  lower->SetBorderSize(10);
  lower->SetGridy();
  lower->SetTickx(1);
  lower->SetTicky(1);
  lower->SetLeftMargin(0.17);
  lower->SetRightMargin(0.05);
  lower->SetTopMargin(0.026);
  lower->SetBottomMargin(0.35);
  lower->SetFrameFillStyle(0);
  lower->SetFrameLineStyle(0);
  lower->SetFrameLineWidth(2);
  lower->SetFrameBorderMode(0);
  lower->SetFrameBorderSize(10);
  lower->SetFrameFillStyle(0);
  lower->SetFrameLineStyle(0);
  lower->SetFrameLineWidth(2);
  lower->SetFrameBorderMode(0);
  lower->SetFrameBorderSize(10);

  ratioH->Draw("e1");
  ratioErrH->Draw("e2same");

  lower->Modified();
  lower->RedrawAxis();
  canv1->cd();
  canv1->Modified();
  canv1->cd();
  canv1->SetSelected(canv1);
  canv1->Update();
  canv1->Print("figures/"+inputFileName+"_postfit.png");
  //  canv1->Print("figures/"+inputFileName+"_postfit.pdf","Portrait pdf");
  
}
