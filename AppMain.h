#ifndef APPMAIN_H
#define APPMAIN_H

#include <QObject>

class AppMain : public QObject
{
    Q_OBJECT
public:
    explicit AppMain(QObject *parent = nullptr);
    void handleRequest();

    QString& getPublickey();
    QString& getPrivatekey();

private:
    void loadPublicKey(QString& publicKey);
    void loadPrivateKey(QString& privateKey);

private:
    QString m_publicKey;
    QString m_privateKey;

public slots:
};

#endif // APPMAIN_H
