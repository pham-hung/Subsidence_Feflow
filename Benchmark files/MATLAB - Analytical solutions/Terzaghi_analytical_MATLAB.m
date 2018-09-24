clear all;
pe0=98.06;
H=10;
z=0;
k=1e-7;
k=k*86400;
PI=3.14159265;
K=500;
v=0.3;
G=3*K*(1-2*v)/2/(1+v);
mv=K+4*G/3;
gf=9.806;
alpha=1;
S=6e-8;
cv=(k/gf)*(K+4*G/3)/(alpha*alpha+(K+4*G/3)*S);
H0s=10.0;

result=zeros(100,1);
for i=1:100
    t=i;
    pet=0;    
    for j=1:1000
    a=(2*j-1)*PI*z/2/H;
    b=-(2*j-1)*(2*j-1)*PI*PI*cv*t/4/H/H;
    c=(-1)^(j-1)/(2*j-1);
    pet=pet+pe0*4*c*cos(a)*exp(b)/PI;    
    end
    result(i,1)=pet/gf+H0s;
end
xlswrite('Terzaghi.xls',result);

