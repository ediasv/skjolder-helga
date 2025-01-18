#include "Ente.h"
#include "Gerenciadores/GerenciadorGrafico.h"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <iostream>

Gerenciadores::Gerenciador_Grafico *Ente::pGG(nullptr);

Ente::Ente(int id) : id(id) { setTarget(); }

Ente::~Ente() { delete pAlvo; }

void Ente::setGerenciadorGrafico(Gerenciadores::Gerenciador_Grafico *ppGG) {
  if (ppGG != nullptr) {
    pGG = ppGG;
  }
}

void Ente::setTarget() {
  if (pGG) {
    pAlvo = pGG->getJanela();
  } else {
    std::cerr << "Erro em setTarget" << std::endl;
  }
}
