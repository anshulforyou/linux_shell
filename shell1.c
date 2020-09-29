#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<time.h>
#include<dirent.h>
#include <sys/wait.h>
// #include <conio.h> 
#include <sys/types.h> 
#include <sys/stat.h>
#include<errno.h>

void echo1(char *token){
	// printf("%s\n", token);
	if (strcmp(token, "-E")==0){
		token = strtok(NULL, " ");
		while( token != NULL ) {
	      	printf( "%s ", token ); //printing each token
	      	token = strtok(NULL, " ");
   		}
	}
	else if(strcmp(token,"-n")==0){
		token = strtok(NULL, " ");
		// printf("%s", token); 
		while( token != NULL ) {
	      printf( "%s ", token ); //printing each token
	      token = strtok(NULL, " ");
	   }
	}
	else {
		// token = strtok(NULL, " ");
		// printf("%s\n", token);
		while( token != NULL ) {
	      printf( "%s ", token ); //printing each token
	      token = strtok(NULL, " ");
	   }
	}
}

int process_cmd(char cmd[]){
	char cmdc[200];
	strcpy(cmdc, cmd);

	char *token;
	token = strtok(cmd, " ");
	// printf("%s\n", token);
	char first[50];
	strcpy(first, token);
	// printf("%s\n", first);
	// if(token != NULL){
	// 	token = strtok(NULL, " ");
	// }

	char cud[200];
	getcwd(cud, 200);

	if (strcmp(first, "echo")==0){
		token = strtok(NULL, " ");
		printf("%s\n", "Running echo");
		echo1(token);
	}
	else if(strcmp(first, "pwd")==0){
		printf("Printing current working directory");
		char dir[200];
		getcwd(dir, 200);
		printf("%s\n", dir);
	}
	else if(strcmp(first, "cd")==0){
		token = strtok(NULL, " ");
		int temp = chdir(token);
		if(temp==-1){
			if(errno==EACCES)
				printf("%s\n", "ACCESS NOT AVAILABLE TO CURRENT USER");
			else if(errno == ENOENT)
				printf("%s\n", "PATH NOT AVAILABLE");
			else 
				printf("%s\n", "ERROR OCCURED");
		}
	}
	else if(strcmp(first, "history")==0){
		token = strtok(NULL, " ");
		if (token == NULL){
			FILE *his = fopen("history.txt", "r");
			char line[200];

			while(fgets(line, sizeof(line), his)){
				// char *point;
				printf("%s\n", line);
			}
			fclose(his);
		}else if(strcmp(token, "-c")){
			unlink("history.txt");
			printf("%s\n", "History Deleted");
		}else if(strcmp(token, "-w")){
			token = strtok(NULL, " ");
			FILE *his = fopen("history.txt", "r");
			char line[200];

			FILE *new = fopen(token, "w");

			while(fgets(line, sizeof(line), his)){
				// char *point;
				// printf("%s\n", line);
				fprintf(new, "%s\n", line);
			}
			fclose(new);
			fclose(his);
		}
	}
	else if(strcmp(first, "date")==0){
		pid_t pid;
		pid = fork();
		if(pid<0){
			fprintf(stderr, "%s\n", "Fork Failed");
		}
		else if (pid ==0){
			char cur[200];
			strcpy(cur, cud);
			char fl[] = "/date";
			strcat(cur, fl);

			execlp(cur, cmdc, NULL);

			// char temp[100]; 
	  //       time_t current_time = time(NULL);
	  //       struct tm *tm = localtime(&current_time);
	  //       strftime(temp, sizeof(temp), "%c", tm);
	  //       printf("\nCurrent Date and Time:\n");
	  //       printf("\n%s\n\n", temp);

		}else{
			wait(NULL);
		}
	}
	else if(strcmp(first, "ls")==0){
		pid_t pid;
		pid = fork();
		if(pid<0){
			fprintf(stderr, "%s\n", "Fork Failed");
		}else if (pid ==0){
			char cur[200];
			strcpy(cur, cud);
			char fl[] = "/lsd";
			strcat(cur, fl);

			execlp(cur, cmdc, NULL);
			}else{
				wait(NULL);
			}	
		}
	
	else if(strcmp(first, "cat")==0){
		pid_t pid;
		pid = fork();
		if(pid<0){
			fprintf(stderr, "%s\n", "Fork Failed");
		}
		else if (pid ==0){
			char cur[200];
			strcpy(cur, cud);
			char fl[] = "/cat";
			strcat(cur, fl);

			execlp(cur, cmdc, NULL);
		}
		else{
			wait(NULL);
		}	
	}
	else if(strcmp(first, "mkdir")==0){
		token = strtok(NULL, " ");
		if(token != NULL){
			char dir[200];
			strcpy(dir, cud);
			char fl[] = "/mkdir";
			strcat(dir, fl);

			execlp(dir, cmdc, NULL);
		}else{
			printf("Directory name not entered");
		}
	}
	else if(strcmp(first, "rm")==0){
		token = strtok(NULL, " ");
		if(token != NULL){
			char dir[200];
			strcpy(dir, cud);
			char fl[] = "/rm";
			strcat(dir, fl);

			execlp(dir, cmdc, NULL);
		}else{
			printf("%s\n", "File name to be deleted is not entered");
		}
	}
}
void main(){
	printf("Welcome to my own shell, this is a dangerous place to be in");
	char cmd[100];
	while(strcmp(cmd, "exit")!=0){	
		printf("\n>>> ");
		fgets(cmd,100,stdin);
		strcmp(cmd, strtok(cmd, "\n"));
		// printf("%s\n", cmd);
		if(strcmp(cmd, "exit")==0)
			break;
		// scanf("%s", cmd);
		// printf("%s\n", cmd);
		FILE *fptr;
		fptr = fopen("history.txt", "a+");
		fprintf(fptr, "%s\n", cmd);
		fclose(fptr);
		process_cmd(cmd);
	}
}