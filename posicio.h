#ifndef POSICIO_HPP
#define POSICIO_HPP

#include <string>
#include <iostream>
#include "tauler.h"

class Fitxa;

class Posicio
{
public:
    Posicio() : m_x(0), m_y(0) {}
    Posicio(const std::string& pos);
    Posicio(int x, int y) : m_x(x), m_y(y) {}

    int getX() const { return m_x; }
    int getY() const { return m_y; }

    bool estaDesti(const Fitxa& f) const;
    void setPosicio(int x, int y) { m_x = x; m_y = y; }
    std::string toString() const;
    bool estaDins(const Posicio p[], int nPosicions) const;
    bool operator==(const Posicio& pos) const;

private:
    int m_x;
    int m_y;
};

std::ostream& operator<<(std::ostream& out, const Posicio& pos);

#endif