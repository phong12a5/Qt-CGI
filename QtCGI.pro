QT       += core network sql
QT       -= gui
TARGET    = autofarmer_api5_1_0.cgi
CONFIG   += console
CONFIG   -= app_bundle
TEMPLATE  = app
SOURCES  += main.cpp \
    QtCGI.cpp \
    QEncryption.cpp \
    AppMain.cpp

HEADERS += \
    QtCGI.h \
    AppDefine.h \
    QEncryption.h \
    AppMain.h


INCLUDEPATH += $$PWD/include/chilkat
LIBS += -L$$PWD/libs/ -lchilkat-9.5.0


CONFIG(release, debug|release) {
    DEFINES += QT_NO_DEBUG_OUTPUT
    message(Release)
}

CONFIG(debug, debug|release) {
    message(Debug)
}
