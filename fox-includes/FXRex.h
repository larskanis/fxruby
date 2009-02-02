/********************************************************************************
*                                                                               *
*                 R e g u l a r   E x p r e s s i o n   C l a s s               *
*                                                                               *
*********************************************************************************
* Copyright (C) 1999,2006 by Jeroen van der Zijp.   All Rights Reserved.        *
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
* $Id: FXRex.h 2343 2006-02-12 20:26:26Z lyle $                             *
********************************************************************************/
#ifndef FXREX_H
#define FXREX_H


namespace FX {


/// Regular expression error codes
enum FXRexError {
  REGERR_OK,
  REGERR_EMPTY,             /// Empty pattern
  REGERR_PAREN,             /// Unmatched parenthesis
  REGERR_BRACK,             /// Unmatched bracket
  REGERR_BRACE,             /// Unmatched brace
  REGERR_RANGE,             /// Bad character range
  REGERR_ESC,               /// Bad escape sequence
  REGERR_COUNT,             /// Bad counted repeat
  REGERR_NOATOM,            /// No atom preceding repetition
  REGERR_REPEAT,            /// Repeat following repeat
  REGERR_BACKREF,           /// Bad backward reference
  REGERR_CLASS,             /// Bad character class
  REGERR_COMPLEX,           /// Expression too complex
  REGERR_MEMORY,            /// Out of memory
  REGERR_TOKEN              /// Illegal token
  };


/// Regular expression parse flags
enum {
  REX_NORMAL    = 0,        /// Normal mode
  REX_CAPTURE   = 1,        /// Perform capturing parentheses
  REX_ICASE     = 2,        /// Case independent matching
  REX_NEWLINE   = 4,        /// Match-any operators match newline too
  REX_VERBATIM  = 8,        /// Disable interpretation of magic characters
  REX_SYNTAX    = 16        /// Perform syntax check only
  };


/// Regular expression match flags
enum {
  REX_FORWARD   = 0,        /// Match scanning forward from offset
  REX_BACKWARD  = 32,       /// Match scanning backward from offset
  REX_NOT_BOL   = 64,       /// Start of string is NOT begin of line
  REX_NOT_EOL   = 128,      /// End of string is NOT end of line
  REX_NOT_EMPTY = 256       /// Do not match empty
  };


/**
* FXRex is a regular expression class implementing a NFA matcher.
* It supports capturing parentheses, non-capturing parentheses,
* positive or negative lookahead, backreferences, case-insensitive
* matching, counted repetitions, lazy or greedy matches, and
* PERL-like matching operators.
* The subject string may be scanned forwards or backwards, and may
* contain any of 256 possible character values.
*
* When parsing a regular expression pattern, the mode parameter is
* the bitwise OR of a set of flags and affects the match algorithm.
* Passing the flag REX_CAPTURE enables capturing parentheses
* and back references. The flag REX_ICASE enables case-insensitive
* matching. When the flag REX_NEWLINE is passed, newlines are treated
* like normal characters; otherwise, newline is NOT matched
* except when explicitly part of a character class. The flag
* REX_VERBATIM disables all special character interpretation.
*
* When matching a compiled pattern, the mode parameter is the
* bitwise OR of a set of flags that affects how the match is
* performed.  Passing the flag REX_BACKWARD causes the match
* to proceed backwards through the subject string.  Passing the
* flags REX_NOT_BOL and/or REX_NOT_EOL causes the begin and
* end of the subject string NOT to be considered a line start
* or line end. The flag REX_NOT_EMPTY causes a match to fail if
* the empty string was matched.
*/
class FXAPI FXRex {
private:
  FXint *code;
private:
  static const FXchar *const errors[];
  static const FXint fallback[];
public:

  /// Construct empty regular expression object
  FXRex():code((FXint*)fallback){}

  /// Copy regular expression object
  FXRex(const FXRex& orig);

  /// Compile expression from pattern; if error is not NULL, error code is returned
  FXRex(const FXchar* pattern,FXint mode=REX_NORMAL,FXRexError* error=NULL);

  /// Compile expression from pattern; if error is not NULL, error code is returned
  FXRex(const FXString& pattern,FXint mode=REX_NORMAL,FXRexError* error=NULL);

  /// Assign another regular expression to this one
  FXRex& operator=(const FXRex& orig);

  /**
  * See if regular expression is empty; the regular expression
  * will be empty when it is unable to parse a pattern due to
  * a syntax error.
  */
  bool empty() const { return (code==fallback); }

  /// Parse pattern, return error code if syntax error is found
  FXRexError parse(const FXchar* pattern,FXint mode=REX_NORMAL);

  /// Parse pattern, return error code if syntax error is found
  FXRexError parse(const FXString& pattern,FXint mode=REX_NORMAL);

  /**
  * Match a subject string of length len, returning TRUE if a match is found
  * and FALSE otherwise.  The entire pattern is captured in beg[0] and end[0],
  * where beg[0] refers to the position of the first matched character and end[0]
  * refers to the position after the last matched character.
  * Sub expressions from capturing parenthesis i are returned in beg[i] and end[i].
  */
  bool match(const FXchar* string,FXint len,FXint* beg=NULL,FXint* end=NULL,FXint mode=REX_FORWARD,FXint npar=1,FXint fm=0,FXint to=2147483647) const;

  /// Search for match in a string
  bool match(const FXString& string,FXint* beg=NULL,FXint* end=NULL,FXint mode=REX_FORWARD,FXint npar=1,FXint fm=0,FXint to=2147483647) const;

  /**
  * After performing a regular expression match with capturing parentheses,
  * a substitution string is build from the replace string, where where "&"
  * is replaced by the entire matched pattern, and "\1" through "\9" are
  * replaced by captured expressions.  The original source string and its
  * length, and the match arrays beg and end must be passed.
  */
  static FXString substitute(const FXchar* string,FXint len,FXint* beg,FXint* end,const FXString& replace,FXint npar=1);

  /// Return substitution string
  static FXString substitute(const FXString& string,FXint* beg,FXint* end,const FXString& replace,FXint npar=1);

  /// Returns error code for given error
  static const FXchar* getError(FXRexError err){ return errors[err]; }

  /// Comparison operators
  bool operator==(const FXRex& rex) const;
  bool operator!=(const FXRex& rex) const;

  /// Saving and loading
  friend FXAPI FXStream& operator<<(FXStream& store,const FXRex& s);
  friend FXAPI FXStream& operator>>(FXStream& store,FXRex& s);

  /// Delete
 ~FXRex();
  };


extern FXAPI FXStream& operator<<(FXStream& store,const FXRex& s);
extern FXAPI FXStream& operator>>(FXStream& store,FXRex& s);

}

#endif
