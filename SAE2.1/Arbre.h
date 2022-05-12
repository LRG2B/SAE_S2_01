//! \file Arbre.h
//! \brief 
//! \date 12/05/2022
//! \version 1.0

#pragma once
#include "CelluleArbre.h"

//! \class Arbre
//! \brief 
//! \date 12/05/2022
//! \version 1.0

class Arbre {
	CelluleArbre* _pArbre;
public:

	//! \param ptr
	Arbre(CelluleArbre* ptr = nullptr) : _pArbre{ ptr } {}

	//! \return _pArbre
	CelluleArbre* get_rac() { return _pArbre; }

	//! \param cel
	//! \return void
	void ajoute_cellule(const CelluleArbre& cel);

	//! \return void
	void affiche_arbre_prefixe()const;

	//! \return void
	void affiche_arbre_infixe()const;

	//! \return void
	void affiche_arbre_postfixe()const;

	//! \return void
	void liberer_arbre();

	//! \return size_t
	size_t nbelem() const;

	//! \return Arbre
	Arbre max()const;

	//! \return Arbre
	Arbre min()const;

	//! \return size_t
	size_t hauteur()const;

	//! \return size_t
	size_t nbfeuille()const;

	//! \return bool
	bool non_degenere()const;

	//! \param cle
	//! \return CelluleArbre*
	CelluleArbre* recherche_ptr(float cle)const;

	//! \param cle
	//! \return void
	void supprime_cellule(float cle);

	//! \param annee
	//! \return float
	float get_temp_mois_annee(int annee);
};