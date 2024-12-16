#pragma once

#ifndef LZW_COMPRESSION_H
#define LZW_COMPRESSION_H

#include <string>

// Compress a file using LZW encoding
void compress(const std::string& inputFileName, const std::string& outputFileName);

// Decompress a file using LZW encoding
void decompress(const std::string& inputFileName, const std::string& outputFileName);

#endif // LZW_COMPRESSION_H
