<<<<<<< HEAD
#ifndef COMMUN_H_INCLUDED
#define COMMUN_H_INCLUDED

#include "../Individual/Individual.h"
#include "../AFP/AFP.h"
//-------------------
//#include "PIPlayer.h"

//---------------------

void InitLTrxNTreateds(vector<TRXs> &LTrxNTreateds, AFP * afpProblem);//::c::v�rifi�::initialiser le vecteur de la liste des trx non trait�
void InitLTrxNTreatedsV2(vector<int> &LTrxNTreateds, AFP * afpProblem);
void AddSolTrxFrequency( AFP * afpProblem,Individual* &Sol,TRXs trx ,int f);
void vecmin(vector<double>* x, int & indexmin);//::c v�rif� ::
void VecMinValue(vector<double> x, int &index);//::c v�rif� ::
void vecmax(vector<double> x, int & indexmax);//retourner la valeur maximale dans un tableau
void vecminInt(vector<int> x, int & indexmin);//retourner l indice de la valeur minimal dans un tableau des entiers
void vecmaxInt(vector<int> x, int & indexmax);//retourner l indice de la valeur maximal dans un tableau des entiers
//mise � jour de la liste des trx non trait�; Update= +1 ajout du trx; Update=-1 : suppression de trx de la liste
void UpdateLTrxNTreateds(vector <TRXs> &LTrxNTreateds, TRXs trx,int Update);//::c v�rifi�::
void UpdateTRxFrequency(TRXs &trx, int f,int Update); //::cv�rif�::Retirer f de la liste de fr�quence valide de trx
void UpdateTRxFrequencyNew(vector<TRXs> LTrxNTreateds,AFP * afpProblem,TRXs &trx, int f,int Update);
void UpdateTRxFrequencyV3(vector<TRXs> LTrxNTreateds,AFP * afpProblem,TRXs &trx, int f,int Update);
void UpdateAllTRxFrequency(vector <TRXs> &LTrxNTreateds,int  f, int Update);//::c v�rifi� mise � jour de la fr�quence dans tt les trx trait�s
void UpdateTRxFrequencyEraseAdj(TRXs &trx, int f);//supprimer la fr�quence et ses voisin (f+1,f-1) dans la liste des freq Availeble fe trx
//void UpdateTRxFrequency1(TRXs &trx, int f,int Update); //Retirer f de la liste de fr�quence valide de trx
int FindTrx(vector <TRXs> LTrxNTreateds, TRXs trx);//::c verifi�::
int FindTrxID(vector <TRXs> LTrxNTreateds, int indextrx);//
int FindFrequency(vector<int>* vectFrequency, int f);//c v�rifi�::
int blockedFrequency(TRXs trx,int f);//::c v�rifi�::verifier si la fr�quence f n'est pac bloqu�e
//----------------------
//neighborhood=======
int FindTrxFirstNeighbor(AFP * afpProblem,TRXs trx,TRXs trxneighbor);
int FindTrxSecondNeighbor(AFP * afpProblem,int sect,int sectneighbor);
double DistancetowTrxs(AFP * afpProblem,TRXs trxone, TRXs trxtwo);

//====================

bool operator ==( const TRXs &b1, const TRXs &b );
//===============================================
//Afficher r�sultats
void ShowResult(int ApproachGameEvaluation,string instance,int NumGame,double elapsed_secs,const int  max_gen,const double  epsilon,vector<Individual*> solutionSs,int indexNASHEbest,vector <double> NASHEJ,vector<Individual*> BestsolutionSs, Individual* solution, string path, double HV);
//--------------- ajput� le 28-3-2019
void UpdateTRxFrequencyV32(vector<int> LTrxNTreateds,AFP * afpProblem,TRXs &trx, int f,int Update);
void UpdateLTrxNTreatedsV2(vector <int> &LTrxNTreateds, TRXs trx,int Update);//::c v�rifi�::
int FindTrxV2(vector <int> LTrxNTreateds, TRXs trx);//::c verifi�::
void AddSolTrxFrequencyV2(Individual* &Sol,int trxid ,int f); //Proc�dure pour affecter f au trx dans la solution
//-----------------------------------------
void Normalize(vector<pair<double,double> > &paircost, pair<double,double> MinT, pair<double,double> MaxT);
double Hypervolume(vector < pair< double, double> > paircost , pair < double,double> R);
//-----------ajout� le 36-4-2019
void NormalizeV2(vector<pair<double,double> > &paircost, pair<double,double> &R);
//----------------------Ajout� le 27-4-2019--------
void vecmaxptr(vector<double>* x, int & indexmax);
//----------fin ajout 27-4-2019 ----------------
//---------------------------   Ajout 03-06-2021 -----------------------------------
void ShowSolution(int StrategyTrxPI,int StrategyTrxPS,Individual* Sol,int ApproachGameEvaluation,string instance,double elapsed_secs,const int  max_gen,const double  epsilon);

//--------------------------- Fin ajout 03-06-2021 -------------------------------
// ------------- ajout 16-6-2021 --------------
int GetSolutionRealSize(Individual* Sol);
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Ajout� le 27-6-2021 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
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

