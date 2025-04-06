<<<<<<< HEAD
#ifndef PSPLAYER_H_INCLUDED
#define PSPLAYER_H_INCLUDED
#include <iostream>
#include <fstream>
#include <algorithm>    // std::find

//#include "PIPlayer.cpp"
#include "../Individual/Individual.h"
#include "../AFP/AFP.h"
//++++++++++++++++++++++++++++++++++16-06-2021 ++++++++++++++

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
using namespace std;

class PSPlayer {
	public:
	    PSPlayer();
		PSPlayer(AFP * afpProblem, const int max_gen,int indexLearn);
		~PSPlayer();
       //fonctions
       //extern AddSolTrxFrequency(Individual* &Sol,TRXs trx ,int f);
        double PSEvaluateObj(Individual* &Sol);//pour evaluer la solution Sol
        //Procédures
        void Play(string instance,int StrategyTrx, int StrategyFreq,vector<TRXs> &LTrxNTreateds,TRXs &trx,Individual * &Sol,AFP * afpProblem);//pour joueur
        void PSChooseTrx(AFP * afpProblem,int Strategytrx, vector<TRXs> LTrxNTreateds,TRXs &trx);
        void PSChooseFrequency(string instance,int StrategyFreq,TRXs trx,int &f,Individual * &solution,AFP * afpProblem);
        void PSBestObjective(vector <Individual*> solutionSs, Individual* &BestSol  );
        //ajouter le 04-3-2019 ---
        void PSUpdateTRxFrequencyErase(TRXs &trx, int f, int alpha);
        void PSUpdateTRxFrequency(vector<TRXs> &LTrxNTreateds,AFP * afpProblem,TRXs &trx,int f, int update);
        //variables
		int IdPlayer;
		 //variable

		int IndexLearnPS;//indicateur d'apprentissage ; indexLearnPI = 1 si PI veut Apprendre; indexLearnPI= 0 ; si PI ne veut pas apprendre
 vector <int> * PSInterventionTRXOrder;
};



#endif // PIPLAYER_H_INCLUDED
=======
#ifndef PSPLAYER_H_INCLUDED
#define PSPLAYER_H_INCLUDED
#include <iostream>
#include <fstream>
#include <algorithm>    // std::find

//#include "PIPlayer.cpp"
#include "../Individual/Individual.h"
#include "../AFP/AFP.h"
//++++++++++++++++++++++++++++++++++16-06-2021 ++++++++++++++

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
using namespace std;

class PSPlayer {
	public:
	    PSPlayer();
		PSPlayer(AFP * afpProblem, const int max_gen,int indexLearn);
		~PSPlayer();
       //fonctions
       //extern AddSolTrxFrequency(Individual* &Sol,TRXs trx ,int f);
        double PSEvaluateObj(Individual* &Sol);//pour evaluer la solution Sol
        //Procédures
        void Play(string instance,int StrategyTrx, int StrategyFreq,vector<TRXs> &LTrxNTreateds,TRXs &trx,Individual * &Sol,AFP * afpProblem);//pour joueur
        void PSChooseTrx(AFP * afpProblem,int Strategytrx, vector<TRXs> LTrxNTreateds,TRXs &trx);
        void PSChooseFrequency(string instance,int StrategyFreq,TRXs trx,int &f,Individual * &solution,AFP * afpProblem);
        void PSBestObjective(vector <Individual*> solutionSs, Individual* &BestSol  );
        //ajouter le 04-3-2019 ---
        void PSUpdateTRxFrequencyErase(TRXs &trx, int f, int alpha);
        void PSUpdateTRxFrequency(vector<TRXs> &LTrxNTreateds,AFP * afpProblem,TRXs &trx,int f, int update);
        //variables
		int IdPlayer;
		 //variable

		int IndexLearnPS;//indicateur d'apprentissage ; indexLearnPI = 1 si PI veut Apprendre; indexLearnPI= 0 ; si PI ne veut pas apprendre
 vector <int> * PSInterventionTRXOrder;
};



#endif // PIPLAYER_H_INCLUDED
>>>>>>> 0514ea9fae0f841576757defb02235a9189b0fad
