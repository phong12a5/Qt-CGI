#ifndef APPDEFINE_H
#define APPDEFINE_H

#include <QDebug>

#define LOGD qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]"

#define PUBLICKEY_PATH      "/var/www/cgi-bin/key_rsa.pub"
#define PRIVATEKEY_PATH     "/var/www/cgi-bin/key_rsa.pri"

#ifdef F_CARE_BUILD
#define PLATFORM_BUILD "f_care"
#endif

#ifdef F_SYSTEM_BUILD
#define PLATFORM_BUILD "f_system"
#endif


#ifdef F_ANDROID_BUILD
#define PLATFORM_BUILD "f_android"
#endif


#ifdef F_ANDROID_WEBVIEW_BUILD
#define PLATFORM_BUILD "f_android_webview"
#endif


#ifdef F_IOS_BUILD
#define PLATFORM_BUILD "f_ios"
#endif


#ifdef F_IOS_WEBVIEW_BUILD
#define PLATFORM_BUILD "f_ios_webview"
#endif


#endif // APPDEFINE_H
