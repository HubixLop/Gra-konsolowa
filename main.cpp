#include <iostream>
#include <cstdlib> // Potrzebne do odświeżania ekranu system("cls")
#include <ctime> // miny 

using namespace std;

// Funkcja wyświetlająca instrukcję gry
void wyswietlInstrukcje() {
    cout << "=== JAK GRAC ===" << endl;
    cout << "Podaj wspolrzedne X i Y oraz akcje:" << endl;
    cout << "0 - odkryj pole" << endl;
    cout << "1 - Postaw flage (F)" << endl;
    cout << "2 - Usun flage (F)" << endl;
    cout << "3 - Zakoncz gre" << endl;
    cout << "---------------------" << endl;
}
int policzMinyWokol(int x, int y, int wysokosc, int szerokosc, char** planszaMin) {
    int minyWokol = 0;
    for(int dy = -1; dy <= 1; dy++) {
        for(int dx = -1; dx <= 1; dx++) {
            int nx = x + dx;
            int ny = y + dy;

            if(nx >= 0 && nx < szerokosc && ny >= 0 && ny < wysokosc) {
                if (planszaMin[ny][nx] == 'M') {
                    minyWokol++;
                }
            }
        }
    }
    return minyWokol;
}
void odkryjPole(int x, int y, int wysokosc, int szerokosc, char** plansza, char** planszaMin){
    if (x < 0 || x >= szerokosc || y < 0 || y>= wysokosc) return;

    if (plansza[y][x] != '#') return;

    int IleMin = policzMinyWokol(x, y, wysokosc, szerokosc, planszaMin);
    plansza[y][x] = '0' + IleMin;

    if (IleMin == 0) {
        for (int dy = -1; dy <= 1; dy++) {
            for (int dx = -1; dx <= 1; dx++) {
                if (dx != 0 || dy != 0) {
                    odkryjPole(x + dx, y + dy, wysokosc, szerokosc, plansza, planszaMin);
                }
            }
        }
    }


}
bool sprawdzWygrana(int wysokosc, int szerokosc, int iloscMin, char** plansza) {
    int zakrytePol = 0;
    
    for (int y = 0; y < wysokosc; y++) {
        for (int x = 0; x < szerokosc; x++) {
            if (plansza[y][x] == '#' || plansza[y][x] == 'F') {
                zakrytePol++;
            }
        }
    }
    return zakrytePol == iloscMin;
}
// Zaktualizowana funkcja wykonajRuch - teraz modyfikuje naszą tablicę
void wykonajRuch(int wysokosc, int szerokosc, int miny, char** plansza, char** planszaMin, bool &graTwa) {
    int x, y, akcja;

    cout << "\nPodaj wspolrzedne (Format: X Y): ";
    cin >> x >> y;

    // Sprawdzenie, czy gracz nie podał współrzędnych poza planszą
    if (x < 0 || x >= szerokosc || y < 0 || y >= wysokosc) {
        cout << "Wspolrzedne poza zakresem planszy!" << endl;
        cout << "\nNacisnij Enter, aby kontynuowac...";
        cin.ignore();
        cin.get();
        return; 
    }

    cout << "Wybierz akcje (0-odkryj, 1-Postaw flage, 2-Usun flage, 3-Zakoncz gre): ";
    cin >> akcja;

    if (akcja == 0) {
        if (plansza[y][x] == '#') {
            if (planszaMin[y][x] == 'M'){
                plansza[y][x] = 'M'; // Odkryto minę
                cout << "\nBOOM! Trafiles na mine! Koniec gry!" << endl;
                graTwa = false;
            }
            else{
                odkryjPole(x, y, wysokosc, szerokosc, plansza, planszaMin);
                cout << "Odkryto pole (" << x << "," << y << ")." << endl;
            }
        }else{
            cout << "To pole jest juz odkryte lub ma flage!" << endl;
        }
    }
    else if (akcja == 1) {
        if (plansza[y][x] == '#') {
            plansza[y][x] = 'F'; // Stawiamy flagę
            cout << "Postawiono flage (F) na polu (" << x << "," << y << ")." << endl;
        } else {
            cout << "Nie mozna postawic flagi na tym polu!" << endl;
        }
    }
    else if (akcja == 2) {
        if (plansza[y][x] == 'F') {
            plansza[y][x] = '#'; // Usuwamy flagę
            cout << "Usunieto flage (F) z pola (" << x << "," << y << ")." << endl;
        } else {
            cout << "Na tym polu nie ma flagi!" << endl;
        }
    }
    else if (akcja ==3){
        graTwa = false;
        cout << "Koniec gry!" << endl;
        return;
    }
    else {
        cout << "Niepoprawna akcja!" << endl;
    }
    if (graTwa && sprawdzWygrana(wysokosc, szerokosc, miny, plansza)){
        cout << "\n======================================" << endl;
        cout << "GRATULACJE! WYGRALES GRE W SAPERA! " << endl;
        cout << "======================================" << endl;
        graTwa = false;
    }

    cout << "\nNacisnij Enter, aby kontynuowac...";
    cin.ignore();
    cin.get();
}

