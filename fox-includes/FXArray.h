/********************************************************************************
*                                                                               *
*                          G e n e r i c   A r r a y                            *
*                                                                               *
*********************************************************************************
* Copyright (C) 1997,2005 by Jeroen van der Zijp.   All Rights Reserved.        *
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
* $Id: FXArray.h 2335 2006-01-28 02:33:03Z lyle $                           *
********************************************************************************/
#ifndef FXARRAY_H
#define FXARRAY_H

#ifndef FXELEMENT_H
#include "FXElement.h"
#endif

namespace FX {


/// Array of some generic type
template<class TYPE>
class FXArray {
protected:
  TYPE  *ptr;   // Data array
  FXint  num;   // Number in array
public:

  /// Create as empty
  FXArray():ptr(NULL),num(0){
    }

  /// Create with given size n
  FXArray(FXint n):ptr(NULL),num(0){
    if(allocElms(ptr,n)){ constructElms(ptr,n); num=n; }
    }

  /// Create initialized from another array
  FXArray(const FXArray<TYPE>& src):ptr(NULL),num(0){
    if(allocElms(ptr,src.num)){ constructElms(ptr,src.num); copyElms(ptr,src.ptr,src.num); num=src.num; }
    }

  /// Create initialized with n copies of object
  FXArray(const TYPE& src,FXint n):ptr(NULL),num(0){
    if(allocElms(ptr,n)){ constructElms(ptr,n); fillElms(ptr,src,n); num=n; }
    }

  /// Create initialized with array of n objects
  FXArray(const TYPE* src,FXint n):ptr(NULL),num(0){
    if(allocElms(ptr,n)){ constructElms(ptr,n); copyElms(ptr,src,n); num=n; }
    }

  /// Return number of elements
  FXint no() const { return num; }

  /// Change number of elements to n
  bool no(FXint n){
    if(n!=num){
      if(n<num){
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
  FXArray<TYPE>& operator=(const FXArray<TYPE>& src){
    if(ptr!=src.ptr){ no(src.num); copyElms(ptr,src.ptr,src.num); }
    return *this;
    }

  /// Index into array
  TYPE& operator[](FXint i){ return ptr[i]; }
  const TYPE& operator[](FXint i) const { return ptr[i]; }

  /// Index into list
  TYPE& at(FXint i){ return ptr[i]; }
  const TYPE& at(FXint i) const { return ptr[i]; }

  /// Return pointer to list
  TYPE* data() const { return ptr; }

  /// Adopt array from source
  FXArray<TYPE>& adopt(FXArray<TYPE>& src){
    no(0);
    ptr=src.ptr; src.ptr=NULL;
    num=src.num; src.num=0;
    return *this;
    }

  /// Assign object p to list
  FXArray<TYPE>& assign(const TYPE& src){
    if(no(1)){ ptr[0]=src; }
    return *this;
    }

  /// Assign n copies of object to list
  FXArray<TYPE>& assign(const TYPE& src,FXint n){
    if(no(n)){ fillElms(ptr,src,n); }
    return *this;
    }

  /// Assign n objects to list
  FXArray<TYPE>& assign(const TYPE* src,FXint n){
    if(no(n)){ copyElms(ptr,src,n); }
    return *this;
    }

  /// Assign n objects to list
  FXArray<TYPE>& assign(const FXArray<TYPE>& src){
    if(no(src.num)){ copyElms(ptr,src.ptr,src.num); }
    return *this;
    }

  /// Insert an object
  FXArray<TYPE>& insert(FXint pos,const TYPE& src){
    if(no(num+1)){ moveElms(ptr+pos+1,ptr+pos,num-pos-1); ptr[pos]=src; }
    return *this;
    }

  /// Insert n copies of object at specified position
  FXArray<TYPE>& insert(FXint pos,const TYPE& src,FXint n){
    if(no(num+n)){ moveElms(ptr+pos+n,ptr+pos,num-pos-n); fillElms(ptr+pos,src,n); }
    return *this;
    }

  /// Insert n objects at specified position
  FXArray<TYPE>& insert(FXint pos,const TYPE* src,FXint n){
    if(no(num+n)){ moveElms(ptr+pos+n,ptr+pos,num-pos-n); copyElms(ptr+pos,src,n); }
    return *this;
    }

  /// Insert n objects at specified position
  FXArray<TYPE>& insert(FXint pos,const FXArray<TYPE>& src){
    if(no(num+src.num)){ moveElms(ptr+pos+src.num,ptr+pos,num-pos-src.num); copyElms(ptr+pos,src.ptr,src.num); }
    return *this;
    }

  /// Prepend object
  FXArray<TYPE>& prepend(const TYPE& src){
    if(no(num+1)){ moveElms(ptr+1,ptr,num-1); ptr[0]=src; }
    return *this;
    }

  /// Prepend n copies of object
  FXArray<TYPE>& prepend(const TYPE& src,FXint n){
    if(no(num+n)){ moveElms(ptr+n,ptr,num-n); fillElms(ptr,src,n); }
    return *this;
    }

  /// Prepend n objects
  FXArray<TYPE>& prepend(const TYPE* src,FXint n){
    if(no(num+n)){ moveElms(ptr+n,ptr,num-n); copyElms(ptr,src,n); }
    return *this;
    }

  /// Prepend n objects
  FXArray<TYPE>& prepend(const FXArray<TYPE>& src){
    if(no(num+src.num)){ moveElms(ptr+src.num,ptr,num-src.num); copyElms(ptr,src.ptr,src.num); }
    return *this;
    }

  /// Append object
  FXArray<TYPE>& append(const TYPE& src){
    if(no(num+1)){ ptr[num-1]=src; }
    return *this;
    }

  /// Append n copies of object
  FXArray<TYPE>& append(const TYPE& src,FXint n){
    if(no(num+n)){ fillElms(ptr+num-n,src,n); }
    return *this;
    }

  /// Append n objects
  FXArray<TYPE>& append(const TYPE* src,FXint n){
    if(no(num+n)){ copyElms(ptr+num-n,src,n); }
    return *this;
    }

  /// Append n objects
  FXArray<TYPE>& append(const FXArray<TYPE>& src){
    if(no(num+src.num)){ copyElms(ptr+num-src.num,src.ptr,src.num); }
    return *this;
    }

  /// Remove object at pos
  FXArray<TYPE>& erase(FXint pos){
    moveElms(ptr+pos,ptr+pos+1,num-pos-1); no(num-1);
    return *this;
    }

  /// Remove n objects starting at pos
  FXArray<TYPE>& erase(FXint pos,FXint n){
    moveElms(ptr+pos,ptr+pos+n,num-n-pos); no(num-n);
    return *this;
    }

  /// Remove all objects
  FXArray<TYPE>& clear(){
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
