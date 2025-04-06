<<<<<<< HEAD
#ifndef COMMUN_H_INCLUDED
#define COMMUN_H_INCLUDED

#include "../Individual/Individual.h"
#include "../AFP/AFP.h"
//-------------------
//#include "PIPlayer.h"

//---------------------

void InitLTrxNTreateds(vector<TRXs> &LTrxNTreateds, AFP * afpProblem);//::c::vérifié::initialiser le vecteur de la liste des trx non traité
void InitLTrxNTreatedsV2(vector<int> &LTrxNTreateds, AFP * afpProblem);
void AddSolTrxFrequency( AFP * afpProblem,Individual* &Sol,TRXs trx ,int f);
void vecmin(vector<double>* x, int & indexmin);//::c vérifé ::
void VecMinValue(vector<double> x, int &index);//::c vérifé ::
void vecmax(vector<double> x, int & indexmax);//retourner la valeur maximale dans un tableau
void vecminInt(vector<int> x, int & indexmin);//retourner l indice de la valeur minimal dans un tableau des entiers
void vecmaxInt(vector<int> x, int & indexmax);//retourner l indice de la valeur maximal dans un tableau des entiers
//mise à jour de la liste des trx non traité; Update= +1 ajout du trx; Update=-1 : suppression de trx de la liste
void UpdateLTrxNTreateds(vector <TRXs> &LTrxNTreateds, TRXs trx,int Update);//::c vérifié::
void UpdateTRxFrequency(TRXs &trx, int f,int Update); //::cvérifé::Retirer f de la liste de fréquence valide de trx
void UpdateTRxFrequencyNew(vector<TRXs> LTrxNTreateds,AFP * afpProblem,TRXs &trx, int f,int Update);
void UpdateTRxFrequencyV3(vector<TRXs> LTrxNTreateds,AFP * afpProblem,TRXs &trx, int f,int Update);
void UpdateAllTRxFrequency(vector <TRXs> &LTrxNTreateds,int  f, int Update);//::c vérifié mise à jour de la fréquence dans tt les trx traités
void UpdateTRxFrequencyEraseAdj(TRXs &trx, int f);//supprimer la fréquence et ses voisin (f+1,f-1) dans la liste des freq Availeble fe trx
//void UpdateTRxFrequency1(TRXs &trx, int f,int Update); //Retirer f de la liste de fréquence valide de trx
int FindTrx(vector <TRXs> LTrxNTreateds, TRXs trx);//::c verifié::
int FindTrxID(vector <TRXs> LTrxNTreateds, int indextrx);//
int FindFrequency(vector<int>* vectFrequency, int f);//c vérifié::
int blockedFrequency(TRXs trx,int f);//::c vérifié::verifier si la fréquence f n'est pac bloquée
//----------------------
//neighborhood=======
int FindTrxFirstNeighbor(AFP * afpProblem,TRXs trx,TRXs trxneighbor);
int FindTrxSecondNeighbor(AFP * afpProblem,int sect,int sectneighbor);
double DistancetowTrxs(AFP * afpProblem,TRXs trxone, TRXs trxtwo);

//====================

bool operator ==( const TRXs &b1, const TRXs &b );
//===============================================
//Afficher résultats
void ShowResult(int ApproachGameEvaluation,string instance,int NumGame,double elapsed_secs,const int  max_gen,const double  epsilon,vector<Individual*> solutionSs,int indexNASHEbest,vector <double> NASHEJ,vector<Individual*> BestsolutionSs, Individual* solution, string path, double HV);
//--------------- ajputé le 28-3-2019
void UpdateTRxFrequencyV32(vector<int> LTrxNTreateds,AFP * afpProblem,TRXs &trx, int f,int Update);
void UpdateLTrxNTreatedsV2(vector <int> &LTrxNTreateds, TRXs trx,int Update);//::c vérifié::
int FindTrxV2(vector <int> LTrxNTreateds, TRXs trx);//::c verifié::
void AddSolTrxFrequencyV2(Individual* &Sol,int trxid ,int f); //Procédure pour affecter f au trx dans la solution
//-----------------------------------------
void Normalize(vector<pair<double,double> > &paircost, pair<double,double> MinT, pair<double,double> MaxT);
double Hypervolume(vector < pair< double, double> > paircost , pair < double,double> R);
//-----------ajouté le 36-4-2019
void NormalizeV2(vector<pair<double,double> > &paircost, pair<double,double> &R);
//----------------------Ajouté le 27-4-2019--------
void vecmaxptr(vector<double>* x, int & indexmax);
//----------fin ajout 27-4-2019 ----------------
//---------------------------   Ajout 03-06-2021 -----------------------------------
void ShowSolution(int StrategyTrxPI,int StrategyTrxPS,Individual* Sol,int ApproachGameEvaluation,string instance,double elapsed_secs,const int  max_gen,const double  epsilon);

