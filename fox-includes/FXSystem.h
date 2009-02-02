/********************************************************************************
*                                                                               *
*         M i s c e l l a n e o u s   S y s t e m   F u n c t i o n s           *
*                                                                               *
*********************************************************************************
* Copyright (C) 2005,2007 by Jeroen van der Zijp.   All Rights Reserved.        *
*********************************************************************************
* This library is free software; you can redistribute it and/or modify          *
* it under the terms of the GNU Lesser General Public License as published by   *
* the Free Software Foundation; either version 3 of the License, or             *
* (at your option) any later version.                                           *
*                                                                               *
* This library is distributed in the hope that it will be useful,               *
* but WITHOUT ANY WARRANTY; without even the implied warranty of                *
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                 *
* GNU Lesser General Public License for more details.                           *
*                                                                               *
* You should have received a copy of the GNU Lesser General Public License      *
* along with this program.  If not, see <http://www.gnu.org/licenses/>          *
*********************************************************************************
* $Id: FXSystem.h 2765 2007-11-19 18:11:18Z lyle $                          *
********************************************************************************/
#ifndef FXSYSTEM_H
#define FXSYSTEM_H



namespace FX {



namespace FXSystem {


/// Convert time in nanoseconds since 1/1/1970 to local date string
FXString FXAPI localTime(FXTime value);

/// Convert time in nanoseconds since 1/1/1970 to universal date string
FXString FXAPI universalTime(FXTime value);

/**
* Convert time in nanoseconds since 1/1/1970 to local date string as per strftime.
* Format characters supported by most systems are:
*
*  %a %A %b %B %c %d %H %I %j %m %M %p %S %U %w %W %x %X %y %Y %Z %%
*
* Some systems support additional conversions.
*/
FXString FXAPI localTime(const FXchar *format,FXTime value);

/**
* Convert time in nanoseconds since 1/1/1970 to universal date string as per strftime.
*/
FXString FXAPI universalTime(const FXchar *format,FXTime value);


/// Get effective user id
FXuint FXAPI user();

/// Get effective group id
FXuint FXAPI group();

/// Return owner name from uid if available
FXString FXAPI userName(FXuint uid);

/// Return group name from gid if available
FXString FXAPI groupName(FXuint gid);

/// Get current effective user name
FXString FXAPI currentUserName();

/// Get current effective group name
FXString FXAPI currentGroupName();


/// Get permissions string
FXString FXAPI modeString(FXuint mode);



/// Return value of environment variable name
FXString FXAPI getEnvironment(const FXString& name);

/// Change value of environment variable name, return true if success
FXbool FXAPI setEnvironment(const FXString& name,const FXString& value);



/// Get the current working directory
FXString FXAPI getCurrentDirectory();

/// Set the current working directory
FXbool FXAPI setCurrentDirectory(const FXString& path);

/// Return the current drive (for Win32 systems)
FXString FXAPI getCurrentDrive();

/// Set the current drive (for Win32 systems)
FXbool FXAPI setCurrentDrive(const FXString& prefix);



/// Get executable path
FXString FXAPI getExecPath();

/// Return the home directory for the current user
FXString FXAPI getHomeDirectory();

/// Return the home directory for a given user
FXString FXAPI getUserDirectory(const FXString& user);

/// Return temporary directory
FXString FXAPI getTempDirectory();


/// Get process id
FXint FXAPI getProcessId();


/// Return host name
extern FXAPI FXString getHostName();


/// Determine if UTF8 locale in effect
FXbool FXAPI localeIsUTF8();


/**
* Get DLL name for given base name; for example "png"
* becomes "libpng.so" on Linux, and "png.dll" on Windows.
*/
FXString FXAPI dllName(const FXString& name);

}

}

#endif
