# Mano 16-Bit Emulator Documentation

## Overview

The Mano 16-Bit Emulator is a C-based instruction-level virtual machine inspired by the Morris Mano Basic Computer architecture.

It simulates a custom 16-bit CPU capable of executing binary programs generated from a custom assembler. The emulator implements a complete Fetch → Decode → Execute pipeline and supports memory-reference, register-reference, and I/O instructions.

This emulator acts as the execution backend of the **Bare-Metal-Core** ecosystem.

---

# System Architecture

The emulator is divided into multiple components responsible for instruction execution, memory access, decoding, and CPU state management.

## CPU Registers

The emulator simulates core processor registers:

| Register | Purpose |
|----------|---------|
| AC | Accumulator register |
| PC | Program Counter |
| IR | Instruction Register |
| MAR | Memory Address Register |
| MDR | Memory Data Register |
| E | Carry flag |
| Z | Zero flag |
| N | Negative flag |
| V | Overflow flag |
| IEN | Interrupt enable |

---

# Memory Model

The emulator uses:

8192 bytes of memory

Memory is:

Byte-addressable

Each word consists of:

2 bytes
Memory Layout
0th – 499th word      → Data Segment
500th – 4095th word   → Instruction Segment

Since:

1 word = 2 bytes

the emulator internally converts word addresses into byte offsets.

Example:

Word Address = 500
Byte Address = 1000

This conversion is handled automatically during instruction decoding.

Instruction Execution Cycle

The emulator executes instructions through a:

Fetch → Decode → Execute

pipeline.

1. Fetch Stage

The CPU fetches the instruction from memory using the Program Counter.

Example:

IR ← Memory[PC]
PC ← PC + 2

Since each instruction occupies:

1 word = 2 bytes

the Program Counter increments by:

2

after every fetch.

2. Decode Stage

The fetched instruction is decoded into:

Opcode
Address field
Mode bit

The decoder extracts:

Opcode → upper bits
Operand → lower 12 bits

The emulator automatically converts word-addressed instructions into byte-addressable memory locations.

Example:

Address = 500

500 × 2

= 1000 byte offset
3. Execute Stage

The decoded instruction is executed.

Supported operations include:

Arithmetic operations
Logical operations
Data transfer
Branching and control flow
Input / Output instructions
Supported Instruction Set
Memory Reference Instructions
Instruction	Description
AND	Bitwise AND
ADD	Addition
LDA	Load accumulator
STA	Store accumulator
BUN	Unconditional branch
BSA	Branch and save return address
ISZ	Increment and skip if zero
Register Reference Instructions
Instruction	Description
CLA	Clear accumulator
CLE	Clear carry flag
CMA	Complement accumulator
CME	Complement carry
CIR	Circular shift right
CIL	Circular shift left
INC	Increment accumulator
SPA	Skip if positive
SNA	Skip if negative
SZA	Skip if accumulator is zero
SZE	Skip if carry equals zero
HLT	Halt execution
I/O Instructions
Instruction	Description
INP	Input character
OUT	Output character
SKI	Skip if input flag set
SKO	Skip if output flag set
ION	Interrupt enable
IOF	Interrupt disable
Project Structure
Mano-emulator/
│── cpu.c
│── cpu.h
│── memory.c
│── memory.h
│── execute.c
│── execute.h
│── decode.c
│── decode.h
│── opcode.h
│── main.c
│── Makefile
│── README.md
│── DOCUMENTATION.md
Installation
Requirements

Install:

GCC or Clang
Make
Clone the Repository
git clone https://github.com/Tanuj-Rana/Mano-emulator.git
cd Mano-emulator
Building the Emulator

Compile the emulator using:

make

This generates the executable:

emulator

If make does not work:

gcc cpu.c decode.c execute.c main.c memory.c -o emulator
How to Generate assembled.bin

The emulator does not directly execute assembly code.

You must first convert assembly source code into:

assembled.bin

using the custom assembler.

Step 1: Clone the Custom Assembler

GitHub Repository:

https://github.com/AnshuNegi2006/Mano-Machine-Assembler

Clone:

git clone https://github.com/AnshuNegi2006/Mano-Machine-Assembler.git
cd Mano-Machine-Assembler
Step 2: Build the Assembler

Compile the assembler:

make
Step 3: Create Assembly Program

Create a file:

program.sys

Example program:

```
VAR a 10;
VAR b 20;
VAR ans 0;

LDA a;
ADD b;
STA ans;

LDA ans;

HLT;
```

Step 4: Generate Binary File

Run:

./assembler program.sys

This generates:

assembled.bin

Step 5: Move Binary File

Copy or move:

assembled.bin

into the emulator directory.

Example:

mv assembled.bin path/to/Mano-emulator/

or manually copy it.

How to Run the Emulator

Inside the emulator directory:

Run:

./emulator

The emulator will automatically load:

assembled.bin

from the current directory.

Example Execution

Example terminal output:
```
Hello World!

Enter a number : 5
Enter a number : 10

Execution Halted
Final AC = 15
Final PC = 1206
Example Programs
Addition Program
VAR a 50;
VAR b 25;
VAR c 15;
VAR ans 0;

LDA a;
ADD b;
STA ans;

LDA ans;
ADD c;
STA ans;

LDA ans;

HLT;
```
Expected Output:

Final AC = 90
How Variables Work

Variables declared using:

VAR x 50;

are automatically stored inside the:

Data Segment (0–499 words)

Example:
```
VAR x 50;

can later be accessed using:

LDA x;
ADD x;
STA x;
```
The assembler automatically resolves memory addresses.

Common Terminal Commands
Build Emulator
make
Run Emulator
./emulator
Rebuild Emulator
make clean
make
Build Without Makefile
gcc cpu.c decode.c execute.c main.c memory.c -o emulator
Known Limitations

Current limitations include:

Character-based I/O system
No advanced interrupt handling
No GUI debugger
Limited numeric formatting
No execution visualization
Technical Challenge Faced

One of the major implementation challenges was handling the mismatch between:

Word-addressed instructions

and

Byte-addressable memory

Since:

1 word = 2 bytes

instruction addresses required internal conversion into byte offsets.

This initially caused:

Instruction misalignment
Opcode corruption
Infinite loops
Out-of-bound memory access

Resolving this issue significantly improved architectural correctness.

Future Improvements

Planned improvements:

Numeric output instruction
Better debugger support
Improved interrupt system
More instruction validation
Execution tracing
Better assembler integration


Author
Tanuj Rana

GitHub:

https://github.com/Tanuj-Rana
