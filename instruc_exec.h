#ifndef INSTRUC_EXEC
#define INSTRUC_EXEC

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "instruc_utils.h"

int32_t* process_instruction(uint32_t instruc, int32_t *registers, int32_t *ram, int32_t *pc);

#endif
