#include "Arbre.h"
#include <iostream>

void Arbre::ajoute_cellule(const CelluleArbre& cel) {

	CelluleArbre* ptcel1 = new CelluleArbre(cel._deltaT, cel._annee, cel._tempMois, cel._tSigmaMois);
	CelluleArbre* p = _pArbre;

	bool nontrouve = true;
	if (p == nullptr) { nontrouve = false; _pArbre = ptcel1; } //insere en tete
	while (nontrouve) {
		if (ptcel1->_deltaT < p->_deltaT) {
			if (p->_pFilsG == nullptr) {
				nontrouve = false; p->_pFilsG = ptcel1;
			}
			else p = p->_pFilsG;
		}
		else {
			if (p->_pFilsD == nullptr) {
				nontrouve = false; p->_pFilsD = ptcel1;
			}
			else p = p->_pFilsD;

		}
	}
}



void Arbre::affiche_arbre_prefixe()const {
	if (_pArbre) {
		Arbre arbregauche(this->_pArbre->_pFilsG);
		Arbre arbredroit(this->_pArbre->_pFilsD);

		std::cout << _pArbre->_deltaT << " / ";
		arbregauche.affiche_arbre_prefixe();
		arbredroit.affiche_arbre_prefixe();
	}
}


void Arbre::affiche_arbre_infixe()const {
	if (_pArbre) {
		Arbre arbregauche(this->_pArbre->_pFilsG);
		Arbre arbredroit(this->_pArbre->_pFilsD);

		arbregauche.affiche_arbre_infixe();
		std::cout << _pArbre->_deltaT;
		arbredroit.affiche_arbre_infixe();
	}
}



void Arbre::affiche_arbre_postfixe()const {
	if (_pArbre) {
		Arbre arbregauche(this->_pArbre->_pFilsG);
		Arbre arbredroit(this->_pArbre->_pFilsD);

		arbregauche.affiche_arbre_postfixe();
		arbredroit.affiche_arbre_postfixe();
		std::cout << _pArbre->_deltaT;
	}
}


void Arbre::liberer_arbre() {
	if (_pArbre) {
		if (_pArbre->_pFilsD != nullptr)
		{
			Arbre arbredroit(this->_pArbre->_pFilsD);
			arbredroit.liberer_arbre();
		}
		if (_pArbre->_pFilsG != nullptr)
		{
			Arbre arbregauche(this->_pArbre->_pFilsG);
			arbregauche.liberer_arbre();
		}
		delete _pArbre;
	}
	_pArbre = nullptr;
}


Arbre Arbre::max()const {
	if (_pArbre) {
		Arbre arbredroit(this->_pArbre->_pFilsD);
		if (this->_pArbre->_pFilsD == nullptr)
		{
			return _pArbre;
		}
		arbredroit.max();
	}
}

Arbre Arbre::min()const {
	if (_pArbre) {
		Arbre arbredroit(this->_pArbre->_pFilsG);
		if (this->_pArbre->_pFilsG == nullptr)
		{
			return _pArbre;
		}
		arbredroit.min();
	}
}

size_t Arbre::hauteur()const {
	if (_pArbre) {
		Arbre arbregauche(this->_pArbre->_pFilsG);
		Arbre arbredroit(this->_pArbre->_pFilsD);
		return (1 + std::max(arbregauche.hauteur(), arbredroit.hauteur()));
	}
	return 0;
}


size_t Arbre::nbelem() const {
	if (_pArbre) {
		Arbre arbregauche(this->_pArbre->_pFilsG);
		Arbre arbredroit(this->_pArbre->_pFilsD);
		return (1 + arbregauche.nbelem() + arbredroit.nbelem());
	}
	return 0;
}


