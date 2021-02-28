#include <bits/stdc++.h>
#define inf 1e9

using namespace std;

/// aici modific daca vreau ca AI sa se uite mai mult in viitor
int ADANCIME = 9;

char a[10][10];
char coloane[10];
int ordineMutari[10];
char caracter[2];

struct ColoanaScor
{
    int numarColoana, valoareScor;
};


void Initializari();
void AfisareTabla();

int MutareValida(char b[10][10], int col);
int CautaLinieLibera(char b[10][10], int col);

void Mutare(char b[10][10], int col, char c);

int NumarMutariValide(char b[10][10]);
void CopiazaBinD(char b[10][10], char e[10][10]);

int SectiuneScor(char v[5], int pozitieCaracter);
int EuristicaScorTabla(char b[10][10], int pozitieCaracter);

ColoanaScor minimax_AlphaBeta(char b[10][10], int adancime, int pozitieAI, int alpha, int beta);

void UrmatoareaMutareAI();
void UrmatoareaMutareJucator();

int VerifCastig(char b[10][10], char c);

int AlegerePrimulJucator();
void StartJoc();


int main()
{
    Initializari();

    StartJoc();

    return 0;
}

void Initializari()
{
    int i = 1;
    for(char c = '1'; c <= '7'; c++)
        coloane[i++] = c;
    coloane[0] = '-';
    coloane[8] = '-';

    ordineMutari[1] = 4;
    ordineMutari[2] = 3;
    ordineMutari[3] = 5;
    ordineMutari[4] = 2;
    ordineMutari[5] = 6;
    ordineMutari[6] = 1;
    ordineMutari[7] = 7;

    caracter[0] = 'X'; /// /AI
    caracter[1] = 'O'; /// jucator
}

void AfisareTabla()
{
    cout << "\n\n";
    cout << "\t _________________________________________\n";
    cout << "\t|     |     |     |     |     |     |     |\n";
    cout << "\t|  " << a[1][1] << "  |  " <<   a[1][2] << "  |  " << a[1][3] << "  |  " << a[1][4] << "  |  " << a[1][5] << "  |  " << a[1][6] << "  |  " << a[1][7] << "  |\n";
    cout << "\t|_____|_____|_____|_____|_____|_____|_____|\n";
    cout << "\t|     |     |     |     |     |     |     |\n";
    cout << "\t|  " << a[2][1] << "  |  " << a[2][2] << "  |  " << a[2][3] << "  |  " << a[2][4] << "  |  " << a[2][5] << "  |  " << a[2][6] << "  |  " << a[2][7] << "  |\n";
    cout << "\t|_____|_____|_____|_____|_____|_____|_____|\n";
    cout << "\t|     |     |     |     |     |     |     |\n";
    cout << "\t|  " << a[3][1] << "  |  " << a[3][2] << "  |  " << a[3][3] << "  |  " << a[3][4] << "  |  " << a[3][5] << "  |  " << a[3][6] << "  |  " << a[3][7] << "  |\n";
    cout << "\t|_____|_____|_____|_____|_____|_____|_____|\n";
    cout << "\t|     |     |     |     |     |     |     |\n";
    cout << "\t|  " << a[4][1] << "  |  " << a[4][2] << "  |  " << a[4][3] << "  |  " << a[4][4] << "  |  " << a[4][5] << "  |  " << a[4][6] << "  |  " << a[4][7] << "  |\n";
    cout << "\t|_____|_____|_____|_____|_____|_____|_____|\n";
    cout << "\t|     |     |     |     |     |     |     |\n";
    cout << "\t|  " << a[5][1] << "  |  " << a[5][2] << "  |  " << a[5][3] << "  |  " << a[5][4] << "  |  " << a[5][5] << "  |  " << a[5][6] << "  |  " << a[5][7] << "  |\n";
    cout << "\t|_____|_____|_____|_____|_____|_____|_____|\n";
    cout << "\t|     |     |     |     |     |     |     |\n";
    cout << "\t|  " << a[6][1] << "  |  " << a[6][2] << "  |  " << a[6][3] << "  |  " << a[6][4] << "  |  " << a[6][5] << "  |  " << a[6][6] << "  |  " << a[6][7] << "  |\n";
    cout << "\t|_____|_____|_____|_____|_____|_____|_____|\n";
}

