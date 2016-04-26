function yy = triginterpol(y_known_points,x_precise)  
N = numel(y_known_points);
M = N/2;  



disp(['N:',num2str(N)]); 
disp(['M:',num2str(M)]); 

z = fft(y_known_points);     % possibly holding info about this being cosine wave.

A_0 = 2*z(1);
A_M = 2*z(M);  

n = length(x_precise);
yy = zeros(1,n);
A_l = zeros(1,M);
B_l = zeros(1,M);

 for a = 1:n %loop over all x's that need to be calculated
     zz = 0; %assist variable
     for l = 1:M-1
         A_l(l) =      z(l+1) + z(N-l+1);
         B_l(l) = 1i.*(z(l+1) - z(N-l+1));
         zz = zz+(A_l(l).*cos(l.*x_precise(a)) + B_l(l).*sin(l.*x_precise(a)));
     end % for l
     
     %% Final formula that needs to be taken into consideration.
     yy(a) = A_0/2 + zz + (A_M/2.*cos(M.*x_precise(a)));
 end  % for a
end
