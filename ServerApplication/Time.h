#include <iostream>
#include <time.h>
#include <string>

using namespace std;
#pragma warning(disable : 4996)

class Time
{
public:
	Time();
	~Time();
	int getHour();
	int getMinute();
	int getSecond();
	int getYear();
	int getMonth();
	int getMonthDay();
	int getYearDay();
	int getWeekDay();
	string getWatch();
	string getDate();
	void printWatch();
	void printDate();
	void printWeekDay();

private:
	time_t now;
	tm *ltm;

};

Time::Time()
{
}

Time::~Time()
{
}

int Time::getHour()
{
	now = time(0);
	ltm = localtime(&now);
	return ltm->tm_hour;
}

int Time::getMinute()
{
	now = time(0);
	ltm = localtime(&now);
	return ltm->tm_min;
}

int Time::getSecond()
{
	now = time(0);
	ltm = localtime(&now);
	return ltm->tm_sec;
}

int Time::getYear()
{
	now = time(0);
	ltm = localtime(&now);
	return ltm->tm_year + 1900;
}

int Time::getMonth()
{
	now = time(0);
	ltm = localtime(&now);
	return ltm->tm_mon + 1;
}

int Time::getMonthDay()
{
	now = time(0);
	ltm = localtime(&now);
	return ltm->tm_mday;
}

int Time::getYearDay()
{
	now = time(0);
	ltm = localtime(&now);
	return ltm->tm_yday;
}

int Time::getWeekDay()
{
	now = time(0);
	ltm = localtime(&now);
	return ltm->tm_wday + 1;
}

string Time::getDate()
{
	now = time(0);
	ltm = localtime(&now);

	string TimeTransactions = to_string(1900 + ltm->tm_year)
		+ "/" + to_string(1 + ltm->tm_mon) + "/" + to_string(ltm->tm_mday);

	return TimeTransactions;
}

string Time::getWatch()
{
	now = time(0);
	ltm = localtime(&now);

	string TimeTransactions = to_string(ltm->tm_hour) + ":" + to_string(ltm->tm_min);

	return TimeTransactions;
}

void Time::printWatch()
{
	now = time(0);
	ltm = localtime(&now);

	if (ltm->tm_hour > 12)
	{
		cout << ltm->tm_hour - 12 << ":";
		cout << ltm->tm_min;
		cout << " PM ";
	}
	else
	{
		cout << ltm->tm_hour << ":";
		cout << ltm->tm_min;
		cout << " AM ";
	}
}

void Time::printDate()
{
	now = time(0);
	ltm = localtime(&now);

	cout << 1900 + ltm->tm_year << "/";
	cout << 1 + ltm->tm_mon << "/";
	cout << ltm->tm_mday << " ";
}

void Time::printWeekDay()
{
	char week[7][10] = { "MON", "TUE", "WED", "THU", "FRI", "SAT", "SUN" };
	cout << week[ltm->tm_wday - 1];
}