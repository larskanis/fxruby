/********************************************************************************
*                                                                               *
*                         A t o m i c   I n t e g e r                           *
*                                                                               *
*********************************************************************************
* Copyright (C) 2006,2009 by Jeroen van der Zijp.   All Rights Reserved.        *
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
* $Id: FXAtomic.h,v 1.32 2009/01/22 13:31:24 fox Exp $                          *
********************************************************************************/
#ifndef FXATOMIC_H
#define FXATOMIC_H


namespace FX {


/**
* An atomically modifyable integer.
*/
class FXAtomicInt {
private:
  volatile FXint val;
public:

  /// Constructs an atomic integer with a given initial value.
  FXAtomicInt(FXint v=0):val(v){}


  /// Assign from value
  FXAtomicInt& operator=(FXint v){ val=v; return *this; }


  /// Returns current value of the integer
  operator FXint() const { return val; }


  /// Returns current value of the integer
  inline FXint get() const { return val; }


  /// Set variable to v; return old value
  inline FXint set(FXint v){
#if defined(WIN32)
    return InterlockedExchange((LONG*)&val,v);
#elif (defined(__GNUC__) || defined(__ICC)) && (defined(__i386__) || defined(__x86_64__))
    FXint ret=v;
    __asm__ __volatile__("lock\n\t"
                         "xchgl %0,%1\n\t" : "=r" (ret) : "m" (val), "0" (ret) : "memory");
    return ret;
#else
    FXint ret=val;
    val=v;
    return ret;
#endif
    }


  /// If variable is equal to expect, set it to v; returns old value
  inline FXint cas(FXint expect,FXint v){
#if defined(WIN32)
    return InterlockedCompareExchange((LONG*)&val,v,expect);
#elif (defined(__GNUC__) || defined(__ICC)) && (defined(__i386__) || defined(__x86_64__))
    FXint ret;
    __asm__ __volatile__("lock\n\t"
                         "cmpxchgl %1,%2\n\t" : "=a" (ret) : "r" (v), "m" (val), "0" (expect) : "memory");
    return ret;
#elif defined(__GNUC__) && defined (__GNUC_MINOR__) && ((4 < __GNUC__) || (4 == __GNUC__ && 1 <= __GNUC_MINOR__))
    return __sync_val_compare_and_swap(&val,expect,v);
#else
    FXint ret=val;
    if(val==expect) val=v;
    return ret;
#endif
    }


  /// Atomically add v to the variable
  inline FXAtomicInt& operator+=(FXint v){
#if defined(WIN32)
    InterlockedAdd((LONG*)&val,v);
#elif (defined(__GNUC__) || defined(__ICC)) && (defined(__i386__) || defined(__x86_64__))
    __asm__ __volatile__ ("lock\n\t"
                          "addl %1,%0\n\t" : "=m" (val) : "ir" (v), "m" (val) : "memory");
#elif defined(__GNUC__) && defined (__GNUC_MINOR__) && ((4 < __GNUC__) || (4 == __GNUC__ && 1 <= __GNUC_MINOR__))
    __sync_add_and_fetch(&val,v);
#else
    val+=v;
#endif
    return *this;
    }


  /// Atomically substract v from the variable
  inline FXAtomicInt& operator-=(FXint v){
#if defined(WIN32)
    InterlockedAdd((LONG*)&val,-v);
#elif (defined(__GNUC__) || defined(__ICC)) && (defined(__i386__) || defined(__x86_64__))
    __asm__ __volatile__ ("lock\n\t"
                          "subl %1,%0\n\t" : "=m" (val) : "ir" (v), "m" (val) : "memory");
#elif defined(__GNUC__) && defined (__GNUC_MINOR__) && ((4 < __GNUC__) || (4 == __GNUC__ && 1 <= __GNUC_MINOR__))
    __sync_add_and_fetch(&val,-v);
#else
    val-=v;
#endif
    return *this;
    }


