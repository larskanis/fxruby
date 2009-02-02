/********************************************************************************
*                                                                               *
*                           R e g i s t r y   C l a s s                         *
*                                                                               *
*********************************************************************************
* Copyright (C) 1998,2006 by Jeroen van der Zijp.   All Rights Reserved.        *
*********************************************************************************
* This library is free software; you can redistribute it and/or                 *
* modify it under the terms of the GNU Lesser General Public                    *
* License as published by the Free Software Foundation; either                  *
* version 2.1 of the License, or (at your option) any later version.            *
*                                                                               *
* This library is distributed in the hope that it will be useful,               *
* but WITHOUT ANY WARRANTY; without even the implied warranty of                *
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU             *
* Lesser General Public License for more details.                               *
*                                                                               *
* You should have received a copy of the GNU Lesser General Public              *
* License along with this library; if not, write to the Free Software           *
* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA.    *
*********************************************************************************
* $Id: FXRegistry.h 2344 2006-02-12 21:19:36Z lyle $                        *
********************************************************************************/
#ifndef FXREGISTRY_H
#define FXREGISTRY_H

#ifndef FXSETTINGS_H
#include "FXSettings.h"
#endif

namespace FX {


/**
* The registry maintains a database of persistent settings for an application.
* The settings database is organized in two groups of three layers each.  The
* system-wide settings group contains settings information pertaining to all
* users on a system.  The per-user settings group contains settings affecting
* that user only.
* Each settings group contains a desktop layer, which comprises the settings
* which affect all FOX programs, a vendor layer which holds settings that
* affect all applications from that vendor (e.g. a application-suite), and
* an application layer which holds settings only for a single application.
* The vendor-key and application-key determine which files these layers come
* from, while the "Desktop" key is used for all FOX applications.
* Settings in the system-wide group are overwritten by the per-user group,
* and settings from the "Desktop" layer are overwritten by the vendor-layer;
* vendor-layer settings are overwritten by the application-layer settings.
* Only the per-user, per-application settings ever gets written; the layers
* in the system-group only get written during installation and configuration
* of the application.
* The registry is read when FXApp::init() is called, and written back to the
* system when FXApp::exit() is called.
*/
class FXAPI FXRegistry : public FXSettings {
  FXDECLARE(FXRegistry)
protected:
  FXString applicationkey;  // Application key
  FXString vendorkey;       // Vendor key
  bool     ascii;           // ASCII file-based registry
protected:
  bool readFromDir(const FXString& dirname,bool mark);
#ifdef WIN32
  bool readFromRegistry(void* hRootKey,bool mark);
  bool writeToRegistry(void* hRootKey);
  bool readFromRegistryGroup(void* org,const char* groupname,bool mark=false);
  bool writeToRegistryGroup(void* org,const char* groupname);
#endif
private:
  FXRegistry(const FXRegistry&);
  FXRegistry &operator=(const FXRegistry&);
public:

  /**
  * Construct registry object; akey and vkey must be string constants.
  * Regular applications SHOULD set a vendor key!
  */
  FXRegistry(const FXString& akey=FXString::null,const FXString& vkey=FXString::null);

  /// Read registry
  bool read();

  /// Write registry
  bool write();

  /// Return application key
  const FXString& getAppKey() const { return applicationkey; }

  /// Return vendor key
  const FXString& getVendorKey() const { return vendorkey; }

  /**
  * Set ASCII mode; under MS-Windows, this will switch the system to a
  * file-based registry system, instead of using the System Registry API.
  */
  void setAsciiMode(bool asciiMode){ ascii=asciiMode; }

  /// Get ASCII mode
  bool getAsciiMode() const { return ascii; }
  };

}

#endif
