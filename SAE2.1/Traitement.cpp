//! \file Traitement.cpp
//! \brief 
//! \date 12/05/2022
//! \version 1.0

#include "Traitement.h"

//exemple de fonction pour l exploitation de la structure arborescente
float somme_deltaT(Arbre ab) {

	if (ab.get_rac() == nullptr) return 0;
	else {
		Arbre arbregauche(ab.get_rac()->_pFilsG);
		Arbre arbredroit(ab.get_rac()->_pFilsD);

		return ab.get_rac()->_deltaT + somme_deltaT(arbregauche) + somme_deltaT(arbredroit); // parcours prefixe
	}
}

// Calcul la somme des temperatures sur un mois donnee
float sommeTemp(Arbre ab)
{
	if (ab.get_rac() == nullptr) return 0;
	else {
		Arbre arbregauche(ab.get_rac()->_pFilsG);
		Arbre arbredroit(ab.get_rac()->_pFilsD);

		return ab.get_rac()->_tempMois + sommeTemp(arbregauche) + sommeTemp(arbredroit);
	}
}

// Affichage de la somme des températures sur un mois donnee
void displaySommeTemp(ListeStation& lB, std::vector<std::string>& nameMonth)
{
	std::cout << "\x1B[1;31m Quelle est la somme des temperatures de l'ensemble des stations sur un mois donne ?\x1B[0m\n\n";
	CelluleStation* p = lB.get_tete();
	while (p != nullptr) {
		std::cout << "\x1B[1;33m Les sommes des temp de la station " << p->_ID << " sont : \x1B[0m\n";
		for (size_t i = 0; i < p->tab_arbres.size(); i++) {
			std::cout << "Mois de " << nameMonth[i] << " : \x1B[1;32m" << sommeTemp(p->tab_arbres[i]) << "\x1B[0m\n";
		}
		p = p->_pSuiv;
	}
	std::cout << "\x1B[0m" << std::endl;
}

// Calcul la moyenne des temperatures sur un mois donnee
float moyTemp(Arbre ab)
{
	if (ab.get_rac() == nullptr) return 0;
	else {
		return sommeTemp(ab) / ab.nbelem();
	}
}