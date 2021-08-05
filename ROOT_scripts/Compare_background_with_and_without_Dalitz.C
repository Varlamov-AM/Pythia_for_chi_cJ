void Compare_background_with_and_without_Dalitz(){

  TFile *file1 = new TFile("Pythia_for_Soft_QCD_corr_part_1.root");
  TFile *file2 = new TFile("Pythia_for_Soft_QCD_corr_part_1_with_Dalitz.root");
  gStyle->SetPadGridX(1);
  gStyle->SetPadGridY(1);



  // Get hostograms from files
  //____________________________________________________________________________


  TH2F* elecposi_from_even_with_Dalitz[6];

  elecposi_from_even_with_Dalitz[0] = 
    (TH2F*)file2->Get("hMassElecPosi_from_even_ALICE0_c0_from_even");
  elecposi_from_even_with_Dalitz[1] = 
    (TH2F*)file2->Get("hMassElecPosi_from_even_ALICE0_c1_from_even");
  elecposi_from_even_with_Dalitz[2] = 
    (TH2F*)file2->Get("hMassElecPosi_from_even_ALICE0_c2_from_even");
  elecposi_from_even_with_Dalitz[3] = 
    (TH2F*)file2->Get("hMassElecPosi_from_even_ALICE3_p1_from_even");
  elecposi_from_even_with_Dalitz[4] = 
    (TH2F*)file2->Get("hMassElecPosi_from_even_ALICE3_p2_from_even");
  elecposi_from_even_with_Dalitz[5] = 
  (TH2F*)file2->Get("hMassElecPosi_from_even_ALICE3_p3_from_even");

  TH2F* elecposigam_diff_elecposi_with_Dalitz[6];

  elecposigam_diff_elecposi_with_Dalitz[0] = 
    (TH2F*)file2->Get("hMassElecPosiGam_diff_ElecPosi_ALICE0_c0_from_backg");
  elecposigam_diff_elecposi_with_Dalitz[1] = 
    (TH2F*)file2->Get("hMassElecPosiGam_diff_ElecPosi_ALICE0_c1_from_backg");
  elecposigam_diff_elecposi_with_Dalitz[2] = 
    (TH2F*)file2->Get("hMassElecPosiGam_diff_ElecPosi_ALICE0_c2_from_backg");
  elecposigam_diff_elecposi_with_Dalitz[3] = 
    (TH2F*)file2->Get("hMassElecPosiGam_diff_ElecPosi_ALICE3_p1_from_backg");
  elecposigam_diff_elecposi_with_Dalitz[4] = 
    (TH2F*)file2->Get("hMassElecPosiGam_diff_ElecPosi_ALICE3_p2_from_backg");
  elecposigam_diff_elecposi_with_Dalitz[5] = 
    (TH2F*)file2->Get("hMassElecPosiGam_diff_ElecPosi_ALICE3_p3_from_backg");


  TH2F* elecposi_from_even_without_Dalitz[6];

  elecposi_from_even_without_Dalitz[0] = 
    (TH2F*)file1->Get("hMassElecPosi_from_even_ALICE0_c0_from_even");
  elecposi_from_even_without_Dalitz[1] = 
    (TH2F*)file1->Get("hMassElecPosi_from_even_ALICE0_c1_from_even");
  elecposi_from_even_without_Dalitz[2] = 
    (TH2F*)file1->Get("hMassElecPosi_from_even_ALICE0_c2_from_even");
  elecposi_from_even_without_Dalitz[3] = 
    (TH2F*)file1->Get("hMassElecPosi_from_even_ALICE3_p1_from_even");
  elecposi_from_even_without_Dalitz[4] = 
    (TH2F*)file1->Get("hMassElecPosi_from_even_ALICE3_p2_from_even");
  elecposi_from_even_without_Dalitz[5] = 
  (TH2F*)file1->Get("hMassElecPosi_from_even_ALICE3_p3_from_even");

  TH2F* elecposigam_diff_elecposi_without_Dalitz[6];

  elecposigam_diff_elecposi_without_Dalitz[0] = 
    (TH2F*)file1->Get("hMassElecPosiGam_diff_ElecPosi_ALICE0_c0_from_backg");
  elecposigam_diff_elecposi_without_Dalitz[1] = 
    (TH2F*)file1->Get("hMassElecPosiGam_diff_ElecPosi_ALICE0_c1_from_backg");
  elecposigam_diff_elecposi_without_Dalitz[2] = 
    (TH2F*)file1->Get("hMassElecPosiGam_diff_ElecPosi_ALICE0_c2_from_backg");
  elecposigam_diff_elecposi_without_Dalitz[3] = 
    (TH2F*)file1->Get("hMassElecPosiGam_diff_ElecPosi_ALICE3_p1_from_backg");
  elecposigam_diff_elecposi_without_Dalitz[4] = 
    (TH2F*)file1->Get("hMassElecPosiGam_diff_ElecPosi_ALICE3_p2_from_backg");
  elecposigam_diff_elecposi_without_Dalitz[5] = 
    (TH2F*)file1->Get("hMassElecPosiGam_diff_ElecPosi_ALICE3_p3_from_backg");


  // Create canvases and init arrays of 1-dim histograms
  //____________________________________________________________________________


  TCanvas *compare_elecposi = new TCanvas("compare_elecposi", 
					  "Compare_elecposi_mass_spectrum");
  compare_elecposi->Divide(2, 3);
  
  TCanvas *ratio_elecposi_c = new TCanvas("ratio_elecposi_c", 
					  "Find_ratio_elecposi_mass_spectrum");
  ratio_elecposi_c->Divide(2, 3);
  
  TCanvas *compare_elecposigam = new TCanvas("compare_elecposigamm", 
					     "Compare_Delta_mass_spectrum");
  compare_elecposigam->Divide(2, 3);

  TCanvas *ratio_elecposigam_c = new TCanvas("ratio_elecposigam_c", 
					     "Find_ratio_Delta_mass_spectrum");
  ratio_elecposigam_c->Divide(2, 3);


  TH1D* elecposi_with_Dalitz_one_dim[6];
  TH1D* elecposi_without_Dalitz_one_dim[6];
  TH1D* ratio_elecposi[6];

  TH1D* elecposigam_with_Dalitz_one_dim[6];
  TH1D* elecposigam_without_Dalitz_one_dim[6];
  TH1D* ratio_elecposigam[6];

  for(int i = 0; i < 6; i++){

    TString with_Dalitz = Form("with_Dalitz_elecposi_h%d", i + 1);
    TString without_Dalitz = Form("without_Dalitz_elecposi_h%d", i + 1);


    elecposi_with_Dalitz_one_dim[i] = (TH1D*)(elecposi_from_even_with_Dalitz[i])->ProjectionX(with_Dalitz);
    
    elecposi_without_Dalitz_one_dim[i] = (TH1D*)(elecposi_from_even_without_Dalitz[i])->
      ProjectionX(without_Dalitz);

    elecposi_with_Dalitz_one_dim[i]->Rebin(5);
    elecposi_without_Dalitz_one_dim[i]->Rebin(5);
    
    ratio_elecposi[i] = (TH1D*)elecposi_without_Dalitz_one_dim[i]->Clone();
    ratio_elecposi[i]->Divide(elecposi_with_Dalitz_one_dim[i]);
    ratio_elecposi[i]->SetAxisRange(0., 1.29, "Y");
  }

  //draw

  for (int i = 0; i < 6 ; i++){
    compare_elecposi->cd(i + 1);
    gPad->SetLogy();

    elecposi_with_Dalitz_one_dim[i]->SetLineColor(kBlue);
    elecposi_without_Dalitz_one_dim[i]->SetLineColor(kRed);

    elecposi_with_Dalitz_one_dim[i]->Draw("he");
    elecposi_without_Dalitz_one_dim[i]->Draw("he same");

    ratio_elecposi_c->cd(i + 1);
    ratio_elecposi[i]->Draw("he");
  }


  //

  
  for (int i = 0; i < 6; i++){

    TString with_Dalitz = Form("with_Dalitz_elecposigam_h%d", i + 1);
    TString without_Dalitz = Form("without_Dalitz_elecposigam_h%d", i + 1);


    elecposigam_with_Dalitz_one_dim[i] = (TH1D*)(elecposigam_diff_elecposi_with_Dalitz[i])->ProjectionX(with_Dalitz);
    
    elecposigam_without_Dalitz_one_dim[i] = (TH1D*)(elecposigam_diff_elecposi_without_Dalitz[i])->
      ProjectionX(without_Dalitz);

    elecposigam_with_Dalitz_one_dim[i]->Rebin(5);
    elecposigam_without_Dalitz_one_dim[i]->Rebin(5);
    
    ratio_elecposigam[i] = (TH1D*)elecposigam_without_Dalitz_one_dim[i]->Clone();
    ratio_elecposigam[i]->Divide(elecposigam_with_Dalitz_one_dim[i]);
    ratio_elecposigam[i]->SetAxisRange(0., 1.29, "Y");

    
  
  }

  for (int i = 0; i < 6; i++){
    compare_elecposigam->cd(i + 1);

    elecposigam_with_Dalitz_one_dim[i]->SetLineColor(kBlue); 
    elecposigam_without_Dalitz_one_dim[i]->SetLineColor(kRed);

    elecposigam_with_Dalitz_one_dim[i]->Draw();
    elecposigam_without_Dalitz_one_dim[i]->Draw("same");

    
    ratio_elecposigam_c->cd(i + 1);
    ratio_elecposigam[i]->Draw("he");
    
    
  }

  compare_elecposi->Print("compare_elecposi.pdf");
  ratio_elecposi_c->Print("ratio_elecposi.pdf");
  compare_elecposigam->Print("compare_elecposigam.pdf");
  ratio_elecposigam_c->Print("ratio_elecposigam.pdf");

  return;
}
