// boost_date.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

// Copyright (c) 2015
// Author: Chrono Law

#include <cassert>
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <algorithm>

using namespace std;

//#define DATE_TIME_NO_DEFAULT_CONSTRUCTOR
#include <boost/date_time/gregorian/gregorian.hpp>
using namespace boost::gregorian;

//////////////////////////////////////////


//////////////////////////////////////////
void case11()
{
	date_period dp(date(2017, 1, 1), days(20));

	dp.shift(days(3));
	assert(dp.begin().day() == 4);
	assert(dp.length().days() == 20);

	dp.expand(days(3));
	assert(dp.begin().day() == 1);
	assert(dp.length().days() == 26);

}

//////////////////////////////////////////

void case12()
{
	date_period dp(date(2010, 1, 1), days(20));

	assert(dp.is_after(date(2009, 12, 1)));
	assert(dp.is_before(date(2010, 2, 1)));
	assert(dp.contains(date(2010, 1, 10)));

	date_period dp2(date(2010, 1, 5), days(10));
	assert(dp.contains(dp2));

	assert(dp.intersects(dp2));
	assert(dp.intersection(dp2) == dp2);

	date_period dp3(date(2010, 1, 21), days(5));
	assert(!dp3.intersects(dp2));
	assert(dp3.intersection(dp2).is_null());

	assert(dp.is_adjacent(dp3));
	assert(!dp.intersects(dp3));

}

//////////////////////////////////////////
void case13()
{
	date_period dp1(date(2010, 1, 1), days(20));
	date_period dp2(date(2010, 1, 5), days(10));
	date_period dp3(date(2010, 2, 1), days(5));
	date_period dp4(date(2010, 1, 15), days(10));

	assert(dp1.contains(dp2) && dp1.merge(dp2) == dp1);
	assert(!dp1.intersects(dp3) && dp1.merge(dp3).is_null());
	assert(dp1.intersects(dp2) && dp1.merge(dp4).end() == dp4.end());
	assert(dp1.span(dp3).end() == dp3.end());
}

//////////////////////////////////////////
void case14()
{
	date d(2007, 9, 28);
	day_iterator d_iter(d);

	assert(d_iter == d);
	++d_iter;
	assert(d_iter == date(2007, 9, 29));

	year_iterator y_iter(*d_iter, 10);
	assert(y_iter == d + days(1));
	++y_iter;
	assert(y_iter->year() == 2017);

	day_iterator iter(day_clock::local_day());
	++iter;

	//iter += 5;
	//std::advance(iter, 5);
}

//////////////////////////////////////////
void case15()
{
	typedef gregorian_calendar gre_cal;
	cout << "Y2017 is "
		<< (gre_cal::is_leap_year(2017) ? "" : "not")
		<< " a leap year." << endl;
	assert(gre_cal::end_of_month_day(2017, 2) == 28);
}

//////////////////////////////////////////
void case16()
{
	date d(2017, 1, 23);

	date d_start(d.year(), d.month(), 1);
	date d_end = d.end_of_month();

	for (day_iterator d_iter(d_start);
		d_iter <= d_end; ++d_iter)
	{
		cout << *d_iter << " " <<
			d_iter->day_of_week() << endl;
	}

}

//////////////////////////////////////////
void case17()
{
	date d(2017, 1, 23);

	date d18years = d + years(18);
	cout << d18years << " is "
		<< d18years.day_of_week() << endl;

	int count = 0;
	for (day_iterator d_iter(date(d18years.year(), 1, 1));
		d_iter <= d18years.end_of_month(); ++d_iter)
	{
		if (d_iter->day_of_week() == Sunday)
		{
			++count;
		}
	}
	cout << "total " << count << " Sundays." << endl;

	count = 0;
	for (month_iterator m_iter(date(d18years.year(), 1, 1));
		m_iter < date(d18years.year() + 1, 1, 1); ++m_iter)
	{
		count += m_iter->end_of_month().day();
	}
	cout << "total " << count << " days of year." << endl;

}

//////////////////////////////////////////
class credit_card
{
public:
	string bank_name;
	int bill_day_no;

	credit_card(const char* bname, int no) :
		bank_name(bname), bill_day_no(no) {}

	int calc_free_days(date consume_day = day_clock::local_day()) const
	{
		date bill_day(consume_day.year(), consume_day.month(), bill_day_no);
		if (consume_day > bill_day)
		{
			bill_day += months(1);
		}

		return (bill_day - consume_day).days() + 20;
	}

	friend bool operator<(const credit_card& l, const credit_card& r)
	{

		return l.calc_free_days() < r.calc_free_days();
	}
};

void case18()
{
	credit_card a("A bank", 25);
	credit_card b("B bank", 12);

	credit_card tmp = std::max(a, b);
	cout << "You should use " << tmp.bank_name
		<< ", free days = " << tmp.calc_free_days() << endl;
}



//////////////////////////////////////////

void case1()
{
	date d1;
	date d2(2010, 1, 1);
	date d3(2000, Jan, 1);
	date d4(d2);

	assert(d1 == date(not_a_date_time));
	assert(d2 == d4);
	assert(d3 < d4);
}

