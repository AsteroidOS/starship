/*
 *  libwatchfish - library with common functionality for SailfishOS smartwatch connector programs.
 *  Copyright (C) 2016 Javier S. Pedro <dev.git@javispedro.com>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "calendarsource.h"
#include "calendarsource_p.h"

namespace watchfish
{

Q_LOGGING_CATEGORY(calendarSourceCat, "watchfish-CalendarSource")

CalendarSourcePrivate::CalendarSourcePrivate(CalendarSource *q)
	: calendar(new mKCal::ExtendedCalendar(KDateTime::Spec::LocalZone())),
	  calendarStorage(calendar->defaultStorage(calendar)),
	  q_ptr(q)
{
	calendarStorage->registerObserver(this);
	if (!calendarStorage->open()) {
		qCWarning(calendarSourceCat) << "Cannot open calendar database";
	}
}

CalendarSourcePrivate::~CalendarSourcePrivate()
{
	calendarStorage->unregisterObserver(this);
}

void CalendarSourcePrivate::storageModified(mKCal::ExtendedStorage *storage, const QString &info)
{
	Q_Q(CalendarSource);
	Q_UNUSED(storage);
	qCDebug(calendarSourceCat) << "Storage modified:" << info;
	emit q->changed();
}

void CalendarSourcePrivate::storageProgress(mKCal::ExtendedStorage *storage, const QString &info)
{
	Q_UNUSED(storage);
	Q_UNUSED(info);
	// Nothing to do
}

void CalendarSourcePrivate::storageFinished(mKCal::ExtendedStorage *storage, bool error, const QString &info)
{
	Q_UNUSED(storage);
	Q_UNUSED(error);
	Q_UNUSED(info);
	// Nothing to do
}

CalendarEvent CalendarSourcePrivate::convertToEvent(const mKCal::ExtendedCalendar::ExpandedIncidence &expanded)
{
	const KCalCore::Incidence::Ptr &incidence = expanded.second;
	CalendarEvent event;

	event.setUid(incidence->uid());

	event.setStart(expanded.first.dtStart);
	event.setEnd(expanded.first.dtEnd);

	event.setAllDay(incidence->allDay());
	event.setTitle(incidence->summary());
	event.setLocation(incidence->location());

	return event;
}

CalendarSource::CalendarSource(QObject *parent)
	: QObject(parent), d_ptr(new CalendarSourcePrivate(this))
{
}

CalendarSource::~CalendarSource()
{
	delete d_ptr;
}

QList<CalendarEvent> CalendarSource::fetchEvents(const QDate &start, const QDate &end,
												 bool startInclusive, bool endInclusive)
{
	Q_D(CalendarSource);
	int count;
	count = d->calendarStorage->loadRecurringIncidences();
	qCDebug(calendarSourceCat) << "Loaded" << count << "recurring events";
	count = d->calendarStorage->load(start, end);
	qCDebug(calendarSourceCat) << "Loaded" << count << "normal events";

	QList<CalendarEvent> events;
	QVector<mKCal::ExtendedCalendar::ExpandedIncidence> incidences = d->calendar->rawExpandedEvents(start, end, startInclusive, endInclusive);
	Q_FOREACH(const mKCal::ExtendedCalendar::ExpandedIncidence &expanded, incidences) {
		events.append(d->convertToEvent(expanded));
	}

	qCDebug(calendarSourceCat) << "Returning" << events.size() << "events";
	return events;
}

}
