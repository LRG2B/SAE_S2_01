//! \file Arbre.h
//! \brief Fichier de la classe Arbre
//! \date 12/05/2022
//! \version 1.0

#pragma once
#include "CelluleArbre.h"

//! \class Arbre
//! \brief Classe modélisant un arbre binaire de recherche
//! \date 12/05/2022
//! \version 1.0

class Arbre {
	CelluleArbre* _pArbre;
public:

	//! \brief constructeur de Arbre
	//! \param ptr
	Arbre(CelluleArbre* ptr = nullptr) : _pArbre{ ptr } {}

	//! \brief retourne la racine de l'arbre
	//! \return _pArbre
	CelluleArbre* get_rac() { return _pArbre; }

	//! \brief Ajoute une cellule dans l'arbre
	//! \param cel
	//! \return void
	void ajoute_cellule(const CelluleArbre& cel);

	//! \brief Affiche un arbre avec la méthode préfixé
	//! \return void
	void affiche_arbre_prefixe()const;

	//! \brief Affiche un arbre avec la méthode infixé
	//! \return void
	void affiche_arbre_infixe()const;

	//! \brief Affiche un arbre avec la méthode postfixé
	//! \return void
	void affiche_arbre_postfixe()const;

	//! \brief Detruit toutes les branche de l'arbre
	//! \return void
	void liberer_arbre();

	//! \brief Donne le nombre d'élement
	//! \return size_t
	size_t nbelem() const;

	//! \brief Donne la valeur max de l'arbre
	//! \return Arbre
	Arbre max()const;

	//! \brief Donne la valeur min de l'arbre
	//! \return Arbre
	Arbre min()const;

	//! \brief Retourne la hauteur de l'arbre 
	//! \return size_t
	size_t hauteur()const;

	//! \brief Retourne le nombre de feuille de l'arbre
	//! \return size_t
	size_t nbfeuille()const;

	//! \brief Teste si l'arbre est dégénèrer ou pas
	//! \return bool
	bool non_degenere()const;

	//! \brief Recherche une valeur
	//! \param cle
	//! \return CelluleArbre*
	CelluleArbre* recherche_ptr(float cle)const;

	//! \brief Supprime la cellule correspondant a la valeur
	//! \param cle
	//! \return void
	void supprime_cellule(float cle);

	//! \brief Donne la moyenne de temperaure du mois pour l'anne passer en paramètre
	//! \param annee
	//! \return float
	float get_temp_mois_annee(int annee);
};