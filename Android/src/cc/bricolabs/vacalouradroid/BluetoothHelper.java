package cc.bricolabs.vacalouradroid;

import android.bluetooth.BluetoothAdapter;

public class BluetoothHelper {

	public static final int BT_OK = 0;
	public static final int BT_NOT_SUPPORTED = 1;
	public static final int BT_DISABLED = 2;

	private BluetoothAdapter adapter = null;
	private String bt_address = null;
	private String bt_name = null;

	private static BluetoothHelper instance = null;

	private BluetoothHelper() {
	}
	
	public String getAddress() {
		return bt_address;
	}
	
	public String getName() {
		return bt_name;
	}

	public static BluetoothHelper getInstance() {

		if (instance == null) {
			instance = new BluetoothHelper();
		}

		return instance;
	}

	public int init() {

		adapter = BluetoothAdapter.getDefaultAdapter();

		if (adapter == null) {
			return BT_NOT_SUPPORTED;
		}

		if (!adapter.isEnabled()) {
			return BT_DISABLED;
		}

		bt_address = adapter.getAddress();
		bt_name = adapter.getName();

		return BT_OK;
	}

}
