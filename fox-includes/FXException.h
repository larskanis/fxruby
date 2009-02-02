/********************************************************************************
*                                                                               *
*                          E x c e p t i o n  T y p e s                         *
*                                                                               *
*********************************************************************************
* Copyright (C) 2000,2005 by Jeroen van der Zijp.   All Rights Reserved.        *
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
* $Id: FXException.h 2127 2005-08-07 20:21:35Z lyle $                       *
********************************************************************************/
#ifndef FXEXCEPTION_H
#define FXEXCEPTION_H


namespace FX {

/// Generic catch-all exception
class FXAPI FXException {
private:
  const FXchar *message;
private:
  static const FXchar exceptionName[];
public:
  FXException():message(FXException::exceptionName){}
  FXException(const FXchar *msg):message(msg){}
  const FXchar *what() const { return message; }
  ~FXException(){}
  };


/// Generic error exception
class FXAPI FXErrorException : public FXException {
private:
  static const FXchar exceptionName[];
public:
  FXErrorException():FXException(FXErrorException::exceptionName){}
  FXErrorException(const FXchar *msg):FXException(msg){}
  };


/// Index out of range
class FXAPI FXRangeException : public FXErrorException {
private:
  static const FXchar exceptionName[];
public:
  FXRangeException():FXErrorException(FXRangeException::exceptionName){}
  FXRangeException(const FXchar *msg):FXErrorException(msg){}
  };


/// Invalid pointer
class FXAPI FXPointerException : public FXErrorException {
private:
  static const FXchar exceptionName[];
public:
  FXPointerException():FXErrorException(FXPointerException::exceptionName){}
  FXPointerException(const FXchar *msg):FXErrorException(msg){}
  };


/// Generic resource exception
class FXAPI FXResourceException : public FXException {
private:
  static const FXchar exceptionName[];
public:
  FXResourceException():FXException(FXResourceException::exceptionName){}
  FXResourceException(const FXchar *msg):FXException(msg){}
  };


/// Out of memory
class FXAPI FXMemoryException : public FXResourceException {
private:
  static const FXchar exceptionName[];
public:
  FXMemoryException():FXResourceException(FXMemoryException::exceptionName){}
  FXMemoryException(const FXchar *msg):FXResourceException(msg){}
  };


/// Window exception
class FXAPI FXWindowException : public FXResourceException {
private:
  static const FXchar exceptionName[];
public:
  FXWindowException():FXResourceException(FXWindowException::exceptionName){}
  FXWindowException(const FXchar *msg):FXResourceException(msg){}
  };


/// Image, cursor, bitmap exception
class FXAPI FXImageException : public FXResourceException {
private:
  static const FXchar exceptionName[];
public:
  FXImageException():FXResourceException(FXImageException::exceptionName){}
  FXImageException(const FXchar *msg):FXResourceException(msg){}
  };


/// Font exception
class FXAPI FXFontException : public FXResourceException {
private:
  static const FXchar exceptionName[];
public:
  FXFontException():FXResourceException(FXFontException::exceptionName){}
  FXFontException(const FXchar *msg):FXResourceException(msg){}
  };

}

#endif
