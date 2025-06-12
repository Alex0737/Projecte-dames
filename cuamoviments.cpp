#include "cuamoviments.h"
#include <string>

CuaMoviments::~CuaMoviments()
{
	while (m_primer != nullptr)
	{
		NodeMoviments* aux = m_primer;
		m_primer = m_primer->getNext();
		delete aux;
	}
	m_darrer = nullptr;
}

Moviments CuaMoviments::treuPrimerMoviment()
{
	Moviments mov;
	if (m_primer != nullptr)
	{
		NodeMoviments* aux = m_primer;
		mov = aux->getValor();
		m_primer = m_primer->getNext();
		if (m_primer == nullptr)
			m_darrer = nullptr;
		delete aux;
	}
	return mov;
}

bool CuaMoviments::buida() const
{
	return(m_primer == nullptr);
}

void CuaMoviments::guardarMoviments(const string& nomFitxer)
{
	ofstream fitxer(nomFitxer);
	if (fitxer.is_open())
	{
		NodeMoviments* aux = m_primer;
		while (aux != nullptr)
		{
			Moviments m = aux->getValor();
			if (m.getNombre() >= 2)
			{
				fitxer << m.getPosicioIndex(0).toString() << " " << m.getUltimaPosicio().toString() << endl;
			}
			aux = aux->getNext();

		}
		fitxer.close();
	}
}

void CuaMoviments::carregaMoviments(const string& nomFitxer)
{
	ifstream fitxer(nomFitxer);

	if (fitxer.is_open())
	{
		while (!buida())
		{
			treuPrimerMoviment();
		}
		string origen, desti;

		while (fitxer >> origen >> desti)
		{
			Moviments m;
			m.afegirPosicio(Posicio(origen));
			m.afegirPosicio(Posicio(desti));
			afegirMoviment(m);

		}
		fitxer.close();
	}
}

void CuaMoviments::afegirMoviment(const Moviments& m)
{
	NodeMoviments* nou = new NodeMoviments(m);
	if (m_darrer != nullptr)
	{
		m_darrer->setNext(nou);
	}
	else
		m_primer = nou;

	m_darrer = nou;
}