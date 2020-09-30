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
	      	printf( "%s\n", token ); //printing each token
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
	      printf( "%s\n", token ); //printing each token
	      token = strtok(NULL, " ");
	   }
	}
}

void cd_help(){
	printf("%s\n", "Change the shell working directory.");
	printf("%s\n", "Change the current directory to DIR.  The default DIR is the value of the HOME shell variable.");
    printf("%s\n", "Options:");
    printf("%s\n", "-L	force symbolic links to be followed: resolve symbolic");
    printf("%s\n", "links in DIR after processing instances of `..'");  
    		
    printf("%s\n", "The default is to follow symbolic links, as if `-L' were specified.");
	printf("%s\n", "`..' is processed by removing the immediately previous pathname component back to a slash or the beginning of DIR.");

}

void pwd_help(){
	printf("%s\n", "Print the name of the current working directory.");
	printf("%s\n", "Options:");
	printf("%s\n", "-L	print the value of $PWD if it names the current working");
	printf("%s\n", "directory.");
}

int process_cmd(char cmd[], char dir[]){
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
	strcpy(cud, dir);
	// getcwd(cud, 200);

	if (strcmp(first, "echo")==0){
		token = strtok(NULL, " ");
		printf("%s\n", "Running echo");
		echo1(token);
	}
	else if(strcmp(first, "pwd")==0){
		token = strtok(NULL, " ");
		if(token == NULL || strcmp("-L", token)==0){
			printf("Printing current working directory");
			char dir[200];
			char* val = getcwd(dir, 200);
			if(val == NULL){
				if(errno==EACCES){
					printf("%s\n", "PERMISSION DENIED");
				}else if(errno == ENOENT){
					printf("%s\n", "CURRENT WORKING DIRECTORY UNLNKED");
				}
			}

			printf("%s\n", dir);	
		}else if(strcmp("--help", token)==0){
			pwd_help;
		}
	}
	else if(strcmp(first, "cd")==0){
		token = strtok(NULL, " ");
		if (strcmp("-L", token)==0){
			int temp = chdir(token);
			if(temp==-1){
				if(errno==EACCES)
					printf("%s\n", "ACCESS NOT AVAILABLE TO CURRENT USER");
				else if(errno == ENOENT)
					printf("%s\n", "PATH NOT AVAILABLE");
				else 
					printf("%s\n", "ERROR OCCURED");
			}	
		}else if(strcmp("--help", token)){
			cd_help();
		}else{
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
	}
	else if(strcmp(first, "history")==0){
		token = strtok(NULL, " ");
		if (token == NULL){
			FILE *his = fopen("history.txt", "r");
			char line[200];

			if(his==NULL){
				if(errno == ENFILE){
					printf("%s\n", "NO MORE FILES CAN BE OPENED");
				}else if(errno == EINVAL){
					printf("%s\n", "INVALID ARGUMENTS, NOT ABLE TO OPEN FILE");
				}else{
					printf("%s\n", "NOT ABLE TO OPEN FILE, ERROR NOT RECOGNISED");
				}
			}

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

			if(his==NULL){
				if(errno == ENFILE){
					printf("%s\n", "NO MORE FILES CAN BE OPENED");
				}else if(errno == EINVAL){
					printf("%s\n", "INVALID ARGUMENTS, NOT ABLE TO OPEN FILE");
				}else{
					printf("%s\n", "NOT ABLE TO OPEN FILE, ERROR NOT RECOGNISED");
				}
			}

			FILE *new = fopen(token, "w");
			if(new==NULL){
				if(errno == ENFILE){
					printf("%s\n", "NO MORE FILES CAN BE OPENED");
				}else if(errno == EINVAL){
					printf("%s\n", "INVALID ARGUMENTS, NOT ABLE TO OPEN FILE");
				}else{
					printf("%s\n", "NOT ABLE TO OPEN FILE, ERROR NOT RECOGNISED");
				}
			}

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
		pid_t pid;
		pid = fork();
		if(pid<0){
			fprintf(stderr, "%s\n", "Fork Failed");
		}else if (pid ==0){
			token = strtok(NULL, " ");
			if(token != NULL){
				char dir[200];
				strcpy(dir, cud);
				char fl[] = "/mkdir";
				strcat(dir, fl);

				execlp(dir, cmdc, cud, NULL);
			}else{
				printf("Directory name not entered");
			}
		}else{
			wait(NULL);
		}
	}
	else if(strcmp(first, "rm")==0){
		pid_t pid;
		pid = fork();
		if(pid<0){
			fprintf(stderr, "%s\n", "Fork Failed");
		}
		else if (pid ==0){
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
		else{
			wait(NULL);
		}
	}
}

void main(){
	printf("%s\n", "Welcome to my own shell, this is a dangerous place to be in");
	char cmd[100];
	char cud[200];
	char* val = getcwd(cud, 200);
	if(val == NULL){
		if(errno==EACCES){
			printf("%s\n", "PERMISSION DENIED");
		}else if(errno == ENOENT){
			printf("%s\n", "CURRENT WORKING DIRECTORY UNLNKED");
		}
	}
	while(strcmp(cmd, "exit")!=0){	
		printf(">>> ");
		fgets(cmd,100,stdin);
		strcmp(cmd, strtok(cmd, "\n"));
		// printf("%s\n", cmd);
		if(strcmp(cmd, "exit")==0)
			break;
		// scanf("%s", cmd);
		// printf("%s\n", cmd);
		FILE *fptr;
		fptr = fopen("history.txt", "a+");
		if(fptr==NULL){
			if(errno == ENFILE){
				printf("%s\n", "NO MORE FILES CAN BE OPENED");
			}else if(errno == EINVAL){
				printf("%s\n", "INVALID ARGUMENTS, NOT ABLE TO OPEN FILE");
			}else{
				printf("%s\n", "NOT ABLE TO OPEN FILE, ERROR NOT RECOGNISED");
			}
		}
		fprintf(fptr, "%s\n", cmd);
		fclose(fptr);
		process_cmd(cmd, cud);
	}
}