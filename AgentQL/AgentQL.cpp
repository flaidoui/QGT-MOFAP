#include <iostream>
#include <cstdlib>      // std::rand, std::srand
#include <algorithm>    // std::find
#include <sstream>//LF:convert string
#include <ctime>        // std::time
#include <sstream>//LF:convert string
#include <fstream>
//#include <random>
//--------------------------rand répété
#include <cmath>
//---------------------======================
#include "AgentQL.h"

//---------------------------------------
#include "../Individual/Individual.h"
#include "../AFP/AFP.h"
<<<<<<< HEAD
#include "../Commun/Commun.h"

//===================================
bool my_cmpDoubleDoublePairActionCostHighFirst(const pair <Action,double>   &a, const pair <Action,double>   &b)
{
    // smallest comes first
    return a.second > b.second;
}
=======
#include "../Commun/Commun.h"

//===================================
bool my_cmpDoubleDoublePairActionCostHighFirst(const pair <Action,double>   &a, const pair <Action,double>   &b)
{
    // smallest comes first
    return a.second > b.second;
}
>>>>>>> 0514ea9fae0f841576757defb02235a9189b0fad
//========================================


extern bool my_cmpSupDoublePair(const pair <double,double>   &a, const pair <double,double>   &b);
//---------------------------------
 AGENTQL:: AGENTQL(AFP * afpProblem, const int max_gen)//()