void InitLTrxNTreateds(vector<TRXs> &LTrxNTreateds, AFP * afpProblem);//::c::v�rifi�::initialiser le vecteur de la liste des trx non trait�
void InitLTrxNTreatedsV2(vector<int> &LTrxNTreateds, AFP * afpProblem);
void AddSolTrxFrequency( AFP * afpProblem,Individual* &Sol,TRXs trx ,int f);
void vecmin(vector<double>* x, int & indexmin);//::c v�rif� ::
void VecMinValue(vector<double> x, int &index);//::c v�rif� ::
void vecmax(vector<double> x, int & indexmax);//retourner la valeur maximale dans un tableau
void vecminInt(vector<int> x, int & indexmin);//retourner l indice de la valeur minimal dans un tableau des entiers
void vecmaxInt(vector<int> x, int & indexmax);//retourner l indice de la valeur maximal dans un tableau des entiers
//mise � jour de la liste des trx non trait�; Update= +1 ajout du trx; Update=-1 : suppression de trx de la liste
void UpdateLTrxNTreateds(vector <TRXs> &LTrxNTreateds, TRXs trx,int Update);//::c v�rifi�::
void UpdateTRxFrequency(TRXs &trx, int f,int Update); //::cv�rif�::Retirer f de la liste de fr�quence valide de trx
void UpdateTRxFrequencyNew(vector<TRXs> LTrxNTreateds,AFP * afpProblem,TRXs &trx, int f,int Update);
void UpdateTRxFrequencyV3(vector<TRXs> LTrxNTreateds,AFP * afpProblem,TRXs &trx, int f,int Update);
void UpdateAllTRxFrequency(vector <TRXs> &LTrxNTreateds,int  f, int Update);//::c v�rifi� mise � jour de la fr�quence dans tt les trx trait�s
void UpdateTRxFrequencyEraseAdj(TRXs &trx, int f);//supprimer la fr�quence et ses voisin (f+1,f-1) dans la liste des freq Availeble fe trx
//void UpdateTRxFrequency1(TRXs &trx, int f,int Update); //Retirer f de la liste de fr�quence valide de trx
int FindTrx(vector <TRXs> LTrxNTreateds, TRXs trx);//::c verifi�::
int FindTrxID(vector <TRXs> LTrxNTreateds, int indextrx);//
int FindFrequency(vector<int>* vectFrequency, int f);//c v�rifi�::
int blockedFrequency(TRXs trx,int f);//::c v�rifi�::verifier si la fr�quence f n'est pac bloqu�e
//----------------------
//neighborhood=======
int FindTrxFirstNeighbor(AFP * afpProblem,TRXs trx,TRXs trxneighbor);
int FindTrxSecondNeighbor(AFP * afpProblem,int sect,int sectneighbor);
double DistancetowTrxs(AFP * afpProblem,TRXs trxone, TRXs trxtwo);

//====================

bool operator ==( const TRXs &b1, const TRXs &b );
//===============================================
//Afficher r�sultats
void ShowResult(int ApproachGameEvaluation,string instance,int NumGame,double elapsed_secs,const int  max_gen,const double  epsilon,vector<Individual*> solutionSs,int indexNASHEbest,vector <double> NASHEJ,vector<Individual*> BestsolutionSs, Individual* solution, string path, double HV);
//--------------- ajput� le 28-3-2019
void UpdateTRxFrequencyV32(vector<int> LTrxNTreateds,AFP * afpProblem,TRXs &trx, int f,int Update);
void UpdateLTrxNTreatedsV2(vector <int> &LTrxNTreateds, TRXs trx,int Update);//::c v�rifi�::
int FindTrxV2(vector <int> LTrxNTreateds, TRXs trx);//::c verifi�::
void AddSolTrxFrequencyV2(Individual* &Sol,int trxid ,int f); //Proc�dure pour affecter f au trx dans la solution
//-----------------------------------------
void Normalize(vector<pair<double,double> > &paircost, pair<double,double> MinT, pair<double,double> MaxT);
double Hypervolume(vector < pair< double, double> > paircost , pair < double,double> R);
//-----------ajout� le 36-4-2019
void NormalizeV2(vector<pair<double,double> > &paircost, pair<double,double> &R);
//----------------------Ajout� le 27-4-2019--------
void vecmaxptr(vector<double>* x, int & indexmax);
//----------fin ajout 27-4-2019 ----------------
//---------------------------   Ajout 03-06-2021 -----------------------------------
void ShowSolution(int StrategyTrxPI,int StrategyTrxPS,Individual* Sol,int ApproachGameEvaluation,string instance,double elapsed_secs,const int  max_gen,const double  epsilon);

//--------------------------- Fin ajout 03-06-2021 -------------------------------
// ------------- ajout 16-6-2021 --------------
int GetSolutionRealSize(Individual* Sol);
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Ajout� le 27-6-2021 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void ShowPlayerInterventionOrder(Individual* Sol,int ApproachGameEvaluation,string instance,double elapsed_secs,const int  max_gen,const double  epsilon, int SizePIInterventionOrder, int SizePSInterventionOrder);
void ShowPlayerTRXOrder(vector <int> *IdTRX,int ApproachGameEvaluation,string instance,double elapsed_secs,const int  max_gen,const double  epsilon);
int GetVectorRealSize(vector <int> * vec);

//============== Ajout le -1-2-2022-----------------------------
void ShowNashvaluersResult(int indexNASHEbest,vector <double> NASHEJ, string path, double HV,vector<Individual*> solutionSs);


//======================================Ajout 16 -3- 2022 ====================================
void ShowResultNorm(int ApproachGameEvaluation,string instance,int NumGame,double elapsed_secs,const int  max_gen,const double epsilon,vector<Individual*> solutionSs,int indexNASHEbest,vector <double> NASHEJ,vector<Individual*> BestsolutionSs, Individual* solution, string path, double HVNorm);
#endif // COMMUN_H_INCLUDED
>>>>>>> 0514ea9fae0f841576757defb02235a9189b0fad
