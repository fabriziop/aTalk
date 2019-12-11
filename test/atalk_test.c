/* .+

.context    : aTalk, real time data communication
.title      : test aTalk protocol
.kind       : c source
.author     : Fabrizio Pollastri <mxgbot@gmail.com>
.site       : Revello - Italy
.creation   : 10-Aug-2019
.copyright  : (c) 2019 Fabrizio Pollastri
.license    : GNU Lesser General Public License version 3

.description

This program tests the aTalk communication protocol. 

.- */

#define NUMBER_OF_TESTS 100
#define RANDOM_DATA_SIZE_MIN 1
#define RANDOM_DATA_SIZE_MAX 32
#define DATA_SIZE_MAX 32
#define MSG_ENCODER BASE16
#define QUEUE_DEPTH 4


#include <stdio.h>

#include "../src/atalk.h"
#include "../src/atalk_loop.h"


int main() {

  struct aTalk *atalk;
  unsigned char random_data[RANDOM_DATA_SIZE_MAX];
  unsigned int random_data_size;
  unsigned char receive_data[DATA_SIZE_MAX];
  uint8_t receive_data_size;
  int error;

  /* init aTalk */
  atalk = atalk_init(DATA_SIZE_MAX,MSG_ENCODER);
  if (atalk == NULL) {
    printf("ERROR: atalk_init failed to allocate aTalk struc.\n");
    exit(1);
  }
  
  /* init local loop */
  error = atalk_loop_init(atalk,QUEUE_DEPTH);
  if (error) {
    printf("ERROR: atalk_loop_init failed to allocate Queue struc.");
    exit(1);
  }


  /* repeat the test, each time changing data */
  for (int i=0; i < NUMBER_OF_TESTS; i++) {

    /* generate a buffer of random data, with random size in the range
    * DATA_SIZE_MIN - DATA_SIZE_MAX */
    random_data_size = rand() 
      % (RANDOM_DATA_SIZE_MAX - RANDOM_DATA_SIZE_MIN)
      + RANDOM_DATA_SIZE_MIN;
    for (unsigned int r=0; r < random_data_size; r++) {
      random_data[r] = rand();
    }

    /* send random data */
    error = atalk_send(atalk,random_data,random_data_size);

    /* check for send errors */
    if (error) {
      printf("ERROR %d sending data at test #%d.\n",error,i);
      continue;
    }

    /* receive data */
    error = atalk_receive(atalk,receive_data,&receive_data_size);

    /* check for receive errors */
    if (error) {
      printf("ERROR #%d receiving data at test #%d.\n",error,i);
      continue;
    }
	
    /* compare received data with transmitted data */	
    for (int j=0; j < receive_data_size; j++) {
      if (random_data[j] != receive_data[j]) {
        printf("ERROR on data at test #%d.\n", i);
        printf("ERROR receive data size = %d\n",receive_data_size);
        printf("ERROR tx data[%d] = %x\n",j,random_data[j]);
        printf("ERROR rx data[%d] = %x\n",j,receive_data[j]);
        exit(1);
      }
    }
  }
    printf("TEST OK\n");
}

