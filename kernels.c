/********************************************************
 * Kernels to be optimized for the CS:APP Performance Lab
 ********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "defs.h"
#include <string.h>
/*
 * Please fill in the following team struct
 */
team_t team = {
    "Error no name found",              /* Team name */

    "Caleb Ouellette",     /* First member full name */
    "ouellec@wwu.edu",  /* First member email address */

    "",                   /* Second member full name (leave blank if none) */
    ""                    /* Second member email addr (leave blank if none) */
};

/***************
 * ROTATE KERNEL
 ***************/

/******************************************************
 * Your different versions of the rotate kernel go here
 ******************************************************/

/*
 * naive_rotate - The naive baseline version of rotate
 */
char naive_rotate_descr[] = "naive_rotate: Naive baseline implementation";
void naive_rotate(int dim, pixel *src, pixel *dst)
{
    int i, j;

    for (i = 0; i < dim; i++)
	   for (j = 0; j < dim; j++)
	    dst[RIDX(dim-1-j, i, dim)] = src[RIDX(i, j, dim)];

}

/*
 * rotate - Your current working version of rotate
 * IMPORTANT: This is the version you will be graded on
 */
char rotate_descr[] = "rotate: Current working version";
void rotate(int dim, pixel *src, pixel *dst)
{
  int i, j;

  for (i = 0; i < dim; i++)
   for (j = 0; j < dim; j++)
    dst[RIDX(dim-1-j, i, dim)] = src[RIDX(i, j, dim)];

    //Move whole row to column using 1 for loop.
    //Add loop unroll


}

char rotate_by_row_descr[] = "rotateByRow: Using whole row move.";
void rotateByRow(int dim, pixel *src, pixel *dst)
{
  int i, j, c;
  pixel row[dim];

  for (i = 0; i < dim; i++){

    c = 0;
    for (j = 0; j < (dim); j++){
    row[j] = src[c + i];
    c += dim;
    }
    int dstRow = (dim - i - 1) * (dim);
    memcpy(dst + dstRow, row, dim * sizeof(pixel));
  }
}




char rotate_by_row_descr_Three[] = "rotateByRow: Using whole row move. Three";
void rotateByRowThree(int dim, pixel *src, pixel *dst)
{
  int i, j, c, dstRow;

  for (i = 0; i < dim ; i+=1){

    dstRow = (dim - i - 1) * (dim);
    for (c = 0, j = 0; j < dim; j++){
      dst[dstRow + j] =  src[c + i];
      c += dim;
    }
  }
}


char rotate_by_row_descr_ThreeB[] = "rotateByRow: Using whole row move. ThreeB";
void rotateByRowThreeB(int dim, pixel *src, pixel *dst)
{
  int i, j, dstRow;

  for (i = 0; i < dim ; i+=1){

    dstRow = (dim - i - 1) * (dim);
    for (j = 0; j < dim; j++){
      dst[dstRow + j] =  src[(j*dim) + i];
    }
  }
}





char rotate_by_row_descr_ThreeUnroll8[] = "rotateByRow: Using whole row move. Three Unrolled 8";
void rotateByRowThreeUnroll8(int dim, pixel *src, pixel *dst)
{
  int i, j, c, dstRow;
  dstRow = (dim - 1) * (dim);
  for (i = 0; i < dim ; i+=1){


    for (c = 0, j = 0; j < (dim - 15); j+=16){
      dst[dstRow + j] =  src[c + i];
      c += dim;
      dst[dstRow + j + 1] =  src[c + i];
      c += dim;
      dst[dstRow + j+ 2] =  src[c + i];
      c += dim;
      dst[dstRow + j+ 3] =  src[c + i];
      c += dim;
      dst[dstRow + j+ 4] =  src[c + i];
      c += dim;
      dst[dstRow + j+ 5] =  src[c + i];
      c += dim;
      dst[dstRow + j+ 6] =  src[c + i];
      c += dim;
      dst[dstRow + j+ 7] =  src[c + i];
      c += dim;
      dst[dstRow + j+ 8] =  src[c + i];
      c += dim;
      dst[dstRow + j+ 9] =  src[c + i];
      c += dim;
      dst[dstRow + j+ 10] =  src[c + i];
      c += dim;
      dst[dstRow + j+ 11] =  src[c + i];
      c += dim;
      dst[dstRow + j+ 12] =  src[c + i];
      c += dim;
      dst[dstRow + j+ 13] =  src[c + i];
      c += dim;
      dst[dstRow + j+ 14] =  src[c + i];
      c += dim;
      dst[dstRow + j+ 15] =  src[c + i];
      c += dim;
    }
    dstRow -= dim;
  }
}



