#pragma once

#include "launcher.h"
#include <QAbstractListModel>
#include <QVector>

namespace Spark {

class LauncherCollectionModel : public QAbstractListModel {
    Q_OBJECT
public:
    enum Role {
        IdRole,
        TitleRole,
        DescriptionRole,
        LogoRole,
        ExecRole,
        ScreenshotsRole
    };

    explicit LauncherCollectionModel(QObject * parent = 0);

    QVariant data(const QModelIndex &index, int role) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QHash<int, QByteArray> roleNames() const;

    QVector<Launcher> launchers() const;
    void setLaunchers(const QVector<Launcher> launchers);

private:
    QVector<Launcher> m_launchers;
};

}
