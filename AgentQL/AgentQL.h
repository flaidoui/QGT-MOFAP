#ifndef AGENTQL_H
#define AGENTQL_H

#include <string>
#include <vector>
#include <map>
#include <set>
<<<<<<< HEAD

//====================================
#include "../Individual/Individual.h"
#include "../AFP/AFP.h"
//=====================================
using namespace std;
const float GAMMA = 0.9;
const float ALPHA = 0.9;
//-----------------------------------------
//strategy frequency
//freqstat=1 Random, reqnum2 Cost .freqnum4 Nash .freqnum 6 Hypervolume .Dominance rank . 550

//---------------------------------
/*struct ActionPI {
    int TRXStratPI;
    int FreqStratPI;
};
struct ActionPS {
    int TRXStratPS;
    int FreqStratPS;
};
//---------------------------------------
*/
// on définit l'action comme étant le coupe (stratégie trx, strategie fréquence)
struct Action
{
     int ActFreq;
    // int ActTRX;
};
//--------------------------------
struct State
{
    int  UnTreatedTRXNumb;
   // TRXs CurrentTRX;
};
//-------------------------------------------
class AGENTQL {
    public:
    AGENTQL(AFP * afpProblem, const int max_gen);//IndexPlayer = 1 si PI est est entrain de joueur ;IndexPlayer = ; si PS est entrain de joueur;
    //IndexPlayer = -1; si aucun joeueur n'est entrain de joueur
    ~AGENTQL();
    //------------------------------------------------------------------------------------------------------------------
    //--------------------------------------------------------------------------------------------------------------
   // vector<int,int> StatesSet; //vecteurs etats : solutions+strategies (TRX,Freq) PI + strategy (TRX,Freq)PS
    vector < Action >  ActionsSet; //vecteurs actions; prédéfinies à l'avance
    double QGAMMA;//combiengt on prète importance des informations à long terme; glment = 0.9
    double QALPHA;//glment =0.01
    //-------------------------------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------------------------------
  // vector < pair < pair < State ,Action > , double > >  Qtable; //matrice (state, action)== (currentsol, action effectuée)== qvalue (valeur hv calculée)  //
   vector < pair < pair < State, Action> , double > >  Qtable;
    //vector <double>* q_table;
   // vector < pair < int, double[][] ;
   // vector < pair < pair < State, Action> , double > > * QDashtable;
    void InitQtable(AFP * afpProblem, const int max_gen);
    Action GetPossibleAction();// recupérer l'action: behavior policy
    double GetMaxQValue(State s, Action & CorrespondingAction);//récupérer la valeur max de Qtable et retourner l'action y associé  dans CorrespondingAction
    void UpdateQtable(double Reward, pair < State ,Action > PairStateAction,double Qtarget);//mise à jour de la table Qtable
    //bool CheckElementQtable(pair < State, Action> Mypair,int & IndexElement); // on vérifie si l'état  existe déja dans Qtable;
    void ObserveReward(int indexplayer,Individual* SolRef, Individual* Sol, double &Reward, string instance);
    void ShowQtable(int ApproachGameEvaluation,string instance,double elapsed_secs,const int  max_gen,const double  epsilon);

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~18- 8-2021 ~~~~~~~~~~~~~~~~~~~~~~~~é
    //int GetIndexState(State s);//retourner l indice dans la table Q de l'état s
    double GetQtarget(State sdash,Action & CorrespondingMaxAction); //retourner Qtarget lorsqu'on est dans l'etat sdash, on recupère l'action
                                                        //qui correspond au plus grande valeur de Q

    bool CheckFinalState(vector<TRXs> LTrxNTreateds);
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~24-8-2021 ~~~~~~~~~~~~~~~~~~~~~~é
    int GetIndexPairStateAction(pair < State ,Action > PairStateAction);
    //----------------------------------------------------------------------------
    //-----------------------------------------------------------------------------
     bool CheckAction(Action A);
         //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ 01 -07-02021
    int GetIndexAction(Action Act);
     //void ShowQDashtable();

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~04 - 07 -2021 ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //void PenalyzeActions( vector <pair <State,Action> > * vect, Individual* solutionRef, int IndexPlayer);
};
#endif
=======

