#include "TLorentzVector.h"
#include "TRandom.h"
#include <math.h>

Double_t smearE(Double_t Etrue, int smear_type)
{
  if (smear_type == 0){
    // Generate smeared photon energy from the true energy
    const Double_t a = 0.018, b = 0.033, c = 0.011; // Energy resolution of ALICE PHOS
    Double_t sigmaE = Etrue * sqrt(a*a/Etrue/Etrue + b*b/Etrue + c*c);
    Double_t Esmeared = gRandom->Gaus(Etrue,sigmaE);
    if (Esmeared<0) Esmeared = 0;
    return Esmeared;
  }

  if (smear_type == 1){
    // Generate smeared photon energy from the true energy
    const Double_t a = 0.001, b = 0.01, c = 0.01; // Energy resolution of ALICE PHOS
    Double_t sigmaE = Etrue * sqrt(a*a/Etrue/Etrue + b*b/Etrue + c*c);
    Double_t Esmeared = gRandom->Gaus(Etrue,sigmaE);
    if (Esmeared<0) Esmeared = 0;
    return Esmeared;
  }
  return 0.;
}
