#include <iostream>
#include "TObject.h"
#include "TMath.h"
#include "AliParticle.h"
#include <vector>
#pragma once

class AliEvent: public TObject{
 public:

  int number_of_particle_in_event;
  int number_of_electrons;

  AliParticle chic;
  AliParticle Jpsi;

  std::vector<AliParticle> electrons;
  std::vector<AliParticle> positrons;
  std::vector<AliParticle> photons;

  AliEvent(){};
  virtual ~AliEvent(){};

  ClassDef(AliEvent,1);
};
