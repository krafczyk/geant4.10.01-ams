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
// -------------------------------------------------------------------
//
// GEANT4 Class file
//
// File name:     G4EmParametersMessenger
//
// Author:        Vladimir Ivanchenko created from G4EnergyLossMessenger
//
// Creation date: 22-05-2013
//
// Modifications:
//
// -------------------------------------------------------------------
//

// Class Description:
//  This is a messenger class to interface to exchange information
//  between G4VEm and UI.
//

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#ifndef G4EmParametersMessenger_h
#define G4EmParametersMessenger_h 1

#include "globals.hh"
#include "G4UImessenger.hh"

class G4UIdirectory;
class G4UIcommand;
class G4UIcmdWithABool;
class G4UIcmdWithAnInteger;
class G4UIcmdWithADouble;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithAString;
class G4EmParameters;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

class G4EmParametersMessenger: public G4UImessenger
{
public:   // with description
  
  G4EmParametersMessenger(G4EmParameters*);
  virtual ~G4EmParametersMessenger();

  virtual void SetNewValue(G4UIcommand*, G4String);

private:

  G4EmParameters*            theParameters;

  G4UIdirectory*             eLossDirectory;
  G4UIdirectory*             mscDirectory;
  G4UIdirectory*             emDirectory;

  G4UIcmdWithABool*          flucCmd;
  G4UIcmdWithABool*          rangeCmd;
  G4UIcmdWithABool*          lpmCmd;
  G4UIcmdWithABool*          splCmd;
  G4UIcmdWithABool*          rsCmd;
  G4UIcmdWithABool*          aplCmd;
  G4UIcmdWithABool*          deCmd;
  G4UIcmdWithABool*          auCmd;
  G4UIcmdWithABool*          pixeCmd;
  G4UIcmdWithABool*          dcutCmd;
  G4UIcmdWithABool*          latCmd;
  G4UIcmdWithABool*          mulatCmd;
  G4UIcmdWithABool*          catCmd;
  G4UIcmdWithABool*          delCmd;

  G4UIcmdWithADouble*        minSubSecCmd;
  G4UIcmdWithADoubleAndUnit* minEnCmd;
  G4UIcmdWithADoubleAndUnit* maxEnCmd;
  G4UIcmdWithADoubleAndUnit* cenCmd;
  G4UIcmdWithADouble*        lllCmd;
  G4UIcmdWithADoubleAndUnit* brCmd;
  G4UIcmdWithADouble*        labCmd;
  G4UIcmdWithADouble*        mscfCmd;
  G4UIcmdWithADoubleAndUnit* angCmd;
  G4UIcmdWithADouble*        frCmd;
  G4UIcmdWithADouble*        fgCmd;
  G4UIcmdWithADouble*        skinCmd;

  G4UIcmdWithAnInteger*      dedxCmd;
  G4UIcmdWithAnInteger*      lamCmd;
  G4UIcmdWithAnInteger*      amCmd;
  G4UIcmdWithAnInteger*      verCmd;
  G4UIcmdWithAnInteger*      ver1Cmd;
  G4UIcmdWithAnInteger*      ver2Cmd;

  G4UIcmdWithAString*        mscCmd;
};

#endif

