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

#include "voicecallcontroller.h"
#include "voicecallcontroller_p.h"

namespace watchfish
{

Q_LOGGING_CATEGORY(voiceCallControllerCat, "watchfish-VoiceCallController")

VoiceCallControllerPrivate::VoiceCallControllerPrivate(VoiceCallController *q)
	: vcm(new OrgNemomobileVoicecallVoiceCallManagerInterface("org.nemomobile.voicecall",
			"/", QDBusConnection::sessionBus(), this)),
	  activeCall(0),
      curInCall(false), curRinging(false),
	  q_ptr(q)
{
	connect(vcm, &OrgNemomobileVoicecallVoiceCallManagerInterface::activeVoiceCallChanged,
			this, &VoiceCallControllerPrivate::handleActiveVoiceCallChanged);
	handleActiveVoiceCallChanged();
}

VoiceCallControllerPrivate::~VoiceCallControllerPrivate()
{
	delete activeCall;
}

void VoiceCallControllerPrivate::handleActiveVoiceCallChanged()
{
	delete activeCall;
	QString id = vcm->activeVoiceCall();
	qCDebug(voiceCallControllerCat) << "Active voice call changed" << id;
	if (!id.isEmpty()) {
		activeCall = new OrgNemomobileVoicecallVoiceCallInterface("org.nemomobile.voicecall",
			QString("/calls/%1").arg(id), vcm->connection(), this);
		connect(activeCall, &OrgNemomobileVoicecallVoiceCallInterface::statusChanged,
		        this, &VoiceCallControllerPrivate::handleActiveVoiceCallStatusChanged);
		connect(activeCall, &OrgNemomobileVoicecallVoiceCallInterface::lineIdChanged,
		        this, &VoiceCallControllerPrivate::handleActiveVoiceCallLineIdChanged);
		VoiceCallStatus status = static_cast<VoiceCallStatus>(activeCall->status());
		setCallerId(activeCall->lineId());
		setCallStatus(status);
		qDebug() << "Status of new call:" << status << curCallerId;
	} else {
		activeCall = 0;
		setCallStatus(STATUS_NULL);
		setCallerId(QString());
	}
}

void VoiceCallControllerPrivate::handleActiveVoiceCallStatusChanged(int status, const QString &statusText)
{
	qCDebug(voiceCallControllerCat) << "Status changed:" << status << statusText;
	setCallStatus(static_cast<VoiceCallStatus>(status));
}

void VoiceCallControllerPrivate::handleActiveVoiceCallLineIdChanged(const QString &lineId)
{
	qCDebug(voiceCallControllerCat) << "LineID changed:" << lineId;
	setCallerId(lineId);
}

void VoiceCallControllerPrivate::setCallStatus(VoiceCallStatus status)
{
	Q_Q(VoiceCallController);
	const bool oldInCall = curInCall, oldRinging = curRinging;
	switch (status) {
	case STATUS_INCOMING:
		curInCall = true;
		curRinging = true;
		break;
	case STATUS_ACTIVE:
	case STATUS_HELD:
	case STATUS_DIALING:
	case STATUS_ALERTING:
	case STATUS_WAITING:
		curInCall = true;
		curRinging = false;
		break;
	case STATUS_DISCONNECTED:
	case STATUS_NULL:
	default:
		curInCall = false;
		curRinging = false;
		break;
	}
	if (oldInCall != curInCall) {
		emit q->inCallChanged();
	}
	if (oldRinging != curRinging) {
		emit q->ringingChanged();
	}
}

void VoiceCallControllerPrivate::setCallerId(const QString &callerId)
{
	Q_Q(VoiceCallController);
	if (callerId != curCallerId) {
		curCallerId = callerId;
		emit q->callerIdChanged();
	}
}

VoiceCallController::VoiceCallController(QObject *parent)
	: QObject(parent), d_ptr(new VoiceCallControllerPrivate(this))
{
}

VoiceCallController::~VoiceCallController()
{
	delete d_ptr;
}

bool VoiceCallController::inCall() const
{
	Q_D(const VoiceCallController);
	return d->curInCall;
}

bool VoiceCallController::ringing() const
{
	Q_D(const VoiceCallController);
	return d->curRinging;
}

QString VoiceCallController::callerId() const
{
	Q_D(const VoiceCallController);
	return d->curCallerId;
}

}
