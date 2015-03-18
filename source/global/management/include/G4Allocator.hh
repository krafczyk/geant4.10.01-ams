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
// ------------------------------------------------------------
// GEANT 4 class header file 
//
// Class Description:
//
// A class for fast allocation of objects to the heap through a pool of
// chunks organised as linked list. It's meant to be used by associating
// it to the object to be allocated and defining for it new and delete
// operators via MallocSingle() and FreeSingle() methods.
       
//      ---------------- G4Allocator ----------------
//
// Author: G.Cosmo (CERN), November 2000
// ------------------------------------------------------------

#ifndef G4Allocator_h
#define G4Allocator_h 1

#include <cstddef>

#include "G4AllocatorPool.hh"
#include <string>
#include <typeinfo>
class G4AllocatorBase
{
  public:
    std::string tn;
    G4AllocatorBase(); 
    virtual ~G4AllocatorBase();
    virtual void ResetStorage()=0;
    virtual void ClearStorage(unsigned long long sz)=0;
    virtual size_t GetAllocatedSize() const=0;
    virtual int GetNoPages() const=0;
    virtual size_t GetPageSize() const=0;
    virtual int GetUsed() const=0; 
    virtual int GetFree() const=0;
    virtual void IncreasePageSize( unsigned int sz )=0;
    virtual size_t CollectGarbage()=0; 
    virtual G4AllocatorPool::G4PoolChunk* GetChunk(void* anElement)=0;


};

template <class Type>
class G4Allocator : public G4AllocatorBase
{
  public:  // with description

    G4Allocator() throw();
    ~G4Allocator() throw();
      // Constructor & destructor

    inline Type* MallocSingle();
    inline void FreeSingle(Type* anElement);
 
      // Malloc and Free methods to be used when overloading
      // new and delete operators in the client <Type> object

      inline void ResetStorage();
      inline void ClearStorage(unsigned long long sz);
      // Returns allocated storage to the free store, resets allocator.
      // Note: contents in memory are lost using this call !
     inline size_t CollectGarbage();
     inline G4AllocatorPool::G4PoolChunk* GetChunk(void* anElement);
    inline size_t GetAllocatedSize() const;
      // Returns the size of the total memory allocated
    inline int GetNoPages() const;
    inline int GetUsed() const;
    inline int GetFree() const;
      // Returns the total number of allocated pages
    inline size_t GetPageSize() const;
      // Returns the current size of a page
    inline void IncreasePageSize( unsigned int sz );
      // Resets allocator and increases default page size of a given factor

  public:  // without description

    // This public section includes standard methods and types
    // required if the allocator is to be used as alternative
    // allocator for STL containers.
    // NOTE: the code below is a trivial implementation to make
    //       this class an STL compliant allocator.
    //       It is anyhow NOT recommended to use this class as
    //       alternative allocator for STL containers !

    typedef Type value_type;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;
    typedef Type* pointer;
    typedef const Type* const_pointer;
    typedef Type& reference;
    typedef const Type& const_reference;

    template <class U> G4Allocator(const G4Allocator<U>& right) throw()
      : mem(right.mem) {}
      // Copy constructor

    pointer address(reference r) const { return &r; }
    const_pointer address(const_reference r) const { return &r; }
      // Returns the address of values

    pointer allocate(size_type n, void* = 0)
    {
      // Allocates space for n elements of type Type, but does not initialise
      //
      Type* mem_alloc = 0;
      if (n == 1)
        mem_alloc = MallocSingle();
      else
        mem_alloc = static_cast<Type*>(::operator new(n*sizeof(Type)));
      return mem_alloc;
    }
    void deallocate(pointer p, size_type n)
    {
      // Deallocates n elements of type Type, but doesn't destroy
      //
      if (n == 1)
        FreeSingle(p);
      else
        ::operator delete((void*)p);
      return;
    }

    void construct(pointer p, const Type& val) { new((void*)p) Type(val); }
      // Initialises *p by val
    void destroy(pointer p) { p->~Type(); }
      // Destroy *p but doesn't deallocate

    size_type max_size() const throw()
    {
      // Returns the maximum number of elements that can be allocated
      //
      return 2147483647/sizeof(Type);
    }

    template <class U>
    struct rebind { typedef G4Allocator<U> other; };
      // Rebind allocator to type U

    G4AllocatorPool mem;
      // Pool of elements of sizeof(Type)
};

// ------------------------------------------------------------
// Inline implementation
// ------------------------------------------------------------

// Initialization of the static pool
//
// template <class Type> G4AllocatorPool G4Allocator<Type>::mem(sizeof(Type));

// ************************************************************
// G4Allocator constructor
// ************************************************************
//
template <class Type>
G4Allocator<Type>::G4Allocator() throw()
  : mem(sizeof(Type))
{
tn=typeid(this).name();
}
// ************************************************************
// G4Allocator destructor
// ************************************************************
//
template <class Type>
G4Allocator<Type>::~G4Allocator() throw()
{
}

// ************************************************************
// MallocSingle
// ************************************************************
//
template <class Type>
Type* G4Allocator<Type>::MallocSingle()
{
  return static_cast<Type*>(mem.Alloc());
}

// ************************************************************
// FreeSingle
// ************************************************************
//
template <class Type>
void G4Allocator<Type>::FreeSingle(Type* anElement)
{
  mem.Free(anElement);
  return;
}

template <class Type>
G4AllocatorPool::G4PoolChunk* G4Allocator<Type>::GetChunk(void* b)
{
 G4AllocatorPool::G4PoolLink* p = static_cast<G4AllocatorPool::G4PoolLink*>(b);
  return mem.GetChunk(p);
}


// ************************************************************
// GetAllocatedSize
// ************************************************************
//
template <class Type>
size_t G4Allocator<Type>::GetAllocatedSize() const
{
  return mem.Size();
}


  template <class Type>
   void G4Allocator<Type>::ResetStorage()
    {
       // Clear all allocated storage and return it to the free store
       //
       mem.Reset();
       return;
  }




  template <class Type>
   void G4Allocator<Type>::ClearStorage(unsigned long long size)
    {
       // Clear  not necessarily all  allocated storage and return it to the free store
       //
       mem.Reset(size);
       return;
       }


template <class Type>
size_t G4Allocator<Type>::CollectGarbage() 
{
  return mem.CollectGarbage();
}



// ************************************************************
// GetNoPages
// ************************************************************
//
template <class Type>
int G4Allocator<Type>::GetNoPages() const
{
  return mem.GetNoPages();
}

template <class Type>
int G4Allocator<Type>::GetUsed() const
{
  return mem.GetUsed();
}


template <class Type>
int G4Allocator<Type>::GetFree() const
{
  return mem.GetFree();
}






// ************************************************************
// GetPageSize
// ************************************************************
//
template <class Type>
size_t G4Allocator<Type>::GetPageSize() const
{
  return mem.GetPageSize();
}

// ************************************************************
// IncreasePageSize
// ************************************************************
//
template <class Type>
void G4Allocator<Type>::IncreasePageSize( unsigned int sz )
{
  ResetStorage();
  mem.GrowPageSize(sz); 
}

// ************************************************************
// operator==
// ************************************************************
//
template <class T1, class T2>
bool operator== (const G4Allocator<T1>&, const G4Allocator<T2>&) throw()
{
  return true;
}

// ************************************************************
// operator!=
// ************************************************************
//
template <class T1, class T2>
bool operator!= (const G4Allocator<T1>&, const G4Allocator<T2>&) throw()
{
  return false;
}

#endif
