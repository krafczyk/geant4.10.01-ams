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
// ----------------------------------------------------------------------
// G4AllocatorPool
//
// Implementation file
//
// Author: G.Cosmo, November 2000
//
#include <iostream>
#include <vector>
#include "G4AllocatorPool.hh"
unsigned long long G4AllocatorPool::Threshold=20000000;

// ************************************************************
// G4AllocatorPool constructor
// ************************************************************
//
G4AllocatorPool::G4AllocatorPool( unsigned int sz )
  : esize(sz<sizeof(G4PoolLink) ? sizeof(G4PoolLink) : sz),
    csize(sz<1024/2-16 ? 1024-16 : sz*10-16),
    chunks(0), head(0), nchunks(0),free(0)
{
}

// ************************************************************
// G4AllocatorPool copy constructor
// ************************************************************
//
G4AllocatorPool::G4AllocatorPool(const G4AllocatorPool& right)
  : esize(right.esize), csize(right.csize),
    chunks(right.chunks), head(right.head), nchunks(right.nchunks)
{
}

// ************************************************************
// G4AllocatorPool operator=
// ************************************************************
//
G4AllocatorPool&
G4AllocatorPool::operator= (const G4AllocatorPool& right)
{
  if (&right == this) { return *this; }
  chunks  = right.chunks;
  head    = right.head;
  nchunks = right.nchunks;
  return *this;
}

// ************************************************************
// G4AllocatorPool destructor
// ************************************************************
//
G4AllocatorPool::~G4AllocatorPool()
{
  Reset();
}

// ************************************************************
// Reset
// ************************************************************
//
void G4AllocatorPool::Reset()
{
  // Free all chunks
  //
  G4PoolChunk* n = chunks;
  G4PoolChunk* p = 0;
  while (n)
  {
    p = n;
    n = n->next;
    delete p;
  }
  head = 0;
  chunks = 0;
  nchunks = 0;
  free=0; 
}

// ************************************************************
// Grow
// ************************************************************
//
void G4AllocatorPool::Grow()
{
  // Allocate new chunk, organize it as a linked list of
  // elements of size 'esize'
  //
  G4PoolChunk* n = new G4PoolChunk(csize);
  n->next = chunks;
  chunks = n;
  nchunks++;

  const int nelem = csize/esize;
  char* start = n->mem;
  char* last = &start[(nelem-1)*esize];
  for (char* p=start; p<last; p+=esize)
  {
    reinterpret_cast<G4PoolLink*>(p)->next
      = reinterpret_cast<G4PoolLink*>(p+esize);
  }
  reinterpret_cast<G4PoolLink*>(last)->next = 0;
  head = reinterpret_cast<G4PoolLink*>(start);
}

G4AllocatorPool::G4PoolChunk * G4AllocatorPool::GetChunk(G4PoolLink*p){
  int k=0;
  for(G4PoolChunk*n=chunks;k++<nchunks;n=n->next){
     G4PoolLink *beg=reinterpret_cast<G4PoolLink*>(n->mem);
     G4PoolLink *end=reinterpret_cast<G4PoolLink*>(n->mem+csize);
     if(p>=beg && p<end){
       return n; 
  }
  }
  std::cerr<<" G4AllocatorPool::GetChunk-S-NoPoolChunk "<<p<<" "<<" "<<nchunks<<std::endl ;

return 0;
}
/*
void G4AllocatorPool::Free( void* b )
{
  G4PoolLink* p = static_cast<G4PoolLink*>(b);
  p->next = head;        // put b back as first element
  head = p;
  G4PoolChunk *n=GetChunk(p);
  if(n){
    n->used--;
    if(n->used==0)free++;
   }
   unsigned long long size=Size();
  if(size>Threshold  && free>nchunks/2+1){
   unsigned long long coll=CollectGarbage();
   unsigned int mess=0;
   const unsigned int gmess=1000;
   if(mess++<gmess)std::cout<<" G4AllocatorPool::Free-I-GarbageCollected "<<coll<<" From "<<size<<" To "<<Size()<<std::endl;
}
}
*/
unsigned long long G4AllocatorPool::CollectGarbage(){
//std::cout<<" G4AllocatorPool::CollectGarbage-I-Entered "<<std::endl;
G4PoolLink *prev=0;
unsigned int el=0;
for(G4PoolLink *p=head;p;p=p->next){
G4PoolChunk *n=GetChunk(p);
if(n && n->used==0){
el++;
if(prev)prev->next=p->next;
else head=p->next;
}
else prev=p;
}
 std::vector<G4PoolChunk*> del;
G4PoolChunk * nrev=0;
int k=0;
for(G4PoolChunk*n=chunks;k++<nchunks;n=n->next){
if(n->used==0){
     if(nrev)nrev->next=n->next;
     else chunks=n->next;
     del.push_back(n);
    }
    else{
      if(n->used<0){
    std::cerr<<" G4AllocatorPool::CollectGarbage-S-UsedNegative "<<n->used<<std::endl;
     }
     nrev=n;
    }
  }
  unsigned long long size=0;
  for(int k=0;k<del.size();k++){
    delete del[k];
    nchunks--;
    free--;
    size+=csize;
  }
//   std::cout<<"G4AllocatorPool::CollectGarbage-I- "<<del.size()<<" "<<nchunks<<" "<<esize<<" "<<csize<<" "<<std::endl;
  return size;
}
