 #include "TLorentzVector.h"
#include "TH1.h"
#include "TH2.h"

bool IsElectronDetectedInCTS(TLorentzVector);
bool IsPhotonDetectedInEMCAL(TLorentzVector);
bool IsPhotonDetectedInPHOS(TLorentzVector); 
bool IsElectronDetectedInALICE3(TLorentzVector, int);

void Invariant_mass_spectr_creator(TLorentzVector p_el_0, 
				   TLorentzVector p_el_1,
				   TLorentzVector p_el_2,
				   TLorentzVector p_el_3,
				   TLorentzVector p_pos_0, 
				   TLorentzVector p_pos_1,
				   TLorentzVector p_pos_2,
				   TLorentzVector p_pos_3,
				   TLorentzVector p_gam_0,
				   TLorentzVector p_gam_1,
				   TH2F *hMassElecPosi,
				   TH2F *hMassGamElecPosi,
				   TH2F *hMassGamElecPosi_diff,
				   TH2F *hMassGamElecPosi_cndtn_1,
				   TH2F *hMassGamElecPosi_cndtn_2,
				   TH2F *hMassGamElecPosi_cndtn_3,
				   TH2F *hMassGamElecPosi_mass_diff,
				   TH2F *hMassGamElecPosi_mass_diff_cndtn_1,
				   TH2F *hMassGamElecPosi_mass_diff_cndtn_2,
				   TH2F *hMassGamElecPosi_mass_diff_cndtn_3, 
				   TH2F *hMassGamElecPosi_background_mass_diff_ALICE3_1, 
				   TH2F *hMassGamElecPosi_background_mass_diff_ALICE3_2, 
				   TH2F *hMassGamElecPosi_background_mass_diff_ALICE3_3,
				   double br)
{
  
  hMassGamElecPosi->Fill((p_el_0 + p_pos_0 + p_gam_0).M(), (p_el_0 + p_pos_0 + p_gam_0).Pt(), br);
  hMassGamElecPosi_diff->Fill((p_el_0 + p_pos_0 + p_gam_0).M() - (p_el_0 + p_pos_0).M(), (p_el_0 + p_pos_0 + p_gam_0).Pt(), br);
  hMassElecPosi->Fill((p_el_0 + p_pos_0).M(), (p_el_0 + p_pos_0).Pt(), br);
  hMassGamElecPosi_mass_diff->Fill((p_el_0 + p_pos_0 + p_gam_0).M() - (p_el_0 + p_pos_0).M(), 
				   (p_el_0 + p_pos_0 + p_gam_0).Pt(), br);
  
  if (IsElectronDetectedInCTS(p_el_0)  &&
      IsElectronDetectedInCTS(p_pos_0) &&
      IsPhotonDetectedInPHOS(p_gam_0))
    {
      
      hMassGamElecPosi_cndtn_1->Fill((p_el_0 + p_pos_0 + p_gam_0).M(), (p_el_0 + p_pos_0 + p_gam_0).Pt(), br);
      hMassGamElecPosi_mass_diff_cndtn_1->Fill((p_el_0 + p_pos_0 + p_gam_0).M() - (p_el_0 + p_pos_0).M(),
					       (p_el_0 + p_pos_0 + p_gam_0).Pt(), br);
    }
  
  if (IsElectronDetectedInCTS(p_el_0)   &&
      IsElectronDetectedInCTS(p_pos_0) &&
      IsPhotonDetectedInPHOS(p_gam_0)   &&
      p_gam_0.E() > 5.0)
    {
      
      hMassGamElecPosi_cndtn_2->Fill((p_el_0 + p_pos_0 + p_gam_0).M(), (p_el_0 + p_pos_0 + p_gam_0).Pt(), br);
      hMassGamElecPosi_mass_diff_cndtn_2->Fill((p_el_0 + p_pos_0 + p_gam_0).M() - (p_el_0 + p_pos_0).M(), 
					       (p_el_0 + p_pos_0 + p_gam_0).Pt(), br);
    }

  if (IsPhotonDetectedInEMCAL(p_el_0)  &&
      IsPhotonDetectedInEMCAL(p_pos_0) &&
      IsPhotonDetectedInPHOS(p_gam_0))
    {
      
      hMassGamElecPosi_cndtn_3->Fill((p_el_0 + p_pos_0 + p_gam_0).M(), (p_el_0 + p_pos_0 + p_gam_0).Pt(), br);
      hMassGamElecPosi_mass_diff_cndtn_3->Fill((p_el_0 + p_pos_0 + p_gam_0).M() - (p_el_0 + p_pos_0).M(), 
					       (p_el_0 + p_pos_0 + p_gam_0).Pt(), br);
    }
  
  if (IsElectronDetectedInALICE3(p_el_1, 2)  &&
      IsElectronDetectedInALICE3(p_pos_1, 2) &&
      IsElectronDetectedInALICE3(p_gam_0, 1))
    {
      
      hMassGamElecPosi_background_mass_diff_ALICE3_1->Fill((p_el_1 + p_pos_1 + p_gam_0).M() - (p_el_1 + p_pos_1).M(), 
							   (p_el_1 + p_pos_1 + p_gam_0).Pt(), br);
    }
  
  if (IsElectronDetectedInALICE3(p_el_2, 2)  &&
      IsElectronDetectedInALICE3(p_pos_2, 2) &&
      IsElectronDetectedInALICE3(p_gam_0, 1))
    {
      
      hMassGamElecPosi_background_mass_diff_ALICE3_2->Fill((p_el_2 + p_pos_2 + p_gam_0).M() - (p_el_2 + p_pos_2).M(), 
							   (p_el_2 + p_pos_2 + p_gam_0).Pt(), br);
    }
  
  if (IsElectronDetectedInALICE3(p_el_3, 2)  &&
      IsElectronDetectedInALICE3(p_pos_3, 2) &&
      IsElectronDetectedInALICE3(p_gam_1, 1))
    {
      
      hMassGamElecPosi_background_mass_diff_ALICE3_3->Fill((p_el_3 + p_pos_3 + p_gam_1).M() - (p_el_3 + p_pos_3).M(), 
							   (p_el_3 + p_pos_3 + p_gam_1).Pt(), br);
    }
  return;
}
