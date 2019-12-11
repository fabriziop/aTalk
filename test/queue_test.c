/* .+

.context    : aTalk, real time data communication
.title      : test aTalk tx/rx communication loop
.kind       : c source
.author     : Fabrizio Pollastri <mxgbot@gmail.com>
.site       : Revello - Italy
.creation   : 15-Aug-2019
.copyright  : (c) 2019 Fabrizio Pollastri
.license    : GNU Lesser General Public License version 3

.description

This program tests the aTalk functions atalk_tx and atalk_rx implementing
a software tx/rx loop for testing pourposes. 

.- */

#define NUMBER_OF_TESTS 1000
#define DEPTH 4

#include <stdint.h>
#include <stdio.h>
#include "../src/queue.h"


int main() {

    struct Queue *queue;
    void *random_pointer, *random_pointer_copy;
    int error;

    /* init queue and check for error */
    queue = queue_init(DEPTH);
    if (queue == NULL)
	printf("ERROR: queue allocation failure.\n");

    /* repeat the test, each time changing random pointer */
    for (int i=0; i < NUMBER_OF_TESTS; i++) {

        /* generate a random pointer */
        random_pointer = (void *)(intptr_t)rand();

        /* queue random pointer and check for errors */
        error = queue_push(queue,random_pointer);

        /* check for errors */
        if (error) {
            printf("ERROR #%d queuing data at test #%d.\n",error,i);
	    exit(1);
        }

        /* dequeue data and check for errors*/
        random_pointer_copy = queue_pop(queue);
        if (random_pointer_copy == NULL) {
            printf("ERROR empty queue while dequeuing data at test #%d.\n",i);
	    exit(1);
        }

	/* compare dequeued pointer with original pointer */
	if (random_pointer != random_pointer_copy) {
	    printf("ERROR input and output pointer differs. Test #%d.\n",i);
	    printf("input pointer %x, output pointer %x.\n",
	        (unsigned int)(intptr_t)random_pointer,
		(unsigned int)(intptr_t)random_pointer_copy);
	    exit(1);
	}
    }

    printf("TEST OK\n");

}
