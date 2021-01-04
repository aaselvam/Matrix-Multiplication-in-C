/*********************************************************************************/
/* CSCI-2500 Assignment 1: 2-D/ NxN Matrix Swap and  Multiplication **************/
/* Name: Arya Selvam *************************************************************/
/*********************************************************************************/

/*********************************************************************************/
/* Usual suspects to include *****************************************************/
/*********************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<errno.h>

/*********************************************************************************/
/* Function Calls ****************************************************************/
/*********************************************************************************/

double **mm_alloc( int size )
{
  // allocating an array of pointers to a double
  double** matrix = calloc(size, sizeof(double*));
  int i;
  for(i = 0; i < size; i++){
    // allocating row to doubles
   matrix[i] = calloc(size, sizeof(double*));
  }
  return(matrix);
}

void mm_free( int size, double **matrix  )
{
  // doing the exact opposite as mm_alloc in the opposite order
  int i;
  for(i = 0; i < size; i++){
    free(matrix[i]);
  }
  free(matrix);

  return; // delete for your implementation
}

double **mm_read( char *filename, int *size )
{
  // opening the file
 FILE * fp;
 fp = fopen(filename, "r");
 if(fp == NULL){
   printf("File not found");
   return(NULL);
 }

 // converting the N size of matrix (as a str to an int)
 char sizeString[4];
 fgets(sizeString, 3, fp);
 sscanf(sizeString, "%d", size);
 double **matrix = mm_alloc(*size);
 int i;
 int j;

 // reading from the file to the matrix
 for(i = 0; i < *size; i++){
   for(j = 0; j < *size; j++){
     char value[10];
     fgets(value, 9, fp);
     int val;
     sscanf(value, "%d", &val);
     matrix[i][j] = val;
   }
 }

 // closing the file
 fclose(fp);

 return( matrix );
}

void mm_print( int size, double **matrix )
{
  // fairly simple, just iterating through the matrix and printing it
  int i;
  int j;
  printf("\n");
  printf("/******** START of 2-D Matrix ****************************************************************************");
  printf("\n");
  for(i = 0; i < size; i++){
   for(j = 0; j < size; j++){
     printf("%f", matrix[i][j]);
     printf("\t");
   }
   printf("\n");
  }
  printf("/******** END of 2-D Matrix ******************************************************************************");
  return; // delete for your implementation.
}

double **mm_swap( int size, double **matrix )
{
  // again fairly simple, just swapping the i and i+2 column
  // but we gotta make sure that we initialize all the columns first
  // as some columns will never get swapped
  // we first check if i+2 is less than size, and then swap said columns

  double **swap = mm_alloc(size);
  int i = 0;
  int j = 0;
  int k;
  int l;
  for(k = 0; k < size; k++){
    for(l = 0; l < size; l++){
      swap[k][l] = matrix[k][l];
    }
  }

  while(i+2 < size){
    for(j = 0; j < size; j++){
      double temp = swap[j][i];
      swap[j][i] = swap[j][i+2];
      swap[j][i+2] = temp;
    }
    i++;
  }

  printf("\n");
  printf("Output of Swap Matrix");
  mm_print(size, swap);

  return( swap ); // return the transpose matrix
}

double **mm_matrix_mult( int size, double **matrix, double **swap )
{
  double **results = mm_alloc(size);

  // Have to have 3 for loops to get all values
  int i;
  int j;
  int k;
  for(i = 0; i < size; i++){
    for(j = 0; j < size; j++){
      for(k = 0; k < size; k++){
        results[i][j] += matrix[i][k] * swap[k][j];
      }
    }
  }

  return( results ); // delete for your implementation.
}

int main()
{
  /*
   * you must keep this function AS IS. 
   * you cannot modify it!
   */
  char filename[256];
  double **matrix=NULL;
  double **swap_matrix=NULL;
  double **results_matrix=NULL;
  int size=0;

  printf("Please enter the matrix data file name: ");
  scanf( "%s", filename );

  matrix = mm_read( filename, &size );
  swap_matrix = mm_swap( size, matrix ); 
  results_matrix = mm_matrix_mult( size, matrix, swap_matrix );

  mm_print( size, results_matrix );
  mm_free( size, matrix );
  mm_free( size, swap_matrix );
  mm_free( size, results_matrix );
  return( 0 ); 
}