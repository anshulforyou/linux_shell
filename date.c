#include<time.h>
#include<stdio.h>
#include<string.h>


void main(int a, char** inp){
	char * token;
	token = strtok(inp[0], " ");
	token = strtok(NULL, " ");

	if(strcmp(token, "-R")==0){
		char temp[100]; 
	    time_t current_time = time(NULL);
	    struct tm *tm = localtime(&current_time);

	    strftime(temp, sizeof(temp), "Today is %A %b %d.\n", tm);
	    fputs(temp, stdout);

	    strftime(temp, sizeof(temp), "Time is %I: %M %p.\n", tm);
	    fputs(temp, stdout);

	    // printf("\nCurrent Date and Time:\n");
	    // printf("\n%s\n\n", temp);

	}else if(strcmp(token, "-u")==0){
		char temp[100];
	    time_t current_time = time(NULL);
	    struct tm *tm = gmtime(&current_time);
	    strftime(temp, sizeof(temp), "%c", tm);
	    printf("\nCurrent Date and Time:\n");
	    printf("\n%s\n\n", temp);
	}
	else {
		// if(token == NULL){
		char temp[100]; 
	    time_t current_time = time(NULL);
	    struct tm *tm = localtime(&current_time);
	    strftime(temp, sizeof(temp), "%c", tm);
	    printf("\nCurrent Date and Time:\n");
	    printf("\n%s\n\n", temp);
	}
}
// r,