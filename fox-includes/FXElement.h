/********************************************************************************
*                                                                               *
*                           Generic Element Handling                            *
*                                                                               *
*********************************************************************************
* Copyright (C) 1997,2008 by Jeroen van der Zijp.   All Rights Reserved.        *
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
* $Id: FXElement.h 2867 2008-05-29 21:50:28Z lyle $                         *
********************************************************************************/
#ifndef FXELEMENT_H
#define FXELEMENT_H

namespace FX {

/****************************  D e f i n i t i o n  ****************************/

// Generic implementations for generic objects


/// Construct some elements at a location
template<class EType>
inline void constructElms(EType* ptr,unsigned long n){
  while(n--){ ::new ((void*)ptr) EType; ptr++; }
  }


/// Destruct some elements at a location
template<class EType>
inline void destructElms(EType* ptr,unsigned long n){
  while(n--){ ptr->~EType(); ptr++; }
  }


/// Copy some elements from one place to another
template<class EType>
inline void copyElms(EType* dst,const EType* src,unsigned long n){
  while(n--){ *dst++ = *src++; }
  }


/// Move some elements from overlapping place to another
template<class EType>
inline void moveElms(EType* dst,const EType* src,unsigned long n){
  if(src>dst){
    while(n--){ *dst++ = *src++; }
    }
  else if(dst>src){
    dst+=n;
    src+=n;
    while(n--){ *--dst = *--src; }
    }
  }


/// Fill array of elements with given element
template<class EType>
inline void fillElms(EType* dst,const EType& src,unsigned long n){
  while(n--){ *dst++ = src; }
  }


/// Zero out array of elements
template<class EType>
inline void clearElms(EType* dst,unsigned long n){
  memset(dst,0,sizeof(EType)*n);
  }


/// Allocate array of elements, uninitialized
template<class EType>
inline FXbool allocElms(EType*& ptr,unsigned long n){
  return fxmalloc((void**)&ptr,sizeof(EType)*n);
  }


/// Allocate array of elements, initialized with zero
template<class EType>
inline FXbool callocElms(EType*& ptr,unsigned long n){
  return fxcalloc((void**)&ptr,sizeof(EType)*n);
  }


/// Allocate array of elements, initialized with bit-wise copy of src array
template<class EType>
inline FXbool dupElms(EType*& ptr,const EType* src,unsigned long n){
  return fxmemdup((void**)&ptr,src,sizeof(EType)*n);
  }


/// Resize array of elements, without constructor or destructor
template<class EType>
inline FXbool resizeElms(EType*& ptr,unsigned long n){
  return fxresize((void**)&ptr,sizeof(EType)*n);
  }


/// Free array of elements, without destruction
template<class EType>
inline void freeElms(EType*& ptr){
  fxfree((void**)&ptr);
  }


/**********************  I m p l e m e n t a t i o n  ************************/

// Specific implementations for built-in types


// No-op constructors for array of basic type
inline void constructElms(FXuchar*,unsigned long){ }
inline void constructElms(FXchar*,unsigned long){ }
inline void constructElms(FXushort*,unsigned long){ }
inline void constructElms(FXshort*,unsigned long){ }
inline void constructElms(FXuint*,unsigned long){ }
inline void constructElms(FXint*,unsigned long){ }
inline void constructElms(FXfloat*,unsigned long){ }
inline void constructElms(FXdouble*,unsigned long){ }

// No-op destructors for array of basic type
inline void destructElms(FXuchar*,unsigned long){ }
inline void destructElms(FXchar*,unsigned long){ }
inline void destructElms(FXushort*,unsigned long){ }
inline void destructElms(FXshort*,unsigned long){ }
inline void destructElms(FXuint*,unsigned long){ }
inline void destructElms(FXint*,unsigned long){ }
inline void destructElms(FXfloat*,unsigned long){ }
inline void destructElms(FXdouble*,unsigned long){ }

// Simple bit-wise copy for array of basic type
inline void copyElms(FXuchar* dst,const FXuchar* src,unsigned long n){ memcpy(dst,src,n); }
inline void copyElms(FXchar* dst,const FXchar* src,unsigned long n){ memcpy(dst,src,n); }
inline void copyElms(FXushort* dst,const FXushort* src,unsigned long n){ memcpy(dst,src,n<<1); }
inline void copyElms(FXshort* dst,const FXshort* src,unsigned long n){ memcpy(dst,src,n<<1); }
inline void copyElms(FXuint* dst,const FXuint* src,unsigned long n){ memcpy(dst,src,n<<2); }
inline void copyElms(FXint* dst,const FXint* src,unsigned long n){ memcpy(dst,src,n<<2); }
inline void copyElms(FXfloat* dst,const FXfloat* src,unsigned long n){ memcpy(dst,src,n<<2); }
inline void copyElms(FXdouble* dst,const FXdouble* src,unsigned long n){ memcpy(dst,src,n<<3); }

// Simple bit-wise copy for array of pointers to any type
template<class EType> inline void copyElms(EType** dst,const EType** src,unsigned long n){ memcpy(dst,src,n*sizeof(void*)); }

// Simple bit-wise move for array of basic type
inline void moveElms(FXuchar* dst,const FXuchar* src,unsigned long n){ memmove(dst,src,n); }
inline void moveElms(FXchar* dst,const FXchar* src,unsigned long n){ memmove(dst,src,n); }
inline void moveElms(FXushort* dst,const FXushort* src,unsigned long n){ memmove(dst,src,n<<1); }
inline void moveElms(FXshort* dst,const FXshort* src,unsigned long n){ memmove(dst,src,n<<1); }
inline void moveElms(FXuint* dst,const FXuint* src,unsigned long n){ memmove(dst,src,n<<2); }
inline void moveElms(FXint* dst,const FXint* src,unsigned long n){ memmove(dst,src,n<<2); }
inline void moveElms(FXfloat* dst,const FXfloat* src,unsigned long n){ memmove(dst,src,n<<2); }
inline void moveElms(FXdouble* dst,const FXdouble* src,unsigned long n){ memmove(dst,src,n<<3); }

// Simple bit-wise move for array of pointers to any type
template<class EType> inline void moveElms(EType** dst,const EType** src,unsigned long n){ memmove(dst,src,n*sizeof(void*)); }

// Fill byte arrays with constant
inline void fillElms(FXuchar* dst,const FXuchar& src,unsigned long n){ memset(dst,src,n); }
inline void fillElms(FXchar* dst,const FXchar& src,unsigned long n){ memset(dst,src,n); }

}

#endif
