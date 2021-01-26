#ifndef APPMAIN_H
#define APPMAIN_H

#include <QObject>

class AppMain : public QObject
{
    Q_OBJECT
public:
    explicit AppMain(QObject *parent = nullptr);
    void handleRequest();

private:
    void forwardRequest(QString& api, QString& rquestBody, QString& resposeBody, QString& errorMsg, int& responseCode);
    QString getCurrentTime();
    void addFakeData(QJsonObject &object, QStringList &keyList, QStringList &valueList, int fieldNumber);
    QString getKeyFromTimestamp(const QString& timeStamp);
    QString getIvFromTimestamp(const QString& timeStamp);

    static void encrypt(QString& input, QString& output, QString key, QString iv);
    static void decrypt(QString& input, QString& output, QString key, QString iv);

    static QString hashKey(QString& input, int blockSize);
    static QString hashIv(QString& input, int blockSize);

    static QString encryptTimestamp(QString& timestamp, QString& token);
    static QString decryptTimestamp(QString& timestamp, QString& token);

public slots:
};

#endif // APPMAIN_H
