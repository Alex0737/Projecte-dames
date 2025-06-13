#ifndef FITXA_H
#define FITXA_H

#include "moviments.h"
#include "posicio.h"
#include <vector>
#include "GraphicManager.h"

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
    COLOR_BUIT,
} ColorFitxa;

class Fitxa
{
public:
    Fitxa() : m_posicio(), m_color(COLOR_BLANC), m_tipus(TIPUS_EMPTY) {}
    Fitxa(TipusFitxa tipus, ColorFitxa color, const Posicio& pos) : m_tipus(tipus), m_color(color), m_posicio(pos) {}

    int getX() const { return m_posicio.getX(); }
    int getY() const { return m_posicio.getY(); }
    ColorFitxa getColor() const { return m_color; }
    TipusFitxa getTipus() const { return m_tipus; }
    Posicio getPosicio() const { return m_posicio; }
    int getNumMoviments() const { return m_moviments.size(); }
    Moviments getMoviment(int i) const;
    int getMaxMenjades() const;
    int getNPosicions();


    void setColor(ColorFitxa c) { m_color = c; }
    void setTipus(TipusFitxa t) { m_tipus = t; }
    void setPosicio(const Posicio& p) { m_posicio = p; }
    void setPosicioBuida();
    void setPosNova(const Posicio& pos, ColorFitxa c, TipusFitxa t);
    void setMoviment(const Moviments& m);

    bool estaDesti(const Posicio& p) const;     
    void afegirMoviment(const Moviments& m);

    void convertirDama();
    void netejaMoviments();

    bool operator==(const Fitxa& f) const;

    int getDamesMaximes() const;
    bool calBufar(const Posicio& p, int i) const;
    int getIndexMoviment(const Posicio& p) const;

    void visualitza(int x, int y);

private:
    TipusFitxa m_tipus;
    ColorFitxa m_color;
    Posicio    m_posicio;
    std::vector<Moviments> m_moviments;
};

#endif