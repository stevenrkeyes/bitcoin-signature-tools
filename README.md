# bitcrack

This is a library to deterministically crack a bitcoin private key, given some guesses about the characters in the key. I made it by forking from the bitcoin-signature-tools project and adding code. 

## Dependencies and Building

The only library this depends on is OpenSSL.  On Ubuntu or similar systems, the following should be sufficient to install dependencies and build:

    sudo apt-get install build-essential libssl-dev
    make

## Usage

Modify the guesses for each character in bitcrack.cpp. Then,

    make
    ./bitcrack
