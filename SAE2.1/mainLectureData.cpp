#include <iostream> // std::cout
#include "SAE_Datas_Heat.h"
#include "Traitement.h"
#define LIBGRAPH2_LEVEL 4  
#include <LibGraph2.h>     
#include <Windows.h>
#include <tchar.h>

using namespace LibGraph2;


int APIENTRY _tWinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPTSTR    lpCmdLine,
	int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	SAE_Datas_Heat myStations;
	ListeStation lB = myStations.getListeStation();

    CSize resolution{ 1920, 1080 };

    //Définition des couleurs
    auto noir = MakeARGB(255, 0, 0, 0);
    auto blanc = MakeARGB(255, 255, 255, 255);
    auto rouge = MakeARGB(255, 155, 0, 0);
    auto vert = MakeARGB(255, 54, 225, 7);

    //Définition des intervalles du graphique
    const int inter_annee = 58;                 //Années
    const int inter_temp = 100;                 //Températures

    float val_temp;                             //Valeur de la température pour une année donnée
    int annee = 1992;                           //Définition de l'année de début
    float moyenne_temp = 0;                     //Moyenne de température totale

    CSize taille_point{ 20,20 };                //Définition de la taille du point du graphique
    CPoint pos_point;                           //Position du point dans le graphique
    CPoint pos_point_pre;                       //Position du point précédents dans le graphique
    CRectangle point;                           //Création du rectangle englobant du point
    CPoint centre_point{ 10,10 };               //Définition du centre du point

	ILibGraph2* libgraph = GetLibGraph2();
	libgraph->show(resolution, true);
	evt e;

    while (libgraph->waitForEvent(e))
    {
        switch (e.type)
        {
        case evt_type::evtRefresh:

        case evt_type::evtKeyDown:
            switch (e.vkKeyCode)
            {
            case 'A':
            {
                libgraph->beginPaint();
                //------------------------Affichage-du-cadre
                libgraph->setPen(noir, 4.0f, LibGraph2::pen_DashStyles::Solid);
                libgraph->drawLine(CPoint{ 100,100 }, CPoint{ 100,1000 });              //Cadre gauche
                libgraph->drawLine(CPoint{ 100,1000 }, CPoint{ 1800,1000 });            //Cadre bas
                //------------------------Affichage-des-flèches
                libgraph->drawLine(CPoint{ 100,100 }, CPoint{ 75,125 });                //Flèche haut-gauche
                libgraph->drawLine(CPoint{ 100,100 }, CPoint{ 125,125 });               //Flèche haut-droite
                libgraph->drawLine(CPoint{ 1800,1000 }, CPoint{ 1775, 1025 });          //Flèche droite-bas
                libgraph->drawLine(CPoint{ 1800,1000 }, CPoint{ 1775, 975 });           //Flèche droite-haut

                //------------------------Affichage-des-intervalles-/-valeurs
                for (float i = 1; i <= 8; i++)
                {
                    libgraph->drawLine(CPoint{ 90 ,1000 - (inter_temp * i) }, CPoint{ 110, 1000 - (inter_temp * i) });          // Affichage des intervalles sur l'axe des ordonnées
                }
                pos_point_pre = CPoint{ 100 + (inter_annee * 1) , (1000 - (11.8620358 - 11) * 300) };
                for (float i = 1; i <= 29; i++)
                {
                    libgraph->setPen(noir, 4.0f, LibGraph2::pen_DashStyles::Solid);
                    libgraph->drawLine(CPoint{ 100 + (inter_annee * i), 990 }, CPoint{ 100 + (inter_annee * i), 1010 });        // Affichage des intervalles sur l'axe des abscisses
                    val_temp = lB.get_temp_annee(annee);
                    pos_point = CPoint{ 100 + (inter_annee * i) , (1000-(val_temp-11)*300) };                                   //Redéfinition de la position du point en fonction de la valeur de la température et de l'année
                    point = CRectangle{ pos_point, taille_point };                                                              //Redéfinition du rectangle englobant (modification de sa position)
                    libgraph->drawEllipse(point);                                                                               //Affichage du point
                    libgraph->setPen(rouge, 4.0f, LibGraph2::pen_DashStyles::Solid);
                    libgraph->drawLine(pos_point+centre_point, pos_point_pre+centre_point);                                     //Affichage d'un trait reliant le point actuel et la point précédent
                    moyenne_temp += val_temp;                                                                                   //Incrémentation de la valeur de la température actuel
                    annee++;                                                                                                    //Incrémentation de l'année
                    pos_point_pre = pos_point;                                                                                  //Redéfinition de la position du point précédent au point actuel
                }

                moyenne_temp /= 29;                                                                                             //Calcule de la valeur moyenne de la température sur les 30 années
                libgraph->setPen(vert, 5.0f, LibGraph2::pen_DashStyles::Dash);
                libgraph->drawLine(CPoint{ 158, 1000 - (moyenne_temp-11)*300 }, CPoint{ 1800,1000-(moyenne_temp-11)*300 });     //Affichage d'un trait correspondant à la moyenne de température

                libgraph->endPaint();
                break;
            }
            case VK_ESCAPE:
                exit(0);
                break;
            }
            break;
        case evt_type::evtMouseMove:
            break;
        }
    }
    ReleaseLibGraph2();
    return 0;
}

