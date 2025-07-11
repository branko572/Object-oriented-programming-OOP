//Дадена е дел од дефиницијата на класата Karticka. За секоја картичка се чуваат информации за трансакциска сметка (низа од 15 знаци) , пин код (цел број) и дали има повеќе пин кодови (булова променлива).
//
//За секој картичка може да се пресмета тежината за пробивање на картичката. Тежината на пробивање е бројот на цифрите на пин кодот.
//
//Специјалните картички покрај еден задолжителен имаат уште неколку пин кодови . За овие корисници да се моделира соодветна класа SpecijalnaKaricka во која покрај дополнителните пин кодови (динамичко алоцирана низа од цели броеви) се чува и бројот на пин кодовите (цел број). Со дополнителните пин кодови се менува и тежината на пробивање на картичката и таа се зголемува за бројот на дополнителни пин кодови.
//
//Максималниот број на дополнителни пин кодови кој може да има било која картичка е P. P има фиксна вредност 4 за сите картички и оваа вредност не може да се промени.
//
//Во класите Karticka и SpecijalnaKarticka треба да се имплементираат потребните конструктори, функции за поставување и преземање и деструктор. (5 поени)
//
//За сите објекти од класите треба да се обезбедат следните функции:
//
//преоптоварен оператор << во кој се печатат информации за картичката во формат: smetka: tezina (5 поени)
//tezinaProbivanje() – ја пресметува тежината за пробивање на картичката (5 поени)
//Во класата SpecijalnaKarticka дефинирај ја функцијата:
//
//преоптоварен оператор += за додавање на нов пин код (5 поени)
//Ако се направи обид да се внесат повеќе од дозволениот број на пин кодови во безбедносниот код да се фрли исклучок (објект од класата OutOfBoundException). Фатете го исклучокот во главната функција каде што е потребно. Откако ќе го фатите отпечатете соодветна порака за грешка (Brojot na pin kodovi ne moze da go nadmine dozvolenoto) и справете се со исклучокот така да додадениот пин код не се зема предвид (10 поени)
//
//Дадена е дел од дефиницијата на класата Banka во која се чуваат информаци за името на банката (низа од 30 знаци) и за картичките издадени од банката (низа од 20 покажувачи кон класата Karticka) како и бројот на такви картички.
//
//Велиме дека картичката издадена од банката може да се пробие ако тежината за пробивање е најмногуLIMIT. Вредноста LIMIT е членка на класата Banka, има почетна вредност 7 и истата може да се промени со функцијата setLimit(). За сите банки оваа вредност е иста. (5 поени)
//
//Во класата Banka имплементирај ги функциите:
//
//функција pecatiKarticki() во која се печатат сите картички кои можат да се пробијат, секој во посебен ред. Претходно во првиот ред се печати: Vo bankata XXXXX moze da se probijat kartickite: (5 поени).
//
//функција dodadiDopolnitelenPin(char * smetka, int novPin) во која на картичката со дадена трансакциона сметка се додава нов дополнителен пин код. Ако тоа не е можно функцијата не прави ништо (15 поени).
//
//Комплетна функционалност (5 поени)
//
//For example:
//
//Input	Result
//2
//ab1232432 345 0
//bh4555432 876 1
//4
//ab1232432 2
//ab1112432 100
//ab1232432 56
//ab1211111 88
//Vo bankata Komercijalna moze da se probijat kartickite:
//ab1232432: 3
//bh4555432: 3


#include<iostream>
#include<string.h>
using namespace std;

class OutOfBoundException {
public:
    void print() {
        cout << "Brojot na pin kodovi ne moze da go nadmine dozvolenoto" << endl;
    }
};

class Karticka {
protected:
    char smetka[16];
    int pin;
    bool povekjePin;
public:
    Karticka(char* smetka, int pin) {
        strcpy(this->smetka, smetka);
        this->pin = pin;
        this->povekjePin = false;
    }

    const char* getSmetka() const {
        return smetka;
    }

    bool getDopolnitelenPin() {
        return povekjePin;
    }

    virtual int tezinaProbivanje() {
        int t = pin, count = 0;
        while (t) {
            count++;
            t /= 10;
        }
        return count;
    }

    friend ostream& operator<<(ostream& os, Karticka& k) {
        os  << k.smetka << ": " << k.tezinaProbivanje() << endl;
        return os;
    }

