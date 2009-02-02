/********************************************************************************
*                                                                               *
*                       M e s s a g e   T r a n s l a t o r                     *
*                                                                               *
*********************************************************************************
* Copyright (C) 2005 by Jeroen van der Zijp.   All Rights Reserved.             *
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
* $Id: FXTranslator.h 2290 2005-12-05 03:28:56Z lyle $                       *
********************************************************************************/
#ifndef FXTRANSLATOR_H
#define FXTRANSLATOR_H

#ifndef FXOBJECT_H
#include "FXObject.h"
#endif


////////////////////////////  UNDER DEVELOPMENT  ////////////////////////////////


namespace FX {

class FXApp;
class FXTextCodec;


/**
* The translator class translates a message to another language.
*/
class FXAPI FXTranslator : public FXObject {
  FXDECLARE(FXTranslator)
private:
  FXApp       *app;     // Back link to application object
  FXTextCodec *codec;   // Text codec used for source text
private:
  FXTranslator(const FXTranslator&);
  FXTranslator &operator=(const FXTranslator&);
protected:
  FXTranslator():app((FXApp*)-1L){}
public:

  /// Construct translator
  FXTranslator(FXApp* a);

  /// Get application
  FXApp* getApp() const { return app; }

  /// Translate a string
  virtual const FXchar* tr(const FXchar* context,const FXchar* message,const FXchar* hint=NULL) const;

  /// Change text codec used to decode the messages embedded in the source
  void setTextCodec(FXTextCodec *cdc){ codec=cdc; }

  /// Return text codec
  FXTextCodec *getTextCodec() const { return codec; }

  /// Save translator to a stream
  virtual void save(FXStream& store) const;

  /// Load translator from a stream
  virtual void load(FXStream& store);

  /// Destructor
  virtual ~FXTranslator();
  };


}

#endif
