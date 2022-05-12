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

//! \brief Donne la somme de tout les Delta T
//! \param ab
//! \return float
float somme_deltaT(Arbre ab);

//! \brief Retourne la somme de toute les temperature
//! \param ab
//! \return float
float sommeTemp(Arbre ab);

//! \brief La somme des temperatures de l'ensemble des stations sur un mois donne ? 
//! \param lB, nameMonth
//! \return void
void displaySommeTemp(ListeStation& lB, std::vector<std::string>& nameMonth);

//! \brief Donne la moyenne des temperature
//! \param ab
//! \return float
float moyTemp(Arbre ab);

