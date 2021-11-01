//Rafal Szychowski
#include <iostream>

bool czyZaPolowa(int punkt, int krawedz_szescianu){

    if(punkt > ((krawedz_szescianu - 1) / 2 )) return true;

    return false;
}


void minorMacierzy(long long int mat[32][32], long long int tmp[32][32], int q, int n){

    int i = 0;
    int j = 0;

    for (int a = 1; a < n; a++, i++){        //petle po wierszach i kolumnach, zaczyna od 1, bo rzad o indeksie 0 jest skreslony

            j = 0;

        for (int b = 0; b < n; b++){

            if (b != q){                //jezeli kolumna nie zostala skreslona, to wpisywanie wartosci do macierzy tmp
                tmp[i][j] = mat[a][b];
                j++;
            }
        }
    }
}


long long int wyznacznikMacierzy(long long int mat[32][32], int n){

    long long int det = 0;

    if (n == 1) return mat[0][0];           //jezeli macierz jest 1x1

    if (n == 2) return( (mat[0][0] * mat[1][1]) - (mat[1][0] * mat[0][1]) );        //jezeli macierz jest 2x2

    int znak = 1;
    long long int tmp[32][32];


    for (int i = 0; i < n; i++){                //petla po pierwszym rzedzie macierzy


        minorMacierzy(mat, tmp, i, n);          //tworzenie minora dla kazdej skreslonej kolumny
        det += znak * mat[0][i] * wyznacznikMacierzy(tmp, n - 1);   //rekurencja wszystkich minorów macierzy

        znak = -znak;
    }

    return det;
}


long long int szybkiWyznacznikMacierzy(long long int mat[32][32], int n){

    int tmp = 0;

    if (n == 1) return mat[0][0];

    if (n == 2) return( (mat[0][0] * mat[1][1]) - (mat[1][0] * mat[0][1]) );

    for(int col = 0; col < n; col++){

        bool found = false;

        for(int row = col; row < n; row++){

            if(mat[row][col]){
                if ( row != col ){

                    for(int i = 0; i < n; i++){
                        tmp = mat[row][i];
                        mat[row][i] = mat[col][i];
                        mat[col][i] = tmp;
                    }
                }

                found = true;
                break;
         }
      }

      if(!found) return 0;


      for(int row = col + 1; row < n; row++){

            while(true){

                int del = mat[row][col] / mat[col][col];

                for (int j = col; j < n; j++){
                    mat[row][j] -= del * mat[col][j];
                }

                if (mat[row][col] == 0) break;

                else{
                    for(int i = 0; i < n; i++){
                        tmp = mat[row][i];
                        mat[row][i] = mat[col][i];
                        mat[col][i] = tmp;
                    }
                }
            }
        }
    }

    long long int det = 1;

    for(int i = 0; i < n; i++) {
        det *= mat[i][i];
    }

    return det;
}


bool lezyWCzworoscianie(int x, int y, int z, int l, int v, int p, int l_1, int v_1, int p_1){


    int x1, y1, z1;     //deklaracja wspolrzednch wszystkich wierzcholkow
    int x2, y2, z2;
    int x3, y3, z3;
    int x4, y4, z4;

    x1 = v; y1 = l; z1 = p;     //wierzcholki roznia sie tylko jedna zmienna od glownego wierzcholka
    x2 = v_1; y2 = l; z2 = p;
    x3 = v; y3 = l_1; z3 = p;
    x4 = v; y4 = l; z4 = p_1;

    //std::cout << "\n\nx = " << x << "\ty = " << y << "\tz = " << z << "\n";
    //std::cout << "x1 = " << x1 << "\ty1 = " << y1 << "\tz1 = " << z1 << "\n";
    //std::cout << "x2 = " << x2 << "\ty2 = " << y2 << "\tz2 = " << z2 << "\n";
    //std::cout << "x3 = " << x3 << "\ty3 = " << y3 << "\tz3 = " << z3 << "\n";
    //std::cout << "x4 = " << x4 << "\ty4 = " << y4 << "\tz4 = " << z4 << "\n\n";

    int D0, D1, D2, D3, D4; //Wyznaczniki 5 macierzy sluzace do obliczen

    long long int M0[32][32] = { {x1, y1, z1, 1}, {x2, y2, z2, 1}, {x3, y3, z3, 1}, {x4, y4, z4, 1} };  //macierze do obliczenia wyznaczników
    long long int M1[32][32] = { {x, y, z, 1}, {x2, y2, z2, 1}, {x3, y3, z3, 1}, {x4, y4, z4, 1} };
    long long int M2[32][32] = { {x1, y1, z1, 1}, {x, y, z, 1}, {x3, y3, z3, 1}, {x4, y4, z4, 1} };
    long long int M3[32][32] = { {x1, y1, z1, 1}, {x2, y2, z2, 1}, {x, y, z, 1}, {x4, y4, z4, 1} };
    long long int M4[32][32] = { {x1, y1, z1, 1}, {x2, y2, z2, 1}, {x3, y3, z3, 1}, {x, y, z, 1} };

    D0 = wyznacznikMacierzy(M0, 4);
    D1 = wyznacznikMacierzy(M1, 4);
    D2 = wyznacznikMacierzy(M2, 4);
    D3 = wyznacznikMacierzy(M3, 4);
    D4 = wyznacznikMacierzy(M4, 4);

    //std::cout << "D: " << D0 << "\t" << D1 << "\t" << D2 << "\t" << D3 << "\t" << D4 << "\n";


    if( (D0 >= 0 && D1 >= 0 && D2 >= 0 && D3 >= 0 && D4 >= 0) || (D0 <= 0 && D1 <= 0 && D2 <= 0 && D3 <= 0 && D4 <= 0) ){

        //std::cout << "TAK\n";
        return true;
    }
    else{
        //std::cout << "NIE\n";
        return false;
    }
}