int MutareValida(char b[10][10], int col)
{
    return (col >= 1 && col <= 7 && b[1][col] == NULL);
}

int CautaLinieLibera(char b[10][10], int col)
{
    int lin, i;
    lin = -1;
    for(i = 6; i >= 1 && lin == -1; i--)
        if(b[i][col] == NULL)
            lin = i;
    return lin;
}

void Mutare(char b[10][10], int col, char c)
{
    if(!MutareValida(b, col))
    {
        cout << "\nMutarea nu este valida!";
        AfisareTabla();
        UrmatoareaMutareJucator();
    }
    else
    {
        int lin;
        lin = CautaLinieLibera(b, col);
        b[lin][col] = c;
    }
}

void CopiazaBinD(char b[10][10], char e[10][10])
{
    for(int i = 1; i <= 6; i++)
        for(int j = 1; j <= 7; j++)
            e[i][j] = b[i][j];
}

int NumarMutariValide(char b[10][10])
{
    int nrm = 0;
    for(int i = 1; i <= 7; i++)
        if(b[1][i] == NULL)
            nrm++;
    return nrm;
}

int CautaMutareRandom(char b[10][10])
{
    int pozrand, nrm = 0;
    int valide[] = {0, 0, 0, 0, 0, 0, 0};

    for(int i = 1; i <= 6; i++)
        if(b[i][6] == NULL)
            valide[nrm++] = i;
    pozrand = rand() % 8;
    return valide[pozrand];
}

int EuristicaScorTabla(char b[10][10], int pozitieCaracter)
{
    /**
    vreau sa verific:
    cate linii de 3+1 am - scor 10
    cate linii de 2+2 am - scor 5
    */

    int scor, i, j, c, d, lin3, lin2;
    scor = 0;
    lin3 = lin2 = 0;

    /// pe orizontala
    for(i = 1; i <= 6; i++)
        for(j = 1; j <= 4; j++)
        {
            c = d = 0;
            if(b[i][j] == caracter[pozitieCaracter]) c++;
            if(b[i][j+1] == caracter[pozitieCaracter]) c++;
            if(b[i][j+2] == caracter[pozitieCaracter]) c++;
            if(b[i][j+3] == caracter[pozitieCaracter]) c++;

            if(b[i][j] == NULL) d++;
            if(b[i][j+1] == NULL) d++;
            if(b[i][j+2] == NULL) d++;
            if(b[i][j+3] == NULL) d++;

            if(c == 3 && d == 1) lin3++;
            if(c == 2 && d == 2) lin2++;
        }

    /// pe verticala
    for(j = 1; j <= 7; j++)
        for(i = 1; i <= 3; i++)
        {
            c = d = 0;
            if(b[i][j] == caracter[pozitieCaracter]) c++;
            if(b[i+1][j] == caracter[pozitieCaracter]) c++;
            if(b[i+2][j] == caracter[pozitieCaracter]) c++;
            if(b[i+3][j] == caracter[pozitieCaracter]) c++;

            if(b[i][j] == NULL) d++;
            if(b[i+1][j] == NULL) d++;
            if(b[i+2][j] == NULL) d++;
            if(b[i+3][j] == NULL) d++;

            if(c == 3 && d == 1) lin3++;
            if(c == 2 && d == 2) lin2++;
        }

    /// pe diagonala principala
    for(i = 1; i <= 3; i++)
        for(j = 1; j <= 4; j++)
        {
            c = d = 0;
            if(b[i][j] == caracter[pozitieCaracter]) c++;
            if(b[i+1][j+1] == caracter[pozitieCaracter]) c++;
            if(b[i+2][j+2] == caracter[pozitieCaracter]) c++;
            if(b[i+3][j+3] == caracter[pozitieCaracter]) c++;

            if(b[i][j] == NULL) d++;
            if(b[i+1][j+1] == NULL) d++;
            if(b[i+2][j+2] == NULL) d++;
            if(b[i+3][j+3] == NULL) d++;

            if(c == 3 && d == 1) lin3++;
            if(c == 2 && d == 2) lin2++;
        }

    /// pe diagonala secundara
    lin3 = lin2 = 0;
    for(i = 6; i >= 3; i--)
        for(j = 1; j <= 4; j++)
        {
            c = d = 0;
            if(b[i][j] == caracter[pozitieCaracter]) c++;
            if(b[i-1][j+1] == caracter[pozitieCaracter]) c++;
            if(b[i-2][j+2] == caracter[pozitieCaracter]) c++;
            if(b[i-3][j+3] == caracter[pozitieCaracter]) c++;

            if(b[i][j] == NULL) d++;
            if(b[i-1][j+1] == NULL) d++;
            if(b[i-2][j+2] == NULL) d++;
            if(b[i-3][j+3] == NULL) d++;

            if(c == 3 && d == 1) lin3++;
            if(c == 2 && d == 2) lin2++;
        }

    scor += lin3 * 10 + lin2 * 5;

    return scor;
}

