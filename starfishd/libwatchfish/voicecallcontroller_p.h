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

#ifndef WATCHFISH_VOICECALLCONTROLLER_P_H
#define WATCHFISH_VOICECALLCONTROLLER_P_H

#include "voicecallcontroller.h"
#include "voicecall_interface.h"
#include "voicecallmanager_interface.h"

namespace watchfish
{

enum VoiceCallStatus {
	STATUS_NULL,
	STATUS_ACTIVE,
	STATUS_HELD,
	STATUS_DIALING,
	STATUS_ALERTING,
	STATUS_INCOMING,
	STATUS_WAITING,
	STATUS_DISCONNECTED
};

class VoiceCallControllerPrivate : public QObject
{
	Q_OBJECT

public:
	explicit VoiceCallControllerPrivate(VoiceCallController *q);
	~VoiceCallControllerPrivate();

public slots:
	void handleActiveVoiceCallChanged();
	void handleActiveVoiceCallStatusChanged(int status, const QString &statusName);
	void handleActiveVoiceCallLineIdChanged(const QString &lineId);

public:
	OrgNemomobileVoicecallVoiceCallManagerInterface *vcm;
	OrgNemomobileVoicecallVoiceCallInterface *activeCall;

	bool curInCall;
	bool curRinging;
	QString curCallerId;

	void setCallStatus(VoiceCallStatus status);
	void setCallerId(const QString &callerId);

private:
	VoiceCallController * const q_ptr;
	Q_DECLARE_PUBLIC(VoiceCallController)
};

}

#endif // WATCHFISH_VOICECALLCONTROLLER_P_H

