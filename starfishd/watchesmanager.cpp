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

#include "watchesmanager.h"

#include "libasteroid/watch.h"

WatchesManager::WatchesManager(QObject *parent) : WatchConnection(parent)
{
    m_bluezClient = new BluezClient(this);
    connect(m_bluezClient, &BluezClient::devicesChanged, this, &WatchesManager::loadWatches);
    loadWatches();
}

QList<Watch *> WatchesManager::watches() const
{
    return m_watches;
}

void WatchesManager::loadWatches()
{
    quint32 classOfDevice = QBluetoothDeviceInfo::WearableWristWatch << 2 | QBluetoothDeviceInfo::WearableDevice << 8;

    QList<Device> pairedWatches = m_bluezClient->pairedWatches();
    foreach (const Device &device, pairedWatches) {
        Watch *w = get(device.address);
        if (!w) {
            w = new Watch(QBluetoothDeviceInfo(device.address, device.name, classOfDevice));
            m_watches.append(w);
            emit watchAdded(w);
        }
    }

    QList<Watch *> watchesToRemove;
    foreach (Watch *w, m_watches) {
        bool found = false;
        foreach (const Device &dev, pairedWatches) {
            if (dev.address == w->getAddress()) {
                found = true;
                break;
            }
        }
        if (!found)
            watchesToRemove << w;
    }

    while (!watchesToRemove.isEmpty()) {
        Watch *w = watchesToRemove.takeFirst();
        m_watches.removeOne(w);
        emit watchRemoved(w);
        w->deleteLater();
    }
}

Watch* WatchesManager::get(const QBluetoothAddress &address)
{
    for (int i = 0; i < m_watches.count(); i++) {
        if (m_watches.at(i)->getAddress() == address) {
            return m_watches.at(i);
        }
    }
    return nullptr;
}
