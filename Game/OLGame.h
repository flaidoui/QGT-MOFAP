<<<<<<< HEAD
#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <iostream>
#include <fstream>
//-------------------------------
#include "../PIPlayer/PIPlayer.h"
#include "../PSPlayer/PSPlayer.h"
#include "../Individual/Individual.h"
#include "../AFP/AFP.h"
//------------------------------
//#include "../AgentQL/AgentQL.h"
//-------------------


using namespace std;
//extern void AddSolTrxFrequency(Individual* &Sol,TRXs trx ,int f);
class Game
{


    public:
    //Game();
    Game(AFP * afpProblem, const int max_gen);
    ~Game();
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    Individual * solution;
    vector<Individual*> BestsolutionSs;
    PIPlayer* PI;
    PSPlayer* PS ;
   //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~éé
    void PlayGame(Individual* SolRef, int ApproachGameEvaluation,int ApproachGame,int NumGame, const int max_gen,string instance,AFP* afpProblem,int & StrategyTrxPI,int & StrategyFreqPI,int & StrategyTrxPS,int & StrategyFreqPS);

    void PlayGameSuperp(int ApproachGameEvaluation,int ApproachGame,int NumGame,const int max_gen,string instance,AFP* afpProblem,int StrategyTrxPI,int StrategyFreqPI,int StrategyTrxPS,int StrategyFreqPS);
    //GameEvaluation : on utilise dans la boucle externe Nash, on utilise epsilon pour ramener NAsh vers pareto (selectionner les meilleures solutionq
    void GameEvaluation(string instance,const int  max_gen,vector<Individual*> solutionSs,double start, double & elapsed_secs,int & indexNASHEbest, vector <double> & NASHEJ);
   //------------- ajouté  le 26- 4-2019 -----------------
    void GameEvaluationPareto(string instance,const int  max_gen,vector<Individual*> solutionSs,double start, double & elapsed_secs,int & indexNASHEbest, vector <double> & NASHEJ);
   //les meilleures solutions sont les solutions qi se trouve dans le front ..
   //---------------Fin 26-4-2019---------------------------------------
   //--------------ajouté le 15-5-2019
    void GameEvaluationParetoEcart(string instance,const int max_gen,vector<Individual*> solutionSs,double start, double & elapsed_secs,int & indexNASHEbest, vector <double> & NASHEJ);
    void GameEvaluationParetoHV(string instance,const int max_gen,vector<Individual*> solutionSs,double start, double & elapsed_secs,int & indexNASHEbest, vector <double> & NASHEJ);
    void GameEvaluationNashOneSol(string instance,const int max_gen,vector<Individual*> solutionSs,double start, double & elapsed_secs,int & indexNASHEbest, vector <double> & NASHEJ);
    //================= fin ajout 15-5-2019 ==============================
    //===============ajouté le 26-6-2019-------------------

    void GameEvaluationParetoUneSolNash(string instance,const int max_gen,vector<Individual*> solutionSs,double start, double & elapsed_secs,int & indexNASHEbest, vector <double> & NASHEJ);

    //=============================================================
    //----------- ajouté le 28-3-2019
    void PlayGameV2(int NumGame, const int max_gen,string instance,AFP* afpProblem,int StrategyTrxPI,int StrategyFreqPI,int StrategyTrxPS,int StrategyFreqPS);
    //°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°° Ajouté le 20 /4 /2019 °°°°°°°°°°°°°°°°°°°°°°°°
    double HV;//hypervolume

    //........................Ajout le 11- 10 -2019 ------------------------------

    void GameEvaluationDistEuclUneSol(string instance,const int max_gen,vector<Individual*> solutionSs,double start, double & elapsed_secs,int & indexNASHEbest, vector <double> & NASHEJ);
    //........................................... Ajout le  27 - 6 -2021 ........................
    void PlayGameNaive(int ApproachGameEvaluation,int ApproachGame,int NumGame, const int max_gen,string instance,AFP* afpProblem,int & StrategyTrxPI,int & StrategyFreqPI,int & StrategyTrxPS,int & StrategyFreqPS);



};