char rotate_by_row_Four_descr[] = "rotateByRow: Using whole row move. Four";
void rotateByRowFour(int dim, pixel *src, pixel *dst)
{
  int i, j, c, total;

  total = dim * dim;
  c = dim;
  j = 0;
  for (i = 0; i < total; i++){

    dst[j * dim + c] = src[total - i];
    if(j == dim){
      j = 0;
      c--;
    }else{
      j++;
    }

  }
}




/*********************************************************************
 * register_rotate_functions - Register all of your different versions
 *     of the rotate kernel with the driver by calling the
 *     add_rotate_function() for each test function. When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.
 *********************************************************************/

void register_rotate_functions()
{

    add_rotate_function(&rotateByRowThree, rotate_by_row_descr_Three);
    add_rotate_function(&rotateByRowThreeB, rotate_by_row_descr_ThreeB);
    add_rotate_function(&rotateByRowThreeUnroll8, rotate_by_row_descr_ThreeUnroll8);    
    add_rotate_function(&rotateByRow, rotate_by_row_descr);
    add_rotate_function(&naive_rotate, naive_rotate_descr);
    add_rotate_function(&rotate, rotate_descr);
    /* ... Register additional test functions here */
}


/***************
 * SMOOTH KERNEL
 **************/

/***************************************************************
 * Various typedefs and helper functions for the smooth function
 * You may modify these any way you like.
 **************************************************************/

/* A struct used to compute averaged pixel value */
typedef struct {
    int red;
    int green;
    int blue;
    int num;
} pixel_sum;

/* Compute min and max of two integers, respectively */
static int min(int a, int b) { return (a < b ? a : b); }
static int max(int a, int b) { return (a > b ? a : b); }

/*
 * initialize_pixel_sum - Initializes all fields of sum to 0
 */
static void initialize_pixel_sum(pixel_sum *sum)
{
    sum->red = sum->green = sum->blue = 0;
    sum->num = 0;
    return;
}

/*
 * accumulate_sum - Accumulates field values of p in corresponding
 * fields of sum
 */
static void accumulate_sum(pixel_sum *sum, pixel p)
{
    sum->red += (int) p.red;
    sum->green += (int) p.green;
    sum->blue += (int) p.blue;
    sum->num++;
    return;
}

/*
 * assign_sum_to_pixel - Computes averaged pixel value in current_pixel
 */
static void assign_sum_to_pixel(pixel *current_pixel, pixel_sum sum)
{
    current_pixel->red = (unsigned short) (sum.red/sum.num);
    current_pixel->green = (unsigned short) (sum.green/sum.num);
    current_pixel->blue = (unsigned short) (sum.blue/sum.num);
    return;
}

/*
 * avg - Returns averaged pixel value at (i,j)
 */
static pixel avg(int dim, int i, int j, pixel *src)
{
    int ii, jj;
    pixel_sum sum;
    pixel current_pixel;

    initialize_pixel_sum(&sum);
    for(ii = max(i-1, 0); ii <= min(i+1, dim-1); ii++)
	   for(jj = max(j-1, 0); jj <= min(j+1, dim-1); jj++)
	    accumulate_sum(&sum, src[RIDX(ii, jj, dim)]);

    assign_sum_to_pixel(&current_pixel, sum);
    return current_pixel;
}

//START OF CUSTOM FUNCTIONS

static pixel zero(pixel n) {

  n.red = 0;
  n.green = 0;
  n.blue = 0;

  return n;
}

static pixel divBy(pixel p, int i) {
  pixel n;

  n.red = p.red / i;
  n.green = p.green / i;
  n.blue = p.blue / i;

  return n;
}

static pixel sum(pixel a, pixel b) {
  pixel n;

  n.red = a.red + b.red;
  n.green = a.green + b.green;
  n.blue = a.blue + b.blue;

  return n;
}

