#ifdef _WIN32
	#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

#define FILE_NAME "test.bin"

void createBinaryFile(const char *fName);
void printBinaryFile(const char *fName);
void deleteFirstMaxFromBinary(const char *fName);


int main()
{
	createBinaryFile(FILE_NAME);
	printBinaryFile(FILE_NAME);
	deleteFirstMaxFromBinary(FILE_NAME);
	printBinaryFile(FILE_NAME);

	return 0;
}

void createBinaryFile(const char *fName)
{
	FILE *f = fopen(fName, "wb");
	if (!f)
	{
		printf("File with name %s could not be open for write\n", fName);
		return;
	}
	int n = 0;
	printf("Input number of elements:");
	scanf("%d", &n);
	printf("Input %d double elements:", n);
	for (int i = 0; i < n; i++)
	{
		double element;
		scanf("%lf", &element);
		fwrite(&element, sizeof(double), 1, f);
	}
	fclose(f);
}

void printBinaryFile(const char *fName)
{
	FILE *f = fopen(fName, "rb");
	if (!f)
	{
		printf("File is not valid for print\n");
		return;
	}
	printf("File content:\n");
	rewind(f);
	while (!feof(f))
	{
		double element;
		fread(&element, sizeof(double), 1, f);
		if (!feof(f))
			printf("%lf\t", element);
	}
	printf("\n");
	fclose(f);
}

void deleteFirstMaxFromBinary(const char * fName)
{
	FILE *f = fopen(fName, "r+b");
	if (!f)
	{
		printf("File is not valid for proccessing\n");
		return;
	}
	rewind(f);
	double max;
	unsigned int maxIndex = 0, currIndex = 0;
	fread(&max, sizeof(double), 1, f);
	while (!feof(f))
	{
		double tmp;
		fread(&tmp, sizeof(double), 1, f);
		currIndex++;
		if (tmp > max)
		{
			max = tmp;
			maxIndex = currIndex;
		}
	}
	//printf("DEBUG max index = %d\n", maxIndex);
	fseek(f, (maxIndex + 1)*sizeof(double), SEEK_SET);
	while (!feof(f))
	{
		double tmp;
		if (!fread(&tmp, sizeof(double), 1, f))	break;
		//printf("DEBUG tmp = %lf\n", tmp);
		fseek(f, -2 * (long)sizeof(double), SEEK_CUR);
		fwrite(&tmp, sizeof(double), 1, f);
		fseek(f, sizeof(double), SEEK_CUR);
	}
	
	fseek(f, 0, SEEK_END);
	long curFileSize = ftell(f);

	#ifdef __unix__
		#include <unistd.h>
		int desc = fileno(f);
		ftruncate(desc, curFileSize - sizeof(double));
	#else
		#include <io.h>
		int desc = _fileno(f);
		_chsize(desc, curFileSize - sizeof(double));
	#endif

	fclose(f);
}