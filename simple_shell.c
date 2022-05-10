#include "main.h"

#define BUFFER_LEN 1024

int main(){
    char *user_input;
    char* argv[120];
    int argc ;
    char* path = "";
    char file_path[50];
    size_t buff;
    char c;

    while(c != EOF){
        
        write(STDOUT_FILENO, "($) ", 4);     
        
        if ((c = getline(&user_input,&buff, stdin)) == EOF)
        {
                break;
        }
        
        size_t length = strlen(user_input);

        if(length == 0){
            break;
        }

        if (user_input[length - 1] == '\n'){
            user_input[length - 1] = '\0'; // replace last char by '\0' if it is new line char
        }
        if (strcmp("exit",user_input) == 0)
        {
                break;
        }
        
        //split command using spaces
        char *token;                  
        token = strtok(user_input," ");
        int argc=0;
        if(token == NULL){
            continue;
        }
        while(token!=NULL){
            argv[argc]=token;      
            token = strtok(NULL," ");
            argc++;
        }
        
        argv[argc]=NULL; 
        
        strcpy(file_path, path);  //Assign path to file_path 
        strcat(file_path, argv[0]); //conctanate command and file path           

        if (access(file_path,F_OK)==0){  //check the command is available in /bin
        
            pid_t pid, wpid;
            int status;
            
            pid = fork();
            if(pid == 0)
                {
                        if (execve(argv[0], argv, NULL) == -1)
                        {
                                perror("Error");
                        }
                }
                else
                {
                        wait(NULL);
                }
        }
        else {
            printf("Command is not available in the bin\n"); //Command is not available in the bin
        }

    }
} 
