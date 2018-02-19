CONFIG += link_pkgconfig

contains(WATCHFISH_FEATURES, notificationmonitor) {
	PKGCONFIG += dbus-1
	HEADERS += $$PWD/notificationmonitor.h $$PWD/notificationmonitor_p.h $$PWD/notification.h
	SOURCES += $$PWD/notificationmonitor.cpp $$PWD/notification.cpp
}

contains(WATCHFISH_FEATURES, walltime) {
	PKGCONFIG += timed-qt5
	HEADERS += $$PWD/walltimemonitor.h $$PWD/walltimemonitor_p.h
	SOURCES += $$PWD/walltimemonitor.cpp
}

contains(WATCHFISH_FEATURES, music) {
	PKGCONFIG += mpris-qt5
	HEADERS += $$PWD/musiccontroller.h $$PWD/musiccontroller_p.h
	SOURCES += $$PWD/musiccontroller.cpp
        DBUS_INTERFACES += $$PWD/com.Meego.MainVolume2.xml
}

contains(WATCHFISH_FEATURES, calendar) {
	PKGCONFIG += libmkcal-qt5 libkcalcoren-qt5
	HEADERS += $$PWD/calendarsource.h $$PWD/calendarsource_p.h $$PWD/calendarevent.h
	SOURCES += $$PWD/calendarsource.cpp $$PWD/calendarevent.cpp
}

contains(WATCHFISH_FEATURES, voicecall) {
	HEADERS += $$PWD/voicecallcontroller.h $$PWD/voicecallcontroller_p.h
	SOURCES += $$PWD/voicecallcontroller.cpp
	DBUS_INTERFACES += org.nemomobile.voicecall.VoiceCallManager.xml org.nemomobile.voicecall.VoiceCall.xml
}

contains (WATCHFISH_FEATURES, volume) {
	HEADERS += $$PWD/volumecontroller.h $$PWD/volumecontroller_p.h
	SOURCES += $$PWD/volumecontroller.cpp
        DBUS_INTERFACES += $$PWD/com.Meego.MainVolume2.xml
}
