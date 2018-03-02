#include "servicecontrol.h"

#include <QFile>
#include <QDir>
#include <QDebug>
#include <QCoreApplication>
#include <QProcess>

ServiceControl::ServiceControl(QObject *parent) : QObject(parent)
{

}

QString ServiceControl::serviceName() const
{
    return m_serviceName;
}

void ServiceControl::setServiceName(const QString &serviceName)
{
    if (m_serviceName != serviceName) {
        m_serviceName = serviceName;
        emit serviceNameChanged();
    }
}

bool ServiceControl::serviceFileInstalled() const
{
    if (m_serviceName.isEmpty()) {
        qDebug() << "Service name not set.";
        return false;
    }
    QFile f(QDir::homePath() + "/.config/upstart/" + m_serviceName + ".conf");
    return f.exists();
}

bool ServiceControl::installServiceFile()
{
    if (m_serviceName.isEmpty()) {
        qDebug() << "Service name not set. Cannot generate service file.";
        return false;
    }

    QFile f(QDir::homePath() + "/.config/upstart/" + m_serviceName + ".conf");
    if (f.exists()) {
        qDebug() << "Service file already existing...";
        return false;
    }

    if (!f.open(QFile::WriteOnly | QFile::Truncate)) {
        qDebug() << "Cannot create service file";
        return false;
    }

    QString appDir = qApp->applicationDirPath();
    // Try to replace version with "current" to be more robust against updates
    appDir.replace(QRegExp("telescope.asteroidos\/[0-9.]*\/"), "telescope.asteroidos/current/");

    f.write("start on started unity8\n");
    f.write("pre-start script\n");
    f.write("   initctl set-env LD_LIBRARY_PATH=" + appDir.toUtf8() + "/../:$LD_LIBRARY_PATH\n");
    f.write("end script\n");
    f.write("exec " + appDir.toUtf8() + "/" + m_serviceName.toUtf8() + "\n");
    f.close();
    return true;
}

bool ServiceControl::removeServiceFile()
{
    if (m_serviceName.isEmpty()) {
        qDebug() << "Service name not set.";
        return false;
    }
    QFile f(QDir::homePath() + "/.config/upstart/" + m_serviceName + ".conf");
    return f.remove();
}

bool ServiceControl::serviceRunning() const
{
    QProcess p;
    p.start("initctl", {"status", m_serviceName});
    p.waitForFinished();
    QByteArray output = p.readAll();
    qDebug() << output;
    return output.contains("running");
}

bool ServiceControl::setServiceRunning(bool running)
{
    if (running && !serviceRunning()) {
        return startService();
    } else if (!running && serviceRunning()) {
        return stopService();
    }
    return true; // Requested state is already the current state.
}

bool ServiceControl::startService()
{
    qDebug() << "should start service";
    int ret = QProcess::execute("start", {m_serviceName});
    return ret == 0;
}

bool ServiceControl::stopService()
{
    qDebug() << "should stop service";
    int ret = QProcess::execute("stop", {m_serviceName});
    return ret == 0;
}

bool ServiceControl::restartService()
{
    qDebug() << "should stop service";
    int ret = QProcess::execute("restart", {m_serviceName});
    return ret == 0;
}
