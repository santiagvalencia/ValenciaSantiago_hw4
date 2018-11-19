#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <array>
#include <string>

using namespace std;

double dx_dt(double vx); //funcion que retorna la derivada de x
double dy_dt(double vy); //funcion que retorna la derivada de y
double dvy_dt(double vx, double vy); //funcion que retorna la derivada de vx
double dvx_dt(double vx, double vy); //funcion que retorna la derivada de vy
double RungeKutta(double theta, string nombre); //funcion que soluciona la ODE y retorna el rango del proyectil
//constantes del problema
#define PI 3.14159265359
#define N 100000
#define g 10.0
#define c 0.2
#define m 0.2
#define dt 0.00001
#define v0 300.0

int main(){
  //calcula el rango de los lanzamientos con cada angulo
  double x_45 = RungeKutta(45, "RG_45.txt");
  double x_10 = RungeKutta(10, "RG_10.txt");
  double x_20 = RungeKutta(20, "RG_20.txt");
  double x_30 = RungeKutta(30, "RG_30.txt");
  double x_40 = RungeKutta(40, "RG_40.txt");
  double x_50 = RungeKutta(50, "RG_50.txt");
  double x_60 = RungeKutta(60, "RG_60.txt");
  double x_70 = RungeKutta(70, "RG_70.txt");

  cout << "\nDistancia recorrida por el proyectil (45 grados): " << x_45 << " m" << "\n";
  //pone los angulos y las distancias en arreglos
  double angulos[8] = {45, 10, 20, 30, 40, 50, 60, 70};
  double distancias[8] = {x_45, x_10, x_20, x_30, x_40, x_50, x_60, x_70};

  int i; int j; double temp_d; double temp_a;
  //organiza las distancias y angulos de menor a mayor segun el algoritmo de ordenamiento burbuja
  for(i=0; i<8; i++)
  {
    for (j=i+1; j<8; j++)
    {
      if (distancias[j]<distancias[i])
      {
        temp_d = distancias[i];
        temp_a = angulos[i];
        distancias[i] = distancias[j];
        angulos[i] = angulos[j];
        distancias[j] = temp_d;
        angulos[j] = temp_a;
      }
    }
  }

  cout << "La mayor distancia alcanzada es de " << distancias[7]<< " m y corresponde a un angulo de " << angulos[7] <<" grados."<< "\n";

}

double dx_dt(double vx){//derivada de x
  return vx;
}

double dy_dt(double vy){//derivada de y
  return vy;
}

double dvx_dt(double vx, double vy){//derivada de vx segun la formula dada
  return -c*sqrt(vx*vx + vy*vy)*vx/m;
}

double dvy_dt(double vx, double vy){//derivada de vy segun la formula dada
  return -g - c*sqrt(vx*vx + vy*vy)*vy/m;
}

