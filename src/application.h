#pragma once

#include <QQuickView>
#include <QTimer>

#include "navigation/navigationcontroller.h"
#include "utilities/pointers.h"
#include "launchcontroller.h"

class QQuickView;

namespace Spark {

class LaunchController;

class Application : public QObject {
    Q_OBJECT

    Q_PROPERTY(QObject * launchers READ launchers CONSTANT)
    Q_PROPERTY(ProcessState processState READ processState NOTIFY processStateChanged)

    Q_ENUMS(ProcessState)
public:
    enum ProcessState {
        NotRunning = QProcess::NotRunning,
        Starting = QProcess::Starting,
        Running = QProcess::Running
    };

    explicit Application(QObject * parent = 0);

    void initialize();
    void showUserInterface();

    QObject * launchers() const;

    ProcessState processState() const;

public slots:
    bool launch(int index);

signals:
    void processStateChanged();

private slots:
    void onStateChanged();

private:
    void registerQmlTypes();
    void setupQuickEnvironment();

    NavigationController                  m_navigation;
    ObjectScopedPointer<LaunchController> m_launchController;
    ObjectScopedPointer<QQuickView>       m_view;
};

}
