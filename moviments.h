#ifndef MOVIMENTS_H
#define MOVIMENTS_H

#include "posicio.h"

const int POSICIONS_MAXIMES = 64;

class Moviments
{
public:
    Moviments() : m_nPosicionsValides(0), m_menjadesMaximes(0), m_menjadesDames(0), m_menjat(false)
    {
        for (int i = 0; i < POSICIONS_MAXIMES; ++i) {
            m_posicions[i] = Posicio();
            m_posicionsMenjades[i] = Posicio();
        }
    }

    void setMenjat() { m_menjat = true; };
    bool getMenjat() const { return m_menjat; }
    void afegirPosicio(const Posicio& pos);
    void afegirMoviment(Posicio p[], int nPosicions, int menjades);
    void neteja();
    int getNombre() const;
    Posicio getPosicioIndex(int i) const;
    void incrementarMenjades() { m_menjadesMaximes++; }
    void incremetarMenjadesDames() { m_menjadesDames++; }
    int getMenjades() const { return m_menjadesMaximes; }
    bool esUltimaPosicio(const Posicio& p) const;
    Posicio getUltimaPosicio() const;
    bool estaDesti(const Posicio& p) const;
    bool estaFinal(const Posicio& p) const;
    bool operator==(const Moviments& m) const;
    int getDamesMenjades() const;
    Posicio getFitxaMatada(int j) const;

private:
    Posicio m_posicions[POSICIONS_MAXIMES];
    int m_nPosicionsValides;
    Posicio m_posicionsMenjades[POSICIONS_MAXIMES];
    int m_menjadesMaximes;
    int m_menjadesPerPosicio[POSICIONS_MAXIMES];
    int m_menjadesDames;
    bool m_menjat;
};

#endif