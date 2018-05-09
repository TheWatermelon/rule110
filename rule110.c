#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*************************/
/* Author: TheWatermelon */
/* Last date: 2018-05-09 */
/*************************/

/**
 * copy_chars_from : copy source chars into destination 
 * (assuming destination is at least as long as source)
 * param source : source array
 * param dest : destination array
 */
void copy_chars_from(const char* source, char* dest) {
	for(int i=0; source[i]!=0; i++) {
		dest[i] = source[i];
	}
}

/**
 * rule110 : given an index in a sequence of 0s and 1s (char codes), 
 *           checks its neighbors and returns a char corresponding to the rule110
 *
 *                        Rule 110            
 * neighbors: 111 110 101 100 011 010 001 000 
 * output:     0   1   1   0   1   1   1   0  
 *
 * param sequence : the sequence array containing char codes of 0s and 1s
 * param index : an index within the sequence
 * returns : '0' or '1' according to rule110
 */
char rule110(char* sequence, int index) {
	int neighbors = 0;
	int seq_length = strlen(sequence);
	
	//printf("index: %d neighbors: ");

	/* left neighbor (cycle) */
	if(index-1 < 0) {
		//printf("%c", sequence[seq_length-1]);
		if(sequence[seq_length-1]=='1') { neighbors = neighbors | 0x4; }
	} else {
		//printf("%c", sequence[index-1]);
		if(sequence[index-1]=='1') { neighbors = neighbors | 0x4; }
	}
	/* center */
	//printf("%c", sequence[index]);
	if(sequence[index]=='1') { neighbors = neighbors | 0x2; }
	/* right neighbor (cycle) */
	if(index+1 > seq_length-1) {
		//printf("%c", sequence[0]);
		if(sequence[0]=='1') { neighbors = neighbors | 0x1; }
	} else {
		//printf("%c", sequence[index+1]);
		if(sequence[index+1]=='1') { neighbors = neighbors | 0x1; }
	}

	switch(neighbors) {
		case 0:
			//printf(" rule110: 0\n");
			return '0';
		case 1:
			//printf(" rule110: 1\n");
			return '1';
		case 2:
			//printf(" rule110: 1\n");
			return '1';
		case 3:
			//printf(" rule110: 1\n");
			return '1';
		case 4:
			//printf(" rule110: 0\n");
			return '0';
		case 5:
			//printf(" rule110: 1\n");
			return '1';
		case 6:
			//printf(" rule110: 1\n");
			return '1';
		case 7:
			//printf(" rule110: 0\n");
			return '0';
		default:
			//printf(" rule110: 0\n");
			return '0';
	}
}

void main(int argc, const char** argv) 
{
	int iterations = 0;
	/* checking args */
	if(argc < 3) {
		printf("Usage: %s <sequence of 0s and 1s> <iterations>\n", argv[0]);
		return;
	} else {
		/* checking sequence contains only 0s and 1s */
		for(int i=0; argv[1][i]!=0; i++) {
			if(argv[1][i] != '0' &&
					argv[1][i] != '1') {
				printf("Wrong argument! Must be a sequence of 0s and 1s (ex. 01101110)\n");
				return;
			}
		}
		/* getting iterations count */
		/* if argv[2] isn't a number, there will be 0 iteration */
		iterations = atoi(argv[2]);
	}

	char* seq = malloc(strlen(argv[1]));
	char* next_seq = malloc(strlen(argv[1]));
	/* initializing seq from argv[1] */
	copy_chars_from(argv[1], seq); 

	/* starting loop */
	printf("%s\n", seq);
	while(iterations>0) {
		/* iterating through seq */
		for(int i=0; seq[i]!=0; i++) {
			/* generating next sequence */
			next_seq[i] = rule110(seq, i);
		}
		printf("%s\n", next_seq);
		/* replacing seq by next_seq */
		copy_chars_from(next_seq, seq);

		iterations--;
	}

	/* liberating the arrays */
	free(seq);
	free(next_seq);
}
