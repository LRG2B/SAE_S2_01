//! \file ListeStation.h
//! \brief 
//! \date 12/05/2022
//! \version 1.0

#pragma once
#include "CelluleStation.h"

//! \class ListeStation
//! \brief 
//! \date 12/05/2022
//! \version 1.0

class ListeStation{
	CelluleStation* _pListDeb = nullptr;
	CelluleStation* _pListFin = nullptr;
public:

	//! \return _pListDeb
	CelluleStation* get_tete() { return _pListDeb; }

	//! \return _pListFin
	CelluleStation* get_queue() { return _pListFin; }

	//! \param cel
	//! \return void
	void ajoute_cellule_en_tete(const CelluleStation& cel);

	//! \return void
	void affiche_liste()const;
	
	//! \return void
	void affiche_liste_endroit()const;

	//! \return void
	void liberer_liste();

	//! \param annee
	//! \return float
	float get_temp_annee(int annee);

	//! \return size_t
	size_t nbelem() const;

	//! \param cel
	//! \return CelluleStation*
	CelluleStation* recherche_ptr(int cle)const;  

	//! \param cel
	//! \return void
	void supprime_cellule(int cle);
};

