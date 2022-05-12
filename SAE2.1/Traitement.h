//! \file Traitement.h
//! \brief 
//! \date 12/05/2022
//! \version 1.0

#pragma once
#include <iostream>
#include "CelluleStation.h"
#include "ListeStation.h"
#include "CelluleArbre.h"
#include "Arbre.h"
#include <vector>

//! \param ab
//! \return float
float somme_deltaT(Arbre ab);

//! \param ab
//! \return float
float sommeTemp(Arbre ab);

//! \param lB, nameMonth
//! \return void
void displaySommeTemp(ListeStation& lB, std::vector<std::string>& nameMonth);

//! \param ab
//! \return float
float moyTemp(Arbre ab);

//! \param lB, nameMonth
//! \return void
void displayMoyTemp(ListeStation& lB, std::vector<std::string>& nameMonth);

//! \param lB, mois
//! \return void
void displayMoyTempSta(ListeStation& lB, int mois);

//! \param ab1, ab2, ab3
//! \return Arbre
Arbre globalWarning(Arbre ab1, Arbre ab2, Arbre ab3);

//! \param lB
//! \return void
void displayGlobalWarningSeasons(ListeStation& lB);

//! \param ab
//! \return void
void displayDelta(Arbre ab);
