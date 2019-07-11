#include <stdio.h>
#include <tchar.h>
#include <Windows.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>

#define SIZE 32

BOOL my_MultiByteToWideChar(char *pMultiByteStr, wchar_t *wpUnicodeStr, DWORD dwLENGTH);
BOOL my_WideCharToMultiByte(wchar_t *wpUnicodeStr, char *pMultiByteStr, DWORD dwLENGTH);

using namespace std;

int main()
{
	char x[SIZE];
	wchar_t wUnicode[SIZE] = {};
	//get input from user
	printf("Enter the string: ");
	scanf_s("%s", x, SIZE);
	printf("original string: %s\n", x);
	int iRetVal1 = my_MultiByteToWideChar(x, wUnicode, SIZE);
	printf("Return value of my_MultiByteToWideChar: %d\n", iRetVal1);
	int iRetVal2 = my_WideCharToMultiByte(wUnicode, x, SIZE);
	printf("Return value of my_WideCharToMultiByte: %d\n", iRetVal2);

	return 0;


}

//function to convert mbcs to wUnicode
BOOL my_MultiByteToWideChar(char *pMultiByteStr, wchar_t *wpUnicodeStr, DWORD dwLENGTH)
{

	int sizereq1 = MultiByteToWideChar(CP_ACP, 0, pMultiByteStr, -1, NULL, 0); //RetValurns number of characters including the \0 character since last arg is 0

//unicode should be empty and mbcs should have some value
	if (pMultiByteStr == NULL)
	{
		printf("Inside my_MultiByteToWideChar: %u\n", GetLastError());
		return FALSE;
	}

	//would be used in case of dynamically allocating space
	//if (dwLENGTH < sizereq1) //if the dwlength calculated by the above function is greater than size retvalurn error
	//{
	//	return false;
	//}

	MultiByteToWideChar(CP_ACP, 0, pMultiByteStr, -1, wpUnicodeStr, dwLENGTH);
	printf("%u\n", GetLastError()); //RetValurns 0 on success
	printf("MultiByteToWideChar translated: %s \n", wpUnicodeStr);
	
	//pMultiByteStr = NULL; //done converting so make it null for the next conversion
	
	return TRUE;
}

//function to convert wUnicode to mbcs
BOOL my_WideCharToMultiByte(wchar_t *wpUnicodeStr, char *pMultiByteStr, DWORD dwLENGTH)
{

	int sizereq2 = WideCharToMultiByte(CP_UTF8, 0, wpUnicodeStr, -1, NULL, 0, NULL, FALSE);

//mbcs should be empty and unicode should have some value
	if (wpUnicodeStr == NULL)
	{
		printf("Inside my_WideCharToMultiByte: %u\n", GetLastError());
		return FALSE;
	}

	//would be used in case of dynamically allocating space
	//if (dwLENGTH < sizereq2) //if the dwLENGTH calculated by the above function is greater than size RetValurn error
	//{
	//	return FALSE;
	//}

	WideCharToMultiByte(CP_UTF8, 0, wpUnicodeStr, -1, pMultiByteStr, dwLENGTH, NULL, FALSE);
	printf("%u\n", GetLastError());
	printf("WideCharToMultiByte translated: %s\n", pMultiByteStr);

	//wpUnicodeStr = NULL; //done converting so make the variable null

	return TRUE;
}