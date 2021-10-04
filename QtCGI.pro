QT       += core
QT       -= gui
TARGET    = autofarmer_1_1.cgi
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


INCLUDEPATH += $$PWD/chilkat/include/
LIBS += -L$$PWD/chilkat/lib/ -lchilkat-9.5.0


CONFIG(release, debug|release) {
    DEFINES += QT_NO_DEBUG_OUTPUT
    message(Release)
}

CONFIG(debug, debug|release) {
    message(Debug)
}
