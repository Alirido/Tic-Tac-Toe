#include <stdio.h>
#include <string.h>

#define bool int
#define true 1
#define false 0
#define emptyString ""

struct TransitionFunction {
	char state[12];
	int action[10]; // input 1 . . 9
	int fs;
	/*
		fs -> final state
		0 = Not final state
		1 = Computer Win
		2 = Draw
	*/ 
} tf[60000];

int hashing(char temp[]) { // String to int (hashing)
	int i=1;
	int result = 0;
	if (strcmp(temp,"q0") && strcmp(temp,"0")) {
		while (temp[i] != 'c') {
			result = (temp[i]-'0') + result*10;
			i++;
		}
	}
	return result;
}

bool isWin(char temp[]) {
	// Kemaren kenapa dihapus, padahal dipake :(
	bool cell[10] = {false};
	int n = strlen(temp)-1;
	while (temp[n] != 'c') {
		cell[temp[n] - '0'] = true;
		n--;
	}
	if ((cell[1] && cell[2] && cell[3]) || (cell[4] && cell[5] && cell[6]) ||
		(cell[7] && cell[8] && cell[9]) || (cell[1] && cell[4] && cell[7]) ||
		(cell[2] && cell[5] && cell[8]) || (cell[3] && cell[6] && cell[9]) ||
		(cell[1] && cell[5] && cell[9]) || (cell[3] && cell[5] && cell[7]))
		return true;
	else return false;
}

void showInstructions() {
	printf("\t\t\t  Tic-Tac-Toe\n\n"); 
    printf("Choose a cell numbered from 1 to 9 as below"
            " and play\n\n"); 
      
    printf("\t\t\t  1 | 2  | 3  \n"); 
    printf("\t\t\t--------------\n"); 
    printf("\t\t\t  4 | 5  | 6  \n"); 
    printf("\t\t\t--------------\n"); 
    printf("\t\t\t  7 | 8  | 9  \n\n"); 
    printf("Player will play as X.\n");
    printf("Computer will play as O.\n");
      
    printf("-\t-\t-\t-\t-\t-\t-\t-\t-\t-\n\n"); 
}

void viewBoard(int cs) {
	char board[10] = {' '};
	if (!strcmp(tf[cs].state, "q0")) {
		printf("\t\t\t    |    |    \n"); 
    	printf("\t\t\t--------------\n"); 
    	printf("\t\t\t    |    |    \n"); 
    	printf("\t\t\t--------------\n"); 
    	printf("\t\t\t    |    |    \n\n"); 
	} else {
		int i=1;
		while (tf[cs].state[i] != 'c') {
			board[tf[cs].state[i] - '0'] = 'X';
		}
		i++;
		for (i; i<strlen(tf[cs].state); i++) {
			board[tf[cs].state[i] - '0'] = 'O';
		}
		printf("\t\t\t  %c | %c  | %c  \n", board[1], board[2], board[3]); 
   		printf("\t\t\t--------------\n"); 
   		printf("\t\t\t  %c | %c  | %c  \n", board[4], board[5], board[6]); 
   		printf("\t\t\t--------------\n"); 
   		printf("\t\t\t  %c | %c  | %c  \n\n", board[7], board[8], board[9]);
	}
}

bool isValid(int x, int current_state) {
	if (x<1 || x>9)
		return false;
	else {
		int n = strlen(tf[current_state].state)-1;

		while (x != (tf[current_state].state[n] - '0') && n>=0) n--;
		if (n>=0)
			return true;
		else return false;
	}
}

int main() {
	// READ TEXT FILE (EXTERNAL) and Translate to machine logic
	FILE *fp; // fp = file pointer
	
	if ((fp = fopen("DFA.TXT", "r")) == NULL) {
		printf("ERROR - Could not open the DFA.txt file\n");
		return 1;
	}

	char c;
	while (c != EOF) {
		int i=0;
		char s[22];
		while ((c = fgetc(fp)) != ':') {
			s[i] = c;
			i++;
		}
		s[i] = '\0';
		printf("%s\n", s);
		if (!strcmp(s, "Transition function")) {
			printf("MASUK TRANSITION FUNCTION NGGA?\n");
			c = fgetc(fp);
			while (c != EOF) {
				if ((c = fgetc(fp)) != '*') {
					int j=0, idx;
					while (c != '\n' && c != EOF) {
						char tmp[13];
						i=0;
						while (c != ' ' && c != '\n' && c != EOF) {
							tmp[i] = c;
							i++;
							c = fgetc(fp);
						}
						if (!j) {
							idx = hashing(tmp);
							strcpy(tf[idx].state, tmp);
						}
						else {
							tf[idx].action[j] = hashing(tmp);
						}
						j++;
						if (c==' ')
							c = fgetc(fp);
					}
				} else {
					printf("FINAL STATEEE!\n");
					while ((c = fgetc(fp)) != '\n');
				}
			}
		} else if (!strcmp(s, "State akhir")) {

			c = fgetc(fp);

			while (c != '\n') {
				char tmp[13];
				i=0;

				c = fgetc(fp);
				while (c != ' ' && c != '\n') {
					tmp[i] = c;
					i++;
					c = fgetc(fp);
				}
				tmp[i] = '\0';

				int idx = hashing(tmp);
				if (isWin(tmp)) {

					//Debugging
					printf("MENAANGGG!\n");

					tf[idx].fs = 1;
				}
				else {

					//Debugging
					printf("SERIIIII!\n");

					tf[idx].fs = 2;
				}
				strcpy(tf[idx].state, tmp);
			}
		} else {
			printf("Debugging #1: %s\n", s);
			while ((c = fgetc(fp)) != '\n');
		}
	}

	fclose(fp);

	// MULAI PERMAINAN TIC TAC TOE
	showInstructions();
	int current_state=0;
	int trackRecord[10] = {0}; // For showing what states have been passed
	int i = 1, x;
	viewBoard(current_state);
	while (tf[current_state].fs != 1 && tf[current_state].fs != 2) {
		printf("Enter the number: ");
		scanf("%d", &x);
		while (!isValid(x, current_state)) {
			if (x>=1 && x<=9) {
				printf("The cell number was already filled\n");
			} else {
				printf("Invalid input - Please enter a number between 1 and 9 (inclusive)\n");
			}
			printf("Enter the number: ");
			scanf("%d", &x);
		}

		current_state = tf[current_state].action[x];
		trackRecord[i] = current_state;
		viewBoard(current_state);
		i++;
	}

	if (tf[current_state].fs == 1) {
		printf("Well played! Unfortunately, Computer has won\n");
	} else {
		printf("DRAW. You were doing great\n");
	}
	printf("Try again later :)\n\n");
	
	printf("States that have been passed:\n");
	for (int j=0; j<i; j++) {
		printf("%s ", tf[trackRecord[j]].state);
	}

	return 0;
}