#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Dugum {
    int veri;
    struct Dugum* onceki;
    struct Dugum* sonraki;
};

struct CiftYonluBagliListe {
    struct Dugum* bas;
    struct Dugum* son;
};

//Dugum olusturmak icin struct Dugum* dugumOlustur kalıbını kullandim.
struct Dugum* dugumOlustur(int veri) {
    struct Dugum* yeniDugum = (struct Dugum*)malloc(sizeof(struct Dugum));
    
    yeniDugum->veri = veri;
    yeniDugum->onceki = NULL;
    yeniDugum->sonraki = NULL;
    return yeniDugum;
}

int randomsayiOlustur(int mod,int arti){
    int sonuc;
    sonuc = rand() % mod + arti;
    return sonuc;
}

//Listele(): Bağlı listeyi baştan sona listeleyiniz adimini yaptim.
void ListeOlustur(struct CiftYonluBagliListe* liste) {
    int N = randomsayiOlustur(7, 4);
    int kullanilanlar[N];
    for (int i = 0; i < N; i++) {
        kullanilanlar[i] = 0;
    }

    srand(time(NULL));

    for (int i = 0; i < N; i++) {
        int sayi;
        do {
            sayi = randomsayiOlustur(N, 1); 
        } while (kullanilanlar[sayi - 1] != 0); 
        kullanilanlar[sayi - 1] = 1;

        struct Dugum* yeniDugum = dugumOlustur(sayi);
        if (liste->bas == NULL) {
            liste->bas = yeniDugum;
            liste->son = yeniDugum;
        } else {
            yeniDugum->onceki = liste->son;
            liste->son->sonraki = yeniDugum;
            liste->son = yeniDugum;
        }
    }
}

void yazdir(struct CiftYonluBagliListe* liste) {
    printf("Bagli liste: ");
    struct Dugum* simdiki = liste->bas;
    while (simdiki != NULL) {
        printf("%d ", simdiki->veri);
        simdiki = simdiki->sonraki;
    }
    printf("\n");
}

int SaymaIslemiYap(struct CiftYonluBagliListe* liste) {
    if (liste == NULL || liste->bas == NULL || liste->bas->sonraki == NULL) {
        return 0;
    }

    struct Dugum* bas = liste->bas;
    int toplam = 0;

    while (bas != NULL) {
        toplam += bas->veri;
        bas = bas->sonraki;
    }

    int sinir = toplam / 2;

    int simdiki_toplam = 0;
    bas = liste->bas;
    while (bas != NULL) {
        simdiki_toplam += bas->veri;
        printf("%d", bas->veri);
        bas = bas->sonraki;
        if (simdiki_toplam > sinir) {
            break;
        }
        if (bas != NULL) {
            printf("+");
        }
    }
    printf(" - ");
    while (bas != NULL) {
        printf("%d", bas->veri);
        bas = bas->sonraki;
        if (bas != NULL) {
            printf("+");
        }
    }
    int fark = toplam-2*simdiki_toplam;
    if (fark < 0) {
        fark *= -1;
    }
    printf(" = %d\n", fark);
    return fark;
}

void DugumEkleyerekFarkiEsitle(struct CiftYonluBagliListe* liste) {
    if (liste->son == NULL || liste->son->onceki == NULL) {
        printf("Listede yeterli sayida dugum yok.\n");
        return;
    }

    int fark = liste->son->veri - liste->son->onceki->veri;
    if (fark < 0) {
        fark *= -1;
    }

    struct Dugum* yeniDugum = dugumOlustur(fark);
    yeniDugum->onceki = liste->son->onceki;
    yeniDugum->sonraki = liste->son;
    liste->son->onceki->sonraki = yeniDugum;
    liste->son->onceki = yeniDugum;

    printf("---%d nolu dugum eklendi---\n", fark);

    SaymaIslemiYap(liste);
}

void DugumCikararakFarkiEsitle(struct CiftYonluBagliListe* liste) {
    if (liste == NULL || liste->bas == NULL) {
        return;
    }

    struct Dugum* sol = liste->bas;
    struct Dugum* sag = liste->son;
    int toplam = 0;

    struct Dugum* temp = liste->bas;
    while (temp != NULL) {
        toplam += temp->veri;
        temp = temp->sonraki;
    }

    int sinir = toplam / 2;
    int simdiki_toplam = 0;

    while (sol != NULL && simdiki_toplam + sol->veri <= sinir) {
        simdiki_toplam += sol->veri;
        sol = sol->sonraki;
    }

    if (sol != NULL && sol->onceki != NULL) {
        struct Dugum* silinecek = sol->onceki;
        int silinecekVeri = silinecek->veri;

        if (silinecek->onceki != NULL) {
            silinecek->onceki->sonraki = sol;
        } else {
            liste->bas = sol;
        }
        sol->onceki = silinecek->onceki;
        free(silinecek);

        printf("---%d nolu dugum cikarildi--- \n", silinecekVeri);
    }

    SaymaIslemiYap(liste);
}

int main() {
    struct CiftYonluBagliListe liste;
    liste.bas = NULL;
    liste.son = NULL;
   
    int secim;
    do {
        printf("\n1.Yeni Liste Olusturve Goruntele\n2. Yazdir\n3. Sayma Islemi Yap\n4. Dugum Ekleyerek Farki Esitle\n5. Dugum Cikararak Farki Esitle\n0. Cikis\nSeciminizi yapiniz: ");
        scanf("%d", &secim);

        switch (secim) {
            case 1:
                ListeOlustur(&liste);
                yazdir(&liste);
                break;
            case 2:
                yazdir(&liste);
                break;
            case 3:
                SaymaIslemiYap(&liste);
                break;
            case 4:
                DugumEkleyerekFarkiEsitle(&liste);
                break;
            case 5:
                DugumCikararakFarkiEsitle(&liste);
                break;
            case 0:
                printf("Cikis yapiliyor.\n");
                break;
            default:
                printf("Tekrar deneyin.\n");
        }
    } while(secim != 0);

    return 0;
}
