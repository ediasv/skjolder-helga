#pragma once
#include <stack>

#include "IDs.h"
#include "State.h"

namespace Gerenciadores {
class GerenciadorEstados {
 private:
  std::stack<States::State *> pilhaEstados;
  static GerenciadorEstados *instancia;

 private:
  GerenciadorEstados();
  ~GerenciadorEstados();
  GerenciadorEstados(const GerenciadorEstados &) = delete;
  GerenciadorEstados &operator=(const GerenciadorEstados &) = delete;

 public:
  static GerenciadorEstados *getInstancia();
  ID getIdTop();
  void executar();
  void pushEstado(States::State *s);
  States::State *topEstado();
  void popEstado();
};
}  // namespace Gerenciadores
