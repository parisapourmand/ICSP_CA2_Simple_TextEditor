/*parisa pourmand*/
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include"findreplace.h"
void main() {
		int n, m, flag = 0;
		char name[255], word[255],nword[255];
		printf("\nWelcome to the find and replace application!\n\n");
		while (1) {
		printf("How may i serve you?\n1.I want to find a word.\n2.I want to replace a word.\n0.exit\n");
		scanf("%d", &n);
		switch (n) {
		case 1:
			printf("what is the name of the file?");/*get file name from user*/
			gets(name);
			gets(name);
			printf("what is the word?");/*get file name from user*/
			gets(word);
			find(name, word);
			printf("%d %s(s) were found\n", find(name, word), word);
			break;
		case 2:
			printf("what is the name of the file?");/*get file name from user*/
			gets(name);
			gets(name);
			printf("what is the word?");/*get word from user*/
			gets(word);
			printf("what is the new word?");/*get new word from user*/
			gets(nword);
			replace(name,word,nword);
			printf("%d %s(s) were found and replaced!\n", find(name, nword), word);
			break;
		case 0:
			printf("Exiting\n");
			flag = 1;
			break;
		default:
			printf("invalid order.");
		}/*end of switch*/
		if (flag == 1)
			break;
	}/*end of while*/
}