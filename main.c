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
		1 = Win
		2 = Draw
	*/ 
} tf[60000];

// TransitionFunction tf[60000][10];
// bool win[60000], draw[60000]; // Final State

bool isWin(char temp[]) {
	// Check if state(string) is final state or not
	bool a[10] = {false};
	int n = strlen(temp);
	while (temp[n-1] != 'c') {
		a[temp[n-1]-'0'] = true;
		n--;
	}
	if ((a[1] && a[2] && a[3]) || (a[4] && a[5] && a[6]) ||
		(a[7] && a[8] && a[9]) || (a[1] && a[4] && a[7]) ||
		(a[2] && a[5] && a[8]) || (a[3] && a[6] && a[9]) ||
		(a[1] && a[5] && a[9]) || (a[3] && a[5] && a[7]))
		return true;
	else return false;
}

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
	printf("")

	// MINTA PLAYER UNTUK MEMASUKKAN AKSI BERUPA INT DARI 1 - 9
	// SETIAP AKSI TAMPILKAN CURRENT BOARD
	// GUNAKAN FUNGSI UNTUK MMENJALAN SETIAP AKSI PADA MACHINE

	// SETELAH MENCAPAI FINAL STATE, KELUARKAN PESAN ENTAH DRAW, LOSE, ATAU WIN

	return 0;
}