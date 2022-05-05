
#pragma once

#include <iostream>

#include "CelluleStation.h"
#include "ListeStation.h"
#include "CelluleArbre.h"
#include "Arbre.h"
#include <vector>

float somme_deltaT(Arbre ab);

// Q1 : Calcul de la temperature moyenne de l'ensemble des stations sur un mois donne
float sommeTemp(Arbre ab);
void displaySommeTemp(ListeStation& lB, std::vector<std::string>& nameMonth);
float moyTemp(Arbre ab);
void displayMoyTemp(ListeStation& lB, std::vector<std::string>& nameMonth);
void displayMoyTempSta(ListeStation& lB, int mois);

// Q5 : Calculez le réchauffement pour chaque saison
Arbre globalWarning(Arbre ab1, Arbre ab2, Arbre ab3);
void displayGlobalWarningSeasons(ListeStation& lB);
void displayDelta(Arbre ab);
