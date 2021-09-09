#ifndef HISTORY_H
#define HISTORY_H
//Define the layout of a single entry in the history array
  struct Cmd {
    char* cmd; //A saved copy of the user’s command string
    int exitStatus; //The exit status from this command
  };
  
  //Define the maximum number of entries in the history array
  #define MAXHISTORY 10 //Smash will save the history of the last 10 commands
  
  //Function prototypes for the command history feature
  void init_history(void); //Builds data structures for recording cmd history
  void add_history(char *cmd, int exitStatus); //Adds an entry to the history
  void clear_history(void); //Frees all malloc’d memory in the history
  void print_history(int firstSequenceNumber); //Prints the history to stdout
#endif
