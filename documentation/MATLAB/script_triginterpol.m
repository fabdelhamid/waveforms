
clc;
N = 6;
fac = 0.5;
x = (2*pi*(0:fac:N-fac))./N; %%%% witdth of x must be even!; number 0:x:N-1 must be odd.

disp (['Numel: ',num2str(numel(x))]);

y = sin(x);
z = fft(y);

x_precise = 0:0.45:N;
yy = triginterpol(y, x_precise);
 
plot (x, y, 'o', x_precise, yy ./ numel(x) , 'r:');
legend ('Known Points', 'Trignometric Interpolation');


%%% Notes
% Result is more accurate with lesser supplied points!
% Otherwise, a form of ringing 
%%
%  occurs.