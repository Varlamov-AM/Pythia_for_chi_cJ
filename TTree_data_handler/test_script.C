void test_script(){
  
  TFile* file = new TFile("TTree_test.root");
  TTree* tree = (TTree*)file->Get("Tree");
  
  int number_electron_in_event;
  int number_positron_in_event;
  int number_photon_in_event;
  

  Double_t electron_px[1000], electron_py[1000], electron_pz[1000], electron_p0[1000];
  Double_t positron_px[1000], positron_py[1000], positron_pz[1000], positron_p0[1000];
  Double_t photon_px[1000], photon_py[1000], photon_pz[1000], photon_p0[1000];

  //Added ability add to event in tree arrays of particle!
  
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
  

  
  const Int_t nentries = (Int_t)tree->GetEntries();
  const int d = nentries;

  printf("%d\n", nentries);

  TH1D* hist_test1 = new TH1D("h1", "h1", 30, 0.000505, 0.000515);
  TH1D* hist_test2 = new TH1D("h2", "h2", 100, 0., 3.5);
  TH1D* hist_test3 = new TH1D("h3", "h3", 100, 3., 4.);
  TH1D* hist_test4 = new TH1D("h4", "h4", 100, 0., 0.8);
  TLorentzVector elec_data[10000]; 
  TLorentzVector posi_data[10000]; 
  TLorentzVector phot_data[10000]; 

  for (int i = 150000; i < 250000; i++){
    tree->GetEntry(i);
    if (number_electron_in_event != 0){
      for (int k = 0; k < number_electron_in_event; k++){
    	elec_data[k] = TLorentzVector(electron_px[k],
    				      electron_py[k],
    				      electron_pz[k],
    				      electron_p0[k]);
      }
    }
    
    if (number_positron_in_event != 0){
      for (int l = 0; l < number_positron_in_event; l++){
    	posi_data[l] = TLorentzVector(positron_px[l],
    				      positron_py[l],
    				      positron_pz[l],
    				      positron_p0[l]);
      }
    }
    if (number_photon_in_event != 0){
      for (int m = 0; m < number_photon_in_event; m++){
    	phot_data[m] = TLorentzVector(photon_px[m],
    				      photon_py[m],
    				      photon_pz[m],
				      photon_p0[m]);
      }
    }
    
    
    for (int a = 0; a < number_electron_in_event; a++){
      hist_test1->Fill((elec_data[a]).M());
      for (int b = 0; b < number_positron_in_event; b++){
	TLorentzVector tmp;
	tmp = elec_data[a] + posi_data[b];
	//printf("%10.8f,%10.8f, %10.8f\n", tmp.M(), (elec_data[a]).M(),(posi_data[b]).M());
       	hist_test2->Fill((tmp).M());
	for (int c = 0; c < number_photon_in_event; c++){
	  hist_test3->Fill((tmp + phot_data[c]).M());
	  hist_test4->Fill((tmp + phot_data[c]).M() - tmp.M());
	}
      }
    }
    printf("%6d\n", i);
  }

  TFile* output = new TFile("output.root", "RECREATE");
	output->cd();
  hist_test1->Write();
  hist_test2->Write();
  hist_test3->Write();
  hist_test4->Write();
	
  output->Close();
  return;
}
