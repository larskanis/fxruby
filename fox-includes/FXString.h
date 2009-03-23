/********************************************************************************
*                                                                               *
*                           S t r i n g   O b j e c t                           *
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
* $Id: FXString.h,v 1.151 2009/01/06 13:07:27 fox Exp $                         *
********************************************************************************/
#ifndef FXSTRING_H
#define FXSTRING_H

namespace FX {


class FXStream;


/**
* FXString provides essential string manipulation capabilities.
*/
class FXAPI FXString {
private:
  FXchar* str;
public:
  static const FXchar null[];
public:
  static const FXchar      value2Digit[36];
  static const signed char digit2Value[256];
public:
  static const signed char utfBytes[256];
public:

  /// Create empty string
  FXString();

  /// Copy construct
  FXString(const FXString& s);

  /// Construct and init from string
  FXString(const FXchar* s);

  /// Construct and init from wide character string
  FXString(const FXwchar* s);

  /// Construct and init from narrow character string
  FXString(const FXnchar* s);

  /// Construct and init with substring
  FXString(const FXchar* s,FXint n);

  /// Construct and init with wide character substring
  FXString(const FXwchar* s,FXint n);

  /// Construct and init with narrow character substring
  FXString(const FXnchar* s,FXint n);

  /// Construct and fill with constant
  FXString(FXchar c,FXint n);

  /// Length of text in bytes
  FXint length() const { return *(((FXint*)str)-1); }

  /// Change the length of the string to len
  void length(FXint len);

  /// Count number of utf8 characters
  FXint count() const;

  /// Count number of utf8 characters in subrange start...end
  FXint count(FXint start,FXint end) const;

  /// Return byte offset of utf8 character at index
  FXint offset(FXint indx) const;

  /// Return index of utf8 character at byte offset
  FXint index(FXint offs) const;

  /// Validate position to point to begin of utf8 character
  FXint validate(FXint p) const;

  /// Return extent of utf8 character at position
  FXint extent(FXint p) const { return utfBytes[(FXuchar)str[p]]; }

  /// Increment byte offset by one utf8 character
  FXint inc(FXint p) const;

  /// Increment byte offset by n utf8 characters
  FXint inc(FXint p,FXint n) const;

  /// Decrement byte offset by one utf8 character
  FXint dec(FXint p) const;

  /// Decrement byte offset by n utf8 characters
  FXint dec(FXint p,FXint n) const;

  /// Get text contents
  const FXchar* text() const { return (const FXchar*)str; }

  /// See if string is empty
  FXbool empty() const { return (((FXint*)str)[-1]==0); }

  /// See if string is empty
  FXbool operator!() const { return (((FXint*)str)[-1]==0); }

  /// Return a non-const reference to the ith character
  FXchar& operator[](FXint i){ return str[i]; }

  /// Return a const reference to the ith character
  const FXchar& operator[](FXint i) const { return str[i]; }

  /// Return a non-const reference to the ith character
  FXchar& at(FXint i){ return str[i]; }

  /// Return a const reference to the ith character
  const FXchar& at(FXint i) const { return str[i]; }

  /// Return a non-const reference to the first character
  FXchar& head(){ return str[0]; }

  /// Return a const reference to the first character
  const FXchar& head() const { return str[0]; }

  /// Return a non-const reference to the last character
  FXchar& tail(){ return str[length()-1]; }

  /// Return a const reference to the last character
  const FXchar& tail() const { return str[length()-1]; }

  /// Return wide character starting at offset i
  FXwchar wc(FXint i) const;

  /// Assign a string to this
  FXString& operator=(const FXchar* s);

  /// Assign a wide character string to this
  FXString& operator=(const FXwchar* s);

  /// Assign a narrow character string to this
  FXString& operator=(const FXnchar* s);

  /// Assign another string to this
  FXString& operator=(const FXString& s);

  /// Convert to lower case
  FXString& lower();

  /// Convert to upper case
  FXString& upper();

  /// Return num partition(s) from a given start partition in a string separated by delimiters delim.
  FXString section(FXchar delim,FXint start,FXint num=1) const;

