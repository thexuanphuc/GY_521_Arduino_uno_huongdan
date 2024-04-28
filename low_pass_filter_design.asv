%  lets define cut off frequency  37 hz, (this is maximum value for sample rate of system 74 hz )
omg =  2*pi*4
Ts = 1/74;
z = tf('z', Ts);

W1 = tf([1],[1/(omg^2) 1.484/omg 1])
w1d = c2d(W1, Ts, 'tustin')
w1d.Variable = 'z^-1'
[num1 den1] = (tfdata(w1d))
num1 = cell2mat(num1);
den1 = cell2mat(den1);