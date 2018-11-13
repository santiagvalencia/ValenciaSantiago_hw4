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
#define N 200//1000
#define D 0.1
#define T0 10.0
#define Tv 100.0
#define L 0.5
#define R D/2
#define dx L/N
#define dy L/N
#define dt (dx*dx*dy*dy)/(2*nu*(dx*dx + dy*dy))

int main(){

  static double T_pasado[N][N];
  static double T_inicial[N][N];
  static double T_presente[N][N];

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
  for(int i=0; i<N; i++){
    for(int j=0; j<N; j++){
      T_pasado[i][j] = T_inicial[i][j];
    }
  }

  int n_pasos = 10000;
  double T_prom;
  double t;
  ofstream promedios;

  for(int n=0; n<n_pasos; n++){
    for(int i=1; i<N-1; i++){
      for(int j=1; j<N-1; j++){
        r2 = (i*dx-centro_x)*(i*dx-centro_x) + (j*dy-centro_y)*(j*dy-centro_y);
        if(r2 > R*R){
          T_presente[i][j] = T_pasado[i][j] + dt*nu*((T_pasado[i+1][j]-2*T_pasado[i][j]+T_pasado[i-1][j])/(dx*dx) + (T_pasado[i][j+1]-2*T_pasado[i][j]+T_pasado[i][j-1])/(dy*dy));
        }
        else{
          T_presente[i][j] = Tv;
        }
      }
    }
    for(int i=0; i<N; i++){
      T_presente[N-1][i] = T0;
      T_presente[0][i] = T0;
      T_presente[i][N-1] = T0;
      T_presente[i][0] = T0;
    }
    for(int i=0; i<N; i++){
      for(int j=0; j<N; j++){
        T_pasado[i][j] = T_presente[i][j];
      }
    }
  }

  ofstream final;
  final.open("final.txt");
  for(int i=0; i<N; i++){
    for(int j=0; j<N; j++){
      final << T_presente[i][j] << " ";
    }
    final << "\n";
  }
  final.close();


}
