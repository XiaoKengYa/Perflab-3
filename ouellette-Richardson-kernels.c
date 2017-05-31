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
  unsigned int i, j, c, srcRow, srcRow2, srcRow3, srcRow4, srcRow5, srcRow6, srcRow7, srcRow8, srcRow9 ,srcRow10,srcRow11, srcRow12,srcRow13,srcRow14,srcRow15,srcRow16;

  unsigned int i1, i2 ,i3, i4, i5, i6, i7, i8, i9, i10, i11, i12, i13, i14, i15;

  int imax = (dim - 15);

  for (i = 0; i < imax; i+=16){

    srcRow = (dim * i);
    srcRow2 = srcRow + dim;
    srcRow3 = srcRow2 + dim;
    srcRow4 = srcRow3 + dim;
    srcRow5 = srcRow4 + dim;
    srcRow6 = srcRow5 + dim;
    srcRow7 = srcRow6 + dim;
    srcRow8 = srcRow7 + dim;
    srcRow9 = srcRow8 + dim;
    srcRow10 = srcRow9 + dim;
    srcRow11 = srcRow10 + dim;
    srcRow12 = srcRow11 + dim;
    srcRow13 = srcRow12 + dim;
    srcRow14 = srcRow13 + dim;
    srcRow15 = srcRow14 + dim;
    srcRow16 = srcRow15 + dim;

    i1 = i + 1;
    i2 = i + 2;
    i3 = i + 3;
    i4 = i + 4;
    i5 = i + 5;
    i6 = i + 6;
    i7 = i + 7;
    i8 = i + 8;
    i9 = i + 9;
    i10 = i + 10;
    i11 = i + 11;
    i12 = i + 12;
    i13 = i + 13;
    i14 = i + 14;
    i15 = i + 15;

    c = ((dim - 1) * dim);
    for ( j = 0; j < dim; j++){
      dst[c + i] =  src[srcRow + j];
      dst[c + i1] =  src[srcRow2 + j];
      dst[c + i2] =  src[srcRow3 + j];
      dst[c + i3] =  src[srcRow4 + j];
      dst[c + i4] =  src[srcRow5 + j];
      dst[c + i5] =  src[srcRow6 + j];
      dst[c + i6] =  src[srcRow7 + j];
      dst[c + i7] =  src[srcRow8 + j];
      dst[c + i8] =  src[srcRow9 + j];
      dst[c + i9] =  src[srcRow10 + j];
      dst[c + i10] =  src[srcRow11 + j];
      dst[c + i11] =  src[srcRow12 + j];
      dst[c + i12] =  src[srcRow13 + j];
      dst[c + i13] =  src[srcRow14 + j];
      dst[c + i14] =  src[srcRow15 + j];
      dst[c + i15] =  src[srcRow16 + j];
      c -= dim;
    }
  }

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


char rotate_by_row_descr_Three_Unroll_Outer_Reverse_Access[] = "rotateByRow: Using whole row move. Three Undroll outer Reverse_Access";
void rotateByRowThreeUnrollOuterReverseAccess(int dim, pixel *src, pixel *dst)
{
  int i, j, c, srcRow, srcRow2, srcRow3, srcRow4, srcRow5, srcRow6, srcRow7, srcRow8;

  int i1, i2 ,i3, i4, i5, i6, i7;



  for (i = 0; i < (dim - 7) ; i+=8){

    srcRow = (dim * i);
    srcRow2 = srcRow + dim;
    srcRow3 = srcRow2 + dim;
    srcRow4 = srcRow3 + dim;
    srcRow5 = srcRow4 + dim;
    srcRow6 = srcRow5 + dim;
    srcRow7 = srcRow6 + dim;
    srcRow8 = srcRow7 + dim;

    i1 = i + 1;
    i2 = i + 2;
    i3 = i + 3;
    i4 = i + 4;
    i5 = i + 5;
    i6 = i + 6;
    i7 = i + 7;



    for (c = ((dim - 1) * dim), j = 0; j < dim; j++){
      dst[c + i] =  src[srcRow + j];
      dst[c + i1] =  src[srcRow2 + j];
      dst[c + i2] =  src[srcRow3 + j];
      dst[c + i3] =  src[srcRow4 + j];
      dst[c + i4] =  src[srcRow5 + j];
      dst[c + i5] =  src[srcRow6 + j];
      dst[c + i6] =  src[srcRow7 + j];
      dst[c + i7] =  src[srcRow8 + j];
      c -= dim;
    }
  }
}


