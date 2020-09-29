#include<stdio.h>
#include<string.h>
#include <sys/types.h> 
#include <unistd.h> 
#include <stdlib.h>
#include <fcntl.h> 
#include <string.h>
#include<sys/wait.h>

void calculate(char sec){
	int file = open("data.csv", O_RDONLY);
	char *first = (char *)malloc(10*sizeof(char));
	while(first[0]!='\n'){
		read(file, first, 1);
	}
	int student =0;
	int position =0;
	int current =0;
	char *field=(char *) malloc(500*sizeof(char));
	char details[6][700][600];
	// int ptr=0,studentpos=0,fieldpos=0;

	while(1){
		int one = read(file, first, 1);
		if(first[0]==','){
			strcpy(details[position][student], field);
			current=0;
			position++;
			field=(char *) malloc(500*sizeof(char));
		}
		if(first[0]=='\n'){
			strcpy(details[position][student], field);
			position=0;
			student++;
			current=0;
			field = (char *)malloc(500*sizeof(char));

		}
		if(first[0]!=','){
			field[current++]=first[0];
		}
		if(one<=0){
			strcpy(details[position][student], field);
			position =0;
			student++;
			current=0;
			field = (char *)malloc(500*sizeof(char));
			break;
		}

	}
	for(int i=0;i<student;i++){
		if(details[1][i][0]==sec){
			int add = 0;
			for(int j=2;j<6;j++){add+=atoi(details[j][i]);}
			char avg[200];
			float temp = (float)(add)/4;
			printf("\n%s %s\n", "Id:", details[0][i]);
			// printf("%s\n", details[]);
			// printf("%s\n", details[1][i]);

			gcvt(temp, 10, avg);
			printf("%s %s\n", "Average Marks", avg);
		}
	}
}

int main(){
	pid_t pid;

	pid = fork();
	if (pid<0){
		fprintf(stderr, "Fork Failed");
		return 1;
	}
	else if(pid == 0){
		calculate('A');

	}
	else{
		wait(NULL);
		printf("Child Complete");
		calculate('B');
	}

}

