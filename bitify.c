#include<stdio.h>
#include<utf8proc.h>

#define HEX 1
#define SPACES 2
#define HELP 4
#define LAST_ARG 8

int argparse(int len, char **a, int *mode)
{
	int i;
	for (i=1; i<len; i++) {
		if (a[i][0] == '-') {
			if (a[i][1] == 'x') { // 00000001 == HEX
				(*mode) |= HEX;
			} else if (a[i][1] == 's') { // 00000010 == SPACES
				(*mode) |= SPACES;
			} else if (a[i][1] == 'h') { // 00000100 == HELP
				(*mode) |= HELP;
			}
		}
		else {
			return i;
		}
	}
	return i;
}

void bitify(char *line, int mode)
{
	int i;
	while ((*line) != 0) {
		char c = (*line);
		char byte[8];
		for (i=0; i<8; i++) {
			if ((c>>i) & 1) {
				byte[7-i] = '1';
			} else {
				byte[7-i] = '0';
			}
		}
		line++;
		printf("%s", byte);
		if (mode & SPACES) {
			printf(" ");
		}
	}
	
	if (!(mode & LAST_ARG)) {
		char c = ' ';
		char byte[8];
		for (i=0; i<8; i++) {
			if ((c>>i) & 1) {
				byte[7-i] = '1';
			} else {
				byte[7-i] = '0';
			}
		}
		
		printf("%s", byte);
		if (mode & SPACES) {
			printf(" ");
		}
	}
}

void hexify(char *line, int mode)
{
	char hex[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
	int mask = 15;
	while ((*line) != 0) {
		char c = (*line);
		printf("%c", hex[(c>>4)&mask]);
		if (mode & SPACES) {
			printf("%c ", hex[c&mask]);
		} else {
			printf("%c", hex[c&mask]);
		}
		line++;
	}
	
	if (!(mode & LAST_ARG)) {
		printf("%c", hex[(' '>>4)&mask]);
		printf("%c", hex[' '&mask]);
		if (mode & SPACES) {
			printf(" ");
		}
	}
}

void usage()
{
	printf("bitify [options] The text to convert to binary\n");
	printf("Options:\n");
	printf("%3s ~ %s\n", "-x", "converts text to hex instead");
	printf("%3s ~ %s\n", "-s", "adds space between each letter");
	printf("%3s ~ %s\n", "-h", "shows this help menu");
	printf("=== Examples ===\n");
	char *text = "cool prog";
	printf("bitify %s\n", text);
	bitify(text, 0);
	printf("\n---------\nbitify -x %s\n", text);
	hexify(text, 0);
	printf("\n---------\nbitify -x -s %s\n", text);
	hexify(text, 2);
	printf("\n== Examples end ==\n");
}

int main(int argc, char **argv)
{
	if (argc < 2) {
		usage();
		return 1;
	}
	int mode = 0;
	int i = argparse(argc, argv, &mode);
	if (mode & HELP) {
		usage();
		return 0;
	}
	for (; i<argc; i++) {
		if (i+1 == argc) {
			mode |= LAST_ARG; // 00001000 == LAST ARG
		}
		if (mode & 1) {
			hexify(argv[i], mode);
		} else {
			bitify(argv[i], mode);
		}
	}
	printf("\n");
	return 0;
}
