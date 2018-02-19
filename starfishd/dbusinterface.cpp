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

#include "dbusinterface.h"
#include "watchesmanager.h"

#include "libasteroid/watch.h"

#include <QDBusConnection>
#include <QDebug>

/* Watch Interface */

DBusWatch::DBusWatch(Watch *watch, WatchesManager* wm, QObject *parent): QObject(parent), m_watch(watch), m_wm(wm)
{
    m_screenshotService = wm->screenshotService();
    m_weatherService = wm->weatherService();
    m_batteryService = wm->batteryService();
    connect(m_batteryService, SIGNAL(levelChanged(quint8)), this, SIGNAL(LevelChanged(quint8)));
}

void DBusWatch::SelectWatch()
{
    m_wm->setDevice(m_watch);
}

QString DBusWatch::Address() const
{
    return m_watch->getAddress().toString();
}

QString DBusWatch::Name() const
{
    return m_watch->getName();
}

quint8 DBusWatch::BatteryLevel()
{
    return m_batteryService->level();
}

void DBusWatch::RequestScreenshot()
{
    m_screenshotService->requestScreenshot();
}

void DBusWatch::WeatherSetCityName(QString cityName)
{
    m_weatherService->setCity(cityName);
}

/* Manager Interface */

DBusInterface::DBusInterface(WatchesManager *wm, QObject *parent) : QObject(parent)
{
    m_watchesManager = wm;

    QDBusConnection::sessionBus().registerService("org.starfish");
    QDBusConnection::sessionBus().registerObject("/org/starfish/Manager", this, QDBusConnection::ExportScriptableSlots|QDBusConnection::ExportScriptableSignals);

    foreach (Watch *watch, m_watchesManager->watches())
        watchAdded(watch);

    connect(m_watchesManager, &WatchesManager::watchAdded, this, &DBusInterface::watchAdded);
    connect(m_watchesManager, &WatchesManager::watchRemoved, this, &DBusInterface::watchRemoved);
    connect(m_watchesManager, SIGNAL(currentWatchChanged()), this, SIGNAL(SelectedWatchChanged()));
    connect(m_watchesManager, SIGNAL(connected()), this, SIGNAL(SelectedWatchConnectedChanged()));
    connect(m_watchesManager, SIGNAL(disconnected()), this, SIGNAL(SelectedWatchConnectedChanged()));
}

QString DBusInterface::Version()
{
    return QStringLiteral(VERSION);
}

QList<QDBusObjectPath> DBusInterface::ListWatches()
{
    QList<QDBusObjectPath> ret;

    foreach (const QString &address, m_dbusWatches.keys())
        ret.append(QDBusObjectPath("/org/starfish/" + address));

    return ret;
}

QDBusObjectPath DBusInterface::SelectedWatch()
{
    Watch *cur = m_watchesManager->currentWatch();
    if(cur) {
        QString address = cur->getAddress().toString().replace(":", "_");
        return QDBusObjectPath("/org/starfish/" + address);
    } else
        return QDBusObjectPath("/");
}

bool DBusInterface::SelectedWatchConnected()
{
    return m_watchesManager->isConnected();
}

void DBusInterface::watchAdded(Watch *watch)
{
    QString address = watch->getAddress().toString().replace(":", "_");
    if (m_dbusWatches.contains(address))
        return;

    DBusWatch *dbusWatch = new DBusWatch(watch, m_watchesManager, this);
    m_dbusWatches.insert(address, dbusWatch);
    QDBusConnection::sessionBus().registerObject("/org/starfish/" + address, dbusWatch, QDBusConnection::ExportAllContents);

    emit WatchesChanged();
}

void DBusInterface::watchRemoved(Watch *watch)
{
    QString address = watch->getAddress().toString().replace(":", "_");

    QDBusConnection::sessionBus().unregisterObject("/org/starfish/" + address);
    m_dbusWatches.remove(address);

    emit WatchesChanged();
}

