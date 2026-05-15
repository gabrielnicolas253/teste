#include <iostream>
#include <vector>
#include <string>

/**
 * @struct Noticia
 * @brief representa uma notícia armazenada pelo sistema
 * 
 * Cada notícia possui um texto e uma classificação.
 */

struct Noticia {
    std::string texto;
    std::string classificacao;
};

/**
 * @brief Vetor global que armazena todas as notícias guardadas enquanto o programa está ativo.
 */
std::vector<Noticia> dados;

/**
 * @brief Verifica se a classificação da noticia é válida, validando-a.
 * 
 * Retorna erro caso identifique que a classificação é inválida por não ser nenhuma das 3 permitidas.
 * Caso for erro, este é escrito no terminal.
 * 
 * @param classificacao_atual Classificacao atual sendo verificada.
 * @return bool - se for false, representa que a verificação retornou erro.
 */
bool verificacaoDeClassificacao(std::string classificacao_atual){
    if (classificacao_atual != "confiavel" && classificacao_atual != "duvidosa" && classificacao_atual != "falsa"){
        std::cout << "Erro: classificação inserida é inválida, tente novamente." << std::endl;
        return false;
    }
    else {
        return true;
    }
}

/**
 * @brief Verifica se o texto da noticia é válido, validando-a.
 * 
 * Retorna erro caso identifique que o texto é inválido por ser vazio.
 * Caso for erro, este é escrito no terminal.
 * 
 * @param texto_atual Texto atual sendo verificada.
 * @return bool - se for false, representa que a verificação retornou erro.
 */
bool verificacaoDeTexto(std::string texto_atual){
    if (texto_atual == ""){
        std::cout << "Erro: notícia adicionada não possui texto, tente novamente." << std::endl;
        return false;
    }
    else {
        return true;
    }
}

/**
 * @brief Analisa noticias e julga qual classificação é apropriada para esta com base em critérios específicos.
 * 
 * Cada critério é utilizado para calcular um score final com base no texto das notícias:
 * - A ausência da palavra "FONTE".
 * - A presença do símbolo "!!!" ou da palavra "URGENTE".
 * - Tamanho menor que 10 caracteres.
 * 
 * Quanto maior o score, menos confiável é a notícia.
 * 
 * @param txt Texto de notícia a ser analisada.
 * @return std::string - classificação, podendo ser "falsa", "duvidosa" ou "confiavel".
 */
std::string analisarNoticia(std::string txt) {
    int score = 0;
    // Uma notícia sem fonte é julgada como sem base.
    if (txt.find("FONTE") == std::string::npos) {
        score = score + 1;
    } // "!!!" é considerado parte de um texto sensacionalista.
    if (txt.find("!!!") != std::string::npos) {
        score = score + 1;
    } // "URGENTE" é considerado parte de um texto sensacionalista.
    if (txt.find("URGENTE") != std::string::npos) {
        score = score + 1;
    } // Um texto pequeno demais é considerado irrelevante ou sem base.
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

/**
 * @brief Adiciona noticias no vetor global.
 * 
 * @param texto_atual Texto da noticia atualmente sendo adicionada.
 * @param classificacao_atual Classificacao da noticia atualmente sendo adicionada.
 */
void adicionarNoticiaNoVetor(std::string texto_atual, std::string classificacao_atual = "") {
    Noticia noticia_atual;
    noticia_atual.texto = texto_atual;

    //Por conveniência e para não complicar o código, decidi incluir e não modificar essa verificação perdida, 
    //já que essa é a melhor oportunidade de modificar a classificação da notícia diretamente.
    if (classificacao_atual == "") {
        noticia_atual.classificacao = "duvidosa";
    } else {
        noticia_atual.classificacao = classificacao_atual;
    }

    dados.push_back(noticia_atual);
}

/**
 * @brief Cria notícias manualmente, ou seja, permite que o usuário tenha liberdade de determinar o texto e a classificação da notícia.
 * 
 * Precisa chamar funções para validar tanto o texto quanto a classificação, determinadas pelo usuário.
 */
void criarNoticiaManual() {
    std::string texto, classificacao;

    std::cout << "Digite o texto: ";

    //Para caso de erro, decidi especificar aonde o erro ocorreu. É provável que, ao retornar,
    //o mesmo erro ocorra quando o programa tentar ler a entrada do usuário, já que o erro em std::cin persiste.
    if (!getline(std::cin, texto)) {
        std::cout << "Erro: falha na leitura (texto)." << std::endl;
        return;
    }

    std::cout << "Digite classificacao: ";

    if (!getline(std::cin, classificacao)) {
        std::cout << "Erro: falha na leitura (classificação)." << std::endl;
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

/**
 * @brief Cria notícias de maneira automática, permitindo que o usuário determine o texto, porém deixando o sistema julgar qual a classificação apropriada.
 * 
 * Chama função para analisar a notícia e classificar ela apropriadamente
 * Precisa chamar função para validar o texto determinado pelo o usuário.
 */
void criarNoticiaAuto() {
    std::string texto;

    std::cout << "Digite o texto: ";

    if (!getline(std::cin, texto)) {
        std::cout << "Erro: falha na leitura (texto)." << std::endl;
        return;
    }

    std::string classificacao = analisarNoticia(texto);
    
    if(verificacaoDeTexto(texto)){
        adicionarNoticiaNoVetor(texto, classificacao);
    }
}

/**
 * @brief Lista todas as notícias armazenadas no sistema, com seus textos e classificações.
 */
void listarNoticias() {
    int tamanho_do_vetor = dados.size();

    for (int i = 0; i < tamanho_do_vetor; i++) {
        std::cout << "Texto: " << dados[i].texto << std::endl;
        std::cout << "Classificacao: " << dados[i].classificacao << std::endl;
        std::cout << "-------------------" << std::endl;
    }
}

/**
 * @brief Abre o menu do sistema, onde será disponibilizado um conjunto de opções para o usuário escolher, controlando assim o sistema.
 * 
 * Ele mostra ao usuário quais são suas opções, e entra num loop até que a opção de saída seja escolhida.
 * As opções são:
 * 1 - Adicionar uma notícia manualmente.
 * 2 - Adicionar uma notícia de maneira automática.
 * 3 - Listar todas as notícias do sistema.
 * 4 - Sair do loop e encerrar o programa.
 */
void abrirMenu() {
    while (true) {
        std::cout << "1 - adicionar manual" << std::endl;
        std::cout << "2 - adicionar automatico" << std::endl;
        std::cout << "3 - listar" << std::endl;
        std::cout << "4 - sair" << std::endl;

        std::string entrada;

        if (!getline(std::cin, entrada)) {
        std::cout << "Erro: falha na leitura (entrada)." << std::endl;
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

/**
 * @brief Função principal do programa. Ela apenas inicializa o sistema abrindo o menu.
 * 
 * @return int - retornando 0 caso o programa finalize corretamente.
 */
int main() {
    abrirMenu();
    return 0;
}
