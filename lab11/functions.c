#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <conio.h>
#include <ctype.h>
#include <string.h>
#include <stdarg.h>
#include "functions.h"
#define NUM_AMOUNT_OF_MARKS 6
#define NUM_WIDTH_OF_TABLE 128

struct SstdInfo {
	char chSurname[20];
	char chName[20];
	char chBirth[11];
	int nMarks[6];
	double nMarkAvg;
	struct SstdInfo *pNext;
};
//-------------------------------------------------------------------------------
//Вставляє елемент в початок списку та призначає його головою
//
void PushElementBeforeHead(struct SstdInfo *pCurStudent, struct SstdInfo **pHeadStudent) {
  (pCurStudent)->pNext = (*pHeadStudent);
  (*pHeadStudent) = pCurStudent;
}
//-------------------------------------------------------------------------------
//Визначення місця в списку для вставки елемента за середнім балом студентів 
//
void SortElement(struct SstdInfo *pCur, struct SstdInfo **ppHead) {
  if ((pCur)->nMarkAvg < (*ppHead)->nMarkAvg) {
	PushElementBeforeHead(pCur, ppHead);
  } else {
	struct SstdInfo *pSkippedElement = (*ppHead);
	struct SstdInfo *pSkipppeElementNext = pSkippedElement->pNext;
	if (pSkipppeElementNext) {
	  while (1) {
	    if ((pCur)->nMarkAvg < pSkipppeElementNext->nMarkAvg) {
		  InsertElementIntoList(pCur, &pSkippedElement);
		  break;
		} else {
		  if (pSkipppeElementNext->pNext) {
			pSkippedElement = pSkipppeElementNext;
			pSkipppeElementNext = pSkipppeElementNext->pNext;
		  } else {
			break;
		  }
		}
	  }
    }
  }
}
//-------------------------------------------------------------------------------
//Ініціалізує вставку елемента в список на місце визначене функцією sort
//
void InsertElementIntoList(struct SstdInfo* pCurStudent, struct SstdInfo** ppSkiped) {
	struct SstdInfo* pTmpStudent;
	pTmpStudent = (*ppSkiped)->pNext;
	(*ppSkiped)->pNext = (pCurStudent);
	(pCurStudent)->pNext = pTmpStudent;
}
//-------------------------------------------------------------------------------
//
//Перевірка дотримання формату вводу в стрічці для зчитування даних в елемент 
//списку
//
int StringFormatCheck(char chDataString[]) {
	char* pchStrtokPtr = NULL;
	char chDataStringCpy[100];
	strcpy(chDataStringCpy, chDataString);
	char chTestSurname[20], chTestName[20], chTestBirth[11], chStrtokLimits[] = " ";
	int nTestMarks[6];
	pchStrtokPtr = strtok(chDataStringCpy, chStrtokLimits);
	strcpy(chTestSurname, pchStrtokPtr);
	for (int i = 0; i < strlen(pchStrtokPtr); i++) {
		if (!isalpha(chTestSurname[i])) {
			return 1;
		}
	}
	pchStrtokPtr = strtok(NULL, chStrtokLimits);
	strcpy(chTestName, pchStrtokPtr);
	for (int i = 0; i < strlen(pchStrtokPtr); i++) {
		if (!isalpha(chTestName[i])) {
			return 1;
		}
	}
	pchStrtokPtr = strtok(NULL, chStrtokLimits);
	strcpy(chTestBirth, pchStrtokPtr);
	if (strlen(chTestBirth) < 10) {
		return 1;
	}
	else {
		for (int i = 0; i < 10; i++) {
			if (i == 2 || i == 5) {
				if (chTestBirth[i] != '.') {
					return 1;
				}
			}
			else {
				if (!isdigit(chTestBirth[i])) {
					return 1;
				}
			}
		}
	}
	for (int j = 0; j < NUM_AMOUNT_OF_MARKS; j++) {
		pchStrtokPtr = strtok(NULL, chStrtokLimits);
		if (isdigit(*pchStrtokPtr)) {
			nTestMarks[j] = atoi(pchStrtokPtr);
		}
		else {
			return 1;
		}
	}
	return 0;
}
//-------------------------------------------------------------------------------
//Зчитування списку з текстового файлу
//
void InsertStudentElementFromFile(
	FILE *pfOpenedFile,
	char chFileString[], 
	char chStrtokLimits[], 
	char *pchStrtokPtr, 
	struct SstdInfo *pCur, 
	struct SstdInfo **ppHead, 
	int *pnStudentsCnt) {
  static sEnters = 0;
  int nStudentCnt = sEnters;
  while (fgets(chFileString, 100, pfOpenedFile)) {
	  if (StringFormatCheck(chFileString) == 1) {
		  printf("\nError. Incorrect format of data. Try again.\n");
		  continue;
	  }
	pchStrtokPtr = strtok(chFileString, chStrtokLimits);
	strcpy(pCur->chSurname, pchStrtokPtr);
	pchStrtokPtr = strtok(NULL, chStrtokLimits);
	strcpy(pCur->chName, pchStrtokPtr);
	pchStrtokPtr = strtok(NULL, chStrtokLimits);
	strcpy(pCur->chBirth, pchStrtokPtr);
	pCur->nMarkAvg = 0;
	for (int j = 0; j < NUM_AMOUNT_OF_MARKS; j++) {
	  pchStrtokPtr = strtok(NULL, chStrtokLimits);
	  pCur->nMarks[j] = atoi(pchStrtokPtr);
	  pCur->nMarkAvg += pCur->nMarks[j];
	}
	pCur->nMarkAvg = pCur->nMarkAvg / NUM_AMOUNT_OF_MARKS;
	nStudentCnt++;
	if (!(*ppHead)) {
	  (*ppHead) = pCur;
	}
	if (pCur != (*ppHead)) {
		  SortElement(pCur, ppHead);
	}
	struct SstdInfo *pNextStudent = (struct SstdInfo*)malloc(sizeof(struct SstdInfo));
	pCur = (*ppHead);
	for (int k = 0; k < nStudentCnt - 1; k++)
	{
	  if (pCur->pNext) {
	    pCur = pCur->pNext;
	  }
	}
	pNextStudent->pNext = NULL;
	pCur->pNext = pNextStudent;
	pCur = pNextStudent;
  }
  *pnStudentsCnt = nStudentCnt;
  sEnters = sEnters + 1;
}
//-------------------------------------------------------------------------------
//Створення списку студентів за допомогою зчитування з клавіатури
//
void InsertStudentElementByKeyboard(
	char chFileString[], 
	char chStrtokLimits[],
	char *pchStrtokPtr,
	struct SstdInfo *pCurStudent, 
	struct SstdInfo **pHeadStudent,
	int *pnStudentCnt) {
  static sEnters = 0;
  int nStudentCnt = sEnters;
  while (1) {
	printf(">:");
	rewind(stdin);
	fgets(chFileString, 100, stdin);
	if (strstr(chFileString, "end")) {
	  break;
	}
	if (StringFormatCheck(chFileString) == 1) {
	  printf("Error. Incorrect format of data. Try again.\n");
	  continue;
	}
	pchStrtokPtr = strtok(chFileString, chStrtokLimits);
	strcpy(pCurStudent->chSurname, pchStrtokPtr);
	pchStrtokPtr = strtok(NULL, chStrtokLimits);
	strcpy(pCurStudent->chName, pchStrtokPtr);
	pchStrtokPtr = strtok(NULL, chStrtokLimits);
	strcpy(pCurStudent->chBirth, pchStrtokPtr);
	pCurStudent->nMarkAvg = 0;
	for (int j = 0; j < 6; j++) {
	  pchStrtokPtr = strtok(NULL, chStrtokLimits);
	  pCurStudent->nMarks[j] = atoi(pchStrtokPtr);
	  pCurStudent->nMarkAvg += pCurStudent->nMarks[j];
	}
	pCurStudent->nMarkAvg = pCurStudent->nMarkAvg / 6;
	nStudentCnt++;
	if (!(*pHeadStudent)) {
	  (*pHeadStudent) = pCurStudent;
	}
	if (pCurStudent != (*pHeadStudent)) {
	  SortElement(pCurStudent, pHeadStudent);
	}
	struct SstdInfo *pNextStudent = (struct SstdInfo*)malloc(sizeof(struct SstdInfo));
	pCurStudent = (*pHeadStudent);
	for (int k = 0; k < nStudentCnt - 1; k++) {
		if (pCurStudent->pNext) {
			pCurStudent = pCurStudent->pNext;
		}
	}
	pNextStudent->pNext = NULL;
	pCurStudent->pNext = pNextStudent;
	pCurStudent = pNextStudent;
  }
    *pnStudentCnt = nStudentCnt;
    sEnters = sEnters + 1;
}
//-------------------------------------------------------------------------------
//Друк меж таблиці
//
void PrintTableLines()
{
  for (int j = 0; j < NUM_WIDTH_OF_TABLE; j++) {
    printf("=");
  }
}
//-------------------------------------------------------------------------------
//Друк списку студентів у вигляді таблиці
//
void PrintStudentTable(
	struct SstdInfo *pStartFrom,
	struct SstdInfo *pHeadStudent,
	int nStudentCnt) {
  pStartFrom = pHeadStudent;
  PrintTableLines();
  printf("\n|%-20s\t|%-20s\t|%-10s\t| %-5s | %-5s | %-5s | %-5s | %-5s | %-5s | %-5s |\n",
      "Surname", 
	  "Name",
	  "Birthday",
	  "LAAG",
	  "English", 
	  "MathAn",
	  "CDM",
	  "BP",
	  "History", 
	  "Average");
  PrintTableLines();
  for (int j = 0; j < nStudentCnt; j++) {
	printf("\n|%-20s\t|%-20s\t|%-10s\t| %-5d | %-7d | %-6d | %-5d | %-5d | %-7d | %-7.2lf |\n",
		pStartFrom->chSurname,
		pStartFrom->chName,
		pStartFrom->chBirth,
		pStartFrom->nMarks[0],
		pStartFrom->nMarks[1],
		pStartFrom->nMarks[2],
		pStartFrom->nMarks[3],
		pStartFrom->nMarks[4],
		pStartFrom->nMarks[5],
		pStartFrom->nMarkAvg);
	pStartFrom = pStartFrom->pNext;
  }
  PrintTableLines();
  printf("\n");
}
//-------------------------------------------------------------------------------
//Видалення студентів зі списку з наявністю двох двійок серед оцінок
//
void VanishStudentWithTwoBadMarks(
	struct SstdInfo *pCurStudent,
	struct SstdInfo **ppHeadStudent,
	int *pnStudentCnt) {
  struct SstdInfo *pPrevStudent = NULL;
  int nMarksTwo = 0;
  int nChangeCheck = 0;
  pCurStudent = *ppHeadStudent;
  while (pCurStudent->pNext)
  {
  	for (int j = 0; j < NUM_AMOUNT_OF_MARKS; j++) {
  	  if (pCurStudent->nMarks[j] == 2) {
		nMarksTwo++;
	  }
	}
	if (nMarksTwo == 2) {
	  if (pCurStudent == *ppHeadStudent) {
		*ppHeadStudent = pCurStudent->pNext;
	  } else {
		  pPrevStudent->pNext = pCurStudent->pNext;
	  	  nChangeCheck++;
	  }
	  (*pnStudentCnt)--;
	}
	if (!nChangeCheck) {
	  pPrevStudent = pCurStudent;
	}
	pCurStudent = pCurStudent->pNext;
	nChangeCheck = 0;
	nMarksTwo = 0;
  }
}
//-------------------------------------------------------------------------------
//Звільнення динамічної пам'яті, виділеної під список студентів
//
void FreeMemmoryForStudentsList(struct SstdInfo *pHeadStudent) {
  struct SstdInfo* pTmpStudent;
  while (pHeadStudent != NULL) {
	pTmpStudent = pHeadStudent;
	pHeadStudent = pHeadStudent->pNext;
	free(pTmpStudent);
  }
}
//-------------------------------------------------------------------------------
//Створення нового елементу та вставка його в список одразу із сортуванням
//
void CreateElementAndInsertThisIntoList(
	char chStrtokLimits[],
	struct SstdInfo **ppHeadStudent,
	int *nStudentCnt) {
  struct SstdInfo *pNewInsertedElement = (struct SstdInfo*)malloc(sizeof(struct SstdInfo));
  char cInfoString[100];
  char *cStrTokPtr;
  printf("\nEnter the info about student: ");
  rewind(stdin);
  fgets(cInfoString, 100, stdin);
  cStrTokPtr = strtok(cInfoString, chStrtokLimits);
  strcpy(pNewInsertedElement->chSurname, cStrTokPtr);
  cStrTokPtr = strtok(NULL, chStrtokLimits);
  strcpy(pNewInsertedElement->chName, cStrTokPtr);
  cStrTokPtr = strtok(NULL, chStrtokLimits);
  strcpy(pNewInsertedElement->chBirth, cStrTokPtr);
  pNewInsertedElement->nMarkAvg = 0;
  for (int j = 0; j < NUM_AMOUNT_OF_MARKS; j++) {
	cStrTokPtr = strtok(NULL, chStrtokLimits);
 	pNewInsertedElement->nMarks[j] = atoi(cStrTokPtr);
	pNewInsertedElement->nMarkAvg += pNewInsertedElement->nMarks[j];
  }
  pNewInsertedElement->nMarkAvg = pNewInsertedElement->nMarkAvg / 6;
  SortElement(pNewInsertedElement, ppHeadStudent);
  (*nStudentCnt)++;
}
//-------------------------------------------------------------------------------
//Відкриття файлу для зчитування списку студентів
//
void OpenFile(FILE **ppfFilePtr, char chFileAdress[]) {
  while (1)
  {
	rewind(stdin);
	scanf("%s", chFileAdress);
	*ppfFilePtr = fopen(chFileAdress, "r+");
	if (*ppfFilePtr == NULL) {
	  printf("Error. File cannot be opened correctly.\n");
	  printf("Try again\n>:");
	} else {
	  break;
	}
  }
}
//-------------------------------------------------------------------------------
//Вивід фрази, що знаменує закінчення програми
//
void ReplicWithExit() {
  printf("Shutdown. See you soon.\n");
}
//-------------------------------------------------------------------------------
//Відкриття файлу для збереження списку в нього
//
int OpenFileForSave(
	FILE **pfFIlePtr,
	char chFileAdress[],
	struct SstdInfo *pStartElement,
	struct SstdInfo *pHeadStudent,
	int nStudentCnt,
	int nFileSateCheck) {
  pStartElement = pHeadStudent;
  if (nFileSateCheck == 1) {
	*pfFIlePtr = fopen(chFileAdress, "w");
  } else {
	*pfFIlePtr = fopen(chFileAdress, "a");
  }
  if (*pfFIlePtr == NULL)
  {
	printf("File cannot be opened or created correctly.\n ");
	printf("Try again\n");
	return -1;
  }
  if (nFileSateCheck == 1)
  {
	for (int i = 0; i < nStudentCnt; i++) {
	  if (i == nStudentCnt - 1) {
		fprintf(*pfFIlePtr, "%s %s %s %d %d %d %d %d %d",
			pStartElement->chSurname,
			pStartElement->chName, 
			pStartElement->chBirth, 
			pStartElement->nMarks[0], 
			pStartElement->nMarks[1], 
			pStartElement->nMarks[2], 
			pStartElement->nMarks[3],
			pStartElement->nMarks[4], 
			pStartElement->nMarks[5], 
			pStartElement->nMarkAvg);
	  } else {
		fprintf(*pfFIlePtr, "%s %s %s %d %d %d %d %d %d\n",
			pStartElement->chSurname,
			pStartElement->chName,
			pStartElement->chBirth,
			pStartElement->nMarks[0],
			pStartElement->nMarks[1],
			pStartElement->nMarks[2],
			pStartElement->nMarks[3],
			pStartElement->nMarks[4],
			pStartElement->nMarks[5],
			pStartElement->nMarkAvg);
	  }
	  pStartElement = pStartElement->pNext;
	}
  } else {
	fprintf(*pfFIlePtr, "\n");
	for (int i = 0; i < nStudentCnt; i++) {
	  if (i == nStudentCnt - 1) {
		fprintf(*pfFIlePtr, "%s %s %s %d %d %d %d %d %d",
			pStartElement->chSurname,
			pStartElement->chName, 
			pStartElement->chBirth,
			pStartElement->nMarks[0],
			pStartElement->nMarks[1],
			pStartElement->nMarks[2],
			pStartElement->nMarks[3],
			pStartElement->nMarks[4],
			pStartElement->nMarks[5],
			pStartElement->nMarkAvg);
      }	else {
		fprintf(*pfFIlePtr, "%s %s %s %d %d %d %d %d %d\n",
			pStartElement->chSurname,
			pStartElement->chName,
			pStartElement->chBirth,
			pStartElement->nMarks[0],
			pStartElement->nMarks[1],
			pStartElement->nMarks[2],
			pStartElement->nMarks[3],
			pStartElement->nMarks[4],
			pStartElement->nMarks[5],
			pStartElement->nMarkAvg);
	  }
	  pStartElement = pStartElement->pNext;
	}
  }
  fclose(*pfFIlePtr);
  return 0;
}
//-------------------------------------------------------------------------------
//Перевірка відповідності формату серед визначениї опцій вибору відповіді в меню
//
int CorrectChooseOption(int nOptions, char *pchAnswer, ...) {
  va_list vlPtr;
  char cAnswerArgument;
  while (1)
  {
	rewind(stdin);
	scanf("%c", pchAnswer);
	va_start(vlPtr, pchAnswer);
	for (int i = 0; i < nOptions; i++) {
	  cAnswerArgument = va_arg(vlPtr, char);
	  if (*pchAnswer == cAnswerArgument) {
		va_end(vlPtr);
		return 0;
	  }
	}
	printf("You must enter a correct number.Try again.\n>:");
  }
}
//-------------------------------------------------------------------------------