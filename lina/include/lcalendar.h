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

#ifndef LCALENDAR_H
#define LCALENDAR_H

#include <boost/rational.hpp>
#include <time.h>
#include <string>
#include <ldatabase.h>
#include <lutility.h>
#include <lrange.h>
#include <list>

class LTimePeriod;

/// Time and date class.
/** LTime is LINA's time and date type and designed
    for the needs of LINA.*/
class LTime
{
  friend std::ostream &operator<<(std::ostream&, const LTimePeriod&);
  friend std::istream &operator>>(std::istream& is, LTimePeriod&);
  friend std::ostream &operator<<(std::ostream&, const LTime&);
  friend std::istream &operator>>(std::istream& is, LTime&);

  friend bool operator<(const LTime& lhs, const LTime& rhs);
  friend bool operator>(const LTime& lhs, const LTime& rhs);

  friend bool operator>=(const LTime& lhs, const LTime& rhs);
  friend bool operator==(const LTime& lhs, const LTime& rhs);

public:
  /// Default constructor
  LTime() : seconds(0), julian(0) {};
  /// Copy constructor
  LTime(const LTime& ltime);
  /// Constructor
  LTime(int year, int month, int day, int hour, int minute, int second);
  /// Constructor
  LTime(int year, int month, int day);
  /*/// Constructor
  LTime(int year, int week, int weekday);*/
  /// Constructor
  /** Takes a struct tm object*/
  LTime(struct tm *dt);
  /// Constructor
  /** Takes a time_t object*/
  LTime(time_t time);

  /// Set year, month and day
  bool SetYMD( int year, int month, int day );
  /// Set hour, minute and second
  bool SetHMS( int hour, int minute, int second );
  /// Set year, week and (week)-day
  bool SetYWD( int year, int week, int weekday);

  /// Get year
  int Year() const;
  /// Get month
  int Month() const;
  /// Get day
  int Day() const;
  /// Get days in current month
  int DaysInMonth() const;
  /// Add days
  void AddDays(int days);
  /// Add weeks
  void AddWeeks(int weeks);
  /// Add months
  void AddMonths(int months);
  /// Add years
  void AddYears(int years);

  /// Get hour
  int Hour() const;
  /// Get minute
  int Minute() const;
  /// Get second
  int Second() const;
  /// Add seconds
  void AddSeconds(int days);
  /// Add minutes
  void AddMinutes(int months);
  /// Add hours
  void AddHours(int years);

  /// Is this year, month and day combination valid?
  bool IsValidDate(int year, int month, int day);
  /// Is the current year, month and day combination valid?
  bool IsValidDate() const;
  /// Is this hour, minute and second combination valid?
  bool IsValidTime(int hour, int minute, int second);
  /// Is the current hour, minute and second combination valid?
  bool IsValidTime() const;
  /// Is this year a leap year?
  bool LeapYear(int year) const;
  
  /// Days to a certain time.
  int DaysTo(const LTime& to);
  /// Seconds to a certain time.
  int SecondsTo(const LTime& to);
  
private:
  // Convert hour, minute and second to seconds
  void ToSeconds(int hour, int minute, int second)
  { seconds = 3600 * hour + 60 * minute + second; }
  // Convert year, month and day to julian day
  void ToJulian(int year, int month, int day);
  // Convert the current julian day to year, month and day
  void ToGregorian(int& year, int& month, int& day) const;

  // static const members
  static const short month_days[];
  static const int first_gregorian_year;
  static const uint seconds_per_day;
  static const uint first_day;

  // julian day
  unsigned long julian;
  // seconds (in one day)
  unsigned long seconds;
  
  boost::rational<int> asdf;
};

/// Represents a time period.
/** This class holds a start and an end time.
    It provides some manipulation functions.*/
class LTimePeriod
{
  /// Operators << and >>.
  /** Makes `cout' and `cin' operations
      possible with LRange. */
  friend std::ostream &operator<<(std::ostream&, const LTimePeriod&);
  friend std::istream &operator>>(std::istream& is, LTimePeriod&);

public:
  LTimePeriod(const LTime& tp_start,const LTime& tp_end) : start(tp_start),end(tp_end) {};

  LTime start;
  LTime end;

};

/// Represents an event.
/** An event is a time period, that is connected with a certain lid
    and another id, which represents the real event.*/
class LEvent : public LTimePeriod
{

  friend std::ostream &operator<<(std::ostream&, const LEvent&);
  friend std::istream &operator>>(std::istream& is, LEvent&);

  friend bool operator<(const LEvent& lhs, const LEvent& rhs);
  friend bool operator>(const LEvent& lhs, const LEvent& rhs);

public:

  // Forward declaration of structure LEventID
  struct LEventID;

  /// Constructor.
  LEvent(const LTime& tp_start,const LTime& tp_end,const LEventID& event_id) : LTimePeriod(tp_start,tp_end),event_id(event_id)  { }
  /// Copy constructor.
  LEvent(const LEvent& levent) : LTimePeriod(levent.start,levent.end),event_id(levent.event_id)
  {}
  /// Destructor.
  ~LEvent() {}
  /// Get event ID.
  int EventID() const { return event_id.id; }
  /// Get event LID.
  LID EventLID() const { return *event_id.lid; }

  /// A structure  to store an event id/lid
  struct LEventID
  {
    LEventID(const LEventID& leventid) : lid(*leventid.lid), id(leventid.id) {}
    LEventID(const LID& _lid, int _id) :lid(_lid),id(_id) {};
    LPtr<LID> lid;
    int id;
  };

private:
  // private LEventID
  LEventID event_id;
};

typedef LEvent::LEventID LEventID;

class LEventInterface
{

public:
  virtual void HandleEvent(const LEvent& levent) = 0;

};

enum EventStatusEnum { EventNotStarted, EventStart, EventOngoing, EventEnd, EventFinished};

/// Controls events.
class LCalendar : public LDatabaseInterface
{
public:
  LCalendar(const LID& lid) : LDatabaseInterface(lid) {};
  LCalendar(const LID& lid,const LTime& cur) : LDatabaseInterface(lid) { MakeLazy(&current_time); current_time = cur; };
  virtual void Save() const;

  /// Return pointer to next event
  LEvent* NextEvent()
  {
    return const_cast<LEvent*>(&(*event_list.begin()));
  }

  /// Return the current calendar time
  LTime CurrentTime() { LazyGet("current_time",current_time); return current_time; };
  bool InsertEvent(const LEvent& event)
  {
    event_list.insert(event);
  }
  void TakeEvent(const LEvent& event);

  /// Returns the event status of an event 
  EventStatusEnum EventStatus(const LEvent& event) const;


private:
  void TakeOldEvents();

  std::set<LEvent> event_list;
  LTime current_time;
};

#endif //LCALENDAR_H
