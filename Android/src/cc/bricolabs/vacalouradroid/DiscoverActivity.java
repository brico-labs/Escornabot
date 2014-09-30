package cc.bricolabs.vacalouradroid;

import java.util.ArrayList;

import android.app.Activity;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.support.v4.app.NavUtils;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.MenuItem;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.ViewGroup;
import android.view.Window;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.BaseAdapter;
import android.widget.Button;
import android.widget.ListAdapter;
import android.widget.ListView;
import android.widget.TextView;

public class DiscoverActivity extends Activity {

	private static ArrayList<BluetoothDevice> discoveredDevices = new ArrayList<BluetoothDevice>();
	private static int selectedIndex = -1;

	LayoutInflater inflater;

	Button btnScan;
	ListView lstDevices; 
	DeviceAdapter deviceAdapter;

	private final BroadcastReceiver mReceiver = new BroadcastReceiver() {

		public void onReceive(Context context, Intent intent) {

			String action = intent.getAction();

			if (BluetoothDevice.ACTION_FOUND.equals(action)) {

				BluetoothDevice device = intent
						.getParcelableExtra(BluetoothDevice.EXTRA_DEVICE);

				if (device != null) {
					addDiscoveredDevice(device);
				}

			} else if (BluetoothAdapter.ACTION_DISCOVERY_FINISHED
					.equals(action)) {

				discoveryFinished();
			}
		}
	};

	protected void onCreate(android.os.Bundle savedInstanceState) {

		super.onCreate(savedInstanceState);

		requestWindowFeature(Window.FEATURE_INDETERMINATE_PROGRESS);
		getActionBar().setDisplayHomeAsUpEnabled(true);
		inflater = (LayoutInflater) getSystemService(Context.LAYOUT_INFLATER_SERVICE);
		setResult(Activity.RESULT_CANCELED);
		setContentView(R.layout.activity_discover);

		btnScan = (Button) findViewById(R.id.btnScan);
		btnScan.setOnClickListener(new OnClickListener() {
			@Override
			public void onClick(View v) {
				doDiscovery();
			}
		});

		lstDevices = (ListView) findViewById(R.id.lstDevices);
		lstDevices.setEmptyView(findViewById(R.id.lstDevicesEmpty));
		deviceAdapter = new DeviceAdapter();
		lstDevices.setAdapter(deviceAdapter);
		lstDevices.setOnItemClickListener(new OnItemClickListener() {
			@Override
			public void onItemClick(AdapterView<?> parent, View view,
					int position, long id) {
				selectedIndex = position;
				BluetoothDevice device = discoveredDevices.get(selectedIndex);
				Log.i(App.LOGTAG,
						String.format("Device selected: %s (%s)",
								device.getName(), device.getAddress()));
			}
		});

		registerReceiver(mReceiver, new IntentFilter(
				BluetoothDevice.ACTION_FOUND));
		registerReceiver(mReceiver, new IntentFilter(
				BluetoothAdapter.ACTION_DISCOVERY_FINISHED));
	};

	private void doDiscovery() {

		setProgressBarIndeterminateVisibility(true);
		btnScan.setEnabled(false);
		discoveredDevices.clear();
		deviceAdapter.notifyDataSetChanged();
		selectedIndex = -1;
		BluetoothHelper.getInstance().startDiscover();
	}

	protected void discoveryFinished() {

		setProgressBarIndeterminateVisibility(false);
		btnScan.setEnabled(true);
	}

	@Override
	protected void onDestroy() {

		super.onDestroy();
		BluetoothHelper.getInstance().cancelDiscovery();
		unregisterReceiver(mReceiver);
	}
	
	@Override
	public boolean onOptionsItemSelected(MenuItem item) {
		
	    switch (item.getItemId()) {
	    case android.R.id.home:
	        NavUtils.navigateUpFromSameTask(this);
	        return true;
	    }	    
	    return super.onOptionsItemSelected(item);
	}

	private void addDiscoveredDevice(BluetoothDevice device) {

		discoveredDevices.add(device);
		Log.i(App.LOGTAG,
				String.format("BT device %s (%s)", device.getName(),
						device.getAddress()));
		deviceAdapter.notifyDataSetChanged();
	}

	class DeviceAdapter extends BaseAdapter implements ListAdapter {

		@Override
		public int getCount() {
			return discoveredDevices.size();
		}

		@Override
		public Object getItem(int position) {
			return discoveredDevices.get(position);
		}

		@Override
		public long getItemId(int position) {
			return position;
		}

		@Override
		public View getView(int position, View convertView, ViewGroup parent) {

			View view = convertView;

			if (view == null) {
				view = inflater.inflate(
						android.R.layout.simple_expandable_list_item_2, parent,
						false);
			}

			BluetoothDevice device = discoveredDevices.get(position);

			String name = (device.getName() != null ? device.getName() : String
					.format("-%s-", device.getAddress()));
			TextView txtTitle = (TextView) view
					.findViewById(android.R.id.text1);
			txtTitle.setText(name);

			TextView txtSubtitle = (TextView) view
					.findViewById(android.R.id.text2);
			txtSubtitle.setText(device.getAddress());

			return view;
		};

	};
}
