#ifndef PROCESSOR_H
#define PROCESSOR_H
#include <QMainWindow>
#include <cmath>
#include <algorithm>

class Processor
{
public:
    Processor();
    ~Processor();
    double * process(int n);
    double calculate_result(double value);
private:
    int number_of_points;
    double **left;
    double *right;
    double *result;

    void free_space();


    double E_x(double x);
    double e_i_x(int n, int i, double x);
    double e_der_i_x(int n, int i, double x);
    double b_u_v(int n, int u,int v,double int_start, double int_end);
    double l_v(int n, int v);

    //Funkcje użyte w celu rozwiązania liniowego układu równań powstały w oparciu
    //o kod autorstwa mgr. Jerzego Wałaszka ze strony eduinf.waw.pl
    void ludist (int n, double ** A);
    void lusolve(int n, double ** A, double * B, double * X);
};

#endif // PROCESSOR_H
