/********************************************************************************
*                                                                               *
*                         A t o m i c   I n t e g e r                           *
*                                                                               *
*********************************************************************************
* Copyright (C) 2006,2007 by Jeroen van der Zijp.   All Rights Reserved.        *
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
* $Id: FXAtomic.h,v 1.24 2007/11/02 15:43:45 fox Exp $                          *
********************************************************************************/
#ifndef FXATOMIC_H
#define FXATOMIC_H


namespace FX {


/**
* An atomically incrementable integer
*/
class FXAtomicInt {
  volatile int val;
public:

  /// Constructs an atomic integer with a given initial value.
  FXAtomicInt(int v=0):val(v){}

  /// Returns current value of the integer
  operator int() const { return val; }


  /// Returns current value of the integer
  inline int get() const { return val; }


  /// Set variable to v; return old value
  inline int set(int v){
#if defined(WIN32)
    return InterlockedExchange((LONG*)&val,v);
#elif defined(__GNUC__) && defined (__GNUC_MINOR__) && ((4 < __GNUC__) || (4 == __GNUC__ && 1 <= __GNUC_MINOR__))
    int ret=v;
    __asm__ __volatile__("lock\n\t"
                         "xchgl %0,%1\n\t" : "=r" (ret) : "m" (val), "0" (ret) : "memory");
    return ret;
#else
    int ret=val;
    val=v;
    return ret;
#endif
    }


  /// If variable is equal to expect, set it to v; returns old value
  inline int test_and_set(int expect,int v){
#if defined(WIN32)
    return InterlockedCompareExchange((LONG*)&val,v,expect);
#elif defined(__GNUC__) && defined (__GNUC_MINOR__) && ((4 < __GNUC__) || (4 == __GNUC__ && 1 <= __GNUC_MINOR__))
    return __sync_val_compare_and_swap(&val,expect,v);
#elif (defined(__GNUC__) || defined(__ICC)) && (defined(__i386__) || defined(__x86_64__))
    int ret;
    __asm__ __volatile__("lock\n\t"
                         "cmpxchgl %1,%2\n\t" : "=a" (ret) : "r" (v), "m" (val), "0" (expect) : "memory");
    return ret;
#else
    int ret=val;
    if(ret==expect) val=v;
    return ret;
#endif
    }


  /// Atomically add v to the variable
  inline FXAtomicInt& operator+=(int v){
#if defined(WIN32)
    InterlockedAdd((LONG*)&val,v);
#elif defined(__GNUC__) && defined (__GNUC_MINOR__) && ((4 < __GNUC__) || (4 == __GNUC__ && 1 <= __GNUC_MINOR__))
    __sync_add_and_fetch(&val,v);
#elif (defined(__GNUC__) || defined(__ICC)) && (defined(__i386__) || defined(__x86_64__))
    __asm__ __volatile__ ("lock\n\t"
                          "addl %1,%0\n\t" : "=m" (val) : "ir" (v), "m" (val) : "memory");
#else
    val+=v;
#endif
    return *this;
    }


  /// Atomically substract v from the variable
  inline FXAtomicInt& operator-=(int v){
#if defined(WIN32)
    InterlockedAdd((LONG*)&val,-v);
#elif defined(__GNUC__) && defined (__GNUC_MINOR__) && ((4 < __GNUC__) || (4 == __GNUC__ && 1 <= __GNUC_MINOR__))
    __sync_add_and_fetch(&val,-v);
#elif (defined(__GNUC__) || defined(__ICC)) && (defined(__i386__) || defined(__x86_64__))
    __asm__ __volatile__ ("lock\n\t"
                          "subl %1,%0\n\t" : "=m" (val) : "ir" (v), "m" (val) : "memory");
#else
    val-=v;
#endif
    return *this;
    }


