#include <iostream>
#include <TLorentzVector.h>
#include "Pythia8/Pythia.h"
#include <TH2.h>
#include <string>

using namespace Pythia8;

TLorentzVector resolutionPhoton  (TLorentzVector, int);
TLorentzVector resolutionElectron(TLorentzVector, int);
bool IsElectronDetectedInCTS(TLorentzVector);
bool IsElectronDetectedInALICE3(TLorentzVector, int);
bool IsPhotonDetectedInEMCAL(TLorentzVector);
bool IsPhotonDetectedInPHOS(TLorentzVector);
double Jpsi_Mass(double, int);
double Jpsi_Sigma(double, int);


void Background_handler(Pythia* pythia,
			int* elec, int* posi, int* gamm,
			int elec_num, int posi_num, int gam_num,
			TLorentzVector* elec_data, 
			TLorentzVector* posi_data,
			TLorentzVector* gamma_data,
			TLorentzVector* elec_true_data, 
			TLorentzVector* posi_true_data,
			TLorentzVector* Jpsi_data_ALICE0_1,
			TLorentzVector* Jpsi_data_ALICE0_2,
			TLorentzVector* Jpsi_data_ALICE3_1,
			TLorentzVector* Jpsi_data_ALICE3_2,
			TLorentzVector* Jpsi_data_ALICE3_3,
			TH2F** hMassElecPosiGam_diff_ElecPosi_from_backg,
			TH2F** hMassElecPosi_from_cand,
			TH2F** hMassElecPosi_from_even,
			TH2F** hJpsi_from_cand,
       			TH2F** hElectron_pt_y_event,
			TH2F** hPositron_pt_y_event,
			TH2F** hGamma_pt_y_event,
			double br){


  /* This method is designed to handle background events. As variables, 
     the method receives a pointer to the pythia generator, pointers to 
     arrays of electrons, positrons and photons from the event.

     Then, the following steps are performed:
     
     1. Formation of four-momentum particles.
     2. Smearing four-momentum.
     3. Selection of candidates J/psi.
     4. Forming a combinatorial background, filling background into the 
     corresponding histogram.

  */

  // 4-momentum for particles

  if (elec_num != 0){
    
    for (int i = 0; i < elec_num; i++){
      TLorentzVector tmp(pythia->event[*(elec + i)].px(), 
			 pythia->event[*(elec + i)].py(), 
			 pythia->event[*(elec + i)].pz(), 
			 pythia->event[*(elec + i)].e());
      
      *(elec_data + 3 * i + 0) = resolutionElectron(tmp, 0);
      *(elec_data + 3 * i + 1) = resolutionElectron(tmp, 1);
      *(elec_data + 3 * i + 2) = resolutionElectron(tmp, 2);
      *(elec_data + 3 * i + 3) = resolutionElectron(tmp, 2);
      elec_true_data[i] = tmp;
      
    }
  }
  if (posi_num != 0){
   
    for (int i = 0; i < posi_num; i++){
      TLorentzVector tmp(pythia->event[*(posi + i)].px(), 
			 pythia->event[*(posi + i)].py(), 
			 pythia->event[*(posi + i)].pz(), 
			 pythia->event[*(posi + i)].e());
      
      *(posi_data + 3 * i + 0) = resolutionElectron(tmp, 0);
      *(posi_data + 3 * i + 1) = resolutionElectron(tmp, 1);
      *(posi_data + 3 * i + 2) = resolutionElectron(tmp, 2);
      *(posi_data + 3 * i + 3) = resolutionElectron(tmp, 3);
      posi_true_data[i] = tmp;
      
    }
  }
  if (gam_num != 0){
   
    for (int i = 0; i < gam_num; i++){
      TLorentzVector tmp(pythia->event[*(gamm + i)].px(), 
			 pythia->event[*(gamm + i)].py(), 
			 pythia->event[*(gamm + i)].pz(), 
			 pythia->event[*(gamm + i)].e());
      
      *(gamma_data + 2 * i + 0) = resolutionPhoton(tmp, 0);
      *(gamma_data + 2 * i + 1) = resolutionPhoton(tmp, 1);
    }
  }
  
 
  // find candidates for J/psi
  
  /* 
     1. Evaluate J/psi mass with defied function Jpsi_Mass(p_T);
     2. Evaluate J/psi sigma with defined function Jpsi_Sigma(p_T);
     3. p_T is taken from (P_{e^+} + P_{e^-}).Pt()
     4. Compare |(P_{e^+} + P_{e^-}).M() - Jpsi_Mass((P_{e^+} + P_{e^-}).Pt())|
     v Jpsi_Sigma((P_{e^+} + P_{e^-}).Pt()). if || < sigma, then forming Jpsi 
     from thats e^{+}e^{-} pair, else continue.
     5. Create arrays of Jpsi TLorentzVectors.

  */

  Int_t Jpsi_num_ALICE0_1 = 0;
  Int_t Jpsi_num_ALICE0_2 = 0;
  Int_t Jpsi_num_ALICE3_1 = 0;
  Int_t Jpsi_num_ALICE3_2 = 0;
  Int_t Jpsi_num_ALICE3_3 = 0;


  if (elec_num != 0 && posi_num != 0){  
    for (int i = 0; i < elec_num; i++){
      for (int j = 0; j < posi_num; j++){
	double Jpsi_mass[4]; 
	double Jpsi_sigma[4];
	
	for (int l = 0; l < 4; l++){
	  Jpsi_mass[l] = Jpsi_Mass((elec_data[i] + posi_data[j]).Pt(), l);
	  Jpsi_sigma[l] = Jpsi_Sigma((elec_data[i] + posi_data[j]).Pt(), l);
	}
	if (IsElectronDetectedInCTS(elec_true_data[i]) &&
	    IsElectronDetectedInCTS(posi_true_data[j])){
	  if (fabs((*(elec_data + 4 * i + 0) + 
		    *(posi_data + 4 * j + 0)).M() - Jpsi_mass[0]) <= 
	      Jpsi_sigma[0]){
	    Jpsi_data_ALICE0_1[Jpsi_num_ALICE0_1] = (*(elec_data + 4 * i + 0) + 
						   *(posi_data + 4 * j + 0));
	    
	    hMassElecPosi_from_cand[0]->Fill(
	    (Jpsi_data_ALICE0_1[Jpsi_num_ALICE0_1].M()),
	    (Jpsi_data_ALICE0_1[Jpsi_num_ALICE0_1].Pt()),
	    br);
	    
	    hMassElecPosi_from_cand[1]->Fill(
	    (Jpsi_data_ALICE0_1[Jpsi_num_ALICE0_1].M()),
	    (Jpsi_data_ALICE0_1[Jpsi_num_ALICE0_1].Pt()),
	    br);
	    
	    hJpsi_from_cand[0]->Fill(
            (Jpsi_data_ALICE0_1[Jpsi_num_ALICE0_1].Pt()),
	    (Jpsi_data_ALICE0_1[Jpsi_num_ALICE0_1].Rapidity()),
	    br);

	    hJpsi_from_cand[1]->Fill(
            (Jpsi_data_ALICE0_1[Jpsi_num_ALICE0_1].Pt()),
	    (Jpsi_data_ALICE0_1[Jpsi_num_ALICE0_1].Rapidity()),
	    br);
	    
	    Jpsi_num_ALICE0_1++;

	  }

	  hMassElecPosi_from_even[0]->Fill(
	  ((*(elec_data + 4 * i + 0) + 
	    *(posi_data + 4 * j + 0)).M()),
	  ((*(elec_data + 4 * i + 0) + 
	    *(posi_data + 4 * j + 0)).Pt()),
	  br);
	    
	  hMassElecPosi_from_even[1]->Fill(
	  ((*(elec_data + 4 * i + 0) + 
	    *(posi_data + 4 * j + 0)).M()),
	  ((*(elec_data + 4 * i + 0) + 
	    *(posi_data + 4 * j + 0)).Pt()),
	  br);
	  
	  hElectron_pt_y_event[0]->Fill(
	  ((*(elec_data + 4 * i + 0)).Pt()),
	  ((*(elec_data + 4 * i + 0)).Rapidity()),
	  br);
	  
	  hPositron_pt_y_event[0]->Fill(
	  ((*(posi_data + 4 * i + 0)).Pt()),
	  ((*(posi_data + 4 * i + 0)).Rapidity()),
	  br);
	  
	  hElectron_pt_y_event[1]->Fill(
	  ((*(elec_data + 4 * i + 0)).Pt()),
	  ((*(elec_data + 4 * i + 0)).Rapidity()),
	  br);
	  
	  hPositron_pt_y_event[1]->Fill(
	  ((*(posi_data + 4 * i + 0)).Pt()),
	  ((*(posi_data + 4 * i + 0)).Rapidity()),
	  br);
	}

	if (IsPhotonDetectedInEMCAL(elec_true_data[i]) &&
	    IsPhotonDetectedInEMCAL(posi_true_data[j])){
	  if (fabs((*(elec_data + 4 * i + 0) + 
		    *(posi_data + 4 * j + 0)).M() - Jpsi_mass[0]) <= 
	      Jpsi_sigma[0]){
	    Jpsi_data_ALICE0_2[Jpsi_num_ALICE0_2] = (*(elec_data + 4 * i + 0) + 
						     *(posi_data + 4 * j + 0));
	    
	    hMassElecPosi_from_cand[2]->Fill(
	    (Jpsi_data_ALICE0_2[Jpsi_num_ALICE0_2].M()),
	    (Jpsi_data_ALICE0_2[Jpsi_num_ALICE0_2].Pt()),
	    br);
	    
	    hJpsi_from_cand[2]->Fill(
	    (Jpsi_data_ALICE0_2[Jpsi_num_ALICE0_2].Pt()),
	    (Jpsi_data_ALICE0_2[Jpsi_num_ALICE0_2].Rapidity()),
	    br);
	    
	    Jpsi_num_ALICE0_2++;

	  }

	  hMassElecPosi_from_even[2]->Fill(
	  ((*(elec_data + 4 * i + 0) + 
	    *(posi_data + 4 * j + 0)).M()),
	  ((*(elec_data + 4 * i + 0) + 
	    *(posi_data + 4 * j + 0)).Pt()),
	  br);

	  hElectron_pt_y_event[2]->Fill(
	  ((*(elec_data + 4 * i + 0)).Pt()),
	  ((*(elec_data + 4 * i + 0)).Rapidity()),
	  br);

	  hPositron_pt_y_event[2]->Fill(
	  ((*(posi_data + 4 * i + 0)).Pt()),
	  ((*(posi_data + 4 * i + 0)).Rapidity()),
	  br);
	    
	}
	if (IsElectronDetectedInALICE3(elec_true_data[i], 2) &&
	    IsElectronDetectedInALICE3(posi_true_data[j], 2)){
	  if (fabs((*(elec_data + 4 * i + 1) + 
		    *(posi_data + 4 * j + 1)).M() - Jpsi_mass[1]) <= 
	      Jpsi_sigma[1]){
	    Jpsi_data_ALICE3_1[Jpsi_num_ALICE3_1] = (*(elec_data + 4 * i + 1) + 
						     *(posi_data + 4 * j + 1));
	    
	    hMassElecPosi_from_cand[3]->Fill(
	    (Jpsi_data_ALICE3_1[Jpsi_num_ALICE3_1].M()),
	    (Jpsi_data_ALICE3_1[Jpsi_num_ALICE3_1].Pt()),
	    br);
	    
	    hJpsi_from_cand[3]->Fill(
            (Jpsi_data_ALICE3_1[Jpsi_num_ALICE3_1].Pt()),
	    (Jpsi_data_ALICE3_1[Jpsi_num_ALICE3_1].Rapidity()),
	    br);
	    
	    Jpsi_num_ALICE3_1++;
	  }

	  hMassElecPosi_from_even[3]->Fill(
	  ((*(elec_data + 4 * i + 1) + 
	    *(posi_data + 4 * j + 1)).M()),
	  ((*(elec_data + 4 * i + 1) + 
	    *(posi_data + 4 * j + 1)).Pt()),
	  br);

	  hElectron_pt_y_event[3]->Fill(
	  ((*(elec_data + 4 * i + 1)).Pt()),
	  ((*(elec_data + 4 * i + 1)).Rapidity()),
	  br);

	  hPositron_pt_y_event[3]->Fill(
	  ((*(posi_data + 4 * i + 1)).Pt()),
	  ((*(posi_data + 4 * i + 1)).Rapidity()),
	  br);

	}
	if (IsElectronDetectedInALICE3(elec_true_data[i], 2) &&
	    IsElectronDetectedInALICE3(posi_true_data[j], 2)){
	   if (fabs((*(elec_data + 4 * i + 2) + 
		     *(posi_data + 4 * j + 2)).M() - Jpsi_mass[2]) <= 
	      Jpsi_sigma[2]){
	    Jpsi_data_ALICE3_2[Jpsi_num_ALICE3_2] = (*(elec_data + 4 * i + 2) + 
						     *(posi_data + 4 * j + 2));
	    
	    hMassElecPosi_from_cand[4]->Fill(
	    (Jpsi_data_ALICE3_2[Jpsi_num_ALICE3_2].M()),
	    (Jpsi_data_ALICE3_2[Jpsi_num_ALICE3_2].Pt()),
	    br);
	    
	    hJpsi_from_cand[4]->Fill(
            (Jpsi_data_ALICE3_2[Jpsi_num_ALICE3_2].Pt()),
	    (Jpsi_data_ALICE3_2[Jpsi_num_ALICE3_2].Rapidity()),
	    br);
	    
	    Jpsi_num_ALICE3_2++;
	   }

	  hMassElecPosi_from_even[4]->Fill(
	  ((*(elec_data + 4 * i + 2) + 
	    *(posi_data + 4 * j + 2)).M()),
	  ((*(elec_data + 4 * i + 2) + 
	    *(posi_data + 4 * j + 2)).Pt()),
	  br);

	  hElectron_pt_y_event[4]->Fill(
	  ((*(elec_data + 4 * i + 2)).Pt()),
	  ((*(elec_data + 4 * i + 2)).Rapidity()),
	  br);

	  hPositron_pt_y_event[4]->Fill(
	  ((*(posi_data + 4 * i + 2)).Pt()),
	  ((*(posi_data + 4 * i + 2)).Rapidity()),
	  br);

	}
	if (IsElectronDetectedInALICE3(elec_true_data[i], 2) &&
	    IsElectronDetectedInALICE3(posi_true_data[j], 2)){
	  if (fabs((*(elec_data + 4 * i + 3) + 
		    *(posi_data + 4 * j + 3)).M() - Jpsi_mass[3]) <= 
	      Jpsi_sigma[3]){
	    Jpsi_data_ALICE3_3[Jpsi_num_ALICE3_3] = (*(elec_data + 4 * i + 3) + 
						     *(posi_data + 4 * j + 3));
	    
	    hMassElecPosi_from_cand[5]->Fill(
	    (Jpsi_data_ALICE3_3[Jpsi_num_ALICE3_3].M()),
	    (Jpsi_data_ALICE3_3[Jpsi_num_ALICE3_3].Pt()),
	    br);
	    
	    hJpsi_from_cand[5]->Fill(
            (Jpsi_data_ALICE3_3[Jpsi_num_ALICE3_3].Pt()),
	    (Jpsi_data_ALICE3_3[Jpsi_num_ALICE3_3].Rapidity()),
	    br);
	    
	    Jpsi_num_ALICE3_3++;
	  }

	  hMassElecPosi_from_even[5]->Fill(
	  ((*(elec_data + 4 * i + 3) + 
	    *(posi_data + 4 * j + 3)).M()),
	  ((*(elec_data + 4 * i + 3) + 
	    *(posi_data + 4 * j + 3)).Pt()),
	  br);

	  hElectron_pt_y_event[5]->Fill(
	  ((*(elec_data + 4 * i + 3)).Pt()),
	  ((*(elec_data + 4 * i + 3)).Rapidity()),
	  br);

	  hPositron_pt_y_event[5]->Fill(
	  ((*(posi_data + 4 * i + 3)).Pt()),
	  ((*(posi_data + 4 * i + 3)).Rapidity()),
	  br);
	  
	}
      }
    }
  }


  if (gam_num != 0){
   
    for (int i = 0; i < gam_num; i++){

      if (IsPhotonDetectedInPHOS(*(gamma_data + 2 * i))){
	hGamma_pt_y_event[0]->Fill(
	((*(gamma_data + 2 * i)).Pt()),
	((*(gamma_data + 2 * i)).Rapidity()),
	br);
	
	hGamma_pt_y_event[2]->Fill(
	((*(gamma_data + 2 * i)).Pt()),
	((*(gamma_data + 2 * i)).Rapidity()),
	br);
      };
      
      if (IsPhotonDetectedInPHOS(*(gamma_data + 2 * i)) &&
	  ((*(gamma_data + 2 * i)).Pt() >= 5.)){
	hGamma_pt_y_event[1]->Fill(
	((*(gamma_data + 2 * i)).Pt()),
	((*(gamma_data + 2 * i)).Rapidity()),
	br);
      };

      if (IsElectronDetectedInALICE3(*(gamma_data + 2 * i), 1)){
	hGamma_pt_y_event[3]->Fill(
	((*(gamma_data + 2 * i)).Pt()),
	((*(gamma_data + 2 * i)).Rapidity()),
	br);
	
	hGamma_pt_y_event[4]->Fill(
	((*(gamma_data + 2 * i)).Pt()),
	((*(gamma_data + 2 * i)).Rapidity()),
	br);
      }

      if (IsElectronDetectedInALICE3(*(gamma_data + 2 * i + 1), 1)){
	hGamma_pt_y_event[5]->Fill(
	((*(gamma_data + 2 * i + 1)).Pt()),
	((*(gamma_data + 2 * i + 1)).Rapidity()),
	br);
      }

    }
  }
 
  

  if (Jpsi_num_ALICE0_1 != 0 && gam_num != 0){
    for (int i = 0; i < Jpsi_num_ALICE0_1; i++){ 
      for (int j = 0; j < gam_num; j++){
	if(IsPhotonDetectedInPHOS(*(gamma_data + 2*j))){
	  
	  //test printing to find program bugs
	  if((Jpsi_data_ALICE0_1[i] + *(gamma_data + 2*j)).M() - Jpsi_data_ALICE0_1[i].M()){
	    printf("\nFind candidate to chi_c with mass close to Jpsi\n");
	    printf("Jpsi candidate and gamma 4-momentum:\n");

	    
	    double Jpsi_E  = Jpsi_data_ALICE0_1[i].E();
	    double Jpsi_px = Jpsi_data_ALICE0_1[i].Px();
	    double Jpsi_py = Jpsi_data_ALICE0_1[i].Py();
	    double Jpsi_pz = Jpsi_data_ALICE0_1[i].Pz();


	    double gamma_E  = (*(gamma_data + 2*j)).E();
	    double gamma_px = (*(gamma_data + 2*j)).Px();
	    double gamma_py = (*(gamma_data + 2*j)).Py();
	    double gamma_pz = (*(gamma_data + 2*j)).Pz();

	    printf("|   %7.3f   |      |   %7.3f   |\n", Jpsi_E, gamma_E);
	    printf("|   %7.3f   |      |   %7.3f   |\n", Jpsi_px, gamma_px);
	    printf("|   %7.3f   |      |   %7.3f   |\n", Jpsi_py, gamma_py);
	    printf("|   %7.3f   |      |   %7.3f   |\n", Jpsi_pz, gamma_pz);

	    
	  }

	  hMassElecPosiGam_diff_ElecPosi_from_backg[0]->Fill(
	  ((Jpsi_data_ALICE0_1[i] + *(gamma_data + 2*j)).M() - Jpsi_data_ALICE0_1[i].M()),
	  ((Jpsi_data_ALICE0_1[i] + *(gamma_data + 2*j)).Pt()),
	  br);
	}
	if(IsPhotonDetectedInPHOS(*(gamma_data + 2*j)) && 
	   (*(gamma_data + 2*j)).Pt() >= 5.0){
	  hMassElecPosiGam_diff_ElecPosi_from_backg[1]->Fill(
	  ((Jpsi_data_ALICE0_1[i] + *(gamma_data + 2*j)).M() - Jpsi_data_ALICE0_1[i].M()),
	  ((Jpsi_data_ALICE0_1[i] + *(gamma_data + 2*j)).Pt()),
	  br);
	}
      }
    }   
  }if (Jpsi_num_ALICE0_2 != 0 && gam_num != 0){
    for (int i = 0; i < Jpsi_num_ALICE0_2; i++){ 
      for (int j = 0; j < gam_num; j++){
	if(IsPhotonDetectedInPHOS(*(gamma_data + 2*j))){
	  hMassElecPosiGam_diff_ElecPosi_from_backg[2]->Fill(
	  ((Jpsi_data_ALICE0_2[i] + *(gamma_data + 2*j)).M() - Jpsi_data_ALICE0_2[i].M()),
	  ((Jpsi_data_ALICE0_2[i] + *(gamma_data + 2*j)).Pt()),
	  br);
	}
      }
    }   
  } 

  if (Jpsi_num_ALICE3_1 != 0 && gam_num != 0){
    for (int i = 0; i < Jpsi_num_ALICE3_1; i++){ 
      for (int j = 0; j < gam_num; j++){
	if(IsElectronDetectedInALICE3(*(gamma_data + 2*j), 1)){
	  hMassElecPosiGam_diff_ElecPosi_from_backg[3]->Fill(
          ((Jpsi_data_ALICE3_1[i] + *(gamma_data + 2*j)).M() - Jpsi_data_ALICE3_1[i].M()),
	  ((Jpsi_data_ALICE3_1[i] + *(gamma_data + 2*j)).Pt()),
	  br);
	}
      }
    }   
  } 

  if (Jpsi_num_ALICE3_2 != 0 && gam_num != 0){
    for (int i = 0; i < Jpsi_num_ALICE3_2; i++){ 
      for (int j = 0; j < gam_num; j++){
	if(IsElectronDetectedInALICE3(*(gamma_data + 2*j), 1)){
	  hMassElecPosiGam_diff_ElecPosi_from_backg[4]->Fill(
          ((Jpsi_data_ALICE3_2[i] + *(gamma_data + 2*j)).M() - Jpsi_data_ALICE3_2[i].M()),
	  ((Jpsi_data_ALICE3_2[i] + *(gamma_data + 2*j)).Pt()),
	  br);
	}
      }
    }   
  }  

  if (Jpsi_num_ALICE3_3 != 0 && gam_num != 0){
    for (int i = 0; i < Jpsi_num_ALICE3_3; i++){ 
      for (int j = 0; j < gam_num; j++){
	if(IsElectronDetectedInALICE3(*(gamma_data + 2*j + 1), 1)){
	  hMassElecPosiGam_diff_ElecPosi_from_backg[5]->Fill(
	  ((Jpsi_data_ALICE3_3[i] + *(gamma_data + 2*j + 1)).M() - Jpsi_data_ALICE3_3[i].M()),
	  ((Jpsi_data_ALICE3_3[i] + *(gamma_data + 2*j + 1)).Pt()),
	  br);
	}
      }
    }   
  }
  
  return;
}
