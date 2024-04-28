%  lets define cut off frequency  37 hz, (this is maximum value for sample rate of system 74 hz )
omg =  40; % 40 hz
Ts = 0.02;
z = tf('z', Ts);

W1 = tf([1],[1/(omg^2) 1.484/omg 1])
w1d = c2d(W1, Ts, 'tustin')
w1d.Variable = 'z^-1'
[num1 den1] = (tfdata(w1d))
num1 = cell2mat(num1);
den1 = cell2mat(den1);
w1d

% coefficient of filter:
% num1: 0.0912408759124087	0.182481751824818	0.0912408759124087
% den1: 1	-0.958029197080292	0.322992700729927
% implement in form:
%
  % 
  % 0.09124 + 0.1825 z^-1 + 0.09124 z^-2    Y_out
  % ------------------------------------  = ------- =  w1d 
  %     1 - 0.958 z^-1 + 0.323 z^-2         X_in
