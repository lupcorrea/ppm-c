//
///* Include file module */
//#include "file/whatever.h"
//
///* Include model module */
//#include "model/whatever.h"
//
///* Include test module */
//#include "test/whatever.h"
//
///* Include compression and decompression module */
//#include "zip/whatever.h"

#include <vector>   //std::vector
#include <fstream>  //std::fstream
#include <iostream> //std::cerr, std::endl
#include "arithmetic/ArithmeticCoderC.h"

#define END_OF_FILE     256
#define APLHABET_SIZE   257

void encode(std::fstream& source, std::fstream& target) {

    //Creates coder and set output stream (target)
    ArithmeticCoderC coder;
    coder.SetFile(&target);

    //Occurrences (starts all with value 1, equal probability)
    std::vector<unsigned int> occurrences(APLHABET_SIZE, 1);
    unsigned int total = APLHABET_SIZE;

    while(!source.eof()) {

        //Reads a byte from source
        unsigned char symbol;
        source.read(reinterpret_cast<char*>(&symbol), sizeof(char));

        //Calculates low
        unsigned int low = 0;
        for(unsigned char i = 0;  i < symbol; i++) {
            low += occurrences[i];
        }

        //Encode symbol, high = low + occurrences[symbol];
        coder.Encode(low, low + occurrences[symbol], total);

        //Update occurrences and total
        occurrences[symbol]++;
        total++;

    }

    //Encode EOF
    coder.Encode(total-1, total, total);
    coder.EncodeFinish();

}

void decode(std::fstream& source, std::fstream& target) {

    //Creates decoder and set input stream
    ArithmeticCoderC coder;
    coder.SetFile(&source);
    coder.DecodeStart();

    //Occurrences (starts all with value 1, equal probability)
    std::vector<unsigned int> occurrences(APLHABET_SIZE, 1);
    unsigned int total = APLHABET_SIZE;

    //Reads the first point of the interval
    unsigned int value = coder.DecodeTarget(total);

    while(value != (total-1)) {

        unsigned int low = 0;
        unsigned char symbol = 0;

        //Calculates symbol and low
        for(symbol = 0; low + occurrences[symbol] <= value; symbol++) {
            low += occurrences[symbol];
        }

        //Writes byte in output stream
        target.write(reinterpret_cast<char*>(&symbol), sizeof(char));

        //Update decoder
        coder.Decode(low, low + occurrences[symbol]);

        //Update occurrences and total
        occurrences[symbol]++;
        total++;

        //Get new point of interval
        value = coder.DecodeTarget(total);

    };
}

int main() {

    //Read original file
    std::fstream source1("file/coin.jpg", std::ios::in | std::ios::binary);
    if(!source1.is_open()) {
        std::cerr << "Failed to read original file. " << std::endl;
        return 1;
    }

    //Create output stream to target.zp
    std::fstream target1("target.zp", std::ios::out | std::ios::binary);
    if(!target1.is_open()) {
        std::cerr << "Failed to create zp file. " << std::endl;
        return 1;
    }

    //Encode
    encode(source1, target1);

    //Close files
    source1.close();
    target1.close();

    //Read zp file
    std::fstream source2("target.zp", std::ios::in | std::ios::binary);
    if(!source2.is_open()) {
        std::cerr << "Failed to read zp file. " << std::endl;
        return 1;
    }

    //Create output stream to rebuild file
    std::fstream target2("rebuild.jpg", std::ios::out | std::ios::binary);
    if(!target2.is_open()) {
        std::cerr << "Failed to create rebuild file. " << std::endl;
        return 1;
    }

    //Decode
    decode(source2, target2);

    //Close files
    source2.close();
    target2.close();

    /* Read original file */

    /* Build the model */

    /* Build the header */

    /* Compress the model */

    /* Write compressed file */

    /* Decompress the file */

    /* Write decompressed file */

    /* Test compression */

    return 0;
}
