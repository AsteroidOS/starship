#ifndef CALENDAREVENT_H
#define CALENDAREVENT_H

#include <QSharedDataPointer>
#include <QDateTime>
#include <QMetaType>

namespace watchfish
{

struct CalendarEventData;

class CalendarEvent
{
	Q_GADGET

	Q_PROPERTY(QString uid READ uid WRITE setUid)
	Q_PROPERTY(QDateTime start READ start WRITE setStart)
	Q_PROPERTY(QDateTime end READ end WRITE setEnd)
	Q_PROPERTY(QString title READ title WRITE setTitle)
	Q_PROPERTY(QString location READ location WRITE setLocation)
	Q_PROPERTY(QString description READ description WRITE setDescription)
	Q_PROPERTY(bool allDay READ allDay WRITE setAllDay)

public:
	CalendarEvent();
	CalendarEvent(const CalendarEvent &);
	CalendarEvent &operator=(const CalendarEvent &);
	~CalendarEvent();

	QString uid() const;
	void setUid(const QString &uid);

	QDateTime start() const;
	void setStart(const QDateTime &state);

	QDateTime end() const;
	void setEnd(const QDateTime &end);

	QString title() const;
	void setTitle(const QString &v);

	QString location() const;
	void setLocation(const QString &v);

	QString description() const;
	void setDescription(const QString &v);

	bool allDay() const;
	void setAllDay(bool allDay);

private:
	QSharedDataPointer<CalendarEventData> data;
};

}

#endif // CALENDAREVENT_H
