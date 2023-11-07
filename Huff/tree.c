// Orshak Ivan, 08.10.2016

#include "huff.h"
#include <stdlib.h>
#include <string.h>

static TREE* CreateNode(int Symb, int Freq, TREE* Left, TREE* Right)
{
	TREE* node = malloc(sizeof(TREE));

	if (node == NULL)
		return NULL;

	node->Symb = Symb;
	node->Freq = Freq;
	node->Left = Left;
	node->Right = Right;

	return node;
}

void InsertNode(TREE* Nodes[], TREE* Node, int* NumOfNodes)
{
	int i = 0;

	while ((Nodes[i] != NULL) && Nodes[i]->Freq >= Node->Freq)
		i++;

	if (Nodes[i] != NULL)
		memmove(Nodes + i + 1, Nodes + i, (*NumOfNodes - i) * sizeof(TREE*));

	Nodes[i] = Node;
	(*NumOfNodes)++;

	return;
}

int CreateNodes(TREE* Nodes[], int* Freq, int* NumOfNodes)
{
	int i;

	for (i = 0; i < 256; i++)
		if (Freq[i] != 0)
		{
			TREE* node = CreateNode(i, Freq[i], NULL, NULL);

			if (node == NULL)
				return 0;

			InsertNode(Nodes, node, NumOfNodes);
		}

	return 1;
}

int BuildTree(int NumOfNodes, TREE* Nodes[])
{
	TREE* Tree;

	while (NumOfNodes > 1)
	{
		TREE* left = Nodes[NumOfNodes - 1], * right = Nodes[NumOfNodes - 2];

		Tree = CreateNode(0, left->Freq + right->Freq, left, right);

		if (Tree == NULL)
			return 0;

		Nodes[NumOfNodes - 1] = Nodes[NumOfNodes - 2] = NULL;
		NumOfNodes -= 2;
		InsertNode(Nodes, Tree, &NumOfNodes);
	}

	return 1;
}

void PrintTree(TREE* T, int level)
{
	if (T != NULL)
	{
		PrintTree(T->Right, level + 1);
		printf("%*d,%d\n", level * 5, T->Symb, T->Freq);
		PrintTree(T->Left, level + 1);
	}

	return;
}

void BuildCodes(TREE* T, char Codes[][256], char* Code, int level)
{
	if (T->Left == NULL && T->Right == NULL)
		strncpy(Codes[T->Symb], Code, level);
	else
	{
		Code[level] = '0';
		BuildCodes(T->Left, Codes, Code, level + 1);
		Code[level] = '1';
		BuildCodes(T->Right, Codes, Code, level + 1);
	}

	return;
}

void PrintCoef(char Codes[][256], int* Freq, TREE* Nodes[])
{
	int sum = 0, i;

	for (i = 0; i < 256; i++)
		if (Freq[i] != 0)
			sum += (Freq[i] * strlen(Codes[i]));

	printf("Coef is %f", (float)sum / 8 / Nodes[0]->Freq);

	return;
}

void PrintCodes(char Codes[][256], int* Freq)
{
	int i;

	for (i = 0; i < 256; i++)
		if (Freq[i] != 0)
			printf("%c=%i - %s\n", i, i, Codes[i]);

	return;
}