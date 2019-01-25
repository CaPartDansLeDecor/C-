 /*************************************************************************
                           Logline  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <Logline> (fichier Logline.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
using namespace std;

//------------------------------------------------------ Include personnel
#include "Logline.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
// type Logline::Méthode ( liste des paramètres )
// Algorithme :
//
//{
//} //----- Fin de Méthode

 Logline::AfficheLigne (  )
// Algorithme :
//
{
   cout<< "Date : "<<date.heure<<":"<<date.minutes<<endl<<"Referer : "<<referer<<endl<<"URL"<<url<<endl;
} //----- Fin de AfficheLigne
//------------------------------------------------- Surcharge d'opérateurs
Logline & Logline::operator = ( const Logline & unLogline )
// Algorithme :
//
{
} //----- Fin de operator =


//-------------------------------------------- Constructeurs - destructeur
Logline::Logline ( const Logline & unLogline )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de copie de <Logline>" << endl;
#endif
} //----- Fin de Logline (constructeur de copie)


Logline::Logline (string ligne)
  

// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <Logline>" << endl;
#endif
  
  int i=0;
  while(ligne[i++]!=':'){
  }
  date.heure = atoi(ligne[i]);
  ++(++i);
  date.minutes = atoi(ligne[++i]);
  while(ligne[i++]!='"'){
  }
  while(ligne[i++]!=' '){
  }
  int j=0;
  while(ligne[i]!='"'){
    url[j++]=ligne[i++];
  }
  while(ligne[i++]!='"'){
  }
  while(ligne[i]!='"'){
    referer[j++]=ligne[i++];
  }
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

