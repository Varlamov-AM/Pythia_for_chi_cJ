#include "TRandom.h"
#include <math.h>

Double_t sigmaX(Double_t E)
{
  const Double_t a = 0.15, b = 0.25; // realistic coordinate resolution in PHOS
  Double_t sigmaX = sqrt(a*a + b*b/E);
  return sigmaX;
}
