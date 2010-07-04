// ------------------------
// projects/c++/date/Date.h
// Copyright (C) 2010
// Glenn P. Downing
// ------------------------

#ifndef Date_h
#define Date_h

// --------
// includes
// --------

#include <cassert>   // assert
#include <iostream>  // ostream
#include <stdexcept> // invalid_argument
#include <utility>   // !=, <=, >, >=



const int monthDaysSum[] = {0,0,31,59,90,120,151,181,212,243,273,304,334};
const int monthDays[] =      {0,31,28,31,30, 31, 30, 31, 31, 30, 31, 30, 31};
const int leapMonthDays[] =  {0,31,29, 31,30, 31, 30, 31, 31, 30, 31, 30, 31};
const std::string monthNames[] = {"Pad","Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};

/*
namespace std     {
namespace rel_ops {

template <typename T>
inline bool operator != (const T& lhs, const T& rhs) {
    return !(lhs == rhs);}

template <typename T>
inline bool operator <= (const T& lhs, const T& rhs) {
    return !(rhs < lhs);}

template <typename T>
inline bool operator > (const T& lhs, const T& rhs) {
    return (rhs < lhs);}

template <typename T>
inline bool operator >= (const T& lhs, const T& rhs) {
    return !(lhs < rhs);}

} // rel_ops
} // std;
*/

// -----
// using
// -----

using namespace std::rel_ops;

// ----
// Date
// ----

template <typename T>
class Date {
        
        // helper structure 
        struct DateParts
        {
            int month;
            int day;
            T year;
        };
        
    public:
        // ----------
        // operator +
        // ----------

        /**
         * @return a new Date computed by adding a given number of days to the original date.
         * @throws invalid_argument if the resulting date precedes 1 Jan 1600
         */
        friend Date operator + (Date lhs, const T& rhs) {
            return lhs += rhs;}

        /**
         * @return a new Date computed by adding a given number of days to the original date.
         * @throws invalid_argument if the resulting date precedes 1 Jan 1600
         */
        friend Date operator + (const T& lhs, Date rhs) {
            return rhs += lhs;}

        // ----------
        // operator -
        // ----------

        /**
         * @return a new Date computed by subtracting the given number of days from the given Date.
         * @throws invalid_argument if the resulting date precedes 1 Jan 1600
         */
        friend Date operator - (Date lhs, const T& rhs) {
            return lhs -= rhs;}

        // -----------
        // operator <<
        // -----------

        /**
         * @param  lhs an ostream
         * @param  rhs a date
         * @return the ostream
         * output a string representation of the date (e.g. "3 Feb 2008")
         */
        friend std::ostream& operator << (std::ostream& lhs, const Date& rhs) {
            DateParts d = rhs.to_date();
            return lhs<<d.day << " " << monthNames[d.month] <<" "<< d.year ;
        }

    private:
        // ----
        // data
        // ----

        T days;
        
    private:
        // -----
        // valid
        // -----

        /**
         * @return true if current date is valid.
         */
        bool valid () const {
            return days >= 0;}

        // -----------
        // constructor
        // -----------

        /**
         * @param days >= 0
         * Date(0) -> 1 Jan 1600
         */
        Date (const T& days) {
            assert(days >= 0);
            this->days = days;
            if (!valid())
                throw std::invalid_argument("Date::Date()");}

        // -------
        // to_days
        // -------

        /**
         * @return the number of days since 1 Jan 1600, >= 0
         * 1 Jan 1600 -> 0
         */
        T to_days () const {
            assert(valid());
            return days;}
            
        /**
         * @return DateParts representation of current date
         * helps with printing and answering questions about leap year status of current date.
         */
        DateParts to_date () const {
            DateParts result;
            result.day = 1;
            result.year = 1600;
            result.month = 1;
            T tempDays = days+1;
            
            while((tempDays>=366 && (result.year%4 == 0 && (result.year%400== 0 || result.year%100!=0))) || tempDays>=365)
            {
                tempDays-= ((result.year%4 == 0 && (result.year%400== 0 || result.year%100!=0))) ? 366 : 365;
                result.year++;
            }
            bool isLeapYear =((result.year%4 == 0 && (result.year%400== 0 || result.year%100!=0)));
            while((tempDays > monthDays[result.month] && !isLeapYear) || (tempDays > leapMonthDays[result.month] && isLeapYear))
            {
                tempDays-= isLeapYear ? leapMonthDays[result.month] : monthDays[result.month];
                ++result.month;
            }
            result.day=tempDays;
            return result;
        }

    public:
        // -----------
        // constructor
        // -----------

        /**
         * @param  day   >= 1 && <= 31
         * @param  month >= 1 && <= 1(year%100 !=0 || year%400 == 0)) && month==2 && day <=29)2
         * @param  year  >= 1600
         * @throws invalid_argument if the resulting date is invalid
         */
        Date (const T& day, const T& month, const T& year) : days(0){
        	using namespace std;

        	bool isLeapYear = (year% 4 == 0 && (year%100 !=0 || year%400 == 0));
        	if(year >= 1600 && month > 0 && month < 13 && day >=1)
        	{

				if(day <= monthDays[month] || (isLeapYear && month==2 && day<=29)) 
				{
					days+=day-1;
					days+=monthDaysSum[month];
					if(isLeapYear && month>2)   //passed leap day in the current year
					   ++days;
				}
				else
				{
					throw std::invalid_argument("Date::Date()");
				}
				
				int x400 = (year - 1600) / 400;
				days += 97*x400;

				int x100 = (year - 1600-x400*400) / 100;
				days +=  x100>0 ? 1 + 24*x100 : 0;

				int x4 = (year - 1600-x400*400 - x100*100) / 4;
				int modx4 = (year - 1600-x400*400 - x100*100) % 4;

				if((1600 + x400*400 + x100*100) % 100 == 0 && 
				    (1600 + x400*400 + x100*100) % 400 != 0  && x4>0) 
				    x4--; //decrement if first 4 grouping starts on non leap year.

				days += x4;
                
                int wasYear = year - modx4; 
                bool wasLeapYear = (modx4 >= 1) && (wasYear%4 == 0 && (wasYear%100 != 0 || wasYear%400 == 0));

				if(wasLeapYear)
				{
					++days; 
				}
                
				days+=(year-1600)*365;
        	}
        	else
        	{
        		throw std::invalid_argument("Date::Date()");
        	}
            assert(valid());
        }

        // Default copy, destructor, and copy assignment.
        // Date (const Date&);
        // ~Date ();
        // Date& operator = (const Date&);

        // -----------
        // operator ==
        // -----------

        /**
         * @param rhs Date object to comapre with
         * @return true if the two dates are the same
         */
        bool operator == (const Date& rhs) const {
            return this->days == rhs.days;}

        // ----------
        // operator <
        // ----------

        /**
         * @param rhs Date object to compare with
         * @return true if "this" date is futher in the past then rhs
         */
        bool operator < (const Date& rhs) const {
            return this->days < rhs.days;}

        // -----------
        // operator +=
        // -----------

        /**
         * Add the given days to "this" date.
         * @param  days the number of days to add (may be negative!)
         * @return the date resulting from adding days
         * @throws invalid_argument if the resulting date precedes 1 Jan 1600
         */
        Date& operator += (const T& days) {
            if(this->days + days < 0)
        		throw std::invalid_argument("Date::+=");
        	this->days += days;
            return *this;}

        // -----------
        // operator -=
        // -----------

        /**
         * Subtract the given days from "this" date.
         * @param  days the number of days to subtract (may be negative!)
         * @returif (!valid())
                throw std::n the date resulting from subtracting days
         * @throws invalid_argument if the resulting date precedes 1 Jan 1600
         */
        Date& operator -= (const T& days) {
            if(this->days - days < 0)
        		throw std::invalid_argument("Date::-=");
        	this->days -= days;
            return *this;}

        // ----------
        // operator -
        // ----------

        /**
         * @return the number of days between the dates (lhs - rhs)
         */
        T operator - (const Date& rhs) const {
            return this->days - rhs.days;}

        // --------
        // get_days
        // --------
        /**
         * @ return the number of days from 1,1,1600 to current date
         */
        T get_days() const
        {
            return to_days();
        }

        // ---------
        // leap_year
        // ---------

        /**
         * @return true if current date is leap year, false otherwise
         */
        bool leap_year () const {
            int year = to_date().year;
            return (year% 4 == 0 && (year%100 !=0 || year%400 == 0));
            }};

#endif // Date_h
