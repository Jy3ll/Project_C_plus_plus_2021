#include "processor.h"


Processor::Processor()
{
    number_of_points=0;
    left=nullptr;
    right=nullptr;
    result=nullptr;
}

void Processor::free_space(){
    if(left){
        for(int i=0;i<number_of_points;i++){
            delete [] left[i];
        }
        delete [] left;
    }
    if(right){
        delete [] right;
    }

    if(result){
        delete [] result;
    }
}

Processor::~Processor(){
    free_space();
}

double Processor::E_x(double x){
    if(x >=0 && x<= 1){
        return 3.0;
    }else{
        return 5.0;
    }
}


double Processor::e_i_x(int n, int i, double x){
    if(1.0-abs(n/2.0*(x- 2.0*(double)i/ (double)n))>=0.0){
        return 1.0-abs(n/2.0*(x- 2.0*(double)i/ (double)n));
    }else{
        return 0.0;
    }
}

double Processor::e_der_i_x(int n,  int i, double x){
    if(2.0* (double) (i-1)/(double) n <= x && x < 2.0*(double) i / (double) n){
         return n/2.0;
     }else if( 2.0*(double) i / (double) n<= x && x < 2.0 *(double)(i+1)/(double) n){
         return (-n)/2.0;
     }
     else{
         return 0.0;
     }
}

double Processor::b_u_v(int n,int u,int v,double int_start, double int_end){
    double point1=((int_end-int_start)/2.0)*((-1.0)/sqrt(3))+(int_start+int_end)/2.0;
    double point2=((int_end-int_start)/2.0)*(1.0/sqrt(3))+(int_start+int_end)/2.0;

    return ((int_end-int_start)/2.0)*(E_x(point1)*e_der_i_x(n,u,point1)*e_der_i_x(n,v,point1)+
                                            E_x(point2)*e_der_i_x(n,u,point2)*e_der_i_x(n,v,point2))-
                                            3 * e_i_x(n,u,0.0) * e_i_x(n,v,0.0);
}

double Processor::l_v(int n, int v){
    return (-30.0)*e_i_x(n,v,0.0);
}

//Funkcje użyte w celu rozwiązania liniowego układu równań powstały w oparciu
//o kod autorstwa mgr. Jerzego Wałaszka ze strony eduinf.waw.pl
void Processor::ludist (int n, double ** A){
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
void Processor::lusolve(int n, double ** A, double * B, double * X){
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

double * Processor::process(int n){
    free_space();
    number_of_points=n;
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
                    start= std::max(0.0,2.0*std::min(i,j)/(double) n);
                    fin= std::min(2.0,2.0*std::max(i,j)/(double) n);
                }else if(i==j){
                    start= std::max(0.0,2.0*(double)(i-1)/(double) n);
                    fin= std::min(2.0,2.0*(double) (i+1)/(double) n);
                }

                left[i][j]=b_u_v(n,i,j,start,fin);
            }
        }

    }
    right[n]=0;
    //Solving
    ludist(n+1,left);
    lusolve(n+1,left,right,result);
    return result;
}

double Processor::calculate_result(double value){
    double y=0.0;
    for(int j=0;j<number_of_points+1;j++){
       y+=result[j]*e_i_x(number_of_points,j,value);
    }
    return y;
}

