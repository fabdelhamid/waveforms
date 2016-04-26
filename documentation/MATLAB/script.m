
clc;
N = 6;
x = (2*pi*(0:0.1:N-1))./N;
inc = 1;

while 1<2
    y2 = sin(x);
    z1 = fft(y2);
    
    y2 = sin (x .* inc); %sin(x);
    z2 = fft(y2);
    
    plot (x, real(z1),'g', x, imag(z1),'y', x, real(z2), 'r', x, imag(z2), 'b');
    legend ('Real Omega=1','Imag Omega=1',['Real Omega=',num2str(1+inc)],['Imag Omega=',num2str(1+inc)]);
    inc = inc + 0.01;
    pause(0.01);
end 

x_fein = 0:0.01:N;
yy = triginterpol(y, x_fein);
 
plot (x_fein, yy, 'r:', x, y);

%plot(x_fein, yy/N);
%hold on;
%plot(x_fein, cos(x_fein), 'r-');
%hold off;
max(abs(yy/N-cos(x_fein)));