  /// Return num partition(s) from a given start partition in a string separated by set of delimiters from delim of size n
  FXString section(const FXchar* delim,FXint n,FXint start,FXint num) const;

  /// Return num partition(s) from a given start partition in a string separated by set of delimiters from delim.
  FXString section(const FXchar* delim,FXint start,FXint num=1) const;

  /// Return num partition(s) from a given start partition in a string separated by set of delimiters from delim.
  FXString section(const FXString& delim,FXint start,FXint num=1) const;

  /// Adopt string s, leaving s empty
  FXString& adopt(FXString& s);

  /// Assign character c to this string
  FXString& assign(FXchar c);

  /// Assign n characters c to this string
  FXString& assign(FXchar c,FXint n);

  /// Assign first n characters of string s to this string
  FXString& assign(const FXchar *s,FXint n);

  /// Assign first n characters of wide character string s to this string
  FXString& assign(const FXwchar *s,FXint n);

  /// Assign first n characters of narrow character string s to this string
  FXString& assign(const FXnchar *s,FXint n);

  /// Assign string s to this string
  FXString& assign(const FXchar* s);

  /// Assign wide character string s to this string
  FXString& assign(const FXwchar* s);

  /// Assign narrow character string s to this string
  FXString& assign(const FXnchar* s);

  /// Assign string s to this string
  FXString& assign(const FXString& s);

  /// Insert character at specified position
  FXString& insert(FXint pos,FXchar c);

  /// Insert n characters c at specified position
  FXString& insert(FXint pos,FXchar c,FXint n);

  /// Insert first n characters of string at specified position
  FXString& insert(FXint pos,const FXchar* s,FXint n);

  /// Insert first n characters of wide character string at specified position
  FXString& insert(FXint pos,const FXwchar* s,FXint n);

  /// Insert first n characters of narrow character string at specified position
  FXString& insert(FXint pos,const FXnchar* s,FXint n);

  /// Insert string at specified position
  FXString& insert(FXint pos,const FXchar* s);

  /// Insert wide character string at specified position
  FXString& insert(FXint pos,const FXwchar* s);

  /// Insert narrow character string at specified position
  FXString& insert(FXint pos,const FXnchar* s);

  /// Insert string at specified position
  FXString& insert(FXint pos,const FXString& s);

  /// Prepend string with input character
  FXString& prepend(FXchar c);

  /// Prepend string with n characters c
  FXString& prepend(FXchar c,FXint n);

  /// Prepend first n characters of string s
  FXString& prepend(const FXchar* s,FXint n);

  /// Prepend first n characters of wide character string s
  FXString& prepend(const FXwchar* s,FXint n);

  /// Prepend first n characters of narrow character string s
  FXString& prepend(const FXnchar* s,FXint n);

  /// Prepend string with string s
  FXString& prepend(const FXchar* s);

  /// Prepend string with wide character string
  FXString& prepend(const FXwchar* s);

  /// Prepend string with narrow character string
  FXString& prepend(const FXnchar* s);

  /// Prepend string with string s
  FXString& prepend(const FXString& s);

  /// Append character c to this string
  FXString& append(FXchar c);

  /// Append n characters c to this string
  FXString& append(FXchar c,FXint n);

  /// Append first n characters of string s to this string
  FXString& append(const FXchar* s,FXint n);

  /// Append first n characters of wide character string s to this string
  FXString& append(const FXwchar* s,FXint n);

  /// Append first n characters of narrow character string s to this string
  FXString& append(const FXnchar* s,FXint n);

  /// Append string s to this string
  FXString& append(const FXchar* s);

  /// Append wide character string s to this string
  FXString& append(const FXwchar* s);

  /// Append narrow character string s to this string
  FXString& append(const FXnchar* s);

  /// Append string s to this string
  FXString& append(const FXString& s);

  /// Replace a single character
  FXString& replace(FXint pos,FXchar c);

  /// Replace the m characters at pos with n characters c
  FXString& replace(FXint pos,FXint m,FXchar c,FXint n);

