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
#define DATA_SIZE_MIN 1
#define DATA_SIZE_MAX 100
#define MSG_ENCODER BASE16
#define QUEUE_DEPTH 4

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../src/atalk_loop.h"


int main() {

  struct aTalk *atalk;;
  int error;
  char *random_data;
  uint8_t random_data_size;
  int msglen;

  /* init aTalk */
  atalk = atalk_init(DATA_SIZE_MAX,MSG_ENCODER);
  if (atalk == NULL) {
    printf("ERROR: atalk_init failed to allocate aTalk struc.\n");
    exit(1);
  }

  /* init local loop */
  error = atalk_loop_init(atalk,QUEUE_DEPTH);
  if (error) {
    printf("ERROR: atalk_loop_init failed to allocate Queue struc.\n");
    exit(1);
  }

  /* repeat the test, each time changing data */
  for (int i=0; i < NUMBER_OF_TESTS; i++) {

    /* generate a buffer of random data ASCII printable, with random size
     * in the range DATA_SIZE_MIN - DATA_SIZE_MAX */
    random_data = atalk->send_msg_encoded;
    random_data_size = rand() % (DATA_SIZE_MAX-DATA_SIZE_MIN)+DATA_SIZE_MIN;
    for (unsigned int r=0; r < random_data_size - 1; r++) {
      random_data[r] = rand() % 64 + 32;
    }
    random_data[random_data_size - 1] = 0;

    /* queue data */
    msglen = atalk_loop_tx(atalk);

    /* check for errors */
    if (msglen < 0) {
      printf("ERROR #%d queuing data at test #%d.\n",msglen,i);
      exit(1);
    }

    /* dequeue data */
    msglen = atalk_loop_rx(atalk);
	
    /* check for errors */
    if (msglen < 0) {
      printf("ERROR #%d dequeuing data at test #%d.\n",msglen,i);
      exit(1);
    }
    if (strcmp(random_data,atalk->receive_msg_encoded)) {
      printf("ERROR #%d on received data at test #%d.\n",msglen,i);
      printf("Random data:\n%s\n",random_data);
      printf("Received data:\n%s\n",atalk->receive_msg_encoded);
      exit(1);
    }
  }
  printf("TEST OK\n");
}
