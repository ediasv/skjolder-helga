#pragma once
#include "Gerenciadores/GerenciadorGrafico.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Window.hpp>

class Ente {
protected:
  int id;
  static Gerenciadores::Gerenciador_Grafico *pGG;
  sf::RenderTarget *pAlvo;

public:
  Ente(int id);
  virtual ~Ente();

  static void setGerenciadorGrafico(Gerenciadores::Gerenciador_Grafico *ppGG);
  void setTarget();
  const int getId() const;
  virtual void desenhar() = 0;
  virtual void executar() = 0;
};
