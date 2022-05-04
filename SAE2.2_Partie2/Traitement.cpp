#include "Traitement.h"
#include <algorithm>

//exemple de fonction pour l exploitation de la structure arborescente
float somme_deltaT(Arbre ab) {

	if (ab.get_rac() == nullptr) return 0;
	else {
		Arbre arbregauche(ab.get_rac()->_pFilsG);
		Arbre arbredroit(ab.get_rac()->_pFilsD);

		return ab.get_rac()->_deltaT + somme_deltaT(arbregauche) + somme_deltaT(arbredroit); // parcours prefixe
	}
}

float moy_temp_station(Arbre abre) //question 1
{
	return abre.somme_temp() / abre.nbelem(); //voir dans Arbre.cpp la fonction somme_temp()
}

float moyMois(float mois, ListeStation list) //question 1
{
	float moyTot;
	float moyStation = 0;
	CelluleStation* cel = list.get_tete();
	while (cel) //tant que cel n'est pas = nullptr
	{
		Arbre arb(cel->tab_arbres[mois - 1]); //def de la cellule arbre de la station pour un mois donne
		moyStation += moy_temp_station(arb);//somme des moyennes de temp de chaque Station
	//											//voir dans Arvre.cpp la fonction moy_temp_station()
		cel = cel->_pSuiv; // passage a la cellule suivante
	}
	moyTot = moyStation / list.nbelem(); //calcul de la moyenne
	return moyTot;
}

std::array<std::array<std::array<float, 12>, 18>, 30> tabTempMoyMoisStationAnnee(ListeStation list)
{
	std::array<std::array<std::array<float, 12>, 18>, 30> tab;
	for (size_t i = 0; i < 30; i++) //pour chaque annee
	{
		CelluleStation* Stat = list.get_tete();
		size_t j = 0;
		while (Stat) //pour chaque Station
		{
			for (size_t k = 0; k < 12; k++) //pour chaque mois
			{
				tab[i][j][k] = (Stat->tab_arbres[k]).recherche_annee(1992+i)->_tempMois;
			}
			Stat = Stat->_pSuiv;
			j++;
		}
	}
	return tab;
}

void affichePlusChaudTrois(ListeStation list)
{
	std::array<std::array<std::array<float, 12>, 18>, 30> tab = tabTempMoyMoisStationAnnee(list);
	std::vector<float> moyA;
	for (size_t i = 0; i < 30; i++) //chq annee
	{
		float moy = 0;
		for (size_t j = 0; j < 18; j++)//chq station
		{
			for (size_t k = 0; k < 12; k++)//chq mois
			{
				moy += tab[i][j][k];
			}
			moy /= 12; //moyenne de chq station
		}
		moy /= 18; //moyenne de chq annee
		moyA.push_back(moy);
		std::sort(moyA.begin(), moyA.end());
	}
	std::cout << moyA[0] << " " << moyA[1] << " " << moyA[2] << "\n";
}


