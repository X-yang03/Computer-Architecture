#include <stdio.h>
#include "shell.h"

#define op_R 0x00  //R type instruction

//with 3 registers
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


//J type



#define funct_addu



void process_instruction()
{
    uint32_t ins = mem_read_32(CURRENT_STATE.PC);  //read the instruction to be processed via PC register

    /* execute one instruction here. You should use CURRENT_STATE and modify
     * values in NEXT_STATE. You can call mem_read_32() and mem_write_32() to
     * access memory. */
}
