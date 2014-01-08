#pragma once

#include <QObject>
#include <QVector>
#include "utilities/pointers.h"
#include "launcher.h"
#include "launchercollectionmodel.h"

namespace Spark {

class LaunchController : public QObject {
    Q_OBJECT
public:
    explicit LaunchController(QObject * parent = 0);

    void initialize();

    QObject * model() const;

private:
    ObjectScopedPointer<LauncherCollectionModel> m_launchers;
    LauncherLoader m_loader;
};

}