  /// Replaces the m characters at pos with first n characters of string s
  FXString& replace(FXint pos,FXint m,const FXchar* s,FXint n);

  /// Replaces the m characters at pos with first n characters of wide character string s
  FXString& replace(FXint pos,FXint m,const FXwchar* s,FXint n);

  /// Replaces the m characters at pos with first n characters of narrow character string s
  FXString& replace(FXint pos,FXint m,const FXnchar* s,FXint n);

  /// Replace the m characters at pos with string s
  FXString& replace(FXint pos,FXint m,const FXchar* s);

  /// Replace the m characters at pos with wide character string s
  FXString& replace(FXint pos,FXint m,const FXwchar* s);

  /// Replace the m characters at pos with narrow character string s
  FXString& replace(FXint pos,FXint m,const FXnchar* s);

  /// Replace the m characters at pos with string s
  FXString& replace(FXint pos,FXint m,const FXString& s);

  /// Move range of m characters from src position to dst position
  FXString& move(FXint dst,FXint src,FXint n);

  /// Remove one character
  FXString& erase(FXint pos);

  /// Remove substring
  FXString& erase(FXint pos,FXint n);

  /// Return number of occurrences of ch in string
  FXint contains(FXchar ch) const;

  /// Return number of occurrences of string sub in string
  FXint contains(const FXchar* sub,FXint n) const;

  /// Return number of occurrences of string sub in string
  FXint contains(const FXchar* sub) const;

  /// Return number of occurrences of string sub in string
  FXint contains(const FXString& sub) const;

  /// Substitute one character by another
  FXString& substitute(FXchar org,FXchar sub,FXbool all=true);

  /// Substitute one string by another
  FXString& substitute(const FXchar* org,FXint olen,const FXchar *rep,FXint rlen,FXbool all=true);

  /// Substitute one string by another
  FXString& substitute(const FXchar* org,const FXchar *rep,FXbool all=true);

  /// Substitute one string by another
  FXString& substitute(const FXString& org,const FXString& rep,FXbool all=true);

  /// Simplify whitespace in string
  FXString& simplify();

  /// Remove leading and trailing whitespace
  FXString& trim();

  /// Remove leading whitespace
  FXString& trimBegin();

  /// Remove trailing whitespace
  FXString& trimEnd();

  /// Truncate string at pos
  FXString& trunc(FXint pos);

  /// Clear
  FXString& clear();

  /// Get left most part
  FXString left(FXint n) const;

  /// Get right most part
  FXString right(FXint n) const;

  /// Get some part in the middle
  FXString mid(FXint pos,FXint n) const;

  /**
  * Return all characters before the n-th occurrence of ch,
  * searching from the beginning of the string. If the character
  * is not found, return the entire string.  If n<=0, return
  * the empty string.
  */
  FXString before(FXchar ch,FXint n=1) const;

  /**
  * Return all characters before the n-th occurrence of ch,
  * searching from the end of the string. If the character
  * is not found, return the empty string. If n<=0, return
  * the entire string.
  */
  FXString rbefore(FXchar ch,FXint n=1) const;

  /**
  * Return all characters after the nth occurrence of ch,
  * searching from the beginning of the string. If the character
  * is not found, return the empty string.  If n<=0, return
  * the entire string.
  */
  FXString after(FXchar ch,FXint n=1) const;

  /**
  * Return all characters after the nth occurrence of ch,
  * searching from the end of the string. If the character
  * is not found, return the entire string. If n<=0, return
  * the empty string.
  */
  FXString rafter(FXchar ch,FXint n=1) const;

  /// Find a character, searching forward; return position or -1
  FXint find(FXchar c,FXint pos=0) const;

  /// Find a character, searching backward; return position or -1
  FXint rfind(FXchar c,FXint pos=2147483647) const;

  /// Find n-th occurrence of character, searching forward; return position or -1
  FXint find(FXchar c,FXint pos,FXint n) const;

  /// Find n-th occurrence of character, searching backward; return position or -1
  FXint rfind(FXchar c,FXint pos,FXint n) const;

