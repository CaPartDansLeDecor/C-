/*************************************************************************
                           Logline  -  Contient les données d'une ligne d'un fichier log'
                             -------------------
    début                : 18/01/2019
    copyright            : 3IF - LERANDY Emmy & GUILHIN Mathis
    e-mail               : emmy.lerandy@insa-lyon.fr - mathis.guilhin@insa-lyon.fr
*************************************************************************/

//---------- Interface de la classe <Logline> (fichier Logline.h) ----------------
#if ! defined ( Logline_H )
#define Logline_H
//--------------------------------------------------- Interfaces utilisées
using namespace std;
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Logline>
//
//
//------------------------------------------------------------------------

class Logline
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    // type Méthode ( liste des paramètres );
    // Mode d'emploi :
    //
    // Contrat :
    //
    
void    AfficheLigne ();
    // Mode d'emploi :
    //
    // Contrat :
    //
    

//------------------------------------------------- Surcharge d'opérateurs
    //Logline & operator = ( const Logline & unLogline );
    // Mode d'emploi :
    //
    // Contrat :
    //


//-------------------------------------------- Constructeurs - destructeur
    //Logline ( const Logline & unLogline );
    // Mode d'emploi (constructeur de copie) :
    //
    // Contrat :
    //

    Logline (string ligne);
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~Logline ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
  string url, referer;
  Date date;
  friend class Query;
};

//-------------------------------- Autres définitions dépendantes de <Logline>

#endif // LOGLINE_H

