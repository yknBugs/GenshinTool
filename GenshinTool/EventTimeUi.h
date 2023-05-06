#pragma once

#define MAXLOAD_TIME 180

#include "EventTime.h"
#include "Display.h"
#include "Option.h"

class EventTimeUi
{
private:
	string timeToString(TimeCaculator time, bool includeWeek = false);
	string weekToString(TimeCaculator time);

public:
	void showUi();

	void primogemExpectUi(TimeCaculator startTime, TimeCaculator endTime);
	void wishExpectUi(TimeCaculator startTime, TimeCaculator endTime);

	void newVersionUi(TimeCaculator startTime, TimeCaculator endTime);

	void sourceExpectUi(TimeCaculator startTime, TimeCaculator endTime);
};