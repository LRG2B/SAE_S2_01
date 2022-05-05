#include "SAE_Datas_Heat.h"

#include <iostream> // std::cerr
#include <algorithm>    // std::find
#include <numeric> // std::accumulate

std::string  SAE_Datas_Heat::readFileIntoString(const std::string& path)const {
    auto ss = std::ostringstream{};
    std::ifstream input_file(path);
    if (!input_file.is_open()) {
        std::cerr << "Could not open the file - '"
            << path << "'\n";
        exit(EXIT_FAILURE);
    }
    ss << input_file.rdbuf();
    return ss.str();
}

std::vector<std::string>  SAE_Datas_Heat::listAllFiles()const {
    std::filesystem::path path("data");
    std::vector<std::string> myFiles;
    for (const auto& file : std::filesystem::directory_iterator(path))
        if (file.path().filename().extension() == ".csv")
            myFiles.push_back(file.path().string());
    return myFiles;
}

std::map<int, std::pair<float, float> > SAE_Datas_Heat::parseContentFile(std::string filename) {
    std::string file_contents;                                           // contenu du fichier CSV en un seul string
    std::map<int, std::pair<float, float> > csv_contents; // contenu du fichier mis dans la structure de donn�es on a � la fois l'ID de la station et une paire Tmoy Tsigma
    char delimiter = ';';
  
    file_contents = readFileIntoString(filename);

    std::pair<float, float> TmoyTsigma;        // contiendra la temp�rature moyenne du mois et son �cart type
    std::istringstream sstream(file_contents); // flux contenant tout le fichier CSV 
    std::vector< std::string > items;          // contiendra une ligne du fichier CSV sous forme de tableau de string 
    std::string sIndexStation;                 // nom de la station sous forme de string (par exemple "07005")
    std::string record;                        // contenu d'une ligne du fichier CSV comme un seul string
    const size_t colTmoy = 3;                  // colonne du tableau contenant la temp�rature moyenne du mois
    const size_t colTsigma = 4;                // colonne du tableau contenant les �carts-types moyen des temp�ratures du mois

    size_t counter = 0; // lignes du fichier CSV
    while (std::getline(sstream, record)) {
        std::istringstream line(record);
        bool indexIsLoaded = false;
        while (std::getline(line, record, delimiter)) {
            record.erase(std::remove_if(record.begin(), record.end(), isspace), record.end());
            if(indexIsLoaded)
                items.push_back(record); // On ajoute le string lu au vecteur
            else {
                sIndexStation = record; // On sauvegarde l'index de la station en string
                indexIsLoaded = true;
            }
        }
        if (counter != 0) // On ne met pas la ligne avec les entetes de colonne
        {
            int indexStation = std::atoi(sIndexStation.c_str());
            if (items[colTmoy].size() == 0 && items[colTsigma].size() == 0) // il n'y a rien � enregister
            {
                ; // Donc on fait rien
            }
            else
                if(items[colTmoy].size() == 0)       // Tsigma existe alors que Tmoy n existe pas : erreur dans le fichier CSV c'est TMoy � la place de Tsigma
                    TmoyTsigma = std::make_pair(std::stof(items[colTsigma]), 0.0);
                else
                    if(items[colTsigma].size() == 0) // Pas d'�cart type
                        TmoyTsigma = std::make_pair(std::stof(items[colTmoy]),0.0);
                    else                             // CAS g�n�ral on a Tmoy et Tsigma
                        TmoyTsigma = std::make_pair(std::stof(items[colTmoy]), std::stof(items[colTsigma]));
            csv_contents[indexStation]=TmoyTsigma;
        }
        items.clear();
        counter += 1;
    }
    return csv_contents;
}

