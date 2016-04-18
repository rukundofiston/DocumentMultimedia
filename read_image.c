#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <math.h>

#include "rdjpeg.h"

#define SIZE 4

void displayHistogramm (char *argv[], int libsvm_format) {
  int i,j,count,k;
  CIMAGE cim;

  // Lecture de l'image en input
  read_cimage(argv[1],&cim);
  
  float ***h = (float ***)malloc(SIZE*sizeof(float**));
    
    for (i = 0; i< SIZE; i++) {
      h[i] = (float **) malloc(SIZE*sizeof(float *));      
      for (j = 0; j < SIZE; j++) {
        h[i][j] = (float *)malloc(SIZE*sizeof(float));
      }
    }
  
  // initialisation de l'histogramme h
    for (i = 0; i < SIZE; i++) {
      for (j = 0; j < SIZE; j++) {
        for (k = 0; k < SIZE; k++) {
          h[i][j][k] = 0.0;
        }
      }
    }

  // Remplissage du tableau h
  for (j = 0; j < cim.ny; j++) {
    for (i = 0; i < cim.nx; i++) {
      int r = ((cim.r[i][j] *SIZE)/256);
      int g = ((cim.g[i][j] *SIZE)/256);
      int b = ((cim.b[i][j] *SIZE)/256);
      h[r][g][b] = h[r][g][b] + 1.0;    
    }
  }

  // Normalisation
  for (i = 0; i < SIZE; i++) {
      for (j = 0; j < SIZE; j++) {
        for (k = 0; k < SIZE; k++) {
          h[k][j][i] = h[k][j][i]/(cim.nx*cim.ny);          
        }
    }
  }
  
  // Affichage du tableau au format libsvm
  if (libsvm_format == 1){
    count = 0;
    printf("%d",count++);
    // Normalisation
    for (i = 0; i < SIZE; i++) {
      for (j = 0; j < SIZE; j++) {
        for (k = 0; k < SIZE; k++) {          
          if (h[k][j][i] > 0.0){
            printf(" %d:%f",count, h[k][j][i]);          
          }
          count++;
        }
      }
    }
    printf("\n");    
  }

}


int main(int argc, char *argv[]) {
  displayHistogramm(argv,1);
  exit(0);
}