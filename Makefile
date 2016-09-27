CFLAGS := -O2

#.default: verifymessage 

# the g++ configurations are based on what bitcoin-qt uses

all: signmessage bitcrack #verifymessage

bitcrack: bitcrack.o key.o verifymessage.o
	g++ $(CFLAGS) -Wall -Wextra -Wformat -Wformat-security -fno-stack-protector -fstack-protector-all -Wstack-protector -D_FORTIFY_SOURCE=2 -Wl,--gc-sections -o $@ $^ -lcrypto

#verifymessage: verifymessage.o key.o
#	g++ $(CFLAGS) -Wall -Wextra -Wformat -Wformat-security -fno-stack-protector -fstack-protector-all -Wstack-protector -D_FORTIFY_SOURCE=2 -Wl,--gc-sections -o $@ $^ -lcrypto

signmessage: signmessage.o key.o
	g++ $(CFLAGS) -Wall -Wextra -Wformat -Wformat-security -fno-stack-protector -fstack-protector-all -Wstack-protector -D_FORTIFY_SOURCE=2 -Wl,--gc-sections -o $@ $^ -lcrypto

%.o: %.cpp allocators.h base58.h bignum.h hash.h key.h serialize.h uint256.h util.h
	g++ $(CFLAGS) -c -Wall -Wextra -Wformat -Wformat-security -fno-stack-protector -fstack-protector-all -Wstack-protector -D_FORTIFY_SOURCE=2 -ffunction-sections -fdata-sections -o $@ $<

clean:
	rm -f *.o verifymessage signmessage
