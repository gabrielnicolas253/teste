#include <iostream>
#include <vector>
#include <string>

struct Noticia {
    std::string texto;
    std::string classificacao;
};

std::vector<Noticia> dados;


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
    } 
    else if (score == 1) {
        return "duvidosa";
    } 
    else {
        return "falsa";
    }
}

// função que faz tudo
void adicionarNoticiaNoVetor(std::string texto_atual, std::string classificacao_atual = "") {
    // adiciona coisa
    Noticia noticia_atual;
    noticia_atual.texto = texto_atual;

    if (classificacao_atual == "") {
        noticia_atual.classificacao = "duvidosa";
    } else {
        noticia_atual.classificacao = classificacao_atual;
    }

    dados.push_back(noticia_atual);
}

bool verificacaoDeClassificacao(std::string classificacao_atual){
    if (classificacao_atual != "confiavel" && classificacao_atual != "duvidosa" && classificacao_atual != "falsa"){
        std::cout << "Erro: classificação inserida é inválida, tente novamente." << std::endl;
        return false;
    }
    else {
        return true;
    }
}

bool verificacaoDeTexto(std::string texto_atual){
    if (texto_atual == ""){
        std::cout << "Erro: notícia adicionada não possui texto, tente novamente." << std::endl;
        return false;
    }
    else {
        return true;
    }
}

void criarNoticiaManual() {
    std::string texto, classificacao;

    std::cout << "Digite o texto: ";

    if (!getline(std::cin, texto)) {
        std::cout << "Erro: falha na leitura." << std::endl;
        return;
    }

    std::cout << "Digite classificacao: ";

    if (!getline(std::cin, classificacao)) {
        std::cout << "Erro: falha na leitura." << std::endl;
        return;
    }

    if (!verificacaoDeClassificacao(classificacao)){
        return;
    }

    if (verificacaoDeTexto(texto)){
        adicionarNoticiaNoVetor(texto, classificacao);
    } 
    else {
        return;
    }
}

void criarNoticiaAuto() {
    std::string texto;

    std::cout << "Digite o texto: ";

    if (!getline(std::cin, texto)) {
        std::cout << "Erro: falha na leitura." << std::endl;
        return;
    }

    std::string classificacao = analisarNoticia(texto);
    
    if(verificacaoDeTexto(texto)){
        adicionarNoticiaNoVetor(texto, classificacao);
    }
}

void listarNoticias() {
    int tamanho_do_vetor = dados.size();
    // lista tudo
    for (int i = 0; i < tamanho_do_vetor; i++) {
        std::cout << "Texto: " << dados[i].texto << std::endl;
        std::cout << "Classificacao: " << dados[i].classificacao << std::endl;
        std::cout << "-------------------" << std::endl;
    }
}

void abrirMenu() {
    while (true) {
        std::cout << "1 - adicionar manual" << std::endl;
        std::cout << "2 - adicionar automatico" << std::endl;
        std::cout << "3 - listar" << std::endl;
        std::cout << "4 - sair" << std::endl;

        std::string entrada;

        if (!getline(std::cin, entrada)) {
        std::cout << "Erro: falha na leitura." << std::endl;
        break;
        }

        if (entrada == "1") {
            criarNoticiaManual();
        } 
        
        else if (entrada == "2") {
            criarNoticiaAuto();
        } 
        
        else if (entrada == "3") {
            listarNoticias();
        } 
        
        else if (entrada == "4") {
            break;
        } 
        
        else {
            std::cout << "Erro: valor inválido inserido, tente novamente." << std::endl;
        }
    }
}

// inicia programa
int main() {
    abrirMenu();
    return 0;
}
