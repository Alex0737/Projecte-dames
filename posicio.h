#include <string>
#include <fstream>
using namespace std;

int const DIMENSIO = 2;

class Posicio
{
public:
	Posicio() { m_x = 0; m_y = 0; }
	Posicio(const string& posicio) { fromString(posicio); }

	int getX() const { return m_x; }
	int getY() const { return m_y; }

	void setPosicio(int x, int y) { m_x = x; m_y = y; }
	void setX(int x) { m_x = x; }
	void setY(int y) { m_y = y; }

	void fromString(const string& pos);
	string toString() const;

	bool operator==(const Posicio& posicio) const;


private:
	int m_x;
	int m_y;
};