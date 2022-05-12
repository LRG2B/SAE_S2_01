//! \file ListeStation.cpp
//! \brief 
//! \date 12/05/2022
//! \version 1.0

#pragma once
#include "ListeStation.h"
#include <iostream>
#include <vector>
#include <string>

// Cette fonction est un peu a modifier par rapport a la partie 1 car il y a un tableau maintenant en plus
void ListeStation::ajoute_cellule_en_tete(const CelluleStation& cel) {
	// Initialisation du pointeur de la cellule à ajouter en tete
	CelluleStation* celTete = new CelluleStation(cel._ID);
	celTete->tab_arbres = cel.tab_arbres;

	// cas 1 : si la liste est vide
	if (_pListFin == nullptr) {
		// On ajoute la cellule au debut et la fin
		_pListFin = celTete;
		_pListDeb = celTete;
	}
	// cas 2 : si la liste n'est pas vide
	else {
		// On initialise le pointeur du suivant pour la nouvelle cellule
		celTete->_pSuiv = _pListDeb;
		// On initialise le pointeur du precedant pour la cellule de debut
		_pListDeb->_pPred = celTete;
		// On ajoute la cellule au debut
		_pListDeb = celTete;
	}
}

void ListeStation::affiche_liste() const {
	CelluleStation* p = _pListDeb;
	std::vector<std::string> nameMonth = { "Janvier", "Fevrier", "Mars", "Avril", "Mai", "Juin", "Juillet",
		"Aout", "Septembre", "Octobre", "Novemebre", "Decembre" };
	while (p != nullptr) {
		std::cout << "\x1B[1;31m ID : " << p->_ID << "\x1B[0m\n";
		for (size_t i = 0; i < p->tab_arbres.size(); i++) {
			std::cout << "Mois de " << nameMonth[i] << " : \x1B[1;32m";
			p->tab_arbres[i].affiche_arbre_prefixe();
			std::cout << "\x1B[0m\n";
		}
		p = p->_pSuiv;
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void ListeStation::affiche_liste_endroit() const {
	CelluleStation* p = _pListFin;
	std::cout << "\x1B[1;32m";
	while (p != nullptr) {
		std::cout << p->_ID << " ";
		p = p->_pPred;
	}
	std::cout << "\x1B[0m" << std::endl;
}

size_t ListeStation::nbelem() const
{
	CelluleStation* p = _pListDeb;
	int nb = 0;
	while (p != nullptr) {
		nb += 1;
		p = p->_pSuiv;
	}
	return nb;
}

// renvoie le ptr vers cellule avec cle. Si cle absente renvoie null
CelluleStation* ListeStation::recherche_ptr(int cle)const
{
	CelluleStation* p = _pListDeb;
	if (!_pListFin) return nullptr;  //liste vide
	else {
		while (p != nullptr && p->_ID != cle) {
			p = p->_pSuiv;
		}
		if (p)
			return p;
		else return nullptr;
	}
}

void ListeStation::supprime_cellule(int cle)
{
	CelluleStation* pred = recherche_ptr(cle)->_pPred;
	CelluleStation* p;

	if (pred != nullptr && pred->_pSuiv->_pSuiv == nullptr) {
		p = pred->_pSuiv;
		pred->_pSuiv = nullptr;
		_pListFin = pred;
		delete p;
	}
	else if (pred != nullptr) {
		p = pred->_pSuiv;
		pred->_pSuiv = p->_pSuiv;
		p->_pSuiv->_pPred = pred;
		delete p;
	}
	else {
		if (_pListDeb && _pListDeb->_ID == cle && _pListDeb == _pListFin) {
			p = _pListDeb;
			_pListDeb = nullptr;
			_pListFin = nullptr;
			delete p;
		}
		else if (_pListDeb && _pListDeb->_ID == cle) {
			p = _pListDeb;
			p->_pSuiv->_pPred = nullptr;
			_pListDeb = p->_pSuiv;
			delete p;
		}
	}
}

void ListeStation::liberer_liste()
{
	CelluleStation* p = _pListDeb;
	while (_pListDeb != nullptr) {
		CelluleStation* p = _pListDeb;
		_pListDeb = _pListDeb->_pSuiv;
		delete p;
	}
}

float ListeStation::get_temp_annee(int annee)
{
	float temp = 0;
	CelluleStation* pStation = _pListDeb;
	while (pStation != _pListFin)
	{
		temp += pStation->get_temp_annee_station(annee);
		pStation = pStation->_pSuiv;
	}
	return temp / this->nbelem();
}