#include "Entidades/Personagens/Jogador.h"

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>

#include "Entidades/Personagens/Personagem.h"

using namespace Entidades::Personagens;

bool Jogador::ehPrimeiroJogador = true;

Jogador::Jogador(const sf::Vector2f &pos)
    : Personagem(ID::IDjogador), pContr(nullptr), podePular(true) {
  pContr = new Controladores::Controlador_Jogador();
  pContr->setJog(this);

  if (ehPrimeiroJogador) {
    setTextura("/assets/Personagens/Ymir.png");
    this->ehPrimeiroJogador = false;
  } else
    setTextura("/assets/Personagens/Helga.png");

  setPos(pos);
  pSprite->setPosition(pos);

  // TODO: Mudar a hitbox para a classe entidade
  sf::FloatRect hitbox({16, 16, 16.f, 16.f});
  setHitbox(hitbox);
}

Jogador::~Jogador() {}

void Jogador::setPrimeiroJog(bool ehPrimeiroJogador) {
  this->ehPrimeiroJogador = ehPrimeiroJogador;
}

bool Jogador::getPrimeiroJog() const { return ehPrimeiroJogador; }

void Jogador::andarDireita() {
  if (getVel().x < MAXVEL) {
    sf::Vector2f vel = getVel();
    vel.x += ACEL;
    setVel(vel);
  } else {
    setVelX(MAXVEL);
  }
}

void Jogador::andarEsquerda() {
  if (getVel().x > -MAXVEL) {
    sf::Vector2f vel = getVel();
    vel.x -= ACEL;
    setVel(vel);
  } else {
    setVelX(-MAXVEL);
  }
}

void Jogador::naoAndar() { setVelX(0); }

void Jogador::pular() {
  if (podePular) {
    setVelY(-2 * MAXVEL);
    setNoChao(false);
  }
}

void Jogador::aplicaLentidao(float viscosidade) {
  sf::Vector2f vel = getVel();
  vel *= viscosidade;
  setVel(vel);
}

void Jogador::executar() {
  pContr->controlarJogador();

  if (!getNoChao()) cair();

  mover();
}

void Jogador::atacar() { std::cout << "ataquei" << '\n'; }

Controladores::Controlador_Jogador *Jogador::getControlador() const {
  return pContr;
}
