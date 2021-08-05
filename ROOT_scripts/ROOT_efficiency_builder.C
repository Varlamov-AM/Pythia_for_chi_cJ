#include <math.h> 
#include <iostream>

Double_t Gaus3Sum_with_pol2(Double_t *, Double_t *);
Double_t Gaus3Sum(Double_t *, Double_t *);
Double_t Gaus(Double_t *, Double_t *);

void ROOT_efficiency_builder(){

  
  //Open target input ROOT file
  
  TFile *file = new TFile("Pythia_for_charmonium_new_version.root");
  

  //Input histograms
  //cand delta mass:
  TH2F *hDeltaMass_cand_c0 = 
    (TH2F*)file->Get("hMassElecPosiGam_diff_ElecPosi_ALICE0_c0_from_backg");
  TH2F *hDeltaMass_cand_c1 = 
    (TH2F*)file->Get("hMassElecPosiGam_diff_ElecPosi_ALICE0_c1_from_backg");
  TH2F *hDeltaMass_cand_c2 = 
    (TH2F*)file->Get("hMassElecPosiGam_diff_ElecPosi_ALICE0_c2_from_backg");
  TH2F *hDeltaMass_cand_p1 = 
    (TH2F*)file->Get("hMassElecPosiGam_diff_ElecPosi_ALICE3_p1_from_backg");
  TH2F *hDeltaMass_cand_p2 = 
    (TH2F*)file->Get("hMassElecPosiGam_diff_ElecPosi_ALICE3_p2_from_backg");
  TH2F *hDeltaMass_cand_p3 = 
    (TH2F*)file->Get("hMassElecPosiGam_diff_ElecPosi_ALICE3_p3_from_backg");

  //true charm delta mass
  TH2F *hDeltaMass_true_c0 = 
    (TH2F*)file->Get("hMassElecPosiGam_diff_ElecPosi_ALICE0_c0_from_chi_c");
  TH2F *hDeltaMass_true_c1 = 
    (TH2F*)file->Get("hMassElecPosiGam_diff_ElecPosi_ALICE0_c1_from_chi_c");
  TH2F *hDeltaMass_true_c2 = 
    (TH2F*)file->Get("hMassElecPosiGam_diff_ElecPosi_ALICE0_c2_from_chi_c");
  TH2F *hDeltaMass_true_p1 = 
    (TH2F*)file->Get("hMassElecPosiGam_diff_ElecPosi_ALICE3_p1_from_chi_c");
  TH2F *hDeltaMass_true_p2 = 
    (TH2F*)file->Get("hMassElecPosiGam_diff_ElecPosi_ALICE3_p2_from_chi_c");
  TH2F *hDeltaMass_true_p3 = 
    (TH2F*)file->Get("hMassElecPosiGam_diff_ElecPosi_ALICE3_p3_from_chi_c");
  
  //Jpsi_cand_pt_y
  TH2F *hJpsi_from_cand_cndtn1 = (TH2F*)file->Get("hJpsi_from_cand_ALICE0_c0");
  TH2F *hJpsi_from_cand_cndtn2 = (TH2F*)file->Get("hJpsi_from_cand_ALICE0_c1");
  TH2F *hJpsi_from_cand_cndtn3 = (TH2F*)file->Get("hJpsi_from_cand_ALICE0_c2");
  TH2F *hJpsi_from_cand_cndtn4 = (TH2F*)file->Get("hJpsi_from_cand_ALICE3_p1");

  //Jpsi_cand_mass_pt
  TH2F *hMassElecPosi_from_Jpsi_ALICE0_c0_from_cand = 
    (TH2F*)file->Get("hMassElecPosi_from_cand_ALICE0_c0_from_cand");
  TH2F *hMassElecPosi_from_Jpsi_ALICE0_c1_from_cand = 
    (TH2F*)file->Get("hMassElecPosi_from_cand_ALICE0_c1_from_cand");
  TH2F *hMassElecPosi_from_Jpsi_ALICE0_c2_from_cand = 
    (TH2F*)file->Get("hMassElecPosi_from_cand_ALICE0_c2_from_cand");
  TH2F *hMassElecPosi_from_Jpsi_ALICE3_p1_from_cand = 
    (TH2F*)file->Get("hMassElecPosi_from_cand_ALICE3_p1_from_cand");

  //Jpsi_true
  TH2F *hMassElecPosi_from_Jpsi_ALICE0_c0_from_chic = 
    (TH2F*)file->Get("hMassElecPosi_from_Jpsi_ALICE0_c0_from_chic");
  TH2F *hMassElecPosi_from_Jpsi_ALICE0_c1_from_chic = 
    (TH2F*)file->Get("hMassElecPosi_from_Jpsi_ALICE0_c1_from_chic");
  TH2F *hMassElecPosi_from_Jpsi_ALICE0_c2_from_chic = 
    (TH2F*)file->Get("hMassElecPosi_from_Jpsi_ALICE0_c2_from_chic");
  TH2F *hMassElecPosi_from_Jpsi_ALICE3_p1_from_chic = 
    (TH2F*)file->Get("hMassElecPosi_from_Jpsi_ALICE3_p1_from_chic");
  
  //Create arrays of histograms
  //hists for Jpsi eficiency
  
  TH1D *Jpsi_cand_cndtn1;
  TH1D *Jpsi_cand_cndtn2;
  TH1D *Jpsi_cand_cndtn3;
  TH1D *Jpsi_cand_cndtn4;
  
  TH1D *Jpsi_chic_cndtn1;
  TH1D *Jpsi_chic_cndtn2;
  TH1D *Jpsi_chic_cndtn3;
  TH1D *Jpsi_chic_cndtn4;
  
  //hists for chic efficiency

  TH1D *hMassElecPosiGam_diff_ElecPosi_ALICE0_c0_from_backg;
  TH1D *hMassElecPosiGam_diff_ElecPosi_ALICE0_c1_from_backg;
  TH1D *hMassElecPosiGam_diff_ElecPosi_ALICE0_c2_from_backg;
  TH1D *hMassElecPosiGam_diff_ElecPosi_ALICE0_p1_from_backg;
  TH1D *hMassElecPosiGam_diff_ElecPosi_ALICE0_p2_from_backg;
  TH1D *hMassElecPosiGam_diff_ElecPosi_ALICE0_p3_from_backg;

  TH1D *hMassElecPosiGam_diff_ElecPosi_ALICE0_c0_from_chi_c;
  TH1D *hMassElecPosiGam_diff_ElecPosi_ALICE0_c1_from_chi_c;
  TH1D *hMassElecPosiGam_diff_ElecPosi_ALICE0_c2_from_chi_c;
  TH1D *hMassElecPosiGam_diff_ElecPosi_ALICE0_p1_from_chi_c;
  TH1D *hMassElecPosiGam_diff_ElecPosi_ALICE0_p2_from_chi_c;
  TH1D *hMassElecPosiGam_diff_ElecPosi_ALICE0_p3_from_chi_c;
  
  //Describe arrays of histograms 
  
  
  TString title_1 = Form("Jpsi_cand_c1_eta");
  TString title_2 = Form("Jpsi_cand_c2_eta");
  TString title_3 = Form("Jpsi_cand_c3_eta");
  TString title_4 = Form("Jpsi_cand_c4_eta");
  
  Jpsi_cand_cndtn1_al = hJpsi_from_cand_cndtn1->ProjectionX(title_1);
  Jpsi_cand_cndtn2_al = hJpsi_from_cand_cndtn2->ProjectionX(title_2);
  Jpsi_cand_cndtn3_al = hJpsi_from_cand_cndtn3->ProjectionX(title_3);
  Jpsi_cand_cndtn4_al = hJpsi_from_cand_cndtn4->ProjectionX(title_4);
  
  TString title_5 = Form("Jpsi_true_c1");
  TString title_6 = Form("Jpsi_true_c2");
  TString title_7 = Form("Jpsi_true_c3");
  TString title_8 = Form("Jpsi_true_c4");
    
  Jpsi_chic_cndtn1 = 
    hMassElecPosi_from_Jpsi_ALICE0_c0_from_chic->ProjectionY(title_5);
  Jpsi_chic_cndtn2 =  
    hMassElecPosi_from_Jpsi_ALICE0_c1_from_chic->ProjectionY(title_6);
  Jpsi_chic_cndtn3 =  
    hMassElecPosi_from_Jpsi_ALICE0_c2_from_chic->ProjectionY(title_7);
  Jpsi_chic_cndtn4 =  
    hMassElecPosi_from_Jpsi_ALICE3_p1_from_chic->ProjectionY(title_8);

  TString title_9  = Form("Jpsi_cand_c1_m");
  TString title_10 = Form("Jpsi_cand_c2_m");
  TString title_11 = Form("Jpsi_cand_c3_m");
  TString title_12 = Form("Jpsi_cand_c4_m");
    
  Jpsi_cand_cndtn1 = 
    hMassElecPosi_from_cand_ALICE0_c0_from_cand->ProjectionY(title_9);
  Jpsi_cand_cndtn2 =  
    hMassElecPosi_from_cand_ALICE0_c1_from_cand->ProjectionY(title_10);
  Jpsi_cand_cndtn3 =  
    hMassElecPosi_from_cand_ALICE0_c2_from_cand->ProjectionY(title_11);
  Jpsi_cand_cndtn4 =  
    hMassElecPosi_from_cand_ALICE3_p1_from_cand->ProjectionY(title_12);
  
  Jpsi_cand_cndtn1_al->Rebin(5);
  Jpsi_cand_cndtn2_al->Rebin(5);
  Jpsi_cand_cndtn3_al->Rebin(5);
  Jpsi_cand_cndtn4_al->Rebin(5);
  
  Jpsi_cand_cndtn1_al->SetLineColor(kBlue);
  Jpsi_cand_cndtn2_al->SetLineColor(kBlue);
  Jpsi_cand_cndtn3_al->SetLineColor(kBlue);
  Jpsi_cand_cndtn4_al->SetLineColor(kBlue);

  Jpsi_chic_cndtn1->SetLineColor(kRed);
  Jpsi_chic_cndtn2->SetLineColor(kRed);
  Jpsi_chic_cndtn3->SetLineColor(kRed);
  Jpsi_chic_cndtn4->SetLineColor(kRed);
  
  Jpsi_cand_cndtn1->SetLineColor(kBlue);
  Jpsi_cand_cndtn2->SetLineColor(kBlue);
  Jpsi_cand_cndtn3->SetLineColor(kBlue);
  Jpsi_cand_cndtn4->SetLineColor(kBlue);


  //hist for charmonium efficiency
  TH1D* hDeltaMass_true_all_pt[6];

  hDeltaMass_true_all_pt[0] = hDeltaMass_true_c0->ProjectionX();
  hDeltaMass_true_all_pt[1] = hDeltaMass_true_c1->ProjectionX();
  hDeltaMass_true_all_pt[2] = hDeltaMass_true_c2->ProjectionX();
  hDeltaMass_true_all_pt[3] = hDeltaMass_true_p1->ProjectionX();
  hDeltaMass_true_all_pt[4] = hDeltaMass_true_p2->ProjectionX();
  hDeltaMass_true_all_pt[5] = hDeltaMass_true_p3->ProjectionX();


  TH1D* hDeltaMass_back_all_pt[6];
  TH1D* hBackground[6];
  

  hDeltaMass_back_all_pt[0] = hDeltaMass_cand_c0->ProjectionX();
  hDeltaMass_back_all_pt[1] = hDeltaMass_cand_c1->ProjectionX();
  hDeltaMass_back_all_pt[2] = hDeltaMass_cand_c2->ProjectionX();
  hDeltaMass_back_all_pt[3] = hDeltaMass_cand_p1->ProjectionX();
  hDeltaMass_back_all_pt[4] = hDeltaMass_cand_p2->ProjectionX();
  hDeltaMass_back_all_pt[5] = hDeltaMass_cand_p3->ProjectionX();

  TH1D* chic_witout_back[6];
  chic_witout_back[0] = (TH1D*)hDeltaMass_back_all_pt[0]->Clone();
  chic_witout_back[1] = (TH1D*)hDeltaMass_back_all_pt[1]->Clone();
  chic_witout_back[2] = (TH1D*)hDeltaMass_back_all_pt[2]->Clone();
  chic_witout_back[3] = (TH1D*)hDeltaMass_back_all_pt[3]->Clone();
  chic_witout_back[4] = (TH1D*)hDeltaMass_back_all_pt[4]->Clone();
  chic_witout_back[5] = (TH1D*)hDeltaMass_back_all_pt[5]->Clone();

  //Draw Jpsi data

  TCanvas *c1 = new TCanvas("c1", "Jpsi true and candidates");
  c1->Divide(2, 2);
  
  c1->cd(1);
  Jpsi_cand_cndtn1->SetTitle("dN_{J/#psi}/dp_{T}, cndtn_1");
  Jpsi_cand_cndtn1->Draw();
  Jpsi_chic_cndtn1->Draw("same");
  gPad->SetLogy();
  gStyle->SetOptStat(0);
  TLegend *legend_1 = new TLegend(0.6,0.6,0.85,0.85);
  legend_1->SetBorderSize(0);
  legend_1->AddEntry(Jpsi_cand_cndtn1,"cand J/#psi","lp");
  legend_1->AddEntry(Jpsi_chic_cndtn1,"true J/#psi","lp");
  legend_1->Draw();
   
  c1->cd(2);
  Jpsi_cand_cndtn2->SetTitle("dN_{J/#psi}/dp_{T}, cndtn_2");
  Jpsi_cand_cndtn2->Draw();
  Jpsi_chic_cndtn2->Draw("same");
  gPad->SetLogy();
  gStyle->SetOptStat(0);
  TLegend *legend_2 = new TLegend(0.6,0.6,0.85,0.85);
  legend_2->SetBorderSize(0);
  legend_2->AddEntry(Jpsi_cand_cndtn2,"cand J/#psi","lp");
  legend_2->AddEntry(Jpsi_chic_cndtn2,"true J/#psi","lp");
  legend_2->Draw();
 
  c1->cd(3);
  Jpsi_cand_cndtn3->SetTitle("dN_{J/#psi}/dp_{T}, cndtn_3");
  Jpsi_cand_cndtn3->Draw();
  Jpsi_chic_cndtn3->Draw("same");
  gPad->SetLogy();
  gStyle->SetOptStat(0);
  TLegend *legend_3 = new TLegend(0.6,0.6,0.85,0.85);
  legend_3->SetBorderSize(0);
  legend_3->AddEntry(Jpsi_cand_cndtn3,"cand J/#psi","lp");
  legend_3->AddEntry(Jpsi_chic_cndtn3,"true J/#psi","lp");
  legend_3->Draw();

  c1->cd(4);
  Jpsi_cand_cndtn4->SetTitle("dN_{J/#psi}/dp_{T}, cndtn_4");
  Jpsi_cand_cndtn4->Draw();
  Jpsi_chic_cndtn4->Draw("same");
  gPad->SetLogy();
  gStyle->SetOptStat(0);
  TLegend *legend_4 = new TLegend(0.6,0.6,0.85,0.85);
  legend_4->SetBorderSize(0);
  legend_4->AddEntry(Jpsi_cand_cndtn4,"cand J/#psi","lp");
  legend_4->AddEntry(Jpsi_chic_cndtn4,"true J/#psi","lp");
  legend_4->Draw();
  
  c1->Print("Jpsi_true_and_candidates.pdf");

  //Find Jpsi efficiency
  
  TH1D* Jpsi_efficiency_c1 = (TH1D*)Jpsi_cand_cndtn1->Clone();
  TH1D* Jpsi_efficiency_c2 = (TH1D*)Jpsi_cand_cndtn2->Clone();
  TH1D* Jpsi_efficiency_c3 = (TH1D*)Jpsi_cand_cndtn3->Clone();
  TH1D* Jpsi_efficiency_c4 = (TH1D*)Jpsi_cand_cndtn4->Clone();
  
  Jpsi_efficiency_c1->Divide(Jpsi_chic_cndtn1);
  Jpsi_efficiency_c2->Divide(Jpsi_chic_cndtn2);
  Jpsi_efficiency_c3->Divide(Jpsi_chic_cndtn3);
  Jpsi_efficiency_c4->Divide(Jpsi_chic_cndtn4);
  

  TCanvas *c2 = new TCanvas("c2", "J/psi efficiency");
  c2->Divide(2, 2);
  
  c2->cd(1);
  Jpsi_efficiency_c1->SetTitle("N_{cand J/#psi}/N_{true J/#psi}, cndtn_1");
  Jpsi_efficiency_c1->Draw();
   
  c2->cd(2);
  Jpsi_efficiency_c2->SetTitle("N_{cand J/#psi}/N_{true J/#psi}, cndtn_2");
  Jpsi_efficiency_c2->Draw();
 
  c2->cd(3);
  Jpsi_efficiency_c3->SetTitle("N_{cand J/#psi}/N_{true J/#psi}, cndtn_3");
  Jpsi_efficiency_c3->Draw();

  c2->cd(4);
  Jpsi_efficiency_c4->SetTitle("N_{cand J/#psi}/N_{true J/#psi}, cndtn_4");
  Jpsi_efficiency_c4->Draw();

  c2->Print("Jpsi_efficiency.pdf");

  TCanvas *c11 = new TCanvas("c11", "Jpsi true and candidates_alternative");
  c11->Divide(2, 2);
  
  c11->cd(1);
  Jpsi_cand_cndtn1_al->SetTitle("dN_{J/#psi}/dp_{T}, cndtn_1");
  Jpsi_cand_cndtn1_al->Draw();
  Jpsi_chic_cndtn1->Draw("same");
  gPad->SetLogy();
  gStyle->SetOptStat(0);
  TLegend *legend_1 = new TLegend(0.6,0.6,0.85,0.85);
  legend_1->SetBorderSize(0);
  legend_1->AddEntry(Jpsi_cand_cndtn1_al,"cand J/#psi","lp");
  legend_1->AddEntry(Jpsi_chic_cndtn1,"true J/#psi","lp");
  legend_1->Draw();
   
  c11->cd(2);
  Jpsi_cand_cndtn2_al->SetTitle("dN_{J/#psi}/dp_{T}, cndtn_2");
  Jpsi_cand_cndtn2_al->Draw();
  Jpsi_chic_cndtn2->Draw("same");
  gPad->SetLogy();
  gStyle->SetOptStat(0);
  TLegend *legend_2 = new TLegend(0.6,0.6,0.85,0.85);
  legend_2->SetBorderSize(0);
  legend_2->AddEntry(Jpsi_cand_cndtn2_al,"cand J/#psi","lp");
  legend_2->AddEntry(Jpsi_chic_cndtn2,"true J/#psi","lp");
  legend_2->Draw();
 
  c11->cd(3);
  Jpsi_cand_cndtn3_al->SetTitle("dN_{J/#psi}/dp_{T}, cndtn_3");
  Jpsi_cand_cndtn3_al->Draw();
  Jpsi_chic_cndtn3->Draw("same");
  gPad->SetLogy();
  gStyle->SetOptStat(0);
  TLegend *legend_3 = new TLegend(0.6,0.6,0.85,0.85);
  legend_3->SetBorderSize(0);
  legend_3->AddEntry(Jpsi_cand_cndtn3_al,"cand J/#psi","lp");
  legend_3->AddEntry(Jpsi_chic_cndtn3,"true J/#psi","lp");
  legend_3->Draw();

  c11->cd(4);
  Jpsi_cand_cndtn4_al->SetTitle("dN_{J/#psi}/dp_{T}, cndtn_4");
  Jpsi_cand_cndtn4_al->Draw();
  Jpsi_chic_cndtn4->Draw("same");
  gPad->SetLogy();
  gStyle->SetOptStat(0);
  TLegend *legend_4 = new TLegend(0.6,0.6,0.85,0.85);
  legend_4->SetBorderSize(0);
  legend_4->AddEntry(Jpsi_cand_cndtn4_al,"cand J/#psi","lp");
  legend_4->AddEntry(Jpsi_chic_cndtn4,"true J/#psi","lp");
  legend_4->Draw();
  
  c11->Print("Jpsi_true_and_candidates_alternative.pdf");

  //Find Jpsi efficiency
  
  TH1D* Jpsi_efficiency_c1_al = (TH1D*)Jpsi_cand_cndtn1_al->Clone();
  TH1D* Jpsi_efficiency_c2_al = (TH1D*)Jpsi_cand_cndtn2_al->Clone();
  TH1D* Jpsi_efficiency_c3_al = (TH1D*)Jpsi_cand_cndtn3_al->Clone();
  TH1D* Jpsi_efficiency_c4_al = (TH1D*)Jpsi_cand_cndtn4_al->Clone();
  
  Jpsi_efficiency_c1_al->Divide(Jpsi_chic_cndtn1);
  Jpsi_efficiency_c2_al->Divide(Jpsi_chic_cndtn2);
  Jpsi_efficiency_c3_al->Divide(Jpsi_chic_cndtn3);
  Jpsi_efficiency_c4_al->Divide(Jpsi_chic_cndtn4);
  

  TCanvas *c22 = new TCanvas("c22", "J/psi efficiency_alternative");
  c22->Divide(2, 2);
  
  c22->cd(1);
  Jpsi_efficiency_c1_al->SetTitle("N_{cand J/#psi}/N_{true J/#psi}, cndtn_1");
  Jpsi_efficiency_c1_al->Draw();
   
  c22->cd(2);
  Jpsi_efficiency_c2_al->SetTitle("N_{cand J/#psi}/N_{true J/#psi}, cndtn_2");
  Jpsi_efficiency_c2_al->Draw();
 
  c22->cd(3);
  Jpsi_efficiency_c3_al->SetTitle("N_{cand J/#psi}/N_{true J/#psi}, cndtn_3");
  Jpsi_efficiency_c3_al->Draw();

  c22->cd(4);
  Jpsi_efficiency_c4_al->SetTitle("N_{cand J/#psi}/N_{true J/#psi}, cndtn_4");
  Jpsi_efficiency_c4_al->Draw();

  c22->Print("Jpsi_efficienc_alternative.pdf");

  //Find charmonium efficiency

  //Create true charm all pt pic with fit

  TF1 *fGaus3Sum[6];
  TH1D* hDeltaMass_true_all_pt[6];
  TString  title_all_pt[6];
  Double_t sigma_c0_low_boarder[6];
  Double_t sigma_c0_up_boarder[6];
  Double_t sigma_c1_low_boarder[6];
  Double_t sigma_c1_up_boarder[6];
  Double_t sigma_c2_low_boarder[6];
  Double_t sigma_c2_up_boarder[6];

  sigma_c0_low_boarder[0] = 0.012;
  sigma_c0_low_boarder[1] = 0.012;
  sigma_c0_low_boarder[2] = 0.012;
  sigma_c0_low_boarder[3] = 0.012;
  sigma_c0_low_boarder[4] = 0.012;
  sigma_c0_low_boarder[5] = 0.001;

  sigma_c0_up_boarder[0] = 0.020;
  sigma_c0_up_boarder[1] = 0.020;
  sigma_c0_up_boarder[2] = 0.020;
  sigma_c0_up_boarder[3] = 0.025;
  sigma_c0_up_boarder[4] = 0.020;
  sigma_c0_up_boarder[5] = 0.015;

  sigma_c1_low_boarder[0] = 0.010;
  sigma_c1_low_boarder[1] = 0.010;
  sigma_c1_low_boarder[2] = 0.010;
  sigma_c1_low_boarder[3] = 0.010;
  sigma_c1_low_boarder[4] = 0.010;
  sigma_c1_low_boarder[5] = 0.001;

  sigma_c1_up_boarder[0] = 0.020;
  sigma_c1_up_boarder[1] = 0.020;
  sigma_c1_up_boarder[2] = 0.020;
  sigma_c1_up_boarder[3] = 0.018;
  sigma_c1_up_boarder[4] = 0.018;
  sigma_c1_up_boarder[5] = 0.010;

  sigma_c2_low_boarder[0] = 0.010;
  sigma_c2_low_boarder[1] = 0.010;
  sigma_c2_low_boarder[2] = 0.010;
  sigma_c2_low_boarder[3] = 0.010;
  sigma_c2_low_boarder[4] = 0.010;
  sigma_c2_low_boarder[5] = 0.001;

  sigma_c2_up_boarder[0] = 0.020;
  sigma_c2_up_boarder[1] = 0.020;
  sigma_c2_up_boarder[2] = 0.020;
  sigma_c2_up_boarder[3] = 0.019;
  sigma_c2_up_boarder[4] = 0.019;
  sigma_c2_up_boarder[5] = 0.010;
  

  hDeltaMass_true_all_pt[0] = hDeltaMass_true_c0->ProjectionX();
  hDeltaMass_true_all_pt[1] = hDeltaMass_true_c1->ProjectionX();
  hDeltaMass_true_all_pt[2] = hDeltaMass_true_c2->ProjectionX();
  hDeltaMass_true_all_pt[3] = hDeltaMass_true_p1->ProjectionX();
  hDeltaMass_true_all_pt[4] = hDeltaMass_true_p2->ProjectionX();
  hDeltaMass_true_all_pt[5] = hDeltaMass_true_p3->ProjectionX();


  for (int i = 0; i < 6; i++){
    if (i < 3){
      title_all_pt[i] = Form("dN/dp_{T}, cndtn%d", i + 1);
    }
    if (i >= 3){
      title_all_pt[i] = Form("dN/dp_{T}, cndtn4_p%d", i - 2);
    }
  }
  

  TCanvas *c3 = new TCanvas("c3","True Delta M fit");
  TCanvas *true_chi_c_delta_m[6];
  TString canv_name[6];
  TString hist_name[6];
  
  c3->Divide(2, 3);
  
  for (int i = 0; i < 6; i++){
    c3->cd(i + 1);

    hDeltaMass_true_all_pt[i]->SetTitle(title_all_pt[i]);
    
    fGaus3Sum[i] = new TF1("fGaus3Sum",Gaus3Sum,0.,1.,9);
    fGaus3Sum[i]->SetParName(0,"A_{0}") ;
    fGaus3Sum[i]->SetParName(1,"m_{0}") ;
    fGaus3Sum[i]->SetParName(2,"#sigma_{0}") ;
    fGaus3Sum[i]->SetParName(3,"A_{1}") ;
    fGaus3Sum[i]->SetParName(4,"m_{1}") ;
    fGaus3Sum[i]->SetParName(5,"#sigma_{1}") ;
    fGaus3Sum[i]->SetParName(6,"A_{2}") ;
    fGaus3Sum[i]->SetParName(7,"m_{2}") ;
    fGaus3Sum[i]->SetParName(8,"#sigma_{2}") ;
    fGaus3Sum[i]->SetLineColor(kRed);

    fGaus3Sum[i]->SetParameters(1,0.3192,0.001,
				1,0.4148,0.001,
				1,0.4584,0.001);

    fGaus3Sum[i]->SetParLimits(1,0.313,0.318);
    fGaus3Sum[i]->
      SetParLimits(2,sigma_c0_low_boarder[i],sigma_c0_up_boarder[i]);
    
    fGaus3Sum[i]->SetParLimits(4,0.408,0.420);
    fGaus3Sum[i]->
      SetParLimits(5,sigma_c1_low_boarder[i],sigma_c1_up_boarder[i]);
    
    fGaus3Sum[i]->SetParLimits(7,0.455,0.465);
    fGaus3Sum[i]->
      SetParLimits(8,sigma_c2_low_boarder[i],sigma_c2_up_boarder[i]);
    
    hDeltaMass_true_all_pt[i]->Fit(fGaus3Sum[i],"","",0.25,0.53);

    TF1 *fGausChiC0 = new TF1("fGausChiC0",Gaus,0.,1.,3);
    TF1 *fGausChiC1 = new TF1("fGausChiC1",Gaus,0.,1.,3);
    TF1 *fGausChiC2 = new TF1("fGausChiC2",Gaus,0.,1.,3);
    fGausChiC0->SetParameters(fGaus3Sum[i]->GetParameters());
    fGausChiC1->SetParameters(fGaus3Sum[i]->GetParameters()+3);
    fGausChiC2->SetParameters(fGaus3Sum[i]->GetParameters()+6);
    fGausChiC0->SetLineColor(kBlue);
    fGausChiC1->SetLineColor(kGreen+1);
    fGausChiC2->SetLineColor(kOrange+1);
  
    fGausChiC0->Draw("same");
    fGausChiC1->Draw("same");
    fGausChiC2->Draw("same");
    gStyle->SetOptFit(111111);
    gStyle->SetOptStat(11);
    
    if (i < 3){
      canv_name[i] = Form("true_chic_mass_diff_c%d.pdf", i + 1);
      hist_name[i] = Form("true_chic_mass_diff_c%d", i + 1);
    }
    if (i >= 3){
      canv_name[i] = Form("true_chic_mass_diff_c4_p%d.pdf", i - 2);
      hist_name[i] = Form("true_chic_mass_diff_c4_p%d", i - 2);
    }
    true_chi_c_delta_m[i] = new TCanvas(hist_name[i], hist_name[i]);
    true_chi_c_delta_m[i]->cd();
    hDeltaMass_true_all_pt[i]->SetTitle(title_all_pt[i]);
    hDeltaMass_true_all_pt[i]->Draw();
    fGaus3Sum[i]->Draw("same");
    fGausChiC0->Draw("same");
    fGausChiC1->Draw("same");
    fGausChiC2->Draw("same");
    gStyle->SetOptFit(111111);
    gStyle->SetOptStat(11);
  }

  c3->Print("True_charm_Delta_M_fit_all_pt.pdf");true_chi_c_delta_m[i];
  true_chi_c_delta_m[0]->Print(canv_name[0]);
  true_chi_c_delta_m[1]->Print(canv_name[1]);
  true_chi_c_delta_m[2]->Print(canv_name[2]);
  true_chi_c_delta_m[3]->Print(canv_name[3]);
  true_chi_c_delta_m[4]->Print(canv_name[4]);
  true_chi_c_delta_m[5]->Print(canv_name[5]);

  //Create background all pt pic with fit

  TF1 *fGaus3Sum_with_pol2[6];
  

  TCanvas *c4 = new TCanvas("c4","Backg Delta M fit");
  TString canv_name[6];
  TString hist_name[6];

  Double_t params_1[12] = {1,0.3192,0.001, 
			   1,0.4148,0.001,
			   1,0.4584,0.001,
			   1.43815e+01,-6.52537e+00, 8.20938e-01};
  
  Double_t params_2[12] = {1,0.3192,0.001, 
			   1,0.4148,0.001,
			   1,0.4584,0.001,
			   1.43815e+01,-6.52537e+00, 8.20938e-01};
  
  Double_t params_3[12] = {1,0.3192,0.001, 
			   1,0.4148,0.001,
			   1,0.4584,0.001,
			   1.21790e+00, -8.27097e-01, 1.36026e-01};
  
  Double_t params_4[12] = {1,0.3192,0.001, 
			   1,0.4148,0.001,
			   1,0.4584,0.001,
			   2.99620e+04, -1.07307e+05, 8.40076e+04};
  
  Double_t params_5[12] = {1,0.3192,0.001, 
			   1,0.4148,0.001,
			   1,0.4584,0.001,
			   2.99620e+04, -1.07307e+05, 8.40076e+04};
  
  Double_t params_6[12] = {1,0.3192,0.001, 
			   1,0.4148,0.001,
			   1,0.4584,0.001,
			   2.99620e+04, -1.07307e+05, 8.40076e+04};

  Double_t * params[6];
  
  params[0] = params_1;
  params[1] = params_2;
  params[2] = params_3;
  params[3] = params_4;
  params[4] = params_5;
  params[5] = params_6;
  
  c4->Divide(2, 3);
  
  for (int i = 0; i < 6; i++){
    c4->cd(i + 1);hDeltaMass_back_all_pt[i]->SetTitle(title_all_pt[i]);
    
    fGaus3Sum_with_pol2[i] = 
      new TF1("fGaus3Sum_with_pol2",Gaus3Sum_with_pol2,0.,1.,12);
    fGaus3Sum_with_pol2[i]->SetParName(0,"A_{0}") ;
    fGaus3Sum_with_pol2[i]->SetParName(1,"m_{0}") ;
    fGaus3Sum_with_pol2[i]->SetParName(2,"#sigma_{0}") ;
    fGaus3Sum_with_pol2[i]->SetParName(3,"A_{1}") ;
    fGaus3Sum_with_pol2[i]->SetParName(4,"m_{1}") ;
    fGaus3Sum_with_pol2[i]->SetParName(5,"#sigma_{1}") ;
    fGaus3Sum_with_pol2[i]->SetParName(6,"A_{2}") ;
    fGaus3Sum_with_pol2[i]->SetParName(7,"m_{2}") ;
    fGaus3Sum_with_pol2[i]->SetParName(8,"#sigma_{2}") ;
    fGaus3Sum_with_pol2[i]->SetLineColor(kRed);
    
    fGaus3Sum_with_pol2[i]->SetParameters(params[i]);
    
    fGaus3Sum_with_pol2[i]->SetParLimits(1,0.313,0.318);
    fGaus3Sum_with_pol2[i]->
      SetParLimits(2,sigma_c0_low_boarder[i],sigma_c0_up_boarder[i]);
    
    fGaus3Sum_with_pol2[i]->SetParLimits(4,0.408,0.420);
    fGaus3Sum_with_pol2[i]->
      SetParLimits(5,sigma_c1_low_boarder[i],sigma_c1_up_boarder[i]);
    
    fGaus3Sum_with_pol2[i]->SetParLimits(7,0.455,0.465);
    fGaus3Sum_with_pol2[i]->
      SetParLimits(8,sigma_c2_low_boarder[i],sigma_c2_up_boarder[i]);
    
    hDeltaMass_back_all_pt[i]->Fit(fGaus3Sum_with_pol2[i],"","",0.25,0.53);
    
    TF1 *fGausChiC0 = new TF1("fGausChiC0",Gaus,0.,1.,3);
    TF1 *fGausChiC1 = new TF1("fGausChiC1",Gaus,0.,1.,3);
    TF1 *fGausChiC2 = new TF1("fGausChiC2",Gaus,0.,1.,3);
    TF1 *pol2_backg = new TF1("pol2_backg",pol2,0.,1.,3);
    fGausChiC0->SetParameters(fGaus3Sum_with_pol2[i]->GetParameters());
    fGausChiC1->SetParameters(fGaus3Sum_with_pol2[i]->GetParameters()+3);
    fGausChiC2->SetParameters(fGaus3Sum_with_pol2[i]->GetParameters()+6);
    pol2_backg->SetParameters(fGaus3Sum_with_pol2[i]->GetParameters()+9);
    fGausChiC0->SetLineColor(kBlue);
    fGausChiC1->SetLineColor(kGreen+1);
    fGausChiC2->SetLineColor(kOrange+1);
    pol2_backg->SetLineColor(kCyan);

    pol2_backg->SetNpx(200);
    
    hBackground[i] = (TH1D*)pol2_backg->GetHistogram();
    
    fGausChiC0->Draw("same");
    fGausChiC1->Draw("same");
    fGausChiC2->Draw("same");
    pol2_backg->Draw("same");
    
    gStyle->SetOptFit(111111);
    gStyle->SetOptStat(11);
  }
  
  c4->Print("Backg_charm_Delta_M_fit_all_pt.pdf");


  //Find efficiency of charmonium

  TH1D* charmonium_efficiency[6];
  TString efficiency_title[6];
  TString efficiency_name[6];

  TCanvas *c5 = new TCanvas("c5", "Charmonium_witout_backg");
  c5->Divide(2, 3);

  for (int i = 0; i < 6; i++){
    c5->cd(i + 1);
    if (i < 3){
      efficiency_name[i] = Form("charmonium_efficiency_c%d", i + 1);
      efficiency_title[i] = Form("#chi_{c}cand/#chi_{c}true");
    } 
    if (i >= 3){
      efficiency_name[i] = Form("charmonium_efficiency_c4_p5d", i - 2);
      efficiency_title[i] = Form("#chi_{c}cand/#chi_{c}true");
    }
    
    chic_witout_back[i]->SetTitle(efficiency_title[i]);
    chic_witout_back[i]->Add(hBackground[i], -1);
    chic_witout_back[i]->SetAxisRange(0.25,0.53,"X");
    chic_witout_back[i]->Draw();
  }

  c5->Print("chic_without_backg.pdf");
  
  TCanvas *c6 = new TCanvas("c6", "Charmonium_efficiency");
  c6->Divide(2, 3);

  for (int i = 0; i < 6; i++){
    c6->cd(i + 1);

    charmonium_efficiency[i] = (TH1D*)chic_witout_back[i]->Clone();  
    charmonium_efficiency[i]->Divide(hDeltaMass_true_all_pt[i]);
    charmonium_efficiency[i]->SetAxisRange(0.3, 0.5, "X");
    charmonium_efficiency[i]->Draw();
  }

  c6->Print("charmonium_efficiency.pdf");

  //Find number of true chi_c[0, 1, 2](pT)

  /*TCanvas* chic_canv[6];
  chic_canv[0] = new TCanvas("chic_canv0", "chi_c data cndtn_1");
  chic_canv[1] = new TCanvas("chic_canv1", "chi_c data cndtn_2");
  chic_canv[2] = new TCanvas("chic_canv2", "chi_c data cndtn_3");
  chic_canv[3] = new TCanvas("chic_canv3", "chi_c data cndtn_4_p1");
  chic_canv[4] = new TCanvas("chic_canv4", "chi_c data cndtn_4_p2");
  chic_canv[5] = new TCanvas("chic_canv5", "chi_c data cndtn_4_p3");
  
  TH2F* hDeltaMass_true[6];
  
  hDeltaMass_true[0] = hDeltaMass_true_c0;
  hDeltaMass_true[1] = hDeltaMass_true_c1;
  hDeltaMass_true[2] = hDeltaMass_true_c2;
  hDeltaMass_true[3] = hDeltaMass_true_p1;
  hDeltaMass_true[4] = hDeltaMass_true_p2;
  hDeltaMass_true[5] = hDeltaMass_true_p3;
  
  const Int_t NBINS = 19; 
  double border_arr[NBINS + 1] = 
    {0.,1.,2.,3.,4.,5.,6.,7.,8.,9.,10.,12.,14.,16.,18.,20.,25.,30.,35.,50.}; 

  TH1D *hchi_c_true[NBINS][6];
  double chic_true_num[NBINS][3];
  
  chic_canv[0]->Divide(4, 5);
  chic_canv[1]->Divide(4, 5);
  chic_canv[2]->Divide(4, 5);
  chic_canv[3]->Divide(4, 5);
  chic_canv[4]->Divide(4, 5);
  chic_canv[5]->Divide(4, 5);

  TF1 *fGaus3Sum = new TF1("fGaus3Sum",Gaus3Sum,0.,1.,9);
  fGaus3Sum->SetParName(0,"A_{0}") ;
  fGaus3Sum->SetParName(1,"m_{0}") ;
  fGaus3Sum->SetParName(2,"#sigma_{0}") ;
  fGaus3Sum->SetParName(3,"A_{1}") ;
  fGaus3Sum->SetParName(4,"m_{1}") ;
  fGaus3Sum->SetParName(5,"#sigma_{1}") ;
  fGaus3Sum->SetParName(6,"A_{2}") ;
  fGaus3Sum->SetParName(7,"m_{2}") ;
  fGaus3Sum->SetParName(8,"#sigma_{2}") ;
  fGaus3Sum->SetLineColor(kRed);

  double true_chi_c0_num[NBINS][6];
  double true_chi_c1_num[NBINS][6];
  double true_chi_c2_num[NBINS][6];
    

  for(int iPt = 0; iPt < NBINS; iPt++){
    TString name_pr = Form("p_T_slice_%d", iPt);
    for (int i = 0; i < 6; i++){
      hchi_c_true[iPt][i] = hDeltaMass_true[i]->
	ProjectionX(name_pr, border_arr[iPt], border_arr[iPt + 1]); 
      
      fGaus3Sum->SetParameters(1,0.3192,0.015,
			       1,0.4148,0.014,
			       1,0.4584,0.015);

      fGaus3Sum->SetParLimits(1,0.313,0.318);
      fGaus3Sum->SetParLimits(2,0.012,0.02);
 
      fGaus3Sum->SetParLimits(4,0.408,0.420);
      fGaus3Sum->SetParLimits(5,0.010,0.020);
      
      fGaus3Sum->SetParLimits(7,0.455,0.465);
      fGaus3Sum->SetParLimits(8,0.010,0.020);
      
      chic_canv[i]->cd(iPt + 1);

      hchi_c_true[iPt][i]->Fit(fGaus3Sum,"","",0.25,0.53);

      TF1 *fGausChiC0 = new TF1("fGausChiC0",Gaus,0.,1.,3);
      TF1 *fGausChiC1 = new TF1("fGausChiC1",Gaus,0.,1.,3);
      TF1 *fGausChiC2 = new TF1("fGausChiC2",Gaus,0.,1.,3);
      fGausChiC0->SetParameters(fGaus3Sum->GetParameters());
      fGausChiC1->SetParameters(fGaus3Sum->GetParameters()+3);
      fGausChiC2->SetParameters(fGaus3Sum->GetParameters()+6);
      fGausChiC0->SetLineColor(kBlue);
      fGausChiC1->SetLineColor(kGreen+1);
      fGausChiC2->SetLineColor(kOrange+1);
  
      fGausChiC0->Draw("same");
      fGausChiC1->Draw("same");
      fGausChiC2->Draw("same");
      
      true_chi_c0_num[iPt][i] = TMath::Sqrt(TMath::TwoPi())*fGaus3Sum->
	GetParameter(0)*fGaus3Sum->GetParameter(2)/hchi_c_true[iPt][i]->
	GetBinWidth(1);
      true_chi_c1_num[iPt][i] = TMath::Sqrt(TMath::TwoPi())*fGaus3Sum->
	GetParameter(3)*fGaus3Sum->GetParameter(5)/hchi_c_true[iPt][i]->
	GetBinWidth(1);
      true_chi_c2_num[iPt][i] = TMath::Sqrt(TMath::TwoPi())*fGaus3Sum->
	GetParameter(6)*fGaus3Sum->GetParameter(8)/hchi_c_true[iPt][i]->
	GetBinWidth(1);
      printf("Number of chi_c0: = %.2e \n",true_chi_c0_num[iPt][i]);
      printf("Number of chi_c1: = %.2e \n",true_chi_c1_num[iPt][i]);
      printf("Number of chi_c2: = %.2e \n",true_chi_c2_num[iPt][i]);
    }
    
  }

  chic_canv[0]->Print("chi_c_data_cndtn_1.pdf");
  chic_canv[1]->Print("chi_c_data_cndtn_2.pdf");
  chic_canv[2]->Print("chi_c_data_cndtn_3.pdf");
  chic_canv[3]->Print("chi_c_data_cndtn_4_p1.pdf");
  chic_canv[4]->Print("chi_c_data_cndtn_4_p2.pdf");
  chic_canv[5]->Print("chi_c_data_cndtn_4_p3.pdf");

  TH1D* number_of_true_chic0[6];
  TH1D* number_of_true_chic1[6];
  TH1D* number_of_true_chic2[6];

  for (int i = 0; i < 6; i++){
    TString name0 = Form("number_of_chic0_%d", i + 1);
    TString name1 = Form("number_of_chic1_%d", i + 1);
    TString name2 = Form("number_of_chic2_%d", i + 1);
    number_of_true_chic0[i] = new 
      TH1D(name0, "number_of_true_chic0", NBINS, border_arr);
    number_of_true_chic1[i] = new 
      TH1D(name1, "number_of_true_chic1", NBINS, border_arr);
    number_of_true_chic2[i] = new 
      TH1D(name2, "number_of_true_chic2", NBINS, border_arr);
    for(int iPt = 1; iPt <= NBINS; iPt++){
      number_of_true_chic0[i]->SetBinContent(iPt, true_chi_c0_num[iPt - 1][i]);
      number_of_true_chic1[i]->SetBinContent(iPt, true_chi_c1_num[iPt - 1][i]);
      number_of_true_chic2[i]->SetBinContent(iPt, true_chi_c2_num[iPt - 1][i]);
    }
    }*/

  //Find number of cand chi_c[0, 1, 2](pT)*/
  
  return;
}

