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
#include "TTree.h"
#include "AliEvent.h"
#include "AliParticle.h"
#include "TObject.h"

class AliParticle;
class AliEvent;

using namespace Pythia8;
 

void Init(Pythia*);
void ROOT_file_creator();

int main(int argc, char* argv[]) {


  // read input parameters
  printf("argc = %d, argv[0] = %s\n",argc,argv[0]);
  if (argc != 2) {
    printf("Usage: %s <nEvents>\n",argv[0]);
    printf("       <nEvents>=0 is the number of events to generate.\n");
    return 1;
  }

  char fn[1024];
  sprintf(fn, "%s", "TTree_test.root");
  TFile* outFile = new TFile(fn, "RECREATE");
  
  TTree *test_tree = new TTree("Tree", "Test_tree");
  test_tree->SetMaxTreeSize(1000000000);

  AliEvent* General_event = new AliEvent;
  AliParticle chi_c;
  AliParticle Jpsi;


  test_tree->Branch("AliEvent",&General_event);
  

  int nEvents = atoi(argv[1]);
  cout << "nEvents = " << nEvents << endl;

  //Create the ROOT application environment. 
  TApplication theApp("hist", &argc, argv);

  Pythia pythia;

  Init(&(pythia));

  cout << "List all decays of particle 10441, 20443, 445\n";
  
  pythia.particleData.list(10441);
  pythia.particleData.list(20443);
  pythia.particleData.list(445);
  

  //define particles id from Pythia8 


  const int idChic0        =  10441;
  const int idChic1        =  20443;
  const int idChic2        =  445;
  const int idJpsi         =  443;
  const int idElectron     =  11;
  const int idPhoton       =  22;
  
  int nEvent2Print = 10;

  // Begin event loop. Generate event

  int iEvent2Print = 0;
  
  for (int iEvent = 0; iEvent < nEvents; ++iEvent){
    if (!pythia.next()) continue;
    int number_of_electrons = 0;
    int number_of_positrons = 0;
    int number_of_photons   = 0;


    //print first nEvent2Print events
    if (iEvent2Print < nEvent2Print) //pythia.event.list();
    iEvent2Print++;

    // Loop over all particles in the generated event    
    for (int i = 0; i < pythia.event.size(); ++i){
      
      General_event->number_of_particle_in_event = pythia.event.size();
      
      if (fabs(pythia.event[i].eta()) > 4.){
	continue;
      }

      if (pythia.event[i].id() == idChic0 ||
	  pythia.event[i].id() == idChic1 ||
	  pythia.event[i].id() == idChic2){
	if (pythia.event[i].status() == -62){
	  chi_c.px = pythia.event[i].px();
	  chi_c.py = pythia.event[i].py();
	  chi_c.pz = pythia.event[i].pz();
	  chi_c.p0 = pythia.event[i].e();
	  chi_c.id = pythia.event[i].id();
	  chi_c.number_in_event = i;
	  chi_c.mother_number_in_event = pythia.event[i].mother1();
	  chi_c.mother_id = pythia.event[chi_c.mother_number_in_event].id();
	  chi_c.daughter_1_number_in_event =  pythia.event[i].daughter1();
	  chi_c.daughter_2_number_in_event =  pythia.event[i].daughter2();
	}
      }

      if (pythia.event[i].id() == idJpsi){
	Jpsi.px = pythia.event[i].px();
	Jpsi.py = pythia.event[i].py();
	Jpsi.pz = pythia.event[i].pz();
	Jpsi.p0 = pythia.event[i].e();
	Jpsi.id = pythia.event[i].id();
	Jpsi.number_in_event = i;
	Jpsi.mother_number_in_event = pythia.event[i].mother1();
	Jpsi.mother_id = pythia.event[chi_c.mother_number_in_event].id();
	Jpsi.daughter_1_number_in_event =  pythia.event[i].daughter1();
	Jpsi.daughter_2_number_in_event =  pythia.event[i].daughter2();
      }

      if (pythia.event[i].id() == idElectron){
	number_of_electrons++;
      }
      
      if (pythia.event[i].id() == -idElectron){
	number_of_positrons++;
      }
      
      if (pythia.event[i].id() == idPhoton){
	number_of_photons++;
      }
    } // End of particle loop
    General_event->chic = chi_c;
    General_event->Jpsi = Jpsi;
    
    AliParticle electrons[1000];
    AliParticle positrons[1000];
    AliParticle photons[2000];
    std::vector<AliParticle> electr;
    std::vector<AliParticle> positr;
    std::vector<AliParticle> phots;
    int elec = 0;
    int posi = 0;
    int phot = 0;

    if (number_of_electrons != 0){
      for (int i = 0; i < pythia.event.size(); ++i){
	if (pythia.event[i].id() == idElectron){
	  AliParticle electron_tmp;
	  electron_tmp.px = pythia.event[i].px();
	  electron_tmp.py = pythia.event[i].py();
	  electron_tmp.pz = pythia.event[i].pz();
	  electron_tmp.p0 = pythia.event[i].e();
	  electron_tmp.id = pythia.event[i].id();
	  electron_tmp.number_in_event = i;
	  electron_tmp.mother_number_in_event = pythia.event[i].mother1();
	  electron_tmp.mother_id = 
	    pythia.event[electron_tmp.mother_number_in_event].id();
	  electron_tmp.daughter_1_number_in_event = 
	    pythia.event[i].daughter1();
	  electron_tmp.daughter_2_number_in_event = 
	    pythia.event[i].daughter2();
	  elec++;
	  electr.push_back(electron_tmp);
	  // electrons[elec].px = pythia.event[i].px();
	  // electrons[elec].py = pythia.event[i].py();
	  // electrons[elec].pz = pythia.event[i].pz();
	  // electrons[elec].p0 = pythia.event[i].e();
	  // electrons[elec].id = pythia.event[i].id();
	  // electrons[elec].number_in_event = i;
	  // electrons[elec].mother_number_in_event = pythia.event[i].mother1();
	  // electrons[elec].mother_id = 
	  //   pythia.event[electrons[elec].mother_number_in_event].id();
	  // electrons[elec].daughter_1_number_in_event = 
	  //   pythia.event[i].daughter1();
	  // electrons[elec].daughter_2_number_in_event = 
	  //   pythia.event[i].daughter2();
	  // elec++;
	  // electr.push_back(electrons[elec]);
	}
      }
    } 
    if (number_of_positrons != 0){
      for (int i = 0; i < pythia.event.size(); ++i){
    	if (pythia.event[i].id() == -idElectron){
	  AliParticle positron_tmp;
	  positron_tmp.px = pythia.event[i].px();
	  positron_tmp.py = pythia.event[i].py();
	  positron_tmp.pz = pythia.event[i].pz();
	  positron_tmp.p0 = pythia.event[i].e();
	  positron_tmp.id = pythia.event[i].id();
	  positron_tmp.number_in_event = i;
	  positron_tmp.mother_number_in_event = pythia.event[i].mother1();
	  positron_tmp.mother_id = 
	    pythia.event[positron_tmp.mother_number_in_event].id();
	  positron_tmp.daughter_1_number_in_event = 
	    pythia.event[i].daughter1();
	  positron_tmp.daughter_2_number_in_event = 
	    pythia.event[i].daughter2();
	  posi++;
	  positr.push_back(positron_tmp);
    	  // positrons[posi].px = pythia.event[i].px();
    	  // positrons[posi].py = pythia.event[i].py();
    	  // positrons[posi].pz = pythia.event[i].pz();
    	  // positrons[posi].p0 = pythia.event[i].e();
    	  // positrons[posi].id = pythia.event[i].id();
    	  // positrons[posi].number_in_event = i;
    	  // positrons[posi].mother_number_in_event = pythia.event[i].mother1();
    	  // positrons[posi].mother_id = 
    	  //   pythia.event[positrons[posi].mother_number_in_event].id();
    	  // positrons[posi].daughter_1_number_in_event = 
    	  //   pythia.event[i].daughter1();
    	  // positrons[posi].daughter_2_number_in_event = 
    	  // pythia.event[i].daughter2();
    	  // posi++;
	  // positr.push_back(positrons[posi]);
    	}
      }
    }
    if (number_of_photons != 0){
      for (int i = 0; i < pythia.event.size(); ++i){
    	if (pythia.event[i].id() == idPhoton){
	  AliParticle photon_tmp;
	  photon_tmp.px = pythia.event[i].px();
	  photon_tmp.py = pythia.event[i].py();
	  photon_tmp.pz = pythia.event[i].pz();
	  photon_tmp.p0 = pythia.event[i].e();
	  photon_tmp.id = pythia.event[i].id();
	  photon_tmp.number_in_event = i;
	  photon_tmp.mother_number_in_event = pythia.event[i].mother1();
	  photon_tmp.mother_id = 
	    pythia.event[photon_tmp.mother_number_in_event].id();
	  photon_tmp.daughter_1_number_in_event = 
	    pythia.event[i].daughter1();
	  photon_tmp.daughter_2_number_in_event = 
	    pythia.event[i].daughter2();
	  phot++;
	  phots.push_back(photon_tmp);
    	  // photons[phot].px = pythia.event[i].px();
    	  // photons[phot].py = pythia.event[i].py();
    	  // photons[phot].pz = pythia.event[i].pz();
    	  // photons[phot].p0 = pythia.event[i].e();
    	  // photons[phot].id = pythia.event[i].id();
    	  // photons[phot].number_in_event = i;
    	  // photons[phot].mother_number_in_event = pythia.event[i].mother1();
    	  // photons[phot].mother_id = 
    	  //   pythia.event[photons[phot].mother_number_in_event].id();
    	  // photons[phot].daughter_1_number_in_event = 
    	  //   pythia.event[i].daughter1();
    	  // photons[phot].daughter_2_number_in_event = 
    	  //   pythia.event[i].daughter2();
    	  // phot++;
	  // phots.push_back(photons[phot]);
    	}
      }
    }
    General_event->electrons = electr;
    General_event->positrons = positr;
    General_event->photons = phots;
    test_tree->Fill();

  } // End of event loop
  

  test_tree->Print();
  test_tree->Write();
  outFile->Close();
  
  return 0;
}
