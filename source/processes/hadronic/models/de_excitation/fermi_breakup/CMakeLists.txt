#------------------------------------------------------------------------------
# CMakeLists.txt
# Module : G4hadronic_deex_fermi_breakup
# Package: Geant4.src.G4processes.G4hadronic.G4hadronic_models.G4hadronic_deex.G4hadronic_deex_fermi_breakup
#
# CMakeLists.txt for building a single granular library.
#
# Generated on : 24/9/2010
#
# $Id$
#
#------------------------------------------------------------------------------

if(GEANT4_BUILD_GRANULAR_LIBS)
    include(Geant4MacroLibraryTargets)
    GEANT4_GRANULAR_LIBRARY_TARGET(COMPONENT sources.cmake)
endif()

