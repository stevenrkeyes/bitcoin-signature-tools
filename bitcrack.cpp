#include <stdio.h>
#include <vector>

#include "verifymessage.h"
#include "signmessage.h"
#include "bitcrack_util.h"

// note: takes about 4.3 microseconds per guess on my machine

bool fTestNet = false;
const string strMessageMagic = "Bitcoin Signed Message:\n"; // from main.cpp

const std::string public_address = "1qkCBiEjY4GAUFBcrsDXqyM6EPbZKTqCW";
const std::string encoded_string = "HKfTaGxIyLKyKeibtg6dKHLaZtvSFuQa+wC66fV9wUbEzqmY6VmKGt77aslK1y5y9Br8VW2fo3i2PVQwkBXjRcQ=";
const std::string plain_string = "mrdeath5493";

// test private key 5HueCGU8rMjxEXxiPuD5BDku4MkFqeZyd4dZ1jvhTVqvbTLvyTJ
std::vector< std::vector <char > > possibility_array = {
{'5'}, //
{'J'}, //Steve Jobs
{'K'}, //Stephanie Kwolek
{'A'}, //Archimedes
{'B'}, //Nolan Bushnell
{'V', 'L'}, //Leonardo da Vinci? Louis-Sebastien Lenormand?
{'F'}, //?????????????????????????????????????????????????????????????????????
{'W','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'}, //??????????????????????????
{'G'}, //Gutenberg
{'F'}, //Pedro Flores?
{'e', 'E'}, //fill in the blank "e" in e=mc^2, or 'E', (or as in Einstein)
{'S'}, //Henry W Seeley
{'S'}, //John Spilsbury
{'3'}, //
{'V', 'E', 'R', }, //Leonardo da Vinci? Egyptians? Romans????????????????????
{'R'}, //Wilhelm Rontgen?
{'Y'}, //person: Linus Yale, Jr
{'H'}, //Christian Hulsmeyer
{'S', 'W', 'U'}, //George Stephenson????????? what is this object???????????????????????
{'E'}, //Gustave Eiffel
{'N'}, //person: Alfred Nobel
{'H', 'F'}, //Jackson Haines? Finns?
{'X'}, //fill in the blank: x chromosome
{'Y'}, //fill in the blank: y chromosome
{'I', 'E'}, //Inuit? Eskimo? ???????????????????????????????????????????????????
{'M', 'P', 'H'}, //Eadweard Muybridge
{'G'}, //person: Galileo Galilei
{'C', 'W'}, //Chester Carlson? Joseph Wilson?
{'A', 'Y'}, //Alcuin of York
{'K'},
{'L'}, //Hon Lik
{'H'},
{'E', 'B'}, //Thomas Edison? Alexander Graham Bell?
{'J'}, //Whitcomb L Judson
{'X'}, //fill in the blank: alphabet
{'H', 'E', 'B', 'T', 'P'}, //Hitchings or Elion
{'9'}, // euro introduction year
{'B'}, //Louis Braille
{'S', 'O'}, //John O'Sullivan?
{'G', 'A'}, //Bill Gates? Paul Allen?
{'K', '2'}, //
{'N'}, //
{'F'}, //Michael Faraday
{'E'}, //Albert Einstein
{'X'}, //
{'C'}, //André Cassagnes
{'Y', 'N'}, //Gunpei Yokoi or Nintendo
{'X', '3'}, //
{'E', '6'}, //Oleg?????????????????????????????????????????????????????????
{'E'}, //Martin Eberhard
{'E'} //Douglas Engelbart};
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
    fprintf(stdout, "Number of possibilities to check: %ld\n", num_possibilities);
    fprintf(stdout, "Estimated time: %d minutes\n", (int)(0.0000043 * num_possibilities / 60.0));
    fprintf(stdout, "\n");
    
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
        //fprintf(stdout, "%s", possible_key.c_str());
        bool result = checkKey(possible_key);
        if (result){
            fprintf(stdout, " - key found\n");
            return 0;
        }
        //fprintf(stdout, " - incorrect guess\n");
    }
    
    return 0;
}
