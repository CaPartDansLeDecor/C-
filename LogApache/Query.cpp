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
#include <string.h>
#include <algorithm>
#include <fstream> 
using namespace std;

//------------------------------------------------------ Include personnel
#include "Interface.h"
#include "Query.h"
#include "Logline.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

template<typename A, typename B>
std::pair<B,A> flip_pair(const std::pair<A,B> &p)
{
  return std::pair<B,A>(p.second, p.first);
}

template<typename A, typename B>
std::multimap<B,A> flip_map(const std::map<A,B> &src)
{
  std::multimap<B,A> dst;
  std::transform(src.begin(), src.end(), std::inserter(dst, dst.begin()), ::flip_pair<A,B>);
  return dst;
}

void Query::run ()
// Algorithme :
//
{
  printTop10();
  if(options[3]){
    //Traitement Heure
  } 
   
} //----- Fin de Méthode

void Query::printTop10 ()
  // Algorithme :
  //
{
  map<string,int> toBeRanked;
  std::map<string,int>::iterator it;
  ifstream ifLog ;
  ifLog.open(logFile);
  string s;
  if(ifLog)
  {
    
    while(getline(ifLog,s)){
      Logline logAct = Logline(s);
      bool valide = true;
      if(options[2]){
        if(logAct.url.find(".css")!=std::string::npos){
          valide = false;
        }
      }
      if(options[3]){
        
      } 
      if(valide){
        it = toBeRanked.find(logAct.url);
        if(it==toBeRanked.end()){
          toBeRanked.insert(make_pair(logAct.url,1));
        } else {
          (*it).second += 1;
        }
      }
    }
    multimap<int,string> top10;
    top10 = flip_map(toBeRanked);
    std::multimap<int,string>::reverse_iterator ri = top10.rbegin();
    int i = 1;
    do {
      cout << i++ << " : " << (*ri).second << " : " << (*ri).first << " hits" << endl;
    } while(i<=10 && (++ri)!=top10.rend()) ;
  } else
  {
    cerr << "Erreur d'ouverture du fichier" << endl;
  }
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
  run();
  
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

