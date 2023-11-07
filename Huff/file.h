// Orshak Ivan, 08.10.2016

#ifndef _FILE_H_
#define _FILE_H_

int CountFreq(int* Freq, FILE* FIn);
void WriteTable(int NumOfNodes, FILE* FOut, int* Freq);
void Enñode(FILE* FIn, FILE* FOut, char Codes[][256], int Freq);
void ReadTable(FILE* FIn, int* Freq);
void Decode(FILE* FIn, TREE* Nodes[], FILE* FOut);

#endif