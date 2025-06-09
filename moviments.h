#ifndef MOVIMENTS_H
#define MOVIMENTS_H

#include "posicio.h"
#include <vector>

class Moviments
{
public:
    Moviments() : m_menjadesMaximes(0), m_menjadesDames(0), m_menjat(false) {}
    Moviments(const Posicio& posInicial, bool menjat, bool dama);

    void setMenjat() { m_menjat = true; }

    bool getMenjat() const { return m_menjat; }
    int getNombre() const { return m_posicions.size(); }
    Posicio getPosicioIndex(int i) const;

    void incrementarMenjades() { m_menjadesMaximes++; }
    void incrementarMenjadesDames() { m_menjadesDames++; }
    int getMenjades() const { return m_menjadesMaximes; }

    void afegirPosicio(const Posicio& pos);
    void afegirMoviment(const std::vector<Posicio>& p, int menjades);
    void neteja();

    bool esUltimaPosicio(const Posicio& p) const;
    Posicio getUltimaPosicio() const;
    Moviments& operator=(const Moviments& m);

    bool esCaptura() { return m_menjadesMaximes > 0; }

    bool estaDesti(const Posicio& p)const;

    bool operator==(const Moviments& m) const;

    void afegirMort(const Posicio& p);
    int getDamesMenjades() const;
    Posicio getFitxaMatada(int j) const;

private:
    std::vector<Posicio> m_posicions;
    std::vector<Posicio> m_posicionsMenjades;
    int m_menjadesMaximes; // numero maxim de menjades que es pot fer en un moviment
    int m_menjadesDames;
    bool m_menjat;
};

#endif