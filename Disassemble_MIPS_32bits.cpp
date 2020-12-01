#include<windows.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<time.h>
#include<ctype.h>
typedef long long int LLI;

typedef struct StackB {
    char base[1024];
    int fur;
} STACKBASE;

STACKBASE* StackBase = (STACKBASE*)malloc(sizeof(STACKBASE));

void IniStackBase() {
    StackBase->fur = 0;
}

void PushStackBase(int push) {
    StackBase->base[StackBase->fur] = push;
    StackBase->fur++;
}

char PopStackBase() {
    StackBase->fur--;
    char tem = StackBase->base[StackBase->fur];
    return tem;
}

char ITOA(int n) {
    return (char)('0' + n);
}

int ATOI(char a) {
    if (a >= '0' && a <= '9')
        return (int)(a - '0');
    else if (a >= 'a' && a <= 'f')
        return (int)(10 + (a - 'a'));
    else if (a >= 'A' && a <= 'F')
        return (int)(10 + (a - 'A'));
    else return -1;
}

char* DecToBin_Return(unsigned int num) {
    if (num == 0) {
        static char res[65];
        memset(res, '\0', sizeof(res));
        strcpy(res, "0");
        return res;
    }
    IniStackBase();
    while (num) {
        PushStackBase(ITOA(num % 2));
        num /= 2;
    }
    static char res[65];
    memset(res, '\0', sizeof(res));
    int cur = 0;
    while (StackBase->fur != 0) {
        res[cur++] = PopStackBase();
    }
    return res;
}

int BinToDec_Return(const char bin[]) {
    int dec = 0, len = strlen(bin);
    for (int i = 0; i < len; i++) {
        dec += ((int)bin[i] - (int)'0') * (1 << (len - i - 1));
    }
    return dec;
}

unsigned int HexToDec(const char hex[]) {
    unsigned int trans[500] = { 0 };
    for (int i = (int)'A'; i <= (int)'Z'; i++) {
        trans[i] = 10 + i - (int)'A';
    }
    for (int i = (int)'0'; i <= (int)'9'; i++) {
        trans[i] = i - (int)'0';
    }
    unsigned int dec = 0, len = strlen(hex);
    for (unsigned int i = 0; i < len; i++) {
        char tem = hex[i];
        if ('a' <= hex[i] && hex[i] <= 'f') tem += 'A' - 'a';
        dec += trans[(unsigned int)tem] * (1 << 4 * (unsigned int)(len - 1 - i));
    }
    return dec;
}

void Trim_n(char str[]) {
    if (str[strlen(str) - 1] == '\n') str[strlen(str) - 1] = '\0';
}