static pixel vertSum(int dim, int i, int j, pixel *src) {
  pixel n;

  n.red = src[RIDX(i, j, dim)].red + src[RIDX(i+1, j , dim)].red;
  n.green = src[RIDX(i, j, dim)].green + src[RIDX(i+1, j , dim)].green;
  n.blue = src[RIDX(i, j, dim)].blue + src[RIDX(i+1, j , dim)].blue;

  return n;
}

static pixel lDiagSum(int dim, int i, int j, pixel *src) {
  pixel n;

  n.red = src[RIDX(i, j, dim)].red + src[RIDX(i+1, j-1, dim)].red;
  n.green = src[RIDX(i, j, dim)].green + src[RIDX(i+1, j-1, dim)].green;
  n.blue = src[RIDX(i, j, dim)].blue + src[RIDX(i+1, j-1, dim)].blue;

  return n;
}

static pixel rDiagSum(int dim, int i, int j, pixel *src) {
  pixel n;

  n.red = src[RIDX(i, j, dim)].red + src[RIDX(i+1, j+1, dim)].red;
  n.green = src[RIDX(i, j, dim)].green + src[RIDX(i+1, j+1, dim)].green;
  n.blue = src[RIDX(i, j, dim)].blue + src[RIDX(i+1, j+1, dim)].blue;

  return n;
}

static pixel horizSum(int dim, int i, int j, pixel *src) {

  pixel n;

  n.red = src[RIDX(i, j, dim)].red + src[RIDX(i, j+1 , dim)].red;
  n.green = src[RIDX(i, j, dim)].green + src[RIDX(i, j+1 , dim)].green;
  n.blue = src[RIDX(i, j, dim)].blue + src[RIDX(i, j+1, dim)].blue;

  return n;
}

/******************************************************
 * Your different versions of the smooth kernel go here
 ******************************************************/

/*
 * naive_smooth - The naive baseline version of smooth
 */
char naive_smooth_descr[] = "naive_smooth: Naive baseline implementation";
void naive_smooth(int dim, pixel *src, pixel *dst)
{
    int i, j;

    for (i = 0; i < dim; i++)
	   for (j = 0; j < dim; j++)
	    dst[RIDX(i, j, dim)] = avg(dim, i, j, src);
}

/*
 * smooth - Your current working version of smooth.
 * IMPORTANT: This is the version you will be graded on
 */
