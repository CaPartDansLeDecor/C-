/*************************************************************************
Collection  -  description
-------------------
début                : Novembre 2018
copyright            : Mathis Guilhin & Téo Bouvard
*************************************************************************/

//---------- Réalisation de la classe <Collection> (fichier Collection.cpp) ------------

//---------------------------------------------------------------- INCLUDE
//-------------------------------------------------------- Include système
#include <iostream>
#include <typeinfo>
#include <cstring>
using namespace std;
//------------------------------------------------------ Include personnel
#include "Collection.h"
#define underline "\033[4m"
#define stopunderline "\033[0m"
//------------------------------------------------------------- Constantes
const int TAILLE_INITIALE = 1; //doit être différent de 0 pour Resize()
//----------------------------------------------------------------- PUBLIC
//----------------------------------------------------- Méthodes publiques
void Collection::Resize()
{
	int newSize = 2*nbElementsMax;
	Trajet** resized_arr = new Trajet* [newSize];

	for(int i = 0; i < nbElementsMax; i++){
		resized_arr[i] = elements[i];
	}
	nbElementsMax = newSize;

	delete[] elements;
	elements = resized_arr;
}

void Collection::AfficherCollection() const
{
	for (int i = 0; i < nbElements; i++){
		cout << "\t" << underline <<"Trajet " << i + 1 << stopunderline << endl;
		elements[i]->Afficher();
		cout << endl;
	}
}

void Collection::AfficherCollectionFormat() const
{
  cout << nbElements <<  endl;
  for (int i = 0; i < nbElements; i++){
    elements[i]->AfficherFormat();
    cout << endl;
  }
}

void Collection::AfficherNbCollectionFormat(int nbTrajets, int premierTrajet) const
{
  int nbElementsAjoutes = 0;
  int i = premierTrajet;
  while(i< premierTrajet + nbTrajets && i <nbElements){
   	nbElementsAjoutes++;
   	i++;
  }
  cout << nbElementsAjoutes << endl;
  i = premierTrajet;
  while(i< premierTrajet + nbTrajets && i <nbElements){
   	elements[i++]->AfficherFormat();
   	cout << endl;
  }
    
}

void Collection::AfficherTrajetsSimples() const
{
  int nbTrajetSimple = 0;
  for (int i = 0; i < nbElements; i++){
	if(strcmp(typeid(* elements[i]).name(),"12TrajetSimple")==0){
	  nbTrajetSimple++;
	}
  }
  cout << nbTrajetSimple <<  endl;
  for (int i = 0; i < nbElements; i++){
	if(strcmp(typeid(* elements[i]).name(),"12TrajetSimple")==0){
	  elements[i]->AfficherFormat();
	  cout << endl << endl;
	}
  }

}

void Collection::AfficherTrajetsComposes() const
{
  int nbTrajetCompose = 0;
  for (int i = 0; i < nbElements; i++){
	if(strcmp(typeid(* elements[i]).name(),"13TrajetCompose")==0){
	  nbTrajetCompose++;
	}
  }
  cout << nbTrajetCompose <<  endl;
  for (int i = 0; i < nbElements; i++){
	if(strcmp(typeid(* elements[i]).name(),"13TrajetCompose")==0){
	  elements[i]->AfficherFormat();
	  cout << endl << endl;
	}
  }

}

void Collection::AfficherTrajetsDepart(char* villeDepart) const
{
    int nbTrajetAjoute = 0;
    for (int i = 0; i < nbElements; i++){
        if(strcmp(villeDepart,elements[i]->getVille(0))==0){
        nbTrajetAjoute++;
        }
    }
    cout << nbTrajetAjoute <<  endl;
    for (int i = 0; i < nbElements; i++){
        if(strcmp(villeDepart,elements[i]->getVille(0))==0){
          elements[i]->AfficherFormat();
        }
    }
}

void Collection::AfficherTrajetsArrivee(char* villeArrivee) const
{
    int nbTrajetAjoute = 0;
    for (int i = 0; i < nbElements; i++){
        if(strcmp(villeArrivee,elements[i]->getVille(1))==0){
        nbTrajetAjoute++;
        }
    }
    cout << nbTrajetAjoute <<  endl;
    for (int i = 0; i < nbElements; i++){
        if(strcmp(villeArrivee,elements[i]->getVille(1))==0){
            elements[i]->AfficherFormat();
        }
    }
}

void Collection::AfficherTrajetsDepartArrivee(char* villeDepart, char* villeArrivee) const
{
    int nbTrajetAjoute = 0;
    for (int i = 0; i < nbElements; i++){
        if(strcmp(villeArrivee,elements[i]->getVille(1))==0 && strcmp(villeDepart,elements[i]->getVille(0))==0){
        nbTrajetAjoute++;
        }
    }
    cout << nbTrajetAjoute << endl;
    for (int i = 0; i < nbElements; i++){
        if(strcmp(villeArrivee,elements[i]->getVille(1))==0 && strcmp(villeDepart,elements[i]->getVille(0))==0){
            elements[i]->AfficherFormat();
        }
    }
}

Trajet* Collection::getElement(int i) const
{
	return elements[i];
}

int Collection::getNbElements() const
{
	return nbElements;
}

void Collection::Ajouter(Trajet * t)
{
	//ajout d'un nouveau trajet si la taille le permet
	if (nbElements < nbElementsMax){
		elements[nbElements++] = t;
	}
	//sinon redimensionnement du tableau dynamique
	else{
		Collection::Resize();
		elements[nbElements++] = t;

		#ifdef MAP2
		cout << "Nouveau nbElements " << nbElements << endl;
		cout << "Nouveau nbElementsMax " << nbElementsMax << endl;
		#endif
	}
}

Collection* Collection::cloneCollection() const{
	Collection* c = new Collection;
	for (int i = 0; i < nbElements; i++){
		c->Ajouter(elements[i]->clone());
	}
	return c;
}

//-------------------------------------------- Constructeurs - destructeur
Collection::Collection ()
{
	nbElements = 0;
	elements = new Trajet* [TAILLE_INITIALE];
	nbElementsMax = TAILLE_INITIALE;
	#ifdef MAP
	cout << "Appel au constructeur de <Collection>" << endl;
	#endif
} //----- Fin de Collection

Collection::~Collection ()
{
	for (int i = 0; i < nbElements; i++){
		delete elements[i];
	}
	delete [] elements;
	#ifdef MAP
	cout << "Appel au destructeur de <Collection>" << endl;
	#endif

}//----- Fin de ~Collection
