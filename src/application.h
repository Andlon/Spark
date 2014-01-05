#pragma once

#include <QQuickView>

#include "navigation/navigationcontroller.h"
#include "utilities/pointers.h"

namespace Spark {

class Application : public QObject {
    Q_OBJECT
public:
    explicit Application(QObject * parent = 0);

    void initialize();
    void showUserInterface();

private:
    void registerQmlTypes();
    void setupQuickEnvironment();

    NavigationController            m_navigation;
    ObjectScopedPointer<QQuickView> m_view;
};

}
