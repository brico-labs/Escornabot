package cc.bricolabs.vacalouradroid.fragments;

import android.app.Fragment;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.MotionEvent;
import android.view.View;
import android.view.View.OnTouchListener;
import android.view.ViewGroup;
import cc.bricolabs.vacalouradroid.R;

public class ButtonsFragment extends Fragment implements OnTouchListener {

	public static final int BTN_NONE = 0;
	public static final int BTN_NORTH = 1;
	public static final int BTN_EAST = 2;
	public static final int BTN_SOUTH = 3;
	public static final int BTN_WEST = 4;
	public static final int BTN_GO = 5;
	public static final int BTN_RESET = 6;

	public interface onButtonAction {

		void onButtonPressed(int button);

		void onButtonReleased(int button);
	}

	private onButtonAction buttonActionHandler = null;

	public void setOnButtonAction(onButtonAction handler) {
		this.buttonActionHandler = handler;
	}

	@Override
	public View onCreateView(LayoutInflater inflater, ViewGroup container,
			Bundle savedInstanceState) {

		View view = inflater.inflate(R.layout.fragment_buttons, container,
				false);

		view.findViewById(R.id.btn_north).setOnTouchListener(this);
		view.findViewById(R.id.btn_east).setOnTouchListener(this);
		view.findViewById(R.id.btn_south).setOnTouchListener(this);
		view.findViewById(R.id.btn_west).setOnTouchListener(this);
		view.findViewById(R.id.btn_go).setOnTouchListener(this);
		view.findViewById(R.id.btn_reset).setOnTouchListener(this);

		return view;
	}

	@Override
	public boolean onTouch(View v, MotionEvent event) {

		int action = event.getAction();
		int button;

		if (action == MotionEvent.ACTION_UP) {

			button = identifyButton(v.getId());

			if (button != BTN_NONE && buttonActionHandler != null) {

				buttonActionHandler.onButtonReleased(button);
			}

			v.performClick();

		} else if (action == MotionEvent.ACTION_DOWN) {

			button = identifyButton(v.getId());

			if (button != BTN_NONE && buttonActionHandler != null) {

				buttonActionHandler.onButtonReleased(button);
			}
		}

		return true;
	}

	private int identifyButton(int viewId) {

		switch (viewId) {

		case R.id.btn_north:
			return BTN_NORTH;

		case R.id.btn_east:
			return BTN_EAST;

		case R.id.btn_south:
			return BTN_SOUTH;

		case R.id.btn_west:
			return BTN_WEST;

		case R.id.btn_go:
			return BTN_GO;

		case R.id.btn_reset:
			return BTN_RESET;
		}

		return BTN_NONE;
	}
}