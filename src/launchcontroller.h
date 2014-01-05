#pragma once

#include <QObject>
#include "launcher.h"

namespace Spark {

class LaunchController : public QObject {
    Q_OBJECT
public:
    explicit LaunchController(QObject * parent = 0);

    void initialize();

private:
};

}
