#pragma once

#include <QObject>
#include <QtGlobal>

class PowerManager : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool canReboot READ canReboot CONSTANT)
    Q_PROPERTY(bool canShutdown READ canShutdown CONSTANT)
public:
    explicit PowerManager(QObject *parent = 0) : QObject(parent) { }

    virtual bool canReboot() const { return false; }
    virtual bool canShutdown() const { return false; }

signals:

public slots:
    virtual void shutdown() { }
    virtual void reboot() { }
};
