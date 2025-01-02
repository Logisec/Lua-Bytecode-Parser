/**
*
* Date: 1-1-2025
* Author: Jeremiah J.
* File: Deserializer.cpp
* Description: Welp this is where all the magic happens ladies. We read the header do some checks and then read the proto(s).
*			   So much fun! :D
*
*/
#include "Deserializer.hpp"

Deserializer::Deserializer(const std::vector<uint8_t>& bytecode): bytecode(bytecode), intSize(4) {}

Deserializer::Header Deserializer::ReadHeader(Reader& reader) {
	Header header;

	header.Esc = reader.ReadByte();
	header.Signature = std::string(reinterpret_cast<const char*>(reader.ReadBytes(3).data()), 3);

	if (header.Signature != "Lua") throw std::runtime_error("Invalid signature");

	header.Version = reader.ReadByte();
	header.Format = reader.ReadByte();

	if (header.Version != 0x51 || header.Format != 0) throw std::runtime_error("Invalid version or format");

	header.Endianness = reader.ReadByte();
	header.IntSize = reader.ReadByte();
	header.Size_tSize = reader.ReadByte();
	header.InstructionSize = reader.ReadByte();
	header.LuaNumberSize = reader.ReadByte();
	header.IntegralFlag = reader.ReadByte();

	return header;
}

Deserializer::Prototype Deserializer::ReadPrototype(Reader& reader) {
	Prototype proto;
	
	proto.Source = reader.ReadString();
	proto.LineDefined = reader.ReadInt32();
	proto.LastLineDefined = reader.ReadInt32();
	proto.NumUpvalues = reader.ReadByte();
	proto.NumParameters = reader.ReadByte();
	proto.IsVararg = reader.ReadByte();
	proto.MaxStackSize = reader.ReadByte();

	uint32_t instructionCount = reader.ReadInt32();
	for (uint32_t i = 0; i < instructionCount; i++) {
		uint32_t instruction = reader.ReadInt32();
		uint32_t opcode = instruction % 0x40;
		uint32_t reg_a = (instruction >> 6) % 0xFF;

		std::string mnemonic = InstructionSet[opcode].Mnemonic;
		std::string type = InstructionSet[opcode].Type;
		std::string description = InstructionSet[opcode].Description;

		if (type == "iABC") {
			uint32_t reg_b = (instruction >> 23) % 0x1FF;
			uint32_t reg_c = (instruction >> 14) % 0x1FF;
			proto.Instructions.push_back({ opcode, reg_a, reg_b, reg_c, mnemonic, description });
		} 
		else if (type == "iABx") {
			uint32_t reg_bx = (instruction >> 14) % 0x3FFFF;
			proto.Instructions.push_back({ opcode, reg_a, reg_bx, 0, mnemonic, description });
		} 
		else if (type == "iAsBx") {
			uint32_t sbx = ((instruction >> 14) & 0x3FFFF) - 131071;
			proto.Instructions.push_back({ opcode, reg_a, sbx, 0, mnemonic, description });
		}
	}

	uint32_t constantCount = reader.ReadInt32();
	for (uint32_t i = 0; i < constantCount; i++) {
		uint8_t type = reader.ReadByte();
		Constant constant;

		switch (type) {
		case 0:
			constant.type = Constant::Type::Nil;
			constant.value = std::monostate{};
			break;
		case 1:
			constant.type = Constant::Type::Boolean;
			constant.value = static_cast<bool>(reader.ReadByte());
			break;
		case 3: {
			double number = reader.ReadDouble();
			if (std::floor(number) == number) {
				constant.type = Constant::Type::Number;
				constant.value = static_cast<int>(number);
			}
			else {
				constant.type = Constant::Type::Number;
				constant.value = number;
			}
			break;
		}
		case 4:
			constant.type = Constant::Type::String;
			constant.value = reader.ReadString();
			break;
		default:
			throw std::runtime_error("Unknown constant type");
		}
		proto.Constants.push_back(constant);
	}

	uint32_t prototypeCount = reader.ReadInt32();
	for (uint32_t i = 0; i < prototypeCount; i++) {
		proto.Prototypes.push_back(ReadPrototype(reader));
	}

	uint32_t sourcePositionCount = reader.ReadInt32();
	for (uint32_t i = 0; i < sourcePositionCount; i++) {
		proto.Debug.SourcePositions.push_back(reader.ReadInt32());
	}

	uint32_t localCount = reader.ReadInt32();
	for (uint32_t i = 0; i < localCount; i++) {
		Prototype::Debug::Local local;
		local.Name = reader.ReadString();
		local.Start = reader.ReadInt32();
		local.End = reader.ReadInt32();
		proto.Debug.Locals.push_back(local);
	}

	uint32_t upvalueCount = reader.ReadInt32();
	for (uint32_t i = 0; i < upvalueCount; i++) {
		Prototype::Debug::Upvalue upvalue;
		upvalue.Name = reader.ReadString();
		proto.Debug.Upvalues.push_back(upvalue);
	}

	return proto;
}

std::pair<Deserializer::Header, Deserializer::Prototype> Deserializer::Parse() {
	Reader reader(bytecode);
	Header header = ReadHeader(reader);
	Prototype proto = ReadPrototype(reader);

	return std::make_pair(header, proto);
}