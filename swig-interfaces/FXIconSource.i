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
* An icon source is a class that loads an icon of any type.
* It exists purely for convenience, to make loading icons
* simpler by concentrating the knowledge of the supported
* icon formats in a single place.
* Needless to say, this class is subclassable, allowing users
* to add additional icon types and make them available to
* all widgets which deal with icons.
* Note, the icons are loaded, but NOT created (realized) yet;
* this allows users to manipulate the pixel data prior to
* realizing the icons.
*/
class FXIconSource : public FXObject {
public:

  %extend {
    /// Construct an icon source
    FXIconSource(FXApp* a){
      return new FXRbIconSource(a);
      }
  }

  /// Destroy
  virtual ~FXIconSource();
  };

DECLARE_FXOBJECT_VIRTUALS(FXIconSource)
DECLARE_FXICONSOURCE_VIRTUALS(FXIconSource)