  /// Find a substring of length n, searching forward; return position or -1
  FXint find(const FXchar* substr,FXint n,FXint pos) const;

  /// Find a substring of length n, searching backward; return position or -1
  FXint rfind(const FXchar* substr,FXint n,FXint pos) const;

  /// Find a substring, searching forward; return position or -1
  FXint find(const FXchar* substr,FXint pos=0) const;

  /// Find a substring, searching backward; return position or -1
  FXint rfind(const FXchar* substr,FXint pos=2147483647) const;

  /// Find a substring, searching forward; return position or -1
  FXint find(const FXString& substr,FXint pos=0) const;

  /// Find a substring, searching backward; return position or -1
  FXint rfind(const FXString& substr,FXint pos=2147483647) const;

  /// Find first character in the set of size n, starting from pos; return position or -1
  FXint find_first_of(const FXchar* set,FXint n,FXint pos) const;

  /// Find first character in the set, starting from pos; return position or -1
  FXint find_first_of(const FXchar* set,FXint pos=0) const;

  /// Find first character in the set, starting from pos; return position or -1
  FXint find_first_of(const FXString& set,FXint pos=0) const;

  /// Find first character, starting from pos; return position or -1
  FXint find_first_of(FXchar c,FXint pos=0) const;

  /// Find last character in the set of size n, starting from pos; return position or -1
  FXint find_last_of(const FXchar* set,FXint n,FXint pos) const;

  /// Find last character in the set, starting from pos; return position or -1
  FXint find_last_of(const FXchar* set,FXint pos=2147483647) const;

  /// Find last character in the set, starting from pos; return position or -1
  FXint find_last_of(const FXString& set,FXint pos=2147483647) const;

  /// Find last character, starting from pos; return position or -1
  FXint find_last_of(FXchar c,FXint pos=0) const;

  /// Find first character NOT in the set of size n, starting from pos; return position or -1
  FXint find_first_not_of(const FXchar* set,FXint n,FXint pos) const;

  /// Find first character NOT in the set, starting from pos; return position or -1
  FXint find_first_not_of(const FXchar* set,FXint pos=0) const;

  /// Find first character NOT in the set, starting from pos; return position or -1
  FXint find_first_not_of(const FXString& set,FXint pos=0) const;

  /// Find first character NOT equal to c, starting from pos; return position or -1
  FXint find_first_not_of(FXchar c,FXint pos=0) const;

  /// Find last character NOT in the set of size n, starting from pos; return position or -1
  FXint find_last_not_of(const FXchar* set,FXint n,FXint pos) const;

  /// Find last character NOT in the set, starting from pos; return position or -1
  FXint find_last_not_of(const FXchar* set,FXint pos=2147483647) const;

  /// Find last character NOT in the set, starting from pos; return position or -1
  FXint find_last_not_of(const FXString& set,FXint pos=2147483647) const;

  /// Find last character NOT equal to c, starting from pos; return position or -1
  FXint find_last_not_of(FXchar c,FXint pos=0) const;

  /// Scan a string a-la scanf
  FXint scan(const FXchar* fmt,...) const FX_SCANF(2,3) ;
  FXint vscan(const FXchar* fmt,va_list args) const;

  /// Format a string a-la printf
  FXint format(const FXchar* fmt,...) FX_PRINTF(2,3) ;
  FXint vformat(const FXchar* fmt,va_list args);

  /// Convert to long integer
  FXlong toLong(FXint base=10) const;

  /// Convert to unsigned long integer
  FXulong toULong(FXint base=10) const;

  /// Convert to integer
  FXint toInt(FXint base=10) const;

  /// Convert to unsigned integer
  FXuint toUInt(FXint base=10) const;

  /// Convert to double
  FXdouble toDouble() const;

  /// Convert to float
  FXfloat toFloat() const;

  /// Convert from long integer
  FXString& fromLong(FXlong number,FXint base=10);

  /// Convert from unsigned long integer
  FXString& fromULong(FXulong number,FXint base=10);

