#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/utsname.h>
#include <unistd.h>

#define MAX_LENGTH 1024                  
#define DELIMS " \t\r\n"                                    
                                                           

int main(int argc, char *argv[]) {
  struct utsname detect;
  uname(&detect);

  char *cmd;
  char line[MAX_LENGTH];

  while (1) {
    printf("%s-%s:~$ ",detect.nodename, detect.sysname);
    if (!fgets(line, MAX_LENGTH, stdin)) break;

    // Parse and execute command
    if ((cmd = strtok(line, DELIMS))) {
      // Clear errors
      errno = 0;

      if (strcmp(cmd, "cd") == 0) {
        char *arg = strtok(0, DELIMS);

        if (!arg) fprintf(stderr, "cd missing argument.\n");
        else chdir(arg);

      } else if (strcmp(cmd, "exit") == 0) break;
        else system(line);

      if (errno) perror("Command failed");
    }
  }

  return 0;

}