/********************************************************************************
*                                                                               *
*                      E x p r e s s i o n   E v a l u a t o r                  *
*                                                                               *
*********************************************************************************
* Copyright (C) 1998,2006 by Jeroen van der Zijp.   All Rights Reserved.        *
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
* $Id: FXExpression.h 2401 2006-04-27 00:46:49Z lyle $                      *
********************************************************************************/
#ifndef FXEXPRESSION_H
#define FXEXPRESSION_H


namespace FX {


/// Expression error codes
enum FXExpressionError {
  EXPRERR_OK,
  EXPRERR_EMPTY,             /// Empty input
  EXPRERR_MEMORY,            /// Out of memory
  EXPRERR_PAREN,             /// Unmatched parentheses
  EXPRERR_TOKEN,             /// Illegal token
  EXPRERR_COMMA,             /// Expected comma
  EXPRERR_IDENT              /// Unknown identifier
  };


/// Expression
class FXAPI FXExpression {
private:
  FXuchar *code;
private:
  static const FXuchar initial[];
  static const FXchar *const errors[];
public:

  /// Construct empty expression object
  FXExpression();

  /// Copy expression object
  FXExpression(const FXExpression& orig);

  /// Compile expression; if error is not NULL, error code is returned
  FXExpression(const FXchar* expression,const FXchar* variables=NULL,FXExpressionError* error=NULL);

  /// Compile expression; if error is not NULL, error code is returned
  FXExpression(const FXString& expression,const FXString& variables=FXString::null,FXExpressionError* error=NULL);

  /// Assign another expression to this one
  FXExpression& operator=(const FXExpression& orig);

  /// See if expression is empty
  bool empty() const { return (code==initial); }

  /// Evaluate expression with given arguments, if any
  FXdouble evaluate(const FXdouble *args=NULL);

  /// Parse expression, return error code if syntax error is found
  FXExpressionError parse(const FXchar* expression,const FXchar* variables=NULL);

  /// Parse expression, return error code if syntax error is found
  FXExpressionError parse(const FXString& expression,const FXString& variables=FXString::null);

  /// Returns error code for given error
  static const FXchar* getError(FXExpressionError err){ return errors[err]; }

  /// Delete
 ~FXExpression();
  };

}

#endif
