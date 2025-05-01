#ifndef FITXA_H
#define FITXA_H

#include "moviments.h"
#include "posicio.h"
#include "tauler.h"

int const MAX_MOVS_FITXA = 64;

typedef enum
{
    TIPUS_NORMAL,
    TIPUS_DAMA,
    TIPUS_EMPTY
} TipusFitxa;

typedef enum
{
    COLOR_NEGRE,
    COLOR_BLANC,
} ColorFitxa;

class Fitxa
{
public:
    Fitxa() : m_posicio(), m_color(COLOR_BLANC), m_tipus(TIPUS_EMPTY) {};
    Fitxa(TipusFitxa tipus, ColorFitxa color, const Posicio& pos) : m_tipus(tipus), m_color(color), m_posicio(pos) {};

    int getX() const { return m_posicio.getX(); }
    int getY() const { return m_posicio.getY(); }
    ColorFitxa getColor() const { return m_color; }
    TipusFitxa getTipus() const { return m_tipus; }
    Posicio getPosicio() const { return m_posicio; }
    int getNumMoviments() const { return m_nMoviments; }
    Moviments getMoviment(int i) const { return m_moviments[i]; }
    int getMaxMenjades() const;

    void setColor(ColorFitxa c) { m_color = c; }
    void setTipus(TipusFitxa t) { m_tipus = t; }
    void setPosicio(const Posicio& p) { m_posicio = p; }
    void setPosicioBuida();
    void setPosNova(const Posicio& pos, ColorFitxa c, TipusFitxa t);

    bool estaDesti(const Posicio& p)const;


    string posicionsMoviment();
    Posicio movimentsValids(int n);
    void movimentNormal2(const Tauler& tauler)



    bool operator==(const Fitxa& f);


    void convertirDama();
    void afegirMoviment(const Moviments& moviment);
    void netejaMoviments();
    void calcularMovimentsValids(const Tauler& tauler);
    void movimentNormal(const Tauler& tauler);
    bool operator==(const Fitxa& f) const;

    void calcularMovimentsValids7(const Tauler& tauler);

    int getDamesMaximes() const;

    bool calBufar(const Posicio& p, int i) const;

    int getIndexMoviment(const Posicio& p) const;

private:
    Posicio    m_posicio;
    ColorFitxa m_color;
    TipusFitxa m_tipus;
    Moviments  m_moviments[MAX_MOVS_FITXA];
    int        m_nMoviments;
};

#endif
