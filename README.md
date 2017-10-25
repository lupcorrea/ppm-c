# PPM-C

[![standard-readme compliant](https://img.shields.io/badge/readme%20style-standard-brightgreen.svg?style=flat-square)](https://github.com/RichardLitt/standard-readme)

> This repository was created by Daniel Poltronieri, Lucas Correa and Christopher Régis.

This is a compressor utilizing PPM (Prediction by Partial Matching) to generate a input to an Arithmetic compressor **Colocar aqui de onde a gente tirou ele** implemented in the C++ programming language.

## Table of Contents

- [Background](#background)
- [Compilation](#Compilation)
- [Usage](#usage)
- [API](#api)
- [Contribute](#contribute)
- [License](#license)

## Background

### Course

This code implementation was developed as the first assignment in the Introduction to information Theory ministered by Derzu Omaia in the Federal University of Parahyba in the second semester of 2017.

### PPM
Prediction by partial matching (PPM) is an adaptive statistical data compression technique based on context modeling and prediction. PPM models use a set of previous symbols in the uncompressed symbol stream to predict the next symbol in the stream. PPM algorithms can also be used to cluster data into predicted groupings in cluster analysis.
[Source](https://en.wikipedia.org/wiki/Prediction_by_partial_matching)

### Arithmetic

Arithmetic coding is a form of entropy encoding used in lossless data compression. Normally, a string of characters such as the words "hello there" is represented using a fixed number of bits per character, as in the ASCII code. When a string is converted to arithmetic encoding, frequently used characters will be stored with fewer bits and not-so-frequently occurring characters will be stored with more bits, resulting in fewer bits used in total. Arithmetic coding differs from other forms of entropy encoding, such as Huffman coding, in that rather than separating the input into component symbols and replacing each with a code, arithmetic coding encodes the entire message into a single number, an arbitrary-precision fraction q where 0.0 ≤ q < 1.0. It represents the current information as a range, defined by two numbers. Recent Asymmetric Numeral Systems family of entropy coders allows for faster implementations thanks to directly operating on a single natural number representing the current information.
[Source](https://en.wikipedia.org/wiki/Arithmetic_coding)

## Compilation

This module depends upon a knowledge of [Markdown]().

```
```

### Any optional sections

## Usage

```
```

### Any optional sections

## Contribute

See [the contribute file](contribute.md)!

PRs accepted.

Small note: If editing the Readme, please conform to the [standard-readme](https://github.com/RichardLitt/standard-readme) specification.

### Any optional sections

## License

[MIT © Richard McRichface.](../LICENSE)
