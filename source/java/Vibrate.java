//adapt that accordingly
package com.example.example;
import com.example.example.R;

import android.content.Context;
import android.os.Vibrator;
import android.app.Activity;
import android.os.Bundle;

import android.content.BroadcastReceiver;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.SharedPreferences;
import android.preference.PreferenceManager;
import android.support.v4.content.LocalBroadcastManager;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
//import android.widget.ProgressBar;
//import android.widget.TextView;

import com.google.android.gms.common.ConnectionResult;
import com.google.android.gms.common.GoogleApiAvailability;

public class Vibrate extends org.qtproject.qt5.android.bindings.QtActivity
{
    // start GCM
    private static final int PLAY_SERVICES_RESOLUTION_REQUEST = 9000;
    private static final String TAG = "MainActivity";

    private BroadcastReceiver mRegistrationBroadcastReceiver;
    //private KeyStore m_keyStore;

    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);

        mRegistrationBroadcastReceiver = new BroadcastReceiver()
        {
            @Override
            public void onReceive(Context context, Intent intent)
            {
                SharedPreferences sharedPreferences = PreferenceManager.getDefaultSharedPreferences(context);
                String token = sharedPreferences.getString(QuickstartPreferences.GCM_TOKEN, "");
                Log.i("Activity", token);
                JavaNatives.sendGCMToken(token);
            }
        };

        if (checkPlayServices())
        {
            // Start IntentService to register this application with GCM.
            Intent intent = new Intent(this, RegistrationIntentService.class);
            startService(intent);
        }
    }

    @Override
    protected void onResume()
    {
        super.onResume();
        LocalBroadcastManager.getInstance(this).registerReceiver(mRegistrationBroadcastReceiver,
                                            new IntentFilter(QuickstartPreferences.GCM_TOKEN));
    }

    @Override
    protected void onSaveInstanceState(Bundle outState) {
        super.onSaveInstanceState(outState);
    }

    @Override
    protected void onPause()
    {
        LocalBroadcastManager.getInstance(this).unregisterReceiver(mRegistrationBroadcastReceiver);
        super.onPause();
    }

    /*@Override
    public void onDestroy() {
        super.onDestroy();
    }*/

    /*@Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        QFacebookBinding.onActivityResult(requestCode, resultCode, data);
    }*/


    //
    // Check the device to make sure it has the Google Play Services APK. If
    // it doesn't, display a dialog that allows users to download the APK from
    // the Google Play Store or enable it in the device's system settings.
    //
    private boolean checkPlayServices()
    {
        GoogleApiAvailability apiAvailability = GoogleApiAvailability.getInstance();
        int resultCode = apiAvailability.isGooglePlayServicesAvailable(this);
        if (resultCode != ConnectionResult.SUCCESS)
        {
            if (apiAvailability.isUserResolvableError(resultCode))
            {
                apiAvailability.getErrorDialog(this, resultCode, PLAY_SERVICES_RESOLUTION_REQUEST).show();
            }
            else
            {
                Log.i(TAG, "This device is not supported.");
                finish();
            }
            return false;
        }
        return true;
    }



    // start vibrate
    public static Vibrator m_vibrator;
    public static Vibrate m_istance;
    public Vibrate()
    {
        m_istance = this;
    }
    public static void start(int x)
    {
        if (m_vibrator == null)
        {
            if (m_istance != null)
            {
                m_vibrator = (Vibrator) m_istance.getSystemService(Context.VIBRATOR_SERVICE);
                m_vibrator.vibrate(x);
            }
        }
        else m_vibrator.vibrate(x);
        //MyJniNatives.log(new String("vibrated"));
    }
    // end vibrate

}
