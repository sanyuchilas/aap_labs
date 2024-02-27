#include <stdio.h>
#include <string.h>


typedef struct klass {
  char name[20];
  char klass_name;
  float ball;
} pupil;

void printPupil(const char* name, pupil* x)
{
	printf("%s: %s\t%c\t%.2f\n", name, x->name, x->klass_name, x->ball);
}

void printPupilArray(const char* name, pupil* x, int n)
{
	for(int i = 0; i < n; i++)
	{
		printPupil(name, x + i);
	}
}


int main()
{
	pupil a, b[3] = {{"Petrov Petr", 'B', 3.7}, {"Sidorov Sidor", 'C'}, {"Sergeev Sergey"}}, *c;
	printf("Input student name:");
	fgets(a.name, 19, stdin);
	if (a.name[strlen(a.name) - 1] == '\n')
	{
		a.name[strlen(a.name) - 1] = '\0';
	}
	printf("Input student class letter:");
	a.klass_name = getchar();
	printf("Input student gpa:");
	scanf("%f", &a.ball);
	printPupil("a", &a);
	c = &a;
	printPupil("*c", c);
	printPupilArray("b", b, 3);
	
	return 0;
}