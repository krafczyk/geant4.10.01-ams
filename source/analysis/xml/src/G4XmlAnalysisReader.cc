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

// Author: Ivana Hrivnacova, 25/07/2014 (ivana@ipno.in2p3.fr)

#include "G4XmlAnalysisReader.hh"
#include "G4XmlRFileManager.hh"
#include "G4H1ToolsManager.hh"
#include "G4H2ToolsManager.hh"
#include "G4H3ToolsManager.hh"
#include "G4P1ToolsManager.hh"
#include "G4P2ToolsManager.hh"
#include "G4XmlRNtupleManager.hh"
#include "G4XmlRNtupleDescription.hh"
#include "G4AnalysisVerbose.hh"
#include "G4AnalysisUtilities.hh"
#include "G4Threading.hh"

#include <iostream>
#include <cstdio>

using namespace G4Analysis;

G4XmlAnalysisReader* G4XmlAnalysisReader::fgMasterInstance = 0;
G4ThreadLocal G4XmlAnalysisReader* G4XmlAnalysisReader::fgInstance = 0;

//_____________________________________________________________________________
G4XmlAnalysisReader* G4XmlAnalysisReader::Instance()
{
  if ( fgInstance == 0 ) {
    G4bool isMaster = ! G4Threading::IsWorkerThread();
    fgInstance = new G4XmlAnalysisReader(isMaster);
  }
  
  return fgInstance;
}    

//_____________________________________________________________________________
G4XmlAnalysisReader::G4XmlAnalysisReader(G4bool isMaster)
 : G4VAnalysisReader("Xml", isMaster),
   fH1Manager(0),
   fH2Manager(0),
   fH3Manager(0),
   fP1Manager(0),
   fP2Manager(0),
   fNtupleManager(0),
   fFileManager(0)
{
  if ( ( isMaster && fgMasterInstance ) || ( fgInstance ) ) {
    G4ExceptionDescription description;
    description 
      << "      " 
      << "G4XmlAnalysisReader already exists." 
      << "Cannot create another instance.";
    G4Exception("G4XmlAnalysisReader::G4XmlAnalysisReader()",
                "Analysis_F001", FatalException, description);
  }
  if ( isMaster ) fgMasterInstance = this;
  fgInstance = this;

  // Create managers
  fH1Manager = new G4H1ToolsManager(fState);
  fH2Manager = new G4H2ToolsManager(fState);
  fH3Manager = new G4H3ToolsManager(fState);
  fP1Manager = new G4P1ToolsManager(fState);
  fP2Manager = new G4P2ToolsManager(fState);
  fNtupleManager = new G4XmlRNtupleManager(fState);
  fFileManager = new G4XmlRFileManager(fState);
      // The managers will be deleted by the base class
  
  // Set managers to base class
  SetH1Manager(fH1Manager);
  SetH2Manager(fH2Manager);
  SetH3Manager(fH3Manager);
  SetP1Manager(fP1Manager);
  SetP2Manager(fP2Manager);
  SetNtupleManager(fNtupleManager);
  SetFileManager(fFileManager);
}

//_____________________________________________________________________________
G4XmlAnalysisReader::~G4XmlAnalysisReader()
{
  if ( fState.GetIsMaster() ) fgMasterInstance = 0;
  fgInstance = 0;
}

// 
// private methods
//

//_____________________________________________________________________________
tools::raxml_out* G4XmlAnalysisReader::GetHandler(
                             const G4String& fileName, 
                             const G4String& objectName,
                             const G4String& objectType,
                             const G4String& inFunction)
{
// Get buffer for reading object specified by objectName and objectType
// for a file specified by fileName; 
// open the file if it was not yet open 

  // Histograms and profiles are not saved per thread
  // and ntuple file name is already updated
  tools::raxml* rfile = fFileManager->GetRFile(fileName);
  if ( ! rfile ) {
    if ( ! fFileManager->OpenRFile(fileName) ) return 0;
    rfile = fFileManager->GetRFile(fileName);
  }

  tools::raxml_out* handler = 0;
  if ( rfile ) {
    std::vector<tools::raxml_out>& objects = rfile->objects();
    std::vector<tools::raxml_out>::iterator it;
    for (it = objects.begin(); it!=objects.end(); ++it) {
      tools::raxml_out& object = *it;
      if ( object.cls() == objectType && object.name() == objectName ) {
        handler = &object;
        break;
      }  
    }
  }  
  
  if ( ! handler ) {
    G4ExceptionDescription description;
    description 
      << "      " 
      << "Cannot get "<< objectName << " in file " << fileName; 
    G4String inFunctionFull = "G4XmlAnalysisReader::";
    inFunctionFull.append(inFunction);
    G4Exception(inFunctionFull, "Analysis_WR011", JustWarning, description);
    return 0;
  }
  
  return handler;  
}                             

//_____________________________________________________________________________
G4bool G4XmlAnalysisReader::Reset()
{
// Reset histograms and ntuple

  G4bool finalResult = true;
  
  G4bool result = fH1Manager->Reset();
  finalResult = finalResult && result;

  result = fH2Manager->Reset();
  finalResult = finalResult && result;
  
  result = fNtupleManager->Reset();
  finalResult = finalResult && result;
  
  return finalResult;
}  
 
// 
// protected methods
//

