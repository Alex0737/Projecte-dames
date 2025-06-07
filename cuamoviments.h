#include <queue>
#include "tauler.hpp"
#include <fstream>
#include <string>

class CuaMoviments
{
private:
	queue<Moviments> m_cua;
public:
	CuaMoviments() {};
	CuaMoviments(Fitxa f, Posicio p1, Posicio p2) {}
	Moviments treuPrimerMoviment();
	bool buida();
	void carregaMoviments(const string& nomFitxer);
	void guardarMoviments(const string& nom);
	void afegirMoviment(const Moviments& m);
	Moviments treuPrimer() { return m_cua.front(); }

};