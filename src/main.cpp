#include <QGuiApplication>

#include "application.h"

int main(int argc, char **argv)
{
    QGuiApplication app(argc, argv);

    Spark::Application spark;
    spark.initialize();
    spark.showUserInterface();

    return app.exec();
}
