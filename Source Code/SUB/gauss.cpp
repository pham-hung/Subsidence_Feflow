#include "gauss.h"

Gauss::Gauss()
{
    createGauss4();
    createGauss8();
    createGauss9();
    createGauss13();
    createGauss27();
}

void Gauss::createGauss4()
{
    gauss4=MatrixXd::Zero(4,4);
    gauss4(0,0)=0.585410;
    gauss4(0,1)=0.138197;
    gauss4(0,2)=0.138197;
    gauss4(0,3)=0.041667;

    gauss4(1,0)=0.138197;
    gauss4(1,1)=0.585410;
    gauss4(1,2)=0.138197;
    gauss4(1,3)=0.041667;

    gauss4(2,0)=0.138197;
    gauss4(2,1)=0.138197;
    gauss4(2,2)=0.585410;
    gauss4(2,3)=0.041667;

    gauss4(3,0)=0.138197;
    gauss4(3,1)=0.138197;
    gauss4(3,2)=0.138197;
    gauss4(3,3)=0.041667;
}

void Gauss::createGauss8()
{
    //2x2x2, for brick 8 nodes
    gauss8=MatrixXd::Zero(8,4);
    double gaussValue=0.57735;
    gauss8(0,0)=-gaussValue;
    gauss8(0,1)=-gaussValue;
    gauss8(0,2)=-gaussValue;
    gauss8(0,3)=1;

    gauss8(1,0)=gaussValue;
    gauss8(1,1)=-gaussValue;
    gauss8(1,2)=-gaussValue;
    gauss8(1,3)=1;

    gauss8(2,0)=gaussValue;
    gauss8(2,1)=-gaussValue;
    gauss8(2,2)=gaussValue;
    gauss8(2,3)=1;

    gauss8(3,0)=-gaussValue;
    gauss8(3,1)=-gaussValue;
    gauss8(3,2)=gaussValue;
    gauss8(3,3)=1;

    gauss8(4,0)=-gaussValue;
    gauss8(4,1)=gaussValue;
    gauss8(4,2)=-gaussValue;
    gauss8(4,3)=1;

    gauss8(5,0)=gaussValue;
    gauss8(5,1)=gaussValue;
    gauss8(5,2)=-gaussValue;
    gauss8(5,3)=1;

    gauss8(6,0)=gaussValue;
    gauss8(6,1)=gaussValue;
    gauss8(6,2)=gaussValue;
    gauss8(6,3)=1;

    gauss8(7,0)=-gaussValue;
    gauss8(7,1)=gaussValue;
    gauss8(7,2)=gaussValue;
    gauss8(7,3)=1;

}

void Gauss::createGauss9()
{
    gauss9=MatrixXd::Zero(9,4);
    double gauss1=sqrt(3.0/5.0);
    gauss9<<(1.0/6.0),(1.0/6.0),-gauss1,(1.0/6.0)*(5.0/9.0),
            (1.0/6.0),(2.0/3.0),-gauss1,(1.0/6.0)*(5.0/9.0),
            (2.0/3.0),(1.0/6.0),-gauss1,(1.0/6.0)*(5.0/9.0),
            (1.0/6.0),(1.0/6.0),0.0,(1.0/6.0)*(8.0/9.0),
            (1.0/6.0),(2.0/3.0),0.0,(1.0/6.0)*(8.0/9.0),
            (2.0/3.0),(1.0/6.0),0.0,(1.0/6.0)*(8.0/9.0),
            (1.0/6.0),(1.0/6.0),gauss1,(1.0/6.0)*(5.0/9.0),
            (1.0/6.0),(2.0/3.0),gauss1,(1.0/6.0)*(5.0/9.0),
            (2.0/3.0),(1.0/6.0),gauss1,(1.0/6.0)*(5.0/9.0);
}

void Gauss::createGauss27()
{
    //3x3x3,for brick 20-nodes
    gauss27=MatrixXd::Zero(27,4);
    double g1=-sqrt(3.0/5.0);
    double g2=0;
    double g3=sqrt(3.0/5.0);
    double w1=5.0/9.0;
    double w2=8.0/9.0;
    double w3=5.0/9.0;

    gauss27<<g1,g1,g1,w1*w1*w1,
            g2,g1,g1,w2*w1*w1,
            g3,g1,g1,w3*w1*w1,
            g3,g2,g1,w3*w2*w1,
            g3,g3,g1,w3*w3*w1,
            g2,g3,g1,w2*w3*w1,
            g1,g3,g1,w1*w3*w1,
            g1,g2,g1,w1*w2*w1,
            g2,g2,g1,w2*w2*w1,
            g1,g1,g2,w1*w1*w2,
            g2,g1,g2,w2*w1*w2,
            g3,g1,g2,w3*w1*w2,
            g3,g2,g2,w3*w2*w2,
            g3,g3,g2,w3*w3*w2,
            g2,g3,g2,w2*w3*w2,
            g1,g3,g2,w1*w3*w2,
            g1,g2,g2,w1*w2*w2,
            g2,g2,g2,w2*w2*w2,
            g1,g1,g3,w1*w1*w3,
            g2,g1,g3,w2*w1*w3,
            g3,g1,g3,w3*w1*w3,
            g3,g2,g3,w3*w2*w3,
            g3,g3,g3,w3*w3*w3,
            g2,g3,g3,w2*w3*w3,
            g1,g3,g3,w1*w3*w3,
            g1,g2,g3,w1*w2*w3,
            g2,g2,g3,w2*w2*w3;

}

void Gauss::createGauss13()
{
    //13 gauss points, for Pyramid elements
    gauss13=MatrixXd::Zero(13,4);
    double g1=(7.0/8.0)*sqrt(35.0/39.0);
    double g2=0.6106396;
    double g3=(1.0/56.0)*sqrt(37043.0/35.0);
    double g4=(-1.0/7.0);
    double g5=(-9.0/28.0);
    double g6=0.524394;
    double g7=(-127.0/153.0);
    double w1=0.515003;
    double w2=0.2571837;
    double w3=2.4740050;
    double w4=0.4195157;
    gauss13<<-g1,-g1,g4,w1,
            g1,-g1,g4,w1,
            g1,g1,g4,w1,
            -g1,g1,g4,w1,
            -g2,0,g5,w2,
            g2,0,g5,w2,
            0,-g2,g5,w2,
            0,g2,g5,w2,
            0,0,g6,w3,
            -g3,-g3,g7,w4,
            g3,-g3,g7,w4,
            g3,g3,g7,w4,
            -g3,g3,g7,w4;

}
