/*************************************************************************
 Voyage  -  description
-------------------
début                : Novembre 2018
copyright            : Mathis Guilhin & Téo Bouvard
*************************************************************************/

//---------- Réalisation du module <Voyage> (fichier Voyage.cpp) ---------------

/////////////////////////////////////////////////////////////////  INCLUDE
//-------------------------------------------------------- Include système
#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

//------------------------------------------------------ Include personnel
#include "Voyage.h"
#include "Catalogue.h"
#include "TrajetSimple.h"
#include "TrajetCompose.h"
///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes
const int TAILLE_MAX_STRING = 20;
#define BIGNUMBER 999999
//------------------------------------------------------------------ Types
//---------------------------------------------------- Variables statiques

//------------------------------------------------------ Fonctions privées

static void sautDeLigne(ifstream *fic, string *lecture2, int nbLignes){
	for(int i = 0 ; i<nbLignes ; i++){
		getline(*fic,*lecture2);
	}
}
static void affichageMenu(){
  cout << "Afficher le catalogue : 0 | Ajouter un trajet : 1 | Rechercher un trajet : 2 | Rechercher un trajet (avancé) : 3 | Ajouter des trajets à partir d'un fichier : 4 | Creer une sauvegarde du catalogue : 5 | Quitter l'application : 9" << endl << endl;
}
static void affichageMenuAjout(){
    cout <<"Ajouter tous les trajets : 0 | Ajouter uniquement les trajets simples : 1 | Ajouter uniquement les trajets composés : 2 | Ajouter selon la ville de départ /d'arrivée : 3 | Ajouter un nombre de trajets définis : 4"<<endl<<endl ;
}
static void affichageMenuSauvegarde(){
cout <<"Sauvegarder tous les trajets : 0 | Sauvegarder uniquement les trajets simples : 1 |Sauvegarder uniquement les trajets composés : 2 | Sauvegarder selon la ville de départ / d'arrivée : 3 | Sauvegarder un nombre de trajets définis : 4"<<endl<<endl ;
}
static Trajet* creerTrajetSimple(){
  char* ville1 = new char[TAILLE_MAX_STRING];
  char* ville2 = new char[TAILLE_MAX_STRING];
  char* mdTransport = new char[TAILLE_MAX_STRING];
  
  cout << "Ville de départ ?"<< endl;
  cin >> ville1;
  cout << "Ville d'arrivée ?"<< endl;
  cin >> ville2;
  cout << "Mode de Transport ?"<< endl;
  cin >> mdTransport;
  
  Trajet* trajet = new TrajetSimple(ville1, ville2, mdTransport);
  
  delete [] ville1;
  delete [] ville2;
  delete [] mdTransport;
  
  return trajet;
}
static void creationTrajet(Collection * c, int option){
  if(option == 1){
    c->Ajouter(creerTrajetSimple());
  } else if(option == 2){
    int nEscales;
    cout << "Nombre d'escales ?" << endl;
    while(!(cin >> nEscales)){
      cin.clear();
      cin.ignore(BIGNUMBER, '\n');
      cout << "Entrée invalide. Réessayez" << endl;
    }
    Collection* collectionTrajets = new Collection;
    for(int i = 0 ; i < nEscales; i++){
      cout << "Escale n°" << i+1 << endl;
      //Le code commenté correspond à une autre version de l'application permettant de créer des trajets
      //composés dans lequels il y a des trajets composés. Nous avons ici utilisé la simplification
      //du cahier des charges
      /*cout << "Trajet simple : 1 | Trajet composé : 2" << endl;
      int choix;
      cin >> choix;
      creationTrajet(collectionTrajets,choix);*/
      creationTrajet(collectionTrajets,1);
    }
    
    //on vérifie que le trajet ajouté est valide
    bool valide = true;
    for(int i = 0; i < collectionTrajets->getNbElements() - 1; i++){
      if (strcmp(collectionTrajets->getElement(i)->getVille(1),collectionTrajets->getElement(i+1)->getVille(0)) != 0){
        valide = false;
      }
    }
    if (valide){
      TrajetCompose* trajet = new TrajetCompose(collectionTrajets);
      c->Ajouter(trajet);
      cout << "Trajet ajouté au catalogue" << endl;
    }
    else{
      cout << "Saisie de trajet non valide !" << endl;
      delete collectionTrajets;
    }
  }
}
static void ajoutTrajetSimple(Collection *c, ifstream *fic ,string *lecture2){
		char* ville1 = new char[TAILLE_MAX_STRING];
  		char* ville2 = new char[TAILLE_MAX_STRING];
  		char* modeTransport = new char[TAILLE_MAX_STRING];
  		strcpy(ville1,(*lecture2).c_str());
		sautDeLigne(fic,lecture2,1);
		strcpy(ville2,(*lecture2).c_str());
		sautDeLigne(fic,lecture2,1);
		strcpy(modeTransport,(*lecture2).c_str());
		Trajet* trajet = new TrajetSimple(ville1, ville2, modeTransport);
		c->Ajouter(trajet);	
		delete [] ville1;
		delete [] ville2;
		delete [] modeTransport;	  		
}
static void ajoutTrajetCompose(Collection *c, ifstream *fic ,string *lecture2){
	Collection* collectionTrajets = new Collection ;
	char *finTrajet  = new char[(*lecture2).length()+1];
	strcpy(finTrajet, (*lecture2).c_str());
	while(strcmp(finTrajet,"_")!=0){
		delete [] finTrajet;
		ajoutTrajetSimple(collectionTrajets,fic,lecture2);
		sautDeLigne(fic,lecture2,2);
		finTrajet  = new char[(*lecture2).length()+1];
		strcpy(finTrajet, (*lecture2).c_str());
	}
		delete [] finTrajet;  
		TrajetCompose* trajet = new TrajetCompose(collectionTrajets);
		c->Ajouter(trajet);
}
static void eviteTrajetCompose(ifstream *fic, string* lecture2){
   
	char *finTrajet  = new char[(*lecture2).length()+1];
	strcpy(finTrajet, (*lecture2).c_str());
	while(strcmp(finTrajet,"_")!=0){
		delete [] finTrajet;
		getline(*fic,*lecture2);
		finTrajet  = new char[(*lecture2).length()+1];
		strcpy(finTrajet, (*lecture2).c_str());
	}
	delete [] finTrajet;
}
static void lectureClavier(int *lect){
    while(!(cin >> *lect)){
    cin.clear();
    cin.ignore(BIGNUMBER, '\n');
    cout << "Entrée invalide. Réessayez" << endl;
  }
}
bool exists (string nom) {
    ifstream f(nom.c_str());
    return f.good();
}

