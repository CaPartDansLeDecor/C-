/*************************************************************************
 Query  -  Lance les appels en fonction des options
 -------------------
 début                : 18/01/2019
 copyright            : 3IF - LERANDY Emmy & GUILHIN Mathis
 e-mail               : emmy.lerandy@insa-lyon.fr - mathis.guilhin@insa-lyon.fr
 *************************************************************************/

//---------- Interface de la classe <Query> (fichier Query.h) ----------------
#if ! defined ( Query_H )
#define Query_H

//--------------------------------------------------- Interfaces utilisées

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types
typedef struct url_referer{
  string url;
  string referer;
} url_referer;

//------------------------------------------------------------------------
// Rôle de la classe <Query>
//
//
//------------------------------------------------------------------------

class Query
{
  
    
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    // type Méthode ( liste des paramètres );
    // Mode d'emploi :
    //
    // Contrat :
    //
    
  void run();
    // Mode d'emploi :
    //
    // Contrat :
    //

  void printTop10();
    // Mode d'emploi :
    //
    // Contrat :
    //
    
//------------------------------------------------- Surcharge d'opérateurs
    //Query & operator = ( const Query & unQuery );
    // Mode d'emploi :
    //
    // Contrat :
    //


//-------------------------------------------- Constructeurs - destructeur
    //Query ( const Query & unQuery );
    // Mode d'emploi (constructeur de copie) :
    //
    // Contrat :
    //

    Query (bool opt[4], string nomFic1="", string nomFic2="", Date d ={0,0});
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~Query ( );
    // Mode d'emploi :
    //
    // Contrat :
    //
    
    void afficher();

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
  bool options [4];
  string dotFile;
  string logFile;
  Date date;

};

//-------------------------------- Autres définitions dépendantes de <Query>

#endif // XXX_H

