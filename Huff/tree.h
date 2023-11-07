// Orshak Ivan, 08.10.2016

#ifndef _TREE_H_
#define _TREE_H_

int CreateNodes(TREE* Nodes[], int* Freq, int* NumOfNodes);
void PrintTree(TREE* T, int level);
int BuildTree();
void BuildCodes(TREE* T, char Codes[][256], char* Code, int level);
void PrintCoef(char Codes[][256], int* Freq, TREE* Nodes[]);
void PrintCodes(char Codes[][256], int* Freq);

#endif