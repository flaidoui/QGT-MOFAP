#include <fstream>
<<<<<<< HEAD
// random_shuffle example
#include <iostream>     // std::cout
#include <algorithm>    // std::random_shuffle
#include <vector>       // std::vector
#include<set>           //set
#include <map>
#include <ctime>        // std::time
#include <cstdlib>      // std::rand, std::srand
using namespace std;
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "AFP/AFP.h"
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//###################################################
// ############# my libraries - LAIDOUI Fatma
//##################################################
//#include "PIPlayer/PIPlayer.h" //joueur PI:minimiser le coût de l'interférence totale interference totale
//#include "PIPlayer/PIPlayer.cpp"//
//#include "PSPlayer/PSPlayer.h"//joueur PS:minimiser le span
//#include "PSPlayer/PSPlayer.cpp"
//#include "Commun/Commun.h"
#include "Game/Game.h"
//#include "Game/Game.cpp"
//-----------------------------
//execution parallelle Laidoui Fatma ajout 9-10-2019
#include <omp.h>
//------------------------------------------------------
//******************** Agent Qlearning *******************
//#include "AgentQL/AgentQL.h"

const double  epsilon  = 0.1;//0.05;//0.1;

//-------------------------------------------------


//##########################My functions LAIDOUI FATMA#######################

extern bool my_cmpvectintinffirst(const int &a, const int  &b);
extern bool my_cmpInfDoublePair(const pair <int,double>   &a, const pair <int,double>   &b);
extern bool my_cmpSupFirst(const pair <int,double>   &a, const pair <int,double>   &b);
//###################################################

