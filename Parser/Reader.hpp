/**
*
* Date: 1-1-2025
* Author: Jeremiah J.
* File: Reader.hpp
* Description: Handles definitions and header files for the reader class.
*
*/
#pragma once

#include <vector>
#include <string>
#include <cstdint>
#include <stdexcept>
#include <cmath>
#include <iomanip>
#include <sstream>

class Reader {
private:
	std::vector<uint8_t> bytecode;
	size_t index;

public:
	Reader(const std::vector<uint8_t>& bytecode, size_t index = 0);

	uint8_t ReadByte();
	std::vector<uint8_t> ReadBytes(size_t count);
	int32_t ReadInt32();
	double ReadDouble();
	std::string ReadString();
	void SkipBytes(size_t count);
	size_t GetIndex() const;
	std::string ByteToHex(uint8_t byte);
	std::string BytesToHex(const std::vector<uint8_t>& bytes);
};