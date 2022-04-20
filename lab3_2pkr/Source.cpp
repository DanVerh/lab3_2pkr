#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h>

using namespace std;

enum Spec { KN, IT, MATH, PH, TR };
string strSpec[] = { "����'����� �����", "�����������", "���������� �� ��������", "Գ���� �� �����������", "������� ��������" };

struct Student {
    string lname;
    int kurs;
    Spec spec;
    double phgr;
    double mgr;
    union {
        double itgr;
        double numbgr;
        double pedgr;
    };
};

void Create(Student* s, const int amSt);
void Print(Student* p, const int N);
void Sort(Student* p, const int N);
int* Index(Student* p, int N);
int binSearch(Student* p, const int N, const string lname, const Spec spec, const int kurs);
void PrintIndexSort(Student* p, int* I, const int N);

int main() {
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int amSt;
    string lastName;
    Spec spec;
    int specNo, kurs, found;
    cout << "ʳ������ ��������: ";
    cin >> amSt;
    Student* s = new Student[amSt];

    int menuItem;
    do {
        cout << endl << endl << endl;
        cout << "������� ��:" << endl << endl;
        cout << " [1] - �������� ����� � ��������� " << endl;
        cout << " [2] - ���� ����� �� �����" << endl;
        cout << " [3] - ������� ������������� ����� " << endl;
        cout << " [4] - �������� ������������� �� ���� ����� " << endl;
        cout << " [5] - ������� ����� ��� ����������, �� ��������� ������� " << endl;
        cout << " �� �������� ������������ �������� �� ������� ������������ �� ��������� ����." << endl;
        cout << " [0] - ����� �� ���������� �������� " << endl;
        cout << "������ �������: "; cin >> menuItem;
        cout << endl << endl << endl;

        switch (menuItem) {
        case 1:
            Create(s, amSt);
            break;
        case 2:
            Print(s, amSt);
            break;
        case 3:
            Sort(s, amSt);
            break;
        case 4:
            PrintIndexSort(s, Index(s, amSt), amSt);
            break;
        case 5:
            cout << "������ ����� ������:" << endl;
            cout << " �������: "; cin >> lastName;
            cout << endl;
            cout << " ����i����i��� (0 - ����'�����i �����, 1 - I����������, 2 - ���������� �� ������i��, 3 - �i���� �� i����������, 4 - ������� ��������) ";
            cin >> specNo;
            spec = (Spec)specNo;
            cout << " ����: " << endl;
            cin >> kurs;
            cin.get();
            cin.sync(); 



            if ((found = binSearch(s, amSt, lastName, spec, kurs)) != -1)
                cout << "�������� �������� � ������� " << found + 1 << endl;
            else
                cout << "�������� �������� �� ��������" << endl;
            break;
        case 0:
            break;
        }
    } while (menuItem != 0);

    return 0;
}


void Create(Student* s, const int amSt) {
    int sp;
    for (int i = 0; i < amSt; i++) {
        cout << "�������: ";
        cin >> s[i].lname;
        cout << "����: ";
        cin >> s[i].kurs;
        cout << "������������ (0 - ����'����� �����, 1 - �����������, 2 - ���������� �� ��������, 3 - Գ���� �� �����������, 4 - ������� ��������) ";
        cin >> sp;
        s[i].spec = (Spec)sp;
        cout << "������ � ������: ";
        cin >> s[i].phgr;
        cout << "������ � ����������: ";
        cin >> s[i].mgr;
        if (s[i].spec == 0) {
            cout << "������ � �������������: ";
            cin >> s[i].itgr;
        }
        else if (s[i].spec == 1) {
            cout << "������ � ��������� ������: ";
            cin >> s[i].numbgr;
        }
        else {
            cout << "������ � ���������: ";
            cin >> s[i].pedgr;
        }
        cout << endl;
    }
}