  /// Convert from integer
  FXString& fromInt(FXint number,FXint base=10);

  /// Convert from unsigned integer
  FXString& fromUInt(FXuint number,FXint base=10);

  /// Convert from double
  FXString& fromDouble(FXdouble number,FXint prec=6,FXint fmt=2);

  /// Convert from float
  FXString& fromFloat(FXfloat number,FXint prec=6,FXint fmt=2);

  /**
  * Return a string value by converting an integer number to a string,
  * using the given number base, which must be between 2 and 16.
  */
  static FXString value(FXint num,FXint base=10);
  static FXString value(FXuint num,FXint base=10);

  /**
  * Return a string value by converting a long integer number to a string,
  * using the given number base, which must be between 2 and 16.
  */
  static FXString value(FXlong num,FXint base=10);
  static FXString value(FXulong num,FXint base=10);

  /**
  * Return a string value by converting real number to a string, using the given
  * procision and exponential notation mode, which may be 0 (never), 1 (always),
  * or 2 (when needed).
  */
  static FXString value(FXfloat num,FXint prec=6,FXint fmt=2);
  static FXString value(FXdouble num,FXint prec=6,FXint fmt=2);

  /**
  * Return a string value from printf-like format arguments.
  */
  static FXString value(const FXchar* fmt,...) FX_PRINTF(1,2) ;

  /**
  * Return a string value from vprintf-like format arguments.
  */
  static FXString vvalue(const FXchar* fmt,va_list args);

  /// Check if the string contains special characters or leading or trailing whitespace
  FXbool shouldEscape(FXchar lquote=0,FXchar rquote=0) const;

  /// Escape special characters, and optionally enclose with left and right quotes
  FXString& escape(FXchar lquote=0,FXchar rquote=0);

  /// Unescape special characters, and optionally remove left and right quotes
  FXString& unescape(FXchar lquote=0,FXchar rquote=0);

  /// Get hash value
  FXuint hash() const;

  /// Append operators
  FXString& operator+=(const FXString& s);
  FXString& operator+=(const FXchar* s);
  FXString& operator+=(const FXwchar* s);
  FXString& operator+=(const FXnchar* s);
  FXString& operator+=(FXchar c);

  /// Swap two strings
  friend inline void swap(FXString& a,FXString& b);

  /// Saving to a stream
  friend FXAPI FXStream& operator<<(FXStream& store,const FXString& s);

  /// Load from a stream
  friend FXAPI FXStream& operator>>(FXStream& store,FXString& s);

