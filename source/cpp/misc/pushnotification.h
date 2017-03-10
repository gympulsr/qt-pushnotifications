#ifndef PUSHNOTIFICATION_H
#define PUSHNOTIFICATION_H

#include <QObject>
#include <QQmlEngine>

class PushNotificationRegistrationTokenHandler : public QObject{
    Q_OBJECT
    Q_PROPERTY(QString gcmRegistrationToken READ getGcmRegistrationToken NOTIFY gcmRegistrationTokenChanged)
    Q_PROPERTY(QString apnsRegistrationToken READ getAPNSRegistrationToken WRITE setAPNSRegistrationToken NOTIFY apnsRegistrationTokenChanged)
public:
    PushNotificationRegistrationTokenHandler(QObject* parent = 0);
    //singleton type provider function for Qt Quick
    static QObject* pushNotificationRegistrationTokenProvider(QQmlEngine *engine, QJSEngine *scriptEngine);
    //singleton object provider for C++
    static PushNotificationRegistrationTokenHandler* instance();
    void setGcmRegistrationToken(const QString& gcmRegistrationToken);
    QString getGcmRegistrationToken();
    QString getAPNSRegistrationToken() const;
    void setAPNSRegistrationToken(const QString& apnsToken);
    ~PushNotificationRegistrationTokenHandler();
signals:
    void gcmRegistrationTokenChanged();
    void apnsRegistrationTokenChanged();
    void registeredChanged();
private:
    QString m_gcmToken;
    QString m_apnsToken;
};


#endif // PUSHNOTIFICATION_H
