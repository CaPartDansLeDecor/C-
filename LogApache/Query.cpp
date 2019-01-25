/*************************************************************************
 Query  -  Lance les appels en fonction des options
 -------------------
 début                : 18/01/2019
 copyright            : 3IF - LERANDY Emmy & GUILHIN Mathis
 e-mail               : emmy.lerandy@insa-lyon.fr - mathis.guilhin@insa-lyon.fr
 *************************************************************************/

//---------- Réalisation de la classe <Query> (fichier Query.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
#include <map>
#include <stdbool.h>
using namespace std;

//------------------------------------------------------ Include personnel
#include "Interface.h"
#include "Query.h"

//#include "Logline.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
void Query::run ()
// Algorithme :
//
{
  if(options[0]){
    printTop10();
  }
} //----- Fin de Méthode

void Query::printTop10 ()
  // Algorithme :
  //
{
  map<string,int> toBeRanked;
  
} //----- Fin de Méthode

void Query::afficher(){
  printf("%s\r\n%s\r\n",dotFile.c_str(),logFile.c_str());
}



//------------------------------------------------- Surcharge d'opérateurs
/*Query & Query::operator = ( const Query & unQuery )
// Algorithme :
//
{
} //----- Fin de operator = */


//-------------------------------------------- Constructeurs - destructeur
/*Query::Query ( const Query & unQuery )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de copie de <Query>" << endl;
#endif
} //----- Fin de Query (constructeur de copie) */


Query::Query (bool opt[4],  string nomFic1,  string nomFic2, Date d )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <Query>" << endl;
#endif
  
  for(int i = 0; i < 4 ; i++){
    options[i]=opt[i];
  }
  dotFile = nomFic1;
  logFile = nomFic2;
  date = d;
  afficher();
  //run();
  
} //----- Fin de Query


Query::~Query ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <Query>" << endl;
#endif
} //----- Fin de ~Query


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

