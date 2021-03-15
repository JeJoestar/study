#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

int main()
{
	char ans;
	printf("Welcome to the lab011. Please, choose an option that you prefer: \n");
	printf("1)Bulid a table.\n0)Exit.\n");
	scanf("%c", &ans);
	switch (ans)
	{
	case '1': printf("You have chosen \"Build a table\".\n");
			break;
		case '0': return 0;
	}
	printf("In what way you prefer to enter tha data?\n");
	printf("1)Keyboard.\n2)txt-file.\n0)Exit.\n");
	rewind(stdin);
	scanf("%c", &ans);
	switch (ans)
	{
	case '1': printf("You have chosen \"Keyboard\".\n");

		break;
	case '2': printf("You have chosen \"txt-file\".\n");
		break;
	case '0': return 0;
	}
	return 0;
}