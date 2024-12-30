#pragma once

#ifndef LZW_COMPRESSION_H
#define LZW_COMPRESSION_H

#include <string>

// Compress a file using LZW encoding
void compressing(const std::string& inputFileName, const std::string& outputFileName);

// Decompress a file using LZW encoding
void decompressing(const std::string& inputFileName, const std::string& outputFileName);

#endif // LZW_COMPRESSION_H
