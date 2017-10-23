#ifndef PPM_DEFINITIONS_H_
#define PPM_DEFINITIONS_H_

#include <iostream>

/// \brief Constants definition file.

/// Determines the amount of symbols the system will encode.
/// If this variable is set to X, then the system will encode the first X symbols
/// obtained from the input file.
const std::size_t kAlphabetSize = 256;

/// Determines the maximum amount of context levels used for encoding.
/// For better performance, set this variable to lower values.
/// For better compression, set this variable to higher values.
const int kMaxOrder = 3;

/// Determines the "symbol" created to represent the escape.
/// It is always set to one symbol further than the alphabet size,
/// so it doesn't get mistaken for a regular symbol.
const std::size_t kEscape = kAlphabetSize + 1;

/// This variable is not being used yet.
const std::size_t kMessageSize = 12;

#endif
