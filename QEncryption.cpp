#include "QEncryption.h"
#include <QFile>
#include <AppDefine.h>
#include <CkRsa.h>
#include <QJsonObject>
#include <QJsonDocument>

QEncryption* QEncryption::s_instance = nullptr;

QEncryption *QEncryption::instance()
{
    if(s_instance == nullptr) {
        s_instance = new QEncryption(nullptr);
    }
    return s_instance;
}

bool QEncryption::encryptJson(QJsonObject &inputJson, QJsonObject &outputJson, const char *clientPubkey)
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

bool QEncryption::decryptJson(QJsonObject &inputJson, QJsonObject &outputJson, const char * serverPrivateKey)
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

QEncryption::QEncryption(QObject *parent) : QObject(parent)
{

}

bool QEncryption::encryptString(QString &inputString, QString &outputString, const char *clientPubkey)
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

bool QEncryption::decryptString(QString &inputString, QString &outputString, const char * serverPrivateKey)
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