<<<<<<< HEAD
   {            int SizeActions = 4;//5;
=======
   {            int SizeActions = 4;//5;
>>>>>>> 0514ea9fae0f841576757defb02235a9189b0fad
                Action A;


            //On définit les paramètres (coeffeicients) d apprentissage
            QGAMMA = 0.9;
            QALPHA = 0.2;

            //###################################################
            //# initialiser l'ensembles des actions (strategy trx, strategie fréquences
                      //lest strategies de fréquences du joueur PI
<<<<<<< HEAD
            ActionsSet.reserve(SizeActions);
            //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
           /* A.ActTRX = 1;                           // Q(0)
            A.ActFreq = 1;
            ActionsSet.push_back(A);*/
            //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            //ActionsSet.at(1).ActFreq = {2};// choix de la frééquence avec minimum cout
          /*  A.ActTRX = 1;                           // Q(1)
            A.ActFreq = 2;
            ActionsSet.push_back(A);*/
            //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
          //  ActionsSet.at(2).ActFreq  = {550};       // Q(2)
          /*  A.ActTRX = 1;
            A.ActFreq = 550;
            ActionsSet.push_back(A);*/
             //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            // ActionsSet.at(3).ActFreq  = {4};//stratégie de choix de fréquence en mode Nash
           /* A.ActTRX = 1;                               // Q(3)
            A.ActFreq = 4;
            ActionsSet.push_back(A);*/
            //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
             //  ActionsSet.at(4).ActFreq = {6};//stratégie de choix de fréquence en mode Nash
           /* A.ActTRX = 1;                                // Q(4)
            A.ActFreq = 6;
            ActionsSet.push_back(A);*/
               //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
           // A.ActTRX = 8;                               // Q(5)
           /* A.ActFreq = 1;
            ActionsSet.push_back(A);*/
            //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            //ActionsSet.at(1).ActFreq = {2};// choix de la frééquence avec minimum cout
         //   A.ActTRX = 8;                           //// Q(6)
            A.ActFreq = 2;
            ActionsSet.push_back(A);
            //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
          //  ActionsSet.at(2).ActFreq  = {550};            // Q(7)
           // A.ActTRX = 8;
            A.ActFreq = 550;
            ActionsSet.push_back(A);
             //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            // ActionsSet.at(3).ActFreq  = {4};//stratégie de choix de fréquence en mode Nash
           // A.ActTRX = 8;           // Q(8)
            A.ActFreq = 4;
            ActionsSet.push_back(A);
            //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
             //  ActionsSet.at(4).ActFreq = {6};//stratégie de choix de fréquence en mode Nash
           // A.ActTRX = 8;           // Q(9)
            A.ActFreq = 6;
=======
            ActionsSet.reserve(SizeActions);
            //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
           /* A.ActTRX = 1;                           // Q(0)
            A.ActFreq = 1;
            ActionsSet.push_back(A);*/
            //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            //ActionsSet.at(1).ActFreq = {2};// choix de la frééquence avec minimum cout
          /*  A.ActTRX = 1;                           // Q(1)
            A.ActFreq = 2;
            ActionsSet.push_back(A);*/
            //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
          //  ActionsSet.at(2).ActFreq  = {550};       // Q(2)
          /*  A.ActTRX = 1;
            A.ActFreq = 550;
            ActionsSet.push_back(A);*/
             //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            // ActionsSet.at(3).ActFreq  = {4};//stratégie de choix de fréquence en mode Nash
           /* A.ActTRX = 1;                               // Q(3)
            A.ActFreq = 4;
            ActionsSet.push_back(A);*/
            //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
             //  ActionsSet.at(4).ActFreq = {6};//stratégie de choix de fréquence en mode Nash
           /* A.ActTRX = 1;                                // Q(4)
            A.ActFreq = 6;
            ActionsSet.push_back(A);*/
               //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
           // A.ActTRX = 8;                               // Q(5)
           /* A.ActFreq = 1;
            ActionsSet.push_back(A);*/
            //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            //ActionsSet.at(1).ActFreq = {2};// choix de la frééquence avec minimum cout
         //   A.ActTRX = 8;                           //// Q(6)
            A.ActFreq = 2;
            ActionsSet.push_back(A);
            //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
          //  ActionsSet.at(2).ActFreq  = {550};            // Q(7)
           // A.ActTRX = 8;
            A.ActFreq = 550;
            ActionsSet.push_back(A);
             //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            // ActionsSet.at(3).ActFreq  = {4};//stratégie de choix de fréquence en mode Nash
           // A.ActTRX = 8;           // Q(8)
            A.ActFreq = 4;
            ActionsSet.push_back(A);
            //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
             //  ActionsSet.at(4).ActFreq = {6};//stratégie de choix de fréquence en mode Nash
           // A.ActTRX = 8;           // Q(9)
            A.ActFreq = 6;
>>>>>>> 0514ea9fae0f841576757defb02235a9189b0fad
            ActionsSet.push_back(A);

        InitQtable(afpProblem, max_gen);

    }


   //---------------------------------------------------
 AGENTQL::~AGENTQL()
  {
   QGAMMA = 0;
  // ActionsSet = NULL;
   //delete ActionsSet;
   //Qtable = NULL;
<<<<<<< HEAD
   //delete
   vector < Action >().swap(ActionsSet);
=======
   //delete
   vector < Action >().swap(ActionsSet);
>>>>>>> 0514ea9fae0f841576757defb02235a9189b0fad
    vector < pair < pair < State, Action> , double > >().swap(Qtable);

  }
	//-------------------------------------------
    //------------------------------------------------
//Procéédure pour iniyialiser Qtable
void  AGENTQL::InitQtable(AFP * afpProblem, const int max_gen)
{
<<<<<<< HEAD
    Action a; State s; pair <State, Action> p;
     pair < pair < State, Action> , double > pdash;
    int PbSize = afpProblem->trxs.size();
    int ActionsSetSize = ActionsSet.size();
    int taille = PbSize * ActionsSetSize;
     cout << "taille Qtable " << taille << endl;
=======
    Action a; State s; pair <State, Action> p;
     pair < pair < State, Action> , double > pdash;
    int PbSize = afpProblem->trxs.size();
    int ActionsSetSize = ActionsSet.size();
    int taille = PbSize * ActionsSetSize;
     cout << "taille Qtable " << taille << endl;
>>>>>>> 0514ea9fae0f841576757defb02235a9189b0fad
         //Qtable = vector < pair < pair < State, Action> , double > > (taille) ;
    Qtable.reserve(taille);

   int k = 0;
    for(int i = 0; i < afpProblem->trxs.size(); i++)// taille des étates
    {
<<<<<<< HEAD
        s.UnTreatedTRXNumb = i;
        p.first = s;
        for(int j = 0 ; j < ActionsSet.size(); j++)
        {
            a.ActFreq = ActionsSet[j].ActFreq;
=======
        s.UnTreatedTRXNumb = i;
        p.first = s;
        for(int j = 0 ; j < ActionsSet.size(); j++)
        {
            a.ActFreq = ActionsSet[j].ActFreq;
>>>>>>> 0514ea9fae0f841576757defb02235a9189b0fad
          //  a.ActTRX =  ActionsSet[j].ActTRX;
            p.second = a;
            pdash.first = p ;
            pdash.second = 0.0 ;
            //--------------------- pour tester le fctionnementt de cette procedure
           /* if( (i== 1) && (j ==2) )
            {
                 pdash.second = 5.0;
                 cout << " hiii!!!!!!!!!!!!!!!" <<endl;

            }*/
            //===================================================
             Qtable.push_back({pdash});
            // Qtable[k] = pdash;
             k = k+1;
            }
        }
   cout << "Qtable->size()" << Qtable.size() << endl;
}
//-----------------------------------------------------------------
//------------------------------------------------
// recupérer l'action;
// il faut choisir une politique pour selectionner la bonne action
// On commence par choisir une action aléatoirement
 Action AGENTQL::GetPossibleAction ()
 {
//TRXs trx;
//on remplie les partie non copié donc si l = solution->plan->size(), cela veut dire on a trouvé une solution complète toute
  // Au début choisir alétoirement un trx
    srand ( unsigned ( time(0) ) );
    int choice;
    //random_device rd;
    //generate secret number between 1 and 2:
    choice = rand() % ActionsSet.size();

    // cout << " L'ordre de l'action choisi est : " << choice << endl;

    return ActionsSet[choice];
 }
//---------------------------------------------
void AGENTQL::ShowQtable(int ApproachGameEvaluation,string instance,double elapsed_secs,const int  max_gen,const double  epsilon)
{
    ofstream ResultFile; string path;

    path="Resultats/Qtable_";

    string dateTime;
    time_t rawtime;
    struct tm * timeinfo;
    char buffer [80];
    time ( &rawtime );
    timeinfo = localtime ( &rawtime );
    ostringstream temp;  //temp as in temporary
<<<<<<< HEAD
     stringstream ss;
=======
     stringstream ss;
>>>>>>> 0514ea9fae0f841576757defb02235a9189b0fad

     int d = timeinfo->tm_mday;
    temp<<"_";
    temp<<d;

    int m = timeinfo->tm_mon;
    m=m+1;
    temp<<"_";
    temp<<m;


    int h = timeinfo->tm_hour;
    temp<<"_";
    temp<<h;
    temp<<"h";

    int mi= timeinfo->tm_min;
    temp<<"_";
    temp<<mi;
    temp<<"min";

    stringstream sss;
    stringstream ssss;
<<<<<<< HEAD
    stringstream sssss;
    stringstream sinstance;
    sss << max_gen;
    ssss << epsilon;
    sinstance << instance;
     sssss << ApproachGameEvaluation;
=======
    stringstream sssss;
    stringstream sinstance;
    sss << max_gen;
    ssss << epsilon;
    sinstance << instance;
     sssss << ApproachGameEvaluation;
>>>>>>> 0514ea9fae0f841576757defb02235a9189b0fad

    path = path+ sinstance.str()+"_Evaluation_"+sssss.str()+"_epsilon"+ssss.str()+  +"_gen_" + sss.str()+temp.str()+".txt";      //str is temp as string

    ResultFile.open(path.c_str(),std::ios::app);

    if (!ResultFile) {
        cerr << "Unable to open file!!";
        exit(1);   // call system to stop
    }
   ResultFile << " ~~~~~~~~ Qtable is ~~~~~~~~~~~~"   << endl ;
     ResultFile << "size of q table is " << Qtable.size() << endl;
    ResultFile << "size of Actions ****" << ActionsSet.size() << endl;
      ResultFile << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    int i,j;  pair <State, Action> MyPair;
    State s; Action A; double Qvalue; int taille;
     Individual * solutionTemp;
        //à chaque génération, on initialise  la solution(individual)
        solutionTemp = new Individual();
    if(Qtable.empty() == false)
    {

        for (int i = 0; i < Qtable.size(); i++)//LF comment:initiallement le cout est 0
        {
            MyPair = Qtable[i].first;
            s = MyPair.first;
            A = MyPair.second;
            //solutionTemp = s.CurrentSol;
            taille = GetSolutionRealSize(solutionTemp);
            Qvalue = Qtable[i].second;
            ResultFile << "Qtable[" << i << "] ; "  <<" Etat : " ;
            ResultFile<< "state  "<< s.UnTreatedTRXNumb << " with Action (FreqStrat) is (" <<A.ActFreq << ")" << endl << endl ;
            ResultFile<< " Qvalue is " << Qvalue << endl << endl ;
            ResultFile << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            ResultFile << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        }
    }
    else
    {
        ResultFile<<" The table is empty HONEY !!" <<endl;
    }


    ResultFile.close();


}
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
/*void AGENTQL::ShowQDashtable()
{
    ofstream ResultFile;
    string path = "Resultats/QDashtable";
    string dateTime;
    time_t rawtime;
    struct tm * timeinfo;
    char buffer [80];
    time ( &rawtime );
    timeinfo = localtime ( &rawtime );
    ostringstream temp;  //temp as in temporary
     stringstream ss;
     int d = timeinfo->tm_mday;
    temp<<"_";
    temp<<d;

    int m = timeinfo->tm_mon;
    m=m+1;
    temp<<"_";
    temp<<m;


    int h = timeinfo->tm_hour;
    temp<<"_";
    temp<<h;
    temp<<"h";

    int mi= timeinfo->tm_min;
    temp<<"_";
    temp<<mi;
    temp<<"min";

    path = path+temp.str()+".txt";      //str is temp as string
    ResultFile.open(path.c_str(),std::ios::app);

    if (!ResultFile) {
        cerr << "Unable to open file!!";
        exit(1);   // call system to stop
    }
   ResultFile << " ~~~~~~~~ Qtable is ~~~~~~~~~~~~"   << endl ;
     ResultFile << "size of q table is " << Qtable->size() << endl;
      ResultFile << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    int i,j;  pair <State, Action> MyPair;
    State s; Action A; double Qvalue;
    for (int i = 0; i < QDashtable->size(); i++)//LF comment:initiallement le cout est 0
    {
        MyPair = Qtable->at(i).first;
        s = MyPair.first;
        A = MyPair.second;
        Qvalue = Qtable->at(i).second;
        ResultFile << "Etat : " ;

        ResultFile<< " Action (TRXStrategy; FreqStrategy) is (" << A.ActTRX << ";" << A.ActFreq << ")" << endl << endl ;
        ResultFile<< " Qvalue is " << Qvalue << endl << endl ;
        ResultFile << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        ResultFile << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    }


    ResultFile.close();


}*/
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
/*bool AGENTQL::CheckAction(Action A)
{
    int i;
    for (i=0; i < ActionsSet->size(); i++)
    {
        if ((ActionsSet->at(i).ActTRX == A.ActTRX) &&  ( ActionsSet->at(i).ActFreq == A.ActFreq))
            return true;
    }
    return false; //if ( i == ActionsSet->size()) return false;
}*/
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
/*bool AGENTQL::CheckElementQtable( pair < State, Action> Mypair, int & IndexElement)
{
    //vector < pair < pair < State, Action> , double > >  Qtable;
    int i;
    pair < pair < State, Action> , double > p;
    pair < State, Action> secondp;
    State MypairState, secondpState;
    Action MypairAct, secondpAct;
    MypairState =  Mypair.first;
    MypairAct = Mypair.second;
    bool test = false;
    IndexElement = -1;
    for (i=0; i < Qtable->size(); i++)
    {
        //on récupère un élément de la table
        p = Qtable->at(i);
        secondp = p.first;
         secondpState = secondp.first;
         secondpAct= secondp.second;
        if (MypairState.UnTreatedTRXNumb == secondpState.UnTreatedTRXNumb)
        {
            if ((MypairAct.ActTRX == secondpAct.ActTRX) and (MypairAct.ActFreq == secondpAct.ActFreq))
            {
                IndexElement = i;
                test = true;
            }
        }


    }

    return test;
}*/
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
//on est dans s (etat après utilisation de l'action a, on calcule la récompense immédiate après l'utilisation de l'action a
void AGENTQL::ObserveReward (int indexplayer,Individual* solref, Individual* sol, double &Reward, string instance)
{
<<<<<<< HEAD
   if ((solref->PIObj >= sol->PIObj) and  (solref->PSObj >=  sol->PSObj) )
   {
       Reward = + 1;
   }
   else
   {
       Reward = - 1;
   }
=======
   if ((solref->PIObj >= sol->PIObj) and  (solref->PSObj >=  sol->PSObj) )
   {
       Reward = + 1;
   }
   else
   {
       Reward = - 1;
   }
>>>>>>> 0514ea9fae0f841576757defb02235a9189b0fad
    //on evalue si la contrainte n'est pas violé donc +1 ; sionn si la contrainte est viloé donc +1
    /*if (indexplayer == 1) // le joueur PI qui est entrin de joueur donc on vérifie si la contrinte de conférence
    {
        if (solref->PIObj < sol->PIObj)//cela veut dire le choix de la fréquence n'a pas affecté sur le cout d'interference
         //recompense +1
         {
             Reward = -1;
         }
         else // le choix de la fréquence est mauvais
         {
             Reward = +1;
         }

    }
     else if (indexplayer == 2) // le joueur PS qui est entrin de joueur donc on vérifie si la contrinte de separation
    {
        if (solref->PSObj < sol->PSObj)//cela veut dire le choix de la fréquence n'a pas affecté sur le cout de separation
         //recompense +1
         {
             Reward = -1;
         }
         else // le choix de la fréquence est mauvais
         {
             Reward = + 1;
         }

    }
    else
<<<<<<< HEAD
        cout << " Erreur de choix du joueur dans la phase d'apprentissage!!"<<endl;
=======
        cout << " Erreur de choix du joueur dans la phase d'apprentissage!!"<<endl;
>>>>>>> 0514ea9fae0f841576757defb02235a9189b0fad
        */

  /*
   pair<double,double> Min;
     pair<double,double> Max;
     pair < double, double > R;// est le point de référence ; la valeur max (normalisé)
     if (instance == "Seattle")
    //const pair<double,double> MinSeattle = (4000,15) ;
   {
        Min.first = 4000.0;
        Min.second = 15.0 ;
        Max.first = 70000.0;
        Max.second = 200.0;
        R = Max;
   }
   else
   {
       if (instance == "Denver")
       {
            Min.first = 130000.0;
            Min.second = 1200.0 ;
            Max.first = 300000.0;
            Max.second = 2500.0 ;
            R = Max;
       }
   }
//********************************************************
          // Normaliser les valeurs
    R.first = (R.first - Min.first)/(Max.first-Min.first);
    R.second = (R.second - Min.second)/(Max.second-Min.second);
      vector < pair < double, double > > paircost;
    paircost.reserve(1);
    //Remplir le vecteur par la solution actuelle
    paircost.push_back({sol->PIObj,sol->PSObj});
    Normalize(paircost,Min,Max);
    sort(paircost.begin(),paircost.end(),my_cmpSupDoublePair);
    //on évalue la récompense actuelle qui est l'hypervolume
   // Reward = Hypervolume(paircost,R) ;
   // cout << "&&&&&&&&&&&&&&&&&&&&&&&&reward is&&&&&&&&&&&&&&&& " << Reward << endl;

   if (indexplayer == 1)
   {

       Reward = solref->planCC->at(IndexTRX).first - sol->planCC->at(IndexTRX).first   ;}
   else
   {
       if(indexplayer == 2 )
        {Reward = solref->planCC->at(IndexTRX).second - sol->planCC->at(IndexTRX).second ;}
       else
        cout << " Eroor may be a Virus !!" << endl;
   }
   //on penalise si on  a un cout trop elever

*/
}
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
double AGENTQL::GetMaxQValue(State s, Action & CorrespondingAction)
{//Récupérer la valeur  de Qvalue max et son action

<<<<<<< HEAD
    //vector < pair < pair < State, Action> , double > >  Qtable;
=======
    //vector < pair < pair < State, Action> , double > >  Qtable;
>>>>>>> 0514ea9fae0f841576757defb02235a9189b0fad
    // cout << endl<<"==============debut de GetMaxQValue(===================" <<endl<<endl;
    int i; pair < pair < State, Action> , double > p;
    vector < pair < Action,double > > QValueStateVector;
    pair < State, Action> MyPair; double QValueMax;
   pair < State, Action> MypairMax;
    State MypairStateMax, MyPairState; Action MypairActMax, MyPairAct;
<<<<<<< HEAD
    /*p = Qtable[0];
=======
    /*p = Qtable[0];
>>>>>>> 0514ea9fae0f841576757defb02235a9189b0fad

   MypairMax = p.first;
    MypairStateMax =  MypairMax.first;
    MypairActMax = MypairMax.second;
    QValueMax = p.second;*/
<<<<<<< HEAD
    vector < pair < Action,double > > QValueActionVector,QEqualValueActionVector;
    QValueActionVector.reserve(ActionsSet.size());
=======
    vector < pair < Action,double > > QValueActionVector,QEqualValueActionVector;
    QValueActionVector.reserve(ActionsSet.size());
>>>>>>> 0514ea9fae0f841576757defb02235a9189b0fad
    QEqualValueActionVector.reserve(ActionsSet.size());
    int k = 0;
    for (i=1; i < Qtable.size(); i++)
    {
        p = Qtable[i];
         MyPair = p.first;
         MyPairState = MyPair.first;
         MyPairAct = MyPair.second;

        //verifier si l'etat actuelle est l'etat recherchéé
        if (MyPairState.UnTreatedTRXNumb == s.UnTreatedTRXNumb)
        {


        //on sauvegarde toutes les valeur d' actions possible
            //QValueStateVector.push_back({MyPairAct, p.second});
          //  QValueActionVector[k].first = MyPairAct;
<<<<<<< HEAD
           // QValueActionVector[k].second = p.second;
=======
           // QValueActionVector[k].second = p.second;
>>>>>>> 0514ea9fae0f841576757defb02235a9189b0fad
           QValueActionVector.push_back({MyPairAct,p.second});
            k++;

        }
        }// fin for

<<<<<<< HEAD
        // on récupère la plus grande valeur

            if  (QValueActionVector.size()!= 0)
            {

            sort(QValueActionVector.begin(),QValueActionVector.end(),my_cmpDoubleDoublePairActionCostHighFirst);
            bool test =false;
            int indiceEqual = 0;

            QValueMax = QValueActionVector[0].second;
            CorrespondingAction.ActFreq = QValueActionVector[0].first.ActFreq;
          //  CorrespondingAction.ActTRX = QValueActionVector[0].first.ActTRX;
           // CorrespondingAction.ActTRX = QValueStateVector[0].first.ActTRX;
           //on remplit les valeurs égale de cooresponding action pour choisir aléatoirement une action ayant la meme valeur Q

           //==================================================================================
           for(int j=0;j < QValueActionVector.size();j++)
           {
               if(QValueMax == QValueActionVector[j].second)
               {
                   QEqualValueActionVector.push_back( QValueActionVector[j]);
                   indiceEqual = indiceEqual+1;
               }
           }
           //on choisit aléatoirement une de ces valeurs égales
              int choice = rand() % (indiceEqual);
              CorrespondingAction.ActFreq = QValueActionVector[choice].first.ActFreq;
              //CorrespondingAction.ActTRX  = QValueActionVector[choice].first.ActTRX;
              QValueMax = QValueActionVector[choice].second;
            }
            else
            {
              cout << " ERROR: in searching MaxQvalue, vector of actions is empty !!" << endl;
             }
        //}
       //  cout << endl<<"==============FINNNNNNNN GetMaxQValue(===================" <<endl<<endl;
    vector < pair < Action,double > > () . swap(QValueStateVector);
     vector < pair < Action,double > > () . swap(QValueActionVector);
     vector < pair < Action,double > > () . swap(QEqualValueActionVector);
    return(QValueMax);
=======
        // on récupère la plus grande valeur

            if  (QValueActionVector.size()!= 0)
            {

            sort(QValueActionVector.begin(),QValueActionVector.end(),my_cmpDoubleDoublePairActionCostHighFirst);
            bool test =false;
            int indiceEqual = 0;

            QValueMax = QValueActionVector[0].second;
            CorrespondingAction.ActFreq = QValueActionVector[0].first.ActFreq;
          //  CorrespondingAction.ActTRX = QValueActionVector[0].first.ActTRX;
           // CorrespondingAction.ActTRX = QValueStateVector[0].first.ActTRX;
           //on remplit les valeurs égale de cooresponding action pour choisir aléatoirement une action ayant la meme valeur Q

           //==================================================================================
           for(int j=0;j < QValueActionVector.size();j++)
           {
               if(QValueMax == QValueActionVector[j].second)
               {
                   QEqualValueActionVector.push_back( QValueActionVector[j]);
                   indiceEqual = indiceEqual+1;
               }
           }
           //on choisit aléatoirement une de ces valeurs égales
              int choice = rand() % (indiceEqual);
              CorrespondingAction.ActFreq = QValueActionVector[choice].first.ActFreq;
              //CorrespondingAction.ActTRX  = QValueActionVector[choice].first.ActTRX;
              QValueMax = QValueActionVector[choice].second;
            }
            else
            {
              cout << " ERROR: in searching MaxQvalue, vector of actions is empty !!" << endl;
             }
        //}
       //  cout << endl<<"==============FINNNNNNNN GetMaxQValue(===================" <<endl<<endl;
    vector < pair < Action,double > > () . swap(QValueStateVector);
     vector < pair < Action,double > > () . swap(QValueActionVector);
     vector < pair < Action,double > > () . swap(QEqualValueActionVector);
    return(QValueMax);
>>>>>>> 0514ea9fae0f841576757defb02235a9189b0fad
   // return 0.5;
}

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
double AGENTQL::GetQtarget(State sdash , Action & CorrespondingMaxAction)
{
<<<<<<< HEAD
 //int indiceState = GetIndexState(sdash);
=======
 //int indiceState = GetIndexState(sdash);
>>>>>>> 0514ea9fae0f841576757defb02235a9189b0fad
 //cout << endl<<"==============je rentre dans la procedure Qtarget ===================" <<endl<<endl;
 double Qtarget = GetMaxQValue(sdash, CorrespondingMaxAction);
 return Qtarget;
}
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
/*int AGENTQL::GetIndexState(State s)
{
    int i;
    pair < pair < State, Action> , double > p;
    pair < State, Action> MyPair;
    State MyPairState;

    //------------------------------------------
    for(i=0;i<Qtable->size(); i++)
    {
        p = Qtable->at(i);
        MyPair = p.first;
        MyPairState = MyPair.first;
        if (MyPairState.UnTreatedTRXNumb == s.UnTreatedTRXNumb)
            return i;

    }
}*/




//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
void AGENTQL::UpdateQtable(double Reward, pair < State ,Action > PairStateAction,double Qtarget)
{
    /*double QvaleMax;
    int IndexElement;
    bool check = CheckElementQtable(PairStateAction,IndexElement);
    if (check == true)
        Qtable->at(IndexElement).second =  Qtable->at(IndexElement).second + QALPHA*(Reward + QGAMMA * Qtarget);
    else
<<<<<<< HEAD
        cout << "Element not found in Qtable!!" << endl;*/
        int index = GetIndexPairStateAction(PairStateAction);
        cout << " index in qtable is " << index << endl;
        cout << " BFORe Qtable is " << Qtable[index].second << endl;
        cout << "Reward "<< Reward <<endl;
        cout << "Qtarget "<< Qtarget << endl;
        Qtable[index].second =  ( 1- QALPHA )* Qtable[index].second + QALPHA*( Reward + QGAMMA * Qtarget);
=======
        cout << "Element not found in Qtable!!" << endl;*/
        int index = GetIndexPairStateAction(PairStateAction);
        cout << " index in qtable is " << index << endl;
        cout << " BFORe Qtable is " << Qtable[index].second << endl;
        cout << "Reward "<< Reward <<endl;
        cout << "Qtarget "<< Qtarget << endl;
        Qtable[index].second =  ( 1- QALPHA )* Qtable[index].second + QALPHA*( Reward + QGAMMA * Qtarget);
>>>>>>> 0514ea9fae0f841576757defb02235a9189b0fad
       // Qtable[index].second + QALPHA*(Reward + QGAMMA * Qtarget - Qtable[index].second);
        cout << " AFTER  Qtable is " << Qtable[index].second << endl;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/*int AGENTQL::GetIndexAction(Action Act)
{

    int i;
    int indice = -1;
    for(i=0;i<ActionsSet->size(); i++)
    {
        if(ActionsSet->at(i).ActFreq == Act.ActFreq)
        {
            indice = i ;
            i = ActionsSet->size();
        }
    }
    return indice;

   // return 0;

<<<<<<< HEAD
}*/
//========================================================================

int AGENTQL::GetIndexPairStateAction(pair < State ,Action > PairStateAction)
{
  int i, IndexPairStateAction; pair < pair < State, Action> , double > p;
   pair < State, Action> MyPair;
   State MyState;
   Action MyAct;
   IndexPairStateAction = -1;
=======
}*/
//========================================================================

int AGENTQL::GetIndexPairStateAction(pair < State ,Action > PairStateAction)
{
  int i, IndexPairStateAction; pair < pair < State, Action> , double > p;
   pair < State, Action> MyPair;
   State MyState;
   Action MyAct;
   IndexPairStateAction = -1;
>>>>>>> 0514ea9fae0f841576757defb02235a9189b0fad

  for (i=0; i < Qtable.size(); i++)
  {
         p = Qtable[i];//c'est le (couple state, action); Qvaleur
         MyPair  = p.first;////(couple state, action)
         MyState = MyPair.first;
<<<<<<< HEAD
         MyAct   = MyPair.second;
         if((PairStateAction.first.UnTreatedTRXNumb == MyState.UnTreatedTRXNumb ) and (PairStateAction.second.ActFreq == MyAct.ActFreq) )
         {IndexPairStateAction = i;}
=======
         MyAct   = MyPair.second;
         if((PairStateAction.first.UnTreatedTRXNumb == MyState.UnTreatedTRXNumb ) and (PairStateAction.second.ActFreq == MyAct.ActFreq) )
         {IndexPairStateAction = i;}
>>>>>>> 0514ea9fae0f841576757defb02235a9189b0fad
  }

return IndexPairStateAction;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~éé
/*void AGENTQL::PenalyzeActions( vector <pair <State,Action> > * vect, Individual* solutionRef, int IndexPlayer)
{
    int i,IndexElement; bool test;
    pair < pair < State, Action> , double > p;
    pair < State, Action> P;
    for (i=0; i < vect->size(); i++)
    {
        P = vect->at(i);

        test = CheckElementQtable(P,IndexElement);
        if (test == true)
        {
            //on test si le joeur PI est en train de jouer
            if(IndexPlayer == 1)
            {
                 Qtable->at(IndexElement).second =  Qtable->at(IndexElement).second -solutionRef->planCC->at(i).first;
            }
            else
            {
                if(IndexPlayer == 2)
                {
                    Qtable->at(IndexElement).second =  Qtable->at(IndexElement).second -solutionRef->planCC->at(i).second;
                }
                else
                {
                    cout << " Error, this element doesn't exist in Qtable, check your :PenalyzeActions PROCEDURE" << endl;
                }
            }
        }
        else
        cout << "Error, the element doesn't exist in Qtable!!" << endl;
    }
}
*/
//######################################################"18 -8- 2021 ####################################"
   bool AGENTQL::CheckFinalState(vector<TRXs> LTrxNTreateds)
   {
       if (LTrxNTreateds.empty()== true)
         return true;
       else
        return false;
   }
