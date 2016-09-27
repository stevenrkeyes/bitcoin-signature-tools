#include <stdio.h>

#include "verifymessage.h"

int main(int argc, char *argv[]) {
    
    if (argc != 4) {
        fprintf(stderr,
            "verifysig <bitcoinaddress> <signature> <message>\n\n"
            "Verify a signed message\n");
        return 255;
    }
    return verifymessage(argv[1], argv[2], argv[3]);
}
