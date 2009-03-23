/********************************************************************************
*                                                                               *
*                          G e n e r i c   A r r a y                            *
*                                                                               *
*********************************************************************************
* Copyright (C) 1997,2009 by Jeroen van der Zijp.   All Rights Reserved.        *
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
* $Id: FXArray.h,v 1.39 2009/01/06 13:07:21 fox Exp $                           *
********************************************************************************/
#ifndef FXARRAY_H
#define FXARRAY_H

#ifndef FXELEMENT_H
#include "FXElement.h"
#endif

namespace FX {


/// Array of some generic type
template<class EType>
class FXArray {
protected:
  EType  *ptr;   // Data array
  FXint   num;   // Number in array
public:

  /// Create as empty
  FXArray():ptr(NULL),num(0){
    }

  /// Create with given size n
  FXArray(FXint n):ptr(NULL),num(0){
    if(allocElms(ptr,n)){ constructElms(ptr,n); num=n; }
    }

  /// Create initialized from another array
  FXArray(const FXArray<EType>& src):ptr(NULL),num(0){
    if(allocElms(ptr,src.num)){ constructElms(ptr,src.num); copyElms(ptr,src.ptr,src.num); num=src.num; }
    }

  /// Create initialized with n copies of object
  FXArray(const EType& src,FXint n):ptr(NULL),num(0){
    if(allocElms(ptr,n)){ constructElms(ptr,n); fillElms(ptr,src,n); num=n; }
    }

  /// Create initialized with array of n objects
  FXArray(const EType* src,FXint n):ptr(NULL),num(0){
    if(allocElms(ptr,n)){ constructElms(ptr,n); copyElms(ptr,src,n); num=n; }
    }

  /// Return number of elements
  FXint no() const { return num; }

  /// Change number of elements to n
  FXbool no(FXint n){
    if(n!=num){
      if(0<num-n){
        destructElms(ptr+n,num-n);
        if(!resizeElms(ptr,n)) return false;
        }
      else{
        if(!resizeElms(ptr,n)) return false;
        constructElms(ptr+num,n-num);
        }
      num=n;
      }
    return true;
    }

  /// Assign from another list
  FXArray<EType>& operator=(const FXArray<EType>& src){
    if(ptr!=src.ptr){ no(src.num); copyElms(ptr,src.ptr,src.num); }
    return *this;
    }

  /// Index into array
  EType& operator[](FXint i){ return ptr[i]; }
  const EType& operator[](FXint i) const { return ptr[i]; }

  /// Index into list
  EType& at(FXint i){ return ptr[i]; }
  const EType& at(FXint i) const { return ptr[i]; }

  /// First element in list
  EType& head(){ return ptr[0]; }
  const EType& head() const { return ptr[0]; }

  /// Last element in list
  EType& tail(){ return ptr[num-1]; }
  const EType& tail() const { return ptr[num-1]; }

  /// Return pointer to list
  EType* data() const { return ptr; }

  /// Adopt array from source
  FXArray<EType>& adopt(FXArray<EType>& src){
    if(no(0)){ ptr=src.ptr; src.ptr=NULL; num=src.num; src.num=0; }
    return *this;
    }

  /// Assign object p to list
  FXArray<EType>& assign(const EType& src){
    if(no(1)){ ptr[0]=src; }
    return *this;
    }

  /// Assign n copies of object to list
  FXArray<EType>& assign(const EType& src,FXint n){
    if(no(n)){ fillElms(ptr,src,n); }
    return *this;
    }

  /// Assign n objects to list
  FXArray<EType>& assign(const EType* src,FXint n){
    if(no(n)){ copyElms(ptr,src,n); }
    return *this;
    }

  /// Assign n objects to list
  FXArray<EType>& assign(const FXArray<EType>& src){
    return assign(src.ptr,src.num);
    }

  /// Insert an object
  FXArray<EType>& insert(FXint pos,const EType& src){
    if(no(num+1)){ moveElms(ptr+pos+1,ptr+pos,num-pos-1); ptr[pos]=src; }
    return *this;
    }

  /// Insert n copies of object at specified position
  FXArray<EType>& insert(FXint pos,const EType& src,FXint n){
    if(no(num+n)){ moveElms(ptr+pos+n,ptr+pos,num-pos-n); fillElms(ptr+pos,src,n); }
    return *this;
    }