char smooth_descr[] = "smooth: Current working version";
void smooth(int dim, pixel *src, pixel *dst)
{
    int i, size, iterator1, iterator2, iterator3;

    pixel n;

    pixel tempHorizSum;
    pixel[] tempVertSums = new pixel[dim];
    pixel[] temprDiagSums = new pixel[dim-1];
    pixel[] templDiagSums = new pixel[dim-1];

    size = dim-1
    iterator1 = 0;
    iterator2 = 0;
    iterator3 = 0;

    for(i = 0; i < dim; i++) {
      for (j = 0; j < dim; j++) {
        n = zero();
        if(j == 0) {
          if (i == 0) {
            tempHorizSum = horizSum(dim, i, j, src);
            tempVertSums[iterator1] = vertSum(dim, i, j, src);
            temprDiagSums[iterator2] = rDiagSum(dim, i, j, src);

            n = sum(n,tempHorizSum);
            n = sum(n,tempVertSums[iterator1++]);
            n = sum(n,temprDiagSums[iterator2++]);

            dst[RIDX(i, j, dim)] = divBy(n,3);
          } else if (i == size) {
            n = sum(n,tempVertSums[iterator1++]);
            n = sum(n,templDiagSums[iterator3++]);

            tempHorizSum = horizSum(dim, i, j, src);

            n = sum(n,tempHorizSum);

            dst[RIDX(i, j, dim)] = divBy(n,3);
          } else {
            n = sum(n,tempVertSums[iterator1]);
            n = sum(n,templDiagSums[iterator3++]);


            tempHorizSum = horizSum(dim, i, j, src);
            tempVertSums[iterator1] = vertSum(dim, i, j, src);
            temprDiagSums[iterator2] = rDiagSum(dim, i, j, src);

            n = sum(n,tempHorizSum);
            n = sum(n,tempVertSums[iterator1++]);
            n = sum(n,temprDiagSums[iterator2++]);

            dst[RIDX(i, j, dim)] = divBy(n,5);
          }
        } else if (j == size) {
          if(i == 0) {
            n = sum(n,tempHorizSum);

            tempVertSums[iterator1] = vertSum(dim, i, j, src);
            templDiagSums[iterator3] = lDiagSum(dim, i, j, src);

            n = sum(n,tempVertSums[iterator1++]);
            n = sum(n,templDiagSums[iterator3++]);

            dst[RIDX(i, j, dim)] = divBy(n,3);
          } else if (i == size) {
            n = sum(n,tempHorizSum);
            n = sum(n,tempVertSums[iterator1++]);
            n = sum(n,temprDiagSums[iterator2++]);

            dst[RIDX(i, j, dim)] = divBy(n,3);
          } else {
            n = sum(n,tempHorizSum);
            n = sum(n,tempVertSums[iterator1]);
            n = sum(n,temprDiagSums[iterator2++]);

            tempVertSums[iterator1] = vertSum(dim, i, j, src);
            templDiagSums[iterator3] = lDiagSum(dim, i, j, src);

            n = sum(n,tempVertSums[iterator1++]);
            n = sum(n,templDiagSums[iterator3++]);

            dst[RIDX(i, j, dim)] = divBy(n,5);
          }
        } else if (i == 0) {
          n = sum(n,tempVertSums[iterator1]);
          n = sum(n,templDiagSums[iterator3++]);

          tempHorizSum = horizSum(dim, i, j, src);
          tempVertSums[iterator1] = vertSum(dim, i, j, src);
          temprDiagSums[iterator2] = rDiagSum(dim, i, j, src);

          n = sum(n,tempHorizSum);
          n = sum(n,tempVertSums[iterator1++]);
          n = sum(n,temprDiagSums[iterator2++]);

          dst[RIDX(i, j, dim)] = divBy(n,5);
        } else if (i == size) {
          n = sum(n,tempHorizSum);
          n = sum(n,tempVertSums[iterator1]);
          n = sum(n,temprDiagSums[iterator2++]);

          tempVertSums[iterator1] = vertSum(dim, i, j, src);
          templDiagSums[iterator3] = lDiagSum(dim, i, j, src);

          n = sum(n,tempVertSums[iterator1++]);
          n = sum(n,templDiagSums[iterator3++]);

          dst[RIDX(i, j, dim)] = divBy(n,5);
        } else
          n = sum(n,tempHorizSum);
          n = sum(n,tempVertSums[iterator1]);
          n = sum(n,temprDiagSums[iterator2]);
          n = sum(n,templDiagSums[iterator3]);

          tempHorizSum = horizSum(dim, i, j, src);
          tempVertSums[iterator1] = vertSum(dim, i, j, src);
          temprDiagSums[iterator2] = rDiagSum(dim, i, j, src);
          templDiagSums[iterator3] = lDiagSum(dim, i, j, src);

          n = sum(n,tempHorizSum);
          n = sum(n,tempVertSums[iterator1++]);
          n = sum(n,temprDiagSums[iterator2++]);
          n = sum(n,templDiagSums[iterator3++]);

          dst[RIDX(i, j, dim)] = divBy(n,8);
      }
    }
    //store averages of left right pixels in temp variable
    //store averages of veritcal pixels in temp array

    //
}


/*********************************************************************
 * register_smooth_functions - Register all of your different versions
 *     of the smooth kernel with the driver by calling the
 *     add_smooth_function() for each test function.  When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.
 *********************************************************************/

void register_smooth_functions() {
    add_smooth_function(&smooth, smooth_descr);
    add_smooth_function(&naive_smooth, naive_smooth_descr);
    add_smooth_function(&divBy, "");
    add_smooth_function(&zero, "");
    add_smooth_function(&sum, "");
    add_smooth_function(&vertSum, "");
    add_smooth_function(&horizSum, "");
    add_smooth_function(&lDiagSum, "");
    add_smooth_function(&rDiagSum, "");
    /* ... Register additional test functions here */
}
