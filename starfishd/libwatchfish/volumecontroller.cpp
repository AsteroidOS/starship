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

#include "volumecontroller.h"
#include "volumecontroller_p.h"

namespace watchfish
{

Q_LOGGING_CATEGORY(volumeControllerCat, "watchfish-VolumeController")

static const char *VOLUME_SERVICE = "com.Meego.MainVolume2";
static const char *VOLUME_PATH = "/com/meego/mainvolume2";

VolumeControllerPrivate::VolumeControllerPrivate(VolumeController *q)
	: volume(0),
      curValue(0), curMaximum(0),
      q_ptr(q)
{
	const QString address = connectionAddress();
	QDBusConnection connection = QDBusConnection::connectToPeer(address, "pulse");

	volume = new ComMeegoMainVolume2Interface(VOLUME_SERVICE, VOLUME_PATH, connection, this);

	connect(volume, &ComMeegoMainVolume2Interface::StepsUpdated,
	        this, &VolumeControllerPrivate::handleStepsUpdated);
	if (volume->isValid()) {
		handleStepsUpdated(volume->stepCount(), volume->currentStep());
	}
}

VolumeControllerPrivate::~VolumeControllerPrivate()
{
}

QString VolumeControllerPrivate::connectionAddress()
{
	if (qEnvironmentVariableIsSet("PULSE_DBUS_SERVER")) {
		return QString::fromLocal8Bit(qgetenv("PULSE_DBUS_SERVER"));
	} else {
		QDBusConnection bus = QDBusConnection::sessionBus();
		QDBusMessage message = QDBusMessage::createMethodCall("org.pulseaudio.Server", "/org/pulseaudio/server_lookup1",
			"org.freedesktop.DBus.Properties", "Get");
		message.setArguments(QVariantList() << "org.PulseAudio.ServerLookup1" << "Address");
		QDBusMessage reply = bus.call(message);
		if (reply.type() == QDBusMessage::ReplyMessage && reply.arguments().count() > 0) {
			return reply.arguments().first().value<QDBusVariant>().variant().toString();
		}
	}

	return QString();
}

void VolumeControllerPrivate::handleStepsUpdated(uint StepCount, uint CurrentStep)
{
	Q_Q(VolumeController);
	qCDebug(volumeControllerCat) << "updated stuff";
	const int oldValue = curValue, oldMaximum = curMaximum;
	curValue = CurrentStep;
	curMaximum = StepCount;
	if (oldMaximum != 0) {
		qCDebug(volumeControllerCat) << "Volume updated" << curValue << "/" << curMaximum;
	}
	if (curMaximum != oldMaximum) {
		emit q->maximumChanged();
	}
	if (curValue != oldValue) {
		emit q->valueChanged();
	}
}

VolumeController::VolumeController(QObject *parent)
    : QObject(parent), d_ptr(new VolumeControllerPrivate(this))
{
}

VolumeController::~VolumeController()
{
}

int VolumeController::value() const
{
	Q_D(const VolumeController);
	return d->volume->currentStep();
}

int VolumeController::minimum() const
{
	return 0;
}

int VolumeController::maximum() const
{
	Q_D(const VolumeController);
	return d->volume->stepCount();
}

void VolumeController::setValue(int v)
{
	Q_D(const VolumeController);
	qCDebug(volumeControllerCat) << "Setting volume to" << v;
	if (!d->volume->isValid()) {
		qCWarning(volumeControllerCat) << "Lost connection to volume interface";
	}
	d->volume->setCurrentStep(v);
}

void VolumeController::up()
{
	setValue(value() + 1);
}

void VolumeController::down()
{
	setValue(value() - 1);
}

}
