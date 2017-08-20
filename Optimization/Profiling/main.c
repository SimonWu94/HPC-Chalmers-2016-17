#include<stdio.h>
#include<stdlib.h>
#include <time.h>


void col_sums(double * sums, const double ** matrix, size_t nrs, size_t ncs)
{
  for ( size_t jx=0; jx < ncs; ++jx ) {
    double sum = 0.;
    for ( size_t ix=0; ix < nrs; ++ix )
      sum += matrix[ix][jx];
    sums[jx] = sum;
  }
}

void row_sums(double * sums, const double ** matrix, size_t nrs, size_t ncs)
{
  for ( size_t ix=0; ix < nrs; ++ix ) {
    double sum = 0;
    for ( size_t jx=0; jx < ncs; ++jx )
      sum += matrix[ix][jx];
    sums[ix] = sum;
  }
}

/* ----------------------------------
naive improvement of the column sum
---------------------------------- */

void col_sums_improved(double * sums, const double ** matrix, size_t nrs, size_t ncs)
{
  
  for ( size_t jx=0; jx < ncs; ++jx ) {
    double sum = 0.;
    double * ptr = &matrix[0][jx];
    for ( size_t ix=0; ix < nrs; ++ix )
      sum += *ptr;
      ptr++;
    sums[jx] = sum;
  }
}



int main() {
  
    //--------------------Weird Matrix Construction------------------
  
    // matrix[n][m];
    int nrs =1000;
    int ncs =1000;
    
    double **matrix  = (double **)malloc(sizeof(double *)*nrs); //n
  
    for(int ix=0; ix<ncs; ix++){
      matrix[ix] = (double *)malloc(sizeof(double)*ncs); //m
      }
      
    for (int ix=0; ix<nrs;ix++){
    for (int jx=0; jx<ncs;jx++){
      
      //--------------for testing---------------
      matrix[ix][jx] = 1.;
      
      //--------------Random entries------------
      //matrix[ix][jx]=(double)rand()/(double)(RAND_MAX)*5.;
    }
    }
  
  printf("Successfully constructed 1000x1000 matrix. \n");
  
  
  
  //-------------------needed variables-----------------------
  double row_sum[nrs];
  double col_sum[ncs];
  double col_sum_improv[ncs];
  double *rsms = row_sum;
  double *csms = col_sum;
  double *csms_improv = col_sum_improv;
  const double **mat = matrix;  //Ask about this!!!!!!!!!!!!!!!!!!!!!!!!
  clock_t start_row, end_row, start_column, end_column, start_col_improv, end_col_improv;
  double cpu_time_used_row;
  double cpu_time_used_column;
  double cpu_time_used_column_improv;
  
  //--------------------Row Sums---------------------
  start_row = clock();
  row_sums(rsms,mat, nrs, ncs);
  end_row = clock();
  
  
  //--------------------Column Sums------------------
  start_column = clock();
  col_sums(csms,mat, nrs, ncs);
  end_column = clock();
  
  
  //-------------------Column Sums Imrpoved----------
  start_col_improv = clock();
  col_sums_improved(csms_improv,mat, nrs, ncs);
  end_col_improv = clock();



  //--------------------Output Values----------------
  /*for (int ix=0; ix<nrs;ix++){
  printf("The row sums are: %f \n",row_sum[ix]);
  }*/
  
  /*for (int ix=0; ix<ncs;ix++){
  printf("The colum sums are: %f \n",col_sum[ix]);
  }*/
  
  //------------Calculation of time used-------------
  cpu_time_used_row = ((double) (end_row- start_row)) / CLOCKS_PER_SEC;
  cpu_time_used_column = ((double) (end_column - start_column)) / CLOCKS_PER_SEC;
  cpu_time_used_column_improv = ((double) (end_col_improv- start_col_improv)) / CLOCKS_PER_SEC;
  
  printf("Row timing: %f \n", cpu_time_used_row);
  printf("Column timing: %f \n", cpu_time_used_column);
  printf("Improved Column timing: %f \n", cpu_time_used_column_improv);
  
  
  free(matrix);
  return 0;
}