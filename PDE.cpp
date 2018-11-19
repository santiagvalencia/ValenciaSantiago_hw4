#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <array>
#include <string>

using namespace std;
//Constantes del problema
#define k 1.62
#define Cp 820.0
#define rho 2710.0
#define nu k/(Cp*rho)
#define N 100//1000 //Numero de puntos
#define D 0.1 //Diametro del circulo
#define T0 10.0 //Temperatura de condiciones iniciale
#define Tv 100.0 //Temperatura del circulo
#define L 0.5 //longitud del cuadrado
#define R D/2 //Radio del circulo
#define dx L/N //Salto en x
#define dy L/N //Salto en y
#define dt (dx*dx*dy*dy)/(2*nu*(dx*dx+dy*dy)) //dt calculado segun analisis de estabilidad
//funciones a utilizar
double promedio(double M[N][N]);
void imprimir(double M[N][N], double t, string nombre);

int main(){
  static double T_inicial[N][N]; //crea arreglos para cada condicion de frontera
  static double T_pasadoF[N][N]; //F es fronteras fijas
  static double T_presenteF[N][N];

  static double T_pasadoA[N][N]; //A es fronteras abiertas
  static double T_presenteA[N][N];

  static double T_pasadoP[N][N]; //P es fronteras periodicas
  static double T_presenteP[N][N];

  double r2; //variable para determinar el radio del circulo al cuadrado
  double centro_x = L/2; double centro_y = L/2; //variables para determinar el centro del cuadrado

  for(int i=0; i<N; i++){ //condiciones iniciales
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

  for(int i=0; i<N; i++){ //inicializa los pasados con las condiciones iniciales
    for(int j=0; j<N; j++){
      T_pasadoF[i][j] = T_inicial[i][j];
      T_pasadoA[i][j] = T_inicial[i][j];
      T_pasadoP[i][j] = T_inicial[i][j];
    }
  }

  double T_final = 500000; //tiempo final suficiente para alcanzar el equilibrio en los tres casos
  double step = dt; //copia el valor de dt
  int n_pasos = T_final/step; //define el numero de pasos segun el tiempo y dt
  double t; //variable para medir el tiempo
  ofstream promedios; //ofstream en el que se imprimen las temperaturas promedio
  promedios.open("promedios.txt");

  for(int n=0; n<n_pasos; n++){//recorre el tiempo
    t = n*step; //actualiza el tiempo
    for(int i=1; i<N-1; i++){//recorre las posiciones horizantales
      for(int j=1; j<N-1; j++){//recorre las posiciones verticales
        r2 = (i*dx-centro_x)*(i*dx-centro_x) + (j*dy-centro_y)*(j*dy-centro_y); //determina si el punto evaluado esta en el circulo o fuera
        if(r2 > R*R){//Si esta fuera sigue la ecuacion diferencial
          T_presenteF[i][j] = T_pasadoF[i][j] + dt*nu*((T_pasadoF[i+1][j]-2*T_pasadoF[i][j]+T_pasadoF[i-1][j])/(dx*dx) + (T_pasadoF[i][j+1]-2*T_pasadoF[i][j]+T_pasadoF[i][j-1])/(dy*dy));
          T_presenteA[i][j] = T_pasadoA[i][j] + dt*nu*((T_pasadoA[i+1][j]-2*T_pasadoA[i][j]+T_pasadoA[i-1][j])/(dx*dx) + (T_pasadoA[i][j+1]-2*T_pasadoA[i][j]+T_pasadoA[i][j-1])/(dy*dy));
          T_presenteP[i][j] = T_pasadoP[i][j] + dt*nu*((T_pasadoP[i+1][j]-2*T_pasadoP[i][j]+T_pasadoP[i-1][j])/(dx*dx) + (T_pasadoP[i][j+1]-2*T_pasadoP[i][j]+T_pasadoP[i][j-1])/(dy*dy));
        }
        else{//De lo contrario la temperatura es TV
          T_presenteF[i][j] = Tv;
          T_presenteA[i][j] = Tv;
          T_presenteP[i][j] = Tv;
        }
      }
    }
    for(int i=0; i<N; i++){
      T_presenteF[N-1][i] = T0; //Condiciones de frontera fijas:
      T_presenteF[0][i] = T0; //Las temperaturas en los bordes son constantes
      T_presenteF[i][N-1] = T0;
      T_presenteF[i][0] = T0;

      T_presenteA[N-1][i] = T_presenteA[N-2][i]; //Condiciones de frontera abiertas:
      T_presenteA[0][i] = T_presenteA[1][i]; //Cada punto del borde toma el valor de su vecino anterior
      T_presenteA[i][N-1] = T_presenteA[i][N-2];
      T_presenteA[i][0] = T_presenteA[i][1];

      T_presenteP[N-1][i] = T_presenteP[N-2][i]; //Condiciones de frontera periodicas:
      T_presenteP[0][i] = T_presenteP[N-1][i]; //En uno de los extremos hay condiciones abiertas
      T_presenteP[i][N-1] = T_presenteP[i][N-2]; //El punto del extremo opuesto toma el valor del otro extremo
      T_presenteP[i][0] = T_presenteP[i][N-1];
    }
    //Se actualizan los valores presentes
    for(int i=0; i<N; i++){
      for(int j=0; j<N; j++){
        T_pasadoF[i][j] = T_presenteF[i][j];
        T_pasadoA[i][j] = T_presenteA[i][j];
        T_pasadoP[i][j] = T_presenteP[i][j];
      }
    }//documento de temperaturas promedio para cada caso
    promedios << t << " " << promedio(T_presenteF) << " " << promedio(T_presenteA) << " "<< promedio(T_presenteP) << "\n";
    //tiempos de impresion de la distribucion de temperaturas
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
  promedios.close(); //cierra el archivo de promedios e imprime las distribuciones de temperatura finales
  imprimir(T_presenteF, t, "final_F.txt");
  imprimir(T_presenteA, t, "final_A.txt");
  imprimir(T_presenteP, t, "final_P.txt");
}

double promedio(double M[N][N]){ //funcion para  calcular el promedio de un arreglo NxN
  double suma = 0; //crea un sumador
  for(int i=0; i<N; i++){ //recorre el arreglo
    for(int j=0; j<N; j++){
      suma += M[i][j]; //suma cada elemento
    }
  }
  suma /= (N*N); //divide entre el numero total de elementos
  return suma; //retorna el promedio
}

void imprimir(double M[N][N], double t, string nombre){//funcion para imprimir en un archivo un arreglo
  ofstream archivo; //crea y abre un archivo con el nombre dado
  archivo.open(nombre);
  for(int i=0; i<N; i++){
    for(int j=0; j<N; j++){
      archivo << M[i][j] << " "; //imprime cada valor del arreglo en el archivo
    }
    archivo << t << "\n"; //incluye tambien el tiempo correspondiente
  }
  archivo.close(); //cierra el archivo
}