double RungeKutta(double theta, string nombre){//funcion que soluciona la ODE para un angulo dado y guarda los datos en un archivo con nombre dado

  ofstream archivo;//abre el archivo y lo nombra segun se especifica
  archivo.open(nombre);
  //crea los arreglos necesarios para resolver el problema
  double x[N];
  double y[N];
  double vx[N];
  double vy[N];
  double t[N];
  double v[N];

  theta = theta*PI/180; //convierte el angulo en radianes
  //define el primer punto de cada arreglo segun las condiciones iniciales
  x[0] = 0;
  y[0] = 0;
  vx[0] = v0*cos(theta);
  vy[0] = v0*sin(theta);
  t[0] = 0;
  v[0] = v0;
  //imprime las condiciones iniciales en el archivo
  archivo << t[0] << " " << x[0] << " " << y[0] << " " << vx[0] << " " << vy[0] << " " << v[0] << "\n";
  //crea las variables necesarias para el metodo Runge-Kutta
  double k1_prima_x; double k1_prima_y; double k1_prima_vx; double k1_prima_vy;
  double k2_prima_x; double k2_prima_y; double k2_prima_vx; double k2_prima_vy;
  double k3_prima_x; double k3_prima_y; double k3_prima_vx; double k3_prima_vy;
  double k4_prima_x; double k4_prima_y; double k4_prima_vx; double k4_prima_vy;

  double x_1; double y_1; double vx_1; double vy_1;
  double x_2; double y_2; double vx_2; double vy_2;
  double x_3; double y_3; double vx_3; double vy_3;

  double k_prom_x; double k_prom_y; double k_prom_vx; double k_prom_vy;
  //recorre los arreglos sin cambiar las condiciones iniciales
  for(int i=1; i<N; i++){
    //Primer paso Runge-Kutta
    k1_prima_x = dx_dt(vx[i-1]);
    k1_prima_y = dy_dt(vy[i-1]);
    k1_prima_vx = dvx_dt(vx[i-1], vy[i-1]);
    k1_prima_vy = dvy_dt(vx[i-1], vy[i-1]);
    //Segundo paso Runge-Kutta
    x_1 = x[i-1] + (dt/2)*k1_prima_x;
    y_1 = y[i-1] + (dt/2)*k1_prima_y;
    vx_1 = vx[i-1] + (dt/2)*k1_prima_vx;
    vy_1 = vy[i-1] + (dt/2)*k1_prima_vy;
    k2_prima_x = dx_dt(vx_1);
    k2_prima_y = dy_dt(vy_1);
    k2_prima_vx = dvx_dt(vx_1, vy_1);
    k2_prima_vy = dvy_dt(vx_1, vy_1);
    //Tercer paso Runge-Kutta
    x_2 = x[i-1] + (dt/2)*k2_prima_x;
    y_2 = y[i-1] + (dt/2)*k2_prima_y;
    vx_2 = vx[i-1] + (dt/2)*k2_prima_vx;
    vy_2 = vy[i-1] + (dt/2)*k2_prima_vy;
    k3_prima_x = dx_dt(vx_2);
    k3_prima_y = dy_dt(vy_2);
    k3_prima_vx = dvx_dt(vx_2, vy_2);
    k3_prima_vy = dvy_dt(vx_2, vy_2);
    //Cuarto paso Runge-Kutta
    x_3 = x[i-1] + dt*k2_prima_x;
    y_3 = y[i-1] + dt*k2_prima_y;
    vx_3 = vx[i-1] + dt*k2_prima_vx;
    vy_3 = vy[i-1] + dt*k2_prima_vy;
    k4_prima_x = dx_dt(vx_3);
    k4_prima_y = dy_dt(vy_3);
    k4_prima_vx = dvx_dt(vx_3, vy_3);
    k4_prima_vy = dvy_dt(vx_3, vy_3);
    //Promedios
    k_prom_x = (k1_prima_x + 2*k2_prima_x + 2*k3_prima_x + k4_prima_x);
    k_prom_y = (k1_prima_y + 2*k2_prima_y + 2*k3_prima_y + k4_prima_y);
    k_prom_vx = (k1_prima_vx + 2*k2_prima_vx + 2*k3_prima_vx + k4_prima_vx);
    k_prom_vy = (k1_prima_vy + 2*k2_prima_vy + 2*k3_prima_vy + k4_prima_vy);
    //Actualiza los valores de los arreglos
    t[i] = t[i-1] + dt;
    x[i] = x[i-1] + dt*k_prom_x;
    y[i] = y[i-1] + dt*k_prom_y;
    vx[i] = vx[i-1] + dt*k_prom_vx;
    vy[i] = vy[i-1] + dt*k_prom_vy;
    v[i] = sqrt(vx[i]*vx[i] + vy[i]*vy[i]);
    //Si la posicion vertical llega al piso cierra el archivo y retorna el valor de x (el rango del tiro), lo que termina el ciclo
    if(y[i]<0){
      archivo.close();
      return x[i];
    }
    //Imprime los datos en el archivo
    archivo << t[i] << " " << x[i] << " " << y[i] << " " << vx[i] << " " << vy[i] << " " << v[i] << "\n";
  }
  //Si el lanzamiento no llega al piso despues de N-1 iteraciones la funcion retorna 0
  return 0;
}
