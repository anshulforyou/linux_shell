#include<sys/types.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include <errno.h>
#include <stdbool.h>

int main(){
	pid_t pid;

	FILE *data = fopen("data.csv", "r");
	char item[100];
	int a, c, d, e, f;
	char status;

	pid = fork();
	if (pid<0){
		fprintf(stderr, "Fork Failed");
		return 1;
	}
	else if(pid == 0){
		if (data == NULL){
			perror("Unable to open the file.");
			exit(1);
		}

		// fscanf(data, "%s, %s, %s, %s, %s, %s", item, item, item, item, item, item);
		fseek(data, 1, SEEK_SET);
		while(fscanf(data, "%d,%s,%d,%d,%d,%d", &a, item, &c, &d, &e, &f) != EOF)  
		{   
			int ans;
			ans = c+d+e+f;
			ans = ans/4;
		    printf("\n%d", ans);
		    printf("\n%d %s %d %d %d %d", a, item, c, d, e, f);
		}  
		if(feof(data))  
		{            
		         puts("EOF");     
		}  
		else 
		{  
		 puts("CAN NOT READ");  
		}  
		// getch();  
		return 0;

		// while (true) {
	 //        int ret = fscanf(data, "%s %c", item, &status);
	 //        if(ret == 2)
	 //            printf("\n%s \t %c", item, status);
	 //        else if(errno != 0) {
	 //            perror("scanf:");
	 //            break;
	 //        } else if(ret == EOF) {
	 //            break;
	 //        } else {
	 //            printf("No match.\n");
	 //        }
  //   	}
	    // printf("\n");
	    // if(feof(data)) {
	    //     puts("EOF");
	    // }
	    // return 0;

		// char line[200];
		// while(fgets(line, sizeof(line), data)){
		// 	char *token;
		// 	token = strtok(line, ",");


		// 	while(token!=NULL){
		// 		printf("%-12s", token);
		// 		token = strtok(NULL, ",");
		// 	}
		// 	printf("\n");
		// }
	}
	else{
		// wait(NULL);
		printf("Child Complete");
	}

	fclose(data);
	return 0;
}