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

#ifndef WATCHFISH_VOLUMECONTROLLER_P_H
#define WATCHFISH_VOLUMECONTROLLER_P_H

#include <QDBusConnection>
#include "mainvolume2_interface.h"
#include "volumecontroller.h"

namespace watchfish
{

class VolumeControllerPrivate : public QObject
{
	Q_OBJECT

public:
	explicit VolumeControllerPrivate(VolumeController *q);
	~VolumeControllerPrivate();

	ComMeegoMainVolume2Interface *volume;

	int curValue;
	int curMaximum;

	static QString connectionAddress();

public slots:
	void handleStepsUpdated(uint StepCount, uint CurrentStep);

private:
	VolumeController * const q_ptr;
	Q_DECLARE_PUBLIC(VolumeController)
};

}

#endif // WATCHFISH_VOLUMECONTROLLER_P_H
