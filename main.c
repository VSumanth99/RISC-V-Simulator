#include <stdio.h>

//for fixed size data types
#include <stdint.h>
#include <stdlib.h>
#include "instruc_utils.h"
#include "instruc_exec.h"
#define MAX_BUFFER_SIZE 1024*1024
#define MAX_INSTRUCTIONS MAX_BUFFER_SIZE / 4
//32 MB
#define MEMORY_SIZE 32 * 1024 * 1024

int main(int argc, char const *argv[])
{
    uint32_t *instructions = NULL;
    int n_instructions=0;

    if(argc != 2)
    {
        printf("ERROR: Improper usage.\n");
        printf("Syntax: riscsimul <program name>\n");
        return -1;
    }
    else
    {
        //open the file
        FILE *fb;
        fb = fopen(argv[1], "rb");
        if(fb==NULL)
        {
            printf("ERROR: Could not open file %s\n", argv[1]);
            return -2;
        }
        //read all the instructions
        instructions = malloc(MAX_BUFFER_SIZE);
        while(fread(&instructions[n_instructions++], 4, 1, fb) == 1)
        {
            //do nothing
        }
        n_instructions -= 1;
    }

    /***********************************************

    *************************************************/
    int32_t *pc = 0;
    int32_t registers[32];


    int32_t *ram = (int32_t*)(calloc(MEMORY_SIZE/4, 4));
    //initialise registers to 0
    for (int i = 0; i < 32; i++)
        registers[i] = 0;

    //initialize stack pointer such that we have 1MB stack
    registers[2] = (int32_t) (ram + (MEMORY_SIZE - 1024*1024)/4);

    //copy the code to memory
    for(int i = 0; i < n_instructions; i++)
    {
        ram[i] = instructions[i];
    }
    free(instructions);

    pc = ram;

    for (; ; )
    {
        int32_t instr = *pc;
        pc = process_instruction(instr, registers, ram, pc);

        //test for program end
        if(pc > ram+n_instructions)
            break;
        //print_registers(registers);
        //getchar();
    }
    printf("\nPrinting register contents:\n" );
    print_registers(registers);
    free(ram);
    return 0;
}
