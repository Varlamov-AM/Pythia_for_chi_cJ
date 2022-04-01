#include "TLorentzVector.h"
#include <iostream>
#include "TMath.h"

bool IsElectronDetectedInALICE3(TLorentzVector p, int part){
  bool flag = false;

  double px = p.Px();
  double py = p.Py();
  double pz = p.Pz();

  double pT = TMath::Sqrt(px*px + py*py);
  double eta = 0.5*TMath::Log((p.P() + pz)/(p.P() - pz));

  if (fabs(eta) <= 2.0){
    if ((part == 2) &&
	(pT >= 0.15)){
      flag = true;    }
    if ((part == 1) &&
	(p.E() >= 0.1)){
      flag = true;
    }
  }

  return flag;
}
