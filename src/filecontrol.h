#include <stdio.h>
#include <string.h>
#include <stdint.h>

//creates a new wave file attaching accurate header and audio data
int write_wave(char * name, uint8_t * data, uint32_t dlen);

//attaches all header data
void write_header(FILE * file, uint32_t dlen);

//sequentially writes the audio data to file
void write_audio(FILE * file, uint8_t * data);


