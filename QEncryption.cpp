#include "QEncryption.h"
#include <QFile>
#include <AppDefine.h>
#include <CkRsa.h>
#include <QJsonObject>
#include <QJsonDocument>
#include <CkCrypt2.h>

QEncryption* QEncryption::s_instance = nullptr;

QEncryption *QEncryption::instance()
{
    if(s_instance == nullptr) {
        s_instance = new QEncryption(nullptr);
    }
    return s_instance;
}

QEncryption::QEncryption(QObject *parent) : QObject(parent)
{

}

QString QEncryption::hashKey(QString& input, int blockSize) {
    QString result;
    if(input.length() >= blockSize &&  32 % blockSize == 0) {
        for(int i = 0; i < 32/blockSize; i++) {
            if(i + blockSize < input.length()) {
                result += input.mid(i,blockSize);
            } else {
                result += input.mid(input.length() - blockSize,blockSize);
            }
        }
    }
    return result;
}

QString QEncryption::hashIv(QString& input, int blockSize) {
    QString result;
    if(input.length() >= blockSize &&  16 % blockSize == 0) {
        for(int i = 0; i < 16/blockSize; i++) {
            if(i + blockSize < input.length()) {
                result += input.mid(i,blockSize);
            } else {
                result += input.mid(input.length() - blockSize,blockSize);
            }
        }
    }
    return result;
}

QString QEncryption::md5(QString input)
{
    CkCrypt2 crypt;
    crypt.put_EncodingMode("hex");
    crypt.put_HashAlgorithm("md5");
    return QString(crypt.hashStringENC(input.toUtf8().data()));
}



void QEncryption::encrypt(QString &input, QString &output, QString key, QString iv, QString encodeMode) {
    CkCrypt2 crypt;
    crypt.put_CryptAlgorithm("aes");
    crypt.put_CipherMode("cbc");
    crypt.put_KeyLength(256);
    crypt.put_PaddingScheme(0);
    crypt.put_EncodingMode(encodeMode.toUtf8().data());
    crypt.SetEncodedIV(iv.toUtf8().data(), "ascii");
    crypt.SetEncodedKey(key.toUtf8().data(), "ascii");
    output = QString(crypt.encryptStringENC(input.toUtf8().data()));
}

void QEncryption::decrypt(QString& input, QString& output, QString key, QString iv, QString encodeMode) {
    CkCrypt2 crypt;
    crypt.put_CryptAlgorithm("aes");
    crypt.put_CipherMode("cbc");
    crypt.put_KeyLength(256);
    crypt.put_PaddingScheme(0);
    crypt.put_EncodingMode(encodeMode.toUtf8().data());
    crypt.SetEncodedIV(iv.toUtf8().data(), "ascii");
    crypt.SetEncodedKey(key.toUtf8().data(), "ascii");
    output = QString(crypt.decryptStringENC(input.toUtf8().data()));
}

