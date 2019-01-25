/*************************************************************************
                           Logline  -  Contient les données d'une ligne d'un fichier log'
                             -------------------
    début                : 18/01/2019
    copyright            : 3IF - LERANDY Emmy & GUILHIN Mathis
    e-mail               : emmy.lerandy@insa-lyon.fr - mathis.guilhin@insa-lyon.fr
*************************************************************************/

//---------- Interface de la classe <Logline> (fichier Logline.h) ----------------
#if ! defined ( LOGLINE_H )
#define LOGLINE_H

//--------------------------------------------------- Interfaces utilisées

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types
typedef struct Date{
  int heure;
  int minutes;
} Date;
//------------------------------------------------------------------------
// Rôle de la classe <Logline>
//
//
//------------------------------------------------------------------------

class Logline :
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    // type Méthode ( liste des paramètres );
    // Mode d'emploi :
    //
    // Contrat :
    //
    
    AfficheLigne ( );
    // Mode d'emploi :
    //
    // Contrat :
    //
    

//------------------------------------------------- Surcharge d'opérateurs
    Logline & operator = ( const Logline & unLogline );
    // Mode d'emploi :
    //
    // Contrat :
    //


//-------------------------------------------- Constructeurs - destructeur
    Logline ( const Logline & unLogline );
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
};

//-------------------------------- Autres définitions dépendantes de <Logline>

#endif // LOGLINE_H

