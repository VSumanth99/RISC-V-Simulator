#include <stdio.h>

//for fixed size data types
#include <stdint.h>
#include <stdlib.h>
#include "instruc_utils.h"
#include "instruc_exec.h"
#define MAX_BUFFER_SIZE 1024*1024
#define MAX_INSTRUCTIONS MAX_BUFFER_SIZE / 4

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
    uint32_t pc = 0;
    int32_t registers[32];

    //initialise registers to 0
    for (int i = 0; i < 32; i++)
      registers[i] = 0;
    for (; ; )
    {		printf("%d\n",pc );
			uint32_t instr = instructions[pc];
			pc = process_instruction(instr, registers, NULL, pc);

      //test for program end
      if(pc > n_instructions)
        break;

	  }
    printf("\nPrinting register contents:\n" );
    print_registers(registers);
  return 0;
}
