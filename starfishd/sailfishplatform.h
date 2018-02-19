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

#ifndef SAILFISHPLATFORM_H
#define SAILFISHPLATFORM_H

#include <QDBusContext>

#include "libwatchfish/musiccontroller.h"
#include "libwatchfish/notificationmonitor.h"
#include "libwatchfish/walltimemonitor.h"

#include <libasteroid/services/mediaservice.h>
#include <libasteroid/services/notificationservice.h>
#include <libasteroid/services/timeservice.h>

#include "watchesmanager.h"

class SailfishPlatform : public QObject, QDBusContext
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "org.freedesktop.Notifications")

public:
    SailfishPlatform(WatchesManager *wm, QObject *parent = 0);
    ~SailfishPlatform();

public slots:
    void onTimeChanged();

    void newNotification(watchfish::Notification *notification);
    void onNotificationClosed(watchfish::Notification::CloseReason);

    void updateMusicStatus();
    void updateMusicTitle();
    void updateMusicAlbum();
    void updateMusicArtist();

private:
    watchfish::MusicController *m_musicController;
    watchfish::NotificationMonitor *m_notificationMonitor;
    watchfish::WallTimeMonitor *m_wallTimeMonitor;

    TimeService *m_timeService;
    MediaService *m_mediaService;
    NotificationService *m_notificationService;
};

#endif // SAILFISHPLATFORM_H

