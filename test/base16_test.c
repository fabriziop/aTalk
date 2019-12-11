/* .+

.context    : aTalk, real time data communication
.title      : test base 16 ascii codec
.kind       : c source
.author     : Fabrizio Pollastri <mxgbot@gmail.com>
.site       : Revello - Italy
.creation   : 8-Aug-2019
.copyright  : (c) 2019 Fabrizio Pollastri
.license    : GNU Lesser General Public License version 3

.description

This program tests the base 16 ascii encoder and decoder functions. 
A buffer of random data is encoded and then decoded and checked against the
original data. Several computation runs are performed with data content and
data size varying at each run.

.- */

# define NUMBER_OF_TESTS 10000
# define DATA_SIZE_MIN 1
# define DATA_SIZE_MAX 10000

#include <stdio.h>
#include "../src/base16.h"


int main() {

   unsigned char random_data[DATA_SIZE_MAX];
   unsigned int random_data_size;
   unsigned char encoded_data[DATA_SIZE_MAX * 2];
   unsigned char decoded_data[DATA_SIZE_MAX];
   unsigned int decoded_data_size;
   int error;

   /* repeat the test, each time changing data */
   for (int i=0; i < NUMBER_OF_TESTS; i++) {

       /* generate a buffer of random data, with random size in the range
	* DATA_SIZE_MIN - DATA_SIZE_MAX */
       random_data_size = rand() % (DATA_SIZE_MAX-DATA_SIZE_MIN)+DATA_SIZE_MIN;
       for (unsigned int r=0; r < random_data_size; r += 4) {
	   random_data[r] = rand();
       }

       /* encode and decode data */
       b16encode(random_data,random_data_size,encoded_data);
       error = b16decode(encoded_data,decoded_data,&decoded_data_size);

       /* check for errors */
       if (error) {
           printf("ERROR #%d decoding data at test #%d.\n",error,i);
       }
       if (random_data_size != decoded_data_size) {
           printf("ERROR on decoded data size at test #%d.\n", i);
           exit(1);
       }
       for (int j=0; j < decoded_data_size; j++) {
	   if (random_data[j] != decoded_data[j]) {
               printf("ERROR on data at test #%d.\n", i);
	       exit(1);
	   }
       }
   }
   printf("TEST OK\n");
}
