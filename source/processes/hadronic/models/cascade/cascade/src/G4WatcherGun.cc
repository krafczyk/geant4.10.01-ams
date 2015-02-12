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
// To include numerous high-Z watchers (e.g., for proton-lead collisions)
// set the preprocessor flag G4CASCADE_WATCHER_HIGHZ
//
// 20100407  M. Kelsey -- Replace std::vector<>::resize(0) with ::clear(),
//		and create vectors pre-sized to maximum needed.
//

#include "G4WatcherGun.hh"
#include "G4ios.hh"

G4WatcherGun::G4WatcherGun()
  : verboseLevel(0) {

  if (verboseLevel > 3) {
    G4cout << " >>> G4WatcherGun::G4WatcherGun" << G4endl;
  }
}

void G4WatcherGun::setWatchers() {

  if (verboseLevel > 3) {
    G4cout << " >>> G4WatcherGun::setWatchers" << G4endl;
  }

  std::vector<G4double> as(27);		// Reserve maximum number of entries
  std::vector<G4double> cs(27);
  std::vector<G4double> errs(27);

  // specific stuff to monitor the difference with fortran
  // particle type
  // Z = 0
  as.push_back(1.0);
  cs.push_back(33520.0);
  errs.push_back(12.4);
  as.push_back(0.0);
  cs.push_back(217.4);
  errs.push_back(1.22);
  watchers.push_back(G4NuclWatcher(0, as, cs, errs, false, false));

  // Z = 1
  as.clear();
  cs.clear();
  errs.clear();
  as.push_back(1.0);
  cs.push_back(7645.0);
  errs.push_back(6.08);
  as.push_back(0.0);
  cs.push_back(109.4);
  errs.push_back(0.96);
  as.push_back(2.0);
  cs.push_back(658.7);
  errs.push_back(4.2);
  as.push_back(3.0);
  cs.push_back(338.6);
  errs.push_back(3.1);
  watchers.push_back(G4NuclWatcher(1, as, cs, errs, false, false));

  // Z = 1
  as.clear();
  cs.clear();
  errs.clear();
  as.push_back(2.0);
  cs.push_back(658.7);
  errs.push_back(4.2);
  as.push_back(3.0);
  cs.push_back(338.6);
  errs.push_back(3.1);
  watchers.push_back(G4NuclWatcher(1, as, cs, errs, false, true));
  
  // Z = -1
  as.clear();
  cs.clear();
  errs.clear();
  as.push_back(0.0);
  cs.push_back(198.3);
  errs.push_back(1.0);
  watchers.push_back(G4NuclWatcher(-1, as, cs, errs, false, false));

  // Z = 2
  as.clear();
  cs.clear();
  errs.clear();
  as.push_back(3.0);
  cs.push_back(28.2);
  errs.push_back(1.0);
  as.push_back(4.0);
  cs.push_back(781.0);
  errs.push_back(5.0);
  watchers.push_back(G4NuclWatcher(2, as, cs, errs, false, true));

#ifdef G4CASCADE_WATCHER_HIGHZ
  // Z = 22
  // watchers for pb208 + 1 GeV p
  as.clear();
  cs.clear();
  errs.clear();
  as.push_back(47.0);
  cs.push_back(0.2);
  errs.push_back(0.029);
  as.push_back(48.0);
  cs.push_back(0.288);
  errs.push_back(0.042);
  as.push_back(49.0);
  cs.push_back(0.349);
  errs.push_back(0.091);
  as.push_back(50.0);
  cs.push_back(0.277);
  errs.push_back(0.061);
  as.push_back(51.0);
  cs.push_back(0.128);
  errs.push_back(0.054);
  as.push_back(52.0);
  cs.push_back(0.06);
  errs.push_back(0.023);
  watchers.push_back(G4NuclWatcher(22, as, cs, errs, false, true));

  // Z = 23
  as.clear();
  cs.clear();
  errs.clear();
  as.push_back(49.0);
  cs.push_back(0.182);
  errs.push_back(0.026);
  as.push_back(50.0);
  cs.push_back(0.303);
  errs.push_back(0.038);
  as.push_back(51.0);
  cs.push_back(0.367);
  errs.push_back(0.084);
  as.push_back(52.0);
  cs.push_back(0.273);
  errs.push_back(0.057);
  as.push_back(53.0);
  cs.push_back(0.239);
  errs.push_back(0.051);
  as.push_back(54.0);
  cs.push_back(0.121);
  errs.push_back(0.022);
  as.push_back(55.0);
  cs.push_back(0.05);
  errs.push_back(0.012);
  watchers.push_back(G4NuclWatcher(23, as, cs, errs, false, true));

  // Z = 24
  as.clear();
  cs.clear();
  errs.clear();
  as.push_back(51.0);
  cs.push_back(0.215);
  errs.push_back(0.024);
  as.push_back(52.0);
  cs.push_back(0.366);
  errs.push_back(0.039);
  as.push_back(53.0);
  cs.push_back(0.386);
  errs.push_back(0.078);
  as.push_back(54.0);
  cs.push_back(0.452);
  errs.push_back(0.068);
  as.push_back(55.0);
  cs.push_back(0.25);
  errs.push_back(0.048);
  as.push_back(56.0);
  cs.push_back(0.217);
  errs.push_back(0.035);
  as.push_back(57.0);
  cs.push_back(0.092);
  errs.push_back(0.011);
  watchers.push_back(G4NuclWatcher(24, as, cs, errs, true, true));

  // Z = 25
  as.clear();
  cs.clear();
  errs.clear();
  as.push_back(53.0);
  cs.push_back(0.181);
  errs.push_back(0.022);
  as.push_back(54.0);
  cs.push_back(0.335);
  errs.push_back(0.035);
  as.push_back(55.0);
  cs.push_back(0.456);
  errs.push_back(0.073);
  as.push_back(56.0);
  cs.push_back(0.475);
  errs.push_back(0.063);
  as.push_back(57.0);
  cs.push_back(0.449);
  errs.push_back(0.046);
  as.push_back(58.0);
  cs.push_back(0.262);
  errs.push_back(0.033);
  as.push_back(59.0);
  cs.push_back(0.17);
  errs.push_back(0.021);
  as.push_back(60.0);
  cs.push_back(0.051);
  errs.push_back(0.015);
  watchers.push_back(G4NuclWatcher(25, as, cs, errs, false, true));

  // Z = 26
  as.clear();
  cs.clear();
  errs.clear();
  as.push_back(55.0);
  cs.push_back(0.129);
  errs.push_back(0.014);
  as.push_back(56.0);
  cs.push_back(0.382);
  errs.push_back(0.027);
  as.push_back(57.0);
  cs.push_back(0.478);
  errs.push_back(0.037);
  as.push_back(58.0);
  cs.push_back(0.649);
  errs.push_back(0.057);
  as.push_back(59.0);
  cs.push_back(0.523);
  errs.push_back(0.033);
  as.push_back(60.0);
  cs.push_back(0.446);
  errs.push_back(0.035);
  as.push_back(61.0);
  cs.push_back(0.263);
  errs.push_back(0.046);
  as.push_back(62.0);
  cs.push_back(0.09);
  errs.push_back(0.014);
  watchers.push_back(G4NuclWatcher(26, as, cs, errs, false, true));

  // Z = 27
  as.clear();
  cs.clear();
  errs.clear();
  as.push_back(57.0);
  cs.push_back(0.0866);
  errs.push_back(0.011);
  as.push_back(58.0);
  cs.push_back(0.311);
  errs.push_back(0.024);
  as.push_back(59.0);
  cs.push_back(0.549);
  errs.push_back(0.039);
  as.push_back(60.0);
  cs.push_back(0.665);
  errs.push_back(0.057);
  as.push_back(61.0);
  cs.push_back(0.714);
  errs.push_back(0.041);
  as.push_back(62.0);
  cs.push_back(0.586);
  errs.push_back(0.042);
  as.push_back(63.0);
  cs.push_back(0.429);
  errs.push_back(0.048);
  as.push_back(64.0);
  cs.push_back(0.167);
  errs.push_back(0.026);
  as.push_back(65.0);
  cs.push_back(0.108);
  errs.push_back(0.046);
  watchers.push_back(G4NuclWatcher(27, as, cs, errs, false, true));

  // Z = 28
  as.clear();
  cs.clear();
  errs.clear();
  as.push_back(59.0);
  cs.push_back(0.035);
  errs.push_back(0.006);
  as.push_back(60.0);
  cs.push_back(0.299);
  errs.push_back(0.02);
  as.push_back(61.0);
  cs.push_back(0.512);
  errs.push_back(0.038);
  as.push_back(62.0);
  cs.push_back(0.865);
  errs.push_back(0.057);
  as.push_back(63.0);
  cs.push_back(0.813);
  errs.push_back(0.045);
  as.push_back(64.0);
  cs.push_back(0.829);
  errs.push_back(0.053);
  as.push_back(65.0);
  cs.push_back(0.596);
  errs.push_back(0.056);
  as.push_back(66.0);
  cs.push_back(0.318);
  errs.push_back(0.072);
  as.push_back(67.0);
  cs.push_back(0.139);
  errs.push_back(0.056);
  as.push_back(68.0);
  cs.push_back(0.054);
  errs.push_back(0.036);
  watchers.push_back(G4NuclWatcher(28, as, cs, errs, true, true));

  // Z = 29
  as.clear();
  cs.clear();
  errs.clear();
  as.push_back(61.0);
  cs.push_back(0.026);
  errs.push_back(0.004);
  as.push_back(62.0);
  cs.push_back(0.179);
  errs.push_back(0.016);
  as.push_back(63.0);
  cs.push_back(0.464);
  errs.push_back(0.03);
  as.push_back(64.0);
  cs.push_back(0.759);
  errs.push_back(0.06);
  as.push_back(65.0);
  cs.push_back(0.973);
  errs.push_back(0.044);
  as.push_back(66.0);
  cs.push_back(0.951);
  errs.push_back(0.055);
  as.push_back(67.0);
  cs.push_back(0.872);
  errs.push_back(0.064);
  as.push_back(68.0);
  cs.push_back(0.485);
  errs.push_back(0.071);
  as.push_back(69.0);
  cs.push_back(0.239);
  errs.push_back(0.056);
  as.push_back(70.0);
  cs.push_back(0.088);
  errs.push_back(0.032);
  as.push_back(71.0);
  cs.push_back(0.041);
  errs.push_back(0.024);
  watchers.push_back(G4NuclWatcher(29, as, cs, errs, false, true));

  // Z = 30
  as.clear();
  cs.clear();
  errs.clear();
  as.push_back(64.0);
  cs.push_back(0.149);
  errs.push_back(0.013);
  as.push_back(65.0);
  cs.push_back(0.422);
  errs.push_back(0.026);
  as.push_back(66.0);
  cs.push_back(0.813);
  errs.push_back(0.059);
  as.push_back(67.0);
  cs.push_back(1.05);
  errs.push_back(0.046);
  as.push_back(68.0);
  cs.push_back(1.205);
  errs.push_back(0.06);
  as.push_back(69.0);
  cs.push_back(1.211);
  errs.push_back(0.073);
  as.push_back(70.0);
  cs.push_back(0.754);
  errs.push_back(0.082);
  as.push_back(71.0);
  cs.push_back(0.401);
  errs.push_back(0.053);
  as.push_back(72.0);
  cs.push_back(0.193);
  errs.push_back(0.038);
  as.push_back(73.0);
  cs.push_back(0.082);
  errs.push_back(0.034);
  watchers.push_back(G4NuclWatcher(30, as, cs, errs, false, true));

  // Z = 31
  as.clear();
  cs.clear();
  errs.clear();
  as.push_back(66.0);
  cs.push_back(0.082);
  errs.push_back(0.008);
  as.push_back(67.0);
  cs.push_back(0.353);
  errs.push_back(0.022);
  as.push_back(68.0);
  cs.push_back(0.737);
  errs.push_back(0.059);
  as.push_back(69.0);
  cs.push_back(1.215);
  errs.push_back(0.049);
  as.push_back(70.0);
  cs.push_back(1.299);
  errs.push_back(0.087);
  as.push_back(71.0);
  cs.push_back(1.453);
  errs.push_back(0.085);
  as.push_back(72.0);
  cs.push_back(1.135);
  errs.push_back(0.096);
  as.push_back(73.0);
  cs.push_back(0.635);
  errs.push_back(0.064);
  as.push_back(74.0);
  cs.push_back(0.334);
  errs.push_back(0.037);
  as.push_back(75.0);
  cs.push_back(0.179);
  errs.push_back(0.047);
  as.push_back(76.0);
  cs.push_back(0.061);
  errs.push_back(0.014);
  watchers.push_back(G4NuclWatcher(31, as, cs, errs, true, true));

  // Z = 32
  as.clear();
  cs.clear();
  errs.clear();
  as.push_back(68.0);
  cs.push_back(0.038);
  errs.push_back(0.005);
  as.push_back(69.0);
  cs.push_back(0.286);
  errs.push_back(0.019);
  as.push_back(70.0);
  cs.push_back(0.719);
  errs.push_back(0.057);
  as.push_back(71.0);
  cs.push_back(1.237);
  errs.push_back(0.056);
  as.push_back(72.0);
  cs.push_back(1.608);
  errs.push_back(0.092);
  as.push_back(73.0);
  cs.push_back(1.626);
  errs.push_back(0.089);
  as.push_back(74.0);
  cs.push_back(1.651);
  errs.push_back(0.107);
  as.push_back(75.0);
  cs.push_back(0.938);
  errs.push_back(0.094);
  as.push_back(76.0);
  cs.push_back(0.61);
  errs.push_back(0.046);
  as.push_back(77.0);
  cs.push_back(0.233);
  errs.push_back(0.076);
  as.push_back(78.0);
  cs.push_back(0.098);
  errs.push_back(0.013);
  as.push_back(79.0);
  cs.push_back(0.04);
  errs.push_back(0.018);
  watchers.push_back(G4NuclWatcher(32, as, cs, errs, false, true));

  // Z = 33
  as.clear();
  cs.clear();
  errs.clear();
  as.push_back(71.0);
  cs.push_back(0.176);
  errs.push_back(0.014);
  as.push_back(72.0);
  cs.push_back(0.493);
  errs.push_back(0.041);
  as.push_back(73.0);
  cs.push_back(1.189);
  errs.push_back(0.055);
  as.push_back(74.0);
  cs.push_back(1.659);
  errs.push_back(0.09);
  as.push_back(75.0);
  cs.push_back(2.066);
  errs.push_back(0.115);
  as.push_back(76.0);
  cs.push_back(1.838);
  errs.push_back(0.119);
  as.push_back(77.0);
  cs.push_back(1.48);
  errs.push_back(0.132);
  as.push_back(78.0);
  cs.push_back(0.815);
  errs.push_back(0.05);
  as.push_back(79.0);
  cs.push_back(0.406);
  errs.push_back(0.073);
  as.push_back(80.0);
  cs.push_back(0.201);
  errs.push_back(0.013);
  as.push_back(81.0);
  cs.push_back(0.079);
  errs.push_back(0.024);
  as.push_back(82.0);
  cs.push_back(0.023);
  errs.push_back(0.01);
  watchers.push_back(G4NuclWatcher(33, as, cs, errs, false, true));

  // Z = 34
  as.clear();
  cs.clear();
  errs.clear();
  as.push_back(73.0);
  cs.push_back(0.102);
  errs.push_back(0.011);
  as.push_back(74.0);
  cs.push_back(0.523);
  errs.push_back(0.041);
  as.push_back(75.0);
  cs.push_back(1.136);
  errs.push_back(0.056);
  as.push_back(76.0);
  cs.push_back(1.741);
  errs.push_back(0.092);
  as.push_back(77.0);
  cs.push_back(2.144);
  errs.push_back(0.115);
  as.push_back(78.0);
  cs.push_back(2.432);
  errs.push_back(0.137);
  as.push_back(79.0);
  cs.push_back(1.904);
  errs.push_back(0.156);
  as.push_back(80.0);
  cs.push_back(1.205);
  errs.push_back(0.056);
  as.push_back(81.0);
  cs.push_back(0.698);
  errs.push_back(0.075);
  as.push_back(82.0);
  cs.push_back(0.328);
  errs.push_back(0.02);
  as.push_back(83.0);
  cs.push_back(0.147);
  errs.push_back(0.045);
  as.push_back(84.0);
  cs.push_back(0.045);
  errs.push_back(0.012);
  watchers.push_back(G4NuclWatcher(34, as, cs, errs, false, true));

  // Z = 35
  as.clear();
  cs.clear();
  errs.clear();
  as.push_back(75.0);
  cs.push_back(0.048);
  errs.push_back(0.006);
  as.push_back(76.0);
  cs.push_back(0.315);
  errs.push_back(0.033);
  as.push_back(77.0);
  cs.push_back(0.973);
  errs.push_back(0.052);
  as.push_back(78.0);
  cs.push_back(1.494);
  errs.push_back(0.086);
  as.push_back(79.0);
  cs.push_back(2.269);
  errs.push_back(0.113);
  as.push_back(80.0);
  cs.push_back(2.566);
  errs.push_back(0.153);
  as.push_back(81.0);
  cs.push_back(2.469);
  errs.push_back(0.162);
  as.push_back(82.0);
  cs.push_back(1.554);
  errs.push_back(0.063);
  as.push_back(83.0);
  cs.push_back(0.991);
  errs.push_back(0.094);
  as.push_back(84.0);
  cs.push_back(0.454);
  errs.push_back(0.023);
  as.push_back(85.0);
  cs.push_back(0.196);
  errs.push_back(0.048);
  as.push_back(86.0);
  cs.push_back(0.095);
  errs.push_back(0.012);
  as.push_back(87.0);
  cs.push_back(0.033);
  errs.push_back(0.02);
  watchers.push_back(G4NuclWatcher(35, as, cs, errs, false, true));

  // spallation part
  // Z = 61
  as.clear();
  cs.clear();
  errs.clear();
  as.push_back(132.0);
  cs.push_back(0.002);
  errs.push_back(0.001);
  as.push_back(133.0);
  cs.push_back(0.009);
  errs.push_back(0.002);
  as.push_back(134.0);
  cs.push_back(0.033);
  errs.push_back(0.003);
  as.push_back(135.0);
  cs.push_back(0.076);
  errs.push_back(0.003);
  as.push_back(136.0);
  cs.push_back(0.128);
  errs.push_back(0.005);
  as.push_back(137.0);
  cs.push_back(0.175);
  errs.push_back(0.006);
  as.push_back(138.0);
  cs.push_back(0.179);
  errs.push_back(0.007);
  as.push_back(139.0);
  cs.push_back(0.17);
  errs.push_back(0.01);
  as.push_back(140.0);
  cs.push_back(0.158);
  errs.push_back(0.009);
  as.push_back(141.0);
  cs.push_back(0.141);
  errs.push_back(0.018);
  as.push_back(142.0);
  cs.push_back(0.083);
  errs.push_back(0.018);
  as.push_back(143.0);
  cs.push_back(0.065);
  errs.push_back(0.022);
  as.push_back(144.0);
  cs.push_back(0.036);
  errs.push_back(0.019);
  as.push_back(145.0);
  cs.push_back(0.023);
  errs.push_back(0.016);
  watchers.push_back(G4NuclWatcher(61, as, cs, errs, true, true));

  // Z = 69
  as.clear();
  cs.clear();
  errs.clear();
  as.push_back(152.0);
  cs.push_back(0.045);
  errs.push_back(0.003);
  as.push_back(153.0);
  cs.push_back(0.18);
  errs.push_back(0.007);
  as.push_back(154.0);
  cs.push_back(0.435);
  errs.push_back(0.016);
  as.push_back(155.0);
  cs.push_back(0.845);
  errs.push_back(0.026);
  as.push_back(156.0);
  cs.push_back(1.283);
  errs.push_back(0.041);
  as.push_back(157.0);
  cs.push_back(1.843);
  errs.push_back(0.057);
  as.push_back(158.0);
  cs.push_back(1.986);
  errs.push_back(0.065);
  as.push_back(159.0);
  cs.push_back(2.078);
  errs.push_back(0.066);
  as.push_back(160.0);
  cs.push_back(1.993);
  errs.push_back(0.063);
  as.push_back(161.0);
  cs.push_back(1.602);
  errs.push_back(0.052);
  as.push_back(162.0);
  cs.push_back(1.241);
  errs.push_back(0.041);
  as.push_back(163.0);
  cs.push_back(0.881);
  errs.push_back(0.03);
  as.push_back(164.0);
  cs.push_back(0.502);
  errs.push_back(0.025);
  as.push_back(165.0);
  cs.push_back(0.299);
  errs.push_back(0.017);
  as.push_back(166.0);
  cs.push_back(0.157);
  errs.push_back(0.008);
  as.push_back(167.0);
  cs.push_back(0.078);
  errs.push_back(0.016);
  as.push_back(168.0);
  cs.push_back(0.033);
  errs.push_back(0.006);
  as.push_back(169.0);
  cs.push_back(0.014);
  errs.push_back(0.01);
  watchers.push_back(G4NuclWatcher(69, as, cs, errs, true, true));

  // Z = 73
  as.clear();
  cs.clear();
  errs.clear();
  as.push_back(160.0);
  cs.push_back(0.003);
  errs.push_back(0.002);
  as.push_back(161.0);
  cs.push_back(0.028);
  errs.push_back(0.003);
  as.push_back(162.0);
  cs.push_back(0.136);
  errs.push_back(0.008);
  as.push_back(163.0);
  cs.push_back(0.484);
  errs.push_back(0.015);
  as.push_back(164.0);
  cs.push_back(1.142);
  errs.push_back(0.039);
  as.push_back(165.0);
  cs.push_back(2.406);
  errs.push_back(0.074);
  as.push_back(166.0);
  cs.push_back(4.178);
  errs.push_back(0.129);
  as.push_back(167.0);
  cs.push_back(5.438);
  errs.push_back(0.165);
  as.push_back(168.0);
  cs.push_back(6.645);
  errs.push_back(0.2);
  as.push_back(169.0);
  cs.push_back(7.348);
  errs.push_back(0.221);
  as.push_back(170.0);
  cs.push_back(6.672);
  errs.push_back(0.202);
  as.push_back(171.0);
  cs.push_back(5.834);
  errs.push_back(0.177);
  as.push_back(172.0);
  cs.push_back(4.667);
  errs.push_back(0.141);
  as.push_back(173.0);
  cs.push_back(3.248);
  errs.push_back(0.099);
  as.push_back(174.0);
  cs.push_back(2.19);
  errs.push_back(0.068);
  as.push_back(175.0);
  cs.push_back(1.454);
  errs.push_back(0.048);
  as.push_back(176.0);
  cs.push_back(0.852);
  errs.push_back(0.032);
  as.push_back(177.0);
  cs.push_back(0.478);
  errs.push_back(0.03);
  as.push_back(178.0);
  cs.push_back(0.277);
  errs.push_back(0.019);
  as.push_back(179.0);
  cs.push_back(0.13);
  errs.push_back(0.025);
  as.push_back(180.0);
  cs.push_back(0.06);
  errs.push_back(0.012);
  as.push_back(181.0);
  cs.push_back(0.036);
  errs.push_back(0.023);
  as.push_back(182.0);
  cs.push_back(0.016);
  errs.push_back(0.009);
  watchers.push_back(G4NuclWatcher(73, as, cs, errs, true, true));

  // Z = 77
  as.clear();
  cs.clear();
  errs.clear();
  as.push_back(170.0);
  cs.push_back(0.003);
  errs.push_back(0.002);
  as.push_back(171.0);
  cs.push_back(0.024);
  errs.push_back(0.005);
  as.push_back(172.0);
  cs.push_back(0.108);
  errs.push_back(0.019);
  as.push_back(173.0);
  cs.push_back(0.423);
  errs.push_back(0.029);
  as.push_back(174.0);
  cs.push_back(1.203);
  errs.push_back(0.051);
  as.push_back(175.0);
  cs.push_back(2.714);
  errs.push_back(0.09);
  as.push_back(176.0);
  cs.push_back(5.004);
  errs.push_back(0.157);
  as.push_back(177.0);
  cs.push_back(7.545);
  errs.push_back(0.233);
  as.push_back(178.0);
  cs.push_back(9.685);
  errs.push_back(0.297);
  as.push_back(179.0);
  cs.push_back(11.664);
  errs.push_back(0.351);
  as.push_back(180.0);
  cs.push_back(12.576);
  errs.push_back(0.378);
  as.push_back(181.0);
  cs.push_back(11.851);
  errs.push_back(0.357);
  as.push_back(182.0);
  cs.push_back(11.269);
  errs.push_back(0.339);
  as.push_back(183.0);
  cs.push_back(10.266);
  errs.push_back(0.308);
  as.push_back(184.0);
  cs.push_back(7.748);
  errs.push_back(0.234);
  as.push_back(185.0);
  cs.push_back(6.576);
  errs.push_back(0.199);
  as.push_back(186.0);
  cs.push_back(4.567);
  errs.push_back(0.138);
  as.push_back(187.0);
  cs.push_back(3.318);
  errs.push_back(0.105);
  as.push_back(188.0);
  cs.push_back(2.478);
  errs.push_back(0.076);
  as.push_back(189.0);
  cs.push_back(1.703);
  errs.push_back(0.055);
  as.push_back(190.0);
  cs.push_back(1.003);
  errs.push_back(0.033);
  as.push_back(191.0);
  cs.push_back(0.744);
  errs.push_back(0.03);
  as.push_back(192.0);
  cs.push_back(0.468);
  errs.push_back(0.019);
  as.push_back(193.0);
  cs.push_back(0.222);
  errs.push_back(0.015);
  as.push_back(194.0);
  cs.push_back(0.133);
  errs.push_back(0.014);
  as.push_back(195.0);
  cs.push_back(0.05);
  errs.push_back(0.019);
  as.push_back(196.0);
  cs.push_back(0.037);
  errs.push_back(0.019);
  watchers.push_back(G4NuclWatcher(77, as, cs, errs, true, true));

  // Z = 81
  as.clear();
  cs.clear();
  errs.clear();
  as.push_back(184.0);
  cs.push_back(0.058);
  errs.push_back(0.026);
  as.push_back(185.0);
  cs.push_back(0.231);
  errs.push_back(0.06);
  as.push_back(186.0);
  cs.push_back(0.723);
  errs.push_back(0.1);
  as.push_back(187.0);
  cs.push_back(1.826);
  errs.push_back(0.098);
  as.push_back(188.0);
  cs.push_back(3.098);
  errs.push_back(0.111);
  as.push_back(189.0);
  cs.push_back(4.293);
  errs.push_back(0.157);
  as.push_back(190.0);
  cs.push_back(7.506);
  errs.push_back(0.227);
  as.push_back(191.0);
  cs.push_back(9.546);
  errs.push_back(0.288);
  as.push_back(192.0);
  cs.push_back(11.259);
  errs.push_back(0.339);
  as.push_back(193.0);
  cs.push_back(13.767);
  errs.push_back(0.414);
  as.push_back(194.0);
  cs.push_back(14.706);
  errs.push_back(0.442);
  as.push_back(195.0);
  cs.push_back(16.069);
  errs.push_back(0.483);
  as.push_back(196.0);
  cs.push_back(18.381);
  errs.push_back(0.552);
  as.push_back(197.0);
  cs.push_back(17.579);
  errs.push_back(0.528);
  as.push_back(198.0);
  cs.push_back(17.002);
  errs.push_back(0.51);
  as.push_back(199.0);
  cs.push_back(18.381);
  errs.push_back(0.552);
  as.push_back(200.0);
  cs.push_back(16.976);
  errs.push_back(0.509);
  as.push_back(201.0);
  cs.push_back(16.913);
  errs.push_back(0.508);
  as.push_back(202.0);
  cs.push_back(17.262);
  errs.push_back(0.518);
  as.push_back(203.0);
  cs.push_back(16.988);
  errs.push_back(0.51);
  as.push_back(204.0);
  cs.push_back(15.681);
  errs.push_back(0.471);
  as.push_back(205.0);
  cs.push_back(12.697);
  errs.push_back(0.457);
  as.push_back(206.0);
  cs.push_back(13.517);
  errs.push_back(0.406);
  as.push_back(207.0);
  cs.push_back(17.525);
  errs.push_back(0.526);
  watchers.push_back(G4NuclWatcher(81, as, cs, errs, true, true));

  // Z = 82
  as.clear();
  cs.clear();
  errs.clear();
  as.push_back(187.0);
  cs.push_back(0.01);
  errs.push_back(0.006);
  as.push_back(188.0);
  cs.push_back(0.067);
  errs.push_back(0.029);
  as.push_back(189.0);
  cs.push_back(0.276);
  errs.push_back(0.094);
  as.push_back(190.0);
  cs.push_back(0.697);
  errs.push_back(0.077);
  as.push_back(191.0);
  cs.push_back(1.632);
  errs.push_back(0.175);
  as.push_back(192.0);
  cs.push_back(2.889);
  errs.push_back(0.092);
  as.push_back(193.0);
  cs.push_back(4.243);
  errs.push_back(0.132);
  as.push_back(194.0);
  cs.push_back(6.23);
  errs.push_back(0.38);
  as.push_back(195.0);
  cs.push_back(7.738);
  errs.push_back(0.233);
  as.push_back(196.0);
  cs.push_back(9.31);
  errs.push_back(0.28);
  as.push_back(197.0);
  cs.push_back(12.186);
  errs.push_back(0.733);
  as.push_back(198.0);
  cs.push_back(13.979);
  errs.push_back(0.42);
  as.push_back(199.0);
  cs.push_back(15.954);
  errs.push_back(0.479);
  as.push_back(200.0);
  cs.push_back(18.22);
  errs.push_back(1.094);
  as.push_back(201.0);
  cs.push_back(20.362);
  errs.push_back(0.611);
  as.push_back(202.0);
  cs.push_back(22.731);
  errs.push_back(0.682);
  as.push_back(203.0);
  cs.push_back(28.71);
  errs.push_back(1.723);
  as.push_back(204.0);
  cs.push_back(26.57);
  errs.push_back(0.797);
  as.push_back(205.0);
  cs.push_back(31.451);
  errs.push_back(0.944);
  as.push_back(206.0);
  cs.push_back(65.257);
  errs.push_back(19.577);
  as.push_back(207.0);
  cs.push_back(63.653);
  errs.push_back(9.573);
  watchers.push_back(G4NuclWatcher(82, as, cs, errs, true, true));

#else

  // watchers for Au197 + P, 800 MeV
  // Z = 80
  as.clear();
  cs.clear();
  errs.clear();
  as.push_back(196.0);
  cs.push_back(1.54);
  errs.push_back(0.2);
  as.push_back(195.0);
  cs.push_back(2.87);
  errs.push_back(0.37);
  as.push_back(194.0);
  cs.push_back(3.61);
  errs.push_back(0.47);
  as.push_back(193.0);
  cs.push_back(4.44);
  errs.push_back(0.38);
  as.push_back(192.0);
  cs.push_back(4.22);
  errs.push_back(0.47);
  as.push_back(191.0);
  cs.push_back(4.17);
  errs.push_back(0.45);
  as.push_back(190.0);
  cs.push_back(4.05);
  errs.push_back(0.43);
  as.push_back(189.0);
  cs.push_back(2.81);
  errs.push_back(0.25);
  as.push_back(188.0);
  cs.push_back(2.14);
  errs.push_back(0.24);
  as.push_back(187.0);
  cs.push_back(1.68);
  errs.push_back(0.15);
  as.push_back(186.0);
  cs.push_back(1.03);
  errs.push_back(0.1);
  as.push_back(185.0);
  cs.push_back(0.72);
  errs.push_back(0.09);
  as.push_back(184.0);
  cs.push_back(0.47);
  errs.push_back(0.05);
  as.push_back(183.0);
  cs.push_back(0.18);
  errs.push_back(0.05);
  as.push_back(182.0);
  cs.push_back(0.11);
  errs.push_back(0.02);
  as.push_back(181.0);
  cs.push_back(0.04);
  errs.push_back(0.01);
  as.push_back(179.0);
  cs.push_back(0.008);
  errs.push_back(0.01);
  as.push_back(178.0);
  cs.push_back(0.003);
  errs.push_back(0.001);
  watchers.push_back(G4NuclWatcher(80, as, cs, errs, true, true));

  // Z = 77
  as.clear();
  cs.clear();
  errs.clear();
  as.push_back(171.0);
  cs.push_back(0.07);
  errs.push_back(0.03);
  as.push_back(172.0);
  cs.push_back(0.29);
  errs.push_back(0.19);
  as.push_back(173.0);
  cs.push_back(0.82);
  errs.push_back(0.22);
  as.push_back(174.0);
  cs.push_back(1.54);
  errs.push_back(0.2);
  as.push_back(175.0);
  cs.push_back(3.16);
  errs.push_back(0.4);
  as.push_back(176.0);
  cs.push_back(6.19);
  errs.push_back(0.79);
  as.push_back(177.0);
  cs.push_back(9.58);
  errs.push_back(1.22);
  as.push_back(178.0);
  cs.push_back(13.35);
  errs.push_back(1.26);
  as.push_back(179.0);
  cs.push_back(17.35);
  errs.push_back(1.39);
  as.push_back(180.0);
  cs.push_back(18.93);
  errs.push_back(1.51);
  as.push_back(181.0);
  cs.push_back(20.13);
  errs.push_back(2.59);
  as.push_back(182.0);
  cs.push_back(19.63);
  errs.push_back(1.82);
  as.push_back(183.0);
  cs.push_back(19.43);
  errs.push_back(1.81);
  as.push_back(184.0);
  cs.push_back(18.09);
  errs.push_back(1.68);
  as.push_back(185.0);
  cs.push_back(15.71);
  errs.push_back(1.46);
  as.push_back(186.0);
  cs.push_back(13.51);
  errs.push_back(1.26);
  as.push_back(187.0);
  cs.push_back(11.52);
  errs.push_back(1.08);
  as.push_back(188.0);
  cs.push_back(8.97);
  errs.push_back(1.15);
  as.push_back(189.0);
  cs.push_back(8.05);
  errs.push_back(1.03);
  as.push_back(190.0);
  cs.push_back(6.02);
  errs.push_back(0.77);
  as.push_back(191.0);
  cs.push_back(5.04);
  errs.push_back(0.54);
  as.push_back(192.0);
  cs.push_back(4.18);
  errs.push_back(0.54);
  as.push_back(193.0);
  cs.push_back(3.54);
  errs.push_back(0.45);
  watchers.push_back(G4NuclWatcher(77, as, cs, errs, true, true));

  // Z = 73
  as.clear();
  cs.clear();
  errs.clear();
  as.push_back(162.0);
  cs.push_back(0.31);
  errs.push_back(0.04);
  as.push_back(163.0);
  cs.push_back(1.21);
  errs.push_back(0.11);
  as.push_back(164.0);
  cs.push_back(3.07);
  errs.push_back(0.29);
  as.push_back(165.0);
  cs.push_back(5.32);
  errs.push_back(0.5);
  as.push_back(166.0);
  cs.push_back(8.68);
  errs.push_back(0.81);
  as.push_back(167.0);
  cs.push_back(11.48);
  errs.push_back(1.46);
  as.push_back(168.0);
  cs.push_back(12.19);
  errs.push_back(1.43);
  as.push_back(169.0);
  cs.push_back(13.1);
  errs.push_back(1.4);
  as.push_back(170.0);
  cs.push_back(12.22);
  errs.push_back(1.48);
  as.push_back(171.0);
  cs.push_back(9.34);
  errs.push_back(1.15);
  as.push_back(172.0);
  cs.push_back(7.51);
  errs.push_back(0.97);
  as.push_back(173.0);
  cs.push_back(5.55);
  errs.push_back(0.71);
  as.push_back(174.0);
  cs.push_back(3.36);
  errs.push_back(0.43);
  as.push_back(175.0);
  cs.push_back(2.26);
  errs.push_back(0.29);
  as.push_back(176.0);
  cs.push_back(1.4);
  errs.push_back(0.14);
  as.push_back(177.0);
  cs.push_back(0.76);
  errs.push_back(0.08);
  as.push_back(178.0);
  cs.push_back(0.43);
  errs.push_back(0.04);
  as.push_back(179.0);
  cs.push_back(0.22);
  errs.push_back(0.03);
  as.push_back(180.0);
  cs.push_back(0.12);
  errs.push_back(0.03);
  as.push_back(181.0);
  cs.push_back(0.06);
  errs.push_back(0.02);
  as.push_back(182.0);
  cs.push_back(0.01);
  errs.push_back(0.008);
  watchers.push_back(G4NuclWatcher(73, as, cs, errs, true, true));

  // Z = 61
  as.clear();
  cs.clear();
  errs.clear();
  as.push_back(133.0);
  cs.push_back(0.01);
  errs.push_back(0.006);
  as.push_back(134.0);
  cs.push_back(0.04);
  errs.push_back(0.01);
  as.push_back(135.0);
  cs.push_back(0.1);
  errs.push_back(0.018);
  as.push_back(136.0);
  cs.push_back(0.16);
  errs.push_back(0.027);
  as.push_back(137.0);
  cs.push_back(0.21);
  errs.push_back(0.034);
  as.push_back(138.0);
  cs.push_back(0.22);
  errs.push_back(0.034);
  as.push_back(139.0);
  cs.push_back(0.22);
  errs.push_back(0.031);
  as.push_back(140.0);
  cs.push_back(0.16);
  errs.push_back(0.023);
  as.push_back(141.0);
  cs.push_back(0.11);
  errs.push_back(0.025);
  as.push_back(142.0);
  cs.push_back(0.08);
  errs.push_back(0.018);
  as.push_back(143.0);
  cs.push_back(0.04);
  errs.push_back(0.005);
  as.push_back(144.0);
  cs.push_back(0.02);
  errs.push_back(0.003);
  watchers.push_back(G4NuclWatcher(61, as, cs, errs, true, true));

  // Z = 79
  as.clear();
  cs.clear();
  errs.clear();
  as.push_back(178.0);
  cs.push_back(0.12);
  errs.push_back(0.02);
  as.push_back(177.0);
  cs.push_back(0.04);
  errs.push_back(0.005);
  as.push_back(176.0);
  cs.push_back(0.01);
  errs.push_back(0.002);
  as.push_back(196.0);
  cs.push_back(57.98);
  errs.push_back(5.46);
  as.push_back(195.0);
  cs.push_back(41.06);
  errs.push_back(3.8);
  as.push_back(194.0);
  cs.push_back(30.99);
  errs.push_back(2.87);
  as.push_back(193.0);
  cs.push_back(29.38);
  errs.push_back(2.72);
  as.push_back(192.0);
  cs.push_back(25.19);
  errs.push_back(2.41);
  as.push_back(191.0);
  cs.push_back(23.38);
  errs.push_back(2.25);
  as.push_back(190.0);
  cs.push_back(21.25);
  errs.push_back(1.83);
  as.push_back(189.0);
  cs.push_back(18.76);
  errs.push_back(1.55);
  as.push_back(188.0);
  cs.push_back(15.47);
  errs.push_back(1.36);
  as.push_back(187.0);
  cs.push_back(13.92);
  errs.push_back(1.22);
  as.push_back(186.0);
  cs.push_back(11.77);
  errs.push_back(1.02);
  as.push_back(185.0);
  cs.push_back(8.61);
  errs.push_back(1.09);
  as.push_back(184.0);
  cs.push_back(6.97);
  errs.push_back(0.67);
  as.push_back(183.0);
  cs.push_back(5.0);
  errs.push_back(0.61);
  as.push_back(182.);
  cs.push_back(3.42);
  errs.push_back(0.29);
  as.push_back(181.0);
  cs.push_back(1.8);
  errs.push_back(0.23);
  as.push_back(180.0);
  cs.push_back(0.91);
  errs.push_back(0.12);
  as.push_back(179.0);
  cs.push_back(0.36);
  errs.push_back(0.05);
  watchers.push_back(G4NuclWatcher(79, as, cs, errs, true, true));

  // Z = 78
  as.clear();
  cs.clear();
  errs.clear();
  as.push_back(178.0);
  cs.push_back(3.04);
  errs.push_back(0.39);
  as.push_back(177.0);
  cs.push_back(1.43);
  errs.push_back(0.18);
  as.push_back(176.0);
  cs.push_back(0.57);
  errs.push_back(0.07);
  as.push_back(175.0);
  cs.push_back(0.18);
  errs.push_back(0.02);
  as.push_back(196.0);
  cs.push_back(21.4);
  errs.push_back(9.68);
  as.push_back(195.0);
  cs.push_back(21.34);
  errs.push_back(5.86);
  as.push_back(194.0);
  cs.push_back(21.28);
  errs.push_back(2.54);
  as.push_back(193.0);
  cs.push_back(18.56);
  errs.push_back(2.32);
  as.push_back(192.0);
  cs.push_back(19.99);
  errs.push_back(1.87);
  as.push_back(191.0);
  cs.push_back(19.84);
  errs.push_back(1.85);
  as.push_back(190.0);
  cs.push_back(19.86);
  errs.push_back(1.85);
  as.push_back(189.0);
  cs.push_back(21.86);
  errs.push_back(2.04);
  as.push_back(188.0);
  cs.push_back(22.05);
  errs.push_back(2.06);
  as.push_back(187.0);
  cs.push_back(21.04);
  errs.push_back(1.96);
  as.push_back(186.0);
  cs.push_back(21.88);
  errs.push_back(2.8);
  as.push_back(185.0);
  cs.push_back(19.84);
  errs.push_back(2.3);
  as.push_back(184.0);
  cs.push_back(18.4);
  errs.push_back(2.36);
  as.push_back(183.0);
  cs.push_back(16.04);
  errs.push_back(2.06);
  as.push_back(182.0);
  cs.push_back(15.5);
  errs.push_back(1.99);
  as.push_back(181.0);
  cs.push_back(11.63);
  errs.push_back(1.49);
  as.push_back(180.0);
  cs.push_back(8.16);
  errs.push_back(1.05);
  as.push_back(179.0);
  cs.push_back(5.49);
  errs.push_back(0.7);
  watchers.push_back(G4NuclWatcher(78, as, cs, errs, true, true));

  // Z = 72
  as.clear();
  cs.clear();
  errs.clear();
  as.push_back(176.0);
  cs.push_back(0.13);
  errs.push_back(0.02);
  as.push_back(175.0);
  cs.push_back(0.31);
  errs.push_back(0.04);
  as.push_back(174.0);
  cs.push_back(0.56);
  errs.push_back(0.07);
  as.push_back(173.0);
  cs.push_back(0.96);
  errs.push_back(0.12);
  as.push_back(172.0);
  cs.push_back(1.82);
  errs.push_back(0.17);
  as.push_back(171.0);
  cs.push_back(3.05);
  errs.push_back(0.31);
  as.push_back(170.0);
  cs.push_back(4.6);
  errs.push_back(0.52);
  as.push_back(169.0);
  cs.push_back(6.05);
  errs.push_back(0.75);
  as.push_back(168.0);
  cs.push_back(8.49);
  errs.push_back(0.84);
  as.push_back(167.0);
  cs.push_back(9.72);
  errs.push_back(1.24);
  as.push_back(166.0);
  cs.push_back(10.46);
  errs.push_back(1.33);
  as.push_back(165.0);
  cs.push_back(9.98);
  errs.push_back(1.18);
  as.push_back(164.0);
  cs.push_back(8.48);
  errs.push_back(0.79);
  as.push_back(163.0);
  cs.push_back(5.93);
  errs.push_back(0.48);
  as.push_back(162.0);
  cs.push_back(3.83);
  errs.push_back(0.36);
  as.push_back(161.0);
  cs.push_back(1.67);
  errs.push_back(0.17);
  as.push_back(160.0);
  cs.push_back(0.57);
  errs.push_back(0.06);
  as.push_back(159.0);
  cs.push_back(0.14);
  errs.push_back(0.02);
  watchers.push_back(G4NuclWatcher(72, as, cs, errs, true, true));

  // Z = 66
  as.clear();
  cs.clear();
  errs.clear();
  as.push_back(157.0);
  cs.push_back(0.14);
  errs.push_back(0.02);
  as.push_back(156.0);
  cs.push_back(0.25);
  errs.push_back(0.05);
  as.push_back(155.0);
  cs.push_back(0.41);
  errs.push_back(0.05);
  as.push_back(154.0);
  cs.push_back(0.69);
  errs.push_back(0.06);
  as.push_back(153.0);
  cs.push_back(0.91);
  errs.push_back(0.09);
  as.push_back(152.0);
  cs.push_back(1.07);
  errs.push_back(0.11);
  as.push_back(151.0);
  cs.push_back(1.23);
  errs.push_back(0.15);
  as.push_back(150.0);
  cs.push_back(1.31);
  errs.push_back(0.14);
  as.push_back(149.0);
  cs.push_back(1.15);
  errs.push_back(0.11);
  as.push_back(148.0);
  cs.push_back(0.91);
  errs.push_back(0.09);
  as.push_back(147.0);
  cs.push_back(0.55);
  errs.push_back(0.1);
  watchers.push_back(G4NuclWatcher(66, as, cs, errs, true, true));

  // Z = 65
  as.clear();
  cs.clear();
  errs.clear();
  as.push_back(153.0);
  cs.push_back(0.21);
  errs.push_back(0.03);
  as.push_back(152.0);
  cs.push_back(0.33);
  errs.push_back(0.03);
  as.push_back(151.0);
  cs.push_back(0.49);
  errs.push_back(0.05);
  as.push_back(150.0);
  cs.push_back(0.62);
  errs.push_back(0.08);
  as.push_back(149.0);
  cs.push_back(0.77);
  errs.push_back(0.1);
  as.push_back(148.0);
  cs.push_back(0.88);
  errs.push_back(0.11);
  as.push_back(147.0);
  cs.push_back(0.93);
  errs.push_back(0.09);
  as.push_back(146.0);
  cs.push_back(0.8);
  errs.push_back(0.08);
  as.push_back(145.0);
  cs.push_back(0.54);
  errs.push_back(0.1);
  as.push_back(144.0);
  cs.push_back(0.28);
  errs.push_back(0.1);

  watchers.push_back(G4NuclWatcher(65, as, cs, errs, true, true));
#endif  

}












