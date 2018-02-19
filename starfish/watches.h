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

#ifndef WATCHES_H
#define WATCHES_H

#include <QObject>
#include <QAbstractListModel>
#include <QDBusServiceWatcher>
#include <QDBusObjectPath>

class Watch;
class QDBusInterface;

class Watches : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(bool connectedToService READ connectedToService NOTIFY connectedToServiceChanged)
    Q_PROPERTY(QString version READ version)
    Q_PROPERTY(int count READ rowCount NOTIFY countChanged)
    Q_PROPERTY(int currentWatch READ currentWatch NOTIFY currentWatchChanged)
    Q_PROPERTY(bool currentWatchConnected READ currentWatchConnected NOTIFY currentWatchConnectedChanged)

public:
    enum Roles {
        RoleAddress,
        RoleName,
        RoleSerialNumber
    };

    Watches(QObject *parent = 0);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

    bool connectedToService();
    QString version() const;

    Q_INVOKABLE Watch *get(int index) const;
    int find(const QString &address) const;

    Q_INVOKABLE void selectWatch(int index);

    int currentWatch();
    bool currentWatchConnected();

signals:
    void connectedToServiceChanged();
    void countChanged();
    void currentWatchChanged();
    void currentWatchConnectedChanged();

private slots:
    void refreshWatches();
    void refreshSelectedWatch();
    void refreshSelectedWatchConnected();

private:
    int find(const QDBusObjectPath &path) const;
    static bool sortWatches(Watch *a, Watch *b);

private:
    bool m_connectedToService = false;
    QList<Watch*> m_watches;
    QDBusServiceWatcher *m_watcher;
    int m_selectedWatch;
    bool m_selectedWatchConnected;
};

#endif // WATCHES_H

