#include "instruc_exec.h"
#include "instruc_utils.h"


uint32_t unsignedbintodec(int32_t n)
{ uint8_t count = 0;
  uint32_t num = 0;

  while(count<32)
    { num = num + 2*(n&0x01);
       n>>1;
       count ++; }
  return num;
}


uint32_t process_instruction(uint32_t instruc, int32_t *registers, uint32_t *ram, uint32_t pc)
{
  //extract the opcode from the instruction
  uint32_t opcode = instruc & 0x7f;
  uint8_t rs1, rs2, rd, funct3, funct7;
  int32_t imm;
  switch (opcode)
  {
    case 0x13:  //I type instruction

      i_type_extract(instruc, &rs1, &rd, &funct3, &imm);
      printf("I-type instruction: rs1:%u rd:%u funct3:%u imm:%d\n\n", rs1, rd, funct3, imm);
      switch (funct3)
      {
        case 0:
        //addi
          registers[rd] = registers[rs1] + imm;
          break;
        case 1:
        //slli

          registers[rd] = (uint32_t)registers[rs1] << (uint32_t)(imm&0x1f);
          break;

        case 2:
        //slti
          registers[rd] = registers[rs1] < imm;
          break;

        case 3:
        //sltiu
          registers[rd] = (uint32_t)registers[rs1] < (uint32_t)imm;
          break;

        case 4:
        //xori
          registers[rd] = registers[rs1] ^ imm;
          break;

        case 5:
        //srli/srai

        if((imm>>5) == 0)
        {
          //srli
          registers[rd] = (uint32_t)registers[rs1] >> (uint32_t)(imm & 0x1f);
        }
        else if((imm>>5) == 32)
        {
          //srai
          registers[rd] = registers[rs1] >> (imm & 0x1f);
        }
        break;

        case 6:
        //ori
          registers[rd] = registers[rs1] | imm;
          break;

        case 7:
        //andi
          registers[rd] = registers[rs1] & imm;
          break;
      }
      pc++;
      break;

    case 0x33: ; //R type instruction
      r_type_extract(instruc, &rs1, &rs2, &rd, &funct7, &funct3);
      printf("R-type instruction: rs1:%u rs2:%u rd:%u funct7:%u funct3:%u\n\n", rs1, rs2, rd, funct7, funct3);
      switch (funct3)
      {
        case 0:
        //add or sub
          if(funct7 == 0)
          {
            //add
            registers[rd] = registers[rs1] + registers[rs2];
          }
          else if(funct7 == 32)
          {
            //subtract
            registers[rd] = registers[rs1] - registers[rs2];
          }
        break;

        case 1:
        //sll
          //get lower 5 bits of registers[rs2]
          registers[rd] = (uint32_t)registers[rs1] << (uint32_t)(registers[rs2] & 0x1f);
        break;

        case 2:
        //slt
          registers[rd] = registers[rs1] < registers[rs2];
        break;

        case 3:
        //sltu
          registers[rd] = (uint32_t)registers[rs1] < (uint32_t)registers[rs2];
        break;

        case 4:
        //xor
          registers[rd] = registers[rs1] ^ registers[rs2];
        break;

        case 5:
        //srl or sra
        if(funct7 == 0)
        {
          //srl
          registers[rd] = (uint32_t)registers[rs1] >> (uint32_t)(registers[rs2]& 0x1f);
        }
        else if(funct7 == 32)
        {
          //sra
          registers[rd] = registers[rs1] >> (registers[rs2]& 0x1f);
        }
        break;

        case 6:
        //or
          registers[rd] = registers[rs1] | registers[rs2];
        break;

        case 7:
        //and
          registers[rd] = registers[rs1] & registers[rs2];
        break;
      }
      pc++;
      break;

    case 0x37: ;
    //lui
      u_type_extract(instruc, &rd, &imm);
      printf("Instruction lui: rd:%u imm:%d\n\n", rd, imm);
      registers[rd] = imm << 12;
      pc++;
      break;
    case 0x63: ;
      b_type_extract(instruc, &rs1, &rs2, &funct3, &imm);
      switch(funct3)
      {
        case 0:
        //beq
        printf("Instruction beq: rs1:%u rs2: %u imm:%d\n\n", rs1,rs2,imm);
        if (registers[rs1] == registers[rs2])
        {
                    pc = pc + (imm/2);  //he 12-bit B-immediate encodes signedoffsets in multiples of 2 bytes.  Also 4 bytes equal to 1 instruction .


        }
        else{ pc++;}
          break;
        case 1:
        //bne
        printf("Instruction bne: rs1:%u rs2: %u imm:%d\n\n", rs1,rs2,imm);
        if (registers[rs1] != registers[rs2])
        {
          //printf("%d\n",pc );
          pc = pc + (imm/2); 
          //printf("%d\n",pc );

        }
        else {pc++;}
          break;
        case 4:
        //blt
        printf("Instruction blt: rs1:%u rs2: %u imm:%d\n\n", rs1,rs2,imm);
        if (registers[rs1] < registers[rs2])
        {
          pc = pc + (imm/2);
        }
        else
          {pc++;}
          break;
        


        case 5:
        //bge
        printf("Instruction bge: rs1:%u rs2: %u imm:%d\n\n", rs1,rs2,imm);
        
        if (registers[rs1] > registers[rs2])
          {pc = pc +(imm/2);}
        else {pc ++;}
          break;
        
        case 6:
        //bltu
        printf("Instruction bltu: rs1:%u rs2: %u imm:%d\n\n", rs1,rs2,imm);
        if (unsignedbintodec(registers[rs1]) < unsignedbintodec(registers[rs2]))
        {
          pc =pc + (imm/2);
        }
        else{ pc++;}
        
          break;
        case 7:
        //bgeu
        printf("Instruction bltu: rs1:%u rs2: %u imm:%d\n\n", rs1,rs2,imm);
        if ( unsignedbintodec(registers[rs1]) > unsignedbintodec(registers[rs2]))
        {
          pc = pc + (imm/2) ;
        }
        else{pc++;}
          break;

      }
      
      break;
    case 0x6f:
      switch(funct3)
      case 0:
        jalr_type_extract(instruc, &rs1, &rd, &funct3, &imm);
        printf("Instruction jalr: rs1:%u rd: %u imm:%d\n\n", rs1,rd,imm);
        registers[rd] = pc +1;
        pc = (registers[rs1] + imm)/4;
        break;
    case 0x67:

      jal_type_extract(instruc,&rd,&imm);
      printf("Instruction jal: rd: %u imm:%d\n\n", rd,imm);
      registers[rd] = pc +1;
      pc = pc + (imm/2);
      break;


    default:
      printf("Unknown instruction with opcode: %u\n", opcode);
      pc++;
  }


  return pc;
}
