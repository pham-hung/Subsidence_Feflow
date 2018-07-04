clear all;
%Step1: Input parameter
PI=3.14159265358979323846264; %Pi number
Cs=0; %Compressiblity of solid grain
Cf=1e-7; %Compressiblity of water
Cm=2e-3;  %Compressiblity of porous media
gf=9.8064;  %Unit weight of water
n=0.6;   %Porosity
a=1;      %Dimension of model  
N=200;    %Number of roots  
eps=1e-10;%Error for finding roots
p0=98.064;   %Initial pore pressure  
H0s=1.0;  %Initial water table

%Step2: Calculate parameters
A=1-Cs/Cm; %Biot's coefficient
S=n*Cf+(A-n)*Cs; %Specific storage
K=1/Cm; %Bulk modulus
v=0.1;  %Poisson's ratio
G=3*K*(1-2*v)/2/(1+v); %Shear modulus
k=1e-9*60*60*24; %hydraulic conductivity
mv=1/(K+4*G/3); %Compressiblity
cv=k/(gf*(A*A*mv+S)); %Consolidation coefficient
eta=(1-v)/(1-2*v);
mc=0.5*eta*(A*A+S*(K+G/3))/A/A;

%Step 3: Find roots of equation

x=0;
for i=1:N
    a1=x+0.000001;     
    a2=x+1.2*PI;
    f1=2*mc*a1*besselj(0,a1)-besselj(1,a1);
    f2=2*mc*a2*besselj(0,a2)-besselj(1,a2);
    cont=true;
    while(cont)
        am=(a1+a2)/2;
        fm=2*mc*am*besselj(0,am)-besselj(1,am);
        if (f1*fm<0) 
            a2=am;f2=fm;
        elseif(f2*fm<0)
            a1=am;f1=fm;
        end        
        if((a2-a1)<0.0000001) 
            cont=false;
        end        
    end
    ZERO(i,1)=(a1+a2)/2;
    x=a2;
end

PorePressure=zeros(200,1);
timeStep=0.1;
for jj=1:200
    t=timeStep*jj;
    p=0;
    r=0.0;    
    for i=1:N
        x=ZERO(i,1);
        J0=besselj(0,x);
        J0r=besselj(0,x*r/a);
        b=-x*x*cv*t/a/a;
        low=(1-mc*x*x-1/(4*mc))*J0;
        p=p+(J0-J0r)*exp(b)/low;
    end
    p=p0*p;
    PorePressure(jj,1)=p;
end
totalHead=zeros(200,1);
totalHead=PorePressure/gf+H0s;
xlswrite('DeLeeuw.xls',totalHead);