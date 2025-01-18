#include "Ente.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>

namespace Entidades {

const float gravidade = 5;

class Entidade : public Ente {
private:
  sf::Vector2f pos;
  sf::RectangleShape corpo;
  const sf::Vector2f gravidade;
  sf::Vector2f tamanho;
  bool noChao;
  std::ostream *buffer;

protected:
  sf::Vector2f velocidade;

public:
  Entidade(int id, const sf::Vector2f pos, const sf::Vector2f tam);
  virtual ~Entidade();

  const sf::FloatRect getCorpo() const;

  void setVel(sf::Vector2f novaVel);
  void setVelX(float velX);
  void setVelY(float velY);
  void setPos(sf::Vector2f novaPos);
  void setNoChao(bool noChao);

  virtual void desenhar();

  const sf::Vector2f getVel() const;
  const sf::Vector2f getPos() const;
  const bool getNoChao() const;
  const sf::Vector2f getSize() const;

  void cair();
};

} // namespace Entidades