int main(){
//---------------------------------------------------- Variables
//Il est necessaire de déclarer les variable ici car on ne peut pas déclarer une variable dans un loop
  int lecture;
  int lecture1;
  int nombreTrajets;
  int nombreTrajetsAct;
  int premierTrajet;
  int trajetActuel;
  char cheminAcces [100];
  ifstream fic;
  ofstream ofic;
  bool erase;
  char* ville1 = new char[TAILLE_MAX_STRING];
  char* ville2 = new char[TAILLE_MAX_STRING];
  char* modeTransport = new char[TAILLE_MAX_STRING];
  char* type;
  streambuf *oldCoutBuffer;
  string lecture2;
  string lectureVille;
  string lectureVille1;
  Catalogue catalogue;
  Collection c;

  cout << endl << "Bienvenue dans le Gestionnaire de Trajets" << endl << endl;
  affichageMenu();
  lectureClavier(&lecture);
  while(lecture != 9){
    
    switch (lecture){
    
        case 0 : //Affichage
        catalogue.AfficherCatalogue();
        break;
          
        case 1 : //Ajout
        cout << endl << "Trajet simple : 1 | Trajet composé : 2" << endl;
        cin >> lecture;
        creationTrajet(catalogue.getCollection(),lecture);
        break;
          
        case 2 : //Recherche Simple
        cout << "Ville de départ ?"<< endl;
        cin >> ville1;
        cout << "Ville d'arrivée ?"<< endl;
        cin >> ville2;
        cout << endl;
        catalogue.RechercherTrajet(ville1, ville2);
        catalogue.RaZ_nbOption();
        break;
          
        case 3 : //Recherche Avancee
        cout << "Ville de départ ?"<< endl;
        cin >> ville1;
        cout << "Ville d'arrivée ?"<< endl;
        cin >> ville2;
        cout << endl;
        catalogue.RechercherTrajetAvance(ville1, ville2,0,&c);
        catalogue.RaZ_nbOption();
        break;
          
        case 4 : //Chargement à partir d'un fichier
        affichageMenuAjout();
        lectureClavier(&lecture);      
        cout << "Veuillez entrer le chemin d'accès du fichier de sauvegarde" << endl;
        cin >> cheminAcces;
        cout << endl;
        fic.open(cheminAcces);
        if( (fic.rdstate () & ifstream::failbit ) !=0 )
        {
            cerr << "Erreur d'ouverture du fichier" << endl;
        } else 
        {
      	 	switch (lecture){
		
				case 0 : //Tous les trajets
                sautDeLigne(&fic,&lecture2,1);
                while(getline(fic,lecture2))
                {
                    type  = new char[lecture2.length()+1];
                    strcpy(type, lecture2.c_str());
                    if(strcmp(type,"S-")==0){ 
                        sautDeLigne(&fic,&lecture2,1);
                        ajoutTrajetSimple(catalogue.getCollection(), &fic ,&lecture2);
                    } else if(strcmp(type,"C-")==0){
                        sautDeLigne(&fic,&lecture2,4);
                        ajoutTrajetCompose(catalogue.getCollection(),&fic,&lecture2);
                    }
                    delete [] type;
                }
                fic.close();
                break;
		  		
		  		case 1: //Les trajets simples
		  		sautDeLigne(&fic,&lecture2,1);
				while(getline(fic,lecture2))
				{
					type  = new char[lecture2.length()+1];
					strcpy(type, lecture2.c_str());
					if(strcmp(type,"S-")==0){
						sautDeLigne(&fic,&lecture2,1);
			  			ajoutTrajetSimple(catalogue.getCollection(), &fic ,&lecture2);
					}else if(strcmp(type,"C-")==0){
						eviteTrajetCompose(&fic,&lecture2);
					}
					delete [] type;
				}
				fic.close();
		  		break;
		  		
		  		case 2 : //Les trajets composés
		  		sautDeLigne(&fic,&lecture2,1);
		    	while(getline(fic,lecture2))
				{
					type  = new char[lecture2.length()+1];
					strcpy(type, lecture2.c_str());
					if(strcmp(type,"C-")==0){
						sautDeLigne(&fic,&lecture2,4);
						ajoutTrajetCompose(catalogue.getCollection(),&fic,&lecture2);
					}
					delete [] type;
				}	
				fic.close();
		  		break;
		  		
		  		case 3 : //Selon ville départ et/ou arrivée
		  			
		   		cout << "Voulez vous rajouter un trajet selon  :" <<endl<< "0 : Sa ville de départ | 1 : Sa ville d'arrivée | 2: Les deux " << endl;
		   		lectureClavier(&lecture);
           		switch (lecture){
				
		    		case 0 : //Ville départ uniquement
		    		cout << "Veuillez entrer la ville de départ" <<endl;
		    		cin>>lectureVille;
			  		getline(fic,lecture2);
		      		while(getline(fic,lecture2))
			  		{
						type  = new char[lecture2.length()+1];
						strcpy(type, lecture2.c_str());
						if(strcmp(type,"S-")==0){
							sautDeLigne(&fic,&lecture2,1);
							//il faut comparer Ville 1 et la ville que l'utilisateur rentre
							if (lecture2.compare(lectureVille)==0){ 
							//Si ça correspond on fait la même chose que l'ajout classique sinon sauter le bon nombre de lignes
								ajoutTrajetSimple(catalogue.getCollection(), &fic ,&lecture2);
							}else{
								sautDeLigne(&fic,&lecture2,3);
							}
						}else if (strcmp(type,"C-")==0){
							sautDeLigne(&fic,&lecture2,1);
							if (lecture2.compare(lectureVille)==0){ 
							//Si ça correspond on fait la même chose que l'ajout classique sinon sauter le bon nombre de lignes
								sautDeLigne(&fic,&lecture2,3);
								ajoutTrajetCompose(catalogue.getCollection(), &fic ,&lecture2);
							}else{
								eviteTrajetCompose(&fic,&lecture2);
							}
						
						}
						
						delete [] type;
			  		}
			  		fic.close();
		    		break;
		    		
		    		case 1 : //Ville arrivée uniquement
		     		cout << "Veuillez entrer la ville d'arrivée" <<endl;
		    		cin>>lectureVille;
			  		getline(fic,lecture2);
		      		while(getline(fic,lecture2))
			  		{
						type  = new char[lecture2.length()+1];
						strcpy(type, lecture2.c_str());
						if(strcmp(type,"S-")==0){
							sautDeLigne(&fic,&lecture2,1);
							strcpy(ville1,lecture2.c_str());
							sautDeLigne(&fic,&lecture2,1);
							//il faut comparer Ville 1 et la ville que l'utilisateur rentre
							if (lecture2.compare(lectureVille)==0){ 
							//Si ça correspond on fait la même chose que l'ajout classique sinon sauter le bon nombre de lignes
								strcpy(ville2,lecture2.c_str());
								sautDeLigne(&fic,&lecture2,1);
								strcpy(modeTransport,lecture2.c_str());
								Trajet* trajet = new TrajetSimple(ville1, ville2, modeTransport);
								catalogue.getCollection()->Ajouter(trajet);									
							}else{
								sautDeLigne(&fic,&lecture2,2);
							}
						}else if (strcmp(type,"C-")==0){
							sautDeLigne(&fic,&lecture2,2);
							if (lecture2.compare(lectureVille)==0){ 
							//Si ça correspond on fait la même chose que l'ajout classique sinon sauter le bon nombre de lignes
								sautDeLigne(&fic,&lecture2,2);
								ajoutTrajetCompose(catalogue.getCollection(), &fic ,&lecture2);
							}else{
								eviteTrajetCompose(&fic,&lecture2);
							}						
						}						
						delete [] type;
					}
					fic.close();
					break;
					
					case 2 : //Ville départ et arrivée					
					cout << "Veuillez entrer la ville de départ" <<endl;
		    		cin>>lectureVille;					
		     		cout << "Veuillez entrer la ville d'arrivée" <<endl;
		    		cin>>lectureVille1;
			  		getline(fic,lecture2);			  		
		      		while(getline(fic,lecture2))
			  		{
						type  = new char[lecture2.length()+1];
						strcpy(type, lecture2.c_str());
						if(strcmp(type,"S-")==0){
							sautDeLigne(&fic,&lecture2,1);
							strcpy(ville1,lecture2.c_str());
							sautDeLigne(&fic,&lecture2,1);
							if ( strcmp(ville1,lectureVille.c_str())==0 && lecture2.compare(lectureVille1)==0){ 
							//Si ça correspond on fait la même chose que l'ajout classique sinon sauter le bon nombre de lignes
								strcpy(ville2,lecture2.c_str());
								sautDeLigne(&fic,&lecture2,1);
								strcpy(modeTransport,lecture2.c_str());
								Trajet* trajet = new TrajetSimple(ville1, ville2, modeTransport);
								catalogue.getCollection()->Ajouter(trajet);	
								
							}else{
								sautDeLigne(&fic,&lecture2,2);
							}
						}else if (strcmp(type,"C-")==0){
							sautDeLigne(&fic,&lecture2,1);
							strcpy(ville1,lecture2.c_str());
							sautDeLigne(&fic,&lecture2,1);
							if ( strcmp(ville1,lectureVille.c_str())==0 && lecture2.compare(lectureVille1)==0){ 
							//Si ça correspond on fait la même chose que l'ajout classique sinon sauter le bon nombre de lignes
								sautDeLigne(&fic,&lecture2,2);
								ajoutTrajetCompose(catalogue.getCollection(), &fic ,&lecture2);
							}else{
								eviteTrajetCompose(&fic,&lecture2);
							}						
						}						
						delete [] type;
					}
					fic.close();
					break;
					
            		default :
		      		cout << "Entrée invalide. Réessayez" << endl;
            		break;
		   		}		   		
		  		break ;
		  		
		  		case 4 : //Selon un nombre de trajets		  		
		  		cout << "Selectionnez le nombre de trajets à ajouter" << endl;		  		
		  		lectureClavier(&nombreTrajets);          		
          		cout << "Selectionnez le numéro du premier trajet" << endl;          		
          		lectureClavier(&premierTrajet);
          		premierTrajet--;
          		trajetActuel = premierTrajet;          		
          		sautDeLigne(&fic,&lecture2,1);
          		nombreTrajetsAct = stoi(lecture2);
          		if(premierTrajet+1>nombreTrajetsAct){
          			cout << "Le premier trajet rentré n'existe pas" << endl;
          		} else {          
          			for(int i = 0; i<premierTrajet+1;i++){
          				getline(fic,lecture2);
          				type  = new char[lecture2.length()+1];
						strcpy(type, lecture2.c_str());
						if(strcmp(type,"S-")==0){
							sautDeLigne(&fic,&lecture2,4);
						} else if(strcmp(type,"C-")==0){
							eviteTrajetCompose(&fic,&lecture2);
						}
						delete [] type;
					}          		
          			while(getline(fic,lecture2) && trajetActuel < (nombreTrajets + premierTrajet))
		  			{
						type  = new char[lecture2.length()+1];
						strcpy(type, lecture2.c_str());
						if(strcmp(type,"S-")==0){
			  				sautDeLigne(&fic,&lecture2,1);
			  				ajoutTrajetSimple(catalogue.getCollection(), &fic ,&lecture2);
						} else if(strcmp(type,"C-")==0){
							sautDeLigne(&fic,&lecture2,4);
			  				ajoutTrajetCompose(catalogue.getCollection(),&fic,&lecture2);
						}
						sautDeLigne(&fic,&lecture2,1);
						delete [] type;
						trajetActuel++;
		  			}		  			
		  		}
		  		fic.close();          		
          		break;
           		
		  		default :
		    		cout << "Entrée invalide. Réessayez" << endl;
          		break;
				}
		}
      break;
      
    case 5 : //Sauvegarde    
    affichageMenuSauvegarde();
    lectureClavier(&lecture);
    cout << "Veuillez entrer le chemin d'accès" << endl;
    cin >> cheminAcces;
    erase = false;
    while( exists(cheminAcces) && !erase) //Teste si un fichier du même nom existe
    {
        cout << "Ce fichier existe déjà. Voulez vous : Renommer votre fichier : 0 | Ecraser le fichier du même nom : 1" << endl;
        lectureClavier(&lecture1); 
        if(lecture1==0){
            cout << "Veuillez saisir le nouveau chemin d'accès de votre fichier" << endl;
            cin >> cheminAcces;
        } else if(lecture1==1){
            erase = true;
        }
    }
    ofic.open(cheminAcces);
    switch (lecture){	
        case 0 :  //Tous les trajets
        oldCoutBuffer = cout.rdbuf(ofic.rdbuf());			  
        catalogue.getCollection()->AfficherCollectionFormat();			  
        cout.rdbuf(oldCoutBuffer);
        ofic.close();
        break;
            
        case 1 : //Les trajets simples
        oldCoutBuffer = cout.rdbuf(ofic.rdbuf());		  
        catalogue.getCollection()->AfficherTrajetsSimples();
        cout.rdbuf(oldCoutBuffer);
        ofic.close();
        break;
           
        case 2 : //Les trajets composés
        oldCoutBuffer = cout.rdbuf(ofic.rdbuf());		  
        catalogue.getCollection()->AfficherTrajetsComposes();
        cout.rdbuf(oldCoutBuffer);
        ofic.close();
        break;
            
        case 3 : //Selon la ville de départ et/ou d'arrivée
        cout << "Voulez vous enregistrer un trajet selon  :" << endl << "Sa ville de départ : 0 | Sa ville d'arrivée : 1 | Les deux : 2 "<<endl;
        lectureClavier(&lecture);            
        switch (lecture){
            case 0 : //Ville départ uniquement
            cout << "Veuillez entrer la ville de départ" <<endl;
            cin>>lectureVille;
            strcpy(ville1, lectureVille.c_str());
            oldCoutBuffer = cout.rdbuf(ofic.rdbuf());
            catalogue.getCollection()->AfficherTrajetsDepart(ville1);
            cout.rdbuf(oldCoutBuffer);
            ofic.close();
            break;
            case 1 : //Ville d'arrivée uniquement
            cout << "Veuillez entrer la ville d'arrivée" <<endl;
            cin>>lectureVille;
            strcpy(ville2, lectureVille.c_str());
            oldCoutBuffer = cout.rdbuf(ofic.rdbuf());
            catalogue.getCollection()->AfficherTrajetsArrivee(ville2);
            cout.rdbuf(oldCoutBuffer);
            ofic.close();
            break;
            case 2 : // Ville de départ et d'arrivée
            cout << "Veuillez entrer la ville de départ" <<endl;
            cin>>lectureVille;
            strcpy(ville1, lectureVille.c_str());
            cout << "Veuillez entrer la ville d'arrivée" <<endl;
            cin>>lectureVille1;
            strcpy(ville2, lectureVille1.c_str());
            oldCoutBuffer = cout.rdbuf(ofic.rdbuf());
            catalogue.getCollection()->AfficherTrajetsDepartArrivee(ville1,ville2);
            cout.rdbuf(oldCoutBuffer);
            ofic.close();
            break;
        }		  
        break ;
            
        case 4 : //Selon un nombre de trajets définis
        cout << "Selectionnez le nombre de trajets à sauvegarder" << endl;		  		
        lectureClavier(&nombreTrajets);          		
        cout << "Selectionnez le numéro du premier trajet" << endl;          		
        lectureClavier(&premierTrajet);
        premierTrajet--; //Permet à l'utilisateur de ne pas manier le trajet 0 (non intuitif)
        if((premierTrajet>=catalogue.getCollection()->getNbElements())){
            cout << "Ce trajet n'existe pas!"<< endl;
        } else {
            oldCoutBuffer = cout.rdbuf(ofic.rdbuf());
            catalogue.getCollection()->AfficherNbCollectionFormat(nombreTrajets, premierTrajet);
            cout.rdbuf(oldCoutBuffer);
            ofic.close();
        }
        break;
            
        default :
        cout << "Entrée invalide. Réessayez" << endl;
        break;    
    }
    break;
    
    
    default :
      cout << "Entrée invalide. Réessayez" << endl;
    break;    
    }    
    affichageMenu();
    lectureClavier(&lecture);
  }  
  cout << "Au revoir !" << endl << endl;  
  delete [] ville1;
  delete [] ville2;
  delete [] modeTransport;    
  return 0;
}
