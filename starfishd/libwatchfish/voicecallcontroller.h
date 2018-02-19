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

#ifndef WATCHFISH_VOICECALLCONTROLLER_H
#define WATCHFISH_VOICECALLCONTROLLER_H

#include <QtCore/QLoggingCategory>

namespace watchfish
{

Q_DECLARE_LOGGING_CATEGORY(voiceCallControllerCat)

class VoiceCallControllerPrivate;

class VoiceCallController : public QObject
{
	Q_OBJECT
	Q_DECLARE_PRIVATE(VoiceCallController)

	Q_PROPERTY(bool inCall READ inCall NOTIFY inCallChanged)
	Q_PROPERTY(bool ringing READ ringing NOTIFY ringingChanged)
	Q_PROPERTY(QString callerId READ callerId NOTIFY callerIdChanged)

public:
	explicit VoiceCallController(QObject *parent = 0);
	~VoiceCallController();

	bool inCall() const;
	bool ringing() const;

	QString callerId() const;

signals:
	void inCallChanged();
	void ringingChanged();
	void callerIdChanged();

private:
	VoiceCallControllerPrivate * const d_ptr;
};

}

#endif // WATCHFISH_VOICECALLCONTROLLER_H
