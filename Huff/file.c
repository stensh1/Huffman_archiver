// Orshak Ivan, 08.10.2016

#include "huff.h"
#include <stdio.h> 

int CountFreq(int* Freq, FILE* FIn)
{
	int tmp;

	while ((tmp = fgetc(FIn)) != EOF)
		Freq[tmp]++;

	rewind(FIn);

	return 0;
}

static void WriteBit(FILE* FOut, int Bit, int Freq)
{
	static int accum, pos;

	if (Freq == 0)
	{
		if (pos == 8)
		{
			fputc(accum, FOut);
			accum = pos = 0;

			return;
		}

		accum |= (Bit << pos++);
		fputc(accum, FOut);
	}
	else
	{
		if (pos == 8)
		{
			fputc(accum, FOut);
			accum = pos = 0;
		}

		accum |= (Bit << pos++);
	}

	return;
}

void WriteTable(int NumOfNodes, FILE* FOut, int* Freq)
{
	int i;

	fputc(NumOfNodes, FOut);

	for (i = 0; i < 256; i++)
		if (Freq[i] != 0)
		{
			fputc(i, FOut);
			fwrite(&Freq[i], sizeof(Freq[i]), 1, FOut);
		}

	return;
}

void Enñode(FILE* FIn, FILE* FOut, char Codes[][256], int Freq)
{
	int tmp;

	while ((tmp = fgetc(FIn)) != EOF)
	{
		int i = 0;

		Freq--;

		while (Codes[tmp][i] != 0)
			WriteBit(FOut, Codes[tmp][i++] - '0', Freq);
	}

	return;
}

void ReadTable(FILE* FIn, int* Freq)
{
	int Frequence, tmp;

	Frequence = fgetc(FIn);

	while (Frequence != 0)
	{
		tmp = fgetc(FIn);
		fread(&Freq[tmp], sizeof(int), 1, FIn);
		Frequence--;
	}

	return;
}

void Decode(FILE* FIn, TREE* Nodes[], FILE* FOut)
{
	int Byte, Bit, cnt;
	TREE* tmp;

	tmp = Nodes[0];

	cnt = Nodes[0]->Freq;

	while ((Byte = fgetc(FIn)) != EOF)
	{
		int pos = 0;

		while (pos != 8 && cnt > 0)
		{
			Bit = (Byte & (1 << pos)) >> pos;
			pos++;

			if (Bit == 1)
				tmp = tmp->Right;
			else
				tmp = tmp->Left;

			if (tmp->Left == NULL && tmp->Right == NULL)
			{
				fputc(tmp->Symb, FOut);
				cnt--;
				tmp = Nodes[0];
			}
		}
	}

	return;
}