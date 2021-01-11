QT       += core network sql
QT       -= gui
TARGET    = autofarmer.api
CONFIG   += console
CONFIG   -= app_bundle
TEMPLATE  = app
SOURCES  += main.cpp \
    QtCGI.cpp \
    QJsonEncryption.cpp \
    AppMain.cpp

HEADERS += \
    QtCGI.h \
    AppDefine.h \
    QJsonEncryption.h \
    AppMain.h


INCLUDEPATH += $$PWD/include/chilkat
LIBS += -L$$PWD/libs/ -lchilkat-9.5.0