void SAE_Datas_Heat::convertDataInList()
{
    size_t maxStation = _vRawData[0].size(); // nombre de stations du premier mois enregistr�
    // maxStation va diminuer au fur et � mesure que des stations vont arr�ter leurs relev�s
    // on skippera les nouvelles stations car elles non plus ne seront pas compl�tes
    size_t monthRecorded = nbMonths();
  
    std::vector<int> vIDstation(maxStation);                     // vecteur des ID des stations
    std::vector<std::vector<float>> vStationTmoy(maxStation);    // vecteur des temp�ratures moyennes
    std::vector<std::vector<float>> vStationTsigma(maxStation);  // vecteur des �carts types moyen des temp�ratures
 
    // Le premier mois on remplit le vecteur d'ID et le d�but des vecteurs de temp�ratures
    size_t nbStation = 0;
    for (const auto& [indexStation, tMoySigma] : _vRawData[0]) { // Pour chaque station du premier mois
        vIDstation[nbStation] = indexStation;
        vStationTmoy[nbStation].resize(monthRecorded); // On r�serve la place pour tous les mois
        vStationTmoy[nbStation][0] = tMoySigma.first;
        vStationTsigma[nbStation].resize(monthRecorded); // On r�serve la place pour tous les mois
        vStationTsigma[nbStation][0] = tMoySigma.second;
        nbStation++; // On incr�mente l'index des stations
    }

    for (size_t month = 1; month < monthRecorded; month++) { // Pour chaque mois
        std::vector<bool> vbIsVisited(maxStation, false); // on remet � faux pour savoir si on a bien enregistr� la station

        for (const auto& [IDstation, tMoySigma] : _vRawData[month]) { // Pour chaque station du mois
            // On regarde si l'ID de la station n'a pas disparu
            // on skippe les nouvelles stations
            auto itIDstation = std::find(vIDstation.begin(), vIDstation.end(), IDstation);
            if(itIDstation != vIDstation.end()) { // Si la station �met depuis le d�but
                size_t iStation = std::distance(vIDstation.begin(), itIDstation); // On r�cup�re son index
                vStationTmoy[iStation][month] = tMoySigma.first;
                vStationTsigma[iStation][month] = tMoySigma.second;
                vbIsVisited[iStation] = true;
            }
            else { // c'est une nouvelle station on ne fait rien
                ;
            }
        }

        // Toutes les stations qui n'ont pas �t� visit�es ont arr�t� d'�mettre et doivent �tre supprim�es
        for (size_t iStation = 0; iStation < maxStation;/* RIEN on incr�mente seulement si la station a �t� visit�e */) {
            if (!vbIsVisited[iStation]) {
                for (size_t i = iStation + 1; i < maxStation; i++) { // on d�cale toutes les stations de 1 cran � gauche
                    vbIsVisited[i - 1] = vbIsVisited[i];
                    vIDstation[i - 1] = vIDstation[i];
                    vStationTmoy[i - 1] = vStationTmoy[i];
                    vStationTsigma[i - 1] = vStationTsigma[i];
                }
                maxStation--;   // on enl�ve la derni�re
                vbIsVisited.pop_back(); vbIsVisited.shrink_to_fit();
                vIDstation.pop_back(); vIDstation.shrink_to_fit();
                vStationTmoy.pop_back(); vStationTmoy.shrink_to_fit();
                vStationTsigma.pop_back(); vStationTsigma.shrink_to_fit();
            }
            else
                iStation++;
        }
    }
    // Il ne reste que 18 stations compl�tes
    // 
    // A COMPLETER
    // vous devez maintenant creer la structure arborescente 
    // Parcours des maxStation stations, creation des cellules de la liste et des 12 arbres associes a chaque cellule
    // la creation d un arbre se fera via la fonction calculDeltaT que vous devez egalement completer

    // Parcours des maxStations stations
    for (size_t iStation = 0; iStation < maxStation; iStation++) {
        // Creation des cellules de la liste
        CelluleStation Sta(vIDstation[iStation]);
        // Creation des 12 arbres pour chaque mois
        for (size_t month = 0; month < 12; month++) {
            // Association des arbres a la cellule station
            Sta.tab_arbres[month] = calculDeltaT(month, vStationTmoy[iStation], vStationTsigma[iStation]);
        }
        // Ajout de la cellule dans la liste bi-directionnelle
        _lListeStations.ajoute_cellule_en_tete(Sta);
    }

  
}

Arbre SAE_Datas_Heat::calculDeltaT(size_t mois, const std::vector<float>& vTmoyStation, const std::vector<float>& vTSigmaStation)
{
    Arbre a;
    int annee = 1992; // annee de d�part
  
    // Creation d'un compteur qui commence au mois + 12 pour etre a l'annee suivante
    size_t cpt = mois + 12;
    // Parcours jusqu'a que le compteur depasse la limite d'un des deux vecteur
    while (cpt < vTmoyStation.size() || cpt < vTSigmaStation.size()) {
        // Incrementation de l'annee avant les instructions car nous partons de annee + 1
        annee++;
        // Creation des cellules arbres avec le calcul du DeltaT
        CelluleArbre Arb((vTmoyStation[cpt] - vTmoyStation[cpt - 12]), annee - 1, vTmoyStation[cpt - 12], vTSigmaStation[cpt - 12]);
        // Ajout de la cellule a l'arbre
        a.ajoute_cellule(Arb);
        // Incrementation du compteur
        cpt += 12;
    }
    // Ce programme ne comptabilise pas la derniere annee (2022) car il est impossible de calculer le DeltaT pour cet annee

    return a;
}




////////////////////////////////////////////////////////////////////////////////////////////////
//                           Public Functions
////////////////////////////////////////////////////////////////////////////////////////////////

size_t SAE_Datas_Heat::nbMonths() const
{
    return _vRawData.size();
}

SAE_Datas_Heat::SAE_Datas_Heat() {
    auto myFiles = listAllFiles();
 
    _vRawData.reserve(myFiles.size());
    for (auto const& file : myFiles)
        _vRawData.emplace_back(parseContentFile(file));
    convertDataInList();
}