bool lezyWSferze(int spr_h, int spr_w, int spr_d, int wierzcholek_h, int wierzcholek_w, int wierzcholek_d, int promien){


    if((((spr_h - wierzcholek_h)*(spr_h - wierzcholek_h)) + ((spr_w - wierzcholek_w)*(spr_w - wierzcholek_w)) + ((spr_d - wierzcholek_d)*(spr_d - wierzcholek_d))) <= (promien * promien))
    return true;

    return false;
}


bool lezyWOktalu(int spr_h, int spr_w, int spr_d, int wierzcholek_h, int wierzcholek_w, int wierzcholek_d, int promien, int krawedz_szescianu){

    if(!lezyWSferze(spr_h, spr_w, spr_d, wierzcholek_h, wierzcholek_w, wierzcholek_d, promien)) return false;

    bool za_polowa_h = false;
    bool za_polowa_w = false;
    bool za_polowa_d = false;

    if(czyZaPolowa(wierzcholek_h, krawedz_szescianu)) za_polowa_h = true;
    if(czyZaPolowa(wierzcholek_w, krawedz_szescianu)) za_polowa_w = true;
    if(czyZaPolowa(wierzcholek_d, krawedz_szescianu)) za_polowa_d = true;

    if( (za_polowa_h && spr_h >= wierzcholek_h - promien && spr_h <= wierzcholek_h ) || (!za_polowa_h && spr_h >= wierzcholek_h && spr_h <= wierzcholek_h + promien) ){
        if( (za_polowa_w && spr_w >= wierzcholek_w - promien && spr_w <= wierzcholek_w ) || (!za_polowa_w && spr_w >= wierzcholek_w && spr_w <= wierzcholek_w + promien) ){
            if( (za_polowa_d && spr_d >= wierzcholek_d - promien && spr_d <= wierzcholek_d ) || (!za_polowa_d && spr_d >= wierzcholek_d && spr_d <= wierzcholek_d + promien) ){
                return true;
            }
        }
    }

    return false;
}



