#include <stdio.h>
#include "shell.h"

#define op_R 0x00  //R type instruction

#define funct_add 0x20 // add 10000
#define funct_addu 0x21 //addu 100001
#define funct_sub 0x22 //sub 100010
#define funct_subu 0x23 //sub 100011

#define funct_and 0x24 //and 100100
#define funct_or  0x25 //or 100101
#define funct_xor 0x26 //xor 100110
#define funct_nor 0x27 //nor 100111

#define funct_slt 0x2a // slt 101010
#define funct_sltu 0x2b //sltu 101011

#define funct_sll 0x00 //sll 000000
#define funct_srl 0x02 //srl 000010
#define funct_sra 0x03 //sra 000011
#define funct_sllv 0x04 //sllv 000100

#define funct_srlv 0x06 //srlv 000110
#define funct_srav 0x07 //srav 000111

#define funct_mult 0x18 //mult 011000
#define funct_mfhi 0x10 //mfhi 010000
#define funct_mflo 0x12 //mflo 010010
#define funct_mthi 0x11 //mthi 010001
#define funct_mtlo 0x13 //mtlo 010011
#define funct_multu 0x19 //multu 011001

#define funct_div 0x1a //div 011010
#define funct_divu 0x1b //divu 011011


#define funct_SYSCALL 0x0a //syscall 001100

#define funct_jalr 0x0b // jalr 001001
#define funct_jr 0x08 //jr 001000

// I type instructions

#define op_addi 0x08 //addi 001000
#define op_addiu 0x09 //addiu 001001
#define op_slti 0x0a  //slti 001010
#define op_sltiu 0x0b // sltiu 001011
#define op_andi 0x0c //andi 001100
#define op_ori 0x0d //ori 001101
#define op_xori 0x0e //xori 001110

#define op_lui 0x0f //lui 001111
#define op_lw 0x23 //lw 100011
#define op_sw 0x2b //sw 101011
#define op_lb 0x20 //lb 100000
#define op_lbu 0x24 //lbu 100100
#define op_lh 0x21 //lh 100001
#define op_lhu 0x25 //lhu 100101
#define op_sb 0x28 //sb 101000
#define op_sh 0x29 //sh 101001


#define op_beq 0x04 //beq 000100
#define op_bne 0x05 //bne 000101

#define op_bgtz 0x07 //bgtz 000111

#define op_Branch 0x01 // REGIMM 000001
#define BGEZ 0x01 //BGEZ 00001
#define BGEZAL 0x11 // BGEZAL 10001
#define BLTZ 0x00 //bltz 00000
#define BLTZAL 0x10 //BLTZAL 10000


//J type

#define op_j 0x02 //J 000010
#define op_jal 0x03 //jal 000011

