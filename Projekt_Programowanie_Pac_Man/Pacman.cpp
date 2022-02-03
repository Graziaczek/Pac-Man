#include <iostream>
#include <conio.h>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <string>
using namespace std;
int punkty{};
int zycia = 3;
int licznik = 30; //licznik czasu oszo�onienia
bool gra = true; //zmienna logiczna decyduj�ca o tym kiedy procesy gry maj� by� uruchomione
bool stop = false; //zmienna decyduj�ca kiedy zresetowa� pozycje duszk�w i gracza
struct pozycja { //struktura opisuj�ca ka�d� poruszaj�c� si� istot� w grze
	int x;
	int y;
	int kierunek;
	char pole;
	char nazwa;
	bool stan; //potrzebne do odpalenia oszo�omienia
};
pozycja oszolomienie(char tab[16][17], pozycja duszek);
pozycja graczReset(char tab[16][17], pozycja gracz);
pozycja clydeReset(char tab[16][17], pozycja clyde);
pozycja inkyReset(char tab[16][17], pozycja inky);
pozycja pinkyReset(char tab[16][17], pozycja pinky);
pozycja blinkyReset(char tab[16][17], pozycja blinky);
void gameOver();
void wygrana();
void graPacMan();
void menu();
void wyswietlaniePlanszy(char tab[16][17], int x, int y) {
	int kulki{};
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			cout << tab[i][j] << " ";
			if (tab[i][j] == '.') {
				kulki += 1;
			}
		}
		cout << endl;
	}
	cout << "Punkty:    " << punkty << endl;
	cout << "�ycia:     " << zycia << endl;
	if (kulki == 0) { //sprawdza czy wszystkie punkty zosta�y zjedzone i czy nas�pi�a wygrana
		wygrana();
	}
}
void wyniki_wyswietl() { //wy�wietla sal� chwa�y
	fstream plik1("wyniki.txt",ios::in);
	string nazwa;
	int p;
	char odp{};
	while (plik1) {
		plik1 >> nazwa;
		plik1 >> p;
		cout << nazwa << " " << p << endl;
		nazwa = ' ';
		p = 0;
	}
	plik1.close();
	cout << endl;
	cout << "1. Powr�t" << endl;
	cout << "2. Wyczy��" << endl;
	while (true) {
		cin >> odp;
		if (odp == '1') {
			system("cls");
			break;
		}
		if (odp == '2') {
			fstream plik2("wyniki.txt", ios::out | ios::trunc);//otwiera plik tekstowy czyszcz�c go przy okazji
			plik2.close();
			system("cls");
			break;
		}
	}
}
void wyniki_zapis() {//zapisuje wyniki z sali chwa�y
	fstream plik;
	plik.open("wyniki.txt", ios::out|ios::app);
	string nazwa;
	cout << "Podaj nazw�:" << endl;
	cin >> nazwa;
	plik << nazwa << endl;
	plik << punkty << endl;
	plik.close();
}
pozycja ruchGracza(char tab[16][17], pozycja p, pozycja blinky, pozycja pinky, pozycja inky, pozycja clyde) {//ruch pacmana
	switch (p.kierunek) {//na podstawie kierunku poruszania si� wybiera w kt�r� stron� ma przemie�ci� pacmana
	case 1:
		if (tab[p.x + 1][p.y] != '#') {
			if (tab[p.x + 1][p.y] == '.')
				punkty += 1;
			if (tab[p.x + 1][p.y] == '*') {//zmienia stan duszka co p�niej determinuje uruchomienie oszo�omienia
				p.stan = 0;
				licznik = 30;
			}
			if ((tab[p.x + 1][p.y] == tab[blinky.x][blinky.y]|| tab[p.x + 1][p.y] == tab[pinky.x][pinky.y] || tab[p.x + 1][p.y] == tab[inky.x][inky.y] || tab[p.x + 1][p.y] == tab[clyde.x][clyde.y]) && p.stan == 1) {//sprawdza czy natkni�to si� na duszka, i je�eli tak - czy nie jest w stanie oszo�omienia
				zycia -= 1;
				if (zycia == 0)
					gameOver();
				stop = true;
				break;
			}
			tab[p.x][p.y] = ' ';
			p.x += 1;
			tab[p.x][p.y] = 'G';//podmienia pozycj� w tablicy
		}
		break;
	case 2:
		if (tab[p.x - 1][p.y] != '#' && tab[p.x - 1][p.y] != '-') {
			if (tab[p.x - 1][p.y] == '.')
				punkty += 1;
			if (tab[p.x - 1][p.y] == '*') {
				p.stan = 0;
				licznik = 30;
			}
			if ((tab[p.x - 1][p.y] == tab[blinky.x][blinky.y] || tab[p.x - 1][p.y] == tab[pinky.x][pinky.y] || tab[p.x - 1][p.y] == tab[inky.x][inky.y] || tab[p.x - 1][p.y] == tab[clyde.x][clyde.y]) && p.stan == 1) {
				zycia -= 1;
				if (zycia == 0)
					gameOver();
				stop = true;
				break;
			}
			tab[p.x][p.y] = ' ';
			p.x -= 1;
			tab[p.x][p.y] = 'G';
		}
		break;
	case 3:
		if (tab[p.x][p.y + 1] != '#' && tab[p.x][p.y + 1] != '-') {
			if (tab[p.x][p.y + 1] == '.')
				punkty += 1;
			licznik = 30;
			if (tab[p.x][p.y + 1] == '*') {
				p.stan = 0;
			}
			if ((tab[p.x][p.y + 1] == tab[blinky.x][blinky.y] || tab[p.x][p.y + 1] == tab[pinky.x][pinky.y] || tab[p.x][p.y + 1] == tab[inky.x][inky.y] || tab[p.x][p.y + 1] == tab[clyde.x][clyde.y]) && p.stan == 1) {
				zycia -= 1;
				if (zycia == 0)
					gameOver();
				stop = true;
				break;
			}
			tab[p.x][p.y] = ' ';
			p.y += 1;
			tab[p.x][p.y] = 'G';
		}
		break;
	case 4:
		if (tab[p.x][p.y - 1] != '#' && tab[p.x][p.y - 1] != '-') {
			if (tab[p.x][p.y - 1] == '.')
				punkty += 1;
			if (tab[p.x][p.y - 1] == '*') {
				p.stan = 0;
				licznik = 30;
			}
			if ((tab[p.x][p.y - 1] == tab[blinky.x][blinky.y] || tab[p.x][p.y - 1] == tab[pinky.x][pinky.y] || tab[p.x][p.y - 1] == tab[inky.x][inky.y] || tab[p.x][p.y - 1] == tab[clyde.x][clyde.y]) && p.stan == 1) {
				zycia -= 1;
				if (zycia == 0)
					gameOver();
				stop = true;
				break;
			}
			tab[p.x][p.y] = ' ';
			p.y -= 1;
			tab[p.x][p.y] = 'G';
		}
		break;
	}
	return p;
}
pozycja ruchBlinky(char tab[16][17], pozycja duszek, pozycja pacman, pozycja pinky, pozycja inky, pozycja clyde) {//ruch blinkiego
	bool mozliwosci[4]{};
	double deltaX[4]{}, deltaY[4]{}, odl{}, minOdl=1000000;
	if (pacman.stan == 0) {//sprawdza czy duszek nie jest oszo�omiony
		duszek = oszolomienie(tab, duszek);
	}
	else {//decyduje o najoptymalniejszym kierunku ruchu dla wyznaczonego sobie celu - w tym przypadku sam pacman
		if ((tab[duszek.x - 1][duszek.y] == ' ' || tab[duszek.x - 1][duszek.y] == '.' || tab[duszek.x - 1][duszek.y] == '*') && duszek.kierunek != 1) {
			mozliwosci[2] = 1;
			deltaX[2] = abs((duszek.x - 1) - pacman.x);
			deltaY[2] = abs(duszek.y - pacman.y);
		}
		if ((tab[duszek.x][duszek.y + 1] == ' ' || tab[duszek.x][duszek.y + 1] == '.' || tab[duszek.x][duszek.y + 1] == '*') && duszek.kierunek != 2) {
			mozliwosci[3] = 1;
			deltaX[3] = abs((duszek.x) - pacman.x);
			deltaY[3] = abs((duszek.y + 1) - pacman.y);
		}
		if ((tab[duszek.x + 1][duszek.y] == ' ' || tab[duszek.x + 1][duszek.y] == '.' || tab[duszek.x + 1][duszek.y] == '*') && duszek.kierunek != 3) {
			mozliwosci[0] = 1;
			deltaX[0] = abs((duszek.x + 1) - pacman.x);
			deltaY[0] = abs(duszek.y - pacman.y);
		}
		if ((tab[duszek.x][duszek.y - 1] == ' ' || tab[duszek.x][duszek.y - 1] == '.' || tab[duszek.x][duszek.y - 1] == '*') && duszek.kierunek != 4) {
			mozliwosci[1] = 1;
			deltaX[1] = abs((duszek.x) - pacman.x);
			deltaY[1] = abs((duszek.y - 1) - pacman.y);
		}
		for (int i = 0; i < 4; i++) {
			if (mozliwosci[i] == 1) {
				odl = sqrt(pow(deltaX[i], 2) + pow(deltaY[i], 2));
				if (odl < minOdl) {
					minOdl = odl;
					duszek.kierunek = i + 1;
				}
			}
		}
		switch (duszek.kierunek) {//ruch duszka - taki jak u pacmana
		case 1:
			if (tab[duszek.x + 1][duszek.y] == tab[pacman.x][pacman.y]) {//sprawdza czy duszek nie napotka� pacmana
				zycia -= 1;
				if (zycia == 0)
					gameOver();
				stop = true;
				break;
			}
			else {
				tab[duszek.x][duszek.y] = duszek.pole;
				duszek.x += 1;
				duszek.pole = tab[duszek.x][duszek.y];
				if (duszek.pole == 'P' || duszek.pole == 'I' || duszek.pole == 'C')
					duszek.pole = ' ';
				tab[duszek.x][duszek.y] = 'B';
				break;
			}
		case 2:
			if (tab[duszek.x][duszek.y - 1] == tab[pacman.x][pacman.y]) {
				zycia -= 1;
				if (zycia == 0)
					gameOver();
				stop = true;
				break;
			}
			else {
				tab[duszek.x][duszek.y] = duszek.pole;
				duszek.y -= 1;
				duszek.pole = tab[duszek.x][duszek.y];
				if (duszek.pole == 'P' || duszek.pole == 'I' || duszek.pole == 'C')
					duszek.pole = ' ';
				tab[duszek.x][duszek.y] = 'B';
				break;
			}
		case 3:
			if (tab[duszek.x - 1][duszek.y] == tab[pacman.x][pacman.y]) {
				zycia -= 1;
				if (zycia == 0)
					gameOver();
				stop = true;
				break;
			}
			else {
				tab[duszek.x][duszek.y] = duszek.pole;
				duszek.x -= 1;
				duszek.pole = tab[duszek.x][duszek.y];
				if (duszek.pole == 'P' || duszek.pole == 'I' || duszek.pole == 'C')
					duszek.pole = ' ';
				tab[duszek.x][duszek.y] = 'B';
				break;
			}
		case 4:
			if (tab[duszek.x][duszek.y + 1] == tab[pacman.x][pacman.y]) {
				zycia -= 1;
				if (zycia == 0)
					gameOver();
				stop = true;
				break;
			}
			else {
				tab[duszek.x][duszek.y] = duszek.pole;
				duszek.y += 1;
				duszek.pole = tab[duszek.x][duszek.y];
				if (duszek.pole == 'P' || duszek.pole == 'I' || duszek.pole == 'C')
					duszek.pole = ' ';
				tab[duszek.x][duszek.y] = 'B';
				break;
			}
		}
	}
	return duszek;
}
pozycja ruchPinky(char tab[16][17], pozycja duszek, pozycja pacman, pozycja blinky, pozycja inky, pozycja clyde) { // to samo co u Blinkiego - r�ni si� cel do kt�rego zmierza Pinky 
	bool mozliwosci[4]{};
	double deltaX[4]{}, deltaY[4]{}, odl{}, minOdl = 1000000;
	if (pacman.stan == 0) {
		duszek = oszolomienie(tab, duszek);
	}
	else {
		if ((tab[duszek.x - 1][duszek.y] == ' ' || tab[duszek.x - 1][duszek.y] == '.' || tab[duszek.x - 1][duszek.y] == '*') && duszek.kierunek != 1) {
			mozliwosci[2] = 1;
			deltaX[2] = abs((duszek.x - 1) - (pacman.x + 2));
			deltaY[2] = abs(duszek.y - pacman.y);
		}
		if ((tab[duszek.x][duszek.y + 1] == ' ' || tab[duszek.x][duszek.y + 1] == '.' || tab[duszek.x][duszek.y + 1] == '*') && duszek.kierunek != 2) {
			mozliwosci[3] = 1;
			deltaX[3] = abs((duszek.x) - (pacman.x + 2));
			deltaY[3] = abs((duszek.y + 1) - pacman.y);
		}
		if ((tab[duszek.x + 1][duszek.y] == ' ' || tab[duszek.x + 1][duszek.y] == '.' || tab[duszek.x + 1][duszek.y] == '*') && duszek.kierunek != 3) {
			mozliwosci[0] = 1;
			deltaX[0] = abs((duszek.x + 1) - (pacman.x + 2));
			deltaY[0] = abs(duszek.y - pacman.y);
		}
		if ((tab[duszek.x][duszek.y - 1] == ' ' || tab[duszek.x][duszek.y - 1] == '.' || tab[duszek.x][duszek.y - 1] == '*') && duszek.kierunek != 4) {
			mozliwosci[1] = 1;
			deltaX[1] = abs((duszek.x) - (pacman.x + 2));
			deltaY[1] = abs((duszek.y - 1) - pacman.y);
		}
		for (int i = 0; i < 4; i++) {
			if (mozliwosci[i] == 1) {
				odl = sqrt(pow(deltaX[i], 2) + pow(deltaY[i], 2));
				if (odl < minOdl) {
					minOdl = odl;
					duszek.kierunek = i + 1;
				}
			}
		}
		switch (duszek.kierunek) {
		case 1:
			if (tab[duszek.x + 1][duszek.y] == tab[pacman.x][pacman.y]) {
				zycia -= 1;
				if (zycia == 0)
					gameOver();
				stop = true;
				break;
			}
			else {
				tab[duszek.x][duszek.y] = duszek.pole;
				duszek.x += 1;
				duszek.pole = tab[duszek.x][duszek.y];
				if (duszek.pole == 'B' || duszek.pole == 'I' || duszek.pole == 'C')
					duszek.pole = ' ';
				tab[duszek.x][duszek.y] = 'P';
				break;
			}
		case 2:
			if (tab[duszek.x][duszek.y - 1] == tab[pacman.x][pacman.y]) {
				zycia -= 1;
				if (zycia == 0)
					gameOver();
				stop = true;
				break;
			}
			else {
				tab[duszek.x][duszek.y] = duszek.pole;
				duszek.y -= 1;
				duszek.pole = tab[duszek.x][duszek.y];
				if (duszek.pole == 'B' || duszek.pole == 'I' || duszek.pole == 'C')
					duszek.pole = ' ';
				tab[duszek.x][duszek.y] = 'P';
				break;
			}
		case 3:
			if (tab[duszek.x - 1][duszek.y] == tab[pacman.x][pacman.y]) {
				zycia -= 1;
				if (zycia == 0)
					gameOver();
				stop = true;
				break;
			}
			else {
				tab[duszek.x][duszek.y] = duszek.pole;
				duszek.x -= 1;
				duszek.pole = tab[duszek.x][duszek.y];
				if (duszek.pole == 'B' || duszek.pole == 'I' || duszek.pole == 'C')
					duszek.pole = ' ';
				tab[duszek.x][duszek.y] = 'P';
				break;
			}
		case 4:
			if (tab[duszek.x][duszek.y + 1] == tab[pacman.x][pacman.y]) {
				zycia -= 1;
				if (zycia == 0)
					gameOver();
				stop = true;
				break;
			}
			else {
				tab[duszek.x][duszek.y] = duszek.pole;
				duszek.y += 1;
				duszek.pole = tab[duszek.x][duszek.y];
				if (duszek.pole == 'B' || duszek.pole == 'I' || duszek.pole == 'C')
					duszek.pole = ' ';
				tab[duszek.x][duszek.y] = 'P';
				break;
			}
		}
	}
	return duszek;
}
pozycja ruchInky(char tab[16][17], pozycja duszek, pozycja pacman, pozycja blinky, pozycja pinky, pozycja clyde) {//to samo co u Blinkiego - r�ni si� cel do kt�rego zmierza Inky
	bool mozliwosci[4]{};
	double deltaX[4]{}, deltaY[4]{}, odl{}, minOdl = 1000000;
	if (pacman.stan == 0) {
		duszek = oszolomienie(tab, duszek);
	}
	else {
		if ((tab[duszek.x - 1][duszek.y] == ' ' || tab[duszek.x - 1][duszek.y] == '.' || tab[duszek.x - 1][duszek.y] == '*') && duszek.kierunek != 1) {
			mozliwosci[2] = 1;
			deltaX[2] = abs((duszek.x - 1) - pacman.x);
			deltaY[2] = abs(duszek.y - (pacman.y + 2));
		}
		if ((tab[duszek.x][duszek.y + 1] == ' ' || tab[duszek.x][duszek.y + 1] == '.' || tab[duszek.x][duszek.y + 1] == '*') && duszek.kierunek != 2) {
			mozliwosci[3] = 1;
			deltaX[3] = abs((duszek.x) - pacman.x);
			deltaY[3] = abs((duszek.y + 1) - (pacman.y + 2));
		}
		if ((tab[duszek.x + 1][duszek.y] == ' ' || tab[duszek.x + 1][duszek.y] == '.' || tab[duszek.x + 1][duszek.y] == '*') && duszek.kierunek != 3) {
			mozliwosci[0] = 1;
			deltaX[0] = abs((duszek.x + 1) - pacman.x);
			deltaY[0] = abs(duszek.y - (pacman.y + 2));
		}
		if ((tab[duszek.x][duszek.y - 1] == ' ' || tab[duszek.x][duszek.y - 1] == '.' || tab[duszek.x][duszek.y - 1] == '*') && duszek.kierunek != 4) {
			mozliwosci[1] = 1;
			deltaX[1] = abs((duszek.x) - pacman.x);
			deltaY[1] = abs((duszek.y - 1) - (pacman.y + 2));
		}
		for (int i = 0; i < 4; i++) {
			if (mozliwosci[i] == 1) {
				odl = sqrt(pow(deltaX[i], 2) + pow(deltaY[i], 2));
				if (odl < minOdl) {
					minOdl = odl;
					duszek.kierunek = i + 1;
				}
			}
		}
		switch (duszek.kierunek) {
		case 1:
			if (tab[duszek.x + 1][duszek.y] == tab[pacman.x][pacman.y]) {
				zycia -= 1;
				if (zycia == 0)
					gameOver();
				stop = true;
				break;
			}
			else {
				tab[duszek.x][duszek.y] = duszek.pole;
				duszek.x += 1;
				duszek.pole = tab[duszek.x][duszek.y];
				if (duszek.pole == 'P' || duszek.pole == 'B' || duszek.pole == 'C')
					duszek.pole = ' ';
				tab[duszek.x][duszek.y] = 'I';
				break;
			}
		case 2:
			if (tab[duszek.x][duszek.y - 1] == tab[pacman.x][pacman.y]) {
				zycia -= 1;
				if (zycia == 0)
					gameOver();
				stop = true;
				break;
			}
			else {
				tab[duszek.x][duszek.y] = duszek.pole;
				duszek.y -= 1;
				duszek.pole = tab[duszek.x][duszek.y];
				if (duszek.pole == 'P' || duszek.pole == 'B' || duszek.pole == 'C')
					duszek.pole = ' ';
				tab[duszek.x][duszek.y] = 'I';
				break;
			}
		case 3:
			if (tab[duszek.x - 1][duszek.y] == tab[pacman.x][pacman.y]) {
				zycia -= 1;
				if (zycia == 0)
					gameOver();
				stop = true;
				break;
			}
			else {
				tab[duszek.x][duszek.y] = duszek.pole;
				duszek.x -= 1;
				duszek.pole = tab[duszek.x][duszek.y];
				if (duszek.pole == 'P' || duszek.pole == 'B' || duszek.pole == 'C')
					duszek.pole = ' ';
				tab[duszek.x][duszek.y] = 'I';
				break;
			}
		case 4:
			if (tab[duszek.x][duszek.y + 1] == tab[pacman.x][pacman.y]) {
				zycia -= 1;
				if (zycia == 0)
					gameOver();
				stop = true;
				break;
			}
			else {
				tab[duszek.x][duszek.y] = duszek.pole;
				duszek.y += 1;
				duszek.pole = tab[duszek.x][duszek.y];
				if (duszek.pole == 'P' || duszek.pole == 'B' || duszek.pole == 'C')
					duszek.pole = ' ';
				tab[duszek.x][duszek.y] = 'I';
				break;
			}
		}
	}
	return duszek;
}
pozycja ruchClyde(char tab[16][17], pozycja duszek, pozycja pacman, pozycja blinky, pozycja pinky, pozycja inky) {//to samo co u Blinkiego - r�ni si� cel do kt�rego zmierza Clyde
	bool mozliwosci[4]{};
	double deltaX[4]{}, deltaY[4]{}, odl{}, minOdl = 1000000;
	if (pacman.stan == 0) {
		duszek=oszolomienie(tab, duszek);
	}
	else {
		if ((tab[duszek.x - 1][duszek.y] == ' ' || tab[duszek.x - 1][duszek.y] == '.' || tab[duszek.x - 1][duszek.y] == '*') && duszek.kierunek != 1) {
			mozliwosci[2] = 1;
			deltaX[2] = abs((duszek.x - 1) - (pacman.x - 6));
			deltaY[2] = abs(duszek.y - (pacman.y - 6));
		}
		if ((tab[duszek.x][duszek.y + 1] == ' ' || tab[duszek.x][duszek.y + 1] == '.' || tab[duszek.x][duszek.y + 1] == '*') && duszek.kierunek != 2) {
			mozliwosci[3] = 1;
			deltaX[3] = abs((duszek.x) - (pacman.x - 6));
			deltaY[3] = abs((duszek.y + 1) - (pacman.y - 6));
		}
		if ((tab[duszek.x + 1][duszek.y] == ' ' || tab[duszek.x + 1][duszek.y] == '.' || tab[duszek.x + 1][duszek.y] == '*') && duszek.kierunek != 3) {
			mozliwosci[0] = 1;
			deltaX[0] = abs((duszek.x + 1) - (pacman.x - 6));
			deltaY[0] = abs(duszek.y - (pacman.y - 6));
		}
		if ((tab[duszek.x][duszek.y - 1] == ' ' || tab[duszek.x][duszek.y - 1] == '.' || tab[duszek.x][duszek.y - 1] == '*') && duszek.kierunek != 4) {
			mozliwosci[1] = 1;
			deltaX[1] = abs((duszek.x) - (pacman.x - 6));
			deltaY[1] = abs((duszek.y - 1) - (pacman.y - 6));
		}
		for (int i = 0; i < 4; i++) {
			if (mozliwosci[i] == 1) {
				odl = sqrt(pow(deltaX[i], 2) + pow(deltaY[i], 2));
				if (odl < minOdl) {
					minOdl = odl;
					duszek.kierunek = i + 1;
				}
			}
		}
		switch (duszek.kierunek) {
		case 1:
			if (tab[duszek.x + 1][duszek.y] == tab[pacman.x][pacman.y]) {
				zycia -= 1;
				if (zycia == 0)
					gameOver();
				stop = false;
				break;
			}
			else {
				tab[duszek.x][duszek.y] = duszek.pole;
				duszek.x += 1;
				duszek.pole = tab[duszek.x][duszek.y];
				if (duszek.pole == 'P' || duszek.pole == 'I' || duszek.pole == 'B')
					duszek.pole = ' ';
				tab[duszek.x][duszek.y] = 'C';
				break;
			}
		case 2:
			if (tab[duszek.x][duszek.y - 1] == tab[pacman.x][pacman.y]) {
				zycia -= 1;
				if (zycia == 0)
					gameOver();
				stop = false;
				break;
			}
			else {
				tab[duszek.x][duszek.y] = duszek.pole;
				duszek.y -= 1;
				duszek.pole = tab[duszek.x][duszek.y];
				if (duszek.pole == 'P' || duszek.pole == 'I' || duszek.pole == 'B')
					duszek.pole = ' ';
				tab[duszek.x][duszek.y] = 'C';
				break;
			}
		case 3:
			if (tab[duszek.x - 1][duszek.y] == tab[pacman.x][pacman.y]) {
				zycia -= 1;
				if (zycia == 0)
					gameOver();
				stop = false;
				break;
			}
			else {
				tab[duszek.x][duszek.y] = duszek.pole;
				duszek.x -= 1;
				duszek.pole = tab[duszek.x][duszek.y];
				if (duszek.pole == 'P' || duszek.pole == 'I' || duszek.pole == 'B')
					duszek.pole = ' ';
				tab[duszek.x][duszek.y] = 'C';
				break;
			}
		case 4:
			if (tab[duszek.x][duszek.y + 1] == tab[pacman.x][pacman.y]) {
				zycia -= 1;
				if (zycia == 0)
					gameOver();
				stop = false;
				break;
			}
			else {
				tab[duszek.x][duszek.y] = duszek.pole;
				duszek.y += 1;
				duszek.pole = tab[duszek.x][duszek.y];
				if (duszek.pole == 'P' || duszek.pole == 'I' || duszek.pole == 'B')
					duszek.pole = ' ';
				tab[duszek.x][duszek.y] = 'C';
				break;
			}
		}
	}
	return duszek;
}
pozycja oszolomienie(char tab[16][17], pozycja duszek) {//poruszanie si� podczas oszo�omienia
	srand(time(NULL));
	bool dziala = 0;
	while (dziala == 0) {
		duszek.kierunek = rand() % 4 + 1; //duszki poruszaj� si� w losowym kierunku
		switch (duszek.kierunek) {
		case 1:
			if((tab[duszek.x + 1][duszek.y] == ' ' || tab[duszek.x + 1][duszek.y] == '.' || tab[duszek.x + 1][duszek.y] == '*') &&duszek.kierunek!=3){//sprawdza czy duszek mo�e wej�� na to pole
				tab[duszek.x][duszek.y] = duszek.pole;
				duszek.x += 1;
				duszek.pole = tab[duszek.x][duszek.y];
				tab[duszek.x][duszek.y] = duszek.nazwa;
				dziala = 1;
			}
			break;
		case 2:
			if((tab[duszek.x][duszek.y - 1] == ' ' || tab[duszek.x][duszek.y - 1] == '.' || tab[duszek.x][duszek.y - 1] == '*') &&duszek.kierunek!=4) {
				tab[duszek.x][duszek.y] = duszek.pole;
				duszek.y -= 1;
				duszek.pole = tab[duszek.x][duszek.y];
				tab[duszek.x][duszek.y] = duszek.nazwa;
				dziala = 1;
			}
			break;
		case 3:
			if ((tab[duszek.x - 1][duszek.y] == ' ' || tab[duszek.x - 1][duszek.y] == '.' || tab[duszek.x - 1][duszek.y] == '*')&&duszek.kierunek!=1) {
				tab[duszek.x][duszek.y] = duszek.pole;
				duszek.x -= 1;
				duszek.pole = tab[duszek.x][duszek.y];
				tab[duszek.x][duszek.y] = duszek.nazwa;
				dziala = 1;
			}
			break;
		case 4:
			if ((tab[duszek.x][duszek.y + 1] == ' '|| tab[duszek.x][duszek.y + 1] == '.'|| tab[duszek.x][duszek.y + 1] == '*')&&duszek.kierunek!=2){
				tab[duszek.x][duszek.y] = duszek.pole;
				duszek.y += 1;
				duszek.pole = tab[duszek.x][duszek.y];
				tab[duszek.x][duszek.y] = duszek.nazwa;
				dziala = 1;
			}
			break;
		}
	}
	return duszek;
}
pozycja blinkyReset(char tab[16][17], pozycja blinky) {//resetuje pozycj� Blinkiego oraz jego kierunek i pole na kt�rym stoi
	tab[blinky.x][blinky.y] = blinky.pole;
	blinky.x = 4;
	blinky.y = 8;
	tab[blinky.x][blinky.y] = 'B';
	blinky.pole = ' ';
	blinky.kierunek = 0;
	return blinky;
}
pozycja pinkyReset(char tab[16][17], pozycja pinky) {//resetuje pozycj� Pinkiego oraz jego kierunek i pole na kt�rym stoi
	tab[pinky.x][pinky.y] = pinky.pole;
	pinky.x = 4;
	pinky.y = 7;
	tab[pinky.x][pinky.y] = 'P';
	pinky.kierunek = 0;
	pinky.pole = ' ';
	return pinky;
}
pozycja inkyReset(char tab[16][17], pozycja inky) {//resetuje pozycj� Inkiego oraz jego kierunek i pole na kt�rym stoi
	tab[inky.x][inky.y] = inky.pole;
	inky.x = 4;
	inky.y = 9;
	tab[inky.x][inky.y] = 'I';
	inky.kierunek = 0;
	inky.pole = ' ';
	return inky;
}
pozycja clydeReset(char tab[16][17], pozycja clyde) {//resetuje pozycj� Clyde'a oraz jego kierunek i pole na kt�rym stoi
	tab[clyde.x][clyde.y] = clyde.pole;
	clyde.x = 1;
	clyde.y = 8;
	tab[clyde.x][clyde.y] = 'C';
	clyde.kierunek = 0;
	clyde.pole = ' ';
	return clyde;
}
pozycja graczReset(char tab[16][17], pozycja gracz) {//resetuje pozycj� gracza oraz jego kierunek
	tab[gracz.x][gracz.y] = ' ';
	gracz.x = 9;
	gracz.y = 8;
	tab[gracz.x][gracz.y] = 'G';
	gracz.kierunek = 0;
	return gracz;
}
void gameOver() {//strona GAME OVER po przegraniu
	system("cls");
	char odp;
	cout << "##### ##### ## ## #####  ##### #   # ##### #####" << endl;
	cout << "#     #   # # # # #      #   # #   # #     #   #" << endl;
	cout << "#  ## ##### #   # ###    #   #  # #  ###   #####" << endl;
	cout << "##### #   # #   # #####  #####   #   ##### #  # " << endl;
	cout << endl;
	cout << "1. Menu" << endl;
	cout << "2. Zapisz wynik" << endl;
	while(true) {
		cin >> odp;
		if (odp == '1') {
			system("cls");
			gra = false;
			break;
		}
		if (odp == '2') {
			system("cls");
			wyniki_zapis();//odpalenie f zapisuj�cej wynik
			gra = false;
			break;
		}
		odp = ' ';
	}
}
void wygrana() {
	char odp{};
	system("cls");
	cout << "#   # #   # ##### ##### ##### ##  # ##### # # #" << endl;
	cout << "# # #  # #  #     #   # #   # # # # #   # # # #" << endl;
	cout << "# # #   #   #  ## ##### ##### #  ## #####      " << endl;
	cout << " # #    #   ##### #  #  #   # #   # #   # # # #" << endl;
	cout << endl;
	cout << "Gratulacje! Wygra�e� map�!" << endl;
	cout << "1. Menu g��wne" << endl;
	cout << "2. Restart" << endl;
	cout << "3. Zapisz wynik" << endl;
	while(true){
		cin >> odp;
		if (odp == '1') {
			system("cls");//czyszczenie ekranu
			gra = false;
			break;
		}
		if (odp == '2') {
			system("cls");
			gra = false;
			graPacMan();
			break;
		}
		if (odp == '3') {
			system("cls");
			gra = false;
			wyniki_zapis();
			break;
		}
		odp = ' ';
	}
}
void graPacMan() {
	gra = true;
	zycia = 3;
	punkty = 0;
	int zwolnienie_duszek = 0;
	pozycja gracz;
	gracz.x = 9;
	gracz.y = 8;
	gracz.pole = ' ';
	gracz.stan = 1;
	pozycja blinky;
	pozycja pinky;
	pozycja inky;
	pozycja clyde;
	clyde.x = 1;
	clyde.y = 8;
	clyde.pole = ' ';
	clyde.stan = 1;
	clyde.nazwa = 'c';
	pinky.x = 4;
	pinky.y = 7;
	pinky.pole = ' ';
	pinky.stan = 1;
	pinky.nazwa = 'p';
	inky.x = 4;
	inky.y = 9;
	inky.pole = ' ';
	inky.stan = 1;
	inky.nazwa = 'i';
	blinky.x = 4;
	blinky.y = 8;
	blinky.pole = ' ';
	blinky.stan = 1;
	blinky.nazwa = 'b';
	gracz.kierunek = 0;//ustawienie pocz�tkowych warto�ci
	char key;
	char tab[16][17] = { {'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'},
						 {'#','*','.','.','#','#','.','.','C','.','.','#','#','.','.','*','#'},
						 {'#','.','#','.','.','#','.','#','#','#','.','#','.','.','#','.','#'},
						 {'#','.','#','#','.','#','.','#','#','#','.','#','.','#','#','.','#'},
						 {'#','.','.','.','.','.','.','P','B','I','.','.','.','.','.','.','#'},
						 {'#','#','#','#','#','.','#','#','#','#','#','.','#','#','#','#','#'},
						 {' ',' ',' ',' ','#','.','#',' ',' ',' ','#','.','#',' ',' ',' ',' '},
						 {' ',' ',' ',' ','#','.','#',' ',' ',' ','#','.','#',' ',' ',' ',' '},
						 {' ',' ',' ',' ','#','.','#','#','#','#','#','.','#',' ',' ',' ',' '},
						 {'#','#','#','#','#','.','.','.','G','.','.','.','#','#','#','#','#'},
						 {'#','.','.','.','.','.','#','#','#','#','#','.','.','.','.','.','#'},
						 {'#','.','#','#','.','#','#','.','*','.','#','#','.','#','#','.','#'},
						 {'#','.','#','#','.','.','.','.','#','.','.','.','.','#','#','.','#'},
						 {'#','*','.','.','.','#','#','#','#','#','#','#','.','.','.','*','#'},
						 {'#','#','#','#','#','#',' ',' ',' ',' ',' ','#','#','#','#','#','#'}
	};//tablica na kt�rej znajduje si� plansza do pacmana
	do {
		wyswietlaniePlanszy(tab, 16, 17);
		if (_kbhit()) {//sprawdza czy jaki� klawisz naci�ni�ty
			key = _getch();
			if (key == 'a') {
				gracz.kierunek = 4;//ustawienie kierunku PacMana
			}
			if (key == 'd') {
				gracz.kierunek = 3;
			}
			if (key == 'w') {
				gracz.kierunek = 2;
			}
			if (key == 's') {
				gracz.kierunek = 1;
			}
			if (key == 'k') {
				gra = false; // ko�czy gr�
				continue;
			}
		}
		if (gracz.kierunek != 0) {//sprawdza czy aktywna gra rozpocz�ta
			gracz = ruchGracza(tab, gracz, blinky, pinky, inky, clyde);//zmienia pozycje gracza
			if (gracz.stan == 0)
				licznik -= 1;//odlicza czas do ko�ca oszo�omienia
			if (licznik == 0) {//ustawia licznik na pocz�tkow� warto��
				licznik = 30;
				gracz.stan = 1;
			}
			if (zwolnienie_duszek % 3 == 0) {//duszki musz� by� wolniejsze ni� gracz aby nie by�o zbyt trudno
				blinky = ruchBlinky(tab, blinky, gracz, pinky, inky, clyde);//zmienia pozycje duszk�w
				pinky = ruchPinky(tab, pinky, gracz, blinky, inky, clyde);
				inky = ruchInky(tab, inky, gracz, blinky, pinky, clyde);
				clyde = ruchClyde(tab, clyde, gracz, blinky, pinky, inky);
			}
			if (stop == true) {
				gracz = graczReset(tab, gracz);//resetuje pozycje ruchomych obiekt�w
				blinky = blinkyReset(tab, blinky);
				pinky = pinkyReset(tab, pinky);
				inky = inkyReset(tab, inky);
				clyde = clydeReset(tab, clyde);
				stop = false;
			}
			zwolnienie_duszek += 1;
			if (zwolnienie_duszek == 31) {//zeruje zwolnienie aby nie wyj�� poza zakres
				zwolnienie_duszek = 1;
			}
		}
		system("cls");
	} while (gra == true); //sprawdza czy gra trwa
}
void menu() {
	bool glowna = true;//sprawdza czy menu ma by� odpalone
	char odp{}, odp1{};
	system("cls");
	while (glowna) {
		cout << "##### ##### ##### ## ## ##### ##  #" << endl;
		cout << "#   # #   # #     # # # #   # # # #" << endl;
		cout << "##### ##### #     #   # ##### #  ##" << endl;
		cout << "#     #   # ##### #   # #   # #   #" << endl;
		cout << endl;
		cout << endl;
		cout << "1. Graj" << endl;
		cout << "2. Instrukcja" << endl;
		cout << "3. Sala chwa�y" << endl;
		cout << "4. Wyj�cie" << endl;
		while (true) {//mo�liwo�� wyboru opcji
			cin >> odp;
			if (odp == '1') {
				system("cls");
				graPacMan();
				break;
			}
			if (odp == '2') {
				system("cls");
				cout << "##### ##  # ##### ##### ##### #   # #   # ##### ##### #####" << endl;
				cout << "  #   # # # ##      #   #   # #   # # ##  #         # #   #" << endl;
				cout << "  #   #  ##   ###   #   ##### #   # ###   #     #   # #####" << endl;
				cout << "##### #   # #####   #   #  #  ##### #  ## ##### ##### #   #" << endl;
				cout << endl;
				cout << endl;
				cout << "Gra polega na sterowaniu tytu�owym bohaterem, czyli Pac-Manem, po labiryncie w celu zebrania jak najwi�kszej ilo�ci punkt�w." << endl;
				cout << "Punkty zdobywa si� 'zjadaj�c' kropki ustawione na planszy." << endl;
				cout << "Dodatkow� przeszkod� s� poruszaj�ce si� po labiryncie duszki(Blinky, Pinky, Inky i Clyde), kt�re czychaj� na �ycie naszego bohatera." << endl;
				cout << "Ka�de bespo�rednie spotkanie z duszkiem skutkuje utrat� �ycia (Pac-Man poiada 3 �ycia)." << endl;
				cout << "Wyj�tkiem jest kiedy Pac-Man zje sepcjaln� kulk� mocy." << endl;
				cout << "Duszki wchodz� w stan oszo�omienia podczas kt�rego nie robi� krzywdy naszemu bohaterowi." << endl;
				cout << "Stan oszo�omienia jest ograniczony w czasie - p�niej duszki wracaj� do swojego zwyk�ego zachowania" << endl;
				cout << "Pac-manem porusza si� za pomoc� klawisz�w (w, s, a, d), a aby zako�czy� gr� natychmiastowo nale�y wcisn�� klawisz 'k'" << endl;
				cout << endl;
				cout << "0. Powr�t" << endl;
				while (true) {
					cin >> odp1;
					if (odp1 == '0') {
						system("cls");
						break;
					}
				}
			}
			if (odp == '3') {
				system("cls");
				wyniki_wyswietl();
				break;
			}
			if (odp == '4') {
				system("cls");
				glowna = false;
				break;
			}
			odp = ' ';
		}
	}
}
int main(){
	setlocale(LC_ALL, "");//polskie znaki
	menu(); //odpalenie menu
	system("pause");
}