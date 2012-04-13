package ca.inicio.paintmachine;

import ioio.lib.api.DigitalOutput;
import ioio.lib.api.PwmOutput;
import ioio.lib.api.exception.ConnectionLostException;
import ioio.lib.util.AbstractIOIOActivity;

import java.util.ArrayList;
import java.util.List;

import android.os.Bundle;
import android.text.method.ScrollingMovementMethod;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.EditText;
import android.widget.RadioButton;
import android.widget.RadioGroup;
import android.widget.RadioGroup.OnCheckedChangeListener;
import android.widget.SeekBar;
import android.widget.TextView;
import android.widget.ToggleButton;

/**
 * This is the main activity of the HelloIOIO example application.
 * 
 * It displays a toggle button on the screen, which enables control of the
 * on-board LED. This example shows a very simple usage of the IOIO, by using
 * the {@link AbstractIOIOActivity} class. For a more advanced use case, see the
 * HelloIOIOPower example.
 */
public class IOIOPaintMachineActivity extends AbstractIOIOActivity {
	private ToggleButton readyButton_;
	private Button spray_, sprayAll_, sprayMessage_;
	private SeekBar ready_, active_, encoder_, duration_;
	private TextView readyText_, activeText_, print_, durationText_;
	private EditText textInput_;
	private RadioGroup servLector_;
	private LetterSmithers smithers;

	private static final int RESET_ID = Menu.FIRST;

	private String data = "";

	private int index = 0;
	private int prevIndex = 1;

	private boolean sprayTrigger, sprayAllTrigger, sprayMessage = false;
	private int servoSelected;

	private float timer = 1000;

	private int letterArray[][][] = {
			{ { 0,1,1,1,0 }, { 1,0,0,0,1 }, { 1,0,0,0,1 }, { 1,0,0,0,1 }, { 1,1,1,1,1 },
					{ 1,0,0,0,1 }, { 1,0,0,0,1 } },
			{ { 1,1,1,1,0 }, { 1,0,0,0,1 }, { 1,0,0,0,1 }, { 1,1,1,1,0 }, { 1,0,0,0,1 },
					{ 1,0,0,0,1 }, { 1,1,1,1,0 } },
			{ { 0,1,1,1,0 }, { 1,0,0,0,1 }, { 1,0,0,0,0 }, { 1,0,0,0,0 }, { 1,0,0,0,0 },
					{ 1,0,0,0,1 }, { 0,1,1,1,0 } },
			{ { 1,1,1,1,0 }, { 1,0,0,0,1 }, { 1,0,0,0,1 }, { 1,0,0,0,1 }, { 1,0,0,0,1 },
					{ 1,0,0,0,1 }, { 1,1,1,1,0 } },
			{ { 1,1,1,1,1 }, { 1,0,0,0,0 }, { 1,0,0,0,0 }, { 1,1,1,1,0 }, { 1,0,0,0,0 },
					{ 1,0,0,0,0 }, { 1,1,1,1,1 } }
	};

