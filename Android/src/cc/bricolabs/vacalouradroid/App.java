package cc.bricolabs.vacalouradroid;

import android.app.Application;
import android.content.Context;
import android.content.pm.PackageManager.NameNotFoundException;

public class App extends Application {

	public static final String LOGTAG = "Vacalourabot";

	private static Context context = null;
	private static String appVersionName;
	private static int appRevision;

	public static Context getContext() {
		return context;
	}

	@Override
	public void onCreate() {

		super.onCreate();

		// app context
		context = super.getApplicationContext();

		// version
		try {
			android.content.pm.PackageInfo pi = getPackageManager()
					.getPackageInfo(getPackageName(), 0);
			appVersionName = pi.versionName;
			appRevision = pi.versionCode;

		} catch (NameNotFoundException e) {

			e.printStackTrace();
		}
	}

	public static String getAppVersionName() {
		return appVersionName;
	}

	public static int getAppRevision() {
		return appRevision;
	}
}
