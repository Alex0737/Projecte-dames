#ifndef NODEMOVIMENT_H
#define NODEMOVIMENT_H

#include "tauler.hpp"

class NodeMoviment
{
public:
    NodeMoviment(const Moviments& m) { m_valor = m; m_next = nullptr; }

    Moviments& getValor() { return m_valor; }

    NodeMoviment* getNext() const { return m_next; }

    void setValor(const Moviments& m) { m_valor = m; }

    void setNext(NodeMoviment* next) { m_next = next; }

private:
    Moviments m_valor;
    NodeMoviment* m_next;
};

#endif