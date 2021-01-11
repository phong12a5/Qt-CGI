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
    outputJson["server_publickey"] = QString(getPublickey().toUtf8().toBase64());
    return success;
}

bool QJsonEncryption::decryptJson(QJsonObject &inputJson, QJsonObject &outputJson)
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
            if(this->decryptString(value,decryptedValue)) {
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

QString &QJsonEncryption::getPublickey()
{
    return m_publicKey;
}

QJsonEncryption::QJsonEncryption(QObject *parent) : QObject(parent)
{
    m_publicKey = QString();
    m_privateKey = QString();

    loadPublicKey(m_publicKey);
    loadPrivateKey(m_privateKey);
    if(!m_publicKey.isEmpty()) {
        LOGD << "Load public key successful: " << m_publicKey;
    } else {
        LOGD << "Load public key failed";
    }

    if(!m_privateKey.isEmpty()) {
        LOGD << "Load private key successful: " << m_privateKey;
    } else {
        LOGD << "Load private key failed";
    }
}

void QJsonEncryption::loadPublicKey(QString& publicKey)
{
    QFile pubFile(PUBLICKEY_PATH);
    if (pubFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QByteArray content = pubFile.readAll();
        if(!content.isNull() && !content.isEmpty()) {
            publicKey = QString(content);
        }
    } else {
        LOGD << "Open " << PUBLICKEY_PATH << " failed";
    }
}

void QJsonEncryption::loadPrivateKey(QString& privateKey)
{
    QFile priFile(PRIVATEKEY_PATH);
    if (priFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QByteArray content = priFile.readAll();
        if(!content.isNull() && !content.isEmpty()) {
            privateKey = QString(content);
        }
    } else {
        LOGD << "Open " << PRIVATEKEY_PATH << " failed";
    }
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

bool QJsonEncryption::decryptString(QString &inputString, QString &outputString)
{
    bool success = false;

    CkRsa rsaDecryptor;

    rsaDecryptor.put_EncodingMode("base64");
    success = rsaDecryptor.ImportPrivateKey(m_privateKey.toUtf8().data());

    bool usePrivateKey = true;
    const char *decryptedStr = rsaDecryptor.decryptStringENC(inputString.toUtf8().data(),usePrivateKey);
    outputString = QString(decryptedStr);
    return success;
}