size_t Arbre::nbfeuille()const
{
	if (!_pArbre)
	{
		return 0;
	}
	if (_pArbre)
	{
		Arbre arbregauche(this->_pArbre->_pFilsG);
		Arbre arbredroit(this->_pArbre->_pFilsD);
		if (this->_pArbre->_pFilsG != nullptr && this->_pArbre->_pFilsD != nullptr)
		{
			return arbregauche.nbfeuille() + arbredroit.nbfeuille();
		}
		return 1;
	}
}


bool Arbre::non_degenere()const {
	if (_pArbre == nullptr) 
		return false;
	else {
		if (_pArbre->_pFilsG != nullptr && _pArbre->_pFilsD != nullptr) 
			return true;
		else {
			if (_pArbre->_pFilsG == nullptr) {
				Arbre arbredroit(this->_pArbre->_pFilsD);
				return arbredroit.non_degenere();
			}
			else { //_pArbre->_pFilsD == nullptr
				Arbre arbregauche(this->_pArbre->_pFilsG);
				return arbregauche.non_degenere();
			}
		}
	}
}


CelluleArbre* Arbre::recherche_ptr(float cle)const {  
	CelluleArbre* p = nullptr;

	if (_pArbre) {
		Arbre arbregauche(this->_pArbre->_pFilsG);
		Arbre arbredroit(this->_pArbre->_pFilsD);
		if (cle == _pArbre->_deltaT) {
			return _pArbre;
		}
		if (cle < _pArbre->_deltaT) {
			arbregauche.recherche_ptr(cle);
		}
		else {
			arbredroit.recherche_ptr(cle);
		}
	}
	else
		return p;
}

void Arbre::supprime_cellule(float cle) {

	CelluleArbre* p = _pArbre;
	CelluleArbre* psauve = _pArbre;
	CelluleArbre* pred = _pArbre;
	bool nontrouve = true;
	if (p != nullptr && p->_deltaT == cle) { //suppression en tete
		pred = p->_pFilsG; // pour rattachement
		if (p->_pFilsD != nullptr) {
			p = p->_pFilsD;
			while (p && p->_pFilsG)
				p = p->_pFilsG;
			p->_pFilsG = pred;
			_pArbre = _pArbre->_pFilsD;
		}
		else
			_pArbre = pred; // pas de sous arbre droit
		delete psauve;
		return;
	}

	bool _pFilsDroit = true;;
	while (p != nullptr && nontrouve) {
		if (cle < p->_deltaT) {
			pred = p;
			_pFilsDroit = false;
			p = p->_pFilsG;
		}
		else
			if (cle > p->_deltaT) {
				pred = p;
				_pFilsDroit = true;
				p = p->_pFilsD;
			}
			else 
				nontrouve = false;  // on a trouve
	}

	if (p && p->_pFilsG == nullptr && p->_pFilsD == nullptr) {  // si feuille
		if (_pFilsDroit)
			pred->_pFilsD = nullptr;
		else
			pred->_pFilsG = nullptr;
		delete p;
	}
	else { //si pas feuille
		psauve = p;

		if (p && p->_pFilsD != nullptr) {
			p = p->_pFilsD;
			while (p && p->_pFilsG)
				p = p->_pFilsG;
			p->_pFilsG = psauve->_pFilsG;
			if (_pFilsDroit)
				pred->_pFilsD = psauve->_pFilsD;
			else
				pred->_pFilsG = psauve->_pFilsD;
		}
		else
			if (pred && psauve)
				if (_pFilsDroit)
					pred->_pFilsD = psauve->_pFilsG;
				else
					pred->_pFilsG = psauve->_pFilsG; // pas de sous arbre droit
		delete psauve;
	}
	
}


float Arbre::get_temp_mois_annee(int annee)
{
	if (_pArbre)
	{
		if (annee == this->_pArbre->_annee)
		{
			return this->_pArbre->_tempMois;
		}
		else
		{
			Arbre arbregauche(this->_pArbre->_pFilsG);
			Arbre arbredroit(this->_pArbre->_pFilsD);

			arbregauche.get_temp_mois_annee(annee);
			arbredroit.get_temp_mois_annee(annee);
		}
	}
}

