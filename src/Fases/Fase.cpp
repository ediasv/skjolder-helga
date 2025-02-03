#include "Fases/Fase.h"

#include <SFML/System/Vector2.hpp>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

#include "Entidades/Entidade.h"
#include "Entidades/Obstaculos/Obstaculo.h"
#include "Entidades/Personagens/Inimigo.h"
#include "Entidades/Personagens/Jogador.h"
#include "Entidades/Personagens/Personagem.h"
#include "Entidades/Projetil.h"
#include "Gerenciadores/GerenciadorColisoes.h"
#include "IDs.h"
#include "Listas/ListaEntidades.h"

using namespace Entidades;

namespace Fases {

Fase::Fase()
    : Ente(ID::IDfase),
      States::State(),
      listaObstaculos(),
      listaJogadores(),
      listaInimigos(),
      listaProjeteis(),
      pFE(nullptr),
      pGC(Gerenciadores::GerenciadorColisoes::getInstancia()) {
  listaObstaculos.limpar();
  listaJogadores.limpar();
  listaInimigos.limpar();
  listaProjeteis.limpar();
}

Fase::~Fase() {
  pGC = nullptr;
  listaObstaculos.limpar();
  listaJogadores.limpar();
  listaInimigos.limpar();
  listaProjeteis.limpar();
}

void Fase::executar() {
  listaObstaculos.executar();
  listaJogadores.executar();
  listaInimigos.executar();
  listaProjeteis.executar();
}

void Fase::incluirNoGC(Entidade *novaEntidade) {
  if (!novaEntidade) {
    std::cerr << "erro: Fase::incluirNoGC() => novaEntidade == nullptr\n";
    exit(EXIT_FAILURE);
  }

  ID id = novaEntidade->getId();

  if (ehObstaculo(id)) {
    pGC->incluirObst(dynamic_cast<Obstaculos::Obstaculo *>(novaEntidade));

  } else if (ehPersonagem(id)) {
    pGC->incluirPers(dynamic_cast<Personagens::Personagem *>(novaEntidade));

  } else if (ehProjetil(id)) {
    pGC->incluirProj(dynamic_cast<Entidades::Projetil *>(novaEntidade));
  }
}

void Fase::incluirNaLista(Entidade *novaEntidade) {
  if (!novaEntidade) {
    std::cerr << "erro: Fase::incluirNaLista() => novaEntidade == nullptr\n";
    exit(EXIT_FAILURE);
  }

  ID id = novaEntidade->getId();

  if (ehJogador(id)) {
    listaJogadores.incluir(novaEntidade);
    Personagens::Inimigos::Inimigo::adicionarJogador(
        dynamic_cast<Personagens::Jogador *>(novaEntidade));

  } else if (ehInimigo(id)) {
    listaInimigos.incluir(novaEntidade);

  } else if (ehObstaculo(id)) {
    listaObstaculos.incluir(novaEntidade);

  } else if (ehProjetil(id)) {
    listaProjeteis.incluir(novaEntidade);
  }
}

void Fase::adicionarProjetil(Entidades::Projetil *novoProjetil) {
  incluirNaLista(novoProjetil);
  incluirNoGC(novoProjetil);
}

void Fase::criarMapa(const std::string path) {
  if (!pFE) {
    std::cerr << "erro: Fase::criarMapa() => pFE == nullptr\n";
    exit(EXIT_FAILURE);
  }

  std::clog << "Criando mapa da fase\n";

  std::ifstream arquivoMapa;
  std::string filePath = ROOT;
  filePath += path;

  std::clog << "Abrindo arquivo: " << filePath << "\n";
  arquivoMapa.open(filePath);

  if (!arquivoMapa.is_open()) {
    std::cerr << "erro: arquivoMapa.open()\n";
    exit(EXIT_FAILURE);
  }
  std::clog << "Arquivo aberto com sucesso\n";

  std::string linha;
  Entidade *novaEntidade;
  for (int j = 0; std::getline(arquivoMapa, linha); j++) {
    for (int i = 0; i < linha.size(); i++) {
      if (linha[i] != ' ') {
        novaEntidade =
            pFE->criarEntidade(linha[i], sf::Vector2f(i * 16, j * 16));
        incluirNaLista(novaEntidade);
        incluirNoGC(novaEntidade);
      }
    }
  }

  arquivoMapa.close();
}

}  // namespace Fases