char raw[10000][50];
char reg[5];
char* Register(char code[]) {
    memset(reg, '\0', sizeof(reg));
    if (strcmp(code, "00000") == 0)
        strcpy(reg, "$0");
    else if (strcmp(code, "00001") == 0)
        strcpy(reg, "$at");
    else if (strcmp(code, "00010") == 0)
        strcpy(reg, "$v0");
    else if (strcmp(code, "00011") == 0)
        strcpy(reg, "$v1");
    else if (strcmp(code, "00100") == 0)
        strcpy(reg, "$a0");
    else if (strcmp(code, "00101") == 0)
        strcpy(reg, "$a1");
    else if (strcmp(code, "00110") == 0)
        strcpy(reg, "$a2");
    else if (strcmp(code, "00111") == 0)
        strcpy(reg, "$a3");
    else if (strcmp(code, "01000") == 0)
        strcpy(reg, "$t0");
    else if (strcmp(code, "01001") == 0)
        strcpy(reg, "$t1");
    else if (strcmp(code, "01010") == 0)
        strcpy(reg, "$t2");
    else if (strcmp(code, "01011") == 0)
        strcpy(reg, "$t3");
    else if (strcmp(code, "01100") == 0)
        strcpy(reg, "$t4");
    else if (strcmp(code, "01101") == 0)
        strcpy(reg, "$t5");
    else if (strcmp(code, "01110") == 0)
        strcpy(reg, "$t6");
    else if (strcmp(code, "01111") == 0)
        strcpy(reg, "$t7");
    else if (strcmp(code, "10000") == 0)
        strcpy(reg, "$s0");
    else if (strcmp(code, "10001") == 0)
        strcpy(reg, "$s1");
    else if (strcmp(code, "10010") == 0)
        strcpy(reg, "$s2");
    else if (strcmp(code, "10011") == 0)
        strcpy(reg, "$s3");
    else if (strcmp(code, "10100") == 0)
        strcpy(reg, "$s4");
    else if (strcmp(code, "10101") == 0)
        strcpy(reg, "$s5");
    else if (strcmp(code, "10110") == 0)
        strcpy(reg, "$s6");
    else if (strcmp(code, "10111") == 0)
        strcpy(reg, "$s7");
    else if (strcmp(code, "11000") == 0)
        strcpy(reg, "$t8");
    else if (strcmp(code, "11001") == 0)
        strcpy(reg, "$t9");
    else if (strcmp(code, "11010") == 0)
        strcpy(reg, "$k0");
    else if (strcmp(code, "11011") == 0)
        strcpy(reg, "$k1");
    else if (strcmp(code, "11100") == 0)
        strcpy(reg, "$gp");
    else if (strcmp(code, "11101") == 0)
        strcpy(reg, "$sp");
    else if (strcmp(code, "11110") == 0)
        strcpy(reg, "$fp");
    else if (strcmp(code, "11111") == 0)
        strcpy(reg, "$ra");
    else strcpy(reg, "*ERR");
    return reg;
}
void Initial_Str(char str[]) {
    memset(str, '\0', sizeof(str));
}
int ADDU(char code[]) {
    char special[10], addu[10];
    Initial_Str(special);
    Initial_Str(addu);
    for (int i = 0; i < 6; i++) special[i] = code[i];
    for (int i = 26; i < 32; i++) addu[i - 26] = code[i];
    special[6] = addu[6] = '\0';
    int judge;
    (strcmp(special, "000000") == 0 && strcmp(addu, "100001") == 0) ? judge = 1 : judge =  0;
    if (judge) {
        char rs[10], rt[10], rd[10];
        Initial_Str(rs);
        Initial_Str(rt);
        Initial_Str(rd);
        for (int i = 6; i < 11; i++) rs[i - 6] = code[i];
        for (int i = 11; i < 16; i++) rt[i - 11] = code[i];
        for (int i = 16; i < 21; i++) rd[i - 16] = code[i];
        rs[5] = rt[5] = rd[5] = '\0';
        strcpy(rs, Register(rs));
        strcpy(rt, Register(rt));
        strcpy(rd, Register(rd));
        printf("%-9s%-5s%-5s%-5s\n", "addu", rd, rs, rt);
        return 1;
    }
    else return 0;
}
int SUBU(char code[]) {
    char special[10], subu[10];
    Initial_Str(special);
    Initial_Str(subu);
    for (int i = 0; i < 6; i++) special[i] = code[i];
    for (int i = 26; i < 32; i++) subu[i - 26] = code[i];
    special[6] = subu[6] = '\0';
    int judge;
    (strcmp(special, "000000") == 0 && strcmp(subu, "100011") == 0) ? judge = 1 : judge = 0;
    if (judge) {
        char rs[10], rt[10], rd[10];
        Initial_Str(rs);
        Initial_Str(rt);
        Initial_Str(rd);
        for (int i = 6; i < 11; i++) rs[i - 6] = code[i];
        for (int i = 11; i < 16; i++) rt[i - 11] = code[i];
        for (int i = 16; i < 21; i++) rd[i - 16] = code[i];
        rs[5] = rt[5] = rd[5] = '\0';
        strcpy(rs, Register(rs));
        strcpy(rt, Register(rt));
        strcpy(rd, Register(rd));
        printf("%-9s%-5s%-5s%-5s\n", "subu", rd, rd, rt);
        return 1;
    }
    else return 0;
}
int JR(char code[]) {
    char special[10], jr[10];
    Initial_Str(special);
    Initial_Str(jr);
    for (int i = 0; i < 6; i++) special[i] = code[i];
    for (int i = 26; i < 32; i++) jr[i - 26] = code[i];
    special[6] = jr[6] = '\0';
    int judge;
    (strcmp(special, "000000") == 0 && strcmp(jr, "001000") == 0) ? judge = 1 : judge = 0;
    if (judge) {
        char rs[10];
        Initial_Str(rs);
        for (int i = 6; i < 11; i++) rs[i - 6] = code[i];
        rs[5] = '\0';
        strcpy(rs, Register(rs));
        printf("%-9s%-5s\n", "jr", rs);
        return 1;
    }
    else return 0;
}
int OR(char code[]) {
    char special[10], orr[10];
    Initial_Str(special);
    Initial_Str(orr);
    for (int i = 0; i < 6; i++) special[i] = code[i];
    for (int i = 26; i < 32; i++) orr[i - 26] = code[i];
    special[6] = orr[6] = '\0';
    int judge;
    (strcmp(special, "000000") == 0 && strcmp(orr, "100101") == 0) ? judge = 1 : judge = 0;
    if (judge) {
        char rs[10], rt[10], rd[10];
        Initial_Str(rs);
        Initial_Str(rt);
        Initial_Str(rd);
        for (int i = 6; i < 11; i++) rs[i - 6] = code[i];
        for (int i = 11; i < 16; i++) rt[i - 11] = code[i];
        for (int i = 16; i < 21; i++) rd[i - 16] = code[i];
        rs[5] = rt[5] = rd[5] = '\0';
        strcpy(rs, Register(rs));
        strcpy(rt, Register(rt));
        strcpy(rd, Register(rd));
        printf("%-9s%-5s%-5s%-5s\n", "or", rd, rs, rt);
        return 1;
    }
    else return 0;
}
int ORI(char code[]) {
    char ori[10];
    Initial_Str(ori);
    for (int i = 0; i < 6; i++) ori[i] = code[i];
    ori[6] = '\0';
    int judge;
    (strcmp(ori, "001101") == 0) ? judge = 1 : judge = 0;
    if (judge) {
        char rs[10], rt[10], imm[20];
        Initial_Str(rs);
        Initial_Str(rt);
        Initial_Str(imm);
        for (int i = 6; i < 11; i++) rs[i - 6] = code[i];
        for (int i = 11; i < 16; i++) rt[i - 11] = code[i];
        for (int i = 16; i < 32; i++) imm[i - 16] = code[i];
        rs[5] = rt[5] = imm[16] = '\0';
        strcpy(rs, Register(rs));
        strcpy(rt, Register(rt));
        printf("%-9s%-5s%-5s%-5d\n", "ori", rt, rs, BinToDec_Return(imm));
        return 1;
    }
    else return 0;
}
int LW(char code[]) {
    char lw[10];
    Initial_Str(lw);
    for (int i = 0; i < 6; i++) lw[i] = code[i];
    lw[6] = '\0';
    int judge;
    (strcmp(lw, "100011") == 0) ? judge = 1 : judge = 0;
    if (judge) {
        char base[10], rt[10], offset[20];
        Initial_Str(base);
        Initial_Str(rt);
        Initial_Str(offset);
        for (int i = 6; i < 11; i++) base[i - 6] = code[i];
        for (int i = 11; i < 16; i++) rt[i - 11] = code[i];
        for (int i = 16; i < 32; i++) offset[i - 16] = code[i];
        base[5] = rt[5] = offset[16] = '\0';
        strcpy(base, Register(base));
        strcpy(rt, Register(rt));
        printf("%-9s%-5s%d(%s)\n", "lw", rt, BinToDec_Return(offset), base);
        return 1;
    }
    else return 0;
}
int SW(char code[]) {
    char sw[10];
    Initial_Str(sw);
    for (int i = 0; i < 6; i++) sw[i] = code[i];
    sw[6] = '\0';
    int judge;
    (strcmp(sw, "101011") == 0) ? judge = 1 : judge = 0;
    if (judge) {
        char base[10], rt[10], offset[20];
        Initial_Str(base);
        Initial_Str(rt);
        Initial_Str(offset);
        for (int i = 6; i < 11; i++) base[i - 6] = code[i];
        for (int i = 11; i < 16; i++) rt[i - 11] = code[i];
        for (int i = 16; i < 32; i++) offset[i - 16] = code[i];
        base[5] = rt[5] = offset[16] = '\0';
        strcpy(base, Register(base));
        strcpy(rt, Register(rt));
        printf("%-9s%-5s%d(%s)\n", "sw", rt, BinToDec_Return(offset), base);
        return 1;
    }
    else return 0;
}
int BEQ(char code[]) {
    char beq[10];
    Initial_Str(beq);
    for (int i = 0; i < 6; i++) beq[i] = code[i];
    beq[6] = '\0';
    int judge;
    (strcmp(beq, "000100") == 0) ? judge = 1 : judge = 0;
    if (judge) {
        char rs[10], rt[10], offset[20];
        Initial_Str(rs);
        Initial_Str(rt);
        Initial_Str(offset);
        for (int i = 6; i < 11; i++) rs[i - 6] = code[i];
        for (int i = 11; i < 16; i++) rt[i - 11] = code[i];
        for (int i = 16; i < 32; i++) offset[i - 16] = code[i];
        rs[5] = rt[5] = offset[16] = '\0';
        strcpy(rs, Register(rs));
        strcpy(rt, Register(rt));
        printf("%-9s%-5s%-5s%-5d\n", "beq", rs, rt, BinToDec_Return(offset));
        return 1;
    }
    else return 0;
}
int LUI(char code[]) {
    char lui[10];
    memset(lui, '\0', sizeof(lui));
    for (int i = 0; i < 6; i++) lui[i] = code[i];
    lui[6] = '\0';
    int judge;
    (strcmp(lui, "001111") == 0) ? judge = 1 : judge = 0;
    if (judge) {
        char rt[10], imm[20];
        Initial_Str(rt);
        Initial_Str(imm);
        for (int i = 11; i < 16; i++) rt[i - 11] = code[i];
        for (int i = 16; i < 32; i++) imm[i - 16] = code[i];
        rt[5] = imm[16] = '\0';
        strcpy(rt, Register(rt));
        printf("%-9s%-5s%-5d\n", "lui", rt, BinToDec_Return(imm));
        return 1;
    }
    else return 0;
}
int JAL(char code[]) {
    char jar[10];
    Initial_Str(jar);
    for (int i = 0; i < 6; i++) jar[i] = code[i];
    jar[6] = '\0';
    int judge;
    (strcmp(jar, "000011") == 0) ? judge = 1 : judge = 0;
    if (judge) {
        char instr_index[30];
        Initial_Str(instr_index);
        for (int i = 6; i < 32; i++) instr_index[i - 6] = code[i];
        instr_index[26] = '\0';
        printf("%-9s%-10d\n", "jal", BinToDec_Return(instr_index));
        return 1;
    }
    else return 0;
}
int NOP(char code[]) {
    if (strcmp(code, "00000000000000000000000000000000") == 0) {
        puts("nop");
        return 1;
    }
    else return 0;
}
void ModifyCode(char code[], int raw_seq) {
    if (strlen(code) < 32) {
        int dif = 32 - strlen(code);
        char dif_zero[35];
        memset(dif_zero, '\0', sizeof(dif_zero));
        for (int i = 0; i < dif; i++) {
            dif_zero[i] = '0';
        }
        strcat(dif_zero, code);
        strcpy(raw[raw_seq], dif_zero);
    }
}
void Disassemble_MIPS_32() {
	puts("***      Open Source @ SprLau.github.io      ***"); 
    puts("Input Assembled Code, Double-Click Enter To End:");
    int lines = 0;
    fgets(raw[lines], 10, stdin);
    Trim_n(raw[lines]);
    while (strcmp(raw[lines], "\0") != 0) {
        lines++;
        fgets(raw[lines], 10, stdin);
        Trim_n(raw[lines]);
    }
    puts("MIPS Code:");
    for (int i = 0; i < lines; i++) {
        unsigned int tem = HexToDec(raw[i]);
        strcpy(raw[i], DecToBin_Return(tem));
        ModifyCode(raw[i], i);
        if (!(NOP(raw[i]) || ADDU(raw[i]) || SUBU(raw[i]) || JR(raw[i]) || OR(raw[i]) || ORI(raw[i]) || LW(raw[i]) || SW(raw[i]) || BEQ(raw[i]) || LUI(raw[i]) || JAL(raw[i]))) {
            printf("Not Supported: %s\n", raw[i]);
        }
    }    
}

int main(void) {
    Disassemble_MIPS_32();
	system("pause"); 
    return 0;
}
