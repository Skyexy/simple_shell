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
	extern char **environ;
	char *path;
	int i = 0;

	while(*environ)
	{
       
		if(strncmp(*environ, "HOME",4) == 0)
       
		{
               
			path = strdup(*environ);
			while(*path && i < 4)
                        {
				path++;
				i++;
			}
			break;
		}
		environ++;
	}
	if (argv[1] == NULL)
	{
		chdir(path);
		return (0);
	}
	else if (strcmp("-",argv[1]) == 0)
	{
		chdir("-");
		return (0);
	}
	else
	{
		if (chdir(argv[1]) == -1)
		{
			perror("Error");
			return (-1);
		}
	}
	return (0);
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
int execute(char** argv)
{
	if (access(argv[0],F_OK)==0)
	{
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
		return(0);
        }
	else
	{
		write(STDOUT_FILENO, "Command is not available in the bin\n",36);
		return (1);
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
			break;
		}
		x++;
	}
	chdir(cwd);
    }
	x = execute(argv);
	return(x);
}
int divd(char *user_input)
{
	int x = 0;
	char *token;
	char *argv[BUFFER_LEN];
	int argc = 0;

	if(strncmp(user_input, "alias",5) == 0)
	{
		_aliass(user_input);
		return (0);
	}
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
	while(token!=NULL)
	{
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
	x = exv(argv);
	return(x);
}
int comma(char *user_input)
{
	char *token;
	char *argv[BUFFER_LEN];
	int x = 0;

	token = strtok(user_input,";");
	while(token != NULL)
	{
		argv[x] = strdup(token);
		token = strtok(NULL,";");
		x++;
	}
	argv[x] = NULL;
	x = 0;
	while(argv[x] != NULL)
	{
		divd(argv[x]);
		x++;
	}
	return (0);
}
int check(char *s, char sign)
{
	int i = 0;
	int y = 0;

	while(s[i] != '\0')
	{
		if(s[i] == sign)
		{
			y++;
		}
		i++;
	}
	return(y);
}
int _aliass(char *user_input)
{
	char *s = malloc(sizeof(char) * BUFFER_LEN);
	char *y = malloc(sizeof(char) * BUFFER_LEN);
	char *argv[BUFFER_LEN];
	char *t = t = "'";
	int x = 0;
	int g;
	int d = 0;
	char *token;
	int argc;
	int z;
	if (strncmp(user_input, "alias ",6) == 0)
	{
		user_input = user_input + 6;
		g = check(user_input, '=');
		if (g == 0)
		{
			token = strtok(user_input," ");
			printf("%s", token);
			argc = 0;
			while(token!=NULL)
			{
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
		z = 0;
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
					my_aliases[z].alias_name = strdup(s);
					s = strtok(NULL,"'");
					my_aliases[z].real_name = strdup(s);
					printf("%s", s);
					x++;
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
	return (0);
}
int join(char *user_input)
{
	char *token;
	char *argv[BUFFER_LEN];
	int x = 0;
	int y = 0;

	token = strtok(user_input,"&");
	while(token != NULL)
	{
		argv[x] = strdup(token);
		token = strtok(NULL,"&");
		x++;
	}
	argv[x] = NULL;
	x = 0;
	while(argv[x] != NULL && y == 0)
	{
		y = divd(argv[x]);
		x++;
	}return (0);
}
int phars(char *user_input)
{
	char *token;
	char *argv[BUFFER_LEN];
	int x = 0;
	int y = 1;

	token = strtok(user_input,"||");
	while(token != NULL)
	{
		argv[x] = strdup(token);
		token = strtok(NULL,"||");
		x++;
	}
	argv[x] = NULL;
	x = 0;
	while(argv[x] != NULL && y == 1)
	{
		y = divd(argv[x]);
		x++;
	}
	return (0);
}
int cont(char *userinput, char s)
{
	char *path = strdup(userinput);
	int x = 0;
	int y = 0;
	int c = 0;
	
	while(path[x] != '\0')
	{
		if (path[x] == s && path[x+1] == s)
		{
			x = x + 2;
			y++;
			if(path[x] == s)
			{
				while(path[x] == s)
				{
					x++;
					c--;
				}
				return(c);
			}
		}
		x++;
	}
	return (y);
}
int seprators(char *user_input)
{
	int x;

	x = _check(user_input, ';');
	if (x != 0)
	{
		if (x > 0)
		{
			comma(user_input);
		}
		else
		{
			perror("Error");
		}
		return (1);
	}
	x = cont(user_input, '&');
	if (x != 0)
	{
		if (x > 0)
		{
			join(user_input);
		}
		else
		{
			perror("Error");
		}
		return (1);
	}
	x = cont(user_input, '|');
	if (x != 0)
	{
		if (x > 0)
		{
			phars(user_input);
		}
		else
		{
			perror("Error");
		}
		return (1);
	}
	x = check(user_input, '#');
	if (x > 0)
	{
		coment(user_input);
		return (1);
	}
	return(0);
}
int _check(char *s, char sign)
{
        int i = 0;
        int y = 0;
        
	while(s[i] != '\0')
	{
		if(s[i] == sign)
		{
			i++;
			y++;
			if (s[i] == sign)
			{
				i++;
				return(-1);
			}
		}
		i++;
	}
	return(y);
}
int coment(char *userinput)
{
	char *token;

	token = strtok(userinput,"#");
	if (token != NULL)
	{
		divd(token);
	}
	return (0);
}
