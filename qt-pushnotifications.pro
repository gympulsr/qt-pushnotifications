QT += qml quick

android{
    QT += androidextras
}

CONFIG += c++11

SOURCES += \
    source/cpp/main.cpp \
    source/cpp/misc/pushnotification.cpp

RESOURCES += qml.qrc


ios{
    ######## adapt the following value to match your TeamID ########
    MY_DEVELOPMENT_TEAM.value = XXXXXXXXX
    ################################################################

    MY_DEVELOPMENT_TEAM.name = DEVELOPMENT_TEAM
    QMAKE_MAC_XCODE_SETTINGS += MY_DEVELOPMENT_TEAM

    MY_ENTITLEMENTS.name = CODE_SIGN_ENTITLEMENTS
    MY_ENTITLEMENTS.value = $$PWD/ios/pushnotifications.entitlements
    QMAKE_MAC_XCODE_SETTINGS += MY_ENTITLEMENTS

    QMAKE_IOS_DEPLOYMENT_TARGET=8.0

    # Note for devices: 1=iPhone, 2=iPad, 1,2=Universal.
    QMAKE_IOS_TARGETED_DEVICE_FAMILY = 1

    QMAKE_INFO_PLIST = $$PWD/ios/Info.plist

    OBJECTIVE_SOURCES += \
                    $$PWD/source/cpp/misc/ios/pushnotification.mm \

    CONFIG -= bitcode

}

android{
    ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

    ################# adapt that accordingly #######################
    ANDROID_JAVA_SOURCES.path = /src/com/example/example
    ################################################################

    ANDROID_JAVA_SOURCES.files = $$files($$PWD/source/java/*.java)
    INSTALLS += ANDROID_JAVA_SOURCES
}

HEADERS += \
    source/cpp/misc/pushnotification.h

DISTFILES += \
    android/AndroidManifest.xml \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradlew \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew.bat
