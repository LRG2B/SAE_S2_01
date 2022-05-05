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

// Affichage de la moyenne des températures sur un mois donnee pour chaque stations
void displayMoyTemp(ListeStation& lB, std::vector<std::string>& nameMonth)
{
	std::cout << "\x1B[1;31m Quelle est la temperature moyenne pour chaque stations sur un mois donne ?\x1B[0m\n\n";
	CelluleStation* p = lB.get_tete();
	while (p != nullptr) {
		std::cout << "\x1B[1;33m Les temp moy des stations " << p->_ID << " est : \x1B[0m\n";
		for (size_t i = 0; i < p->tab_arbres.size(); i++) {
			std::cout << "Mois de " << nameMonth[i] << " : \x1B[1;32m" << moyTemp(p->tab_arbres[i]) << "\x1B[0m\n";
		}
		p = p->_pSuiv;
	}
	std::cout << "\x1B[0m" << std::endl;
}

void displayMoyTempSta(ListeStation& lB, int mois)
{
	// Q1 : Quelle est la température moyenne de l’ensemble des stations sur un mois donné ?
	std::cout << "\x1B[1;31mQ1 : Quelle est la temperature moyenne de l'ensemble des stations sur un mois donne ?\x1B[0m\n\n";
	CelluleStation* p = lB.get_tete();
	float moyStation = 0.0;
	size_t nbElem = p->tab_arbres[mois].nbelem();
	std::cout << "\x1B[1;33m Les temp moy des stations est : \x1B[0m\n";
	while (p != nullptr) {
		moyStation += moyTemp(p->tab_arbres[mois]);
		p = p->_pSuiv;
	}
	moyStation = moyStation / nbElem;
	std::cout << "\x1B[1;32m " << moyStation << "\x1B[0m" << std::endl;
}

Arbre globalWarning(Arbre ab1, Arbre ab2, Arbre ab3)
{
	if (ab1.get_rac() == nullptr || ab2.get_rac() == nullptr || ab3.get_rac() == nullptr) return 0;
	else {
		return std::max(std::max(ab1.get_rac(), ab2.get_rac()), ab3.get_rac());
	}
}

void displayDelta(Arbre ab)
{
	if (ab.get_rac()) {
		Arbre arbregauche(ab.get_rac()->_pFilsG);
		Arbre arbredroit(ab.get_rac()->_pFilsD);

		displayDelta(arbregauche);
		std::cout << "Annee : " << ab.get_rac()->_annee << " / deltaT : " << ab.get_rac()->_deltaT << "\n";
		displayDelta(arbredroit);
	}
}

void displayGlobalWarningSeasons(ListeStation& lB)
{
	std::cout << "\x1B[1;31m Q5 : Calculez le réchauffement pour chaque saison\x1B[0m\n\n";
	CelluleStation* p = lB.get_tete();

	std::cout << "\x1B[1;33m Les temp moy des stations est : \x1B[0m\n";
	while (p != nullptr) {

		for (size_t i = 0; i < p->tab_arbres.size(); i++) {
			Arbre maxhiver = globalWarning((p->_pPred) ? p->_pPred->tab_arbres[11] : p->tab_arbres[11], p->tab_arbres[0], p->tab_arbres[1]);
			Arbre maxPrintemps = globalWarning(p->tab_arbres[2], p->tab_arbres[3], p->tab_arbres[4]);
			Arbre maxEte = globalWarning(p->tab_arbres[5], p->tab_arbres[6], p->tab_arbres[7]);
			Arbre maxAutomme = globalWarning(p->tab_arbres[8], p->tab_arbres[9], p->tab_arbres[10]);

			std::cout << "Maxhiver :\n";
			displayDelta(maxhiver);
			std::cout << "maxPrintemps :\n";
			displayDelta(maxPrintemps);
			std::cout << "maxEte :\n";
			displayDelta(maxEte);
			std::cout << "maxAutomme :\n";
			displayDelta(maxAutomme);
		}

		p = p->_pSuiv;
	}
	std::cout << "\x1B[0m" << std::endl;
}