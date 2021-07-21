#include "Pythia8/Pythia.h"
#include "TH1.h"
#include "TH2.h"
#include "TLorentzVector.h"
#include <iostream>


TLorentzVector resolutionPhoton  (TLorentzVector, int);
TLorentzVector resolutionElectron(TLorentzVector, int);

bool IsElectronDetectedInCTS   (TLorentzVector);
bool IsPhotonDetectedInEMCAL   (TLorentzVector);
bool IsPhotonDetectedInPHOS    (TLorentzVector);
bool IsElectronDetectedInALICE3(TLorentzVector, int);


using namespace Pythia8;


void Signal_event_handler(Pythia* pythia, 
			  int chi_c_name,
			  int part_num,
			  TH2F** hChi_c_pt_y, 
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
			  TH2F** hMassElecPosi_from_Jpsi,
			  TH2F** hJpsi_from_chic,
			  double* branching){
  

  //const int idChic0        =  10441;
  //const int idChic1        =  20443;
  //const int idChic2        =  445;
  const int idJpsi         =  443;
  const int idElectron     =  11;
  const int idPhoton       =  22;
  //const int idPi0          =  111;

  
  if ((chi_c_name == 0) ||
      (chi_c_name == 1) ||
      (chi_c_name == 2)){


    //Find doughter of chi_c    
    int dghtChi1 = pythia->event[part_num].daughter1(); 
    int dghtChi2 = pythia->event[part_num].daughter2(); 
    

    //Select decay chi_c to Jpsi + gamma
    if(dghtChi2 - dghtChi1 == 1                 &&
       pythia->event[dghtChi1].id() == idJpsi   &&
       pythia->event[dghtChi2].id() == idPhoton){
      
      //Find doughter of Jpsi
      int dghtJ1 = pythia->event[dghtChi1].daughter1();
      int dghtJ2 = pythia->event[dghtChi1].daughter2();


      //Select decay Jpsi to e-e+
      if (dghtJ2 - dghtJ1 == 1                             &&
	  pythia->event[dghtJ1].id() == idElectron         &&
	  pythia->event[dghtJ2].id() == (-1) * idElectron){
	
	//Find chi_c transverse momentum and rapidity
	Double_t chi_c_pt = pythia->event[part_num].pT();
	Double_t chi_c_y  = pythia->event[part_num].y();
	Double_t elec_pt  = pythia->event[dghtJ1].pT();
	Double_t elec_y   = pythia->event[dghtJ1].y();
	Double_t posi_pt  = pythia->event[dghtJ2].pT();
	Double_t posi_y   = pythia->event[dghtJ2].y();
	Double_t gamma_pt = pythia->event[dghtChi2].pT();
	Double_t gamma_y  = pythia->event[dghtChi2].y();
	
	
	//Fill histograms to all born chi_c in event
	hChi_c_pt_y[chi_c_name]->Fill(chi_c_pt, chi_c_y, 
				      branching[chi_c_name]);
	hChi_c_pt_y[3]->Fill(chi_c_pt, chi_c_y, 
			     branching[chi_c_name]);

	hChi_c_electron_pt_y[chi_c_name]->Fill(elec_pt, elec_y, 
					       branching[chi_c_name]);
	hChi_c_electron_pt_y[3]->Fill(elec_pt, elec_y, 
				      branching[chi_c_name]);
					
	hChi_c_positron_pt_y[chi_c_name]->Fill(posi_pt, posi_y, 
					       branching[chi_c_name]);
	hChi_c_positron_pt_y[3]->Fill(posi_pt, posi_y, 
				      branching[chi_c_name]);
					
	hChi_c_gamma_pt_y[chi_c_name]->Fill(gamma_pt, gamma_y, 
					    branching[chi_c_name]);
	hChi_c_gamma_pt_y[3]->Fill(gamma_pt, gamma_y, 
				   branching[chi_c_name]);	
	

	//Find components of 4-momentum for e- e+ gamma
	double elec_px = pythia->event[dghtJ1].px();
	double elec_py = pythia->event[dghtJ1].py();
	double elec_pz = pythia->event[dghtJ1].pz();
	double elec_p0 = pythia->event[dghtJ1].e(); 
	
	double posi_px = pythia->event[dghtJ2].px();
	double posi_py = pythia->event[dghtJ2].py();
	double posi_pz = pythia->event[dghtJ2].pz();
	double posi_p0 = pythia->event[dghtJ2].e();
	
	double gamm_px = pythia->event[dghtChi2].px();
	double gamm_py = pythia->event[dghtChi2].py();
	double gamm_pz = pythia->event[dghtChi2].pz();
	double gamm_p0 = pythia->event[dghtChi2].e();   
	
	TLorentzVector pElec(elec_px, elec_py, elec_pz, elec_p0);
	TLorentzVector pPosi(posi_px, posi_py, posi_pz, posi_p0);
	TLorentzVector pGamm(gamm_px, gamm_py, gamm_pz, gamm_p0);

	TLorentzVector pGamm_sm_0 = resolutionPhoton(pGamm, 0);
	TLorentzVector pGamm_sm_1 = resolutionPhoton(pGamm, 1);
	
	TLorentzVector pElec_sm_0 = resolutionElectron(pElec, 0);
	TLorentzVector pElec_sm_1 = resolutionElectron(pElec, 1);
	TLorentzVector pElec_sm_2 = resolutionElectron(pElec, 2);
	TLorentzVector pElec_sm_3 = resolutionElectron(pElec, 3);
	
	TLorentzVector pPosi_sm_0 = resolutionElectron(pPosi, 0);
	TLorentzVector pPosi_sm_1 = resolutionElectron(pPosi, 1);
	TLorentzVector pPosi_sm_2 = resolutionElectron(pPosi, 2);
	TLorentzVector pPosi_sm_3 = resolutionElectron(pPosi, 3);

	
	//Fill histograms for diff conditions
	if (IsElectronDetectedInCTS(pElec) &&
	    IsElectronDetectedInCTS(pPosi) &&
	    IsPhotonDetectedInPHOS(pGamm)){// condition 1
	  
	  hChi_c_pt_y_cndtn_1[chi_c_name]->Fill(chi_c_pt, chi_c_y, 
						branching[chi_c_name]);
	  hChi_c_pt_y_cndtn_1[3]->Fill(chi_c_pt, chi_c_y, 
				       branching[chi_c_name]);
	  
	  hChi_c_electron_pt_y_cndtn_1[chi_c_name]->Fill(elec_pt, elec_y, 
							 branching[chi_c_name]);
	  hChi_c_electron_pt_y_cndtn_1[3]->Fill(elec_pt, elec_y, 
						branching[chi_c_name]);
	  
	  hChi_c_positron_pt_y_cndtn_1[chi_c_name]->Fill(posi_pt, posi_y, 
							 branching[chi_c_name]);
	  hChi_c_positron_pt_y_cndtn_1[3]->Fill(posi_pt, posi_y, 
						branching[chi_c_name]);
	  
	  hChi_c_gamma_pt_y_cndtn_1[chi_c_name]->Fill(gamma_pt, gamma_y, 
						      branching[chi_c_name]);
	  hChi_c_gamma_pt_y_cndtn_1[3]->Fill(gamma_pt, gamma_y, 
					     branching[chi_c_name]);

	  hMassElecPosiGam_diff_ElecPosi_from_chi_c[0]->Fill(
	  ((pElec_sm_0 + pPosi_sm_0 + pGamm_sm_0).M() - 
	   (pElec_sm_0 + pPosi_sm_0).M()),
	  ((pElec_sm_0 + pPosi_sm_0 + pGamm_sm_0).Pt()), 
	  branching[chi_c_name]);



	}
	
	if (IsElectronDetectedInCTS(pElec) &&
	    IsElectronDetectedInCTS(pPosi) &&
	    IsPhotonDetectedInPHOS(pGamm)   &&
	    pGamm.E() > 5.0){// condition 2
	  
	  hChi_c_pt_y_cndtn_2[chi_c_name]->Fill(chi_c_pt, chi_c_y, 
						branching[chi_c_name]);
	  hChi_c_pt_y_cndtn_2[3]->Fill(chi_c_pt, chi_c_y, 
				       branching[chi_c_name]);
	  
	  hChi_c_electron_pt_y_cndtn_2[chi_c_name]->Fill(elec_pt, elec_y, 
							 branching[chi_c_name]);
	  hChi_c_electron_pt_y_cndtn_2[3]->Fill(elec_pt, elec_y, 
						branching[chi_c_name]);
	  
	  hChi_c_positron_pt_y_cndtn_2[chi_c_name]->Fill(posi_pt, posi_y, 
							 branching[chi_c_name]);
	  hChi_c_positron_pt_y_cndtn_2[3]->Fill(posi_pt, posi_y, 
						branching[chi_c_name]);
	  
	  hChi_c_gamma_pt_y_cndtn_2[chi_c_name]->Fill(gamma_pt, gamma_y, 
						      branching[chi_c_name]);
	  hChi_c_gamma_pt_y_cndtn_2[3]->Fill(gamma_pt, gamma_y, 
					     branching[chi_c_name]);

	  hMassElecPosiGam_diff_ElecPosi_from_chi_c[1]->Fill(
	  ((pElec_sm_0 + pPosi_sm_0 + pGamm_sm_0).M() - 
	   (pElec_sm_0 + pPosi_sm_0).M()),
	  ((pElec_sm_0 + pPosi_sm_0 + pGamm_sm_0).Pt()), 
	  branching[chi_c_name]);

	  
	  
	}
	
	if (IsPhotonDetectedInEMCAL(pElec) &&
	    IsPhotonDetectedInEMCAL(pPosi) &&
	    IsPhotonDetectedInPHOS(pGamm)){// condition 3
	  
	  hChi_c_pt_y_cndtn_3[chi_c_name]->Fill(chi_c_pt, chi_c_y, 
						branching[chi_c_name]);
	  hChi_c_pt_y_cndtn_3[3]->Fill(chi_c_pt, chi_c_y, 
				       branching[chi_c_name]);
	  
	  hChi_c_electron_pt_y_cndtn_3[chi_c_name]->Fill(elec_pt, elec_y, 
							 branching[chi_c_name]);
	  hChi_c_electron_pt_y_cndtn_3[3]->Fill(elec_pt, elec_y, 
						branching[chi_c_name]);
	  
	  hChi_c_positron_pt_y_cndtn_3[chi_c_name]->Fill(posi_pt, posi_y, 
							 branching[chi_c_name]);
	  hChi_c_positron_pt_y_cndtn_3[3]->Fill(posi_pt, posi_y, 
						branching[chi_c_name]);
	  
	  hChi_c_gamma_pt_y_cndtn_3[chi_c_name]->Fill(gamma_pt, gamma_y, 
						      branching[chi_c_name]);
	  hChi_c_gamma_pt_y_cndtn_3[3]->Fill(gamma_pt, gamma_y, 
					     branching[chi_c_name]);

	  hMassElecPosiGam_diff_ElecPosi_from_chi_c[2]->Fill(
	  ((pElec_sm_0 + pPosi_sm_0 + pGamm_sm_0).M() - 
	   (pElec_sm_0 + pPosi_sm_0).M()),
	  ((pElec_sm_0 + pPosi_sm_0 + pGamm_sm_0).Pt()), 
	  branching[chi_c_name]);


	  
	}
	
	if (IsElectronDetectedInALICE3(pElec, 2) &&
	    IsElectronDetectedInALICE3(pPosi, 2) &&
	    IsElectronDetectedInALICE3(pGamm, 1)){// condition 4
	  
	  hChi_c_pt_y_cndtn_4[chi_c_name]->Fill(chi_c_pt, chi_c_y, 
						branching[chi_c_name]);
	  hChi_c_pt_y_cndtn_4[3]->Fill(chi_c_pt, chi_c_y, 
				       branching[chi_c_name]);
	  
	  hChi_c_electron_pt_y_cndtn_4[chi_c_name]->Fill(elec_pt, elec_y, 
							 branching[chi_c_name]);
	  hChi_c_electron_pt_y_cndtn_4[3]->Fill(elec_pt, elec_y, 
						branching[chi_c_name]);
	  
	  hChi_c_positron_pt_y_cndtn_4[chi_c_name]->Fill(posi_pt, posi_y, 
							 branching[chi_c_name]);
	  hChi_c_positron_pt_y_cndtn_4[3]->Fill(posi_pt, posi_y, 
						branching[chi_c_name]);
	  
	  hChi_c_gamma_pt_y_cndtn_4[chi_c_name]->Fill(gamma_pt, gamma_y, 
						      branching[chi_c_name]);
	  hChi_c_gamma_pt_y_cndtn_4[3]->Fill(gamma_pt, gamma_y, 
					     branching[chi_c_name]);

	  hMassElecPosiGam_diff_ElecPosi_from_chi_c[3]->Fill(
	  ((pElec_sm_1 + pPosi_sm_1 + pGamm_sm_0).M() - 
	   (pElec_sm_1 + pPosi_sm_1).M()),
	  ((pElec_sm_1 + pPosi_sm_1 + pGamm_sm_0).Pt()), 
	  branching[chi_c_name]);

	  hMassElecPosiGam_diff_ElecPosi_from_chi_c[4]->Fill(
	  ((pElec_sm_2 + pPosi_sm_2 + pGamm_sm_0).M() - 
	   (pElec_sm_2 + pPosi_sm_2).M()),
	  ((pElec_sm_2 + pPosi_sm_2 + pGamm_sm_0).Pt()), 
	  branching[chi_c_name]);

	  hMassElecPosiGam_diff_ElecPosi_from_chi_c[5]->Fill(
	  ((pElec_sm_3 + pPosi_sm_3 + pGamm_sm_1).M() - 
	   (pElec_sm_3 + pPosi_sm_3).M()),
	  ((pElec_sm_3 + pPosi_sm_3 + pGamm_sm_1).Pt()), 
	  branching[chi_c_name]);
	  
	}

	//Fill histograms for Jpsi from chic decays
	if (IsElectronDetectedInCTS(pElec) &&
	    IsElectronDetectedInCTS(pPosi)){
	  hMassElecPosi_from_Jpsi[0]->Fill(
	  ((pElec_sm_0 + pPosi_sm_0).M()),
	  ((pElec_sm_0 + pPosi_sm_0).Pt()), 
	  branching[chi_c_name]);

	  hJpsi_from_chic[0]->Fill(
          ((pElec + pPosi).Pt()),
	  ((pElec + pPosi).Eta()),
	  branching[chi_c_name]);
	
	  hMassElecPosi_from_Jpsi[1]->Fill(
	  ((pElec_sm_0 + pPosi_sm_0).M()),
	  ((pElec_sm_0 + pPosi_sm_0).Pt()), 
	  branching[chi_c_name]);

	  hJpsi_from_chic[1]->Fill(
          ((pElec + pPosi).Pt()),
	  ((pElec + pPosi).Eta()),
	  branching[chi_c_name]);
	}

	if (IsPhotonDetectedInEMCAL(pElec) &&
	    IsPhotonDetectedInEMCAL(pPosi)){
	  hMassElecPosi_from_Jpsi[2]->Fill(
	  ((pElec_sm_0 + pPosi_sm_0).M()),
	  ((pElec_sm_0 + pPosi_sm_0).Pt()),
	  branching[chi_c_name]);

	  hJpsi_from_chic[2]->Fill(
          ((pElec + pPosi).Pt()),
	  ((pElec + pPosi).Eta()),
	  branching[chi_c_name]);
	}

	if (IsElectronDetectedInALICE3(pElec, 2) &&
	    IsElectronDetectedInALICE3(pPosi, 2)){
	  hMassElecPosi_from_Jpsi[3]->Fill(
	  ((pElec_sm_1 + pPosi_sm_1).M()),
	  ((pElec_sm_1 + pPosi_sm_1).Pt()),
	  branching[chi_c_name]);

	  hJpsi_from_chic[3]->Fill(
          ((pElec + pPosi).Pt()),
	  ((pElec + pPosi).Eta()),
	  branching[chi_c_name]);

	  hMassElecPosi_from_Jpsi[4]->Fill(
	  ((pElec_sm_2 + pPosi_sm_2).M()),
	  ((pElec_sm_2 + pPosi_sm_2).Pt()),
	  branching[chi_c_name]);

	  hJpsi_from_chic[4]->Fill(
          ((pElec + pPosi).Pt()),
	  ((pElec + pPosi).Eta()),
	  branching[chi_c_name]);

	  hMassElecPosi_from_Jpsi[5]->Fill(
	  ((pElec_sm_3 + pPosi_sm_3).M()),
	  ((pElec_sm_3 + pPosi_sm_3).Pt()),
	  branching[chi_c_name]);

	  hJpsi_from_chic[5]->Fill(
          ((pElec + pPosi).Pt()),
	  ((pElec + pPosi).Eta()),
	  branching[chi_c_name]);
	}
      }
    }  
  }
  
  if (chi_c_name == 3){//Just Jpsi for born Jpsi count
    //Find doughter of Jpsi
    int dghtJ1 = pythia->event[part_num].daughter1();
    int dghtJ2 = pythia->event[part_num].daughter2();
    
    
    //Select decay Jpsi to e-e+
    if (dghtJ2 - dghtJ1 == 1                             &&
	pythia->event[dghtJ1].id() == idElectron         &&
	pythia->event[dghtJ2].id() == (-1) * idElectron){   

      double elec_px = pythia->event[dghtJ1].px();
      double elec_py = pythia->event[dghtJ1].py();
      double elec_pz = pythia->event[dghtJ1].pz();
      double elec_p0 = pythia->event[dghtJ1].e(); 
      
      double posi_px = pythia->event[dghtJ2].px();
      double posi_py = pythia->event[dghtJ2].py();
      double posi_pz = pythia->event[dghtJ2].pz();
      double posi_p0 = pythia->event[dghtJ2].e();   
	
      TLorentzVector pElec(elec_px, elec_py, elec_pz, elec_p0);
      TLorentzVector pPosi(posi_px, posi_py, posi_pz, posi_p0);
      
      TLorentzVector pElec_sm_0 = resolutionElectron(pElec, 0);
      TLorentzVector pElec_sm_1 = resolutionElectron(pElec, 1);
      TLorentzVector pElec_sm_2 = resolutionElectron(pElec, 2);
      TLorentzVector pElec_sm_3 = resolutionElectron(pElec, 3);
	
      TLorentzVector pPosi_sm_0 = resolutionElectron(pPosi, 0);
      TLorentzVector pPosi_sm_1 = resolutionElectron(pPosi, 1);
      TLorentzVector pPosi_sm_2 = resolutionElectron(pPosi, 2);
      TLorentzVector pPosi_sm_3 = resolutionElectron(pPosi, 3);

      //Fill histograms for firstly Jpsi decays
      if (IsElectronDetectedInCTS(pElec) &&
	  IsElectronDetectedInCTS(pPosi)){
	hMassElecPosi_from_Jpsi[0]->Fill(
	((pElec_sm_0 + pPosi_sm_0).M()),
	((pElec_sm_0 + pPosi_sm_0).Pt()), 
	branching[chi_c_name]);
	
	hJpsi_from_chic[0]->Fill(
        ((pElec + pPosi).Pt()),
	((pElec + pPosi).Eta()),
	branching[chi_c_name]);
	
	hMassElecPosi_from_Jpsi[1]->Fill(
	((pElec_sm_0 + pPosi_sm_0).M()),
	((pElec_sm_0 + pPosi_sm_0).Pt()), 
	branching[chi_c_name]);

	hJpsi_from_chic[1]->Fill(
	((pElec + pPosi).Pt()),
	((pElec + pPosi).Eta()),
	branching[chi_c_name]);
      }

      if (IsPhotonDetectedInEMCAL(pElec) &&
	  IsPhotonDetectedInEMCAL(pPosi)){
	hMassElecPosi_from_Jpsi[2]->Fill(
	((pElec_sm_0 + pPosi_sm_0).M()),
	((pElec_sm_0 + pPosi_sm_0).Pt()),
	branching[chi_c_name]);

	hJpsi_from_chic[2]->Fill(
        ((pElec + pPosi).Pt()),
	((pElec + pPosi).Eta()),
	branching[chi_c_name]);
      }

      if (IsElectronDetectedInALICE3(pElec, 2) &&
	  IsElectronDetectedInALICE3(pPosi, 2)){
	hMassElecPosi_from_Jpsi[3]->Fill(
	((pElec_sm_1 + pPosi_sm_1).M()),
	((pElec_sm_1 + pPosi_sm_1).Pt()),
	branching[chi_c_name]);

	hJpsi_from_chic[3]->Fill(
	((pElec + pPosi).Pt()),
	((pElec + pPosi).Eta()),
	branching[chi_c_name]);

	hMassElecPosi_from_Jpsi[4]->Fill(
	((pElec_sm_2 + pPosi_sm_2).M()),
	((pElec_sm_2 + pPosi_sm_2).Pt()),
	branching[chi_c_name]);

	hJpsi_from_chic[4]->Fill(
	((pElec + pPosi).Pt()),
	((pElec + pPosi).Eta()),
	branching[chi_c_name]);

	hMassElecPosi_from_Jpsi[5]->Fill(
	((pElec_sm_3 + pPosi_sm_3).M()),
	((pElec_sm_3 + pPosi_sm_3).Pt()),
	branching[chi_c_name]);

	hJpsi_from_chic[5]->Fill(
	((pElec + pPosi).Pt()),
	((pElec + pPosi).Eta()),
	branching[chi_c_name]);
      }
    }
  }
  return;
}
