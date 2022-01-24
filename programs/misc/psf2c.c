/*
	@author : eltertrias
	@brief : converts PSF fonts into a C array for OSdev and microcontrollers
*/


#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "include/psf.h"


#define ERROR_TYPE_NORMAL 1
#define ERROR_TYPE_NONEXIT 2


size_t width;
size_t height;
size_t glyph_count;

uint8_t psf_version;
struct psf1_header psfInfo;


int outputError(uint8_t type, const char* error, ...)
{
	va_list args;
	va_start(args, error);

	#ifdef __linux__
	fprintf(stderr, "\033[1;31m");	// Change terminal text color to red - !!only next printed thing would be red!!
	#endif

	if (error == NULL)
	{
		fprintf(stderr, "Internal problem: wrong error output arguments");
		va_end(args);
		exit(EXIT_FAILURE);
	}

	fprintf(stderr, "Error: ");
	vfprintf(stderr, error, args);
	fprintf(stderr, "\n");

	va_end(args);
	if (type == ERROR_TYPE_NORMAL)
		exit(EXIT_FAILURE);
	return -1;
}

int getPSFinfo(FILE* fd)
{
	unsigned char magic[4];

	if (fread(magic, sizeof(unsigned char), 4, fd) == 0)
		return outputError(ERROR_TYPE_NONEXIT, "Failed to read file");

	if (PSF2_MAGIC_OK(magic))
		return outputError(ERROR_TYPE_NONEXIT, "Unsupported version: PSF2 v0");
	else if (PSF1_MAGIC_OK(magic))
	{
		rewind(fd);
		fread(&psfInfo, sizeof(struct psf1_header), 1, fd);
		psf_version = 1;

		height = psfInfo.charsize;
		width = 8;					// All PSF1 fonts have one byte width
		glyph_count = 256;
	}

	return 0;
}

int glyphsIntoArray(FILE* fd)
{
	uint8_t glyph[(height * width) / 8];

	printf("uint8_t* glyphs[] = \n"
	"{\n");

	for (size_t i = 0; i < 256; i++)
	{
		if (fread(&glyph, sizeof(uint8_t), (height * width) / 8, fd) == 0 && !feof(fd))
			outputError(ERROR_TYPE_NONEXIT, "Can't read the glyph");

		printf("\t{");
		for (size_t i = 0; i < ((height * width) / 8); i++)
			printf("0x%x,", glyph[i]);
		printf("},\n");
	}

	printf("};");

	return 0;
}

int main(int argc, char* argv[])
{
	if (argc == 1)
		outputError(ERROR_TYPE_NORMAL, "Not enough arguments supplied");

	FILE* fd = fopen(argv[1], "rb");
	if (fd == NULL)
		outputError(ERROR_TYPE_NORMAL, "Can not open the file");

	if (getPSFinfo(fd) == -1)
	{
		fclose(fd);
		exit(EXIT_FAILURE);
	}

	glyphsIntoArray(fd);

	fclose(fd);
	return 0;
}