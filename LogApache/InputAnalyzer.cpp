#include <stdio.h>
#include <math.h>
#include <cctype>
#include <stdbool.h>
#include <stdint.h>
#include <map>
#include <iostream>
#include <string.h>
#include "Interface.h"
#include "Logline.h"
#include "Query.h"


using namespace std;
void inputAnalyzer();
void afficherOption(bool options[4],char* dotName, char* logName, Date date);
void insertInto(char* toBeFilled, string::iterator* it, string* s,bool* error,bool* options, int option);
void errorOpt(bool* error);
void Annonce();
bool checkDate(string date);
void errorOpt2(bool* error);
void runRequest(bool options[4], string f1, string f2, Date d);


int main(){
	
	Annonce();
	inputAnalyzer();
	/*string s="192.168.0.0 - - [08/Sep/2012:11:16:02 +0200] \"GET /temps/4IF16.html HTTP/1.1\" 200 12106 \"http://intranet-if.insa-lyon.fr/temps/4IF15.html\" \"Mozilla/5.0 (Windows NT 6.1; WOW64; rv:14.0) Gecko/20100101 Firefox/14.0.1\"";
	Logline l1(s);
	l1.AfficheLigne();*/
	return 0;
}

void inputAnalyzer(){
	
	int taille = 100;
	string s;
	getline(cin,s);
	char* dotName = new char[taille];
	char* logName = new char[taille];
	char* heure = new char[taille];
	Date date;
	
	bool options[4]={0,0,0,0};
	string::iterator it = s.begin();
	int i;
	bool end = false;
	bool error = false;
	while(!end){ //Permet de sortir de l'application quand l'utilisateur rentre quit 
		while(strcmp(s.c_str(),"quit")!=0 && (s.find("$./analog ",0)!=0 || strlen(s.c_str())<15)){ //Boule tant que la syntaxe de la commande n'est pas correcte
			printf("Invalid input. Syntax : $./analog [-g FileName.dot] [-e] [-t time] FileName.log\r\n");
			printf("To quit : quit\r\n\r\n");
			getline(cin,s);
			printf("\r\n");
		}
		printf("\r\n");
		
		//Initialisation des options et de l'itérateur
		memset(heure, 0,taille);
		memset(logName, 0,taille);
		memset(dotName, 0,taille);
		date.heure = 0;
		date.minutes = 0;
		for(int i = 0; i<4 ; i++){
			options[i]=0;
		}
		it = s.begin();
		error = false;
		
		if(strcmp(s.c_str(),"quit")!=0){
			options[0]=1;
			while(s.find(" -")!=string::npos && error == false){ //Boucle pour chercher les options
				it = s.begin();
				while(*it != '-' && it != s.end()){
					++it;
				}
				*it = '_'	; //Permet de masquer les options déja traitées pour les recherches suivantes
				switch (*(++it)){
				  case 'g':
					insertInto(dotName,&it,&s,&error, options,1);
					break;
					
					case 'e' :
					options[2]=1; 
					break;
					
					case 't' :
					insertInto(heure,&it,&s,&error,options,3);
					if(!checkDate(heure)){
					    errorOpt2(&error);
					} else {
					  date.heure = atoi(&heure[0]);
					  date.minutes = atoi(&heure[3]);
					}
					break;
				}
				
			}
			
			//Fait avancer l'itérateur jusqu'au nom du fichier log
			while(*it != ' ' && it != s.end() && error == false){
				++it;
			}
			
			it++;
			
			//Copie le nom de fichier log
			i = 0;
			while(it != s.end() && error == false){
				logName[i++]=*(it++);
			}
			
			if(!error){
				afficherOption(options, dotName, logName, date);
			  runRequest(options,dotName,logName,date);
			} else {
				printf("Cannot execute request\r\n\r\n");
			}
			
			getline(cin,s);
		} else {
			end = true;
		}
	}
	//$./analog
}

//Permet de savoir quelles fonctions vont être appellées avec quels paramètres en fonction de l'entrée 
// dans la ligne de cmd
void afficherOption(bool options[4],char* dotName, char* logName, Date date){
	if(options[0]){
		printf("Top 10 of %s\r\n", logName);
	}
	if(options[1]){
		printf("Graph with ficName = %s\r\n",dotName);
	} 
	if(options[2]){
		printf("No Javascript, img and css\r\n");
	}
	if(options[3]){
		printf("Hits in [%d:%d,%d:%d]\r\n",date.heure,date.minutes,date.heure > 22 ?0:date.heure+1,date.minutes);
	}
	printf("\r\n");
}

void runRequest(bool options[4], string f1, string f2, Date d){
  Query q = Query(options,f1,f2,d);
}

void insertInto(char* toBeFilled, string::iterator* it, string* s, bool* error, bool* options,int option){
  if(*(++(++(*it)))!='-'){ //Permet de verifier l'utilisateur n'a pas oublié la cible
    options[option]=1;
    int i = 0;
    while(*(*it)!= ' ' && (*it) != s->end()){
      toBeFilled[i++]=*(*it);
      *(*it) = '_';
      (*it)++;
    }
    if(*it== s->end()){
      errorOpt(error);
    }
  } else {
    errorOpt(error);
  }
	
}

void errorOpt(bool* error){
	printf("missing target on option\r\n\r\n");
	*error = true;
}

void errorOpt2(bool* error){
  printf("Wrong time format. XX:XX\r\n\r\n");
  *error = true;
}

bool checkDate(string date_test){
  bool ans = true;
  if(date_test.length()!=5 || !isdigit(date_test[0]) || !isdigit(date_test[1]) || date_test[2]!=':' || !isdigit(date_test[3]) || !isdigit(date_test[4])){
    ans = false;
    
  }
  if(atoi(&date_test[0]) >= 24 || atoi(&date_test[3]) > 59){
    ans = false;
  }
  return ans;
}

void Annonce(){
	printf("\r\nWelcome in the .log analyzer\r\n");
	printf("Here you can analyze your .log files by ");
	printf("printing the 10 most consulted documents with the following options : \r\n\r\n");
	printf("------create the corresponding .dot file : -g fileName.dot \r\n");
	printf("------exclude documents with image, css or javascript extension : -e \r\n");
	printf("------only consider hits in a period of time [XX:XX,XX:XX+1] : -t XX:XX \r\n");
	printf("Here's the right syntax to do what ever you want : ");
	printf("$./analog [-g FicName.dot] [-e] [-t time] FicName.log\r\n\r\n");
}