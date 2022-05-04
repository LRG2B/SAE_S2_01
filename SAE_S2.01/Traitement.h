#pragma once

#include <iostream>

#include "CelluleStation.h"
#include "ListeStation.h"
#include "CelluleArbre.h"
#include "Arbre.h"
#include <vector>

float somme_deltaT(Arbre ab);

float sommeTemp(Arbre ab);

float moy_temp_station(Arbre abre);

float moyTemp(Arbre ab);


std::array<std::array<std::array<float, 12>, 18>, 30> tabTempMoyMoisStationAnnee(ListeStation list);

void affichePlusChaudTrois();