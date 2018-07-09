#include "elementmatrix.h"

elementMatrix::elementMatrix(QObject *parent) : QObject(parent)
{

}

void elementMatrix::assemblyMatrix()
{
    checkFinish=false;
    gauss=gaussPoint.gauss9;
    Cfe=1e-7;
    gf=9.8604;

    numberOfNode=coordinates.rows();
    numberOfElement=elements.rows();
    totalDegreeOfFreedom=4*numberOfNode;


    trip_total.clear();
    trip_total.resize(0);
    trip_total.reserve(30*30*numberOfElement);
    F.resize(totalDegreeOfFreedom,1);
    F.setZero();

    for (int i=startElement;i<endElement;i++)
    {
        eleNum=i;
        prism6pMatrix(eleNum);
    }

    checkFinish=true;
}

void elementMatrix::prism6pMatrix(int &eleNum)
{
    int ii=eleNum;
    kxe=hydroParameters(ii,1);
    kye=hydroParameters(ii,2);
    kze=hydroParameters(ii,3);
    Ke=mechanicalParameters(ii,0);
    ve=mechanicalParameters(ii,1);
    Ge=3*Ke*(1-2*ve)/2.0f/(1+ve);
    ne=mechanicalParameters(ii,2);
    Cse=mechanicalParameters(ii,3);
    Cme=1/Ke;
    BiotCoeff=1-Cse/Cme;
    Se=ne*Cfe+(BiotCoeff-ne)*Cse;

    //Initial vector
    MatrixXd u0=MatrixXd::Zero(6,1);
    MatrixXd v0=MatrixXd::Zero(6,1);
    MatrixXd w0=MatrixXd::Zero(6,1);
    MatrixXd h0=MatrixXd::Zero(6,1);
    MatrixXd hinitial=MatrixXd::Zero(6,1);

    MatrixXd nodeIndex=MatrixXd::Zero(6,1);
    MatrixXd index_total=MatrixXd::Zero(24,1);
    MatrixXd X_coor=MatrixXd::Zero(6,1);
    MatrixXd Y_coor=MatrixXd::Zero(6,1);
    MatrixXd Z_coor=MatrixXd::Zero(6,1);

    //Shape function
    double g1,g2,g3,g4,wi;
    MatrixXd N=MatrixXd::Zero(1,6);
    MatrixXd dNL1=MatrixXd::Zero(1,6);
    MatrixXd dNL2=MatrixXd::Zero(1,6);
    MatrixXd dNL3=MatrixXd::Zero(1,6);

    MatrixXd jacobi=MatrixXd::Zero(3,3);
    MatrixXd jacobiLeft=MatrixXd::Zero(3,6);
    MatrixXd jacobiRight=MatrixXd::Zero(6,3);

    MatrixXd dN=MatrixXd::Zero(3,6);
    MatrixXd dNx=MatrixXd::Zero(1,6);
    MatrixXd dNy=MatrixXd::Zero(1,6);
    MatrixXd dNz=MatrixXd::Zero(1,6);

    //Element matrix
    MatrixXd Al=MatrixXd::Zero(6,6);
    MatrixXd Bl=MatrixXd::Zero(6,6);
    MatrixXd Cl=MatrixXd::Zero(6,6);
    MatrixXd Dl=MatrixXd::Zero(6,6);
    MatrixXd El=MatrixXd::Zero(6,6);
    MatrixXd Fl=MatrixXd::Zero(6,6);
    MatrixXd Gl=MatrixXd::Zero(6,6);
    MatrixXd Hl=MatrixXd::Zero(6,6);
    MatrixXd Il=MatrixXd::Zero(6,6);
    MatrixXd Jl=MatrixXd::Zero(6,6);
    MatrixXd Ll=MatrixXd::Zero(6,6);
    MatrixXd Ml=MatrixXd::Zero(6,6);
    MatrixXd Nl=MatrixXd::Zero(6,6);
    MatrixXd Ol=MatrixXd::Zero(6,6);
    MatrixXd Pl=MatrixXd::Zero(6,6);
    MatrixXd Ql=MatrixXd::Zero(6,6);
    MatrixXd Ql1=MatrixXd::Zero(6,6);
    MatrixXd Ql2=MatrixXd::Zero(6,6);
    //Fluid matrix
    MatrixXd Kl=MatrixXd::Zero(24,24);
    //Load vector
    MatrixXd QQl=MatrixXd::Zero(6,1);
    MatrixXd Fxl=MatrixXd::Zero(6,1);
    MatrixXd Fyl=MatrixXd::Zero(6,1);
    MatrixXd Fzl=MatrixXd::Zero(6,1);

    //Get coordinates and index
    for (auto j=0;j<6;j++)
    {
        int index=elements(ii,j+1)-1;
        nodeIndex(j,0)=index;
        u0(j,0)=U0(index,0);
        v0(j,0)=V0(index,0);
        w0(j,0)=W0(index,0);
        h0(j,0)=H0(index,0);
        hinitial(j,0)=initialH(index,1);

        X_coor(j,0)=coordinates(index,1);
        Y_coor(j,0)=coordinates(index,2);
        Z_coor(j,0)=coordinates(index,3);

        index_total(j,0)=index;
        index_total(6+j,0)=numberOfNode+index;
        index_total(12+j,0)=2*numberOfNode+index;
        index_total(18+j,0)=3*numberOfNode+index;
    }

    //Loop over gaussian points
    for (auto jj=0;jj<gauss.rows();jj++)
    {
        g1=gauss(jj,0); g2=gauss(jj,1); g3=gauss(jj,2); wi=gauss(jj,3);
        g4=1.0-g1-g2;

        //6 Nodes shape function
        N(0,0)=0.5*g1*(1.0-g3);
        N(0,1)=0.5*g2*(1.0-g3);
        N(0,2)=0.5*g4*(1.0-g3);
        N(0,3)=0.5*g1*(1.0+g3);
        N(0,4)=0.5*g2*(1.0+g3);
        N(0,5)=0.5*g4*(1.0+g3);

        dNL1(0,0)=0.5*(1.0-g3);
        dNL1(0,1)=0.0;
        dNL1(0,2)=-0.5*(1.0-g3);
        dNL1(0,3)=0.5*(1.0+g3);
        dNL1(0,4)=0.0;
        dNL1(0,5)=-0.5*(1.0+g3);

        dNL2(0,0)=0;
        dNL2(0,1)=0.5*(1.0-g3);
        dNL2(0,2)=-0.5*(1.0-g3);
        dNL2(0,3)=0.0;
        dNL2(0,4)=0.5*(1.0+g3);
        dNL2(0,5)=-0.5*(1.0+g3);

        dNL3(0,0)=-0.5*g1;
        dNL3(0,1)=-0.5*g2;
        dNL3(0,2)=-0.5*g4;
        dNL3(0,3)=0.5*g1;
        dNL3(0,4)=0.5*g2;
        dNL3(0,5)=0.5*g4;

        jacobiLeft<<dNL1,dNL2,dNL3;
        jacobiRight<<X_coor,Y_coor,Z_coor;
        jacobi=jacobiLeft*jacobiRight;
        double detj;
        detj=abs(jacobi.determinant());

        dN=jacobi.inverse()*jacobiLeft;
        dNx=dN.row(0);
        dNy=dN.row(1);
        dNz=dN.row(2);

        //Element matrix
        Al=Al+wi*detj*((Ke+4*Ge/3)*dNx.transpose()*dNx+Ge*dNy.transpose()*dNy+Ge*dNz.transpose()*dNz);
        Bl=Bl+wi*detj*((Ke-2*Ge/3)*dNx.transpose()*dNy+Ge*dNy.transpose()*dNx);
        Cl=Cl+wi*detj*((Ke-2*Ge/3)*dNx.transpose()*dNz+Ge*dNz.transpose()*dNx);

        Fl=Fl+wi*detj*((Ke+4*Ge/3)*dNy.transpose()*dNy+Ge*dNx.transpose()*dNx+Ge*dNz.transpose()*dNz);
        El=El+wi*detj*((Ke-2*Ge/3)*dNy.transpose()*dNx+Ge*dNx.transpose()*dNy);
        Gl=Gl+wi*detj*((Ke-2*Ge/3)*dNy.transpose()*dNz+Ge*dNz.transpose()*dNy);

        Ll=Ll+wi*detj*((Ke+4*Ge/3)*dNz.transpose()*dNz+Ge*dNx.transpose()*dNx+Ge*dNy.transpose()*dNy);
        Il=Il+wi*detj*((Ke-2*Ge/3)*dNz.transpose()*dNx+Ge*dNx.transpose()*dNz);
        Jl=Jl+wi*detj*((Ke-2*Ge/3)*dNz.transpose()*dNy+Ge*dNy.transpose()*dNz);

        //total Head
        Dl=Dl-gf*BiotCoeff*detj*wi*dNx.transpose()*N;
        Hl=Hl-gf*BiotCoeff*detj*wi*dNy.transpose()*N;
        Ml=Ml-gf*BiotCoeff*detj*wi*dNz.transpose()*N;

        Ql1=Ql1+Se*gf*detj*wi*N.transpose()*N;
        Ql2=Ql2+detj*wi*((kxe/1.0f)*dNx.transpose()*dNx+(kye/1.0f)*dNy.transpose()*dNy+(kze/1.0f)*dNz.transpose()*dNz);

    } //End loop over gaussian points

    //pore pressure
    //    Nl=-1*Dl.transpose();
    //    Ol=-1*Hl.transpose();
    //    Pl=-1*Ml.transpose();
    //    Ql=Ql1+dt*Ql2;
    //    QQl=Nl*u0+Ol*v0+Pl*w0+Ql1*h0;

    //total Head
    Nl=-1*Dl.transpose()/gf;
    Ol=-1*Hl.transpose()/gf;
    Pl=-1*Ml.transpose()/gf;
    Ql=Ql1+timeIncrement*Ql2;
    QQl=Nl*u0+Ol*v0+Pl*w0+Ql1*h0;

    Kl<<Al,Bl,Cl,Dl,
            El,Fl,Gl,Hl,
            Il,Jl,Ll,Ml,
            Nl,Ol,Pl,Ql;

    //Transfer QQl to F
    for (int j=0;j<6;j++)
    {
        F(nodeIndex(j,0)+3*numberOfNode,0)=F(nodeIndex(j,0)+3*numberOfNode,0)+QQl(j,0);
    }

    Fxl=Dl*hinitial;
    Fyl=Hl*hinitial;
    Fzl=Ml*hinitial;

    //total Head
    for (int j=0;j<6;j++)
    {
        F(nodeIndex(j,0)+0*numberOfNode,0)=F(nodeIndex(j,0)+0*numberOfNode,0)+Fxl(j,0);
        F(nodeIndex(j,0)+1*numberOfNode,0)=F(nodeIndex(j,0)+1*numberOfNode,0)+Fyl(j,0);
        F(nodeIndex(j,0)+2*numberOfNode,0)=F(nodeIndex(j,0)+2*numberOfNode,0)+Fzl(j,0);
    }

    //Assign boundary condition
    for (int j=0;j<Kl.rows();j=j+1)
    {
        int jj=DirichletAll(index_total(j,0),1);
        double boundaryValue=DirichletAll(index_total(j,0),2);
        if(jj==1)
        {
            for (int k1=0;k1<Kl.cols();k1=k1+1)
            {
                int kk=index_total(k1,0);
                F(kk,0)=F(kk,0)-Kl(k1,j)*boundaryValue;
            }
            Kl.row(j).setZero();
            Kl.col(j).setZero();
            Kl(j,j)=1;
        }
    }

    //Push back Kl to trip_total
    for (int j=0;j<Kl.rows();j++)
    {
        for (int jj=0;jj<Kl.cols();jj++)
        {
            int row_i=index_total(j,0);
            int col_j=index_total(jj,0);
            double val_ij=Kl(j,jj);
            trip_total.push_back(Trip(row_i,col_j,val_ij));
        }
    }
}
