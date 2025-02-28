#include <iostream>
#include <string>
#include <ctime>
using namespace std;
bool Game_over = false;
const int BOARD_SIZE = 16;
const char MINE = 'M';
const char FLAG = 'F';
const char EMPTY = ' ';
const char HIDDEN = '²';
string Lettre = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

bool board[BOARD_SIZE][BOARD_SIZE];
bool mines[BOARD_SIZE][BOARD_SIZE];
char dpBoard[BOARD_SIZE][BOARD_SIZE];


bool drapv = false;
int vc1, vc2;
int revinf1, revinf2;
bool verifL = false;

// Initialisatiob du tb 
void initializeBoard() {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = false;
            dpBoard[i][j] = HIDDEN;
        }
    }
}

void Dtb() {
    cout << endl << endl;
    cout << "   ";
    for (int L = 0; L < BOARD_SIZE; L++) {
        cout << Lettre[L] << " ";
    }
    cout << endl;

    for (int c = 0; c < BOARD_SIZE; c++) {
        cout << (c < 10 ? " " : "") << c << "|";
        for (int l = 0; l < BOARD_SIZE; l++) {
            cout << dpBoard[c][l] << "|";
        }
        cout << endl;
    }
    if (Game_over == true) {
        for (int c = 0; c < BOARD_SIZE; c++) {
            for (int l = 0; l < BOARD_SIZE; l++) {
                if (mines[c][l]) {
                    dpBoard[c][l] = MINE;

                }


            }
        }
        cout << endl << "GAME OVER" << endl;
    }

    cout << endl;

}
// Mine random sur le tb 
void minerand() {
    srand((unsigned)time(NULL));
    int nbmine = 40;// Nombre de mines par défaut
    int random;
    int random2;
    for (int placed = 0; placed < nbmine;) {
        random = rand() % BOARD_SIZE;
        random2 = rand() % BOARD_SIZE;
        if (mines[random][random2] == false) {

            if (!mines[random][random2]) {
                mines[random][random2] = true;
                placed++;
            }
        }
        else {
            placed--;
        }
    }

}

// Demande de co à l'utilisateur 
void cordinfo(int coordonner[]) {
    cout << "Entrez la ligne : ";
    cin >> coordonner[0];
    cout << "Entrez la colonne (A-P) : ";
    char col;
    cin >> col;
    coordonner[1] = toupper(col) - 'A';
}

// Sélection de diff par le joueur
void Sdiff() {
    int v;
    cout << "Choisissez une difficulter parmi celles proposer : " << endl;
    cout << "1 - Facile" << endl;
    cout << "2 - Moyen" << endl;
    cout << "3 - Difficile" << endl;
    cout << "Votre choix : ";
    cin >> v;

    switch (v) {
    case 1:
        cout << "Difficulter Facile sélectionner" << endl;
        break;
    case 2:
        cout << "Difficulter Moyenne sélectionner" << endl;
        break;
    case 3:
        cout << "Difficulter Difficile sélectionner" << endl;
        break;
    default:
        cout << "Choix invalide. Veuillez reessayer." << endl;
        Sdiff();
        break;
    }
}

// Placer un drapeau sur la map
void Drapeaux() {
    int coordonner[2];
    cordinfo(coordonner);
    vc1 = coordonner[0];
    vc2 = coordonner[1];

    if (dpBoard[vc1][vc2] == HIDDEN) {
        dpBoard[vc1][vc2] = FLAG;
    }
    else if (dpBoard[vc1][vc2] == FLAG) {
        dpBoard[vc1][vc2] = HIDDEN;
    }
    drapv = true;
}

// Vérification pose tb
bool Validm(int co1, int co2) {
    return (co1 >= 0 and co1 < BOARD_SIZE and co2 >= 0 and co2 < BOARD_SIZE);
}

// Compteur mine 
int ctMines(int co1, int co2) {
    int ct = 0;
    for (int l = -1; l <= 1; l++) {
        for (int c = -1; c <= 1; c++) {
            if (Validm(co1 + l, co2 + c) and mines[co1 + l][co2 + c]) {
                ct++;
            }
        }
    }
    return ct;
}
// Révélation de case 
void rev(int revin1, int revins2) {
    if (!Validm(revin1, revins2) or board[revin1][revins2]) return;

    board[revin1][revins2] = true;

    if (mines[revin1][revins2]) {
        dpBoard[revin1][revins2] = MINE;
        Game_over = true;
        Dtb();

        return;
    }

    int adcMines = ctMines(revin1, revins2);
    if (adcMines > 0) {
        dpBoard[revin1][revins2] = '0' + adcMines;
    }
    else {
        dpBoard[revin1][revins2] = EMPTY;
        for (int l = -1; l <= 1; l++) {
            for (int c = -1; c <= 1; c++) {
                if (l != 0 || c != 0) {
                    rev(revin1 + l, revins2 + c);
                }
            }
        }
    }
}

// Effacement de tout 
void eraseAll() {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            dpBoard[i][j] = HIDDEN;
            board[i][j] = false;
            mines[i][j] = false;
        }
    }
}

// Effacement d'un drapeau spé 
void eraseF() {
    int coordonner[2];
    cordinfo(coordonner);
    if (dpBoard[coordonner[0]][coordonner[1]] == FLAG) {
        dpBoard[coordonner[0]][coordonner[1]] = HIDDEN;
    }
}

void restart() {
    bool exit;
    int rep;
    if (Game_over == true) {
        cout << endl << "VOULEZ VOUS RECOMMENCER UNE PARTIE" << " ?";
        cout << endl << "OUI (1)";
        cout << endl << "NON (2)" << endl;
        cin >> rep;
        switch (rep) {
        case 1:
            Game_over = false;
            eraseAll();
            initializeBoard();
            Sdiff();
            minerand();
            Dtb();
            break;
        case 2:
            exit = true;
            eraseAll();
            break;
        default:
            break;
        }
    }
    else {
        exit = false;
    }
}

int main() {

    eraseAll();
    initializeBoard();
    minerand();
    Sdiff();

    int selectedItem;
    bool exit = false;
    while (!exit) {
        system("cls");
        Dtb();
        restart();
        cout << "1. Effacer un drapeau" << endl;
        cout << "2. Placer un drapeau" << endl;
        cout << "3. Reveler une case" << endl;
        cout << "4. Quitter" << endl;
        cout << "Choisissez une action : ";
        cin >> selectedItem;

        switch (selectedItem) {
        case 1:
            eraseF();
            break;
        case 2:
            Drapeaux();
            break;
        case 3:
            int coord[2];
            cordinfo(coord);
            rev(coord[0], coord[1]);
            break;
        case 4:
            exit = true;
            cout << endl << "VOUS AVEZ ARRETER LA PARTIE" << endl;
            break;
        default:
            cout << "Choix invalide." << endl;
        }
    }
    return 0;
}