#endif // GAME_H_INCLUDED
=======
#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <iostream>
#include <fstream>
//-------------------------------
#include "../PIPlayer/PIPlayer.h"
#include "../PSPlayer/PSPlayer.h"
#include "../Individual/Individual.h"
#include "../AFP/AFP.h"
//------------------------------
//#include "../AgentQL/AgentQL.h"
//-------------------


using namespace std;
//extern void AddSolTrxFrequency(Individual* &Sol,TRXs trx ,int f);
class Game
{


    public:
    //Game();
    Game(AFP * afpProblem, const int max_gen);
    ~Game();
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    Individual * solution;
    vector<Individual*> BestsolutionSs;
    PIPlayer* PI;
    PSPlayer* PS ;
   //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~éé
    void PlayGame(Individual* SolRef, int ApproachGameEvaluation,int ApproachGame,int NumGame, const int max_gen,string instance,AFP* afpProblem,int & StrategyTrxPI,int & StrategyFreqPI,int & StrategyTrxPS,int & StrategyFreqPS);

    void PlayGameSuperp(int ApproachGameEvaluation,int ApproachGame,int NumGame,const int max_gen,string instance,AFP* afpProblem,int StrategyTrxPI,int StrategyFreqPI,int StrategyTrxPS,int StrategyFreqPS);
    //GameEvaluation : on utilise dans la boucle externe Nash, on utilise epsilon pour ramener NAsh vers pareto (selectionner les meilleures solutionq
    void GameEvaluation(string instance,const int  max_gen,vector<Individual*> solutionSs,double start, double & elapsed_secs,int & indexNASHEbest, vector <double> & NASHEJ);
   //------------- ajouté  le 26- 4-2019 -----------------
    void GameEvaluationPareto(string instance,const int  max_gen,vector<Individual*> solutionSs,double start, double & elapsed_secs,int & indexNASHEbest, vector <double> & NASHEJ);
   //les meilleures solutions sont les solutions qi se trouve dans le front ..
   //---------------Fin 26-4-2019---------------------------------------
   //--------------ajouté le 15-5-2019
    void GameEvaluationParetoEcart(string instance,const int max_gen,vector<Individual*> solutionSs,double start, double & elapsed_secs,int & indexNASHEbest, vector <double> & NASHEJ);
    void GameEvaluationParetoHV(string instance,const int max_gen,vector<Individual*> solutionSs,double start, double & elapsed_secs,int & indexNASHEbest, vector <double> & NASHEJ);
    void GameEvaluationNashOneSol(string instance,const int max_gen,vector<Individual*> solutionSs,double start, double & elapsed_secs,int & indexNASHEbest, vector <double> & NASHEJ);
    //================= fin ajout 15-5-2019 ==============================
    //===============ajouté le 26-6-2019-------------------

    void GameEvaluationParetoUneSolNash(string instance,const int max_gen,vector<Individual*> solutionSs,double start, double & elapsed_secs,int & indexNASHEbest, vector <double> & NASHEJ);

    //=============================================================
    //----------- ajouté le 28-3-2019
    void PlayGameV2(int NumGame, const int max_gen,string instance,AFP* afpProblem,int StrategyTrxPI,int StrategyFreqPI,int StrategyTrxPS,int StrategyFreqPS);
    //°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°° Ajouté le 20 /4 /2019 °°°°°°°°°°°°°°°°°°°°°°°°
    double HV;//hypervolume

    //........................Ajout le 11- 10 -2019 ------------------------------

    void GameEvaluationDistEuclUneSol(string instance,const int max_gen,vector<Individual*> solutionSs,double start, double & elapsed_secs,int & indexNASHEbest, vector <double> & NASHEJ);
    //........................................... Ajout le  27 - 6 -2021 ........................
    void PlayGameNaive(int ApproachGameEvaluation,int ApproachGame,int NumGame, const int max_gen,string instance,AFP* afpProblem,int & StrategyTrxPI,int & StrategyFreqPI,int & StrategyTrxPS,int & StrategyFreqPS);



};

#endif // GAME_H_INCLUDED
>>>>>>> 0514ea9fae0f841576757defb02235a9189b0fad
