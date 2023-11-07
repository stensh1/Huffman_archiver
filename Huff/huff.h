// Orshak Ivan, 08.10.2016

#define _CRT_SECURE_NO_WARNINGS

#ifndef _HUFF_H_
#define _HUFF_H_

#include <stdio.h>

typedef struct tagTREE {
	int Symb;
	int Freq;
	struct tagTREE* Right;
	struct tagTREE* Left;
}TREE;

int Compress(char* FileInName, char* FileOutName);
int Decompress(char* FileInName, char* FileOutName);
#endif
