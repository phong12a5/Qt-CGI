#include "AppMain.h"
#include "QtCGI.h"
#include "QJsonEncryption.h"
#include <QJsonDocument>
#include <QJsonObject>

AppMain::AppMain(QObject *parent) : QObject(parent)
{

}

void AppMain::handleRequest()
{
    QtCGI::Instance(true);
    QtCGI::Instance()->SetContentType(QtCGI::ContentTypeJSON);
    QJsonObject response;
    response["success"] = false;
    response["server_publickey"] = QString(QJsonEncryption::instance()->getPublickey().toUtf8().toBase64());

    if(QtCGI::Instance()->GetRequestMethod() == QtCGI::MethodPost) {
        QString postData = QtCGI::Instance()->GetPostData();

        QJsonDocument postDoc = QJsonDocument::fromJson(postData.toUtf8());
        if(!postDoc.isNull() && postDoc.isObject()) {
            QJsonObject postObj = postDoc.object();
            QString client_publickey = postDoc["client_publickey"].toString();
            QJsonObject decryptedObj;
            if(QJsonEncryption::instance()->decryptJson(postObj,decryptedObj)) {

            //
            // Send request to internal api
            //
                QJsonObject rawObj;
                QJsonObject ecryptedObj;
                if(QJsonEncryption::instance()->encryptJson(rawObj,ecryptedObj,client_publickey.toUtf8().data())) {
                    response["success"] = true;
                    response["data"] = QString(QJsonDocument(ecryptedObj).toJson(QJsonDocument::Compact));
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