bool my_cmpDoubleDoublePairHighFirst(const pair <double,double>   &a, const pair <double,double>   &b)
{
    // smallest comes first
    return a.second > b.second;
}
//main
using namespace std;
int main(int argc, char *argv[]) {
    //######################### My variables - LAIDOUI Fatma ##########
    //##############################################################
=======
// random_shuffle example
#include <iostream>     // std::cout
#include <algorithm>    // std::random_shuffle
#include <vector>       // std::vector
#include<set>           //set
#include <map>
#include <ctime>        // std::time
#include <cstdlib>      // std::rand, std::srand
using namespace std;
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "AFP/AFP.h"
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//###################################################
// ############# my libraries - LAIDOUI Fatma
//##################################################
//#include "PIPlayer/PIPlayer.h" //joueur PI:minimiser le coût de l'interférence totale interference totale
//#include "PIPlayer/PIPlayer.cpp"//
//#include "PSPlayer/PSPlayer.h"//joueur PS:minimiser le span
//#include "PSPlayer/PSPlayer.cpp"
//#include "Commun/Commun.h"
#include "Game/Game.h"
//#include "Game/Game.cpp"
//-----------------------------
//execution parallelle Laidoui Fatma ajout 9-10-2019
#include <omp.h>
//------------------------------------------------------
//******************** Agent Qlearning *******************
//#include "AgentQL/AgentQL.h"

const double  epsilon  = 0.1;//0.05;//0.1;

//-------------------------------------------------


//##########################My functions LAIDOUI FATMA#######################

extern bool my_cmpvectintinffirst(const int &a, const int  &b);
extern bool my_cmpInfDoublePair(const pair <int,double>   &a, const pair <int,double>   &b);
extern bool my_cmpSupFirst(const pair <int,double>   &a, const pair <int,double>   &b);
//###################################################

bool my_cmpDoubleDoublePairHighFirst(const pair <double,double>   &a, const pair <double,double>   &b)
{
    // smallest comes first
    return a.second > b.second;
}
//main
using namespace std;
int main(int argc, char *argv[]) {
    //######################### My variables - LAIDOUI Fatma ##########
    //##############################################################
>>>>>>> 0514ea9fae0f841576757defb02235a9189b0fad


  //miscelaneous
	srand(time(NULL));
<<<<<<< HEAD
	cout.precision(10);




 //################################################################
//##################### Déroulement du jeux #######################
//#################################################################

    int max_gen = 2;
    //int Strategy = 1;
  //  int Strategy = 2;
    int StrategyTrxPI;
    int StrategyFreqPI;
    int StrategyTrxPS;
    int StrategyFreqPS;

    int ApproachGameEvaluation = 2;
    int ApproachGame    =   1  ;
    int NumGame         =   1  ;
    StrategyTrxPI       = 1; // 1: freq random,3: distance; 550: pareto, 4 nash, 2 minimum cost; 6: hv
    StrategyFreqPI      =  1; // 1: freq random,3: distance; 550: pareto
    StrategyTrxPS       =   1 ; // 1:trx random, 0: sequentiel, 8 :max interference before
    StrategyFreqPS      =  1; //  1: freq random,3: distance; 550: pareto, 4 nash, 2 minimum cost; 6: hv
 clock_t start = clock();
    //]]]]]]]]]]]]]]] instance = "Denver"]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

    //string instance = "Denver";
    //AFP * afpProblem = new AFP(instance);
    ////Game * G = new Game(afpProblem);
   // G->PlayGame(max_gen,instance,afpProblem,Strategy);
   // delete G;


    //]]]]]]]]]]]]]]] instance = "Seattle" ]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
    //std::cout << __cplusplus << std::endl;
  string instance ="Seattle";
    AFP * afpProblem = new AFP(instance);
    int i;
  Game * G = new Game(afpProblem,max_gen);
     switch(ApproachGame)
    {
        case + 1 :
        {
            //G->PlayGameNaive(ApproachGameEvaluation,ApproachGame,NumGame, max_gen,instance,afpProblem,StrategyTrxPI,StrategyFreqPI,StrategyTrxPS,StrategyFreqPS);
            cout << " G->solution->PIObj " << G->solution->PIObj<< endl;
            cout << " G->solution->PSObj " << G->solution->PSObj<< endl;
           G->PlayGame(G->solution,ApproachGameEvaluation,ApproachGame,NumGame,max_gen,instance,afpProblem,StrategyTrxPI,StrategyFreqPI,StrategyTrxPS,StrategyFreqPS);

            break;
        }
        case +2 :
        {
           G->PlayGameSuperp(ApproachGameEvaluation,ApproachGame,NumGame,max_gen,instance,afpProblem,StrategyTrxPI,StrategyFreqPI,StrategyTrxPS,StrategyFreqPS);
           break ;
        }
        default:
        {
            cout << " Erreur de choix dans l approche du jeu !!"  << endl;
            break ;
        }
    }
    cout << "°°°°°°°°°°°°°°°°°°°°°°°°°°°" <<endl;
    cout << "G->solution->PIObj Main " << G->solution->PIObj << endl;
    cout << "G->solution->PSObj Main " << G->solution->PSObj << endl;
cout << " G - > HV " << G->HV << endl;
    cout << "G->BestsolutionSs->size() "<< G->BestsolutionSs.size()<<endl;
    //------------------------------------------------------
    clock_t stop = clock();//fin de timing
    double elapsed_secs = double(stop - start) / CLOCKS_PER_SEC;
    cout << "Temps d'execution"<<elapsed_secs << " ms" << endl;




    //int Strategy = 3;
    //int Strategy = 4;
    //int Strategy = 5;
    //int Strategy = 6;//sup
    //int Srategy = 7;//la plus mauvaise stratégie
    //int Strategy = 8;//------------ xxxxxxxxxx Mauvais score
    //int Strategy = 9;
    //int Strategy = 10;//Choisir le premier trx  dont son secteur nqui a pas trop de voisin a un saut
    //................................................
     //.......................... Game 01
     //RANDOM




//  int ApproachGameEvaluation = 11; //une solution Nash-
    //int ApproachGameEvaluation = 1; //Nash-ensemble
    //int ApproachGameEvaluation = 2; //pareto-ensemble
   // int ApproachGameEvaluation = 21; //pareto-une solution-meilleur solution qui a le plus grand HV
    // int ApproachGameEvaluation = 22; //pareto-une solution-meilleur solution qui a le plus petit ecart
    //int ApproachGameEvaluation = 23; //pareto-une solution-meilleur solution qui a le plus petit nash


     /* StrategyFreqPI      =   55 ;//Best frequency in term of front pareto pure aléatoire
  StrategyFreqPS      =   550 ;//Best separation in term of Front pareto pure min cost
  StrategyFreqPI      =   551 ;//Best frequency in term of front pareto pure minimum écart
  StrategyFreqPS      =   551 ;//Best separation in term of Front pareto pure minimum écart
  StrategyFreqPI      =   552 ;//Best frequency in term of front pareto pure Plus grand HV
  StrategyFreqPS      =   552 ;//Best separation in term of Front pareto pure Plus grand HV

  StrategyFreqPI      =   500 ;//Best frequency in term of front pareto INSPIRE aléatoire
  StrategyFreqPS      =   500 ;//Best separation in term of Front pareto INSPIRE aléatoire
  StrategyFreqPI      =   501 ;//Best frequency in term of front pareto INSPIRE minimum écart
  StrategyFreqPS      =   501 ;//Best separation in term of Front pareto INSPIRE minimum écart
  StrategyFreqPI      =   502 ;//Best frequency in term of front pareto INSPIRE Plus grand HV
  StrategyFreqPS      =   502 ;//Best separation in term of Front pareto INSPIRE Plus grand HV


  StrategyFreqPI      =   4 ;//Best frequency in term of Nash
  StrategyFreqPS      =   4 ;//Best separation in term of Nash

  StrategyFreqPI      =   6 ;//Best frequency in term of HV
  StrategyFreqPS      =   6 ;//Best separation in term of HV
  */
    //.......................... Game 02

   /* int NumGame     =   02  ;
    StrategyTrxPI   =   1   ; // trx random
    StrategyFreqPI  =   2   ; // freq best min interference
    StrategyTrxPS   =   1   ; // trx random
    StrategyFreqPS  =   1   ; // freq random
    */

    //.......................... Game 03
/*
    int NumGame     =   03  ;
    StrategyTrxPI   =   1   ; // trx random
    StrategyFreqPI  =   1   ; // freq random
    StrategyTrxPS   =   1   ; // trx random
    StrategyFreqPS  =   2   ; // freq best min separation
*/

    //.......................... Game 04
    /*
    int ApproachGame    =   1   ;
    int NumGame         =   4  ;
    StrategyTrxPI       =   1   ; // trx aléatoire selective, meilleur trx qui a un cout le plut petit
    StrategyFreqPI      =   2  ; // freq best min interference
    StrategyTrxPS       =   1   ; // trx random
    StrategyFreqPS      =   2   ; // freq best min separation
    */
  //.......................... Game 05
/*
    int ApproachGame    =   1   ;
    int NumGame     =   06  ;
    StrategyTrxPI   =   1   ; // trx aléatoire selective, meilleur trx qui a un cout le plut petit
    StrategyFreqPI  =   3  ; // freq best  interference en terme de distance
    StrategyTrxPS   =   1   ; // trx random
    StrategyFreqPS  =   3   ; // freq best  separation en terme de distance
*/
//  int ApproachGameEvaluation = 11; //une solution Nash-
    //int ApproachGameEvaluation = 1; //Nash-ensemble
    //int ApproachGameEvaluation = 2; //pareto-ensemble
   // int ApproachGameEvaluation = 21; //pareto-une solution-meilleur solution qui a le plus grand HV
    // int ApproachGameEvaluation = 22; //pareto-une solution-meilleur solution qui a le plus petit ecart
    //int ApproachGameEvaluation = 23; //pareto-une solution-meilleur solution qui a le plus petit nash


     /*
      StrategyFreqPI = 1, aléatoire, 3 : distance,



     StrategyFreqPI      =   55 ;//Best frequency in term of front pareto pure aléatoire
  StrategyFreqPS      =   55 ;//Best separation in term of Front pareto pure aléatoire
  StrategyFreqPI      =   551 ;//Best frequency in term of front pareto pure minimum écart
  StrategyFreqPS      =   551 ;//Best separation in term of Front pareto pure minimum écart
  StrategyFreqPI      =   552 ;//Best frequency in term of front pareto pure Plus grand HV
  StrategyFreqPS      =   552 ;//Best separation in term of Front pareto pure Plus grand HV

  StrategyFreqPI      =   500 ;//Best frequency in term of front pareto INSPIRE aléatoire
  StrategyFreqPS      =   500 ;//Best separation in term of Front pareto INSPIRE aléatoire
  StrategyFreqPI      =   501 ;//Best frequency in term of front pareto INSPIRE minimum écart
  StrategyFreqPS      =   501 ;//Best separation in term of Front pareto INSPIRE minimum écart
  StrategyFreqPI      =   502 ;//Best frequency in term of front pareto INSPIRE Plus grand HV
  StrategyFreqPS      =   502 ;//Best separation in term of Front pareto INSPIRE Plus grand HV
  */

//..............................................
    /*
    int NumGame     =  07   ;
    StrategyTrxPI   =   1   ;//trx alééatoire
    StrategyFreqPI  =   2   ;//best frequency
    StrategyTrxPS   =   1   ;//trx random
    StrategyFreqPS  =   3   ;//Best separation in term of distance
*/
  //.......................... Game 08
/*
    int NumGame     =   8   ;
    StrategyTrxPI   =   1   ;//Choisir un trx qui un nmbre max de trx de meme site,
    StrategyFreqPI  =   3   ;//Best frequency in term of distance
    StrategyTrxPS   =   1   ;//trx random
    StrategyFreqPS  =   2   ;//Best separation in term of cost
*/
     //.......................... Game 09
/*
    int ApproachGame    =   1   ;
    int NumGame         =   9   ;
    StrategyTrxPI       =   1   ;//Choisir un trx qui un nmbre max de trx de meme site,
    StrategyFreqPI      =   4   ;//Best frequency in term of NASH
    StrategyTrxPS       =   1   ;//trx random
    StrategyFreqPS      =   2   ;//Best separation
*/
     //.......................... Game 10
 /* int ApproachGameEvaluation = 2;
    int ApproachGame    =   1   ;
    int NumGame         =   10  ;
    StrategyTrxPI       =   8  ;//Choisir un trx qui un nmbre max de trx de meme site,
    StrategyFreqPI      =   4  ;//Best frequency in term of NASH
    StrategyTrxPS       =   8 ;//trx random
    StrategyFreqPS      =   4   ;//Best separation in term of NASH

  //  int ApproachGameEvaluation = 11; //une solution Nash-
    //int ApproachGameEvaluation = 1; //Nash-ensemble
    //int ApproachGameEvaluation = 2; //pareto-ensemble
   // int ApproachGameEvaluation = 21; //pareto-une solution-meilleur solution qui a le plus grand HV
    // int ApproachGameEvaluation = 22; //pareto-une solution-meilleur solution qui a le plus petit ecart
    //int ApproachGameEvaluation = 23; //pareto-une solution-meilleur solution qui a le plus petit nash

    */
     /* StrategyFreqPI      =   55 ;//Best frequency in term of front pareto pure aléatoire
  StrategyFreqPS      =   55 ;//Best separation in term of Front pareto pure aléatoire
  StrategyFreqPI      =   551 ;//Best frequency in term of front pareto pure minimum écart
  StrategyFreqPS      =   551 ;//Best separation in term of Front pareto pure minimum écart
  StrategyFreqPI      =   552 ;//Best frequency in term of front pareto pure Plus grand HV
  StrategyFreqPS      =   552 ;//Best separation in term of Front pareto pure Plus grand HV

  StrategyFreqPI      =   500 ;//Best frequency in term of front pareto INSPIRE aléatoire
  StrategyFreqPS      =   500 ;//Best separation in term of Front pareto INSPIRE aléatoire
  StrategyFreqPI      =   501 ;//Best frequency in term of front pareto INSPIRE minimum écart
  StrategyFreqPS      =   501 ;//Best separation in term of Front pareto INSPIRE minimum écart
  StrategyFreqPI      =   502 ;//Best frequency in term of front pareto INSPIRE Plus grand HV
  StrategyFreqPS      =   502 ;//Best separation in term of Front pareto INSPIRE Plus grand HV
  */


   //.......................... Game 11
/*
    int ApproachGame    =   1   ;
    int NumGame         =   11  ;

    StrategyTrxPI       =   1   ;//Choisir un trx qui un nmbre max de trx de meme site,
    StrategyFreqPI      =   5   ;//Best frequency in term of front pareto
    StrategyTrxPS       =   1   ;//trx random
    StrategyFreqPS      =   2   ;//Best separation in term of cost
*/
//.......................... Game 12
/*

   int NumGame     =   12   ;
    StrategyTrxPI   =   1   ;//Choisir un trx aléatoire
    StrategyFreqPI  =   2  ;//Best frequency in term of cost interference
    StrategyTrxPS   =   1   ;//trx random
    StrategyFreqPS  =   5  ;//Best separation in term of Front
*/

//.......................... Game 13
/*
   int ApproachGameEvaluation = 2;
    int ApproachGame    =   1  ;
    int NumGame         =   13   ;
    StrategyTrxPI       =   8 ;//Choisir un trx aléatoire
    StrategyFreqPI      =   502 ;//Best frequency in term of front pareto pure
    StrategyTrxPS       =   8   ;//trx random
    StrategyFreqPS      =   502 ;//Best separation in term of Front pareto pure
*/
//===========================================================
//Stratégie pareto pure

 /* StrategyFreqPI      =   55 ;//Best frequency in term of front pareto pure aléatoire
  StrategyFreqPS      =   55 ;//Best separation in term of Front pareto pure aléatoire
  StrategyFreqPI      =   551 ;//Best frequency in term of front pareto pure minimum écart
  StrategyFreqPS      =   551 ;//Best separation in term of Front pareto pure minimum écart
  StrategyFreqPI      =   552 ;//Best frequency in term of front pareto pure Plus grand HV
  StrategyFreqPS      =   552 ;//Best separation in term of Front pareto pure Plus grand HV

  StrategyFreqPI      =   500 ;//Best frequency in term of front pareto INSPIRE aléatoire
  StrategyFreqPS      =   500 ;//Best separation in term of Front pareto INSPIRE aléatoire
  StrategyFreqPI      =   501 ;//Best frequency in term of front pareto INSPIRE minimum écart
  StrategyFreqPS      =   501 ;//Best separation in term of Front pareto INSPIRE minimum écart
  StrategyFreqPI      =   502 ;//Best frequency in term of front pareto INSPIRE Plus grand HV
  StrategyFreqPS      =   502 ;//Best separation in term of Front pareto INSPIRE Plus grand HV
  */
    //===========================
    //===========================
    //StrategyFreqPI      =   50 ;//Best frequency in term of front pareto egoiste
  //StrategyFreqPS      =   50 ;//Best separation in term of Front egoiste
  //  int ApproachGameEvaluation = 11; //une solution Nash-
    //int ApproachGameEvaluation = 1; //Nash-ensemble, epsilon
    //int ApproachGameEvaluation = 2; //pareto-ensemble
   // int ApproachGameEvaluation = 21; //pareto-une solution-meilleur solution qui a le plus grand HV
    // int ApproachGameEvaluation = 22; //pareto-une solution-meilleur solution qui a le plus petit ecart
    //int ApproachGameEvaluation = 23; //pareto-une solution-meilleur solution qui a le plus petit nash


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Modifier le choix de trx superposition  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//int ApproachGame = 2;

//.......................... Game 04

    /*int ApproachGame    =   1   ;
    int NumGame         =   04  ;
    StrategyTrxPI       =   1   ; // trx aléatoire selective, meilleur trx qui a un cout le plut petit
    StrategyFreqPI      =   2   ; // freq best min interference
    StrategyTrxPS       =   1   ; // trx random
    StrategyFreqPS      =   2   ; // freq best min separation
*/





       //.......................... Game 14
/*
    int ApproachGame  =     1   ;
    int NumGame       =     14  ;
    StrategyTrxPI     =     8   ;//choix le trx qui a le plus grand cout
    StrategyFreqPI    =     4   ;//Best frequency in term of NASH
    StrategyTrxPS     =     1   ;//trx random
    StrategyFreqPS    =     4    ;//Best separation in term of NASH
*/
       //.......................... Game 15

/*
    int ApproachGame = 1;
    int NumGame     =   15  ;
    StrategyTrxPI   =   9  ;//Choisir aléatoire
    StrategyFreqPI  =   4   ;//Best frequency in term of NASH
    StrategyTrxPS   =   1   ;//trx random
    StrategyFreqPS  =   4  ;//Best separation in term of NASH
*/
       //.......................... Game 16
  /*
   int ApproachGameEvaluation = 2;
    int ApproachGame  =   1   ;
    int NumGame       =   16  ;
    StrategyTrxPI     =   1   ;//Choisir aléatoire
    StrategyFreqPI    =   6   ;//Best frequency in term of NASH
    StrategyTrxPS     =   1   ;//trx random
    StrategyFreqPS    =   6  ;//Best separation in term of NASH
  */

    //  int ApproachGameEvaluation = 11; //une solution Nash-
    //int ApproachGameEvaluation = 1; //Nash-ensemble
    //int ApproachGameEvaluation = 2; //pareto-ensemble
   // int ApproachGameEvaluation = 21; //pareto-une solution-meilleur solution qui a le plus grand HV
    // int ApproachGameEvaluation = 22; //pareto-une solution-meilleur solution qui a le plus petit ecart
    //int ApproachGameEvaluation = 23; //pareto-une solution-meilleur solution qui a le plus petit nash




    /*
    int ApproachGameEvaluation = 2;
    int ApproachGame  =   1   ;
    int NumGame       =   266  ;
    StrategyTrxPI     =   1   ;//Choisir aléatoire
    StrategyFreqPI    =   6   ;//Best frequency in term of NASH
    StrategyTrxPS     =   1   ;//trx random
    StrategyFreqPS    =   6  ;//Best separation in term of NASH
    */
       //.......................... Game 17
    /*int ApproachGame  =   1   ;
    int NumGame       =   17  ;
    StrategyTrxPI     =   1   ;//Choisir aléatoire
    StrategyFreqPI    =   5   ;//Best frequency in term of NASH
    StrategyTrxPS     =   1   ;//trx random
    StrategyFreqPS    =   6  ;//Best separation in term of hv
*/
/*
       //.......................... Game 18
    int ApproachGame  =   1   ;
    int NumGame       =   18  ;
    StrategyTrxPI     =   1   ;//Choisir aléatoire
    StrategyFreqPI    =   5   ;//Best frequency in term of NASH
    StrategyTrxPS     =   1   ;//trx random
    StrategyFreqPS    =   4 ;//Best separation in term of NASH
*/
       //.......................... Game 19
    /*int ApproachGame  =   1   ;
    int NumGame       =   19 ;
    StrategyTrxPI     =   1   ;//Choisir aléatoire
    StrategyFreqPI    =   4   ;//Best frequency in term of NASH
    StrategyTrxPS     =   1   ;//trx random
    StrategyFreqPS    =   5 ;//Best separation in term of NASH
*/
       //.......................... Game 20
   /* int ApproachGame  =   1   ;
    int NumGame       =   20 ;
    StrategyTrxPI     =   1   ;//Choisir aléatoire
    StrategyFreqPI    =   6  ;//Best frequency in term of NASH
    StrategyTrxPS     =   1   ;//trx random
    StrategyFreqPS    =   5 ;//Best separation in term of NASH
 */

           //.......................... Game 21
   /* int ApproachGame  =   1   ;
    int NumGame       =   21 ;
    StrategyTrxPI     =   1   ;//Choisir aléatoire
    StrategyFreqPI    =   6  ;//Best frequency in term of NASH
    StrategyTrxPS     =   1   ;//trx random
    StrategyFreqPS    =   4 ;//Best separation in term of NASH
    */
         //.......................... Game 22
   /*int ApproachGame  =   1   ;
    int NumGame       =   22;
    StrategyTrxPI     =   1   ;//Choisir aléatoire
    StrategyFreqPI    =   4  ;//Best frequency in term of NASH
    StrategyTrxPS     =   1   ;//trx random
    StrategyFreqPS    =   5 ;//Best separation in term of NASH
*/
         //.......................... Game 23
  /* int ApproachGame  =   1   ;
    int NumGame       =   23;
    StrategyTrxPI     =   1   ;//Choisir aléatoire
    StrategyFreqPI    =   2  ;//Best frequency in term of NASH
    StrategyTrxPS     =   1   ;//trx random
    StrategyFreqPS    =   5 ;//Best separation in term of NASH
*/
           //.......................... Game 55 *****meilleur combinaison***********
  /* int ApproachGame  =   1   ;
    int NumGame       =   55;
    StrategyTrxPI     =   1   ;//Choisir aléatoire
    StrategyFreqPI    =   6 ;//Best frequency in term of NASH
    StrategyTrxPS     =   1   ;//trx random
    StrategyFreqPS    =   5 ;//Best separation in term of NASH
    */
 //*****************************************************************
      /*int ApproachGame  =   1   ;
    int NumGame       =   65;
    StrategyTrxPI     =   1   ;//Choisir aléatoire
    StrategyFreqPI    =  6 ;//Best frequency in term of NASH
    StrategyTrxPS     =   1   ;//trx random
    StrategyFreqPS    =   5 ;//Best separation in term of NASH*/

     /*int ApproachGame  =   1   ;
    int NumGame       =   56;
    StrategyTrxPI     =   1   ;//Choisir aléatoire
    StrategyFreqPI    =  5 ;//Best frequency in term of NASH
    StrategyTrxPS     =   1   ;//trx random
    StrategyFreqPS    =   6 ;//Best separation in term of NASH
*/



    //#############################################################################################
    //cout << "G->PI->QLPI->Qtable->size()" << G->PI->QLPI->Qtable->size()<<endl;

   // cout<<"##############################Tester l'ensemble des action Affichahe l'ensemble des action ##################################"<<endl;
    //cout << "G->QL->ActionsSet->size()" << G->QL->ActionsSet.size()<<endl;



     //##################################################################################################

    //cout<<"############################## Tester la configuration de Qtable ############################"<<endl;
   ShowSolution(StrategyTrxPI,StrategyTrxPS,  G->solution,ApproachGameEvaluation,instance,elapsed_secs,max_gen,epsilon);
   G->QL->ShowQtable(ApproachGameEvaluation,instance,elapsed_secs,max_gen,epsilon);
  // G->ShowMemoryOccurenceUseTRX();
     //##########################################################################################

 /*Test Minimum occurence strategy ========================
  G->initVectorMemoryOccurenceUseTRX(afpProblem);
  G->ShowMemoryOccurenceUseTRX();
  //vector <pair<TRXs,int>> MemoryOccurenceUseTRX;
  TRXs trx;
  pair <TRXs,int> t;
  t = G->MemoryOccurenceUseTRX.at(8);
  G->UpdateOccurenceTRX( t.first, 0);
  TRXs T;
 //  t = G->MemoryOccurenceUseTRX.at(5);
 // T = t.first;
  G->GetTRXMinimumUsed(T);
  cout << "TRX MINIMUM OCCURENCE IS   (TRX; occurrence) : " << T.trxID << endl;//<<"," << t.second << endl;
  */
  //G->ShowMemoryOccurenceUseTRX();

     //######################### Tester GetMaxQValue ###########################################
    /*
     Action CorrespondingAction ;
     State s;
     s.UnTreatedTRXNumb = 1;
     double val = G->PI->QLPI->GetMaxQValue(s, CorrespondingAction); //Récupérer la valeur  de Qvalue max et son action
     cout << " (val,CorrespondingAction.ActFreq) : (" << val  << "," << CorrespondingAction.ActFreq <<")"<<endl;
     */
     //#####################################################################################"
      //######################### Tester double AGENTQL::GetQtarget(State sdash , Action & CorrespondingMaxAction) ###########################################
    /*
     Action CorrespondingAction ;
     State s;
     s.UnTreatedTRXNumb = 1;
     double val = G->PI->QLPI->GetQtarget(s , CorrespondingAction); //Récupérer la valeur  de Qvalue max et son action
     cout << " (Qtarget,CorrespondingAction.ActFreq) : (" << val  << "," << CorrespondingAction.ActFreq <<")"<<endl;
    */
     //#####################################################################################"

         //######################### Tester    GetIndexPairStateAction(pair < State ,Action > PairStateAction); ###########################################

    /* pair < State ,Action > PairStateAction;
     PairStateAction.first.UnTreatedTRXNumb = 0;
     PairStateAction.second.ActFreq = 0;
     int index =  G->PI->QLPI->GetIndexPairStateAction(PairStateAction);
     cout << " GetIndexPairStateAction(PairStateAction) : " << index  << endl;*/

     //#####################################################################################"







    //--------------------------
    //-----------------------afficher la solution ---------------
        /*ofstream ResultFile;
    string path="Exemple/solution_.txt";
     ResultFile.open(path.c_str(),std::ios::app);
     for(i = 0 ; i < afpProblem->trxs.size(); i ++)
     {
         ResultFile << G->solution->plan->at(i)<<endl;
     }
  Individual * solution2;
        //à chaque génération, on initialise  la solution(individual)
        solution2 = new Individual();
        solution2->plan = new vector<int>(afpProblem->trxs.size());
        solution->planCC = new vector<double>(afpProblem->trxs.size());

        for(k=0;k<solution->plan->size();k++)
        {
            solution->plan->at(k)=-1;
            solution->planCC->at(k)=0.0;
            solution ->PIObj = 0.0 ;
            solution->PSObj = 0.0;

        }
ResultFile.close();*/
    //------------------------------------------------

   // cout << "afpProblem->interferenceBasedFitness(G->solution) :" << afpProblem->interferenceBasedFitness(G->solution) <<endl;
    delete G;
     //const pair<double,double> MinSeattle = (4000,15) ;
    /*pair<double,double> MinSeattle;
     MinSeattle.first = 4000.0;
     MinSeattle.second = 15.0 ;
      //const pair<double,double> MaxSeattle =(10000,100);
     pair<double,double> MaxSeattle;
     MaxSeattle.first = 70000.0;
     MaxSeattle.second = 200.0;
   // const pair<double,double> MaxSeattle =(70000,200);
    pair < double, double > R;// est le point de référence ; la valeur max
      R.first = (MaxSeattle.first - MinSeattle.first)/(MaxSeattle.first-MinSeattle.first);
      R.second = (MaxSeattle.second - MinSeattle.second)/(MaxSeattle.second-MinSeattle.second);
      cout << "R.first "<< R.first <<endl;
      cout << "R.second "<< R.second <<endl;*/
    //++++++++++++++++++++++++++++++++++++++++++++
    //++++++++++++++++++++normalized values ++++++++++++++++++
   // const pair<double,double> MinSeattle = (4000,15) ;
   // const pair<double,double> MaxSeattle =(70000,200);
    /* pair<double,double> MinSeattle;
     MinSeattle.first = 1000.0;
     MinSeattle.second = 10.0 ;
   //const pair<double,double> MaxSeattle =(10000,100);
     pair<double,double> MaxSeattle;
     MaxSeattle.first = 4000.0;
     MaxSeattle.second = 40.0;

     /*const pair<double,double> MinDenver = (130000,1200) ;
    const pair<double,double> MaxDenver =(300000,2500);*/

   /* double CI,CS;
      vector < pair<double,double>  > paircost;
      paircost.reserve(2);
      paircost.push_back({1500,10});
      paircost.push_back({1400,15});
      int i;
      //+++++++++++++++++++++++++++++++++
     cout << " ....affichage avant la normalisation ..." <<endl;
      for(i = 0 ; i < paircost.size() ; i++)
      {
          cout << " paircost.at(i).first :" << paircost.at(i).first <<endl;
           cout << " paircost.at(i).second :" << paircost.at(i).second <<endl;
      }
       // cout << " ....affichage après la normalisation ..." <<endl;++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
      // Normaliser les valeurs

      Normalize(paircost,MinSeattle,MaxSeattle);

        //+++++++++++++++++++++++++++++++++++++++++++++++++++++
     cout << " ....affichage avant la normalisation ..." <<endl;
      for(i = 0 ; i < paircost.size() ; i++)
      {
          cout << " paircost.at(i).first :" << paircost.at(i).first <<endl;
           cout << " paircost.at(i).second :" << paircost.at(i).second <<endl;
      }
      //+++++++++++++++++++++++ calculer l hypervolume ++++++++++++
      //++ 0.trier les valeur selon un ordre décroissant de +++++++++++
      sort(paircost.begin(),paircost.end(),my_cmpDoubleDoublePairHighFirst);
      //++++++++++++++++++++++++++++++++++++++++++++++++++++++++
       cout << " ....affichage après le tri ..." <<endl;
      for(i = 0 ; i < paircost.size() ; i++)
      {
          cout << " paircost.at(i).first :" << paircost.at(i).first <<endl;
           cout << " paircost.at(i).second :" << paircost.at(i).second <<endl;
      }

      // ++++++++++ 1. Choisir le point de référence R, soit R = MaxSeattle
      pair < double, double > R;// est le point de référence ; la valeur max
      R = MaxSeattle;
      //++++++++++++ 2. Normaliser les valeur de R ++++++++++
      R.first = (R.first - MinSeattle.first) / (MaxSeattle.first - MinSeattle.second);
      R.second = (R.second - MinSeattle.second) / (MaxSeattle.first - MinSeattle.second);
      cout << "R.first :"<< R.first << endl;
      cout << "R.second :"<< R.second << endl;
      //+++++++++++++ 3. Calculer l hypervolume ++++++++++++++++++++
      double HV = 0.0 ; //hypervolume

      HV = Hypervolume(paircost , R);
      cout << "HV = " << HV <<endl;*/
 //.........................................
   // verifier veccost...................................................

   /* vector<TRXs> LTrxNTreateds;
    vector <int> LTrxNtreatedsID ;
    LTrxNTreateds.reserve(3);
    LTrxNTreateds.push_back(afpProblem->trxs[0]);
    LTrxNTreateds.push_back(afpProblem->trxs[1]);
    LTrxNTreateds.push_back(afpProblem->trxs[2]);
    Individual * solutionTemp;
    //................INITIALISATION de la solution.......à chaque génération, on initialise  la solution(individual)
    solutionTemp = new Individual();
    solutionTemp->plan = new vector<int>(3);
    solutionTemp->planCC = new vector<double>(3);
    solutionTemp->PlanAffect=new vector< pair<int,int> > ();

    for(i=0;i<3;i++)
    {
        solutionTemp->plan->at(i)= -1 ;
        solutionTemp->planCC->at(i)= 0.0 ;
        if (solutionTemp->plan->at(i)!=-1)//si la case dans le plan n'est pas vide on remplie le planAffect
            {
                solutionTemp->PlanAffect->push_back({i,solutionTemp->plan->at(i)});
                //cout << "i ..." << i << endl;
            }
    }
    cout <<" 1.solutionTemp->PIObj = "<< solutionTemp->PIObj  <<endl;
     cout <<" 1.solutionTemp->PSObj = "<< solutionTemp->PIObj  <<endl;
    solutionTemp->plan->at(0) = 591;
    solutionTemp->PIObj = afpProblem->ComputeSolutionInterference(solutionTemp);
     solutionTemp->PSObj = afpProblem->ComputeSolutionSeparationCost(solutionTemp);
    cout <<" 2.solutionTemp->PIObj = "<< solutionTemp->PIObj  <<endl;
    cout <<" 2.solutionTemp->PSObj = "<< solutionTemp->PSObj  <<endl;
    solutionTemp->plan->at(1) = 591;
    int victimTrx = 2;
    double cost = 0.0 ;
    double costSep = 0.0;
    int victimFrequency = 591;
    solutionTemp->PIObj = afpProblem->ComputeSolutionInterference(solutionTemp);
    solutionTemp->PSObj = afpProblem->ComputeSolutionSeparationCost(solutionTemp);
     solutionTemp->plan->at(2) = 591;
    for(i = 0 ; i < solutionTemp->plan->size(); i++)
    {
        if(solutionTemp->plan->at(i)!=-1)
        {
           int interfererFrequency = solutionTemp->plan->at(i);
           int interfererTrx = i;
           if(interfererTrx!=victimTrx)
            {
                // si dans la meme fréquence
                cost = cost + afpProblem->computeChannelInterference(victimFrequency ,interfererFrequency, victimTrx, interfererTrx)+
                afpProblem->computeChannelInterference(interfererFrequency,victimFrequency ,interfererTrx, victimTrx);
                //les 2 trx sont dans le meme secteur
               if(afpProblem->trxs[victimTrx].sectorID == afpProblem->trxs[interfererTrx].sectorID)
                {
                    //on teste si la contraite de separation co-secteur est respecté!!
                    if (abs (solutionTemp->plan->at(victimTrx)- solutionTemp->plan->at(interfererTrx))< 3)//contrainte co secteur violée
                    {
                        costSep = costSep +1.0;
                    }
                }// secteur different
                else
                {
                    if(afpProblem->trxs[victimTrx].siteID  == afpProblem->trxs[interfererTrx].siteID)
                    {
                        //on teste si la contrainte de separation co-site est respectée!!
                        if (abs (solutionTemp->plan->at(victimTrx)- solutionTemp-> plan->at(interfererTrx))< 2)//contrainte co secteur violée
                        {
                            costSep= costSep +1.0;
                        }
                    }//
                }

            }
        }
    }
    //le cout final de la solution
    cost = solutionTemp->PIObj + cost;
    costSep = solutionTemp->PSObj + costSep;
    solutionTemp->PIObj = afpProblem->ComputeSolutionInterference(solutionTemp);
    solutionTemp->PSObj = afpProblem->ComputeSolutionSeparationCost(solutionTemp);
    cout <<"°°°°°°°°°°° Comparaison °°°°°°°°°°°°°" << endl;
    cout <<" 3.solutionTemp->PIObj = "<< solutionTemp->PIObj  <<endl;
    cout <<" 3.solutionTemp->PSObj = "<< solutionTemp->PSObj  <<endl;
    cout <<"cost = " << cost << endl;
    cout <<"costsep = " << costSep << endl;
*/


=======
	cout.precision(10);




 //################################################################
//##################### Déroulement du jeux #######################
//#################################################################

    int max_gen = 2;
    //int Strategy = 1;
  //  int Strategy = 2;
    int StrategyTrxPI;
    int StrategyFreqPI;
    int StrategyTrxPS;
    int StrategyFreqPS;

    int ApproachGameEvaluation = 2;
    int ApproachGame    =   1  ;
    int NumGame         =   1  ;
    StrategyTrxPI       = 1; // 1: freq random,3: distance; 550: pareto, 4 nash, 2 minimum cost; 6: hv
    StrategyFreqPI      =  1; // 1: freq random,3: distance; 550: pareto
    StrategyTrxPS       =   1 ; // 1:trx random, 0: sequentiel, 8 :max interference before
    StrategyFreqPS      =  1; //  1: freq random,3: distance; 550: pareto, 4 nash, 2 minimum cost; 6: hv
 clock_t start = clock();
    //]]]]]]]]]]]]]]] instance = "Denver"]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

    //string instance = "Denver";
    //AFP * afpProblem = new AFP(instance);
    ////Game * G = new Game(afpProblem);
   // G->PlayGame(max_gen,instance,afpProblem,Strategy);
   // delete G;


    //]]]]]]]]]]]]]]] instance = "Seattle" ]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
    //std::cout << __cplusplus << std::endl;
  string instance ="Seattle";
    AFP * afpProblem = new AFP(instance);
    int i;
  Game * G = new Game(afpProblem,max_gen);
     switch(ApproachGame)
    {
        case + 1 :
        {
            //G->PlayGameNaive(ApproachGameEvaluation,ApproachGame,NumGame, max_gen,instance,afpProblem,StrategyTrxPI,StrategyFreqPI,StrategyTrxPS,StrategyFreqPS);
            cout << " G->solution->PIObj " << G->solution->PIObj<< endl;
            cout << " G->solution->PSObj " << G->solution->PSObj<< endl;
           G->PlayGame(G->solution,ApproachGameEvaluation,ApproachGame,NumGame,max_gen,instance,afpProblem,StrategyTrxPI,StrategyFreqPI,StrategyTrxPS,StrategyFreqPS);

            break;
        }
        case +2 :
        {
           G->PlayGameSuperp(ApproachGameEvaluation,ApproachGame,NumGame,max_gen,instance,afpProblem,StrategyTrxPI,StrategyFreqPI,StrategyTrxPS,StrategyFreqPS);
           break ;
        }
        default:
        {
            cout << " Erreur de choix dans l approche du jeu !!"  << endl;
            break ;
        }
    }
    cout << "°°°°°°°°°°°°°°°°°°°°°°°°°°°" <<endl;
    cout << "G->solution->PIObj Main " << G->solution->PIObj << endl;
    cout << "G->solution->PSObj Main " << G->solution->PSObj << endl;
cout << " G - > HV " << G->HV << endl;
    cout << "G->BestsolutionSs->size() "<< G->BestsolutionSs.size()<<endl;
    //------------------------------------------------------
    clock_t stop = clock();//fin de timing
    double elapsed_secs = double(stop - start) / CLOCKS_PER_SEC;
    cout << "Temps d'execution"<<elapsed_secs << " ms" << endl;




    //int Strategy = 3;
    //int Strategy = 4;
    //int Strategy = 5;
    //int Strategy = 6;//sup
    //int Srategy = 7;//la plus mauvaise stratégie
    //int Strategy = 8;//------------ xxxxxxxxxx Mauvais score
    //int Strategy = 9;
    //int Strategy = 10;//Choisir le premier trx  dont son secteur nqui a pas trop de voisin a un saut
    //................................................
     //.......................... Game 01
     //RANDOM




//  int ApproachGameEvaluation = 11; //une solution Nash-
    //int ApproachGameEvaluation = 1; //Nash-ensemble
    //int ApproachGameEvaluation = 2; //pareto-ensemble
   // int ApproachGameEvaluation = 21; //pareto-une solution-meilleur solution qui a le plus grand HV
    // int ApproachGameEvaluation = 22; //pareto-une solution-meilleur solution qui a le plus petit ecart
    //int ApproachGameEvaluation = 23; //pareto-une solution-meilleur solution qui a le plus petit nash


     /* StrategyFreqPI      =   55 ;//Best frequency in term of front pareto pure aléatoire
  StrategyFreqPS      =   550 ;//Best separation in term of Front pareto pure min cost
  StrategyFreqPI      =   551 ;//Best frequency in term of front pareto pure minimum écart
  StrategyFreqPS      =   551 ;//Best separation in term of Front pareto pure minimum écart
  StrategyFreqPI      =   552 ;//Best frequency in term of front pareto pure Plus grand HV
  StrategyFreqPS      =   552 ;//Best separation in term of Front pareto pure Plus grand HV

  StrategyFreqPI      =   500 ;//Best frequency in term of front pareto INSPIRE aléatoire
  StrategyFreqPS      =   500 ;//Best separation in term of Front pareto INSPIRE aléatoire
  StrategyFreqPI      =   501 ;//Best frequency in term of front pareto INSPIRE minimum écart
  StrategyFreqPS      =   501 ;//Best separation in term of Front pareto INSPIRE minimum écart
  StrategyFreqPI      =   502 ;//Best frequency in term of front pareto INSPIRE Plus grand HV
  StrategyFreqPS      =   502 ;//Best separation in term of Front pareto INSPIRE Plus grand HV


  StrategyFreqPI      =   4 ;//Best frequency in term of Nash
  StrategyFreqPS      =   4 ;//Best separation in term of Nash

  StrategyFreqPI      =   6 ;//Best frequency in term of HV
  StrategyFreqPS      =   6 ;//Best separation in term of HV
  */
    //.......................... Game 02

   /* int NumGame     =   02  ;
    StrategyTrxPI   =   1   ; // trx random
    StrategyFreqPI  =   2   ; // freq best min interference
    StrategyTrxPS   =   1   ; // trx random
    StrategyFreqPS  =   1   ; // freq random
    */

    //.......................... Game 03
/*
    int NumGame     =   03  ;
    StrategyTrxPI   =   1   ; // trx random
    StrategyFreqPI  =   1   ; // freq random
    StrategyTrxPS   =   1   ; // trx random
    StrategyFreqPS  =   2   ; // freq best min separation
*/

    //.......................... Game 04
    /*
    int ApproachGame    =   1   ;
    int NumGame         =   4  ;
    StrategyTrxPI       =   1   ; // trx aléatoire selective, meilleur trx qui a un cout le plut petit
    StrategyFreqPI      =   2  ; // freq best min interference
    StrategyTrxPS       =   1   ; // trx random
    StrategyFreqPS      =   2   ; // freq best min separation
    */
  //.......................... Game 05
/*
    int ApproachGame    =   1   ;
    int NumGame     =   06  ;
    StrategyTrxPI   =   1   ; // trx aléatoire selective, meilleur trx qui a un cout le plut petit
    StrategyFreqPI  =   3  ; // freq best  interference en terme de distance
    StrategyTrxPS   =   1   ; // trx random
    StrategyFreqPS  =   3   ; // freq best  separation en terme de distance
*/
//  int ApproachGameEvaluation = 11; //une solution Nash-
    //int ApproachGameEvaluation = 1; //Nash-ensemble
    //int ApproachGameEvaluation = 2; //pareto-ensemble
   // int ApproachGameEvaluation = 21; //pareto-une solution-meilleur solution qui a le plus grand HV
    // int ApproachGameEvaluation = 22; //pareto-une solution-meilleur solution qui a le plus petit ecart
    //int ApproachGameEvaluation = 23; //pareto-une solution-meilleur solution qui a le plus petit nash


     /*
      StrategyFreqPI = 1, aléatoire, 3 : distance,



     StrategyFreqPI      =   55 ;//Best frequency in term of front pareto pure aléatoire
  StrategyFreqPS      =   55 ;//Best separation in term of Front pareto pure aléatoire
  StrategyFreqPI      =   551 ;//Best frequency in term of front pareto pure minimum écart
  StrategyFreqPS      =   551 ;//Best separation in term of Front pareto pure minimum écart
  StrategyFreqPI      =   552 ;//Best frequency in term of front pareto pure Plus grand HV
  StrategyFreqPS      =   552 ;//Best separation in term of Front pareto pure Plus grand HV

  StrategyFreqPI      =   500 ;//Best frequency in term of front pareto INSPIRE aléatoire
  StrategyFreqPS      =   500 ;//Best separation in term of Front pareto INSPIRE aléatoire
  StrategyFreqPI      =   501 ;//Best frequency in term of front pareto INSPIRE minimum écart
  StrategyFreqPS      =   501 ;//Best separation in term of Front pareto INSPIRE minimum écart
  StrategyFreqPI      =   502 ;//Best frequency in term of front pareto INSPIRE Plus grand HV
  StrategyFreqPS      =   502 ;//Best separation in term of Front pareto INSPIRE Plus grand HV
  */

//..............................................
    /*
    int NumGame     =  07   ;
    StrategyTrxPI   =   1   ;//trx alééatoire
    StrategyFreqPI  =   2   ;//best frequency
    StrategyTrxPS   =   1   ;//trx random
    StrategyFreqPS  =   3   ;//Best separation in term of distance
*/
  //.......................... Game 08
/*
    int NumGame     =   8   ;
    StrategyTrxPI   =   1   ;//Choisir un trx qui un nmbre max de trx de meme site,
    StrategyFreqPI  =   3   ;//Best frequency in term of distance
    StrategyTrxPS   =   1   ;//trx random
    StrategyFreqPS  =   2   ;//Best separation in term of cost
*/
     //.......................... Game 09
/*
    int ApproachGame    =   1   ;
    int NumGame         =   9   ;
    StrategyTrxPI       =   1   ;//Choisir un trx qui un nmbre max de trx de meme site,
    StrategyFreqPI      =   4   ;//Best frequency in term of NASH
    StrategyTrxPS       =   1   ;//trx random
    StrategyFreqPS      =   2   ;//Best separation
*/
     //.......................... Game 10
 /* int ApproachGameEvaluation = 2;
    int ApproachGame    =   1   ;
    int NumGame         =   10  ;
    StrategyTrxPI       =   8  ;//Choisir un trx qui un nmbre max de trx de meme site,
    StrategyFreqPI      =   4  ;//Best frequency in term of NASH
    StrategyTrxPS       =   8 ;//trx random
    StrategyFreqPS      =   4   ;//Best separation in term of NASH

  //  int ApproachGameEvaluation = 11; //une solution Nash-
    //int ApproachGameEvaluation = 1; //Nash-ensemble
    //int ApproachGameEvaluation = 2; //pareto-ensemble
   // int ApproachGameEvaluation = 21; //pareto-une solution-meilleur solution qui a le plus grand HV
    // int ApproachGameEvaluation = 22; //pareto-une solution-meilleur solution qui a le plus petit ecart
    //int ApproachGameEvaluation = 23; //pareto-une solution-meilleur solution qui a le plus petit nash

    */
     /* StrategyFreqPI      =   55 ;//Best frequency in term of front pareto pure aléatoire
  StrategyFreqPS      =   55 ;//Best separation in term of Front pareto pure aléatoire
  StrategyFreqPI      =   551 ;//Best frequency in term of front pareto pure minimum écart
  StrategyFreqPS      =   551 ;//Best separation in term of Front pareto pure minimum écart
  StrategyFreqPI      =   552 ;//Best frequency in term of front pareto pure Plus grand HV
  StrategyFreqPS      =   552 ;//Best separation in term of Front pareto pure Plus grand HV

  StrategyFreqPI      =   500 ;//Best frequency in term of front pareto INSPIRE aléatoire
  StrategyFreqPS      =   500 ;//Best separation in term of Front pareto INSPIRE aléatoire
  StrategyFreqPI      =   501 ;//Best frequency in term of front pareto INSPIRE minimum écart
  StrategyFreqPS      =   501 ;//Best separation in term of Front pareto INSPIRE minimum écart
  StrategyFreqPI      =   502 ;//Best frequency in term of front pareto INSPIRE Plus grand HV
  StrategyFreqPS      =   502 ;//Best separation in term of Front pareto INSPIRE Plus grand HV
  */


   //.......................... Game 11
/*
    int ApproachGame    =   1   ;
    int NumGame         =   11  ;

    StrategyTrxPI       =   1   ;//Choisir un trx qui un nmbre max de trx de meme site,
    StrategyFreqPI      =   5   ;//Best frequency in term of front pareto
    StrategyTrxPS       =   1   ;//trx random
    StrategyFreqPS      =   2   ;//Best separation in term of cost
*/
//.......................... Game 12
/*

   int NumGame     =   12   ;
    StrategyTrxPI   =   1   ;//Choisir un trx aléatoire
    StrategyFreqPI  =   2  ;//Best frequency in term of cost interference
    StrategyTrxPS   =   1   ;//trx random
    StrategyFreqPS  =   5  ;//Best separation in term of Front
*/

//.......................... Game 13
/*
   int ApproachGameEvaluation = 2;
    int ApproachGame    =   1  ;
    int NumGame         =   13   ;
    StrategyTrxPI       =   8 ;//Choisir un trx aléatoire
    StrategyFreqPI      =   502 ;//Best frequency in term of front pareto pure
    StrategyTrxPS       =   8   ;//trx random
    StrategyFreqPS      =   502 ;//Best separation in term of Front pareto pure
*/
//===========================================================
//Stratégie pareto pure

 /* StrategyFreqPI      =   55 ;//Best frequency in term of front pareto pure aléatoire
  StrategyFreqPS      =   55 ;//Best separation in term of Front pareto pure aléatoire
  StrategyFreqPI      =   551 ;//Best frequency in term of front pareto pure minimum écart
  StrategyFreqPS      =   551 ;//Best separation in term of Front pareto pure minimum écart
  StrategyFreqPI      =   552 ;//Best frequency in term of front pareto pure Plus grand HV
  StrategyFreqPS      =   552 ;//Best separation in term of Front pareto pure Plus grand HV

  StrategyFreqPI      =   500 ;//Best frequency in term of front pareto INSPIRE aléatoire
  StrategyFreqPS      =   500 ;//Best separation in term of Front pareto INSPIRE aléatoire
  StrategyFreqPI      =   501 ;//Best frequency in term of front pareto INSPIRE minimum écart
  StrategyFreqPS      =   501 ;//Best separation in term of Front pareto INSPIRE minimum écart
  StrategyFreqPI      =   502 ;//Best frequency in term of front pareto INSPIRE Plus grand HV
  StrategyFreqPS      =   502 ;//Best separation in term of Front pareto INSPIRE Plus grand HV
  */
    //===========================
    //===========================
    //StrategyFreqPI      =   50 ;//Best frequency in term of front pareto egoiste
  //StrategyFreqPS      =   50 ;//Best separation in term of Front egoiste
  //  int ApproachGameEvaluation = 11; //une solution Nash-
    //int ApproachGameEvaluation = 1; //Nash-ensemble, epsilon
    //int ApproachGameEvaluation = 2; //pareto-ensemble
   // int ApproachGameEvaluation = 21; //pareto-une solution-meilleur solution qui a le plus grand HV
    // int ApproachGameEvaluation = 22; //pareto-une solution-meilleur solution qui a le plus petit ecart
    //int ApproachGameEvaluation = 23; //pareto-une solution-meilleur solution qui a le plus petit nash


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Modifier le choix de trx superposition  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//int ApproachGame = 2;

//.......................... Game 04

    /*int ApproachGame    =   1   ;
    int NumGame         =   04  ;
    StrategyTrxPI       =   1   ; // trx aléatoire selective, meilleur trx qui a un cout le plut petit
    StrategyFreqPI      =   2   ; // freq best min interference
    StrategyTrxPS       =   1   ; // trx random
    StrategyFreqPS      =   2   ; // freq best min separation
*/





       //.......................... Game 14
/*
    int ApproachGame  =     1   ;
    int NumGame       =     14  ;
    StrategyTrxPI     =     8   ;//choix le trx qui a le plus grand cout
    StrategyFreqPI    =     4   ;//Best frequency in term of NASH
    StrategyTrxPS     =     1   ;//trx random
    StrategyFreqPS    =     4    ;//Best separation in term of NASH
*/
       //.......................... Game 15

/*
    int ApproachGame = 1;
    int NumGame     =   15  ;
    StrategyTrxPI   =   9  ;//Choisir aléatoire
    StrategyFreqPI  =   4   ;//Best frequency in term of NASH
    StrategyTrxPS   =   1   ;//trx random
    StrategyFreqPS  =   4  ;//Best separation in term of NASH
*/
       //.......................... Game 16
  /*
   int ApproachGameEvaluation = 2;
    int ApproachGame  =   1   ;
    int NumGame       =   16  ;
    StrategyTrxPI     =   1   ;//Choisir aléatoire
    StrategyFreqPI    =   6   ;//Best frequency in term of NASH
    StrategyTrxPS     =   1   ;//trx random
    StrategyFreqPS    =   6  ;//Best separation in term of NASH
  */

    //  int ApproachGameEvaluation = 11; //une solution Nash-
    //int ApproachGameEvaluation = 1; //Nash-ensemble
    //int ApproachGameEvaluation = 2; //pareto-ensemble
   // int ApproachGameEvaluation = 21; //pareto-une solution-meilleur solution qui a le plus grand HV
    // int ApproachGameEvaluation = 22; //pareto-une solution-meilleur solution qui a le plus petit ecart
    //int ApproachGameEvaluation = 23; //pareto-une solution-meilleur solution qui a le plus petit nash




    /*
    int ApproachGameEvaluation = 2;
    int ApproachGame  =   1   ;
    int NumGame       =   266  ;
    StrategyTrxPI     =   1   ;//Choisir aléatoire
    StrategyFreqPI    =   6   ;//Best frequency in term of NASH
    StrategyTrxPS     =   1   ;//trx random
    StrategyFreqPS    =   6  ;//Best separation in term of NASH
    */
       //.......................... Game 17
    /*int ApproachGame  =   1   ;
    int NumGame       =   17  ;
    StrategyTrxPI     =   1   ;//Choisir aléatoire
    StrategyFreqPI    =   5   ;//Best frequency in term of NASH
    StrategyTrxPS     =   1   ;//trx random
    StrategyFreqPS    =   6  ;//Best separation in term of hv
*/
/*
       //.......................... Game 18
    int ApproachGame  =   1   ;
    int NumGame       =   18  ;
    StrategyTrxPI     =   1   ;//Choisir aléatoire
    StrategyFreqPI    =   5   ;//Best frequency in term of NASH
    StrategyTrxPS     =   1   ;//trx random
    StrategyFreqPS    =   4 ;//Best separation in term of NASH
*/
       //.......................... Game 19
    /*int ApproachGame  =   1   ;
    int NumGame       =   19 ;
    StrategyTrxPI     =   1   ;//Choisir aléatoire
    StrategyFreqPI    =   4   ;//Best frequency in term of NASH
    StrategyTrxPS     =   1   ;//trx random
    StrategyFreqPS    =   5 ;//Best separation in term of NASH
*/
       //.......................... Game 20
   /* int ApproachGame  =   1   ;
    int NumGame       =   20 ;
    StrategyTrxPI     =   1   ;//Choisir aléatoire
    StrategyFreqPI    =   6  ;//Best frequency in term of NASH
    StrategyTrxPS     =   1   ;//trx random
    StrategyFreqPS    =   5 ;//Best separation in term of NASH
 */

           //.......................... Game 21
   /* int ApproachGame  =   1   ;
    int NumGame       =   21 ;
    StrategyTrxPI     =   1   ;//Choisir aléatoire
    StrategyFreqPI    =   6  ;//Best frequency in term of NASH
    StrategyTrxPS     =   1   ;//trx random
    StrategyFreqPS    =   4 ;//Best separation in term of NASH
    */
         //.......................... Game 22
   /*int ApproachGame  =   1   ;
    int NumGame       =   22;
    StrategyTrxPI     =   1   ;//Choisir aléatoire
    StrategyFreqPI    =   4  ;//Best frequency in term of NASH
    StrategyTrxPS     =   1   ;//trx random
    StrategyFreqPS    =   5 ;//Best separation in term of NASH
*/
         //.......................... Game 23
  /* int ApproachGame  =   1   ;
    int NumGame       =   23;
    StrategyTrxPI     =   1   ;//Choisir aléatoire
    StrategyFreqPI    =   2  ;//Best frequency in term of NASH
    StrategyTrxPS     =   1   ;//trx random
    StrategyFreqPS    =   5 ;//Best separation in term of NASH
*/
           //.......................... Game 55 *****meilleur combinaison***********
  /* int ApproachGame  =   1   ;
    int NumGame       =   55;
    StrategyTrxPI     =   1   ;//Choisir aléatoire
    StrategyFreqPI    =   6 ;//Best frequency in term of NASH
    StrategyTrxPS     =   1   ;//trx random
    StrategyFreqPS    =   5 ;//Best separation in term of NASH
    */
 //*****************************************************************
      /*int ApproachGame  =   1   ;
    int NumGame       =   65;
    StrategyTrxPI     =   1   ;//Choisir aléatoire
    StrategyFreqPI    =  6 ;//Best frequency in term of NASH
    StrategyTrxPS     =   1   ;//trx random
    StrategyFreqPS    =   5 ;//Best separation in term of NASH*/

     /*int ApproachGame  =   1   ;
    int NumGame       =   56;
    StrategyTrxPI     =   1   ;//Choisir aléatoire
    StrategyFreqPI    =  5 ;//Best frequency in term of NASH
    StrategyTrxPS     =   1   ;//trx random
    StrategyFreqPS    =   6 ;//Best separation in term of NASH
*/



    //#############################################################################################
    //cout << "G->PI->QLPI->Qtable->size()" << G->PI->QLPI->Qtable->size()<<endl;

   // cout<<"##############################Tester l'ensemble des action Affichahe l'ensemble des action ##################################"<<endl;
    //cout << "G->QL->ActionsSet->size()" << G->QL->ActionsSet.size()<<endl;



     //##################################################################################################

    //cout<<"############################## Tester la configuration de Qtable ############################"<<endl;
   ShowSolution(StrategyTrxPI,StrategyTrxPS,  G->solution,ApproachGameEvaluation,instance,elapsed_secs,max_gen,epsilon);
   G->QL->ShowQtable(ApproachGameEvaluation,instance,elapsed_secs,max_gen,epsilon);
  // G->ShowMemoryOccurenceUseTRX();
     //##########################################################################################

 /*Test Minimum occurence strategy ========================
  G->initVectorMemoryOccurenceUseTRX(afpProblem);
  G->ShowMemoryOccurenceUseTRX();
  //vector <pair<TRXs,int>> MemoryOccurenceUseTRX;
  TRXs trx;
  pair <TRXs,int> t;
  t = G->MemoryOccurenceUseTRX.at(8);
  G->UpdateOccurenceTRX( t.first, 0);
  TRXs T;
 //  t = G->MemoryOccurenceUseTRX.at(5);
 // T = t.first;
  G->GetTRXMinimumUsed(T);
  cout << "TRX MINIMUM OCCURENCE IS   (TRX; occurrence) : " << T.trxID << endl;//<<"," << t.second << endl;
  */
  //G->ShowMemoryOccurenceUseTRX();

     //######################### Tester GetMaxQValue ###########################################
    /*
     Action CorrespondingAction ;
     State s;
     s.UnTreatedTRXNumb = 1;
     double val = G->PI->QLPI->GetMaxQValue(s, CorrespondingAction); //Récupérer la valeur  de Qvalue max et son action
     cout << " (val,CorrespondingAction.ActFreq) : (" << val  << "," << CorrespondingAction.ActFreq <<")"<<endl;
     */
     //#####################################################################################"
      //######################### Tester double AGENTQL::GetQtarget(State sdash , Action & CorrespondingMaxAction) ###########################################
    /*
     Action CorrespondingAction ;
     State s;
     s.UnTreatedTRXNumb = 1;
     double val = G->PI->QLPI->GetQtarget(s , CorrespondingAction); //Récupérer la valeur  de Qvalue max et son action
     cout << " (Qtarget,CorrespondingAction.ActFreq) : (" << val  << "," << CorrespondingAction.ActFreq <<")"<<endl;
    */
     //#####################################################################################"

         //######################### Tester    GetIndexPairStateAction(pair < State ,Action > PairStateAction); ###########################################

    /* pair < State ,Action > PairStateAction;
     PairStateAction.first.UnTreatedTRXNumb = 0;
     PairStateAction.second.ActFreq = 0;
     int index =  G->PI->QLPI->GetIndexPairStateAction(PairStateAction);
     cout << " GetIndexPairStateAction(PairStateAction) : " << index  << endl;*/

     //#####################################################################################"







    //--------------------------
    //-----------------------afficher la solution ---------------
        /*ofstream ResultFile;
    string path="Exemple/solution_.txt";
     ResultFile.open(path.c_str(),std::ios::app);
     for(i = 0 ; i < afpProblem->trxs.size(); i ++)
     {
         ResultFile << G->solution->plan->at(i)<<endl;
     }
  Individual * solution2;
        //à chaque génération, on initialise  la solution(individual)
        solution2 = new Individual();
        solution2->plan = new vector<int>(afpProblem->trxs.size());
        solution->planCC = new vector<double>(afpProblem->trxs.size());

        for(k=0;k<solution->plan->size();k++)
        {
            solution->plan->at(k)=-1;
            solution->planCC->at(k)=0.0;
            solution ->PIObj = 0.0 ;
            solution->PSObj = 0.0;

        }
ResultFile.close();*/
    //------------------------------------------------

   // cout << "afpProblem->interferenceBasedFitness(G->solution) :" << afpProblem->interferenceBasedFitness(G->solution) <<endl;
    delete G;
     //const pair<double,double> MinSeattle = (4000,15) ;
    /*pair<double,double> MinSeattle;
     MinSeattle.first = 4000.0;
     MinSeattle.second = 15.0 ;
      //const pair<double,double> MaxSeattle =(10000,100);
     pair<double,double> MaxSeattle;
     MaxSeattle.first = 70000.0;
     MaxSeattle.second = 200.0;
   // const pair<double,double> MaxSeattle =(70000,200);
    pair < double, double > R;// est le point de référence ; la valeur max
      R.first = (MaxSeattle.first - MinSeattle.first)/(MaxSeattle.first-MinSeattle.first);
      R.second = (MaxSeattle.second - MinSeattle.second)/(MaxSeattle.second-MinSeattle.second);
      cout << "R.first "<< R.first <<endl;
      cout << "R.second "<< R.second <<endl;*/
    //++++++++++++++++++++++++++++++++++++++++++++
    //++++++++++++++++++++normalized values ++++++++++++++++++
   // const pair<double,double> MinSeattle = (4000,15) ;
   // const pair<double,double> MaxSeattle =(70000,200);
    /* pair<double,double> MinSeattle;
     MinSeattle.first = 1000.0;
     MinSeattle.second = 10.0 ;
   //const pair<double,double> MaxSeattle =(10000,100);
     pair<double,double> MaxSeattle;
     MaxSeattle.first = 4000.0;
     MaxSeattle.second = 40.0;

     /*const pair<double,double> MinDenver = (130000,1200) ;
    const pair<double,double> MaxDenver =(300000,2500);*/

   /* double CI,CS;
      vector < pair<double,double>  > paircost;
      paircost.reserve(2);
      paircost.push_back({1500,10});
      paircost.push_back({1400,15});
      int i;
      //+++++++++++++++++++++++++++++++++
     cout << " ....affichage avant la normalisation ..." <<endl;
      for(i = 0 ; i < paircost.size() ; i++)
      {
          cout << " paircost.at(i).first :" << paircost.at(i).first <<endl;
           cout << " paircost.at(i).second :" << paircost.at(i).second <<endl;
      }
       // cout << " ....affichage après la normalisation ..." <<endl;++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
      // Normaliser les valeurs

      Normalize(paircost,MinSeattle,MaxSeattle);

        //+++++++++++++++++++++++++++++++++++++++++++++++++++++
     cout << " ....affichage avant la normalisation ..." <<endl;
      for(i = 0 ; i < paircost.size() ; i++)
      {
          cout << " paircost.at(i).first :" << paircost.at(i).first <<endl;
           cout << " paircost.at(i).second :" << paircost.at(i).second <<endl;
      }
      //+++++++++++++++++++++++ calculer l hypervolume ++++++++++++
      //++ 0.trier les valeur selon un ordre décroissant de +++++++++++
      sort(paircost.begin(),paircost.end(),my_cmpDoubleDoublePairHighFirst);
      //++++++++++++++++++++++++++++++++++++++++++++++++++++++++
       cout << " ....affichage après le tri ..." <<endl;
      for(i = 0 ; i < paircost.size() ; i++)
      {
          cout << " paircost.at(i).first :" << paircost.at(i).first <<endl;
           cout << " paircost.at(i).second :" << paircost.at(i).second <<endl;
      }

      // ++++++++++ 1. Choisir le point de référence R, soit R = MaxSeattle
      pair < double, double > R;// est le point de référence ; la valeur max
      R = MaxSeattle;
      //++++++++++++ 2. Normaliser les valeur de R ++++++++++
      R.first = (R.first - MinSeattle.first) / (MaxSeattle.first - MinSeattle.second);
      R.second = (R.second - MinSeattle.second) / (MaxSeattle.first - MinSeattle.second);
      cout << "R.first :"<< R.first << endl;
      cout << "R.second :"<< R.second << endl;
      //+++++++++++++ 3. Calculer l hypervolume ++++++++++++++++++++
      double HV = 0.0 ; //hypervolume

      HV = Hypervolume(paircost , R);
      cout << "HV = " << HV <<endl;*/
 //.........................................
   // verifier veccost...................................................

   /* vector<TRXs> LTrxNTreateds;
    vector <int> LTrxNtreatedsID ;
    LTrxNTreateds.reserve(3);
    LTrxNTreateds.push_back(afpProblem->trxs[0]);
    LTrxNTreateds.push_back(afpProblem->trxs[1]);
    LTrxNTreateds.push_back(afpProblem->trxs[2]);
    Individual * solutionTemp;
    //................INITIALISATION de la solution.......à chaque génération, on initialise  la solution(individual)
    solutionTemp = new Individual();
    solutionTemp->plan = new vector<int>(3);
    solutionTemp->planCC = new vector<double>(3);
    solutionTemp->PlanAffect=new vector< pair<int,int> > ();

    for(i=0;i<3;i++)
    {
        solutionTemp->plan->at(i)= -1 ;
        solutionTemp->planCC->at(i)= 0.0 ;
        if (solutionTemp->plan->at(i)!=-1)//si la case dans le plan n'est pas vide on remplie le planAffect
            {
                solutionTemp->PlanAffect->push_back({i,solutionTemp->plan->at(i)});
                //cout << "i ..." << i << endl;
            }
    }
    cout <<" 1.solutionTemp->PIObj = "<< solutionTemp->PIObj  <<endl;
     cout <<" 1.solutionTemp->PSObj = "<< solutionTemp->PIObj  <<endl;
    solutionTemp->plan->at(0) = 591;
    solutionTemp->PIObj = afpProblem->ComputeSolutionInterference(solutionTemp);
     solutionTemp->PSObj = afpProblem->ComputeSolutionSeparationCost(solutionTemp);
    cout <<" 2.solutionTemp->PIObj = "<< solutionTemp->PIObj  <<endl;
    cout <<" 2.solutionTemp->PSObj = "<< solutionTemp->PSObj  <<endl;
    solutionTemp->plan->at(1) = 591;
    int victimTrx = 2;
    double cost = 0.0 ;
    double costSep = 0.0;
    int victimFrequency = 591;
    solutionTemp->PIObj = afpProblem->ComputeSolutionInterference(solutionTemp);
    solutionTemp->PSObj = afpProblem->ComputeSolutionSeparationCost(solutionTemp);
     solutionTemp->plan->at(2) = 591;
    for(i = 0 ; i < solutionTemp->plan->size(); i++)
    {
        if(solutionTemp->plan->at(i)!=-1)
        {
           int interfererFrequency = solutionTemp->plan->at(i);
           int interfererTrx = i;
           if(interfererTrx!=victimTrx)
            {
                // si dans la meme fréquence
                cost = cost + afpProblem->computeChannelInterference(victimFrequency ,interfererFrequency, victimTrx, interfererTrx)+
                afpProblem->computeChannelInterference(interfererFrequency,victimFrequency ,interfererTrx, victimTrx);
                //les 2 trx sont dans le meme secteur
               if(afpProblem->trxs[victimTrx].sectorID == afpProblem->trxs[interfererTrx].sectorID)
                {
                    //on teste si la contraite de separation co-secteur est respecté!!
                    if (abs (solutionTemp->plan->at(victimTrx)- solutionTemp->plan->at(interfererTrx))< 3)//contrainte co secteur violée
                    {
                        costSep = costSep +1.0;
                    }
                }// secteur different
                else
                {
                    if(afpProblem->trxs[victimTrx].siteID  == afpProblem->trxs[interfererTrx].siteID)
                    {
                        //on teste si la contrainte de separation co-site est respectée!!
                        if (abs (solutionTemp->plan->at(victimTrx)- solutionTemp-> plan->at(interfererTrx))< 2)//contrainte co secteur violée
                        {
                            costSep= costSep +1.0;
                        }
                    }//
                }

            }
        }
    }
    //le cout final de la solution
    cost = solutionTemp->PIObj + cost;
    costSep = solutionTemp->PSObj + costSep;
    solutionTemp->PIObj = afpProblem->ComputeSolutionInterference(solutionTemp);
    solutionTemp->PSObj = afpProblem->ComputeSolutionSeparationCost(solutionTemp);
    cout <<"°°°°°°°°°°° Comparaison °°°°°°°°°°°°°" << endl;
    cout <<" 3.solutionTemp->PIObj = "<< solutionTemp->PIObj  <<endl;
    cout <<" 3.solutionTemp->PSObj = "<< solutionTemp->PSObj  <<endl;
    cout <<"cost = " << cost << endl;
    cout <<"costsep = " << costSep << endl;
*/


>>>>>>> 0514ea9fae0f841576757defb02235a9189b0fad
}//main
