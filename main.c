#include <stdio.h>

#define bool int
#define true 1
#define false 0

int tf[60000][9]; // Transition Function
bool win[60000], draw[60000]; // Final State

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
	if (temp != "qo") {
		while (temp[i] != 'c' ||) {
			result = (temp[i]-'0') + result*10;
			i++;
		}
	}
	return result;
}

int main() {
	// Deklarasi variable
	// READ TEXT FILE (EXTERNAL)
	FILE *fp; // fp = file pointer
	
	if ((fp = fopen("DFA.TXT", "r")) == null) {
		printf("ERROR - Could not open the DFA.txt file\n");
		return 1;
	}

	char c;
	char tmp[20] = "";
	while (c != EOF) {
		while ((c = fgetc()) != ':')
			temp += c;
		c = fgetc();
		if (tmp == "Transition function") {
			while (c != EOF) {
				if ((c = fgetc()) != '*') {
					while (c != '\n' && c != EOF) {
						tmp = "";
						while (c != ' ' && c != '\n' && c != EOF) {
							tmp += 
						}
					}
				}
			}
		} else if (tmp == "State akhir") {
			while (c != '\n') {
				tmp = "";
				while ((c = fgetc()) != ' ' && c != '\n') {
					tmp += c;
				}
				if (isWin(tmp))
					win[hashing(tmp)] = true;
				else draw[hashing(tmp)] = true;
			}
		} else {
			while ((c = fgetc()) != '\n');
		}
	}

	fclose(fp);

	// FUNGSI UNTUK MENERJEMAHKAN INPUT KEDALAM LOGIKA MACHINE

	// MULAI PERMAINAN TIC TAC TOE
	// MINTA PLAYER UNTUK MEMASUKKAN AKSI BERUPA INT DARI 1 - 9
	// SETIAP AKSI TAMPILKAN CURRENT BOARD
	// GUNAKAN FUNGSI UNTUK MMENJALAN SETIAP AKSI PADA MACHINE

	// SETELAH MENCAPAI FINAL STATE, KELUARKAN PESAN ENTAH DRAW, LOSE, ATAU WIN

	return 0;
}