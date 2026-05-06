#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX 1024

int total = 0;
int n1,n2;
char *s1,*s2;
FILE *fp;

int readf(FILE *fp)
{
	if((fp=fopen("strings.txt", "r"))==NULL){
		printf("ERROR: can't open string.txt!\n");
		return 0;
	}

	s1=(char *)malloc(sizeof(char)*MAX);
	if(s1==NULL){
		printf("ERROR: Out of memory!\n");
		fclose(fp);
		return -1;
	}

	s2=(char *)malloc(sizeof(char)*MAX);
	if(s2==NULL){
		printf("ERROR: Out of memory\n");
		free(s1);
		fclose(fp);
		return -1;
	}

	/*read s1 s2 from the file*/
	if(fgets(s1, MAX, fp)==NULL || fgets(s2, MAX, fp)==NULL){
		printf("ERROR: Could not read strings!\n");
		free(s1);
		free(s2);
		fclose(fp);
		return -1;
	}

	fclose(fp);

	/*remove newline characters*/
	s1[strcspn(s1, "\n")] = '\0';
	s2[strcspn(s2, "\n")] = '\0';

	n1=strlen(s1);  /*length of s1*/
	n2=strlen(s2); /*length of s2*/

	if(s1==NULL || s2==NULL || n1<n2)  /*when error exit*/
		return -1;

	return 1;
}

int num_substring(void)
{
	int i,j,k;
	int count;

	for (i = 0; i <= (n1-n2); i++){   
		count=0;

		for(j = i,k = 0; k < n2; j++,k++){  /*search for the next string of size of n2*/  

			if (*(s1+j)!=*(s2+k)){
				break;
			}
			else
				count++;

			if(count==n2)    
				total++;		/*find a substring in this step*/                          
		}
	}

	return total;
}

int main(int argc, char *argv[])
{
	int count;

	if(readf(fp) <= 0){
		return 1;
	}

	count = num_substring();

	printf("The number of substrings is: %d\n", count);

	free(s1);
	free(s2);

	return 0;
}