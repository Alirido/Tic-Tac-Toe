#include <stdio.h>

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
	result = 0;
	if (temp != "qo" || temp != '0') {
		while (temp[i] != 'c' ||) {
			result = (temp[i]-'0') + result*10;
			i++;
		}
	}
	return result;
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
	int board[10] = {0};
	if (tf[cs].state == "qo") {
		printf("\t\t\t    |    |    \n"); 
    	printf("\t\t\t--------------\n"); 
    	printf("\t\t\t    |    |    \n"); 
    	printf("\t\t\t--------------\n"); 
    	printf("\t\t\t    |    |    \n\n"); 
	} else {
		int i=1;
		while (tf[cs].state[i] != 'c') {
			board[tf[cs].state[i] - '0'] = 1;
		}
		i++;
		for (i; i<tf[cs].state.length(); i++) {
			board[tf[cs].state[i] - '0'] = 2;
		}
		
	}
}

int main() {
	// READ TEXT FILE (EXTERNAL) and Translate to machine logic
	FILE *fp; // fp = file pointer
	
	if ((fp = fopen("DFA.TXT", "r")) == null) {
		printf("ERROR - Could not open the DFA.txt file\n");
		return 1;
	}

	char c;
	while (c != EOF) {
		int i=0;
		char s[22];
		while ((c = fgetc()) != ':') {
			s[i] = c;
			i++;
		}
		c = fgetc();
		if (s == "Transition function") {
			while (c != EOF) {
				if ((c = fgetc()) != '*') {
					int j=0, idx;
					while (c != '\n' && c != EOF) {
						char tmp[13];
						i=0;
						while (c != ' ' && c != '\n' && c != EOF) {
							tmp[i] = c;
							i++;
							c = fgetc();
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
							c = fgetc();
					}
				} else while ((c = fgetc()) != '\n');
			}
		} else if (s == "State akhir") {
			while (c != '\n') {
				char tmp[13];
				i=0;
				while ((c = fgetc()) != ' ' && c != '\n') {
					tmp[i] = c;
					i++;
				}
				int idx = hashing(tmp);
				if (isWin(tmp)) {
					tf[idx].fs = 1;
				}
				else {
					tf[idx].fs = 2;
				}
				strcpy(tf[idx].state, tmp);
			}
		} else {
			while ((c = fgetc()) != '\n');
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
		while (!isValid(x)) {
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
	
	printf("States that have been passed:\n")
	for (int j=0; j<i; j++) {
		printf("%s ", tf[trackRecord[j]].state);
	}

	return 0;
}