#include "ListeStation.h"

#include <iostream>



// Cette fonction est un peu a modifier par rapport a la partie 1 car il y a un tableau maintenant en plus
void ListeStation::ajoute_cellule_en_tete(const CelluleStation& cel) 
{
	CelluleStation* cel1 = new CelluleStation(cel._ID);
	if (_pListDeb == nullptr)
	{
		_pListDeb = cel1;
		_pListFin = cel1;
	}
	else
	{
		cel1->_pSuiv = _pListDeb;
		_pListDeb->_pPred = cel1;
		_pListDeb = cel1;
	}
}

void ListeStation::affiche_liste() const 
{
	CelluleStation* p = _pListDeb;
	while (p)
	{
		std::cout << p->_ID << "  ";
		p = p->_pSuiv;
	}
	std::cout << std::endl;
}

void ListeStation::affiche_liste_endroit() const 
{
	CelluleStation* p = _pListFin;
	while (p)
	{
		std::cout << p->_ID << "  ";
		p = p->_pPred;
	}
	std::cout << std::endl;
}




size_t ListeStation::nbelem() const 
{
	int nb = 0;
	CelluleStation* p = _pListDeb;
	while (p)
	{
		nb++;
		p = p->_pSuiv;
	}
	return nb;
}


// renvoie le ptr vers cellule avec cle. Si cle absente renvoie null
CelluleStation* ListeStation::recherche_ptr(int cle)const 
{
	CelluleStation* p = _pListDeb;
	while (p)
	{
		if (p->_ID == cle)
		{
			return p;
		}
		p = p->_pSuiv;
	}
	return nullptr; // pas trouvé
}


void ListeStation::supprime_cellule(int cle) 
{
	CelluleStation* pSup = recherche_ptr(cle);
	CelluleStation* pAv;
	CelluleStation* pAp;
	if (pSup)
	{
		pAv = pSup->_pPred;
		pAp = pSup->_pSuiv;
		pAv->_pSuiv = pSup->_pSuiv;
		pAp->_pPred = pSup->_pPred;
		delete pSup;
	}
	else
		std::cerr << "Erreur de saisie \n";
}


void ListeStation::liberer_liste() 
{
	CelluleStation* p = _pListDeb;
	CelluleStation* pSup;
	while (p)
	{
		pSup = p;
		p = p->_pSuiv;
		delete pSup;
	}
}

