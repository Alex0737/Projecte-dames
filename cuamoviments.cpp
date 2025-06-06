#include "cuamoviments.h"
#include <string>


Moviments CuaMoviments::treuPrimerMoviment()
{
	Moviments m = m_cua.front();
	m_cua.pop();
	return m;
}

bool CuaMoviments::buida()
{
	return(m_cua.empty());
}

void CuaMoviments::guardarMoviments(const string& nomFitxer)
{
	ofstream fitxer(nomFitxer);
	if (fitxer.is_open())
	{
		std::queue<Moviments> copia = m_cua;
		while (!copia.empty())
		{
			Moviments m = copia.front();
			if (m.getNombre() >= 2)
			{
				fitxer << m.getPosicioIndex(0).toString() << " " << m.getUltimaPosicio() << endl;
			}
			copia.pop();
	
		}
		fitxer.close();
	}
}
void CuaMoviments::carregaMoviments(const string& nomFitxer)
{
	ifstream fitxer(nomFitxer);

	if (fitxer.is_open())
	{
		m_cua = queue<Moviments>();
		string origen, desti;

		while (fitxer >> origen >> desti)
		{
			Moviments m;
			m.afegirPosicio(Posicio(origen));
			m.afegirPosicio(Posicio(desti));
			m_cua.push(m);
		
		}
		fitxer.close();
	}
}
