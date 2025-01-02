/**
*
* Date: 1-1-2025
* Author: Jeremiah J.
* File: Deserializer.hpp
* Description: Handles definitions for structs and methods for the deserializer and some header files.
*
*/
#ifndef DESERIALIZER_HPP
#define DESERIALIZER_HPP

#include "Reader.hpp"
#include "Enums.hpp"
#include <variant>
#include <cstring>
#include <iostream>

class Deserializer {
public:
    int intSize;
    std::vector<uint8_t> bytecode;

    struct Header {
        uint8_t Esc;
        std::string Signature;
        uint8_t Version;
        uint8_t Format;
        uint8_t Endianness;
        uint8_t IntSize;
        uint8_t Size_tSize;
        uint8_t InstructionSize;
        uint8_t LuaNumberSize;
        uint8_t IntegralFlag;
    };

    struct Constant {
        enum class Type {
            Nil,
            Boolean,
            Number,
            String
        };

        Type type;
        std::variant<std::monostate, bool, int, double, std::string> value;
    };

	struct Instruction {
		uint32_t Opcode;
		uint32_t RegA;
		uint32_t RegB;
		uint32_t RegC;
		std::string Mnemonic;
		std::string Description;
	};

    struct Prototype {
        std::string Source;
        uint32_t LineDefined;
        uint32_t LastLineDefined;
        uint8_t NumUpvalues;
        uint8_t NumParameters;
        uint8_t IsVararg;
        uint8_t MaxStackSize;

        std::vector<Instruction> Instructions;
        std::vector<Constant> Constants;
        std::vector<Prototype> Prototypes;

        struct Debug {
            std::vector<uint32_t> SourcePositions;
            struct Local {
                std::string Name;
                uint32_t Start;
                uint32_t End;
            };
            std::vector<Local> Locals;

            struct Upvalue {
                std::string Name;
            };
            std::vector<Upvalue> Upvalues;
        } Debug;

    };

	Deserializer(const std::vector<uint8_t>& bytecode);
	Header ReadHeader(Reader& reader);
	Prototype ReadPrototype(Reader& reader);
    std::pair<Header, Prototype> Parse();
};

#endif // !DESERIALIZER_HPP
