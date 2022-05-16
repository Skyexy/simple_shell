#include "main.h"

alias my_aliases[] = {
{"ls", "ls --color=auto"},
{"ll", "ls -alF"},
{"la", "ls -A"},
{NULL, NULL},
};
my_builtins builtins[] = {
     {"exit", &_exi},
     {"env", &env},
     {"cd", &cd},
     {NULL, NULL},
};
int comp(char **argv, char *sig)
{
        char *token;
        int x = 0;
        int y = 0;
        token = strtok(sig, " ");
 
        while(token != NULL)
        {
                if (strcmp(token, argv[y]) == 0)
                {
                        x++;
                }
                y++;
        }
        return(x);
}
int _exi(char **argv __attribute__((unused)))
{
    int d = atoi(argv[1]);
    exit(d);
}
int env(char **argv __attribute__((unused)))
{
    extern char **environ;
    char **env = environ;
    int i = 0;
    
    while(env[i])
    {
        write(STDOUT_FILENO, environ[i], strlen(environ[i]));
        write(STDOUT_FILENO, "\n", 1);
        i++;
    }
    return (0);
}
int cd(char **argv)
{
    char *path = argv[1];
    char me[BUFFER_LEN];
    char *cwd = getcwd(me, BUFFER_LEN);
    char *dir;
    char *to;
    if (path == NULL)
    {
        chdir(cwd);
        return (0);
    }
    else if (strcmp("-",argv[1]) == 0)
    {
        chdir("-");
        return (0);
    }
    else
    {
        dir = strcat(cwd, "/");
        to = strcat(dir, path);
        if (chdir(to) == -1)
        {
            perror("Error");
            return (-1);
        }
    }
    return(0);
}
char *_getpath(void)
{
    extern char **environ;
    char *path;
    int i = 0;

    while(*environ)
    {
        if(strncmp(*environ, "PATH=",5) == 0)
        {
            path = strdup(*environ);
            while(*path && i < 5)
            {
                path++;
                i++;
            }
            return(path);
        }
        environ++;
    }
    return (NULL);
}
void execute(char** argv)
{
    if (access(argv[0],F_OK)==0){
        
            pid_t pid;
            
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
            write(STDOUT_FILENO, "Command is not available in the bin",35);
        }
}
int exv(char **argv)
{
    int x = 0;
    char *path = _getpath();
    char *dirs[BUFFER_LEN];
    char *token = NULL;
    char *cwd = getcwd(NULL, 0);
    struct stat sb;
    
    token = strtok(path, ":");
    x = 0;
    while (token != NULL)
    {
        dirs[x] = strdup(token);
        token = strtok(NULL, ":");
        x++;
    }
    x = 0;
    if (*argv[0] != '/')
    {
        while (dirs[x] != NULL)
        {
            chdir(dirs[x]);
            if (stat(argv[0], &sb) == 0)
            {
                strcat(dirs[x],"/");
                argv[0] = strcat(dirs[x], argv[0]);
                printf("%s", argv[0]);
                break;
            }
            x++;
        }
        chdir(cwd);
    }
    execute(argv);
    return (0);
}
int divd(char *user_input)
{
        int x = 0;
        char *token;
        int argc;
        char *argv[BUFFER_LEN];

        while (my_aliases[x].alias_name != NULL)
        {
                if (strcmp(user_input, my_aliases[x].alias_name) == 0)
                {
                        user_input = strdup(my_aliases[x].real_name);
                }
                x++;
        }
        token = strtok(user_input," ");
        argc = 0;
        while(token!=NULL){
            argv[argc] = strdup(token);
            token = strtok(NULL," ");
            argc++;
        }
        argv[argc]=NULL;
        x = 0;
        while (builtins[x].name != NULL)
        {
                if (strcmp(argv[0], builtins[x].name) == 0)
                {
                        builtins[x].func(argv);
                }
                x++;
        }
        exv(argv);
        return (0);
}
void comma(char *user_input)
{
        char *token;
        char *argv[BUFFER_LEN];
        
        token = strtok(user_input,";");
        while(token != NULL)
        {
                argv[0] = strdup(token);
                divd(argv[0]);
                token = strtok(NULL,"; ");
        }
}
int check(char *s)
{
        int i = 0;
        int y = 0;
        
        while(s[i] != '\0')
        {
                if(s[i] == ';')
                {
                        y++;
                }
                i++;
        }
        return(y);
}

int _aliass(char *user_input)
{
        if(strncmp(user_input, "alias ",6) == 0);
        char *s = malloc(sizeof(char) * BUFFER_LEN);
        char *y = malloc(sizeof(char) * BUFFER_LEN);
        char *argv[BUFFER_LEN];
        char *t = t = "'";
        int x = 0;
        int g;
        int d = 0;
        char *token;
    if (strncmp(user_input, "alias ",6) == 0)
    {
            user_input = user_input + 6;
            g = check(user_input, '=');
            if (g == 0)
            {
                    token = strtok(user_input," ");
                    printf("%s", token);
                    int argc = 0;
                    while(token!=NULL){
                            argv[argc] = strdup(token);
                            token = strtok(NULL," ");
                            argc++;
                    }
                    argv[argc]=NULL;
                    while (argv[d] != NULL)
                        {
                                x = 0;
                                while (my_aliases[x].alias_name != NULL)
                                {
                                        if (strcmp(argv[d], my_aliases[x].alias_name) == 0)
                                        {
                                                s = my_aliases[x].alias_name;
                                                y = my_aliases[x].real_name;
                                                write(STDOUT_FILENO, s, strlen(s));
                                                write(STDOUT_FILENO, "=", 1);
                                                write(STDOUT_FILENO, t, strlen(t));
                                                write(STDOUT_FILENO, y, strlen(y));
                                                write(STDOUT_FILENO, t, strlen(t));
                                                write(STDOUT_FILENO, "\n", 1);
                                        }
                                        x++;
                                }
                                d++;
                        }
            }
            x = 0;
            int z = 0;
            if (g > 0)
            {
                s = strtok(user_input,"='");
                printf("%s", s);
                while (my_aliases[x].alias_name != NULL)
                {
                        x++;
                }
                while (my_aliases[z].alias_name != NULL)
                {
                        if (strcmp(s, my_aliases[z].alias_name) == 0)
                        {
                                my_aliases[x].alias_name = strdup(s);
                                s = strtok(NULL,"'");
                                my_aliases[x].real_name = strdup(s);
                                printf("%s", s);
                                x++;
                                my_aliases[x].alias_name = NULL;
                                my_aliases[x].real_name = NULL;
                                return(0);
                        }
                        z++;
                }
                my_aliases[x].alias_name = strdup(s);
                s = strtok(NULL,"'");
                my_aliases[x].real_name = strdup(s);
                printf("%s", s);
                x++;
                my_aliases[x].alias_name = NULL;
                my_aliases[x].real_name = NULL;
            }
        return(0);
    }
    if (strcmp(user_input, "alias") == 0)
    {
            while (my_aliases[x].alias_name != NULL)
            {
                s = my_aliases[x].alias_name;
                y = my_aliases[x].real_name;
                write(STDOUT_FILENO, s, strlen(s));
                write(STDOUT_FILENO, "=", 1);
                write(STDOUT_FILENO, t, strlen(t));
                write(STDOUT_FILENO, y, strlen(y));
                write(STDOUT_FILENO, t, strlen(t));
                write(STDOUT_FILENO, "\n", 1);
                x++;
            }
            return(0);
    }
}
