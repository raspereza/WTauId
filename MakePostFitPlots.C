#include "HttStylesNew.cc"
#include "CMS_lumi.C"
#include "settings.h"
void MakePostFitPlots() {

  SetStyle();

  loadWorkingPoints();

  TString xtitle = "m_{T} (GeV)";
  TString ytitle = "Events";

  for(unsigned int idx_iso=0; idx_iso<iso.size(); idx_iso++){

    TString inputFileName = "mttau_"+iso[idx_iso]+"_WToTauNu_shapes";
    TString mlfitFileName = "mlfit_Combined_"+iso[idx_iso];
    TFile * inputs = new TFile("output/"+inputFileName+".root");
    if(!inputs){
      cout<<"File "<<inputFileName<<".root not available. Please Check."<<endl;
      exit(-1);      
    }
    TFile * mlfit  = new TFile("datacards/"+mlfitFileName+".root");
    if(!mlfit){
      cout<<"File "<<mlfitFileName<<".root not available. Please Check."<<endl;
      exit(-1);      
    }
    TH1F * h_Data       = (TH1F*)inputs->Get("data_obs");
    TH1F * h_FakeTaus   = (TH1F*)inputs->Get("FakeTaus");
    TH1F * h_WToTauNu   = (TH1F*)inputs->Get("W");
    TH1F * h_TrueTaus   = (TH1F*)inputs->Get("TrueTaus");
    TH1F * h_FakeTaus_x = (TH1F*)mlfit->Get("shapes_fit_s/ch2/FakeTaus");
    TH1F * h_TrueTaus_x = (TH1F*)mlfit->Get("shapes_fit_s/ch2/TrueTaus");
    TH1F * h_WToTauNu_x = (TH1F*)mlfit->Get("shapes_fit_s/ch2/W");
    TH1F * h_total_x    = (TH1F*)mlfit->Get("shapes_fit_s/ch2/total");

    float WNORM  = h_WToTauNu_x->Integral();
    float WDATA  = h_Data->Integral() - h_TrueTaus_x->Integral() - h_FakeTaus_x->Integral();
    float wscale = WDATA/WNORM;
    float total  = h_FakeTaus_x->Integral()+h_TrueTaus_x->Integral()+wscale*h_WToTauNu_x->Integral();

    cout << "h_FakeTaus : " << h_FakeTaus_x->Integral()  << endl;
    cout << "h_WToTauNu : " << wscale*h_WToTauNu_x->Integral()  << endl;
    cout << "h_TrueTaus : " << h_TrueTaus_x->Integral()  << endl;
    cout << "SUM        : " << total                   << endl;
    cout << "DAT        : " << h_Data->Integral()      << endl;
    cout << "wscale     : " << wscale                  << endl;

    TH1F * bkgdErr = (TH1F*)h_WToTauNu->Clone("bkgdErr");
    bkgdErr->SetFillStyle(3013);
    bkgdErr->SetFillColor(1);
    bkgdErr->SetMarkerStyle(21);
    bkgdErr->SetMarkerSize(0);  

    int nBins = h_Data->GetNbinsX();
    for (int iB=1; iB<=nBins; ++iB) {

      h_WToTauNu -> SetBinError(iB,0);
      h_FakeTaus -> SetBinError(iB,0);
      h_TrueTaus -> SetBinError(iB,0);

      h_WToTauNu -> SetBinContent(iB,wscale*h_WToTauNu_x->GetBinContent(iB));
      h_FakeTaus -> SetBinContent(iB,h_FakeTaus_x->GetBinContent(iB));
      h_TrueTaus -> SetBinContent(iB,h_TrueTaus_x->GetBinContent(iB));

      double tot = h_WToTauNu->GetBinContent(iB)+h_FakeTaus->GetBinContent(iB)+h_TrueTaus->GetBinContent(iB);
      double tot_err = h_total_x->GetBinError(iB);
      
      bkgdErr->SetBinContent(iB,tot);
      bkgdErr->SetBinError(iB,tot_err);

    }

    h_WToTauNu->SetFillColor(TColor::GetColor("#FFCC66"));
    h_FakeTaus->SetFillColor(TColor::GetColor("#FFCCFF"));
    h_TrueTaus->SetFillColor(TColor::GetColor("#6F2D35"));

    THStack *stack = new THStack(iso[idx_iso],"");
    stack->Add(h_TrueTaus);
    stack->Add(h_FakeTaus);
    stack->Add(h_WToTauNu);

    h_Data->GetXaxis()->SetTitle(xtitle);
    h_Data->GetYaxis()->SetTitle(ytitle);

    TCanvas * canv1 = MakeCanvas("canv1", "", 700, 800);
    TPad * upper = new TPad("upper", "pad",0,0.31,1,1);
    upper->Draw();
    upper->cd();
    h_Data  -> Draw("e1");
    stack   -> Draw("hist same");
    h_Data  -> Draw("e1 same");
    bkgdErr -> Draw("e2 same");
    
    TLegend * leg = new TLegend(0.55,0.4,0.85,0.78);
    SetLegendStyle(leg);
    leg->SetTextSize(0.047);
    leg->SetHeader(iso[idx_iso]);
    leg->AddEntry(h_Data,"Observed","lp");
    leg->AddEntry(h_WToTauNu,"W#rightarrow#tau#nu","f");
    leg->AddEntry(h_FakeTaus,"bkgd (fake taus)","f");
    leg->AddEntry(h_TrueTaus,"bkgd (true taus)","f");
    leg->Draw();
    writeExtraText = true;
    extraText = "Preliminary";
    CMS_lumi(upper,4,33); 

    upper->Draw("SAME");
    upper->RedrawAxis();
    upper->Modified();
    upper->Update();
    canv1->cd();

    TH1F * ratioH = (TH1F*)h_Data->Clone("ratioH");
    ratioH->SetMarkerColor(1);
    ratioH->SetMarkerStyle(20);
    ratioH->SetMarkerSize(1.2);
    ratioH->SetLineColor(1);
    ratioH->GetYaxis()->SetRangeUser(0.201,1.799);
    ratioH->GetYaxis()->SetNdivisions(505);
    ratioH->GetXaxis()->SetTitle("");
    ratioH->GetYaxis()->SetTitle("Obs./Exp.");
    ratioH->GetYaxis()->CenterTitle();    

    ratioH->Divide((TH1D*)stack->GetStack()->Last());
    TH1D * ratioErrH = (TH1D*)bkgdErr->Clone("ratioErrH");
    for(int i=1; i<=bkgdErr->GetNbinsX(); i++){
      ratioErrH->SetBinError(i,bkgdErr->GetBinError(i)/bkgdErr->GetBinContent(i));
      if(bkgdErr->GetBinContent(i)==0) ratioErrH->SetBinError(i,0);
      ratioErrH->SetBinContent(i,1);
    }

    // ------------>Primitives in pad: lower
    TPad * lower = new TPad("lower", "pad",0,0,1,0.30);
    lower->Draw();
    lower->cd();
    lower->SetGridy();

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
    //canv1->Print("figures/"+inputFileName+"_postfit.pdf","Portrait pdf");
  }
}