//////////////////////////////////////////

void case2()
{
	date d1 = from_string("1999-12-31");
	date d2(from_string("2015/1/1"));
	date d3 = from_undelimited_string("20011118");

	cout << d1 << d2 << d3 << endl;

	cout << day_clock::local_day() << endl;
	cout << day_clock::universal_day() << endl;

}

//////////////////////////////////////////
void case3()
{
	date d1(neg_infin);
	date d2(pos_infin);
	date d3(not_a_date_time);
	date d4(max_date_time);
	date d5(min_date_time);

	cout << d1 << d2 << d3 << d4 << d5 << endl;

	try
	{
		//date d1(1399,12,1);
		//date d2(10000,1,1);
		date d3(2017, 2, 29);
	}
	catch (std::exception& e)
	{
		cout << e.what() << endl;
	}
}

//////////////////////////////////////////
void case4()
{
	date d(2017, 6, 1);
	assert(d.year() == 2017);
	assert(d.month() == 6);
	assert(d.day() == 1);

	date::ymd_type ymd = d.year_month_day();
	assert(ymd.year == 2017);
	assert(ymd.month == 6);
	assert(ymd.day == 1);

	cout << d.day_of_week() << endl;
	cout << d.day_of_year() << endl;
	assert(d.end_of_month() == date(2017, 6, 30));

	cout << date(2015, 1, 10).week_number() << endl;
	cout << date(2016, 1, 10).week_number() << endl;
	cout << date(2017, 1, 10).week_number() << endl;

	assert(date(pos_infin).is_infinity());
	assert(date(pos_infin).is_pos_infinity());
	assert(date(neg_infin).is_neg_infinity());
	assert(date(not_a_date_time).is_not_a_date());
	assert(date(not_a_date_time).is_special());
	assert(!date(2017, 5, 31).is_special());


}

//////////////////////////////////////////
void case5()
{
	date d(2017, 1, 23);

	cout << to_simple_string(d) << endl;
	cout << to_iso_string(d) << endl;
	cout << to_iso_extended_string(d) << endl;
	cout << d << endl;

	//cout << "input date:";
	//cin >>d;
	//cout << d;

}

//////////////////////////////////////////
void case6()
{
	date d(2017, 5, 20);
	tm t = to_tm(d);
	assert(t.tm_hour == 0 && t.tm_min == 0);
	assert(t.tm_year == 117 && t.tm_mday == 20);

	date d2 = date_from_tm(t);
	assert(d == d2);

}

//////////////////////////////////////////
void case7()
{
	days dd1(10), dd2(-100), dd3(255);

	assert(dd1 > dd2 && dd1 < dd3);
	assert(dd1 + dd2 == days(-90));
	assert((dd1 + dd3).days() == 265);
	assert(dd3 / 5 == days(51));

	weeks w(3);
	assert(w.days() == 21);

	months m(5);
	years y(2);

	months m2 = y + m;
	assert(m2.number_of_months() == 29);
	assert((y * 2).number_of_years() == 4);

}

//////////////////////////////////////////
void case8()
{
	date d1(2000, 1, 1), d2(2017, 11, 18);
	cout << d2 - d1 << endl;
	assert(d1 + (d2 - d1) == d2);

	d1 += days(10);
	assert(d1.day() == 11);
	d1 += months(2);
	assert(d1.month() == 3 && d1.day() == 11);
	d1 -= weeks(1);
	assert(d1.day() == 4);

	d2 -= years(10);
	assert(d2.year() == d1.year() + 7);

	{
		date d1(2017, 1, 1);

		date d2 = d1 + days(pos_infin);
		assert(d2.is_pos_infinity());

		d2 = d1 + days(not_a_date_time);
		assert(d2.is_not_a_date());
		d2 = date(neg_infin);
		days dd = d1 - d2;
		assert(dd.is_special() && !dd.is_negative());
	}

	{
		date d(2017, 3, 30);
		d -= months(1);
		d -= months(1);
		d += months(2);
		assert(d.day() == 31);
	}
}

//////////////////////////////////////////
void case9()
{
	date_period dp1(date(2017, 1, 1), days(20));
	date_period dp2(date(2017, 1, 1), date(2016, 1, 1));
	date_period dp3(date(2017, 3, 1), days(-20));

	date_period dp(date(2017, 1, 1), days(20));

	assert(!dp.is_null());
	assert(dp.begin().day() == 1);
	assert(dp.last().day() == 20);
	assert(dp.end().day() == 21);
	assert(dp.length().days() == 20);

	{
		date_period dp1(date(2017, 1, 1), days(20));
		date_period dp2(date(2017, 2, 19), days(10));

		cout << dp1;                        //[2010-Jan-01/2010-Jan-20]
		assert(dp1 < dp2);
	}
}

//////////////////////////////////////////

int main()
{
	
	case11();
	case12();
	case13();
	case14();
	case15();
	case16();
	case17();
	case18();
	
	case1();
	case2();
	case3();
	case4();
	case5();
	case6();
	case7();
	case8();
	case9();

}