//--------------------------- Fin ajout 03-06-2021 -------------------------------
// ------------- ajout 16-6-2021 --------------
int GetSolutionRealSize(Individual* Sol);
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Ajouté le 27-6-2021 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void ShowPlayerInterventionOrder(Individual* Sol,int ApproachGameEvaluation,string instance,double elapsed_secs,const int  max_gen,const double  epsilon, int SizePIInterventionOrder, int SizePSInterventionOrder);
void ShowPlayerTRXOrder(vector <int> *IdTRX,int ApproachGameEvaluation,string instance,double elapsed_secs,const int  max_gen,const double  epsilon);
int GetVectorRealSize(vector <int> * vec);

//============== Ajout le -1-2-2022-----------------------------
void ShowNashvaluersResult(int indexNASHEbest,vector <double> NASHEJ, string path, double HV,vector<Individual*> solutionSs);


//======================================Ajout 16 -3- 2022 ====================================
void ShowResultNorm(int ApproachGameEvaluation,string instance,int NumGame,double elapsed_secs,const int  max_gen,const double epsilon,vector<Individual*> solutionSs,int indexNASHEbest,vector <double> NASHEJ,vector<Individual*> BestsolutionSs, Individual* solution, string path, double HVNorm);
#endif // COMMUN_H_INCLUDED
=======
#ifndef COMMUN_H_INCLUDED
#define COMMUN_H_INCLUDED

#include "../Individual/Individual.h"
#include "../AFP/AFP.h"
//-------------------
//#include "PIPlayer.h"

//---------------------

void InitLTrxNTreateds(vector<TRXs> &LTrxNTreateds, AFP * afpProblem);//::c::vérifié::initialiser le vecteur de la liste des trx non traité
void InitLTrxNTreatedsV2(vector<int> &LTrxNTreateds, AFP * afpProblem);
void AddSolTrxFrequency( AFP * afpProblem,Individual* &Sol,TRXs trx ,int f);
void vecmin(vector<double>* x, int & indexmin);//::c vérifé ::
void VecMinValue(vector<double> x, int &index);//::c vérifé ::
void vecmax(vector<double> x, int & indexmax);//retourner la valeur maximale dans un tableau
void vecminInt(vector<int> x, int & indexmin);//retourner l indice de la valeur minimal dans un tableau des entiers
void vecmaxInt(vector<int> x, int & indexmax);//retourner l indice de la valeur maximal dans un tableau des entiers
//mise à jour de la liste des trx non traité; Update= +1 ajout du trx; Update=-1 : suppression de trx de la liste
void UpdateLTrxNTreateds(vector <TRXs> &LTrxNTreateds, TRXs trx,int Update);//::c vérifié::
void UpdateTRxFrequency(TRXs &trx, int f,int Update); //::cvérifé::Retirer f de la liste de fréquence valide de trx
void UpdateTRxFrequencyNew(vector<TRXs> LTrxNTreateds,AFP * afpProblem,TRXs &trx, int f,int Update);
void UpdateTRxFrequencyV3(vector<TRXs> LTrxNTreateds,AFP * afpProblem,TRXs &trx, int f,int Update);
void UpdateAllTRxFrequency(vector <TRXs> &LTrxNTreateds,int  f, int Update);//::c vérifié mise à jour de la fréquence dans tt les trx traités
void UpdateTRxFrequencyEraseAdj(TRXs &trx, int f);//supprimer la fréquence et ses voisin (f+1,f-1) dans la liste des freq Availeble fe trx
//void UpdateTRxFrequency1(TRXs &trx, int f,int Update); //Retirer f de la liste de fréquence valide de trx
int FindTrx(vector <TRXs> LTrxNTreateds, TRXs trx);//::c verifié::
int FindTrxID(vector <TRXs> LTrxNTreateds, int indextrx);//
int FindFrequency(vector<int>* vectFrequency, int f);//c vérifié::
int blockedFrequency(TRXs trx,int f);//::c vérifié::verifier si la fréquence f n'est pac bloquée
//----------------------
//neighborhood=======
int FindTrxFirstNeighbor(AFP * afpProblem,TRXs trx,TRXs trxneighbor);
int FindTrxSecondNeighbor(AFP * afpProblem,int sect,int sectneighbor);
double DistancetowTrxs(AFP * afpProblem,TRXs trxone, TRXs trxtwo);

