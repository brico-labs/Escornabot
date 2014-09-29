package cc.bricolabs.vacalouradroid;

import android.app.Activity;
import android.bluetooth.BluetoothAdapter;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.Toast;
import cc.bricolabs.vacalouradroid.fragments.ButtonsFragment;
import cc.bricolabs.vacalouradroid.fragments.ButtonsFragment.onButtonAction;

public class MainActivity extends Activity implements onButtonAction {

	private static final int RESULT_ENABLE_BT = 1;
	private static final int RESULT_DISCOVER_BT = 2;
	
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
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}

	@Override
	public boolean onOptionsItemSelected(MenuItem item) {

		switch (item.getItemId()) {

		case R.id.action_settings:
			return true;

		case R.id.action_link_bt:
			linkVacalourabot();
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

	private void linkVacalourabot() {

		BluetoothHelper bt = BluetoothHelper.getInstance();
		switch (bt.init()) {

		case BluetoothHelper.BT_NOT_SUPPORTED:

			Toast.makeText(this,
					R.string.main_deviceDoesNotSupportBluetooth,
					Toast.LENGTH_LONG).show();

			break;

		case BluetoothHelper.BT_DISABLED:

			Intent enableIntent = new Intent(
					BluetoothAdapter.ACTION_REQUEST_ENABLE);
			startActivityForResult(enableIntent, RESULT_ENABLE_BT);

			break;

		case BluetoothHelper.BT_OK:

			Intent discoverIntent = new Intent(this, DiscoverActivity.class);
			startActivityForResult(discoverIntent, RESULT_DISCOVER_BT);
		}
	}

	@Override
	protected void onActivityResult(int requestCode, int resultCode, Intent data) {

		switch (requestCode) {

		case RESULT_ENABLE_BT:
			if (resultCode == RESULT_OK) {
				linkVacalourabot();
			}
			break;
			
		case RESULT_DISCOVER_BT:
			if (resultCode == RESULT_OK) {
				
				// ToDo: send commands to Vacalourabot
			}
			break;

		default:
			super.onActivityResult(requestCode, resultCode, data);
		}
	}
}
