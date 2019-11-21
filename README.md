# RISC-V-Simulator
Simple simulator for RISC-V programs.
So far, has implemented the following instructions:

### R-type instructions
1. `add`     
2. `sub`     
3. `sll`     
4. `slt`     
5. `sltu`    
6. `xor`     
7. `srl`     
8. `sra`     
9. `or`      
10. `and`

### I-type instructions
1. `addi`    
2. `slli`    
3. `slti`    
4. `sltiu`   
5. `xori`    
6. `srli`    
7. `srai`    
8. `ori`     
9. `andi`  

### U-type instructions
1. `lui`
2. `auipc`   

### B-type instructions
1. `beq`     
2. `bne`     
3. `blt`     
4. `bge`     
5. `bltu`    
6. `bgeu`   
7. `jalr`    
8. `jal`   

### Store Instructions
`lb`      
`lh`      
`lw`      
`ld`      
`lbu`     
`lhu`     
`lwu`     

`sb`     
`sh`     
`sw`     
`sd`     

### Environment calls
To use an environmental call, load the ID into register a0, and load any arguments into a1 - a7. 
Any return values will be stored in argument registers.

Following are the environment calls supported

| ID(a0) | Name | Description|
|---|---|---|
| 10 | exit | Ends the program |
| 1 | print_int | print intergers in a1 |
| 4 | print_string | prints the null-terminated string whose address is in a1 |
| 11 | print_character | prints ASCII character in a1 |
| 17 | exit2 | ends the program with return code in a1 |

### Unimplimented Environment Calls

| ID(a0) | Name | Description|
|---|---|---|
| 9 | sbrk | allocates a1 bytes on the heap, returns pointer to start in a0 |


### Installation Dependencies

Note that we have compiled the simulator to work as a 32-bit binary. The appropriate version of `gcc` needs to be installed. On ubuntu 18.04 this corresponds to installing the package `gcc-multilib`, using the command `sudo apt-get install gcc-multilib`

### Note on Stack pointer

We have initialized 32MB of ram for the program. 
We have initialized stack pointer 1MB from the top of ram.
We copied program instructions to bottom of the ram.

Opcodes found here:
https://github.com/riscv/riscv-opcodes/blob/master/opcodes