  /// Atomically bitwise-or v to the variable
  inline FXAtomicInt& operator|=(FXint v){
#if defined(WIN32)
    InterlockedOr((LONG*)&val,v);
#elif (defined(__GNUC__) || defined(__ICC)) && (defined(__i386__) || defined(__x86_64__))
    __asm__ __volatile__ ("lock\n\t"
                          "orl %1,%0\n\t" : "=m" (val) : "ir" (v), "m" (val) : "memory");
#elif defined(__GNUC__) && defined (__GNUC_MINOR__) && ((4 < __GNUC__) || (4 == __GNUC__ && 1 <= __GNUC_MINOR__))
    __sync_or_and_fetch(&val,v);
#else
    val|=v;
#endif
    return *this;
    }


  /// Atomically bitwise-and v to the variable
  inline FXAtomicInt& operator&=(FXint v){
#if defined(WIN32)
    InterlockedAnd((LONG*)&val,v);
#elif defined(__GNUC__) && defined (__GNUC_MINOR__) && ((4 < __GNUC__) || (4 == __GNUC__ && 1 <= __GNUC_MINOR__))
    __sync_and_and_fetch(&val,v);
#elif (defined(__GNUC__) || defined(__ICC)) && (defined(__i386__) || defined(__x86_64__))
    __asm__ __volatile__ ("lock\n\t"
                          "andl %1,%0\n\t" : "=m" (val) : "ir" (v), "m" (val) : "memory");
#else
    val&=v;
#endif
    return *this;
    }


  /// Atomically bitwise-xor v to the variable
  inline FXAtomicInt& operator^=(FXint v){
#if defined(WIN32)
    InterlockedXor((LONG*)&val,v);
#elif defined(__GNUC__) && defined (__GNUC_MINOR__) && ((4 < __GNUC__) || (4 == __GNUC__ && 1 <= __GNUC_MINOR__))
    __sync_xor_and_fetch(&val,v);
#elif (defined(__GNUC__) || defined(__ICC)) && (defined(__i386__) || defined(__x86_64__))
    __asm__ __volatile__ ("lock\n\t"
                          "xorl %1,%0\n\t" : "=m" (val) : "ir" (v), "m" (val) : "memory");
#else
    val^=v;
#endif
    return *this;
    }


  /// Atomically increment the integer, prefix version
  inline FXint operator++(){
#if defined(WIN32)
    return InterlockedAdd((LONG*)&val,1);
#elif (defined(__GNUC__) || defined(__ICC)) && (defined(__i386__) || defined(__x86_64__))
    FXint ret=1;
    __asm__ __volatile__ ("lock\n\t"
                          "xaddl %0,%1\n\t" : "=r"(ret), "=m"(val) : "0"(ret), "m"(val) : "memory");
    return ret+1;
#elif defined(__GNUC__) && defined (__GNUC_MINOR__) && ((4 < __GNUC__) || (4 == __GNUC__ && 1 <= __GNUC_MINOR__))
    return __sync_add_and_fetch(&val,1);
#else
    return ++val;
#endif
    }


  /// Atomically decrement the integer, prefix version
  inline FXint operator--(){
#if defined(WIN32)
    return InterlockedAdd((LONG*)&val,-1);
#elif (defined(__GNUC__) || defined(__ICC)) && (defined(__i386__) || defined(__x86_64__))
    FXint ret=-1;
    __asm__ __volatile__ ("lock\n\t"
                          "xaddl %0,%1\n\t" : "=r"(ret), "=m"(val) : "0"(ret), "m"(val) : "memory");
    return ret-1;
#elif defined(__GNUC__) && defined (__GNUC_MINOR__) && ((4 < __GNUC__) || (4 == __GNUC__ && 1 <= __GNUC_MINOR__))
    return __sync_add_and_fetch(&val,-1);
#else
    return --val;
#endif
    }


