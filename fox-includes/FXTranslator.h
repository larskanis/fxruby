/********************************************************************************
*                                                                               *
*                       M e s s a g e   T r a n s l a t o r                     *
*                                                                               *
*********************************************************************************
* Copyright (C) 2005,2008 by Jeroen van der Zijp.   All Rights Reserved.        *
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
* $Id: FXTranslator.h 2867 2008-05-29 21:50:28Z lyle $                      *
********************************************************************************/
#ifndef FXTRANSLATOR_H
#define FXTRANSLATOR_H

#ifndef FXOBJECT_H
#include "FXObject.h"
#endif


////////////////////////////  UNDER DEVELOPMENT  ////////////////////////////////


namespace FX {


/**
* The translator class translates a message to another language.
*/
class FXAPI FXTranslator : public FXObject {
  FXDECLARE(FXTranslator)
private:
  FXTranslator(const FXTranslator&);
  FXTranslator &operator=(const FXTranslator&);
public:

  /// Construct translator
  FXTranslator();

  /// Translate a string
  virtual const FXchar* tr(const FXchar* context,const FXchar* message,const FXchar* hint=NULL,FXint count=-1) const;

  /// Save translator to a stream
  virtual void save(FXStream& store) const;

  /// Load translator from a stream
  virtual void load(FXStream& store);

  /// Destructor
  virtual ~FXTranslator();
  };


}

#endif
