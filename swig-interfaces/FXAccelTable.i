/***********************************************************************
 * FXRuby -- the Ruby language bindings for the FOX GUI toolkit.
 * Copyright (c) 2001-2009 by Lyle Johnson. All Rights Reserved.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * For further information please contact the author by e-mail
 * at "lyle@lylejohnson.name".
 ***********************************************************************/

/**
 * The accelerator table sends a message to a specific
 * target object when the indicated key and modifier combination
 * is pressed.
 */

class FXAccelTable : public FXObject {
public:
  long onKeyPress(FXObject*,FXSelector,void* PTR_EVENT);
  long onKeyRelease(FXObject*,FXSelector,void* PTR_EVENT);
public:
  %extend {
    /// Construct empty accelerator table
    FXAccelTable(){
      return new FXRbAccelTable();
      }
    }

  /// Add an accelerator into the table
  void addAccel(FXHotKey hotkey,FXObject* target=NULL,FXSelector seldn=0,FXSelector selup=0);

  /// Remove an accelerator from the table
  void removeAccel(FXHotKey hotkey);

  /// Return true if accelerator specified
  bool hasAccel(FXHotKey hotkey) const;

  /// Return target object of the given accelerator
  FXObject* targetOfAccel(FXHotKey hotkey) const;

  /// Destructor
  virtual ~FXAccelTable();
  };

DECLARE_FXOBJECT_VIRTUALS(FXAccelTable)

/**
* Parse accelerator from string, yielding modifier and
* key code.  For example, parseAccel("Ctl+Shift+X")
* yields MKUINT(KEY_X,CONTROLMASK|SHIFTMASK).
*/
FXHotKey parseAccel(const FXString& string);

/**
* Unparse hot key comprising modifier and key code back
* into a string suitable for parsing with fxparseHotKey.
*/
FXString unparseAccel(FXHotKey key);

/**
* Parse hot key from string, yielding modifier and
* key code.  For example, parseHotKey(""Salt && &Pepper!"")
* yields MKUINT(KEY_p,ALTMASK).
*/
FXHotKey parseHotKey(const FXString& string);

/**
* Obtain hot key offset in string, or -1 if not found.
* For example, findHotKey("Salt && &Pepper!") yields 7.
* Note that this is the byte-offset, not the character
* index!
*/
FXint findHotKey(const FXString& string);

/**
* Strip hot key combination from the string.
* For example, stripHotKey("Salt && &Pepper") should
* yield "Salt & Pepper".
*/
FXString stripHotKey(const FXString& string);