  /// Delete
 ~FXString();
  };


/// Swap two strings
inline void swap(FXString& a,FXString& b){ FXchar *t=a.str; a.str=b.str; b.str=t; }

/// Saving to a stream
extern FXAPI FXStream& operator<<(FXStream& store,const FXString& s);

/// Load from a stream
extern FXAPI FXStream& operator>>(FXStream& store,FXString& s);


/// Compare
extern FXAPI FXint compare(const FXchar* s1,const FXchar* s2);
extern FXAPI FXint compare(const FXchar* s1,const FXString& s2);
extern FXAPI FXint compare(const FXString& s1,const FXchar* s2);
extern FXAPI FXint compare(const FXString& s1,const FXString& s2);

/// Compare up to n
extern FXAPI FXint compare(const FXchar* s1,const FXchar* s2,FXint n);
extern FXAPI FXint compare(const FXchar* s1,const FXString& s2,FXint n);
extern FXAPI FXint compare(const FXString& s1,const FXchar* s2,FXint n);
extern FXAPI FXint compare(const FXString& s1,const FXString& s2,FXint n);

/// Compare case insensitive
extern FXAPI FXint comparecase(const FXchar* s1,const FXchar* s2);
extern FXAPI FXint comparecase(const FXchar* s1,const FXString& s2);
extern FXAPI FXint comparecase(const FXString& s1,const FXchar* s2);
extern FXAPI FXint comparecase(const FXString& s1,const FXString& s2);

/// Compare case insensitive up to n
extern FXAPI FXint comparecase(const FXchar* s1,const FXchar* s2,FXint n);
extern FXAPI FXint comparecase(const FXchar* s1,const FXString& s2,FXint n);
extern FXAPI FXint comparecase(const FXString& s1,const FXchar* s2,FXint n);
extern FXAPI FXint comparecase(const FXString& s1,const FXString& s2,FXint n);

/// Compare with numeric interpretation
extern FXAPI FXint compareversion(const FXchar* s1,const FXchar* s2);
extern FXAPI FXint compareversion(const FXchar* s1,const FXString& s2);
extern FXAPI FXint compareversion(const FXString& s1,const FXchar* s2);
extern FXAPI FXint compareversion(const FXString& s1,const FXString& s2);

/// Equality operators
extern FXAPI FXbool operator==(const FXString& s1,const FXString& s2);
extern FXAPI FXbool operator==(const FXString& s1,const FXchar* s2);
extern FXAPI FXbool operator==(const FXchar* s1,const FXString& s2);

/// Inequality operators
extern FXAPI FXbool operator!=(const FXString& s1,const FXString& s2);
extern FXAPI FXbool operator!=(const FXString& s1,const FXchar* s2);
extern FXAPI FXbool operator!=(const FXchar* s1,const FXString& s2);

/// Lexicographic less than operators
extern FXAPI FXbool operator<(const FXString& s1,const FXString& s2);
extern FXAPI FXbool operator<(const FXString& s1,const FXchar* s2);
extern FXAPI FXbool operator<(const FXchar* s1,const FXString& s2);

/// Lexicographic less than or equal operators
extern FXAPI FXbool operator<=(const FXString& s1,const FXString& s2);
extern FXAPI FXbool operator<=(const FXString& s1,const FXchar* s2);
extern FXAPI FXbool operator<=(const FXchar* s1,const FXString& s2);

/// Lexicographic greater than operators
extern FXAPI FXbool operator>(const FXString& s1,const FXString& s2);
extern FXAPI FXbool operator>(const FXString& s1,const FXchar* s2);
extern FXAPI FXbool operator>(const FXchar* s1,const FXString& s2);

/// Lexicographic greater than or equal operators
extern FXAPI FXbool operator>=(const FXString& s1,const FXString& s2);
extern FXAPI FXbool operator>=(const FXString& s1,const FXchar* s2);
extern FXAPI FXbool operator>=(const FXchar* s1,const FXString& s2);

/// Concatenate FXString and FXString
extern FXAPI FXString operator+(const FXString& s1,const FXString& s2);

/// Concatenate FXString and a string
extern FXAPI FXString operator+(const FXString& s1,const FXchar* s2);
extern FXAPI FXString operator+(const FXString& s1,const FXwchar* s2);
extern FXAPI FXString operator+(const FXString& s1,const FXnchar* s2);

/// Concatenate string and FXString
extern FXAPI FXString operator+(const FXchar* s1,const FXString& s2);
extern FXAPI FXString operator+(const FXwchar* s1,const FXString& s2);
extern FXAPI FXString operator+(const FXnchar* s1,const FXString& s2);

/// Concatenate string and single character
extern FXAPI FXString operator+(const FXString& s,FXchar c);
extern FXAPI FXString operator+(FXchar c,const FXString& s);

/// Return utf8 from ascii containing unicode escapes
extern FXAPI FXString fromAscii(const FXString& s);

/// Return ascii containing unicode escapes from utf8
extern FXAPI FXString toAscii(const FXString& s);

/// Return normalized string, i.e. reordering of diacritical marks
extern FXAPI FXString normalize(const FXString& s);

/// Return normalized decomposition of string
extern FXAPI FXString decompose(const FXString& s,FXuint kind);

/// Return normalized composition of string; this first performs normalized decomposition
extern FXAPI FXString compose(const FXString& s,FXuint kind);

/// Convert unix string to dos string
extern FXAPI FXString& unixToDos(FXString& str);

/// Convert dos string to unix string
extern FXAPI FXString& dosToUnix(FXString& str);

}

#endif
