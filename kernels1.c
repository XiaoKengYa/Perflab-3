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

    "Zach Richardson",                   /* Second member full name (leave blank if none) */
    "richarz@wwu.edu"                    /* Second member email addr (leave blank if none) */
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
  add_rotate_function(&rotateByRowThreeB, rotate_by_row_descr_ThreeB);
    add_rotate_function(&rotateByRowThree, rotate_by_row_descr_Three);
  //  add_rotate_function(&rotateByRowFour, rotate_by_row_Four_descr);
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

static pixel divBy(pixel p, int s, int i, int j, pixel *src) {
  pixel n;

  int newS = s-1;

  n.red = p.red;
  n.green = p.green;
  n.blue = p.blue;

  n.red -= src[RIDX(i, j, dim)].red * newS;
  n.green -= src[RIDX(i, j, dim)].green * newS;
  n.blue -= src[RIDX(i, j, dim)].blue * newS;

  n.red = n.red / s;
  n.green = n.green / s;
  n.blue = n.blue / s;

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

 /*
char smooth_descr[] = "smooth: Segmented computing using custom averages";
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

    //first corner
    tempHorizSum = horizSum(dim, i, j, src);
    tempVertSums[iterator1] = vertSum(dim, i, j, src);
    temprDiagSums[iterator2] = rDiagSum(dim, i, j, src);

    n = sum(n,tempHorizSum);
    n = sum(n,tempVertSums[iterator1++]);
    n = sum(n,temprDiagSums[iterator2++]);

    dst[RIDX(i, j, dim)] = divBy(n,4,i,j,src);

    //top edge
    for(j = 1; j < size; j++) {
      n = sum(n,tempHorizSum);

      tempHorizSum = horizSum(dim, i, j, src);
      tempVertSums[iterator1] = vertSum(dim, i, j, src);
      temprDiagSums[iterator2] = rDiagSum(dim, i, j, src);
      templDiagSums[iterator3] = lDiagSum(dim, i, j, src);

      n = sum(n,tempHorizSum);
      n = sum(n,tempVertSums[iterator1++]);
      n = sum(n,temprDiagSums[iterator2++]);
      n = sum(n,templDiagSums[iterator3++]);

      dst[RIDX(i, j, dim)] = divBy(n,6,i,j,src);
    }

    //second corner
    n = sum(n,tempHorizSum);

    tempVertSums[iterator1] = vertSum(dim, i, j, src);
    templDiagSums[iterator3] = lDiagSum(dim, i, j, src);

    n = sum(n,tempVertSums[iterator1++]);
    n = sum(n,templDiagSums[iterator3++]);

    dst[RIDX(i, j, dim)] = divBy(n,4,i,j,src);

    //middle section
    for(i = 1; i < size; i++) {

      iterator1 -= dim + 1;
      iterator2 -= dim;
      iterator3 -= dim;

      //left edge
      n = sum(n,tempVertSums[iterator1]);
      n = sum(n,templDiagSums[iterator3++]);

      tempHorizSum = horizSum(dim, i, j, src);
      tempVertSums[iterator1] = vertSum(dim, i, j, src);
      temprDiagSums[iterator2] = rDiagSum(dim, i, j, src);

      n = sum(n,tempHorizSum);
      n = sum(n,tempVertSums[iterator1++]);
      n = sum(n,temprDiagSums[iterator2++]);

      dst[RIDX(i, j, dim)] = divBy(n,6,i,j,src);

      //middle of rows
      for(j = 1; j < size; j++) {
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

        dst[RIDX(i, j, dim)] = divBy(n,9,i,j,src);
      }

      //right edge
      n = sum(n,tempHorizSum);
      n = sum(n,tempVertSums[iterator1]);
      n = sum(n,temprDiagSums[iterator2++]);

      tempVertSums[iterator1] = vertSum(dim, i, j, src);
      templDiagSums[iterator3] = lDiagSum(dim, i, j, src);

      n = sum(n,tempVertSums[iterator1++]);
      n = sum(n,templDiagSums[iterator3++]);

      dst[RIDX(i, j, dim)] = divBy(n,6,i,j,src);
    }

    iterator1 -= dim + 1;
    iterator2 -= dim;
    iterator3 -= dim;

    //third corner
    n = sum(n,tempVertSums[iterator1++]);
    n = sum(n,templDiagSums[iterator3++]);

    tempHorizSum = horizSum(dim, i, j, src);

    n = sum(n,tempHorizSum);

    dst[RIDX(i, j, dim)] = divBy(n,4,i,j,src);

    //bottom edge
    for (j = 1; j < size; j++) {
      n = sum(n,tempHorizSum);
      n = sum(n,tempVertSums[iterator1++]);
      n = sum(n,temprDiagSums[iterator2++]);
      n = sum(n,templDiagSums[iterator3++]);

      tempHorizSum = horizSum(dim, i, j, src);

      n = sum(n,tempHorizSum);

      dst[RIDX(i, j, dim)] = divBy(n,6,i,j,src);
    }

    //fourth corner
    n = sum(n,tempHorizSum);
    n = sum(n,tempVertSums[iterator1++]);
    n = sum(n,temprDiagSums[iterator2++]);

    dst[RIDX(i, j, dim)] = divBy(n,4,i,j,src);

    /*
    for(i = 0; i < dim; i++) {
      for (j = 0; j < dim; j++) {
        n = zero(n);
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
    */

    //hardcode first corner
    //for loop for top edge
    //hardcode second corner
    //for loop for middle rows
    //  hard code first edge
    //  for loop for middle of row
    //  hard code end edge
    //
    //hard code third corner
    //for loop for bottom edge
    //hard code fourth corner
    //
    //store averages of left right pixels in temp variable
    //store averages of veritcal pixels in temp array

    //
//}

char smooth2_descr[] = "smooth2: segmented and simple";
void smooth2(int dim, pixel *src, pixel *dst) {
    int i, j, tempIndex;
    int tempVar = dim;
    //corners
    dst[0].red = (src[0].red+src[1].red+src[dim].red+src[dim+1].red)/4;
    dst[0].green = (src[0].green+src[1].green+src[dim].green+src[dim+1].green)/4;
    dst[0].blue = (src[0].blue+src[1].blue+src[dim].blue+src[dim+1].blue)/4;

    dst[dim-1].red = (src[dim-1].red+src[dim-2].red+src[dim*2-1].red+src[dim*2-2].red)/4;
    dst[dim-1].green = (src[dim-1].green+src[dim-2].green+src[dim*2-1].green+src[dim*2-2].green)/4;
    dst[dim-1].blue = (src[dim-1].blue+src[dim-2].blue+src[dim*2-1].blue+src[dim*2-2].blue)/4;

    dst[dim*(dim-1)].red = (src[dim*(dim-1)].red+src[dim*(dim-1)+1].red+src[dim*(dim-2)].red+src[dim*(dim-2)+1].red)/4;
    dst[dim*(dim-1)].green = (src[dim*(dim-1)].green+src[dim*(dim-1)+1].green+src[dim*(dim-2)].green+src[dim*(dim-2)+1].green)/4;
    dst[dim*(dim-1)].blue = (src[dim*(dim-1)].blue+src[dim*(dim-1)+1].blue+src[dim*(dim-2)].blue+src[dim*(dim-2)+1].blue)/4;

    dst[dim*dim-1].red = (src[dim*dim-1].red+src[dim*dim-2].red+src[dim*(dim-1)-1].red+src[dim*(dim-1)-2].red)/4;
    dst[dim*dim-1].green = (src[dim*dim-1].green+src[dim*dim-2].green+src[dim*(dim-1)-1].green+src[dim*(dim-1)-2].green)/4;
    dst[dim*dim-1].blue = (src[dim*dim-1].blue+src[dim*dim-2].blue+src[dim*(dim-1)-1].blue+src[dim*(dim-1)-2].blue)/4;

    for (j = 1; j < dim-1; j++) {
        dst[j].red = (src[j].red+src[j-1].red+src[j+1].red+src[j+dim].red+src[j+1+dim].red+src[j-1+dim].red)/6;
        dst[j].green = (src[j].green+src[j-1].green+src[j+1].green+src[j+dim].green+src[j+1+dim].green+src[j-1+dim].green)/6;
        dst[j].blue = (src[j].blue+src[j-1].blue+src[j+1].blue+src[j+dim].blue+src[j+1+dim].blue+src[j-1+dim].blue)/6;
    }
    for (j = dim*(dim-1)+1; j < dim*dim-1; j++) {
        dst[j].red = (src[j].red+src[j-1].red+src[j+1].red+src[j-dim].red+src[j+1-dim].red+src[j-1-dim].red)/6;
        dst[j].green = (src[j].green+src[j-1].green+src[j+1].green+src[j-dim].green+src[j+1-dim].green+src[j-1-dim].green)/6;
        dst[j].blue = (src[j].blue+src[j-1].blue+src[j+1].blue+src[j-dim].blue+src[j+1-dim].blue+src[j-1-dim].blue)/6;
    }
    for (j = dim; j < dim*(dim-1); j+=dim) {
        dst[j].red = (src[j].red+src[j-dim].red+src[j+1].red+src[j+dim].red+src[j+1+dim].red+src[j-dim+1].red)/6;
        dst[j].green = (src[j].green+src[j-dim].green+src[j+1].green+src[j+dim].green+src[j+1+dim].green+src[j-dim+1].green)/6;
        dst[j].blue = (src[j].blue+src[j-dim].blue+src[j+1].blue+src[j+dim].blue+src[j+1+dim].blue+src[j-dim+1].blue)/6;
    }
    for (j = dim+dim-1; j < dim*dim-1; j+=dim) {
        dst[j].red = (src[j].red+src[j-1].red+src[j-dim].red+src[j+dim].red+src[j-dim-1].red+src[j-1+dim].red)/6;
        dst[j].green = (src[j].green+src[j-1].green+src[j-dim].green+src[j+dim].green+src[j-dim-1].green+src[j-1+dim].green)/6;
        dst[j].blue = (src[j].blue+src[j-1].blue+src[j-dim].blue+src[j+dim].blue+src[j-dim-1].blue+src[j-1+dim].blue)/6;
    }
    for (i = 1; i < dim-1; i++) {
        for (j = 1; j < dim-1; j++) {
            tempIndex = tempVar+j;
            dst[tempIndex].red = (src[tempIndex].red+src[tempIndex-1].red+src[tempIndex+1].red+src[tempIndex-dim].red+src[tempIndex-dim-1].red+src[tempIndex-dim+1].red+src[tempIndex+dim].red+src[tempIndex+dim+1].red+src[tempIndex+dim-1].red)/9;
            dst[tempIndex].green = (src[tempIndex].green+src[tempIndex-1].green+src[tempIndex+1].green+src[tempIndex-dim].green+src[tempIndex-dim-1].green+src[tempIndex-dim+1].green+src[tempIndex+dim].green+src[tempIndex+dim+1].green+src[tempIndex+dim-1].green)/9;
            dst[tempIndex].blue = (src[tempIndex].blue+src[tempIndex-1].blue+src[tempIndex+1].blue+src[tempIndex-dim].blue+src[tempIndex-dim-1].blue+src[tempIndex-dim+1].blue+src[tempIndex+dim].blue+src[tempIndex+dim+1].blue+src[tempIndex+dim-1].blue)/9;
        }
        tempVar += dim;
    }
}

char smooth3_descr[] = "smooth3: smooth2 slightly optimized";
void smooth3(int dim, pixel *src, pixel *dst) {
    unsigned i, j, tempIndex;
    unsigned tempVar = dim;
    unsigned dimxPDimM1P = dim*(dim-1);
    unsigned dimxDimM1 = dim*dim-1;
    unsigned dimxPDimM2P = dimxPDimM1P-dim;
    unsigned dimx2 = dim*2;
    //corners
    dst[0].red = (unsigned)(src[0].red+src[1].red+src[dim].red+src[dim+1].red)>>2;
    dst[0].green = (unsigned)(src[0].green+src[1].green+src[dim].green+src[dim+1].green)>>2;
    dst[0].blue = (unsigned)(src[0].blue+src[1].blue+src[dim].blue+src[dim+1].blue)>>2;

    dst[dim-1].red = (unsigned)(src[dim-1].red+src[dim-2].red+src[dimx2-1].red+src[dimx2-2].red)>>2;
    dst[dim-1].green = (unsigned)(src[dim-1].green+src[dim-2].green+src[dimx2-1].green+src[dimx2-2].green)>>2;
    dst[dim-1].blue = (unsigned)(src[dim-1].blue+src[dim-2].blue+src[dimx2-1].blue+src[dimx2-2].blue)>>2;

    dst[dimxPDimM1P].red = (unsigned)(src[dimxPDimM1P].red+src[dimxPDimM1P+1].red+src[dimxPDimM2P].red+src[dimxPDimM2P+1].red)>>2;
    dst[dimxPDimM1P].green = (unsigned)(src[dimxPDimM1P].green+src[dimxPDimM1P+1].green+src[dimxPDimM2P].green+src[dimxPDimM2P+1].green)>>2;
    dst[dimxPDimM1P].blue = (unsigned)(src[dimxPDimM1P].blue+src[dimxPDimM1P+1].blue+src[dimxPDimM2P].blue+src[dimxPDimM2P+1].blue)>>2;

    dst[dimxDimM1].red = (unsigned)(src[dimxDimM1].red+src[dimxDimM1-1].red+src[dimxPDimM1P-1].red+src[dimxPDimM1P-2].red)>>2;
    dst[dimxDimM1].green = (unsigned)(src[dimxDimM1].green+src[dimxDimM1-1].green+src[dimxPDimM1P-1].green+src[dimxPDimM1P-2].green)>>2;
    dst[dimxDimM1].blue = (unsigned)(src[dimxDimM1].blue+src[dimxDimM1-1].blue+src[dimxPDimM1P-1].blue+src[dimxPDimM1P-2].blue)>>2;

    for (j = 1; j < dim-1; j++) {
        dst[j].red = (unsigned)(src[j].red+src[j-1].red+src[j+1].red+src[j+dim].red+src[j+1+dim].red+src[j-1+dim].red)/6;
        dst[j].green = (unsigned)(src[j].green+src[j-1].green+src[j+1].green+src[j+dim].green+src[j+1+dim].green+src[j-1+dim].green)/6;
        dst[j].blue = (unsigned)(src[j].blue+src[j-1].blue+src[j+1].blue+src[j+dim].blue+src[j+1+dim].blue+src[j-1+dim].blue)/6;
    }

    for (j = dimxPDimM1P+1; j < dimxDimM1; j++) {
        dst[j].red = (unsigned)(src[j].red+src[j-1].red+src[j+1].red+src[j-dim].red+src[j+1-dim].red+src[j-1-dim].red)/6;
        dst[j].green = (unsigned)(src[j].green+src[j-1].green+src[j+1].green+src[j-dim].green+src[j+1-dim].green+src[j-1-dim].green)/6;
        dst[j].blue = (unsigned)(src[j].blue+src[j-1].blue+src[j+1].blue+src[j-dim].blue+src[j+1-dim].blue+src[j-1-dim].blue)/6;
    }

    for (j = dim; j < dimxPDimM1P; j+=dim) {
        dst[j].red = (unsigned)(src[j].red+src[j-dim].red+src[j+1].red+src[j+dim].red+src[j+1+dim].red+src[j-dim+1].red)/6;
        dst[j].green = (unsigned)(src[j].green+src[j-dim].green+src[j+1].green+src[j+dim].green+src[j+1+dim].green+src[j-dim+1].green)/6;
        dst[j].blue = (unsigned)(src[j].blue+src[j-dim].blue+src[j+1].blue+src[j+dim].blue+src[j+1+dim].blue+src[j-dim+1].blue)/6;
    }

    for (j = dim+dim-1; j < dimxDimM1; j+=dim) {
        dst[j].red = (unsigned)(src[j].red+src[j-1].red+src[j-dim].red+src[j+dim].red+src[j-dim-1].red+src[j-1+dim].red)/6;
        dst[j].green = (unsigned)(src[j].green+src[j-1].green+src[j-dim].green+src[j+dim].green+src[j-dim-1].green+src[j-1+dim].green)/6;
        dst[j].blue = (unsigned)(src[j].blue+src[j-1].blue+src[j-dim].blue+src[j+dim].blue+src[j-dim-1].blue+src[j-1+dim].blue)/6;
    }

    for (i = 1; i < dim-1; i++) {
        for (j = 1; j < dim-1; j++) {
            tempIndex = tempVar+j;
            dst[tempIndex].red = (unsigned)(src[tempIndex].red+src[tempIndex-1].red+src[tempIndex+1].red+src[tempIndex-dim].red+src[tempIndex-dim-1].red+src[tempIndex-dim+1].red+src[tempIndex+dim].red+src[tempIndex+dim+1].red+src[tempIndex+dim-1].red)/9;
            dst[tempIndex].green = (unsigned)(src[tempIndex].green+src[tempIndex-1].green+src[tempIndex+1].green+src[tempIndex-dim].green+src[tempIndex-dim-1].green+src[tempIndex-dim+1].green+src[tempIndex+dim].green+src[tempIndex+dim+1].green+src[tempIndex+dim-1].green)/9;
            dst[tempIndex].blue = (unsigned)(src[tempIndex].blue+src[tempIndex-1].blue+src[tempIndex+1].blue+src[tempIndex-dim].blue+src[tempIndex-dim-1].blue+src[tempIndex-dim+1].blue+src[tempIndex+dim].blue+src[tempIndex+dim+1].blue+src[tempIndex+dim-1].blue)/9;
        }
        tempVar += dim;
    }
}

char smooth4_descr[] = "smooth4: smooth3 slightly optimized";
void smooth4(int dim, pixel *src, pixel *dst) {
    unsigned i, j, tempIndex;
    unsigned tempVar = dim;
    unsigned dimxPDimM1P = dim*(dim-1);
    unsigned dimxDimM1 = dim*dim-1;
    unsigned dimxPDimM2P = dimxPDimM1P-dim;
    unsigned dimx2 = dim*2;
    unsigned nextLocRed;
    unsigned nextLocGreen;
    unsigned nextLocBlue;
    unsigned currLocRed;
    unsigned currLocGreen;
    unsigned currLocBlue;
    unsigned lastLocRed;
    unsigned lastLocGreen;
    unsigned lastLocBlue;

    //corners
    dst[0].red = (unsigned)(src[0].red+src[1].red+src[dim].red+src[dim+1].red)>>2;
    dst[0].green = (unsigned)(src[0].green+src[1].green+src[dim].green+src[dim+1].green)>>2;
    dst[0].blue = (unsigned)(src[0].blue+src[1].blue+src[dim].blue+src[dim+1].blue)>>2;

    dst[dim-1].red = (unsigned)(src[dim-1].red+src[dim-2].red+src[dimx2-1].red+src[dimx2-2].red)>>2;
    dst[dim-1].green = (unsigned)(src[dim-1].green+src[dim-2].green+src[dimx2-1].green+src[dimx2-2].green)>>2;
    dst[dim-1].blue = (unsigned)(src[dim-1].blue+src[dim-2].blue+src[dimx2-1].blue+src[dimx2-2].blue)>>2;

    dst[dimxPDimM1P].red = (unsigned)(src[dimxPDimM1P].red+src[dimxPDimM1P+1].red+src[dimxPDimM2P].red+src[dimxPDimM2P+1].red)>>2;
    dst[dimxPDimM1P].green = (unsigned)(src[dimxPDimM1P].green+src[dimxPDimM1P+1].green+src[dimxPDimM2P].green+src[dimxPDimM2P+1].green)>>2;
    dst[dimxPDimM1P].blue = (unsigned)(src[dimxPDimM1P].blue+src[dimxPDimM1P+1].blue+src[dimxPDimM2P].blue+src[dimxPDimM2P+1].blue)>>2;

    dst[dimxDimM1].red = (unsigned)(src[dimxDimM1].red+src[dimxDimM1-1].red+src[dimxPDimM1P-1].red+src[dimxPDimM1P-2].red)>>2;
    dst[dimxDimM1].green = (unsigned)(src[dimxDimM1].green+src[dimxDimM1-1].green+src[dimxPDimM1P-1].green+src[dimxPDimM1P-2].green)>>2;
    dst[dimxDimM1].blue = (unsigned)(src[dimxDimM1].blue+src[dimxDimM1-1].blue+src[dimxPDimM1P-1].blue+src[dimxPDimM1P-2].blue)>>2;
    
    nextLocRed = src[2].red;
    nextLocGreen = src[2].green;
    nextLocBlue = src[2].blue;
    currLocRed = src[1].red;
    currLocGreen = src[1].green;
    currLocBlue = src[1].blue;
    lastLocRed = src[0].red;
    lastLocGreen = src[0].green;
    lastLocBlue = src[0].blue;
    for (j = 1; j < dim-1; j++) {
        dst[j].red = (unsigned)(currLocRed+lastLocRed+nextLocRed+src[j+dim].red+src[j+1+dim].red+src[j-1+dim].red)/6;
        dst[j].green = (unsigned)(currLocGreen+lastLocGreen+nextLocGreen+src[j+dim].green+src[j+1+dim].green+src[j-1+dim].green)/6;
        dst[j].blue = (unsigned)(currLocBlue+lastLocBlue+nextLocBlue+src[j+dim].blue+src[j+1+dim].blue+src[j-1+dim].blue)/6;
	lastLocRed = currLocRed;
	lastLocGreen = currLocGreen;
	lastLocBlue = currLocBlue;
	currLocRed = nextLocRed;
	currLocGreen = nextLocGreen;
	currLocBlue = nextLocBlue;
	nextLocRed = src[j+2].red;
	nextLocGreen = src[j+2].green;
	nextLocBlue = src[j+2].blue;
    }
    
    nextLocRed = src[dimxPDimM1P+2].red;
    nextLocGreen = src[dimxPDimM1P+2].green;
    nextLocBlue = src[dimxPDimM1P+2].blue;
    currLocRed = src[dimxPDimM1P+1].red;
    currLocGreen = src[dimxPDimM1P+1].green;
    currLocBlue = src[dimxPDimM1P+1].blue;
    lastLocRed = src[dimxPDimM1P].red;
    lastLocGreen = src[dimxPDimM1P].green;
    lastLocBlue = src[dimxPDimM1P].blue;
    for (j = dimxPDimM1P+1; j < dimxDimM1; j++) {
        dst[j].red = (unsigned)(currLocRed+lastLocRed+nextLocRed+src[j-dim].red+src[j+1-dim].red+src[j-1-dim].red)/6;
        dst[j].green = (unsigned)(currLocGreen+lastLocGreen+nextLocGreen+src[j-dim].green+src[j+1-dim].green+src[j-1-dim].green)/6;
        dst[j].blue = (unsigned)(currLocBlue+lastLocBlue+nextLocBlue+src[j-dim].blue+src[j+1-dim].blue+src[j-1-dim].blue)/6;
	lastLocRed = currLocRed;
	lastLocGreen = currLocGreen;
	lastLocBlue = currLocBlue;
	currLocRed = nextLocRed;
	currLocGreen = nextLocGreen;
	currLocBlue = nextLocBlue;
	nextLocRed = src[j+2].red;
	nextLocGreen = src[j+2].green;
	nextLocBlue = src[j+2].blue;
    }

    nextLocRed = src[dim+dim].red;
    nextLocGreen = src[dim+dim].green;
    nextLocBlue = src[dim+dim].blue;
    currLocRed = src[dim].red;
    currLocGreen = src[dim].green;
    currLocBlue = src[dim].blue;
    lastLocRed = src[0].red;
    lastLocGreen = src[0].green;
    lastLocBlue = src[0].blue;
    for (j = dim; j < dimxPDimM1P; j+=dim) {
        dst[j].red = (unsigned)(currLocRed+lastLocRed+nextLocRed+src[j+1].red+src[j+1+dim].red+src[j-dim+1].red)/6;
        dst[j].green = (unsigned)(currLocGreen+lastLocGreen+nextLocGreen+src[j+1].green+src[j+1+dim].green+src[j-dim+1].green)/6;
        dst[j].blue = (unsigned)(currLocBlue+lastLocBlue+nextLocBlue+src[j+1].blue+src[j+1+dim].blue+src[j-dim+1].blue)/6;
	lastLocRed = currLocRed;
	lastLocGreen = currLocGreen;
	lastLocBlue = currLocBlue;
	currLocRed = nextLocRed;
	currLocGreen = nextLocGreen;
	currLocBlue = nextLocBlue;
	nextLocRed = src[j+dimx2].red;
	nextLocGreen = src[j+dimx2].green;
	nextLocBlue = src[j+dimx2].blue;
    }

    nextLocRed = src[dimx2+dim-1].red;
    nextLocGreen = src[dimx2+dim-1].green;
    nextLocBlue = src[dimx2+dim-1].blue;
    currLocRed = src[dimx2-1].red;
    currLocGreen = src[dimx2-1].green;
    currLocBlue = src[dimx2-1].blue;
    lastLocRed = src[dim-1].red;
    lastLocGreen = src[dim-1].green;
    lastLocBlue = src[dim-1].blue;
    for (j = dimx2-1; j < dimxDimM1; j+=dim) {
        dst[j].red = (unsigned)(currLocRed+lastLocRed+nextLocRed+src[j-1].red+src[j-dim-1].red+src[j-1+dim].red)/6;
        dst[j].green = (unsigned)(currLocGreen+lastLocGreen+nextLocGreen+src[j-1].green+src[j-dim-1].green+src[j-1+dim].green)/6;
        dst[j].blue = (unsigned)(currLocBlue+lastLocBlue+nextLocBlue+src[j-1].blue+src[j-dim-1].blue+src[j-1+dim].blue)/6;
	lastLocRed = currLocRed;
	lastLocGreen = currLocGreen;
	lastLocBlue = currLocBlue;
	currLocRed = nextLocRed;
	currLocGreen = nextLocGreen;
	currLocBlue = nextLocBlue;
	nextLocRed = src[j+dimx2].red;
	nextLocGreen = src[j+dimx2].green;
	nextLocBlue = src[j+dimx2].blue;
    }

    for (i = 1; i < dim-1; i++) {
	nextLocRed = src[tempVar+2].red;
        nextLocGreen = src[tempVar+2].green;
        nextLocBlue = src[tempVar+2].blue;
        currLocRed = src[tempVar+1].red;
        currLocGreen = src[tempVar+1].green;
        currLocBlue = src[tempVar+1].blue;
        lastLocRed = src[tempVar].red;
        lastLocGreen = src[tempVar].green;
        lastLocBlue = src[tempVar].blue;
        for (j = 1; j < dim-1; j++) {
            tempIndex = tempVar+j;
            dst[tempIndex].red = (unsigned)(currLocRed+lastLocRed+nextLocRed+src[tempIndex-dim].red+src[tempIndex-dim-1].red+src[tempIndex-dim+1].red+src[tempIndex+dim].red+src[tempIndex+dim+1].red+src[tempIndex+dim-1].red)/9;
            dst[tempIndex].green = (unsigned)(currLocGreen+lastLocGreen+nextLocGreen+src[tempIndex-dim].green+src[tempIndex-dim-1].green+src[tempIndex-dim+1].green+src[tempIndex+dim].green+src[tempIndex+dim+1].green+src[tempIndex+dim-1].green)/9;
            dst[tempIndex].blue = (unsigned)(currLocBlue+lastLocBlue+nextLocBlue+src[tempIndex-dim].blue+src[tempIndex-dim-1].blue+src[tempIndex-dim+1].blue+src[tempIndex+dim].blue+src[tempIndex+dim+1].blue+src[tempIndex+dim-1].blue)/9;
            lastLocRed = currLocRed;
	    lastLocGreen = currLocGreen;
	    lastLocBlue = currLocBlue;
	    currLocRed = nextLocRed;
	    currLocGreen = nextLocGreen;
	    currLocBlue = nextLocBlue;
	    nextLocRed = src[j+2].red;
	    nextLocGreen = src[j+2].green;
	    nextLocBlue = src[j+2].blue;
        }
        tempVar += dim;
    }
}


/*********************************************************************
 * register_smooth_functions - Register all of your different versions
 *     of the smooth kernel with the driver by calling the
 *     add_smooth_function() for each test function.  When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.
 *********************************************************************/

void register_smooth_functions() {
    //add_smooth_function(&smooth, smooth_descr);
    add_smooth_function(&naive_smooth, naive_smooth_descr);
    add_smooth_function(&smooth2, smooth2_descr);
    add_smooth_function(&smooth3, smooth3_descr);
    add_smooth_function(&smooth4, smooth4_descr);
    /* ... Register additional test functions here */
}
