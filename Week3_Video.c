// You have been given array of binary digits
// Using maximum one swap, you need to find the length of the longest consecutive 1's

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_SIZE 1024

int getMaxLen(char *in, int len);

int main(int argc, char *argv[]){
	if(argc != 2){
		printf("USAGE :: ./a.out <INPUT FILE>\n");
		return -1;
	}

	FILE *fp = fopen(argv[1], "r");

	char input[MAX_SIZE];

	while(fgets(input, MAX_SIZE, fp) != NULL){
		printf("========================\n");	
		int j=0;
		int len = strlen(input);
		input[len-1] = '\0';
		len--;
		printf("Length of input = %d\n", len);
/*
		while(input[j] != '\n'){
			printf("%c\n",input[j]);
			j++;
		}
*/
		printf("%s - Longest length of consecutive 1's = %d\n", input, getMaxLen(input, len));		
	}

	fclose(fp);
} 

int getMaxLen(char *in, int len){
	if(len <= 0){
		return 0;
	}
	
	printf("Inside getMaxLen %s - %d\n", in, len);

	int totalOnes = 0;
	int *leftOnes = (int *) malloc(sizeof(int) * len);
	printf("1\n");
	int *rightOnes = (int *) malloc(sizeof(int) * len);
	
	for(int i=0;i < len;i++){
		if(in[i] == '0'){
			leftOnes[i] = 0;
		}else if(in[i] == '1'){
			if(i-1 >= 0){ 
				leftOnes[i] = leftOnes[i-1] + 1;
			}else{
				leftOnes[i] = 1;
			}
			totalOnes++;
		}
	}

	for(int i=len-1;i >= 0;i--){
		if(in[i] == '0'){
			rightOnes[i] = 0;
		}else if(in[i] == '1'){
			if(i+1 < len){ 
				rightOnes[i] = rightOnes[i+1] + 1;
			}else{
				rightOnes[i] = 1;
			}
		}
	}
	
	int maxlen = 0;
	int GlobalLen = 0;

printf("Total Ones = %d\n", totalOnes);

	if(totalOnes == len) return len;

	int flag = 0;

	for(int i=0;i < len;i++){
		flag = 0;
		if(in[i] == '0'){

			if(i > 0 && leftOnes[i-1] > 0){
				maxlen = leftOnes[i-1];
				flag = 1;
			}

			if(i+1 < len && rightOnes[i+1] > 0){
				maxlen += rightOnes[i+1];
				flag = 1;
			}

			if(maxlen < totalOnes && flag == 1) maxlen++; 
		}

		if(maxlen > GlobalLen){
			GlobalLen = maxlen;
		}
	}

	free(leftOnes);
	free(rightOnes);

	return GlobalLen;
}
