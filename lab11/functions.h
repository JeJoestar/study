#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <conio.h>
#include <string.h>
#include <stdarg.h>

//-------------------------------------------------------------------------------
void Choose1(char chAnswer, struct SstdInfo  *pCur);
//-------------------------------------------------------------------------------
void Choose2(char chAnswer, char chFileString[],
	char chStrtokLimits[],
	char* pchStrtokPtr,
	struct SstdInfo* pCur,
	struct SstdInfo* pHead,
	int* nStudentCnt,
	FILE* pfOpenedFile, char chFileAdress[]);
//-------------------------------------------------------------------------------
void PushElementBeforeHead(struct SstdInfo *pCurStudent, struct SstdInfo **pHeadStudent);
//-------------------------------------------------------------------------------
void InsertElementIntoList(struct SstdInfo *pCurStudent, struct SstdInfo **ppSkiped);
//-------------------------------------------------------------------------------
void SortElement(struct SstdInfo *pCur, struct SstdInfo **ppHead);
//-------------------------------------------------------------------------------
void InsertStudentElementFromFile(FILE *pfOpenedFile,
	char cFileString[],
	char cStrtokLimits[],
	char *pcStrtokPtr,
	struct SstdInfo *pCur,
	struct SstdInfo **ppHead,
	int *pnStudentsCnt);
//-------------------------------------------------------------------------------
void PrintStudentTable(struct SstdInfo *pStartFrom,
	struct SstdInfo *pHeadStudent,
	int nStudentCnt);
//-------------------------------------------------------------------------------
void VanishStudentWithTwoBadMarks(
	struct SstdInfo *pCurStudent,
	struct SstdInfo **ppHeadStudent,
	int *pnStudentCnt);
//-------------------------------------------------------------------------------
void CreateElementAndInsertThisIntoList(
	char chStrtokLimits[],
	struct SstdInfo **ppHeadStudent,
	int* nStudentCnt);
//-------------------------------------------------------------------------------
void FreeMemmoryForStudentsList(struct SstdInfo *pHeadStudent);
//-------------------------------------------------------------------------------
void InsertStudentElementByKeyboard(
	char chFileString[],
	char chStrtokLimits[],
	char *pchStrtokPtr,
	struct SstdInfo *pCurStudent,
	struct SstdInfo **pHeadStudent,
	int *pnStudentCnt);
//-------------------------------------------------------------------------------
void OpenFile(FILE  **ppfFilePtr, char chFileAdress[]);
//-------------------------------------------------------------------------------
void ReplicWithExit();
//-------------------------------------------------------------------------------
int OpenFileForSave(FILE  **pfFIlePtr,
	char chFileAdress[],
	struct SstdInfo *pStartElement,
	struct SstdInfo *pHeadStudent,
	int nStudentCnt,
	int nFileSateCheck);
//-------------------------------------------------------------------------------
int CorrectChooseOption(int nOptions, char *pchAnswer, ...);
//-------------------------------------------------------------------------------
void PrintTableLines();
//-------------------------------------------------------------------------------