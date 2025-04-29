#ifndef MOVIMENTS_H
#define MOVIMENTS_H

#include "posicio.h"

const int POSICIONS_MAXIMES = 64;

class Moviments
{
public:
    Moviments() : m_nMoviments(0) {}
    
    void posicio();

    void afegirPosicio(const Posicio& pos);

    void neteja();

    int getNombre() const { return m_nMoviments; }
    Posicio getPosicio(int i) const { return m_posicions[i]; }

    void posicionsValides(const Posicio& p);
	bool esPotMoureMes(const Posicio& p);
	void executarMoviment();
	bool operator==(const Moviments& m);
	bool movimentValid();


    bool operator==(const Moviments& m) const;

private:
    Posicio m_posicions[POSICIONS_MAXIMES];
    int m_nMoviments;
};

#endif