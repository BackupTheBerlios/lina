/***************************************************************************
 *   Copyright (C) 2003 by Tobias Glaesser                                 *
 *   tobi.web@gmx.de                                                       *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include <lcalendar.h>

using namespace std;

bool LINA::operator<(const LINA::Time& lhs, const LINA::Time& rhs) { return ( lhs.julian < rhs.julian || (lhs.julian == rhs.julian && lhs.seconds < rhs.seconds)); };
bool LINA::operator>(const LINA::Time& lhs, const LINA::Time& rhs) { return ( lhs.julian > rhs.julian || (lhs.julian == rhs.julian && lhs.seconds > rhs.seconds)); };

bool LINA::operator>=(const LINA::Time &lhs, const LINA::Time& rhs)
{
  return (lhs.julian > rhs.julian || (lhs.julian == rhs.julian && lhs.seconds >= rhs.seconds));
}

bool LINA::operator==(const LINA::Time &lhs, const LINA::Time& rhs)
{
  return (lhs.julian == rhs.julian && lhs.seconds == rhs.seconds);
}


bool LINA::operator<(const LINA::Event& lhs, const LINA::Event& rhs) { return ( lhs.start < rhs.start); };
bool LINA::operator>(const LINA::Event& lhs, const LINA::Event& rhs) { return ( lhs.start > rhs.start); };

const short LINA::Time::month_days[] =
  {
    0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
  };
const int LINA::Time::first_gregorian_year	= 1752;
const uint LINA::Time::seconds_per_day	= 86400;
const uint LINA::Time::first_day	= 2361222;

std::ostream& LINA::operator<<(std::ostream& os, const LINA::Time& rv)
{
  return os << rv.julian << " " << rv.seconds;
}

std::istream& LINA::operator>>(std::istream& is, LINA::Time& rv)
{
  return is >> rv.julian >> rv.seconds;
}

std::ostream& LINA::operator<<(std::ostream& os, const LINA::Event& rv)
{
  return os << static_cast<LINA::TimePeriod&>(const_cast<LINA::Event&>(rv)) << " " << *rv.event_id.lid << " " << rv.event_id.id;
}

std::istream& LINA::operator>>(std::istream& is, LINA::Event& rv)
{
  return is >> static_cast<LINA::TimePeriod&>(rv) >> *rv.event_id.lid >> rv.event_id.id;
}

LINA::Time::Time(const LINA::Time& ltime)
{
  julian = ltime.julian;
  seconds = ltime.seconds;
}

LINA::Time::Time(struct tm *dt)
{
  ToSeconds(dt->tm_hour, dt->tm_min, dt->tm_sec);
  ToJulian(dt->tm_year, dt->tm_mon, dt->tm_mday);
}

LINA::Time::Time(time_t time)
{
  struct tm *dt = localtime(&time);
  ToSeconds(dt->tm_hour, dt->tm_min, dt->tm_sec);
  ToJulian(dt->tm_year + 1900, dt->tm_mon + 1, dt->tm_mday);
}

LINA::Time::Time(int year, int month, int day, int hour, int minute, int second) : seconds(0), julian(0)
{
  SetYMD( year, month, day );
  SetHMS( hour, minute, second );
}

LINA::Time::Time(int year, int month, int day) : seconds(0), julian(0)
{
  SetYMD( year, month, day );
  
  asdf = 1;
  asdf.numerator();
}

/*LINA::Time::Time(int year, int week, int weekday) : seconds(0), julian(0)
{
  SetYMD( year, week, weekday );
}*/

bool LINA::Time::SetYMD( int year, int month, int day )
{
  if ( Year() == year && Month() == month && Day() == day )
    return IsValidDate();
  if ( !IsValidDate(year,month,day) )
  {
    return false;
  }
  ToJulian( year, month, day );
  return true;
}

bool LINA::Time::SetHMS( int hour, int minute, int second)
{
  if ( !IsValidTime(hour,minute,second) )
  {
    seconds = seconds_per_day;		// make this invalid
    return false;
  }
  seconds = hour*3600 + minute*60;
  return true;
}

bool LINA::Time::SetYWD( int year, int week, int weekday)
{
ToJulian(year,1,1);
}

int LINA::Time::DaysInMonth() const
{
  int y, m, d;
  ToGregorian( y, m, d );
  if ( m == 2 && LeapYear(y) )
    return 29;
  else
    return month_days[m];
}

void LINA::Time::AddDays(int days)
{
  julian += days;
}

void LINA::Time::AddWeeks(int weeks)
{
  julian += weeks*7;
}

void LINA::Time::AddMonths(int months)
{
  int y, m, d;
  ToGregorian( y, m, d );

  if(months != 0)
  {
    int ny = months/12;
    y += ny;
    m += months%12;
    if(m > 12)
    {
      ++y;
      m -= 12;
    }
    else if(m < 1)
    {
      --y;
      m += 12;
    }
  }

  if( d > LINA::Time(y,m,1).DaysInMonth() )
    d = LINA::Time(y,m,1).DaysInMonth();

  ToJulian(y,m,d);

}

