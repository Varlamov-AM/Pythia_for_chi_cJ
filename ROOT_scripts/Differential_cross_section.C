void Rebining_DCS(TH1D*);

void Differential_cross_section(){

  TFile *file1 = new TFile("Pythia_for_charmonium_new_version.root");
  TFile *file2 = new TFile("Pythia_for_Soft_QCD.root");
  
  TH2F *hChi_c2_pt_y_cndtn_1 = (TH2F*)file1->Get("hChi_c2_pt_y_cndtn_1");//file 1
  TH2F *hChi_c1_pt_y_cndtn_1 = (TH2F*)file1->Get("hChi_c1_pt_y_cndtn_1");
  TH2F *hChi_c0_pt_y_cndtn_1 = (TH2F*)file1->Get("hChi_c0_pt_y_cndtn_1");
  TH2F *hJpsi_from_chic_ALICE0_c0_charm = (TH2F*)file1->Get("hJpsi_from_chic_ALICE0_c0");
  TH2F *hJpsi_from_chic_ALICE0_c0_SOFTQ = (TH2F*)file2->Get("hJpsi_from_chic_ALICE0_c0");
  
  TH2F *hChi_c2_pt_y_cndtn_2 = (TH2F*)file1->Get("hChi_c2_pt_y_cndtn_2");
  TH2F *hChi_c1_pt_y_cndtn_2 = (TH2F*)file1->Get("hChi_c1_pt_y_cndtn_2");
  TH2F *hChi_c0_pt_y_cndtn_2 = (TH2F*)file1->Get("hChi_c0_pt_y_cndtn_2");
  TH2F *hJpsi_from_chic_ALICE0_c1_charm = (TH2F*)file1->Get("hJpsi_from_chic_ALICE0_c1");
  TH2F *hJpsi_from_chic_ALICE0_c1_SOFTQ = (TH2F*)file2->Get("hJpsi_from_chic_ALICE0_c1");
  
  TH2F *hChi_c2_pt_y_cndtn_3 = (TH2F*)file1->Get("hChi_c2_pt_y_cndtn_3");
  TH2F *hChi_c1_pt_y_cndtn_3 = (TH2F*)file1->Get("hChi_c1_pt_y_cndtn_3");
  TH2F *hChi_c0_pt_y_cndtn_3 = (TH2F*)file1->Get("hChi_c0_pt_y_cndtn_3");
  TH2F *hJpsi_from_chic_ALICE0_c2_charm = (TH2F*)file1->Get("hJpsi_from_chic_ALICE0_c2");
  TH2F *hJpsi_from_chic_ALICE0_c2_SOFTQ = (TH2F*)file2->Get("hJpsi_from_chic_ALICE0_c2");
  
  TH2F *hChi_c2_pt_y_cndtn_4 = (TH2F*)file1->Get("hChi_c2_pt_y_cndtn_4");
  TH2F *hChi_c1_pt_y_cndtn_4 = (TH2F*)file1->Get("hChi_c1_pt_y_cndtn_4");
  TH2F *hChi_c0_pt_y_cndtn_4 = (TH2F*)file1->Get("hChi_c0_pt_y_cndtn_4");
  TH2F *hJpsi_from_chic_ALICE3_p1_charm = (TH2F*)file1->Get("hJpsi_from_chic_ALICE3_p1");
  TH2F *hJpsi_from_chic_ALICE3_p1_SOFTQ = (TH2F*)file2->Get("hJpsi_from_chic_ALICE3_p1");
  
  TH2F *hChi_c2_pt_y_charmon = (TH2F*)file1->Get("hChi_c2_pt_y");
  TH2F *hChi_c1_pt_y_charmon = (TH2F*)file1->Get("hChi_c1_pt_y");
  TH2F *hChi_c0_pt_y_charmon = (TH2F*)file1->Get("hChi_c0_pt_y");
  
  TH2F *hChi_c2_pt_y_SoftQCD = (TH2F*)file2->Get("hChi_c2_pt_y");
  TH2F *hChi_c1_pt_y_SoftQCD = (TH2F*)file2->Get("hChi_c1_pt_y");
  TH2F *hChi_c0_pt_y_SoftQCD = (TH2F*)file2->Get("hChi_c0_pt_y");


  TH1F *hCross_section_hist_C  = (TH1F*)file1->Get("hCross_section_hist");
  TH1F *hCross_section_hist_S  = (TH1F*)file2->Get("hCross_section_hist");

  TH2F* Differential_cross_section_cndtn_1[4];
  TH2F* Differential_cross_section_cndtn_2[4];
  TH2F* Differential_cross_section_cndtn_3[4];
  TH2F* Differential_cross_section_cndtn_4[4];
  TH1D* chic_cndtn_1[4];
  TH1D* chic_cndtn_2[4];
  TH1D* chic_cndtn_3[4];
  TH1D* chic_cndtn_4[4];

  Differential_cross_section_cndtn_1[0] = hChi_c0_pt_y_cndtn_1;
  Differential_cross_section_cndtn_1[1] = hChi_c1_pt_y_cndtn_1;
  Differential_cross_section_cndtn_1[2] = hChi_c2_pt_y_cndtn_1;
  Differential_cross_section_cndtn_1[3] = hJpsi_from_chic_ALICE0_c0_charm;

  Differential_cross_section_cndtn_2[0] = hChi_c0_pt_y_cndtn_2;
  Differential_cross_section_cndtn_2[1] = hChi_c1_pt_y_cndtn_2;
  Differential_cross_section_cndtn_2[2] = hChi_c2_pt_y_cndtn_2;
  Differential_cross_section_cndtn_2[3] = hJpsi_from_chic_ALICE0_c1_charm;

  Differential_cross_section_cndtn_3[0] = hChi_c0_pt_y_cndtn_3;
  Differential_cross_section_cndtn_3[1] = hChi_c1_pt_y_cndtn_3;
  Differential_cross_section_cndtn_3[2] = hChi_c2_pt_y_cndtn_3;
  Differential_cross_section_cndtn_3[3] = hJpsi_from_chic_ALICE0_c2_charm;

  Differential_cross_section_cndtn_4[0] = hChi_c0_pt_y_cndtn_4;
  Differential_cross_section_cndtn_4[1] = hChi_c1_pt_y_cndtn_4;
  Differential_cross_section_cndtn_4[2] = hChi_c2_pt_y_cndtn_4;
  Differential_cross_section_cndtn_4[3] = hJpsi_from_chic_ALICE3_p1_charm;

  double xsection = hCross_section_hist_C->GetBinContent(1);
  double ntrials  = hCross_section_hist_C->GetBinContent(2);
  double nfiles   = hCross_section_hist_C->GetEntries()/2;

  double sigma_weight = xsection/ntrials/nfiles;

  double xsection_m = hCross_section_hist_S->GetBinContent(1);
  double ntrials_m  = hCross_section_hist_S->GetBinContent(2);
  double nfiles_m   = hCross_section_hist_S->GetEntries()/2;

  double sigma_weight_m = xsection_m/ntrials_m/nfiles_m;
  

  int nPtBins = hChi_c2_pt_y_cndtn_3->GetNbinsX();
  int nyBins  = hChi_c2_pt_y_cndtn_3->GetNbinsY();

  double scale_factor = (sigma_weight)/((50./nPtBins)*(4./nyBins));
  double scale_factor_m = (sigma_weight_m)/((50./nPtBins)*(4./nyBins));
  
  TCanvas* canv_c1 = new TCanvas("canv_c1", "Differential_cross_section_c1");
  canv_c1->Divide(2, 3);
  
  TCanvas* canv_c2 = new TCanvas("canv_c2", "Differential_cross_section_c2");
  canv_c2->Divide(2, 3);
  
  TCanvas* canv_c3 = new TCanvas("canv_c3", "Differential_cross_section_c3");
  canv_c3->Divide(2, 3);

  TCanvas* canv_c4 = new TCanvas("canv_c4", "Differential_cross_section_c4");
  canv_c4->Divide(2, 3);

  TCanvas* canv_comp = new TCanvas("canv_comp", "Differential_cross_section_all_charm_compare");
  canv_comp->Divide(2, 2);

  TCanvas* canv_ratio = new TCanvas("canv_ratio", "Differential_cross_section_all_charm_ratio");
  canv_ratio->Divide(2, 2);

  TCanvas* canv_comp_jpsi = new TCanvas("canv_comp_jpsi", "Differential_cross_section_jpsi_compare");
  canv_comp_jpsi->Divide(2, 2);

  TCanvas* canv_ratio_jpsi = new TCanvas("canv_ratioJjpsi", "Differential_cross_section_jpsi_ratio");
  canv_ratio_jpsi->Divide(2, 2);

//______________________________________________________________________________

  //Compare differential cross section Charmonium vs SoftQCD process

  canv_comp->cd(1);

  TH1D* hChi_c0_pt_charmon = (TH1D*)hChi_c0_pt_y_charmon->ProjectionX("charmon_0");
  TH1D* hChi_c0_pt_SoftQCD = (TH1D*)hChi_c0_pt_y_SoftQCD->ProjectionX("SoftQCD_0");

  gPad->SetLogy();

  hChi_c0_pt_charmon->SetLineColor(kRed);
  hChi_c0_pt_SoftQCD->SetLineColor(kBlue);
  
  hChi_c0_pt_charmon->Scale(scale_factor);
  hChi_c0_pt_SoftQCD->Scale(scale_factor_m);

  Rebining_DCS(hChi_c0_pt_charmon);
  Rebining_DCS(hChi_c0_pt_SoftQCD);
  
  hChi_c0_pt_charmon->Draw();
  hChi_c0_pt_SoftQCD->Draw("same");

  canv_comp->cd(2);

  gPad->SetLogy();

  TH1D* hChi_c1_pt_charmon = (TH1D*)hChi_c1_pt_y_charmon->ProjectionX("charmon_1");
  TH1D* hChi_c1_pt_SoftQCD = (TH1D*)hChi_c1_pt_y_SoftQCD->ProjectionX("SoftQCD_1");

  hChi_c1_pt_charmon->SetLineColor(kRed);
  hChi_c1_pt_SoftQCD->SetLineColor(kBlue);
  
  hChi_c1_pt_charmon->Scale(scale_factor);
  hChi_c1_pt_SoftQCD->Scale(scale_factor_m);

  Rebining_DCS(hChi_c1_pt_charmon);
  Rebining_DCS(hChi_c1_pt_SoftQCD);

  hChi_c1_pt_charmon->Draw();
  hChi_c1_pt_SoftQCD->Draw("same");

  canv_comp_jpsi->cd(3);

  gPad->SetLogy();

  TH1D* hChi_c2_pt_charmon = (TH1D*)hChi_c2_pt_y_charmon->ProjectionX("charmon_2");
  TH1D* hChi_c2_pt_SoftQCD = (TH1D*)hChi_c2_pt_y_SoftQCD->ProjectionX("SoftQCD_2");

  hChi_c2_pt_charmon->SetLineColor(kRed);
  hChi_c2_pt_SoftQCD->SetLineColor(kBlue);
  
  hChi_c2_pt_charmon->Scale(scale_factor);
  hChi_c2_pt_SoftQCD->Scale(scale_factor_m);

  Rebining_DCS(hChi_c2_pt_charmon);
  Rebining_DCS(hChi_c2_pt_SoftQCD);

  hChi_c2_pt_charmon->Draw();
  hChi_c2_pt_SoftQCD->Draw("same");

//______________________________________________________________________________

  // Find ratio of differential cross section

  canv_ratio->cd(1);
  
  TH1D* chi_c0_ratio = (TH1D*)hChi_c0_pt_charmon->Clone();
  chi_c0_ratio->Divide(hChi_c0_pt_SoftQCD);

  chi_c0_ratio->SetAxisRange(0.,3.99,"Y");
  chi_c0_ratio->Draw();

  canv_ratio->cd(2);
  
  TH1D* chi_c1_ratio = (TH1D*)hChi_c1_pt_charmon->Clone();
  chi_c1_ratio->Divide(hChi_c1_pt_SoftQCD);
  chi_c1_ratio->SetAxisRange(0.,3.99,"Y");

  chi_c1_ratio->Draw();

  canv_ratio->cd(3);
  
  TH1D* chi_c2_ratio = (TH1D*)hChi_c2_pt_charmon->Clone();
  chi_c2_ratio->Divide(hChi_c2_pt_SoftQCD);
  chi_c2_ratio->SetAxisRange(0.,3.99,"Y");

  chi_c2_ratio->Draw();


  //____________________________________________________________________________

 //Compare differential cross section Charmonium vs SoftQCD process for Jpsi

  canv_comp_jpsi->cd(1);

  TH2F* jpsi_c1_charm = (TH2F*)hJpsi_from_chic_ALICE0_c0_charm->Clone();
  TH2F* jpsi_c1_SoftQ = (TH2F*)hJpsi_from_chic_ALICE0_c0_SOFTQ->Clone();

  TH1D* Jpsi_c1_charmonium = jpsi_c1_charm->ProjectionX("jpsi_charm_c1");
  TH1D* Jpsi_c1_SoftQCD_pr = jpsi_c1_SoftQ->ProjectionX("jpsi_SoftQ_c1");

  gPad->SetLogy();

  Jpsi_c1_charmonium->SetLineColor(kRed);
  Jpsi_c1_SoftQCD_pr->SetLineColor(kBlue);
  
  Jpsi_c1_charmonium->Scale(scale_factor);
  Jpsi_c1_SoftQCD_pr->Scale(scale_factor_m);

  Rebining_DCS(Jpsi_c1_charmonium);
  Rebining_DCS(Jpsi_c1_SoftQCD_pr);
  
  Jpsi_c1_charmonium->Draw();
  Jpsi_c1_SoftQCD_pr->Draw("same");

 
  canv_comp_jpsi->cd(2);

  TH2F* jpsi_c2_charm = (TH2F*)hJpsi_from_chic_ALICE0_c1_charm->Clone();
  TH2F* jpsi_c2_SoftQ = (TH2F*)hJpsi_from_chic_ALICE0_c1_SOFTQ->Clone();

  TH1D* Jpsi_c2_charmonium = jpsi_c2_charm->ProjectionX("jpsi_charm_c2");
  TH1D* Jpsi_c2_SoftQCD_pr = jpsi_c2_SoftQ->ProjectionX("jpsi_SoftQ_c2");

  gPad->SetLogy();

  Jpsi_c2_charmonium->SetLineColor(kRed);
  Jpsi_c2_SoftQCD_pr->SetLineColor(kBlue);
  
  Jpsi_c2_charmonium->Scale(scale_factor);
  Jpsi_c2_SoftQCD_pr->Scale(scale_factor_m);

  Rebining_DCS(Jpsi_c2_charmonium);
  Rebining_DCS(Jpsi_c2_SoftQCD_pr);
  
  Jpsi_c2_charmonium->Draw();
  Jpsi_c2_SoftQCD_pr->Draw("same");

 
  canv_comp_jpsi->cd(3);

  TH2F* jpsi_c3_charm = (TH2F*)hJpsi_from_chic_ALICE0_c2_charm->Clone();
  TH2F* jpsi_c3_SoftQ = (TH2F*)hJpsi_from_chic_ALICE0_c2_SOFTQ->Clone();

  TH1D* Jpsi_c3_charmonium = jpsi_c3_charm->ProjectionX("jpsi_charm_c3");
  TH1D* Jpsi_c3_SoftQCD_pr = jpsi_c3_SoftQ->ProjectionX("jpsi_SoftQ_c3");

  gPad->SetLogy();

  Jpsi_c3_charmonium->SetLineColor(kRed);
  Jpsi_c3_SoftQCD_pr->SetLineColor(kBlue);
  
  Jpsi_c3_charmonium->Scale(scale_factor);
  Jpsi_c3_SoftQCD_pr->Scale(scale_factor_m);

  Rebining_DCS(Jpsi_c3_charmonium);
  Rebining_DCS(Jpsi_c3_SoftQCD_pr);
  
  Jpsi_c3_charmonium->Draw();
  Jpsi_c3_SoftQCD_pr->Draw("same");

 
  canv_comp_jpsi->cd(4);

  TH2F* jpsi_c4_charm = (TH2F*)hJpsi_from_chic_ALICE3_p1_charm->Clone();
  TH2F* jpsi_c4_SoftQ = (TH2F*)hJpsi_from_chic_ALICE3_p1_SOFTQ->Clone();

  TH1D* Jpsi_c4_charmonium = jpsi_c4_charm->ProjectionX("jpsi_charm_c4");
  TH1D* Jpsi_c4_SoftQCD_pr = jpsi_c4_SoftQ->ProjectionX("jpsi_SoftQ_c4");

  gPad->SetLogy();

  Jpsi_c4_charmonium->SetLineColor(kRed);
  Jpsi_c4_SoftQCD_pr->SetLineColor(kBlue);
  
  Jpsi_c4_charmonium->Scale(scale_factor);
  Jpsi_c4_SoftQCD_pr->Scale(scale_factor_m);

  Rebining_DCS(Jpsi_c4_charmonium);
  Rebining_DCS(Jpsi_c4_SoftQCD_pr);
  
  Jpsi_c4_charmonium->Draw();
  Jpsi_c4_SoftQCD_pr->Draw("same");

//______________________________________________________________________________

  // Find ratio of differential cross section

  canv_ratio_jpsi->cd(1);
  
  TH1D* Jpsi_c1_ratio = (TH1D*)Jpsi_c1_charmonium->Clone();
  Jpsi_c1_ratio->Divide(Jpsi_c1_SoftQCD_pr);
  Jpsi_c1_ratio->SetAxisRange(0.,3.99,"Y");

  Jpsi_c1_ratio->Draw();

  canv_ratio_jpsi->cd(2);
  
  TH1D* Jpsi_c2_ratio = (TH1D*)Jpsi_c2_charmonium->Clone();
  Jpsi_c2_ratio->Divide(Jpsi_c2_SoftQCD_pr);
  Jpsi_c2_ratio->SetAxisRange(0.,3.99,"Y");

  Jpsi_c2_ratio->Draw();

  canv_ratio_jpsi->cd(3);
  
  TH1D* Jpsi_c3_ratio = (TH1D*)Jpsi_c3_charmonium->Clone();
  Jpsi_c3_ratio->Divide(Jpsi_c3_SoftQCD_pr);
  Jpsi_c3_ratio->SetAxisRange(0.,3.99,"Y");

  Jpsi_c3_ratio->Draw();
  
  TH1D* Jpsi_c4_ratio = (TH1D*)Jpsi_c4_charmonium->Clone();
  Jpsi_c4_ratio->Divide(Jpsi_c4_SoftQCD_pr);
  Jpsi_c4_ratio->SetAxisRange(0.,3.99,"Y");

  Jpsi_c4_ratio->Draw();


//______________________________________________________________________________

  for (int i = 0; i < 5; i++){
    
    if (i < 4){
      Differential_cross_section_cndtn_1[i]->Scale(scale_factor);
    }
    
    canv_c1->cd(i + 1);
    gPad->SetLogy();
    
    if (i == 4){

      TH1D* h0 = (TH1D*)chic_cndtn_1[0]->Clone();
      TH1D* h1 = (TH1D*)chic_cndtn_1[1]->Clone();
      TH1D* h2 = (TH1D*)chic_cndtn_1[2]->Clone();
      h0->SetLineColor(kGreen);
      h1->SetLineColor(kBlue);
      h2->SetLineColor(kRed);

      h1->SetTitle("d#sigma_{#chi_{cJ}}/dp_{T}");

      h1->Draw();
      h2->Draw("same");
      h0->Draw("same");

      continue;
    }

    chic_cndtn_1[i] = Differential_cross_section_cndtn_1[i]->ProjectionX();

    Rebining_DCS(chic_cndtn_1[i]);
    
    TString title = Form("d#sigma_{#chi_{c%d}}/dp_{T}", i);
    if (i == 3){
      title = Form("d#sigma_{J/#psi}/dp_{T}");
    }

    chic_cndtn_1[i]->SetTitle(title);
    chic_cndtn_1[i]->Draw();

    double integral = chic_cndtn_1[i]->Integral();

    cout << integral << "\n";

  }
  cout << "\n\n\n";  

  for (int i = 0; i < 5; i++){
    
    if (i < 4){
      Differential_cross_section_cndtn_2[i]->Scale(scale_factor);
    }
    
    canv_c2->cd(i + 1);
    gPad->SetLogy();
    
    if (i == 4){

      TH1D* h0 = (TH1D*)chic_cndtn_2[0]->Clone();
      TH1D* h1 = (TH1D*)chic_cndtn_2[1]->Clone();
      TH1D* h2 = (TH1D*)chic_cndtn_2[2]->Clone();
      h0->SetLineColor(kGreen);
      h1->SetLineColor(kBlue);
      h2->SetLineColor(kRed);

      h1->SetTitle("d#sigma_{#chi_{cJ}}/dp_{T}");

      h1->Draw();
      h2->Draw("same");
      h0->Draw("same");

      continue;
    }

    chic_cndtn_2[i] = Differential_cross_section_cndtn_2[i]->ProjectionX();

    Rebining_DCS(chic_cndtn_2[i]);
    
    TString title = Form("d#sigma_{#chi_{c%d}}/dp_{T}", i);
    if (i == 3){
      title = Form("d#sigma_{J/#psi}/dp_{T}");
    }

    chic_cndtn_2[i]->SetTitle(title);
    chic_cndtn_2[i]->Draw();

    double integral = chic_cndtn_2[i]->Integral();

    cout << integral << "\n";

  }
  cout << "\n\n\n"; 

  for (int i = 0; i < 5; i++){
    
    if (i < 4){
      Differential_cross_section_cndtn_3[i]->Scale(scale_factor);
    }
    
    canv_c3->cd(i + 1);
    gPad->SetLogy();
    
    if (i == 4){

      TH1D* h0 = (TH1D*)chic_cndtn_3[0]->Clone();
      TH1D* h1 = (TH1D*)chic_cndtn_3[1]->Clone();
      TH1D* h2 = (TH1D*)chic_cndtn_3[2]->Clone();
      h0->SetLineColor(kGreen);
      h1->SetLineColor(kBlue);
      h2->SetLineColor(kRed);

      h1->SetTitle("d#sigma_{#chi_{cJ}}/dp_{T}");

      h1->Draw();
      h2->Draw("same");
      h0->Draw("same");

      continue;
    }

    chic_cndtn_3[i] = Differential_cross_section_cndtn_3[i]->ProjectionX();

    Rebining_DCS(chic_cndtn_3[i]);
    
    TString title = Form("d#sigma_{#chi_{c%d}}/dp_{T}", i);
    if (i == 3){
      title = Form("d#sigma_{J/#psi}/dp_{T}");
    }

    chic_cndtn_3[i]->SetTitle(title);
    chic_cndtn_3[i]->Draw();

    double integral = chic_cndtn_3[i]->Integral();

    cout << integral << "\n";

  }
  cout << "\n\n\n"; 

  for (int i = 0; i < 5; i++){
    
    if (i < 4){
      Differential_cross_section_cndtn_4[i]->Scale(scale_factor);
    }
    
    canv_c4->cd(i + 1);
    gPad->SetLogy();
    
    if (i == 4){

      TH1D* h0 = (TH1D*)chic_cndtn_4[0]->Clone();
      TH1D* h1 = (TH1D*)chic_cndtn_4[1]->Clone();
      TH1D* h2 = (TH1D*)chic_cndtn_4[2]->Clone();
      h0->SetLineColor(kGreen);
      h1->SetLineColor(kBlue);
      h2->SetLineColor(kRed);

      h1->SetTitle("d#sigma_{#chi_{cJ}}/dp_{T}");

      h1->Draw();
      h2->Draw("same");
      h0->Draw("same");

      continue;
    }

    chic_cndtn_4[i] = Differential_cross_section_cndtn_4[i]->ProjectionX();

    Rebining_DCS(chic_cndtn_4[i]);
    
    TString title = Form("d#sigma_{#chi_{c%d}}/dp_{T}", i);
    if (i == 3){
      title = Form("d#sigma_{J/#psi}/dp_{T}");
    }

    chic_cndtn_4[i]->SetTitle(title);
    chic_cndtn_4[i]->Draw();

    double integral = chic_cndtn_4[i]->Integral();

    cout << integral << "\n";

  }
  cout << "\n\n\n"; 

  /*canv_c1->Print("differential_cross_section_c1.pdf");
  canv_c2->Print("differential_cross_section_c2.pdf");
  canv_c3->Print("differential_cross_section_c3.pdf");
  canv_c4->Print("differential_cross_section_c4.pdf");
  canv_comp->Print("compare_d_c_s_charm.pdf");
  canv_ratio->Print("ratio_d_c_s_charm.pdf");
  canv_comp_jpsi->Print("compare_d_c_s_Jpsi.pdf");
  canv_ratio_jpsi->Print("ratio_d_c_s_Jpsi.pdf");*/

  return;
}


void Rebining_DCS(TH1D* hist){

  double sigma_arr[50];

  for (int i = 0; i < 50; i++){
    double sigma = 0.;
    for (int j = 1; j <= 5; j++){
      sigma += hist->GetBinContent(5 * i + j);   
    }
    sigma_arr[i] = sigma * 0.2 / 1.; 
  } 


  TH1D* hist_copy = (TH1D*)hist->Clone();
  hist->Rebin(5);

  for (int i = 1; i <= 50; i++){
    hist->SetBinContent(i, sigma_arr[i - 1]);
  }


  return;
}
