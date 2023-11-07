// Orshak Ivan, 08.10.2016

#include "huff.h"
#include "tree.h"
#include "file.h"
#include <conio.h>

static void PrintFreq(int* Freq)
{
	int i;

	for (i = 0; i < 256; i++)
		if (Freq[i] != 0)
			printf("%i, ", Freq[i]);
}

static PrintNodes(TREE* Nodes[], int NumOfNodes)
{
	int i;

	for (i = 0; i < 256; i++)
		if (Nodes[i] != 0)
			PrintTree(Nodes[i], 0);
}

int Compress(char* FileInName, char* FileOutName)
{
	int Freq[256] = { 0 };
	TREE* Nodes[256] = { 0 };
	char Codes[256][256] = { 0 }, Code[256] = { 0 };
	int NumOfNodes = 0;
	FILE* FIn, * FOut;

	if ((FIn = fopen("data.in", "rb")) == NULL)
		return 0;

	if ((FOut = fopen("data.huf", "wb")) == NULL)
	{
		fclose(FIn);
		return 0;
	}

	printf("\n-=Compress=-\n");
	
	CountFreq(Freq, FIn);
	printf("Frequences:\n");
	PrintFreq(Freq);

	printf("\n\n");
	CreateNodes(Nodes, Freq, &NumOfNodes);
	printf("Nodes:\n");
	PrintNodes(Nodes, NumOfNodes);

	printf("\n\n");

	BuildTree(NumOfNodes, Nodes);
	printf("My tree:\n\n");
	PrintTree(*Nodes, 0);

	printf("\n\n");

	BuildCodes(Nodes[0], Codes, Code, 0);

	PrintCoef(Codes, Freq, Nodes);
	printf("\n\n");

	printf("Codes:\n");
	PrintCodes(Codes, Freq);

	WriteTable(NumOfNodes, FOut, Freq);
	Encode(FIn, FOut, Codes, Nodes[0]->Freq);

	fclose(FIn);
	fclose(FOut);

	return 0;
}

int Decompress(char* FileInName, char* FileOutName)
{
	int Freq[256] = { 0 };
	TREE* Nodes[256] = { 0 };
	int NumOfNodes = 0;
	FILE* FIn, * FOut;

	if ((FIn = fopen("data.huf", "rb")) == NULL)
		return 0;

	if ((FOut = fopen("data.out", "wb")) == NULL)
	{
		fclose(FIn);
		return 0;
	}

	printf("\n-=Decompress=-\n");
	
	ReadTable(FIn, Freq);
	printf("Frequences:\n");
	PrintFreq(Freq);

	CreateNodes(Nodes, Freq, &NumOfNodes);
	printf("\n\nNodes:\n");
	PrintNodes(Nodes, NumOfNodes);

	BuildTree(NumOfNodes, Nodes);
	printf("\n\nMy tree:\n\n");
	PrintTree(*Nodes, 0);

	Decode(FIn, Nodes, FOut);

	fclose(FIn);
	fclose(FOut);

	_getch();

	return 0;
}
