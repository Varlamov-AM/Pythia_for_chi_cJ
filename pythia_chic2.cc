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

int main(int argc, char* argv[]) {


  // read input parameters
  printf("argc = %d, argv[0] = %s\n",argc,argv[0]);
  if (argc != 2) {
    printf("Usage: %s <nEvents>\n",argv[0]);
    printf("       <nEvents>=0 is the number of events to generate.\n");
    return 1;
  }

  char fn[1024];
  sprintf(fn, "%s", "AliEvent_class_data.root");
  TFile* outFile = new TFile(fn, "RECREATE");
  
  TTree *test_tree = new TTree("AliEvent_data", "AliEvent_class_data");
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
  const int idK0L          =  130;
  const int idn            =  2112;
  
  int nEvent2Print = 10;

  // Begin event loop. Generate event

  int iEvent2Print = 0;
  
  for (int iEvent = 0; iEvent < nEvents; ++iEvent){
    if (!pythia.next()) continue;
    int number_of_electrons = 0;
    int number_of_positrons = 0;
    int number_of_photons   = 0;

    std::vector<AliParticle> charged_particle;
    std::vector<AliParticle> neutral_particle;


    //print first nEvent2Print events
    if (iEvent2Print < nEvent2Print) //pythia.event.list();
    iEvent2Print++;

    // Loop over all particles in the generated event    
    for (int i = 0; i < pythia.event.size(); ++i){
      
      General_event->number_of_particle_in_event = pythia.event.size();
      
      if (fabs(pythia.event[i].eta()) > 4.){
	continue;
      }
      
      if(pythia.event[i].isCharged()){
	AliParticle charged_tmp;
	charged_tmp.px = pythia.event[i].px();
	charged_tmp.py = pythia.event[i].py();
	charged_tmp.pz = pythia.event[i].pz();
	charged_tmp.p0 = pythia.event[i].e();
	charged_tmp.id = pythia.event[i].id();
	charged_tmp.number_in_event = i;
	charged_tmp.mother_number_in_event = pythia.event[i].mother1();
	charged_tmp.mother_id = 
	  pythia.event[charged_tmp.mother_number_in_event].id();
	charged_tmp.daughter_1_number_in_event =  pythia.event[i].daughter1();
	charged_tmp.daughter_2_number_in_event =  pythia.event[i].daughter2();
	charged_particle.push_back(charged_tmp);
      }

      if (pythia.event[i].id() == idK0L ||
	  pythia.event[i].id() == idn ||
	  pythia.event[i].id() == -idn){
	AliParticle neutral_tmp;
	neutral_tmp.px = pythia.event[i].px();
	neutral_tmp.py = pythia.event[i].py();
	neutral_tmp.pz = pythia.event[i].pz();
	neutral_tmp.p0 = pythia.event[i].e();
	neutral_tmp.id = pythia.event[i].id();
	neutral_tmp.number_in_event = i;
	neutral_tmp.mother_number_in_event = pythia.event[i].mother1();
	neutral_tmp.mother_id = 
	  pythia.event[neutral_tmp.mother_number_in_event].id();
	neutral_tmp.daughter_1_number_in_event =  pythia.event[i].daughter1();
	neutral_tmp.daughter_2_number_in_event =  pythia.event[i].daughter2();
	neutral_particle.push_back(neutral_tmp);
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
    	}
      }
    }
    General_event->electrons = electr;
    General_event->positrons = positr;
    General_event->photons = phots;
    General_event->charged = charged_particle;
    General_event->neutral = neutral_particle;
    test_tree->Fill();

  } // End of event loop
  

  test_tree->Print();
  test_tree->Write();
  outFile->Close();

  TH1F *hCross_section_hist = new TH1F("hCross_section_hist", "xsection and ntrials data", 2, 0., 1.);


  double xsection = pythia.info.sigmaGen();
  int ntrials  = pythia.info.nAccepted();

  hCross_section_hist->SetBinContent(1, xsection);
  hCross_section_hist->SetBinContent(2, ntrials);  
  
  TFile* cross_section_data = new TFile("Cross_section_data.root", "RECREATE");
  cross_section_data->cd();
  
  hCross_section_hist->Write();
  cross_section_data->Close();
  
  return 0;

}
