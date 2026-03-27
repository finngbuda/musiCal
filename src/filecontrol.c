#include "filecontrol.h"

FILE * write_wave(char * name, uint8_t * data, uint32_t dlen){

	FILE * outWav = fopen(name, "wb");

	write_header(outWav, dlen);

	write_audio(outWav, data);

	return outWav;
}

void write_header(FILE * file, uint32_t dlen){

	
}
