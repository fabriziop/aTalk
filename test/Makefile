# .+ 
#
# .context    : aTalk, real time \data communicationd
# .title      : test make file
# .kind       : make file
# .author     : Fabrizio Pollastri <mxgbot@gmail.com>
# .site       : Revello - Italy
# .creation   : 5-Aug-2019
# .copyright  : (c) 2019 Fabrizio Pollastri
# .license    : GNU Lesser General Public License version 3
# 
# .-

.INCLUDE_DIRS += ../src/atalk ../src

base16_test : base16_test.c ../src/base16.h ../src/base16.c
	cc base16_test.c ../src/base16.c -o base16_test

base64_test : base64_test.c ../src/base64.h ../src/base64.c
	cc base64_test.c ../src/base64.c -o base64_test

crc_ccitt_test : crc_ccitt_test.c ../src/crc_ccitt.h ../src/crc_ccitt.c
	cc crc_ccitt_test.c ../src/crc_ccitt.c -o crc_ccitt_test

queue_test : queue_test.c ../src/queue.h ../src/queue.c
	cc queue_test.c ../src/queue.c -o queue_test

atalk_loop_test : atalk_loop_test.c ../src/atalk.c ../src/atalk_loop.h ../src/atalk_loop.c \
	../src/queue.h ../src/queue.c
	cc atalk_loop_test.c ../src/atalk.c ../src/atalk_loop.c ../src/queue.c \
	../src/base16.c ../src/base64.c ../src/crc_ccitt.c -o atalk_test -o atalk_loop_test

atalk_test : atalk_test.c ../src/atalk.c ../src/atalk_loop.c ../src/queue.c ../src/base16.c ../src/base64.c ../src/crc_ccitt.c
	cc atalk_test.c ../src/atalk_loop.c ../src/atalk.c ../src/queue.c ../src/base16.c ../src/base64.c ../src/crc_ccitt.c -o atalk_test


.PHONY : test clean

test : base16_test base64_test crc_ccitt_test queue_test atalk_loop_test atalk_test
	./base16_test
	./base64_test
	./crc_ccitt_test
	./queue_test
	./atalk_loop_test
	./atalk_test

clean :
	find . -perm /ugo+x -delete

#### end ####
