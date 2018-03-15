#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

void transpose( int n, int blocksize, int * dst, int * src ) {
    int i,j, i2, j2;
    /* TO DO: implement blocking (two more loops) */
    /*for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            dst[j + i*n] = src[i + j*n];
        }
    }*/
    for(i = 0; i < n; i += blocksize){
        for(j = i; j < n; j += blocksize){
            //dst[j + i*n] = src[i + j*n];
            //swap(blocksize, *(src + i + j * n), *(src + j + i * n), *dst);
            for(i2 = 0; i2 < blocksize; i2++) {
                for(j2 = 0; j2 < blocksize; j2++){
                    if ((j + i * n + i2 + j2*n) < n * n && (i + j * n + j2 + i2*n) < n * n) {
                        dst[i + j * n + j2 + i2*n] = src[j + i * n + i2 + j2*n];
                        dst[j + i * n + i2 + j2*n] = src[i + j * n + j2 + i2*n];
                    }
                }
            }
        }
    }
    /*for (int a = 0; a < n; a++){
        for (int b = 0; b < n; b++) {
            src[b + a*n] = dst[b + a*n];
        }
    }*/
}

/*void swap(int n, int * mcol, int * mrow, int * dst) {
    int i,j;
    for(i = 0; i < n; i++)
        for(j = 0; j < 0; j++)
            mcol[j + i*n] = mrow[i + j*n];
    
}*/

int main( int argc, char **argv ) {
    for (int n = 1000; n <= 8000; n *= 2){
        for (int blocksize = 5; blocksize <= n / 2; blocksize += 5){
            if (blocksize >= 45) blocksize += 5;
            if (n >= 2000 && blocksize >= 205) blocksize += 10;
            if (n >= 4000 && blocksize >= 515) blocksize += 30;
            if (n >= 4000 && blocksize >= 1055) blocksize += 50;
            int i, j;
            //int n = n,i,j;
            //int blocksize = blocksize; /* to do: find a better block size */

            /* allocate an n*n block of integers for the matrices */
            int *A = (int*)malloc( n*n*sizeof(int) );
            int *B = (int*)malloc( n*n*sizeof(int) );

            /* initialize A,B to random integers */
            //rand( time( NULL ) );
            for( i = 0; i < n*n; i++ ) A[i] = rand( );
            for( i = 0; i < n*n; i++ ) B[i] = rand( );

            /* measure performance */
            struct timeval start, end;

            gettimeofday( &start, NULL );
            transpose( n, blocksize, B, A );
            gettimeofday( &end, NULL );

            double seconds = (end.tv_sec - start.tv_sec) +
                1.0e-6 * (end.tv_usec - start.tv_usec);

            printf( "n: %d ", n);
            printf( "blocksize: %d", blocksize);
            printf( "  %g milliseconds\n", seconds*1e3 );

            /* check correctness */
            for( i = 0; i < n; i++ )
                for( j = 0; j < n; j++ )
                    if( B[j+i*n] != A[i+j*n] ) {
                        printf("Error!!!! Transpose does not result in correct answer!!\n");
                        exit( -1 );
                    }

            /* release resources */
            free( A );
            free( B );
        }
        printf("\n");
    }
    return 0;
}

