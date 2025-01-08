#pragma once
namespace Listas {

template <typename TL> class Lista {
private:
  template <typename TE> class Elemento {

  private:
    Elemento<TE> *pProx;
    TE *pInfo;

  public:
    Elemento() : pProx(nullptr), pInfo(nullptr) {}
    ~Elemento() {
      pProx = nullptr;
      pInfo = nullptr;
    }
    bool incluir(TE *pElem) { pInfo = pElem; }
    void setProx(Elemento<TE> *pElem) { pProx = pElem; }
    Elemento<TE> *getProximo() const { return pProx; }
    TE *getInfo() const { return pInfo; }
  };
  Elemento<TL> *pPrimeiro;
  Elemento<TL> *pUltimo;
  int tamanho;

public:
  Lista();
  ~Lista();

  Elemento<TL> *getpPrimeiro() const {
    if (pPrimeiro)
      return pPrimeiro;
  }
  Elemento<TL> *getpUltimo() const {
    if (pUltimo)
      return pUltimo;
  }

  bool incluir(TL *p) {
    Elemento<TL> *node = new Elemento<TL>();
    if (node != nullptr) {
      node->incluir(p);
      if (pUltimo != nullptr) {
        pUltimo->setProx(node);
        pUltimo = node;
      } else {
        pPrimeiro = node;
        pUltimo = node;
      }
      tamanho++;
      return true;
    } else {
      return false;
    }
  }
  void remover(TL *p) {
    Elemento<TL> *node = pPrimeiro;
    Elemento<TL> *anterior = nullptr;
    while (node != nullptr) {
      anterior = node;
      node = node->getProximo();
      if (node->getInfo() == p) {
        if (node == pPrimeiro) {
          pPrimeiro = node->getProximo();
        } else if (node == pUltimo) {
          pUltimo = anterior;
        } else {
          anterior->setProx(node->getProximo());
        }
        delete node;
        tamanho--;
        break;
      }
    }
    node = nullptr;
    anterior = nullptr;
  }
  // TL pop(TL* p);
  void limpar() {
    Elemento<TL> *node = pPrimeiro;
    while (node != nullptr) {
      Elemento<TL> *anterior = node;
      node = node->getProximo();
      delete anterior;
    }
    pUltimo = nullptr;
    tamanho = 0;
  }
  int getSize() const { return tamanho; }

public:
  class Iterator {
  private:
    Elemento<TL> *pAtual;

  public:
    Iterator() : pAtual(nullptr) {}
    Iterator(Elemento<TL> *pElem) : pAtual(pElem) {}
    ~Iterator() { pAtual = nullptr; }

    const Iterator &operator++() const {
      pAtual = pAtual->getProximo();
      return *this;
    }
    const Iterator &operator=(const Iterator &outro) const {
      if (&outro != this) {
        pAtual = outro.pAtual;
      }
      return *this;
    }
    const bool &operator!=(const Iterator &outro) const {
      return this->pAtual != outro.pAtual;
    }
  };
  const Iterator begin() { return Iterator(pPrimeiro); }
  const Iterator end() { return Iterator(pUltimo); }
};
} // namespace Listas
