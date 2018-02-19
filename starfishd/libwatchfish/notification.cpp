/*
 *  libwatchfish - library with common functionality for SailfishOS smartwatch connector programs.
 *  Copyright (C) 2015 Javier S. Pedro <dev.git@javispedro.com>
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

#include <QtDBus/QDBusConnection>
#include <QtDBus/QDBusPendingCall>
#include <QtDBus/QDBusMessage>
#include "notification.h"

namespace watchfish
{

namespace
{
struct Action
{
	QString service;
	QString path;
	QString iface;
	QString method;
	QStringList args;
};
}

struct NotificationPrivate
{
	uint id;
	QString appId;
	QString appName;
	QString summary;
	QString body;
	QDateTime timestamp;
	QString icon;
	QString category;
	quint8 urgency;
	bool transient;
	QString previewSummary;
	QString previewBody;
	QHash<QString, Action> actions;
};

Notification::Notification(uint id, QObject *parent) : QObject(parent), d_ptr(new NotificationPrivate)
{
	Q_D(Notification);
	d->id = id;
	d->urgency = 0;
	d->transient = false;
}

Notification::~Notification()
{
}

uint Notification::id() const
{
	Q_D(const Notification);
	return d->id;
}

QString Notification::appId() const
{
	Q_D(const Notification);
	return d->appId;
}

void Notification::setAppId(const QString &appId)
{
	Q_D(Notification);
	if (appId != d->appId) {
		d->appId = appId;
		emit appIdChanged();
	}
}

QString Notification::appName() const
{
	Q_D(const Notification);
	return d->appName;
}

void Notification::setAppName(const QString &appName)
{
	Q_D(Notification);
	if (appName != d->appName) {
		d->appName = appName;
		emit appNameChanged();
	}
}

QString Notification::summary() const
{
	Q_D(const Notification);
	return d->summary;
}

void Notification::setSummary(const QString &summary)
{
	Q_D(Notification);
	if (summary != d->summary) {
		d->summary = summary;
		emit summaryChanged();
	}
}

QString Notification::body() const
{
	Q_D(const Notification);
	return d->body;
}

void Notification::setBody(const QString &body)
{
	Q_D(Notification);
	if (body != d->body) {
		d->body = body;
		emit bodyChanged();
	}
}

QDateTime Notification::timestamp() const
{
	Q_D(const Notification);
	return d->timestamp;
}

void Notification::setTimestamp(const QDateTime &dt)
{
	Q_D(Notification);
	if (dt != d->timestamp) {
		d->timestamp = dt;
		emit timestampChanged();
	}
}

QString Notification::icon() const
{
	Q_D(const Notification);
	return d->icon;
}

void Notification::setIcon(const QString &icon)
{
	Q_D(Notification);
	if (icon != d->icon) {
		d->icon = icon;
		emit iconChanged();
	}
}

QString Notification::category() const
{
	Q_D(const Notification);
	return d->category;
}

void Notification::setCategory(const QString &category)
{
	Q_D(Notification);
	if (category != d->category) {
		d->category = category;
		emit categoryChanged();
	}
}

int Notification::urgency() const
{
	Q_D(const Notification);
	return d->urgency;
}

void Notification::setUrgency(int urgency)
{
	Q_D(Notification);
	if (urgency != d->urgency) {
		d->urgency = urgency;
		emit urgencyChanged();
	}
}

bool Notification::transient() const
{
	Q_D(const Notification);
	return d->transient;
}

void Notification::setTransient(bool transient)
{
	Q_D(Notification);
	if (transient != d->transient) {
		d->transient = transient;
		emit transientChanged();
	}
}

QString Notification::previewSummary() const
{
	Q_D(const Notification);
	return d->previewSummary;
}

void Notification::setPreviewSummary(const QString &summary)
{
	Q_D(Notification);
	if (summary != d->previewSummary) {
		d->previewSummary = summary;
		emit previewSummaryChanged();
	}
}

QString Notification::previewBody() const
{
	Q_D(const Notification);
	return d->previewBody;
}

void Notification::setPreviewBody(const QString &body)
{
	Q_D(Notification);
	if (body != d->previewBody) {
		d->previewBody = body;
		emit previewBodyChanged();
	}
}

QStringList Notification::actions() const
{
	Q_D(const Notification);
	return d->actions.keys();
}

void Notification::addDBusAction(const QString &action, const QString &service, const QString &path, const QString &iface, const QString &method, const QStringList &args)
{
	Q_D(Notification);
	Action &a = d->actions[action];
	a.service = service;
	a.path = path;
	a.iface = iface;
	a.method = method;
	a.args = args;
}

void Notification::invokeAction(const QString &action)
{
	Q_D(Notification);
	if (d->actions.contains(action)) {
		const Action &a = d->actions[action];
		if (!a.service.isEmpty()) {
			QDBusMessage msg = QDBusMessage::createMethodCall(a.service, a.path, a.iface, a.method);
			foreach (const QString &arg, a.args) {
				msg << arg;
			}
			QDBusConnection::sessionBus().asyncCall(msg);
		}
	}
}

void Notification::close()
{
	Q_D(Notification);
	QDBusMessage msg = QDBusMessage::createMethodCall("org.freedesktop.Notifications",
													  "/org/freedesktop/Notifications",
													  "org.freedesktop.Notifications",
													  "CloseNotification");
	msg << quint32(d->id);
	QDBusConnection::sessionBus().asyncCall(msg);
}

}
