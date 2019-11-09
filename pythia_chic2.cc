// File: hist.cc
// This is a simple test program.
// It studies the charged multiplicity distribution at the LHC.
// Modified by Rene Brun, Axel Naumann and Bernhard Meirose 
// to use ROOT for histogramming.
// Copyright (C) 2013 Torbjorn Sjostrand

// Define environment variable PYTHIA8DATA for xlmdoc directory
// for example:
// export PYTHIA8DATA=$ALICE_ROOT/PYTHIA8/pythia8210/xmldoc/

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




using namespace Pythia8;

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

  // randon seed
  TRandom rndm;
  rndm.SetSeed(0);
  int pythiaSeed = rndm.Integer(1000000);
  char processLine[80];
  sprintf(processLine, "Random:Seed = %d",pythiaSeed);

  pythia.readString("Random:setSeed = on");
  pythia.readString(processLine); 

  // Set process type and collision energy
  pythia.readString("Onia:all(3PJ) = on");
  pythia.readString("Beams:eCM = 13000.");
  pythia.init();

  double ptMin = 0.;
  double ptMax = 50.;  //GeV
  double yMin  = 0.; 
  double yMax  = 0.5; 
  

  const int nPtBins = 250;
  const int nyBins = 250; 

  // rapidity range
  double ymax = 0.5;
  
  // create histograms
  TH1F *hChiC2_pt_all     = new TH1F("hChiC2_pt_all"     ,"All #chi_{c2} p_{T} spectrum" , nPtBins, ptMin, ptMax);
  hChiC2_pt_all->Sumw2();

  TH1F *hChiC2_pt_cndtn_1 = new TH1F("hChiC2_pt_cndtn_1" ,"#chi_{c2} p_{T} spectrum"  ,nPtBins, ptMin, ptMax);
  hChiC2_pt_cndtn_1->Sumw2();

  TH1F *hChiC2_y_cndtn_1  = new TH1F("hChiC2_y_cndtn_1"  ,"#chi_{c2} y spectrum"  ,nyBins, yMin, yMax);
  hChiC2_y_cndtn_1->Sumw2(); 

  TH1F *hChiC2_pt_cndtn_2 = new TH1F("hChiC2_pt_cndtn_2" ,"#chi_{c2} p_{T} spectrum"  ,nPtBins, ptMin, ptMax);
  hChiC2_pt_cndtn_1->Sumw2();

  TH1F *hChiC2_y_cndtn_2  = new TH1F("hChiC2_y_cndtn_2"  ,"#chi_{c2} y spectrum"  ,nyBins, yMin, yMax);
  hChiC2_y_cndtn_1->Sumw2();

  TH1F *hGamma_pt_all     = new TH1F("hGamma_pt_all"     ,"#gamma p_{T} spectrum ", nPtBins, ptMin, ptMax);
  hGamma_pt_all->Sumw2();       
  
  TH1F *hPositron_pt_all  = new TH1F("hPositron_pt_all"  ,"e_{+}  p_{T} spectrum", nPtBins, ptMin, ptMax);
  hPositron_pt_all ->Sumw2();

  TH1F *hElectron_pt_all  = new TH1F("hElectron_pt_all"  ,"e_{-}  p_{T} spectrum", nPtBins, ptMin, ptMax);
  hElectron_pt_all ->Sumw2();

  

  const int idChic0        =  441;
  const int idChic2        =  445;
  const int idJpsi         =  443;
  const int idElectron     =  11;
  const int idPositron     = -11;
  const int idPhoton       =  22;

  int nEvent2Print = 10;

  // Begin event loop. Generate event

  int iEvent2Print = 0;
  for (int iEvent = 0; iEvent < nEvents; ++iEvent) {
    if (!pythia.next()) continue;

    // Find number of all final charged particles and pi0's
    for (int i = 0; i < pythia.event.size(); ++i) {
      // Select final-state chi_c2 within |y|<0.5
      if (pythia.event[i].id() == idChic2 &&
	  pythia.event[i].status() == -62 &&
	   fabs(pythia.event[i].y()) <= ymax) {

	// print first nEvent2Print events
	if (iEvent2Print < nEvent2Print) pythia.event.list();
	iEvent2Print++;

	Double_t pt = pythia.event[i].pT(); // transverse momentum
	hChiC2_pt_all->Fill(pt);
	Double_t y  = pythia.event[i].y();

 

	// Find daughters of chi_c2
	int dghtChi1 = pythia.event[i].daughter1(); // first daughter
	int dghtChi2 = pythia.event[i].daughter2(); // last  daughter

	// skip event if the number of chi_c2 daughters is not 2
	if (dghtChi2 - dghtChi1 != 1) continue;

	// select decay chi_c2 -> J/psi gamma
	if ( pythia.event[dghtChi1].id() == idJpsi    &&
	     pythia.event[dghtChi2].id() == idPhoton)  {

	  int dghtJ1 = pythia.event[dghtChi1].daughter1();
	  int dghtJ2 = pythia.event[dghtChi1].daughter2();
	 
	 


	  // skip event if the number of J/psi daughters is not 2
	  if (dghtJ2 - dghtJ1 != 1) continue;

	  Double_t pt_gamma = pythia.event[dghtChi2].pT();
	  Double_t eta_gamma = pythia.event[dghtChi2].eta();

	  hGamma_pt_all->Fill(pt_gamma);


	  // select decay J/psi -> e+ e-
	  if (abs(pythia.event[dghtJ1].id()) == idElectron &&
	      abs(pythia.event[dghtJ2].id()) == idElectron) {
              
	    if (pythia.event[dghtJ1].id() == idElectron)  {
		Double_t pt_positron = pythia.event[dghtJ2].pT();
                Double_t pt_electron = pythia.event[dghtJ1].pT();

                Double_t eta_positron = pythia.event[dghtJ2].eta();
                Double_t eta_electron = pythia.event[dghtJ1].eta();
                

		hPositron_pt_all->Fill(pt_positron);
	        hElectron_pt_all->Fill(pt_electron);


		if (abs(eta_positron) < 0,8  &&
                    abs(eta_electron) < 0,8  &&
                    abs(eta_gamma)    < 0,12 &&
		    pt_electron       > 0.5  &&
		    pt_positron       > 0.5  &&
		    pt_gamma          > 1.0) 
		 
		  {  
		  
		    hChiC2_pt_cndtn_1 ->Fill(pt);
		    hChiC2_y_cndtn_1  ->Fill(y);

		  }


		if (abs(eta_positron) < 0,8  &&
                    abs(eta_electron) < 0,8  &&
                    abs(eta_gamma)    < 0,12 &&
		    pt_electron       > 0.5  &&
		    pt_positron       > 0.5  &&
		    pt_gamma          > 5.0)  
		  
		  { 
		  
		    hChiC2_pt_cndtn_2 ->Fill(pt);
		    hChiC2_y_cndtn_2  ->Fill(y);

		  }

	      }
 

	     if (pythia.event[dghtJ2].id() == idElectron)  {
	        Double_t pt_positron =pythia.event[dghtJ1].pT();
                Double_t pt_electron = pythia.event[dghtJ2].pT();
       
                Double_t eta_positron = pythia.event[dghtJ1].eta();
                Double_t eta_electron = pythia.event[dghtJ2].eta();

	        hPositron_pt_all->Fill(pt_positron);
		hElectron_pt_all->Fill(pt_electron);
	
		if (abs(eta_positron) < 0,8  &&
                    abs(eta_electron) < 0,8  &&
                    abs(eta_gamma)    < 0,12 &&
		    pt_electron       > 0.5  &&
		    pt_positron       > 0.5  &&
		    pt_gamma          > 1.0)   

		  { 
		  
		    hChiC2_pt_cndtn_1 ->Fill(pt);
		    hChiC2_y_cndtn_1  ->Fill(y);
		 
		  }
		
		if (abs(eta_positron) < 0,8  &&
                    abs(eta_electron) < 0,8  &&
                    abs(eta_gamma)    < 0,12 &&
		    pt_electron       > 0.5  &&
		    pt_positron       > 0.5  &&
		    pt_gamma          > 5.0)


		  { 
		  
		    hChiC2_pt_cndtn_2 ->Fill(pt);
		    hChiC2_y_cndtn_2  ->Fill(y);

		  }
 

	      }
	  }
	}

      }
    }

    // Fill charged multiplicity in histogram. End event loop.
  }

  // Statistics on event generation.
  pythia.stat();

  // Convert histograms to differential cross sections
  double xsection = pythia.info.sigmaGen();
  int ntrials  = pythia.info.nAccepted();
  double sigmaweight = xsection/ntrials;
  

  // normalize pT spectra
  double ptBinSize = (ptMax-ptMin) / nPtBins;
  double yBinSize  = (yMax-yMin) / nyBins;

  hChiC2_pt_all       ->Scale(sigmaweight/(ptBinSize * 2. * ymax));
  hGamma_pt_all       ->Scale(sigmaweight/(ptBinSize * 2. * ymax));
  hElectron_pt_all    ->Scale(sigmaweight/(ptBinSize * 2. * ymax));
  hPositron_pt_all    ->Scale(sigmaweight/(ptBinSize * 2. * ymax));
  hChiC2_pt_cndtn_1   ->Scale(sigmaweight/(ptBinSize * 2. * ymax));
  hChiC2_pt_cndtn_2   ->Scale(sigmaweight/(ptBinSize * 2. * ymax));
  hChiC2_y_cndtn_1    ->Scale(sigmaweight/(yBinSize * 2. * ymax));
  hChiC2_y_cndtn_2    ->Scale(sigmaweight/(yBinSize * 2. * ymax)); 

  // Save histogram on file and close file.
  char fn[1024];
  sprintf(fn, "%s", "pythia_chic2.root");
  TFile* outFile = new TFile(fn, "RECREATE");
 
  hChiC2_pt_all      ->Write();
  hChiC2_pt_cndtn_1  ->Write();
  hChiC2_y_cndtn_1   ->Write();
  hChiC2_pt_cndtn_2  ->Write();
  hChiC2_y_cndtn_2   ->Write();
  hGamma_pt_all      ->Write();
  hElectron_pt_all   ->Write();
  hPositron_pt_all   ->Write();

 
  outFile->Close();
  delete outFile;




  return 0;
}
