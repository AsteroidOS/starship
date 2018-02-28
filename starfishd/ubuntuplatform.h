#ifndef UBUNTUPLATFORM_H
#define UBUNTUPLATFORM_H

#include <QDBusContext>

// #include "libwatchfish/musiccontroller.h"
// #include "libwatchfish/notificationmonitor.h"
// #include "libwatchfish/walltimemonitor.h"

#include <libasteroid/services/mediaservice.h>
#include <libasteroid/services/notificationservice.h>
#include <libasteroid/services/timeservice.h>

#include "watchesmanager.h"
class UbuntuPlatform : public QObject, public QDBusContext
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "org.freedesktop.Notifications")

public:
    UbuntuPlatform(WatchesManager *wm, QObject *parent = 0);
    ~UbuntuPlatform();

public slots:
    void onTimeChanged();

    // void newNotification(watchfish::Notification *notification);
    // void onNotificationClosed(watchfish::Notification::CloseReason);

    void updateMusicStatus();
    void updateMusicTitle();
    void updateMusicAlbum();
    void updateMusicArtist();

private:
    // watchfish::MusicController *m_musicController;
    // watchfish::NotificationMonitor *m_notificationMonitor;
    // watchfish::WallTimeMonitor *m_wallTimeMonitor;

    TimeService *m_timeService;
    MediaService *m_mediaService;
    NotificationService *m_notificationService;
};

#endif // UBUNTUPLATFORM_H
