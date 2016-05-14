Fs = 1000;            % Sampling frequency
T = 1/Fs;             % Sampling period
L = 1000;             % Length of signal
t = (0:L-1)*T;        % Time vector


plot(1000*t(1:50),X(1:50))
title('Signal Corrupted with Zero-Mean Random Noise')
xlabel('t (milliseconds)')
ylabel('X(t)')


f = Fs*(0:(L/2))/L;

inc = 0;
o
while 1<2
    f1 = 50;
    
    f2 = 120 + inc;
    
    S = 0.7*sin(2*pi*f1*t) + cos(2*pi*f2*t);
    X = S;%+ 2*randn(size(t));
    
    Y = fft(X);
    P2r = real(Y/L);
    P1r = P2r(1:L/2+1);
    P1r(2:end-1) = 2*P1r(2:end-1);

    P2i = imag(Y/L);
    P1i = P2i(1:L/2+1);
    P1i(2:end-1) = 2*P1i(2:end-1);

    %f = Fs*(0:(L/2))/L;
        
    plot(f, P1r, 'r', f, P1i, 'b');
    legend (['Real ',num2str(f2), ' Hz'],['Imag ',num2str(f2), ' Hz']);
    inc = inc + 0.01;
    pause(0.5);
end 

plot(f,P1)
title('Single-Sided Amplitude Spectrum of X(t)')
xlabel('f (Hz)')
ylabel('|P1(f)|')