char rotate_by_row_descr_Three_Unroll_Outer_Reverse_AccessB16[] = "rotateByRow: Using whole row move. Three Undroll outer Reverse_Access AB Test 16";
void rotateByRowThreeUnrollOuterReverseAccessB16(int dim, pixel *src, pixel *dst)
{
  unsigned int i, j, c, srcRow, srcRow2, srcRow3, srcRow4, srcRow5, srcRow6, srcRow7, srcRow8, srcRow9 ,srcRow10,srcRow11, srcRow12,srcRow13,srcRow14,srcRow15,srcRow16;

  unsigned int i1, i2 ,i3, i4, i5, i6, i7, i8, i9, i10, i11, i12, i13, i14, i15;

  int imax = (dim - 15);

  for (i = 0; i < imax; i+=16){

    srcRow = (dim * i);
    srcRow2 = srcRow + dim;
    srcRow3 = srcRow2 + dim;
    srcRow4 = srcRow3 + dim;
    srcRow5 = srcRow4 + dim;
    srcRow6 = srcRow5 + dim;
    srcRow7 = srcRow6 + dim;
    srcRow8 = srcRow7 + dim;
    srcRow9 = srcRow8 + dim;
    srcRow10 = srcRow9 + dim;
    srcRow11 = srcRow10 + dim;
    srcRow12 = srcRow11 + dim;
    srcRow13 = srcRow12 + dim;
    srcRow14 = srcRow13 + dim;
    srcRow15 = srcRow14 + dim;
    srcRow16 = srcRow15 + dim;

    i1 = i + 1;
    i2 = i + 2;
    i3 = i + 3;
    i4 = i + 4;
    i5 = i + 5;
    i6 = i + 6;
    i7 = i + 7;
    i8 = i + 8;
    i9 = i + 9;
    i10 = i + 10;
    i11 = i + 11;
    i12 = i + 12;
    i13 = i + 13;
    i14 = i + 14;
    i15 = i + 15;

    c = ((dim - 1) * dim);
    for ( j = 0; j < dim; j++){
      dst[c + i] =  src[srcRow + j];
      dst[c + i1] =  src[srcRow2 + j];
      dst[c + i2] =  src[srcRow3 + j];
      dst[c + i3] =  src[srcRow4 + j];
      dst[c + i4] =  src[srcRow5 + j];
      dst[c + i5] =  src[srcRow6 + j];
      dst[c + i6] =  src[srcRow7 + j];
      dst[c + i7] =  src[srcRow8 + j];
      dst[c + i8] =  src[srcRow9 + j];
      dst[c + i9] =  src[srcRow10 + j];
      dst[c + i10] =  src[srcRow11 + j];
      dst[c + i11] =  src[srcRow12 + j];
      dst[c + i12] =  src[srcRow13 + j];
      dst[c + i13] =  src[srcRow14 + j];
      dst[c + i14] =  src[srcRow15 + j];
      dst[c + i15] =  src[srcRow16 + j];
      c -= dim;
    }
  }
}