    virtual ~Karticka() {}
};

class SpecijalnaKarticka : public Karticka {
private:
    int* extrapin;
    int n;
    static const int P = 4;

    void copySpecijalnaKarticka(const SpecijalnaKarticka& s) {
        n = s.n;
        extrapin = new int[n];
        for (int i = 0; i < n; ++i) {
            extrapin[i] = s.extrapin[i];
        }
        povekjePin = true;
    }

public:
    SpecijalnaKarticka(char* smetka = (char*)"", int pin = 0, int* extrapin = nullptr, int n = 0)
            : Karticka(smetka, pin) {
        this->n = n;
        this->extrapin = new int[n];
        for (int i = 0; i < n; ++i) {
            this->extrapin[i] = extrapin[i];
        }
        povekjePin = true;
    }

    SpecijalnaKarticka(const SpecijalnaKarticka& s) : Karticka(s) {
        copySpecijalnaKarticka(s);
    }

    SpecijalnaKarticka& operator=(const SpecijalnaKarticka& other) {
        if (this != &other) {
            delete[] extrapin;
            Karticka::operator=(other);
            copySpecijalnaKarticka(other);
        }
        return *this;
    }

    SpecijalnaKarticka& operator+=(int novpin) {
        if (n >= P) {
            throw OutOfBoundException();
        }
        int* temp = new int[n + 1];
        for (int i = 0; i < n; ++i) {
            temp[i] = extrapin[i];
        }
        temp[n] = novpin;
        delete[] extrapin;
        extrapin = temp;
        n++;
        return *this;
    }

    int tezinaProbivanje() override {
        return Karticka::tezinaProbivanje() + n;
    }

    ~SpecijalnaKarticka() override {
        delete[] extrapin;
    }
};

class Banka {
private:
    char naziv[30];
    Karticka* karticki[20];
    int broj;
    static int LIMIT;
public:
    Banka(char* naziv, Karticka** karticki, int broj) {
        strcpy(this->naziv, naziv);
        for (int i = 0; i < broj; i++) {
            if (karticki[i]->getDopolnitelenPin()) {
                this->karticki[i] = new SpecijalnaKarticka(*dynamic_cast<SpecijalnaKarticka*>(karticki[i]));
            }
            else {
                this->karticki[i] = new Karticka(*karticki[i]);
            }
        }
        this->broj = broj;
    }

    ~Banka() {
        for (int i = 0; i < broj; i++) {
            delete karticki[i];
        }
    }

    static void setLIMIT(int limit) {
        LIMIT = limit;
    }

    void pecatiKarticki() {
        cout << "Vo bankata " << naziv << " moze da se probijat kartickite:" << endl;
        for (int i = 0; i < broj; ++i) {
            if (karticki[i]->tezinaProbivanje() <= LIMIT) {
                cout << *karticki[i];
            }
        }
    }

    void dodadiDopolnitelenPin(char* smetka, int novPin) {
        for (int i = 0; i < broj; ++i) {
            if (strcmp(karticki[i]->getSmetka(), smetka) == 0 && karticki[i]->getDopolnitelenPin()) {
                SpecijalnaKarticka* spk = dynamic_cast<SpecijalnaKarticka*>(karticki[i]);
                try {
                    *spk += novPin;
                }
                catch (OutOfBoundException& e) {
                    e.print();
                }
                return;
            }
        }
    }
};

int Banka::LIMIT = 7;

int main() {
    Karticka** niza;
    int n, m, pin;
    char smetka[16];
    bool daliDopolnitelniPin;

    cin >> n;
    niza = new Karticka * [n];
    for (int i = 0; i < n; i++) {
        cin >> smetka >> pin >> daliDopolnitelniPin;
        if (!daliDopolnitelniPin)
            niza[i] = new Karticka(smetka, pin);
        else
            niza[i] = new SpecijalnaKarticka(smetka, pin);
    }

    Banka komercijalna("Komercijalna", niza, n);
    for (int i = 0; i < n; i++) delete niza[i];
    delete[] niza;

    cin >> m;
    for (int i = 0; i < m; i++) {
        cin >> smetka >> pin;
        komercijalna.dodadiDopolnitelenPin(smetka, pin);
    }

    Banka::setLIMIT(5);
    komercijalna.pecatiKarticki();

    return 0;
}
