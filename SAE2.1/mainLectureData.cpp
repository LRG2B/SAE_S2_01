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

	auto noir = MakeARGB(255, 0, 0, 0);
	auto blanc = MakeARGB(255, 255, 255, 255);
	//CStrin		ListeStation::get_temp_annee retourné	12.5083351	float
g txt_quit = "ytujytytjy";

	CPoint position_rec{ 100,100 };
	CSize taille_rec{ 1700, 900 };
	CRectangle beute{ position_rec, taille_rec };

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

            libgraph->setPen(noir, 5.0f, LibGraph2::pen_DashStyles::Solid);
            libgraph->setSolidBrush(blanc);
            libgraph->drawRectangle(beute);

            //libgraph->setFont("Consolas" , 20 , font_styles::FontStyleRegular);
            libgraph->setSolidBrush(noir);
            //libgraph->drawString(txt_quit, pos_txt);

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

