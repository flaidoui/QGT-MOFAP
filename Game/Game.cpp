#include <iostream>
#include <fstream>
#include <string>
//------------------------------
#include <sstream>//LF:convert string
#include <time.h>
//------------------------------

//..................
#include<vector>
//.............................
#include<cmath> //abs
//---------------------
#include<map>
//----------------------
#include <utility>      // std::pair

// include 17-8-2021--------------------
#include "Game.h"
#include "../Commun/Commun.h"
#include "../PIPlayer/PIPlayer.h"
#include "../PSPlayer/PSPlayer.h"
#include "../AgentQL/AgentQL.h"
#include "../AgentQL/AgentQL.cpp"
//---------------------
///////////////////////////////Procédures et fonctions externes///////////////////////////////////////////////////////
/*
extern void InitLTrxNTreateds(vector<TRXs> &LTrxNTreateds, AFP * afpProblem);
extern void UpdateLTrxNTreateds(vector <TRXs> &LTrxNTreateds, TRXs trx,int Update);
extern void UpdateAllTRxFrequency(vector <TRXs> &LTrxNTreateds,int  f, int Update);
extern int vecmin(vector<double> x) ;
extern void VecMinValue(vector<double> x,int &index) ;*/
extern bool my_cmpInf(const pair <int,int>   &a, const pair <int,int>   &b);
//extern void ShowResult(string instance,double elapsed_secs,const int  max_gen,const double  epsilon,vector<Individual*> solutionSs,int indexNASHEbest,vector <double> NASHEJ,vector<Individual*> BestsolutionSs, Individual* solution);
extern bool my_cmpInfDoublePair(const pair <int,double>   &a, const pair <int,double>   &b);
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
<<<<<<< HEAD
const double  epsilon  = 0.1;//0.05;//0.1;
=======
const double  epsilon  = 0.1;//0.05;//0.1;
>>>>>>> 0514ea9fae0f841576757defb02235a9189b0fad
double EpsilonGreedy = 1.0;
//const int max_tries
///////////////////////////////////////////////////////////


  /* Game::Game()
   {
     PI = new (PIPlayer);
     PS = new (PSPlayer);
     afpProblemG = new AFP();
     solutionG = new Individual();

   }*/
///////////////////////////////////////////////////////////////
<<<<<<< HEAD
extern bool my_cmpSupFirst(const pair <int,double>   &a, const pair <int,double>   &b);
=======
extern bool my_cmpSupFirst(const pair <int,double>   &a, const pair <int,double>   &b);
>>>>>>> 0514ea9fae0f841576757defb02235a9189b0fad


