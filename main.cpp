#include<iostream>
using namespace std;
void wyswietlInstrukcje(){
    cout << "=== JAK GRAC ===" << endl;
    cout <<  "Podaj wspolrzedne X i Y oraz akcje:" << endl;
    cout << "0 - odkryj pole" << endl;
    cout << "1 - Postaw flage (F) " << endl;
    cout << "2 - Usun flage (F)" << endl;
    cout << "nnnnnnnnnnnnnnn\n" << endl;
}

void wykonajRuch(){
    int x,y,akcja;

    cout << "\nPodaj wpolrzedne (Format: X Y): ";
    cin >> x >> y;

    cout <<"Wybierz akcje (0-odkryj, 1-Postaw flage, 2-Usun flage): ";
    cin >> akcja;

    if (akcja == 0){
        cout << "Odkryto pole(" << x << "," << y << ")..." << endl;
    }
    else if (akcja == 1){
        cout << "Postawiono flage (F) na polu (" << x << "," << y << ")..." << endl;
    }
    else if (akcja == 2){
        cout << "Usunieto flage (F) z pola (" << x << "," << y << ")..." << endl;
    }
    else{
        cout << "Niepoprawna akcja!" << endl;
    }
}


void wyswietlPlansze(int wysokosc, int szerokosc, char** plansza){
    cout << "   ";
    for (int x=0; x < szerokosc; x++){
        if (x < 10) cout << x << "  ";
        else cout << x << " ";
    }
    cout << endl;
    for (int y=0; y < wysokosc; y++){
        if (y < 10) cout << y << "  ";
        else cout << y << " ";
        for (int x=0; x < szerokosc; x++){
            cout << plansza[y][x] << "  ";
        }
        cout << endl;
    }
}
int main(){
    int wybor;
    int szerokosc = 9, wysokosc =9, miny =10;

    bool poprawnyWybor = false;
    do {
        cout << "=== SAPER ===" << endl;
        cout << "1. Graj - Poziom Latwy (9x9, 10 miny)" << endl;
        cout << "2. Graj - Poziom Sredni (16x16, 40 miny)" << endl;
        cout << "3. Graj - Poziom Trudny (30x16, 99 miny)" << endl;
        cout << "Wybierz poziom trudnosci (1-3): ";
        cin >> wybor;;

        switch(wybor){
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
    
    char** plansza = new char*[wysokosc];
    for (int i=0; i < wysokosc; i++){
        plansza[i] = new char[szerokosc];
    }    
        for (int y=0; y < wysokosc; y++){
            for (int x=0; x <szerokosc; x++){
                plansza[y][x] = '#';
            }
        }
        wyswietlInstrukcje();
        cout << endl;
        wyswietlPlansze(wysokosc, szerokosc, plansza);
        wykonajRuch();

        for (int i=0; i < wysokosc; i++){
            delete[] plansza[i];
        }
        delete[] plansza;

        return 0;







    }
