#include "filecontrol.h"

// small func to make writing the header easier
void write_string(char * charbuf, FILE * file){
	
	fwrite(charbuf, strlen(charbuf), 1, file);

}

// generates out file
int write_wave(char * name, uint8_t * data, uint32_t dlen){

	FILE * outWav = fopen(name, "wb");

	write_header(outWav, dlen);

	fwrite(data, 1, dlen, outWav);

	fclose(outWav);

	return 0;
}


// writes header info so it will be read properly,
// will fix up at some point, lots of magic numbers
void write_header(FILE * file, uint32_t dlen){

	char chunkID[4] = {'R', 'I', 'F', 'F'};
	write_string(chunkID, file);

	uint32_t chunk_size = dlen + 44;
	fwrite(&chunk_size, 4, 1, file);

	char wave[4] = {'W', 'A', 'V', 'E'};
	write_string(wave, file);

	char fmt[4] = {'f', 'm', 't', ' '};
	write_string(fmt, file);

	uint32_t fmt_size = 16;
	fwrite(&fmt_size, 4, 1, file);

	uint32_t format_channel = 0x00010001;
	fwrite(&format_channel, 4, 1, file);

	uint32_t sample_rate = 44100;
	fwrite(&sample_rate, 4, 1, file);

	uint32_t byte_rate = (sample_rate * 2); // since it's one 16 bit channel, 2 bytes per sample
	fwrite(&format_channel, 4, 1, file);

	uint32_t align_bits = 0x00020010;
	fwrite(&align_bits, 4, 1, file);

	char dataID[4] = {'d', 'a', 't', 'a'};
	write_string(fmt, file);

	fwrite(&dlen, 4, 1, file);

}
