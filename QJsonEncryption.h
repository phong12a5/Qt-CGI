#ifndef QJSONENCRYPTION_H
#define QJSONENCRYPTION_H

#include <QObject>

class QJsonEncryption : public QObject
{
    Q_OBJECT
public:
    static QJsonEncryption* instance();
    bool encryptJson(QJsonObject& inputJsonPath, QJsonObject& outputJsonPath, const char * clientPubkey);
    bool decryptJson(QJsonObject& inputJsonPath, QJsonObject& outputJsonPath, const char * serverPrivateKey);


    bool encryptString(QString& inputString, QString& outputString, const char * clientPubkey);
    bool decryptString(QString& inputString, QString& outputString, const char * serverPrivateKey);

private:
    explicit QJsonEncryption(QObject *parent = nullptr);

private:
    static QJsonEncryption* s_instance;
};

#endif // QJSONENCRYPTION_H