int main(){

    int bok_szescianu;      //dlugosc krawedzi
    std::cin >> bok_szescianu;
    int bok_szescianu_k = bok_szescianu * 1000;
    int srodek_boku_k = bok_szescianu / 2;


    int Szescian[32][32][32] = {0};

    for(int d = 0; d < bok_szescianu; d++){          //wpisywanie danych szescianu
        for(int h = 0; h < bok_szescianu; h++){
            for(int w = 0; w < bok_szescianu; w++){
                std::cin >> Szescian[h][w][d];
            }
        }
    }

    char test;
    std::cin >> test;


    while(test != 'E'){

        if(test == 'T'){

            int l;  //wspolrzedna poziomu wierzcholka
            std::cin >> l;

            int v;  //wspolrzedna pionu wierzcholka
            std::cin >> v;

            int p;  //wpolrzedna panelu wierzcholka
            std::cin >> p;

            int e;  //dlugosc prostopadlych krawedzi czworoscianu
            std::cin >> e;

            int suma;   //zmienna przechowujaca wartosc liczb zawartych w czworoscianie
            suma = 0;


            bool za_polowa_poziom = czyZaPolowa(l, bok_szescianu);
            bool za_polowa_pion = czyZaPolowa(v, bok_szescianu);
            bool za_polowa_panel = czyZaPolowa(p, bok_szescianu);


            int l_1, v_1, p_1;          //wspolrzedne pozostalych wierzcholkow


            if(za_polowa_pion)
                v_1 = v - e;
            else
                v_1 = v + e;


            if(za_polowa_poziom)
                l_1 = l - e;
            else
                l_1 = l + e;


            if(za_polowa_panel)
                p_1 = p - e;
            else
                p_1 = p + e;


            int x1, y1, z1;     //deklaracja wspolrzednch wszystkich wierzcholkow
            int x2, y2, z2;
            int x3, y3, z3;
            int x4, y4, z4;

            x1 = v; y1 = l; z1 = p;     //wierzcholki roznia sie tylko jedna zmienna od glownego wierzcholka
            x2 = v_1; y2 = l; z2 = p;
            x3 = v; y3 = l_1; z3 = p;
            x4 = v; y4 = l; z4 = p_1;



            if(e == 0){     //jezeli czworoscian sklada sie z jednego punktu
                suma = Szescian[l][v][p];
            }

            else{
                for(int d = 0; d < bok_szescianu; d++){
                    for(int h = 0; h < bok_szescianu; h++){
                        for(int w = 0; w < bok_szescianu; w++){
                            if(lezyWCzworoscianie(w, h, d, l, v, p, l_1, v_1, p_1)) suma += Szescian[h][w][d];
                            //std::cout << "h - w - d: " << h << " ; " << w << " ; " << d << "\t" << Szescian[h][w][d] << "\n";
                        }
                    }
                }
            }

            std::cout << suma << "\n";

        }


        if(test == 'C'){

            int l;      //wspolrzedna poziomu wierzcholka
            std::cin >> l;

            int v;      //wspolrzedna pionu wierzcholka
            std::cin >> v;

            int p;      //wpolrzedna panelu wierzcholka
            std::cin >> p;

            int h_p;    //wysokosc prostopadloscianu
            std::cin >> h_p;

            int w_p;    //szerokosc prostopadloscianu
            std::cin >> w_p;

            int d_p;    //glebokosc prostopadloscianu
            std::cin >> d_p;

            int suma;   //zmienna przechowujaca wartosc liczb zawartych w czworoscianie
            suma = 0;


            bool za_polowa_poziom = czyZaPolowa(l, bok_szescianu);
            bool za_polowa_pion = czyZaPolowa(v, bok_szescianu);
            bool za_polowa_panel = czyZaPolowa(p, bok_szescianu);


            if(za_polowa_poziom) l = l - h_p;
            if(za_polowa_pion) v = v - w_p;
            if(za_polowa_panel) p = p - d_p;


            if(h_p == 0 && w_p == 0 && d_p == 0){

                suma = Szescian[l][v][p];
            }
            else {

                for(int d = p; d <= (p + d_p); d++){
                    //std::cout << "d: " << d << "\tp: " << p << "\td_p: " << d_p << "\n" ;

                    if(d >= 0 && d < bok_szescianu){

                        for(int h = l; h <= (l + h_p); h++){
                            //std::cout << "h: " << h << "\n";

                            if(h >= 0 && h < bok_szescianu){

                                for(int w = v; w <= (v + w_p); w++){
                                    //std::cout << "w: " << w << "\n";

                                    if(w >= 0 && w < bok_szescianu) suma += Szescian[h][w][d];
                                }
                            }
                        }
                    }
                }
            }

            std::cout << suma << "\n";

        }

        if(test == 'O'){

            int l;      //wspolrzedna poziomu srodka
            std::cin >> l;

            int v;      //wspolrzedna pionu srodka
            std::cin >> v;

            int p;      //wpolrzedna panelu srodka
            std::cin >> p;

            int r;      //promien
            std::cin >> r;

            int suma;   //zmienna przechowujaca wartosc liczb zawartych w czworoscianie
            suma = 0;


            if(r == 0){     //jezeli oktal sklada sie z jednego punktu
                suma = Szescian[l][v][p];
            }

            else{
                for(int d = 0; d < bok_szescianu; d++){
                    for(int h = 0; h < bok_szescianu; h++){
                        for(int w = 0; w < bok_szescianu; w++){
                            if(lezyWOktalu( h, w, d, l, v, p, r, bok_szescianu)) suma += Szescian[h][w][d];
                            //std::cout << "h - w - d: " << h << " ; " << w << " ; " << d << "\t" << Szescian[h][w][d] << "\n";
                        }
                    }
                }
            }

            std::cout << suma << "\n";


        }









        if(test == 'D'){

            char operacja;
            operacja = '\0';
            std::cin >> operacja;

            int i;
            std::cin >> i;

            long long int tmp[32][32] = {0};

            if(operacja == 'l'){        //poziom

                for(int a = 0; a < bok_szescianu; a++){
                    for(int b = 0; b < bok_szescianu; b++){
                        tmp[a][b] = Szescian[i][a][b];
                    }
                }

                long long int D;
                if(bok_szescianu > 12)
                    D = szybkiWyznacznikMacierzy(tmp, bok_szescianu);

                else
                    D = wyznacznikMacierzy(tmp, bok_szescianu);

                std::cout << D << "\n";
            }



            if(operacja == 'v'){        //pion

                for(int a = 0; a < bok_szescianu; a++){
                    for(int b = 0; b < bok_szescianu; b++){
                        tmp[a][b] = Szescian[a][i][b];
                    }
                }

                long long int D;
                if(bok_szescianu > 12)
                    D = szybkiWyznacznikMacierzy(tmp, bok_szescianu);

                else
                    D = wyznacznikMacierzy(tmp, bok_szescianu);

                std::cout << D << "\n";
            }



            if(operacja == 'p'){        //panel

                for(int a = 0; a < bok_szescianu; a++){
                    for(int b = 0; b < bok_szescianu; b++){
                        tmp[a][b] = Szescian[a][b][i];
                    }
                }

                long long int D;
                if(bok_szescianu > 12)
                    D = szybkiWyznacznikMacierzy(tmp, bok_szescianu);

                else
                    D = wyznacznikMacierzy(tmp, bok_szescianu);

                std::cout << D << "\n";
            }



        }


        std::cin >> test;

    }

}
