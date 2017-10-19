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
#include "model/ppm_tree.h"

#define END_OF_FILE     256
#define APLHABET_SIZE   257

int main() {

    // Read original file
    InputStream original_file ("file/coin.jpg");

    // Create Encoder
    Encoder encoder ("target.zp");

    // Create model
    PPMTree model = PPMTree();

    // Create probability structure
    Probability prob;

    while (!original_file.eof()) {
        // Reads a byte from source
        unsigned char symbol = original_file.readSymbol();

        // Calculate probability
        prob = model.encodeSymbol (symbol);

        //Encode symbol
        encoder.encode (prob.low, prob.high, prob.total);
    }

    //Encode EOF
    encoder.finish();

    return 0;
}
