/* ==================================================================== *
 *                                      *
 *  block_dgemm.c -- Implemant a block matrix multiplication routine    *
 *                                                                      *
 * ==================================================================== */

#include "square_dgemm.h"

#include <stdio.h>
#include <stdlib.h>

/* block parameter ... */
#ifndef BLOCK_SIZE
#   define BLOCK_SIZE ((unsigned) 35)
#endif

// version 2.0 of the block multiplication
unsigned bestBlockSize (const int dim ) {

    unsigned OPT_BLOCK_SIZE = dim ;    // variables to define optimal block size

    // find the optimal block size for the test dimension considered


    if (dim % BLOCK_SIZE == 0) {
        OPT_BLOCK_SIZE = BLOCK_SIZE;
    } else if (dim < BLOCK_SIZE) {
        OPT_BLOCK_SIZE = dim;
    } else {

        /**
         * Check for best fit from below;
         */
        for (int i = 2; i < dim / 2; i++) {

            int testSize = dim % i;

            /**
             * Check to see if current testBlock size is a multiple of BLOCK_SIZE
             */
            if (testSize == 0) {

                /**
                 * Save the smallest differnce between blocksize
                 */
                if ( abs(i - BLOCK_SIZE ) < abs(OPT_BLOCK_SIZE - BLOCK_SIZE)) {
                    OPT_BLOCK_SIZE = i;
                }
            }
        }
    }

    return OPT_BLOCK_SIZE;
}





/**
 *  square_dgemm -- multiply two block matrices A and B adding result to C, result is C = C + A*B
 */
void square_dgemm (const double  *A, const double  *B, double  *C, const unsigned  dim) {
    unsigned lead;  // leading dimension for block multiplication, i.e. number of blocks in a row or column

    unsigned  e, f, g, i, j, k, l, m, n;        // aiding variables to use in the various loops

    unsigned NEW_BLOCK_SIZE = bestBlockSize(dim);

    // use the implemented matrix block multiplication for the optimal size

    lead = dim / NEW_BLOCK_SIZE;

    for (i = 0 ; i < lead; i++) {   // iterate through rows of blocks of matrix A
        for (j = 0; j < lead; j++) { // iterate through columns of blocks of matrix A or rows of blocks of matrix B
            for (k = 0; k < lead; k++) {  // iterate through columns of blocks of matrix B
                for (l = 0; l < NEW_BLOCK_SIZE; l++) {  // iterate through rows of a single block of A
                    const double *A_ix = A + l * dim + j * NEW_BLOCK_SIZE + i * NEW_BLOCK_SIZE * dim;   /* in this definition the j allows to move to the first element of each block,
                                                                                        while the i between rows of blocks */

                    for (m = 0; m < NEW_BLOCK_SIZE; m++) {  // iterate through columns of a single block of B
                        const double *B_xj = B + m + k * NEW_BLOCK_SIZE + j * NEW_BLOCK_SIZE * dim;

                        double cij = C[l * dim + m + i * dim * NEW_BLOCK_SIZE + k * NEW_BLOCK_SIZE];
                        unsigned m_ind = 0;

                        for (n = 0; n < NEW_BLOCK_SIZE; n++) {
                            cij += A_ix[n] * B_xj[m_ind];
                            m_ind += dim;
                        }

                        C[l * dim + m + i * dim * NEW_BLOCK_SIZE + k * NEW_BLOCK_SIZE] = cij;
                    }
                }

            }
        }
    }
}



