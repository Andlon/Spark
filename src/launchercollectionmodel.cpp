#include "launchercollectionmodel.h"

namespace Spark {

LauncherCollectionModel::LauncherCollectionModel(QObject *parent)
    :   QAbstractListModel(parent)
{

}

QVariant LauncherCollectionModel::data(const QModelIndex &index, int role) const
{
    Q_ASSERT(index.isValid());
    int row = index.row();
    Q_ASSERT(row >= 0 && row < m_launchers.count());

    const Launcher & launcher = m_launchers.at(row);

    switch (role)
    {
    case IdRole:
        return launcher.id();
    case TitleRole:
        return launcher.title();
    case DescriptionRole:
        return launcher.description();
    case LogoRole:
        return launcher.logoPath();
    case ExecRole:
        return launcher.execPath();
    case UsageRole:
        return launcher.usage();
    case ScreenshotsRole:
        return launcher.screenshotPaths();

    default:
        return QVariant();
    }
}

int LauncherCollectionModel::rowCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : m_launchers.count();
}

QHash<int, QByteArray> LauncherCollectionModel::roleNames() const
{
    static QHash<int, QByteArray> names;
    if (names.isEmpty())
    {
        names.insert(IdRole, "id");
        names.insert(TitleRole, "title");
        names.insert(DescriptionRole, "description");
        names.insert(LogoRole, "logo");
        names.insert(ExecRole, "exec");
        names.insert(UsageRole, "usage");
        names.insert(ScreenshotsRole, "screenshots");
    }

    return names;
}

QVector<Launcher> LauncherCollectionModel::launchers() const
{
    return m_launchers;
}

void LauncherCollectionModel::setLaunchers(const QVector<Launcher> launchers)
{
    beginResetModel();
    m_launchers = launchers;
    endResetModel();
}



}
