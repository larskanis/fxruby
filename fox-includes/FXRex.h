/********************************************************************************
*                                                                               *
*                 R e g u l a r   E x p r e s s i o n   C l a s s               *
*                                                                               *
*********************************************************************************
* Copyright (C) 1999,2009 by Jeroen van der Zijp.   All Rights Reserved.        *
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
* $Id: FXRex.h,v 1.63 2009/01/06 13:07:27 fox Exp $                             *
********************************************************************************/
#ifndef FXREX_H
#define FXREX_H


namespace FX {


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
* Passing the flag Capture enables capturing parentheses
* and back references. The flag IgnoreCase enables case-insensitive
* matching. When the flag Newline is passed, newlines are treated
* like normal characters; otherwise, newline is NOT matched
* except when explicitly part of a character class. The flag
* Verbatim disables all special character interpretation.
*
* When matching a compiled pattern, the mode parameter is the
* bitwise OR of a set of flags that affects how the match is
* performed.  Passing the flag Backward causes the match
* to proceed backwards through the subject string.  Passing the
* flags NotBol and/or NotEol causes the begin and
* end of the subject string NOT to be considered a line start
* or line end. The flag NotEmpty causes a match to fail if
* the empty string was matched.
*/
class FXAPI FXRex {
private:
  FXint *code;
private:
  static const FXchar *const errors[];
  static const FXint fallback[];
public:

  /// Regular expression parse flags
  enum {
    Normal     = 0,     /// Normal mode
    Capture    = 1,     /// Perform capturing parentheses
    IgnoreCase = 2,     /// Ignore case differences
    Newline    = 4,     /// Match-any operators match newline too
    Verbatim   = 8,     /// Disable interpretation of magic characters
    Syntax     = 16     /// Perform syntax check only
    };


  /// Regular expression match flags
  enum {
    Forward    = 0,     /// Match scanning forward from offset
    Backward   = 32,    /// Match scanning backward from offset
    NotBol     = 64,    /// Start of string is NOT begin of line
    NotEol     = 128,   /// End of string is NOT end of line
    NotEmpty   = 256    /// Do not match empty
    };

  /// Regular expression error codes
  enum Error {
    ErrOK      = 0,     /// No errors
    ErrEmpty   = 1,     /// Empty pattern
    ErrParent  = 2,     /// Unmatched parenthesis
    ErrBracket = 3,     /// Unmatched bracket
    ErrBrace   = 4,     /// Unmatched brace
    ErrRange   = 5,     /// Bad character range
    ErrEscape  = 6,     /// Bad escape sequence
    ErrCount   = 7,     /// Bad counted repeat
    ErrNoAtom  = 8,     /// No atom preceding repetition
    ErrRepeat  = 9,     /// Repeat following repeat
    ErrBackRef = 10,    /// Bad backward reference
    ErrClass   = 11,    /// Bad character class
    ErrComplex = 12,    /// Expression too complex
    ErrMemory  = 13,    /// Out of memory
    ErrToken   = 14,    /// Illegal token
    ErrBehind  = 15     /// Bad look-behind pattern
    };

public:

  /// Construct empty regular expression object
  FXRex():code((FXint*)fallback){}

  /// Copy regular expression object
  FXRex(const FXRex& orig);

  /// Compile expression from pattern; if error is not NULL, error code is returned
  FXRex(const FXchar* pattern,FXint mode=Normal,Error* error=NULL);

  /// Compile expression from pattern; if error is not NULL, error code is returned
  FXRex(const FXString& pattern,FXint mode=Normal,Error* error=NULL);

  /// Assign another regular expression to this one
  FXRex& operator=(const FXRex& orig);

  /**
  * See if regular expression is empty; the regular expression
  * will be empty when it is unable to parse a pattern due to
  * a syntax error.
  */
  FXbool empty() const { return (code==fallback); }

  /// Parse pattern, return error code if syntax error is found
  FXRex::Error parse(const FXchar* pattern,FXint mode=Normal);

  /// Parse pattern, return error code if syntax error is found
  FXRex::Error parse(const FXString& pattern,FXint mode=Normal);

  /**
  * Match a subject string of length len, returning true if a match is found
  * and false otherwise.  The entire pattern is captured in beg[0] and end[0],
  * where beg[0] refers to the position of the first matched character and end[0]
  * refers to the position after the last matched character.
  * Sub expressions from capturing parenthesis i are returned in beg[i] and end[i].
  */
  FXbool match(const FXchar* string,FXint len,FXint* beg=NULL,FXint* end=NULL,FXint mode=Forward,FXint npar=1,FXint fm=0,FXint to=2147483647) const;

  /// Search for match in a string
  FXbool match(const FXString& string,FXint* beg=NULL,FXint* end=NULL,FXint mode=Forward,FXint npar=1,FXint fm=0,FXint to=2147483647) const;

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
  static const FXchar* getError(FXRex::Error err){ return errors[err]; }

  /// Comparison operators
  FXbool operator==(const FXRex& rex) const;
  FXbool operator!=(const FXRex& rex) const;

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
