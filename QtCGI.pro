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
    PLATFORM_BUILD = QT_NO_DEBUG_OUTPUT
    message(Release)
}

CONFIG(debug, debug|release) {
    message(Debug)
}

#CONFIG   += f-care_build
#CONFIG   += f-system_build
#CONFIG   += f-android_build
#CONFIG   += f-android-webview_build
CONFIG   += f-ios_build
#CONFIG   += f-ios-webview_build

f-care_build {
    PLATFORM_BUILD = F_CARE_BUILD
    TARGET  = fity-one.cgi.1
}

f-system_build {
    PLATFORM_BUILD = F_SYSTEM_BUILD
    TARGET  = fity-one.cgi.2
}

f-android_build {
    PLATFORM_BUILD = F_ANDROID_BUILD
    TARGET  = fity-one.cgi.3
}

f-android-webview_build {
    PLATFORM_BUILD = F_ANDROID_WEBVIEW_BUILD
    TARGET  = fity-one.cgi.4
}

f-ios_build {
    PLATFORM_BUILD = F_IOS_BUILD
    TARGET  = fity-one.cgi.5
}

f-ios-webview_build {
    PLATFORM_BUILD = F_IOS_WEBVIEW_BUILD
    TARGET  = fity-one.cgi.6
}
DEFINES += $$PLATFORM_BUILD

target.path = $$PWD/release
INSTALLS += target

