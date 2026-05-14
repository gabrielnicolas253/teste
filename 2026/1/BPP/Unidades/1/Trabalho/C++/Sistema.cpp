#include <iostream>
#include <vector>
#include <string>

struct D {
    std::string t;
    std::string c;
};

std::vector<D> dados;

// função que faz tudo
void f(std::string a, std::string b = "") {
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
        std::cout << "erro" << std::endl;
    }
}

void func2() {
    // lista tudo
    for (int i = 0; i < dados.size(); i++) {
        std::cout << "Texto: " << dados[i].t << std::endl;
        std::cout << "Classificacao: " << dados[i].c << std::endl;
        std::cout << "-------------------" << std::endl;
    }
}

std::string analisar(std::string txt) {
    int score = 0;
    
    if (txt.find("FONTE") == std::string::npos) {
        score = score + 1;
    }
    if (txt.find("!!!") != std::string::npos) {
        score = score + 1;
    }
    if (txt.find("URGENTE") != std::string::npos) {
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
    std::string t, c;

    std::cout << "Digite o texto: ";
    getline(std::cin, t);

    std::cout << "Digite classificacao: ";
    getline(std::cin, c);

    if (c == "") {
        f(t);
    } else {
        f(t, c);
    }
}

void add_auto() {
    std::string t;

    std::cout << "Digite o texto: ";
    getline(std::cin, t);

    std::string c = analisar(t);
    f(t, c);
}

void menu() {
    while (true) {
        std::cout << "1 - adicionar manual" << std::endl;
        std::cout << "2 - adicionar automatico" << std::endl;
        std::cout << "3 - listar" << std::endl;
        std::cout << "4 - sair" << std::endl;

        std::string op;
        getline(std::cin, op);

        if (op == "1") {
            add_manual();
        } else if (op == "2") {
            add_auto();
        } else if (op == "3") {
            func2();
        } else if (op == "4") {
            break;
        } else {
            std::cout << "errado" << std::endl;
        }
    }
}

// inicia programa
int main() {
    menu();
    return 0;
}
