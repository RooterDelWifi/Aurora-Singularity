#include <iostream>
#include <conio.h>
double elden_ring = 0.01;
double peso = 0;
double suma1 = 0;
double suma2 = 0;
double sesgo = 0;
//double m = 29;
//double b = -29;
double a;
double x[2];
double y[2];
//double resol[11];
//double resolx[11];


double neurona(double x){
double out;
out = peso*x + sesgo;
return out;
}

void backpropagation(){

for(int i = 0; i < sizeof(y)/sizeof(double); i++){
 suma1 = suma1 + ((y[i] - neurona(x[i]))*x[i]);
 suma2 = suma2 + (y[i] - neurona(x[i]));
}



peso = peso + elden_ring*suma1;
sesgo = sesgo + elden_ring*suma2;
suma1 = 0;
suma2 = 0;
}

void Programa(){
 std::cout<<"------Introducir patron------"<<std::endl;
 std::cout<<"1. Mete 2 entradas: "<<std::endl;
 std::cin>>x[0]>>x[1];
 std::cout<<"2. Mete 2 salidas: "<<std::endl;
 std::cin>>y[0]>>y[1];
 //calcular();

 for(int i = 1; i < 30000; i++)
 {
 backpropagation();
 std::cout<<peso<<"  "<<suma2*suma2/2<<"  "<<sesgo<<std::endl;
 //std::cout<<x[3]<<"  "<<y[3]<<std::endl;
 }
 //std::cout<<neurona(1)<<"  "<<"  "<<neurona(100)<<std::endl;
 std::cout<<"Aplicarlo a: "<<std::endl;
 std::cin>>a;
 std::cout<<"Prediccion: "<<neurona(a)<<std::endl;
 std::cout<<"Le sumaste "<<sesgo<<" y lo multiplicaste por: "<<peso<<std::endl;
 std::cout<<"Pulsa cualquier tecla..."<<std::endl;
 getch();
 Programa();
}




int main(){
Programa();

getch();
return 0;
}
