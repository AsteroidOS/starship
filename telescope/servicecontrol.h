#ifndef SERVICECONTROL_H
#define SERVICECONTROL_H

#include <QObject>

class ServiceControl : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString serviceName READ serviceName WRITE setServiceName NOTIFY serviceNameChanged)
    Q_PROPERTY(bool serviceFileInstalled READ serviceFileInstalled NOTIFY serviceFileInstalledChanged)
    Q_PROPERTY(bool serviceRunning READ serviceRunning WRITE setServiceRunning NOTIFY serviceRunningChanged)

public:
    explicit ServiceControl(QObject *parent = 0);

    QString serviceName() const;
    void setServiceName(const QString &serviceName);

    bool serviceFileInstalled() const;
    Q_INVOKABLE bool installServiceFile();
    Q_INVOKABLE bool removeServiceFile();

    bool serviceRunning() const;
    bool setServiceRunning(bool running);
    Q_INVOKABLE bool startService();
    Q_INVOKABLE bool stopService();
    Q_INVOKABLE bool restartService();

signals:
    void serviceNameChanged();
    void serviceFileInstalledChanged();
    void serviceRunningChanged();

private:
    QString m_serviceName;
};

#endif