  /// Insert n objects at specified position
  FXArray<EType>& insert(FXint pos,const EType* src,FXint n){
    if(no(num+n)){ moveElms(ptr+pos+n,ptr+pos,num-pos-n); copyElms(ptr+pos,src,n); }
    return *this;
    }

  /// Insert n objects at specified position
  FXArray<EType>& insert(FXint pos,const FXArray<EType>& src){
    return insert(pos,src.ptr,src.num);
    }

  /// Prepend object
  FXArray<EType>& prepend(const EType& src){
    if(no(num+1)){ moveElms(ptr+1,ptr,num-1); ptr[0]=src; }
    return *this;
    }

  /// Prepend n copies of object
  FXArray<EType>& prepend(const EType& src,FXint n){
    if(no(num+n)){ moveElms(ptr+n,ptr,num-n); fillElms(ptr,src,n); }
    return *this;
    }

  /// Prepend n objects
  FXArray<EType>& prepend(const EType* src,FXint n){
    if(no(num+n)){ moveElms(ptr+n,ptr,num-n); copyElms(ptr,src,n); }
    return *this;
    }

  /// Prepend n objects
  FXArray<EType>& prepend(const FXArray<EType>& src){
    return prepend(src.ptr,src.num);
    }

  /// Append object
  FXArray<EType>& append(const EType& src){
    if(no(num+1)){ ptr[num-1]=src; }
    return *this;
    }

  /// Append n copies of object
  FXArray<EType>& append(const EType& src,FXint n){
    if(no(num+n)){ fillElms(ptr+num-n,src,n); }
    return *this;
    }

  /// Append n objects
  FXArray<EType>& append(const EType* src,FXint n){
    if(no(num+n)){ copyElms(ptr+num-n,src,n); }
    return *this;
    }

  /// Append n objects
  FXArray<EType>& append(const FXArray<EType>& src){
    return append(src.ptr,src.num);
    }

  /// Replace an object
  FXArray<EType>& replace(FXint pos,const EType& src){
    ptr[pos]=src;
    return *this;
    }

  /// Replace the m objects at pos with n copies of src
  FXArray<EType>& replace(FXint pos,FXint m,const EType& src,FXint n){
    if(m<n){
      if(!no(num-m+n)) return *this;
      moveElms(ptr+pos+n,ptr+pos+m,num-pos-n);
      }
    else if(m>n){
      moveElms(ptr+pos+n,ptr+pos+m,num-pos-m);
      if(!no(num-m+n)) return *this;
      }
    fillElms(ptr+pos,src,n);
    return *this;
    }

  /// Replace m objects at pos by n objects from src
  FXArray<EType>& replace(FXint pos,FXint m,const EType* src,FXint n){
    if(m<n){
      if(!no(num-m+n)) return *this;
      moveElms(ptr+pos+n,ptr+pos+m,num-pos-n);
      }
    else if(m>n){
      moveElms(ptr+pos+n,ptr+pos+m,num-pos-m);
      if(!no(num-m+n)) return *this;
      }
    copyElms(ptr+pos,src,n);
    return *this;
    }

  /// Replace m objects at pos by objects from src
  FXArray<EType>& replace(FXint pos,FXint m,const FXArray<EType>& src){
    return replace(pos,m,src.ptr,src.num);
    }

  /// Remove object at pos
  FXArray<EType>& erase(FXint pos){
    moveElms(ptr+pos,ptr+pos+1,num-pos-1); no(num-1);
    return *this;
    }

  /// Remove n objects starting at pos
  FXArray<EType>& erase(FXint pos,FXint n){
    moveElms(ptr+pos,ptr+pos+n,num-n-pos); no(num-n);
    return *this;
    }

  /// Push object to end
  FXArray<EType>& push(const EType& src){
    if(no(num+1)){ ptr[num-1]=src; }
    return *this;
    }

  /// Pop object from end
  FXArray<EType>& pop(){
    no(num-1);
    return *this;
    }

  /// Remove all objects
  FXArray<EType>& clear(){
    destructElms(ptr,num); freeElms(ptr); num=0;
    return *this;
    }

  /// Delete data
  ~FXArray(){
    destructElms(ptr,num); freeElms(ptr);
    }
  };

}

#endif
