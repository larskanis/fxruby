/********************************************************************************
*                                                                               *
*                    A u t o m a t i c   P o i n t e r                          *
*                                                                               *
*********************************************************************************
* Copyright (C) 2007,2009 by Jeroen van der Zijp.   All Rights Reserved.        *
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
* $Id: FXAutoPtr.h,v 1.15 2009/01/06 13:07:21 fox Exp $                         *
********************************************************************************/
#ifndef FXAUTOPTR_H
#define FXAUTOPTR_H

namespace FX {


/// Automatic pointer
template<class EType> class FXAutoPtr {
private:
  EType* ptr;
public:

  /// Construct with optional pointer
  FXAutoPtr(EType* p=NULL):ptr(p){ }

  /// Copy constructor from an automatic pointer with compatible type
  template<class T> FXAutoPtr(FXAutoPtr<T>& orig):ptr(orig.release()){ }

  /// Assign from pointer
  FXAutoPtr& operator=(EType *p){ ptr=p; return *this; }

  /// Assign from an automatic pointer with compatible type
  template<class T> FXAutoPtr& operator=(FXAutoPtr<T>& orig){ reset(orig.release()); return *this; }

  /// Conversion operators
  operator EType*() const { return ptr; }

  /// Dereference operator
  EType& operator*() const { return *ptr; }

  /// Follow pointer operator
  EType* operator->() const { return ptr; }

  /// Release hold on the pointer
  EType* release(){ EType* tmp=ptr; ptr=NULL; return tmp; }

  /// Delete old object, replace by new, if any
  void reset(EType* p=NULL){ if(p!=ptr){ delete ptr; ptr=p; } }

  /// Destruction deletes pointer
  ~FXAutoPtr(){ delete ptr; }
  };

}

#endif

