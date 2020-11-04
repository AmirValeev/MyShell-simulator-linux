#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>

char* get_str()
{
	char *s = (char *) malloc(10 * sizeof(char));
	if (s == NULL)
  {
		printf("OS didn't gave memory\n");
		exit(1);
	}
	int len = 10, n, pos=0;
	while(fgets(s+pos, 10, stdin))
  {
		n = strlen(s);
		if (s[n-1] != '\n')
    {
			pos = n;
			len+= 10;
			s = (char *)realloc(s, len*sizeof(char));
      if (s == NULL)
      {
        printf("OS didn't gave memory\n");
        exit(1);
      }
		} else {
			s[n-1] = '\0';
			return s;
		}
	}
	free (s);
	return NULL;
}


char** shell_split_str(char* str)
{
  int i = 0, pos = 0, word_number = 0;
  char manage_symbols[] = "&|;><()";
  char **words = (char**)malloc(sizeof(char*));
  char *word = (char*)malloc(sizeof(char));

  while (*(str+pos) != '\0')
  {
    if ((*(str+pos) == ' ') || (*(str+pos) == '\t'))
    {
      pos++;
      continue;
    }
    if (strchr(manage_symbols, *(str+pos)))
    {
      word[i++] = *(str+pos);
      word = (char*)realloc(word, (i+1) * sizeof(char));
      if (!strchr(manage_symbols, *(str+pos+1)) || (*(str+pos+1) == '\0'))
      {
        word[i] = '\0';
        words[word_number] = word;
        word = (char*)malloc(sizeof(char));
        word_number++;
        words = (char**)realloc(words, (word_number+1) * sizeof(char*));
        i = 0;
      }
      pos++;
      continue;
    }
    word[i++] = *(str+pos);
    word = (char*)realloc(word, (i+1)*sizeof(char));
    if ((*(str+pos+1) == ' ') || (*(str+pos+1) == '\t') || (*(str+pos+1) == '\0') || (strchr(manage_symbols, *(str+pos+1))))
    {
      word[i] = '\0';
      words[word_number] = word;
      word = (char*)malloc(sizeof(char));
      word_number++;
      words = (char**)realloc(words, (word_number+1) * sizeof(char*));
      i = 0;
    }
    pos++;
  }

  free(word);
  words[word_number] = NULL;
  return words;
}

void free_args(char **args)
{
  int i = 0;
  while (args[i]) {
    free(args[i++]);
  }
  free(args);
}


void shell_loop()
{
  int i=0;
  char *str;
  char **args;
  while ((str = get_str()))
  {
    i = 0;
    args = shell_split_str(str);
    free(str);
    while (args[i])
    {
      printf("%s\n", args[i]);
      i++;
    }
    free_args(args);
  }
}


int main(int argc, char **argv) {
  if (argc == 2)
  {
    int fd;
    if ((fd = open(argv[1], O_RDONLY)) == -1)
    {
      printf("Error while opening file\n");
      exit(1);
      close(fd);
    }
    dup2(fd, 0);
  }
  shell_loop();
  return 0;
}
