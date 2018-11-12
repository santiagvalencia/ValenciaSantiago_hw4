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
double dvx_dt(double vx, double vy);

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

  double k1_prima_x; double k1_prima_y; double k1_prima_vx; double k1_prima_vy;
  double k2_prima_x; double k2_prima_y; double k2_prima_vx; double k2_prima_vy;
  double k3_prima_x; double k3_prima_y; double k3_prima_vx; double k3_prima_vy;
  double k4_prima_x; double k4_prima_y; double k4_prima_vx; double k4_prima_vy;

  double x_1; double y_1; double vx_1; double vy_1;
  double x_2; double y_2; double vx_2; double vy_2;
  double x_3; double y_3; double vx_3; double vy_3;

  double k_prom_x; double k_prom_y; double k_prom_vx; double k_prom_vy;

for(int i=1; i<N; i++){
  k1_prima_x = dx_dt(vx[i-1]);
  k1_prima_y = dy_dt(vy[i-1]);
  k1_prima_vx = dvx_dt(vx[i-1], vy[i-1]);
  k1_prima_vy = dvy_dt(vx[i-1], vy[i-1]);

  x_1 = x[i-1] + (dt/2)*k1_prima_x;
  y_1 = y[i-1] + (dt/2)*k1_prima_y;
  vx_1 = vx[i-1] + (dt/2)*k1_prima_vx;
  vy_1 = vy[i-1] + (dt/2)*k1_prima_vy;
  k2_prima_x = dx_dt(vx_1);
  k2_prima_y = dy_dt(vy_1);
  k2_prima_vx = dvx_dt(vx_1, vy_1);
  k2_prima_vy = dvy_dt(vx_1, vy_1);

  x_2 = x[i-1] + (dt/2)*k2_prima_x;
  y_2 = y[i-1] + (dt/2)*k2_prima_y;
  vx_2 = vx[i-1] + (dt/2)*k2_prima_vx;
  vy_2 = vy[i-1] + (dt/2)*k2_prima_vy;
  k3_prima_x = dx_dt(vx_2);
  k3_prima_y = dy_dt(vy_2);
  k3_prima_vx = dvx_dt(vx_2, vy_2);
  k3_prima_vy = dvy_dt(vx_2, vy_2);

  x_3 = x[i-1] + dt*k2_prima_x;
  y_3 = y[i-1] + dt*k2_prima_y;
  vx_3 = vx[i-1] + dt*k2_prima_vx;
  vy_3 = vy[i-1] + dt*k2_prima_vy;
  k4_prima_x = dx_dt(vx_3);
  k4_prima_y = dy_dt(vy_3);
  k4_prima_vx = dvx_dt(vx_3, vy_3);
  k4_prima_vy = dvy_dt(vx_3, vy_3);

  k_prom_x = (k1_prima_x + 2*k2_prima_x + 2*k3_prima_x + k4_prima_x);
  k_prom_y = (k1_prima_y + 2*k2_prima_y + 2*k3_prima_y + k4_prima_y);
  k_prom_vx = (k1_prima_vx + 2*k2_prima_vx + 2*k3_prima_vx + k4_prima_vx);
  k_prom_vy = (k1_prima_vy + 2*k2_prima_vy + 2*k3_prima_vy + k4_prima_vy);

  t[i] = t[i-1] + dt;
  x[i] = x[i-1] + dt*k_prom_x;
  y[i] = y[i-1] + dt*k_prom_y;
  vx[i] = vx[i-1] + dt*k_prom_vx;
  vy[i] = vy[i-1] + dt*k_prom_vy;

  cout << t[i] << " " << x[i] << " " << y[i] << " " << vx[i] << " " << vy[i] << "\n";

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
