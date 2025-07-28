
# Skuggi - GameBoy Emulator in C++
![Language](https://img.shields.io/badge/language-C++-blue?style=flat-square)
![Platform](https://img.shields.io/badge/platform-Game%20Boy-red?style=flat-square)
![Type](https://img.shields.io/badge/type-Emulator-blue?style=flat-square)
![License](https://img.shields.io/badge/license-MIT-green?style=flat-square)
![Status](https://img.shields.io/badge/status-WIP-orange?style=flat-square)

## Motivation

Sometime ago I was completely obsessed to understand how a computer works. This emulator then emerges as a learning opportunity that joins my love for old games and the possibility do virtually reproduce what I was studying. 

## The project

This work is meant to be the intersection of many "small projects". The current is to correctly emulate the gbz80 GameBoy chipset completely from scratch in C++. Which I hope in the future will evolve into a working emulator. Later on I have some ideas on real time game debugging and other features I aim to implement. 

## Challenges

### The Fetch-Decode-Execute cycle

This is one of the main components of a working emulator, and I indeed wanted to implement it the best way I could. My goal was to get away with the "easy path" of a multidude of switch-cases to link the read opcode with the correct instruction. And I did it by creating a more sophisticated data pipeline presented below:

1. When creating a CPU instance, a Json with the Instruction's metadata is loaded into the cpu. The data for each instruction is kept in an "_Instruction_" object within a map linking opcode and the object. Furthermore, the CPU also contains a map, linking the mnemonic of each instruction and its implementation.
3. After fetching the opcode, the cpu can retrieve the correct Instruction within the map.
3. The _Execute Instruction_ CPU method is feeded with the _Instruction_, creating a _InstructionParameters_ object with the correct parameters needed for the execution and getting the right Instruction implementation with the instruction's mnemonic.
4. Still in the execute method, the correct implementation is feeded with the _InstructionParameters_, and it's its work to find out how to deal with the data.

It may seem a little overcomplicated at first, but this complication's reward is a better readability, maintability and modularity. Making the code easier to understand, expand and debug. It also avoids excessive comparation, which accelerates the response time, mainly due to the unordered_maps used to store metadata and the instruction's code itself. 

## References

The main references are technical, and listed bellow (with no care to importance positioning):

1. gbdev pandocs: https://gbdev.io/pandocs/
2. gbz80 Instruction Set: https://rgbds.gbdev.io/docs/v0.9.3/gbz80.7#LD__HL_,r8
3. GB complete technical reference: https://gekkio.fi/files/gb-docs/gbctr.pdf