Double_t Gaus3Sum_with_pol2(Double_t *x, Double_t *p){
  
  Double_t dM1 = (x[0]-p[1])/p[2];
  Double_t y1  = p[0]*exp(-dM1*dM1/2.);

  Double_t dM2 = (x[0]-p[4])/p[5];
  Double_t y2  = p[3]*exp(-dM2*dM2/2.);

  Double_t dM3 = (x[0]-p[7])/p[8];
  Double_t y3  = p[6]*exp(-dM3*dM3/2.);
  
  Double_t y4 = p[9]*x[0]*x[0] + p[10]*x[0] + p[11];
  
  return y1+y2+y3+y4;
}

Double_t pol2(Double_t *x, Double_t *p){
  
  Double_t y1 = p[0]*x[0]*x[0] + p[1]*x[0] + p[2];
  
  return y1;
}

Double_t Gaus3Sum(Double_t *x, Double_t *p){
  
  Double_t dM1 = (x[0]-p[1])/p[2];
  Double_t y1  = p[0]*exp(-dM1*dM1/2.);

  Double_t dM2 = (x[0]-p[4])/p[5];
  Double_t y2  = p[3]*exp(-dM2*dM2/2.);

  Double_t dM3 = (x[0]-p[7])/p[8];
  Double_t y3  = p[6]*exp(-dM3*dM3/2.);
  
  return y1+y2+y3;
}

Double_t Gaus(Double_t *x, Double_t *p){
  
  Double_t dM1 = (x[0]-p[1])/p[2];
  Double_t y1  = p[0]*exp(-dM1*dM1/2.);
  
  return y1;
}
