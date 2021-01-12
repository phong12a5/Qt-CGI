#include "AppMain.h"
#include "QtCGI.h"
#include "QJsonEncryption.h"
#include <QJsonDocument>
#include <QFile>
#include <QJsonObject>
#include <AppDefine.h>

AppMain::AppMain(QObject *parent) : QObject(parent)
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

void AppMain::handleRequest()
{
    QtCGI::Instance(true);
    QtCGI::Instance()->SetContentType(QtCGI::ContentTypeJSON);
    QJsonObject response;
    response["success"] = false;
    response["server_publickey"] = QString(getPublickey().toUtf8().toBase64());

    if(QtCGI::Instance()->GetRequestMethod() == QtCGI::MethodPost) {
        QString postData = QtCGI::Instance()->GetPostData();
        QMap<QString, QString> params = QtCGI::Instance()->GetQueryData();
        QString api = params.value("api");
        QString token = params.value("token");


        QJsonDocument postDoc = QJsonDocument::fromJson(postData.toUtf8());
        if(!postDoc.isNull() && postDoc.isObject()) {
            QJsonObject postObj = postDoc.object();
            QString client_publickey = postDoc["client_publickey"].toString();
            QJsonObject decryptedObj;
            if(QJsonEncryption::instance()->decryptJson(postObj,decryptedObj,getPrivatekey().toUtf8().data())) {

                QJsonObject rawObj;
            //
            // Send request to internal api
            //
                /* FOR TEST */
                rawObj["dropboxaccesstoken"] = "alaoaooaoaoaoa";
                rawObj["debug_mode"] = "test";
                /* END FOR TEST */

                QString rawStr = QString(QJsonDocument(rawObj).toJson(QJsonDocument::Compact));

                QString ecryptedStr;
                if(QJsonEncryption::instance()->encryptString(rawStr,ecryptedStr,client_publickey.toUtf8().data())) {
                    response["success"] = true;
                    response["data"] = ecryptedStr;
                } else {
                    response["message"] = "Could encrypt data from internal api";
                }
            } else {
                response["message"] = "Could decrypt POST data";
            }
        } else {
            response["message"] = "Could not parse POST data: " + postData;
        }
    } else {
        response["message"] = "Request method is not POST";
    }

    // Set the content
    QtCGI::Instance()->SetContent(QJsonDocument(response).toJson(QJsonDocument::Compact));
    // Write the content
    QtCGI::Instance()->WriteResponse();
// Return the application execution
}

QString &AppMain::getPublickey()
{
    return m_publicKey;
}

QString &AppMain::getPrivatekey()
{
    return m_privateKey;
}

void AppMain::loadPublicKey(QString& publicKey)
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

void AppMain::loadPrivateKey(QString& privateKey)
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
