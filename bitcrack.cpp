#include <stdio.h>
#include <vector>

#include "verifymessage.h"
#include "bitcrack_util.h"

const std::string public_address = "1GAehh7TsJAHuUAeKZcXf5CnwuGuGgyX2S";
const std::string encoded_string = "HPA5v84Kr5CGBfv9meE1JSyUU1GuXD4g9mv6yPxupm9aSdW6efZkSMqLFwVuWr+2g2J4GyWURLot9rWoEDBnDk8=";
const std::string plain_string = "hello";

// test private key 5HueCGU8rMjxEXxiPuD5BDku4MkFqeZyd4dZ1jvhTVqvbTLvyTJ
std::vector< std::vector <char > > possibility_array = {
{'5', 'A', 'B', 'C'},
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

int main(int argc, char *argv[]) {
        
    fprintf(stdout, "Testing mixed-radix library; should print 1 day, 0 hours, 1 minute, 2 seconds:\n");
    std::vector<int> foo = {365, 24, 60, 60}; // time mixed radix representation
    std::vector<int> baz = mixed_radix(86462, foo);
    fprintf(stdout, "%d days, ", baz[0]); // days, 1
    fprintf(stdout, "%d hours, ", baz[1]); // hours, 0
    fprintf(stdout, "%d minutes, ", baz[2]); // minutes, 1
    fprintf(stdout, "%d seconds", baz[3]); // seconds, 2
    fprintf(stdout, "\n\n");
    
    long int num_possibilities = 1;
    for (int i = 0; i < (int)possibility_array.size(); i++) {
        num_possibilities *= (long)(possibility_array[i].size());
    }
    fprintf(stdout, "Number of possibilities to check: %ld", num_possibilities);
    
    return verifymessage(public_address, encoded_string, plain_string);
}
