#include <iostream>
#include <ctime>
using namespace std;
clock_t time1, time2;

void cacheEx(){
// Ovaj snippet bi trebao prikazivat da brzina do 64B ostaje relativno ista, a sve poslje toga drasticno otpada, teorija != praksa
	int v = 256*1024*1024;
	int *polje = new int[v];
	for(int i = 1; i < 1025; i <<= 1){
		cout << i << endl;
		time1 = clock();
		for (int j = 0; j < v; j += i) polje[j] = i; //polje[i]++
		time2 = clock();
		cout << "Vrijeme: " << time2 - time1 << endl;	
	}
}

void somethingWentWrongHere(){
	int v = 256*1024*1024;
	int *polje2 = new int[v];
	int vMod = v - 1;
	for(int j = 1; j < 257; j <<= 1){
		time1 = clock();
		for (int i = 0; i < v; i++) {
	    	polje2[(i * j) & v]++; 
		}
		time2 = clock();
		cout << "Vrijeme: " << time2 - time1 << endl;

	}
}

void thruPutEx() {
//Demonstracija propusnosti koja prikazuje produljeno vrijeme operacije ako se odvija na istoj memorijskoj lokaciji
	int v = 256*1024*1024;
	int *polje2 = new int[2];
	time1 = clock();
	for (int i=0; i<v; i++) { 
		polje2[0]++; 
		polje2[0]++; 
		
	}
	time2 = clock();
	cout << "Vrijeme: " << time2 - time1 << endl; 

	time1 = clock();
	for (int i=0; i<v; i++) { 
		polje2[0]++; 
		polje2[1]++; 
	}
	time2 = clock();
	cout << "Vrijeme: " << time2 - time1 << endl;
}

void cacheEx2(){
//Ovaj snipet prikazuje razliku izmedu zbrajanja 2D polja po asimptoti najprije, a onda po ordinati najprije
	int *polje3[1024][1024];
	
	time1 = clock();
	for (int i=0; i<1024; i++) { 
		for (int j = 0; j < 1024; j++){
			polje3[i][j]++;
		}
	}
	
	time2 = clock();
	cout << "Vrijeme: " << time2 - time1 << endl;

	time1 = clock();
	for (int i=0; i<1024; i++) { 
		for (int j = 0; j < 1024; j++){
			polje3[j][i]++;
		}
	}
	
	time2 = clock();
	cout << "Vrijeme: " << time2 - time1 << endl;
}


int main() {
	
	int izbor;
	do{
		
		cout << "1. Demonstracija utjecaja cache memorije preko 2D polja" << endl;
		cout << "2. Demonstracija necega što ne radi" << endl;
		cout << "3. Demonstracija propusnosti" << endl;
		cout << "4. Demonstracija utjecaja cache memorije koja ne radi" << endl;
		cin >> izbor;
		switch(izbor){
			case 1:
				cacheEx2();
				break;
			case 2:
				somethingWentWrongHere();
				break;
			case 3:
				thruPutEx();
				break;
			case 4:
				cacheEx();
				break;
		}
		
	}while(izbor != 9);

	return 0;
	
	
}