	private float servoPos[][] = { { 1000, 1500 }, { 1000, 1500 },
			{ 1000, 1500 }, { 1000, 1500 }, { 1000, 1500 } }; // 0 =
	// ready;
	// 1 =
	// active
	private int duration = 1020;

	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.main);

		smithers = new LetterSmithers();

		readyButton_ = (ToggleButton) findViewById(R.id.readyPos);

		spray_ = (Button) findViewById(R.id.spray);
		sprayAll_ = (Button) findViewById(R.id.sprayAll);
		sprayMessage_ = (Button) findViewById(R.id.sprayMessage);

		spray_.setOnClickListener(new OnClickListener() {
			@Override
			public void onClick(View v) {
				sprayTrigger = true;
				timer = 1000;
			}
		});

		sprayAll_.setOnClickListener(new OnClickListener() {
			@Override
			public void onClick(View v) {
				sprayAllTrigger = true;
				timer = 1000;
			}
		});

		sprayMessage_.setOnClickListener(new OnClickListener() {
			@Override
			public void onClick(View v) {
				sprayMessage = true;
				timer = 1000;

				if (index == 4) {
					smithers.cursor++;
					index = 0;
				} else
					index++;

				smithers.setString(textInput_.getText().toString());
				smithers.setLetterCode(index);

			}
		});

		servLector_ = (RadioGroup) findViewById(R.id.srevoGroup);
		servLector_.setOnCheckedChangeListener(new OnCheckedChangeListener() {

			@Override
			public void onCheckedChanged(RadioGroup group, int checkedId) {
				RadioButton radio = (RadioButton) findViewById(checkedId);

				adjustServo(radio.getText());
			}
		});

		ready_ = (SeekBar) findViewById(R.id.servoSeekbar);
		active_ = (SeekBar) findViewById(R.id.dutyCycle);
		encoder_ = (SeekBar) findViewById(R.id.encoder);
		duration_ = (SeekBar) findViewById(R.id.duration);

		duration_.setProgress(duration);

		readyText_ = (TextView) findViewById(R.id.seekVal);
		activeText_ = (TextView) findViewById(R.id.dutyVal);
		durationText_ = (TextView) findViewById(R.id.durationText);

		textInput_ = (EditText) findViewById(R.id.message);

		print_ = (TextView) findViewById(R.id.print);
		print_.setMovementMethod(new ScrollingMovementMethod());

	}

	class IOIOThread extends AbstractIOIOActivity.IOIOThread {
		/** The on-board LED. */
		private DigitalOutput led_;
		private PwmOutput servo_0, servo_1, servo_2, servo_3, servo_4;

		private boolean sprayed = true;

		private List<PwmOutput> s_;

		private int[] servoPins = { 7, 6, 5, 4, 3 };

		@Override
		protected void setup() throws ConnectionLostException {
			led_ = ioio_.openDigitalOutput(0, true);
			servo_0 = ioio_.openPwmOutput(11, 100);
			servo_1 = ioio_.openPwmOutput(10, 100);
			servo_2 = ioio_.openPwmOutput(7, 100);
			servo_3 = ioio_.openPwmOutput(6, 100);
			servo_4 = ioio_.openPwmOutput(5, 100);
			servo_3 = ioio_.openPwmOutput(4, 100);
			servo_4 = ioio_.openPwmOutput(3, 100);

			s_ = new ArrayList<PwmOutput>();
			/*
			 * for(int i = 0; 0 < servoPins.length; i++){ PwmOutput servo_ =
			 * ioio_.openPwmOutput(servoPins[i], 100);
			 * servo_.setPulseWidth(1000); s_.add(i,servo_); }
			 */
			servo_0.setPulseWidth(1000);
			servo_1.setPulseWidth(1000);

			s_.add(0, servo_0);
			s_.add(1, servo_1);
			s_.add(2, servo_2);
			s_.add(3, servo_3);
			s_.add(4, servo_4);

		}

		@Override
		protected void loop() throws ConnectionLostException {

			led_.write(!true);

			float readyState = ready_.getProgress();
			float activeState = active_.getProgress();
			duration = duration_.getProgress() + 1000;
			// setText(Float.toString(500 + sb * 2), text_);
			// setText(Float.toString(dv),dutyVal_);

			setText(Float.toString(ready_.getProgress()), readyText_);
			setText(Float.toString(active_.getProgress()), activeText_);
			setText(Float.toString(duration), durationText_);

			data = Float.toString(timer) + "  " + servoSelected + "\n"
					+ "ready " + servoPos[servoSelected][0] + "active "
					+ servoPos[servoSelected][1] + " index: " + index
					+ " letterCode: " + smithers.getLetterCode();

			// encoder(encoder_.getProgress());
			adjustServoPosWrap(readyState, activeState);

			if (sprayTrigger == true) {
				data += " Single Spray";
				singleSpray(servoSelected);
			}
			if (sprayAllTrigger == true) {
				data += " All Spray";
				allSpray();
			}
			if (sprayMessage == true) {
				data += " Message";
				servoSpray();
			}

			setText(data, print_);

			try {
				sleep(10);
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}

		private void encoder(float x) {
			int increment = 10;

			if ((x % increment) == 0.0 && prevIndex != x) {
				index += 1;
				timer = 1000;
				// prevIndex = x;
			}

		}

		private void singleSpray(int i) throws ConnectionLostException {
			PwmOutput servo = (PwmOutput) s_.get(i);

			if (timer < duration) {
				servo.setPulseWidth(servoPos[i][1]);
				timer += 3;
			} else {
				servo.setPulseWidth(servoPos[i][0]);
				sprayTrigger = false;
			}

		}

		private void allSpray() throws ConnectionLostException {
			if (timer < duration) {
				for (int i = 0; i < s_.size(); i++) {
					PwmOutput servo = (PwmOutput) s_.get(i);
					servo.setPulseWidth(servoPos[i][1]);
				}
				timer += 3;
			} else {
				for (int i = 0; i < s_.size(); i++) {
					PwmOutput servo = (PwmOutput) s_.get(i);
					servo.setPulseWidth(servoPos[i][0]);
				}
				sprayAllTrigger = false;
			}
		}

		private void servoSpray() throws ConnectionLostException {
			int letter = smithers.getLetterCode();
			setText(" letter code:" + Integer.toString(letter) + "  index: "
					+ index + data, print_);

			if (timer < duration) {
				for (int i = 0; i < s_.size(); i++) {
					PwmOutput servo = (PwmOutput) s_.get(i);

					if (letterArray[letter][index][i] == 1) {
						servo.setPulseWidth(servoPos[i][1]);
						led_.write(!true);
					}

				}
				timer += 3;
			} else {
				for (int i = 0; i < s_.size(); i++) {
					PwmOutput servo = (PwmOutput) s_.get(i);
					servo.setPulseWidth(servoPos[i][0]);
					led_.write(!false);
				}
				sprayMessage = false;
			}

		}

		private void spray(int b, PwmOutput servo, int i) {
			if (b == 1) {

			}

		}

		private void adjustServoPosWrap(float readyState, float activeState) {
			if (readyButton_.isChecked()) {
				adjustServoPos(servoSelected, activeState, 1);
				adjustServoPos(servoSelected, readyState, 0);
			} else {
				ready_.setProgress((int) servoPos[servoSelected][0]);
				active_.setProgress((int) servoPos[servoSelected][1]);
			}
		}

		private void adjustServoPos(int servo, float val, int a) {
			servoPos[servo][a] = val;
		}
	}

	@Override
	protected AbstractIOIOActivity.IOIOThread createIOIOThread() {
		return new IOIOThread();
	}

	private void adjustServo(CharSequence id) {
		String c = id.toString();
		servoSelected = Integer.parseInt(c);

	}

	private void setText(final String str, final TextView t) {
		runOnUiThread(new Runnable() {
			@Override
			public void run() {
				t.setText(str);
			}

		});
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		super.onCreateOptionsMenu(menu);
		menu.add(0, RESET_ID, 0, R.string.menu_reset);

		return true;

	}

	@Override
	public boolean onMenuItemSelected(int featureId, MenuItem item) {
		switch (item.getItemId()) {
		case RESET_ID:
			index = 0;
			return true;
		}
		return super.onMenuItemSelected(featureId, item);
	}
}
