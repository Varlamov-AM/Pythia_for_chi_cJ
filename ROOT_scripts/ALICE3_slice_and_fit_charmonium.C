#include <math.h> 
#include <iostream>

Double_t Gaus3Sum_with_pol2(Double_t *, Double_t *);
Double_t Gaus3Sum(Double_t *, Double_t *);
Double_t Gaus(Double_t *, Double_t *);

void ALICE3_slice_and_fit_charmonium(){


  TFile *file = new TFile("Pythia_for_charmonium_new_version.root");
  
  //Get histograms

  TH2F* hDeltaMass[6];

  hDeltaMass[0] = 
    (TH2F*)file->Get("hMassElecPosiGam_diff_ElecPosi_ALICE0_c0_from_backg");
  hDeltaMass[1] = 
    (TH2F*)file->Get("hMassElecPosiGam_diff_ElecPosi_ALICE0_c1_from_backg");
  hDeltaMass[2] = 
    (TH2F*)file->Get("hMassElecPosiGam_diff_ElecPosi_ALICE0_c2_from_backg");
  hDeltaMass[3] = 
    (TH2F*)file->Get("hMassElecPosiGam_diff_ElecPosi_ALICE3_p1_from_backg");
  hDeltaMass[4] = 
    (TH2F*)file->Get("hMassElecPosiGam_diff_ElecPosi_ALICE3_p2_from_backg");
  hDeltaMass[5] = 
    (TH2F*)file->Get("hMassElecPosiGam_diff_ElecPosi_ALICE3_p3_from_backg");


  const Int_t NBINS = 15;
  double border_arr[NBINS + 1] = {0.,1.,2.,3.,4.,5.,6.,7.,8.,9.,10.,12.,14.,20.,25.,50.};
  TH1D* sliced_spectrum[NBINS][6];


  TCanvas *canv[6]; 

  canv[0]= new TCanvas("canv0", "Sliced spectrum test ALICE0_c1");
  canv[0]->Divide(4,4);
  
  canv[1]= new TCanvas("canv1", "Sliced spectrum test ALICE0_c2");
  canv[1]->Divide(4,4);
  
  canv[2]= new TCanvas("canv2", "Sliced spectrum test ALICE0_c3");
  canv[2]->Divide(4,4);
  
  canv[3]= new TCanvas("canv3", "Sliced spectrum test ALICE3_p1");
  canv[3]->Divide(4,4);
  
  canv[4]= new TCanvas("canv4", "Sliced spectrum test ALICE3_p2");
  canv[4]->Divide(4,4);
  
  canv[5]= new TCanvas("canv5", "Sliced spectrum test ALICE3_p3");
  canv[5]->Divide(4,4);


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
  
  params[0] = params_1;
  params[1] = params_2;
  params[2] = params_3;
  params[3] = params_4;
  params[4] = params_5;
  params[5] = params_6;

  for (int iPt = 0; iPt < NBINS; iPt++){
    for(int j = 0; j < 6; j++){
      TString name_pro;
      if (j < 3){
	name_pro = Form("ALICE0_c%d_p_T_slice_%d", j + 1, iPt + 1);
      }
      if (j >= 3){
	name_pro = Form("ALICE3_p%d_p_T_slice_%d", j - 2, iPt + 1);
      }
      sliced_spectrum[iPt][j] = (TH1D*)(hDeltaMass[j]->ProjectionX(name_pro.Data(), border_arr[iPt], border_arr[iPt + 1]));
      canv[j]->cd(iPt + 1);
      
      double M_min = 0.25;
      double M_max = 0.53;

      TF1 *fGaus3Sum_with_pol2 = 
	new TF1("fGaus3Sum_with_pol2",Gaus3Sum_with_pol2,M_min,M_max,12);
      fGaus3Sum_with_pol2->SetParName(0,"A_{0}") ;
      fGaus3Sum_with_pol2->SetParName(1,"m_{0}") ;
      fGaus3Sum_with_pol2->SetParName(2,"#sigma_{0}") ;
      fGaus3Sum_with_pol2->SetParName(3,"A_{1}") ;
      fGaus3Sum_with_pol2->SetParName(4,"m_{1}") ;
      fGaus3Sum_with_pol2->SetParName(5,"#sigma_{1}") ;
      fGaus3Sum_with_pol2->SetParName(6,"A_{2}") ;
      fGaus3Sum_with_pol2->SetParName(7,"m_{2}") ;
      fGaus3Sum_with_pol2->SetParName(8,"#sigma_{2}") ;
      fGaus3Sum_with_pol2->SetLineColor(kRed);
      
      fGaus3Sum_with_pol2->SetParameters(params[j]);
      
      fGaus3Sum_with_pol2->SetParLimits(1,0.313,0.318);
      fGaus3Sum_with_pol2->
	SetParLimits(2,sigma_c0_low_boarder[j],sigma_c0_up_boarder[j]);
      
      fGaus3Sum_with_pol2->SetParLimits(4,0.408,0.420);
      fGaus3Sum_with_pol2->
      SetParLimits(5,sigma_c1_low_boarder[j],sigma_c1_up_boarder[j]);
      
      fGaus3Sum_with_pol2->SetParLimits(7,0.455,0.465);
      fGaus3Sum_with_pol2->
	SetParLimits(8,sigma_c2_low_boarder[j],sigma_c2_up_boarder[j]);
      
      sliced_spectrum[iPt][j]->Fit(fGaus3Sum_with_pol2,"","",M_min,M_max);
      
      double m_chic0 = fGaus3Sum_with_pol2->GetParameter(1);
      double m_chic1 = fGaus3Sum_with_pol2->GetParameter(4);
      double m_chic2 = fGaus3Sum_with_pol2->GetParameter(7);
      double s_chic0 = fGaus3Sum_with_pol2->GetParameter(2);
      double s_chic1 = fGaus3Sum_with_pol2->GetParameter(5);
      double s_chic2 = fGaus3Sum_with_pol2->GetParameter(8);

      TF1 *fGausChiC0 = new TF1("fGausChiC0",Gaus,m_chic0 - 3 * s_chic0, m_chic0 + 3 * s_chic0,3);
      TF1 *fGausChiC1 = new TF1("fGausChiC1",Gaus,m_chic1 - 3 * s_chic1, m_chic1 + 3 * s_chic1,3);
      TF1 *fGausChiC2 = new TF1("fGausChiC2",Gaus,m_chic2 - 3 * s_chic2, m_chic2 + 3 * s_chic2,3);
      TF1 *pol2_backg = new TF1("pol2_backg",pol2,M_min,M_max,3);
      fGausChiC0->SetParameters(fGaus3Sum_with_pol2->GetParameters());
      fGausChiC1->SetParameters(fGaus3Sum_with_pol2->GetParameters()+3);
      fGausChiC2->SetParameters(fGaus3Sum_with_pol2->GetParameters()+6);
      pol2_backg->SetParameters(fGaus3Sum_with_pol2->GetParameters()+9);
      fGausChiC0->SetLineColor(kBlue);
      fGausChiC1->SetLineColor(kGreen+1);
      fGausChiC2->SetLineColor(kOrange+1);
      pol2_backg->SetLineColor(kCyan);
      
      fGausChiC0->Draw("same");
      fGausChiC1->Draw("same");
      fGausChiC2->Draw("same");
      pol2_backg->Draw("same");
      
      gStyle->SetOptFit(111111);
      gStyle->SetOptStat(11);
    }
  }
  

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
