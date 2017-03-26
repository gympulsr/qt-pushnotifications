#include "pushnotification.h"
#include <mutex>

#ifdef Q_OS_ANDROID
#include <QAndroidJniObject>
#include <QtAndroidExtras>
#endif

QString g_gcmRegistrationToken = "";
std::mutex g_RegistrationTokenMutex;

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
    if(g_gcmRegistrationToken != ""){
        g_RegistrationTokenMutex.lock();
        setGcmRegistrationToken(g_gcmRegistrationToken);
        g_gcmRegistrationToken = "";
        g_RegistrationTokenMutex.unlock();
    }
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




#ifdef Q_OS_ANDROID
static void gcmTokenResult(JNIEnv* /*env*/ env, jobject obj, jstring gcmToken)
{
    const char* nativeString = env->GetStringUTFChars(gcmToken, 0);
    qDebug() << "GCM Token is:" << nativeString;

    //the following is kind of a "hack". We can't use
    //   PushNotificationRegistrationTokenHandler::instance()->setGcmRegistrationToken(QString(nativeString));
    //directly, as this function most probably get's called before the GUI application is initialized. Using a
    //QObject before the application is initialized results in undefined behavior and might crash the application.
    //So in order to avoid that we are storing the gcm registration token in a global variable. The
    //PushNotificationRegistrationTokenHandler::getGcmRegistrationToken() method copies the value in it's own
    //private member variable, as soon as the gcm registration token is available.
    //Just to be on the safe side, we are protecting the variable with a mutex.
    g_RegistrationTokenMutex.lock();
    g_gcmRegistrationToken = QString(nativeString);
    g_RegistrationTokenMutex.unlock();

}


// create a vector with all our JNINativeMethod(s)
static JNINativeMethod methods[] = {
    { "sendGCMToken", // const char* function name;
        "(Ljava/lang/String;)V",
        (void *)gcmTokenResult // function pointer
    }
};


// this method is called automatically by Java VM
// after the .so file is loaded
JNIEXPORT jint JNI_OnLoad(JavaVM* vm, void* /*reserved*/)
{
    JNIEnv* env;
    // get the JNIEnv pointer.
    if (vm->GetEnv(reinterpret_cast<void**>(&env), JNI_VERSION_1_6)
           != JNI_OK) {
        return JNI_ERR;
    }

    // search for Java class which declares the native methods
    jclass javaClass = env->FindClass("com/example/example/JavaNatives");
    if (!javaClass)
        return JNI_ERR;

    // register our native methods
    if (env->RegisterNatives(javaClass, methods,
                            sizeof(methods) / sizeof(methods[0])) < 0) {
        return JNI_ERR;
    }

    return JNI_VERSION_1_6;
}
#endif
