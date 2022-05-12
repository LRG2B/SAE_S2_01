//! \file CelluleStation.h
//! \brief Fichier de la classe CelluleStation
//! \date 12/05/2022
//! \version 1.0

#pragma once
#include "Arbre.h"
#include <array>

//! \class CelluleStation
//! \brief Classe modélisant les céllules utiliser par la classe ListeStation
//! \date 12/05/2022
//! \version 1.0

struct CelluleStation
{
    int _ID; // numero identification station
    std::array<Arbre, 12> tab_arbres; // 1 arbre par mois
    CelluleStation* _pSuiv; // pointeur vers la cellule suivante
    CelluleStation* _pPred; // pointeur vers la cellule précèdante

    //! \brief Constructeur
    //! \param ID
    CelluleStation(int ID = -1) : _ID{ ID }, _pSuiv{ nullptr }, _pPred{ nullptr } {}

    //! \brief Donne la Temperature moyenne d'une station sur une année donner
    //! \param annee
    //! \return float
    float CelluleStation::get_temp_annee_station(int annee);
};

