#ifndef __STREAM_H__
#define __STREAM_H__

#include <string>       //std::string
#include <fstream>      //std::fstream, std::ios_base
#include <iostream>     //std::cerr, std::endl
#include <cstdlib>      //std::exit()
#include <type_traits>  //std::enable_if<>

template <std::ios_base::openmode mode>
class Stream : public fstream {

public:

    /// \brief Default constructor.
    Stream(void) : fstream() {}

    /// \brief Constructor.
    /// \param filename The filename to open/create.
    Stream(const std::string& filename) : fstream() {
        Stream::open(filename);
    }

    /// \brief Destructor.
    ~Stream(void) {
        if(std::fstream::is_open()) std::fstream::close();
    }

    /// \brief Function to open/create a file.
    /// \param filename The filename to open/create.
    void open(const std::string& filename) {
        std::fstream::open(filename, mode);
        if(!is_open()) { // Checks if open
            std::cerr << "Could not create/open file: " << filename << std::endl;
            std::exit(1);
        }
    }

    /// \brief Read next symbol (if there are still symbols).
    /// Function available only if this is InputStream.
    /// \return Next symbol of file.
    template <std::ios_base::openmode A = mode>
    typename std::enable_if<(A & std::ios::in) == std::ios::in, unsigned char>::type
    readSymbol(void) {
        unsigned char symbol;
        std::fstream::read(reinterpret_cast<char*>(&symbol), sizeof(char));
        return symbol;
    }

    /// \brief Writes a symbol to the output file.
    /// Function available only if this is OutputStream.
    /// \param symbol The symbol to be written.
    template <std::ios_base::openmode A = mode>
    typename std::enable_if<(A & std::ios::out) == std::ios::out>::type
    writeSymbol(unsigned char symbol) {
        std::fstream::write(reinterpret_cast<char*>(&symbol), sizeof(char));
    }

    /// \brief Close the file
    void close(void) {
        std::fstream::close();
    }

};

//Define new types
typedef Stream<std::ios::in  | std::ios::binary> InputStream;
typedef Stream<std::ios::out | std::ios::binary> OutputStream;

#endif // __STREAM_H__
