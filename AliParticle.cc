#include "AliParticle.h"
#include "TLorentzVector.h" 

TLorentzVector AliParticle::FMomentum(){
  TLorentzVector res = TLorentzVector(px, py, pz, p0);
  return res;
}

int AliParticle::Number_of_daughters(){
  return daughter_2_number_in_event - daughter_1_number_in_event;
}

ClassImp(AliParticle);
