// calculate angle from accelerator(after compensation offset)
// unit [degree]
// _aax, _aay  la goc roll, pitch , tinh duoc nho du lieu tu accelerator(sau khi tru offset)
  _aax = atan(       _ay / sqrt(_ax2 + _az2)) * GY521_RAD2DEGREES;
  _aay = atan(-1.0 * _ax / sqrt(_ay2 + _az2)) * GY521_RAD2DEGREES;
// _gx, _gy rate changing from gyroscope, unit [degree per second]


// KALMAN FILTER
  //for roll
_1dkalman(_roll_k, _uncertain_roll, duration , _gx , _aax);
_roll_k = _output_kalman[0];  // goc sau khi fung kalman filter, can luu lai cho lan tinh toan tiep theo
_uncertain_roll = _output_kalman[1]; // gia tri can luu cho lan tinh toan tiep theo
//for pitch
_1dkalman(_pitch_k, _uncertain_pitch, duration , _gy, _aay);
_pitch_k = _output_kalman[0];// goc sau khi fung kalman filter, can luu lai cho lan tinh toan tiep theo
_uncertain_pitch = _output_kalman[1]; // gia tri can luu cho lan tinh toan tiep theo



//  function for kalman filter
void GY521::_1dkalman(float state_k , float motion_uncertainty_k,float duration, float rate, float measured_acce){
  state_k += duration * rate;
  motion_uncertainty_k += duration*duration*GY521_cov_gyro*GY521_cov_gyro ;
  _gain_k = motion_uncertainty_k *1 /(motion_uncertainty_k + GY521_cov_acce);
  // calculation return value of state and motion unvertainty
  state_k = state_k + _gain_k*(measured_acce - state_k);
  motion_uncertainty_k = (1-_gain_k)*motion_uncertainty_k ;
  _output_kalman[0] = state_k;
  _output_kalman[1] = motion_uncertainty_k;
}