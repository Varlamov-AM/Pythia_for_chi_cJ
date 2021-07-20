#include "TH1.h"
#include "TH2.h"
#include "TFile.h"

void Histogram_creator(TH2F** hChi_c_pt_y, 
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
		       TH2F** hMassElecPosiGam_diff_ElecPosi_from_chi_c,
		       TH2F** hMassElecPosiGam_diff_ElecPosi_from_backg,
		       TH2F** hMassElecPosi_from_Jpsi,
		       TH2F** hMassElecPosi_from_cand,
		       TH2F** hJpsi_from_chic,
		       TH2F** hJpsi_from_cand){
  
  const int nPtBins         = 250;
  const int nyBins          = 16; 
  const int nMBins          = 200;
  const int nPtBins_inv_m   = 50;

  TString name_chi_c_pt_y[4];
  TString title_chi_c_pt_y[4];
  TString name_chi_c_electron_pt_y[4];
  TString title_chi_c_electron_pt_y[4];
  TString name_chi_c_positron_pt_y[4];
  TString title_chi_c_positron_pt_y[4];
  TString name_chi_c_gamma_pt_y[4];
  TString title_chi_c_gamma_pt_y[4];
  

  TString name_chi_c_pt_y_cndtn_1[4];
  TString title_chi_c_pt_y_cndtn_1[4];
  TString name_chi_c_electron_pt_y_cndtn_1[4];
  TString title_chi_c_electron_pt_y_cndtn_1[4];
  TString name_chi_c_positron_pt_y_cndtn_1[4];
  TString title_chi_c_positron_pt_y_cndtn_1[4];
  TString name_chi_c_gamma_pt_y_cndtn_1[4];
  TString title_chi_c_gamma_pt_y_cndtn_1[4];
  
  
  TString name_chi_c_pt_y_cndtn_2[4];
  TString title_chi_c_pt_y_cndtn_2[4];
  TString name_chi_c_electron_pt_y_cndtn_2[4];
  TString title_chi_c_electron_pt_y_cndtn_2[4];
  TString name_chi_c_positron_pt_y_cndtn_2[4];
  TString title_chi_c_positron_pt_y_cndtn_2[4];
  TString name_chi_c_gamma_pt_y_cndtn_2[4];
  TString title_chi_c_gamma_pt_y_cndtn_2[4];
  

  TString name_chi_c_pt_y_cndtn_3[4];
  TString title_chi_c_pt_y_cndtn_3[4];
  TString name_chi_c_electron_pt_y_cndtn_3[4];
  TString title_chi_c_electron_pt_y_cndtn_3[4];
  TString name_chi_c_positron_pt_y_cndtn_3[4];
  TString title_chi_c_positron_pt_y_cndtn_3[4];
  TString name_chi_c_gamma_pt_y_cndtn_3[4];
  TString title_chi_c_gamma_pt_y_cndtn_3[4];
  
  
  TString name_chi_c_pt_y_cndtn_4[4];
  TString title_chi_c_pt_y_cndtn_4[4];
  TString name_chi_c_electron_pt_y_cndtn_4[4];
  TString title_chi_c_electron_pt_y_cndtn_4[4];
  TString name_chi_c_positron_pt_y_cndtn_4[4];
  TString title_chi_c_positron_pt_y_cndtn_4[4];
  TString name_chi_c_gamma_pt_y_cndtn_4[4];
  TString title_chi_c_gamma_pt_y_cndtn_4[4];


  for (int j = 0; j < 4; j++){
    
    name_chi_c_pt_y[j]  = Form("hChi_c%d_pt_y",j);
    title_chi_c_pt_y[j] = Form("d^{2}N_{#chi_{c%d}}/dp_{T}dy", j);
    name_chi_c_electron_pt_y[j] = Form("hChi_c%d_electron_pt_y", j);
    title_chi_c_electron_pt_y[j] = Form("d^{2}N_{e^{-}}/dp_{T}dy");
    name_chi_c_positron_pt_y[j] = Form("hChi_c%d_positron_pt_y", j);
    title_chi_c_positron_pt_y[j] = Form("d^{2}N_{e^{+}}/dp_{T}dy");
    name_chi_c_gamma_pt_y[j] = Form("hChi_c%d_gamma_pt_y", j);
    title_chi_c_gamma_pt_y[j] = Form("d^{2}N_{#gamma}/dp_{T}dy");
    
    name_chi_c_pt_y_cndtn_1[j]  = Form("hChi_c%d_pt_y_cndtn_1",j);
    title_chi_c_pt_y_cndtn_1[j] = Form("d^{2}N_{#chi_{c%d}}/dp_{T}dy", j);
    name_chi_c_electron_pt_y_cndtn_1[j] = 
      Form("hChi_c%d_electron_pt_y_cndtn_1", j);
    title_chi_c_electron_pt_y_cndtn_1[j] = Form("d^{2}N_{e^{-}}/dp_{T}dy");
    name_chi_c_positron_pt_y_cndtn_1[j] = 
      Form("hChi_c%d_positron_pt_y_cndtn_1", j);
    title_chi_c_positron_pt_y_cndtn_1[j] = Form("d^{2}N_{e^{+}}/dp_{T}dy");
    name_chi_c_gamma_pt_y_cndtn_1[j] = 
      Form("hChi_c%d_gamma_pt_y_cndtn_1", j);
    title_chi_c_gamma_pt_y_cndtn_1[j] = Form("d^{2}N_{#gamma}/dp_{T}dy");
    
    name_chi_c_pt_y_cndtn_2[j]  = Form("hChi_c%d_pt_y_cndtn_2",j);
    title_chi_c_pt_y_cndtn_2[j] = Form("d^{2}N_{#chi_{c%d}}/dp_{T}dy", j);
    name_chi_c_electron_pt_y_cndtn_2[j] = 
      Form("hChi_c%d_electron_pt_y_cndtn_2", j);
    title_chi_c_electron_pt_y_cndtn_2[j] = Form("d^{2}N_{e^{-}}/dp_{T}dy");
    name_chi_c_positron_pt_y_cndtn_2[j] = 
      Form("hChi_c%d_positron_pt_y_cndtn_2", j);
    title_chi_c_positron_pt_y_cndtn_2[j] = Form("d^{2}N_{e^{+}}/dp_{T}dy");
    name_chi_c_gamma_pt_y_cndtn_2[j] = 
      Form("hChi_c%d_gamma_pt_y_cndtn_2", j);
    title_chi_c_gamma_pt_y_cndtn_2[j] = Form("d^{2}N_{#gamma}/dp_{T}dy");

    name_chi_c_pt_y_cndtn_3[j]  = Form("hChi_c%d_pt_y_cndtn_3",j);
    title_chi_c_pt_y_cndtn_3[j] = Form("d^{2}N_{#chi_{c%d}}/dp_{T}dy", j);
    name_chi_c_electron_pt_y_cndtn_3[j] = 
      Form("hChi_c%d_electron_pt_y_cndtn_3", j);
    title_chi_c_electron_pt_y_cndtn_3[j] = Form("d^{2}N_{e^{-}}/dp_{T}dy");
    name_chi_c_positron_pt_y_cndtn_3[j] = 
      Form("hChi_c%d_positron_pt_y_cndtn_3", j);
    title_chi_c_positron_pt_y_cndtn_3[j] = Form("d^{2}N_{e^{+}}/dp_{T}dy");
    name_chi_c_gamma_pt_y_cndtn_3[j] = 
      Form("hChi_c%d_gamma_pt_y_cndtn_3", j);
    title_chi_c_gamma_pt_y_cndtn_3[j] = Form("d^{2}N_{#gamma}/dp_{T}dy");
    
    name_chi_c_pt_y_cndtn_4[j]  = Form("hChi_c%d_pt_y_cndtn_4",j);
    title_chi_c_pt_y_cndtn_4[j] = Form("d^{2}N_{#chi_{c%d}}/dp_{T}dy", j);
    name_chi_c_electron_pt_y_cndtn_4[j] = 
      Form("hChi_c%d_electron_pt_y_cndtn_4", j);
    title_chi_c_electron_pt_y_cndtn_4[j] = Form("d^{2}N_{e^{-}}/dp_{T}dy");
    name_chi_c_positron_pt_y_cndtn_4[j] = 
      Form("hChi_c%d_positron_pt_y_cndtn_4", j);
    title_chi_c_positron_pt_y_cndtn_4[j] = Form("d^{2}N_{e^{+}}/dp_{T}dy");
    name_chi_c_gamma_pt_y_cndtn_4[j] = 
      Form("hChi_c%d_gamma_pt_y_cndtn_4", j);
    title_chi_c_gamma_pt_y_cndtn_4[j] = Form("d^{2}N_{#gamma}/dp_{T}dy");
    
    if (j == 3){
      
      name_chi_c_pt_y[j]  = Form("hChi_c_all_pt_y");
      title_chi_c_pt_y[j] = Form("d^{2}N_{#chi_{cJ}}/dp_{T}dy");
      name_chi_c_electron_pt_y[j] = Form("hChi_c_all_electron_pt_y");
      title_chi_c_electron_pt_y[j] = Form("d^{2}N_{e^{-}}/dp_{T}dy");
      name_chi_c_positron_pt_y[j] = Form("hChi_c_all_positron_pt_y");
      title_chi_c_positron_pt_y[j] = Form("d^{2}N_{e^{+}}/dp_{T}dy");
      name_chi_c_gamma_pt_y[j] = Form("hChi_c_all_gamma_pt_y");
      title_chi_c_gamma_pt_y[j] = Form("d^{2}N_{#gamma}/dp_{T}dy");

      name_chi_c_pt_y_cndtn_1[j]  = Form("hChi_c_all_pt_y_cndtn_1");
      title_chi_c_pt_y_cndtn_1[j] = Form("d^{2}N_{#chi_{cJ}}/dp_{T}dy");
      name_chi_c_electron_pt_y_cndtn_1[j] = 
	Form("hChi_c_all_electron_pt_y_cndtn_1");
      title_chi_c_electron_pt_y_cndtn_1[j] = Form("d^{2}N_{e^{-}}/dp_{T}dy");
      name_chi_c_positron_pt_y_cndtn_1[j] = 
	Form("hChi_c_all_positron_pt_y_cndtn_1");
      title_chi_c_positron_pt_y_cndtn_1[j] = Form("d^{2}N_{e^{+}}/dp_{T}dy");
      name_chi_c_gamma_pt_y_cndtn_1[j] = 
	Form("hChi_c_all_gamma_pt_y_cndtn_1");
      title_chi_c_gamma_pt_y_cndtn_1[j] = Form("d^{2}N_{#gamma}/dp_{T}dy");
      
      name_chi_c_pt_y_cndtn_2[j]  = Form("hChi_c_all_pt_y_cndtn_2");
      title_chi_c_pt_y_cndtn_2[j] = Form("d^{2}N_{#chi_{cJ}}/dp_{T}dy");
      name_chi_c_electron_pt_y_cndtn_2[j] = 
	Form("hChi_c_all_electron_pt_y_cndtn_2");
      title_chi_c_electron_pt_y_cndtn_2[j] = Form("d^{2}N_{e^{-}}/dp_{T}dy");
      name_chi_c_positron_pt_y_cndtn_2[j] = 
	Form("hChi_c_all_positron_pt_y_cndtn_2");
      title_chi_c_positron_pt_y_cndtn_2[j] = Form("d^{2}N_{e^{+}}/dp_{T}dy");
      name_chi_c_gamma_pt_y_cndtn_2[j] = 
	Form("hChi_c_all_gamma_pt_y_cndtn_2");
      title_chi_c_gamma_pt_y_cndtn_2[j] = Form("d^{2}N_{#gamma}/dp_{T}dy");

      name_chi_c_pt_y_cndtn_3[j]  = Form("hChi_c_all_pt_y_cndtn_3");
      title_chi_c_pt_y_cndtn_3[j] = Form("d^{2}N_{#chi_{cJ}}/dp_{T}dy");
      name_chi_c_electron_pt_y_cndtn_3[j] = 
	Form("hChi_c_all_electron_pt_y_cndtn_3");
      title_chi_c_electron_pt_y_cndtn_3[j] = Form("d^{2}N_{e^{-}}/dp_{T}dy");
      name_chi_c_positron_pt_y_cndtn_3[j] = 
	Form("hChi_c_all_positron_pt_y_cndtn_3");
      title_chi_c_positron_pt_y_cndtn_3[j] = Form("d^{2}N_{e^{+}}/dp_{T}dy");
      name_chi_c_gamma_pt_y_cndtn_3[j] = 
	Form("hChi_c_all_gamma_pt_y_cndtn_3");
      title_chi_c_gamma_pt_y_cndtn_3[j] = Form("d^{2}N_{#gamma}/dp_{T}dy");

      name_chi_c_pt_y_cndtn_4[j]  = Form("hChi_c_all_pt_y_cndtn_4");
      title_chi_c_pt_y_cndtn_4[j] = Form("d^{2}N_{#chi_{cJ}}/dp_{T}dy");
      name_chi_c_electron_pt_y_cndtn_4[j] = 
	Form("hChi_c_all_electron_pt_y_cndtn_4");
      title_chi_c_electron_pt_y_cndtn_4[j] = Form("d^{2}N_{e^{-}}/dp_{T}dy");
      name_chi_c_positron_pt_y_cndtn_4[j] = 
	Form("hChi_c_all_positron_pt_y_cndtn_4");
      title_chi_c_positron_pt_y_cndtn_4[j] = Form("d^{2}N_{e^{+}}/dp_{T}dy");
      name_chi_c_gamma_pt_y_cndtn_4[j] = 
	Form("hChi_c_all_gamma_pt_y_cndtn_4");
      title_chi_c_gamma_pt_y_cndtn_4[j] = Form("d^{2}N_{#gamma}/dp_{T}dy");
      
    }
    
    hChi_c_pt_y[j] = new TH2F(name_chi_c_pt_y[j], title_chi_c_pt_y[j],
			      nPtBins, 0., 50., nyBins, -2., 2.);
    hChi_c_pt_y[j]->Sumw2();
    hChi_c_electron_pt_y[j] = new TH2F(name_chi_c_electron_pt_y[j], 
				       title_chi_c_electron_pt_y[j],
				       nPtBins, 0., 50., nyBins, -2., 2.);
    hChi_c_electron_pt_y[j]->Sumw2();
    hChi_c_positron_pt_y[j] = new TH2F(name_chi_c_positron_pt_y[j], 
				       title_chi_c_positron_pt_y[j],
				       nPtBins, 0., 50., nyBins, -2., 2.);
    hChi_c_positron_pt_y[j]->Sumw2();
    hChi_c_gamma_pt_y[j] = new TH2F(name_chi_c_gamma_pt_y[j], 
				    title_chi_c_gamma_pt_y[j],
				    nPtBins, 0., 50., nyBins, -2., 2.);
    hChi_c_gamma_pt_y[j]->Sumw2();
    
    
    hChi_c_pt_y_cndtn_1[j] = 
      new TH2F(name_chi_c_pt_y_cndtn_1[j], 
	       title_chi_c_pt_y_cndtn_1[j],
	       nPtBins, 0., 50., nyBins, -2., 2.);
    hChi_c_pt_y_cndtn_1[j]->Sumw2();
    hChi_c_electron_pt_y_cndtn_1[j] = 
      new TH2F(name_chi_c_electron_pt_y_cndtn_1[j],
	       title_chi_c_electron_pt_y_cndtn_1[j],
	       nPtBins, 0., 50., nyBins, -2., 2.);
    hChi_c_electron_pt_y_cndtn_1[j]->Sumw2();
    hChi_c_positron_pt_y_cndtn_1[j] = 
      new TH2F(name_chi_c_positron_pt_y_cndtn_1[j], 
	       title_chi_c_positron_pt_y_cndtn_1[j],
	       nPtBins, 0., 50., nyBins, -2., 2.);
    hChi_c_positron_pt_y_cndtn_1[j]->Sumw2();
    hChi_c_gamma_pt_y_cndtn_1[j] = 
      new TH2F(name_chi_c_gamma_pt_y_cndtn_1[j], 
	       title_chi_c_gamma_pt_y_cndtn_1[j],
	       nPtBins, 0., 50., nyBins, -2., 2.);
    hChi_c_gamma_pt_y_cndtn_1[j]->Sumw2();
    
    
    hChi_c_pt_y_cndtn_2[j] = 
      new TH2F(name_chi_c_pt_y_cndtn_2[j], 
	       title_chi_c_pt_y_cndtn_2[j],
	       nPtBins, 0., 50., nyBins, -2., 2.);
    hChi_c_pt_y_cndtn_2[j]->Sumw2();
    hChi_c_electron_pt_y_cndtn_2[j] = 
      new TH2F(name_chi_c_electron_pt_y_cndtn_2[j],
	       title_chi_c_electron_pt_y_cndtn_2[j],
	       nPtBins, 0., 50., nyBins, -2., 2.);
    hChi_c_electron_pt_y_cndtn_2[j]->Sumw2();
    hChi_c_positron_pt_y_cndtn_2[j] = 
      new TH2F(name_chi_c_positron_pt_y_cndtn_2[j], 
	       title_chi_c_positron_pt_y_cndtn_2[j],
	       nPtBins, 0., 50., nyBins, -2., 2.);
    hChi_c_positron_pt_y_cndtn_2[j]->Sumw2();
    hChi_c_gamma_pt_y_cndtn_2[j] = 
      new TH2F(name_chi_c_gamma_pt_y_cndtn_2[j], 
	       title_chi_c_gamma_pt_y_cndtn_2[j],
	       nPtBins, 0., 50., nyBins, -2., 2.);
    hChi_c_gamma_pt_y_cndtn_2[j]->Sumw2();
    
    
    hChi_c_pt_y_cndtn_3[j] = 
      new TH2F(name_chi_c_pt_y_cndtn_3[j], 
	       title_chi_c_pt_y_cndtn_3[j],
	       nPtBins, 0., 50., nyBins, -2., 2.);
    hChi_c_pt_y_cndtn_3[j]->Sumw2();
    hChi_c_electron_pt_y_cndtn_3[j] = 
      new TH2F(name_chi_c_electron_pt_y_cndtn_3[j],
	       title_chi_c_electron_pt_y_cndtn_3[j],
	       nPtBins, 0., 50., nyBins, -2., 2.);
    hChi_c_electron_pt_y_cndtn_3[j]->Sumw2();
    hChi_c_positron_pt_y_cndtn_3[j] = 
      new TH2F(name_chi_c_positron_pt_y_cndtn_3[j], 
	       title_chi_c_positron_pt_y_cndtn_3[j],
	       nPtBins, 0., 50., nyBins, -2., 2.);
    hChi_c_positron_pt_y_cndtn_3[j]->Sumw2();
    hChi_c_gamma_pt_y_cndtn_3[j] = 
      new TH2F(name_chi_c_gamma_pt_y_cndtn_3[j], 
	       title_chi_c_gamma_pt_y_cndtn_3[j],
	       nPtBins, 0., 50., nyBins, -2., 2.);
    hChi_c_gamma_pt_y_cndtn_3[j]->Sumw2();
    
    
    hChi_c_pt_y_cndtn_4[j] = 
      new TH2F(name_chi_c_pt_y_cndtn_4[j], 
	       title_chi_c_pt_y_cndtn_4[j],
	       nPtBins, 0., 50., nyBins, -2., 2.);
    hChi_c_pt_y_cndtn_4[j]->Sumw2();
    hChi_c_electron_pt_y_cndtn_4[j] = 
      new TH2F(name_chi_c_electron_pt_y_cndtn_4[j],
	       title_chi_c_electron_pt_y_cndtn_4[j],
	       nPtBins, 0., 50., nyBins, -2., 2.);
    hChi_c_electron_pt_y_cndtn_4[j]->Sumw2();
    hChi_c_positron_pt_y_cndtn_4[j] = 
      new TH2F(name_chi_c_positron_pt_y_cndtn_4[j], 
	       title_chi_c_positron_pt_y_cndtn_4[j],
	       nPtBins, 0., 50., nyBins, -2., 2.);
    hChi_c_positron_pt_y_cndtn_4[j]->Sumw2();
    hChi_c_gamma_pt_y_cndtn_4[j] = 
      new TH2F(name_chi_c_gamma_pt_y_cndtn_4[j], 
	       title_chi_c_gamma_pt_y_cndtn_4[j],
	       nPtBins, 0., 50., nyBins, -2., 2.);
    hChi_c_gamma_pt_y_cndtn_4[j]->Sumw2();
  }
  
  TString name_hMassElecPosiGam_diff_ElecPosi_from_chi_c[6];
  TString title_hMassElecPosiGam_diff_ElecPosi_from_chi_c[6];
  TString name_hMassElecPosiGam_diff_ElecPosi_from_backg[6];
  TString title_hMassElecPosiGam_diff_ElecPosi_from_backg[6];
  
  for (int i = 0; i < 6; i++){
    if (i < 3){
      name_hMassElecPosiGam_diff_ElecPosi_from_chi_c[i] = 
	Form("hMassElecPosiGam_diff_ElecPosi_ALICE%d_c%d_from_chi_c", 0, i);
      name_hMassElecPosiGam_diff_ElecPosi_from_backg[i] = 
	Form("hMassElecPosiGam_diff_ElecPosi_ALICE%d_c%d_from_backg", 0, i);
    }
    if (i >= 3){
      name_hMassElecPosiGam_diff_ElecPosi_from_chi_c[i] = 
	Form("hMassElecPosiGam_diff_ElecPosi_ALICE%d_p%d_from_chi_c", 3, i-2);
      name_hMassElecPosiGam_diff_ElecPosi_from_backg[i] = 
	Form("hMassElecPosiGam_diff_ElecPosi_ALICE%d_p%d_from_backg", 3, i-2);
    }
    title_hMassElecPosiGam_diff_ElecPosi_from_chi_c[i] = 
      Form("d^{2}N/d#DeltaMdp_{T}");
    title_hMassElecPosiGam_diff_ElecPosi_from_backg[i] = 
      Form("d^{2}N/d#DeltaMdp_{T}");
    
    
    hMassElecPosiGam_diff_ElecPosi_from_chi_c[i] = 
      new TH2F(name_hMassElecPosiGam_diff_ElecPosi_from_chi_c[i],
	       title_hMassElecPosiGam_diff_ElecPosi_from_chi_c[i],
	       nMBins, 0., 0.8, nPtBins_inv_m, 0., 50.);
    
    hMassElecPosiGam_diff_ElecPosi_from_backg[i] = 
      new TH2F(name_hMassElecPosiGam_diff_ElecPosi_from_backg[i],
	       title_hMassElecPosiGam_diff_ElecPosi_from_backg[i],
	       nMBins, 0., 0.8, nPtBins_inv_m, 0., 50.);
    
  }


  TString name_hJpsi_from_chic[6];
  TString title_hJpsi_from_chic[6];
  TString name_hJpsi_from_cand[6];
  TString title_hJpsi_from_cand[6];


  for (int i = 0; i < 4; i++){
    
    name_hJpsi_from_chic[i] = 
      Form("hJpsi_from_chic_cndtn%d", i + 1);
    name_hJpsi_from_cand[i] = 
      Form("hJpsi_from_cand_cndtn%d", i + 1);
    
    title_hJpsi_from_chic[i] = Form("d^{2}N_{J/#psi}/dp_{T}dy"); 
    title_hJpsi_from_cand[i] = Form("d^{2}N_{J/#psi}/dp_{T}dy");
    
    hJpsi_from_chic[i] = 
      new TH2F (name_hJpsi_from_chic[i],title_hJpsi_from_chic[i],
		nPtBins, 0., 50., nyBins, -2, 2);
    hJpsi_from_cand[i] = 
      new TH2F (name_hJpsi_from_cand[i],title_hJpsi_from_cand[i],
		nPtBins, 0., 50., nyBins, -2, 2);
  }


  TString name_hMassElecPosi_from_Jpsi[6];
  TString title_hMassElecPosi_from_Jpsi[6];
  TString name_hMassElecPosi_from_cand[6];
  TString title_hMassElecPosi_from_cand[6];
 
    
  for (int i = 0; i < 6; i++){
    if (i < 3){
      name_hMassElecPosi_from_Jpsi[i] = 
	Form("hMassElecPosi_from_Jpsi_ALICE%d_c%d_from_chic", 0, i);
      name_hMassElecPosi_from_cand[i] = 
	Form("hMassElecPosi_from_cand_ALICE%d_c%d_from_cand", 0, i);
    }
    if (i >= 3){
      name_hMassElecPosi_from_Jpsi[i] =  
	Form("hMassElecPosi_from_Jpsi_ALICE%d_p%d_from_chic", 3, i-2);
      name_hMassElecPosi_from_cand[i] = 
	Form("hMassElecPosi_from_cand_ALICE%d_p%d_from_cand", 3, i-2);
    }
    title_hMassElecPosi_from_Jpsi[i] = Form("d^{2}N/dMdp_{T}");
    title_hMassElecPosi_from_cand[i] = Form("d^{2}N/dMdp_{T}");
    hMassElecPosi_from_Jpsi[i] = 
      new TH2F (name_hMassElecPosi_from_Jpsi[i],
		title_hMassElecPosi_from_Jpsi[i],
		nMBins, 2.1, 4.1, nPtBins_inv_m, 0., 50.);
    hMassElecPosi_from_cand[i] = 
      new TH2F (name_hMassElecPosi_from_cand[i],
		title_hMassElecPosi_from_cand[i],
		nMBins, 2.1, 4.1, nPtBins_inv_m, 0., 50.);
  }
  

  return;
}