void excute_R(uint32_t rs,uint32_t rt,uint32_t rd,uint32_t shamt,uint32_t funct){

    NEXT_STATE.PC = CURRENT_STATE.PC + 4;

    switch (funct)
    {
    case funct_add:
        NEXT_STATE.REGS[rd] = (int)CURRENT_STATE.REGS[rs]+(int)CURRENT_STATE.REGS[rt];
        break;

    case funct_addu:
        NEXT_STATE.REGS[rd] = CURRENT_STATE.REGS[rs]+CURRENT_STATE.REGS[rt];
        break;

    case funct_sub:
        NEXT_STATE.REGS[rd] = (int)CURRENT_STATE.REGS[rs]-(int)CURRENT_STATE.REGS[rt];
        break;

    case funct_subu:
         NEXT_STATE.REGS[rd] = CURRENT_STATE.REGS[rs]-CURRENT_STATE.REGS[rt];
        break;

    case funct_and:
         NEXT_STATE.REGS[rd] = CURRENT_STATE.REGS[rs] & CURRENT_STATE.REGS[rt];
        break;

    case funct_or:
        NEXT_STATE.REGS[rd] = CURRENT_STATE.REGS[rs] | CURRENT_STATE.REGS[rt];
        break;

    case funct_xor:
        NEXT_STATE.REGS[rd] = CURRENT_STATE.REGS[rs] ^ CURRENT_STATE.REGS[rt];
        break;

    case funct_nor :
        NEXT_STATE.REGS[rd] = ~(CURRENT_STATE.REGS[rs] | CURRENT_STATE.REGS[rt]);
        break;

    case funct_slt:
        NEXT_STATE.REGS[rd] = 1 ? ((int)CURRENT_STATE.REGS[rs]<(int)CURRENT_STATE.REGS[rt]) : 0;
        break;

    case funct_sltu:
        NEXT_STATE.REGS[rd] = 1 ? (CURRENT_STATE.REGS[rs]<CURRENT_STATE.REGS[rt]) : 0;
        break;

    case funct_sll:
        NEXT_STATE.REGS[rd]=CURRENT_STATE.REGS[rt] << shamt;
        break;

    case funct_srl:
         NEXT_STATE.REGS[rd]=(uint32_t)(CURRENT_STATE.REGS[rt] >> shamt);
        break;

    case funct_sra:
        NEXT_STATE.REGS[rd] = (int)(CURRENT_STATE.REGS[rt] >> shamt);
         break;

    case funct_sllv:
         NEXT_STATE.REGS[rd]=CURRENT_STATE.REGS[rt] << CURRENT_STATE.REGS[rs];
        break;
    
    case funct_srlv:
         NEXT_STATE.REGS[rd]=(uint32_t)(CURRENT_STATE.REGS[rt] >> CURRENT_STATE.REGS[rs]);
        break;
    
    case funct_srav:
        NEXT_STATE.REGS[rd] = (int)(CURRENT_STATE.REGS[rt] >> CURRENT_STATE.REGS[rs]);
         break;

    case funct_mult:
        int64_t mult = (int64_t)CURRENT_STATE.REGS[rs] * (int64_t)CURRENT_STATE.REGS[rt];
        NEXT_STATE.HI = (uint32_t)mult >> 32;
        NEXT_STATE.LO =(uint32_t) mult&0x00000000FFFFFFFF;
        break;
    
    case funct_multu:
        uint64_t mult = (uint64_t)CURRENT_STATE.REGS[rs] * (uint64_t)CURRENT_STATE.REGS[rt];
        NEXT_STATE.HI = (uint32_t)mult >> 32;
        NEXT_STATE.LO =(uint32_t) mult&0x00000000FFFFFFFF;
        break;

    case funct_mfhi:
         NEXT_STATE.REGS[rd] = CURRENT_STATE.HI;
        break;

    case funct_mflo:
         NEXT_STATE.REGS[rd] = CURRENT_STATE.LO;
        break;

    case funct_mthi:
        NEXT_STATE.HI = CURRENT_STATE.REGS[rd];
        break;

    case funct_mtlo:
        NEXT_STATE.LO = CURRENT_STATE.REGS[rd];
        break;

    case funct_div:
        if (CURRENT_STATE.REGS[rt]== 0)
                        exit(1);
                    
        NEXT_STATE.HI=((int)CURRENT_STATE.REGS[rs] % (int)CURRENT_STATE.REGS[rt]);

        NEXT_STATE.LO=((int)CURRENT_STATE.REGS[rs] / (int)CURRENT_STATE.REGS[rt]);
        break;
    
    case funct_divu:
        if (CURRENT_STATE.REGS[rt]== 0)
                        exit(1);
                    
        NEXT_STATE.HI=((uint32_t)CURRENT_STATE.REGS[rs] % (uint32_t)CURRENT_STATE.REGS[rt]);

        NEXT_STATE.LO=((uint32_t)CURRENT_STATE.REGS[rs] / (uint32_t)CURRENT_STATE.REGS[rt]);
        break;

    case funct_jr:
        if(CURRENT_STATE.REGS[rs] % 32 != 0) // not word-aligned
            {
                printf('address is not word-aligned!\n');
                exit(1);
            }
        NEXT_STATE.PC = CURRENT_STATE.REGS[rs];
        break;

    case funct_jalr:
        if(CURRENT_STATE.REGS[rs] % 32 != 0) // not word-aligned
            {
                printf('address is not word-aligned!\n');
                exit(1);
            }
        NEXT_STATE.REGS[rd] = CURRENT_STATE.PC + 8;
        NEXT_STATE.PC = CURRENT_STATE.REGS[rs];
        break;
    
    case funct_SYSCALL:
        if (CURRENT_STATE.REGS[2] == 0x0a)
            RUN_BIT = 0;
        break;

    default:

        break;
    }
}

void excute_I_and_J(uint32_t op , uint32_t rs,uint32_t rt,uint32_t rd,uint32_t imm,uint32_t target){

}

void process_instruction()
{
    uint32_t ins = mem_read_32(CURRENT_STATE.PC);  //read the instruction to be processed via PC register


    uint32_t op = (ins >> 26) & 0x3F; // ins[31:26]
    uint32_t rs = (ins >> 21) & 0x1F; // ins[25:21]
    uint32_t rt = (ins >> 16) & 0x1F; //ins [20:16]
    uint32_t rd = (ins >> 11) & 0x1F; //ins [15:11]
    uint32_t shamt = (ins >> 6) & 0x1F; //ins[10:6]
    uint32_t funct = (ins >> 0) & 0x3F; //ins[5:0]
    uint32_t imm = (ins >> 0) & 0xFFFF; //ins[15:0]
    //uint32_t extend_imm = sign_extend_h2w(imm);
    uint32_t target = ins & 0x3ffffff;
    /* execute one instruction here. You should use CURRENT_STATE and modify
     * values in NEXT_STATE. You can call mem_read_32() and mem_write_32() to
     * access memory. */
    if(op == op_R){
            excute_R(rs,rt,rd,shamt,funct);
    }

}
