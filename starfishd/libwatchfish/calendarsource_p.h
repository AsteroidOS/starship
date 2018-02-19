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

#ifndef WATCHFISH_CALENDARSOURCE_P_H
#define WATCHFISH_CALENDARSOURCE_P_H

#include <extendedstorage.h>
#include "calendarsource.h"

namespace watchfish
{

class CalendarSourcePrivate : public QObject, public mKCal::ExtendedStorageObserver
{
	Q_OBJECT

public:
	explicit CalendarSourcePrivate(CalendarSource *q);
	~CalendarSourcePrivate();

	mKCal::ExtendedCalendar::Ptr calendar;
	mKCal::ExtendedStorage::Ptr calendarStorage;

	void storageModified(mKCal::ExtendedStorage *storage, const QString &info) Q_DECL_OVERRIDE;
	void storageProgress(mKCal::ExtendedStorage *storage, const QString &info) Q_DECL_OVERRIDE;
	void storageFinished(mKCal::ExtendedStorage *storage, bool error, const QString &info) Q_DECL_OVERRIDE;

	static CalendarEvent convertToEvent(const mKCal::ExtendedCalendar::ExpandedIncidence &expanded);

private:
	CalendarSource * const q_ptr;
	Q_DECLARE_PUBLIC(CalendarSource)
};

}

#endif // WATCHFISH_CALENDARSOURCE_P_H