//_____________________________________________________________________________
G4int G4XmlAnalysisReader::ReadH1Impl(const G4String& h1Name, 
                                      const G4String& fileName,
                                      G4bool /*isUserFileName*/)
{
#ifdef G4VERBOSE
  if ( fState.GetVerboseL4() ) 
    fState.GetVerboseL4()->Message("read", "h1", h1Name);
#endif

  tools::raxml_out* handler
    = GetHandler(fileName, h1Name, tools::histo::h1d::s_class(), "ReadH1Impl");
  if ( ! handler ) return kInvalidId;

  tools::histo::h1d* h1 
    = static_cast<tools::histo::h1d*>(handler->object());
  G4int id = fH1Manager->AddH1(h1Name, h1);

#ifdef G4VERBOSE
  if ( fState.GetVerboseL2() ) 
    fState.GetVerboseL2()->Message("read", "h1", h1Name, id > kInvalidId);
#endif
  
  return id;  
}  

//_____________________________________________________________________________
G4int G4XmlAnalysisReader::ReadH2Impl(const G4String& h2Name, 
                                      const G4String& fileName,
                                      G4bool /*isUserFileName*/)
{
#ifdef G4VERBOSE
  if ( fState.GetVerboseL4() ) 
    fState.GetVerboseL4()->Message("read", "h2", h2Name);
#endif

  tools::raxml_out* handler
    = GetHandler(fileName, h2Name, tools::histo::h2d::s_class(), "ReadH2Impl");
  if ( ! handler ) return kInvalidId;

  tools::histo::h2d* h2 
    = static_cast<tools::histo::h2d*>(handler->object());
  G4int id = fH2Manager->AddH2(h2Name, h2);

#ifdef G4VERBOSE
  if ( fState.GetVerboseL2() ) 
    fState.GetVerboseL2()->Message("read", "h2", h2Name, id > kInvalidId);
#endif
  
  return id;  
}  

//_____________________________________________________________________________
G4int G4XmlAnalysisReader::ReadH3Impl(const G4String& h3Name, 
                                      const G4String& fileName,
                                      G4bool /*isUserFileName*/)
{
#ifdef G4VERBOSE
  if ( fState.GetVerboseL4() ) 
    fState.GetVerboseL4()->Message("read", "h3", h3Name);
#endif

  tools::raxml_out* handler
    = GetHandler(fileName, h3Name, tools::histo::h3d::s_class(), "ReadH3Impl");
  if ( ! handler ) return kInvalidId;

  tools::histo::h3d* h3 
    = static_cast<tools::histo::h3d*>(handler->object());
  G4int id = fH3Manager->AddH3(h3Name, h3);

#ifdef G4VERBOSE
  if ( fState.GetVerboseL2() ) 
    fState.GetVerboseL2()->Message("read", "h3", h3Name, id > kInvalidId);
#endif
  
  return id;  
}  

//_____________________________________________________________________________
G4int G4XmlAnalysisReader::ReadP1Impl(const G4String& p1Name, 
                                      const G4String& fileName,
                                      G4bool /*isUserFileName*/)
{
#ifdef G4VERBOSE
  if ( fState.GetVerboseL4() ) 
    fState.GetVerboseL4()->Message("read", "p1", p1Name);
#endif

  tools::raxml_out* handler
    = GetHandler(fileName, p1Name, tools::histo::p1d::s_class(), "ReadP1Impl");
  if ( ! handler ) return kInvalidId;

  tools::histo::p1d* p1 
    = static_cast<tools::histo::p1d*>(handler->object());
  G4int id = fP1Manager->AddP1(p1Name, p1);

#ifdef G4VERBOSE
  if ( fState.GetVerboseL2() ) 
    fState.GetVerboseL2()->Message("read", "p1", p1Name, id > kInvalidId);
#endif
  
  return id;  
}  

//_____________________________________________________________________________
G4int G4XmlAnalysisReader::ReadP2Impl(const G4String& p2Name, 
                                      const G4String& fileName,
                                      G4bool /*isUserFileName*/)
{
#ifdef G4VERBOSE
  if ( fState.GetVerboseL4() ) 
    fState.GetVerboseL4()->Message("read", "p2", p2Name);
#endif

  tools::raxml_out* handler
    = GetHandler(fileName, p2Name, tools::histo::p2d::s_class(), "ReadP2Impl");
  if ( ! handler ) return kInvalidId;

  tools::histo::p2d* p2 
    = static_cast<tools::histo::p2d*>(handler->object());
  G4int id = fP2Manager->AddP2(p2Name, p2);

#ifdef G4VERBOSE
  if ( fState.GetVerboseL2() ) 
    fState.GetVerboseL2()->Message("read", "p2", p2Name, id > kInvalidId);
#endif
  
  return id;  
}  

//_____________________________________________________________________________
G4int G4XmlAnalysisReader::ReadNtupleImpl(const G4String& ntupleName, 
                                          const G4String& fileName,
                                          G4bool isUserFileName)
{
#ifdef G4VERBOSE
  if ( fState.GetVerboseL4() ) 
    fState.GetVerboseL4()->Message("read", "ntuple", ntupleName);
#endif

  // Ntuples are saved per object and per thread
  // but apply the ntuple name and the thread suffixes
  // only if fileName is not provided explicitly
  G4String fullFileName = fileName;
  if ( ! isUserFileName ) {
    fullFileName = fFileManager->GetNtupleFileName(ntupleName);
  }  

  tools::raxml_out* handler
    = GetHandler(fullFileName, ntupleName, tools::aida::ntuple::s_class(), 
                 "ReadNtupleImpl");
  if ( ! handler ) return kInvalidId;

  tools::aida::ntuple* rntuple 
    = static_cast<tools::aida::ntuple*>(handler->object());
  G4int id 
    = fNtupleManager->SetNtuple(new G4XmlRNtupleDescription(rntuple));
  
#ifdef G4VERBOSE
  if ( fState.GetVerboseL2() ) 
    fState.GetVerboseL2()->Message("read", "ntuple", ntupleName, id > kInvalidId);
#endif
  
  return id;
}  
