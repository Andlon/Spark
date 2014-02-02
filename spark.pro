QT += quick network
CONFIG += c++11

win32:QMAKE_POST_LINK += deploy.bat
unix:QMAKE_POST_LINK += sh deploy.sh

unix:!mac {
    LIBS += -Wl,-rpath=\\\$$ORIGIN/libs
}

win32:LIBS += -luser32 -ladvapi32

unix {
QT += dbus network
}

RCC_DIR = "build/rcc"
UI_DIR = "build/uic"
MOC_DIR = "build/moc"
OBJECTS_DIR = "build/obj"

CONFIG(debug, debug|release) {
    DESTDIR = "debug"
}
CONFIG(release, debug|release) {
    DESTDIR = "release"
}

INCLUDEPATH -= "$$PWD"

#QML_IMPORT_PATH += "$$PWD/assets/modules"

HEADERS += \
    src/application.h \
    src/navigation/lircclient.h \
    src/navigation/navigation.h \
    src/navigation/navigationcontroller.h \
    src/navigation/windowsnavigationfilter.h \
    src/utilities/pointers.h \
    src/launcher.h \
    src/launchcontroller.h \
    src/launchercollectionmodel.h \
    src/power/linuxpowermanager.h \
    src/power/power.h \
    src/power/powermanager.h \
    src/power/windowspowermanager.h

SOURCES += \
    src/application.cpp \
    src/main.cpp \
    src/navigation/lircclient.cpp \
    src/navigation/navigation.cpp \
    src/navigation/navigationcontroller.cpp \
    src/launcher.cpp \
    src/launchcontroller.cpp \
    src/launchercollectionmodel.cpp \
    src/power/linuxpowermanager.cpp \
    src/power/windowspowermanager.cpp

OTHER_FILES += \
    assets/interfaces/default/main.qml \
    assets/interfaces/default/LauncherView.qml \
    assets/interfaces/default/Pattern.qml \
    assets/interfaces/default/LauncherMicrocopy.qml \
    assets/interfaces/default/PowerMenu.qml
