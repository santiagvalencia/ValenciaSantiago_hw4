#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <array>
#include <string>

using namespace std;

#define k 1.62
#define Cp 820.0
#define rho 2710.0
#define nu k/(Cp*rho)
#define N 100//1000
#define D 0.1
#define T0 10.0
#define Tv 100.0
#define L 0.5
#define R D/2
#define dx L/N
#define dy L/N
#define dt (dx*dx*dy*dy)/(2*nu*(dx*dx+dy*dy))

double promedio(double M[N][N]);
void imprimir(double M[N][N], double t, string nombre);

int main(){
  static double T_inicial[N][N];
  static double T_pasadoF[N][N];
  static double T_presenteF[N][N];

  static double T_pasadoA[N][N];
  static double T_presenteA[N][N];

  static double T_pasadoP[N][N];
  static double T_presenteP[N][N];

  double r2;
  double centro_x = L/2; double centro_y = L/2;

  for(int i=0; i<N; i++){
    for(int j=0; j<N; j++){
      r2 = (i*dx-centro_x)*(i*dx-centro_x) + (j*dy-centro_y)*(j*dy-centro_y);
      if(r2 > R*R){
        T_inicial[i][j] = T0;
      }
      else{
        T_inicial[i][j] = Tv;
      }
    }
  }

  imprimir(T_inicial, 0, "inicial.txt");

  for(int i=0; i<N; i++){
    for(int j=0; j<N; j++){
      T_pasadoF[i][j] = T_inicial[i][j];
      T_pasadoA[i][j] = T_inicial[i][j];
      T_pasadoP[i][j] = T_inicial[i][j];
    }
  }

  double T_final = 500000;
  double step = dt;
  int n_pasos = T_final/step;
  double t;
  ofstream promedios;
  promedios.open("promedios.txt");

  for(int n=0; n<n_pasos; n++){
    t = n*step;
    for(int i=1; i<N-1; i++){
      for(int j=1; j<N-1; j++){
        r2 = (i*dx-centro_x)*(i*dx-centro_x) + (j*dy-centro_y)*(j*dy-centro_y);
        if(r2 > R*R){
          T_presenteF[i][j] = T_pasadoF[i][j] + dt*nu*((T_pasadoF[i+1][j]-2*T_pasadoF[i][j]+T_pasadoF[i-1][j])/(dx*dx) + (T_pasadoF[i][j+1]-2*T_pasadoF[i][j]+T_pasadoF[i][j-1])/(dy*dy));
          T_presenteA[i][j] = T_pasadoA[i][j] + dt*nu*((T_pasadoA[i+1][j]-2*T_pasadoA[i][j]+T_pasadoA[i-1][j])/(dx*dx) + (T_pasadoA[i][j+1]-2*T_pasadoA[i][j]+T_pasadoA[i][j-1])/(dy*dy));
          T_presenteP[i][j] = T_pasadoP[i][j] + dt*nu*((T_pasadoP[i+1][j]-2*T_pasadoP[i][j]+T_pasadoP[i-1][j])/(dx*dx) + (T_pasadoP[i][j+1]-2*T_pasadoP[i][j]+T_pasadoP[i][j-1])/(dy*dy));
        }
        else{
          T_presenteF[i][j] = Tv;
          T_presenteA[i][j] = Tv;
          T_presenteP[i][j] = Tv;
        }
      }
    }
    for(int i=0; i<N; i++){
      T_presenteF[N-1][i] = T0;
      T_presenteF[0][i] = T0;
      T_presenteF[i][N-1] = T0;
      T_presenteF[i][0] = T0;

      T_presenteA[N-1][i] = T_presenteA[N-2][i];
      T_presenteA[0][i] = T_presenteA[1][i];
      T_presenteA[i][N-1] = T_presenteA[i][N-2];
      T_presenteA[i][0] = T_presenteA[i][1];

      T_presenteP[N-1][i] = T_presenteP[N-2][i];
      T_presenteP[0][i] = T_presenteP[N-1][i];
      T_presenteP[i][N-1] = T_presenteP[i][N-2];
      T_presenteP[i][0] = T_presenteP[i][N-1];
    }

    for(int i=0; i<N; i++){
      for(int j=0; j<N; j++){
        T_pasadoF[i][j] = T_presenteF[i][j];
        T_pasadoA[i][j] = T_presenteA[i][j];
        T_pasadoP[i][j] = T_presenteP[i][j];
      }
    }
    promedios << t << " " << promedio(T_presenteF) << " " << promedio(T_presenteA) << " "<< promedio(T_presenteP) << "\n";

    if(n==int(5000/step)){
      imprimir(T_presenteF, t, "intermedio1_F.txt");
    }
    if(n==int(10000/step)){
      imprimir(T_presenteF, t, "intermedio2_F.txt");
    }
    if(n==int(20000/step)){
      imprimir(T_presenteA, t, "intermedio1_A.txt");
      imprimir(T_presenteP, t, "intermedio1_P.txt");
    }
    else if(n==int(85000/step)){
      imprimir(T_presenteA, t, "intermedio2_A.txt");
      imprimir(T_presenteP, t, "intermedio2_P.txt");
    }
  }
  promedios.close();
  imprimir(T_presenteF, t, "final_F.txt");
  imprimir(T_presenteA, t, "final_A.txt");
  imprimir(T_presenteP, t, "final_P.txt");
}

double promedio(double M[N][N]){
  double suma = 0;
  for(int i=0; i<N; i++){
    for(int j=0; j<N; j++){
      suma += M[i][j];
    }
  }
  suma /= (N*N);
  return suma;
}

void imprimir(double M[N][N], double t, string nombre){
  ofstream archivo;
  archivo.open(nombre);
  for(int i=0; i<N; i++){
    for(int j=0; j<N; j++){
      archivo << M[i][j] << " ";
    }
    archivo << t << "\n";
  }
  archivo.close();
}
