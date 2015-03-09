//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
// $Id$
//
// by V. Lara
//
// Modified:
// 23.08.2010 V.Ivanchenko general cleanup, move constructor and destructor 
//            the source, use G4Pow
 
#include "G4HETCFragment.hh"
#include "G4PhysicalConstants.hh"
#include "G4PreCompoundParameters.hh"

G4HETCFragment::
G4HETCFragment(const G4ParticleDefinition* part,
	       G4VCoulombBarrier* aCoulombBarrier)
  : G4VPreCompoundFragment(part, aCoulombBarrier)
{
  G4double r0 = theParameters->Getr0();
  r2norm = r0*r0/(CLHEP::pi*CLHEP::hbarc*CLHEP::hbarc*CLHEP::hbarc);
}

G4HETCFragment::~G4HETCFragment()
{}

G4double G4HETCFragment::
CalcEmissionProbability(const G4Fragment & aFragment)
{
  if (GetEnergyThreshold() <= 0.0) 
    {
      theEmissionProbability = 0.0;
      return 0.0;
    }    
  // Coulomb barrier is the lower limit 
  // of integration over kinetic energy
  G4double LowerLimit = theCoulombBarrier;
  
  // Excitation energy of nucleus after fragment emission is the upper limit
  // of integration over kinetic energy
  G4double UpperLimit = GetMaximalKineticEnergy();
  
  theEmissionProbability = 
    IntegrateEmissionProbability(LowerLimit,UpperLimit,aFragment);
    
  return theEmissionProbability;
}

G4double G4HETCFragment::
IntegrateEmissionProbability(const G4double & Low, const G4double & Up,
			     const G4Fragment & aFragment)
{
  
  if ( !IsItPossible(aFragment) ) { return 0.0; }
    
  G4double U = aFragment.GetExcitationEnergy();

  G4int P  = aFragment.GetNumberOfParticles();
  G4int H  = aFragment.GetNumberOfHoles();
  G4int N  = P + H;
  G4int Pb = P - GetA();
  G4int Nb = Pb + H;
  if (Nb <= 0.0) { return 0.0; }
  G4double ga = (6.0/pi2)*aFragment.GetA_asInt()*theParameters->GetLevelDensity();
  G4double gb = (6.0/pi2)*GetRestA()*theParameters->GetLevelDensity();

  G4double A  = G4double(P*P+H*H+P-3*H)/(4.0*ga);
  G4double Ab = G4double(Pb*Pb+H*H+Pb-3*H)/(4.0*gb);
  U = std::max(U-A,0.0);
  if (U <= 0.0) { return 0.0; }

  G4int Pf = P;
  G4int Hf = H;
  G4int Nf = N-1;
  for (G4int i = 1; i < GetA(); ++i)
    {
      Pf *= (P-i);
      Hf *= (H-i);
      Nf *= (N-1-i);
    }

  G4double X = std::max(Up - Ab + GetBeta(),0.0);
  G4double Y = std::max(Up - Ab - Low, 0.0);

  G4double Probability = r2norm*GetSpinFactor()*GetReducedMass()*GetAlpha() 
    *g4pow->Z23(GetRestA())*Pf*Hf*Nf*K(aFragment)*(X/Nb - Y/(Nb+1))
    *U*g4pow->powN(gb*Y,Nb)/g4pow->powN(ga*U,N);

  //  G4double Probability = GetSpinFactor()/(pi*hbarc*hbarc*hbarc) 
  //  * GetReducedMass() * GetAlpha() *
  //  r0 * r0 * std::pow->Z23(GetRestA())/std::pow->pow(U,G4double(N-1)) * 
  //  (std::pow->(gb,Nb)/std::pow(ga,N)) * Pf * Hf * Nf * K(aFragment) *
  //  std::pow(Y,Nb) * (X/Nb - Y/(Nb+1));

  return Probability;
}