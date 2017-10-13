#ifndef __ENCODER_H__
#define __ENCODER_H__

#include "Stream.h"
#include "arithmetic/ArithmeticCoderC.h"

class Encoder {

public:

    /// \brief Constructor.
    /// \param output_filename Name of the file where the bits will be written.
    Encoder(const std::string& output_filename) : coder(), stream(output_filename) {
        coder.SetFile(&stream);
    }

    /// \brief Symbol encoding function.
    /// \param low Beginning of the symbol range.
    /// \param high End of symbol range.
    /// \param total Max value of range.
    void encode(unsigned int low, unsigned int high, unsigned int total) {
        coder.Encode(low, high, total);
    }

    /// \brief Encode finish.
    void finish(void) {
        coder.EncodeFinish();
        stream.close();
    }

private:
    ArithmeticCoderC coder;
    OutputStream stream;

};

#endif // __ENCODER_H__
