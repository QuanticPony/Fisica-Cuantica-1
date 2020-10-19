# include <stdlib.h>
# include <stdio.h>
# include <time.h>

# include "eispack.h"
#include "eispack.c"
//Resuelve el rotor 1D tomando la base exp(i*m*phi)
//Variables globales
double pi=3.141592653589793238;
double hb = 1.05459e-34; //h barra, pero no se usa, las energías se dan en unidades de hb^2/(2*Inercia)
int l=40;  //l = m maximo ( -l <= m <= l, i = m+l, 0<=i<n, n = 2l+1)
int nfun1=0,nfun=1; //numeros de funciones de onda para listar (inicial y final)
double dphiL = 5.; // incremento en phi(º) para LISTAR
double V0=-20;  //Minimo potencial (Puesto V0*cos(n*phi))
double epsilon=0.0;//1.e-2;//bias del potencial(minimos no equivalentes).
char nv=2; // para potencial V0cos(nv*phi)

//Funcion potencial
double V(double phi)

{/* Potencial V(phi) = V0*cos(nv*phi)
    se calcula 2*I*V/h^2
    V0 = 2*I*Vmax/hbar^2*/

 return V0*cos(nv*phi*pi/180.)+V0*epsilon*cos(phi*pi/180.);
}
double IntegralV(int i, int j)
{double I,dphi=0.2,phi; //dphi = incremento en phi (º) para la integral
 I=0.;
 for(phi=dphi; phi<=360.; phi=phi+dphi) I=I+V(phi)*cos((i-j)*phi*pi/180.);
 return I*dphi/360.;
}
main()
{
	FILE *pflevels,*pfun;
double phi, H[100][100];
double Sci,psire,psiim; // partes real e imaginaria de la funcion de onda
double xmin,xmax,ymin,ymax,real; //Para plot
   int i;
  int ierr;
  int j;
  int k;
  int matz = 1;  //matz = 1; Si  queremos listar autovectores
  int n = 2*l+1;
  double a[n*n] ;
  double a2[n*n];
  double *r;
  double w[n];
  double x[n*n];
double c[n]; //Coeficientes de la funcion de onda en la base exp(i*m*phi)/sqrt(2*pi)

// Calcula elementos de matriz del hamiltoniano
// psi(phi) Sum_j=0^n c[j]*exp(i*(j-l)*phi)/sqrt(2*pi)  
//
// Escribe en pantalla los datos del programa
printf("\n programa Rotor_1D");
printf("\n Energias = hbar^2/2I * autovalores");
printf("\n Potencial: V0*cos( %i*phi), V0 = %lf",nv,V0);
printf("\n base ortonormal de funciones usada: 1/sqrt(2*pi)*exp(i*m*phi)");
printf("\n l = Maximo |m|: %i   -l <= m <= l Numero de funciones de base: %i ",l,2*l+1);
printf("\n Funciones de onda para dibujar:  F%i(phi)  - F%i(phi)",nfun1,nfun);
printf("\n\n Cada vez, cerrar la ventana del dibujo para continuar el programa\n");
printf("\n pulsar <RET> para continuar");
getchar();

//Calcula los elementos de matriz del hamiltoniano 

for(i=0;i<n;i++)for(j=i;j<n;j++)
 {H[i][j]=IntegralV(i,j);
 if(i==j) H[i][j]=H[i][j]+(i-l)*(i-l);
 }
for(i=1;i<n;i++)for(j=0;j<=i-1;j++) H[i][j]=H[j][i];
for(i=0;i<n;i++)for(j=0;j<n;j++) a[i+j*n]=H[i][j];
//
/*  Guarda una copia de la matriz, por filas. 
   la original estará diagonalizada al salir de la función rs*/

  for ( j = 0; j < n; j++ )
  {
    for ( i = 0; i < n; i++ )
    {
      a2[i+j*n] = a[i+j*n];
    }
  }
  printf ( "\n" );
  printf ( "TEST06\n" );
  printf ( "  RS computes the eigenvalues and eigenvectors\n" );
  printf ( "  of a real symmetric matrix.\n" );
  printf ( "\n" );
  printf ( "  Matrix order = %d\n", n );
/* Esto sólo para test
  r8mat_print ( n, n, a, "  The matrix A:" ); */

  ierr = rs ( n, a, w, matz, x ); //AQUI ES DONDE DIAGONALIZA POR EL ALGORITMO QR
  /* a partir de aquí:
    n = 2l+1: numero de funciones de la base = no de autovectores calculados
    w[]  array 1D de n = 2l+1 elementos con los autovalores
    x[] = autovectores = coeficientes de las autofunciones en la base tomada,
           todos seguidos en un array 1D de n*n = (2l+1)*(2l+1) elementos
    matz = valor dado a la entrada: 1 = calcular autovalores y autovectores, matz = 0: solo autovalores
  */
  if ( ierr != 0 ) //Escribe mensaje de error si hay alguno
  {
    printf ( "\n" );
    printf ( "TEST06 - Warning!\n" );
    printf ( "  The error return flag IERR = %d\n", ierr );
    return;
  }

  r8vec_print ( n, w, "  Autovalores Lambda\n(Energías en unidades de beta, con base en la minima E potencial):" );

  if ( matz != 0 )
  {
    //r8mat_print ( n, n, x, "  The eigenvector matrix:" );
    r = r8mat_mm_new ( n, n, n, a2, x );
    for ( j = 0; j < n; j++ )
    {
      for ( i = 0; i < n; i++ )
      {
        r[i+j*n] = r[i+j*n] - w[j] * x[i+j*n];
      }
    }

    //r8mat_print ( n, n, r, "  The residual (A-Lambda*I)*X:" );
  }
  
  //printf("\n teclear <ret>");
  //getchar();
  
  
  //Guarda los Niveles obtenidos en fichero de texto y lo dibuja junto con el potencial
  xmin=-180;
  xmax=180;
  ymin=-fabs(V0)*1.1;
  ymax=fabs(V0)*4;
  pflevels=fopen("R_1D_levels.plt","w");
   fprintf(pflevels,"unset key");
    fprintf(pflevels,"\nset xrange [%4.0lf:%4.0lf]",xmin,xmax );
  fprintf(pflevels,"\nset yrange [%lf:%lf]",ymin,ymax );
  fprintf(pflevels,"\n# Autovalores (Niveles de energia * 2I/hb^2)");
 fprintf(pflevels,"\nplot %lf lt -1 lw 2",w[0]);
   for(i=1;i<n;i++) fprintf(pflevels,"\nreplot %lf lt -1 lw 2",w[i]);
  fprintf(pflevels,"\n# Potential");
       fprintf(pflevels,"\nreplot '-' with filledcurves y1=%lf lt 1 ",V0*1.1);
  for(phi=-180;phi<=360;phi=phi+1) fprintf(pflevels,"\n %lf %lf",phi,V(phi));
     fprintf(pflevels,"\nend"); 
  fclose(pflevels); 
  system("R_1D_levels.plt");

 //Lista, guarda y dibuja los valores de las funciones de onda solicitadas
 
   printf("\n\n Funciones de onda nos: %i - %i",nfun1,nfun);
  printf("\n\n phi(º)   Re_psi     Im_psi");
  xmin=-180.;
  xmax=180.;
  ymin=-1.2;
  ymax=1.2;
   pfun=fopen("R_1D_func.plt","w");
   fprintf(pfun,"set multiplot" );
   fprintf(pfun,"\nset xrange [%4.0lf:%4.0lf]",xmin,xmax);
   fprintf(pfun,"\nset yrange [%4.1lf:%4.1lf]",ymin,ymax );
    fprintf(pfun,"\nset nokey" );
     fprintf(pfun,"\nset title \"F. de onda %i - %i\"",nfun1,nfun);
  //fprintf(pfun,"plot 0 with lines");
   fprintf(pfun,"\n# Potencial");
    fprintf(pfun,"\nset label \"Potencial\" at %lf,%lf",xmin+(xmax-xmin)*0.1,ymax-(ymax-ymin)*0.1);
      fprintf(pfun,"\nplot 0 with lines lt -1 "); // Dibuja la linea de cero     
   fprintf(pfun,"\nplot '-' with lines lt 2 ");
   for(phi=-180;phi<=180;phi=phi+1) fprintf(pfun,"\n %lf %lf",phi,V(phi)/fabs(V0));
     fprintf(pfun,"\nend"); 
 // Funciones de onda
  for(j=nfun1;j<=nfun;j++)
  {
   Sci=0.; //Acumulador para normalizar
   for(i=0;i<n;i++) Sci=Sci+x[i+j*n]*x[i+j*n];
   printf("\n\n  Coeficientes de la funcion de onda: %i",j);
   for(i=0;i<n;i++) 
   {c[i]=x[i+j*n];
    printf("\n %i %lf", i,c[i]);
   }

   fprintf(pfun,"\nplot '-' using 1:2 with lines lt %i",j+3);
   real=0; //Para determinar si la  F.de.O es real o imaginaria
   for(phi=-180.;phi<=180.;phi=phi+dphiL) 
   {psire=0.;
    psiim=0.;
    for(i=0;i<n;i++)
    {
     psire=psire+c[i]*cos((i-l)*phi*pi/180.)/sqrt(2*pi);
     psiim=psiim+c[i]*sin((i-l)*phi*pi/180.)/sqrt(2*pi);
     real=real+fabs(psire)-fabs(psiim); //Integra la diferencia para ver si es mayor la parte real
    }  
   printf("\n %lf %lf %lf",phi, psire,psiim);
   if(real>=0)fprintf(pfun,"\n %lf %lf",phi, psire); 
   else fprintf(pfun,"\n %lf %lf",phi, psiim); 
   }
   fprintf(pfun,"\nend");
  }
   fclose(pfun);
   system("R_1D_func.plt");//C:/gnuplot/bin/
   //getchar();
    
  
    free ( r );
  return;
}
