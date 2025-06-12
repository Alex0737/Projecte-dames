#include <queue>
#include "tauler.hpp"
#include <fstream>
#include <string>

class NodeMoviments
{
private:
	Moviments m_valor;
	NodeMoviments* m_next;

public:
	NodeMoviments(const Moviments& valor) { m_valor = valor; m_next = nullptr; }
	Moviments& getValor() { return m_valor; }
	NodeMoviments* getNext() { return m_next; }
	void setValor(const Moviments& valor) { m_valor = valor; }
	void setNext(NodeMoviments* next) { m_next = next; }
};

class CuaMoviments
{
private:
	NodeMoviments* m_primer;
	NodeMoviments* m_darrer;
public:
	CuaMoviments() {};
	CuaMoviments(Fitxa f, Posicio p1, Posicio p2) {}
	
	~CuaMoviments();

	Moviments treuPrimerMoviment();
	bool buida() const;
	void carregaMoviments(const string& nomFitxer);
	void guardarMoviments(const string& nom);
	void afegirMoviment(const Moviments& m);

};