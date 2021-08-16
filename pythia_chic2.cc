// Stdlib header file for input and output.
#include <iostream>

// Header file to access Pythia 8 program elements.
// #include "Pythia8/Pythia.h"
#include "Pythia8/Pythia.h"

// ROOT, for histogramming.
#include "TH1.h"
#include "TH2.h"

// ROOT, for interactive graphics.
#include "TVirtualPad.h"
#include "TApplication.h"

// ROOT, to set random seed (Pythia random seed based on tume does not work!)
#include "TRandom.h"
#include "TMath.h"

// ROOT, for saving file.
#include "TFile.h"

#include "TLorentzVector.h"

using namespace Pythia8;


void Init(Pythia*);
void Histogram_creator(TH2F**, TH2F**, TH2F**, TH2F**, TH2F**,
		       TH2F**, TH2F**, TH2F**, TH2F**, TH2F**,
		       TH2F**, TH2F**, TH2F**, TH2F**, TH2F**,
		       TH2F**, TH2F**, TH2F**, TH2F**, TH2F**,
		       TH2F**, TH2F**, TH2F**, TH2F**, TH2F**, 
		       TH2F**, TH2F**, TH2F**, TH2F**, TH2F**);
void ROOT_file_creator(TH2F**, TH2F**, TH2F**, TH2F**, TH2F**,
		       TH2F**, TH2F**, TH2F**, TH2F**, TH2F**,
		       TH2F**, TH2F**, TH2F**, TH2F**, TH2F**,
		       TH2F**, TH2F**, TH2F**, TH2F**, TH2F**,
		       TH2F**, TH2F**, TH2F**, TH2F**, TH2F**,
		       TH2F**, TH2F**, TH2F**, TH2F**, TH2F**,  
		       TH1F*);
void Background_handler (Pythia*, int *, int*, int*, int, int, int, 
			 TLorentzVector*, TLorentzVector*, TLorentzVector*, 
			 TLorentzVector*, TLorentzVector*, TLorentzVector*, 
			 TLorentzVector*, TLorentzVector*, TLorentzVector*, 
			 TLorentzVector*,
			 TH2F**, TH2F**, TH2F**, TH2F**, TH2F**, TH2F**, TH2F**, 
			 double);
void Signal_event_handler(Pythia*, int, int,
			  TH2F**, TH2F**, TH2F**, TH2F**, TH2F**,
			  TH2F**, TH2F**, TH2F**, TH2F**, TH2F**,
			  TH2F**, TH2F**, TH2F**, TH2F**, TH2F**,
			  TH2F**, TH2F**, TH2F**, TH2F**, TH2F**,
			  TH2F**, TH2F**, TH2F**,
			  double*);



