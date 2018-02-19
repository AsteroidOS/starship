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

#ifndef WATCHFISH_VOLUMECONTROLLER_H
#define WATCHFISH_VOLUMECONTROLLER_H

#include <QtCore/QLoggingCategory>

namespace watchfish
{

Q_DECLARE_LOGGING_CATEGORY(volumeControllerCat)

class VolumeControllerPrivate;

class VolumeController : public QObject
{
	Q_OBJECT
	Q_DECLARE_PRIVATE(VolumeController)

	Q_PROPERTY(int value READ value WRITE setValue NOTIFY valueChanged)
	Q_PROPERTY(int minimum READ minimum NOTIFY minimumChanged)
	Q_PROPERTY(int maximum READ maximum NOTIFY maximumChanged)

public:
	explicit VolumeController(QObject *parent = 0);
	~VolumeController();

	int value() const;
	int minimum() const;
	int maximum() const;

	void setValue(int v);

public slots:
	void up();
	void down();

signals:
	void valueChanged();
	void minimumChanged();
	void maximumChanged();

private:
	VolumeControllerPrivate * const d_ptr;
};

}

#endif // WATCHFISH_VOLUMECONTROLLER_H