//====================

bool operator ==( const TRXs &b1, const TRXs &b );
//===============================================
//Afficher résultats
void ShowResult(int ApproachGameEvaluation,string instance,int NumGame,double elapsed_secs,const int  max_gen,const double  epsilon,vector<Individual*> solutionSs,int indexNASHEbest,vector <double> NASHEJ,vector<Individual*> BestsolutionSs, Individual* solution, string path, double HV);
//--------------- ajputé le 28-3-2019
void UpdateTRxFrequencyV32(vector<int> LTrxNTreateds,AFP * afpProblem,TRXs &trx, int f,int Update);
void UpdateLTrxNTreatedsV2(vector <int> &LTrxNTreateds, TRXs trx,int Update);//::c vérifié::
int FindTrxV2(vector <int> LTrxNTreateds, TRXs trx);//::c verifié::
void AddSolTrxFrequencyV2(Individual* &Sol,int trxid ,int f); //Procédure pour affecter f au trx dans la solution
//-----------------------------------------
void Normalize(vector<pair<double,double> > &paircost, pair<double,double> MinT, pair<double,double> MaxT);
double Hypervolume(vector < pair< double, double> > paircost , pair < double,double> R);
//-----------ajouté le 36-4-2019
void NormalizeV2(vector<pair<double,double> > &paircost, pair<double,double> &R);
//----------------------Ajouté le 27-4-2019--------
void vecmaxptr(vector<double>* x, int & indexmax);
//----------fin ajout 27-4-2019 ----------------
//---------------------------   Ajout 03-06-2021 -----------------------------------
void ShowSolution(int StrategyTrxPI,int StrategyTrxPS,Individual* Sol,int ApproachGameEvaluation,string instance,double elapsed_secs,const int  max_gen,const double  epsilon);

//--------------------------- Fin ajout 03-06-2021 -------------------------------
// ------------- ajout 16-6-2021 --------------
int GetSolutionRealSize(Individual* Sol);
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Ajouté le 27-6-2021 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void ShowPlayerInterventionOrder(Individual* Sol,int ApproachGameEvaluation,string instance,double elapsed_secs,const int  max_gen,const double  epsilon, int SizePIInterventionOrder, int SizePSInterventionOrder);
void ShowPlayerTRXOrder(vector <int> *IdTRX,int ApproachGameEvaluation,string instance,double elapsed_secs,const int  max_gen,const double  epsilon);
int GetVectorRealSize(vector <int> * vec);

//============== Ajout le -1-2-2022-----------------------------
void ShowNashvaluersResult(int indexNASHEbest,vector <double> NASHEJ, string path, double HV,vector<Individual*> solutionSs);


//======================================Ajout 16 -3- 2022 ====================================
void ShowResultNorm(int ApproachGameEvaluation,string instance,int NumGame,double elapsed_secs,const int  max_gen,const double epsilon,vector<Individual*> solutionSs,int indexNASHEbest,vector <double> NASHEJ,vector<Individual*> BestsolutionSs, Individual* solution, string path, double HVNorm);
#endif // COMMUN_H_INCLUDED
>>>>>>> 0514ea9fae0f841576757defb02235a9189b0fad
