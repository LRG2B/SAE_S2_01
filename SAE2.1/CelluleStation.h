//! \file CelluleStation.h
//! \brief 
//! \date 12/05/2022
//! \version 1.0

#pragma once
#include "Arbre.h"
#include <array>

//! \class CelluleStation
//! \brief 
//! \date 12/05/2022
//! \version 1.0

struct CelluleStation
{
    int _ID; // numero identification station
    std::array<Arbre, 12> tab_arbres; // 1 arbre par mois
    CelluleStation* _pSuiv;
    CelluleStation* _pPred;

    //! \param ID
    CelluleStation(int ID = -1) : _ID{ ID }, _pSuiv{ nullptr }, _pPred{ nullptr } {}
    
    //! \param annee
    //! \return float
    float CelluleStation::get_temp_annee_station(int annee);
};