// Funkcja rysująca planszę
void wyswietlPlansze(int wysokosc, int szerokosc, char** plansza) {
    cout << "   ";
    for (int x = 0; x < szerokosc; x++) {
        if (x < 10) cout << x << "  ";
        else cout << x << " ";
    }
    cout << endl;

    for (int y = 0; y < wysokosc; y++) {
        if (y < 10) cout << " " << y << " ";
        else cout << y << " ";

        for (int x = 0; x < szerokosc; x++) {
            cout << plansza[y][x] << "  ";
        }
        cout << endl;
    }
}
void generujMiny(int wysokosc, int szerokosc, int iloscMin, char** planszaMin) {
    int postawioneMiny = 0;

    while (postawioneMiny < iloscMin) {
        int losX = rand() % szerokosc;
        int losY = rand() % wysokosc;

        if (planszaMin[losY][losX] != 'M') { // Sprawdzenie, czy na tym polu nie ma już miny
            planszaMin[losY][losX] = 'M'; // Umieszczamy minę
            postawioneMiny++;
        }
    }
}

int main() {
    int wybor;
    int szerokosc = 9, wysokosc = 9, miny = 10; 
    bool poprawnyWybor = false;

    // Menu wyboru poziomu
    do {
        cout << "=== SAPER ===" << endl;
        cout << "1. Graj - Poziom Latwy (9x9, 10 min)" << endl;
        cout << "2. Graj - Poziom Sredni (16x16, 40 min)" << endl;
        cout << "3. Graj - Poziom Trudny (30x16, 99 min)" << endl;
        cout << "Wybierz poziom trudnosci (1-3): ";
        cin >> wybor;

        switch (wybor) {
            case 1:
                szerokosc = 9;
                wysokosc = 9;
                miny = 10;
                poprawnyWybor = true;
                break;
            case 2:
                szerokosc = 16;
                wysokosc = 16;
                miny = 40; 
                poprawnyWybor = true;
                break;
            case 3:
                szerokosc = 30;
                wysokosc = 16;
                miny = 99; 
                poprawnyWybor = true;
                break;
            default:
                cout << "\nNiepoprawny wybor! Sprobuj ponownie.\n" << endl;
                poprawnyWybor = false;
                break;
        }
    } while (!poprawnyWybor);

    cout << "\nWybrano poziom! Plansza: " << szerokosc << "x" << wysokosc << ", Miny: " << miny << endl;

    // Tworzenie dynamicznej tablicy dwuwymiarowej
    char** plansza = new char*[wysokosc];
    for (int i = 0; i < wysokosc; i++) {
        plansza[i] = new char[szerokosc];
    }

    // Wypełnianie zakrytymi polami '#'
    for (int y = 0; y < wysokosc; y++) {
        for (int x = 0; x < szerokosc; x++) {
            plansza[y][x] = '#';
        }
    }
    srand(time(0));

    char** planszaMin = new char*[wysokosc];
    for (int i = 0; i < wysokosc; i++) {
        planszaMin[i] = new char[szerokosc];
    }
    
    for (int y = 0; y < wysokosc; y++) {
        for (int x = 0; x < szerokosc; x++) {
            planszaMin[y][x] = '0'; 
        }
    }

    generujMiny(wysokosc, szerokosc, miny, planszaMin);
    // GŁÓWNA PĘTLA GRY
    bool graTwa = true;
    while (graTwa) {
        system("cls"); // Czyszczenie konsoli, aby plansza nie przesuwała się w dół
        
        wyswietlInstrukcje();
        cout << endl;
        
        wyswietlPlansze(wysokosc, szerokosc, plansza);
        
        wykonajRuch(wysokosc, szerokosc, miny, plansza, planszaMin, graTwa);
    }

    // Czyszczenie pamięci
    for (int i = 0; i < wysokosc; i++) {
        delete[] plansza[i];
        delete[] planszaMin[i];
    }
    delete[] plansza;
    delete[] planszaMin;
    
    return 0;
}