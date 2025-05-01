#ifndef POSICIO_HPP
#define POSICIO_HPP

#include <string>
#include <fstream>
#include <iostream>
#include "fitxa.h"
#include "tauler.hpp"
using namespace std;

const int DIMENSIO = 2;

class Fitxa;

class Posicio
{
public:
	Posicio() { m_x = 0; m_y = 0; }
	Posicio(const string& pos) { m_x = (N_FILES - 1) - (pos[1] - '1'); m_y = pos[0] - 'a'; }
	Posicio(int x, int y) { m_x = x, m_y = y; }

	int getX() const { return m_x; }
	int getY() const { return m_y; }

	bool estaDesti(const Fitxa& f) const;

	void setPosicio(int x, int y) { m_x = x; m_y = y; }
	void setX(int x) { m_x = x; }
	void setY(int y) { m_y = y; }

	string toString() const;

	bool estaDins(const Posicio p[], int nPosicions) const;

	bool operator==(const Posicio& pos) const;


private:
	int m_x;
	int m_y;
};
ostream& operator<<(ostream& out, const Posicio& pos);

#endif