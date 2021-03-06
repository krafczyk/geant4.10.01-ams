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
//
// $Id$
//
// 
// Implementation for G4UBox wrapper class
// --------------------------------------------------------------------

#include "G4Box.hh"
#include "G4UBox.hh"
#include "G4VPVParameterisation.hh"

////////////////////////////////////////////////////////////////////////
//
// Constructor - check & set half widths


G4UBox::G4UBox(const G4String& pName,
                   G4double pX,
                   G4double pY,
                   G4double pZ)
  : G4USolid(pName, new UBox(pName, pX, pY, pZ))
{
}

//////////////////////////////////////////////////////////////////////////
//
// Fake default constructor - sets only member data and allocates memory
//                            for usage restricted to object persistency.

G4UBox::G4UBox( __void__& a )
  : G4USolid(a)
{
}

//////////////////////////////////////////////////////////////////////////
//
// Destructor

G4UBox::~G4UBox()
{
}

//////////////////////////////////////////////////////////////////////////
//
// Copy constructor

G4UBox::G4UBox(const G4UBox& rhs)
  : G4USolid(rhs)
{
}

//////////////////////////////////////////////////////////////////////////
//
// Assignment operator

G4UBox& G4UBox::operator = (const G4UBox& rhs) 
{
   // Check assignment to self
   //
   if (this == &rhs)  { return *this; }

   // Copy base class data
   //
   G4USolid::operator=(rhs);

   return *this;
}

////////////////////////////////////////////////////////////////////////
//
// Dispatch to parameterisation for replication mechanism dimension
// computation & modification.

void G4UBox::ComputeDimensions(G4VPVParameterisation* p,
                               const G4int n,
                               const G4VPhysicalVolume* pRep)
{
  p->ComputeDimensions(*(G4Box*)this,n,pRep);
}

//////////////////////////////////////////////////////////////////////////
//
// Make a clone of the object

G4VSolid* G4UBox::Clone() const
{
  return new G4UBox(*this);
}
