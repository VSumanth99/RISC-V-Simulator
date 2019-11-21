#include "instruc_exec.h"
#include "instruc_utils.h"

int32_t* process_instruction(uint32_t instruc, int32_t *registers, int32_t *ram, int32_t *pc)
{
    //extract the opcode from the instruction
    uint32_t opcode = instruc & 0x7f;
    uint8_t rs1, rs2, rd, funct3, funct7;
    int32_t imm;
    switch (opcode)
    {
    case 0x13:  //I type instruction

        i_type_extract(instruc, &rs1, &rd, &funct3, &imm);
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


        switch (funct3)
        {
        case 0:
            //add or sub
            if(funct7 == 0)
            {
                //add
                registers[rd] = registers[rs1] + registers[rs2];
                ;
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

    case 0x17:
        ;
        //auipc
        u_type_extract(instruc, &rd, &imm);
        if(rd!=0)
            registers[rd] = (pc-ram)*4 + (imm << 12);

        pc++;
        break;

    case 0x37:
        ;
        //lui
        u_type_extract(instruc, &rd, &imm);

        registers[rd] = imm << 12;

        pc++;
        break;

    case 0x63:
        ;
        b_type_extract(instruc, &rs1, &rs2, &funct3, &imm);
        switch(funct3)
        {
        case 0:
            ;
            //beq

            if (registers[rs1] == registers[rs2])
            {
                pc = pc + (imm/2);
                //The 12-bit B-immediate encodes signed offsets in multiples of 2 bytes.
                //Also 4 bytes equal to 1 instruction .
            }
            else
                pc++;
            break;
        case 1:
            ;
            //bne

            if (registers[rs1] != registers[rs2])
            {
                pc = pc + (imm/2);
            }
            else {
                pc++;
            }
            break;
        case 4:
            ;
            //blt

            if (registers[rs1] < registers[rs2])
            {
                pc = pc + (imm/2);
            }
            else
            {
                pc++;
            }
            break;

        case 5:
            ;
            //bge

            if (registers[rs1] > registers[rs2])
                pc = pc +(imm/2);
            else
                pc ++;
            break;

        case 6:
            ;
            //bltu
            if ((uint32_t)(registers[rs1]) < (uint32_t)(registers[rs2]))
            {
                pc =  pc + (imm/2);
            }
            else
                pc++;

            break;

        case 7:
            ;
            //bgeu
            if ( (uint32_t)(registers[rs1]) > (uint32_t)(registers[rs2]))
                pc = pc + (imm/2) ;

            else
                pc++;
            break;
        }
        break;

    case 0x67:
    {   //jalr
        i_type_extract(instruc, &rs1, &rd, &funct3, &imm);
        switch(funct3)
        {
        case 0:
            ;
            if(rd!=0)
                registers[rd] = (int32_t)(pc + 1); //storing pointer value in register
            pc = ram + ((registers[rs1] + imm)&0xfffffffe)/4;
            break;
        }
        break;
    }

    case 0x6f:
    {   //jal (J type instruction)
        j_type_extract(instruc,&rd,&imm);
        if(rd!=0)
            registers[rd] = (int32_t)(pc - ram + 1) * 4; //storing pointer value in register
        pc = pc + (imm/2);
        break;
    }

    case 0x03:
        load_type_extract(instruc,&rs1, &rd, &funct3, &imm);
        switch(funct3)
        {
        case 0:
            //lb
            registers[rd] = sign_extend((ram[(registers[rs1] + imm)/4])&0xff, 8);
            pc++;
            break;

        case 1:
            //lh
            registers[rd] = sign_extend((ram[(registers[rs1] + imm)/4])&0xffff, 16);
            pc++;
            break;

        case 2:
            //lw


            registers[rd] = ram[(registers[rs1] + imm)/4] ;

            pc++;
            break;

        case 3:
            //ld
            printf("ERROR: Trying to use ld instruction in 32-bit system\n");
            pc++;
            break;

        case 4:
            //lbu
            registers[rd] = ram[(registers[rs1] + imm)/4]&0xff;
            pc++;
            break;

        case 5:
            //lhu
            registers[rd] = ram[(registers[rs1] + imm)/4] & 0xffff;
            pc++;
            break;

        case 6:
            //lwu
            registers[rd] = ram[(registers[rs1] + imm)/4] & 0xffffffff;
            pc++;
            break;
        }
        break;

    case 0x23:
        s_type_extract(instruc, &rs2, &rs1, &funct3, &imm);

        switch(funct3)
        {
        case 0:
            //sb
            ram[(registers[rs1] + imm)/4] = registers[rs2]&0xff;
            pc++;
            break;
        case 1:
            //sh
            ram[(registers[rs1] + imm)/4] = registers[rs2]&0xffff;
            pc++;
            break;

        case 2:
            //sw
            ram[(registers[rs1] + imm)/4] = registers[rs2]&0xffffffff;
            pc++;
            break;

        case 3:
            //sd
            printf("ERROR: Trying to use 64bit instruction sd in 32-bit simulator\n");
            pc++;
            break;
        }
        break;

    case 0x73: ;//ecall
        switch (registers[10])
        {
        case 10:
            //print registers
            printf("Exiting the program...printing registers\n");
            print_registers(registers);
            exit(0);
        }
    default:
        printf("Unknown instruction with opcode: %u\n", opcode);
        pc++;
    }

    return pc;
}
