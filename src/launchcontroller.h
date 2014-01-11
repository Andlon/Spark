#pragma once

#include <QObject>
#include <QVector>
#include <QProcess>
#include "utilities/pointers.h"
#include "launcher.h"
#include "launchercollectionmodel.h"

namespace Spark {

class LaunchController : public QObject {
    Q_OBJECT
public:
    explicit LaunchController(QObject * parent = 0);

    void initialize();

    QProcess::ProcessState state() const;

    QObject * model() const;

public slots:
    bool launch(int index);

signals:
    void stateChanged();

private:
    ObjectScopedPointer<QProcess>                   m_process;
    ObjectScopedPointer<LauncherCollectionModel>    m_launchers;
    LauncherLoader m_loader;
};

}