ColoanaScor minimax_AlphaBeta(char b[10][10], int adancime, int pozitieCaracter, int alpha, int beta)
{
    ColoanaScor cazParticular;
    cazParticular.valoareScor = 0;

    /// daca adancimea e 0 fac euristica si nu mai parcurg in continuare
    if(adancime == 0)
    {
        cazParticular.numarColoana = -1;
        cazParticular.valoareScor = EuristicaScorTabla(b, pozitieCaracter);
        return cazParticular;
    }

    /// in urmatoarele cazuri e nod terminal adica se termina jocul
    if(VerifCastig(b, 'X')) /// castiga AI
    {
        cazParticular.numarColoana = -1;
        cazParticular.valoareScor = inf;
        return cazParticular;
    }
    if(VerifCastig(b,'O')) /// castiga jucatorul
    {
        cazParticular.numarColoana = -1;
        cazParticular.valoareScor = -inf;
        return cazParticular;
    }
    if(NumarMutariValide(b) == 0) /// e remiza
    {
        cazParticular.numarColoana = -1;
        cazParticular.valoareScor = 0;
        return cazParticular;
    }

    ColoanaScor scor;
    int scor_nou;

    char d[10][10];
    /// daca joaca AI vreau sa maximizez scorul
    if(caracter[pozitieCaracter] == 'X')
    {
        scor.valoareScor = -inf;
        scor.numarColoana = CautaMutareRandom(b);

        for(int colord = 1; colord <= 7; colord++)
        {
            int col = ordineMutari[colord];
            if(MutareValida(b, col))
            {
                /// fac eu mutarea asta in alta matrice
                CopiazaBinD(b, d);
                Mutare(d, col, caracter[pozitieCaracter]);

                /// ma duc sa ii fac mutarea jucatorului cu caracterul celalalt
                scor_nou = minimax_AlphaBeta(d, adancime - 1, abs(pozitieCaracter - 1), alpha, beta).valoareScor;

                if(scor_nou > scor.valoareScor)
                {
                    scor.valoareScor = scor_nou;
                    scor.numarColoana = col;
                }

                /// actualizez alpha daca e nevoie
                alpha = max(alpha, scor.valoareScor);
                if(alpha >= beta)
                    break;
            }
        }
        return scor;
    }
    /// daca joaca jucatorul vreau sa minimizez scorul
    else
    {
        scor.valoareScor = inf;
        scor.numarColoana = CautaMutareRandom(b);

        for(int colord = 1; colord <= 7; colord++)
        {
            int col = ordineMutari[colord];
            if(MutareValida(b, col))
            {
                /// fac mutarea jucatorului in alta matrice
                CopiazaBinD(b, d);
                Mutare(d, col, caracter[pozitieCaracter]);

                /// ma duc sa fac mutarea mea cu caracterul celalalt
                scor_nou = minimax_AlphaBeta(d, adancime - 1, abs(pozitieCaracter - 1), alpha, beta).valoareScor;

                if(scor_nou < scor.valoareScor)
                {
                    scor.valoareScor = scor_nou;
                    scor.numarColoana = col;
                }

                /// actualizez beta daca e nevoie
                beta = min(beta, scor.valoareScor);
                if(alpha >= beta)
                    break;
            }
        }
        return scor;
    }
}

