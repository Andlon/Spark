#pragma once

#include <QByteArray>

class QXmlStreamReader;

namespace Spark {

class Configuration {
public:
    Configuration();

    void parse(const QByteArray & data);

    bool allowExit() const { return m_allowExit; }
    bool allowShutdown() const { return m_allowShutdown; }
    bool allowRestart() const { return m_allowRestart; }

private:
    bool m_allowExit;
    bool m_allowShutdown;
    bool m_allowRestart;

    void processSparkElement(QXmlStreamReader & reader);
    void processElement(QXmlStreamReader & reader);
};
}
