/*
DESCRIPTION: LC-3 assembler
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
	fp = fopen(argv[1], "r");
	while (fgets(buff, 255, fp) != NULL) 
	{
		if (buff[0] == '.') 
		{
			continue;
		}
		char *opcode = strtok(buff, sep);
		char *phrase;
		int i = 0;
		while ((phrase = strtok(NULL, sep)) != NULL) 
		{
			sscanf(phrase, "r%d", &operands[i++]);
		}
		int instruc = 0;
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
		}
		printf("%x\n", instruc);
	}
}