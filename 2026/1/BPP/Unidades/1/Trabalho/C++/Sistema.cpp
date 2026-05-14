#include <iostream>
#include <vector>
#include <string>

struct Noticia {
    std::string texto;
    std::string classificacao;
};

std::vector<Noticia> dados;

// função que faz tudo
void adicionarNoticiaNoVetor(std::string texto_atual, std::string classificacao_atual = "") {
    // adiciona coisa
    if (texto_atual != "") {
        Noticia noticia_atual;
        noticia_atual.texto = texto_atual;

        if (classificacao_atual == "") {
            noticia_atual.classificacao = "duvidosa";
        } else {
            noticia_atual.classificacao = classificacao_atual;
        }

        dados.push_back(noticia_atual);
    } else {
        std::cout << "erro" << std::endl;
    }
}

void listarNoticias() {
    // lista tudo
    for (int i = 0; i < dados.size(); i++) {
        std::cout << "Texto: " << dados[i].t << std::endl;
        std::cout << "Classificacao: " << dados[i].c << std::endl;
        std::cout << "-------------------" << std::endl;
    }
}

std::string analisarNoticia(std::string txt) {
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

void criarNoticiaManual() {
    std::string texto, classificacao;

    std::cout << "Digite o texto: ";
    getline(std::cin, texto);

    std::cout << "Digite classificacao: ";
    getline(std::cin, classificacao);

    if (classificacao == "") {
        adicionarNoticiaNoVetor(texto);
    } else {
        adicionarNoticiaNoVetor(texto, classificacao);
    }
}

void criarNoticiaAuto() {
    std::string texto;

    std::cout << "Digite o texto: ";
    getline(std::cin, texto);

    std::string classificacao = analisarNoticia(texto);
    adicionarNoticiaNoVetor(texto, classificacao);
}

void abrirMenu() {
    while (true) {
        std::cout << "1 - adicionar manual" << std::endl;
        std::cout << "2 - adicionar automatico" << std::endl;
        std::cout << "3 - listar" << std::endl;
        std::cout << "4 - sair" << std::endl;

        std::string entrada;
        getline(std::cin,entrada);

        if (entrada == "1") {
            criarNoticiaManual();
        } else if (entrada == "2") {
            criarNoticiaAuto();
        } else if (entrada == "3") {
            listarNoticias();
        } else if (entrada == "4") {
            break;
        } else {
            std::cout << "errado" << std::endl;
        }
    }
}

// inicia programa
int main() {
    abrirMenu();
    return 0;
}
