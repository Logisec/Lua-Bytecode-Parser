/**
*
* Date: 1-1-2025
* Author: Jeremiah J.
* File: Enums.hpp
* Description: Handles each instruction's information along with a lua description from lopcodes.h.
*              Might make the descriptions more descriptive in the future. :wink:
*
*/
#pragma once

struct InstructionInfo {
    const char* Mnemonic;
    const char* Type;
    const char* Description;
};

constexpr InstructionInfo InstructionSet[] = {
    {"MOVE", "iABC", "R(A) := R(B)"},
    {"LOADK", "iABx", "R(A) := Kst(Bx)"},
    {"LOADBOOL", "iABC", "R(A) := (Bool)B; if (C) pc++"},
    {"LOADNIL", "iABC", "R(A), R(A+1), ..., R(A+B-1) := nil"},
    {"GETUPVAL", "iABC", "R(A) := UpValue[B]"},
    {"GETGLOBAL", "iABx", "R(A) := Gbl[Kst(Bx)]"},
    {"GETTABLE", "iABC", "R(A) := R(B)[RK(C)]"},
    {"SETGLOBAL", "iABx", "Gbl[Kst(Bx)] := R(A)"},
    {"SETUPVAL", "iABC", "UpValue[B] := R(A)"},
    {"SETTABLE", "iABC", "R(A)[RK(B)] := RK(C)"},
    {"NEWTABLE", "iABC", "R(A) := {}; size = B, C"},
    {"SELF", "iABC", "R(A+1) := R(B); R(A) := R(B)[RK(C)]"},
    {"ADD", "iABC", "R(A) := RK(B) + RK(C)"},
    {"SUB", "iABC", "R(A) := RK(B) - RK(C)"},
    {"MUL", "iABC", "R(A) := RK(B) * RK(C)"},
    {"DIV", "iABC", "R(A) := RK(B) / RK(C)"},
    {"MOD", "iABC", "R(A) := RK(B) % RK(C)"},
    {"POW", "iABC", "R(A) := RK(B) ^ RK(C)"},
    {"UNM", "iABC", "R(A) := -R(B)"},
    {"NOT", "iABC", "R(A) := not R(B)"},
    {"LEN", "iABC", "R(A) := length of R(B)"},
    {"CONCAT", "iABC", "R(A) := R(B) .. ... .. R(C)"},
    {"JMP", "iAsBx", "pc += sBx"},
    {"EQ", "iABC", "if ((RK(B) == RK(C)) ~= A) then pc++"},
    {"LT", "iABC", "if ((RK(B) < RK(C)) ~= A) then pc++"},
    {"LE", "iABC", "if ((RK(B) <= RK(C)) ~= A) then pc++"},
    {"TEST", "iABC", "if not (R(A) <=> C) then pc++"},
    {"TESTSET", "iABC", "if (R(B) <=> C) then R(A) := R(B) else pc++"},
    {"CALL", "iABC", "R(A), ..., R(A+C-2) := R(A)(R(A+1), ..., R(A+B-1))"},
    {"TAILCALL", "iABC", "return R(A)(R(A+1), ..., R(A+B-1))"},
    {"RETURN", "iABC", "return R(A), ..., R(A+B-2)"},
    {"FORLOOP", "iAsBx", "R(A) += R(A+2); if R(A) <= R(A+1) then { pc += sBx; R(A+3) = R(A) }"},
    {"FORPREP", "iAsBx", "R(A) -= R(A+2); pc += sBx"},
    {"TFORLOOP", "iABC", "R(A+3), ..., R(A+2+C) := R(A)(R(A+1), R(A+2)); if R(A+3) ~= nil then R(A+2) = R(A+3) else pc++"},
    {"SETLIST", "iABC", "R(A)[(C-1)*FPF+i] := R(A+i), 1 <= i <= B"},
    {"CLOSE", "iABC", "close all variables in the stack up to (>=) R(A)"},
    {"CLOSURE", "iABx", "R(A) := closure(KPROTO[Bx], R(A), ..., R(A+n))"},
    {"VARARG", "iABC", "R(A), R(A+1), ..., R(A+B-1) := vararg"},
    {"INVALID", "", "Invalid opcode or undefined behavior"}
};