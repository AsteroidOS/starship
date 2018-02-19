/*
 * Copyright (C) 2018 - Florent Revest <revestflo@gmail.com>
 *               2016 - Andrew Branson <andrew.branson@jollamobile.com>
 *                      Ruslan N. Marchenko <me@ruff.mobi>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "watches.h"
#include "watch.h"

#include <QDBusConnection>
#include <QDBusInterface>
#include <QDebug>
#include <QDBusArgument>
#include <QDBusServiceWatcher>
#include <algorithm>

#define STARFISH_SERVICE QStringLiteral("org.starfish")
#define STARFISH_MANAGER_PATH QStringLiteral("/org/starfish/Manager")
#define STARFISH_MANAGER_INTERFACE QStringLiteral("org.starfish.Manager")

Watches::Watches(QObject *parent) : QAbstractListModel(parent), m_selectedWatch(-1)
{
    refreshWatches();
    refreshSelectedWatch();
    refreshSelectedWatchConnected();
    m_watcher = new QDBusServiceWatcher(STARFISH_SERVICE, QDBusConnection::sessionBus(), QDBusServiceWatcher::WatchForOwnerChange, this);
    QDBusConnection::sessionBus().connect(STARFISH_SERVICE, STARFISH_MANAGER_PATH, STARFISH_MANAGER_INTERFACE, "WatchesChanged", this, SLOT(refreshWatches()));
    QDBusConnection::sessionBus().connect(STARFISH_SERVICE, STARFISH_MANAGER_PATH, STARFISH_MANAGER_INTERFACE, "SelectedWatchChanged", this, SLOT(refreshSelectedWatch()));
    QDBusConnection::sessionBus().connect(STARFISH_SERVICE, STARFISH_MANAGER_PATH, STARFISH_MANAGER_INTERFACE, "SelectedWatchConnectedChanged", this, SLOT(refreshSelectedWatchConnected()));
    connect(m_watcher, &QDBusServiceWatcher::serviceRegistered, [this]() {
        refreshWatches();
        refreshSelectedWatch();
        refreshSelectedWatchConnected();
        QDBusConnection::sessionBus().connect(STARFISH_SERVICE, STARFISH_MANAGER_PATH, STARFISH_MANAGER_INTERFACE, "WatchesChanged", this, SLOT(refreshWatches()));
        QDBusConnection::sessionBus().connect(STARFISH_SERVICE, STARFISH_MANAGER_PATH, STARFISH_MANAGER_INTERFACE, "SelectedWatchChanged", this, SLOT(refreshSelectedWatch()));
        QDBusConnection::sessionBus().connect(STARFISH_SERVICE, STARFISH_MANAGER_PATH, STARFISH_MANAGER_INTERFACE, "SelectedWatchConnectedChanged", this, SLOT(refreshSelectedWatchConnected()));
    });
    connect(m_watcher, &QDBusServiceWatcher::serviceUnregistered, [this]() {
        beginResetModel();
        qDeleteAll(m_watches);
        m_watches.clear();
        endResetModel();
        m_connectedToService = false;
        emit connectedToServiceChanged();
    });
}

int Watches::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_watches.count();
}

QVariant Watches::data(const QModelIndex &index, int role) const
{
    switch (role) {
    case RoleAddress:
        return m_watches.at(index.row())->address();
    case RoleName:
        return m_watches.at(index.row())->name();
    }

    return QVariant();
}

QHash<int, QByteArray> Watches::roleNames() const
{
    QHash<int,QByteArray> roles;
    roles.insert(RoleAddress, "address");
    roles.insert(RoleName, "name");
    roles.insert(RoleSerialNumber, "serialNumber");
    return roles;
}

bool Watches::connectedToService()
{
    return m_connectedToService;
}

QString Watches::version() const
{
    QDBusInterface iface(STARFISH_SERVICE, STARFISH_MANAGER_PATH, STARFISH_MANAGER_INTERFACE);
    if (!iface.isValid()) {
        qWarning() << "Could not connect to starfishd.";
        return QString();
    }
    QDBusMessage reply = iface.call("Version");
    if (reply.type() == QDBusMessage::ErrorMessage) {
        qWarning() << "Error refreshing watches:" << reply.errorMessage();
        return QString();
    }
    if (reply.arguments().count() == 0) {
        qWarning() << "No reply from service.";
        return QString();
    }
    return reply.arguments().first().toString();
}

Watch *Watches::get(int index) const
{
    if (index >= 0 && index < m_watches.count())
        return m_watches.at(index);

    return nullptr;
}

int Watches::find(const QString &address) const
{
    for (int i = 0; i < m_watches.count(); i++) {
        if (m_watches.at(i)->address() == address)
            return i;
    }
    return -1;
}

void Watches::refreshWatches()
{
    QDBusInterface iface(STARFISH_SERVICE, STARFISH_MANAGER_PATH, STARFISH_MANAGER_INTERFACE);
    if (!iface.isValid()) {
        qWarning() << "Could not connect to starfishd.";
        return;
    }
    QDBusMessage reply = iface.call("ListWatches");
    if (reply.type() == QDBusMessage::ErrorMessage) {
        qWarning() << "Error refreshing watches:" << reply.errorMessage();
        return;
    }
    if (reply.arguments().count() == 0) {
        qWarning() << "No reply from service.";
        return;
    }
    const QDBusArgument &arg = reply.arguments().first().value<QDBusArgument>();
    QStringList availableList;
    arg.beginArray();
    while (!arg.atEnd()) {
        QDBusObjectPath p;
        arg >> p;
        if (find(p) == -1) {
            Watch *watch = new Watch(p, this);
            beginInsertRows(QModelIndex(), m_watches.count(), m_watches.count());
            m_watches.append(watch);
            endInsertRows();
            emit countChanged();
        }
        availableList << p.path();
        std::sort(m_watches.begin(), m_watches.end(), Watches::sortWatches);
    }
    arg.endArray();

    QList<Watch*> toRemove;
    foreach (Watch *watch, m_watches) {
        bool found = false;
        foreach (const QString &path, availableList) {
            if (path == watch->path().path()) {
                found = true;
                break;
            }
        }
        if (!found)
            toRemove << watch;
    }

    while (!toRemove.isEmpty()) {
        Watch *watch = toRemove.takeFirst();
        int idx = m_watches.indexOf(watch);
        beginRemoveRows(QModelIndex(), idx, idx);
        m_watches.takeAt(idx)->deleteLater();
        endRemoveRows();
        emit countChanged();
    }

    if (!m_connectedToService) {
        m_connectedToService = true;
        emit connectedToServiceChanged();
    }
}

void Watches::refreshSelectedWatch()
{
    QDBusInterface iface(STARFISH_SERVICE, STARFISH_MANAGER_PATH, STARFISH_MANAGER_INTERFACE);
    if (!iface.isValid()) {
        qWarning() << "Could not connect to starfishd.";
        return;
    }
    QDBusMessage reply = iface.call("SelectedWatch");
    if (reply.type() == QDBusMessage::ErrorMessage) {
        qWarning() << "Error refreshing watches:" << reply.errorMessage();
        return;
    }
    if (reply.arguments().count() == 0) {
        qWarning() << "No reply from service.";
        return;
    }
    const QDBusObjectPath &p = reply.arguments().first().value<QDBusObjectPath>();
    int selectedWatch = find(p);

    if(m_selectedWatch != selectedWatch) {
        m_selectedWatch = find(p);
        emit currentWatchChanged();
    }
}

void Watches::refreshSelectedWatchConnected()
{
    QDBusInterface iface(STARFISH_SERVICE, STARFISH_MANAGER_PATH, STARFISH_MANAGER_INTERFACE);
    if (!iface.isValid()) {
        qWarning() << "Could not connect to starfishd.";
        return;
    }
    QDBusMessage reply = iface.call("SelectedWatch");
    if (reply.type() == QDBusMessage::ErrorMessage) {
        qWarning() << "Error refreshing watches:" << reply.errorMessage();
        return;
    }
    if (reply.arguments().count() == 0) {
        qWarning() << "No reply from service.";
        return;
    }
    bool connected = reply.arguments().first().toBool();

    if(m_selectedWatchConnected != connected) {
        m_selectedWatchConnected = connected;
        emit currentWatchConnectedChanged();
    }
}

int Watches::currentWatch()
{
    return m_selectedWatch;
}

bool Watches::currentWatchConnected()
{
    return m_selectedWatchConnected;
}

bool Watches::sortWatches(Watch *a, Watch *b)
{
    return a->name() < b->name();
}

int Watches::find(const QDBusObjectPath &path) const
{
    for (int i = 0; i < m_watches.count(); i++) {
        if (m_watches.at(i)->path() == path)
            return i;
    }
    return -1;
}

void Watches::selectWatch(int index)
{
    Watch *w = get(index);
    if(w)
        w->selectWatch();
}
