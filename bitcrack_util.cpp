using namespace std;
#include <vector>
#include "bitcrack_util.h"
#include <stdio.h>

vector<int> mixed_radix(int number, vector<int> bases){
    // make a vector output the same size as the vector bases
    // (is there a better way to do this?)
    vector<int> output = bases;
    
    int n = number;
    int num_bases = bases.size();
    int j = num_bases;
    int i;
    int base;
    for (i = 0; i < num_bases; i++) {
        j--;
	base = bases[j];
        output[j] = n % base;
        n = int(n / base);
    }
    return output;
}

/*
def mixed_radix(number, bases):
    output = []
    
    for base in reversed(bases):
        output_reversed = list(reversed(output))
        output_reversed.append(number % base)
        output = list(reversed(output_reversed))
        number = int(number / base)          #div is integer division (round down)

    return output
*/
