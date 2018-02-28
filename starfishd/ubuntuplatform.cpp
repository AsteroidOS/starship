#include "ubuntuplatform.h"

// #include "libwatchfish/musiccontroller.h"
// #include "libwatchfish/notificationmonitor.h"
// #include "libwatchfish/walltimemonitor.h"

#include <QDBusConnection>
#include <QDBusMetaType>
#include <QDBusReply>
#include <QDebug>
#include <QSettings>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QUuid>

UbuntuPlatform::UbuntuPlatform(WatchesManager *wm, QObject *parent) : QObject(parent)
{
    qDBusRegisterMetaType<QList<QVariantMap>>();

    m_timeService = wm->timeService();
    // m_wallTimeMonitor = new watchfish::WallTimeMonitor(this);
    // connect(m_wallTimeMonitor, &watchfish::WallTimeMonitor::timeChanged, this, &UbuntuPlatform::onTimeChanged);

    // m_notificationService = wm->notificationService();
    // m_notificationMonitor = new watchfish::NotificationMonitor(this);
    // connect(m_notificationMonitor, &watchfish::NotificationMonitor::notification, this, &UbuntuPlatform::newNotification);

    // m_mediaService = wm->mediaService();
    // m_musicController = new watchfish::MusicController(this);
    // connect(m_musicController, SIGNAL(statusChanged()), SLOT(updateMusicStatus()));
    // connect(m_musicController, SIGNAL(titleChanged()), SLOT(updateMusicTitle()));
    // connect(m_musicController, SIGNAL(albumChanged()), SLOT(updateMusicAlbum()));
    // connect(m_musicController, SIGNAL(artistChanged()), SLOT(updateMusicArtist()));
    // connect(m_mediaService, SIGNAL(play()), m_musicController, SLOT(play()));
    // connect(m_mediaService, SIGNAL(pause()), m_musicController, SLOT(play()));
    // connect(m_mediaService, SIGNAL(next()), m_musicController, SLOT(next()));
    // connect(m_mediaService, SIGNAL(previous()), m_musicController, SLOT(previous()));
}

UbuntuPlatform::~UbuntuPlatform()
{
    // delete m_musicController;
    // delete m_notificationMonitor;
    // delete m_wallTimeMonitor;
}

void UbuntuPlatform::onTimeChanged() {
    m_timeService->setTime(QDateTime());
}

// void UbuntuPlatform::newNotification(watchfish::Notification *notification)
// {
//     // if (!notification->category().endsWith(".group")) {
//     //     connect(notification, SIGNAL(closed(CloseReason)), this, SLOT(onNotificationClosed(CloseReason)));
//     //     m_notificationService->insertNotification(notification->appId(), notification->id(), notification->appName(), "ios-mail", notification->summary(), notification->body(), NotificationService::Strong);
//     // }
// }

// void UbuntuPlatform::onNotificationClosed(watchfish::Notification::CloseReason)
// {
//     // watchfish::Notification *notif = (watchfish::Notification *)sender();
//     // m_notificationService->removeNotification(notif->id());
// }

void UbuntuPlatform::updateMusicStatus()
{
    // m_mediaService->setPlaying(m_musicController->status() == watchfish::MusicController::StatusPlaying);
}

void UbuntuPlatform::updateMusicTitle()
{
    // m_mediaService->setTitle(m_musicController->title());
}

void UbuntuPlatform::updateMusicAlbum()
{
    // m_mediaService->setAlbum(m_musicController->album());
}

void UbuntuPlatform::updateMusicArtist()
{
    // m_mediaService->setArtist(m_musicController->artist());
}