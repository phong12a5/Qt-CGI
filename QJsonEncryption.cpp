#include "QJsonEncryption.h"
#include <QFile>
#include <AppDefine.h>
#include <CkRsa.h>
#include <QJsonObject>
#include <QJsonDocument>

QJsonEncryption* QJsonEncryption::s_instance = nullptr;

QJsonEncryption *QJsonEncryption::instance()
{
    if(s_instance == nullptr) {
        s_instance = new QJsonEncryption(nullptr);
    }
    return s_instance;
}

bool QJsonEncryption::encryptJson(QJsonObject &inputJson, QJsonObject &outputJson, const char *clientPubkey)
{
    bool success = true;
    for(QString key: inputJson.keys()) {
        if(key == "appname" ||
                key == "info" ||
                key == "data" ||
                key == "uid" ||
                key == "email" ||
                key == "country" ||
                key == "action" ||
                key == "secretkey" ||
                key == "limit") {
            QString value = inputJson.value(key).toString();
            QString encryptedValue;
            if(this->encryptString(value,encryptedValue,clientPubkey)) {
                outputJson[key] = encryptedValue;
            } else {
                success = false;
            }
                // Do encrypt
        } else {

        }
    }
    return success;
}

bool QJsonEncryption::decryptJson(QJsonObject &inputJson, QJsonObject &outputJson, const char * serverPrivateKey)
{
    bool success = true;
    for(QString key: inputJson.keys()) {
        if(key == "appname" ||
                key == "info" ||
                key == "data" ||
                key == "uid" ||
                key == "email" ||
                key == "country" ||
                key == "action" ||
                key == "secretkey" ||
                key == "limit") {
            QString value = inputJson.value(key).toString();
            QString decryptedValue;
            if(this->decryptString(value,decryptedValue,serverPrivateKey)) {
                outputJson[key] = decryptedValue;
            } else {
                success = false;
            }
                // Do encrypt
        } else {

        }
    }
    return success;
}

QJsonEncryption::QJsonEncryption(QObject *parent) : QObject(parent)
{

}

bool QJsonEncryption::encryptString(QString &inputString, QString &outputString, const char *clientPubkey)
{
    bool success = false;
    CkRsa rsaEncryptor;

    // Encrypted output is always binary.  In this case, we want
    // to encode the encrypted bytes in a printable string.
    // Our choices are "hex", "base64", "url", "quoted-printable".
    rsaEncryptor.put_EncodingMode("base64");

    // We'll encrypt with the public key and decrypt with the private
    // key.  It's also possible to do the reverse.
    success = rsaEncryptor.ImportPublicKey(clientPubkey);

    bool usePrivateKey = false;
    const char *encryptedStr = rsaEncryptor.encryptStringENC(inputString.toUtf8().data(),usePrivateKey);
    outputString = QString(encryptedStr);
    return success;
}

bool QJsonEncryption::decryptString(QString &inputString, QString &outputString, const char * serverPrivateKey)
{
    bool success = false;

    CkRsa rsaDecryptor;

    rsaDecryptor.put_EncodingMode("base64");
    success = rsaDecryptor.ImportPrivateKey(serverPrivateKey);

    bool usePrivateKey = true;
    const char *decryptedStr = rsaDecryptor.decryptStringENC(inputString.toUtf8().data(),usePrivateKey);
    outputString = QString(decryptedStr);
    return success;
}
