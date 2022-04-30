#include <iostream>
#include <conio.h>
#include <chrono>
#include <ctime>
#include <cstdlib>
using namespace std;

struct Dugum {
    int veri;       //d���m�n say�sal de�eri
    Dugum* sonraki; //sonraki d���me i�aret�i
};
struct Kuyruk {
    Dugum* bas;     //kuyru�un ba��ndaki eleman�n adresini tutar
    Dugum* son;     //kuyru�un sonundaki eleman�n adresini tutar
    void olustur(); //ba�lang�� i�in gereken tan�mlar� i�erir
    void kapat();   //program bitiminde bellek iadesi yapar
    void ekle(int); //kuyru�a yeni veri ekler
    int cikar();    //kuyruktan s�radaki eleman� ��kar�r
    bool bosMu();   //kuyruk bo� mu kontrol eder
    void yazdir();
    int boyut;
};
struct Yigin {
    Kuyruk k1, k2;  //y���n i�in kullan�lacak kuyruk de�i�kenleri
    void olustur(); //ba�lang�� i�in gereken tan�mlar� i�erir
    void kapat();   //program bitiminde bellek iadesi yapar
    void ekle(int); //kuyru�a yeni veri ekler
    int cikar();    //kuyruktan s�radaki eleman� ��kar�r
    bool bosMu();   //kuyruk bo� mu kontrol eder
    int tepe();     //y���n�n tepesindeki eleman� okur
    void yazdir();  //y���n elemanlar�n� s�rayla ekrana yazar
    int boyut;
};
void siraliEkle(Yigin* s, int x);
void yiginCikar(Yigin* s);

int main()
{
    Kuyruk* que = new Kuyruk();
    Yigin* stack = new Yigin();
    stack->ekle(3);
    stack->ekle(1);
    stack->ekle(7);
    stack->ekle(4);
    stack->ekle(8);
    cout << "Orijinal Yigin:" << endl;
    stack->yazdir();
    cout << endl;
    cout << endl;
    cout << endl;
    cout << "---yiginCikar fonksiyon cagrisi---";
    yiginCikar(stack);
    cout << endl;
    cout << endl;
    cout << endl;
    cout << "Sirali Yigin:" << endl;
    stack->yazdir();
}

void siraliEkle(Yigin* s, int x)
{
    if (s->bosMu() or x > s->tepe())
    {
        cout << x;
        s->ekle(x);
        return;
    }

    int temp = s->cikar();
    siraliEkle(s, x);

    s->ekle(temp);
}
void yiginCikar(Yigin* s)
{
    if (!s->bosMu())
    {
        int x = s->cikar();
        yiginCikar(s);

        siraliEkle(s, x);
    }
}

//YIGIN Yap�s� ile ilgili kodlar
void Yigin::olustur()
{
    k1.bas = NULL;
    k1.son = NULL;

    k2.bas = NULL;
    k2.son = NULL;
    boyut = 0;
}
void Yigin::ekle(int y)
{
    k2.ekle(y);
    while (!k1.bosMu())
    {
        k2.ekle(k1.bas->veri);
        k1.cikar();
    }
    Kuyruk k = k1;
    k1 = k2;
    k2 = k;
    boyut++;
}
int Yigin::cikar()
{
    if (k1.bosMu())
        return -1;
    boyut--;
    return k1.cikar();
}
bool Yigin::bosMu()
{
    return k1.bosMu();
}
int Yigin::tepe()
{
    if (k1.bosMu())
        return -1;
    return k1.son->veri;
}
void Yigin::yazdir()
{
    k1.yazdir();
}
void Yigin::kapat()
{

}
//########################################################

//KUYRUK Yap�s� ile ilgili kodlar
void Kuyruk::olustur()
{
    bas = NULL;
    son = NULL;
    boyut = 0;
}
void Kuyruk::ekle(int x)
{
    Dugum* temp1 = new Dugum(); //[bas -> xx -> yy -> son(zz)]
    temp1->veri = x;
    temp1->sonraki = NULL;

    if (bas == NULL)
    {
        bas = temp1;            
        son = bas;
    }
    else
    {
        son->sonraki = temp1;   //[bas -> xx -> yy -> son(zz) -> temp1]
        son = temp1;            //[bas -> xx -> yy -> zz -> son(temp1)]
    }
    boyut++;
}
int Kuyruk::cikar()
{
    Dugum* ustdugum;            //[bas -> xx -> yy -> son]
    int gecici;

    ustdugum = bas;             //[ustdugum(bas) -> xx -> yy -> son]
    bas = bas->sonraki;         //[ustdugum -> xx(bas) -> yy -> son]
    gecici = ustdugum->veri;
    delete ustdugum;            //[bas(xx) -> yy -> son]
    boyut--;
    return gecici;
}
bool Kuyruk::bosMu()
{
    return bas == NULL;
}
void Kuyruk::yazdir()
{
    Dugum* temp1 = bas;
    
    if (!bosMu())
    {
        for (int i = 1; i <= boyut; i++)
        {
            cout << temp1->veri << " ";
            temp1 = temp1->sonraki;
        }
    }
    else
    {
        cout << endl << "KUYRUK BOS!";
    }
}
void Kuyruk::kapat()
{
    Dugum* p;
    while (bas)
    {
        p = bas;
        bas = bas->sonraki;
        delete p;
    }
    boyut = 0;
}
//########################################################