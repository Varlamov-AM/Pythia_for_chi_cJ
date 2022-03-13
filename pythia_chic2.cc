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
  
  int number_positron_in_event = 0;
  int number_electron_in_event = 0;
  int number_photon_in_event = 0;
  Double_t electron_px[1000];
  Double_t electron_py[1000];
  Double_t electron_pz[1000];
  Double_t electron_p0[1000];
  Double_t positron_px[1000];
  Double_t positron_py[1000];
  Double_t positron_pz[1000];
  Double_t positron_p0[1000];
  Double_t photon_px[1000];
  Double_t photon_py[1000];
  Double_t photon_pz[1000];
  Double_t photon_p0[1000];
  
  TTree *test_tree = new TTree("Tree", "Test_tree");
  
  
  test_tree->Branch("number_electron_in_event", 
  		    &number_electron_in_event, 
  		    "number_electron_in_event/I");
  test_tree->Branch("number_positron_in_event", 
  		    &number_positron_in_event, 
  		    "number_positron_in_event/I");
  test_tree->Branch("number_photon_in_event", 
  		    &number_photon_in_event, 
  		    "number_photon_in_event/I");
  test_tree->Branch("electron_px",
  		    electron_px, 
  		    "electron_px[number_electron_in_event]/D");
  test_tree->Branch("electron_py",
  		    electron_py, 
  		    "electron_py[number_electron_in_event]/D");
  test_tree->Branch("electron_pz",
  		    electron_pz, 
  		    "electron_pz[number_electron_in_event]/D");
  test_tree->Branch("electron_p0",
  		    electron_p0, 
  		    "electron_p0[number_electron_in_event]/D");
  test_tree->Branch("positron_px",
  		    positron_px, 
  		    "positron_px[number_positron_in_event]/D");
  test_tree->Branch("positron_py",
  		    positron_py, 
  		    "positron_py[number_positron_in_event]/D");
  test_tree->Branch("positron_pz",
  		    positron_pz, 
  		    "positron_pz[number_positron_in_event]/D");
  test_tree->Branch("positron_p0",
  		    positron_p0, 
  		    "positron_p0[number_positron_in_event]/D");
  test_tree->Branch("photon_px",
  		    photon_px, 
  		    "photon_px[number_photon_in_event]/D");
  test_tree->Branch("photon_py",
  		    photon_py, 
  		    "photon_py[number_photon_in_event]/D");
  test_tree->Branch("photon_pz",
  		    photon_pz, 
  		    "photon_pz[number_photon_in_event]/D");
  test_tree->Branch("photon_p0",
  		    photon_p0, 
  		    "photon_p0[number_photon_in_event]/D");

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


  // const int idChic0        =  10441;
  // const int idChic1        =  20443;
  // const int idChic2        =  445;
  // const int idJpsi         =  443;
  const int idElectron     =  11;
  const int idPhoton       =  22;
  
  int nEvent2Print = 10;

  // Begin event loop. Generate event

  int iEvent2Print = 0;
  
  for (int iEvent = 0; iEvent < nEvents; ++iEvent){
    if (!pythia.next()) continue;

    //print first nEvent2Print events
    if (iEvent2Print < nEvent2Print) //pythia.event.list();
    iEvent2Print++;
      int elec, posi, phot;
      elec = 0; 
      posi = 0;
      phot = 0;

    // Loop over all particles in the generated event    
    for (int i = 0; i < pythia.event.size(); ++i){
      if (pythia.event[i].id() == idElectron){ 
  	electron_px[elec] = pythia.event[i].px();
  	electron_py[elec] = pythia.event[i].py();
  	electron_pz[elec] = pythia.event[i].pz();
  	electron_p0[elec] = pythia.event[i].e();
  	elec++;
      }
      
      if (pythia.event[i].id() == -idElectron){
  	positron_px[posi] = pythia.event[i].px();
  	positron_py[posi] = pythia.event[i].py();
  	positron_pz[posi] = pythia.event[i].pz();
  	positron_p0[posi] = pythia.event[i].e();
  	posi++;
      }
      
      if (pythia.event[i].id() == idPhoton){
  	photon_px[phot] = pythia.event[i].px();
  	photon_py[phot] = pythia.event[i].py();
  	photon_pz[phot] = pythia.event[i].pz();
  	photon_p0[phot] = pythia.event[i].e();
  	phot++;
      }
    } // End of particle loop  
    
    number_electron_in_event = elec;
    number_positron_in_event = posi;
    number_photon_in_event = phot;
    test_tree->Fill();

  } // End of event loop
  

  outFile->cd();
  test_tree->Print();
  test_tree->Write();
  
  return 0;
}
