
#include "instruc_utils.h"
#include <stdio.h>


void print_registers(int32_t *registers)
{
    FILE *write_ptr;
    for(int i = 0; i < 32; i++)
    {
      printf("x%d:\t\t%d\n", i, registers[i]);
    }
    write_ptr = fopen("dump.res","wb");  // w for write, b for binary
    fwrite(registers, 4*32, 1 , write_ptr);

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

void b_type_extract(uint32_t instruc, uint8_t* rs1, uint8_t* rs2, uint8_t* funct3, int32_t*imm)
{
  *rs1 = (instruc>>15) & 0x1f;
  *rs2 = (instruc>>20) & 0x1f;
  *funct3 =(instruc>>12) &0x07;
  int32_t imm_12 = (((instruc>>31)&0x01)<<11);
  int32_t imm_11 = (((instruc>>7)&0x01)<<10);
  int32_t imm_10_5 =(((instruc>>25)&0x3f)<<4);
  int32_t imm_4_1 = ((instruc>>8)&0x0f);
  *imm = sign_extend(imm_12+imm_11+imm_10_5+imm_4_1,12);
}

void jalr_type_extract(uint32_t instruc, uint8_t* rs1, uint8_t* rd, uint8_t* funct3, int32_t *imm)
{
  *rd = (instruc >> 7) & 0x1f;
  *funct3 = (instruc >> 12) & 0x07;
  *rs1 = (instruc >> 15) & 0x1f;
  *imm = sign_extend(instruc >> 20, 12);
}

void j_type_extract(uint32_t instruc,uint8_t* rd,int32_t* imm)
{
  *rd = (instruc >> 7) & 0x1f;
  int32_t imm_20 = (((instruc>>31)&0x01)<<19);
  int32_t imm_19_12 = (((instruc>>12)&0xff)<<11);
  int32_t imm_11 = (((instruc>>20)&0x01)<<10);
  int32_t imm_10_1 = ((instruc>>21)&0x3ff);
  *imm = sign_extend(imm_20 + imm_19_12 + imm_11 + imm_10_1, 20);
}

void load_type_extract(uint32_t instruc, uint8_t* rs1, uint8_t* rd, uint8_t* funct3, int32_t* imm)
{
  *rd = (instruc >> 7) & 0x1f;
  *funct3 = (instruc >> 12) & 0x07;
  *rs1 = (instruc >> 15) & 0x1f;
  *imm = sign_extend(instruc >> 20, 12);
}

void s_type_extract(uint32_t instruc, uint8_t* rs2, uint8_t* rs1, uint8_t* funct3, int32_t* imm)
{
  *rs2 = (instruc>>20)&0x1f;
  *rs1 = (instruc>>15)&0x1f;
  *funct3 = (instruc>>12)&0x07;
  int32_t imm_11_5 = (((instruc>>25)&0x7f)<<5);
  int32_t imm_4_0 = ((instruc>>7)&0x1f) ;
  *imm = sign_extend(imm_11_5 + imm_4_0, 12);
}
