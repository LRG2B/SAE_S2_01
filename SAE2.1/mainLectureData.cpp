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
	//std::cout << myStations.nbMonths() << "\n";
	ListeStation lB = myStations.getListeStation();
	//lB.affiche_liste();

	std::vector<std::string> nameMonth = { "Janvier", "Fevrier", "Mars", "Avril", "Mai", "Juin", "Juillet",
	"Aout", "Septembre", "Octobre", "Novemebre", "Decembre" };

    auto beeeeeuuuute =  lB.get_temp_annee(2000);

    CSize resolution{ 1920, 1080 };
    CPoint pos_txt{ 0, 0 };

    //Définition des couleurs
    auto noir = MakeARGB(255, 0, 0, 0);
    auto blanc = MakeARGB(255, 255, 255, 255);

    auto inter = 100;

    CSize taille_point{ 20,20 };
    CPoint pos_point{ 200, 500 };
    CRectangle point{ pos_point, taille_point };

	//Récupération de l'objet principal de LibGraph 2
	ILibGraph2* libgraph = GetLibGraph2();
	//Affiche la fenêtre graphique avec une taille_rec par défaut
	libgraph->show(resolution, true);
	evt e;  //Evénement LibGraph 2

    //Boucle principale d'événements
    while (libgraph->waitForEvent(e))
    {
        switch (e.type)  //En fonction du type d'événement
        {
        case evt_type::evtRefresh:  //Raffraichissement de l'affichage (tout redessiner)
          //Utiliser éventuellement les fonctions libgraph->beginPaint() / libgraph->endPaint() pour activer le backbuffer
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

            //libgraph->setFont("Segoe UI", 40, font_styles::FontStyleRegular);
            //libgraph->setSolidBrush(noir);
            //libgraph->drawString(CString{"OUI"}, pos_txt);

            //------------------------Affichage-des-intervalles
            for (float i = 1; i <= 8; i++)
            {
                libgraph->drawLine(CPoint{ 90 ,1000 - (inter * i) }, CPoint{ 110, 1000 - (inter * i) });
            }
            for (float i = 1; i <= 16; i++)
            {
                libgraph->drawLine(CPoint{ 100 + (inter * i), 990 }, CPoint{ 100 + (inter * i), 1010 });
                //libgraph->drawString(annee, CPoint{100 + (inter * i), 990});
                //annee += 1;
            }

            libgraph->drawEllipse(point);
            //point = { CPoint{300,400}, taille_point };
            //libgraph->drawEllipse(point);
            //libgraph->setPen(noir, 2.0f, LibGraph2::pen_DashStyles::Solid);
            libgraph->drawLine(pos_point, CPoint{ 300,400 });

            //libgraph->drawLine(CPoint{ 90, 1010 }, CPoint{ 110, 990 });

            //Affichage du texte de fermeture
            /*libgraph->setFont("Consolas" , 20 , font_styles::FontStyleRegular);
            libgraph->setSolidBrush(noir);
            libgraph->drawString(txt_quit, pos_txt);*/

            libgraph->endPaint();
            break;

        case evt_type::evtKeyDown:  //Enfoncement d'une touche
            switch (e.vkKeyCode) //En fonction de la touche enfoncée
            {
            case VK_ESCAPE:
                exit(0);
                break;
            }
            break;

        case evt_type::evtMouseMove:  //Déplacement de la souris
          //Position de la souris dans les variables e.x et e.y
            break;
        }
    }

    //Libération de l'objet principal de LibGraph 2
    ReleaseLibGraph2();
    return 0;
}

