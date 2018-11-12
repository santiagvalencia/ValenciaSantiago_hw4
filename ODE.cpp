#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <array>

using namespace std;

double dx_dt(double vx);
double dy_dt(double vy);
double dvy_dt(double vx, double vy);
double dvy_dt(double vx, double vy);

#define PI 3.14159265359
#define N 10000
#define g 10.0
#define c 0.2
#define m 0.2
#define dt 0.001

int main(){
  double x[N];
  double y[N];
  double vx[N];
  double vy[N];
  double t[N];

  double theta = 45*PI/180;
  double v0 = 300;

  x[0] = 0;
  y[0] = 0;
  vx[0] = 300*cos(theta);
  vy[0] = 300*sin(theta);
  t[0] = 0;

  double k1_prima_x;
  double k1_prima_y;
  double k1_prima_vx;
  double k1_prima vy;

for(int i=1; i<N; i++){
  k1_prima_x = dx_dt(x[i-1], vx[i-1]);
  k1_prima_y = dy_dt(y[i-1], vy[i-1]);
  k1_prima_vx = dvx_dt()








}



}

double dx_dt(double vx){
  return vx;
}

double dy_dt(double vy){
  return vy;
}

double dvx_dt(double vx, double vy){
  return -c*sqrt(vx*vx + vy*vy)*vx/m;
}

double dvy_dt(double vx, double vy){
  return -g - c*sqrt(vx*vx + vy*vy)*vy/m;
}
