//! \file ListeStation.h
//! \brief Fichier de la classe ListeStation
//! \date 12/05/2022
//! \version 1.0

#pragma once
#include "CelluleStation.h"

//! \class ListeStation
//! \brief Classe mod�lisant une liste chain�e
//! \date 12/05/2022
//! \version 1.0

class ListeStation{
	CelluleStation* _pListDeb = nullptr; //pointeur sur la premi�re cellule
	CelluleStation* _pListFin = nullptr; //pointeur sur la derni�re cellule
public:

	//! \brief Donne le premier �l�ment de la liste
	//! \return _pListDeb
	CelluleStation* get_tete() { return _pListDeb; }

	//! \brief Donne le dernier �l�ment de la liste
	//! \return _pListFin
	CelluleStation* get_queue() { return _pListFin; }

	//! \brief Ajouter une cellule a la liste
	//! \param cel
	//! \return void
	void ajoute_cellule_en_tete(const CelluleStation& cel);

	//! \brief Affiche la liste 
	//! \return void
	void affiche_liste()const;
	
	//! \brief Affiche la cellule dans l'autre sens
	//! \return void
	void affiche_liste_endroit()const;

	//! \brief Detruit tout les �l�ment de la liste
	//! \return void
	void liberer_liste();

	//! \brief Donne la temp�rature moyenne sur l'ann�e de toute les station
	//! \param annee
	//! \return float
	float get_temp_annee(int annee);

	//! \brief Donne le nombre d'element de la liste
	//! \return size_t
	size_t nbelem() const;

	//! \brief Recherche une Station par son ID
	//! \param cel
	//! \return CelluleStation*
	CelluleStation* recherche_ptr(int cle)const;  

	//! \brief Supprime la cellule correspondant a l'ID donner
	//! \param cel
	//! \return void
	void supprime_cellule(int cle);
};

