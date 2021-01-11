#ifndef APPDEFINE_H
#define APPDEFINE_H

#include <QDebug>

#define LOGD qDebug() << "[" << __FUNCTION__ << "][" << __LINE__ << "]"

#define PUBLICKEY_PATH      "/var/www/cgi-bin/key_rsa.pub"
#define PRIVATEKEY_PATH     "/var/www/cgi-bin/key_rsa.pri"

#endif // APPDEFINE_H