char rotate_by_row_descr_Three_Unroll_Outer_Reverse_AccessB32[] = "rotateByRow: Using whole row move. Three Undroll outer Reverse_Access AB Test 32";
void rotateByRowThreeUnrollOuterReverseAccessB32(int dim, pixel *src, pixel *dst)
{
  unsigned int i, j, c, srcRow, srcRow2, srcRow3, srcRow4, srcRow5, srcRow6, srcRow7, srcRow8, srcRow9 ,srcRow10,srcRow11, srcRow12,srcRow13,srcRow14,srcRow15,srcRow16,srcRow17,srcRow18,srcRow19,srcRow20,srcRow21,srcRow22,srcRow23,srcRow24,srcRow25,srcRow26,srcRow27,srcRow28,srcRow29,srcRow30, srcRow31, srcRow32;

  unsigned int i1, i2 ,i3, i4, i5, i6, i7, i8, i9, i10, i11, i12, i13, i14, i15, i16, i17, i18, i19, i20, i21, i22, i23, i24, i25, i26, i27, i28, i29, i30, i31;

  int imax = (dim - 31);

  for (i = 0; i < imax; i+=32){

    srcRow = (dim * i);
    srcRow2 = srcRow + dim;
    srcRow3 = srcRow2 + dim;
    srcRow4 = srcRow3 + dim;
    srcRow5 = srcRow4 + dim;
    srcRow6 = srcRow5 + dim;
    srcRow7 = srcRow6 + dim;
    srcRow8 = srcRow7 + dim;
    srcRow9 = srcRow8 + dim;
    srcRow10 = srcRow9 + dim;
    srcRow11 = srcRow10 + dim;
    srcRow12 = srcRow11 + dim;
    srcRow13 = srcRow12 + dim;
    srcRow14 = srcRow13 + dim;
    srcRow15 = srcRow14 + dim;
    srcRow16 = srcRow15 + dim;

    srcRow17 = srcRow16 + dim;
    srcRow18 = srcRow17 + dim;
    srcRow19 = srcRow18 + dim;
    srcRow20 = srcRow19 + dim;
    srcRow21 = srcRow20 + dim;
    srcRow22 = srcRow21 + dim;
    srcRow23 = srcRow22 + dim;
    srcRow24 = srcRow23 + dim;
    srcRow25 = srcRow24 + dim;
    srcRow26 = srcRow25 + dim;
    srcRow27 = srcRow26 + dim;
    srcRow28 = srcRow27 + dim;
    srcRow29 = srcRow28 + dim;
    srcRow30 = srcRow29 + dim;
    srcRow31 = srcRow30 + dim;
    srcRow32 = srcRow31 + dim;





    i1 = i + 1;
    i2 = i + 2;
    i3 = i + 3;
    i4 = i + 4;
    i5 = i + 5;
    i6 = i + 6;
    i7 = i + 7;
    i8 = i + 8;
    i9 = i + 9;
    i10 = i + 10;
    i11 = i + 11;
    i12 = i + 12;
    i13 = i + 13;
    i14 = i + 14;
    i15 = i + 15;

    i16 = i + 16;
    i17 = i + 17;
    i18 = i + 18;
    i19 = i + 19;
    i20 = i + 20;
    i21 = i + 21;
    i22 = i + 22;
    i23 = i + 23;
    i24 = i + 24;
    i25 = i + 25;
    i26 = i + 26;
    i27 = i + 27;
    i28 = i + 28;
    i29 = i + 29;
    i30 = i + 30;
    i31 = i + 31;


    c = (dim - 1) * dim;
    for ( j = 0; j < dim; j++){
      dst[c + i] =  src[srcRow + j];
      dst[c + i1] =  src[srcRow2 + j];
      dst[c + i2] =  src[srcRow3 + j];
      dst[c + i3] =  src[srcRow4 + j];
      dst[c + i4] =  src[srcRow5 + j];
      dst[c + i5] =  src[srcRow6 + j];
      dst[c + i6] =  src[srcRow7 + j];
      dst[c + i7] =  src[srcRow8 + j];
      dst[c + i8] =  src[srcRow9 + j];
      dst[c + i9] =  src[srcRow10 + j];
      dst[c + i10] =  src[srcRow11 + j];
      dst[c + i11] =  src[srcRow12 + j];
      dst[c + i12] =  src[srcRow13 + j];
      dst[c + i13] =  src[srcRow14 + j];
      dst[c + i14] =  src[srcRow15 + j];
      dst[c + i15] =  src[srcRow16 + j];

        dst[c + i16] =  src[srcRow17 + j];
        dst[c + i17] =  src[srcRow18 + j];
        dst[c + i18] =  src[srcRow19 + j];
        dst[c + i19] =  src[srcRow20 + j];
        dst[c + i20] =  src[srcRow21 + j];
        dst[c + i21] =  src[srcRow22 + j];
        dst[c + i22] =  src[srcRow23 + j];
        dst[c + i23] =  src[srcRow24 + j];
        dst[c + i24] =  src[srcRow25 + j];
        dst[c + i25] =  src[srcRow26 + j];
        dst[c + i26] =  src[srcRow27 + j];
        dst[c + i27] =  src[srcRow28 + j];
        dst[c + i28] =  src[srcRow29 + j];
        dst[c + i29] =  src[srcRow30 + j];
        dst[c + i30] =  src[srcRow31 + j];
        dst[c + i31] =  src[srcRow32 + j];
      c -= dim;
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

    //add_rotate_function(&rotateByRowThree, rotate_by_row_descr_Three);
    //add_rotate_function(&rotateByRowThreeB, rotate_by_row_descr_ThreeB);
    //add_rotate_function(&rotateByRowThreeUnroll8, rotate_by_row_descr_ThreeUnroll8);
    //  add_rotate_function(&rotateByRowThreeUnrollOuterReverseAccess, rotate_by_row_descr_Three_Unroll_Outer_Reverse_Access);
    //  add_rotate_function(&rotateByRowThreeUnrollOuterReverseAccessB16, rotate_by_row_descr_Three_Unroll_Outer_Reverse_AccessB16);
    //    add_rotate_function(&rotateByRowThreeUnrollOuterReverseAccessB32, rotate_by_row_descr_Three_Unroll_Outer_Reverse_AccessB32);
    //add_rotate_function(&rotateByRow, rotate_by_row_descr);
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

 /*static pixel divBy(pixel p, int s, int i, int j, pixel *src) {
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
 }*/

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

char smooth_descr[] = "smooth: final version";
 void smooth(int dim, pixel *src, pixel *dst)
 {
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

 char smooth2_descr[] = "smooth2: ...";
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
     //add_smooth_function(&smooth2, smooth2_descr);
     /* ... Register additional test functions here */
 }
