QT += qml quick

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

HEADERS += \
    source/cpp/misc/pushnotification.h
