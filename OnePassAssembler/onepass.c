#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 30
// contents of input file along with mnemonic value and loc value stored in a structure called table
struct input
{
    char label[20], opcode[20], operand[20], mnemonic[25];
    int loc;
};
struct input table[MAX];
struct symtab
{
    char sym[10];
    int f, val, ref;
};
struct symtab symtbl[MAX];
void main()
{
    int f1, i = 1, j = 1, flag, locctr, x;
    char add[20], code[20], mnemcode[20];
    FILE *fp1, *fp2, *fp3, *fp4;
    fp1 = fopen("input1.txt", "r");
    fp2 = fopen("optab1.txt", "r");
    fp3 = fopen("spout.txt", "w");
    fp4 = fopen("symtab.txt", "w");
    /*if ( fp1 == NULL ) {printf("hai3\n");
    perror("Ups"); /* Show an error and exit}*/
    fscanf(fp1, "%s%s%s", table[i].label, table[i].opcode, table[i].operand);
    if (strcmp(table[i].opcode, "START") == 0)
    {
        locctr = atoi(table[i].operand);
        i++;
        fscanf(fp1, "%s%s%s", table[i].label, table[i].opcode, table[i].operand);
    }
    else
        locctr = 0;
    while (strcmp(table[i].opcode, "END") != 0)
    {
        if (strcmp(table[i].label, "**") != 0)
        {
            for (x = 1; x < j; x++)
            {
                f1 = 0;
                if ((strcmp(symtbl[x].sym, table[i].label) == 0) && (symtbl[x].f == 1))
                {
                    symtbl[x].val = locctr;
                    symtbl[x].f = 0;
                    table[symtbl[x].ref].loc = locctr;
                    f1 = 1;
                    break;
                }
            }
            if (f1 == 0)
            {
                strcpy(symtbl[j].sym, table[i].label);
                symtbl[j].val = locctr;
                symtbl[j].f = 0;
                j++;
            }
        }
        fscanf(fp2, "%s%s", code, mnemcode);
        while (strcmp(code, "END") != 0)
        {
            if (strcmp(table[i].opcode, code) == 0)
            {
                strcpy(table[i].mnemonic, mnemcode);
                locctr += 3;
                for (x = 1; x <= j; x++)
                {
                    flag = 0;
                    if (strcmp(table[i].operand, symtbl[x].sym) == 0)
                    {
                        flag = 1;
                        if (symtbl[x].f == 0)
                            table[i].loc = symtbl[x].val;
                        break;
                    }
                }
                if (flag != 1)
                {
                    strcpy(symtbl[j].sym, table[i].operand);
                    symtbl[j].f = 1;
                    symtbl[j].ref = i;
                    j++;
                }
            }
            fscanf(fp2, "%s%s", code, mnemcode);
        }
        rewind(fp2);
        if (strcmp(table[i].opcode, "WORD") == 0)
        {
            locctr += 3;
            strcpy(table[i].mnemonic, "\0");
            table[i].loc = atoi(table[i].operand);
        }
        else if (strcmp(table[i].opcode, "RESW") == 0)
        {
            locctr += (3 * (atoi(table[i].operand)));
            strcpy(table[i].mnemonic, "\0");
            table[i].loc = atoi("\0");
        }
        else if (strcmp(table[i].opcode, "RESB") == 0)
        {
            locctr += (atoi(table[i].operand));
            strcpy(table[i].mnemonic, "\0");
            table[i].loc = atoi("\0");
        }
        else if (strcmp(table[i].opcode, "BYTE") == 0)
        {
            ++locctr;
            if ((table[i].operand[0] == 'C') || (table[i].operand[0] == 'X'))
                table[i].loc = (int)table[i].operand[2];
            else
                table[i].loc = locctr;
        }
        i++;
        fscanf(fp1, "%s%s%s", table[i].label, table[i].opcode, table[i].operand);
    }
    for (x = 1; x <= i; x++)
    {
        sprintf(add, "%d", table[x].loc);
        fprintf(fp3, "%s\t%s\t%s\t%s\n", table[x].label, table[x].opcode, table[x].operand, strcat(table[x].mnemonic, add));
    }
    printf("\n\n symol table\n\n");
    for (x = 1; x < j; x++)
    {
        printf("%s\t%d\n", symtbl[x].sym, symtbl[x].val);
        fprintf(fp4, "%s\t%d\n", symtbl[x].sym, symtbl[x].val);
    }
}