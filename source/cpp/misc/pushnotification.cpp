#include "pushnotification.h"

PushNotificationRegistrationTokenHandler::PushNotificationRegistrationTokenHandler(QObject *parent)
    : QObject(parent),
      m_gcmToken(""),
      m_apnsToken("")
{
}

QObject* PushNotificationRegistrationTokenHandler::pushNotificationRegistrationTokenProvider(QQmlEngine *engine, QJSEngine *scriptEngine){
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)
    return PushNotificationRegistrationTokenHandler::instance();
}

PushNotificationRegistrationTokenHandler* PushNotificationRegistrationTokenHandler::instance() {
    static PushNotificationRegistrationTokenHandler* pushNotificationRegistrationTokenHandler = new PushNotificationRegistrationTokenHandler();
    return pushNotificationRegistrationTokenHandler;
}

void PushNotificationRegistrationTokenHandler::setGcmRegistrationToken(const QString& gcmToken){
    m_gcmToken = gcmToken;
}

QString PushNotificationRegistrationTokenHandler::getGcmRegistrationToken(){
    return m_gcmToken;
}

QString PushNotificationRegistrationTokenHandler::getAPNSRegistrationToken() const{
    return m_apnsToken;
}

void PushNotificationRegistrationTokenHandler::setAPNSRegistrationToken(const QString& apnsToken){
    m_apnsToken = apnsToken;
    apnsRegistrationTokenChanged(); //emit signal
}

PushNotificationRegistrationTokenHandler::~PushNotificationRegistrationTokenHandler(){
}
