#include "CelluleStation.h"


float CelluleStation::get_temp_annee_station(int annee)
{
	float temp_annee = 0;
	for (auto arbre : tab_arbres)
		temp_annee += arbre.get_temp_mois_annee(annee);
	return temp_annee / 12.0f;
}