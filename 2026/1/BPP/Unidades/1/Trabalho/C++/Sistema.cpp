#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct D {
    string t;
    string c;
};

vector<D> dados;

// função que faz tudo
void f(string a, string b = "") {
    // adiciona coisa
    if (a != "") {
        D d;
        d.t = a;

        if (b == "") {
            d.c = "duvidosa";
        } else {
            d.c = b;
        }

        dados.push_back(d);
    } else {
        cout << "erro" << endl;
    }
}

void func2() {
    // lista tudo
    for (int i = 0; i < dados.size(); i++) {
        cout << "Texto: " << dados[i].t << endl;
        cout << "Classificacao: " << dados[i].c << endl;
        cout << "-------------------" << endl;
    }
}

string analisar(string txt) {
    int score = 0;
    
    if (txt.find("FONTE") == string::npos) {
        score = score + 1;
    }
    if (txt.find("!!!") != string::npos) {
        score = score + 1;
    }
    if (txt.find("URGENTE") != string::npos) {
        score = score + 1;
    }
    if (txt.length() < 10) {
        score = score + 1;
    }

    if (score == 0) {
        return "confiavel";
    } else if (score == 1) {
        return "duvidosa";
    } else {
        return "falsa";
    }
}

void add_manual() {
    string t, c;

    cout << "Digite o texto: ";
    getline(cin, t);

    cout << "Digite classificacao: ";
    getline(cin, c);

    if (c == "") {
        f(t);
    } else {
        f(t, c);
    }
}

void add_auto() {
    string t;

    cout << "Digite o texto: ";
    getline(cin, t);

    string c = analisar(t);
    f(t, c);
}

void menu() {
    while (true) {
        cout << "1 - adicionar manual" << endl;
        cout << "2 - adicionar automatico" << endl;
        cout << "3 - listar" << endl;
        cout << "4 - sair" << endl;

        string op;
        getline(cin, op);

        if (op == "1") {
            add_manual();
        } else if (op == "2") {
            add_auto();
        } else if (op == "3") {
            func2();
        } else if (op == "4") {
            break;
        } else {
            cout << "errado" << endl;
        }
    }
}

// inicia programa
int main() {
    menu();
    return 0;
}