  /// Atomically bitwise-or v to the variable
  inline FXAtomicInt& operator|=(int v){
#if defined(WIN32)
    InterlockedOr((LONG*)&val,v);
#elif defined(__GNUC__) && defined (__GNUC_MINOR__) && ((4 < __GNUC__) || (4 == __GNUC__ && 1 <= __GNUC_MINOR__))
    __sync_or_and_fetch(&val,v);
#elif (defined(__GNUC__) || defined(__ICC)) && (defined(__i386__) || defined(__x86_64__))
    __asm__ __volatile__ ("lock\n\t"
                          "orl %1,%0\n\t" : "=m" (val) : "ir" (v), "m" (val) : "memory");
#else
    val|=v;
#endif
    return *this;
    }


  /// Atomically bitwise-and v to the variable
  inline FXAtomicInt& operator&=(int v){
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
  inline FXAtomicInt& operator^=(int v){
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
  inline int operator++(){
#if defined(WIN32)
    return InterlockedAdd((LONG*)&val,1);
#elif defined(__GNUC__) && defined (__GNUC_MINOR__) && ((4 < __GNUC__) || (4 == __GNUC__ && 1 <= __GNUC_MINOR__))
    return __sync_add_and_fetch(&val,1);
#elif (defined(__GNUC__) || defined(__ICC)) && (defined(__i386__) || defined(__x86_64__))
    int ret=1;
    __asm__ __volatile__ ("lock\n\t"
                          "xaddl %0,%1\n\t" : "=r"(ret), "=m"(val) : "0"(ret), "m"(val) : "memory");
    return ret+1;
#else
    return ++val;
#endif
    }


  /// Atomically decrement the integer, prefix version
  inline int operator--(){
#if defined(WIN32)
    return InterlockedAdd((LONG*)&val,-1);
#elif defined(__GNUC__) && defined (__GNUC_MINOR__) && ((4 < __GNUC__) || (4 == __GNUC__ && 1 <= __GNUC_MINOR__))
    return __sync_add_and_fetch(&val,-1);
#elif (defined(__GNUC__) || defined(__ICC)) && (defined(__i386__) || defined(__x86_64__))
    int ret=-1;
    __asm__ __volatile__ ("lock\n\t"
                          "xaddl %0,%1\n\t" : "=r"(ret), "=m"(val) : "0"(ret), "m"(val) : "memory");
    return ret-1;
#else
    return --val;
#endif
    }


  /// Atomically increment value, postfix version
  inline int operator++(int){
#if defined(WIN32)
    return InterlockedExchangeAdd((LONG*)&val,1);
#elif defined(__GNUC__) && defined (__GNUC_MINOR__) && ((4 < __GNUC__) || (4 == __GNUC__ && 1 <= __GNUC_MINOR__))
    return __sync_fetch_and_add(&val,1);
#elif (defined(__GNUC__) || defined(__ICC)) && (defined(__i386__) || defined(__x86_64__))
    int ret=1;
    __asm__ __volatile__ ("lock\n\t"
                          "xaddl %0,%1\n\t" : "=r"(ret), "=m"(val) : "0"(ret), "m"(val) : "memory");
    return ret;
#else
    return val++;
#endif
    }


  /// Atomically decrement value, postfix version
  inline int operator--(int){
#if defined(WIN32)
    return InterlockedExchangeAdd((LONG*)&val,-1);
#elif defined(__GNUC__) && defined (__GNUC_MINOR__) && ((4 < __GNUC__) || (4 == __GNUC__ && 1 <= __GNUC_MINOR__))
    return __sync_fetch_and_add(&val,-1);
#elif (defined(__GNUC__) || defined(__ICC)) && (defined(__i386__) || defined(__x86_64__))
    int ret=-1;
    __asm__ __volatile__ ("lock\n\t"
                          "xaddl %0,%1\n\t" : "=r"(ret), "=m"(val) : "0"(ret), "m"(val) : "memory");
    return ret;
#else
    return val--;
#endif
    }
  };

}

#endif
