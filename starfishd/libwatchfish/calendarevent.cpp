#include "calendarevent.h"

namespace watchfish
{

struct CalendarEventData : public QSharedData
{
	QString uid;
	QDateTime start;
	QDateTime end;
	QString title;
	QString location;
	QString description;
	bool allDay;
};

CalendarEvent::CalendarEvent() : data(new CalendarEventData)
{
}

CalendarEvent::CalendarEvent(const CalendarEvent &rhs) : data(rhs.data)
{
}

CalendarEvent &CalendarEvent::operator=(const CalendarEvent &rhs)
{
	if (this != &rhs)
		data.operator=(rhs.data);
	return *this;
}

CalendarEvent::~CalendarEvent()
{
}

QString CalendarEvent::uid() const
{
	return data->uid;
}

void CalendarEvent::setUid(const QString &v)
{
	if (data->uid != v) {
		data->uid = v;
	}
}


QDateTime CalendarEvent::start() const
{
	return data->start;
}

void CalendarEvent::setStart(const QDateTime &v)
{
	if (data->start != v) {
		data->start = v;
	}
}

QDateTime CalendarEvent::end() const
{
	return data->end;
}

void CalendarEvent::setEnd(const QDateTime &v)
{
	if (data->end != v) {
		data->end = v;
	}
}

QString CalendarEvent::title() const
{
	return data->title;
}

void CalendarEvent::setTitle(const QString &v)
{
	if (data->title != v) {
		data->title = v;
	}
}

QString CalendarEvent::location() const
{
	return data->location;
}

void CalendarEvent::setLocation(const QString &v)
{
	if (data->location != v) {
		data->location = v;
	}
}

QString CalendarEvent::description() const
{
	return data->description;
}

void CalendarEvent::setDescription(const QString &v)
{
	if (data->description != v) {
		data->description = v;
	}
}

bool CalendarEvent::allDay() const {
	return data->allDay;
}

void CalendarEvent::setAllDay(bool allDay) {
	if (data->allDay != allDay) {
		data->allDay = allDay;
	}
}

}
