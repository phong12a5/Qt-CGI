#ifndef QEncryption_H
#define QEncryption_H

#include <QObject>

class QEncryption : public QObject
{
    Q_OBJECT
public:
    static QEncryption* instance();

    static void encrypt(QString& input, QString& output, QString key, QString iv, QString encodeMode = "base64");
    static void decrypt(QString& input, QString& output, QString key, QString iv, QString encodeMode = "base64");

    static QString hashKey(QString& input, int blockSize);
    static QString hashIv(QString& input, int blockSize);

private:
    explicit QEncryption(QObject *parent = nullptr);

private:
    static QEncryption* s_instance;
};

#endif // QEncryption_H
