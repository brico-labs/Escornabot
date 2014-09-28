package cc.bricolabs.vacalouradroid;

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import cc.bricolabs.vacalouradroid.fragments.ButtonsFragment;
import cc.bricolabs.vacalouradroid.fragments.ButtonsFragment.onButtonAction;

public class MainActivity extends Activity implements onButtonAction {

	ButtonsFragment buttons;

	@Override
	protected void onCreate(Bundle savedInstanceState) {

		super.onCreate(savedInstanceState);

		setTitle(String.format("%s %s", getString(R.string.app_name),
				App.getAppVersionName()));
		
		setContentView(R.layout.activity_main);

		if (savedInstanceState == null) {

			buttons = (ButtonsFragment) getFragmentManager().findFragmentById(
					R.id.fragButtons);
			buttons.setOnButtonAction(this);
		}
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}

	@Override
	public boolean onOptionsItemSelected(MenuItem item) {
		// Handle action bar item clicks here. The action bar will
		// automatically handle clicks on the Home/Up button, so long
		// as you specify a parent activity in AndroidManifest.xml.
		int id = item.getItemId();
		if (id == R.id.action_settings) {
			return true;
		}
		return super.onOptionsItemSelected(item);
	}

	@Override
	public void onButtonPressed(int button) {

		Log.d(App.LOGTAG, "Pressed " + button);
	}

	@Override
	public void onButtonReleased(int button) {

		Log.d(App.LOGTAG, "Released " + button);
	}

}
