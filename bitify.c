#include<stdio.h>
#include<utf8proc.h>

int argparse(int len, char **a, int *index)
{
	int i;
	int mode = 0;
	for (i=1; i<len; i++) {
		if (a[i][0] == '-') {
			(*index)++;
			if (a[i][1] == 'x')
				mode |= 1;
			else if (a[i][1] == 's')
				mode |= 2;
			else if (a[i][1] == 'h')
				mode |= 4;
		}
	}
	return mode;
}

void bitify(char *line, int mode)
{
	int i;
	while ((*line) != 0) {
		char c = (*line);
		char byte[8];
		for (i=0; i<8; i++)
			if ((c>>i) & 1)
				byte[7-i] = '1';
			else
				byte[7-i] = '0';
		line++;
		if (mode & 2)
			printf("%s ", byte);
		else
			printf("%s", byte);
	}
	char c = ' ';
	char byte[8];
	for (i=0; i<8; i++)
		if ((c>>i) & 1)
			byte[7-i] = '1';
		else
			byte[7-i] = '0';
	if (mode & 2)
		printf("%s ", byte);
	else
		printf("%s", byte);
}

void hexify(char *line, int mode)
{
	char hex[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
	int mask = 15;
	while ((*line) != 0) {
		char c = (*line);
		printf("%c", hex[(c>>4)&mask]);
		if (mode & 2)
			printf("%c ", hex[c&mask]);
		else
			printf("%c", hex[c&mask]);
		line++;
	}
	printf("%c", hex[(' '>>4)&mask]);
	if (mode & 2)
		printf("%c ", hex[' '&mask]);
	else
		printf("%c", hex[' '&mask]);
}

void usage()
{
	printf("bitify [options] The text to convert to binary\n");
	printf("Options:\n");
	printf("%3s - %s\n", "-x", "converts text to hex instead");
	printf("%3s - %s\n", "-s", "adds space between each letter");
	printf("%3s - %s\n", "-h", "shows this help menu");
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
	// mode 0 = bitify (default), mode 1 = hexify
	int i = 1;
	int mode = argparse(argc, argv, &i);
	if (mode & 4) {
		usage();
		return 0;
	}
	for (; i<argc; i++)
		if (mode & 1)
			hexify(argv[i], mode);
		else
			bitify(argv[i], mode);
	printf("\n");
	return 0;
}
