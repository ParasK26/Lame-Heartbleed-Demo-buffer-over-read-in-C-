/**
 * The following is a really basic demonstration of a heartbleed vulnerability exploit
 * Author: ParasK26
 * Date: 10/04/2019
 **/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define BUFFERSIZE 500
#define COMMANDSIZE 20

int isPrintable(char toCheck) {
	if (toCheck > 31 && toCheck < 127) {
	       return 1;
	}
	return 0;
}	

void delay(int time) {
	time_t start = clock(), ticksRequired = time * CLOCKS_PER_SEC;
	while (clock() - start < ticksRequired);
}

void printInstructions() {
	printf("... The fake heartbleed vulnerable server is live! To exit just enter \"exit\"\n");
	printf("Since our server uses no bounds checking on the heartbeat, enter a huge payload size and uncover the secret!\n");
	printf("Send your heartbeat request in the form \"heartbeat <payload> <size of payload>\"\n");
}

int main(void) {
	char buffer[BUFFERSIZE] = {0}, command[COMMANDSIZE];
	int payloadSize, i, j, pos;
	printf("Initializing heartbleed demo...\n\n");
	delay(2);
	printInstructions();
	strcpy(&buffer[50], "SECRET TIME!!!!!!!!!!! SeCreTs @re $@cr3d: This is a lame heartbleed demo"); 

	do {
		printf("\nEnter your command below:\n");
		scanf("%s", command);
		if (strcmp(command, "heartbeat") == 0) {
			scanf("%s %d", buffer, &payloadSize);
			printf("\nSending heartbeat packet...\n");
			delay(1);
			printf("... Response Received!\n\n");
			for (i = 0; i < payloadSize && i < BUFFERSIZE; i = pos) {
				pos = i;
				for (j = 0; j < 10 && pos < payloadSize && pos < BUFFERSIZE; j++) {
					printf("%2x ", buffer[pos++]);
				}
				for (; j < 10; j++) {
					printf("   ");
				}

				printf("\t");
				pos = i;

				for (j = 0; j < 10 && pos < payloadSize && pos < BUFFERSIZE; j++) {
					if (isPrintable(buffer[pos])) {
						printf("%c", buffer[pos]);
					} else {
						printf(".");
					}
					printf(" ");
					pos++;
				}
				printf("\n");
			}
		} else if (strcmp(command, "exit") != 0) {
			fflush(stdin);
			printf("Invalid command!\n");
			printInstructions();
		}
	} while (strcmp(command, "exit") != 0);
	printf("\n.......Exiting programme. BYE!!\n");
	return 0;
}
