// Orshak Ivan, 08.10.2016

#include "huff.h"

int main()
{
	Compress("data.in", "data.huf");
	Decompress("data.huf", "data.out");

	return 0;
}