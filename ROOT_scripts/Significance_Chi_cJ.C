Double_t Gaus3Sum(Double_t*, Double_t*);

void Significance_Chi_cJ(){

  /* 
     
     This ROOT script is created to find chi_cJ significance. For that, we do:

     1. Declare  input data files (Signal data -- Pythia8 Charmonium::all
     configuration, Background data -- Pythia8 SoftQCD configuration).
     2. Take from input data Invariant Mass Spectrum of M(e+ e- gamma) - 
     - M(e+ e-).
     3. Take statistic information from Input data: process cross section and
     number of generated events with numer of root files.
     4. Prepare cross section converting: count 2 scale factors to count 
     number of particle in both histograms.
     5. Prepare 2-dimensional invariant mass speectrum transvers momentum 
     slices.
     6. Fit signal data with 3 Gausian summ function to get chi_c0, chi_c1 and 
     chi_c2 peaks parametrs. (We need do that to separate statistics for 
     different chi_cJ particles. Firstly, we need to create new hist arrays. New
     hists will be contain from different pT integraed projection).
     7. Count numericaly integral under peaks on signal histograms to find 
     number of each particle chi_cJ depence of transverse momentum.
     8. Count numericaly integral under background function on background 
     histograms to find number of all particle in mass intervals depence of 
     transverse momentum.
     9. Find chi_cJ significance with using next equation:
     
     sign_{chi_{cJ}} = \frac{eff * N_{chi_{cJ}, signal}}
                            {\sqrt{eff * N_{signal + backgr}}}

     10. Create histograms with depence sign_{chi_{cJ}} from transverse 
     momentum of chi_{cJ}. 
     11. Count Differential cross section.
     12. Create output root file.
     13. Write all results in output file.
     
  */

  
  // 1.------------------------------------------------------------------------

  TFile* Signal_file = new TFile("Chi_cJ_signal_data.root");
  TFile* Backgr_file = new TFile("Chi_cJ_background_data.root");

  // 2.------------------------------------------------------------------------

  TH2F* signal_data_histograms[3];
  TH2F* backgr_data_histograms[3];


  for (int i = 0; i < 3; i++){
    
    TString signal_hist_name = 
      Form("hMassElecPosiGam_diff_ElecPosi_ALICE3_p%d_from_chi_c", i + 1);
    TString backgr_hist_name = 
      Form("hMassElecPosiGam_diff_ElecPosi_ALICE3_p%d_from_backg", i + 1);
    
    signal_data_histograms[i] = 
      (TH2F*)Signal_file->Get(signal_hist_name.Data());
    backgr_data_histograms[i] = 
      (TH2F*)Backgr_file->Get(backgr_hist_name.Data());

  }

  // 3.------------------------------------------------------------------------

  TH1F* Statistic_data[2];

  Statistic_data[0] = (TH1F*)Signal_file->Get("hCross_section_hist");
  Statistic_data[1] = (TH1F*)Backgr_file->Get("hCross_section_hist");

  // 4.------------------------------------------------------------------------

  double N_events_signal;
  double N_events_backgr;
  
  double X_section_signal;
  double X_section_backgr;
  
  double N_files_signal;
  double N_files_backgr;

  N_events_signal = Statistic_data[0]->GetBinContent(2);
  N_events_backgr = Statistic_data[1]->GetBinContent(2);

  X_section_signal = Statistic_data[0]->GetBinContent(1);
  X_section_backgr = Statistic_data[1]->GetBinContent(1);
  
  N_files_signal = Statistic_data[0]->GetEntries();
  N_files_backgr = Statistic_data[1]->GetEntries();

  //     TEST PRINTING     //
  
  
  printf("N_events_signal = %9.0f; N_events_backgr = %9.0f\n", 
	 N_events_signal, N_events_backgr);
  printf("X_section_signal = %9.4f; X_section_backgr = %9.4f\n", 
	 X_section_signal, X_section_backgr);
  printf("N_files_signal = %9.0f; N_files_backgr = %9.0f\n", 
	 N_files_signal, N_files_backgr);
  

  double Luminocity = 3.; // Integral luminocity in (pbarn)^{-1}
  
  double scale_factor_signal;
  double scale_factor_backgr;

  double complex_registration_efficiency;
  
  complex_registration_efficiency = 1.;
  
  scale_factor_signal = 
    ((X_section_signal/N_files_signal)/(N_events_signal/2)) * 
    (1.e12 * Luminocity * complex_registration_efficiency);
  scale_factor_backgr = 
    ((X_section_backgr/N_files_backgr)/(N_events_backgr/2)) * 
    (1.e12 * Luminocity * complex_registration_efficiency);

  //     TEST PRINTING     //
  
  
  printf("scale_factor_signal = %9.3f; scale_factor_backgr = %9.3f\n", 
	 scale_factor_signal, scale_factor_backgr);
    
  for (int i = 0; i< 3; i++){
    signal_data_histograms[i]->Scale(scale_factor_signal);
    backgr_data_histograms[i]->Scale(scale_factor_backgr);
  }
  

  // 5.------------------------------------------------------------------------

  TH1D* signal_hist_slices[3][50];
  TH1D* backgr_hist_slices[3][50];

  const int number_bins = 28;

  int edges[number_bins + 1] = 
    {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 
     11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 
     21, 22, 23, 24, 25, 26, 31, 41, 51};

  //    TEST PRINT     //

  for (i = 0; i< number_bins; i++){
    printf("(%d, %d)\n", edges[i], edges[i + 1] - 1);
  }  

  for (int i = 0; i < 3; i++){
    for (int j = 0; j < number_bins; j++){
      
      TString signal_hist_slices_name;
      TString backgr_hist_slices_name;

      signal_hist_slices_name = 
	Form("Signal_ALICE3_p%d_inv_mass_spectrum_slice_pT_%d_%d", 
	     i + 1, 
	     edges[j], 
	     edges[j + 1]);
      backgr_hist_slices_name = 
	Form("Backgr_ALICE3_p%d_inv_mass_spectrum_slice_pT_%d_%d", 
	     i + 1, 
	     edges[j], 
	     edges[j + 1]);

      signal_hist_slices[i][j] = (TH1D*)signal_data_histograms[i]->
	ProjectionX(signal_hist_slices_name.Data(),
		    edges[j], 
		    edges[j + 1] - 1);
      backgr_hist_slices[i][j] = (TH1D*)backgr_data_histograms[i]->
	ProjectionX(backgr_hist_slices_name.Data(),
		    edges[j], 
		    edges[j + 1] - 1);
      
    }
  }

  // 6.------------------------------------------------------------------------

  double M_min = 0.25;
  double M_max = 0.53;

  double particle_amplitude_data[9][number_bins];  
  double particle_mass_data[9][number_bins];  
  double particle_sigma_data[9][number_bins];

  TF1 *fGaus3Sum = 
    new TF1("fGaus3Sum",Gaus3Sum,M_min,M_max,9);

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

  fGaus3Sum->SetParLimits(1,0.313,0.318);
  fGaus3Sum->SetParLimits(4,0.408,0.418);
  fGaus3Sum->SetParLimits(7,0.455,0.465);

  fGaus3Sum->SetParLimits(0,0.,1.e9);
  fGaus3Sum->SetParLimits(3,0.,1.e9);
  fGaus3Sum->SetParLimits(6,0.,1.e9);

  fGaus3Sum->SetParLimits(2,1.e-3,1.);
  fGaus3Sum->SetParLimits(5,1.e-3,1.);
  fGaus3Sum->SetParLimits(8,1.e-3,1.);

  //      TEST FIT     //

  /*TCanvas* canv_p1 = new TCanvas("canv_p1", "canv_p1");
  TCanvas* canv_p2 = new TCanvas("canv_p2", "canv_p2");
  TCanvas* canv_p3 = new TCanvas("canv_p3", "canv_p3");

  canv_p1->Divide(6, 6);
  canv_p2->Divide(6, 6);
  canv_p3->Divide(6, 6);*/

  for (int i = 0; i < number_bins; i++){
    signal_hist_slices[0][i]->Fit(fGaus3Sum, "", "", M_min, M_max);
    
    particle_amplitude_data[0][i] = fGaus3Sum->GetParameter(0);
    particle_mass_data[0][i] = fGaus3Sum->GetParameter(1);
    particle_sigma_data[0][i] = fGaus3Sum->GetParameter(2);
    
    particle_amplitude_data[1][i] = fGaus3Sum->GetParameter(3);
    particle_mass_data[1][i] = fGaus3Sum->GetParameter(4);
    particle_sigma_data[1][i] = fGaus3Sum->GetParameter(5);
    
    particle_amplitude_data[2][i] = fGaus3Sum->GetParameter(6);
    particle_mass_data[2][i] = fGaus3Sum->GetParameter(7);
    particle_sigma_data[2][i] = fGaus3Sum->GetParameter(8);
    
    signal_hist_slices[1][i]->Fit(fGaus3Sum, "", "", M_min, M_max);
    
    particle_amplitude_data[3][i] = fGaus3Sum->GetParameter(0);
    particle_mass_data[3][i] = fGaus3Sum->GetParameter(1);
    particle_sigma_data[3][i] = fGaus3Sum->GetParameter(2);
    
    particle_amplitude_data[4][i] = fGaus3Sum->GetParameter(3);
    particle_mass_data[4][i] = fGaus3Sum->GetParameter(4);
    particle_sigma_data[4][i] = fGaus3Sum->GetParameter(5);
    
    particle_amplitude_data[5][i] = fGaus3Sum->GetParameter(6);
    particle_mass_data[5][i] = fGaus3Sum->GetParameter(7);
    particle_sigma_data[5][i] = fGaus3Sum->GetParameter(8);
    
    signal_hist_slices[2][i]->Fit(fGaus3Sum, "", "", M_min, M_max);
    
    particle_amplitude_data[6][i] = fGaus3Sum->GetParameter(0);
    particle_mass_data[6][i] = fGaus3Sum->GetParameter(1);
    particle_sigma_data[6][i] = fGaus3Sum->GetParameter(2);
    
    particle_amplitude_data[7][i] = fGaus3Sum->GetParameter(3);
    particle_mass_data[7][i] = fGaus3Sum->GetParameter(4);
    particle_sigma_data[7][i] = fGaus3Sum->GetParameter(5);
    
    particle_amplitude_data[8][i] = fGaus3Sum->GetParameter(6);
    particle_mass_data[8][i] = fGaus3Sum->GetParameter(7);
    particle_sigma_data[8][i] = fGaus3Sum->GetParameter(8);

    //     TEST PRINT     //
    
    printf("\nALICE3 p1: chi_c0: (%8.3f, %8.3f, %8.3f)\n",
	   particle_amplitude_data[0][i],
	   particle_mass_data[0][i],
	   particle_sigma_data[0][i]);
    printf("           chi_c1: (%8.3f, %8.3f, %8.3f)\n",
	   particle_amplitude_data[1][i],
	   particle_mass_data[1][i],
	   particle_sigma_data[1][i]);
    printf("           chi_c2: (%8.3f, %8.3f, %8.3f)\n",
	   particle_amplitude_data[2][i],
	   particle_mass_data[2][i],
	   particle_sigma_data[2][i]);
    printf("\n\n\nALICE3 p2: chi_c0: (%8.3f, %8.3f, %8.3f)\n",
	   particle_amplitude_data[3][i],
	   particle_mass_data[3][i],
	   particle_sigma_data[3][i]);
    printf("           chi_c1: (%8.3f, %8.3f, %8.3f)\n",
	   particle_amplitude_data[4][i],
	   particle_mass_data[4][i],
	   particle_sigma_data[4][i]);
    printf("           chi_c2: (%8.3f, %8.3f, %8.3f)\n",
	   particle_amplitude_data[5][i],
	   particle_mass_data[5][i],
	   particle_sigma_data[5][i]);
    printf("\n\n\nALICE3 p3: chi_c0: (%8.3f, %8.3f, %8.3f)\n",
	   particle_amplitude_data[6][i],
	   particle_mass_data[6][i],
	   particle_sigma_data[6][i]);
    printf("           chi_c1: (%8.3f, %8.3f, %8.3f)\n",
	   particle_amplitude_data[7][i],
	   particle_mass_data[7][i],
	   particle_sigma_data[7][i]);
    printf("           chi_c2: (%8.3f, %8.3f, %8.3f)\n",
	   particle_amplitude_data[8][i],
	   particle_mass_data[8][i],
	   particle_sigma_data[8][i]);

  }

  // 7.------------------------------------------------------------------------

  double Number_of_signal_particle[9][number_bins];

  double dM = backgr_hist_slices[0][0]->GetBinWidth(1);

  //     INFO PRINT     //
  
  printf("%45s", " ALICE3 par_1 ");
  printf("%45s", " ALICE3 par_2 ");
  printf("%45s", " ALICE3 par_3 ");
  printf("\n");
  printf("%15s", " chi_c0 ");
  printf("%15s", " chi_c1 ");
  printf("%15s", " chi_c2 ");
  printf("%15s", " chi_c0 ");
  printf("%15s", " chi_c1 ");
  printf("%15s", " chi_c2 ");
  printf("%15s", " chi_c0 ");
  printf("%15s", " chi_c1 ");
  printf("%15s", " chi_c2 ");
  printf("\n");
  for (int i = 0; i < number_bins; i++){
    for (int j = 0; j < 9; j++){
      Number_of_signal_particle[j][i] = 
	TMath::Sqrt(TMath::TwoPi()) * particle_amplitude_data[j][i] * 
	particle_sigma_data[j][i]/dM;
      printf("%15.4f", Number_of_signal_particle[j][i]);
    }
    printf("\n");
  }


  // 8.------------------------------------------------------------------------
  
  int mass_interval_boarder[9][2 * number_bins];
  double Number_of_backgr_particle[9][number_bins];
  
  for (int i = 0; i < number_bins; i++){
    for (int j = 0; j < 3; j++){
      
      mass_interval_boarder[3 * j + 0][2 * i + 0] = backgr_hist_slices[j][i]->
	FindBin(particle_mass_data[3 * j + 0][i] - 
		3 * particle_sigma_data[3 * j + 0][i] - 0.0001);
   
      mass_interval_boarder[3 * j + 0][2 * i + 1] = backgr_hist_slices[j][i]->
	FindBin(particle_mass_data[3 * j + 0][i] + 
		3 * particle_sigma_data[3 * j + 0][i] + 0.0001);
      
      mass_interval_boarder[3 * j + 1][2 * i + 0] = backgr_hist_slices[j][i]->
	FindBin(particle_mass_data[3 * j + 1][i] - 
		3 * particle_sigma_data[3 * j + 1][i] - 0.0001);
      mass_interval_boarder[3 * j + 1][2 * i + 1] = backgr_hist_slices[j][i]->
	FindBin(particle_mass_data[3 * j + 1][i] + 
		3 * particle_sigma_data[3 * j + 1][i] + 0.0001);
      
      mass_interval_boarder[3 * j + 2][2 * i + 0] = backgr_hist_slices[j][i]->
	FindBin(particle_mass_data[3 * j + 2][i] - 
		3 * particle_sigma_data[3 * j + 2][i] - 0.0001);
      mass_interval_boarder[3 * j + 2][2 * i + 1] = backgr_hist_slices[j][i]->
	FindBin(particle_mass_data[3 * j + 2][i] + 
		3 * particle_sigma_data[3 * j + 2][i] + 0.0001);

      Number_of_backgr_particle[3 * j + 0][i] = backgr_hist_slices[j][i]->
	Integral(mass_interval_boarder[3 * j + 0][2 * i + 0],
		 mass_interval_boarder[3 * j + 0][2 * i + 1]);
      
      Number_of_backgr_particle[3 * j + 1][i] = backgr_hist_slices[j][i]->
	Integral(mass_interval_boarder[3 * j + 1][2 * i + 0],
		 mass_interval_boarder[3 * j + 1][2 * i + 1]);
      
      Number_of_backgr_particle[3 * j + 2][i] = backgr_hist_slices[j][i]->
	Integral(mass_interval_boarder[3 * j + 2][2 * i + 0],
		 mass_interval_boarder[3 * j + 2][2 * i + 1]);
      
      //     TEST PRINT     //

      printf("(%3d, %3d); (%3d, %3d); (%3d, %3d)\n",
	     mass_interval_boarder[3 * j + 0][2 * i + 0],
	     mass_interval_boarder[3 * j + 0][2 * i + 1],
	     mass_interval_boarder[3 * j + 1][2 * i + 0],
	     mass_interval_boarder[3 * j + 1][2 * i + 1],
	     mass_interval_boarder[3 * j + 2][2 * i + 0],
	     mass_interval_boarder[3 * j + 2][2 * i + 1]);
    }
  }
  
  //     INFO PRINT     //
  
  printf("%45s", " ALICE3 par_1 ");
  printf("%45s", " ALICE3 par_2 ");
  printf("%45s", " ALICE3 par_3 ");
  printf("\n");
  printf("%15s", " chi_c0 ");
  printf("%15s", " chi_c1 ");
  printf("%15s", " chi_c2 ");
  printf("%15s", " chi_c0 ");
  printf("%15s", " chi_c1 ");
  printf("%15s", " chi_c2 ");
  printf("%15s", " chi_c0 ");
  printf("%15s", " chi_c1 ");
  printf("%15s", " chi_c2 ");
  printf("\n");
  for (int i = 0; i < number_bins; i++){
    for (int j = 0; j < 9; j++){
      printf("%15.4f", Number_of_backgr_particle[j][i]);
    }
    printf("\n");
  }


  // 9.------------------------------------------------------------------------

  double chi_cJ_significance[9][number_bins];

  for (int i = 0; i < number_bins; i++){
    for (int j = 0; j < 9; j++){
      chi_cJ_significance[j][i] = (Number_of_signal_particle[j][i])/
	(TMath::Sqrt(Number_of_backgr_particle[j][i] + 
		     Number_of_signal_particle[j][i]));
    }
  }

  

  // 10.-----------------------------------------------------------------------

  TH1D* chi_cJ_significance_hist[9];

  TCanvas* Significance_chicJ_canv = new TCanvas("Significance_chicJ_canv", 
						 "Significance_chicJ_canv");

  double edges_h[number_bins + 1] =
    {0., 1., 2., 3., 4., 5., 6., 7., 8., 9., 10.,
     11., 12., 13., 14., 15., 16., 17., 18., 19.,
     20., 21., 22., 23., 24., 25., 30., 40., 50.};

  Significance_chicJ_canv->Divide(3, 3);
  for (int i = 0; i < 3; i++){
    TString name_0 = Form("chi_c%d_significance_dep_from_pT_for_ALICE3_par%d", 
			  0, i + 1);
    TString name_1 = Form("chi_c%d_significance_dep_from_pT_for_ALICE3_par%d", 
			  1, i + 1);
    TString name_2 = Form("chi_c%d_significance_dep_from_pT_for_ALICE3_par%d", 
			  2, i + 1);
    TString title_0 = Form("chi_c%d_significance_dep_from_pT_for_ALICE3_par%d", 
			  0, i + 1);
    TString title_1 = Form("chi_c%d_significance_dep_from_pT_for_ALICE3_par%d", 
			  1, i + 1);
    TString title_2 = Form("chi_c%d_significance_dep_from_pT_for_ALICE3_par%d", 
			  2, i + 1);


    chi_cJ_significance_hist[3 * i + 0] = 
      new TH1D(name_0.Data(), title_0.Data(), number_bins, edges_h);
    chi_cJ_significance_hist[3 * i + 1] = 
      new TH1D(name_1.Data(), title_1.Data(), number_bins, edges_h);
    chi_cJ_significance_hist[3 * i + 2] = 
      new TH1D(name_2.Data(), title_2.Data(), number_bins, edges_h);
    
    chi_cJ_significance_hist[3 * i + 0]->SetXTitle("p_{T} #chi_{cJ}, (GeV/c)");
    chi_cJ_significance_hist[3 * i + 1]->SetXTitle("p_{T} #chi_{cJ}, (GeV/c)");
    chi_cJ_significance_hist[3 * i + 2]->SetXTitle("p_{T} #chi_{cJ}, (GeV/c)");
    
    for (int j = 0; j < number_bins; j++){
      chi_cJ_significance_hist[3 * i + 0]->
	SetBinContent(j + 1, chi_cJ_significance[3 * i + 0][j]);
      chi_cJ_significance_hist[3 * i + 1]->
	SetBinContent(j + 1, chi_cJ_significance[3 * i + 1][j]);
      chi_cJ_significance_hist[3 * i + 2]->
	SetBinContent(j + 1, chi_cJ_significance[3 * i + 2][j]);
    }

    for (int j = 0; j < number_bins; j++){
      chi_cJ_significance_hist[3 * i + 0]->SetLineColor(kRed);
      chi_cJ_significance_hist[3 * i + 1]->SetLineColor(kBlue);
      chi_cJ_significance_hist[3 * i + 2]->SetLineColor(kGreen);
    }
  }

  
  for (int i = 0; i < 9; i++){
    Significance_chicJ_canv->cd(i + 1);
    gPad->SetLogy();
    gStyle->SetOptStat(0);
    chi_cJ_significance_hist[i]->Draw();
  }

  TCanvas* ALICE3_compare_sign_par1 = new TCanvas("ALICE3_compare_sign_par1", 
						  "ALICE3_compare_sign_par1");
  TCanvas* ALICE3_compare_sign_par2 = new TCanvas("ALICE3_compare_sign_par2", 
						  "ALICE3_compare_sign_par2");
  TCanvas* ALICE3_compare_sign_par3 = new TCanvas("ALICE3_compare_sign_par3", 
						  "ALICE3_compare_sign_par3");
  

  ALICE3_compare_sign_par1->cd();
  gPad->SetGrid();
  gPad->SetLogy();  
  gStyle->SetOptStat(0);
  TLegend *legend_p1 = new TLegend(0.8,0.7,0.89,0.89);
  legend_p1->SetBorderSize(0);
  legend_p1->AddEntry(chi_cJ_significance_hist[2],"#chi_{c2}","lp");
  legend_p1->AddEntry(chi_cJ_significance_hist[0],"#chi_{c0}","lp");
  legend_p1->AddEntry(chi_cJ_significance_hist[1],"#chi_{c1}","lp");
  chi_cJ_significance_hist[2]->SetAxisRange(0.8e-1, 1.e5, "Y");
  chi_cJ_significance_hist[2]->Draw();
  chi_cJ_significance_hist[0]->Draw("same");
  chi_cJ_significance_hist[1]->Draw("same");
  legend_p1->Draw("same");
  
  ALICE3_compare_sign_par2->cd();
  gPad->SetGrid();
  gPad->SetLogy();
  gStyle->SetOptStat(0);
  TLegend *legend_p2 = new TLegend(0.8,0.7,0.89,0.89);
  legend_p2->SetBorderSize(0);
  legend_p2->AddEntry(chi_cJ_significance_hist[5],"#chi_{c2}","lp");
  legend_p2->AddEntry(chi_cJ_significance_hist[3],"#chi_{c0}","lp");
  legend_p2->AddEntry(chi_cJ_significance_hist[4],"#chi_{c1}","lp");
  chi_cJ_significance_hist[5]->SetAxisRange(0.8e-1, 1.e5, "Y");
  chi_cJ_significance_hist[5]->Draw();
  chi_cJ_significance_hist[3]->Draw("same");
  chi_cJ_significance_hist[4]->Draw("same");
  legend_p2->Draw("same");
  
  ALICE3_compare_sign_par3->cd();
  gPad->SetGrid();
  gPad->SetLogy();
  gStyle->SetOptStat(0);
  TLegend *legend_p3 = new TLegend(0.8,0.7,0.89,0.89);
  legend_p3->SetBorderSize(0);
  legend_p3->AddEntry(chi_cJ_significance_hist[8],"#chi_{c2}","lp");
  legend_p3->AddEntry(chi_cJ_significance_hist[6],"#chi_{c0}","lp");
  legend_p3->AddEntry(chi_cJ_significance_hist[7],"#chi_{c1}","lp");
  chi_cJ_significance_hist[8]->SetAxisRange(0.8e-1, 1.e5, "Y");
  chi_cJ_significance_hist[8]->Draw();
  chi_cJ_significance_hist[6]->Draw("same");
  chi_cJ_significance_hist[7]->Draw("same");
  legend_p3->Draw("same");

  
  // 11.-----------------------------------------------------------------------

  TH1D* differential_cross_section_hist[9];
  
  TString hist_name;
  TString hist_titl;
  
  for (int i = 0; i < 3; i++){
    for (int j = 0; j < 3; j++){
      hist_name = Form("Differential_cross_section_chi_c%d_ALICE_p%d",
		       i, j + 1);
      hist_titl = Form("Differential_cross_section_chi_c%d_ALICE_p%d",
			       i, j + 1);
      differential_cross_section_hist[3 * j + i] = new TH1D(hist_name.Data(),
							    hist_titl.Data(),
							    number_bins,
							    edges_h);
    
      
      printf("%d, %d\n", i, j);
    }
  }

  // 12.-----------------------------------------------------------------------
  
  for (int j = 0; j < 9; j++){
    double dcs;
    for (int k = 0; k < number_bins; k++){
      dcs = Number_of_signal_particle[j][k]/((Luminocity) *
					     (edges_h[k + 1] - 
					      edges_h[k]));
      printf("%20.20f\n", dcs);
      //differential_cross_section_hist[3 * j]->SetBinContent(k + 1, k);
      differential_cross_section_hist[j]->SetBinContent(k + 1, dcs);
      differential_cross_section_hist[j]->
	SetXTitle("p_{T} #chi_{cJ}, (GeV/c)");
      differential_cross_section_hist[j]->
	SetYTitle("d#sigma/dp_{T}, pb/(GeV/c)");
    }
  }

  TCanvas* ALICE3_compare_dcs_par1 = new TCanvas("ALICE3_compare_dcs_par1", 
						 "ALICE3_compare_dcs_par1");
  TCanvas* ALICE3_compare_dcs_par2 = new TCanvas("ALICE3_compare_dcs_par2", 
						 "ALICE3_compare_dcs_par2");
  TCanvas* ALICE3_compare_dcs_par3 = new TCanvas("ALICE3_compare_dcs_par3", 
						 "ALICE3_compare_dcs_par3");
  
  
  ALICE3_compare_dcs_par1->cd();
  gPad->SetGrid();
  gPad->SetLogy();  
  gStyle->SetOptStat(0);
  TLegend *legend_p11 = new TLegend(0.8,0.7,0.89,0.89);
  legend_p11->SetBorderSize(0);
  differential_cross_section_hist[2]->SetLineColor(kRed);
  differential_cross_section_hist[0]->SetLineColor(kBlue);
  differential_cross_section_hist[1]->SetLineColor(kGreen);
  legend_p11->AddEntry(differential_cross_section_hist[2],"#chi_{c2}","lp");
  legend_p11->AddEntry(differential_cross_section_hist[0],"#chi_{c0}","lp");
  legend_p11->AddEntry(differential_cross_section_hist[1],"#chi_{c1}","lp");
  differential_cross_section_hist[2]->Draw();
  differential_cross_section_hist[0]->Draw("same");
  differential_cross_section_hist[1]->Draw("same");
  legend_p11->Draw("same");
  
  ALICE3_compare_dcs_par2->cd();
  gPad->SetGrid();
  gPad->SetLogy();
  gStyle->SetOptStat(0);
  TLegend *legend_p22 = new TLegend(0.8,0.7,0.89,0.89);
  legend_p22->SetBorderSize(0);
  differential_cross_section_hist[5]->SetLineColor(kRed);
  differential_cross_section_hist[3]->SetLineColor(kBlue);
  differential_cross_section_hist[4]->SetLineColor(kGreen);
  legend_p22->AddEntry(differential_cross_section_hist[5],"#chi_{c2}","lp");
  legend_p22->AddEntry(differential_cross_section_hist[3],"#chi_{c0}","lp");
  legend_p22->AddEntry(differential_cross_section_hist[4],"#chi_{c1}","lp");
  differential_cross_section_hist[5]->Draw();
  differential_cross_section_hist[3]->Draw("same");
  differential_cross_section_hist[4]->Draw("same");
  legend_p22->Draw("same");
  
  ALICE3_compare_dcs_par3->cd();
  gPad->SetGrid();
  gPad->SetLogy();
  gStyle->SetOptStat(0);
  TLegend *legend_p33 = new TLegend(0.8,0.7,0.89,0.89);
  legend_p33->SetBorderSize(0);
  differential_cross_section_hist[8]->SetLineColor(kRed);
  differential_cross_section_hist[6]->SetLineColor(kBlue);
  differential_cross_section_hist[7]->SetLineColor(kGreen);
  legend_p33->AddEntry(differential_cross_section_hist[8],"#chi_{c2}","lp");
  legend_p33->AddEntry(differential_cross_section_hist[6],"#chi_{c0}","lp");
  legend_p33->AddEntry(differential_cross_section_hist[7],"#chi_{c1}","lp");
  differential_cross_section_hist[8]->Draw();
  differential_cross_section_hist[6]->Draw("same");
  differential_cross_section_hist[7]->Draw("same");
  legend_p33->Draw("same");

  
  // 13.-----------------------------------------------------------------------


  TFile* outfile = new TFile("Chi_cJ_significance_output.root", "RECREATE");


  // 14.-----------------------------------------------------------------------

    
  for (int i = 0; i < 3; i++){
    signal_data_histograms[i]->Write();
  }
  
  for (int i = 0; i < 3; i++){
    backgr_data_histograms[i]->Write();
  }
  
  for (int i = 0; i < 3; i++){
    for (int j = 0; j < number_bins; j++){
      signal_hist_slices[i][j]->Write();      
    }
  }
  
  for (int i = 0; i < 3; i++){
    for (int j = 0; j < number_bins; j++){
      backgr_hist_slices[i][j]->Write();
    }
  }

  for (int i = 0; i < 9; i++){
    chi_cJ_significance_hist[i]->Write();
  }

  for (int i = 0; i < 9; i++){
    differential_cross_section_hist[i]->Write();
  }
  
  Significance_chicJ_canv->Print("Significance_chicJ_general_plot.pdf");
  ALICE3_compare_sign_par1->Print("Significance_chicJ_ALICE3_par_1.pdf");
  ALICE3_compare_sign_par2->Print("Significance_chicJ_ALICE3_par_2.pdf");
  ALICE3_compare_sign_par3->Print("Significance_chicJ_ALICE3_par_3.pdf");
  ALICE3_compare_dcs_par1->Print("Diff_cross_section_chicJ_ALICE3_par_1.pdf");
  ALICE3_compare_dcs_par2->Print("Diff_cross_section_chicJ_ALICE3_par_2.pdf");
  ALICE3_compare_dcs_par3->Print("Diff_cross_section_chicJ_ALICE3_par_3.pdf");
  
  return;
}

//-----------------------------------------------------------------------------

// Describe fit function:

Double_t Gaus3Sum(Double_t *x, Double_t *p){
  
  Double_t dM1 = (x[0]-p[1])/p[2];
  Double_t y1  = p[0]*exp(-dM1*dM1/2.);

  Double_t dM2 = (x[0]-p[4])/p[5];
  Double_t y2  = p[3]*exp(-dM2*dM2/2.);

  Double_t dM3 = (x[0]-p[7])/p[8];
  Double_t y3  = p[6]*exp(-dM3*dM3/2.);
  
  return y1+y2+y3;
}
