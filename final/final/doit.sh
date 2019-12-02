# generate final tests
#
# results shall be:
# simple: x1 to x4, is 1, 2, 3, and 4
# C based results in a1 (x11):
# medium: sum of 0 to 19, written and loaded into stack is 190, 0xbe
# fact(7): 5040, 0x13b0




riscv32-unknown-elf-gcc -nostartfiles -march=rv32i -mabi=ilp32 -Wl,--script=$HOME/linker.ld simple.s -o simple.out
riscv32-unknown-elf-objcopy simple.out --dump-section .text=simple.bin

riscv32-unknown-elf-gcc -nostartfiles -march=rv32i -mabi=ilp32 -Wl,--script=$HOME/linker.ld fact.c -o fact.out
riscv32-unknown-elf-objcopy fact.out --dump-section .text=fact.bin

riscv32-unknown-elf-gcc -nostartfiles -march=rv32i -mabi=ilp32 -Wl,--script=$HOME/linker.ld medium.c -o medium.out
riscv32-unknown-elf-objcopy medium.out --dump-section .text=medium.bin