bool my_cmpSupDoublePair(const pair <double,double>   &a, const pair <double,double>   &b)
{
    // smallest comes first
    return a.second > b.second;
}

   //////////////////////////////////////////////////////////////////////////
   Game::Game(AFP* afpProblem,const int max_gen)
   {
     int k;
     //on veut que PI apprends
     PI = new PIPlayer(afpProblem, max_gen, 1);
     //----------------------
<<<<<<< HEAD
     PS = new PSPlayer(afpProblem, max_gen, 1);

       QL = new AGENTQL(afpProblem, max_gen);

      //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

=======
     PS = new PSPlayer(afpProblem, max_gen, 1);

       QL = new AGENTQL(afpProblem, max_gen);

      //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

>>>>>>> 0514ea9fae0f841576757defb02235a9189b0fad

     //--------------------------------------------------
     solution = new Individual();
     solution->plan = new vector<int>;
     solution->plan->reserve(afpProblem->trxs.size());
     solution->planCC = new vector<pair<double,double> >;
     solution->planCC->reserve(afpProblem->trxs.size());
     solution->PSObj = 0.0 ;
     solution->PIObj = 0.0 ;
     for(k=0;k<solution->plan->size();k++)
     {
        solution->plan->at(k)=-1;
        solution->planCC->at(k).first = 0.0;
        solution->planCC->at(k).second = 0.0;
     }
     //BestsolutionSs.reserve(max_gen);
     HV = 0.0 ;
   }

    Game::~Game()
    {
        delete PI;
        delete PS;
<<<<<<< HEAD
        delete solution;
=======
        delete solution;
>>>>>>> 0514ea9fae0f841576757defb02235a9189b0fad
        //delete QL;
    }


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~é
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Superposition ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 void Game::PlayGameSuperp(int ApproachGameEvaluation,int ApproachGame,int NumGame,const int  max_gen,string instance,AFP* afpProblem,int StrategyTrxPI,int StrategyFreqPI,int StrategyTrxPS,int StrategyFreqPS)
{
     //°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°
    //ecrire le résultat dans un fichier : Resultat/resultatDatesystem.txt
    ofstream ResultFile;
    // Declaring argument for time()

    string dateTime;
    time_t rawtime;
    struct tm * timeinfo;
    char buffer [80];
    time ( &rawtime );
    timeinfo = localtime ( &rawtime );
     string path="Resultats/";
      ostringstream temp;  //temp as in temporary
    /*temp<<"_";
    int y = timeinfo->tm_year;
    temp<<y;*/
    temp << "AppG"<< ApproachGame<<"Eval_"<<ApproachGameEvaluation << "_";
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

   /* int sec =timeinfo->tm_sec;
    temp<<"_";
    temp<<sec;
    temp<<"sec";*/
    path=path+temp.str();      //str is temp as string

    stringstream ss;
    stringstream sss;
    stringstream ssss;
    stringstream sssss;
     stringstream stratFreqPI;
      stringstream stratFreqPS;
           stringstream stratTrxPI;
      stringstream stratTrxPS;
    sss << max_gen;
    ss << NumGame;
    ssss << epsilon;
    sssss << ApproachGameEvaluation;
    stratFreqPI << StrategyFreqPI;
    stratFreqPS << StrategyFreqPS;
    stratTrxPI << StrategyTrxPI;
    stratTrxPS << StrategyTrxPS;
     string appEv;
    switch (ApproachGameEvaluation)
    {
        case 11 :
        {
            appEv = "UneSolNash";
            break;
        }
        case 1 :
        {
            appEv = "Nash";
            break;
        }
         case 2 :
        {
            appEv = "Pareto";
            break;
        }
          case 22 :
        {
            appEv = "ParetoUneEcart";
            break;
        }
          case 21 :
        {
            appEv = "ParetoUneHV";
            break;
        }
           case 23 :
        {
            appEv = "ParetoUneNash";
            break;
        }
            case 24 :
        {
            appEv = "DistEucUne";
            break;
        }
         default:
            {
                cout << "erreur de choix d evaluation du jeu !!";
                break;
            }
    }

   // path = path + "_epsilon" + ssss.str()+ "_max_gen" + sss.str()+"_game" + ss.str() + "_" + "EvaluationApp_" + sssss.str() + "_" + instance;

 path = path + "_epsilon" + ssss.str()+ "_gen" + sss.str()+"_game" + ss.str() + "_" + appEv +  "_" + instance +  "_StrategyTrxPIPS_" + stratTrxPI.str()+ "_" + stratTrxPS.str() + "_StrategyFreqPIPS_" + stratFreqPI.str()+ "_" + stratFreqPS.str();
    path = path + ".txt";
    //
    ResultFile.open(path.c_str(),std::ios::app);
    if (!ResultFile) {
        cerr << "Unable to open file!!";
        exit(1);   // call system to stop
    }
    ResultFile <<"############### Game theory approach #################"<<endl;
    ResultFile << "max_gen : " <<max_gen<<endl;
    ResultFile << "Instance : "<< instance<< endl;

   //°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°
























   //°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°


    double elapsed_secs;

    //------------------------------------------------------------
    cout<<"########## game theory aproaches##############"<<endl;

    vector<TRXs> LTrxNTreateds;
    vector <Individual*> solutionSs;
    solutionSs.reserve(afpProblem->trxs.size());

    //-----------------variables Equilibre de nash..........
    vector<double> NASHEJ ;
    NASHEJ.reserve(max_gen);
    double NASHEbest;
    int indexNASHEbest;
    //..................................................
    int j,k;//,i,k,l;
    cout<<" size solution "<< afpProblem->trxs.size()<<endl;
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //pour calculer le temps d'excecution
    clock_t start = clock();


    //var super position -----------
    ///////////////////////////////////////////////////////////////
    int max_tries = 2;//afpProblem->trxs.size();
    ///////////////////////////////////////////////////////////////
    int i,l;
    //------------------------------------------------------------




    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    for(j=0; j<max_gen;j++)
    {

        Individual * solution;
        //à chaque génération, on initialise  la solution(individual)
        solution = new Individual();
        solution->plan = new vector<int>(afpProblem->trxs.size());
        solution->planCC = new vector<pair<double,double> >(afpProblem->trxs.size());

        for(k=0;k<solution->plan->size();k++)
        {
            solution->plan->at(k)=-1;
            solution->planCC->at(k).first = 0.0;
            solution->planCC->at(k).second = 0.0;
            solution ->PIObj = 0.0 ;
            solution->PSObj = 0.0;

        }

          vector<TRXs> LTrxNTreateds;
        Individual * solutionTemp;
        //à chaque génération, on initialise  la solution(individual)


        // vérification de solutionTemp
        /* for(k=0;k<solutionTemp->plan->size();k++)
        {
            cout << "solutionTemp->plan->at(k) "<<      solutionTemp->plan->at(k) << endl;
        }*/
        //initialiser la liste des trx non-traité --

        //initialiser la liste des trx non-traité --
        LTrxNTreateds.reserve(afpProblem->trxs.size());
        InitLTrxNTreateds(LTrxNTreateds,afpProblem);//initailiser le vecteur des trx non traité

        //---------------------------------------------- La superposition ---------------------------------------------
        //----------------------------------------------------------------------------------------------------
        TRXs trx;int f;bool test;
        int t;

        //+++++++++++++++++++++
          vector<TRXs> LTrxNTreatedsPI;
          LTrxNTreatedsPI.reserve(afpProblem->trxs.size());
          vector<TRXs> LTrxNTreatedsPS;
          LTrxNTreatedsPS.reserve(afpProblem->trxs.size());
        //++++++++++++++++++++
          //================================================================================
        vector <int> vectSolPI;//vecteur de solution du joueur PI
        vectSolPI.reserve(afpProblem->trxs.size());//vecteur de solution du joueur PI
        vector <int> vectSolPS;
        vectSolPS.reserve(afpProblem->trxs.size());//vecteur de solution du joueur PS
        vector <int> vectSol;
        vectSol.reserve(afpProblem->trxs.size());//vecteur de solution

           //====================================================================================

        for (t=0;t<max_tries; t++)
        {
            //***************************************************************************
            //*********************Initialiser la solution de premier joueur *******************************
            Individual* solutionPI;
            solutionPI = new Individual();
            solutionPI->plan = new vector<int>(afpProblem->trxs.size());
            solution->planCC = new vector<pair<double,double> >(afpProblem->trxs.size());

           //================================================================================
           //vector <int> vectSolPI (afpProblem->trxs.size());//vecteur de solution du joueur PI
           //vector <int> vectSolPS (afpProblem->trxs.size());//vecteur de solution du joueur PS
           //vector <int> vectSol (afpProblem->trxs.size());//vecteur de solution du joueur PI
           //====================================================================================

            //======== copier la solution partielle
            for(k=0;k<afpProblem->trxs.size();k++)
            {
                solutionPI->plan->at(k) = solution->plan->at(k);//vectSol.at(k);
                //solutionPI->plan->push_back(solution->plan->at(k));
               // solutionPI->planCC->at(k)=0.0;
            }

            //initialiser la liste des trx non-traité --
            //vector<TRXs> LTrxNTreatedsPI;
             // LTrxNTreatedsPI.reserve(solutionPI->plan->size());
            // InitLTrxNTreateds(LTrxNTreatedsPI,afpProblem);//initailiser le vecteur des trx non traité
            //LTrxNTreatedsPI = LTrxNTreateds;

            for(k=0;k<LTrxNTreateds.size();k++)
            {
                 LTrxNTreatedsPI.push_back(LTrxNTreateds[k]) ;
            }

            //****************************************************
            //***************************************************
            while(LTrxNTreatedsPI.empty()==false)
            {
                PI-> Play(instance,StrategyTrxPI, StrategyFreqPI,trx, LTrxNTreatedsPI,solutionPI, afpProblem);
                //PI-> Play(StrategyTrxPI, StrategyFreqPI,trx, LTrxNTreateds,solution, afpProblem);
            }

            //********************************************************
            //copier la solution trouvée dans un vecteur
            /*for(k = 0 ; k < afpProblem->trxs.size(); k++)
            {
                vectSolPI.push_back(solutionPI->plan->at(k));
            }*/
            //supprimer la solution PI

            // LTrxNTreatedsPI.erase(LTrxNTreatedsPI.begin(),LTrxNTreatedsPI.end());
            vector<TRXs>().swap(LTrxNTreatedsPI);
            //delete(solutionPI);
            //***************************************************************************
            //*********************Initialiser la solution* du joueur PS******************************
            Individual* solutionPS;
            solutionPS = new Individual();
            solutionPS->plan = new vector<int>(afpProblem->trxs.size());
            solution->planCC = new vector<pair<double,double> >(afpProblem->trxs.size());
            for(k=0;k<afpProblem->trxs.size();k++)
            {
                solutionPS->plan->at(k) =    solution->plan->at(k);
               // solutionPS->planCC->at(k)=0.0;
                // solutionPS->plan->push_back(solution->plan->at(k));
            }
              //vector<TRXs> LTrxNTreatedsPS;
              //------------remplir le vecteur LTrxNTreatedsPS
            for(k=0;k<LTrxNTreateds.size();k++)
            {
                 LTrxNTreatedsPS.push_back(LTrxNTreateds[k]) ;
            }
           // LTrxNTreatedsPS.reserve(solutionPS->plan->size());
           // InitLTrxNTreateds(LTrxNTreatedsPS,afpProblem);//initailiser le vecteur des trx non traité
            //LTrxNTreatedsPS=LTrxNTreateds;
            //****************************************************
            //***************************************************

           while(LTrxNTreatedsPS.empty()==false)
            {

               PS-> Play(instance,StrategyTrxPS, StrategyFreqPS, LTrxNTreatedsPS,trx,solutionPS,afpProblem);
            }
            //********************************************************

            //supprimer la solution PI



            vector<TRXs>().swap(LTrxNTreatedsPS);



            //copier la solution trouvée dans un vecteur
           /* for(k=0;k< afpProblem->trxs.size();k++)
            {
                vectSolPS.push_back(solutionPS->plan->at(k));
            }*/
           // delete(solutionPS);
            //***************************************************************************

            //****************************************************
            //*********************Detecter la rassemblance*******************************
            int r;//itérateur de rassemblance
            int s=0;
            l = 0;
            //garder la rassemblance sinon les autres valeur sont à -1
           for (r=0; r < afpProblem->trxs.size();r++)
            {
                if (solution->plan->at(r)== -1)//(vectSol.at(k) == -1on n a pas encore remplie la solution
                {
                    int freq1 = solutionPI->plan->at(r);//vectSolPI.at(r);//solutionPI->plan->at(r);//vectSolPI[r];//;  //solutionPS->plan->at(k)=//vectSolPI[r];
                    int freq2 = solutionPS->plan->at(r);//vectSolPS.at(r);//solutionPS->plan->at(r);//vectSolPS.at(r);//solutionPS->plan->at(r);;
                   // cout << " /////////////////  freq1 //////////// " << freq1 << endl;
                   // cout << " freq2 ***************** " << freq2 << endl;

                    if(freq1 == freq2)//les fréquences choisi par les deux joueur sont égale, on la garde
                    {
                        solution->plan->at(r) = freq1;
                       // vectSol.at(k) = freq1;
                        UpdateLTrxNTreateds(LTrxNTreateds,afpProblem->trxs[r] ,-1);
                        l = l+1;
                    }
                }

                 //solution -> plan->at(r) = solutionPI->plan->at(r);
            }//fin rassemblance
            //vider les vecteur non utilisés
           //vectSolPI.erase(vectSolPI.begin(),vectSolPI.end());
            //vector<int>().swap(vectSolPI);
            // vectSolPI.erase(vectSolPS.begin(),vectSolPS.end());
            //vector<int>().swap(vectSolPS);

            cout << "degré de  resemblance  " <<l <<endl;
            //delete(solutionPS);
            //**************************************************************************************
            //************************** Mettre à jour la liste des trx non traité disponibles ******


            delete solutionPI;
            delete solutionPS;
            //***************************************************
            //***************************************************
        if (l == afpProblem->trxs.size()) t = max_tries;// on a copier toute la solution

        }// for (t=0;t<max_tries; t++)

 //   }//tester uniquement pour la première génération    //---------------------------------------------------------------------------

       cout << "number of trx  ::" << afpProblem->trxs.size()<<endl;

       //-------------------------------------------------End superposition ----------------------------------------
       //-----------------------------------------------------------------------------------------------------------
//TRXs trx;
//on remplie les partie non copié donc si l = solution->plan->size(), cela veut dire on a trouvé une solution complète toute
  // Au début choisir alétoirement un trx
    srand ( unsigned ( time(0) ) );
    int choice;
    //generate secret number between 1 and 2:
    choice = rand() % 2 + 1;
    //  choice = 1 ;
    cout <<"choice is : " << choice <<endl;
   /* if (choice ==1)//c est le premier joueur qui joue
    {
        PI-> Play(StrategyTrxPI, StrategyFreqPI,trx, LTrxNTreateds,solution, afpProblem);
    }
    else// cest le deuxième joueur qui joue
    {
       PS-> Play(StrategyTrxPS, StrategyFreqPS, LTrxNTreateds,solution,afpProblem);
    }*/
//-----------------------------------------------------------------
    while(LTrxNTreateds.empty()==false)
    {
                //PI-> Play(StrategyTrxPI, StrategyFreqPI,trx, LTrxNTreateds,solution, afpProblem);
            if(choice == 1)
            {
                 PI-> Play(instance,StrategyTrxPI, StrategyFreqPI,trx, LTrxNTreateds,solution, afpProblem);//PI joue avec la dexiem stratégie:trx random-random frequency
            }
            else
            {

                PS-> Play(instance,StrategyTrxPS, StrategyFreqPS, LTrxNTreatedsPS,trx,solution,afpProblem);
            }
            //----
            if (LTrxNTreateds.empty()== false)
            {
               if(choice == 1)
               {
                  PS-> Play(instance,StrategyTrxPS, StrategyFreqPS, LTrxNTreatedsPS,trx,solution,afpProblem);
               }
               else
               {
                   PI-> Play(instance,StrategyTrxPI, StrategyFreqPI,trx, LTrxNTreateds,solution, afpProblem);
               }
            }

        }//while


        //]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

        //calculer le cout de la solution trpuvée
        solution->PIObj = afpProblem->ComputeSolutionInterference(solution);//LF comment : ma fonction objectif (cacul de cout intererence)
        solution->PSObj = afpProblem->ComputeSolutionSeparationCost(solution);//LF comment : ma fonction objectif (cacule le cout de separation)
        //Enregistrer la solution actuelle
        solutionSs.push_back(solution);


    vector<TRXs>().swap(LTrxNTreateds);

    }//max_gen

      // ResultFile.close();
    //-----------------variables Equilibre de nash..........

    //NASHEJ.reserve(max_gen);
 //-----------------variables Equilibre de nash..........
   // vector<double> NASHEJ ;
    //NASHEJ.reserve(max_gen);
    //double NASHEbest;
<<<<<<< HEAD
   // int indexNASHEbest;
=======
   // int indexNASHEbest;
>>>>>>> 0514ea9fae0f841576757defb02235a9189b0fad
   double HVValue;
    switch(ApproachGameEvaluation)
    {
        case 11:
        {
<<<<<<< HEAD
            GameEvaluationNashOneSol( instance, max_gen,solutionSs,start, elapsed_secs,indexNASHEbest,NASHEJ);
=======
            GameEvaluationNashOneSol( instance, max_gen,solutionSs,start, elapsed_secs,indexNASHEbest,NASHEJ);
>>>>>>> 0514ea9fae0f841576757defb02235a9189b0fad
            HVValue = HV;
            break;
        }
        case 1://evaluation nash ensemble
        {
<<<<<<< HEAD
            GameEvaluation( instance, max_gen,solutionSs,start, elapsed_secs,indexNASHEbest,NASHEJ);
=======
            GameEvaluation( instance, max_gen,solutionSs,start, elapsed_secs,indexNASHEbest,NASHEJ);
>>>>>>> 0514ea9fae0f841576757defb02235a9189b0fad
            HVValue = HV;
            break;
        }
         case 2:
        {
<<<<<<< HEAD
            GameEvaluationPareto( instance, max_gen,solutionSs,start, elapsed_secs,indexNASHEbest,NASHEJ);
=======
            GameEvaluationPareto( instance, max_gen,solutionSs,start, elapsed_secs,indexNASHEbest,NASHEJ);
>>>>>>> 0514ea9fae0f841576757defb02235a9189b0fad
            HVValue = HV;
            break;
        }
          case 22:
        {
<<<<<<< HEAD
            GameEvaluationParetoEcart( instance, max_gen,solutionSs,start, elapsed_secs,indexNASHEbest,NASHEJ);
=======
            GameEvaluationParetoEcart( instance, max_gen,solutionSs,start, elapsed_secs,indexNASHEbest,NASHEJ);
>>>>>>> 0514ea9fae0f841576757defb02235a9189b0fad
            HVValue = HV;
            break;
        }
           case 21:
        {
<<<<<<< HEAD
            GameEvaluationParetoHV( instance, max_gen,solutionSs,start, elapsed_secs,indexNASHEbest,NASHEJ);
=======
            GameEvaluationParetoHV( instance, max_gen,solutionSs,start, elapsed_secs,indexNASHEbest,NASHEJ);
>>>>>>> 0514ea9fae0f841576757defb02235a9189b0fad
            HVValue = HV;
            break;
        }
          case 23:
        {
<<<<<<< HEAD
            GameEvaluationParetoUneSolNash( instance, max_gen,solutionSs,start, elapsed_secs,indexNASHEbest,NASHEJ, HVValue);
=======
            GameEvaluationParetoUneSolNash( instance, max_gen,solutionSs,start, elapsed_secs,indexNASHEbest,NASHEJ, HVValue);
>>>>>>> 0514ea9fae0f841576757defb02235a9189b0fad
            HVValue = HV;
            break;
        }
          case 24:
        {
<<<<<<< HEAD
            GameEvaluationDistEuclUneSol( instance, max_gen,solutionSs,start, elapsed_secs,indexNASHEbest,NASHEJ);
=======
            GameEvaluationDistEuclUneSol( instance, max_gen,solutionSs,start, elapsed_secs,indexNASHEbest,NASHEJ);
>>>>>>> 0514ea9fae0f841576757defb02235a9189b0fad
            HVValue = HV;
            break;
        }

         default:
            {
<<<<<<< HEAD
                cout << "Erreur de choix de stratégie d'évaluation " << endl;
=======
                cout << "Erreur de choix de stratégie d'évaluation " << endl;
>>>>>>> 0514ea9fae0f841576757defb02235a9189b0fad
                HVValue = HV;
                break;
            }
 }
        ShowResult(ApproachGameEvaluation,instance,NumGame,elapsed_secs,max_gen,epsilon,solutionSs,indexNASHEbest,NASHEJ,BestsolutionSs,solution,path, HVValue);


}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~é
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ End superposition ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void Game::PlayGame(Individual* solutionRef,int ApproachGameEvaluation,int ApproachGame,int NumGame,const int max_gen, string instance,AFP* afpProblem, int & StrategyTrxPI,int & StrategyFreqPI,int & StrategyTrxPS,int & StrategyFreqPS)
{
  int periode = 1000;
     //-----------------variables Equilibre de nash..........
    vector<double> NASHEJ ;
    //NASHEJ.reserve(max_gen);
    double NASHEbest;
<<<<<<< HEAD
    int indexNASHEbest;
=======
    int indexNASHEbest;
>>>>>>> 0514ea9fae0f841576757defb02235a9189b0fad
        double HVValue;
    //°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°
    //ecrire le résultat dans un fichier : Resultat/resultatDatesystem.txt
 ofstream ResultFile;
    // Declaring argument for time()

    string dateTime;
    time_t rawtime;
    struct tm * timeinfo;
    char buffer [80];
    time ( &rawtime );
    timeinfo = localtime ( &rawtime );
  //  string path="Resultats/result_";7
<<<<<<< HEAD
    string path="Resultats/Q1Com_";
=======
    string path="Resultats/Q1Com_";
>>>>>>> 0514ea9fae0f841576757defb02235a9189b0fad
    ;
      ostringstream temp;  //temp as in temporary
    /*temp<<"_";
    int y = timeinfo->tm_year;
    temp<<y;*/
    temp << "AppG"<< ApproachGame<<"Eval_"<<ApproachGameEvaluation << "_";
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

   /* int sec =timeinfo->tm_sec;
    temp<<"_";
    temp<<sec;
    temp<<"sec";*/
    path=path+temp.str();      //str is temp as string

    stringstream ss;
    stringstream sss;
    stringstream ssss;
    stringstream sssss;
     stringstream stratFreqPI;
      stringstream stratFreqPS;
           stringstream stratTrxPI;
      stringstream stratTrxPS;
    sss << max_gen;
    ss << NumGame;
    ssss << epsilon;
    sssss << ApproachGameEvaluation;
    stratFreqPI << StrategyFreqPI;
    stratFreqPS << StrategyFreqPS;
    stratTrxPI << StrategyTrxPI;
    stratTrxPS << StrategyTrxPS;
     string appEv;
    switch (ApproachGameEvaluation)
    {
        case 11 :
        {
            appEv = "UneSolNash";
            break;
        }
        case 1 :
        {
            appEv = "Nash";
            break;
        }
         case 2 :
        {
            appEv = "Pareto";
            break;
        }
          case 22 :
        {
            appEv = "ParetoUneEcart";
            break;
        }
          case 21 :
        {
            appEv = "ParetoUneHV";
            break;
        }
           case 23 :
        {
            appEv = "ParetoUneNash";
            break;
        }
            case 24 :
        {
            appEv = "DistEucUne";
            break;
        }
         default:
            {
                cout << "erreur de choix d evaluation du jeu !!";
                break;
            }
    }

   // path = path + "_epsilon" + ssss.str()+ "_max_gen" + sss.str()+"_game" + ss.str() + "_" + "EvaluationApp_" + sssss.str() + "_" + instance;

 path = path + "_epsilon" + ssss.str()+ "_gen" + sss.str()+"_game" + ss.str() + "_" + appEv +  "_" + instance +  "_StrategyTrxPIPS_" + stratTrxPI.str()+ "_" + stratTrxPS.str();
<<<<<<< HEAD
    path = path + ".txt";

=======
    path = path + ".txt";

>>>>>>> 0514ea9fae0f841576757defb02235a9189b0fad
    //pathnash = pathnash +  "_" + instance  + "_";
    //
    ResultFile.open(path.c_str(),std::ios::app);
    if (!ResultFile) {
        cerr << "Unable to open file!!";
        exit(1);   // call system to stop
    }
    ResultFile <<"############### Game theory approach #################"<<endl;
    ResultFile << "max_gen : " <<max_gen<<endl;
<<<<<<< HEAD
    ResultFile << "Instance : "<< instance<< endl;
=======
    ResultFile << "Instance : "<< instance<< endl;
>>>>>>> 0514ea9fae0f841576757defb02235a9189b0fad
       ResultFile << "Epsilon : "<< epsilon << endl;

   //°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°


    double elapsed_secs;

    //------------------------------------------------------------
    cout<<"########## game theory aproaches##############"<<endl;


    vector <Individual*> solutionSs;
    //solutionSs.reserve(max_gen);

    //..................................................
    int j,k;//,i,k,l;
    //cout<<" size solution "<< afpProblem->trxs.size()<<endl;
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //pour calculer le temps d'excecution
    clock_t start = clock();
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //while(clock()- start)
<<<<<<< HEAD
  //#pragma omp parallel for
   double r, rEpsilon, rAlpha, rGamma;
  double EpsilonGreedyInit = 0.1;
  double EpsilonGreedyEnd = 0.001;
    double AlphaInit = 0.1;
  double AlphaEnd = 0.001;

  double GammaInit = 0.95;
  double GammaEnd = 0.8;
  int half = max_gen / 3;
  EpsilonGreedy = 0.1;
  int mi_max_gen;//la moitié de l'intervalle
   mi_max_gen = max_gen/2;
   cout << "mi_max_gen :" << mi_max_gen <<endl;
  srand ( unsigned ( time(0) ) );
    for(j=0; j < max_gen;j++)
    {
      // EpsilonGreedy = (j+1)/(max_gen+1);
     // EpsilonGreedy = 1/(j+1);
    // EpsilonGreedy = max_gen / (max_gen+j);
    // if ( j == half)
   // {

          r = (max_gen - j) / max_gen;




      /* if ( j < mi_max_gen)
        {
            //°°°°°°°°°°°°°°°°° Alpha : Au dé°but on connait rien, on fait importance aux information précédente°°°°°°°°°°°°°°°
            AlphaInit = 0.99;
            AlphaEnd = 0.51;
            rAlpha = (mi_max_gen -j) / mi_max_gen;
            //°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°
            //°°°°°°°°°°° Gamma : on a rien appri on fait pas importance aux informations future: gamma faibe°°°°°°°°°°°°°°°°°°°°°°°°

            GammaInit = 0.5;
            GammaEnd = 0.01;
            rGamma = (mi_max_gen -j) / mi_max_gen;
            //°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°
            EpsilonGreedyInit = 0.5;
             EpsilonGreedyEnd = 0.25;
             rEpsilon = (mi_max_gen -j) / mi_max_gen;
        }
        //°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°
        else
        {
             AlphaInit = 0.5;
            AlphaEnd = 0.01;
            rAlpha = (max_gen  - (j - mi_max_gen)) / max_gen;
            //°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°
            GammaInit = 0.99;
            GammaEnd = 0.51;
            rGamma = (max_gen  - (j - mi_max_gen)) / max_gen;
            //°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°
             //°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°
            EpsilonGreedyInit = 0.251;
             EpsilonGreedyEnd = 0.001;
             rEpsilon = (max_gen  - (j - mi_max_gen)) / max_gen;

        }*/
          //QL->QALPHA = (AlphaInit - AlphaEnd) * rAlpha + AlphaEnd;
          ////QL->QGAMMA = (GammaInit - GammaEnd) * rGamma + GammaEnd;

          //EpsilonGreedy = (EpsilonGreedyInit - EpsilonGreedyEnd) * rEpsilon + EpsilonGreedyEnd;
        EpsilonGreedy = (EpsilonGreedyInit - EpsilonGreedyEnd) * r + EpsilonGreedyEnd;

         QL->QALPHA = (AlphaInit - AlphaEnd) * r + AlphaEnd;
        QL->QGAMMA = (GammaInit - GammaEnd) * r + GammaEnd;
       // QL->QALPHA = 1/pow(j,r);
        //QL->QGAMMA = 1/pow(j,r);

    //}

    /*for(j=0; j<max_gen;j++)
    {
        EpsilonGreedy = 1/(1+j);
        QL->QALPHA = 1/pow((1+j),0.5);
        QL->QGAMMA = 1/pow((1+j),0.5);*/

=======
  //#pragma omp parallel for
   double r, rEpsilon, rAlpha, rGamma;
  double EpsilonGreedyInit = 0.1;
  double EpsilonGreedyEnd = 0.001;
    double AlphaInit = 0.1;
  double AlphaEnd = 0.001;

  double GammaInit = 0.95;
  double GammaEnd = 0.8;
  int half = max_gen / 3;
  EpsilonGreedy = 0.1;
  int mi_max_gen;//la moitié de l'intervalle
   mi_max_gen = max_gen/2;
   cout << "mi_max_gen :" << mi_max_gen <<endl;
  srand ( unsigned ( time(0) ) );
    for(j=0; j < max_gen;j++)
    {
      // EpsilonGreedy = (j+1)/(max_gen+1);
     // EpsilonGreedy = 1/(j+1);
    // EpsilonGreedy = max_gen / (max_gen+j);
    // if ( j == half)
   // {

          r = (max_gen - j) / max_gen;




      /* if ( j < mi_max_gen)
        {
            //°°°°°°°°°°°°°°°°° Alpha : Au dé°but on connait rien, on fait importance aux information précédente°°°°°°°°°°°°°°°
            AlphaInit = 0.99;
            AlphaEnd = 0.51;
            rAlpha = (mi_max_gen -j) / mi_max_gen;
            //°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°
            //°°°°°°°°°°° Gamma : on a rien appri on fait pas importance aux informations future: gamma faibe°°°°°°°°°°°°°°°°°°°°°°°°

            GammaInit = 0.5;
            GammaEnd = 0.01;
            rGamma = (mi_max_gen -j) / mi_max_gen;
            //°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°
            EpsilonGreedyInit = 0.5;
             EpsilonGreedyEnd = 0.25;
             rEpsilon = (mi_max_gen -j) / mi_max_gen;
        }
        //°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°
        else
        {
             AlphaInit = 0.5;
            AlphaEnd = 0.01;
            rAlpha = (max_gen  - (j - mi_max_gen)) / max_gen;
            //°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°
            GammaInit = 0.99;
            GammaEnd = 0.51;
            rGamma = (max_gen  - (j - mi_max_gen)) / max_gen;
            //°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°
             //°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°
            EpsilonGreedyInit = 0.251;
             EpsilonGreedyEnd = 0.001;
             rEpsilon = (max_gen  - (j - mi_max_gen)) / max_gen;

        }*/
          //QL->QALPHA = (AlphaInit - AlphaEnd) * rAlpha + AlphaEnd;
          ////QL->QGAMMA = (GammaInit - GammaEnd) * rGamma + GammaEnd;

          //EpsilonGreedy = (EpsilonGreedyInit - EpsilonGreedyEnd) * rEpsilon + EpsilonGreedyEnd;
        EpsilonGreedy = (EpsilonGreedyInit - EpsilonGreedyEnd) * r + EpsilonGreedyEnd;

         QL->QALPHA = (AlphaInit - AlphaEnd) * r + AlphaEnd;
        QL->QGAMMA = (GammaInit - GammaEnd) * r + GammaEnd;
       // QL->QALPHA = 1/pow(j,r);
        //QL->QGAMMA = 1/pow(j,r);

    //}

    /*for(j=0; j<max_gen;j++)
    {
        EpsilonGreedy = 1/(1+j);
        QL->QALPHA = 1/pow((1+j),0.5);
        QL->QGAMMA = 1/pow((1+j),0.5);*/

>>>>>>> 0514ea9fae0f841576757defb02235a9189b0fad
        vector<TRXs> LTrxNTreateds;
        Individual * solutionTemp;
        //à chaque génération, on initialise  la solution(individual)
        solutionTemp = new Individual();
        solutionTemp->plan = new vector<int>(afpProblem->trxs.size());
        solutionTemp->planCC = new vector<pair<double,double> >(afpProblem->trxs.size());
        solutionTemp->PIObj = 0.0 ;
        solutionTemp->PSObj = 0.0 ;
        for(k=0;k<solutionTemp->plan->size();k++)
        {
            solutionTemp->plan->at(k)=-1;
            solutionTemp->planCC->at(k).first = 0.0;
            solutionTemp->planCC->at(k).second = 0.0;


        }
        // vérification de solutionTemp
        /* for(k=0;k<solutionTemp->plan->size();k++)
        {
            cout << "solutionTemp->plan->at(k) "<<      solutionTemp->plan->at(k) << endl;
        }*/
        //initialiser la liste des trx non-traité --
        InitLTrxNTreateds(LTrxNTreateds,afpProblem);//initailiser le vecteur des trx non traité
        //--------------------------------------------
        TRXs trx;int f;
      //-------------------
        // Au début choisir alétoirement un trx

        int choice;
        //choisir aléatoirement un chiffre 1 ou 2. Si 1 c est le joueur PI qui joue, si 2: le joueur PS qui joue
        choice = rand() % 2 + 1;
       // choice = 1 ;
<<<<<<< HEAD
        cout <<"============choice is : ===========>" << choice <<endl;
=======
        cout <<"============choice is : ===========>" << choice <<endl;
>>>>>>> 0514ea9fae0f841576757defb02235a9189b0fad
        cout <<"============generation number : ===========>" << j <<endl;
        //#################################################"
        State stat,sdash;
        TRXs trxdash, inittrxdash;
        Action ActPI,ActPS,CorrespondingActionPI,CorrespondingActionTargetPI, CorrespondingActionPS,CorrespondingActionTargetPS;
        double QtargetPS,QtargetPI;
        double Reward;
<<<<<<< HEAD
        pair < State ,Action > PairStateActionPI, PairStateActionPS ;
        //===========================================================

        //######################################################
        //======== epsilon greedy =================


//choice = 1;
        double ProbGreedy ;
       ProbGreedy = (double)rand() / (double)RAND_MAX  ;
       // if ( j==0 )
        //    {
                CorrespondingActionPI = QL->GetPossibleAction();
                CorrespondingActionPS = QL->GetPossibleAction();

              if (choice == 1)
              {
                   choice = 2 ;
                    //0. choix aléatoire d'un état ----------------------------
                    PI->PIChooseTrx(1,LTrxNTreateds,inittrxdash,afpProblem,solutionTemp);
                    stat.UnTreatedTRXNumb = inittrxdash.trxID; // c'est le  de TRX initiallement choisi
                  //0.choix aléatoire de l'action initial ( choisir strategy trx, strategy freq à appliquer sur le trx deja choisix aléatoirement

                    //PI->PIChooseTrx(CorrespondingActionPI.ActTRX,LTrxNTreateds,inittrxdash,afpProblem,solutionTemp);
                    PI->PIChooseFrequency(instance,CorrespondingActionPI.ActFreq,inittrxdash,solutionTemp, afpProblem,f);
                    AddSolTrxFrequency(afpProblem,solutionTemp,inittrxdash ,f);
                    UpdateLTrxNTreateds(LTrxNTreateds, inittrxdash,-1); //Retirer trx de LTrxNTreated
                    // prochain etat est déterminé deja par la première action
                   // pour ne pas modifier la solution actuelle on crée une copie solTemp
=======
        pair < State ,Action > PairStateActionPI, PairStateActionPS ;
        //===========================================================

        //######################################################
        //======== epsilon greedy =================


//choice = 1;
        double ProbGreedy ;
       ProbGreedy = (double)rand() / (double)RAND_MAX  ;
       // if ( j==0 )
        //    {
                CorrespondingActionPI = QL->GetPossibleAction();
                CorrespondingActionPS = QL->GetPossibleAction();

              if (choice == 1)
              {
                   choice = 2 ;
                    //0. choix aléatoire d'un état ----------------------------
                    PI->PIChooseTrx(1,LTrxNTreateds,inittrxdash,afpProblem,solutionTemp);
                    stat.UnTreatedTRXNumb = inittrxdash.trxID; // c'est le  de TRX initiallement choisi
                  //0.choix aléatoire de l'action initial ( choisir strategy trx, strategy freq à appliquer sur le trx deja choisix aléatoirement

                    //PI->PIChooseTrx(CorrespondingActionPI.ActTRX,LTrxNTreateds,inittrxdash,afpProblem,solutionTemp);
                    PI->PIChooseFrequency(instance,CorrespondingActionPI.ActFreq,inittrxdash,solutionTemp, afpProblem,f);
                    AddSolTrxFrequency(afpProblem,solutionTemp,inittrxdash ,f);
                    UpdateLTrxNTreateds(LTrxNTreateds, inittrxdash,-1); //Retirer trx de LTrxNTreated
                    // prochain etat est déterminé deja par la première action
                   // pour ne pas modifier la solution actuelle on crée une copie solTemp
>>>>>>> 0514ea9fae0f841576757defb02235a9189b0fad
                   Individual * solTemp;
                   solTemp = new Individual();
                    // solTemp->plan = new vector<int>(afpProblem->trxs.size());
                    //   solTemp->planCC = new vector<pair<double,double> >(afpProblem->trxs.size());
                   solTemp ->PIObj = 0.0 ;
                   solTemp->PSObj = 0.0 ;

<<<<<<< HEAD
                   solTemp = solutionTemp;
                   PI->PIChooseTrx(StrategyTrxPI,LTrxNTreateds,trxdash,afpProblem,solTemp);
                   //-----------------prochain etat est sdash ----------------------------
                   sdash.UnTreatedTRXNumb = trxdash.trxID; //est le prochain etat//+++++++++++++++++++++
                   //--------------Evaluer la récompense-----------------------------------------------------------------------
                   //-------------------------------------------------------------------------------------
                   CorrespondingActionPI = QL->GetPossibleAction();
                   PI->PIChooseFrequency(instance,CorrespondingActionPI.ActFreq,trxdash,solTemp, afpProblem,f);
                   AddSolTrxFrequency(afpProblem,solTemp,trxdash ,f);
                   QL->ObserveReward(1,solutionTemp, solTemp,Reward, instance);//+++++++++Reward++++++++++
                   QtargetPI = QL->GetQtarget(sdash , CorrespondingActionTargetPI);
                    PairStateActionPI.first.UnTreatedTRXNumb = stat.UnTreatedTRXNumb;
                   //PairStateActionPI.second.ActTRX = CorrespondingActionPI.ActTRX;
                   PairStateActionPI.second.ActFreq = CorrespondingActionPI.ActFreq;
                  // int indexQtarget = PI->QLPI->GetIndexPairStateAction(PairStateAction);
                   //maintenant mettre ajour Qvaleur de stat
                   QL->UpdateQtable(Reward, PairStateActionPI, QtargetPI);//++++++++++++++++++ Mise à jour de la table ++

                   //=====================================
                   //mettre à jour prochain action et prochain etat

                   CorrespondingActionPI = CorrespondingActionTargetPI;
                   stat = sdash;
                   //=======================================================
                   // Mettre à jour la solution ===========================
                   solutionTemp = solTemp ;
                   //=================== mettre à jour la liste des TRX non traité
                   UpdateLTrxNTreateds(LTrxNTreateds, trxdash,-1); //Retirer trx de LTrxNTreated
               }


        else// choice =2; cest le deuxième joueur qui joue PSSSSSSSSSSSSSSSSSSs
       {
                    choice = 1;
                    //0. choix aléatoire d'un état ----------------------------
                    PS->PSChooseTrx(afpProblem,1, LTrxNTreateds,inittrxdash);
                    stat.UnTreatedTRXNumb = inittrxdash.trxID; // c'est le  de TRX initiallement choisi
                  //0.choix aléatoire de l'action initial ( choisir strategy trx, strategy freq à appliquer sur le trx deja choisix aléatoirement

                  //  cout<< "CorrespondingActionPS.ActTRX " << CorrespondingActionPS.ActTRX << endl;
                    cout<< "CorrespondingActionPS.ActFreq " << CorrespondingActionPS.ActFreq << endl;
                    //PI->PIChooseTrx(CorrespondingActionPI.ActTRX,LTrxNTreateds,inittrxdash,afpProblem,solutionTemp);
                    //void PSChooseFrequency(string instance,int StrategyFreq,TRXs trx,int &f,Individual * &solution,AFP * afpProblem);
                    PS->PSChooseFrequency(instance,CorrespondingActionPS.ActFreq,inittrxdash,f,solutionTemp,afpProblem);
                    AddSolTrxFrequency(afpProblem,solutionTemp,inittrxdash ,f);
                    UpdateLTrxNTreateds(LTrxNTreateds, inittrxdash,-1); //Retirer trx de LTrxNTreated
                    // prochain etat est déterminé deja par la première action
                   // pour ne pas modifier la solution actuelle on crée une copie solTemp
=======
                   solTemp = solutionTemp;
                   PI->PIChooseTrx(StrategyTrxPI,LTrxNTreateds,trxdash,afpProblem,solTemp);
                   //-----------------prochain etat est sdash ----------------------------
                   sdash.UnTreatedTRXNumb = trxdash.trxID; //est le prochain etat//+++++++++++++++++++++
                   //--------------Evaluer la récompense-----------------------------------------------------------------------
                   //-------------------------------------------------------------------------------------
                   CorrespondingActionPI = QL->GetPossibleAction();
                   PI->PIChooseFrequency(instance,CorrespondingActionPI.ActFreq,trxdash,solTemp, afpProblem,f);
                   AddSolTrxFrequency(afpProblem,solTemp,trxdash ,f);
                   QL->ObserveReward(1,solutionTemp, solTemp,Reward, instance);//+++++++++Reward++++++++++
                   QtargetPI = QL->GetQtarget(sdash , CorrespondingActionTargetPI);
                    PairStateActionPI.first.UnTreatedTRXNumb = stat.UnTreatedTRXNumb;
                   //PairStateActionPI.second.ActTRX = CorrespondingActionPI.ActTRX;
                   PairStateActionPI.second.ActFreq = CorrespondingActionPI.ActFreq;
                  // int indexQtarget = PI->QLPI->GetIndexPairStateAction(PairStateAction);
                   //maintenant mettre ajour Qvaleur de stat
                   QL->UpdateQtable(Reward, PairStateActionPI, QtargetPI);//++++++++++++++++++ Mise à jour de la table ++

                   //=====================================
                   //mettre à jour prochain action et prochain etat

                   CorrespondingActionPI = CorrespondingActionTargetPI;
                   stat = sdash;
                   //=======================================================
                   // Mettre à jour la solution ===========================
                   solutionTemp = solTemp ;
                   //=================== mettre à jour la liste des TRX non traité
                   UpdateLTrxNTreateds(LTrxNTreateds, trxdash,-1); //Retirer trx de LTrxNTreated
               }


        else// choice =2; cest le deuxième joueur qui joue PSSSSSSSSSSSSSSSSSSs
       {
                    choice = 1;
                    //0. choix aléatoire d'un état ----------------------------
                    PS->PSChooseTrx(afpProblem,1, LTrxNTreateds,inittrxdash);
                    stat.UnTreatedTRXNumb = inittrxdash.trxID; // c'est le  de TRX initiallement choisi
                  //0.choix aléatoire de l'action initial ( choisir strategy trx, strategy freq à appliquer sur le trx deja choisix aléatoirement

                  //  cout<< "CorrespondingActionPS.ActTRX " << CorrespondingActionPS.ActTRX << endl;
                    cout<< "CorrespondingActionPS.ActFreq " << CorrespondingActionPS.ActFreq << endl;
                    //PI->PIChooseTrx(CorrespondingActionPI.ActTRX,LTrxNTreateds,inittrxdash,afpProblem,solutionTemp);
                    //void PSChooseFrequency(string instance,int StrategyFreq,TRXs trx,int &f,Individual * &solution,AFP * afpProblem);
                    PS->PSChooseFrequency(instance,CorrespondingActionPS.ActFreq,inittrxdash,f,solutionTemp,afpProblem);
                    AddSolTrxFrequency(afpProblem,solutionTemp,inittrxdash ,f);
                    UpdateLTrxNTreateds(LTrxNTreateds, inittrxdash,-1); //Retirer trx de LTrxNTreated
                    // prochain etat est déterminé deja par la première action
                   // pour ne pas modifier la solution actuelle on crée une copie solTemp
>>>>>>> 0514ea9fae0f841576757defb02235a9189b0fad
                   Individual * solTemp;
                   solTemp = new Individual();
                    // solTemp->plan = new vector<int>(afpProblem->trxs.size());
                    //   solTemp->planCC = new vector<pair<double,double> >(afpProblem->trxs.size());
                   solTemp ->PIObj = 0.0 ;
                   solTemp->PSObj = 0.0 ;

<<<<<<< HEAD
                   solTemp = solutionTemp;
                   //-------------------------------------------------
                   //observer les recompense

                   PS->PSChooseTrx(afpProblem,StrategyTrxPS,LTrxNTreateds,trxdash);
                   //-----------------prochain etat est sdash ----------------------------
                   sdash.UnTreatedTRXNumb = trxdash.trxID; //est le prochain etat//+++++++++++++++++++++
                   //--------------Evaluer la récompense-----------------------------------------------------------------------
                   //-------------------------------------------------------------------------------------
                   //void PSChooseFrequency(string instance,int StrategyFreq,TRXs trx,int &f,Individual * &solution,AFP * afpProblem);
                    CorrespondingActionPS = QL->GetPossibleAction();

                   PS->PSChooseFrequency(instance,CorrespondingActionPS.ActFreq,trxdash,f,solTemp,afpProblem);
                   AddSolTrxFrequency(afpProblem,solTemp,trxdash ,f);
                   QL->ObserveReward(2,solutionTemp, solTemp,Reward, instance);//+++++++++Reward++++++++++
                   QtargetPS = QL->GetQtarget(sdash , CorrespondingActionTargetPS);
                   PairStateActionPS.first.UnTreatedTRXNumb = stat.UnTreatedTRXNumb;
                   //PairStateActionPS.second.ActTRX = CorrespondingActionPS.ActTRX;
                   PairStateActionPS.second.ActFreq = CorrespondingActionPS.ActFreq;
                   //int indexQtarget = PS->QLPS->GetIndexPairStateAction(PairStateAction);
                   //maintenant mettre ajour Qvaleur de stat
                   QL->UpdateQtable(Reward, PairStateActionPS, QtargetPS);//++++++++++++++++++ Mise à jour de la table ++

                   //=====================================
                   //mettre à jour prochain action et prochain etat

                   CorrespondingActionPS = CorrespondingActionTargetPS;
                   stat = sdash;
                   //=======================================================
                   // Mettre à jour la solution ===========================
                   solutionTemp = solTemp ;
                   //=================== mettre à jour la liste des TRX non traité
                   UpdateLTrxNTreateds(LTrxNTreateds, trxdash,-1); //Retirer trx de LTrxNTreated

              }//choice

                //solTemp = NULL;
                //delete solTemp;
  //  }// j===0



=======
                   solTemp = solutionTemp;
                   //-------------------------------------------------
                   //observer les recompense

                   PS->PSChooseTrx(afpProblem,StrategyTrxPS,LTrxNTreateds,trxdash);
                   //-----------------prochain etat est sdash ----------------------------
                   sdash.UnTreatedTRXNumb = trxdash.trxID; //est le prochain etat//+++++++++++++++++++++
                   //--------------Evaluer la récompense-----------------------------------------------------------------------
                   //-------------------------------------------------------------------------------------
                   //void PSChooseFrequency(string instance,int StrategyFreq,TRXs trx,int &f,Individual * &solution,AFP * afpProblem);
                    CorrespondingActionPS = QL->GetPossibleAction();

                   PS->PSChooseFrequency(instance,CorrespondingActionPS.ActFreq,trxdash,f,solTemp,afpProblem);
                   AddSolTrxFrequency(afpProblem,solTemp,trxdash ,f);
                   QL->ObserveReward(2,solutionTemp, solTemp,Reward, instance);//+++++++++Reward++++++++++
                   QtargetPS = QL->GetQtarget(sdash , CorrespondingActionTargetPS);
                   PairStateActionPS.first.UnTreatedTRXNumb = stat.UnTreatedTRXNumb;
                   //PairStateActionPS.second.ActTRX = CorrespondingActionPS.ActTRX;
                   PairStateActionPS.second.ActFreq = CorrespondingActionPS.ActFreq;
                   //int indexQtarget = PS->QLPS->GetIndexPairStateAction(PairStateAction);
                   //maintenant mettre ajour Qvaleur de stat
                   QL->UpdateQtable(Reward, PairStateActionPS, QtargetPS);//++++++++++++++++++ Mise à jour de la table ++

                   //=====================================
                   //mettre à jour prochain action et prochain etat

                   CorrespondingActionPS = CorrespondingActionTargetPS;
                   stat = sdash;
                   //=======================================================
                   // Mettre à jour la solution ===========================
                   solutionTemp = solTemp ;
                   //=================== mettre à jour la liste des TRX non traité
                   UpdateLTrxNTreateds(LTrxNTreateds, trxdash,-1); //Retirer trx de LTrxNTreated

              }//choice

                //solTemp = NULL;
                //delete solTemp;
  //  }// j===0



>>>>>>> 0514ea9fae0f841576757defb02235a9189b0fad
        //#######################################################3

  //##########################################
//-----------------------------------------------------------------
    while(LTrxNTreateds.size() != 0 )
<<<<<<< HEAD
    {
          ProbGreedy = (double)rand() / (double)RAND_MAX  ;
         //  choice = rand() % 2 + 1;
        if (LTrxNTreateds.size()== 1)// il rest un seul trx , choix aléatoire d'une action ou max Q
        {
             if(choice == 2) // PI etait entrain de jouer, on inverse le role: c est le tour de PS
            {
                 choice = 1;
                 //***************************************************************************************************
                if (ProbGreedy < EpsilonGreedy)//Choix aléatoire d'une action//choix aeatoire d une strategi
               {
                   CorrespondingActionPS = QL->GetPossibleAction();
                    //cout << "CorrespondingActionPS.ActTRX " << CorrespondingActionPS.ActTRX << endl;
                    //cout << "CorrespondingActionPS.ActFreq " << CorrespondingActionPS.ActFreq << endl;
               }
=======
    {
          ProbGreedy = (double)rand() / (double)RAND_MAX  ;
         //  choice = rand() % 2 + 1;
        if (LTrxNTreateds.size()== 1)// il rest un seul trx , choix aléatoire d'une action ou max Q
        {
             if(choice == 2) // PI etait entrain de jouer, on inverse le role: c est le tour de PS
            {
                 choice = 1;
                 //***************************************************************************************************
                if (ProbGreedy < EpsilonGreedy)//Choix aléatoire d'une action//choix aeatoire d une strategi
               {
                   CorrespondingActionPS = QL->GetPossibleAction();
                    //cout << "CorrespondingActionPS.ActTRX " << CorrespondingActionPS.ActTRX << endl;
                    //cout << "CorrespondingActionPS.ActFreq " << CorrespondingActionPS.ActFreq << endl;
               }
>>>>>>> 0514ea9fae0f841576757defb02235a9189b0fad
               Individual * solTemp;
                   solTemp = new Individual();
                    // solTemp->plan = new vector<int>(afpProblem->trxs.size());
                    //   solTemp->planCC = new vector<pair<double,double> >(afpProblem->trxs.size());
                   solTemp ->PIObj = 0.0 ;
                   solTemp->PSObj = 0.0 ;

<<<<<<< HEAD
                   solTemp = solutionTemp;

                   PS->PSChooseTrx(afpProblem, StrategyTrxPS, LTrxNTreateds,trxdash);

                   //-----------------prochain etat est sdash ----------------------------
                   sdash.UnTreatedTRXNumb = trxdash.trxID; //est le prochain etat//+++++++++++++++++++++
                   //-------------------------------------------------------------------------------------
                   //-------------------------------------------------------------------------------------

                   PS->PSChooseFrequency(instance, CorrespondingActionPS.ActFreq, trxdash, f, solTemp, afpProblem);


                   AddSolTrxFrequency(afpProblem,solTemp,trxdash ,f);
                   QL->ObserveReward(2,solutionTemp, solTemp,Reward, instance);//+++++++++Reward++++++++++
                    cout << "RRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR"  <<endl;
                   cout << " Reward PS is"  <<Reward << endl;
                   cout << "RRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR"  <<endl;
                   QtargetPS = 0; //Récupérer la valeur  de Qvalue max et son action
                    //récupérer les coordonnées ds Qtable
                   PairStateActionPS.first.UnTreatedTRXNumb = stat.UnTreatedTRXNumb;
                 //  PairStateActionPS.second.ActTRX = CorrespondingActionPS.ActTRX;
                   PairStateActionPS.second.ActFreq = CorrespondingActionPS.ActFreq;
                   //int indexQtarget = PS->QLPS->GetIndexPairStateAction(PairStateAction);
                   //maintenant mettre ajour Qvaleur de stat
                   QL->UpdateQtable(Reward, PairStateActionPS, QtargetPS);//++++++++++++++++++ Mise à jour de la table ++
                   solutionTemp = solTemp ;
                   //=================== mettre à jour la liste des TRX non traité
                   UpdateLTrxNTreateds(LTrxNTreateds, trxdash,-1); //Retirer trx de LTrxNTreated
            //**************************************************************************************************************
            }
            else//choice = 1
            {
                 choice = 2;
                 //***************************************************************************************************
                 if (ProbGreedy < EpsilonGreedy)//Choix aléatoire d'une action//choix aeatoire d une strategi
               {
                   CorrespondingActionPI = QL->GetPossibleAction();
               }

=======
                   solTemp = solutionTemp;

                   PS->PSChooseTrx(afpProblem, StrategyTrxPS, LTrxNTreateds,trxdash);

                   //-----------------prochain etat est sdash ----------------------------
                   sdash.UnTreatedTRXNumb = trxdash.trxID; //est le prochain etat//+++++++++++++++++++++
                   //-------------------------------------------------------------------------------------
                   //-------------------------------------------------------------------------------------

                   PS->PSChooseFrequency(instance, CorrespondingActionPS.ActFreq, trxdash, f, solTemp, afpProblem);


                   AddSolTrxFrequency(afpProblem,solTemp,trxdash ,f);
                   QL->ObserveReward(2,solutionTemp, solTemp,Reward, instance);//+++++++++Reward++++++++++
                    cout << "RRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR"  <<endl;
                   cout << " Reward PS is"  <<Reward << endl;
                   cout << "RRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR"  <<endl;
                   QtargetPS = 0; //Récupérer la valeur  de Qvalue max et son action
                    //récupérer les coordonnées ds Qtable
                   PairStateActionPS.first.UnTreatedTRXNumb = stat.UnTreatedTRXNumb;
                 //  PairStateActionPS.second.ActTRX = CorrespondingActionPS.ActTRX;
                   PairStateActionPS.second.ActFreq = CorrespondingActionPS.ActFreq;
                   //int indexQtarget = PS->QLPS->GetIndexPairStateAction(PairStateAction);
                   //maintenant mettre ajour Qvaleur de stat
                   QL->UpdateQtable(Reward, PairStateActionPS, QtargetPS);//++++++++++++++++++ Mise à jour de la table ++
                   solutionTemp = solTemp ;
                   //=================== mettre à jour la liste des TRX non traité
                   UpdateLTrxNTreateds(LTrxNTreateds, trxdash,-1); //Retirer trx de LTrxNTreated
            //**************************************************************************************************************
            }
            else//choice = 1
            {
                 choice = 2;
                 //***************************************************************************************************
                 if (ProbGreedy < EpsilonGreedy)//Choix aléatoire d'une action//choix aeatoire d une strategi
               {
                   CorrespondingActionPI = QL->GetPossibleAction();
               }

>>>>>>> 0514ea9fae0f841576757defb02235a9189b0fad
                 Individual * solTemp;
                   solTemp = new Individual();
                    // solTemp->plan = new vector<int>(afpProblem->trxs.size());
                    //   solTemp->planCC = new vector<pair<double,double> >(afpProblem->trxs.size());
                   solTemp ->PIObj = 0.0 ;
                   solTemp->PSObj = 0.0 ;

<<<<<<< HEAD
                   solTemp = solutionTemp;
                   PI->PIChooseTrx(StrategyTrxPI,LTrxNTreateds,trxdash,afpProblem,solTemp);
                   //-----------------prochain etat est sdash ----------------------------
                   sdash.UnTreatedTRXNumb = trxdash.trxID; //est le prochain etat//+++++++++++++++++++++
                   //-------------------------------------------------------------------------------------
                   //-------------------------------------------------------------------------------------
                   PI->PIChooseFrequency(instance,CorrespondingActionPI.ActFreq,trxdash,solTemp, afpProblem,f);
                   AddSolTrxFrequency(afpProblem,solTemp,trxdash ,f);
                   QL->ObserveReward(1,solutionTemp, solTemp,Reward, instance);//+++++++++Reward++++++++++
                   QtargetPI = 0; //Récupérer la valeur  de Qvalue max et son action
                    //récupérer les coordonnées ds Qtable
                   PairStateActionPI.first.UnTreatedTRXNumb = stat.UnTreatedTRXNumb;
                   //PairStateActionPI.second.ActTRX = CorrespondingActionPI.ActTRX;
                   PairStateActionPI.second.ActFreq = CorrespondingActionPI.ActFreq;
                   //int indexQtarget = PI->QLPI->GetIndexPairStateAction(PairStateAction);
                   //maintenant mettre ajour Qvaleur de stat
                   QL->UpdateQtable(Reward, PairStateActionPI, QtargetPI);//++++++++++++++++++ Mise à jour de la table ++

                   //=====================================
                   //mettre à jour prochain action et prochain etat

                   CorrespondingActionPI = CorrespondingActionTargetPI;
                   stat = sdash;
                   //=======================================================
                   // Mettre à jour la solution ===========================
                   solutionTemp = solTemp ;
                   //=================== mettre à jour la liste des TRX non traité
                   UpdateLTrxNTreateds(LTrxNTreateds, trxdash,-1); //Retirer trx de LTrxNTreated            }//choice

        }
    }
        //================================================================================================
       else// ce nest pas la dernier eta
       {
              // PI-> Play(instance,StrategyTrxPI,  StrategyFreqPI ,trx, LTrxNTreateds,solutionTemp, afpProblem);
            if(choice == 2) // PI etait entrain de jouer, on inverse le role: c est le tour de PS
            {
               //  choice = 1;
                 if (ProbGreedy < EpsilonGreedy)//Choix aléatoire d'une action//choix aeatoire d une strategi
               {
                   CorrespondingActionPS = QL->GetPossibleAction();
                   // cout << "CorrespondingActionPS.ActTRX " << CorrespondingActionPS.ActTRX << endl;
                   // cout << "CorrespondingActionPS.ActFreq " << CorrespondingActionPS.ActFreq << endl;
               }
=======
                   solTemp = solutionTemp;
                   PI->PIChooseTrx(StrategyTrxPI,LTrxNTreateds,trxdash,afpProblem,solTemp);
                   //-----------------prochain etat est sdash ----------------------------
                   sdash.UnTreatedTRXNumb = trxdash.trxID; //est le prochain etat//+++++++++++++++++++++
                   //-------------------------------------------------------------------------------------
                   //-------------------------------------------------------------------------------------
                   PI->PIChooseFrequency(instance,CorrespondingActionPI.ActFreq,trxdash,solTemp, afpProblem,f);
                   AddSolTrxFrequency(afpProblem,solTemp,trxdash ,f);
                   QL->ObserveReward(1,solutionTemp, solTemp,Reward, instance);//+++++++++Reward++++++++++
                   QtargetPI = 0; //Récupérer la valeur  de Qvalue max et son action
                    //récupérer les coordonnées ds Qtable
                   PairStateActionPI.first.UnTreatedTRXNumb = stat.UnTreatedTRXNumb;
                   //PairStateActionPI.second.ActTRX = CorrespondingActionPI.ActTRX;
                   PairStateActionPI.second.ActFreq = CorrespondingActionPI.ActFreq;
                   //int indexQtarget = PI->QLPI->GetIndexPairStateAction(PairStateAction);
                   //maintenant mettre ajour Qvaleur de stat
                   QL->UpdateQtable(Reward, PairStateActionPI, QtargetPI);//++++++++++++++++++ Mise à jour de la table ++

                   //=====================================
                   //mettre à jour prochain action et prochain etat

                   CorrespondingActionPI = CorrespondingActionTargetPI;
                   stat = sdash;
                   //=======================================================
                   // Mettre à jour la solution ===========================
                   solutionTemp = solTemp ;
                   //=================== mettre à jour la liste des TRX non traité
                   UpdateLTrxNTreateds(LTrxNTreateds, trxdash,-1); //Retirer trx de LTrxNTreated            }//choice

        }
    }
        //================================================================================================
       else// ce nest pas la dernier eta
       {
              // PI-> Play(instance,StrategyTrxPI,  StrategyFreqPI ,trx, LTrxNTreateds,solutionTemp, afpProblem);
            if(choice == 2) // PI etait entrain de jouer, on inverse le role: c est le tour de PS
            {
               //  choice = 1;
                 if (ProbGreedy < EpsilonGreedy)//Choix aléatoire d'une action//choix aeatoire d une strategi
               {
                   CorrespondingActionPS = QL->GetPossibleAction();
                   // cout << "CorrespondingActionPS.ActTRX " << CorrespondingActionPS.ActTRX << endl;
                   // cout << "CorrespondingActionPS.ActFreq " << CorrespondingActionPS.ActFreq << endl;
               }
>>>>>>> 0514ea9fae0f841576757defb02235a9189b0fad
               Individual * solTemp;
                   solTemp = new Individual();
                    // solTemp->plan = new vector<int>(afpProblem->trxs.size());
                    //   solTemp->planCC = new vector<pair<double,double> >(afpProblem->trxs.size());
                   solTemp ->PIObj = 0.0 ;
                   solTemp->PSObj = 0.0 ;

<<<<<<< HEAD
                   solTemp = solutionTemp;

                   PS->PSChooseTrx(afpProblem, StrategyTrxPS, LTrxNTreateds,trxdash);

                   //-----------------prochain etat est sdash ----------------------------
                   sdash.UnTreatedTRXNumb = trxdash.trxID; //est le prochain etat//+++++++++++++++++++++
                   //-------------------------------------------------------------------------------------
                   //-------------------------------------------------------------------------------------

                   PS->PSChooseFrequency(instance, CorrespondingActionPS.ActFreq, trxdash, f, solTemp, afpProblem);

                   AddSolTrxFrequency(afpProblem,solTemp,trxdash ,f);
                   QL->ObserveReward(2,solutionTemp, solTemp,Reward, instance);//+++++++++Reward++++++++++
                   QtargetPS = QL->GetQtarget(sdash , CorrespondingActionTargetPS); //Récupérer la valeur  de Qvalue max et son action
                     cout << "RRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR"  <<endl;
                   cout << " Reward PS is"  <<Reward << endl;
                   cout << "RRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR"  <<endl;
                    //récupérer les coordonnées ds Qtable
                   PairStateActionPS.first.UnTreatedTRXNumb = stat.UnTreatedTRXNumb;
                  // PairStateActionPS.second.ActTRX = CorrespondingActionPS.ActTRX;
                   PairStateActionPS.second.ActFreq = CorrespondingActionPS.ActFreq;
                  // int indexQtarget = PS->QLPS->GetIndexPairStateAction(PairStateAction);
                   //maintenant mettre ajour Qvaleur de stat
                   QL->UpdateQtable(Reward, PairStateActionPS, QtargetPS);//++++++++++++++++++ Mise à jour de la table ++


                   solutionTemp = solTemp ;
                   //=================== mettre à jour la liste des TRX non traité
                   UpdateLTrxNTreateds(LTrxNTreateds, trxdash,-1); //Retirer trx de LTrxNTreated
            //***************************************************************
            // cest l'autre joueu qui va joueurr
=======
                   solTemp = solutionTemp;

                   PS->PSChooseTrx(afpProblem, StrategyTrxPS, LTrxNTreateds,trxdash);

                   //-----------------prochain etat est sdash ----------------------------
                   sdash.UnTreatedTRXNumb = trxdash.trxID; //est le prochain etat//+++++++++++++++++++++
                   //-------------------------------------------------------------------------------------
                   //-------------------------------------------------------------------------------------

                   PS->PSChooseFrequency(instance, CorrespondingActionPS.ActFreq, trxdash, f, solTemp, afpProblem);

                   AddSolTrxFrequency(afpProblem,solTemp,trxdash ,f);
                   QL->ObserveReward(2,solutionTemp, solTemp,Reward, instance);//+++++++++Reward++++++++++
                   QtargetPS = QL->GetQtarget(sdash , CorrespondingActionTargetPS); //Récupérer la valeur  de Qvalue max et son action
                     cout << "RRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR"  <<endl;
                   cout << " Reward PS is"  <<Reward << endl;
                   cout << "RRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR"  <<endl;
                    //récupérer les coordonnées ds Qtable
                   PairStateActionPS.first.UnTreatedTRXNumb = stat.UnTreatedTRXNumb;
                  // PairStateActionPS.second.ActTRX = CorrespondingActionPS.ActTRX;
                   PairStateActionPS.second.ActFreq = CorrespondingActionPS.ActFreq;
                  // int indexQtarget = PS->QLPS->GetIndexPairStateAction(PairStateAction);
                   //maintenant mettre ajour Qvaleur de stat
                   QL->UpdateQtable(Reward, PairStateActionPS, QtargetPS);//++++++++++++++++++ Mise à jour de la table ++


                   solutionTemp = solTemp ;
                   //=================== mettre à jour la liste des TRX non traité
                   UpdateLTrxNTreateds(LTrxNTreateds, trxdash,-1); //Retirer trx de LTrxNTreated
            //***************************************************************
            // cest l'autre joueu qui va joueurr
>>>>>>> 0514ea9fae0f841576757defb02235a9189b0fad

            }
            else//choice = 1
            {
<<<<<<< HEAD
               // choice = 2;
                //***************************************************************************************************
                 if (ProbGreedy < EpsilonGreedy)//Choix aléatoire d'une action//choix aeatoire d une strategi
               {
                   CorrespondingActionPI = QL->GetPossibleAction();
               }

=======
               // choice = 2;
                //***************************************************************************************************
                 if (ProbGreedy < EpsilonGreedy)//Choix aléatoire d'une action//choix aeatoire d une strategi
               {
                   CorrespondingActionPI = QL->GetPossibleAction();
               }

>>>>>>> 0514ea9fae0f841576757defb02235a9189b0fad
                 Individual * solTemp;
                   solTemp = new Individual();
                    // solTemp->plan = new vector<int>(afpProblem->trxs.size());
                    //   solTemp->planCC = new vector<pair<double,double> >(afpProblem->trxs.size());
                   solTemp ->PIObj = 0.0 ;
                   solTemp->PSObj = 0.0 ;

<<<<<<< HEAD
                   solTemp = solutionTemp;
                   PI->PIChooseTrx(StrategyTrxPI,LTrxNTreateds,trxdash,afpProblem,solTemp);
                   //-----------------prochain etat est sdash ----------------------------
                   sdash.UnTreatedTRXNumb = trxdash.trxID; //est le prochain etat//+++++++++++++++++++++
                   //-------------------------------------------------------------------------------------
                   //-------------------------------------------------------------------------------------
                   PI->PIChooseFrequency(instance,CorrespondingActionPI.ActFreq,trxdash,solTemp, afpProblem,f);
                   AddSolTrxFrequency(afpProblem,solTemp,trxdash ,f);
                   QL->ObserveReward(1,solutionTemp, solTemp,Reward, instance);//+++++++++Reward++++++++++
                  QtargetPI = QL->GetQtarget(sdash , CorrespondingActionTargetPI); //Récupérer la valeur  de Qvalue max et son action
                    //récupérer les coordonnées ds Qtable
                   PairStateActionPI.first.UnTreatedTRXNumb = stat.UnTreatedTRXNumb;
                   //PairStateActionPI.second.ActTRX = CorrespondingActionPI.ActTRX;
                   PairStateActionPI.second.ActFreq = CorrespondingActionPI.ActFreq;
                  // int indexQtarget = PI->QLPI->GetIndexPairStateAction(PairStateAction);
                   //maintenant mettre ajour Qvaleur de stat
                   QL->UpdateQtable(Reward, PairStateActionPI, QtargetPI);//++++++++++++++++++ Mise à jour de la table ++

                   //=====================================
                   //mettre à jour prochain action et prochain etat

                   CorrespondingActionPI = CorrespondingActionTargetPI;
                   stat = sdash;
                   //=======================================================
                   // Mettre à jour la solution ===========================
                   solutionTemp = solTemp ;
                   //=================== mettre à jour la liste des TRX non traité
                   UpdateLTrxNTreateds(LTrxNTreateds, trxdash,-1); //Retirer trx de LTrxNTreated            }//choice

            }
=======
                   solTemp = solutionTemp;
                   PI->PIChooseTrx(StrategyTrxPI,LTrxNTreateds,trxdash,afpProblem,solTemp);
                   //-----------------prochain etat est sdash ----------------------------
                   sdash.UnTreatedTRXNumb = trxdash.trxID; //est le prochain etat//+++++++++++++++++++++
                   //-------------------------------------------------------------------------------------
                   //-------------------------------------------------------------------------------------
                   PI->PIChooseFrequency(instance,CorrespondingActionPI.ActFreq,trxdash,solTemp, afpProblem,f);
                   AddSolTrxFrequency(afpProblem,solTemp,trxdash ,f);
                   QL->ObserveReward(1,solutionTemp, solTemp,Reward, instance);//+++++++++Reward++++++++++
                  QtargetPI = QL->GetQtarget(sdash , CorrespondingActionTargetPI); //Récupérer la valeur  de Qvalue max et son action
                    //récupérer les coordonnées ds Qtable
                   PairStateActionPI.first.UnTreatedTRXNumb = stat.UnTreatedTRXNumb;
                   //PairStateActionPI.second.ActTRX = CorrespondingActionPI.ActTRX;
                   PairStateActionPI.second.ActFreq = CorrespondingActionPI.ActFreq;
                  // int indexQtarget = PI->QLPI->GetIndexPairStateAction(PairStateAction);
                   //maintenant mettre ajour Qvaleur de stat
                   QL->UpdateQtable(Reward, PairStateActionPI, QtargetPI);//++++++++++++++++++ Mise à jour de la table ++

                   //=====================================
                   //mettre à jour prochain action et prochain etat

                   CorrespondingActionPI = CorrespondingActionTargetPI;
                   stat = sdash;
                   //=======================================================
                   // Mettre à jour la solution ===========================
                   solutionTemp = solTemp ;
                   //=================== mettre à jour la liste des TRX non traité
                   UpdateLTrxNTreateds(LTrxNTreateds, trxdash,-1); //Retirer trx de LTrxNTreated            }//choice

            }
>>>>>>> 0514ea9fae0f841576757defb02235a9189b0fad

              //PI-> Play(instance,StrategyTrxPI, StrategyFreqPI,trx, LTrxNTreateds,solutionTemp, afpProblem);
        }//ce n'est pas le dernier etat
        }//while



        //calculer le cout de la solution trpuvée
        solutionTemp->PIObj = afpProblem->ComputeSolutionInterference(solutionTemp);//;afpProblem->interferenceBasedFitness(solutionTemp);//afpProblem->ComputeSolutionInterference(solution);//LF comment : ma fonction objectif (cacul de cout intererence)
        solutionTemp->PSObj = afpProblem->ComputeSolutionSeparationCost(solutionTemp);//LF comment : ma fonction objectif (cacule le cout de separation)
        //Enregistrer la solution actuelle
        //solutionSs[j] = new Individual();
        solutionSs.push_back(solutionTemp);

       // solutionSs[j] = solutionTemp;
      //  cout << "avant ---------" <<endl;
      //  cout <<  "solutionTemp->PIObj  " << solutionTemp->PIObj << endl ;
    //cout <<  "solutionTemp->PSObj  " << solutionTemp->PSObj << endl ;
<<<<<<< HEAD
   // delete solutionTemp;
    clock_t stop = clock();//fin de timing
    elapsed_secs = double(stop - start) / CLOCKS_PER_SEC;
   if (  (j == 10) or (j == 20) or (j == 30) or (j == 40) or (j == 50) or (j == 100) or
         (j == periode) or (j==2 * periode) or (j==3 * periode)or (j == 4 * periode) or
         (j== 5 * periode) or (j== 6 * periode) or (j == 7 * periode) or
         (j==8  * periode) or (j== 9 * periode) or (j == 10 * periode))//(j == 1000) or (j == 2000) or (j == 3000) or (j == 4000) or (j == 5000))
   {
       vector <double> NASHEJ2;
       //NASH2.reserve(3);
     switch(ApproachGameEvaluation)
    {
        case 11:
        {
            vector<Individual*>().swap(BestsolutionSs);

            GameEvaluationNashOneSol( instance, j,solutionSs,start, elapsed_secs,indexNASHEbest,NASHEJ2);
            HVValue = HV;
=======
   // delete solutionTemp;
    clock_t stop = clock();//fin de timing
    elapsed_secs = double(stop - start) / CLOCKS_PER_SEC;
   if (  (j == 10) or (j == 20) or (j == 30) or (j == 40) or (j == 50) or (j == 100) or
         (j == periode) or (j==2 * periode) or (j==3 * periode)or (j == 4 * periode) or
         (j== 5 * periode) or (j== 6 * periode) or (j == 7 * periode) or
         (j==8  * periode) or (j== 9 * periode) or (j == 10 * periode))//(j == 1000) or (j == 2000) or (j == 3000) or (j == 4000) or (j == 5000))
   {
       vector <double> NASHEJ2;
       //NASH2.reserve(3);
     switch(ApproachGameEvaluation)
    {
        case 11:
        {
            vector<Individual*>().swap(BestsolutionSs);

            GameEvaluationNashOneSol( instance, j,solutionSs,start, elapsed_secs,indexNASHEbest,NASHEJ2);
            HVValue = HV;
>>>>>>> 0514ea9fae0f841576757defb02235a9189b0fad
            break;
        }
        case 1://evaluation nash ensemble
        {
<<<<<<< HEAD
            GameEvaluation( instance, j,solutionSs,start, elapsed_secs,indexNASHEbest,NASHEJ2);
=======
            GameEvaluation( instance, j,solutionSs,start, elapsed_secs,indexNASHEbest,NASHEJ2);
>>>>>>> 0514ea9fae0f841576757defb02235a9189b0fad
            HVValue = HV;
            break;
        }
         case 2:
        {
<<<<<<< HEAD
            GameEvaluationPareto( instance, j,solutionSs,start, elapsed_secs,indexNASHEbest,NASHEJ2);
=======
            GameEvaluationPareto( instance, j,solutionSs,start, elapsed_secs,indexNASHEbest,NASHEJ2);
>>>>>>> 0514ea9fae0f841576757defb02235a9189b0fad
            HVValue = HV;
            break;
        }
          case 22:
        {
<<<<<<< HEAD
            GameEvaluationParetoEcart( instance, j,solutionSs,start, elapsed_secs,indexNASHEbest,NASHEJ2);
=======
            GameEvaluationParetoEcart( instance, j,solutionSs,start, elapsed_secs,indexNASHEbest,NASHEJ2);
>>>>>>> 0514ea9fae0f841576757defb02235a9189b0fad
            HVValue = HV;
            break;
        }
           case 21:
        {
<<<<<<< HEAD
            GameEvaluationParetoHV( instance, j,solutionSs,start, elapsed_secs,indexNASHEbest,NASHEJ2);
=======
            GameEvaluationParetoHV( instance, j,solutionSs,start, elapsed_secs,indexNASHEbest,NASHEJ2);
>>>>>>> 0514ea9fae0f841576757defb02235a9189b0fad
            HVValue = HV;
            break;
        }
          case 23:
        {
<<<<<<< HEAD

            GameEvaluationParetoUneSolNash( instance, j,solutionSs,start, elapsed_secs,indexNASHEbest,NASHEJ2, HVValue);
=======

            GameEvaluationParetoUneSolNash( instance, j,solutionSs,start, elapsed_secs,indexNASHEbest,NASHEJ2, HVValue);
>>>>>>> 0514ea9fae0f841576757defb02235a9189b0fad
            HVValue = HV;
            break;
        }
          case 24:
        {
<<<<<<< HEAD
            GameEvaluationDistEuclUneSol( instance, j,solutionSs,start, elapsed_secs,indexNASHEbest,NASHEJ2);
=======
            GameEvaluationDistEuclUneSol( instance, j,solutionSs,start, elapsed_secs,indexNASHEbest,NASHEJ2);
>>>>>>> 0514ea9fae0f841576757defb02235a9189b0fad
            HVValue = HV;
            break;
        }

         default:
            {
                cout << "Erreur de choix de stratégie d'évaluation " << endl;
                break;
            }
<<<<<<< HEAD
        }

        stringstream sj;
        sj << j;

    //string pathnash =  "Resultats/" + "_epsilon" + ssss.str()+ "_gen" + sj.str() +  instance +  "_StrategyTrxPIPS_" + stratTrxPI.str()+ "_" + stratTrxPS.str()+ ".txt";
   //"_game" + ss.str() + "_" + appEv +  "_"
   //string path="Resultats/";
  string pathnash = "Resultats/" + sj.str() + "_" + appEv + "_" + instance + temp.str()+  "_StrategyTrxPIPS_" + stratTrxPI.str()+ "_" + stratTrxPS.str() + ".txt";
   //string path="Resultats/";
   // HV == 0; indexNASHEbest = 0; NASHEJ2.push_back(0);
    ShowNashvaluersResult(indexNASHEbest,NASHEJ2, pathnash, HV,solutionSs);
   } //end j == 3





=======
        }

        stringstream sj;
        sj << j;

    //string pathnash =  "Resultats/" + "_epsilon" + ssss.str()+ "_gen" + sj.str() +  instance +  "_StrategyTrxPIPS_" + stratTrxPI.str()+ "_" + stratTrxPS.str()+ ".txt";
   //"_game" + ss.str() + "_" + appEv +  "_"
   //string path="Resultats/";
  string pathnash = "Resultats/" + sj.str() + "_" + appEv + "_" + instance + temp.str()+  "_StrategyTrxPIPS_" + stratTrxPI.str()+ "_" + stratTrxPS.str() + ".txt";
   //string path="Resultats/";
   // HV == 0; indexNASHEbest = 0; NASHEJ2.push_back(0);
    ShowNashvaluersResult(indexNASHEbest,NASHEJ2, pathnash, HV,solutionSs);
   } //end j == 3





>>>>>>> 0514ea9fae0f841576757defb02235a9189b0fad

        vector<TRXs>().swap(LTrxNTreateds);
        solutionTemp = NULL;
     delete solutionTemp;

    }//max_gen

   // delete
    //cout << "solutionSs.size()"<< solutionSs.size()<<endl;
    //.................................................................................
 // ************************************************EVALUATION ******************************
    //ResultFile.close();

    switch(ApproachGameEvaluation)
    {
        case 11:
        {
<<<<<<< HEAD
           vector<Individual*>().swap(BestsolutionSs);
            GameEvaluationNashOneSol( instance, max_gen,solutionSs,start, elapsed_secs,indexNASHEbest,NASHEJ);
            HVValue = HV;
=======
           vector<Individual*>().swap(BestsolutionSs);
            GameEvaluationNashOneSol( instance, max_gen,solutionSs,start, elapsed_secs,indexNASHEbest,NASHEJ);
            HVValue = HV;
>>>>>>> 0514ea9fae0f841576757defb02235a9189b0fad
            break;
        }
        case 1://evaluation nash ensemble
        {
<<<<<<< HEAD
            GameEvaluation( instance, max_gen,solutionSs,start, elapsed_secs,indexNASHEbest,NASHEJ);
=======
            GameEvaluation( instance, max_gen,solutionSs,start, elapsed_secs,indexNASHEbest,NASHEJ);
>>>>>>> 0514ea9fae0f841576757defb02235a9189b0fad
            HVValue = HV;
            break;
        }
         case 2:
        {
<<<<<<< HEAD
            GameEvaluationPareto( instance, max_gen,solutionSs,start, elapsed_secs,indexNASHEbest,NASHEJ);
=======
            GameEvaluationPareto( instance, max_gen,solutionSs,start, elapsed_secs,indexNASHEbest,NASHEJ);
>>>>>>> 0514ea9fae0f841576757defb02235a9189b0fad
            HVValue = HV;
            break;
        }
          case 22:
        {
<<<<<<< HEAD
            GameEvaluationParetoEcart( instance, max_gen,solutionSs,start, elapsed_secs,indexNASHEbest,NASHEJ);
=======
            GameEvaluationParetoEcart( instance, max_gen,solutionSs,start, elapsed_secs,indexNASHEbest,NASHEJ);
>>>>>>> 0514ea9fae0f841576757defb02235a9189b0fad
            HVValue = HV;
            break;
        }
           case 21:
        {
<<<<<<< HEAD
            GameEvaluationParetoHV( instance, max_gen,solutionSs,start, elapsed_secs,indexNASHEbest,NASHEJ);
=======
            GameEvaluationParetoHV( instance, max_gen,solutionSs,start, elapsed_secs,indexNASHEbest,NASHEJ);
>>>>>>> 0514ea9fae0f841576757defb02235a9189b0fad
            HVValue = HV;
            break;
        }
          case 23:
        {
<<<<<<< HEAD

            GameEvaluationParetoUneSolNash( instance, max_gen,solutionSs,start, elapsed_secs,indexNASHEbest,NASHEJ, HVValue);
=======

            GameEvaluationParetoUneSolNash( instance, max_gen,solutionSs,start, elapsed_secs,indexNASHEbest,NASHEJ, HVValue);
>>>>>>> 0514ea9fae0f841576757defb02235a9189b0fad
            HVValue = HV;
            break;
        }
          case 24:
        {
<<<<<<< HEAD
            GameEvaluationDistEuclUneSol( instance, max_gen,solutionSs,start, elapsed_secs,indexNASHEbest,NASHEJ);
=======
            GameEvaluationDistEuclUneSol( instance, max_gen,solutionSs,start, elapsed_secs,indexNASHEbest,NASHEJ);
>>>>>>> 0514ea9fae0f841576757defb02235a9189b0fad
            HVValue = HV;
            break;
        }

         default:
            {
                cout << "Erreur de choix de stratégie d'évaluation " << endl;
                break;
            }
<<<<<<< HEAD
 }
 clock_t stop = clock();//fin de timing
    elapsed_secs = double(stop - start) / CLOCKS_PER_SEC;
    ShowResult(ApproachGameEvaluation,instance,NumGame,elapsed_secs,max_gen,epsilon,solutionSs,indexNASHEbest,NASHEJ,BestsolutionSs,solution,path, HVValue);
      //  QL->ShowQtable(ApproachGameEvaluation,instance,elapsed_secs,max_gen,epsilon);
=======
 }
 clock_t stop = clock();//fin de timing
    elapsed_secs = double(stop - start) / CLOCKS_PER_SEC;
    ShowResult(ApproachGameEvaluation,instance,NumGame,elapsed_secs,max_gen,epsilon,solutionSs,indexNASHEbest,NASHEJ,BestsolutionSs,solution,path, HVValue);
      //  QL->ShowQtable(ApproachGameEvaluation,instance,elapsed_secs,max_gen,epsilon);
>>>>>>> 0514ea9fae0f841576757defb02235a9189b0fad
       // ShowSolution(StrategyTrxPI,StrategyTrxPS,  solution,ApproachGameEvaluation,instance,elapsed_secs,max_gen,epsilon);
    //+++++++++++++++++++++++++++ Afficher la solution ++++++++++++++++++++++++++++++++++++
    //cout << "afpProblem->ComputeSolutionInterference(BestsolutionSs[0])-----"<< afpProblem->ComputeSolutionInterference(BestsolutionSs.at(0)) << endl;
    //cout << "afpProblem->interferenceBasedFitness(BestsolutionSs[0])-----" << afpProblem->interferenceBasedFitness(BestsolutionSs.at(0)) << endl;

}
//=============================================================================================
//============================ Ajouté le 15-5-2019 ===================================
//--------------------------
void Game::GameEvaluationNashOneSol(string instance,const int max_gen,vector<Individual*> solutionSs,double start, double & elapsed_secs,int & indexNASHEbest, vector <double> & NASHEJ)
{
    int k,j;
    //-------------------------------------------------------------------------
    int indexBestSolPI, indexBestSolPS ;//= 0; ;// 0;
    double BestObjectivePI, BestObjectivePS, CurrentObjectivePI, CurrentObjectivePS;
    vector<double> VectBestSolPI;
    //VectBestSolPI.reserve(max_gen);
    vector<double> VectBestSolPS;
    //VectBestSolPS.reserve(max_gen);
    //------------------------------------------
    //NASHEJ.reserve(max_gen);
    double NASHEbest;
    //----------------------------------------------------------------------
    //---------------- Evaluer la meilleur solution pour le joueur PI
    //----------------------------------------------------------------------
     cout <<"Afete ---"<<endl;
      for(k = 0 ; k < solutionSs.size(); k++)
        {
          //  cout<< " solutionSs[k]->PIObj " <<solutionSs[k]->PIObj <<endl;
            VectBestSolPI.push_back(solutionSs.at(k)->PIObj);
          //  cout << "VectBestSolPI(k) " << VectBestSolPI[k] <<endl;
        }
        //cout <<"$$$$$$$$$$$$$$$$$$$$$$$$$"<<endl;

        BestObjectivePI = 0.0;
        //cout << " VectBestSolPI.size() " << VectBestSolPI.size() << endl;
        VecMinValue(VectBestSolPI,indexBestSolPI);
       // cout << "indexBestSolPI : " << indexBestSolPI << endl;
        BestObjectivePI = solutionSs[indexBestSolPI]->PIObj;
       //cout << " solutionSs[indexBestSolPI]->PIObj " << solutionSs[indexBestSolPI]->PIObj<<endl;
       //cout << " BestObjectivePI===================== "<<BestObjectivePI<<endl;
       //----------------------------------------------------------------------
        //---------------- Evaluer la meilleur solution pour le joueur PI
        //----------------------------------------------------------------------
        for(k = 0 ; k < solutionSs.size(); k++)
        {
            //cout<< " solutionSs[k]->PIObj " <<solutionSs[k]->PIObj <<endl;
            VectBestSolPS.push_back(solutionSs[k]->PSObj);
            //cout << "VectBestSolPI(k) " << VectBestSolPI[k] <<endl;
        }
        BestObjectivePS = 0.0;
        VecMinValue(VectBestSolPS,indexBestSolPS);
       // cout << "indexBestSolPS : " << indexBestSolPS << endl;
        BestObjectivePS = solutionSs[indexBestSolPS]->PSObj;
     //     cout << " BestObjectivePS===================== "<<BestObjectivePS<<endl;;
        //vider la mémoire
        vector<double>().swap(VectBestSolPI);
        vector<double>().swap(VectBestSolPS);
       // cout << "indexBestSolPS : " << indexBestSolPS << endl;
      // cout << "  BestObjectivePS================  " << BestObjectivePS << endl;
       //-------------------------------------------------------------------------
       //------------------------Remplissage du vecteur NASH -----
       //---------------------------------------------------------------------------

       //......................Utiliser le point de référence .....................
       //...........................................................................................
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
        //==================================Best solultions ================
        //BestObjectivePI = Min.first;
        //BestObjectivePS = Min.second;
       //...........................................................................
       //...........................................................................





       //------------------------------------------------
    for(j=0 ; j < max_gen ; j++)
    {
        CurrentObjectivePI = solutionSs[j]->PIObj;
        CurrentObjectivePS = solutionSs[j]->PSObj;
        //...........................................................EQuilibre de Nash ..................................
        if(BestObjectivePS == 0)
        {
           //[j] = (CurrentObjectivePI - BestObjectivePI)/BestObjectivePI;
           if (BestObjectivePI !=0 ) NASHEJ.push_back((CurrentObjectivePI - BestObjectivePI)/BestObjectivePI);
           else NASHEJ.push_back(0);
        }
        else
        {
            if (BestObjectivePI !=0 ) NASHEJ.push_back((CurrentObjectivePI - BestObjectivePI)/BestObjectivePI + (CurrentObjectivePS - BestObjectivePS)/BestObjectivePS);
           else NASHEJ.push_back((CurrentObjectivePS - BestObjectivePS)/BestObjectivePS);
        }
        cout << " NASHEJ[" << j << "] "<< NASHEJ.at(j) << endl;
    } // fin de remplissage de vecteur nash
   //----------------------------------------------------------------------------------------------
    // ----Trouver la meilleur valeur de nash qui est la valeur la plus petite dans le tableau NASHJ
    //---------------------------------------------------------------------------------------------------
        VecMinValue(NASHEJ,indexNASHEbest);
        NASHEbest = NASHEJ[indexNASHEbest];
        cout << "indexNASHEbest==========  "<< indexNASHEbest << endl;
        cout << "NASHEbest " <<NASHEbest<<endl;
        //********************Enregistrer la solution dans solution de game****************************
    //  this->solution = new Individual();
<<<<<<< HEAD
        solution = solutionSs[indexNASHEbest];

        //nettoyer  le vecteur d abord
          vector<Individual*>().swap(BestsolutionSs);
         BestsolutionSs.push_back(solution);

=======
        solution = solutionSs[indexNASHEbest];

        //nettoyer  le vecteur d abord
          vector<Individual*>().swap(BestsolutionSs);
         BestsolutionSs.push_back(solution);

>>>>>>> 0514ea9fae0f841576757defb02235a9189b0fad
         cout << " BestsolutionSs.size()***" <<BestsolutionSs.size() <<endl;
//????????????????????????????????????????????
        //this->solution = solutionSs[indexNASHEbest];
        //this->solution->plan = solutionSs[indexNASHEbest]->plan;

        //cout << "solutionSs.size() "<< solutionSs.size() << endl;
    // cout << "solution->PIObj Evaluation--" << solutionSs[indexNASHEbest]->PIObj <<endl;
        //cout << "solution->PSObj Evaluation---" << solutionSs[indexNASHEbest]->PSObj <<endl;
        //***********************************************************************************************
        //---------------------------------------------------------------------------------------
        //------------------ Enregistrer les meilleurs solution dans le tableau BestsolutionSs ---
        //-----------------------------------------------------------------------------------------
       /* k=0;
        // BestsolutionSs.push_back(solution);//la premiière valeeur et la meilleur valeur trouvée !!

        for(j=0 ; j < max_gen ; j++)
        {
            if (( NASHEJ[j] -  NASHEbest) <= epsilon)//enregistrer cette solution qui est proche de la meilleur solution trouvée
            {
                BestsolutionSs.push_back(solutionSs[j]);
                k = k+1 ;
            }
        }*/
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~é
    //~~~~~~~~~~~~~~~~~~~~~~~~ Calculer l hypervolume ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //+++++++++ 1. Normaliser les valeur trouvées
    // copier les valeur des couts dans un vecteur paircost
    vector < pair < double, double > > paircost;
    paircost.reserve(BestsolutionSs.size());
    for( j = 0 ; j < BestsolutionSs.size() ; j ++)
    {
        paircost.push_back({BestsolutionSs[j]->PIObj,BestsolutionSs[j]->PSObj});
    }
    //----------------------
    /* pair<double,double> Min;
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

*/

    int i;
    /*  cout << " ....affichage avant la normalisation ..." <<endl;
      for(i = 0 ; i < paircost.size() ; i++)
      {
          cout << " paircost.at(i).first :" << paircost.at(i).first <<endl;
           cout << " paircost.at(i).second :" << paircost.at(i).second <<endl;
      }
      cout <<" R.first " << R.first<<endl;
       cout << "R.second "<< R.second <<endl;*/
      //********************************************************
          // Normaliser les valeurs
    R.first = (R.first - Min.first)/(Max.first-Min.first);
    R.second = (R.second - Min.second)/(Max.second-Min.second);
    Normalize(paircost,Min,Max);
    //**********************************************************
       /*cout  << " ....affichage après la normalisation ..." <<endl;
      for(i = 0 ; i < paircost.size() ; i++)
      {
          cout << " paircost.at(i).first :" << paircost.at(i).first <<endl;
           cout << " paircost.at(i).second :" << paircost.at(i).second <<endl;
      }
         cout <<" R.first " << R.first<<endl;
       cout << "R.second "<< R.second <<endl;*/
    //++++ trier les valeur selon Y -----
    sort(paircost.begin(),paircost.end(),my_cmpSupDoublePair);
    //+++++++++++++++++++++++++++++++++++++++++++++
    cout << "°°°°°°°°°°°°°°°°après le tri paircost de vient °°°°°°°°°" <<endl;
       for(i = 0 ; i < paircost.size() ; i++)
      {
          cout << " paircost.at(i).first :" << paircost.at(i).first <<endl;
           cout << " paircost.at(i).second :" << paircost.at(i).second <<endl;
      }

    //++++++++ 2 . calculer l hypervolume +++++++++++
    HV = Hypervolume(paircost,R) * 100;

    //+++++++++++++++++

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //~~~~~~~~~~~~~~~~~~~~Evaluer le temps d 'exécution ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

   cout <<"  ---------------------------------------------------------" <<endl;
    clock_t stop = clock();//fin de timing
    elapsed_secs = double(stop - start) / CLOCKS_PER_SEC;
    cout << "Temps d'execution"<<elapsed_secs << " ms" << endl;
    //---------------------------------------------------------
    for(k=0;k< max_gen;k++)
    {
<<<<<<< HEAD
        cout<< " solutionSs["<<k<<"]-> Nashvalue: " << NASHEJ.at(k) << endl;
=======
        cout<< " solutionSs["<<k<<"]-> Nashvalue: " << NASHEJ.at(k) << endl;
>>>>>>> 0514ea9fae0f841576757defb02235a9189b0fad
        cout<< " solutionSs["<<k<<"]->PIObj : " << solutionSs[k]->PIObj << endl;
        cout<< " solutionSs["<<k<<"]->PSObj : " << solutionSs[k]->PSObj << endl;
    }
}


//================================= fin 15-5-2019 =======================================
//--------------------------
void Game::GameEvaluation(string instance,const int max_gen,vector<Individual*> solutionSs,double start, double & elapsed_secs,int & indexNASHEbest, vector <double> & NASHEJ)
{
    int k,j;
    //-------------------------------------------------------------------------
    int indexBestSolPI, indexBestSolPS ;//= 0; ;// 0;
    double BestObjectivePI, BestObjectivePS, CurrentObjectivePI, CurrentObjectivePS;
    vector<double> VectBestSolPI;
    //VectBestSolPI.reserve(max_gen);
    vector<double> VectBestSolPS;
    //VectBestSolPS.reserve(max_gen);
    //------------------------------------------
    //NASHEJ.reserve(max_gen);
    double NASHEbest;
    //----------------------------------------------------------------------
    //---------------- Evaluer la meilleur solution pour le joueur PI
    //----------------------------------------------------------------------
     cout <<"Afete ---"<<endl;
      for(k = 0 ; k < solutionSs.size(); k++)
        {
          //  cout<< " solutionSs[k]->PIObj " <<solutionSs[k]->PIObj <<endl;
            VectBestSolPI.push_back(solutionSs.at(k)->PIObj);
          //  cout << "VectBestSolPI(k) " << VectBestSolPI[k] <<endl;
        }
        //cout <<"$$$$$$$$$$$$$$$$$$$$$$$$$"<<endl;

        BestObjectivePI = 0.0;
        //cout << " VectBestSolPI.size() " << VectBestSolPI.size() << endl;
        VecMinValue(VectBestSolPI,indexBestSolPI);
       // cout << "indexBestSolPI : " << indexBestSolPI << endl;
        BestObjectivePI = solutionSs[indexBestSolPI]->PIObj;
       //cout << " solutionSs[indexBestSolPI]->PIObj " << solutionSs[indexBestSolPI]->PIObj<<endl;
       //cout << " BestObjectivePI===================== "<<BestObjectivePI<<endl;
       //----------------------------------------------------------------------
        //---------------- Evaluer la meilleur solution pour le joueur PI
        //----------------------------------------------------------------------
        for(k = 0 ; k < solutionSs.size(); k++)
        {
            //cout<< " solutionSs[k]->PIObj " <<solutionSs[k]->PIObj <<endl;
            VectBestSolPS.push_back(solutionSs[k]->PSObj);
            //cout << "VectBestSolPI(k) " << VectBestSolPI[k] <<endl;
        }
        BestObjectivePS = 0.0;
        VecMinValue(VectBestSolPS,indexBestSolPS);
       // cout << "indexBestSolPS : " << indexBestSolPS << endl;
        BestObjectivePS = solutionSs[indexBestSolPS]->PSObj;
     //     cout << " BestObjectivePS===================== "<<BestObjectivePS<<endl;;
        //vider la mémoire
        vector<double>().swap(VectBestSolPI);
        vector<double>().swap(VectBestSolPS);
       // cout << "indexBestSolPS : " << indexBestSolPS << endl;
      // cout << "  BestObjectivePS================  " << BestObjectivePS << endl;
      //=================================================


      //......................Utiliser le point de référence ...................................
      //.......................................................................................

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
          /*
            Min.first =  130000.0;
            Min.second = 800.0  ;
            Max.first =300000.0;
            Max.second = 2000.0 ;
            */

                R = Max;
       }
   }
   //=============================================

      //BestObjectivePI = Min.first;
      //BestObjectivePS = Min.second;





       //-------------------------------------------------------------------------
       //------------------------Remplissage du vecteur NASH -----
       //---------------------------------------------------------------------------
    for(j=0 ; j < max_gen ; j++)
    {
        CurrentObjectivePI = solutionSs[j]->PIObj;
        CurrentObjectivePS = solutionSs[j]->PSObj;
        //...........................................................EQuilibre de Nash ..................................
        if(BestObjectivePS == 0)
        {
           //[j] = (CurrentObjectivePI - BestObjectivePI)/BestObjectivePI;
           if (BestObjectivePI !=0 ) NASHEJ.push_back((CurrentObjectivePI - BestObjectivePI)/BestObjectivePI);
           else NASHEJ.push_back(0);
        }
        else
        {
           if (BestObjectivePI !=0 ) NASHEJ.push_back((CurrentObjectivePI - BestObjectivePI)/BestObjectivePI + (CurrentObjectivePS - BestObjectivePS)/BestObjectivePS);
           else NASHEJ.push_back((CurrentObjectivePS - BestObjectivePS)/BestObjectivePS);
        }
        cout << " NASHEJ[" << j << "] "<< NASHEJ.at(j) << endl;
    } // fin de remplissage de vecteur nash
   //----------------------------------------------------------------------------------------------
    // ----Trouver la meilleur valeur de nash qui est la valeur la plus petite dans le tableau NASHJ
    //---------------------------------------------------------------------------------------------------
        VecMinValue(NASHEJ,indexNASHEbest);
        NASHEbest = NASHEJ[indexNASHEbest];
        cout << "indexNASHEbest==========  "<< indexNASHEbest << endl;
        cout << "NASHEbest " <<NASHEbest<<endl;
        //********************Enregistrer la solution dans solution de game****************************
    //  this->solution = new Individual();
        solution = solutionSs[indexNASHEbest];
    //????????????????????????????????????????????
        //this->solution = solutionSs[indexNASHEbest];
        //this->solution->plan = solutionSs[indexNASHEbest]->plan;

        //cout << "solutionSs.size() "<< solutionSs.size() << endl;
    // cout << "solution->PIObj Evaluation--" << solutionSs[indexNASHEbest]->PIObj <<endl;
        //cout << "solution->PSObj Evaluation---" << solutionSs[indexNASHEbest]->PSObj <<endl;
        //***********************************************************************************************
        //---------------------------------------------------------------------------------------
        //------------------ Enregistrer les meilleurs solution dans le tableau BestsolutionSs ---
        //-----------------------------------------------------------------------------------------
        k=0;
<<<<<<< HEAD
        // BestsolutionSs.push_back(solution);//la premiière valeeur et la meilleur valeur trouvée !!
=======
        // BestsolutionSs.push_back(solution);//la premiière valeeur et la meilleur valeur trouvée !!
>>>>>>> 0514ea9fae0f841576757defb02235a9189b0fad
        vector<Individual*>().swap(BestsolutionSs);

        for(j=0 ; j < max_gen ; j++)
        {
            if (( NASHEJ[j] -  NASHEbest) <= epsilon)//enregistrer cette solution qui est proche de la meilleur solution trouvée
            {
                BestsolutionSs.push_back(solutionSs[j]);
                k = k+1 ;
            }
        }
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~é
    //~~~~~~~~~~~~~~~~~~~~~~~~ Calculer l hypervolume ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //+++++++++ 1. Normaliser les valeur trouvées
    // copier les valeur des couts dans un vecteur paircost
    vector < pair < double, double > > paircost;
    paircost.reserve(BestsolutionSs.size());
    for( j = 0 ; j < BestsolutionSs.size() ; j ++)
    {
        paircost.push_back({BestsolutionSs[j]->PIObj,BestsolutionSs[j]->PSObj});
    }
    //----------------------


   int i;
      cout << " ....affichage avant la normalisation ..." <<endl;
      for(i = 0 ; i < paircost.size() ; i++)
      {
          cout << " paircost.at(i).first :" << paircost.at(i).first <<endl;
           cout << " paircost.at(i).second :" << paircost.at(i).second <<endl;
      }
      cout <<" R.first " << R.first<<endl;
       cout << "R.second "<< R.second <<endl;
      //********************************************************
          // Normaliser les valeurs
    R.first = (R.first - Min.first)/(Max.first-Min.first);
    R.second = (R.second - Min.second)/(Max.second-Min.second);
    Normalize(paircost,Min,Max);
    //**********************************************************
      cout  << " ....affichage après la normalisation ..." <<endl;
      for(i = 0 ; i < paircost.size() ; i++)
      {
          cout << " paircost.at(i).first :" << paircost.at(i).first <<endl;
           cout << " paircost.at(i).second :" << paircost.at(i).second <<endl;
      }
     cout <<" R.first " << R.first<<endl;
    cout << "R.second "<< R.second <<endl;
    //++++ trier les valeur selon Y -----
    sort(paircost.begin(),paircost.end(),my_cmpSupDoublePair);
    //+++++++++++++++++++++++++++++++++++++++++++++
    cout << "°°°°°°°°°°°°°°°°après le tri paircost de vient °°°°°°°°°" <<endl;
       for(i = 0 ; i < paircost.size() ; i++)
      {
          cout << " paircost.at(i).first :" << paircost.at(i).first <<endl;
           cout << " paircost.at(i).second :" << paircost.at(i).second <<endl;
      }
    //++++++++ 2 . calculer l hypervolume +++++++++++
    HV = Hypervolume(paircost,R) * 100;
    //+++++++++++++++++
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //~~~~~~~~~~~~~~~~~~~~Evaluer le temps d 'exécution ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    cout <<"  ---------------------------------------------------------" <<endl;
    clock_t stop = clock();//fin de timing
    elapsed_secs = double(stop - start) / CLOCKS_PER_SEC;
    cout << "Temps d'execution"<<elapsed_secs << " ms" << endl;
    //---------------------------------------------------------
    for(k=0;k< max_gen;k++)
    {
<<<<<<< HEAD
       cout<< " solutionSs["<<k<<"]->Nash : " << NASHEJ.at(k) <<endl;
=======
       cout<< " solutionSs["<<k<<"]->Nash : " << NASHEJ.at(k) <<endl;
>>>>>>> 0514ea9fae0f841576757defb02235a9189b0fad
        cout<< " solutionSs["<<k<<"]->PIObj : " << solutionSs[k]->PIObj << endl;
        cout<< " solutionSs["<<k<<"]->PSObj : " << solutionSs[k]->PSObj << endl;
    }
}
//---------------------------------------------------------------------------
//--------------- Ajouté le 26 -4 -209 ---------------------------------------
// récupérer  l ensemble de solutoions non dominées --------------------
    void Game::GameEvaluationPareto(string instance,const int max_gen,vector<Individual*> solutionSs,double start, double & elapsed_secs,int & indexNASHEbest, vector <double> & NASHEJ)
    {
  //vector < int> IndexesSolNonDominantes;
  int i, j;
  int DominantScore;


      vector < pair<int,int> > IndexesFreqsNonDominantes;
                 //(int,int) :: le premier enregistre l index de la fréquence non dominante
                  //(int,int) :: le dexieme , combien de fois la fréquence est non dominante
      IndexesFreqsNonDominantes.reserve(max_gen);
      for( i = 0; i < max_gen;i++)//la solution condidate est dans l indice i
                {

            DominantScore = 0 ;// pour compter le nombre de solution qui domine la solution courante

                  for( j = 0; j < max_gen ;j++)
                   {
                       if (i!=j)
                       {


                       if (((solutionSs[i]->PIObj >= solutionSs[j]->PIObj) && (solutionSs[i]->PSObj  > solutionSs[j]->PSObj )) || (((solutionSs[i]->PSObj>= solutionSs[j]->PSObj) && (solutionSs[i]->PIObj > solutionSs[j]->PIObj))) )
                             DominantScore   = DominantScore +   1;
                        /* if (!((solutionSs[i]->PSObj<= solutionSs[j]->PSObj) && (solutionSs[i]->PIObj < solutionSs[j]->PIObj)))
                             DominantScore   = DominantScore +   1;*/

                       }//i!=j
                   }//fin j
                        if (DominantScore ==0)
                       // IndexesFreqsNonDominantes.push_back({i,DominantScore});// on insert l'index de la solution et son cout d'interfÃ©rences
                         BestsolutionSs.push_back(solutionSs[i]);
                       // cout << "la solution " << i << " est dominee par  " << DominantScore << " autres solutions" << endl;
                }//fin i
                //cout << "BestsolutionSs .size() " << BestsolutionSs .size() << endl;
    //sort(IndexesFreqsNonDominantes.begin(),IndexesFreqsNonDominantes.end(),my_cmpInf);

   // cout << "IndexesFreqsNonDominantes.size() "<<IndexesFreqsNonDominantes.size() <<endl;

   // int score = IndexesFreqsNonDominantes.front().second;
   // BestsolutionSs.push_back(solutionSs[IndexesFreqsNonDominantes.at(0).first]);// on insère la première bonne solution

    //s il existe un ensemble de bonne solutions ayant le mem score , on les insère
/*
   i= 1;
    while (i < IndexesFreqsNonDominantes.size() )
    {
        if (score == IndexesFreqsNonDominantes.at(i).second)
        {
            BestsolutionSs.push_back(solutionSs[IndexesFreqsNonDominantes.at(i).first]);
            i = i+1;
        }
        else
        {
          i = IndexesFreqsNonDominantes.size()   ;
        }

    }*/


//cout << "IndexesFreqsNonDominantes.back().second "<<IndexesFreqsNonDominantes.back().second<< endl;




    //--------------------------
    cout << "BestsolutionSs.size()  "<<BestsolutionSs.size() <<endl;
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~é
    //~~~~~~~~~~~~~~~~~~~~~~~~ Calculer l hypervolume ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //+++++++++ 1. Normaliser les valeur trouvées
    // copier les valeur des couts dans un vecteur paircost
    vector < pair < double, double > > paircost;
    paircost.reserve(BestsolutionSs.size());
    for( j = 0 ; j < BestsolutionSs.size() ; j ++)
    {
        paircost.push_back({BestsolutionSs[j]->PIObj,BestsolutionSs[j]->PSObj});
    }
   //----------------------
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


      cout << " ....affichage avant la normalisation ..." <<endl;
      for(i = 0 ; i < paircost.size() ; i++)
      {
          cout << " paircost.at(i).first :" << paircost.at(i).first <<endl;
           cout << " paircost.at(i).second :" << paircost.at(i).second <<endl;
      }
      cout <<" R.first " << R.first<<endl;
       cout << "R.second "<< R.second <<endl;
      //********************************************************
          // Normaliser les valeurs
    R.first = (R.first - Min.first)/(Max.first-Min.first);
    R.second = (R.second - Min.second)/(Max.second-Min.second);
    Normalize(paircost,Min,Max);
    //**********************************************************
       cout  << " ....affichage après la normalisation ..." <<endl;
      for(i = 0 ; i < paircost.size() ; i++)
      {
          cout << " paircost.at(i).first :" << paircost.at(i).first <<endl;
           cout << " paircost.at(i).second :" << paircost.at(i).second <<endl;
      }
         cout <<" R.first " << R.first<<endl;
       cout << "R.second "<< R.second <<endl;
    //++++ trier les valeur selon Y -----
    sort(paircost.begin(),paircost.end(),my_cmpSupDoublePair);
    //+++++++++++++++++++++++++++++++++++++++++++++
    cout << "°°°°°°°°°°°°°°°°après le tri paircost de vient °°°°°°°°°" <<endl;
       for(i = 0 ; i < paircost.size() ; i++)
      {
          cout << " paircost.at(i).first :" << paircost.at(i).first <<endl;
           cout << " paircost.at(i).second :" << paircost.at(i).second <<endl;
      }

    //++++++++ 2 . calculer l hypervolume +++++++++++
    HV = Hypervolume(paircost,R) * 100;
   //--------------
    //+++++++++++++++++ Ajouté le 26- 6 -2019 ---
     //Remplir les valeurs de nash des meilleurs solutions trouvées ----------------------
     int k;
    //-------------------------------------------------------------------------
    int indexBestSolPI, indexBestSolPS ;//= 0; ;// 0;
    double BestObjectivePI, BestObjectivePS, CurrentObjectivePI, CurrentObjectivePS;
    vector<double> VectBestSolPI;
    //VectBestSolPI.reserve(max_gen);
    vector<double> VectBestSolPS;
    //VectBestSolPS.reserve(max_gen);
    //------------------------------------------
    //NASHEJ.reserve(max_gen);
    double NASHEbest;
    //----------------------------------------------------------------------
    //---------------- Evaluer la meilleur solution pour le joueur PI
    //----------------------------------------------------------------------
     //cout <<"Afete ---"<<endl;
      for(k = 0 ; k < BestsolutionSs.size(); k++)
        {
          //  cout<< " solutionSs[k]->PIObj " <<solutionSs[k]->PIObj <<endl;
            VectBestSolPI.push_back(BestsolutionSs.at(k)->PIObj);
          //  cout << "VectBestSolPI(k) " << VectBestSolPI[k] <<endl;
        }
        //cout <<"$$$$$$$$$$$$$$$$$$$$$$$$$"<<endl;

        BestObjectivePI = 0.0;
        //cout << " VectBestSolPI.size() " << VectBestSolPI.size() << endl;
        VecMinValue(VectBestSolPI,indexBestSolPI);
       // cout << "indexBestSolPI : " << indexBestSolPI << endl;
        BestObjectivePI = BestsolutionSs[indexBestSolPI]->PIObj;
       //cout << " solutionSs[indexBestSolPI]->PIObj " << solutionSs[indexBestSolPI]->PIObj<<endl;
       //cout << " BestObjectivePI===================== "<<BestObjectivePI<<endl;
       //----------------------------------------------------------------------
        //---------------- Evaluer la meilleur solution pour le joueur PI
        //----------------------------------------------------------------------
        for(k = 0 ; k <  BestsolutionSs.size(); k++)
        {
            //cout<< " solutionSs[k]->PIObj " <<solutionSs[k]->PIObj <<endl;
            VectBestSolPS.push_back(BestsolutionSs[k]->PSObj);
            //cout << "VectBestSolPI(k) " << VectBestSolPI[k] <<endl;
        }
        BestObjectivePS = 0.0;
        VecMinValue(VectBestSolPS,indexBestSolPS);
       // cout << "indexBestSolPS : " << indexBestSolPS << endl;
        BestObjectivePS =  BestsolutionSs[indexBestSolPS]->PSObj;
     //     cout << " BestObjectivePS===================== "<<BestObjectivePS<<endl;;
        //vider la mémoire
        vector<double>().swap(VectBestSolPI);
        vector<double>().swap(VectBestSolPS);
       // cout << "indexBestSolPS : " << indexBestSolPS << endl;
      // cout << "  BestObjectivePS================  " << BestObjectivePS << endl;
       //-------------------------------------------------------------------------
       //------------------------Remplissage du vecteur NASH -----
       //---------------------------------------------------------------------------
      // ......................Utiliser le point de référence R ...................
      //.............................................................................
            BestObjectivePI = Min.first;
           BestObjectivePS = Min.second;
      //..........................................................................
      //...............................................................................

       //=======================
    for(j=0 ; j < BestsolutionSs.size() ; j++)
    {
        CurrentObjectivePI =  BestsolutionSs[j]->PIObj;
        CurrentObjectivePS = BestsolutionSs[j]->PSObj;
        //...........................................................EQuilibre de Nash ..................................
        if(BestObjectivePS == 0)
        {
           //[j] = (CurrentObjectivePI - BestObjectivePI)/BestObjectivePI;
           if (BestObjectivePI !=0 ) NASHEJ.push_back((CurrentObjectivePI - BestObjectivePI)/BestObjectivePI);
           else NASHEJ.push_back(0);
        }
        else
        {
           if (BestObjectivePI !=0 ) NASHEJ.push_back((CurrentObjectivePI - BestObjectivePI)/BestObjectivePI + (CurrentObjectivePS - BestObjectivePS)/BestObjectivePS);
           else NASHEJ.push_back((CurrentObjectivePS - BestObjectivePS)/BestObjectivePS);

        }
        cout << " NASHEJ[" << j << "] "<< NASHEJ.at(j) << endl;
    } // fin de remplissage de vecteur nash
      // ----Trouver la meilleur valeur de nash qui est la valeur la plus petite dans le tableau NASHJ
    //---------------------------------------------------------------------------------------------------
        VecMinValue(NASHEJ,indexNASHEbest);
        NASHEbest = NASHEJ[indexNASHEbest];
        cout << "indexNASHEbest==========  "<< indexNASHEbest << endl;
        cout << "NASHEbest " <<NASHEbest<<endl;

    //------------ fin ajout 26-6-2019 -----------


    //+++++++++++++++++

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //~~~~~~~~~~~~~~~~~~~~Evaluer le temps d 'exécution ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

   cout <<"  ---------------------------------------------------------" <<endl;
    clock_t stop = clock();//fin de timing
    elapsed_secs = double(stop - start) / CLOCKS_PER_SEC;
}
//===================================================================================================
//============================== PAreto une solution Ecart ====================
      void Game::GameEvaluationParetoEcart(string instance,const int max_gen,vector<Individual*> solutionSs,double start, double & elapsed_secs,int & indexNASHEbest, vector <double> & NASHEJ)
    {
  //vector < int> IndexesSolNonDominantes;
  int i, j;
  int DominantScore;


      vector < pair<int,int> > IndexesFreqsNonDominantes;
                 //(int,int) :: le premier enregistre l index de la fréquence non dominante
                  //(int,int) :: le dexieme , combien de fois la fréquence est non dominante
      IndexesFreqsNonDominantes.reserve(max_gen);
      for( i = 0; i < max_gen;i++)//la solution condidate est dans l indice i
                {

            DominantScore = 0 ;// pour compter le nombre de solution qui domine la solution courante

                  for( j = 0; j < max_gen ;j++)
                   {
                       if (i!=j)
                       {


                       if (((solutionSs[i]->PIObj >= solutionSs[j]->PIObj) && (solutionSs[i]->PSObj  > solutionSs[j]->PSObj )) || (((solutionSs[i]->PSObj>= solutionSs[j]->PSObj) && (solutionSs[i]->PIObj > solutionSs[j]->PIObj))) )
                             DominantScore   = DominantScore +   1;
                        /* if (!((solutionSs[i]->PSObj<= solutionSs[j]->PSObj) && (solutionSs[i]->PIObj < solutionSs[j]->PIObj)))
                             DominantScore   = DominantScore +   1;*/

                       }//i!=j
                   }//fin j
                        if (DominantScore ==0)
                       // IndexesFreqsNonDominantes.push_back({i,DominantScore});// on insert l'index de la solution et son cout d'interfÃ©rences
                         BestsolutionSs.push_back(solutionSs[i]);
                       // cout << "la solution " << i << " est dominee par  " << DominantScore << " autres solutions" << endl;
                }//fin i
   /* sort(IndexesFreqsNonDominantes.begin(),IndexesFreqsNonDominantes.end(),my_cmpInf);

   // cout << "IndexesFreqsNonDominantes.size() "<<IndexesFreqsNonDominantes.size() <<endl;

    int score = IndexesFreqsNonDominantes.front().second;
    BestsolutionSs.push_back(solutionSs[IndexesFreqsNonDominantes.at(0).first]);// on insère la première bonne solution

    //s il existe un ensemble de bonne solutions ayant le mem score , on les insère

   i= 1;
    while (i < IndexesFreqsNonDominantes.size() )
    {
        if (score == IndexesFreqsNonDominantes.at(i).second)
        {
            BestsolutionSs.push_back(solutionSs[IndexesFreqsNonDominantes.at(i).first]);
            i = i+1;
        }
        else
        {
          i = IndexesFreqsNonDominantes.size()   ;
        }

    }*/

//cout << "IndexesFreqsNonDominantes.back().second "<<IndexesFreqsNonDominantes.back().second<< endl;




    //--------------------------
    cout << "BestsolutionSs.size()  "<<BestsolutionSs.size() <<endl;
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~é
    //~~~~~~~~~~~~~~~~~~~~~~~~ Calculer l hypervolume ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //+++++++++ 1. Normaliser les valeur trouvées
    // copier les valeur des couts dans un vecteur paircost
    vector < pair < double, double > > paircost;
    paircost.reserve(BestsolutionSs.size());
    for( j = 0 ; j < BestsolutionSs.size() ; j ++)
    {
        paircost.push_back({BestsolutionSs[j]->PIObj,BestsolutionSs[j]->PSObj});
    }
   //----------------------
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


      cout << " ....affichage avant la normalisation ..." <<endl;
      for(i = 0 ; i < paircost.size() ; i++)
      {
          cout << " paircost.at(i).first :" << paircost.at(i).first <<endl;
           cout << " paircost.at(i).second :" << paircost.at(i).second <<endl;
      }
      cout <<" R.first " << R.first<<endl;
       cout << "R.second "<< R.second <<endl;
      //********************************************************
          // Normaliser les valeurs
    R.first = (R.first - Min.first)/(Max.first-Min.first);
    R.second = (R.second - Min.second)/(Max.second-Min.second);
    Normalize(paircost,Min,Max);
    //**********************************************************
       /*cout  << " ....affichage après la normalisation ..." <<endl;
      for(i = 0 ; i < paircost.size() ; i++)
      {
          cout << " paircost.at(i).first :" << paircost.at(i).first <<endl;
           cout << " paircost.at(i).second :" << paircost.at(i).second <<endl;
      }
         cout <<" R.first " << R.first<<endl;
       cout << "R.second "<< R.second <<endl;*/
    //++++ trier les valeur selon Y -----
    vector< pair < int, double > > VectEcart;
    VectEcart.reserve(BestsolutionSs.size());

    for(i = 0 ; i < BestsolutionSs.size(); i++)
    {
       double ecart = abs(paircost.at(i).first - paircost.at(i).second);
       VectEcart.push_back({i,ecart});
    }
    //-------------------------
    cout << "++++++++++ afficher vect ecart avant tri +++++++++++++ " << endl;

    for(i = 0 ; i < VectEcart.size() ; i++)
      {
          cout << " VectEcart.at(i).first :" << VectEcart.at(i).first <<endl;
           cout << " VectEcart.at(i).second:" << VectEcart.at(i).second <<endl;
      }
      //-----------------------
    sort(VectEcart.begin(),VectEcart.end(),my_cmpInfDoublePair);
    int IndexBestSol = VectEcart.front().first;
    solution = BestsolutionSs[IndexBestSol];
    cout << "IndexBestSol:::" << IndexBestSol << endl;
    //+++++++++++++++++++++++++++++++++++++++++++++
    cout << "°°°°°°°°°°°°°°°° solution retenue °°°°°°°°°" <<endl;


    vector < pair < double, double > > pairsol;
    pairsol.reserve(1);
    pairsol.push_back({paircost.at(IndexBestSol).first, paircost.at(IndexBestSol).second });
    //++++++++ 2 . calculer l hypervolume +++++++++++
    HV = Hypervolume(pairsol,R) * 100;


    //+++++++++++++++++
    //++++++++++++++++++++++
    //Remplir les valeurs de nash ----------------------
     int k;
    //-------------------------------------------------------------------------
    int indexBestSolPI, indexBestSolPS ;//= 0; ;// 0;
    double BestObjectivePI, BestObjectivePS, CurrentObjectivePI, CurrentObjectivePS;
    vector<double> VectBestSolPI;
    //VectBestSolPI.reserve(max_gen);
    vector<double> VectBestSolPS;
    //VectBestSolPS.reserve(max_gen);
    //------------------------------------------
    //NASHEJ.reserve(max_gen);
    double NASHEbest;
    //----------------------------------------------------------------------
    //---------------- Evaluer la meilleur solution pour le joueur PI
    //----------------------------------------------------------------------
     cout <<"Afete ---"<<endl;
      for(k = 0 ; k < solutionSs.size(); k++)
        {
          //  cout<< " solutionSs[k]->PIObj " <<solutionSs[k]->PIObj <<endl;
            VectBestSolPI.push_back(solutionSs.at(k)->PIObj);
          //  cout << "VectBestSolPI(k) " << VectBestSolPI[k] <<endl;
        }
        //cout <<"$$$$$$$$$$$$$$$$$$$$$$$$$"<<endl;

        BestObjectivePI = 0.0;
        //cout << " VectBestSolPI.size() " << VectBestSolPI.size() << endl;
        VecMinValue(VectBestSolPI,indexBestSolPI);
       // cout << "indexBestSolPI : " << indexBestSolPI << endl;
        BestObjectivePI = solutionSs[indexBestSolPI]->PIObj;
       //cout << " solutionSs[indexBestSolPI]->PIObj " << solutionSs[indexBestSolPI]->PIObj<<endl;
       //cout << " BestObjectivePI===================== "<<BestObjectivePI<<endl;
       //----------------------------------------------------------------------
        //---------------- Evaluer la meilleur solution pour le joueur PI
        //----------------------------------------------------------------------
         BestObjectivePI  = Min.first;
         BestObjectivePS  = Min.second;



        //========================================
        for(k = 0 ; k < max_gen; k++)
        {
            //cout<< " solutionSs[k]->PIObj " <<solutionSs[k]->PIObj <<endl;
            VectBestSolPS.push_back(solutionSs[k]->PSObj);
            //cout << "VectBestSolPI(k) " << VectBestSolPI[k] <<endl;
        }
        BestObjectivePS = 0.0;
        VecMinValue(VectBestSolPS,indexBestSolPS);
       // cout << "indexBestSolPS : " << indexBestSolPS << endl;
        BestObjectivePS = solutionSs[indexBestSolPS]->PSObj;
     //     cout << " BestObjectivePS===================== "<<BestObjectivePS<<endl;;
        //vider la mémoire
        vector<double>().swap(VectBestSolPI);
        vector<double>().swap(VectBestSolPS);
       // cout << "indexBestSolPS : " << indexBestSolPS << endl;
      // cout << "  BestObjectivePS================  " << BestObjectivePS << endl;
       //-------------------------------------------------------------------------


        BestObjectivePI  = Min.first;
         BestObjectivePS  = Min.second;
       //------------------------Remplissage du vecteur NASH -----
       //---------------------------------------------------------------------------
    for(j=0 ; j < max_gen ; j++)
    {
        CurrentObjectivePI = solutionSs[j]->PIObj;
        CurrentObjectivePS = solutionSs[j]->PSObj;
        //...........................................................EQuilibre de Nash ..................................

		   if(BestObjectivePS == 0)
        {
           //[j] = (CurrentObjectivePI - BestObjectivePI)/BestObjectivePI;
           if (BestObjectivePI !=0 ) NASHEJ.push_back((CurrentObjectivePI - BestObjectivePI)/BestObjectivePI);
           else NASHEJ.push_back(0);
        }
        else
        {
           if (BestObjectivePI !=0 ) NASHEJ.push_back((CurrentObjectivePI - BestObjectivePI)/BestObjectivePI + (CurrentObjectivePS - BestObjectivePS)/BestObjectivePS);
           else NASHEJ.push_back((CurrentObjectivePS - BestObjectivePS)/BestObjectivePS);

        }
        cout << " NASHEJ[" << j << "] "<< NASHEJ.at(j) << endl;
    } // fin de remplissage de vecteur nash
   //----------------------------------------------------------------------------------------------
    // ----Trouver la meilleur valeur de nash qui est la valeur la plus petite dans le tableau NASHJ
    //---------------------------------------------------------------------------------------------------
   indexNASHEbest = IndexBestSol;

    //+++++++++++++++++

    //+++++++++++++++++

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //~~~~~~~~~~~~~~~~~~~~Evaluer le temps d 'exécution ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

   cout <<"  ---------------------------------------------------------" <<endl;
    clock_t stop = clock();//fin de timing
    elapsed_secs = double(stop - start) / CLOCKS_PER_SEC;
}

//================================= Pareto Ecart ==============================================
//============================================================================================================

//================================= Pareto Ecart ==============================================
//============================================================================================================
//============================== PAreto une solution Ecart ====================
      void Game::GameEvaluationParetoHV(string instance,const int max_gen,vector<Individual*> solutionSs,double start, double & elapsed_secs,int & indexNASHEbest, vector <double> & NASHEJ)
    {
  //vector < int> IndexesSolNonDominantes;
  int i, j;
  int DominantScore;


      vector < pair<int,int> > IndexesFreqsNonDominantes;
                 //(int,int) :: le premier enregistre l index de la fréquence non dominante
                  //(int,int) :: le dexieme , combien de fois la fréquence est non dominante
      IndexesFreqsNonDominantes.reserve(max_gen);
    /*  for( i = 0; i < max_gen;i++)//la solution condidate est dans l indice i
                {

            DominantScore = 0 ;// pour compter le nombre de solution qui domine la solution courante

                  for( j = 0; j < max_gen ;j++)
                   {
                       if (i!=j)
                       {

                            if (((solutionSs[i]->PIObj >= solutionSs[j]->PIObj) && (solutionSs[i]->PSObj  > solutionSs[j]->PSObj )) || (((solutionSs[i]->PSObj>= solutionSs[j]->PSObj) && (solutionSs[i]->PIObj > solutionSs[j]->PIObj))) )
                             DominantScore   = DominantScore +   1;
                       }
                   }

                        IndexesFreqsNonDominantes.push_back({i,DominantScore});// on insert l'index de la solution et son cout d'interfÃ©rences

                       // cout << "la solution " << i << " est dominee par  " << DominantScore << " autres solutions" << endl;
                }//fin i
              */
                //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*****++++
                  for( i = 0; i < max_gen;i++)//la solution condidate est dans l indice i
                {

            DominantScore = 0 ;// pour compter le nombre de solution qui domine la solution courante

                  for( j = 0; j < max_gen ;j++)
                   {
                       if (i!=j)
                       {


                       if (((solutionSs[i]->PIObj >= solutionSs[j]->PIObj) && (solutionSs[i]->PSObj  > solutionSs[j]->PSObj )) || (((solutionSs[i]->PSObj>= solutionSs[j]->PSObj) && (solutionSs[i]->PIObj > solutionSs[j]->PIObj))) )
                             DominantScore   = DominantScore +   1;
                        /* if (!((solutionSs[i]->PSObj<= solutionSs[j]->PSObj) && (solutionSs[i]->PIObj < solutionSs[j]->PIObj)))
                             DominantScore   = DominantScore +   1;*/

                       }//i!=j
                   }//fin j
                        if (DominantScore ==0)
                       // IndexesFreqsNonDominantes.push_back({i,DominantScore});// on insert l'index de la solution et son cout d'interfÃ©rences
                         BestsolutionSs.push_back(solutionSs[i]);
                       // cout << "la solution " << i << " est dominee par  " << DominantScore << " autres solutions" << endl;
                }//fin i


                //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++****+++


    /*sort(IndexesFreqsNonDominantes.begin(),IndexesFreqsNonDominantes.end(),my_cmpInf);

   // cout << "IndexesFreqsNonDominantes.size() "<<IndexesFreqsNonDominantes.size() <<endl;

    int score = IndexesFreqsNonDominantes.front().second;
    BestsolutionSs.push_back(solutionSs[IndexesFreqsNonDominantes.at(0).first]);// on insère la première bonne solution
*/
    //s il existe un ensemble de bonne solutions ayant le mem score , on les insère
/*
   i= 1;
    while (i < IndexesFreqsNonDominantes.size() )
    {
        if (score == IndexesFreqsNonDominantes.at(i).second)
        {
            BestsolutionSs.push_back(solutionSs[IndexesFreqsNonDominantes.at(i).first]);
            i = i+1;
        }
        else
        {
          i = IndexesFreqsNonDominantes.size()   ;
        }

    }*/

//cout << "IndexesFreqsNonDominantes.back().second "<<IndexesFreqsNonDominantes.back().second<< endl;




    //--------------------------
    cout << "BestsolutionSs.size()  "<<BestsolutionSs.size() <<endl;
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~é
    //~~~~~~~~~~~~~~~~~~~~~~~~ Calculer l hypervolume ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //+++++++++ 1. Normaliser les valeur trouvées
    // copier les valeur des couts dans un vecteur paircost
    vector < pair < double, double > > paircost;
    paircost.reserve(BestsolutionSs.size());
    for( j = 0 ; j < BestsolutionSs.size() ; j ++)
    {
        paircost.push_back({BestsolutionSs[j]->PIObj,BestsolutionSs[j]->PSObj});
    }
   //----------------------
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


      cout << " ....affichage avant la normalisation ..." <<endl;
      for(i = 0 ; i < paircost.size() ; i++)
      {
          cout << " paircost.at(i).first :" << paircost.at(i).first <<endl;
           cout << " paircost.at(i).second :" << paircost.at(i).second <<endl;
      }
      cout <<" R.first " << R.first<<endl;
       cout << "R.second "<< R.second <<endl;
      //********************************************************
          // Normaliser les valeurs
    R.first = (R.first - Min.first)/(Max.first-Min.first);
    R.second = (R.second - Min.second)/(Max.second-Min.second);
    Normalize(paircost,Min,Max);
    //**********************************************************
       /*cout  << " ....affichage après la normalisation ..." <<endl;
      for(i = 0 ; i < paircost.size() ; i++)
      {
          cout << " paircost.at(i).first :" << paircost.at(i).first <<endl;
           cout << " paircost.at(i).second :" << paircost.at(i).second <<endl;
      }
         cout <<" R.first " << R.first<<endl;
       cout << "R.second "<< R.second <<endl;*/
    //++++ trier les valeur selon Y -----
     sort(paircost.begin(),paircost.end(),my_cmpSupDoublePair);
    vector< pair < int, double > > VectHV;
    VectHV.reserve(BestsolutionSs.size());

    for(i = 0 ; i < BestsolutionSs.size(); i++)
    {
       double ValHV = (R.first - paircost.at(i).first)* (R.second - paircost.at(i).second);
       VectHV.push_back({i,ValHV});
    }
    //-------------------------
    cout << "++++++++++ afficher vect ecart avant tri +++++++++++++ " << endl;

    for(i = 0 ; i < VectHV.size() ; i++)
      {
          cout << " VectHV.at(i).first :" << VectHV.at(i).first <<endl;
           cout << " VectHV.at(i).second:" << VectHV.at(i).second <<endl;
      }
      //-----------------------
    sort(VectHV.begin(),VectHV.end(),my_cmpSupDoublePair);
    int IndexBestSol = VectHV.front().first;
    solution = BestsolutionSs[IndexBestSol];
    cout << "IndexBestSol:::" << IndexBestSol << endl;
    //+++++++++++++++++++++++++++++++++++++++++++++
    cout << "°°°°°°°°°°°°°°°° solution retenue °°°°°°°°°" <<endl;


    vector < pair < double, double > > pairsol;
    pairsol.reserve(1);
    pairsol.push_back({paircost.at(IndexBestSol).first, paircost.at(IndexBestSol).second });
    //++++++++ 2 . calculer l hypervolume +++++++++++
    HV = Hypervolume(pairsol,R) * 100;

    //+++++++++++++++++
    //Remplir les valeurs de nash ----------------------
     int k;
    //-------------------------------------------------------------------------
    int indexBestSolPI, indexBestSolPS ;//= 0; ;// 0;
    double BestObjectivePI, BestObjectivePS, CurrentObjectivePI, CurrentObjectivePS;
    vector<double> VectBestSolPI;
    //VectBestSolPI.reserve(max_gen);
    vector<double> VectBestSolPS;
    //VectBestSolPS.reserve(max_gen);
    //------------------------------------------
    //NASHEJ.reserve(max_gen);
    double NASHEbest;
    //----------------------------------------------------------------------
    //---------------- Evaluer la meilleur solution pour le joueur PI
    //----------------------------------------------------------------------
     cout <<"Afete ---"<<endl;
      for(k = 0 ; k < solutionSs.size(); k++)
        {
          //  cout<< " solutionSs[k]->PIObj " <<solutionSs[k]->PIObj <<endl;
            VectBestSolPI.push_back(solutionSs.at(k)->PIObj);
          //  cout << "VectBestSolPI(k) " << VectBestSolPI[k] <<endl;
        }
        //cout <<"$$$$$$$$$$$$$$$$$$$$$$$$$"<<endl;

        BestObjectivePI = 0.0;
        //cout << " VectBestSolPI.size() " << VectBestSolPI.size() << endl;
        VecMinValue(VectBestSolPI,indexBestSolPI);
       // cout << "indexBestSolPI : " << indexBestSolPI << endl;
        BestObjectivePI = solutionSs[indexBestSolPI]->PIObj;
       //cout << " solutionSs[indexBestSolPI]->PIObj " << solutionSs[indexBestSolPI]->PIObj<<endl;
       //cout << " BestObjectivePI===================== "<<BestObjectivePI<<endl;
       //----------------------------------------------------------------------
        //---------------- Evaluer la meilleur solution pour le joueur PI
        //----------------------------------------------------------------------
         BestObjectivePI  = Min.first;
         BestObjectivePS  = Min.second;



        //========================================
        for(k = 0 ; k < max_gen; k++)
        {
            //cout<< " solutionSs[k]->PIObj " <<solutionSs[k]->PIObj <<endl;
            VectBestSolPS.push_back(solutionSs[k]->PSObj);
            //cout << "VectBestSolPI(k) " << VectBestSolPI[k] <<endl;
        }
        BestObjectivePS = 0.0;
        VecMinValue(VectBestSolPS,indexBestSolPS);
       // cout << "indexBestSolPS : " << indexBestSolPS << endl;
        BestObjectivePS = solutionSs[indexBestSolPS]->PSObj;
     //     cout << " BestObjectivePS===================== "<<BestObjectivePS<<endl;;
        //vider la mémoire
        vector<double>().swap(VectBestSolPI);
        vector<double>().swap(VectBestSolPS);
       // cout << "indexBestSolPS : " << indexBestSolPS << endl;
      // cout << "  BestObjectivePS================  " << BestObjectivePS << endl;
       //-------------------------------------------------------------------------
       //------------------------Remplissage du vecteur NASH -----
       //---------------------------------------------------------------------------
    for(j=0 ; j < max_gen ; j++)
    {
        CurrentObjectivePI = solutionSs[j]->PIObj;
        CurrentObjectivePS = solutionSs[j]->PSObj;
        //...........................................................EQuilibre de Nash ..................................
        if(BestObjectivePS == 0)
        {
           //[j] = (CurrentObjectivePI - BestObjectivePI)/BestObjectivePI;
           if (BestObjectivePI !=0 ) NASHEJ.push_back((CurrentObjectivePI - BestObjectivePI)/BestObjectivePI);
           else NASHEJ.push_back(0);
        }
        else
        {
           if (BestObjectivePI !=0 ) NASHEJ.push_back((CurrentObjectivePI - BestObjectivePI)/BestObjectivePI + (CurrentObjectivePS - BestObjectivePS)/BestObjectivePS);
           else NASHEJ.push_back((CurrentObjectivePS - BestObjectivePS)/BestObjectivePS);

        }
        cout << " NASHEJ[" << j << "] "<< NASHEJ.at(j) << endl;
    } // fin de remplissage de vecteur nash
   //----------------------------------------------------------------------------------------------
    // ----Trouver la meilleur valeur de nash qui est la valeur la plus petite dans le tableau NASHJ
    //---------------------------------------------------------------------------------------------------
   indexNASHEbest = IndexBestSol;


    //+++++++++++++++++

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //~~~~~~~~~~~~~~~~~~~~Evaluer le temps d 'exécution ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

   cout <<"  ---------------------------------------------------------" <<endl;
    clock_t stop = clock();//fin de timing
    elapsed_secs = double(stop - start) / CLOCKS_PER_SEC;
}
//+++++++++++++++++ ajouté le 26-6-2019 ----------------------------
  void Game::GameEvaluationParetoUneSolNash(string instance,const int max_gen,vector<Individual*> solutionSs,double start, double & elapsed_secs,int & indexNASHEbest, vector <double> & NASHEJ , double &HVValue)
    {
  //vector < int> IndexesSolNonDominantes;
  int i, j;
  int DominantScore;


      vector < pair<int,int> > IndexesFreqsNonDominantes;
                 //(int,int) :: le premier enregistre l index de la fréquence non dominante
                  //(int,int) :: le dexieme , combien de fois la fréquence est non dominante
      IndexesFreqsNonDominantes.reserve(max_gen);
    /*  for( i = 0; i < max_gen;i++)//la solution condidate est dans l indice i
                {

            DominantScore = 0 ;// pour compter le nombre de solution qui domine la solution courante

                  for( j = 0; j < max_gen ;j++)
                   {
                       if (i!=j)
                       {

                            if (((solutionSs[i]->PIObj >= solutionSs[j]->PIObj) && (solutionSs[i]->PSObj  > solutionSs[j]->PSObj )) || (((solutionSs[i]->PSObj>= solutionSs[j]->PSObj) && (solutionSs[i]->PIObj > solutionSs[j]->PIObj))) )
                             DominantScore   = DominantScore +   1;
                       }
                   }

                        IndexesFreqsNonDominantes.push_back({i,DominantScore});// on insert l'index de la solution et son cout d'interfÃ©rences

                       // cout << "la solution " << i << " est dominee par  " << DominantScore << " autres solutions" << endl;
                }//fin i
              */
                //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*****++++
                  for( i = 0; i < max_gen;i++)//la solution condidate est dans l indice i
                {

            DominantScore = 0 ;// pour compter le nombre de solution qui domine la solution courante

                  for( j = 0; j < max_gen ;j++)
                   {
                       if (i!=j)
                       {


                       if (((solutionSs[i]->PIObj >= solutionSs[j]->PIObj) && (solutionSs[i]->PSObj  > solutionSs[j]->PSObj )) || (((solutionSs[i]->PSObj>= solutionSs[j]->PSObj) && (solutionSs[i]->PIObj > solutionSs[j]->PIObj))) )
                             DominantScore   = DominantScore +   1;
                        /* if (!((solutionSs[i]->PSObj<= solutionSs[j]->PSObj) && (solutionSs[i]->PIObj < solutionSs[j]->PIObj)))
                             DominantScore   = DominantScore +   1;*/

                       }//i!=j
                   }//fin j
                        if (DominantScore ==0)
                       // IndexesFreqsNonDominantes.push_back({i,DominantScore});// on insert l'index de la solution et son cout d'interfÃ©rences
                         BestsolutionSs.push_back(solutionSs[i]);
                       // cout << "la solution " << i << " est dominee par  " << DominantScore << " autres solutions" << endl;
                }//fin i


                //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++****+++

  cout << "BestsolutionSs.size()" << BestsolutionSs.size() <<endl;

    //+++++++++++++++++
    //Remplir les valeurs de nash ----------------------
     int k;
    //-------------------------------------------------------------------------
    int indexBestSolPI, indexBestSolPS ;//= 0; ;// 0;
    double BestObjectivePI, BestObjectivePS, CurrentObjectivePI, CurrentObjectivePS;
    vector<double> VectBestSolPI;
    //VectBestSolPI.reserve(max_gen);
    vector<double> VectBestSolPS;
    //VectBestSolPS.reserve(max_gen);
    //------------------------------------------
    //NASHEJ.reserve(max_gen);
    double NASHEbest;
    //----------------------------------------------------------------------
    //---------------- Evaluer la meilleur solution pour le joueur PI
    //----------------------------------------------------------------------
     cout <<"Afete ---"<<endl;
      for(k = 0 ; k < BestsolutionSs.size(); k++)
        {
          //  cout<< " solutionSs[k]->PIObj " <<solutionSs[k]->PIObj <<endl;
            VectBestSolPI.push_back(BestsolutionSs.at(k)->PIObj);
          //  cout << "VectBestSolPI(k) " << VectBestSolPI[k] <<endl;
        }
        //cout <<"$$$$$$$$$$$$$$$$$$$$$$$$$"<<endl;

        BestObjectivePI = 0.0;
        //cout << " VectBestSolPI.size() " << VectBestSolPI.size() << endl;
        VecMinValue(VectBestSolPI,indexBestSolPI);
       // cout << "indexBestSolPI : " << indexBestSolPI << endl;
        BestObjectivePI = BestsolutionSs[indexBestSolPI]->PIObj;
       //cout << " solutionSs[indexBestSolPI]->PIObj " << solutionSs[indexBestSolPI]->PIObj<<endl;
       //cout << " BestObjectivePI===================== "<<BestObjectivePI<<endl;
       //----------------------------------------------------------------------
        //---------------- Evaluer la meilleur solution pour le joueur PI
        //----------------------------------------------------------------------
        for(k = 0 ; k <  BestsolutionSs.size(); k++)
        {
            //cout<< " solutionSs[k]->PIObj " <<solutionSs[k]->PIObj <<endl;
            VectBestSolPS.push_back(BestsolutionSs[k]->PSObj);
            //cout << "VectBestSolPI(k) " << VectBestSolPI[k] <<endl;
        }
        BestObjectivePS = 0.0;
        VecMinValue(VectBestSolPS,indexBestSolPS);
       // cout << "indexBestSolPS : " << indexBestSolPS << endl;
        BestObjectivePS =  BestsolutionSs[indexBestSolPS]->PSObj;
     //     cout << " BestObjectivePS===================== "<<BestObjectivePS<<endl;;
        //vider la mémoire
        vector<double>().swap(VectBestSolPI);
        vector<double>().swap(VectBestSolPS);
       // cout << "indexBestSolPS : " << indexBestSolPS << endl;
      // cout << "  BestObjectivePS================  " << BestObjectivePS << endl;
       //-------------------------------------------------------------------------
       //------------------------Remplissage du vecteur NASH -----
       //---------------------------------------------------------------------------
       //pour pouvoir comparer il faut homogeniser, nous choisissons le best c le min des couts pour les deux joueurs
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
       //==================================Best solultions ================
       //................... Utiliser le point de référence  ...................................
        BestObjectivePI = Min.first;
        BestObjectivePS = Min.second;
        //......................................................................

       //================================================



    for(j=0 ; j < BestsolutionSs.size() ; j++)
    {
        CurrentObjectivePI =  BestsolutionSs[j]->PIObj;
        CurrentObjectivePS = BestsolutionSs[j]->PSObj;
        //...........................................................EQuilibre de Nash ..................................
        if(BestObjectivePS == 0)
        {
           //[j] = (CurrentObjectivePI - BestObjectivePI)/BestObjectivePI;
           if (BestObjectivePI !=0 ) NASHEJ.push_back((CurrentObjectivePI - BestObjectivePI)/BestObjectivePI);
           else NASHEJ.push_back(0);
        }
        else
        {
            if (BestObjectivePI !=0 ) NASHEJ.push_back((CurrentObjectivePI - BestObjectivePI)/BestObjectivePI + (CurrentObjectivePS - BestObjectivePS)/BestObjectivePS);
           else NASHEJ.push_back((CurrentObjectivePS - BestObjectivePS)/BestObjectivePS);
        }
        cout << " NASHEJ[" << j << "] "<< NASHEJ.at(j) << endl;
    } // fin de remplissage de vecteur nash
   //----------------------------------------------------------------------------------------------
    // ----Trouver la meilleur valeur de nash qui est la valeur la plus petite dans le tableau NASHJ
    //---------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------
    // ----Trouver la meilleur valeur de nash qui est la valeur la plus petite dans le tableau NASHJ
    //---------------------------------------------------------------------------------------------------
        VecMinValue(NASHEJ,indexNASHEbest);
        NASHEbest = NASHEJ[indexNASHEbest];
        cout << "indexNASHEbest==========  "<< indexNASHEbest << endl;
        cout << "NASHEbest " <<NASHEbest<<endl;
        //********************Enregistrer la solution dans solution de game****************************
    //  this->solution = new Individual();
        solution = BestsolutionSs[indexNASHEbest];
   //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~é
    //~~~~~~~~~~~~~~~~~~~~~~~~ Calculer l hypervolume ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //+++++++++ 1. Normaliser les valeur trouvées
    // copier les valeur des couts dans un vecteur paircost
    vector < pair < double, double > > paircost;
    paircost.reserve(1);
    /*for( j = 0 ; j < BestsolutionSs.size() ; j ++)
    {
        paircost.push_back({BestsolutionSs[j]->PIObj,BestsolutionSs[j]->PSObj});
    }*/
     paircost.push_back({solution->PIObj,solution->PSObj});
    //----------------------
    /* pair<double,double> Min;
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
   }*/

      cout << " ....affichage avant la normalisation ..." <<endl;
      for(i = 0 ; i < paircost.size() ; i++)
      {
          cout << " paircost.at(i).first :" << paircost.at(i).first <<endl;
           cout << " paircost.at(i).second :" << paircost.at(i).second <<endl;
      }
      cout <<" R.first " << R.first<<endl;
       cout << "R.second "<< R.second <<endl;
      //********************************************************
          // Normaliser les valeurs
    R.first = (R.first - Min.first)/(Max.first-Min.first);
    R.second = (R.second - Min.second)/(Max.second-Min.second);
    Normalize(paircost,Min,Max);
    //**********************************************************
       cout  << " ....affichage après la normalisation ..." <<endl;
      for(i = 0 ; i < paircost.size() ; i++)
      {
          cout << " paircost.at(i).first :" << paircost.at(i).first <<endl;
           cout << " paircost.at(i).second :" << paircost.at(i).second <<endl;
      }
         cout <<" R.first " << R.first<<endl;
       cout << "R.second "<< R.second <<endl;
    //++++ trier les valeur selon Y -----
    sort(paircost.begin(),paircost.end(),my_cmpSupDoublePair);
    //+++++++++++++++++++++++++++++++++++++++++++++
    cout << "°°°°°°°°°°°°°°°°après le tri paircost de vient °°°°°°°°°" <<endl;
       for(i = 0 ; i < paircost.size() ; i++)
      {
          cout << " paircost.at(i).first :" << paircost.at(i).first <<endl;
           cout << " paircost.at(i).second :" << paircost.at(i).second <<endl;
      }

    //++++++++ 2 . calculer l hypervolume +++++++++++
    HV = Hypervolume(paircost,R) * 100;
   HVValue = HV ;
    //++++++++++++++++++++++++++++++ calculer hypervolume d une solution +++++++++++++++++++

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //~~~~~~~~~~~~~~~~~~~~Evaluer le temps d 'exécution ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

   cout <<"  ---------------------------------------------------------" <<endl;
    clock_t stop = clock();//fin de timing
    elapsed_secs = double(stop - start) / CLOCKS_PER_SEC;
}

//================================= PFin ajout 26-6-2019 -------------------- ==============================================

//.................. Utiliser la distance euclidienne pour choisir la meilleure solution ....................
//.....................................................................................................

 void Game::GameEvaluationDistEuclUneSol(string instance,const int max_gen,vector<Individual*> solutionSs,double start, double & elapsed_secs,int & indexNASHEbest, vector <double> & NASHEJ)
    {
    //vector < int> IndexesSolNonDominantes;
        int i, j;
         double BestObjectivePI, BestObjectivePS, CurrentObjectivePI, CurrentObjectivePS;
           //---------------------------------------------------------------------------
       //pour pouvoir comparer il faut homogeniser, nous choisissons le best c le min des couts pour les deux joueurs
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
        //..............................................
            vector < pair<int,double> > distanceEuc;
            distanceEuc.reserve(solutionSs.size());
            double DS = 0.0;
           // #pragma omp parallel for
            for(i=0;i<max_gen;i++)
            {
                DS=sqrt(pow(R.first-solutionSs[i]->PIObj,2)+pow(R.second-solutionSs[i]->PSObj,2));// calculer la distance euclidienne
                distanceEuc.push_back({i,DS});
            }
            sort(distanceEuc.begin(),distanceEuc.end(),my_cmpSupFirst); // la plus grande distance est la première
            indexNASHEbest = distanceEuc.front().first;



       //==================================Best solultions ================
       //................... Utiliser le point de référence  ...................................


       //================================================

      // la meilleure solution c'est celle qui correspond à indexNASHEbest
        solution = solutionSs[indexNASHEbest];

        //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~é
            //~~~~~~~~~~~~~~~~~~~~~~~~ Calculer l hypervolume ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //+++++++++ 1. Normaliser les valeur trouvées
    // copier les valeur des couts dans un vecteur paircost
    vector < pair < double, double > > paircost;
    paircost.reserve(1);
    /*for( j = 0 ; j < BestsolutionSs.size() ; j ++)
    {
        paircost.push_back({BestsolutionSs[j]->PIObj,BestsolutionSs[j]->PSObj});
    }*/
     paircost.push_back({solution->PIObj,solution->PSObj});
    //----------------------


      cout << " ....affichage avant la normalisation ..." <<endl;
      for(i = 0 ; i < paircost.size() ; i++)
      {
          cout << " paircost.at(i).first :" << paircost.at(i).first <<endl;
           cout << " paircost.at(i).second :" << paircost.at(i).second <<endl;
      }
      cout <<" R.first " << R.first<<endl;
       cout << "R.second "<< R.second <<endl;
      //********************************************************
          // Normaliser les valeurs
    R.first = (R.first - Min.first)/(Max.first-Min.first);
    R.second = (R.second - Min.second)/(Max.second-Min.second);
    Normalize(paircost,Min,Max);
    //**********************************************************
       cout  << " ....affichage après la normalisation ..." <<endl;
      for(i = 0 ; i < paircost.size() ; i++)
      {
          cout << " paircost.at(i).first :" << paircost.at(i).first <<endl;
           cout << " paircost.at(i).second :" << paircost.at(i).second <<endl;
      }
         cout <<" R.first " << R.first<<endl;
       cout << "R.second "<< R.second <<endl;
    //++++ trier les valeur selon Y -----
    sort(paircost.begin(),paircost.end(),my_cmpSupDoublePair);
    //+++++++++++++++++++++++++++++++++++++++++++++
    cout << "°°°°°°°°°°°°°°°°après le tri paircost de vient °°°°°°°°°" <<endl;
       for(i = 0 ; i < paircost.size() ; i++)
      {
          cout << " paircost.at(i).first :" << paircost.at(i).first <<endl;
           cout << " paircost.at(i).second :" << paircost.at(i).second <<endl;
      }

    //++++++++ 2 . calculer l hypervolume +++++++++++
    HV = Hypervolume(paircost,R) * 100;

    //++++++++++++++++++++++++++++++ calculer hypervolume d une solution +++++++++++++++++++
     //................... Utiliser le point de référence  ...................................
        BestObjectivePI = Min.first;
        BestObjectivePS = Min.second;
        //......................................................................
        BestsolutionSs.push_back(solution);
       //================================================



    for(j=0 ; j < max_gen ; j++)
    {
        CurrentObjectivePI =  solutionSs[j]->PIObj;
        CurrentObjectivePS = solutionSs[j]->PSObj;
        //...........................................................EQuilibre de Nash ..................................
        if(BestObjectivePS == 0)
        {
           //[j] = (CurrentObjectivePI - BestObjectivePI)/BestObjectivePI;
           if (BestObjectivePI !=0 ) NASHEJ.push_back((CurrentObjectivePI - BestObjectivePI)/BestObjectivePI);
           else NASHEJ.push_back(0);
        }
        else
        {
           if (BestObjectivePI !=0 ) NASHEJ.push_back((CurrentObjectivePI - BestObjectivePI)/BestObjectivePI + (CurrentObjectivePS - BestObjectivePS)/BestObjectivePS);
           else NASHEJ.push_back((CurrentObjectivePS - BestObjectivePS)/BestObjectivePS);
        }
        cout << " NASHEJ[" << j << "] "<< NASHEJ.at(j) << endl;
    } // fin de remplissage de vecteur nash
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //~~~~~~~~~~~~~~~~~~~~Evaluer le temps d 'exécution ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    cout << "indexNASHEbest " << indexNASHEbest << endl;
          cout << " NASHEJ[indexNASHEbest]" << NASHEJ[indexNASHEbest]<< endl;
   cout <<"  ---------------------------------------------------------" <<endl;



    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //~~~~~~~~~~~~~~~~~~~~Evaluer le temps d 'exécution ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   // indexNASHEbest = IndexBestSol;



   //°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°
   //°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°





    clock_t stop = clock();//fin de timing
    elapsed_secs = double(stop - start) / CLOCKS_PER_SEC;
}
//================================= PFin ajout 26-6-2019 -------------------- ==============================================

//============================================================================================================
//========================================================================================
void Game::PlayGameV2(int NumGame,const int max_gen, string instance,AFP* afpProblem, int StrategyTrxPI,int StrategyFreqPI,int StrategyTrxPS,int StrategyFreqPS)
{
    double elapsed_secs;

    //------------------------------------------------------------
    cout<<"########## game theory aproaches##############"<<endl;


    vector <Individual*> solutionSs;
    //solutionSs.reserve(max_gen);

    //..................................................
    int j,k;//,i,k,l;
    cout<<" size solution "<< afpProblem->trxs.size()<<endl;
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //pour calculer le temps d'excecution
    clock_t start = clock();
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    for(j=0; j<max_gen;j++)
    {
        vector<int> LTrxNTreateds;
        Individual * solutionTemp;
        //à chaque génération, on initialise  la solution(individual)
        solutionTemp = new Individual();
        //solutionTemp->plan = new vector<int>(afpProblem->trxs.size());
        solutionTemp->plan = new vector<int>();
        solutionTemp->plan->reserve(afpProblem->trxs.size());
       // solutionTemp->planCC = new vector<double>(afpProblem->trxs.size());
         solutionTemp->planCC = new vector<pair<double,double> >();
        solutionTemp->planCC->reserve(afpProblem->trxs.size());

        for(k=0; k < afpProblem->trxs.size(); k++)
        {
            //solutionTemp->plan->at(k) = -1;
            solutionTemp->plan->push_back(-1);
            solutionTemp->planCC->at(k).first = 0.0;
            solutionTemp->planCC->at(k).second = 0.0;
            solutionTemp ->PIObj = 0.0 ;
            solutionTemp->PSObj = 0.0 ;

        }
        //initialiser la liste des trx non-traité --
        //LTrxNTreateds.reserve(afpProblem->trxs.size());
       // cout << "afpProblem->trxs.size()" << afpProblem->trxs.size() << endl;
        InitLTrxNTreatedsV2(LTrxNTreateds,afpProblem);//initailiser le vecteur des trx non traité
        //cout << "LTrxNTreateds.size()" << LTrxNTreateds.size()<< endl;
        //--------------------------------------------
        TRXs trx;int f;
      //-------------------
//TRXs trx;
//on remplie les partie non copié donc si l = solution->plan->size(), cela veut dire on a trouvé une solution complète toute
  // Au début choisir alétoirement un trx
        srand ( unsigned ( time(0) ) );
        int choice;
    //choisir aléatoirement un chiffre 1 ou 2. Si 1 c est le joueur PI qui joue, si 2: le joueur PS qui joue
        choice = rand() % 2 + 1;
    // choice = 1 ;
    //cout <<"choice is : " << choice <<endl;

   /* if (choice ==1)//c est le premier joueur qui joue
    {
       PI->PIChooseTrx(StrategyTrxPI,LTrxNTreateds,trx,afpProblem,solutionTemp);//choix aléatoire du premier trx
    }
    else// cest le deuxième joueur qui joue
    {
       PS-> Play(StrategyTrxPS, StrategyFreqPS, LTrxNTreateds,solutionTemp,afpProblem);
    }*/
//-----------------------------------------------------------------
  /*  while(LTrxNTreateds.empty()==false)
    {
                //PI-> Play(StrategyTrxPI, StrategyFreqPI,trx, LTrxNTreateds,solution, afpProblem);
            if(choice == 1)
            {
                 PI-> Play(StrategyTrxPI, StrategyFreqPI,trx, LTrxNTreateds,solutionTemp, afpProblem);//PI joue avec la dexiem stratégie:trx random-random frequency
            }
            else
            {
                 PS-> Play(StrategyTrxPS, StrategyFreqPS, LTrxNTreateds,solutionTemp,afpProblem);
            }
            //----
            if (LTrxNTreateds.empty()== false)
            {
               if(choice == 1)
               {
                   PS-> Play(StrategyTrxPS, StrategyFreqPS, LTrxNTreateds,solutionTemp,afpProblem);
               }
               else
               {
                   PI-> Play(StrategyTrxPI, StrategyFreqPI,trx, LTrxNTreateds,solutionTemp, afpProblem);
               }
            }

        }//while

*/
       //la première fois on choisit aléatoirement un joueur ;
        //cout << "LTrxNTreateds.size() "<< LTrxNTreateds.size() <<endl;
        PI-> PlayV2(instance,1, StrategyFreqPI,trx, LTrxNTreateds,solutionTemp, afpProblem);
        while(LTrxNTreateds.empty()==false)
        {
            PI-> PlayV2(instance,StrategyTrxPI, StrategyFreqPI,trx, LTrxNTreateds,solutionTemp, afpProblem);
        }
        //]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
        // avec reafectation
     /*  vector < pair<int,double>  > PlanCCCostITrx ; //   MaxCostITrx[i].first = trxID; MaxCostITrx[i].second = son plus grand cout
        PlanCCCostITrx.reserve(solutionTemp.size());
        while(LTrxNTreateds.empty()==false)
        {
            int initialCost = afpProblem->ComputeSolutionInterference(solutionTemp);
            PI-> Play(StrategyTrxPI, StrategyFreqPI,trx, LTrxNTreateds,solutionTemp, afpProblem);
            solutionTemp->planCC[trxID] = afpProblem->ComputeSolutionInterference(solutionTemp) - initialCost;
            // enregistere le cout plancc dans un verteur
            for(k = 0 ; k < solutionTemp.size(); k ++ )
              {PlanCCCostITrx.push_back({k,solutionTemp->planCC[k] });}
            sort(PlanCCCostITrx.begin(),PlanCCCostITrx.end(),my_cmpSupFirst);
            pair<int,double> node ;
            node = PlanCCCostITrx.front();
            victimTrx =  afpProblem->trxs[node.first];
        }   //while(LTrxNTreateds.empty()==false)
        */

        //]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

        //calculer le cout de la solution trpuvée
        solutionTemp->PIObj = afpProblem->ComputeSolutionInterference(solutionTemp);//;afpProblem->interferenceBasedFitness(solutionTemp);//afpProblem->ComputeSolutionInterference(solution);//LF comment : ma fonction objectif (cacul de cout intererence)
        solutionTemp->PSObj = afpProblem->ComputeSolutionSeparationCost(solutionTemp);//LF comment : ma fonction objectif (cacule le cout de separation)
        //Enregistrer la solution actuelle
        //solutionSs[j] = new Individual();
        solutionSs.push_back(solutionTemp);

       // solutionSs[j] = solutionTemp;
      //  cout << "avant ---------" <<endl;
      //  cout <<  "solutionTemp->PIObj  " << solutionTemp->PIObj << endl ;
    //cout <<  "solutionTemp->PSObj  " << solutionTemp->PSObj << endl ;
   // delete solutionTemp;
        vector<int>().swap(LTrxNTreateds);

    }//max_gen

   // delete
    //cout << "solutionSs.size()"<< solutionSs.size()<<endl;
    //.................................................................................
 // ************************************************EVALUATION ******************************

    //-----------------variables Equilibre de nash..........
    vector<double> NASHEJ ;
    //NASHEJ.reserve(max_gen);
    double NASHEbest;
    int indexNASHEbest;
   // GameEvaluation( max_gen,solutionSs,start, elapsed_secs,indexNASHEbest,NASHEJ);
  //  ShowResult(instance,NumGame,elapsed_secs,max_gen,epsilon,solutionSs,indexNASHEbest,NASHEJ,BestsolutionSs,solution);

    //+++++++++++++++++++++++++++ Afficher la solution ++++++++++++++++++++++++++++++++++++
    //cout << "afpProblem->ComputeSolutionInterference(BestsolutionSs[0])-----"<< afpProblem->ComputeSolutionInterference(BestsolutionSs.at(0)) << endl;
    //cout << "afpProblem->interferenceBasedFitness(BestsolutionSs[0])-----" << afpProblem->interferenceBasedFitness(BestsolutionSs.at(0)) << endl;

}


//####################################################################################################
//######################################################## 15 - 8- 2021 ########################################################
void Game::PlayGameNaive(int ApproachGameEvaluation,int ApproachGame,int NumGame,const int max_gen, string instance,AFP* afpProblem, int & StrategyTrxPI,int & StrategyFreqPI,int & StrategyTrxPS,int & StrategyFreqPS)
{
    //°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°
    //ecrire le résultat dans un fichier : Resultat/resultatDatesystem.txt
ofstream ResultFile;
    // Declaring argument for time()

    string dateTime;
    time_t rawtime;
    struct tm * timeinfo;
    char buffer [80];
    time ( &rawtime );
    timeinfo = localtime ( &rawtime );
  //  string path="Resultats/result_";7
    string path="Resultats/";
      ostringstream temp;  //temp as in temporary
    /*temp<<"_";
    int y = timeinfo->tm_year;
    temp<<y;*/
    temp << "NAIIVE_AppG"<< ApproachGame<<"Eval_"<<ApproachGameEvaluation << "_";
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

   /* int sec =timeinfo->tm_sec;
    temp<<"_";
    temp<<sec;
    temp<<"sec";*/
    path=path+temp.str();      //str is temp as string

    stringstream ss;
    stringstream sss;
    stringstream ssss;
    stringstream sssss;
     stringstream stratFreqPI;
      stringstream stratFreqPS;
           stringstream stratTrxPI;
      stringstream stratTrxPS;
    sss << max_gen;
    ss << NumGame;
    ssss << epsilon;
    sssss << ApproachGameEvaluation;
    stratFreqPI << StrategyFreqPI;
    stratFreqPS << StrategyFreqPS;
    stratTrxPI << StrategyTrxPI;
    stratTrxPS << StrategyTrxPS;
     string appEv;
    switch (ApproachGameEvaluation)
    {
        case 11 :
        {
            appEv = "UneSolNash";
            break;
        }
        case 1 :
        {
            appEv = "Nash";
            break;
        }
         case 2 :
        {
            appEv = "Pareto";
            break;
        }
          case 22 :
        {
            appEv = "ParetoUneEcart";
            break;
        }
          case 21 :
        {
            appEv = "ParetoUneHV";
            break;
        }
           case 23 :
        {
            appEv = "ParetoUneNash";
            break;
        }
            case 24 :
        {
            appEv = "DistEucUne";
            break;
        }
         default:
            {
                cout << "erreur de choix d evaluation du jeu !!";
                break;
            }
    }

   // path = path + "_epsilon" + ssss.str()+ "_max_gen" + sss.str()+"_game" + ss.str() + "_" + "EvaluationApp_" + sssss.str() + "_" + instance;

 path = path + "_epsilon" + ssss.str()+ "_gen" + sss.str()+"_game" + ss.str() + "_" + appEv +  "_" + instance +  "_StrategyTrxPIPS_" + stratTrxPI.str()+ "_" + stratTrxPS.str() + "_StrategyFreqPIPS_" + stratFreqPI.str()+ "_" + stratFreqPS.str();
    path = path + ".txt";
    //
    ResultFile.open(path.c_str(),std::ios::app);
    if (!ResultFile) {
        cerr << "Unable to open file!!";
        exit(1);   // call system to stop
    }
    ResultFile <<"############### Game theory approach #################"<<endl;
    ResultFile << "max_gen : " <<max_gen<<endl;
    ResultFile << "Instance : "<< instance<< endl;

 cout<<"########## game theory aproaches##############"<<endl;

 double elapsed_secs;
    vector <Individual*> solutionSs;
    //solutionSs.reserve(max_gen);

    //..................................................
    int j,k;//,i,k,l;
    cout<<" size solution "<< afpProblem->trxs.size()<<endl;
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //pour calculer le temps d'excecution
    clock_t start = clock();
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //while(clock()- start)
  //#pragma omp parallel for
    for(j=0; j<max_gen;j++)
    {
        vector<TRXs> LTrxNTreateds;
        Individual * solutionTemp;
        //à chaque génération, on initialise  la solution(individual)
        solutionTemp = new Individual();
        solutionTemp->plan = new vector<int>(afpProblem->trxs.size());
        solutionTemp->planCC = new vector < pair <double,double> >(afpProblem->trxs.size());
        solutionTemp->VecPlayerIntervOrd = new vector <PlayerInterventionOrder>(afpProblem->trxs.size());
         solutionTemp ->PIObj = 0.0 ;
        solutionTemp->PSObj = 0.0 ;
        PI->PInterventionTRXOrder = new vector <int> (afpProblem->trxs.size());

        PS->PSInterventionTRXOrder = new vector <int> (afpProblem->trxs.size());

        for(k=0;k<solutionTemp->plan->size();k++)
        {
            solutionTemp->plan->at(k) = -1;
            solutionTemp->planCC->at(k).first=0.0;
            solutionTemp->planCC->at(k).second=0.0;
            PI->PInterventionTRXOrder ->at(k) = -1;
            PS->PSInterventionTRXOrder->at(k) = -1;

        }
        // vérification de solutionTemp
        /* for(k=0;k<solutionTemp->plan->size();k++)
        {
            cout << "solutionTemp->plan->at(k) "<<      solutionTemp->plan->at(k) << endl;
        }*/
        //initialiser la liste des trx non-traité --
        InitLTrxNTreateds(LTrxNTreateds,afpProblem);//initailiser le vecteur des trx non traité
        //--------------------------------------------
        TRXs trx;int f;
      //-------------------
        // Au début choisir alétoirement un trx
        srand ( unsigned ( time(0) ) );
        int choice;
        //choisir aléatoirement un chiffre 1 ou 2. Si 1 c est le joueur PI qui joue, si 2: le joueur PS qui joue
        choice = rand() % 2 + 1;
        // choice = 1 ;
        //cout <<"choice is : " << choice <<endl;
  int k = 0;
  int piplayerorder = 0;
  int psplayerorder =  0;
  if (choice ==1)//c est le premier joueur qui joue
    {

        PI-> Play(instance,StrategyTrxPI, StrategyFreqPI,trx, LTrxNTreateds,solutionTemp, afpProblem);//choix aléatoire du premier trx
        solutionTemp->VecPlayerIntervOrd->at(k).IdentPlayer = 1;
        solutionTemp->VecPlayerIntervOrd->at(k).IdTRXUsed = trx.trxID;
        PI->PInterventionTRXOrder->at(piplayerorder) = trx.trxID;
        piplayerorder = piplayerorder + 1;

    }
    else// cest le deuxième joueur qui joue
    {
       PS-> Play(instance,StrategyTrxPS, StrategyFreqPS, LTrxNTreateds,trx,solutionTemp,afpProblem);
       solutionTemp->VecPlayerIntervOrd->at(k).IdentPlayer = 2;
       solutionTemp->VecPlayerIntervOrd->at(k).IdTRXUsed = trx.trxID;
       PS->PSInterventionTRXOrder->at(psplayerorder) = trx.trxID;
        psplayerorder = psplayerorder + 1;

    }

    //PI-> Play(instance,1, 1,trx, LTrxNTreateds,solutionTemp, afpProblem);//choix aléatoire du premier trx
//-----------------------------------------------------------------
    while(LTrxNTreateds.empty()==false)
    {
                //PI-> Play(StrategyTrxPI, StrategyFreqPI,trx, LTrxNTreateds,solution, afpProblem);
                k = k+1;
           if(choice == 1)
            {
               PS-> Play(instance,StrategyTrxPS, StrategyFreqPS, LTrxNTreateds,trx,solutionTemp,afpProblem);
               solutionTemp->VecPlayerIntervOrd->at(k).IdentPlayer = 2;
               solutionTemp->VecPlayerIntervOrd->at(k).IdTRXUsed = trx.trxID;
               PS->PSInterventionTRXOrder->at(psplayerorder) = trx.trxID;
               psplayerorder = psplayerorder + 1;
            }
            else
            {
                PI-> Play(instance,StrategyTrxPI, StrategyFreqPI,trx, LTrxNTreateds,solutionTemp, afpProblem);//PI joue avec la dexiem stratégie:trx random-random frequency
                solutionTemp->VecPlayerIntervOrd->at(k).IdentPlayer = 1;
                solutionTemp->VecPlayerIntervOrd->at(k).IdTRXUsed = trx.trxID;
                PI->PInterventionTRXOrder->at(piplayerorder) = trx.trxID;
                piplayerorder = piplayerorder + 1;
               // PI->PInterventionTRXOrder->push_back({trx.trxID});
            }
             // PI-> Play(instance,StrategyTrxPI, StrategyFreqPI,trx, LTrxNTreateds,solutionTemp, afpProblem);
            //----
           if (LTrxNTreateds.empty()== false)
            {
               k = k+1;
               if(choice == 1)
               {
                    PI-> Play(instance,StrategyTrxPI, StrategyFreqPI,trx, LTrxNTreateds,solutionTemp, afpProblem);
                    solutionTemp->VecPlayerIntervOrd->at(k).IdentPlayer = 1;
                    solutionTemp->VecPlayerIntervOrd->at(k).IdTRXUsed = trx.trxID;
                    PI->PInterventionTRXOrder->at(piplayerorder) = trx.trxID;
                    piplayerorder = piplayerorder + 1;;

               }
               else
               {
                   PS-> Play(instance,StrategyTrxPS, StrategyFreqPS, LTrxNTreateds,trx,solutionTemp,afpProblem);
                   solutionTemp->VecPlayerIntervOrd->at(k).IdentPlayer = 2;
                   solutionTemp->VecPlayerIntervOrd->at(k).IdTRXUsed = trx.trxID;
                   PS->PSInterventionTRXOrder->at(psplayerorder) = trx.trxID;
                   psplayerorder = psplayerorder + 1;

               }
            }

        }//while


        //]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

        //calculer le cout de la solution trpuvée
        solutionTemp->PIObj = afpProblem->ComputeSolutionInterference(solutionTemp);//;afpProblem->interferenceBasedFitness(solutionTemp);//afpProblem->ComputeSolutionInterference(solution);//LF comment : ma fonction objectif (cacul de cout intererence)
        solutionTemp->PSObj = afpProblem->ComputeSolutionSeparationCost(solutionTemp);//LF comment : ma fonction objectif (cacule le cout de separation)
        //Enregistrer la solution actuelle
        //solutionSs[j] = new Individual();
        solutionSs.push_back(solutionTemp);

       // solutionSs[j] = solutionTemp;
      //  cout << "avant ---------" <<endl;
      //  cout <<  "solutionTemp->PIObj  " << solutionTemp->PIObj << endl ;
    //cout <<  "solutionTemp->PSObj  " << solutionTemp->PSObj << endl ;
   // delete solutionTemp;
        vector<TRXs>().swap(LTrxNTreateds);
        //delete(solutionTemp);

    }//max+_gen

   // delete
    //cout << "solutionSs.size()"<< solutionSs.size()<<endl;
    //.................................................................................
 // ************************************************EVALUATION ******************************
    //ResultFile.close();
    //-----------------variables Equilibre de nash..........
    vector<double> NASHEJ ;
    //NASHEJ.reserve(max_gen);
    double NASHEbest;
<<<<<<< HEAD
    int indexNASHEbest;
=======
    int indexNASHEbest;
>>>>>>> 0514ea9fae0f841576757defb02235a9189b0fad
    double HVValue;
    switch(ApproachGameEvaluation)
    {
        case 11:
        {
<<<<<<< HEAD
            GameEvaluationNashOneSol( instance, max_gen,solutionSs,start, elapsed_secs,indexNASHEbest,NASHEJ);
=======
            GameEvaluationNashOneSol( instance, max_gen,solutionSs,start, elapsed_secs,indexNASHEbest,NASHEJ);
>>>>>>> 0514ea9fae0f841576757defb02235a9189b0fad
            HVValue = HV;
            break;
        }
        case 1://evaluation nash ensemble
        {
<<<<<<< HEAD
            GameEvaluation( instance, max_gen,solutionSs,start, elapsed_secs,indexNASHEbest,NASHEJ);
=======
            GameEvaluation( instance, max_gen,solutionSs,start, elapsed_secs,indexNASHEbest,NASHEJ);
>>>>>>> 0514ea9fae0f841576757defb02235a9189b0fad
            HVValue = HV;
            break;
        }
         case 2:
        {
<<<<<<< HEAD
            GameEvaluationPareto( instance, max_gen,solutionSs,start, elapsed_secs,indexNASHEbest,NASHEJ);
=======
            GameEvaluationPareto( instance, max_gen,solutionSs,start, elapsed_secs,indexNASHEbest,NASHEJ);
>>>>>>> 0514ea9fae0f841576757defb02235a9189b0fad
            HVValue = HV;
            break;
        }
          case 22:
        {
<<<<<<< HEAD
            GameEvaluationParetoEcart( instance, max_gen,solutionSs,start, elapsed_secs,indexNASHEbest,NASHEJ);
=======
            GameEvaluationParetoEcart( instance, max_gen,solutionSs,start, elapsed_secs,indexNASHEbest,NASHEJ);
>>>>>>> 0514ea9fae0f841576757defb02235a9189b0fad
            HVValue = HV;
            break;
        }
           case 21:
        {
<<<<<<< HEAD
            GameEvaluationParetoHV( instance, max_gen,solutionSs,start, elapsed_secs,indexNASHEbest,NASHEJ);
=======
            GameEvaluationParetoHV( instance, max_gen,solutionSs,start, elapsed_secs,indexNASHEbest,NASHEJ);
>>>>>>> 0514ea9fae0f841576757defb02235a9189b0fad
            HVValue = HV;
            break;
        }
          case 23:
        {
<<<<<<< HEAD
            GameEvaluationParetoUneSolNash( instance, max_gen,solutionSs,start, elapsed_secs,indexNASHEbest,NASHEJ, HVValue);
=======
            GameEvaluationParetoUneSolNash( instance, max_gen,solutionSs,start, elapsed_secs,indexNASHEbest,NASHEJ, HVValue);
>>>>>>> 0514ea9fae0f841576757defb02235a9189b0fad
            HVValue = HV;
            break;
        }
          case 24:
        {
<<<<<<< HEAD
            GameEvaluationDistEuclUneSol( instance, max_gen,solutionSs,start, elapsed_secs,indexNASHEbest,NASHEJ);
=======
            GameEvaluationDistEuclUneSol( instance, max_gen,solutionSs,start, elapsed_secs,indexNASHEbest,NASHEJ);
>>>>>>> 0514ea9fae0f841576757defb02235a9189b0fad
            HVValue = HV;
            break;
        }

         default:
            {
                cout << "Erreur de choix de stratégie d'évaluation " << endl;
                break;
            }
 }
        ShowResult(ApproachGameEvaluation,instance,NumGame,elapsed_secs,max_gen,epsilon,solutionSs,indexNASHEbest,NASHEJ,BestsolutionSs,solution,path, HV);

    //+++++++++++++++++++++++++++ Afficher la solution ++++++++++++++++++++++++++++++++++++
    //cout << "afpProblem->ComputeSolutionInterference(BestsolutionSs[0])-----"<< afpProblem->ComputeSolutionInterference(BestsolutionSs.at(0)) << endl;
    //cout << "afpProblem->interferenceBasedFitness(BestsolutionSs[0])-----" << afpProblem->interferenceBasedFitness(BestsolutionSs.at(0)) << endl;
 int SizePIntervention = GetVectorRealSize(PI->PInterventionTRXOrder);
 int SizePSntervention = GetVectorRealSize(PS->PSInterventionTRXOrder);
 ShowPlayerInterventionOrder(solution,ApproachGameEvaluation,instance,elapsed_secs,max_gen,epsilon, SizePIntervention,SizePSntervention );

}