int main(int argc, char* argv[]) {


  // read input parameters
  printf("argc = %d, argv[0] = %s\n",argc,argv[0]);
  if (argc != 2) {
    printf("Usage: %s <nEvents>\n",argv[0]);
    printf("       <nEvents>=0 is the number of events to generate.\n");
    return 1;
  }

  
  int nEvents = atoi(argv[1]);
  cout << "nEvents = " << nEvents << endl;

  // Create the ROOT application environment. 
  TApplication theApp("hist", &argc, argv);

  Pythia pythia;

  Init(&(pythia));

  cout << "List all decays of particle 10441, 20443, 445\n";
  
  pythia.particleData.list(10441);
  pythia.particleData.list(20443);
  pythia.particleData.list(445);

  
  /*define arrays of branching, which we are going to use when generate only
    charmonium decays*/


  //double chic_final_br[4] = {7.5819e-04, 202.383e-04, 114.624e-04, 5.971e-2};
  double all_final_br[4] = {1., 1., 1., 1.};
  

  //define particles id from Pythia8 


  const int idChic0        =  10441;
  const int idChic1        =  20443;
  const int idChic2        =  445;
  const int idJpsi         =  443;
  const int idElectron     =  11;
  const int idPhoton       =  22;

  
  // create histograms

  //Histograms for particles
  
  //All chi_c in event
  TH2F* hChi_c_pt_y[4];
  TH2F* hChi_c_electron_pt_y[4];
  TH2F* hChi_c_positron_pt_y[4];
  TH2F* hChi_c_gamma_pt_y[4];
  
  //chi_c in event with cndtn_1
  TH2F* hChi_c_pt_y_cndtn_1[4];
  TH2F* hChi_c_electron_pt_y_cndtn_1[4];
  TH2F* hChi_c_positron_pt_y_cndtn_1[4];
  TH2F* hChi_c_gamma_pt_y_cndtn_1[4];
  
  //chi_c in event with cndtn_1
  TH2F* hChi_c_pt_y_cndtn_2[4];
  TH2F* hChi_c_electron_pt_y_cndtn_2[4];
  TH2F* hChi_c_positron_pt_y_cndtn_2[4];
  TH2F* hChi_c_gamma_pt_y_cndtn_2[4];  
  
  //chi_c in event with cndtn_1
  TH2F* hChi_c_pt_y_cndtn_3[4];
  TH2F* hChi_c_electron_pt_y_cndtn_3[4];
  TH2F* hChi_c_positron_pt_y_cndtn_3[4];
  TH2F* hChi_c_gamma_pt_y_cndtn_3[4];
    
  //chi_c in event with cndtn_1
  TH2F* hChi_c_pt_y_cndtn_4[4];
  TH2F* hChi_c_electron_pt_y_cndtn_4[4];
  TH2F* hChi_c_positron_pt_y_cndtn_4[4];
  TH2F* hChi_c_gamma_pt_y_cndtn_4[4];

  //e+e-gamma from event in aceptance
  TH2F* hElectron_pt_y_event[6];
  TH2F* hPositron_pt_y_event[6];
  TH2F* hGamma_pt_y_event[6];

  //Histograms for invariant mass spectrum


  TH2F* hMassElecPosiGam_diff_ElecPosi_from_chi_c[6];
  TH2F* hMassElecPosiGam_diff_ElecPosi_from_backg[6];
  TH2F* hMassElecPosi_from_Jpsi[6];
  TH2F* hMassElecPosi_from_cand[6];
  TH2F* hMassElecPosi_from_even[6];
  
  
  //Histogram for Jpsi and Jpsi candidates


  TH2F* hJpsi_from_chic[6];
  TH2F* hJpsi_from_cand[6];

  Histogram_creator(&(hChi_c_pt_y[0]),
		    &(hChi_c_electron_pt_y[0]),
		    &(hChi_c_positron_pt_y[0]),
		    &(hChi_c_gamma_pt_y[0]),
		    &(hChi_c_pt_y_cndtn_1[0]),
		    &(hChi_c_electron_pt_y_cndtn_1[0]),
		    &(hChi_c_positron_pt_y_cndtn_1[0]),
		    &(hChi_c_gamma_pt_y_cndtn_1[0]),
		    &(hChi_c_pt_y_cndtn_2[0]),
		    &(hChi_c_electron_pt_y_cndtn_2[0]),
		    &(hChi_c_positron_pt_y_cndtn_2[0]),
		    &(hChi_c_gamma_pt_y_cndtn_2[0]),
		    &(hChi_c_pt_y_cndtn_3[0]),
		    &(hChi_c_electron_pt_y_cndtn_3[0]),
		    &(hChi_c_positron_pt_y_cndtn_3[0]),
		    &(hChi_c_gamma_pt_y_cndtn_3[0]),
		    &(hChi_c_pt_y_cndtn_4[0]),
		    &(hChi_c_electron_pt_y_cndtn_4[0]),
		    &(hChi_c_positron_pt_y_cndtn_4[0]),
		    &(hChi_c_gamma_pt_y_cndtn_4[0]), 
		    &(hElectron_pt_y_event[0]), 
		    &(hPositron_pt_y_event[0]), 
		    &(hGamma_pt_y_event[0]),
		    &(hMassElecPosiGam_diff_ElecPosi_from_chi_c[0]),
		    &(hMassElecPosiGam_diff_ElecPosi_from_backg[0]),
		    &(hMassElecPosi_from_Jpsi[0]),
		    &(hMassElecPosi_from_cand[0]),
		    &(hMassElecPosi_from_even[0]),
		    &(hJpsi_from_chic[0]), 
		    &(hJpsi_from_cand[0]));

  
  int nEvent2Print = 10;

  // Begin event loop. Generate event

  const int max_num_of_part = 10000;

  int elec_num = 0;
  int posi_num = 0;
  int gamm_num = 0;
  int elec[max_num_of_part];
  int posi[max_num_of_part];
  int gamm[max_num_of_part];
  TLorentzVector elec_data[max_num_of_part][4];
  TLorentzVector posi_data[max_num_of_part][4];
  TLorentzVector gamma_data[max_num_of_part][2];
  TLorentzVector elec_true_data[max_num_of_part];
  TLorentzVector posi_true_data[max_num_of_part];
  TLorentzVector Jpsi_data_ALICE0_1[max_num_of_part];
  TLorentzVector Jpsi_data_ALICE0_2[max_num_of_part];
  TLorentzVector Jpsi_data_ALICE3_1[max_num_of_part];
  TLorentzVector Jpsi_data_ALICE3_2[max_num_of_part];
  TLorentzVector Jpsi_data_ALICE3_3[max_num_of_part];

  int iEvent2Print = 0;

  
  for (int iEvent = 0; iEvent < nEvents; ++iEvent) {
    if (!pythia.next()) continue;

    // print first nEvent2Print events
    if (iEvent2Print < nEvent2Print) pythia.event.list();
    iEvent2Print++;

    bool Jpsi_first = true;
    int chi_c_num = -1;
    double event_weight = 1.;
    int charm_number = 0;

    // Loop over all particles in the generated event    
    for (int i = 0; i < pythia.event.size(); ++i) {

      //Handle true charmonium event: 
      if (((pythia.event[i].id() == idChic0) && 
	   (pythia.event[i].status() == -62))        ||
	  ((pythia.event[i].id() == idChic1) && 
	   (pythia.event[i].status() == -62))        ||
	  ((pythia.event[i].id() == idChic2) && 
	   (pythia.event[i].status() == -62))        ||
	  ((pythia.event[i].id() == idJpsi)  && 
	   (pythia.event[i].status() == -91))){
	charm_number++;
	bool count_ev = true;
	
	if ((pythia.event[i].id() == idChic0) ||
	    (pythia.event[i].id() == idChic1) ||
	    (pythia.event[i].id() == idChic2)){
	  
	  Jpsi_first = false;

	  if(pythia.event[i].id() == idChic0){
	    chi_c_num = 0;
	  }
	  
	  if(pythia.event[i].id() == idChic1){
	    chi_c_num = 1;
	  }
	  
	  if(pythia.event[i].id() == idChic2){
	    chi_c_num = 2;
	  }
	}
	
	if ((pythia.event[i].id() == idJpsi) && 
	    (Jpsi_first == true)){
	  chi_c_num = 3;
	} 
	if ((pythia.event[i].id() == idJpsi) && 
	    (Jpsi_first == false)){
	  count_ev = false;
	} 

	
	
	/*Evaluate event_weight -- weight, which are going from 
	  charmonium decays branching

	  
	  Attention! Array chic_final_br use only for charmonium generator
	  configuration! For other configuration use all_final_br*/

	//event_weight = all_final_br[chi_c_num];
	event_weight = 0.03632;
     	if (count_ev && charm_number == 1){
	  Signal_event_handler(&(pythia), chi_c_num, i,
			       &(hChi_c_pt_y[0]),
			       &(hChi_c_electron_pt_y[0]),
			       &(hChi_c_positron_pt_y[0]),
			       &(hChi_c_gamma_pt_y[0]),
			       &(hChi_c_pt_y_cndtn_1[0]),
			       &(hChi_c_electron_pt_y_cndtn_1[0]),
			       &(hChi_c_positron_pt_y_cndtn_1[0]),
			       &(hChi_c_gamma_pt_y_cndtn_1[0]),
			       &(hChi_c_pt_y_cndtn_2[0]),
			       &(hChi_c_electron_pt_y_cndtn_2[0]),
			       &(hChi_c_positron_pt_y_cndtn_2[0]),
			       &(hChi_c_gamma_pt_y_cndtn_2[0]),
			       &(hChi_c_pt_y_cndtn_3[0]),
			       &(hChi_c_electron_pt_y_cndtn_3[0]),
			       &(hChi_c_positron_pt_y_cndtn_3[0]),
			       &(hChi_c_gamma_pt_y_cndtn_3[0]),
			       &(hChi_c_pt_y_cndtn_4[0]),
			       &(hChi_c_electron_pt_y_cndtn_4[0]),
			       &(hChi_c_positron_pt_y_cndtn_4[0]),
			       &(hChi_c_gamma_pt_y_cndtn_4[0]),
			       &(hMassElecPosiGam_diff_ElecPosi_from_chi_c[0]),
			       &(hMassElecPosi_from_Jpsi[0]),
			       &(hJpsi_from_chic[0]),
			       &(all_final_br[0]));/*ATTENTION: array 
						    chic_final_br use only 
						    for charmonium generator 
						    configuration! For other 
						    configuration use 
						    all_final_br*/
	}
	
	
      }
      
      /*Handle background events.
	For that we need:
	
	1) Find all electrons and create arrays of their index.
	2) Find all positrons and create arrays of their index.
	3) Find all photons and create arrays of their index.*/
      
      if ((pythia.event[i].id() == idElectron)        &&
	  (elec_num <= max_num_of_part - 2)            ){
	*(elec + elec_num) = i;
	elec_num++;
      }
      
      if ((pythia.event[i].id() == -1 * idElectron)   &&
	  (posi_num <= max_num_of_part - 2)            ){	
	*(posi + posi_num) = i;
	posi_num++;
      }
      
      if ((pythia.event[i].id() == idPhoton)          &&
	  (gamm_num <= max_num_of_part - 2)            ){	
	*(gamm + gamm_num) = i;
	gamm_num++;
      }
      
    } // End of particle loop

    //in that place we should call Background handler

    //Print event_weight
    Background_handler(&(pythia), elec, posi, gamm, 
		       elec_num, posi_num, gamm_num, 
		       &(elec_data[0][0]), 
		       &(posi_data[0][0]), 
		       &(gamma_data[0][0]), 
		       elec_true_data, posi_true_data, 
		       Jpsi_data_ALICE0_1,
		       Jpsi_data_ALICE0_2,
		       Jpsi_data_ALICE3_1,
		       Jpsi_data_ALICE3_2,
		       Jpsi_data_ALICE3_3,
		       &(hMassElecPosiGam_diff_ElecPosi_from_backg[0]),
		       &(hMassElecPosi_from_cand[0]),
		       &(hMassElecPosi_from_even[0]),
		       &(hJpsi_from_cand[0]),
		       &(hElectron_pt_y_event[0]),
		       &(hPositron_pt_y_event[0]),
		       &(hGamma_pt_y_event[0]),
		       event_weight);
    
    elec_num = 0;
    posi_num = 0;
    gamm_num = 0;
  
  } // End of event loop
  
  // Statistics on event generation.
  pythia.stat();

  
  TH1F *hCross_section_hist = new TH1F("hCross_section_hist", "xsection and ntrials data", 2, 0., 1.);


  double xsection = pythia.info.sigmaGen();
  int ntrials  = pythia.info.nAccepted();

  hCross_section_hist->SetBinContent(1, xsection);
  hCross_section_hist->SetBinContent(2, ntrials);
    

  ROOT_file_creator(&(hChi_c_pt_y[0]),
		    &(hChi_c_electron_pt_y[0]),
		    &(hChi_c_positron_pt_y[0]),
		    &(hChi_c_gamma_pt_y[0]),
		    &(hChi_c_pt_y_cndtn_1[0]),
		    &(hChi_c_electron_pt_y_cndtn_1[0]),
		    &(hChi_c_positron_pt_y_cndtn_1[0]),
		    &(hChi_c_gamma_pt_y_cndtn_1[0]),
		    &(hChi_c_pt_y_cndtn_2[0]),
		    &(hChi_c_electron_pt_y_cndtn_2[0]),
		    &(hChi_c_positron_pt_y_cndtn_2[0]),
		    &(hChi_c_gamma_pt_y_cndtn_2[0]),
		    &(hChi_c_pt_y_cndtn_3[0]),
		    &(hChi_c_electron_pt_y_cndtn_3[0]),
		    &(hChi_c_positron_pt_y_cndtn_3[0]),
		    &(hChi_c_gamma_pt_y_cndtn_3[0]),
		    &(hChi_c_pt_y_cndtn_4[0]),
		    &(hChi_c_electron_pt_y_cndtn_4[0]),
		    &(hChi_c_positron_pt_y_cndtn_4[0]),
		    &(hChi_c_gamma_pt_y_cndtn_4[0]), 
		    &(hElectron_pt_y_event[0]), 
		    &(hPositron_pt_y_event[0]), 
		    &(hGamma_pt_y_event[0]),
		    &(hMassElecPosiGam_diff_ElecPosi_from_chi_c[0]),
		    &(hMassElecPosiGam_diff_ElecPosi_from_backg[0]),
		    &(hMassElecPosi_from_Jpsi[0]),
		    &(hMassElecPosi_from_cand[0]),
		    &(hMassElecPosi_from_even[0]),
		    &(hJpsi_from_chic[0]), 
		    &(hJpsi_from_cand[0]),
		    hCross_section_hist);


  return 0;
}
