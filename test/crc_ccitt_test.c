/* .+

.context    : aTalk, real time data communication
.title      : test CRC 16 CCITT
.kind       : c source
.author     : Fabrizio Pollastri <mxgbot@gmail.com>
.site       : Revello - Italy
.creation   : 25-Jul-2019
.copyright  : (c) 2019 Fabrizio Pollastri
.license    : GNU Lesser General Public License version 3

.description

This program tests the function that computes the 16 bits cyclic redundancy
check according to the CCITT standard. Several computation runs are performed
over buffers of random data with content and size varying at each run.

.- */

# define NUMBER_OF_TESTS 10000
# define DATA_SIZE_MIN 1
# define DATA_SIZE_MAX 254

#include <stdio.h>
#include "../src/crc_ccitt.h"


int main() {

   size_t random_size;
   unsigned char random_data[DATA_SIZE_MAX + 2];
   unsigned short crc;

   /* repeat the test, each time changing data */
   for (int i=0; i < NUMBER_OF_TESTS; i++) {

       /* generate a buffer of random data, with random size in the range
	* DATA_SIZE_MIN - DATA_SIZE_MAX */
       random_size = rand() % (DATA_SIZE_MAX - DATA_SIZE_MIN) + DATA_SIZE_MIN;
       for (size_t r=0; r < random_size; r += 4) {
	   random_data[r] = rand();
       }

       /* compute CRC on data */
       crc = crc_ccitt(random_data,random_size,0xffff,0);

       /* append CRC to data buffer */
       random_data[random_size] = (unsigned char)((crc >> 8) & 0xff);
       random_data[random_size + 1] = (unsigned char)(crc & 0xff);

       /* compute CRC on data plus CRC: the result shoud be zero. */
       crc = crc_ccitt(random_data,random_size + 2,0xffff,0);

       /* check errors */
       if (crc) {
           printf("ERROR at test #%d.\n", i);
	   exit(1);
       }
   }
   printf("TEST OK\n");
}
