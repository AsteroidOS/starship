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

#ifndef WATCHESMANAGER_H
#define WATCHESMANAGER_H

#include <QObject>
#include <QBluetoothAddress>

#include <libasteroid/scanner.h>
#include <libasteroid/watchconnection.h>

#include <bluez/bluezclient.h>

class Watch;

class WatchesManager : public WatchConnection
{
    Q_OBJECT

public:
    explicit WatchesManager(QObject *parent = 0);

    QList<Watch *> watches() const;
    Watch* get(const QBluetoothAddress &address);

signals:
    void watchAdded(Watch *watch);
    void watchRemoved(Watch *watch);

private slots:
    void loadWatches();

private:
    QList<Watch *> m_watches;
    BluezClient *m_bluezClient;
};

#endif // WATCHESMANAGER_H

