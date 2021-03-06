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
// -------------------------------------------------------------------
//      GEANT 4 class header file 
//
// Class description:
//
// Class implementing a memory pool for fast allocation and deallocation
// of memory chunks.  The size of the chunks for small allocated objects
// is fixed to 1Kb and takes into account of memory alignment; for large
// objects it is set to 10 times the object's size.
// The implementation is derived from: B.Stroustrup, The C++ Programming
// Language, Third Edition.

//           -------------- G4AllocatorPool ----------------
//
// Author: G.Cosmo (CERN), November 2000
// -------------------------------------------------------------------

#ifndef G4AllocatorPool_h
#define G4AllocatorPool_h 1
#include <map>
class G4AllocatorPool
{
  public:
  static   long long gThreshold;  // Garbage Collection Threshold
  public:
   static unsigned long long  GetThreshold(){return gThreshold>0?gThreshold:-gThreshold;}
   static bool AutoGarbageCollectionOn(){return gThreshold>0;}
   static bool GarbageCollectionOff(){return gThreshold==0;} 
   static void SetGarbageCollection(unsigned long long threshold=1000000, bool autogarbage=false); 
       
    explicit G4AllocatorPool( unsigned int n=0 );
      // Create a pool of elements of size n
    ~G4AllocatorPool();
      // Destructor. Return storage to the free store
    inline void* Alloc();
      // Allocate one element
     inline void  Free( void* b );
      // Return an element back to the pool

    inline unsigned int  Size() const;
      // Return storage size
    void  Reset(unsigned long long size=0);
      // Return storage to the free store
    int GetUsed()const;
     inline int GetFree() const {return free;}
    inline int  GetNoPages() const;
      // Return the total number of allocated pages
    inline unsigned int  GetPageSize() const;
      // Accessor for default page size
    inline void GrowPageSize( unsigned int factor );
      // Increase default page size by a given factor
  private:

    G4AllocatorPool(const G4AllocatorPool& right);
      // Provate copy constructor
    G4AllocatorPool& operator= (const G4AllocatorPool& right);
      // Private equality operator
public:
    struct G4PoolLink
    {
      G4PoolLink* next;
    };
    class G4PoolChunk
    {
      public:
        explicit G4PoolChunk(unsigned int sz)
          : size(sz), mem(new char[size]), used(0), next(0) {;}
        ~G4PoolChunk() { delete [] mem; }
        const unsigned int size;
        char* mem;
        int used;
        G4PoolChunk* next;
    };

    void Grow();
      // Make pool larger
      //   
      //
     inline G4PoolChunk * GetChunk( G4PoolLink *p);
     unsigned long long CollectGarbage(); 
  private:

    const unsigned int esize;
    unsigned int csize;
    G4PoolChunk* chunks;
    G4PoolLink* head;
    int nchunks;
    int free;
    std::map<G4PoolLink*,G4PoolChunk*> fmap;
    std::map<G4PoolLink*,G4PoolChunk*>::iterator ith;
    
};

// ------------------------------------------------------------
// Inline implementation
// ------------------------------------------------------------

#include <iostream>
inline G4AllocatorPool::G4PoolChunk * G4AllocatorPool::GetChunk(G4PoolLink*p){
if(ith!=fmap.end() && ith->first>p && (const char*)(((const char*)(ith->first))-csize)<(const char*)p){
return ith->second;
}
ith=fmap.lower_bound(p);
if(ith!=fmap.end()){
return ith->second;
}
std::cerr<<" G4AllocatorPool::GetChunk-S-NoPoolChunk "<<p<<" "<<" "<<nchunks<<std::endl ;

return 0;
}



// ************************************************************
// Alloc
// ************************************************************
//
inline void*
G4AllocatorPool::Alloc()
{
  if (head==0) { Grow(); free++; }
  G4PoolLink* p = head;  // return first element
  head = p->next;
  if(GarbageCollectionOff())return p;
  G4PoolChunk*n=GetChunk(p);
  if(n && n->used++==0)free--;
  return p;
}

// ************************************************************
// Free
// ************************************************************
//
inline void G4AllocatorPool::Free( void* b )
{
  G4PoolLink* p = static_cast<G4PoolLink*>(b);
  p->next = head;        // put b back as first element
  head = p;
  if(GarbageCollectionOff())return ;
  G4PoolChunk *n=GetChunk(p);
  if(n && --(n->used)==0)free++;
  if(AutoGarbageCollectionOn() && free>nchunks/2+1 && Size()>GetThreshold() ){  
    CollectGarbage();
   // unsigned long long coll=CollectGarbage();
   //unsigned int mess=0;
   //const unsigned int gmess=1000;
   //if(mess++<gmess)std::cout<<" G4AllocatorPool::Free-I-GarbageCollected "<<coll<<" From "<<size<<" To "<<Size()<<std::endl;
}
}


// ************************************************************
// Size
// ************************************************************
//
inline unsigned int
G4AllocatorPool::Size() const
{
  return nchunks*csize;
}



// ************************************************************
// GetNoPages
// ************************************************************
//
inline int
G4AllocatorPool::GetNoPages() const
{
  return nchunks;
}

// ************************************************************
// GetPageSize
// ************************************************************
//
inline unsigned int
G4AllocatorPool::GetPageSize() const
{
  return csize;
}

// ************************************************************
// GrowPageSize
// ************************************************************
//
inline void
G4AllocatorPool::GrowPageSize( unsigned int sz )
{
  csize = (sz) ? sz*csize : csize; 
}

#endif
