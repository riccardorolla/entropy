#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define SIZE 256

float entropy_calc(long byte_count[], int length)
{
	float entropy=0;
	float count;
	int i;

	/* entropy calculation */
	for (i = 0; i < SIZE; i++)
	{
		if (byte_count[i] != 0)
		{
			count = (float)byte_count[i] / (float)length;
			entropy += -count * log2f(count);
		}
	}
	return entropy;
}

int main(int argc, char **argv)
{
	FILE            *inFile;
	size_t             n;              // Bytes read by fread;
	unsigned int				pos = 0;
	int             i;
	int             j;

	unsigned long length=0;         // length of file
	float           count;
	float           entropy=0;
	
	char *			buffer;


	/* do this for all files */
	if (argc <= 2) {
		printf("entropy segment_size filename1 [filename2] ... [filename3]");
		exit(1);
	}  //otherwise continue on our merry way....
	size_t segment = atoi(argv[1])*1.0;  //argv[0] is the program name
							   //atoi = ascii to int
	if (segment == 0) {
		printf("entropy segment_size filename1 [filename2] ... [filename3]");
		exit(1);
		 
	}
	 


	for (j = 2; j < argc; j++)
	{
		

		inFile = fopen(argv[j], "rb");    // opens the file given on command line

		if (inFile == NULL)                // error-checking to see if file exists
		{
			printf("Files does not exist. `%s`\n", argv[j]);
			continue;
		}
		buffer = (char *)malloc(sizeof(char)*segment);
	
		while ((n = fread(buffer, sizeof(char), segment, inFile)) != 0)
		{
		
	 
			/* Add the buffer to the byte_count */
			long            byte_count[SIZE];
			memset(byte_count, 0, sizeof(long) * (SIZE));
		    for (i = 0; i < n; i++)
			{
				 
					byte_count[(unsigned char)buffer[i]]++;
				 
				 
					  length++;
			} 
 
			 pos = pos + n;
 
	 
			float entropy = entropy_calc(byte_count, length);
			printf("%s,%i,%i,%02.5f   \n", argv[j], pos-n,pos, entropy);

			 
			entropy = 0;
			length = 0;
	
		}
		
	     
		fclose(inFile);


	}
	return 0;
}