#include <math.h>
#include <stdio.h>
#include "eispak.c"

//funciones
    double V(double x, double c, double altura){
        
        double pot;
        
        if (x>=0){
            pot = c*x;
            return pot;            
        }
        
        if (x<0){
            return altura;
        }
    }

int main (int argc, char**argv){
    
    //definimos las constantes o variables globales que usaremos
    double pi=acos(-1);                //valor de pi
    double h_=1.054571818e-34          //valor de ħ=h/(2π) en J·s
    double qe=−1.602176565e-19         //carga del electrón en C
    double uma=1.660538921e-27         //unidad de masa atómica en kg
    
    //variables 
    double c;
    double altura;          //parametros del potencial
    double a;
    double b;               //rango de calculo de la FDO
    

    
    
    
}
