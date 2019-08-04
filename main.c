#include <error.h>
#include <stdint.h>
#include <stdio.h>

#define NDEBUG 1

FILE* fd;

uint8_t file_buffer[1024];
size_t file_read = 0;
size_t file_index = 0;

static void fatal(char* str)
{
	if (fd != NULL)
	{
		fclose(fd);
	}
	
	error(1, 0, "fatal: %s", str);
}

static uint8_t read_byte()
{
	if (file_index == file_read)
	{
		if (feof(fd) != 0)
		{
			return EOF;
		}
	
		file_read = fread(file_buffer, 1, 1024, fd);
	}
	
	return file_buffer[file_index++];	
}

static inline void unread_byte()
{
	file_index--;
}

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		fatal("incorrect number of arguments");
	}

	fd = fopen(argv[1], "r");

	if (fd == NULL)
	{
		fatal("can't open file");
	}

#ifndef NDEBUG
	char c;
	for (;;)
	{
		c = read_byte();
		
		if (c == EOF)
		{
			return 0;
		}

		printf("%c", c);
	}
#endif

	fclose(fd);	
	return 0;
}
