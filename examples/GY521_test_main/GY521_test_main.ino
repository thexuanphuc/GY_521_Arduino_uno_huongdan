//
//    FILE: GY521_test_main.ino
// PURPOSE: output raw and compare complementary filter and Kalman filter.


#include "GY521.h"

GY521 sensor(0x68);
uint32_t counter = 0;
float last_micro;
float pre_roll_k = 0;
float pre_pitch_k = 0;
float rate_filted = 0;
float A[3] = { 0.0225143814860251,	0.0450287629720503	0.0225143814860251 };
float B[3] = {1	,-1.51644153521773,0.606499061161834 };
float x_in_roll[3] = { 0 };
float y_out_roll[3] = { 0 };

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  // Serial.print("GY521_LIB_VERSION: ");
  Serial.println(GY521_LIB_VERSION);

  Wire.begin();

  delay(100);
  while (sensor.wakeup() == false) {
    Serial.print(millis());
    Serial.println("\tCould not connect to GY521: please check the GY521 address (0x68/0x69)");
    delay(1000);
  }
  sensor.setAccelSensitivity(0);  //  2g
  sensor.setGyroSensitivity(0);   //  250 degrees/s

  sensor.setThrottle();
  Serial.println("start...");

  //  set calibration values from calibration sketch.
  sensor.axe = -0.115445065;
  sensor.aye = -0.032862794;
  sensor.aze = -0.009886982;
  sensor.gxe = 2.929099273;
  sensor.gye = 1.300198435;
  sensor.gze = 1.400099277;
  last_micro = 0.0;
}
void low_pass_filter(float x_in[3], float y_out[3]) {  //Low Pass Butterworth Filter
  y_out[0] = A[0] * x_in[0] + A[1] * x_in[1] + A[2] * x_in[2] - B[1] * y_out[1] - B[2] * y_out[2];
  y_out[2] = y_out[1];
  y_out[1] = y_out[0];
  x_in[2] = x_in[1];
  x_in[1] = x_in[0];
}

void loop() {
  // this part to find the duration between sampling
  // float now = micros();
  // float duration = (now - last_micro) * 1e-6;  //  duration in seconds.
  // last_micro = now;
  // Serial.println();
  // Serial.println(duration, 10);
  sensor.read_with_KF();
  float ax = sensor.getAccelX();
  float ay = sensor.getAccelY();
  float az = sensor.getAccelZ();
  float gx = sensor.getGyroX();
  float gy = sensor.getGyroY();
  float gz = sensor.getGyroZ();


  // //using complementary filter
  // float pitch = sensor.getPitch();
  // float roll  = sensor.getRoll();

  // // calculate only with accelerator
  // float x = sensor.getAngleX();
  // float y = sensor.getAngleY();

  // // angle if use kalman filter
  // float pitch_k = sensor.get_pitch_kalman();
  // float roll_k = sensor.get_roll_kalman();
  // // angle without any filter from accelerator
  // float roll_no_filter = sensor.getAngleX();
  // float pitch_no_filter = sensor.getAngleY();



  // //raw acceleration in [g]
  // Serial.print(ax, 3);
  // Serial.print(',');
  // Serial.print(ay, 3);
  // Serial.print(',');
  // Serial.print(az, 3);
  // Serial.print(',');
  // // raw data from gyroscope [deg / s]
  // Serial.print(gx, 3);
  // Serial.print(',');
  // Serial.print(gy, 3);
  // Serial.print(',');
  // Serial.print(gz, 3);
  // Serial.print(',');

  // // after using Kalman filter
  // Serial.print(roll_k, 3); //roll Kalman filter
  // Serial.print(',');
  // // Serial.print(roll, 3); //roll complementary filter
  // // Serial.print(',');
  // Serial.print(roll_no_filter);  // no filter
  // Serial.print(',');
  // Serial.print(pitch_k  , 3); //pitch Kalman filter
  // // Serial.print(pitch, 3); //pitch complementary filter
  // // Serial.print(',');
  // Serial.print(',');
  // Serial.println(pitch_no_filter); // pitch no filter
  // low pass filter for gyroscope
  x_in_roll[0] = sensor.getGyroX();
  Serial.print(x_in_roll[2], 3);
  Serial.print(',');  // roll rate no filter
  low_pass_filter(x_in_roll, y_out_roll);
  Serial.println(y_out_roll[0], 3);  //roll rate after low pass filter
  // float gy_raw = sensor.getGyroY();
  // float gz_raw = sensor.getGyroZ();

  delay(8);
}


//  -- END OF FILE --
