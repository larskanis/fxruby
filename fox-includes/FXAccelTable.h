/********************************************************************************
*                                                                               *
*                   A c c e l e r a t o r   T a b l e   C l a s s               *
*                                                                               *
*********************************************************************************
* Copyright (C) 1998,2005 by Jeroen van der Zijp.   All Rights Reserved.        *
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
* $Id: FXAccelTable.h 2335 2006-01-28 02:33:03Z lyle $                      *
********************************************************************************/
#ifndef FXACCELTABLE_H
#define FXACCELTABLE_H

#ifndef FXOBJECT_H
#include "FXObject.h"
#endif

namespace FX {


/**
* The accelerator table sends a message to a specific
* target object when the indicated key and modifier combination
* is pressed.
*/
class FXAPI FXAccelTable : public FXObject {
  FXDECLARE(FXAccelTable)
protected:
  struct FXAccelKey {
    FXObject    *target;    // Target object of message
    FXSelector   messagedn; // Message being sent
    FXSelector   messageup; // Message being sent
    FXHotKey     code;      // Keysym and modifier mask to match
    };
private:
  FXAccelKey *key;          // Accelerator table
  FXuint      max;          // Largest table index
  FXuint      num;          // Number of entries
private:
  void resize(FXuint m);
private:
  FXAccelTable(const FXAccelTable&);
  FXAccelTable &operator=(const FXAccelTable&);
public:
  long onKeyPress(FXObject*,FXSelector,void*);
  long onKeyRelease(FXObject*,FXSelector,void*);
public:

  /// Construct empty accelerator table
  FXAccelTable();

  /// Add an accelerator into the table
  void addAccel(FXHotKey hotkey,FXObject* target=NULL,FXSelector seldn=0,FXSelector selup=0);

  /// Remove an accelerator from the table
  void removeAccel(FXHotKey hotkey);

  /// Return true if accelerator specified
  bool hasAccel(FXHotKey hotkey) const;

  /// Return target object of the given accelerator
  FXObject* targetOfAccel(FXHotKey hotkey) const;

  /**
  * Parse accelerator from string, yielding modifier and
  * key code.  For example, parseAccel("Ctl+Shift+X")
  * yields MKUINT(KEY_X,CONTROLMASK|SHIFTMASK).
  */
  friend FXAPI FXHotKey parseAccel(const FXString& string);

  /**
  * Unparse hot key comprising modifier and key code back
  * into a string suitable for parsing with fxparseHotKey.
  */
  friend FXAPI FXString unparseAccel(FXHotKey key);

  /**
  * Parse hot key from string, yielding modifier and
  * key code.  For example, parseHotKey(""Salt && &Pepper!"")
  * yields MKUINT(KEY_p,ALTMASK).
  */
  friend FXAPI FXHotKey parseHotKey(const FXString& string);

  /**
  * Obtain hot key offset in string, or -1 if not found.
  * For example, findHotKey("Salt && &Pepper!") yields 7.
  * Note that this is the byte-offset, not the character
  * index!
  */
  friend FXAPI FXint findHotKey(const FXString& string);

  /**
  * Strip hot key combination from the string.
  * For example, stripHotKey("Salt && &Pepper") should
  * yield "Salt & Pepper".
  */
  friend FXAPI FXString stripHotKey(const FXString& string);

  /// Save table to a stream
  virtual void save(FXStream& store) const;

  /// Load table from a stream
  virtual void load(FXStream& store);

  /// Destructor
  virtual ~FXAccelTable();
  };


extern FXAPI FXHotKey parseAccel(const FXString& string);
extern FXAPI FXString unparseAccel(FXHotKey key);
extern FXAPI FXHotKey parseHotKey(const FXString& string);
extern FXAPI FXint findHotKey(const FXString& string);
extern FXAPI FXString stripHotKey(const FXString& string);

}

#endif
