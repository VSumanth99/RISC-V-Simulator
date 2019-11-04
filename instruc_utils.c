
#include "instruc_utils.h"
#include <stdio.h>


void print_registers(int32_t *registers)
{
    for(int i = 0; i < 32; i++)
    {
      printf("x%d:\t\t%d\n", i, registers[i]);
    }
}

int32_t sign_extend(int32_t num, int bits)
{
  uint32_t left_most = num >> (bits-1);
  return left_most == 0x01 ? ((0xffffffff<<bits) + num ) : num;
}

void r_type_extract(uint32_t instruc, uint8_t* rs1, uint8_t* rs2, uint8_t* rd, uint8_t* funct7, uint8_t* funct3)
{
  *rs1 = (instruc >> 15) & 0x1f;
  *rs2 = (instruc >> 20) & 0x1f;
  *rd = (instruc >> 7) & 0x1f;
  *funct7 = (instruc >> 25) & 0x7f;
  *funct3 = (instruc >> 12) & 0x07;
}

void i_type_extract(uint32_t instruc, uint8_t* rs1, uint8_t* rd, uint8_t* funct3, int32_t *imm)
{
  *rd = (instruc >> 7) & 0x1f;
  *funct3 = (instruc >> 12) & 0x07;
  *rs1 = (instruc >> 15) & 0x1f;
  *imm = sign_extend(instruc >> 20, 12);
}

void u_type_extract(uint32_t instruc, uint8_t* rd, int32_t *imm)
{
  *rd = (instruc>>7) & 0x1f;
  *imm = (instruc >> 12);

}
