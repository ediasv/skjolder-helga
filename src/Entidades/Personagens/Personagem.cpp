#include "Entidades/Personagens/Personagem.h"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

using namespace Entidades::Personagens;

Personagem::Personagem(ID id) : Entidade(id), hp(100), olhandoEsquerda(false) {}

Personagem::~Personagem() {}

void Personagem::mover() {
  sf::Vector2f novaPos = getPos() + (velocidade * pGG->getDeltaTempo());
  setPos(novaPos);
  pSprite->setPosition(novaPos);
}

void Personagem::setOlhandoEsquerda(bool olhandoEsquerda) {
  this->olhandoEsquerda = olhandoEsquerda;
}

void Personagem::atualizaOrientacao() {
  if (olhandoEsquerda) {
    pSprite->setScale(-3.f, 3.f);
    pSprite->setOrigin(pSprite->getLocalBounds().width, 0);
  } else {
    pSprite->setScale(3.f, 3.f);
    pSprite->setOrigin(0, 0);
  }
}
void Personagem::tomarDano(int dano) { hp -= dano; }
