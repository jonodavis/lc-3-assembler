/*
DESCRIPTION: implementation of .fill
AUTHOR: Jono Davis 
DATE: 10/17
*/

#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) 
{
	FILE *fp;
	char buff[255];
	char *sep = ", ";
	int operands[3];
	int imm;
	fp = fopen(argv[1], "r");
	int haltReached = 0;
	int instrucCount = 0;

	// SYMBOL TABLE
	FILE *fp2;
	fp2 = fopen("SymbolTable", "w");

	while (fgets(buff, 255, fp) != NULL) 
	{
		if (buff[0] == '.') 
		{
			int orig;
			if (sscanf(buff, ".orig x%x", &orig) != 0)
			{
				instrucCount = orig;
			}
			continue;
		}
		char *opcode = strtok(buff, sep);
		char *phrase;
		int i = 0;
		imm = 0;
		while ((phrase = strtok(NULL, sep)) != NULL) 
		{
			if (phrase[0] == 'r')
			{
				sscanf(phrase, "r%d", &operands[i++]);
				imm = 0;
			}
			else if (phrase[0] == '#')
			{
				sscanf(phrase, "#%d", &operands[i++]);
				imm = 1;
			}
		}
		if (haltReached == 1)
		{
			fprintf(fp2, "%s %x\n", opcode, instrucCount);
			instrucCount++;
		}
		else
		{
			int instruc = 0;
			if (imm == 0)
			{
				if (strcmp(opcode, "add") == 0)
				{
					instruc |= 0x1 << 0xc;
					instruc |= operands[0] << 0x9;
					instruc |= operands[1] << 0x6;
					instruc |= operands[2];
				}
				else if (strcmp(opcode, "and") == 0)
				{
					instruc |= 0x5 << 0xc;
					instruc |= operands[0] << 0x9;
					instruc |= operands[1] << 0x6;
					instruc |= operands[2];
				}
				else if (strcmp(opcode, "halt\n") == 0)
				{
					instruc |= 0xf << 0xc;
					instruc |= 0x25;
					haltReached = 1;
				}
				else if (strcmp(opcode, "jmp") == 0)
				{
					instruc |= 0xc << 0xc;
					instruc |= operands[0] << 0x6;
				}
			}
			else if (imm == 1)
			{
				if (strcmp(opcode, "add") == 0)
				{
					instruc |= 0x1 << 0xc;
					instruc |= operands[0] << 0x9;
					instruc |= operands[1] << 0x6;
					instruc |= 0x1 << 0x5;
					instruc |= operands[2] & 0x1f;

				}
				else if (strcmp(opcode, "and") == 0)
				{
					instruc |= 0x5 << 0xc;
					instruc |= operands[0] << 0x9;
					instruc |= operands[1] << 0x6;
					instruc |= 0x1 << 0x5;
					instruc |= operands[2] & 0x1f;
				}
			}
			instrucCount++;
			printf("%x\n", instruc);
		}
	}
	fclose(fp);
	fclose(fp2);
}