void LINA::Time::AddYears(int years)
{
  int y, m, d;
  ToGregorian( y, m, d );
  y += years;


  if( d > LINA::Time(y,m,1).DaysInMonth() )
    d = LINA::Time(y,m,1).DaysInMonth();

  ToJulian(y,m,d);
}

void LINA::Time::AddSeconds(int secs)
{
  if ( secs < 0 )
  {
    // % not well-defined for -ve, but / is.
    int negdays = (seconds_per_day-secs) / seconds_per_day;
    seconds = ((int)seconds + secs + negdays*seconds_per_day)
              % seconds_per_day;
  }
  else
  {
    seconds = ((int)seconds + secs) % seconds_per_day;
  }
}

void LINA::Time::AddMinutes(int mins)
{
  AddSeconds(mins*60);
}

void LINA::Time::AddHours(int hours)
{
  AddSeconds(hours*3600);
}

int LINA::Time::Year() const
{
  int y, m, d;
  ToGregorian( y, m, d );
  return y;
}

int LINA::Time::Month() const
{
  int y, m, d;
  ToGregorian( y, m, d );
  return m;
}

int LINA::Time::Day() const
{
  int y, m, d;
  ToGregorian( y, m, d );
  return d;
}

int LINA::Time::Hour() const
{
  return seconds / 3600;
}

int LINA::Time::Minute() const
{
  return (seconds % 3600)/60;
}

int LINA::Time::Second() const
{
  return seconds % 60;
}

bool LINA::Time::IsValidDate( int year, int month, int day )
{
  if ( year >= 0 && year <= 99 )
    year += 1900;
  else if ( year < first_gregorian_year || (year == first_gregorian_year && (month < 9 ||
            (month == 9 && day < 14))) )
    return false;
  return (day > 0 && month > 0 && month <= 12) &&
         (day <= month_days[month] || (day == 29 && month == 2 && LeapYear(year)));
}

bool LINA::Time::IsValidDate() const
{
  return julian >= first_day;
  static const uint FIRST_DAY	= 2361222;	// Julian day for 1752-09-14
}

bool LINA::Time::IsValidTime() const
{
  return seconds < seconds_per_day;
}

bool LINA::Time::IsValidTime( int hour, int minute, int second )
{
  return (uint)hour < 24 && (uint)minute < 60 && (uint)second < 60;
}

bool LINA::Time::LeapYear( int year ) const
{
  return year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
}

int LINA::Time::SecondsTo(const LINA::Time& to)
{
return to.seconds - seconds;
}

int LINA::Time::DaysTo(const LINA::Time& to)
{
return to.julian - julian;
}

void LINA::Time::ToJulian(int year, int month, int day)
{
  unsigned long c, ya;
  if ( year <= 99 )
    year += 1900;
  if ( month > 2 )
  {
    month -= 3;
  }
  else
  {
    month += 9;
    year--;
  }
  c = year;					// NOTE: Sym C++ 6.0 bug
  c /= 100;
  ya = year - 100*c;
  julian = 1721119 + day + (146097*c)/4 + (1461*ya)/4 + (153*month+2)/5;
}

void LINA::Time::ToGregorian(int &year, int &month, int &day ) const
{
  uint x;
  uint j = julian - 1721119;
  year = (j*4 - 1)/146097;
  j = j*4 - 146097*year - 1;
  x = j/4;
  j = (x*4 + 3) / 1461;
  year = 100*year + j;
  x = (x*4) + 3 - 1461*j;
  x = (x + 4)/4;
  month = (5*x - 3)/153;
  x = 5*x - 3 - 153*month;
  day = (x + 5)/5;
  if ( month < 10 )
  {
    month += 3;
  }
  else
  {
    month -= 9;
    year++;
  }
}

std::ostream& LINA::operator<<(std::ostream& os, const LINA::TimePeriod& rv)
{
  return os << rv.start << " " << rv.end;
}

std::istream& LINA::operator>>(std::istream& is, LINA::TimePeriod& rv)
{
  return is >> rv.start >> rv.end;
}

void LINA::Calendar::Save() const
  {}

LINA::EventStatusEnum LINA::Calendar::EventStatus(const LINA::Event& event) const
{
  if( current_time > event.start)
    return EventNotStarted;
  else if ( current_time == event.start)
    return EventStart;
  else if ( current_time > event.start && current_time < event.end )
    return EventOngoing;
  else if ( current_time == event.end)
    return EventEnd;
  else if ( current_time > event.end)
    return EventFinished;
}

void LINA::Calendar::TakeOldEvents()
{
  for(std::set<LINA::Event>::iterator it = event_list.begin(); it != event_list.end(); ++it)
    {
      if((*it).start >= current_time)
      {
        --it;
        for(std::set<LINA::Event>::iterator s_it = event_list.begin(); s_it != it; ++s_it)
          {
            if((*s_it).end < current_time)
            {
              event_list.erase(s_it);
            }
          }
        break;
      }
    }
};
