#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlEngine>
#include "misc/pushnotification.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    qmlRegisterSingletonType<PushNotificationRegistrationTokenHandler>("com.example.example", 1, 0, "PushNotificationRegistrationTokenHandler",
                                                                        PushNotificationRegistrationTokenHandler::pushNotificationRegistrationTokenProvider);

    QQmlApplicationEngine engine;
    engine.addImportPath(QStringLiteral("qrc:/"));
    engine.load(QUrl(QStringLiteral("qrc:/source/qml/main.qml")));

    return app.exec();
}
