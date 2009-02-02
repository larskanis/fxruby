/***********************************************************************
 * FXRuby -- the Ruby language bindings for the FOX GUI toolkit.
 * Copyright (c) 2001-2003 by J. Lyle Johnson. All Rights Reserved.
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
 * at "lyle@rubyforge.org".
 ***********************************************************************/

/***********************************************************************
 * $Id: FXTranslator.i 2873 2008-05-30 21:38:58Z lyle $
 ***********************************************************************/

/**
* The translator class translates a message to another language.
*/
class FXTranslator : public FXObject {
public:

  %extend {
    /// Construct translator
    FXTranslator() { return new FXRbTranslator(); }
  }

  /// Destructor
  virtual ~FXTranslator();
  };

DECLARE_FXOBJECT_VIRTUALS(FXTranslator)
DECLARE_FXTRANSLATOR_VIRTUALS(FXTranslator)

