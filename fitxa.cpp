#include "fitxa.h"

void Fitxa::afegirMoviment(const Moviments& m)
{
    m_moviments.push_back(m);
}

void Fitxa::setMoviment(const Moviments& m)
{
    m_moviments.push_back(m);
}

void Fitxa::convertirDama()
{
    m_tipus = TIPUS_DAMA;
}

void Fitxa::netejaMoviments()
{
    m_moviments.clear();
}

void Fitxa::setPosicioBuida()
{
    m_tipus = TIPUS_EMPTY;
}

bool Fitxa::operator==(const Fitxa& f) const
{
    return (m_posicio == f.getPosicio() && m_color == f.getColor() && m_tipus == f.getTipus());
}

void Fitxa::setPosNova(const Posicio& pos, ColorFitxa c, TipusFitxa t)
{
    m_posicio = pos;
    m_color = c;
    m_tipus = t;
}

int Fitxa::getMaxMenjades() const
{
    int max = 0;
    for (const auto& mov : m_moviments)
    {
        if (mov.getMenjades() > max)
            max = mov.getMenjades();
    }
    return max;
}

int Fitxa::getDamesMaximes() const
{
    int max = 0;
    for (const auto& mov : m_moviments)
    {
        if (mov.getDamesMenjades() > max)
            max = mov.getDamesMenjades();
    }
    return max;
}

bool Fitxa::calBufar(const Posicio& p, int i) const
{
    int maxMenjades = getMaxMenjades();
    int menjaAquestMov = getMoviment(i).getMenjades();
    return (maxMenjades > 0 && menjaAquestMov < maxMenjades);
}

bool Fitxa::estaDesti(const Posicio& p)const
{
    bool trobat = false;
    for (const auto& mov : m_moviments)
    {
        int i = 0;
        while (i < mov.getNombre() && !trobat)
        {
            if (p == mov.getPosicioIndex(i))
                trobat = true;
            else
                i++;
        }
    }
    return trobat;
}

int Fitxa::getIndexMoviment(const Posicio& p)const
{
    int res = -1;
    for (size_t j = 0; j < m_moviments.size(); ++j)
    {
        int i = 0;
        bool trobat = false;
        while (i < m_moviments[j].getNombre() && !trobat)
        {
            if (p == m_moviments[j].getPosicioIndex(i))
            {
                trobat = true;
                res = j;
            }
            else
                i++;
        }
    }
    return res;
}

void Fitxa::visualitza(int x, int y) {
    IMAGE_NAME img;
    if (m_color == COLOR_BLANC)
        img = (m_tipus == TIPUS_DAMA) ? GRAFIC_DAMA_BLANCA : GRAFIC_FITXA_BLANCA;
    else
        img = (m_tipus == TIPUS_DAMA) ? GRAFIC_DAMA_NEGRA : GRAFIC_FITXA_NEGRA;
    GraphicManager::getInstance()->drawSprite(img, x, y);
}


int fitxa::getNPosicions()
{
    int posicions = ;
    for(int i = 0; i < m_moviments.size(); i++)
    {
        posicions += m_moviments[i].getNombre();
    }

    return posicions;
}

