/**
*
* Date: 1-1-2025
* Author: Jeremiah J.
* File: PrettyPrint.hpp
* Description: Handles headers and methods for pretty printing.
*
*/
#ifndef PRETTY_PRINT_HEADER
#define PRETTY_PRINT_HEADER

#include "Deserializer.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>

void PrintHeader(const Deserializer::Header& header);
void PrintPrototype(const Deserializer::Prototype& proto, int level = 0, const std::string& funcName = "main");
void PrintAll(const Deserializer::Header& header, const Deserializer::Prototype& proto);

#endif // !PRETTY_PRINT_HEADER
