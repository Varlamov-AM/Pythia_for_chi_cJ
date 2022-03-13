#include "TH1.h"
#include "TH2.h"
#include "TFile.h"

void add_tree_data_test(int input, int* output, TTree* tree);

void ROOT_file_creator(){

//Save histogram on file and close file.
  char fn[1024];
  sprintf(fn, "%s", "pythia_chic2.root");
  TFile* outFile = new TFile(fn, "RECREATE");

  TTree *test_tree = new TTree("T", "Test_tree");

  Int_t number_particle_in_event;
  test_tree->Branch("number_particle_in_event", 
		    &number_particle_in_event, 
		    "number_particle_in_event/I");

  outFile->Close();
  delete outFile;

  return;
}

void add_tree_data_test(int input, int* output, TTree* tree){

  &(output) = input;

  tree->Fill();
  
  return;
}
