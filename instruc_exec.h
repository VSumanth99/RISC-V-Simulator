#ifndef INSTRUC_EXEC
#define INSTRUC_EXEC

#include <stdint.h>
#include <stdio.h>
#include "instruc_utils.h"

uint32_t process_instruction(uint32_t instruc, int32_t *registers, int32_t *ram, uint32_t pc);
uint32_t unsignedbintodec(int32_t n);

#endif
