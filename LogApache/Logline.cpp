/*************************************************************************
 Logline  -  Contient les données d'une ligne d'un fichier log'
 -------------------
 début                : 18/01/2019
 copyright            : 3IF - LERANDY Emmy & GUILHIN Mathis
 e-mail               : emmy.lerandy@insa-lyon.fr - mathis.guilhin@insa-lyon.fr
 *************************************************************************/

//---------- Réalisation de la classe <Logline> (fichier Logline.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
#include <cctype>
#include <string>
#include <string.h>

using namespace std;

//------------------------------------------------------ Include personnel
#include "Interface.h"
#include "Logline.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
// type Logline::Méthode ( liste des paramètres )
// Algorithme :
//
//{
//} //----- Fin de Méthode

void Logline::AfficheLigne (  )
// Algorithme :
//
{
   cout<< "Date : "<<date.heure<<":"<<date.minutes<<endl<<"Referer : "<<referer<<endl<<"URL : "<<url<<endl;
} //----- Fin de AfficheLigne
//------------------------------------------------- Surcharge d'opérateurs

/*Logline & Logline::operator = ( const Logline & unLogline )
// Algorithme :
//
{
} //----- Fin de operator = */


//-------------------------------------------- Constructeurs - destructeur
/*Logline::Logline ( const Logline & unLogline )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de copie de <Logline>" << endl;
#endif
} //----- Fin de Logline (constructeur de copie)
*/

Logline::Logline (string ligne)
  

// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <Logline>" << endl;
#endif
  
  //Heure
  
  int i = 0;
  while(ligne.at(++i)!=':'){}
  date.heure = atoi(&ligne[++i]);
  //Minutes
  
  ++(++i);
  date.minutes = atoi(&ligne[++i]);
  
  //URL
  while(ligne.at(++i)!='"'){}
  while(ligne.at(++i)!=' '){}

  int j =0;
  int former_i = i;
  while(ligne.at(++i)!=' '){
    j++;
  }

  url = ligne.substr(former_i,j+1);
  
  //Referer
  while(ligne.at(++i)!='"'){}
  while(ligne.at(++i)!='"'){}

  j = 0;
  former_i = i;
  while(ligne.at(++i)!=' '){
    j++;
  }
  referer = ligne.substr(former_i,j+1);

  
  #ifdef MAP
  cout<< "date.heure "<< date.heure <<endl;
  cout<< "date.minutes "<< date.minutes <<endl;
  cout<< "URL "<< url <<endl;
  cout<< "referer "<< referer <<endl;
  #endif
  
  
 
} //----- Fin de Logline


Logline::~Logline ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <Logline>" << endl;
#endif
} //----- Fin de ~Logline


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

