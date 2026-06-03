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
int main(){
    int wybor;
    int szerokosc = 9, wysokosc =9, miny =10;
    do {
        cout << "=== SAPER ===" << endl;
        cout << "1. Graj - Poziom Latwy (9x9, 10 min)" << endl;
        cout << "2. Graj - Poziom Sredni (16x16, 40 min)" << endl;
        cout << "3. Graj - Poziom Trudny (30x16, 99 min)" << endl;
    }
}
