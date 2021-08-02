#include "TH1.h"
#include "TH2.h"
#include "TFile.h"


void ROOT_file_creator(TH2F** hChi_c_pt_y, 
		       TH2F** hChi_c_electron_pt_y, 
		       TH2F** hChi_c_positron_pt_y, 
		       TH2F** hChi_c_gamma_pt_y, 
		       TH2F** hChi_c_pt_y_cndtn_1,
		       TH2F** hChi_c_electron_pt_y_cndtn_1,
		       TH2F** hChi_c_positron_pt_y_cndtn_1, 
		       TH2F** hChi_c_gamma_pt_y_cndtn_1, 
		       TH2F** hChi_c_pt_y_cndtn_2, 
		       TH2F** hChi_c_electron_pt_y_cndtn_2,
		       TH2F** hChi_c_positron_pt_y_cndtn_2, 
		       TH2F** hChi_c_gamma_pt_y_cndtn_2, 
		       TH2F** hChi_c_pt_y_cndtn_3, 
		       TH2F** hChi_c_electron_pt_y_cndtn_3, 
		       TH2F** hChi_c_positron_pt_y_cndtn_3,
		       TH2F** hChi_c_gamma_pt_y_cndtn_3, 
		       TH2F** hChi_c_pt_y_cndtn_4, 
		       TH2F** hChi_c_electron_pt_y_cndtn_4, 
		       TH2F** hChi_c_positron_pt_y_cndtn_4, 
		       TH2F** hChi_c_gamma_pt_y_cndtn_4,
		       TH2F** hElectron_pt_y_event,
		       TH2F** hPositron_pt_y_event,
		       TH2F** hGamma_pt_y_event,
		       TH2F** hMassElecPosiGam_diff_ElecPosi_from_chi_c,
		       TH2F** hMassElecPosiGam_diff_ElecPosi_from_backg,
		       TH2F** hMassElecPosi_from_Jpsi,
		       TH2F** hMassElecPosi_from_cand,
		       TH2F** hMassElecPosi_from_even,
		       TH2F** hJpsi_from_chic,
		       TH2F** hJpsi_from_cand,
		       TH1F* hCross_section_hist){

//Save histogram on file and close file.
  char fn[1024];
  sprintf(fn, "%s", "pythia_chic2.root");
  TFile* outFile = new TFile(fn, "RECREATE");


  for (int i = 0; i < 4; i++){
    hChi_c_pt_y[i]                                                    ->Write();
    hChi_c_electron_pt_y[i]                                           ->Write();
    hChi_c_positron_pt_y[i]                                           ->Write();
    hChi_c_gamma_pt_y[i]                                              ->Write();
  }

  for (int i = 0; i < 4; i++){
    hChi_c_pt_y_cndtn_1[i]                                            ->Write();
    hChi_c_electron_pt_y_cndtn_1[i]                                   ->Write();
    hChi_c_positron_pt_y_cndtn_1[i]                                   ->Write();
    hChi_c_gamma_pt_y_cndtn_1[i]                                      ->Write();
  }

  for (int i = 0; i < 4; i++){
    hChi_c_pt_y_cndtn_2[i]                                            ->Write();
    hChi_c_electron_pt_y_cndtn_2[i]                                   ->Write();
    hChi_c_positron_pt_y_cndtn_2[i]                                   ->Write();
    hChi_c_gamma_pt_y_cndtn_2[i]                                      ->Write();
  }

  for (int i = 0; i < 4; i++){
    hChi_c_pt_y_cndtn_3[i]                                            ->Write();
    hChi_c_electron_pt_y_cndtn_3[i]                                   ->Write();
    hChi_c_positron_pt_y_cndtn_3[i]                                   ->Write();
    hChi_c_gamma_pt_y_cndtn_3[i]                                      ->Write();
  }

  for (int i = 0; i < 4; i++){
    hChi_c_pt_y_cndtn_4[i]                                            ->Write();
    hChi_c_electron_pt_y_cndtn_4[i]                                   ->Write();
    hChi_c_positron_pt_y_cndtn_4[i]                                   ->Write();
    hChi_c_gamma_pt_y_cndtn_4[i]                                      ->Write();
  }

  for (int i = 0; i < 6; i++){
    hElectron_pt_y_event[i]                                           ->Write();
    hPositron_pt_y_event[i]                                           ->Write();
    hGamma_pt_y_event[i]                                              ->Write();
  }
  
  for (int i = 0; i < 6; i++){
    hMassElecPosiGam_diff_ElecPosi_from_chi_c[i]                      ->Write();
    hMassElecPosiGam_diff_ElecPosi_from_backg[i]                      ->Write();
  }
  
  for (int i = 0; i < 6; i++){
    hMassElecPosi_from_Jpsi[i]                                        ->Write();
  }
  
  for (int i = 0; i < 6; i++){
    hMassElecPosi_from_cand[i]                                        ->Write();
  }
  
  for (int i = 0; i < 6; i++){
    hMassElecPosi_from_even[i]                                        ->Write();
  }

  for (int i = 0; i < 6; i++){
    hJpsi_from_chic[i]                                                ->Write();
  }
  
  for (int i = 0; i < 6; i++){
    hJpsi_from_cand[i]                                                ->Write();
  }
  
  hCross_section_hist                                                 ->Write();

  outFile->Close();
  delete outFile;

  return;
}
