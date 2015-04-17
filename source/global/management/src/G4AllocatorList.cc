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

#include <iomanip>

#include "G4AllocatorList.hh"
#include "G4Allocator.hh"
#include "G4ios.hh"

G4ThreadLocal G4AllocatorList* G4AllocatorList::fAllocatorList=0;

G4AllocatorList* G4AllocatorList::GetAllocatorList()
{
  if(!fAllocatorList)
  {
    fAllocatorList = new G4AllocatorList;
  }
  return fAllocatorList;
}

G4AllocatorList* G4AllocatorList::GetAllocatorListIfExist()
{
  return fAllocatorList;
}

G4AllocatorList::G4AllocatorList()
{
}

G4AllocatorList::~G4AllocatorList()
{
  fAllocatorList = 0;
}

void G4AllocatorList::Register(G4AllocatorBase* alloc)
{
  fList.push_back(alloc);
}



void G4AllocatorList::Destroy(G4int nStat, G4int verboseLevel)
{
  std::vector<G4AllocatorBase*>::iterator itr=fList.begin();
  G4int i=0, j=0;
  G4double mem=0;
  for(; itr!=fList.end();++itr)
  {
    if(i<nStat)
    {
      i++;
      mem += (*itr)->GetAllocatedSize();
      (*itr)->ResetStorage();
      continue;
    }
    j++;
    mem += (*itr)->GetAllocatedSize();
    (*itr)->ResetStorage();
    delete *itr; 
  }
  if(verboseLevel>0)
  {
    G4cout << "================== Deleting memory pools ==================="
           << G4endl;
    G4cout << "Number of memory pools allocated: " << Size()
           << "; of which, static: " << i << G4endl;
    G4cout << "Dynamic pools deleted: " << j 
           << " / Total memory freed: " << std::setprecision(2)
           << mem/1048576 << std::setprecision(6) << " Mb" << G4endl;
    G4cout << "============================================================"
           << G4endl;
  }
  fList.clear();
}



unsigned long long G4AllocatorList::CollectGarbage(unsigned long long thr)
{
  unsigned long long mem=0;
  for(std::vector<G4AllocatorBase*>::iterator itr=fList.begin(); itr!=fList.end();++itr){
    if((*itr)->GetAllocatedSize()>(thr?thr:G4AllocatorPool::GetThreshold()))
    mem += (*itr)->CollectGarbage();
}
  return mem;
}




unsigned long long G4AllocatorList::GetAllocatedSize()
{
  unsigned long long mem=0;
  for(std::vector<G4AllocatorBase*>::iterator itr=fList.begin(); itr!=fList.end();++itr){
    mem+=(*itr)->GetAllocatedSize();
}
  return mem;
}



 long long G4AllocatorList::GetUsed()
{
   long long mem=0;
  for(std::vector<G4AllocatorBase*>::iterator itr=fList.begin(); itr!=fList.end(
);++itr){
    mem+=(*itr)->GetUsed();
}
  return mem;
}



int G4AllocatorList::GetNoPages()
{
  unsigned long long mem=0;
  for(std::vector<G4AllocatorBase*>::iterator itr=fList.begin(); itr!=fList.end();++itr){
    mem+=(*itr)->GetNoPages();
}
  return mem;
}




G4int G4AllocatorList::Size() const
{
  return fList.size();
}
