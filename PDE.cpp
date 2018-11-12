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
#define N 1000
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
  static double T_futuro[N][N];

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



}
