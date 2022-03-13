#include <iostream>
#include <TFile.h>
#include <TTree.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TLorentzVector.h>

bool IsElectronDetectedInALICE3(TLorentzVector, int);
bool IsElectronDetectedInCTS(TLorentzVector);
bool IsPhotonDetectedInEMCAL(TLorentzVector);
bool IsPhotonDetectedInPHOS(TLorentzVector);

int main(){
  
  TFile* input = new TFile("TTree_test.root");
  TFile* output = new TFile("output.root", "RECREATE");
  TTree* tree = (TTree*)input->Get("Tree");
  tree->Print();

  int n = tree->GetEntries();
  printf("Number of entries: %10d\n", n);

  int number_electron_in_event;
  int number_positron_in_event;
  int number_photon_in_event;


  Double_t electron_px[1000]; 
  Double_t electron_py[1000]; 
  Double_t electron_pz[1000]; 
  Double_t electron_p0[1000];
  Double_t positron_px[1000];
  Double_t positron_py[1000];
  Double_t positron_pz[1000]; 
  Double_t positron_p0[1000];
  Double_t photon_px[1000], photon_py[1000], photon_pz[1000], photon_p0[1000];


  tree->SetBranchAddress("number_electron_in_event", &number_electron_in_event);
  tree->SetBranchAddress("number_positron_in_event", &number_positron_in_event);
  tree->SetBranchAddress("number_photon_in_event", &number_photon_in_event);
  
  tree->SetBranchAddress("electron_px", electron_px);
  tree->SetBranchAddress("electron_py", electron_py);
  tree->SetBranchAddress("electron_pz", electron_pz);
  tree->SetBranchAddress("electron_p0", electron_p0);

  tree->SetBranchAddress("positron_px", positron_px);
  tree->SetBranchAddress("positron_py", positron_py);
  tree->SetBranchAddress("positron_pz", positron_pz);
  tree->SetBranchAddress("positron_p0", positron_p0);

  tree->SetBranchAddress("photon_px", photon_px);
  tree->SetBranchAddress("photon_py", photon_py);
  tree->SetBranchAddress("photon_pz", photon_pz);
  tree->SetBranchAddress("photon_p0", photon_p0);



  TH1D* hist_test01 = new TH1D("h01", "M(e^{-}), GeV/c^{2}", 30, 0.000505, 0.000515);
  TH2D* hist_test02 = new TH2D("h02", "M(e^{+}e^{-}), GeV/c^{2}", 100, 0., 3.5, 50, 0., 50.);
  TH2D* hist_test03 = new TH2D("h03", "M(e^{+}e^{-}#gamma), GeV/c^{2}", 100, 3., 4., 50, 0., 50.);
  TH2D* hist_test04 = new TH2D("h04", "M(e^{+}e^{-}#gamma) - M(e^{+}e^{-}), GeV/c^{2}", 100, 0., 0.8, 50, 0., 50.);
  TH2D* hist_test05 = new TH2D("h05", "M(e^{+}e^{-}) in acceptance ALICE3, GeV/c^{2}", 100, 0., 3.5, 50, 0., 50.);
  TH2D* hist_test06 = new TH2D("h06", "M(e^{+}e^{-}#gamma) in acceptance ALICE3, GeV/c^{2}", 100, 3., 4., 50, 0., 50.);
  TH2D* hist_test07 = new TH2D("h07", "M(e^{+}e^{-}#gamma) - M(e^{+}e^{-}) in acceptance ALICE3, GeV/c^{2}", 100, 0., 0.8, 50, 0., 50.);
  TH2D* hist_test08 = new TH2D("h08", "M(e^{+}e^{-}) in acceptance CTS, GeV/c^{2}", 100, 0., 3.5, 50, 0., 50.);
  TH2D* hist_test09 = new TH2D("h09", "M(e^{+}e^{-}#gamma) in acceptance CTS and PHOS, GeV/c^{2}", 100, 3., 4., 50, 0., 50.);
  TH2D* hist_test10 = new TH2D("h10", "M(e^{+}e^{-}#gamma) - M(e^{+}e^{-}) in acceptance CTS and PHOS, GeV/c^{2}", 100, 0., 0.8, 50, 0., 50.);
  TH2D* hist_test11 = new TH2D("h11", "M(e^{+}e^{-}) in acceptance EMCAL, GeV/c^{2}", 100, 0., 3.5, 50, 0., 50.);
  TH2D* hist_test12 = new TH2D("h12", "M(e^{+}e^{-}#gamma) in acceptance EMCAL and PHOS, GeV/c^{2}", 100, 3., 4., 50, 0., 50.);
  TH2D* hist_test13 = new TH2D("h13", "M(e^{+}e^{-}#gamma) - M(e^{+}e^{-}) in acceptance EMCAL and PHOS, GeV/c^{2}", 100, 0., 0.8, 50, 0., 50.);

  
  for (int i = 0; i < n; i++){
    tree->GetEntry(i);
    TLorentzVector elec_data[number_electron_in_event];
    TLorentzVector posi_data[number_positron_in_event];
    TLorentzVector phot_data[number_photon_in_event];
    
    if(number_electron_in_event != 0){
      for (int k = 0; k < number_electron_in_event; k++){
	elec_data[k] = TLorentzVector(electron_px[k],
				      electron_py[k],
				      electron_pz[k],
				      electron_p0[k]);
      }
    }
      
    if(number_electron_in_event != 0){ 
      for (int l = 0; l < number_electron_in_event; l++){
	posi_data[l] = TLorentzVector(positron_px[l],
				      positron_py[l],
				      positron_pz[l],
				      positron_p0[l]);
      }
    }
      
    if(number_photon_in_event != 0){ 
      for (int m = 0; m < number_photon_in_event; m++){
	phot_data[m] = TLorentzVector(photon_px[m],
				      photon_py[m],
				      photon_pz[m],
				      photon_p0[m]);
      }
    }
    
    for (int a = 0; a < number_electron_in_event; a++){
      hist_test01->Fill((elec_data[a]).M());
      for (int b = 0; b < number_positron_in_event; b++){
	TLorentzVector tmp_all;
	tmp_all = elec_data[a] + posi_data[b];
       	hist_test02->Fill((tmp_all).M(), (tmp_all).Pt());
	for (int c = 0; c < number_photon_in_event; c++){
	  hist_test03->Fill((tmp_all + phot_data[c]).M(), 
			    (tmp_all + phot_data[c]).Pt());
	  hist_test04->Fill((tmp_all + phot_data[c]).M() - tmp_all.M(),
			    (tmp_all + phot_data[c]).Pt());
	}
	if (IsElectronDetectedInALICE3(elec_data[a], 1) &&
	    IsElectronDetectedInALICE3(posi_data[b], 1)){
	  TLorentzVector tmp_acc;
	  tmp_acc = elec_data[a] + posi_data[b];
	  hist_test05->Fill((tmp_acc).M(), (tmp_acc).Pt());
	  for (int c = 0; c < number_photon_in_event; c++){
	    if (IsElectronDetectedInALICE3(phot_data[c], 2)){
	      hist_test06->Fill((tmp_acc + phot_data[c]).M(), 
				(tmp_acc + phot_data[c]).Pt());
	      hist_test07->Fill((tmp_acc + phot_data[c]).M() - tmp_acc.M(),
				(tmp_acc + phot_data[c]).Pt());
	    }
	  }
	}
	if (IsElectronDetectedInCTS(elec_data[a]) &&
	    IsElectronDetectedInCTS(posi_data[b])){
	  TLorentzVector tmp_acc;
	  tmp_acc = elec_data[a] + posi_data[b];
	  hist_test08->Fill((tmp_acc).M(), (tmp_acc).Pt());
	  for (int c = 0; c < number_photon_in_event; c++){
	    if (IsPhotonDetectedInPHOS(phot_data[c])){
	      hist_test09->Fill((tmp_acc + phot_data[c]).M(), 
				(tmp_acc + phot_data[c]).Pt());
	      hist_test10->Fill((tmp_acc + phot_data[c]).M() - tmp_acc.M(),
				(tmp_acc + phot_data[c]).Pt());
	    }
	  }
	}
	if (IsPhotonDetectedInEMCAL(elec_data[a]) &&
	    IsPhotonDetectedInEMCAL(posi_data[b])){
	  TLorentzVector tmp_acc;
	  tmp_acc = elec_data[a] + posi_data[b];
	  hist_test11->Fill((tmp_acc).M(), (tmp_acc).Pt());
	  for (int c = 0; c < number_photon_in_event; c++){
	    if (IsPhotonDetectedInPHOS(phot_data[c])){
	      hist_test12->Fill((tmp_acc + phot_data[c]).M(), 
				(tmp_acc + phot_data[c]).Pt());
	      hist_test13->Fill((tmp_acc + phot_data[c]).M() - tmp_acc.M(),
				(tmp_acc + phot_data[c]).Pt());
	    }
	  }
	}
      }
    }
    if (i % 1000 == 0){
      printf("Handled events: %6d\n", i);
    } 
  }
  
  output->cd();
  
  hist_test01->Write();
  hist_test02->Write();
  hist_test03->Write();
  hist_test04->Write();
  hist_test05->Write();
  hist_test06->Write();
  hist_test07->Write();
  hist_test08->Write();
  hist_test09->Write();
  hist_test10->Write();
  hist_test11->Write();
  hist_test12->Write();
  hist_test13->Write();
  

  return 0;
}
