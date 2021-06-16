#include <iostream>
#include <cmath>
#include <cstdlib>
#include <fstream>
using namespace std;

double E_x(double x){
    if(x >=0 && x<= 1){
        return 3.0;
    }else{
        return 5.0;
    }
}

double e_i_x(int n, int i, double x){
    if(1.0-abs(n/2.0*(x- 2.0*(double)i/ (double)n))>=0.0){
        return 1.0-abs(n/2.0*(x- 2.0*(double)i/ (double)n));
    }else{
        return 0.0;
    }
}

double e_der_i_x(int n, int i, double x){
   if(2.0* (double) (i-1)/(double) n <= x && x < 2.0*(double) i / (double) n){
        return n/2.0;
    }else if( 2.0*(double) i / (double) n<= x && x < 2.0 *(double)(i+1)/(double) n){
        return (-n)/2.0;
    }
    else{
        return 0.0;
    }
}


double b_u_v(int n,int u,int v,double int_start, double int_end){ //wi=1 xi= +/- sqrt(1/3) u,v represent number of ei
    double point1=((int_end-int_start)/2.0)*((-1.0)/sqrt(3))+(int_start+int_end)/2.0;
    double point2=((int_end-int_start)/2.0)*(1.0/sqrt(3))+(int_start+int_end)/2.0;

    return ((int_end-int_start)/2.0)*(E_x(point1)*e_der_i_x(n,u,point1)*e_der_i_x(n,v,point1)+
                                            E_x(point2)*e_der_i_x(n,u,point2)*e_der_i_x(n,v,point2))-
                                            3 * e_i_x(n,u,0.0) * e_i_x(n,v,0.0); // -3u(0)v(0)
}

double l_v(int n, int v){
    //if(v==0){
        return (-30.0)*e_i_x(n,v,0.0);
    //}else{
       // return 0.0;
    //}
}

//Funkcje u¿yte w celu rozwi¹zania liniowego uk³adu równañ powsta³y w oparciu
//o kod autorstwa mgr. Jerzego Wa³aszka ze strony eduinf.waw.pl
void ludist (int n, double ** A){
    for(int k=0;k<n-1;k++){
        for(int i=k+1;i<n;i++){
            A[i][k] /= A[k][k];
        }

        for(int i=k+1;i<n;i++){
            for(int j=k+1;j<n;j++){
                A[i][j] -= A[i][k]*A[k][j];
            }
        }
    }
}

void lusolve(int n, double ** A, double * B, double * X){
    X[0]=B[0];
    for(int i=1;i<n;i++){
        double s=0;
        for(int j=0;j<i;j++){
            s+= A[i][j]*X[j];
        }
        X[i]=B[i]-s;
    }
    X[n-1] /= A[n-1][n-1];
    for(int i=n-2;i>=0;i--){
        double s=0;
        for(int j=i+1;j<n;j++){
            s+= A[i][j]*X[j];
        }
        X[i]=(X[i]-s) / A[i][i];
    }
}

int main(){
    int n;
    cout<<"Podaj liczbe elementow: "<<endl;
    cin>>n;
    double **left;
    double *right;
    double *result;
    left= new double * [n+1];
    right = new double [n+1];
    result = new double [n+1];
    double start;
    double fin;
    for(int i=0;i<n+1;i++){
        right[i]=l_v(n,i);
        left[i]= new double [n+1];
        for(int j=0;j<n+1;j++){
            start=0.0;
            fin=2.0;
            if(i==n || j==n){ //Dirichlet
                if(i==n && j==n){
                    left[i][j]=1;
                }else{
                    left[i][j]=0;
                }
            }else{
                if(abs (i-j)==1){
                    start= max(0.0,2.0*min(i,j)/(double) n);
                    fin= min(2.0,2.0*max(i,j)/(double) n);
                }else if(i==j){
                    start= max(0.0,2.0*(double)(i-1)/(double) n);
                    fin= min(2.0,2.0*(double) (i+1)/(double) n);
                }

                left[i][j]=b_u_v(n,i,j,start,fin);
            }
           //cout<<left[i][j]<<" ";
        }
        //cout<<endl;
    }
    right[n]=0;
    /*cout<<"---------------"<<endl;
    for(int i=0;i<n+1;i++){
        cout<<right[i]<<endl;
    }*/
    ludist(n+1,left);
    lusolve(n+1,left,right,result);
    /*cout<<"---------------"<<endl;
    for(int i=0;i<n+1;i++){
        cout<<result[i]<<endl;
    }*/
    fstream file;
    file.open("dane.txt",ios::out);
    if(file.good()){
        double step=2.0/1000;
        for(int i=0;i<1000;i++){
            double y=0.0;
            for(int j=0;j<n+1;j++){
                y+=result[j]*e_i_x(n,j,step*i);
            }
            file<<step*i<<","<<y<<endl;

        }
        file.close();
    }
    for(int i=0;i<n+1;i++) delete [ ] left[i];
    delete [] left;
    delete [] right;
    delete [] result;
    system("PAUSE");
    return 0;
}
