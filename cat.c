#include<stdio.h>
#include<string.h>

void main(int a, char** inp){
	char * token;
	token = strtok(inp[0], " ");
	token = strtok(NULL, " ");

	if(strcmp(token, "-E")==0){
		token = strtok(NULL, " ");
		while(token != NULL){
			char file1[100];
			strcpy(file1, token);
			FILE *fptr1 = fopen(file1, "r");
			char line1[2000];
			while(fgets(line1, sizeof(line1), fptr1)){
				printf("%s\n", line1);
				printf("$");
			}
			token = strtok(NULL, " ");
		}
	}else if(strcmp(token, "-n")){
		token = strtok(NULL, " ");
		while(token != NULL){
			char file1[100];
			strcpy(file1, token);
			FILE *fptr1 = fopen(file1, "r");
			char line1[2000];
			int count=1;
			while(fgets(line1, sizeof(line1), fptr1)){
				printf("%d\n", count);
				printf("%s\n", line1);
				count++;
			}
			token = strtok(NULL, " ");
		}
	}
	else{
		while(token != NULL){
			char file1[100];
			strcpy(file1, token);
			FILE *fptr1 = fopen(file1, "r");
			char line1[2000];
			while(fgets(line1, sizeof(line1), fptr1)){
				printf("%s\n", line1);
			}
			token = strtok(NULL, " ");
		}
	}
}