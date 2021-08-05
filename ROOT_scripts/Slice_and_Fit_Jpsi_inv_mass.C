#include <math.h> 
#include <iostream>


void Slice_and_Fit_Jpsi_inv_mass_new_version(){

  TFile *file = new TFile("pythia_for_Jpsi_fit.root");
  TH2F *hMassElecPosi_background_ALICE0 = (TH2F*)file->Get("hMassElecPosi_background_ALICE0");
  TH2F *hMassElecPosi_background_ALICE3_1 = (TH2F*)file->Get("hMassElecPosi_background_ALICE3_1");
  TH2F *hMassElecPosi_background_ALICE3_2 = (TH2F*)file->Get("hMassElecPosi_background_ALICE3_2");
  TH2F *hMassElecPosi_background_ALICE3_3 = (TH2F*)file->Get("hMassElecPosi_background_ALICE3_3");
  
  const Int_t NBINS = 19;
  const Int_t NNBINS = 38;
  
  double border_arr[NBINS + 1] = {0.,1.,2.,3.,4.,5.,6.,7.,8.,9.,10.,12.,14.,16.,18.,20.,25.,30.,35.,50.};
  double fit_arr1[NNBINS + 1] = {3.05,3.15,3.04,3.16,3.04,3.16,3.03,3.17,3.02,3.18,3.02,3.18,3.02,3.18,3.01,3.19,3.01,3.19,2.99,3.20,2.97,3.21,2.96,3.23,2.95,3.25,2.93,3.27,2.90,3.30,2.87,3.31,2.80,3.40,2.77,3.41,2.75,3.43};
  double fit_arr2[NNBINS + 1] = {2.98,3.21,2.98,3.21,2.98,3.21,2.98,3.21,2.98,3.21,2.98,3.21,2.98,3.21,2.98,3.21,2.98,3.21,2.98,3.21,2.98,3.21,2.99,3.21,2.99,3.22,2.98,3.21,2.98,3.21,2.98,3.21,2.98,3.21,2.98,3.21,2.98,3.21}; 
  double fit_arr3[NNBINS + 1] = {2.91,3.27,2.90,3.28,2.90,3.30,2.87,3.30,2.87,3.31,2.87,3.30,2.87,3.31,2.87,3.31,2.87,3.31,2.89,3.31,2.90,3.30,2.91,3.28,2.92,3.27,2.93,3.26,2.94,3.26,2.95,3.25,2.97,3.23,3.00,3.20,3.00,3.20};
  double fit_arr4[NNBINS + 1] = {2.91,3.27,2.90,3.28,2.90,3.30,2.87,3.30,2.87,3.31,2.87,3.30,2.87,3.31,2.87,3.31,2.87,3.31,2.89,3.31,2.90,3.30,2.91,3.28,2.92,3.27,2.93,3.26,2.94,3.26,2.95,3.25,2.97,3.23,3.00,3.20,3.00,3.20};
  
  TH1D *hMassJpsi_params_0 = new TH1D("hMassJpsi_params_0", "M_{J/#psi}, GeV/c^{2}", NBINS, border_arr);
  hMassJpsi_params_0->Sumw2();
  TH1D *hMassJpsi_params_1 = new TH1D("hMassJpsi_params_1", "M_{J/#psi}, GeV/c^{2}", NBINS, border_arr);
  hMassJpsi_params_1->Sumw2();
  TH1D *hMassJpsi_params_2 = new TH1D("hMassJpsi_params_2", "M_{J/#psi}, GeV/c^{2}", NBINS, border_arr);
  hMassJpsi_params_2->Sumw2();
  TH1D *hMassJpsi_params_3 = new TH1D("hMassJpsi_params_3", "M_{J/#psi}, GeV/c^{2}", NBINS, border_arr);
  hMassJpsi_params_3->Sumw2();
  
  TH1D *hSigmaJpsi_params_0 = new TH1D("hSigmaJpsi_params_0", "#sigma_{M_{J/#psi}}, GeV/c^{2}", NBINS, border_arr);
  hSigmaJpsi_params_0->Sumw2();
  
  TH1D *hSigmaJpsi_params_1 = new TH1D("hSigmaJpsi_params_1", "#sigma_{M_{J/#psi}}, GeV/c^{2}", NBINS, border_arr);
  hSigmaJpsi_params_1->Sumw2();
  
  TH1D *hSigmaJpsi_params_2 = new TH1D("hSigmaJpsi_params_2", "#sigma_{M_{J/#psi}}, GeV/c^{2}", NBINS, border_arr);
  hSigmaJpsi_params_2->Sumw2();
  
  TH1D *hSigmaJpsi_params_3 = new TH1D("hSigmaJpsi_params_3", "#sigma_{M_{J/#psi}}, GeV/c^{2}", NBINS, border_arr);
  hSigmaJpsi_params_3->Sumw2();
  
  //TF1 *Mass_fit_func = new TF1("Mass_fit_func", "[0]*x*x*x + [1]*x*x + [2]*x +[3]", 0., 50.);
  //TF1 *Sigma_fit_func = new TF1("Sigma_fit_func", "[0]*exp([1]*(x - [2])) + [3]*x +[4]", 0., 50.);
 

  TF1 *hMassJpsi_params_0_fit_f = new TF1("hMassJpsi_params_0_fit_f", "[0]*x*x*x + [1]*x*x + [2]*x +[3]", 0., 50.);   // 3.09661e+00  7.89973e-05  -3.6652e-07  1.24448e-07 // 3.48896e-02 -1.89391e-01 -4.74279e+00 2.45733e-03 5.17263e-03 [0]*exp([1]*(x - [2])) + [3]*x + [4]
  TF1 *hMassJpsi_params_1_fit_f = new TF1("hMassJpsi_params_1_fit_f", "[0]*(1 - exp([1]*(x - [2]) + [3]))", 0., 50.); // 3.09866e+00 -2.43897e-01  1.14869e+02 -3.51459e+01 // 3.29870e-02
  TF1 *hMassJpsi_params_2_fit_f = new TF1("hMassJpsi_params_2_fit_f", "[0]*(1 - exp([1]*(x - [2]) + [3]))", 0., 50.); // 3.09900e+00 -2.75641e-01 -8.30817e-01 -6.20492e+00 // 4.65884e-02 1.69952e+02 -1.25253e+01 [0]/sqrt(sqrt((x + [1]))+[2])
  TF1 *hMassJpsi_params_3_fit_f = new TF1("hMassJpsi_params_3_fit_f", "[0]*(1 - exp([1]*(x - [2]) + [3]))", 0., 50.); // 3.09810e+00 -3.39904e-01  1.05611e+02 -4.28149e+01 // 3.06009e-02 2.87757e+02 -1.68239e+01 [0]/sqrt(sqrt(sqrt((x + [1]))+[2]))

 
  TH1D *hMass0[NBINS];
  TH1D *hMass1[NBINS];
  TH1D *hMass2[NBINS];
  TH1D *hMass3[NBINS];
  
  TCanvas *c1 = new TCanvas("c1","c1");
  c1->Divide(6,4);
  for (Int_t iPt=0; iPt<NBINS; iPt++) {
    Int_t ptMin, ptMax;
    ptMin = hMassElecPosi_background_ALICE0->GetYaxis()->FindBin(border_arr[iPt]+0.01);
    ptMax = hMassElecPosi_background_ALICE0->GetYaxis()->FindBin(border_arr[iPt+1]-0.01);
    TString name = Form("ALICE0_Jpsi_inv_mass_with_p_T_%02d",iPt);
    TString title = Form("%.0f < p_T < %.0f",border_arr[iPt],border_arr[iPt+1]);
    hMass0[iPt] = hMassElecPosi_background_ALICE0->ProjectionX(name,ptMin,ptMax);
    hMass0[iPt]->SetTitle(title);
    //if (iPt > 20) hMass[iPt]->Rebin(2);
    //if (iPt == NBINS - 3) hMass0[iPt]->Rebin(2);
    if (iPt == NBINS - 2) hMass0[iPt]->Rebin(4);
    if (iPt == NBINS - 1) hMass0[iPt]->Rebin(4);
    c1->cd(iPt+1);
    hMass0[iPt]->Fit("gaus","","",fit_arr1[2*iPt],fit_arr1[2*iPt + 1]);
    gStyle->SetOptFit(111);
    Double_t mMean = hMass0[iPt]->GetFunction("gaus")->GetParameter(1);
    Double_t sigma = hMass0[iPt]->GetFunction("gaus")->GetParameter(2);
    Double_t mError = hMass0[iPt]->GetFunction("gaus")->GetParError(1);
    Double_t sError = hMass0[iPt]->GetFunction("gaus")->GetParError(2);
    hMassJpsi_params_0->SetBinContent(iPt+1,mMean);
    hMassJpsi_params_0->SetBinError  (iPt+1,mError);
    hSigmaJpsi_params_0->SetBinContent(iPt+1,sigma);
    hSigmaJpsi_params_0->SetBinError  (iPt+1,sError);
  }
  
  
  c1->cd(NBINS + 1);
  hMassJpsi_params_0->Draw();
  hMassJpsi_params_3->Fit("hMassJpsi_params_0_fit_f", "","", 0., 50.);

  
  
  c1->cd(NBINS + 2);
  hSigmaJpsi_params_0->Draw();;
  
  TCanvas *c2 = new TCanvas("c2","c2");
  c2->Divide(6,4);
  for (Int_t iPt=0; iPt<NBINS; iPt++) {
    Int_t ptMin, ptMax;
    ptMin = hMassElecPosi_background_ALICE3_1->GetYaxis()->FindBin(border_arr[iPt]+0.01);
    ptMax = hMassElecPosi_background_ALICE3_1->GetYaxis()->FindBin(border_arr[iPt+1]-0.01);
    TString name = Form("ALICE3_1_Jpsi_inv_mass_with_p_T_%02d",iPt);
    TString title = Form("%.0f < p_T < %.0f",border_arr[iPt],border_arr[iPt+1]);
    hMass1[iPt] = hMassElecPosi_background_ALICE3_1->ProjectionX(name,ptMin,ptMax);
    hMass1[iPt]->SetTitle(title);
    //if (iPt > 20) hMass[iPt]->Rebin(2);
    if (iPt == NBINS - 2) hMass1[iPt]->Rebin(2);
    if (iPt == NBINS - 1) hMass1[iPt]->Rebin(4);
    c2->cd(iPt+1);
    hMass1[iPt]->Fit("gaus","","",fit_arr2[2*iPt],fit_arr2[2*iPt + 1]);
    gStyle->SetOptFit(111);
    Double_t mMean = hMass1[iPt]->GetFunction("gaus")->GetParameter(1);
    Double_t sigma = hMass1[iPt]->GetFunction("gaus")->GetParameter(2);
    Double_t mError = hMass1[iPt]->GetFunction("gaus")->GetParError(1);
    Double_t sError = hMass1[iPt]->GetFunction("gaus")->GetParError(2);
    hMassJpsi_params_1->SetBinContent(iPt+1,mMean);
    hMassJpsi_params_1->SetBinError  (iPt+1,mError);
    hSigmaJpsi_params_1->SetBinContent(iPt+1,sigma);
    hSigmaJpsi_params_1->SetBinError  (iPt+1,sError);
  }
  
  
  c2->cd(NBINS + 1);
  hMassJpsi_params_1->Draw();
  
  
  c2->cd(NBINS + 2);
  hSigmaJpsi_params_1->Draw();
  
  TCanvas *c3 = new TCanvas("c3","c3");
  c3->Divide(6,4);
  for (Int_t iPt=0; iPt<NBINS; iPt++) {
    Int_t ptMin, ptMax;
    ptMin = hMassElecPosi_background_ALICE3_2->GetYaxis()->FindBin(border_arr[iPt]+0.01);
    ptMax = hMassElecPosi_background_ALICE3_2->GetYaxis()->FindBin(border_arr[iPt+1]-0.01);
    TString name = Form("ALICE3_2_Jpsi_inv_mass_with_p_T_%02d",iPt);
    TString title = Form("%.0f < p_T < %.0f",border_arr[iPt],border_arr[iPt+1]);
    hMass2[iPt] = hMassElecPosi_background_ALICE3_2->ProjectionX(name,ptMin,ptMax);
    hMass2[iPt]->SetTitle(title);
    //if (iPt > 20) hMass[iPt]->Rebin(2);
    if (iPt == NBINS - 2) hMass2[iPt]->Rebin(2);
    if (iPt == NBINS - 1) hMass2[iPt]->Rebin(4);
    c3->cd(iPt+1);
    hMass2[iPt]->Fit("gaus","","",fit_arr3[2*iPt],fit_arr3[2*iPt + 1]);
    gStyle->SetOptFit(111);
    Double_t mMean = hMass2[iPt]->GetFunction("gaus")->GetParameter(1);
    Double_t sigma = hMass2[iPt]->GetFunction("gaus")->GetParameter(2);
    Double_t mError = hMass2[iPt]->GetFunction("gaus")->GetParError(1);
    Double_t sError = hMass2[iPt]->GetFunction("gaus")->GetParError(2);
    hMassJpsi_params_2->SetBinContent(iPt+1,mMean);
    hMassJpsi_params_2->SetBinError  (iPt+1,mError);
    hSigmaJpsi_params_2->SetBinContent(iPt+1,sigma);
    hSigmaJpsi_params_2->SetBinError  (iPt+1,sError);
  }
  
  
  c3->cd(NBINS + 1);
  hMassJpsi_params_2->Draw();
  
  
  c3->cd(NBINS + 2);
  hSigmaJpsi_params_2->Draw();
  
  TCanvas *c4 = new TCanvas("c4","c4");
  c4->Divide(6,4);
  for (Int_t iPt=0; iPt<NBINS; iPt++) {
    Int_t ptMin, ptMax;
    ptMin = hMassElecPosi_background_ALICE3_3->GetYaxis()->FindBin(border_arr[iPt]+0.01);
    ptMax = hMassElecPosi_background_ALICE3_3->GetYaxis()->FindBin(border_arr[iPt+1]-0.01);
    TString name = Form("ALICE3_3_Jpsi_inv_mass_with_p_T_%02d",iPt);
    TString title = Form("%.0f < p_T < %.0f",border_arr[iPt],border_arr[iPt+1]);
    hMass3[iPt] = hMassElecPosi_background_ALICE3_3->ProjectionX(name,ptMin,ptMax);
    hMass3[iPt]->SetTitle(title);
    //if (iPt > 20) hMass[iPt]->Rebin(2);
    if (iPt == NBINS - 2) hMass3[iPt]->Rebin(2);
    if (iPt == NBINS - 1) hMass3[iPt]->Rebin(2);
    c4->cd(iPt+1);
    hMass3[iPt]->Fit("gaus","","",fit_arr4[2*iPt],fit_arr4[2*iPt + 1]);
    gStyle->SetOptFit(111);
    Double_t mMean = hMass3[iPt]->GetFunction("gaus")->GetParameter(1);
    Double_t sigma = hMass3[iPt]->GetFunction("gaus")->GetParameter(2);
    Double_t mError = hMass3[iPt]->GetFunction("gaus")->GetParError(1);
    Double_t sError = hMass3[iPt]->GetFunction("gaus")->GetParError(2);
    hMassJpsi_params_3->SetBinContent(iPt+1,mMean);
    hMassJpsi_params_3->SetBinError  (iPt+1,mError);
    hSigmaJpsi_params_3->SetBinContent(iPt+1,sigma);
    hSigmaJpsi_params_3->SetBinError  (iPt+1,sError);
  }
  
  
  c4->cd(NBINS + 1);
  hMassJpsi_params_3->Draw();
  
  
  c4->cd(NBINS + 2);
  hSigmaJpsi_params_3->Draw();
  
  

  
  TFile *outFile = new TFile("Jpsi_decays_data_from_pythia_with_diff_par.root", "RECREATE");
  
  for(int i = 0; i < NBINS; i++){
    hMass0[i]->Write();
  }
  for(int i = 0; i < NBINS; i++){
    hMass1[i]->Write();
  }
  for(int i = 0; i < NBINS; i++){
    hMass2[i]->Write();
  }
  for(int i = 0; i < NBINS; i++){
    hMass3[i]->Write();
  }


	
  hMassJpsi_params_0 ->Write();
  hSigmaJpsi_params_0->Write();
  hMassJpsi_params_1 ->Write();
  hSigmaJpsi_params_1->Write();
  hMassJpsi_params_2 ->Write();
  hSigmaJpsi_params_2->Write();
  hMassJpsi_params_3 ->Write();
  hSigmaJpsi_params_3->Write();
  
  outFile->Close();

  c1->Print("ALICE0.pdf");
  c2->Print("ALICE3_1.pdf");
  c3->Print("ALICE3_2.pdf");
  c4->Print("ALICE3_3.pdf");


  return;
}