void UrmatoareaMutareAI()
{
    int coloanaAleasa;
    char d[10][10];
    CopiazaBinD(a,d);
    coloanaAleasa = minimax_AlphaBeta(d, ADANCIME, 0, -inf, inf).numarColoana;

    Mutare(a, coloanaAleasa, 'X');
    if(coloane[coloanaAleasa] != '-' && a[1][coloanaAleasa] != NULL)
        coloane[coloanaAleasa] = '-';

    if(VerifCastig(a, 'X') == 1)
    {
        AfisareTabla();
        cout << "\n\n\t\t\tAi pierdut!\n";
        exit(0);
    }
}

void UrmatoareaMutareJucator()
{
    int mutareJucator;
    cout << "\n\t   " << coloane[1] << "     " << coloane[2] << "     " << coloane[3] << "     " << coloane[4] << "     " << coloane[5] << "     " << coloane[6] << "     " << coloane[7] << "\n";
    cout << "\nCare este mutarea ta?\n\n";
    cin >> mutareJucator;
    cout << "\n";

    Mutare(a, mutareJucator, 'O');
    if(coloane[mutareJucator] != '-' && a[1][mutareJucator] != NULL)
        coloane[mutareJucator] = '-';

    if(VerifCastig(a, 'O') == 1)
    {
        AfisareTabla();
        cout << "\n\n\t\t\tAi castigat!\n";
        exit(0);
    }
}

int VerifCastig(char b[10][10], char c)
{
    /// verifica daca este stare de castig pe b pentru caracterul c
    int i, j;

    /// verific pe orizontala
    for(i = 1; i <= 6; i++)
        for(j = 1; j <= 4; j++)
            if(b[i][j] == c && b[i][j+1] == c && b[i][j+2] == c && b[i][j+3] == c)
                return 1;

    /// verific pe verticala
    for(i = 1; i <= 3; i++)
        for(j = 1; j <= 7; j++)
            if(b[i][j] == c && b[i+1][j] == c && b[i+2][j] == c && b[i+3][j] == c)
                return 1;

    /// verific pe diagonala principala
    for(i = 1; i <= 3; i++)
        for(j = 1; j <= 4; j++)
            if(b[i][j] == c && b[i+1][j+1] == c && b[i+2][j+2] == c && b[i+3][j+3] == c)
                return 1;

    /// verific pe diagonala secundara
    for(i = 4; i <= 6; i++)
        for(j = 4; j  >= 1; j--)
            if(b[i][j] == c && b[i-1][j+1] == c && b[i-2][j+2] == c && b[i-3][j+3] == c)
                return 1;

    return 0;
}

int AlegerePrimulJucator()
{
    /// returneaza 1 daca incepe jucatorul
    /// returneaza 0 daca incepe AI

    cout << "\nVrei sa incepi primul? ( da / nu )\n\n";
    char c[5];
    cin >> c;
    cout << "\n";
    if((c[0] == 'D' || c[0] == 'd') && (c[1] == 'A' || c[1] == 'a'))
        return 1;
    else if((c[0] == 'N' || c[0] == 'n') && (c[1] == 'U' || c[1] == 'u'))
        return 0;
    return 0;
}

void StartJoc()
{
    int jucator;
    jucator = AlegerePrimulJucator();

    while(true)
    {
        if(NumarMutariValide(a) == 0)
        {
            AfisareTabla();
            cout << "\n\n\t\t\tEste remiza!\n";
            exit(0);
        }

        if(jucator == 1) /// jucatorul pune pe tabla
        {
            AfisareTabla();
            UrmatoareaMutareJucator();
            jucator = 0;
        }
        else /// AI pune pe tabla
        {
            AfisareTabla();
            UrmatoareaMutareAI();
            jucator = 1;
        }
    }
}
