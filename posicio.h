#include <string>
#include <fstream>
#include <iostream>
using namespace std;

int const DIMENSIO = 2;

class Posicio
{
public:
	Posicio() { m_x = 0; m_y = 0; }
	Posicio(const string& pos) { m_x = (N_FILES - 1) - (pos[1] - '1'); m_y = pos[0] - 'a'; }
	Posicio(int x, int y) { m_x = x, m_y = y; }

	int getX() const { return m_x; }
	int getY() const { return m_y; }

	void setPosicio(int x, int y) { m_x = x; m_y = y; }
	void setX(int x) { m_x = x; }
	void setY(int y) { m_y = y; }

	string toString() const;

	TipusFitxa getTipus();

	bool operator==(const Posicio& posicio) const;


private:
	int m_x;
	int m_y;
};
ostream& operator<<(ostream& out, const Posicio& pos);
