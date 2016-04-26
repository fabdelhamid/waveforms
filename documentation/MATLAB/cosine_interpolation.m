x = zeros (1,50);
x(1)  = 1;
x(50) = -1;

%plot(x,'ro');

x1 = 1;
x3 = length(x);

y1 = x(1);
y3 = x(length(x));

amax = 50;
ymax = max(y1,y3);
ymin = min(y1,y3);

if y1>y3
    xmax = x1;
    xmin = x3;
else
    xmax = x3;
    xmin = x1;
end 

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% We need
% cos (W*Xmax + phi) = Ymax
%   W*Xmax + Phi = acos (Ymax)
%   W = (acos(Ymax) - Phi)/Xmax
%
% cos (W*Xmin + phi) = Ymin
%   W*Xmin + Phi = acos(Ymin)
%   Phi = (acos(Ymin) - W*Xmin)
%
% >> W  = (acos(Ymax) - (acos(Ymin) - W*Xmin))/Xmax
%       = (acos(Ymax) - acos(Ymin) + W*Xmin)/Xmax
%       = acos(Ymax)/Xmax - acos(Ymin)/Xmax + W* Xmin/Xmax
%    W - W*Xmin/Xmax = acos(Ymax)/Xmax - acos(Ymin)/Xmax
%    W * (1 - Xmin/Xmax) = acos(Ymax)/Xmax - acos(Ymin)/Xmax
%    W = ((acos(Ymax)/Xmax) - (acos(Ymin)/Xmax)) /(1 - Xmin/Xmax)

w = ((acos(ymax)/xmax) - (acos(ymin)/xmax)) /(1 - xmin/xmax)
phi = (acos(ymin) - w*xmin)

for i=2:length(x)-1
  x(i) = cos (w*i + phi);
end

plot(x);


