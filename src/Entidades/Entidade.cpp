#include "Entidades/Entidade.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>

using namespace Entidades;

Entidade::Entidade(int id, const sf::Vector2f pos, const sf::Vector2f tam)
    : Ente(id), pos(pos), velocidade(0, 0), gravidade(0, 0.1), tamanho(tam),
      corpo(sf::RectangleShape(tam)), noChao(false), buffer(nullptr) {
  corpo.setPosition(pos);
}

Entidade::~Entidade() { buffer = nullptr; }

void Entidade::setPos(sf::Vector2f novaPos) {
  corpo.setPosition(novaPos);
  pos = novaPos;
}

void Entidade::setVel(sf::Vector2f novaVel) { velocidade = novaVel; }

void Entidade::setVelX(float velX) { velocidade.x = velX; }

void Entidade::setVelY(float velY) { velocidade.y = velY; }

void Entidade::setNoChao(bool noChao) { this->noChao = noChao; }

void Entidade::desenhar() {}

const sf::Vector2f Entidade::getPos() const { return pos; }

const sf::Vector2f Entidade::getVel() const { return velocidade; }

const bool Entidade::getNoChao() const { return noChao; }

const sf::Vector2<float> Entidade::getSize() const { return tamanho; }

void Entidade::cair() { setVel(getVel() + gravidade); }