  /// Atomically increment value, postfix version
  inline int operator++(FXint){
#if defined(WIN32)
    return InterlockedExchangeAdd((LONG*)&val,1);
#elif (defined(__GNUC__) || defined(__ICC)) && (defined(__i386__) || defined(__x86_64__))
    FXint ret=1;
    __asm__ __volatile__ ("lock\n\t"
                          "xaddl %0,%1\n\t" : "=r"(ret), "=m"(val) : "0"(ret), "m"(val) : "memory");
    return ret;
#elif defined(__GNUC__) && defined (__GNUC_MINOR__) && ((4 < __GNUC__) || (4 == __GNUC__ && 1 <= __GNUC_MINOR__))
    return __sync_fetch_and_add(&val,1);
#else
    return val++;
#endif
    }


  /// Atomically decrement value, postfix version
  inline FXint operator--(FXint){
#if defined(WIN32)
    return InterlockedExchangeAdd((LONG*)&val,-1);
#elif (defined(__GNUC__) || defined(__ICC)) && (defined(__i386__) || defined(__x86_64__))
    FXint ret=-1;
    __asm__ __volatile__ ("lock\n\t"
                          "xaddl %0,%1\n\t" : "=r"(ret), "=m"(val) : "0"(ret), "m"(val) : "memory");
    return ret;
#elif defined(__GNUC__) && defined (__GNUC_MINOR__) && ((4 < __GNUC__) || (4 == __GNUC__ && 1 <= __GNUC_MINOR__))
    return __sync_fetch_and_add(&val,-1);
#else
    return val--;
#endif
    }
  };




/**
* An atomically modifyable pointer.
*/
template<class EType>
class FXAtomicPtr {
private:
  EType *volatile ptr;
public:

  /// Constructs an atomic pointer with a given initial value.
  FXAtomicPtr(EType* p=NULL):ptr(p){ }

  /// Assign from pointer
  FXAtomicPtr& operator=(EType *p){ ptr=p; return *this; }

  /// Returns current value of the pointer
  operator EType*() const { return ptr; }

  /// Dereference operator
  EType& operator*() const { return *ptr; }

  /// Follow pointer operator
  EType *operator->() const { return ptr; }


  /// Returns current value of the pointer
  inline EType* get() const { return ptr; }


  /// Set pointer to p; return old value
  inline EType* set(EType* p){
#if defined(WIN32)
   return (EType*)InterlockedExchangePointer((void *volatile)&ptr,p);
#elif (defined(__GNUC__) || defined(__ICC)) && defined(__i386__)
    EType* ret=p;
    __asm__ __volatile__("lock\n\t"
                         "xchgl %0,%1\n\t" : "=r" (ret) : "m" (ptr), "0" (ret) : "memory");
    return ret;
#elif (defined(__GNUC__) || defined(__ICC)) && defined(__x86_64__)
    EType* ret=p;
    __asm__ __volatile__("lock\n\t"
                         "xchgq %0,%1\n\t" : "=r" (ret) : "m" (ptr), "0" (ret) : "memory");
    return ret;
#else
    EType* ret=ptr;
    ptr=p;
    return ret;
#endif
    }


  /// If pointer is equal to expect, set it to p; returns old value
  inline EType* cas(EType* expect,EType* p){
#if defined(WIN32)
    return (EType*)InterlockedCompareExchangePointer((void *volatile)&ptr,p,expect);
#elif (defined(__GNUC__) || defined(__ICC)) && defined(__i386__)
    EType* ret;
    __asm__ __volatile__("lock\n\t"
                         "cmpxchgl %1,%2\n\t" : "=a" (ret) : "r" (p), "m" (ptr), "0" (expect) : "memory");
    return ret;
#elif (defined(__GNUC__) || defined(__ICC)) && defined(__x86_64__)
    EType* ret;
    __asm__ __volatile__("lock\n\t"
                         "cmpxchgq %1,%2\n\t" : "=a" (ret) : "r" (p), "m" (ptr), "0" (expect) : "memory");
    return ret;
#elif defined(__GNUC__) && defined (__GNUC_MINOR__) && ((4 < __GNUC__) || (4 == __GNUC__ && 1 <= __GNUC_MINOR__))
    return __sync_val_compare_and_swap(&ptr,expect,p);
#else
    EType* ret=ptr;
    if(ptr==expect) ptr=p;
    return ret;
#endif
    }
  };


}

#endif
