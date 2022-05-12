//! \file SAE_Datas_Heat.h
//! \brief 
//! \date 12/05/2022
//! \version 1.0

#pragma once

#include "ListeStation.h"
#include "Arbre.h"
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <map>
#include <utility>

//! \class SAE_Datas_Heat
//! \brief 
//! \date 12/05/2022
//! \version 1.0

class SAE_Datas_Heat {
	
	std::vector<std::map<int, std::pair<float,float>>> _vRawData;
	ListeStation _lListeStations;

	//! \param path
	//! \return std::string
	std::string readFileIntoString(const std::string& path)const;

	//! \return std::vector<std::string>
	std::vector<std::string> listAllFiles()const;

	//! \param filename
	//! \return std::map<int, std::pair<float, float>>
	std::map<int, std::pair<float, float>> parseContentFile(std::string filename);

	//! \return void
	void convertDataInList();

	//! \param mois, vTmoyStation, vTSigmaStation
	//! \return Arbre
	Arbre calculDeltaT(size_t mois, const std::vector<float>& vTmoyStation, const std::vector<float>& vTSigmaStation);

public:
	
	SAE_Datas_Heat();

	//! \return size_t
	size_t nbMonths()const;

	//! \return size_t
	size_t nbStations()const { return _lListeStations.nbelem(); }

	//! \return ListeStation&
	const ListeStation& getListeStation()const { return _lListeStations; }
};