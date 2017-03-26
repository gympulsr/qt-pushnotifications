from apns2.client import APNsClient
from apns2.payload import Payload
from gcm import GCM
import os

#####
## set TARGET to 'android' if you want to send push notifications to android devices
## set TARGET to 'ios' if you want to send push notifications to iOs devices
TARGET = "ios"

###### Set your bundle id
BUNDLE_ID = "com.example.example"

currentDir = os.path.dirname(os.path.realpath(__file__))


if(TARGET == "ios"):
    ###### If you are using a production certificate, change this to 'False' 
    APNS_USE_SANDBOX = True

    ###### set path to APNS certificate
    APNS_CERT_PATH = currentDir + os.path.sep + "apns.pem"

    def static_vars(**kwargs):
        def decorate(func):
            for k in kwargs:
                setattr(func, k, kwargs[k])
            return func
        return decorate

    #creating a connection to the Apple Push notification service is really expensive and furthermore
    #has the disadvantage, that Apple detects multiple connection/disconnection attempts as possible DDos attack!
    #so we use a static variable to keep the connection open as long as possible.
    @static_vars(client=APNsClient('apns.pem', use_sandbox=APNS_USE_SANDBOX, use_alternative_port=False))
    def sendAPNSNotification(token, message):
        payload = Payload(alert=message, sound="default", badge=0)
        #client = APNsClient(APNS_CERT_PATH, use_sandbox=True, use_alternative_port=False)
        sendAPNSNotification.client.send_notification(token, payload, topic=BUNDLE_ID)

elif(TARGET == "android"): 
    GCM_API_KEY = "YOUR_GCM_API_KEY" #adapt that accordingly

    def sendGCMNotification(registrationTokenList, message):
        gcm = GCM(GCM_API_KEY)
        #print 'send message to gcm registration ids ' + ', '.join(registrationTokenList)
        retVal = gcm.json_request(registration_ids=registrationTokenList, data={"message": message}, 
                                    delay_while_idle=False)
        return retVal

if __name__ == "__main__":
    token = "YOUR_TOKEN" #change that to your token
    message = "Hello World"

    print "Sending '%s' to the phone with the token %s" %(message, token,)

    if(TARGET == "ios"):
	   sendAPNSNotification(token, message)
    elif(TARGET == "android"):
        sendGCMNotification([token], message)
    else:
        print "UNKNOWN TARGET"

