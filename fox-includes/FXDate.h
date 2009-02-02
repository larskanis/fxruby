/********************************************************************************
*                                                                               *
*                            D a t e   C l a s s                                *
*                                                                               *
*********************************************************************************
* Copyright (C) 2005 by Jeroen van der Zijp.   All Rights Reserved.             *
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
* $Id: FXDate.h 2335 2006-01-28 02:33:03Z lyle $                             *
********************************************************************************/
#ifndef FXDATE_H
#define FXDATE_H

namespace FX {



/**
* Gregorian date object.
*/
class FXAPI FXDate {
private:
  FXuint julian;
private:
  static const FXchar shortMonthName[12][4];
  static const FXchar longMonthName[12][10];
  static const FXchar shortWeekDay[7][4];
  static const FXchar longWeekDay[7][10];
protected:
  static void greg2jul(FXuint& jd,FXint y,FXint m,FXint d);
  static void jul2greg(FXuint jd,FXint& y,FXint& m,FXint& d);
public:

  /// Names for the months
  enum {
    Jan=1,Feb,Mar,Apr,May,Jun,Jul,Aug,Sep,Oct,Nov,Dec
    };

  /// Names for the weekdays
  enum {
    Sun=0,Mon,Tue,Wed,Thu,Fri,Sat
    };

public:

  /// Default constructor
  FXDate(){}

  /// Copy constructor
  FXDate(const FXDate& date):julian(date.julian){}

  /// Initialize with year, month, and day
  FXDate(FXint y,FXint m,FXint d);

  /// Initialize with julian day number
  FXDate(FXuint j):julian(j){}

  /// Set julian day number
  void setJulian(FXuint day){ julian=day; }

  /// Get julian day number
  FXuint getJulian() const { return julian; }

  /// Set to year, month, and day
  void setDate(FXint y,FXint m,FXint d);

  /// Get year, month, and day
  void getDate(FXint& y,FXint& m,FXint& d) const;

  /// Return day of the month
  FXint day() const;

  /// Return month
  FXint month() const;

  /// Return year
  FXint year() const;

  /// Return day of the week
  FXint dayOfWeek() const;

  /// Return day of year
  FXint dayOfYear() const;

  /// Return days in this month
  FXint daysInMonth() const;

  /// Return true if leap year
  bool leapYear() const;

  /// Is the value a leap year
  static bool leapYear(FXint y);

  /// Get the name of the month
  static const FXchar *monthName(FXint month){ return longMonthName[month-1]; }

  /// Get the abbreviated name of the month
  static const FXchar *monthNameShort(FXint month){ return shortMonthName[month-1]; }

  /// Get the name of the day
  static const FXchar *dayName(FXint day){ return longWeekDay[day]; }

  /// Get the abbreviated name of the day
  static const FXchar *dayNameShort(FXint day){ return shortWeekDay[day]; }

  /// Return current local date
  static FXDate localDate();

  /// Return current UTC (Zulu) date
  static FXDate zuluDate();

  /// Assignment
  FXDate& operator=(const FXDate& date){julian=date.julian;return *this;}

  /// Assignment operators
  FXDate& operator+=(FXint x){ julian+=x; return *this; }
  FXDate& operator-=(FXint x){ julian-=x; return *this; }

  /// Increment and decrement
  FXDate& operator++(){ julian++; return *this; }
  FXDate& operator--(){ julian--; return *this; }

  /// Equality tests
  bool operator==(const FXDate& date) const { return julian==date.julian;}
  bool operator!=(const FXDate& date) const { return julian!=date.julian;}

  /// Inequality tests
  bool operator<(const FXDate& date) const { return julian<date.julian;}
  bool operator<=(const FXDate& date) const { return julian<=date.julian;}
  bool operator>(const FXDate& date) const { return julian>date.julian;}
  bool operator>=(const FXDate& date) const { return julian>=date.julian;}

  /// Add days to date yielding another date
  friend inline FXDate operator+(const FXDate& d,FXint x);
  friend inline FXDate operator+(FXint x,const FXDate& d);

  /// Substract dates yielding days
  friend inline FXint operator-(const FXDate& a,const FXDate& b);

  /// save to stream
  friend FXAPI FXStream& operator<<(FXStream& store,const FXDate& d);

  /// load from stream
  friend FXAPI FXStream& operator>>(FXStream& store,FXDate& d);
  };


inline FXDate operator+(const FXDate& d,FXint x){ return FXDate(d.julian+x); }
inline FXDate operator+(FXint x,const FXDate& d){ return FXDate(x+d.julian); }
inline FXint operator-(const FXDate& a,const FXDate& b){return a.julian-b.julian; }

extern FXAPI FXStream& operator<<(FXStream& store,const FXDate& d);
extern FXAPI FXStream& operator>>(FXStream& store,FXDate& d);

}

#endif
