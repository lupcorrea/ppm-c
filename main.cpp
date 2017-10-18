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

#include "Stream.h"
#include "Encoder.h"
#include "Decoder.h"

#define END_OF_FILE     256
#define APLHABET_SIZE   257

void encode(InputStream& source, Encoder& coder) {

    //Occurrences (starts all with value 1, equal probability)
    std::vector<unsigned int> occurrences(APLHABET_SIZE, 1);
    unsigned int total = APLHABET_SIZE;

    while(!source.eof()) {

        //Reads a byte from source
        unsigned char symbol = source.readSymbol();
//        source.read(reinterpret_cast<char*>(&symbol), sizeof(char));

        //Calculates low
        unsigned int low = 0;
        for(unsigned char i = 0;  i < symbol; i++) {
            low += occurrences[i];
        }

        //Encode symbol, high = low + occurrences[symbol];
        coder.encode(low, low + occurrences[symbol], total);

        //Update occurrences and total
        occurrences[symbol]++;
        total++;

    }

    //Encode EOF
    coder.encode(total-1, total, total);
    coder.finish();

}

void decode(OutputStream& target, Decoder& coder) {

    //Occurrences (starts all with value 1, equal probability)
    std::vector<unsigned int> occurrences(APLHABET_SIZE, 1);
    unsigned int total = APLHABET_SIZE;

    unsigned int symbol = 0;

    do {

        //Get new value to decode
        unsigned int value = coder.decodeTarget(total);

        //Calculates symbol and low
        unsigned int low = 0;
        for(symbol = 0; low + occurrences[symbol] <= value; symbol++) {
            low += occurrences[symbol];
        }

        //Writes symbol in output stream (if not EOF)
        if(symbol < END_OF_FILE) target.writeSymbol(symbol);

        //Removes the effect of the decoded symbol.
        coder.decode(low, low + occurrences[symbol]);

        //Update occurrences and total (update model)
        occurrences[symbol]++;
        total++;

    } while(symbol != END_OF_FILE);
}


int main() {

    //Read original file
    InputStream original_file("file/coin.jpg");

    //Create Encoder.
    Encoder encoder("target.zp");

    //Encode
    encode(original_file, encoder);

    //Create output file
    OutputStream rebuild_file("rebuild.jpg");

    //Create decoder
    Decoder decoder("target.zp");

    //Decode
    decode(rebuild_file, decoder);

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