void Print(Student* p, const int N) {
    cout << "===========================================================================================" << endl;
    cout << "| No | ������� | ���� |        ������������        | Գ���� | ���������� | ����� ������ |" << endl;
    cout << "-------------------------------------------------------------------------------------------" << endl;
    for (int i = 0; i < N; i++) {
        cout << "| " << setw(3) << right << i + 1 << "";
        cout << "| " << setw(9) << right << p[i].lname
            << "| " << setw(5) << right << p[i].kurs
            << "| " << setw(28) << strSpec[p[i].spec]
            << "| " << setw(7) << right << p[i].phgr
            << "| " << setw(11) << right << p[i].mgr;
        if (p[i].spec == 0) {
            cout << "| " << setw(13) << right << p[i].itgr;
        }
        else if (p[i].spec == 1) {
            cout << "| " << setw(13) << right << p[i].numbgr;
        }
        else {
            cout << "| " << setw(13) << right << p[i].pedgr;
        }
        cout << "|";
        cout << endl;
    }
    cout << "===========================================================================================" << endl;
    cout << endl;
}

void Sort(Student* p, const int N){
    Student tmp;
    for (int i0 = 0; i0 < N - 1; i0++)
        for (int i1 = 0; i1 < N - i0 - 1; i1++)
            if ((p[i1].kurs > p[i1 + 1].kurs)
                ||
                (p[i1].kurs == p[i1 + 1].kurs &&
                    p[i1].spec > p[i1 + 1].spec)
                ||
                (p[i1].spec == p[i1 + 1].spec &&
                    p[i1 + 1].lname > p[i1].lname && p[i1].kurs == p[i1 + 1].kurs))
            {
                tmp = p[i1];
                p[i1] = p[i1 + 1];
                p[i1 + 1] = tmp;
            }
}

int* Index(Student* p, int N) {
    int* I = new int[N];

    for (int i = 0; i < N; i++) {
        I[i] = i;
    }

    int i, j, value;
    for (i = 1; i < N; i++) {
        value = I[i];
        for (j = i - 1; j >= 0 && ((p[I[j]].kurs > p[value].kurs)
            ||
            (p[I[j]].kurs == p[value].kurs &&
                p[I[j]].spec > p[value].spec)
            ||
            (p[I[j]].spec == p[value].spec &&
                p[value].lname > p[I[j]].lname));
            j--)
        {
            I[j + 1] = I[j];
        }
        I[j + 1] = value;
    }
    return I;
}

int binSearch(Student* p, const int N, const string lname, const Spec spec, const int kurs){ 
    int L = 0, R = N - 1, m;
    do {
        m = (L + R) / 2;
        if (p[m].lname == lname && p[m].spec == spec && p[m].kurs == kurs)
            return m;
        if ((p[m].lname > lname)
            ||
            (p[m].lname == lname &&
                p[m].spec < spec)
            ||
            p[m].spec < spec &&
            p[m].kurs == kurs)
        {
            L = m + 1;
        }
        else
        {
            R = m - 1;
        }
    } while (L <= R);
    return -1;
}

void PrintIndexSort(Student* p, int *I, const int N) {
    cout << "===========================================================================================" << endl;
    cout << "| No | ������� | ���� |        ������������        | Գ���� | ���������� | ����� ������ |" << endl;
    cout << "-------------------------------------------------------------------------------------------" << endl;
    for (int i = 0; i < N; i++) {
        cout << "| " << setw(3) << right << i + 1 << "";
        cout << "| " << setw(9) << right << p[I[i]].lname
            << "| " << setw(5) << right << p[I[i]].kurs
            << "| " << setw(28) << strSpec[p[I[i]].spec]
            << "| " << setw(7) << right << p[I[i]].phgr
            << "| " << setw(11) << right << p[I[i]].mgr;
        if (p[i].spec == 0) {
            cout << "| " << setw(13) << right << p[I[i]].itgr;
        }
        else if (p[i].spec == 1) {
            cout << "| " << setw(13) << right << p[I[i]].numbgr;
        }
        else {
            cout << "| " << setw(13) << right << p[I[i]].pedgr;
        }
        cout << "|";
        cout << endl;
    }
    cout << "===========================================================================================" << endl;
    cout << endl;
}

