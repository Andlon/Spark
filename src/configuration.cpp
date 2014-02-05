#include "configuration.h"

#include <QXmlStreamReader>
#include <QDebug>

namespace Spark {

namespace {
bool stringToBool(QString str, bool & ok)
{
    str = str.trimmed().toLower();

    if ((str.toInt(&ok) == 0 && ok) || str == "true")
    {
        ok = true;
        return true;
    }
    else if ((str.toInt(&ok) != 0 && ok) || str == "false")
    {
        ok = true;
        return false;
    }
    else
    {
        ok = false;
        return true;
    }
}

}

Configuration::Configuration()
    :   m_allowExit(true), m_allowShutdown(true), m_allowRestart(true)
{

}

void Configuration::parse(const QByteArray &data)
{
    QXmlStreamReader reader(data);

    if (reader.readNextStartElement())
    {
        if (reader.name() == "spark")
        {
            processSparkElement(reader);
        }
    }
    else
    {
        qWarning() << "Failed to parse configuration file. Could not find spark element. Configured options will be ignored.";
    }
}

void Configuration::processSparkElement(QXmlStreamReader &reader)
{
    while (reader.readNextStartElement())
    {
        bool isBoolean;
        const QStringRef element = reader.name();
        const QString text = reader.readElementText(QXmlStreamReader::SkipChildElements);
        const bool boolValue = stringToBool(text, isBoolean);

        if (element == "allowexit" && isBoolean)
            m_allowExit = boolValue;
        else if (element == "allowshutdown" && isBoolean)
            m_allowShutdown = boolValue;
        else if (element == "allowrestart" && isBoolean)
            m_allowRestart = boolValue;
        else
        {
            if (element != "launchers")
                qWarning() << "Unknown configuration element " << element << " ignored.";
        }
    }
}




}
