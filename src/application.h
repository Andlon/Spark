#pragma once

#include <QQuickView>

#include "navigation/navigationcontroller.h"
#include "utilities/pointers.h"
#include "launchcontroller.h"

class QQuickView;

namespace Spark {

class LaunchController;

class Application : public QObject {
    Q_OBJECT

    Q_PROPERTY(QObject * launchers READ launchers CONSTANT)
public:
    explicit Application(QObject * parent = 0);

    void initialize();
    void showUserInterface();

    QObject * launchers() const;

private:
    void registerQmlTypes();
    void setupQuickEnvironment();

    NavigationController                            m_navigation;
    ObjectScopedPointer<LaunchController>           m_launchController;
    ObjectScopedPointer<QQuickView>                 m_view;
};

}
