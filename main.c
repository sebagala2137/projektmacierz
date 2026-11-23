 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
#define MAX 20


typedef struct _macierz{
    int w;
    int k;
    double wartosci[MAX][MAX];
} macierz;
void zapisz (char *nazwa, macierz x){
	int i,j;
 	FILE*fout = fopen(nazwa, "w");
 	fprintf(fout,"%d\n",x.w);
 	fprintf(fout,"%d\n",x.k);
 	for (i=0;i<x.w ; i++){
 		for(j=0; j<x.k ; j++){
 			fprintf(fout, "%.2f ", x.wartosci[i][j]);
		 }
 		if (i <(x.w-1))
 			fprintf(fout,"\n");
	 }
 	fclose(fout);
 	
}

macierz wczytaj(char * nazwa_pliku){
	int i;
	int j;
	double ile;
	macierz x;
	printf("bede probowal wczytac dane z pliku: %s\n", nazwa_pliku);
	FILE * fin = fopen(nazwa_pliku, "r");
	if(fin==NULL){
		printf("nie udalo sie otworzyc: %s", nazwa_pliku);
		exit(3);
	}
	ile = fscanf(fin,"%d", &x.w);
	if (ile !=1){
		printf("format zly, info o wierszach tez bylo zle");
		exit(2);
	}
	ile = fscanf(fin,"%d", &x.k);
	if (ile !=1){
		printf("format zly, info o kolumnach tez bylo zle");
		exit(2);
	}
	
	for (i=0; i<x.w;i++){
		for(j=0;j<x.k;j++){
			ile = fscanf(fin,"%lf", &x.wartosci[i][j]);
			if(ile != 1){
				printf("format zly, brakuje liczb");
				exit(2);
			}
		}
	}

	return x;
}

void wypisz(macierz x)
{
    int i, j;
    printf("\n");
    for (i = 0; i < x.w; i++) {
        for (j = 0; j < x.k; j++) {
            printf("%8.2f", x.wartosci[i][j]);
        }
        printf("\n");
    }
}




macierz pomnoz(macierz x, macierz y)
{
    int i, j, n;
    double wynik;
    macierz z;
    if(x.k != y.w){
        printf("nie mozna wykonac operacji, kolumny macierzy 1 nie sa rowne wierszom macierzy 2\n");
        exit(4);
    }
    for (i = 0; i < x.w; i++) {
        for (j = 0; j < y.k; j++) {
            wynik = 0.0;
            for (n = 0; n < x.k; n++) {
            wynik = wynik + x.wartosci[i][n] * y.wartosci[n][j];
            }
        z.wartosci[i][j] = wynik;
        }
    }
    return z;
}
macierz dodaj(macierz x, macierz y){
    int i,j;
    macierz z;
    if(x.w != y.w){
        printf("nie mozna wykonac operacji, ilosc wierszy lub kolumn macierzy rozni sie\n");

        exit(4);
    }
    if(x.k != y.k){
        printf("nie mozna wykonac operacji, ilosc kolumn macierzy rozni sie\n");
        exit(4);
    }
    for(i=0;i<x.w;i++){
        for(j=0;j<x.k;j++){
            z.wartosci[i][j] = x.wartosci[i][j] + y.wartosci[i][j];
        }   
    }
    return z;
}

macierz odejmij(macierz x, macierz y){
    int i,j;
    macierz z;
    if(x.w != y.w){
        printf("nie mozna wykonac operacji, ilosc wierszy lub kolumn macierzy rozni sie\n");
        exit(4);
    }
    if(x.k != y.k){
        printf("nie mozna wykonac operacji, ilosc kolumn macierzy rozni sie\n");
        exit(4);
    }
    for(i=0;i<x.w;i++){
        for(j=0;j<x.k;j++){
            z.wartosci[i][j] = x.wartosci[i][j] - y.wartosci[i][j];
        }   
    }
    return z;
}


int main(){
    int o;
    macierz m1;
    macierz m2;
    macierz m3;
    char a[10];
    char b[10];
    printf("dostepne pliki wraz z programem:\n A.txt \n B.txt \n C.txt \n D.txt \n F.txt \n G.txt \n \n ");
    printf("podaj nazwe pierwszeg pliku:\n");
    scanf("%s", a);
    m1 = wczytaj(a);
    printf("podaj nazwe drugiego pliku:\n");
    scanf("%s", b);
    m2 = wczytaj(b);
    printf("wybiez operacje; 1 - dodawanie; 2 - odejmowanie; 3 - mnozenie\n");
    scanf("%ld", &o);
    if(o==1){
        m3=dodaj(m1,m2);
        wypisz(m1);
        wypisz(m2);
        wypisz(m3);
        zapisz("wynik.txt",m3);
        printf("wynik zapisano w pliku wynik.txt");
    }
    else if(o==2){
        m3=odejmij(m1,m2);
        wypisz(m1);
        wypisz(m2);
        wypisz(m3);
        zapisz("wynik.txt",m3);
        printf("wynik zapisano w pliku wynik.txt");
    }
    else if(o==3){
        m3=pomnoz(m1,m2);
        wypisz(m1);
        wypisz(m2);
        wypisz(m3);
        zapisz("wynik.txt",m3);
        printf("wynik zapisano w pliku wynik.txt");
    }
    else if(o>3||o<0){
        printf("nie ma takiej operacji");
        exit(2);

    }
    printf("\n");






    return 0;
}