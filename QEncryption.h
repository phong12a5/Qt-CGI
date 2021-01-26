#ifndef QEncryption_H
#define QEncryption_H

#include <QObject>

class QEncryption : public QObject
{
    Q_OBJECT
public:
    static QEncryption* instance();
    bool encryptJson(QJsonObject& inputJsonPath, QJsonObject& outputJsonPath, const char * clientPubkey);
    bool decryptJson(QJsonObject& inputJsonPath, QJsonObject& outputJsonPath, const char * serverPrivateKey);


    bool encryptString(QString& inputString, QString& outputString, const char * clientPubkey);
    bool decryptString(QString& inputString, QString& outputString, const char * serverPrivateKey);

private:
    explicit QEncryption(QObject *parent = nullptr);

private:
    static QEncryption* s_instance;
};

#endif // QEncryption_H
