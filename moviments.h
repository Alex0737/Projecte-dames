
#ifndef MOVIMENTS_H
#define MOVIMENTS_H

const int POSICIONS_MAXIMES = 10;

#include "posicio.h"

class Moviments
{
public:
    Moviments() : m_nPosicionsValides(0), m_menjadesMaximes(0), m_menjadesDames(0), m_menjat(false), m_posicions{}, m_posicionsMenjades{} {}
    Moviments(const Posicio& posInicial, bool menjat, bool dama);

    void setMenjat() { m_menjat = true; };

    bool getMenjat() const { return m_menjat; }
    int getNombre() const;
    Posicio getPosicioIndex(int i) const;

    void incrementarMenjades() { m_menjadesMaximes++; }
    void incrementarMenjadesDames() { m_menjadesDames++; }
    int getMenjades() const { return m_menjadesMaximes; }

    void afegirPosicio(const Posicio& pos);
    void afegirMoviment(Posicio p[], int m_nPosicionsValides, int menjades);
    void neteja();

    bool esUltimaPosicio(const Posicio& p) const;
    Posicio getUltimaPosicio() const;
    Moviments& operator=(const Moviments& m);

    bool estaDesti(const Posicio& p)const;

    bool operator==(const Moviments& m) const;

    void afegirMort(const Posicio& p);
    int getDamesMenjades() const;
    Posicio getFitxaMatada(int j) const;

private:
    Posicio m_posicions[POSICIONS_MAXIMES]; //array de pos valides
    int m_nPosicionsValides;
    Posicio m_posicionsMenjades[POSICIONS_MAXIMES];
    int m_menjadesMaximes; // numero maxim de menjades que es pot fer en un moviment
    int m_menjadesDames;
    bool m_menjat;
};

#endif