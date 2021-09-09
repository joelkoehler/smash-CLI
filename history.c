#include <stdio.h>
#include <stdlib.h>
#define MAXHISTORY 10
#include <string.h>
#include "history.h"

extern char* strdup(const char* str);

struct Cmd hist[MAXHISTORY];
int currentPos = 0;
int wrap = 0;

void init_history(void) {
	for(int i = 0; i < MAXHISTORY; i++) {
		hist[i].cmd = NULL;
		hist[i].exitStatus = -1; 
	}
}

void add_history(char *cmd, int exitStatus) {
	if(hist[currentPos % MAXHISTORY].cmd != NULL)  {
		free(hist[currentPos % MAXHISTORY].cmd);
		hist[currentPos % MAXHISTORY].exitStatus = -1;
	}

	//hist[currentPos % MAXHISTORY].cmd = (char *) malloc(sizeof(cmd));
	(hist[currentPos % MAXHISTORY]).cmd = strdup(cmd);
	//strncpy(hist[currentPos % MAXHISTORY].cmd) = hist[currentPos % MAXHISTORY].cmd;
	hist[currentPos % MAXHISTORY].exitStatus = exitStatus;
	currentPos++;
	if (currentPos == MAXHISTORY) {
		currentPos = 0;
		wrap = 1;
	}
}

void clear_history(void) {
	for(int i = 0; i < MAXHISTORY; i++) {
		free(hist[i].cmd);
		hist[i].exitStatus = -1;
	}
}

void print_history(int firstSequenceNumber) {
	int listNumber = 1;
	if(wrap == 1) {
		for(int i = currentPos; i < MAXHISTORY; i++) {
			printf("%d [%d] %s\n", listNumber++, hist[i].exitStatus, hist[i].cmd);
		}
	}
	for(int i = 0; i < currentPos; i++) {
		printf("%d [%d] %s\n", listNumber++, hist[i].exitStatus, hist[i].cmd);
	}
}
