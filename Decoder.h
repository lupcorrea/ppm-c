#ifndef __DECODER_H__
#define __DECODER_H__

#include "Stream.h"
#include "arithmetic/ArithmeticCoderC.h"

class Decoder {

public:

    /// \brief Constructor.
    /// \param output_filename Name of the file where the bits will be written.
    Decoder(const std::string& input_filename) : coder(), stream(input_filename) {
        coder.SetFile(&stream);
        coder.DecodeStart();
    }

    /// \brief Function to get a value to decode.
    /// \param total Max value of range.
    /// \return A value to decode.
    unsigned int decodeTarget(unsigned int total) {
        return coder.DecodeTarget(total);
    }

    /// \brief Removes the effect of the decoded symbol.
    /// \param low Beginning of the decoded symbol range.
    /// \param high End of decoded symbol range.
    void decode(unsigned int low, unsigned int high) {
        coder.Decode(low, high);
    }

private:
    ArithmeticCoderC coder;
    InputStream stream;

};

#endif // __DECODER_H__
