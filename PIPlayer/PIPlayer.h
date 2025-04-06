<<<<<<< HEAD
#ifndef PIPLAYER_H_INCLUDED
#define PIPLAYER_H_INCLUDED
#include <iostream>
#include <fstream>
#include <ctime>
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "../Individual/Individual.h"
#include "../AFP/AFP.h"
#include "../Commun/Commun.h"
//++++++++++++++++++++++++++++++++++24-05-2021 ++++++++++++++

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
using namespace std;
//extern void AddSolTrxFrequency(Individual* &Sol,TRXs trx ,int f);
class PIPlayer {
	public:
		PIPlayer();
		PIPlayer(AFP * afpProblem, const int max_gen,int IndexLearn);
		~PIPlayer();
		//Fonctions
		double PIEvaluateObj(Individual* &Sol);
		//int IndexMinValue(vector<double>* vect);//fonction pour r��cup�rer l'index de la valeur minimale
		//Proc�dures
		void Play(string instance,int StrategyTrx, int StrategyFreq,TRXs &trx, vector<TRXs> &LTrxNTreateds,Individual* &Sol, AFP * afpProblem);


		void PIChooseTrx(int Strategy,vector<TRXs> LTrxNTreateds,TRXs &trx,AFP* afpProblem,Individual* &Sol);// Proc�dure pour choisir al�atoirement un  trx non trait�
        void ChooseTrxRandom(vector<TRXs> LTrxNTreateds,TRXs &trx);
        void ChooseTrxMostDistant(Individual * solution, AFP * afpProblem,  vector<TRXs> LTrxNTreateds, TRXs &trx);
	//	void PIChooseFrequency(int Strategy,TRXs trx,int &f);//proc�dure pour choisir la meilleur fr�quence de trx
        void PIChooseFrequency(string instance,int StrategyFreq,TRXs trx,Individual * &solution, AFP * afpProblem,int &f);
        void ChooseFrequencyRandom(TRXs trx, int &f);
        //--------------------------------------------------------------------
        void PIBestObjective(vector <Individual*> solutionSs, Individual* &BestSol  );
        //------------------------------------------------------------
        // ajout� le 28-3-2019 -------------------------------

        void PlayV2(string instance,int StrategyTrx, int StrategyFreq,TRXs &trx, vector<int> &LTrxNTreateds,Individual* &Sol, AFP * afpProblem);
        void PIChooseTrxV2(int Strategy,vector<int> LTrxNTreateds,TRXs &trx,AFP* afpProblem,Individual* &Sol);// Proc�dure pour choisi
        void PlayReaffect(string instance,int StrategyTrx, int StrategyFreq, TRXs &trx ,vector<TRXs> &LTrxNTreateds, Individual* &Sol, AFP * afpProblem);
        void PIReassign(Individual* &Sol, AFP * afpProblem,int StrategyFreq);// modifier la solution actuelle en choisisant un trx et le modifier

        //variables
		int IdPlayer;

		int IndexLearnPI;//indicateur d'apprentissage ; indexLearnPI = 1 si PI veut Apprendre; indexLearnPI= 0 ; si PI ne veut pas apprendre
        //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Ajout� le 27 - 6 -2021 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        vector <int> * PInterventionTRXOrder;
};



#endif // PIPLAYER_H_INCLUDED
=======
#ifndef PIPLAYER_H_INCLUDED
#define PIPLAYER_H_INCLUDED
#include <iostream>
#include <fstream>
#include <ctime>
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "../Individual/Individual.h"
#include "../AFP/AFP.h"
#include "../Commun/Commun.h"
//++++++++++++++++++++++++++++++++++24-05-2021 ++++++++++++++

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
using namespace std;
//extern void AddSolTrxFrequency(Individual* &Sol,TRXs trx ,int f);
class PIPlayer {
	public:
		PIPlayer();
		PIPlayer(AFP * afpProblem, const int max_gen,int IndexLearn);
		~PIPlayer();
		//Fonctions
		double PIEvaluateObj(Individual* &Sol);
		//int IndexMinValue(vector<double>* vect);//fonction pour r��cup�rer l'index de la valeur minimale
		//Proc�dures
		void Play(string instance,int StrategyTrx, int StrategyFreq,TRXs &trx, vector<TRXs> &LTrxNTreateds,Individual* &Sol, AFP * afpProblem);


		void PIChooseTrx(int Strategy,vector<TRXs> LTrxNTreateds,TRXs &trx,AFP* afpProblem,Individual* &Sol);// Proc�dure pour choisir al�atoirement un  trx non trait�
        void ChooseTrxRandom(vector<TRXs> LTrxNTreateds,TRXs &trx);
        void ChooseTrxMostDistant(Individual * solution, AFP * afpProblem,  vector<TRXs> LTrxNTreateds, TRXs &trx);
	//	void PIChooseFrequency(int Strategy,TRXs trx,int &f);//proc�dure pour choisir la meilleur fr�quence de trx
        void PIChooseFrequency(string instance,int StrategyFreq,TRXs trx,Individual * &solution, AFP * afpProblem,int &f);
        void ChooseFrequencyRandom(TRXs trx, int &f);
        //--------------------------------------------------------------------
        void PIBestObjective(vector <Individual*> solutionSs, Individual* &BestSol  );
        //------------------------------------------------------------
        // ajout� le 28-3-2019 -------------------------------

        void PlayV2(string instance,int StrategyTrx, int StrategyFreq,TRXs &trx, vector<int> &LTrxNTreateds,Individual* &Sol, AFP * afpProblem);
        void PIChooseTrxV2(int Strategy,vector<int> LTrxNTreateds,TRXs &trx,AFP* afpProblem,Individual* &Sol);// Proc�dure pour choisi
        void PlayReaffect(string instance,int StrategyTrx, int StrategyFreq, TRXs &trx ,vector<TRXs> &LTrxNTreateds, Individual* &Sol, AFP * afpProblem);
        void PIReassign(Individual* &Sol, AFP * afpProblem,int StrategyFreq);// modifier la solution actuelle en choisisant un trx et le modifier

        //variables
		int IdPlayer;

		int IndexLearnPI;//indicateur d'apprentissage ; indexLearnPI = 1 si PI veut Apprendre; indexLearnPI= 0 ; si PI ne veut pas apprendre
        //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Ajout� le 27 - 6 -2021 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        vector <int> * PInterventionTRXOrder;
};



#endif // PIPLAYER_H_INCLUDED
>>>>>>> 0514ea9fae0f841576757defb02235a9189b0fad
