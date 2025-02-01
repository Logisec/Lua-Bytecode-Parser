/**
*
* Date: 1-1-2025
* Author: Jeremiah J.
* File: PrettyPrint.cpp
* Description: Handles printing everything beautifully.
*
*/
#include "PrettyPrint.hpp"

void PrintHeader(const Deserializer::Header& header) {
    std::cout << "-- Header Info --" << std::endl;
    std::cout << "Signature: '" << header.Signature << "'" << std::endl;
    std::cout << "Version: " << (int)header.Version << std::endl;
    std::cout << "Format: " << (int)header.Format << std::endl;
    std::cout << "Endianness: " << (header.Endianness == 0 ? "Big Endian" : "Little Endian") << std::endl;
    std::cout << "Int Size: " << (int)header.IntSize << std::endl;
    std::cout << "Size_t Size: " << (int)header.Size_tSize << std::endl;
    std::cout << "Instruction Size: " << (int)header.InstructionSize << std::endl;
    std::cout << "Lua Number Size: " << (int)header.LuaNumberSize << std::endl;
    std::cout << "Integral Flag: " << (int)header.IntegralFlag << std::endl;
}

void PrintPrototype(const Deserializer::Prototype& proto, int level, const std::string& funcName) {
    std::string indent(level * 4, ' ');
    std::cout << indent << "function " << funcName << "(...)" << std::endl;

    std::cout << indent << "    -- Prototype Info --" << std::endl;
    std::cout << indent << "    Source = '" << (proto.Source.empty() ? "(none)" : proto.Source) << "'" << std::endl;
    std::cout << indent << "    LineDefined = " << proto.LineDefined << std::endl;
    std::cout << indent << "    LastLineDefined = " << proto.LastLineDefined << std::endl;
    std::cout << indent << "    NumUpvalues = " << (int)proto.NumUpvalues << std::endl;
    std::cout << indent << "    NumParameters = " << (int)proto.NumParameters << std::endl;
    std::cout << indent << "    IsVararg = " << (proto.IsVararg ? "true" : "false") << std::endl;
    std::cout << indent << "    MaxStackSize = " << (int)proto.MaxStackSize << std::endl;

    std::cout << indent << "    -- Constants --" << std::endl;
    for (const auto& constant : proto.Constants) {
        std::string type;
        std::string value;

        if (constant.type == Deserializer::Constant::Type::Nil) {
            type = "Nil";
            value = "nil";
        }
        else if (constant.type == Deserializer::Constant::Type::Boolean) {
            type = "Boolean";
            value = std::get<bool>(constant.value) ? "true" : "false";
        }
        else if (constant.type == Deserializer::Constant::Type::Number) {
            type = "Number";
            if (constant.value.index() == 2) {
                value = std::to_string(std::get<int>(constant.value));
            }
            else if (constant.value.index() == 3) { 
                value = std::to_string(std::get<double>(constant.value));
            }
        }
        else if (constant.type == Deserializer::Constant::Type::String) {
            type = "String";
            value = '"' + std::get<std::string>(constant.value) + '"';
        }

        std::cout << indent << "    [Constant] Type = " << type << ", Value = " << value << std::endl;
    }

    std::cout << indent << "    -- Instructions --" << std::endl;
    for (const auto& instr : proto.Instructions) {
        std::cout << indent << "    Opcode: " << instr.Opcode
            << ", A: " << instr.RegA
            << ", B: " << std::visit([](auto&& arg) { return std::to_string(arg); }, instr.RegB)
            << ", C: " << std::visit([](auto&& arg) { return std::to_string(arg); }, instr.RegC)
            << ", Mnemonic: " << instr.Mnemonic << std::endl;
    }

    if (!proto.Prototypes.empty()) {
        std::cout << indent << "    -- Nested Prototypes --" << std::endl;
        for (size_t i = 0; i < proto.Prototypes.size(); ++i) {
            std::stringstream nestedFuncName;
            nestedFuncName << "proto_" << &proto.Prototypes[i];
            PrintPrototype(proto.Prototypes[i], level + 1, nestedFuncName.str());
        }
    }

    std::cout << indent << "end" << std::endl;
}

void PrintAll(const Deserializer::Header& header, const Deserializer::Prototype& proto) {
    PrintHeader(header);
    PrintPrototype(proto, 0, "main");
}
