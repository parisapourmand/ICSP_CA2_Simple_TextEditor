/*parisa pourmand*/
#define _CRT_SECURE_NO_WARNINGS
#include"findreplace.h"
//function for counting number of letters
int count(char word[]) {
	int num = 0;
	for (int i = 0; word[i] != NULL; i++)
		num++;
	return num;
}

//function for finding number of words
int find(char name[], char word[]) {
	FILE *fp;
	int n, i, j, k, num = 0;
	fp = fopen(name, "r");
	if (fp == NULL)
		printf("Could not open file");
	/*initializing arr*/
	char *arr = (char*)malloc(sizeof(char));
	if (arr == NULL)
		printf("memory allocation failed");
	for (i = 0; !feof(fp); i++) {
		arr = (char*)realloc(arr, (i + 2)*sizeof(char));
		if (arr == NULL)
			printf("memory allocation failed");
		fread(arr + i, sizeof(char), 1, fp);
	}
	arr[i] = NULL;
	//check the first word 
	for (k = 0; word[k] != NULL; k++)
		if (word[k] != arr[k] && word[k] != other(arr[k]) )
			break;
	if (word[k] == NULL) {
		if (arr[k] == ' ')
			num++;
	}
	//check the rest of the file
	fseek(fp, 0, SEEK_SET);
	for (j = k-1; j < i; j++) {
		{
			for (k = 0; word[k] != NULL; k++)
				if (word[k] != arr[j + k + 1] && word[k] != other(arr[j + k + 1]) )
					break;
		}
		if (word[k] == NULL && (arr[j] == ' ') && (arr[j + k + 1] == ' ' ||arr[j + k + 1] == '\n' || arr[j + k + 2] == NULL))
			num++;
	}
	free(arr);
	fclose(fp);
	return num;
}
//function for replacing word and printing date and time
void replace(char name[], char word[], char nword[]) {
	FILE *fp;
	int  i, j = 0, j2 = 0, k, f, t, m = 0;
	fp = fopen(name, "r+");
	if (fp == NULL)
		printf("Could not open file");
	/*initializing arr and arr2*/
	char *arr = (char*)malloc(sizeof(char));
	if (arr == NULL)
		printf("memory allocation failed");
	for (i = 0; !feof(fp); i++) {
		arr = (char*)realloc(arr, (i + 2)*sizeof(char));
		if (arr == NULL)
			printf("memory allocation failed");
		fread(arr + i, sizeof(char), 1, fp);
	}
	arr[i] = NULL;
	fseek(fp, 0, SEEK_SET);
	char *arr2 = (char*)malloc((i + abs(count(nword) - count(word))*find(name, word))*sizeof(char) + 10);
	if (arr2 == NULL)
		printf("memory allocation failed");
	//initializing arr2
	//for first word
	for (k = 0; word[k] != NULL; k++)
		if (word[k] != arr[k] && word[k] != other(arr[k]) )
			break;
	if (word[k] == NULL) {
		if (arr[k] == ' ') {
			for (m = 0; m < count(nword); m++)
				arr2[m] = nword[m];
			j2 = count(nword);
			j = k;
		}
		else
		{
			arr2[j2] = arr[j];
			j2++;
			j = 1;
		}
	}
	fseek(fp, 0, SEEK_SET);
	//the rest of the array
	for (; j < i; j++) {
		for (k = 0; word[k] != NULL; k++)
			if (word[k] != arr[j + k] && word[k] != other(arr[j + k]) )
				break;
		if (word[k] == NULL && (arr[j - 1] == ' ' || arr[j - 1] == '\n') && (arr[j + k] == ' ' || arr[j + k] == '\n' || arr[j + k + 1] == NULL))
		{
			j += (k - 1);
			//arr2[j2] = ' ';
			for (m = 0; m < count(nword); m++) {
				arr2[j2] = nword[m];
				j2++;
			}
		}
		else
		{
			arr2[j2] = arr[j];
			j2++;
		}
	}
	fwrite(arr2, sizeof(char), j2 - 1, fp);
	while (j2 < i){
		fprintf(fp, " ");
		j2++;
	}
	fclose(fp);
	fp = fopen(name, "a");
	fprintf(fp, "\n***At %s - %s the word \"%s\" was replaced with \"%s\".", __DATE__, __TIME__, word, nword);/*print date and time*/
	free(arr);
	free(arr2);
	fclose(fp);
}
//function for checking captal and lower case
char other(char c)
{
	if (c <= 'z' && c >= 'a')
		return c - 'a' + 'A';
	else
		return c - 'A' + 'a';
}