#include <stdio.h> 
#include <string.h> 
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/wait.h> 
#include "history.h"
#include "smash.h"

void executeCommand(char *str) {
  char *args[4096];
  
  char* token = strtok(str, " "); // Retrieves first argument (in this case, the command)
  args[0] = token; // Set args[0] to the command chosen
  if (args[0] == NULL) {
    return;
  }  
 
  int index = 1;
  while (token != NULL) { //build args array
        token = strtok(NULL, " ");
        args[index] = token;
        index++;
  }
  args[index] = NULL;
  int argc = index - 1;
  
  if(strcmp(args[0], "cd") == 0) { // cd command chosen
    int exitStatus = 0;
    if(args[1] != NULL) {
      exitStatus = chdir(args[1]);
      
      if(exitStatus == 0) {
        puts(args[1]);
      }
      
      else if (exitStatus == -1) {
        perror(args[1]);
        exitStatus = 1;
      }
    }
    add_history(str, exitStatus);
  }
  else if(strcmp(args[0], "history") == 0) { // history command chosen
  add_history(str, 0);
    print_history(0);
  }
  
  else if(strcmp(args[0], "exit") == 0) { // exit command chosen
    exit(0);
  }
  
  else { // Unrecognised command
    int exitStatus;
    exitStatus = executeExternalCommand(args);
    char line[4096];
    strcpy(line, "");
    for (int i = 0; i < argc; i++) {
      strcat(line, args[i]);
      if (i < argc - 1) {
        strcat(line, " ");
      }
    }
    add_history(line, exitStatus);
  }
    
}

int executeExternalCommand(char **argv) {
  pid_t childID = fork(); // create two processes...
  int exitStatus = 0;
  
  if (childID < 0) { // error
    exit(1);
  }
  
  else if (childID == 0) { // child: execution
    if (execvp(argv[0], argv) == -1) {
      perror(argv[0]);
    }
    exit(execvp(argv[0], argv));
  }
  
  else { // parent: exit status
    int status;
    if (waitpid(childID, &status, 0) != -1) {
      if (WIFEXITED(status)) {
        int returned = WEXITSTATUS(status);
        return returned;
      }
    }
  }
  return exitStatus;
}