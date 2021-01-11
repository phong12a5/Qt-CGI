#ifndef QJSONENCRYPTION_H
#define QJSONENCRYPTION_H

#include <QObject>

class QJsonEncryption : public QObject
{
    Q_OBJECT
public:
    static QJsonEncryption* instance();
    bool encryptJson(QJsonObject& inputJsonPath, QJsonObject& outputJsonPath, const char * clientPubkey);
    bool decryptJson(QJsonObject& inputJsonPath, QJsonObject& outputJsonPath);

    QString& getPublickey();
private:
    explicit QJsonEncryption(QObject *parent = nullptr);

    void loadPublicKey(QString& publicKey);
    void loadPrivateKey(QString& privateKey);

    bool encryptString(QString& inputString, QString& outputString, const char * clientPubkey);
    bool decryptString(QString& inputString, QString& outputString);


private:
    static QJsonEncryption* s_instance;

    QString m_publicKey;
    QString m_privateKey;

public slots:
};

#endif // QJSONENCRYPTION_H
