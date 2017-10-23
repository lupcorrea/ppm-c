#include <vector>
#include <fstream>
#include <iostream>
#include "arithmetic/ArithmeticCoderC.h"

#include "Stream.h"
#include "Encoder.h"
#include "Decoder.h"
#include "model/ppm_tree.h"

#define END_OF_FILE     256
#define APLHABET_SIZE   257

int main() {

    // Read original file
    InputStream original_file ("file/abracadabra.txt");

    // Create Encoder
    Encoder encoder ("target.zp");

    // Create model
    PPMTree model = PPMTree();

    while (!original_file.eof()) {
        // Reads a byte from source
        unsigned char symbol = original_file.readSymbol();

        // Calculate probability and encode symbol
        model.encodeSymbol (encoder, symbol);
    }

    //Encode EOF
    encoder.finish();

    return 0;
}
