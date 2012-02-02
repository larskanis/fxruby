/********************************************************************************
*                                                                               *
*                            D a t e   C l a s s                                *
*                                                                               *
*********************************************************************************
* Copyright (C) 2005,2007 by Jeroen van der Zijp.   All Rights Reserved.        *
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
* $Id: FXDate.h 2727 2007-11-16 17:28:42Z lyle $                            *
********************************************************************************/
#ifndef FXDATE_H
#define FXDATE_H

namespace FX {



/**
* Gregorian date class, which is useful for calendrical calculations.
*/
class FXAPI FXDate {
private:
  FXuint julian;
private:
  static const FXchar shortMonthName[12][4];
  static const FXchar longMonthName[12][10];
  static const FXchar shortWeekDay[7][4];
  static const FXchar longWeekDay[7][10];
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

  /// Initialize with julian day number
  FXDate(FXuint jd):julian(jd){}

  /// Initialize with year and day of year
  FXDate(FXint yr,FXint dy);

  /// Initialize with year, month, and day of month
  FXDate(FXint yr,FXint mo,FXint dy);

  /// Set julian day number
  void setJulian(FXuint jd){ julian=jd; }

  /// Get julian day number
  FXuint getJulian() const { return julian; }

  /// Set date to year and day of year
  void setDate(FXint yr,FXint dy);

  /// Get year and day of year from date
  void getDate(FXint& yr,FXint& dy) const;

  /// Set date to year, month, and day of month
  void setDate(FXint yr,FXint mo,FXint dy);

  /// Get year, month, and day of month from date
  void getDate(FXint& yr,FXint& mo,FXint& dy) const;

  /// Set date from nanoseconds since 1/1/1970
  void setTime(FXTime ns);

  /// Get nanoseconds since 1/1/1970 from date
  FXTime getTime() const;

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

  /// Return ISO8601 week number of this date
  FXint weekOfYear() const;

  /// Return true if this is a leap year
  FXbool leapYear() const;

  /// Return number of days in this year
  FXint daysInYear() const;

  /// Return days in this month
  FXint daysInMonth() const;

  /// Add d days to this date
  FXDate& addDays(FXint d);

  /// Add m months to this date; day of month is adjusted for leap-years
  FXDate& addMonths(FXint m);

  /// Add y years to this date; day of month is adjusted for leap-years
  FXDate& addYears(FXint y);

  /// Is the value a leap year
  static FXbool leapYear(FXint yr);

  /// Return number of days in a given year
  static FXint daysInYear(FXint yr);

  /// Return number of days in the month in given year, month
  static FXint daysInMonth(FXint yr,FXint mo);

  /// Get the name of the month
  static const FXchar *monthName(FXint mo){ return longMonthName[mo-1]; }

  /// Get the abbreviated name of the month
  static const FXchar *monthNameShort(FXint mo){ return shortMonthName[mo-1]; }

  /// Get the name of the day
  static const FXchar *dayName(FXint dy){ return longWeekDay[dy]; }

  /// Get the abbreviated name of the day
  static const FXchar *dayNameShort(FXint dy){ return shortWeekDay[dy]; }

  /// Return current local date
  static FXDate localDate();

  /// Return current universal (UTC) date
  static FXDate universalDate();

  /// Assignment
  FXDate& operator=(const FXDate& date){julian=date.julian;return *this;}

  /// Assignment operators
  FXDate& operator+=(FXint x){ julian+=x; return *this; }
  FXDate& operator-=(FXint x){ julian-=x; return *this; }

  /// Pre-Increment and decrement
  FXDate& operator++(){ ++julian; return *this; }
  FXDate& operator--(){ --julian; return *this; }

  /// Post-Increment and decrement
  FXDate operator++(int){ FXDate t(julian++); return t; }
  FXDate operator--(int){ FXDate t(julian--); return t; }

  /// Equality tests
  FXbool operator==(const FXDate& date) const { return julian==date.julian;}
  FXbool operator!=(const FXDate& date) const { return julian!=date.julian;}

  /// Inequality tests
  FXbool operator<(const FXDate& date) const { return julian<date.julian;}
  FXbool operator<=(const FXDate& date) const { return julian<=date.julian;}
  FXbool operator>(const FXDate& date) const { return julian>date.julian;}
  FXbool operator>=(const FXDate& date) const { return julian>=date.julian;}

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
