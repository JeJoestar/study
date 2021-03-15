#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <conio.h>
#include <string.h>
#include <stdarg.h>
#include "functions.h"

struct SstdInfo {
	char cSurname[20];
	char cName[20];
	char cBirth[11];
	int nMarks[6];
	double nMarkAvg;
	struct SstdInfo *pNext;
};


int main()
{
	char cAnswer, cFileAdress[100], cFileString[100], cStrtokLimits[] = " ";
	char* pcStrtokPtr = NULL;
	int nStateFileChecker, nStudentCnt;
	struct SstdInfo* pHead = NULL, * pCur = (struct SstdInfo*)malloc(sizeof(struct SstdInfo));;
	FILE* pfOpenedFile = NULL;

	//CHOOSE1
  printf("Welcome to the lab011. Please, choose an option that you prefer: \n");
  printf("1)Bulid a table.\n0)Exit.\n>:");
  CorrectChooseOption(2, &cAnswer, '1', '0');
  switch (cAnswer) {
	case '1': {
	  printf("You have chosen \"Build a table\".\n");
	  break; 
	}
	case '0': {
	  free(pCur); ReplicWithExit(); return 0;
	}
  }
	//CHOOSE2
  printf("In what way you prefer to enter tha data?\n");
  printf("1)Keyboard.\n2).txt file.\n0)Exit.\n>:");
  CorrectChooseOption(3, &cAnswer, '1', '2', '0');
  switch (cAnswer) {
  case '1': {
	printf("Enter the info about student or enter \"end\", if you want to stop:\n>:");
	InsertStudentElementByKeyboard(cFileString, cStrtokLimits, pcStrtokPtr, pCur, &pHead, &nStudentCnt);
	PrintStudentTable(pCur, pHead, nStudentCnt);
	break;
	}
  case '2': {
	printf("Enter the file location. Example: D:\\file\\...\\file.txt\n>:");
	OpenFile(&pfOpenedFile, cFileAdress);
	InsertStudentElementFromFile(pfOpenedFile, cFileString, cStrtokLimits, pcStrtokPtr, pCur, &pHead, &nStudentCnt);
	PrintStudentTable(pCur, pHead, nStudentCnt);
	printf("Do you want to vanish students with two \"2\" marks?\n");
	printf("1)Yes.\n0)No.\n:>");
	CorrectChooseOption(2, &cAnswer, '1', '0');
	switch (cAnswer) {
	  case '1': {
	  VanishStudentWithTwoBadMarks(pCur, &pHead, &nStudentCnt);
	  PrintStudentTable(pCur, pHead, nStudentCnt);
	  break;
	  }
	  case '0': {
		break;
	  }
	}
	fclose(pfOpenedFile);
	break;
    }
    case '0': {
	  FreeMemmoryForStudentsList(pHead);
 	  ReplicWithExit();
	  return 0;
    }
  }
	//CHOOSE3
  do {
	printf("Anything else?\n");
	printf("1)Add an element by keyboard.\n2)Vanish vanish students with two \"2\" marks\n3)Save table. Exit.\n0)No.\n>:");
	CorrectChooseOption(4, &cAnswer, '1', '2', '3', '0');
	switch (cAnswer) {
	  case '1': {
		CreateElementAndInsertThisIntoList(cStrtokLimits, &pHead, &nStudentCnt);
		PrintStudentTable(pCur, pHead, nStudentCnt);
		break;
	  }
	  case '2': {
	    VanishStudentWithTwoBadMarks(pCur, &pHead, &nStudentCnt);
	    PrintStudentTable(pCur, pHead, nStudentCnt);
	    break;
	  }
	  case '3': {
		printf("Which file is it?\n");
		printf("1)New.\n0)Already created.\n:>");
		CorrectChooseOption(2, &cAnswer, '1', '0');
		switch (cAnswer) {
		  case '1': {
		    nStateFileChecker = 1;
		    break;
		  }
		  case '0': {
		    nStateFileChecker = 0;
		    break;
		  }
	    }
		printf("Enter the file location. Example: D:\\file\\...\\file.txt\n>:");
		do {
		  rewind(stdin);
		  scanf("%s", cFileAdress);
		} while (OpenFileForSave(&pfOpenedFile, cFileAdress, pCur, pHead, nStudentCnt, nStateFileChecker) == (-1));
		printf("File has been succesfully created. Table saved.");
		break;
	  }
	  case '0': {
		FreeMemmoryForStudentsList(pHead);
		ReplicWithExit();
		return 0;
	  }
	}
  } while (cAnswer == '0');
  return 0;
}