//====================================
#include "../Individual/Individual.h"
#include "../AFP/AFP.h"
//=====================================
using namespace std;
const float GAMMA = 0.9;
const float ALPHA = 0.9;
//-----------------------------------------
//strategy frequency
//freqstat=1 Random, reqnum2 Cost .freqnum4 Nash .freqnum 6 Hypervolume .Dominance rank . 550

//---------------------------------
/*struct ActionPI {
    int TRXStratPI;
    int FreqStratPI;
};
struct ActionPS {
    int TRXStratPS;
    int FreqStratPS;
};
//---------------------------------------
*/
// on définit l'action comme étant le coupe (stratégie trx, strategie fréquence)
struct Action
{
     int ActFreq;
    // int ActTRX;
};
//--------------------------------
struct State
{
    int  UnTreatedTRXNumb;
   // TRXs CurrentTRX;
};
//-------------------------------------------
class AGENTQL {
    public:
    AGENTQL(AFP * afpProblem, const int max_gen);//IndexPlayer = 1 si PI est est entrain de joueur ;IndexPlayer = ; si PS est entrain de joueur;
    //IndexPlayer = -1; si aucun joeueur n'est entrain de joueur
    ~AGENTQL();
    //------------------------------------------------------------------------------------------------------------------
    //--------------------------------------------------------------------------------------------------------------
   // vector<int,int> StatesSet; //vecteurs etats : solutions+strategies (TRX,Freq) PI + strategy (TRX,Freq)PS
    vector < Action >  ActionsSet; //vecteurs actions; prédéfinies à l'avance
    double QGAMMA;//combiengt on prète importance des informations à long terme; glment = 0.9
    double QALPHA;//glment =0.01
    //-------------------------------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------------------------------
  // vector < pair < pair < State ,Action > , double > >  Qtable; //matrice (state, action)== (currentsol, action effectuée)== qvalue (valeur hv calculée)  //
   vector < pair < pair < State, Action> , double > >  Qtable;
    //vector <double>* q_table;
   // vector < pair < int, double[][] ;
   // vector < pair < pair < State, Action> , double > > * QDashtable;
    void InitQtable(AFP * afpProblem, const int max_gen);
    Action GetPossibleAction();// recupérer l'action: behavior policy
    double GetMaxQValue(State s, Action & CorrespondingAction);//récupérer la valeur max de Qtable et retourner l'action y associé  dans CorrespondingAction
    void UpdateQtable(double Reward, pair < State ,Action > PairStateAction,double Qtarget);//mise à jour de la table Qtable
    //bool CheckElementQtable(pair < State, Action> Mypair,int & IndexElement); // on vérifie si l'état  existe déja dans Qtable;
    void ObserveReward(int indexplayer,Individual* SolRef, Individual* Sol, double &Reward, string instance);
    void ShowQtable(int ApproachGameEvaluation,string instance,double elapsed_secs,const int  max_gen,const double  epsilon);

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~18- 8-2021 ~~~~~~~~~~~~~~~~~~~~~~~~é
    //int GetIndexState(State s);//retourner l indice dans la table Q de l'état s
    double GetQtarget(State sdash,Action & CorrespondingMaxAction); //retourner Qtarget lorsqu'on est dans l'etat sdash, on recupère l'action
                                                        //qui correspond au plus grande valeur de Q

    bool CheckFinalState(vector<TRXs> LTrxNTreateds);
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~24-8-2021 ~~~~~~~~~~~~~~~~~~~~~~é
    int GetIndexPairStateAction(pair < State ,Action > PairStateAction);
    //----------------------------------------------------------------------------
    //-----------------------------------------------------------------------------
     bool CheckAction(Action A);
         //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ 01 -07-02021
    int GetIndexAction(Action Act);
     //void ShowQDashtable();

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~04 - 07 -2021 ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //void PenalyzeActions( vector <pair <State,Action> > * vect, Individual* solutionRef, int IndexPlayer);
};
#endif
>>>>>>> 0514ea9fae0f841576757defb02235a9189b0fad
