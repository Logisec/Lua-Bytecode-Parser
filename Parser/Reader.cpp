/**
*
* Date: 1-1-2025
* Author: Jeremiah J.
* File: Reader.cpp
* Description: This is the source file for the Reader class.
*
*/
#include "Reader.hpp"

Reader::Reader(const std::vector<uint8_t>& bytecode, size_t index): bytecode(bytecode), index(index) {}

uint8_t Reader::ReadByte() {
	if (index >= bytecode.size()) throw std::out_of_range("Read past end of bytecode");
	return bytecode[index++];
}

std::vector<uint8_t> Reader::ReadBytes(size_t count) {
	if (index + count > bytecode.size()) throw std::out_of_range("Read past end of bytecode");
	std::vector<uint8_t> bytes(bytecode.begin() + index, bytecode.begin() + index + count);
	index += count;
	return bytes;
}

int32_t Reader::ReadInt32() {
	auto bytes = ReadBytes(4);
	return bytes[0] | (bytes[1] << 8) | (bytes[2] << 16) | (bytes[3] << 24);
}

int64_t Reader::ReadInt64() {
	auto bytes = ReadBytes(8);
	return static_cast<int64_t>(bytes[0]) |
		(static_cast<int64_t>(bytes[1]) << 8) |
		(static_cast<int64_t>(bytes[2]) << 16) |
		(static_cast<int64_t>(bytes[3]) << 24) |
		(static_cast<int64_t>(bytes[4]) << 32) |
		(static_cast<int64_t>(bytes[5]) << 40) |
		(static_cast<int64_t>(bytes[6]) << 48) |
		(static_cast<int64_t>(bytes[7]) << 56);
}

double Reader::ReadDouble() {
	auto bytes = ReadBytes(8);
	double value;
	std::memcpy(&value, bytes.data(), sizeof(double));
	return value;
}

std::string Reader::ReadString(size_t sizeParams) {
	auto length = ReadInt();
	if (length <= 0) return "";
	auto bytes = ReadBytes(static_cast<size_t>(length));
	if (bytes.back() == 0) bytes.pop_back();
	return std::string(bytes.begin(), bytes.end());
}

void Reader::SkipBytes(size_t count) {
	if (index + count > bytecode.size()) throw std::out_of_range("Skipped past end of bytecode");
	index += count;
}

size_t Reader::GetIndex() const {
	return index;
}

std::string Reader::ByteToHex(uint8_t byte) {
	std::stringstream stream;
	stream << std::hex << std::uppercase << std::setw(2) << std::setfill('0') << static_cast<int>(byte);
	return stream.str();
}

std::string Reader::BytesToHex(const std::vector<uint8_t>& bytes) {
	std::stringstream stream;
	for (const auto& byte : bytes) {
		stream << ByteToHex(byte) << " ";
	}
	return stream.str();
}