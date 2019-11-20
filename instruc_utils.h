#ifndef INSTRUC_UTILS
#define INSTRUC_UTILS

#include <stdint.h>

void print_registers(int32_t *registers);
void r_type_extract(uint32_t instruc, uint8_t* rs1, uint8_t* rs2, uint8_t* rd, uint8_t* funct7, uint8_t* funct3);
void i_type_extract(uint32_t instruc, uint8_t* rs1, uint8_t* rd, uint8_t* funct3, int32_t *imm);
void u_type_extract(uint32_t instruc, uint8_t* rd, int32_t *imm);
void b_type_extract(uint32_t instruc, uint8_t* rs1, uint8_t* rs2, uint8_t* funct3, int32_t*imm);
int32_t sign_extend(int32_t num, int bits);
void j_type_extract(uint32_t instruc,uint8_t* rd,int32_t* imm);
void load_type_extract(uint32_t instruc, uint8_t* rs1, uint8_t* rd, uint8_t* funct3, int32_t *imm);
void s_type_extract(uint32_t instruc, uint8_t* rs2, uint8_t* rs1, uint8_t* funct3, int32_t* imm);


#endif
