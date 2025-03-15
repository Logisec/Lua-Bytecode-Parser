## Lua Bytecode Parser
###### This is a basic lua 5.1 bytecode parser written C++.

##### Usage:
```
Open the solution file in visual studio make sure you're building with C++17.

Parser.exe <file> (luac file)
```


##### Example:
```lua
-- This is to demonstrate the parser's ability to parse multiple nested prototypes.
(function()
	print("Hello, World!");

	(function()
		print(1);
	end)();
end)();
```

##### Output:
```lua
-- Header Info --
Signature: 'Lua'
Version: 81
Format: 0
Endianness: Big Endian
Int Size: 4
Size_t Size: 4
Instruction Size: 4
Lua Number Size: 8
Integral Flag: 0
function main(...)
    -- Prototype Info --
    Source = '@test.lua'
    LineDefined = 0
    LastLineDefined = 0
    NumUpvalues = 0
    NumParameters = 0
    IsVararg = true
    MaxStackSize = 2
    -- Constants --
    -- Instructions --
    Opcode: 36, A: 0, B: 0, C: 0, Mnemonic: CLOSURE
    Opcode: 28, A: 3, B: 1, C: 2, Mnemonic: CALL
    Opcode: 30, A: 2, B: 1, C: 1, Mnemonic: RETURN
    -- Nested Prototypes --
    function proto_000001D6127E6B50(...)
        -- Prototype Info --
        Source = '(none)'
        LineDefined = 1
        LastLineDefined = 1
        NumUpvalues = 0
        NumParameters = 0
        IsVararg = false
        MaxStackSize = 2
        -- Constants --
        [Constant] Type = String, Value = "print"
        [Constant] Type = String, Value = "Hello, World!"
        -- Instructions --
        Opcode: 5, A: 0, B: 0, C: 0, Mnemonic: GETGLOBAL
        Opcode: 1, A: 2, B: 1, C: 0, Mnemonic: LOADK
        Opcode: 28, A: 5, B: 2, C: 3, Mnemonic: CALL
        Opcode: 36, A: 0, B: 0, C: 0, Mnemonic: CLOSURE
        Opcode: 28, A: 3, B: 1, C: 2, Mnemonic: CALL
        Opcode: 30, A: 2, B: 1, C: 1, Mnemonic: RETURN
        -- Nested Prototypes --
        function proto_000001D6127E8F30(...)
            -- Prototype Info --
            Source = '(none)'
            LineDefined = 1
            LastLineDefined = 1
            NumUpvalues = 0
            NumParameters = 0
            IsVararg = false
            MaxStackSize = 2
            -- Constants --
            [Constant] Type = String, Value = "print"
            [Constant] Type = Number, Value = 1
            -- Instructions --
            Opcode: 5, A: 0, B: 0, C: 0, Mnemonic: GETGLOBAL
            Opcode: 1, A: 2, B: 1, C: 0, Mnemonic: LOADK
            Opcode: 28, A: 5, B: 2, C: 3, Mnemonic: CALL
            Opcode: 30, A: 2, B: 1, C: 1, Mnemonic: RETURN
        end
    end
end
```

###### We output it in a lua like format. We got the idea from luac.nl.
###### Anyways, we plan to release a more dynamic version which will handle each and every Lua version.
###### See anything that could be improved on? Let us know! [Logisec Contact Us](https://logisec.net/contact)

###### Creds:
- [Lua 5.1 Bytecode Reference](https://archive.org/details/a-no-frills-intro-to-lua-5.1-vm-instructions)
- [Lua 5.1 lopcodes.h](https://www.lua.org/source/5.1/lopcodes.h.html)
- [Luac.nl](http://luac.nl/)
