CFLAGS := -O2 -std=c++11

all: signmessage bitcrack

bitcrack: bitcrack.o key.o verifymessage.o bitcrack_util.o
	g++ $(CFLAGS) -Wall -Wextra -Wformat -Wformat-security -fno-stack-protector -fstack-protector-all -Wstack-protector -Wno-unused-parameter -D_FORTIFY_SOURCE=2 -Wl,--gc-sections -o $@ $^ -lcrypto

%.o: %.cpp allocators.h base58.h bignum.h hash.h key.h serialize.h uint256.h util.h
	g++ $(CFLAGS) -c -Wall -Wextra -Wformat -Wformat-security -fno-stack-protector -fstack-protector-all -Wstack-protector -D_FORTIFY_SOURCE=2 -ffunction-sections -fdata-sections -o $@ $<

clean:
	rm -f *.o verifymessage signmessage bitcrack bitcrack_util
