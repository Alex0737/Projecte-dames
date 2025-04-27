#include "posicio.h"

using namespace std;

const int POSICIONS_MAXIMES = 64;



class Moviments
{
public:
	Moviments();

	void posicio();
	void getPosicions(Posicio& p[30]);

	void posicionsValides(const Posicio& p);
	bool esPotMoureMes(const Posicio& p);
	void executarMoviment();
	bool operator==(const Moviments& m);
	bool movimentValid();

private:
	Posicio m_movimentsValides[POSICIONS_MAXIMES];
	Posicio m_movimentAtual[POSICIONS_MAXIMES];
};
