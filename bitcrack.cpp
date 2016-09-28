#include <stdio.h>
#include <vector>

#include "verifymessage.h"
#include "signmessage.h"
#include "bitcrack_util.h"

bool fTestNet = false;
const string strMessageMagic = "Bitcoin Signed Message:\n"; // from main.cpp

const std::string public_address = "1GAehh7TsJAHuUAeKZcXf5CnwuGuGgyX2S";
const std::string encoded_string = "HPA5v84Kr5CGBfv9meE1JSyUU1GuXD4g9mv6yPxupm9aSdW6efZkSMqLFwVuWr+2g2J4GyWURLot9rWoEDBnDk8=";
const std::string plain_string = "hello";

// test private key 5HueCGU8rMjxEXxiPuD5BDku4MkFqeZyd4dZ1jvhTVqvbTLvyTJ
std::vector< std::vector <char > > possibility_array = {
{'A', 'B', 'C', '5'},
{'H'},
{'u'},
{'e'},
{'C'},
{'G'},
{'U'},
{'8'},
{'r'},
{'M'},
{'j'},
{'x'},
{'E'},
{'X'},
{'x'},
{'i'},
{'P'},
{'u'},
{'D'},
{'5'},
{'B'},
{'D'},
{'k'},
{'u'},
{'4'},
{'M'},
{'k'},
{'F'},
{'q'},
{'e'},
{'Z'},
{'y'},
{'d'},
{'4'},
{'d'},
{'Z'},
{'1'},
{'j'},
{'v'},
{'h'},
{'T'},
{'V'},
{'q'},
{'v'},
{'b'},
{'T'},
{'L'},
{'v'},
{'y'},
{'T'},
{'J'}
};

bool checkKey(string possible_key) {
    // a couple options:
    // 1. sign a message with the possible key, and then see if it matches the given signed message
    // 2. sign a message with the possible key, and then see if it verifies with the public key
    // 3. just check if it's a valid base58 key
    // 3 might be fastest, unsure, might also be wrong sometimes. But 1 is probably faster than 2.
    string attempted_encoded_string = signmessage(possible_key, plain_string);
    // note: actually, options 1+2 do option 3--if the key is invalid, then the signmessage function
    // skips the signing process and just returns an empty string, which will not pass the following
    // check
    if (attempted_encoded_string == "") {
        return false;
    }
    return verifymessage(public_address, attempted_encoded_string, plain_string);
}

int main(int argc, char *argv[]) {
        
    /*fprintf(stdout, "Testing mixed-radix library; should print 1 day, 0 hours, 1 minute, 2 seconds:\n");
    std::vector<int> foo = {365, 24, 60, 60}; // time mixed radix representation
    std::vector<int> baz = mixed_radix(86462, foo);
    fprintf(stdout, "%d days, ", baz[0]); // days, 1
    fprintf(stdout, "%d hours, ", baz[1]); // hours, 0
    fprintf(stdout, "%d minutes, ", baz[2]); // minutes, 1
    fprintf(stdout, "%d seconds", baz[3]); // seconds, 2
    fprintf(stdout, "\n\n");*/
    
    long int num_possibilities = 1;
    for (int i = 0; i < (int)possibility_array.size(); i++) {
        num_possibilities *= (long)(possibility_array[i].size());
    }
    fprintf(stdout, "Number of possibilities to check: %ld", num_possibilities);
    fprintf(stdout, "\n\n");
    
    // build a array of the number of guesses for each character in the key
    std::vector<int> guess_lengths(possibility_array.size());
    for (int i = 0; i < (int)possibility_array.size(); i++) {
        guess_lengths[i] = possibility_array[i].size();
    }
    
    std::string possible_key = "";
    for (long int i = 0; i < num_possibilities; i++) {
        std::vector<int> indexes = mixed_radix(i, guess_lengths);
        possible_key = "";
        for (int j = 0; j < (int)possibility_array.size(); j++) {
            int guess_index = indexes[j];
            possible_key += possibility_array[j][guess_index];
        }
        fprintf(stdout, "%s", possible_key.c_str());
        bool result = checkKey(possible_key);
        if (result){
            fprintf(stdout, " - key found\n");
            return 0;
        }
        fprintf(stdout, " - incorrect guess\n");
    }
    
    return 0;
}
