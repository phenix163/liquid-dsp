//
// interleaver_example.c
//
// This example demonstrates the functionality of the liquid
// interleaver object.  Interleavers serve to distribute 
// grouped bit errors evenly throughout a block of data. This
// aids certain forward error-correction codes in correcting
// bit errors.  In this example, data bits are interleaved and
// de-interleaved; the resulting sequence is validated to
// match the original.
// SEE ALSO: packetizer_example.c
//

#include <stdio.h>
#include <stdlib.h> // for rand()

#include "liquid.h"

int main() {
    // options
    unsigned int n=9; // message length
    interleaver_type type = LIQUID_INTERLEAVER_SEQUENCE; // interleaver type

    // create the interleaver
    interleaver q = interleaver_create(n, type);
    interleaver_print(q);
    if (n<10)
        interleaver_debug_print(q);

    // create arrays
    unsigned char x[n]; // original message data
    unsigned char y[n]; // interleaved data
    unsigned char z[n]; // de-interleaved data

    // generate random data sequence
    unsigned int i;
    for (i=0; i<n; i++)
        x[i] = rand()%256;

    // interleave/de-interleave the data
    interleaver_encode(q,x,y);
    interleaver_decode(q,y,z);
    //interleaver_print(q);

    // print, compute errors
    unsigned int num_errors=0;
    printf("x\ty\tz\n");
    for (i=0; i<n; i++) {
        printf("%u\t%u\t%u\n", (unsigned int) (x[i]),
                               (unsigned int) (y[i]),
                               (unsigned int) (z[i]));
        //printf("y[%u] = %u\n", i, (unsigned int) (y[i]));
        //printf("y[%u] = %#0x\n", i, (unsigned int) (y[i]));
        num_errors += (x[i]==z[i]) ? 0 : 1;
    }
    printf("errors: %u / %u\n", num_errors, n);

    // destroy the interleaver object
    interleaver_destroy(q);

    printf("done.\n");
    return 0;
}

