<<<<<<< HEAD
#include <iostream>
#include <fstream>



//--------------------------

#include <cstdlib>      // std::rand, std::srand
#include <algorithm>    // std::find
#include <time.h>
#include<cmath>
//#include "Commun.cpp"
//#include "Individual.h"
//using namespace std;
#include "PSPlayer.h"
#include "../Commun/Commun.h"

//#################################################################
//Extern my Procedures and  functions  - LAIDOUI FAtma ----
//##################################################################
extern void AddSolTrxFrequency(AFP * afpProblem,Individual* &Sol,TRXs trx ,int f);
extern void UpdateLTrxNTreateds(vector <TRXs> &LTrxNTreateds, TRXs trx,int Add); //Retirer trx de LTrxNTreated
extern void UpdateTRxFrequency(TRXs &trx, int f,int Add); //Retirer f de la liste de fr�quence valide de trx
extern void UpdateTRxFrequency(TRXs &trx, int f,int Update);
extern void UpdateTRxFrequencyNew(vector<TRXs> LTrxNTreateds,AFP * afpProblem,TRXs &trx, int f,int Update);
extern bool my_cmpInf(const pair <int,int>   &a, const pair <int,int>   &b);
extern bool my_cmp(const pair <int,int>   &a, const pair <int,int>   &b);
extern bool my_cmpInfDoublePair(const pair <int,double>   &a, const pair <int,double>   &b);
extern bool my_cmpInfdouble (const double  &a,  const double   &b);
extern bool my_cmpSupFirst(const pair <int,double>   &a, const pair <int,double>   &b);
extern bool my_cmpvectintinffirst(const int &a, const int  &b);
extern bool my_cmpSupDoublePair(const pair <double,double>   &a, const pair <double,double>   &b);
//###############################################################################################
/*bool my_cmpInf(const pair <int,int>   &a, const pair <int,int>   &b)
{
    // smallest comes first
    return a.second < b.second;
}*/

//-------------------------------------
using namespace std;

/*bool my_cmpvectintinffirstPS(const int &a, const int  &b)
{
    // smallest comes first
    return a< b;
}*/
//##########################################################
PSPlayer::PSPlayer()
{
    IdPlayer = 2;
}
//##########################################################
PSPlayer::PSPlayer(AFP * afpProblem, const int max_gen,int indexLearn)
{
    IdPlayer = 2;
    PSInterventionTRXOrder = new vector <int> (afpProblem->trxs.size());
   // IdPlayer = 1;

}
//---------------------------------------------------------------------------------
PSPlayer::~PSPlayer()
{
IdPlayer = -1; IndexLearnPS = -1;
}
bool my_cmpPS(const pair <int,int>   &a, const pair <int,int>   &b)
{
    // smallest comes first
    return a.second > b.second;
}
bool my_cmpInfPS(const pair <int,int>   &a, const pair <int,int>   &b)
{
    // smallest comes first
    return a.second < b.second;
}
//++++++++++++++++++++++++++++++++
//ajouter le 04/ 3/2018 ---
void PSPlayer::PSUpdateTRxFrequencyErase(TRXs &trx, int f, int alpha) //alpha = 3 si on est dans le meme secteur; = 2 secteur diff�rent
{
    int freq;
    int indexf=FindFrequency(trx.AvailableFrequencies,f);
    if (indexf!=-1)//la fr�quence existe
    {
       trx.AvailableFrequencies->erase( trx.AvailableFrequencies->begin()+indexf);
    }
    freq = f - alpha;
    indexf = FindFrequency(trx.AvailableFrequencies,freq);
    if (indexf!=-1)//la fr�quence existe
    {
       trx.AvailableFrequencies->erase( trx.AvailableFrequencies->begin()+indexf);
    }
    //suppression des fr�quence adjacente de f
    freq = f + alpha;
    indexf=FindFrequency(trx.AvailableFrequencies,freq);
    //cout << "indexf "  <<indexf <<endl;
    if (indexf!=-1)//la fr�quence existe
    {
       trx.AvailableFrequencies->erase( trx.AvailableFrequencies->begin()+indexf);
    }
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void PSPlayer::PSUpdateTRxFrequency(vector<TRXs> &LTrxNTreateds,AFP * afpProblem,TRXs &trx,int f, int Update)
{
     int i;
    TRXs othertrxId;
    switch(Update)
    {
       case + 1://Ajout
        {
            break;
        }
        case -1://Suppression
        {
            int freq, indexf ;
            if(LTrxNTreateds.empty()==false)
            {
                if (trx.AvailableFrequencies->empty()==false)
                {

                    PSUpdateTRxFrequencyErase(trx, f,3);
                    for(i=0; i<LTrxNTreateds.size();i++)
                    {
                        othertrxId = LTrxNTreateds[i];
                        if(trx.sectorID == afpProblem->trxs[othertrxId.trxID].sectorID)//meme secteur
                        {
                            PSUpdateTRxFrequencyErase(othertrxId, f,3);
                        }//  if(trx.sectorID == afpProblem->trxs[othertrxId.trxID].sectorID)
                        else
                        {
                               if(trx.siteID == afpProblem->trxs[othertrxId.trxID].siteID)//meme secteur
                               {
                                   PSUpdateTRxFrequencyErase(othertrxId, f,2);
                               }
                        }
                    }
                 }
            }//if(LTrxNTreateds.empty()==false)
            else//if(LTrxNTreateds.empty()==true)
            {
                cout <<" EROOR : The list of untreated trx is empty!!"<<endl;
            }
            break;
        }//case -1
       default:
        {
            cout<<" Player  PS: ERREUR de mise � jour de fr�quence !!"<<endl;
            break;
        }//default switch

    }//fin switch

}


//++++++++++++++++++++++++++++++++++++++++++++++++
void PSPlayer::Play(string instance,int StrategyTrx, int StrategyFreq,vector<TRXs> &LTrxNTreateds,TRXs &trx,Individual* &Sol,AFP * afpProblem)
{
          //  TRXs trx;int f;
            //PSChooseTrx(StrategyTrx,LTrxNTreateds, trx);// 1:choisir al�atoirement un  trx non trait�


               int index,indexmin,i;
               TRXs victimtrx,othertrx;int f; //vector <int> Numneighbor;
     /*	vector< pair <int,int> >  Numneighbor;
    Numneighbor.reserve(LTrxNTreateds.size());
    for(i=0;i<LTrxNTreateds.size();i++)
    {
        Numneighbor.push_back({i,afpProblem->neighbors[LTrxNTreateds[i].sectorID].size()});//le nombre de secteur voisin du secteeur du trx i
    //trx i, le nombre de ses voisin de meme secteur
    }

    //vecminInt(Numneighbor, indexmin);
    //trier le vecteur Numneighbor selon le nombre min des voisins de  sector
    sort(Numneighbor.begin(), Numneighbor.end(),my_cmpInfPS);
    trx= LTrxNTreateds[Numneighbor[0].first]; //on choisit le premier trx dans le vecteur Numneighbor car il a le petit nombre de voisin
*/
            PSChooseTrx(afpProblem,StrategyTrx,LTrxNTreateds,trx);
           // cout << "trx.trxID" <<  trx.trxID <<endl;
            PSChooseFrequency(instance,StrategyFreq,trx,f,Sol,afpProblem) ;//1 : choisir al�atoirement une fr�quence ; 2 choisir la meilleur fr�quence
            AddSolTrxFrequency(afpProblem,Sol,trx ,f); //Proc�dure pour affecter f au trx dans la solution
            //UpdateTRxFrequencyNew(LTrxNTreateds,afpProblem,trx,f,-1);
            //UpdateTRxFrequencyV3(LTrxNTreateds,afpProblem,trx,f,-1);
          //  PSUpdateTRxFrequency(LTrxNTreateds,afpProblem,trx,f, -1);
            UpdateLTrxNTreateds(LTrxNTreateds, trx,-1); //Retirer trx de LTrxNTreated

}
double PSPlayer::PSEvaluateObj(Individual* &Sol)
{
    return 0.0;
}
//---------------------------------------
void PSPlayer::PSChooseTrx(AFP * afpProblem,int Strategytrx,vector<TRXs> LTrxNTreateds,TRXs &trx)
{
    switch(Strategytrx)
    {
case +9 :// trx qui a  le plus petit cout ds la matrice
    {
        int i,ID ;
        vector < pair < int,double> > paircost;
        //------------------------------------------------------------
        paircost.reserve(LTrxNTreateds.size());
        for(i= 0 ; i < LTrxNTreateds.size(); i++)
        {
            ID = LTrxNTreateds[i].trxID;
            paircost.push_back({ID,afpProblem->MaxCostITrx[ID].second});
        }
        sort(paircost.begin(),paircost.end(),my_cmpInfDoublePair);
        pair <int,double> node  = paircost.front();
        trx = afpProblem->trxs[node.first];
        vector < pair < int,double> >().swap(paircost);
        //cout << "trx.trxID   " << trx.trxID << endl;
        break;
    }
   case +8 : //le trx qui a le plus  grand cout de la matrice MI
    {
        int i,ID ;
        vector < pair < int,double> > paircost;
        paircost.reserve(LTrxNTreateds.size());

        //------------------------------------------------------------
     //   paircost.reserve(LTrxNTreateds.size());
        for(i= 0 ; i < LTrxNTreateds.size(); i++)
        {
            ID = LTrxNTreateds[i].trxID;

            paircost.push_back({ID,afpProblem->MaxCostITrx[ID].second});
        }
        sort(paircost.begin(),paircost.end(),my_cmpSupFirst);
        pair <int,double> node  = paircost.front();
        trx = afpProblem->trxs[node.first];
        vector < pair < int,double> >().swap(paircost);
        break;
    }


         case 0: //choix al�atoire du trx
       {
           //ChooseTrxRandom(LTrxNTreateds,trx);
          /* int i;
           vector <int> TrxIds;
           TrxIds.reserve(LTrxNTreateds.size());
           for(i = 0 ; i< LTrxNTreateds.size(); i++)
            TrxIds.push_back(LTrxNTreateds.at(i).trxID);
        sort(TrxIds.begin(),TrxIds.end(), my_cmpvectintinffirst);
        trx = afpProblem->trxs[TrxIds.front()];*/
        trx = LTrxNTreateds.at(0);
           break;
       }//case +1
       case  +1 ://Strategie 1 : Choix al�atoire de trx.
      {
        //LTrxNTreated : la liste des trx non trait�s
        int i;
        if(LTrxNTreateds.empty()==true)//on
        {
           //throw string("ERREUR: Le vecteur des trx trait� est vide !!");
                cout<<"Player PS: ERREUR: The vector of treated Trx is EMPTY!!" <<endl;;
            }
            else
            {
           //modifier l'ordre du tableau LTrxNTreateds et choisir ccelui de l entete
               /* std::srand ( unsigned ( time(0) ) );
            // using built-in random generator:
                std::random_shuffle ( LTrxNTreateds.begin(), LTrxNTreateds.end() );

                trx= LTrxNTreateds.front();*/
          // cout<<"trx choisit is :"<<trx.trxID<<endl;
           //choisir al�atoirement un index
           int index;
            index = rand() % LTrxNTreateds.size();
            trx=LTrxNTreateds.at(index);
            }//endelse
            break;

        }//case +1
                //
     case + 2 : //Choisir un trx qui un nmbre max de trx de meme site
      {     int i,j;
           	vector< pair <int,int> >  TrxNumberTrxSameSect;
            TrxNumberTrxSameSect.reserve(LTrxNTreateds.size());
           	for(i=0;i<LTrxNTreateds.size();i++)
            {
                //TrxNumberTrxSameSect[i].first=LTrxNTreateds[i].trxID;
               // TrxNumberTrxSameSect[i].second=0;
                TrxNumberTrxSameSect.push_back({LTrxNTreateds[i].trxID,0});
            }//end   	for(i=0;i<LTrxNTreateds.size();i++)
            //-------------afficher au prmier lieu le contenu de TrxNumberTrxSameSect

            for(i=0;i<LTrxNTreateds.size();i++)
            {
                TrxNumberTrxSameSect[i].second =0.0;
                for(j=0;j<LTrxNTreateds.size();j++)
                {
                    if(LTrxNTreateds[i].trxID!=LTrxNTreateds[j].trxID)//pour ne pas prendre le trx encoure d evaluation
                    {
                        if (LTrxNTreateds[i].siteID == LTrxNTreateds[j].siteID)//l'autre trx est dans le meme secteur
                      //  if (LTrxNTreateds[i].sectorID == LTrxNTreateds[j].sectorID)//l'autre trx est dans le meme secteur
                        {
                            TrxNumberTrxSameSect[i].second = TrxNumberTrxSameSect[i].second + 1;
                        }

                    }// if(LTrxNTreateds[i].trxID!=LTrxNTreateds[j].trxID)
                }//for(j=0;j<LTrxNTreateds.size()-1;j++)

               // TrxNumberTrxSameSect[i].first=LTrxNTreateds[i].trxID;
                //TrxNumberTrxSameSect[i].second=-1;
            }//(i=0;i<LTrxNTreateds.size();i++)
            //ordonner la liste
            sort(TrxNumberTrxSameSect.begin(), TrxNumberTrxSameSect.end(),my_cmp);
            int indextrx =TrxNumberTrxSameSect[0].first;// l'indice de trx � retirer;
            int pos = FindTrxID(LTrxNTreateds, indextrx);
            trx = LTrxNTreateds[pos];

            break;
       }//case + 2
        case + 3 : //choix de trx qui a le min de trx dans le meme site
      {     int i,j;
           	vector< pair <int,int> >  TrxNumberTrxSameSect;
            TrxNumberTrxSameSect.reserve(LTrxNTreateds.size());

           	for(i=0;i<LTrxNTreateds.size();i++)
            {
                //TrxNumberTrxSameSect[i].first=LTrxNTreateds[i].trxID;
               // TrxNumberTrxSameSect[i].second=0;
                TrxNumberTrxSameSect.push_back({LTrxNTreateds[i].trxID,0});
            }//end   	for(i=0;i<LTrxNTreateds.size();i++)
            //-------------afficher au prmier lieu le contenu de TrxNumberTrxSameSect

            for(i=0;i<LTrxNTreateds.size();i++)
            {
                TrxNumberTrxSameSect[i].second =0.0;
                for(j=0;j<LTrxNTreateds.size();j++)
                {
                    if(LTrxNTreateds[i].trxID!=LTrxNTreateds[j].trxID)//pour ne pas prendre le trx encoure d evaluation
                    {
                        if (LTrxNTreateds[i].siteID == LTrxNTreateds[j].siteID)//l'autre trx est dans le meme secteur
                      //  if (LTrxNTreateds[i].sectorID == LTrxNTreateds[j].sectorID)//l'autre trx est dans le meme secteur
                        {
                            TrxNumberTrxSameSect[i].second = TrxNumberTrxSameSect[i].second + 1;
                        }

                    }// if(LTrxNTreateds[i].trxID!=LTrxNTreateds[j].trxID)
                }//for(j=0;j<LTrxNTreateds.size()-1;j++)

               // TrxNumberTrxSameSect[i].first=LTrxNTreateds[i].trxID;
                //TrxNumberTrxSameSect[i].second=-1;
            }//(i=0;i<LTrxNTreateds.size();i++)
            //ordonner la liste
            sort(TrxNumberTrxSameSect.begin(), TrxNumberTrxSameSect.end(),my_cmpInf);//ordonner selon un ordre decroissant des trx de meme site
            int indextrx =TrxNumberTrxSameSect[0].first;// l'indice de trx � retirer;
            int pos = FindTrxID(LTrxNTreateds, indextrx);
            trx = LTrxNTreateds[pos];

            break;
       }//case + 2

         case + 4 : //choix de trx qui a le plus de trx dans diff�rent
      {     int i,j;
           	vector< pair <int,int> >  TrxNumberTrxSameSect;
            TrxNumberTrxSameSect.reserve(LTrxNTreateds.size());
           	for(i=0;i<LTrxNTreateds.size();i++)
            {
                //TrxNumberTrxSameSect[i].first=LTrxNTreateds[i].trxID;
               // TrxNumberTrxSameSect[i].second=0;
                TrxNumberTrxSameSect.push_back({LTrxNTreateds[i].trxID,0});
            }//end   	for(i=0;i<LTrxNTreateds.size();i++)
            //-------------afficher au prmier lieu le contenu de TrxNumberTrxSameSect

            for(i=0;i<LTrxNTreateds.size();i++)
            {
                TrxNumberTrxSameSect[i].second =0.0;
                for(j=0;j<LTrxNTreateds.size();j++)
                {
                    if(LTrxNTreateds[i].trxID!=LTrxNTreateds[j].trxID)//pour ne pas prendre le trx encoure d evaluation
                    {
                        if (LTrxNTreateds[i].siteID != LTrxNTreateds[j].siteID)//l'autre trx est dans le meme secteur
                      //  if (LTrxNTreateds[i].sectorID == LTrxNTreateds[j].sectorID)//l'autre trx est dans le meme secteur
                        {
                            TrxNumberTrxSameSect[i].second = TrxNumberTrxSameSect[i].second + 1;
                        }

                    }// if(LTrxNTreateds[i].trxID!=LTrxNTreateds[j].trxID)
                }//for(j=0;j<LTrxNTreateds.size()-1;j++)

               // TrxNumberTrxSameSect[i].first=LTrxNTreateds[i].trxID;
                //TrxNumberTrxSameSect[i].second=-1;
            }//(i=0;i<LTrxNTreateds.size();i++)
            //ordonner la liste
            sort(TrxNumberTrxSameSect.begin(), TrxNumberTrxSameSect.end(),my_cmp);//ordonner selon un ordre decroissant des trx de meme site
            int indextrx =TrxNumberTrxSameSect[0].first;// l'indice de trx � retirer;
            int pos = FindTrxID(LTrxNTreateds, indextrx);
            trx = LTrxNTreateds[pos];

            break;
       }//case + 4
        case +6:
        {// choisir le trx qui a le plus petit nbre de trx avec qui il interfere
            int i,indextrx ;
           //calculer pour chque trx non trait� , la taille des trx avec qui il interfere et l enregistrer dans LTrxNTreatedsSizeinterfere
            vector <pair<int,int> > LTrxNTreatedsSizeinterfere;
            LTrxNTreatedsSizeinterfere.reserve(LTrxNTreateds.size());
             for(i = 0 ; i < LTrxNTreateds.size() ; i++)
             {
                LTrxNTreatedsSizeinterfere.push_back({LTrxNTreateds[i].trxID, afpProblem->interferenceMatrix[i].size() });
             }
              // trier  en ordre croissantle tableau LTrxNTreatedsSizeinterfere selon la taille des trx avec qui il interfer
           sort (LTrxNTreatedsSizeinterfere.begin(), LTrxNTreatedsSizeinterfere.end(), my_cmpInf);
           indextrx = LTrxNTreatedsSizeinterfere.front().first;
 // le trx souhait� et le prmier trx qui a un nombre petir des trx avec qui il interf�re
         for(i = 0 ; i < LTrxNTreateds.size() ; i++)
             {
                 if (LTrxNTreateds[i].trxID == indextrx )
                 {
                     trx = LTrxNTreateds[i];
                     i = LTrxNTreateds.size();
                 }
             }

        //------
        break;
        }//case 6


        default :
        {
            cout << "Player PS:ERREUR de choix de strategy TRX"<< endl;
            break;
        }
    }//finswitch

}
 void PSPlayer::PSChooseFrequency(string instance,int StrategyFreq,TRXs trx,int &f,Individual * &solution,AFP * afpProblem)
 {
    switch (StrategyFreq)
    {
        case  + 1 ://choix al�atoire de la fr�quence
        {
            int index;
            if (trx.AvailableFrequencies->empty()== false )//on choisit des fr�quences disponible
            {
                index= rand() % trx.AvailableFrequencies->size();
                f= trx.AvailableFrequencies->at(index);
                solution->PIObj = afpProblem->ComputeSolutionInterference(solution);
                solution->PSObj = afpProblem->ComputeSolutionSeparationCost(solution);
                solution->planCC->at(trx.trxID).first = solution->PIObj;
                solution->planCC->at(trx.trxID).second = solution->PSObj;
            }
            else//on chosit des fr�quence valide
            {
                index = rand() % trx.validFrequencies->size();
                f=trx.validFrequencies->at(index);
            }
            break;
        }//case +1
        //....................
         //................
        case + 2 ://choix de la meilleur fr�quence
        {
            int i,indexmin,j,k;
       // Individual * tempsol =  new Individual();
        int tempfreq;
        //��������������������������������� copier la solution dans tempsol ����������������������
        //���������������������������������������������������������������������������������������
        //tempsol = solution;
        //tempsol->plan = new vector <int>(solution->plan->size());
        //tempsol->planCC = new vector <double>(solution->planCC->size());
        solution->PlanAffect = new vector< pair<int,int> > ();
        // tempsol->PIObj = solution->PIObj;
        // tempsol->PSObj = solution->PSObj;
        for(i=0;i<solution->plan->size();i++)
        {
            //tempsol->plan->at(i) = solution->plan->at(i);
            //tempsol->planCC->at(i) = solution->planCC->at(i);
           // tempsol->PIObj = solution->PIObj;
            //tempsol->PSObj = solution->PSObj;
            if(solution->plan->at(i)!=-1)//si la case dans le plan n'est pas vide on remplie le planAffect
            {
                solution->PlanAffect->push_back({i,solution->plan->at(i)});
            }
        }

        //����������������������������������������������������������
        //���������������������������������������������������������������
        //   tempsol->planCC=NULL;
        //LF comment: on traverse tte les fr�quence et on calcule le cout
        int victimFrequency,interfererFrequency;
        int victimTrx,interfererTrx;
        victimTrx = trx.trxID;

        int taille;
        //..........................................................
        //..........................................................
        //vecteur pour enregistrer le couple de cout  interference, separation � la fois
        vector < pair<double,double>  > paircost ;
        //----------------------
        if(trx.AvailableFrequencies->empty()==false)
        {
           taille =trx.AvailableFrequencies->size();

            vector<double> * veccost = new vector <double>(taille);
                 vector<double> * cost = new vector <double>(taille);
            if (taille>1)
            {
                for(i=0 ;i < taille ; i++)//pour chaque fr�quence probable on evalue le cout
                {

                    victimFrequency =trx.AvailableFrequencies->at(i);
                    veccost->at(i)=0.0;
                    cost->at(i)=0.0;
                    solution->PlanAffect->push_back({trx.trxID,victimFrequency});
                    //on �value la solution avec le nouveau couple : {victimTrx,victimFrequency}
                   int victimTrx1 = trx.trxID; int victimFrequency1 = trx.AvailableFrequencies->at(i);
                    for(j=0;j< solution->PlanAffect->size();j++)
                    {

                        victimTrx = solution->PlanAffect->at(j).first;
                        victimFrequency = solution->PlanAffect->at(j).second;
                       interfererTrx = solution->PlanAffect->at(j).first;
                        interfererFrequency = solution->PlanAffect->at(j).second;
                        if ( interfererTrx != victimTrx1)
                        {
                           // calculer le cout d interference
                            veccost->at(i)  = veccost->at(i)  + afpProblem->computeChannelInterference(victimFrequency1 ,interfererFrequency, victimTrx1, interfererTrx)+
                            afpProblem->computeChannelInterference(interfererFrequency,victimFrequency1 ,interfererTrx, victimTrx1);
                            //cout de separation
                           if(afpProblem->trxs[victimTrx1].sectorID == afpProblem->trxs[interfererTrx].sectorID)
                            {
                                //on teste si la contraite de separation co-secteur est respect�!!
                                if (abs (interfererFrequency-victimFrequency1)<3 )//contrainte co secteur viol�e
                                {
                                    cost->at(i) = cost->at(i) + 1.0;
                                }
                            }// secteur different
                            else
                            {
                                if(afpProblem->trxs[victimTrx1].siteID  == afpProblem->trxs[interfererTrx].siteID)
                                {
                        //on teste si la contrainte de separation co-site est respect�e!!
                                    if (abs (interfererFrequency-victimFrequency1)< 2)//contrainte co secteur viol�e
                                    {
                                        cost->at(i) = cost->at(i) + 1.0;
                                    }
                                }//
                            }
                        }

                    }// for(j=0 ;j < taille ; j++)//pour chaque fr�quence probable on evalue le cout
                    //.............................................................................
                    //.............................................................................
                    // enregister les couts dans le vecteur
                  //  cout << veccost->at(i) << veccost->at(i) << endl;
                    veccost->at(i) = veccost->at(i) + solution->PIObj ;
                    cost->at(i) = cost->at(i) + solution->PSObj ;
                    paircost.push_back({veccost->at(i),cost->at(i)});
                    //...................................................................
                    solution->PlanAffect->pop_back();//on retire le couple probable apres evaluation de cout et l avoir enregistr� dans veccost
                    // cout<<"frequence ::" <<trx.AvailableFrequencies->at(i)<<", son sout veccost[i] ==="<< veccost->at(i)<<endl;
                } //fortrx.AvailableFrequencies
                 //tempsol->plan->at(trx.trxID) = -1;
                    // cout<<"frequence ::" <<trx.AvailableFrequencies->at(i)<<", son sout veccost[i] ==="<< veccost->at(i)<<endl;
                //} //fortrx.AvailableFrequencies

              //le nombre de g�n�ration est le nombre de fr�quence valide
            //chaque position dans AvailableFrequencies correspond � currentobjectif
            //..............................................................
           //...................................................................................
            //utiliser l equilibre de nash
                // cout << " vcouts->size()  "<< vcouts->size() << endl;
                //+++++++++++++++++++++++++ afficer vcost
                  /*ofstream ResultFile;
            string path="Exemples/veccostMinPS_.txt";
            ResultFile.open(path.c_str(),std::ios::app);
            if (!ResultFile) {
                cerr << "Unable to open file!!";
                exit(1);   // call system to stop
            }
            ResultFile << " trx -......" << trx.trxID << endl;
            for(i=0 ;i < trx.AvailableFrequencies->size() ; i++)
            {ResultFile << "frequency , cout  ::"<< trx.AvailableFrequencies->at(i) << " ,  " <<cost->at(i)<<endl;
            }
    */
            //++++++++++choisir la valeur minimal ++++++++++++++++++++++++++
             vector < pair<int,double>  > paircostMinSep ;//pour sauvegarder la fr�quence, et sa valeur de nash
             paircostMinSep.reserve(trx.AvailableFrequencies->size());
            for(i = 0 ; i< trx.AvailableFrequencies->size(); i++)
            {
                paircostMinSep.push_back({trx.AvailableFrequencies->at(i),cost->at(i)});
            }
            //-----------------------------------------------
            //ResultFile << "avant  le tri -----" << endl;
           /*
            for ( i = 0 ; i < paircostMinSep.size() ; i++)
            ResultFile << " frequence , cost :::" << paircostMinSep.at(i).first << " , " << paircostMinSep.at(i).second << endl;
           */
           //------------------------------trier le tableau selon un ordre croissant de cout de separation---------
            sort(paircostMinSep.begin(),paircostMinSep.end(),my_cmpInfDoublePair);
            //---------------------------------------
             //--------------------- apr�s le tri
           // ResultFile << "apr�s le tri -----" << endl;
            for ( i = 0 ; i < paircostMinSep.size() ; i++)
           // ResultFile << " frequence , nash :::" << paircostMinSep.at(i).first << " , " << paircostMinSep.at(i).second << endl;

            //------------------------------------------------------------
             // si les valeurs sont �gales, nous choisissons al�atoirement une fr�quence
            //---------------------------------------------------
            k = 0 ; // pour calculer le nombre de valeurs �gale
            for(i = 0 ; i < paircostMinSep.size(); i++)
            {
                double val = paircostMinSep.at(i).second;
                pair<int,double> pnextval;
                if((i+1) < paircostMinSep.size())
                {
                    pnextval = paircostMinSep.at(i+1);
                    double nextval = pnextval.second;
                    // on copie les valeurs egales dans un tableau
                    //cout<< "hiiii here " << endl;
                    if( val == nextval )
                    {
                        k = k +1 ;//k contient le nombre de valeur �gale
                        // cout<< "hiiii here " << endl;
                    }
                    else
                    {
                        i = paircostMinSep.size();
                    }
                }
            }
            //-------
           // ResultFile << "k valeur agales "<< k <<endl;
            indexmin = rand() % (k+1);
           // ResultFile << " la fr�quence probable ***"<< paircostMinSep.at(indexmin).first<<endl;
            //---chosir la fr�quence
            f = paircostMinSep.at(indexmin).first;
                //++++++++++++++++++++++++++++++++++++++++
               // vecmin(veccost, indexmin);//indexmin:indice de la fr�quencence qui a la valeur minimale
                //cout<<"indexmin f " << indexmin<<endl;
               // indexmin = trx.AvailableFrequencies->at(0);
              // f=trx.AvailableFrequencies->at(indexmin);//indice de la fr�quence ayant un cout minimal,
                  //++++++++++++++++++++++++++++++++++++
          //  ResultFile << " f choisit est======>" << f <<endl;
           //      ResultFile.close();
                  solution->PIObj = veccost->at(indexmin);
     solution->PSObj = cost->at(indexmin);
    //+++++++++++++++++++++++++++++++


    //++++++++++++++++++++
     //vider la m�moire--vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
    vector < pair<double,double>  >().swap(paircost) ;

    delete(veccost);
    delete(cost);
    //delete(tempsol->PlanAffect);
    delete(solution->PlanAffect);
      //------------------------------- 31-8-2021 ---------------------------------------
    vector < pair<int,double>  > ().swap(paircostMinSep);
    //----------------------------------------------------------------------------------
            }//la liste des fr�quence Availble est vide
            else
            {
                f = trx.AvailableFrequencies->at(0);
            }
        }
            //*******************************************************************************
            else//on selectionne la meilleur fr�quence Valide
            {
                int taille =trx.validFrequencies->size();
                vector<double> * veccost = new vector <double>(taille);
                 vector<double> * cost = new vector <double>(taille);
                veccost->reserve(taille);
                if (trx.validFrequencies->empty()==false)
                {
                    for(i=0 ;i < taille ; i++)//pour chaque fr�quence probable on evalue le cout
                    {
                        int victimFrequency =trx.validFrequencies->at(i);
                    veccost->at(i)=0.0;
                    cost->at(i)=0.0;
                    solution->PlanAffect->push_back({trx.trxID,victimFrequency});
                    //on �value la solution avec le nouveau couple : {victimTrx,victimFrequency}
                   int victimTrx1 = trx.trxID; int victimFrequency1 = trx.AvailableFrequencies->at(i);
                    for(j=0;j< solution->PlanAffect->size();j++)
                    {

                        victimTrx = solution->PlanAffect->at(j).first;
                        victimFrequency = solution->PlanAffect->at(j).second;
                       interfererTrx = solution->PlanAffect->at(j).first;
                        interfererFrequency = solution->PlanAffect->at(j).second;
                        if ( interfererTrx != victimTrx1)
                        {
                           // calculer le cout d interference
                            veccost->at(i)  = veccost->at(i)  + afpProblem->computeChannelInterference(victimFrequency1 ,interfererFrequency, victimTrx1, interfererTrx)+
                            afpProblem->computeChannelInterference(interfererFrequency,victimFrequency1 ,interfererTrx, victimTrx1);
                            //cout de separation
                           if(afpProblem->trxs[victimTrx1].sectorID == afpProblem->trxs[interfererTrx].sectorID)
                            {
                                //on teste si la contraite de separation co-secteur est respect�!!
                                if (abs (interfererFrequency-victimFrequency1)<3 )//contrainte co secteur viol�e
                                {
                                    cost->at(i) = cost->at(i) + 1.0;
                                }
                            }// secteur different
                            else
                            {
                                if(afpProblem->trxs[victimTrx1].siteID  == afpProblem->trxs[interfererTrx].siteID)
                                {
                        //on teste si la contrainte de separation co-site est respect�e!!
                                    if (abs (interfererFrequency-victimFrequency1)< 2)//contrainte co secteur viol�e
                                    {
                                        cost->at(i) = cost->at(i) + 1.0;
                                    }
                                }//
                            }
                        }

                    }// for(j=0 ;j < taille ; j++)//pour chaque fr�quence probable on evalue le cout
                    //.............................................................................
                    //.............................................................................
                    // enregister les couts dans le vecteur
                  //  cout << veccost->at(i) << veccost->at(i) << endl;
                    veccost->at(i) = veccost->at(i) + solution->PIObj ;
                    cost->at(i) = cost->at(i) + solution->PSObj ;
                    paircost.push_back({veccost->at(i),cost->at(i)});
                    //...................................................................
                    solution->PlanAffect->pop_back();//on retire le couple probable apres evaluation de cout et l avoir enregistr� dans veccost
                    // cout<<"frequence ::" <<trx.AvailableFrequencies->at(i)<<", son sout veccost[i] ==="<< veccost->at(i)<<endl;
                } //fortrx.AvailableFrequencies
          // cout << " vcouts->size()  "<< vcouts->size() << endl;
            //++++++++++choisir la valeur minimal ++++++++++++++++++++++++++
             vector < pair<int,double>  > paircostMinSep ;//pour sauvegarder la fr�quence, et sa valeur de nash
             paircostMinSep.reserve(trx.validFrequencies->size());
            for(i = 0 ; i< trx.validFrequencies->size(); i++)
            {
                paircostMinSep.push_back({trx.validFrequencies->at(i),cost->at(i)});
            }

            //------------------Trier le tableau ---------------------
              sort(paircostMinSep.begin(),paircostMinSep.end(),my_cmpInfDoublePair);

            //------------------------------------------------------------
             // si les valeurs sont �gales, nous choisissons al�atoirement une fr�quence
            //---------------------------------------------------
            k = 0 ; // pour calculer le nombre de valeurs �gales
            for(i = 0 ; i < paircostMinSep.size(); i++)
            {
                double val = paircostMinSep.at(i).second;
                pair<int,double> pnextval;
                if((i+1) < paircostMinSep.size())
                {
                    pnextval = paircostMinSep.at(i+1);
                    double nextval = pnextval.second;
                    // on copie les valeurs egales dans un tableau
                    //cout<< "hiiii here " << endl;
                    if( val == nextval )
                    {
                        k = k +1 ;//k contient le nombre de valeur �gale
                        // cout<< "hiiii here " << endl;
                    }
                    else
                    {
                        i = paircostMinSep.size();
                    }
                }
            }
            //-------
            indexmin = rand() % (k+1);
            //---chosir la fr�quence
            f = paircostMinSep.at(indexmin).first;
            solution->PIObj = veccost->at(indexmin);
     solution->PSObj = cost->at(indexmin);
    //+++++++++++++++++++++++++++++++


    //++++++++++++++++++++
     //vider la m�moire--vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
    vector < pair<double,double>  >().swap(paircost) ;

    delete(veccost);
    delete(cost);
    //delete(tempsol->PlanAffect);
    delete(solution->PlanAffect);
                }//if (trx.validFrequencies->empty')==false)
                else
                {
                    cout << "ERROR Valid frequencies is EMPTY !!" << endl;
                }
            }
            //**************************************************************************
           break;
        }//case 2 best separation
         //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~�
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Distance ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   case  +3 ://strategy 2 choisir la meilleur fr�quence en terme distance euclidienne
    {
       int i,indexmin,j,k;
       // Individual * tempsol =  new Individual();
        int tempfreq;
        //��������������������������������� copier la solution dans tempsol ����������������������
        //���������������������������������������������������������������������������������������
        //tempsol = solution;
        //tempsol->plan = new vector <int>(solution->plan->size());
        //tempsol->planCC = new vector <double>(solution->planCC->size());
        solution->PlanAffect = new vector< pair<int,int> > ();
        // tempsol->PIObj = solution->PIObj;
        // tempsol->PSObj = solution->PSObj;
        for(i=0;i<solution->plan->size();i++)
        {
            //tempsol->plan->at(i) = solution->plan->at(i);
            //tempsol->planCC->at(i) = solution->planCC->at(i);
           // tempsol->PIObj = solution->PIObj;
            //tempsol->PSObj = solution->PSObj;
            if(solution->plan->at(i)!=-1)//si la case dans le plan n'est pas vide on remplie le planAffect
            {
                solution->PlanAffect->push_back({i,solution->plan->at(i)});
            }
        }

        //����������������������������������������������������������
        //���������������������������������������������������������������
        //   tempsol->planCC=NULL;
        //LF comment: on traverse tte les fr�quence et on calcule le cout
        int victimFrequency,interfererFrequency;
        int victimTrx,interfererTrx;
        victimTrx = trx.trxID;

        int taille;
        //..........................................................
        //..........................................................
        //vecteur pour enregistrer le couple de cout  interference, separation � la fois
        vector < pair<double,double>  > paircost ;
        //----------------------
        if(trx.AvailableFrequencies->empty()==false)
        {
           taille =trx.AvailableFrequencies->size();

            vector<double> * veccost = new vector <double>(taille);
                 vector<double> * cost = new vector <double>(taille);
            if (taille>1)
            {
              // #pragma omp parallel for
                for(i=0 ;i < taille ; i++)//pour chaque fr�quence probable on evalue le cout
                {

                    victimFrequency =trx.AvailableFrequencies->at(i);
                    veccost->at(i)=0.0;
                    cost->at(i)=0.0;
                    solution->PlanAffect->push_back({trx.trxID,victimFrequency});
                    //on �value la solution avec le nouveau couple : {victimTrx,victimFrequency}
                   int victimTrx1 = trx.trxID; int victimFrequency1 = trx.AvailableFrequencies->at(i);
                    for(j=0;j< solution->PlanAffect->size();j++)
                    {

                        victimTrx = solution->PlanAffect->at(j).first;
                        victimFrequency = solution->PlanAffect->at(j).second;
                       interfererTrx = solution->PlanAffect->at(j).first;
                        interfererFrequency = solution->PlanAffect->at(j).second;
                        if ( interfererTrx != victimTrx1)
                        {
                           // calculer le cout d interference
                            veccost->at(i)  = veccost->at(i)  + afpProblem->computeChannelInterference(victimFrequency1 ,interfererFrequency, victimTrx1, interfererTrx)+
                            afpProblem->computeChannelInterference(interfererFrequency,victimFrequency1 ,interfererTrx, victimTrx1);
                            //cout de separation
                           if(afpProblem->trxs[victimTrx1].sectorID == afpProblem->trxs[interfererTrx].sectorID)
                            {
                                //on teste si la contraite de separation co-secteur est respect�!!
                                if (abs (interfererFrequency-victimFrequency1)<3 )//contrainte co secteur viol�e
                                {
                                    cost->at(i) = cost->at(i) + 1.0;
                                }
                            }// secteur different
                            else
                            {
                                if(afpProblem->trxs[victimTrx1].siteID  == afpProblem->trxs[interfererTrx].siteID)
                                {
                        //on teste si la contrainte de separation co-site est respect�e!!
                                    if (abs (interfererFrequency-victimFrequency1)< 2)//contrainte co secteur viol�e
                                    {
                                        cost->at(i) = cost->at(i) + 1.0;
                                    }
                                }//
                            }
                        }

                    }// for(j=0 ;j < taille ; j++)//pour chaque fr�quence probable on evalue le cout
                    //.............................................................................
                    //.............................................................................
                    // enregister les couts dans le vecteur
                  //  cout << veccost->at(i) << veccost->at(i) << endl;
                    veccost->at(i) = veccost->at(i) + solution->PIObj ;
                    cost->at(i) = cost->at(i) + solution->PSObj ;
                    paircost.push_back({veccost->at(i),cost->at(i)});
                    //...................................................................
                    solution->PlanAffect->pop_back();//on retire le couple probable apres evaluation de cout et l avoir enregistr� dans veccost
                    // cout<<"frequence ::" <<trx.AvailableFrequencies->at(i)<<", son sout veccost[i] ==="<< veccost->at(i)<<endl;
                } //fortrx.AvailableFrequencies
               // vecmin(veccost, indexmin);//indexmin:indice de la fr�quencence qui a la valeur minimale
                //.............................................................................
                //.......................................................................................
               //rechercher l indexmin indice de la fr�quence dans available frequency qui a
               // une distance minimal
               //distance = abs(  paircost.first-paircost.second);
//cout << "paircost[0].first---------------" << paircost[0].first << endl;
//cout << "paircost[0].second---------------" << paircost[0].second << endl;
                indexmin= 0;
               /* double distance = abs (paircost[0].first - paircost[0].second) ;
                for(i=0;i<taille;i++)
                {
                    if(distance > abs( paircost[i].first - paircost[i].second ))
                    {
                        indexmin = i;
                        distance = abs(paircost[i].first - paircost[i].second);
                    }
                }*/


                //2.-----Normaliser -------------------------
//D�finir les valeurs de normalisation
	        pair<double,double> Min;
            pair<double,double> Max;
            pair < double, double > R;// est le point de r�f�rence ; la valeur max (normalis�)
            if (instance == "Seattle")
            //const pair<double,double> MinSeattle = (4000,15) ;
            {
                Min.first = 4000.0;
                Min.second = 15.0 ;
                Max.first = 70000.0;
                Max.second = 200.0;
                R = Max;
            }
            else if (instance == "Denver")
                {
                    Min.first = 130000.0;
                    //Min.second = 1200.0 ;
                    Min.second = 1000.0 ;
                    Max.first = 300000.0;
                    Max.second = 2500.0 ;
                    R = Max;
                }
            else if (instance== "Seattle_conception")
            {
                Min.first =  30.0;
                Min.second = 0.0  ;
                Max.first = 200000.0;
                Max.second = 5.0 ;
                R = Max;
            }

               // Normaliser les valeurs
        R.first = (R.first - Min.first)/(Max.first-Min.first);
        R.second = (R.second - Min.second)/(Max.second-Min.second);
        //cout << "R== " << R.first << " " <<R.second << endl;
        Normalize(paircost,Min,Max);
 //..............................................
    vector < pair<int,double> > distanceLF;
        distanceLF.reserve(trx.AvailableFrequencies->size());
    double DS = 0.0;
    // #pragma omp parallel for
        for(i=0;i<trx.AvailableFrequencies->size();i++)
        {
            DS=sqrt(pow(R.first-paircost[i].first,2)+pow(R.second-paircost[i].second,2));// calculer la distance euclidienne
           //  DS=sqrt(pow(paircost[i].first,2)+pow(paircost[i].second,2));// calculer la distance euclidienne
          //  cout << "DS === " << DS <<endl;
            distanceLF.push_back({i,DS});
        }
         sort(distanceLF.begin(),distanceLF.end(),my_cmpSupFirst); // la plus grande distance est la premi�re

    indexmin = distanceLF.front().first;



//......................................
//cout << "indexmin-----------" << indexmin << endl;

                //..............................................................
                //...................................................................................
                f=trx.AvailableFrequencies->at(indexmin);//indice de la fr�quence ayant un cout minimal,
              vector < pair<double,double>  >().swap(paircost) ;

              solution->PIObj = veccost->at(indexmin);
        solution->PSObj = cost->at(indexmin);
             delete(veccost);
               delete(cost);

delete(solution->PlanAffect);



            }//taille >1
            else
            {
                if(taille==1)
                {
                    f=trx.AvailableFrequencies->at(0);
                // cout<<" frequency choisit:lorsque la taille est 0"<<f<<endl;
                // cout<<"hii"<<endl;
                }
            }//taille == 1?!!*/
        }// Availablefrequencies is empty()
        else//Availablefrequencies==empty()
        {// on choisit la meilleur fr�quence VALID

            //****************#################################""
        //----------------------
        if(trx.validFrequencies->empty()==false)
        {
            vector<double> * veccost = new vector <double>(taille);
                 vector<double> * cost = new vector <double>(taille);
            if (taille>1)
            {
                for(i=0 ;i < taille ; i++)//pour chaque fr�quence probable on evalue le cout
                {

                    victimFrequency =trx.AvailableFrequencies->at(i);
                    veccost->at(i)=0.0;
                    cost->at(i)=0.0;
                    solution->PlanAffect->push_back({trx.trxID,victimFrequency});
                    //on �value la solution avec le nouveau couple : {victimTrx,victimFrequency}
                   int victimTrx1 = trx.trxID; int victimFrequency1 = trx.AvailableFrequencies->at(i);
                    for(j=0;j< solution->PlanAffect->size();j++)
                    {

                        victimTrx = solution->PlanAffect->at(j).first;
                        victimFrequency = solution->PlanAffect->at(j).second;
                       interfererTrx = solution->PlanAffect->at(j).first;
                        interfererFrequency = solution->PlanAffect->at(j).second;
                        if ( interfererTrx != victimTrx1)
                        {
                           // calculer le cout d interference
                            veccost->at(i)  = veccost->at(i)  + afpProblem->computeChannelInterference(victimFrequency1 ,interfererFrequency, victimTrx1, interfererTrx)+
                            afpProblem->computeChannelInterference(interfererFrequency,victimFrequency1 ,interfererTrx, victimTrx1);
                            //cout de separation
                           if(afpProblem->trxs[victimTrx1].sectorID == afpProblem->trxs[interfererTrx].sectorID)
                            {
                                //on teste si la contraite de separation co-secteur est respect�!!
                                if (abs (interfererFrequency-victimFrequency1)<3 )//contrainte co secteur viol�e
                                {
                                    cost->at(i) = cost->at(i) + 1.0;
                                }
                            }// secteur different
                            else
                            {
                                if(afpProblem->trxs[victimTrx1].siteID  == afpProblem->trxs[interfererTrx].siteID)
                                {
                        //on teste si la contrainte de separation co-site est respect�e!!
                                    if (abs (interfererFrequency-victimFrequency1)< 2)//contrainte co secteur viol�e
                                    {
                                        cost->at(i) = cost->at(i) + 1.0;
                                    }
                                }//
                            }
                        }

                    }// for(j=0 ;j < taille ; j++)//pour chaque fr�quence probable on evalue le cout
                    //.............................................................................
                    //.............................................................................
                    // enregister les couts dans le vecteur
                  //  cout << veccost->at(i) << veccost->at(i) << endl;
                    veccost->at(i) = veccost->at(i) + solution->PIObj ;
                    cost->at(i) = cost->at(i) + solution->PSObj ;
                    paircost.push_back({veccost->at(i),cost->at(i)});
                    //...................................................................
                    solution->PlanAffect->pop_back();//on retire le couple probable apres evaluation de cout et l avoir enregistr� dans veccost
                    // cout<<"frequence ::" <<trx.AvailableFrequencies->at(i)<<", son sout veccost[i] ==="<< veccost->at(i)<<endl;
                } //fortrx.AvailableFrequencies
              //  vecmin(veccost, indexmin);//indexmin:indice de la fr�quencence qui a la valeur minimale
                  //.............................................................................
                //.......................................................................................
               //rechercher l indexmin indice de la fr�quence dans available frequency qui a
               // une distance minimal
               //distance = abs(  paircost.first-paircost.second);
               indexmin= 0;
                double distance = abs(paircost[0].first - paircost[0].second) ;
                for(i=0;i<taille;i++)
                {
                    if(distance > abs( paircost[i].first - paircost[i].second))
                    {
                        indexmin = i;
                        distance = abs( paircost[i].first - paircost[i].second);
                    }
                }



                //..............................................................
                //...................................................................................
                f=trx.validFrequencies->at(indexmin);//indice de la fr�quence ayant un cout minimal,
                vector < pair<double,double>  >().swap(paircost) ;

              solution->PIObj = veccost->at(indexmin);
        solution->PSObj = cost->at(indexmin);
             delete(veccost);
               delete(cost);

            }//taille >1
            else
            {
                if(taille==1)
                {
                    f=trx.validFrequencies->at(0);
                // cout<<" frequency choisit:lorsque la taille est 0"<<f<<endl;
                // cout<<"hii"<<endl;
                }
            }//taille == 1?!!
        }
        else//Availablefrequencies==empty()
        {
            cout<<" la liste des fr�quences valide est vide **"<<endl;
        }
           //******************
            //cout<<" la liste des fr�quences disponibles est vide **"<<endl;
        }
    break;
    }//case 3  : best frequency DISTANCE
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~End distance ~~~~~~~~~~~~~~~~~~
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~NASH ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

     case  +4 ://strategy 2 choisir la meilleur fr�quence en terme de NASH
    { int i,j,k,choosedf,indexmin;
            double csect,csite;//coutsect, cout secteur adjacent

        Individual * tempsol =  new Individual();
        int tempfreq;
        //��������������������������������� copier la solution dans tempsol ����������������������
        //���������������������������������������������������������������������������������������
        //tempsol = solution;
        tempsol->plan = new vector <int>(solution->plan->size());
        tempsol->planCC = new vector <pair<double,double> >(solution->planCC->size());
        tempsol->PlanAffect = new vector< pair<int,int> > ();
        tempsol->PIObj = solution->PIObj;
        tempsol->PSObj = solution->PSObj;
        for(i=0;i<solution->plan->size();i++)
        {
            tempsol->plan->at(i) = solution->plan->at(i);
            tempsol->planCC->at(i) = solution->planCC->at(i);
           // tempsol->PIObj = solution->PIObj;
            //tempsol->PSObj = solution->PSObj;
            if(tempsol->plan->at(i)!=-1)//si la case dans le plan n'est pas vide on remplie le planAffect
            {
                tempsol->PlanAffect->push_back({i,tempsol->plan->at(i)});
            }
        }
        int victimFrequency,interfererFrequency;
        int victimTrx,interfererTrx;
        victimTrx = trx.trxID;
        victimTrx = trx.trxID;
            int taille;
            //--------------
            // on choisit sauf si la liste des fr�quences Availble n est pas vide
          vector < pair<double,double>  > paircost ;
      if(trx.AvailableFrequencies->empty()==false)
        {
           taille =trx.AvailableFrequencies->size();

            vector<double> * veccost = new vector <double>(taille);
             vector<double> * cost = new vector <double>(taille);
            if (taille>1)
            {
            // #pragma omp parallel for
                for(i=0 ;i < taille ; i++)//pour chaque fr�quence probable on evalue le cout
                {

                    int victimFrequency =trx.AvailableFrequencies->at(i);
                    //tempsol->plan->at(victimTrx)=victimFrequency;
                    //veccost[i]=0.0;
                    // veccost->at(i) ;
                    veccost->at(i)=0.0;
                    cost->at(i)=0.0;

                    //....................
                  //  paircost.push_back({0.0,0.0});
                    //.........................
                    //   veccost->at(0)=5.0;
                    // cout<<"veccost->size()"<<veccost->size()<<endl;
                    tempsol->PlanAffect->push_back({trx.trxID,victimFrequency});
                    // tempsol->PlanAffect->size();
                    // cout<<"   tempsol->PlanAffect->size()"<<   tempsol->PlanAffect->size()<<endl;
                    //on �value la solution avec le nouveau couple : {victimTrx,victimFrequency}

                        int victimTrx1 = trx.trxID; int victimFrequency1 = trx.AvailableFrequencies->at(i);

                  for(j=0;j<tempsol->PlanAffect->size();j++)
                    {

                        victimTrx = tempsol->PlanAffect->at(j).first;
                        victimFrequency = tempsol->PlanAffect->at(j).second;
                       /* for(k = 0 ; k < tempsol->PlanAffect->size() ; k++)
                        {
                            interfererTrx=tempsol->PlanAffect->at(k).first;
                            interfererFrequency=tempsol->PlanAffect->at(k).second;
                            if ( interfererTrx != victimTrx)
                            {
                                veccost->at(i) = veccost->at(i)+ afpProblem->computeChannelInterference(victimFrequency ,interfererFrequency, victimTrx,interfererTrx);
                            //PSPSPSPSPSPPSPSPSPSPSPSPSPSPSP
                            }
                        }*/
                        interfererTrx=tempsol->PlanAffect->at(j).first;
                        interfererFrequency=tempsol->PlanAffect->at(j).second;
                        if ( interfererTrx != victimTrx1)
                        {
                            veccost->at(i)  = veccost->at(i)  + afpProblem->computeChannelInterference(victimFrequency1 ,interfererFrequency, victimTrx1, interfererTrx)+
                            afpProblem->computeChannelInterference(interfererFrequency,victimFrequency1 ,interfererTrx, victimTrx1);
                            //cout de separation
                           if(afpProblem->trxs[victimTrx1].sectorID == afpProblem->trxs[interfererTrx].sectorID)
                            {
                                //on teste si la contraite de separation co-secteur est respect�!!
                                if (abs (interfererFrequency-victimFrequency1)< 3)//contrainte co secteur viol�e
                                {
                                    cost->at(i) = cost->at(i) + 1.0;
                                }
                            }// secteur different
                            else
                            {
                                if(afpProblem->trxs[victimTrx1].siteID  == afpProblem->trxs[interfererTrx].siteID)
                                {
                        //on teste si la contrainte de separation co-site est respect�e!!
                                    if (abs (interfererFrequency-victimFrequency1)< 2)//contrainte co secteur viol�e
                                    {
                                        cost->at(i) = cost->at(i) + 1.0;
                                    }
                                }//
                            }
                        }
                        /* for(k = j+1 ; k < tempsol->PlanAffect->size() ; k++)
                        {
                            interfererTrx=tempsol->PlanAffect->at(k).first;
                            interfererFrequency=tempsol->PlanAffect->at(k).second;
                            if(afpProblem->trxs[victimTrx].sectorID == afpProblem->trxs[interfererTrx].sectorID)
                            {
                                //cout << "hiiiii i m here we are in the same sector !!!" << endl;
                                if (abs ( interfererFrequency-victimFrequency)< 3)//contrainte co secteur viol�e
                                {
                                // cout << "Oups we have violated co sector constraint !!" << endl;
                                    cost->at(i) = cost->at(i) + 1.0;
                                }
                            }
                            else
                            {
                               if(afpProblem->trxs[victimTrx].siteID  == afpProblem->trxs[interfererTrx].siteID)
                               {
                                //on teste si la contrainte de separation co-site est respect�e!!
                                    if (abs (interfererFrequency-victimFrequency)< 2)//contrainte co secteur viol�e
                                    {
                                    // cout << "Oups we have violated co site constraint !!" << endl;
                                        cost->at(i) = cost->at(i) + 1.0;
                                    // cout << " csite " << csite<<endl;
                                    }

                                }//if(trx.siteID == afpProblem->trxs[tempsol->PlanAffect->at(j).first].siteID )

                            }//else on n est pas dans le meme site

                        }*/

                       //PSPSPSPSPSPSPSPSPSPSPSPSPSPSPSPSPSPSPSP
                    }// for(j=0 ;j < taille ; j++)//pour chaque fr�quence probable on evalue le cout
                    //.............................................................................
                    //.............................................................................
                    // enregister les couts dans le vecteur
                  //  cout << veccost->at(i) << veccost->at(i) << endl;
                    veccost->at(i) = veccost->at(i) + tempsol->PIObj ;
                    cost->at(i) = cost->at(i) + tempsol->PSObj ;
                    paircost.push_back({veccost->at(i),cost->at(i)});
                    //...................................................................
                    tempsol->PlanAffect->pop_back();//on retire le couple probable apres evaluation de cout et l avoir enregistr� dans veccost
                    // cout<<"frequence ::" <<trx.AvailableFrequencies->at(i)<<", son sout veccost[i] ==="<< veccost->at(i)<<endl;
                } //fortrx.AvailableFrequencies
                 //tempsol->plan->at(trx.trxID) = -1;
                    // cout<<"frequence ::" <<trx.AvailableFrequencies->at(i)<<", son sout veccost[i] ==="<< veccost->at(i)<<endl;
                //} //fortrx.AvailableFrequencies
               //utiliser l equilibre de nash
              //le nombre de g�n�ration est le nombre de fr�quence valide
            //chaque position dans AvailableFrequencies correspond � currentobjectif
            //..............................................................
           //...................................................................................
            //utiliser l equilibre de nash
                // cout << " vcouts->size()  "<< vcouts->size() << endl;
                //+++++++++++++++++++++++++ afficer vcost
            /*  ofstream ResultFile;
            string path="Exemples/veccostNASHPS_K_.txt";
            ResultFile.open(path.c_str(),std::ios::app);
            if (!ResultFile) {
                cerr << "Unable to open file!!";
                exit(1);   // call system to stop
            }
            ResultFile << " trx -......" << trx.trxID << endl;
            for(i=0 ;i < trx.AvailableFrequencies->size() ; i++)
            {ResultFile << trx.AvailableFrequencies->at(i) << " :   " << paircost[i].first << " = " << veccost->at(i)<<  ", " << paircost[i].second<<endl;
            }*/


            //+++++++++++++++++++++++++++++++++++++++++++++
            double BestObjectivePI,CurrentObjectivePI;
            double BestObjectivePS,CurrentObjectivePS;

             //-------------------------------
            //trouver BestObjectivePI et BestObjectivePS;
            //cout << " paircost[0].first---" << paircost[0].first <<endl;
            //cout << " paircost[0].second---" << paircost[0].second <<endl;
            BestObjectivePI = paircost[0].first;
            BestObjectivePS = paircost[0].second;
            //cout << "BestObjectivePI,BestObjectivePS  " << BestObjectivePI << " , " << BestObjectivePS << endl;
            for(i=0;i<trx.AvailableFrequencies->size();i++)
            {
                //cout <<  "paircost[i].first " << paircost[i].first << endl;
                if(BestObjectivePI > paircost[i].first)
                {
                    BestObjectivePI = paircost[i].first;
                    //cout << "BestObjectivePI "<<BestObjectivePI<< endl;
                }
                if(BestObjectivePS > paircost[i].second)
                {
                    BestObjectivePS = paircost[i].second;
                }
            }
            // cout << "BestObjectivePI,BestObjectivePS  " << BestObjectivePI << " , " << BestObjectivePS << endl;
            // trouver le meilleur couple
            int indexNASHEbest;
            indexNASHEbest = 0;
            vector<double> NASHEJ;//---------------
            double NASHEbest;
            const int SizeNashVect = trx.AvailableFrequencies->size();
            NASHEJ.reserve(SizeNashVect);
            // cout << "SizeNashVect**** " << SizeNashVect <<endl;
            // indexmin = 0;
            double gama = 0.1;
            //remplire le table de NAshj-------------------------------
            // #pragma omp parallel for
            for( i = 0; i < trx.AvailableFrequencies->size();i++)
            {
                if (BestObjectivePS != 0)
                {
                    if(BestObjectivePI != 0 )
                    {
                       //NASHEJ.push_back(0.9*(paircost[i].first - BestObjectivePI)/BestObjectivePI+ 0.1*(paircost[i].second - BestObjectivePS)/BestObjectivePS);
                        NASHEJ.push_back((paircost[i].first - BestObjectivePI)/BestObjectivePI+ (paircost[i].second - BestObjectivePS)/BestObjectivePS);
                        //NASHEJ.push_back((paircost[i].second - BestObjectivePS)/BestObjectivePS);
                    }
                    else
                    {
                       //NASHEJ.push_back(0.1*(paircost[i].second - BestObjectivePS)/BestObjectivePS);
                        NASHEJ.push_back((paircost[i].second - BestObjectivePS)/BestObjectivePS);


                    }
                }
                else
                {
                    //NASHEJ.push_back(0);
                    if(BestObjectivePI !=0 )
                    {
                        //NASHEJ.push_back(0.9*(paircost[i].first - BestObjectivePI)/BestObjectivePI);
                        NASHEJ.push_back((paircost[i].first - BestObjectivePI)/BestObjectivePI);
                    }
                    else
                    {
                        NASHEJ.push_back(0);
                    }
                }
            }

             //++++++++++++++++++++++++++aficher les valeur de nash ++++++++++++++
            /* ResultFile << "���������������������� NASH ����������" <<endl;
            for(i=0 ;i < trx.AvailableFrequencies->size() ; i++)
            {
                ResultFile << "NASHEJ.at(i) " << NASHEJ.at(i) <<endl;
            }*/
            //------------------------trouver la meilleur valeur de NAsh (la plus petite)--------------------------
            /*NASHEbest = NASHEJ.at(0);
           //  cout << "NASHEJ.at(0) ......" <<NASHEJ.at(0)<<endl;
            for( i = 0; i < trx.AvailableFrequencies->size();i++)
            {
                if ( NASHEJ.at(i) <  NASHEbest )//enregistrer cette solution
                {
                    NASHEbest = NASHEJ.at(i);
                    indexNASHEbest = i;
                   // cout << "hi ..." <<endl;
                }
            }
            indexmin = indexNASHEbest;*/

          //  cout << "indexmin " <<indexmin <<endl;

         //   vecmin(veccost,indexmin);
            //cout << "indexmin "<< indexmin << endl;
 //++++++++++++++++++++rechercher la valeur minimal dans un tableau nash si plus sieur valeur de nash sont egale
 //on choisit al�atoirement une variable  +++++
   vector < pair<int,double>  > paircostNash ;//pour sauvegarder la fr�quence, et sa valeur de nash
             paircostNash.reserve(NASHEJ.size());
    for(i = 0 ; i< NASHEJ.size(); i++)
    {
       paircostNash.push_back({trx.AvailableFrequencies->at(i),NASHEJ.at(i)});
       //paircostNash.at(i).first = trx.AvailableFrequencies->at(i);
        //paircostNash.at(i).second = NASHEJ.at(i);
    }
    //-----------------------------------
    /* ResultFile << "avant  le tri -----" << endl;
     for ( i = 0 ; i < paircostNash.size() ; i++)
    ResultFile << " frequence , nash :::" << paircostNash.at(i).first << " , " << paircostNash.at(i).second << endl;*/
    //------------------------------trier le tableau ---------
    sort(paircostNash.begin(),paircostNash.end(),my_cmpInfDoublePair);//le pleus petit d abord
   // sort(paircostNash.begin(),paircostNash.end(),my_cmpSupFirst);
    //-----------------------------------------------------
    // si les valeurs sont �gales, nous choisissons al�atoirement une fr�quence
    //cout << "paircostNash.size()  " << paircostNash.size() <<endl;
    //--------------------- apr�s le tri
   /* ResultFile << "apr�s le tri -----" << endl;
     for ( i = 0 ; i < paircostNash.size() ; i++)
    ResultFile << " frequence , nash :::" << paircostNash.at(i).first << " , " << paircostNash.at(i).second << endl;*/

    //---------------------------------------------------
    i = 0;     k = 0 ;
    for(i = 0 ; i < paircostNash.size(); i++)
    {
         double val = paircostNash.at(i).second;
         pair<int,double> pnextval;
         if((i+1) < paircostNash.size())
         {
            pnextval = paircostNash.at(i+1);
            double nextval = pnextval.second;
            // on copie les valeurs egales dans un tableau
            //cout<< "hiiii here " << endl;
            if( val == nextval )
            {
                k = k +1 ;//k contient le nombre de valeur �gale
               // cout<< "hiiii here " << endl;

            }
            else
            {
                i = paircostNash.size();
            }
         }
    }
    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
   // ResultFile << "k valeur agales "<< k <<endl;
    indexmin = rand() % (k+1);
     // ResultFile << " la fr�quence probable ***"<< paircostNash.at(indexmin).first<<endl;
     f = paircostNash.at(indexmin).first;
        // rechercher l indice de  f*************** ajout� le 25-4-2019
    int indexf;
    for(i = 0 ; i < trx.AvailableFrequencies->size(); i++)
    {
        if(trx.AvailableFrequencies->at(i) == f)
        {
            indexf = i;
            i = trx.AvailableFrequencies->size();
        }
    }

      solution->PIObj = veccost->at(indexf);
      solution->PSObj = cost->at(indexf);
      solution->planCC->at(trx.trxID).first = solution->PIObj;
      solution->planCC->at(trx.trxID).second = solution->PSObj;
            //................................................................................
            //................................................................................
           // f=trx.AvailableFrequencies->at(indexmin);//indice de la fr�quence ayant un cout minimal,




           // ResultFile << " f choisit est======>" << f <<endl;




           // ResultFile.close();
            //vider la m�moire--vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
           // vector<double>().swap(NASHEJ);
            vector < pair<double,double>  >().swap(paircost) ;
             delete(veccost);
               delete(cost);
              delete(tempsol->PlanAffect);
              //-------------------
              vector < pair<int,double>  > ().swap(paircostNash);
                vector<double> ().swap(NASHEJ);
                delete(tempsol);




            }//taille >1
            else
            {
                if(taille==1)
                {
                    f=trx.AvailableFrequencies->at(0);
                // cout<<" frequency choisit:lorsque la taille est 0"<<f<<endl;
                // cout<<"hii"<<endl;
                }
            }//taille == 1?!!
        }// Availablefrequencies is empty()
        else//Availablefrequencies==empty()
        {// on choisit la meilleur fr�quence VALID

            //****************#################################""
        //----------------------
      if(trx.validFrequencies->empty()==false)
            {
                taille =trx.validFrequencies->size();
                vector<double> * veccost = new vector <double>(taille);
                  vector<double> * cost = new vector <double>(taille);
                if (taille>1)
                {
                    for(i=0 ;i < taille ; i++)//pour chaque fr�quence probable on evalue le cout
                {

                    victimFrequency =trx.validFrequencies->at(i);
                    //on �value la solution avec le nouveau couple : {victimTrx,victimFrequency}
                      veccost->at(i)=0.0;
                    cost->at(i)=0.0;
                    tempsol->PlanAffect->push_back({trx.trxID,victimFrequency});
                    //on �value la solution avec le nouveau couple : {victimTrx,victimFrequency}
                   int victimTrx1 = trx.trxID; int victimFrequency1 = trx.AvailableFrequencies->at(i);
                    for(j=0;j<tempsol->PlanAffect->size();j++)
                    {

                        victimTrx = tempsol->PlanAffect->at(j).first;
                        victimFrequency = tempsol->PlanAffect->at(j).second;
                       interfererTrx=tempsol->PlanAffect->at(j).first;
                        interfererFrequency=tempsol->PlanAffect->at(j).second;
                        if ( interfererTrx != victimTrx1)
                        {
                           // calculer le cout d interference
                            veccost->at(i)  = veccost->at(i)  + afpProblem->computeChannelInterference(victimFrequency1 ,interfererFrequency, victimTrx1, interfererTrx)+
                            afpProblem->computeChannelInterference(interfererFrequency,victimFrequency1 ,interfererTrx, victimTrx1);
                            //cout de separation
                           if(afpProblem->trxs[victimTrx1].sectorID == afpProblem->trxs[interfererTrx].sectorID)
                            {
                                //on teste si la contraite de separation co-secteur est respect�!!
                                if (abs (interfererFrequency-victimFrequency1)<3 )//contrainte co secteur viol�e
                                {
                                    cost->at(i) = cost->at(i) + 1.0;
                                }
                            }// secteur different
                            else
                            {
                                if(afpProblem->trxs[victimTrx1].siteID  == afpProblem->trxs[interfererTrx].siteID)
                                {
                        //on teste si la contrainte de separation co-site est respect�e!!
                                    if (abs (interfererFrequency-victimFrequency1)< 2)//contrainte co secteur viol�e
                                    {
                                        cost->at(i) = cost->at(i) + 1.0;
                                    }
                                }//
                            }
                        }

                    }// for(j=0 ;j < taille ; j++)//pour chaque fr�quence probable on evalue le cout
                    //.............................................................................
                    //.............................................................................
                    // enregister les couts dans le vecteur
                  //  cout << veccost->at(i) << veccost->at(i) << endl;
                    veccost->at(i) = veccost->at(i) + tempsol->PIObj ;
                    cost->at(i) = cost->at(i) + tempsol->PSObj ;
                    paircost.push_back({veccost->at(i),cost->at(i)});
                    //...................................................................
                    tempsol->PlanAffect->pop_back();//on retire le couple probable apres evaluation de cout et l avoir enregistr� dans veccost
                    // cout<<"frequence ::" <<trx.AvailableFrequencies->at(i)<<", son sout veccost[i] ==="<< veccost->at(i)<<endl;
                } //fortrx.AvailableFrequencies
                    //.............................................................................
                    //.......................................................................................
                    //rechercher l indexmin indice de la fr�quence dans available frequency qui a
                    // une distance minimal
                    //distance = abs(  paircost.first-paircost.second);
                    //..............................................................
                    //...................................................................................
                    //utiliser l equilibre de nash
                    double BestObjectivePI,CurrentObjectivePI;
                    double BestObjectivePS,CurrentObjectivePS;
                    //-------------------------------
                    //trouver BestObjectivePI et BestObjectivePS;
                    //cout << " paircost[0].first---" << paircost[0].first <<endl;
                    //cout << " paircost[0].second---" << paircost[0].second <<endl;
                    BestObjectivePI = paircost[0].first;
                    BestObjectivePS = paircost[0].second;
                    for(i=0;i<trx.validFrequencies->size();i++)
                    {
                        if(BestObjectivePI > paircost[i].first)
                        {
                            BestObjectivePI = paircost[i].first;
                        }
                        if(BestObjectivePS > paircost[i].second)
                        {
                            BestObjectivePS = paircost[i].second;
                        }
                    }
                    // trouver le meilleur couple
                    int indexNASHEbest;
                    indexNASHEbest = 0;
                    vector<double> NASHEJ;
                    double NASHEbest;
                    const int SizeNashVect = trx.validFrequencies->size();
                    // NASHEJ.reserve(SizeNashVect);
                    // cout << "SizeNashVect**** " << SizeNashVect <<endl;
                    // indexmin = 0;
                    double gama = 0.1;
                  //remplire le table de NAshj-------------------------------
            for( i = 0; i < trx.AvailableFrequencies->size();i++)
            {
                if (BestObjectivePS != 0)
                {
                    if(BestObjectivePI !=0 )
                    {
                        NASHEJ.push_back((paircost[i].first - BestObjectivePI)/BestObjectivePI+ (paircost[i].second - BestObjectivePS)/BestObjectivePS);
                    }
                    else
                    {
                         NASHEJ.push_back((paircost[i].first - BestObjectivePS)/BestObjectivePS);
                    }
                }
                else
                {
                    if(BestObjectivePI !=0 )
                    {
                        NASHEJ.push_back((paircost[i].first - BestObjectivePI)/BestObjectivePI);
                    }
                    else
                    {
                        NASHEJ.push_back(0);
                    }
                }
            }
            //-----trouver la meilleur valeur de NAsh (la plus petite)--------------------------
            //++++++++++++++++++++rechercher la valeur minimal dans un tableau nash si plus sieur valeur de nash sont egale
 //on choisit al�atoirement une variable  +++++
   vector < pair<int,double>  > paircostNash ;//pour sauvegarder la fr�quence, et sa valeur de nash
             paircostNash.reserve(NASHEJ.size());
    for(i = 0 ; i< NASHEJ.size(); i++)
    {
       paircostNash.push_back({trx.validFrequencies->at(i),NASHEJ.at(i)});
       //paircostNash.at(i).first = trx.AvailableFrequencies->at(i);
        //paircostNash.at(i).second = NASHEJ.at(i);
    }

    //------------------------------trier le tableau selon un ordre croissant  ---------
    sort(paircostNash.begin(),paircostNash.end(),my_cmpInfDoublePair);
    //-----------------------------------------------------
    //---------------------Rassembler les valeurs minimal �gales et choisir al�atoirement une------------------------------
    i = 0;     k = 0 ;
    for(i = 0 ; i < paircostNash.size(); i++)
    {
         double val = paircostNash.at(i).second;
         pair<int,double> pnextval;
         if((i+1) < paircostNash.size())
         {
            pnextval = paircostNash.at(i+1);
            double nextval = pnextval.second;
            // on copie les valeurs egales dans un tableau
            //cout<< "hiiii here " << endl;
            if( val == nextval )
            {
                k = k +1 ;//k contient le nombre de valeur �gale
               // cout<< "hiiii here " << endl;

            }
            else
            {
                i = paircostNash.size();
            }
         }
    }
    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    indexmin = rand() % (k+1);
     f = paircostNash.at(indexmin).first;
    // rechercher l indice de  f*************** ajout� le 25-4-2019
    int indexf;
    for(i = 0 ; i < trx.validFrequencies->size(); i++)
    {
        if(trx.validFrequencies->at(i) == f)
        {
            indexf = i;
            i = trx.validFrequencies->size();
        }
    }
     solution->PIObj = veccost->at(indexf);
     solution->PSObj = cost->at(indexf);
     //................................................................................                vector < pair<double,double>  >().swap(paircost) ;
       //vider la m�moire--vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
           // vector<double>().swap(NASHEJ);
            vector < pair<double,double>  >().swap(paircost) ;

             delete(veccost);
               delete(cost);
              delete(tempsol->PlanAffect);
                //vector<double> ().swap(NASHEJ);
              //  delete(tempsol);
 //vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
            //vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
            }//taille >1::pl
            else
            {
                if(taille==1)
                {
                    f=trx.validFrequencies->at(0);
                // cout<<" frequency choisit:lorsque la taille est 0"<<f<<endl;
                // cout<<"hii"<<endl;
                }
            }//taille == 1?!!
        }
        else//Availablefrequencies==empty()
        {
            cout<<" la liste des fr�quences valide est vide **"<<endl;
        }
            //******************
            //cout<<" la liste des fr�quences disponibles est vide **"<<endl;
        }
    break;
    }//case 4 : best frequency in term of NASH

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~END NASH
    case 10 :
    {

         int i,indexmin;
        Individual * tempsol =  new Individual();int tempfreq;
        tempsol = solution;
        //   tempsol->planCC=NULL;
        //LF comment: on traverse tte les fr�quence et on calcule le cout
        int victimFrequency,interfererFrequency;
        int victimTrx,interfererTrx;
        victimTrx = trx.trxID;
        //------utiliser ma fonction de calcul de cout
        tempsol=solution; int j;

        //on remplie planaffect pour accelerer la recherche
        tempsol->PlanAffect = new vector< pair<int,int> > ();
        for(i=0;i<tempsol->plan->size();i++)
        {
            if (tempsol->plan->at(i)!=-1)//si la case dans le plan n'est pas vide on remplie le planAffect
            {
                tempsol->PlanAffect->push_back({i,tempsol->plan->at(i)});
            }
        }
        //cout<<"   tempsol->PlanAffect->size()"<<   tempsol->PlanAffect->size()<<endl;
        //----------------------
        victimTrx=trx.trxID; int taille;
                   //..........................................................
            //..........................................................
            //vecteur pour enregistrer le couple de cout  interference, separation � la fois

              vector < pair<double,double>  > paircost;
               paircost.reserve(afpProblem->trxs.size());
            //.............................................................
            //....................................................
        //----------------------
        if(trx.AvailableFrequencies->empty()==false)
        {
           taille =trx.AvailableFrequencies->size();

            vector<double> * veccost = new vector <double>(taille);

            if (taille>1)
            {
                for(i=0 ;i < taille ; i++)//pour chaque fr�quence probable on evalue le cout
                {
                    victimFrequency =trx.AvailableFrequencies->at(i);
                    //tempsol->plan->at(victimTrx)=victimFrequency;
                    //veccost[i]=0.0;
                    // veccost->at(i) ;
                    veccost->at(i)=0.0;
                    //....................
                   paircost.push_back({0.0,0.0});
                    //.........................
                    //   veccost->at(0)=5.0;
                    // cout<<"veccost->size()"<<veccost->size()<<endl;
                    tempsol->PlanAffect->push_back({victimTrx,victimFrequency});
                    // tempsol->PlanAffect->size();
                    // cout<<"   tempsol->PlanAffect->size()"<<   tempsol->PlanAffect->size()<<endl;
                    //on �value la solution avec le nouveau couple : {victimTrx,victimFrequency}
                    double cost = 0.0;
                    for(j=0;j<tempsol->PlanAffect->size();j++)
                    {
                        interfererTrx=tempsol->PlanAffect->at(j).first;
                        interfererFrequency=tempsol->PlanAffect->at(j).second;
                        veccost->at(i) = veccost->at(i)+ afpProblem->computeChannelInterference(victimFrequency ,interfererFrequency, victimTrx,interfererTrx);
                        //PSPSPSPSPSPPSPSPSPSPSPSPSPSPSP
                        // calculer le cout de s�paration
                        if(victimTrx!=interfererTrx)
                          {if(trx.sectorID == afpProblem->trxs[tempsol->PlanAffect->at(j).first].sectorID )
                        {
                        //cout << "hiiiii i m here we are in the same sector !!!" << endl;
                            if(abs(victimFrequency - tempsol->PlanAffect->at(j).second ) < 3)//contrainte viol�e
                            {
                                // cout << "Oups we have violated co sector constraint !!" << endl;
                                cost = cost + 1.0;
                            }
                        }
                        else
                        {
                                      //cout << "Hiii we are not in the same  sector!!!" << endl;
                            if(trx.siteID == afpProblem->trxs[tempsol->PlanAffect->at(j).first].siteID )
                            {
                                         //cout << "hiiiii i m here we are in the same site!!!" << endl;
                                if(abs(victimFrequency - tempsol->PlanAffect->at(j).second ) < 2)//contrainte viol�e
                                {
                                    // cout << "Oups we have violated co site constraint !!" << endl;
                                    cost = cost + 1.0;
                                    // cout << " csite " << csite<<endl;
                                }

                            }//if(trx.siteID == afpProblem->trxs[tempsol->PlanAffect->at(j).first].siteID )

                        }//else on n est pas dans le meme site

                       //PSPSPSPSPSPSPSPSPSPSPSPSPSPSPSPSPSPSPSP
                    }}// for(i=0 ;i < taille ; i++)//pour chaque fr�quence probable on evalue le cout
                    //.............................................................................
                    // enregister les couts dans le vecteur

                    paircost[i].first = veccost->at(i);
                    paircost[i].second = cost;
                    //...................................................................
                    tempsol->PlanAffect->pop_back();//on retire le couple probable apres evaluation de cout et l avoir enregistr� dans veccost
                    // cout<<"frequence ::" <<trx.AvailableFrequencies->at(i)<<", son sout veccost[i] ==="<< veccost->at(i)<<endl;
                } //fortrx.AvailableFrequencies
              // cout <<  "paircost[0].first---------" << paircost[0].first <<endl;
             //  cout <<  "paircost[0].second ---------" << paircost[0].second <<endl;
              //  vecmin(veccost, indexmin);//indexmin:indice de la fr�quencence qui a la valeur minimale
                //.............................................................................


//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
     //DOMINANCE
                 //...................................................
                 //.....................................................
                // I . Retirer la non dominance pour chaque fr�quence
                // ....................................................
                //...................................................

                bool test = true; //je supose que la soluution est domiin�e et je vais tester si c est vrai
                int indexdominantf, NonDominantScore;
                indexdominantf = -1;
                vector < pair<int,int> > IndexesFreqsNonDominantes;
                 //(int,int) :: le premier enregistre l index de la fr�quence non dominante
                  //(int,int) :: le dexieme , combien de fois la fr�quence est non dominante
                IndexesFreqsNonDominantes.reserve(trx.AvailableFrequencies->size());
                for( i = 0; i < trx.AvailableFrequencies->size();i++)//la solution condidate est dans l indice i
                {
                  //dominance par rapport au premier joueur
                  NonDominantScore = 0 ;
                  //IndexesFreqsNonDominantes[i].first = i ;
                 // IndexesFreqsNonDominantes[i].second = 0;
                   for( j = 0; j < trx.AvailableFrequencies->size();j++)
                   {
                       if (i!=j)
                       {
                            // je te
                            if (paircost[i].first <= paircost[j].first) // on teste la non dominance par rapport au premier objectif
                            {
                                if (paircost[i].second < paircost[j].second)
                                {
                                     NonDominantScore =   NonDominantScore;                                   ;
                                }
                                 IndexesFreqsNonDominantes.push_back({i,NonDominantScore});
                            }//
                            else
                            {
                                if (paircost[i].second <= paircost[j].second) // on teste la non dominance par rapport au deuci�me objectif
                                {
                                     if (paircost[i].first < paircost[j].first)
                                    {
                                        NonDominantScore =   NonDominantScore + 1 ;                                   ;
                                    }
                                     IndexesFreqsNonDominantes.push_back({i,NonDominantScore});
                                }
                            }
                            //sauvegarder le score
                            //IndexesFreqsNonDominantes[i].second = NonDominantScore;

                        }//i!=j
                    }//fin j

                }//fin i
                //...................................................
                 //.....................................................
                // II . Trier le tableau de la non dominance selon un ordre croissant
                // ....................................................
                //...................................................
               // sort(IndexesFreqsNonDominantes.begin(),IndexesFreqsNonDominantes.end(),my_cmp);
                //la
                   // copier les solution trouver dans un vecteur avec son cout d separation qui
                vector < pair < int, double> > NonDominanteCost;
                NonDominanteCost.reserve(IndexesFreqsNonDominantes.size());
                for(i = 0; i < IndexesFreqsNonDominantes.size(); i++ )
                {
                    NonDominanteCost.push_back({IndexesFreqsNonDominantes[i].first, paircost[IndexesFreqsNonDominantes[i].first].second });
                }
                // trier le tableau selon un ordre d�croisant du cout et retirer la premi�re valeur dans NonDominanteCost


                sort(NonDominanteCost.begin(),NonDominanteCost.end(),my_cmpInfDoublePair);
                indexmin = NonDominanteCost.front().first;

     //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    // parmis les solution trouv�e IndexesFreqsDominantes dans r�cup�r�rer la  fr�quence qui a la plus petite valeur decout
    //cout << "IndexesFreqsDominantesPSPS.size()------- "<< IndexesFreqsNonDominantes.size() << endl;
    /*if (IndexesFreqsNonDominantes.empty() == false)
    {
        indexmin= 0 ;
        double costdom = veccost->at(IndexesFreqsNonDominantes[0]);
        cout <<" costdom ------------" <<costdom << endl;
        // chosir la fr�quence avec le pust petit cout
        int index ;
        for ( j= 0 ; j < IndexesFreqsNonDominantes.size() ; j++)
        {
            index = IndexesFreqsNonDominantes[j];
            if(costdom > veccost->at(index) );
            {
                indexmin = index ;
                costdom = veccost->at(index);
            }
        }
         cout << "indexmin***" << indexmin << endl;
    }
    else // si je trouve pas je r�cup�re la fr�quence qui a le plus petit cout
    {vecmin(veccost, indexmin);*/
   // vecmin(veccost, indexmin);
  // indexmin = IndexesFreqsNonDominantes[0].first ;
  //  cout << "noooooooooooooooo---" <<endl;

    //............................End dominance ..................................
    //..............................................................
    //................................................................................
    f=trx.AvailableFrequencies->at(indexmin);//indice de la fr�quence recherch�
    //--------------------- dominance available
    }//if (taille >1)
    else
    {
       if(taille==1) // la taille  == 1; je n ai qu'un choix
        {
            f=trx.AvailableFrequencies->at(0);
            // cout<<" frequency choisit:lorsque la taille est 0"<<f<<endl;
            // cout<<"hii"<<endl;
        }
    }//taille :.!=1
 }// Availablefrequencies is empty()
else//Availablefrequencies==empty() // aucune fr�quence n'est diponible j'utilise les fr�quence valides
        {// on choisit la meilleur fr�quence VALID

            //****************#################################""
        //----------------------
        if(trx.validFrequencies->empty()==false)
        {
            taille =trx.validFrequencies->size();
            vector<double> * veccost = new vector <double>(taille);
            if (taille>1)
            {
                for(i=0 ;i < taille ; i++)//pour chaque fr�quence probable on evalue le cout
                {
                    victimFrequency =trx.validFrequencies->at(i);
                    //tempsol->plan->at(victimTrx)=victimFrequency;
                    //veccost[i]=0.0;
                    // veccost->at(i) ;
                    veccost->at(i)=0.0;
                    //...................................
                   paircost.push_back({0.0,0.0});
                    double cost = 0.0;

                    //..........................
                    //   veccost->at(0)=5.0;
                    // cout<<"veccost->size()"<<veccost->size()<<endl;
                    tempsol->PlanAffect->push_back({victimTrx,victimFrequency});
                    // tempsol->PlanAffect->size();
                    // cout<<"   tempsol->PlanAffect->size()"<<   tempsol->PlanAffect->size()<<endl;
                    //on �value la solution avec le nouveau couple : {victimTrx,victimFrequency}
                    for(j=0;j<tempsol->PlanAffect->size();j++)
                    {
                        interfererTrx=tempsol->PlanAffect->at(j).first;
                        interfererFrequency=tempsol->PlanAffect->at(j).second;
                        veccost->at(i) = veccost->at(i)+afpProblem->computeChannelInterference(victimFrequency ,interfererFrequency, victimTrx,interfererTrx);

                     //PSPSPSPSPSPPSPSPSPSPSPSPSPSPSP
                        // calculer le cout de s�paration
                      if(victimTrx!=interfererTrx)
                      {if(trx.sectorID == afpProblem->trxs[tempsol->PlanAffect->at(j).first].sectorID )
                        {
                        //cout << "hiiiii i m here we are in the same sector !!!" << endl;
                            if(abs(victimFrequency - tempsol->PlanAffect->at(j).second ) < 3)//contrainte viol�e
                            {
                                // cout << "Oups we have violated co sector constraint !!" << endl;
                                cost = cost + 1.0;
                            }
                        }
                        else
                        {
                                      //cout << "Hiii we are not in the same  sector!!!" << endl;
                            if(trx.siteID == afpProblem->trxs[tempsol->PlanAffect->at(j).first].siteID )
                            {
                                         //cout << "hiiiii i m here we are in the same site!!!" << endl;
                                if(abs(victimFrequency - tempsol->PlanAffect->at(j).second ) < 2)//contrainte viol�e
                                {
                                    // cout << "Oups we have violated co site constraint !!" << endl;
                                    cost = cost + 1.0;
                                    // cout << " csite " << csite<<endl;
                                }

                            }//if(trx.siteID == afpProblem->trxs[tempsol->PlanAffect->at(j).first].siteID )

                        }//else on n est pas dans le meme site

                       //PSPSPSPSPSPSPSPSPSPSPSPSPSPSPSPSPSPSPSP

                    }}
                     //.............................................................................
                    // enregister les couts dans le vecteur

                    paircost[i].first = veccost->at(i);
                    paircost[i].second = cost ;
                    //...................................................................
                    tempsol->PlanAffect->pop_back();//on retire le couple probable apres evaluation de cout et l avoir enregistr� dans veccost
                    // cout<<"frequence ::" <<trx.AvailableFrequencies->at(i)<<", son sout veccost[i] ==="<< veccost->at(i)<<endl;
                } //fortrx.AvailableFrequencies
              //  vecmin(veccost, indexmin);//indexmin:indice de la fr�quencence qui a la valeur minimale
                  //.............................................................................
                //.......................................................................................
               //rechercher l indexmin indice de la fr�quence dans available frequency qui a
               // une distance minimal
               //distance = abs(  paircost.first-paircost.second);
          //..............................................................
                //...................................................................................

        //DOMINANCE


                 //...................................................
                 //.....................................................
                // I . Retirer la non dominance pour chaque fr�quence
                // ....................................................
                //...................................................

                bool test = true; //je supose que la soluution est domiin�e et je vais tester si c est vrai
                int indexdominantf, NonDominantScore;
                indexdominantf = -1;
                vector < pair<int,int> > IndexesFreqsNonDominantes;
                 //(int,int) :: le premier enregistre l index de la fr�quence non dominante
                  //(int,int) :: le dexieme , combien de fois la fr�quence est non dominante
                IndexesFreqsNonDominantes.reserve(trx.validFrequencies->size());
                for( i = 0; i < trx.validFrequencies->size();i++)//la solution condidate est dans l indice i
                {
                  //dominance par rapport au premier joueur
                  NonDominantScore = 0 ;
                  //IndexesFreqsNonDominantes[i].first = i ;
                 // IndexesFreqsNonDominantes[i].second = 0;
                   for( j = 0; j < trx.validFrequencies->size();j++)
                   {
                       if (i!=j)
                       {
                            // je te
                            if (paircost[i].first <= paircost[j].first) // on teste la non dominance par rapport au premier objectif
                            {
                                if (paircost[i].second < paircost[j].second)
                                {
                                     NonDominantScore =   NonDominantScore    ;                                   ;
                                }
                                     IndexesFreqsNonDominantes.push_back({i,NonDominantScore});
                            }//
                            else
                            {
                                if (paircost[i].second <= paircost[j].second) // on teste la non dominance par rapport au deuci�me objectif
                                {
                                     if (paircost[i].first < paircost[j].first)
                                    {
                                        NonDominantScore =   NonDominantScore + 1 ;                                   ;
                                    }
                                         IndexesFreqsNonDominantes.push_back({i,NonDominantScore});
                                }
                            }
                            //sauvegarder le score
                            //IndexesFreqsNonDominantes[i].second = NonDominantScore;

                        }//i!=j
                    }//fin j

                }//fin i
                //...................................................
                 //.....................................................
                // II . Trier le tableau de la non dominance selon un ordre croissant
                // ....................................................
                //...................................................
               // sort(IndexesFreqsNonDominantes.begin(),IndexesFreqsNonDominantes.end(),my_cmp);
                //la
                        // copier les solution trouver dans un vecteur avec son cout d separation qui
                vector < pair < int, double> > NonDominanteCost;
                NonDominanteCost.reserve(IndexesFreqsNonDominantes.size());
                for(i = 0; i < IndexesFreqsNonDominantes.size(); i++ )
                {
                    NonDominanteCost.push_back({IndexesFreqsNonDominantes[i].first, paircost[IndexesFreqsNonDominantes[i].first].second });
                }
                // trier le tableau selon un ordre d�croisant du cout et retirer la premi�re valeur dans NonDominanteCost


                sort(NonDominanteCost.begin(),NonDominanteCost.end(),my_cmpInfDoublePair);
                indexmin = NonDominanteCost.front().first;



                //..............................................................
                //...................................................................................
                f=trx.validFrequencies->at(indexmin);//indice de la fr�quence ayant un cout minimal,

            }//taille >1
            else
            {
                if(taille==1)
                {
                    f=trx.validFrequencies->at(0);
                // cout<<" frequency choisit:lorsque la taille est 0"<<f<<endl;
                // cout<<"hii"<<endl;
                }
            }//taille == 1?!!
        }
        else//Availablefrequencies==empty()
        {
            cout<<" la liste des fr�quences valide est vide **"<<endl;
        }
















            //******************
            //cout<<" la liste des fr�quences disponibles est vide **"<<endl;
        }

        break;
    }

 //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ FRONt PARETO Inspir�e ~~~~~~~~~~~~~~~~~~~~~~
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 case 5://strategy 5 choisir la meilleur fr�quence en terme Front parteo
    {
          int i,indexmin,j,k;
       // Individual * tempsol =  new Individual();
        int tempfreq;
        //��������������������������������� copier la solution dans tempsol ����������������������
        //���������������������������������������������������������������������������������������
        //tempsol = solution;
        //tempsol->plan = new vector <int>(solution->plan->size());
        //tempsol->planCC = new vector <double>(solution->planCC->size());
        solution->PlanAffect = new vector< pair<int,int> > ();
        // tempsol->PIObj = solution->PIObj;
        // tempsol->PSObj = solution->PSObj;
        for(i=0;i<solution->plan->size();i++)
        {
            //tempsol->plan->at(i) = solution->plan->at(i);
            //tempsol->planCC->at(i) = solution->planCC->at(i);
           // tempsol->PIObj = solution->PIObj;
            //tempsol->PSObj = solution->PSObj;
            if(solution->plan->at(i)!=-1)//si la case dans le plan n'est pas vide on remplie le planAffect
            {
                solution->PlanAffect->push_back({i,solution->plan->at(i)});
            }
        }

        //����������������������������������������������������������
        //���������������������������������������������������������������
        //   tempsol->planCC=NULL;
        //LF comment: on traverse tte les fr�quence et on calcule le cout
        int victimFrequency,interfererFrequency;
        int victimTrx,interfererTrx;
        victimTrx = trx.trxID;

        int taille;
        //..........................................................
        //..........................................................
        //vecteur pour enregistrer le couple de cout  interference, separation � la fois
        vector < pair<double,double>  > paircost ;
        //----------------------
        if(trx.AvailableFrequencies->empty()==false)
        {
           taille =trx.AvailableFrequencies->size();

            vector<double> * veccost = new vector <double>(taille);
                 vector<double> * cost = new vector <double>(taille);
            if (taille>1)
            {
                //paralleliser les traitements
                //#pragma omp parallel for
                for(i=0 ;i < taille ; i++)//pour chaque fr�quence probable on evalue le cout
                {

                    victimFrequency =trx.AvailableFrequencies->at(i);
                    veccost->at(i)=0.0;
                    cost->at(i)=0.0;
                    solution->PlanAffect->push_back({trx.trxID,victimFrequency});
                    //on �value la solution avec le nouveau couple : {victimTrx,victimFrequency}
                   int victimTrx1 = trx.trxID; int victimFrequency1 = trx.AvailableFrequencies->at(i);
                    for(j=0;j< solution->PlanAffect->size();j++)
                    {

                        victimTrx = solution->PlanAffect->at(j).first;
                        victimFrequency = solution->PlanAffect->at(j).second;
                       interfererTrx = solution->PlanAffect->at(j).first;
                        interfererFrequency = solution->PlanAffect->at(j).second;
                        if ( interfererTrx != victimTrx1)
                        {
                           // calculer le cout d interference
                            veccost->at(i)  = veccost->at(i)  + afpProblem->computeChannelInterference(victimFrequency1 ,interfererFrequency, victimTrx1, interfererTrx)+
                            afpProblem->computeChannelInterference(interfererFrequency,victimFrequency1 ,interfererTrx, victimTrx1);
                            //cout de separation
                           if(afpProblem->trxs[victimTrx1].sectorID == afpProblem->trxs[interfererTrx].sectorID)
                            {
                                //on teste si la contraite de separation co-secteur est respect�!!
                                if (abs (interfererFrequency-victimFrequency1)<3 )//contrainte co secteur viol�e
                                {
                                    cost->at(i) = cost->at(i) + 1.0;
                                }
                            }// secteur different
                            else
                            {
                                if(afpProblem->trxs[victimTrx1].siteID  == afpProblem->trxs[interfererTrx].siteID)
                                {
                        //on teste si la contrainte de separation co-site est respect�e!!
                                    if (abs (interfererFrequency-victimFrequency1)< 2)//contrainte co secteur viol�e
                                    {
                                        cost->at(i) = cost->at(i) + 1.0;
                                    }
                                }//
                            }
                        }

                    }// for(j=0 ;j < taille ; j++)//pour chaque fr�quence probable on evalue le cout
                    //.............................................................................
                    //.............................................................................
                    // enregister les couts dans le vecteur
                  //  cout << veccost->at(i) << veccost->at(i) << endl;
                    veccost->at(i) = veccost->at(i) + solution->PIObj ;
                    cost->at(i) = cost->at(i) + solution->PSObj ;
                    paircost.push_back({veccost->at(i),cost->at(i)});
                    //...................................................................
                    solution->PlanAffect->pop_back();//on retire le couple probable apres evaluation de cout et l avoir enregistr� dans veccost
                    // cout<<"frequence ::" <<trx.AvailableFrequencies->at(i)<<", son sout veccost[i] ==="<< veccost->at(i)<<endl;
                } //fortrx.AvailableFrequencies


 //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
     //DOMINANCE
   //
                 //...................................................
                 //.....................................................
                // I . Retirer la non dominance pour chaque fr�quence
                // ....................................................
                //...................................................

                //je supose que la soluution est domiin�e et je vais tester si c est vrai

                    //+++++++++++++Laidi modifi� +++++++++++++++++++++++++++++++++++
      //je supose que la soluution est domiin�e et je vais tester si c est vrai
                int  NonDominantScore, DominantScore;

                vector < pair<int,int> > IndexesFreqsNonDominantes;
                int flag1, flag2, index;
                double interCost;
                 //(int,int) :: le premier enregistre l index de la fr�quence non dominante
                  //(int,int) :: le dexieme , combien de fois la fr�quence est non dominante
                IndexesFreqsNonDominantes.reserve(trx.AvailableFrequencies->size());

                for( i = 0; i < trx.AvailableFrequencies->size();i++)//la solution condidate est dans l indice i
                {

                  DominantScore = 0 ;// pour compter le nombre de solution qui domine la solution courante

                   for( j = 0; j < trx.AvailableFrequencies->size();j++)
                   {
                        //Laidi ---

                                /*
                               flag1 = 0;
                               flag2 = 0;
                               if (paircost[i].first >= paircost[j].first)
                                flag1++;

                               if (paircost[i].first > paircost[j].first)
                                flag2++;

                               if (paircost[i].second >= paircost[j].second)
                                flag1++;

                               if (paircost[i].second > paircost[j].second)
                                flag2++;


                          if (flag1 >= 2 && flag2>=1){ //pour tester la condition de dominance pour nos deux objectifs
          //array_domination_count[i] = array_domination_count[i] + 1; // lpour compter le nbr de solution qui domine la solution i
                              DominantScore= DominantScore+1; //pour la solution 'i'
                           }

                        */
                             /*if (paircost[i].first > paircost[j].first)
                                   {
                                      if (paircost[i].second >= paircost[j].second)
                                       DominantScore   = DominantScore +   1; //pour la solution 'i'
                                   }


                                    if (paircost[i].second > paircost[j].second)
                                        {
                                            if(paircost[i].first >= paircost[j].first)
                                            DominantScore   = DominantScore +   1; //pour la solution 'i'
                                        }*/
                                        if(i!=j)
                                       {


                         if (!((paircost[i].first <= paircost[j].first) && (paircost[i].second <= paircost[j].second)))
                             DominantScore   = DominantScore +   1;
                                       }

                 }

                     /* if (DominantScore == 0)
                  IndexesFreqsNonDominantes.push_back({i,paircost[i].second}); // contient l'indice de la fr�quence frqq ainsi que le cout d'interf�rences
                */
                //j ins�re pour chque solution f son score
                 IndexesFreqsNonDominantes.push_back({i,DominantScore});
                }//fin i
               // cout << " la taille des frqs non dominee PI == " << IndexesFreqsNonDominantes.size() << endl ;
                //+++++++++++++++++++++++++++++++++++++++Afficher paircost

           //++++++++++++++++++++++++++++++++++++++++++++++++++++++++

                //...................................................
                 //.....................................................
                // II . Trier le tableau de la non dominance selon un ordre croissant
                // ....................................................
                //...................................................
              //  sort(IndexesFreqsNonDominantes.begin(),IndexesFreqsNonDominantes.end(),my_cmp);
              //  cout << "  IndexesFreqsNonDominantes.size() ****"<< IndexesFreqsNonDominantes.size() << endl;


                // copier les solution trouver dans un vecteur avec son cout d interferqunce qui
               /* vector < pair < int, double> > NonDominanteCost;//contient l indice des valeur non domin�e et le cout
                NonDominanteCost.reserve(IndexesFreqsNonDominantes.size());
                for(i = 0; i < IndexesFreqsNonDominantes.size(); i++ )
                {
                    NonDominanteCost.push_back({IndexesFreqsNonDominantes[i].first, paircost[IndexesFreqsNonDominantes[i].first].first });
                }*/
                // trier le tableau selon un ordre d�croisant du cout et retirer la premi�re valeur
              // cout << " ���������IndexesFreqsNonDominantes.size() " << IndexesFreqsNonDominantes.size() <<endl;

              if (IndexesFreqsNonDominantes.size()!= 0)
              {
                  //cout << " la taille du vect solutions non dom PS == " << IndexesFreqsNonDominantes.size()<< endl;
                 // sort(IndexesFreqsNonDominantes.begin(),IndexesFreqsNonDominantes.end(),my_cmpInfDoublePair);//trier selon un ordre croissant de cout
                sort(IndexesFreqsNonDominantes.begin(),IndexesFreqsNonDominantes.end(),my_cmpInf);
                //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                //~~~~~~~~~~~~~~~~~~~~~~~~~~~si plusieurs fr�queences  non domlinates ont le meme cout on choisit
                // al�atoirement une
                //---------------------------------------------------
                i = 0;     k = 0 ;
                for(i = 0 ; i < IndexesFreqsNonDominantes.size(); i++)
                {
                    //double val = IndexesFreqsNonDominantes.at(i).second;
                    int val = IndexesFreqsNonDominantes.at(i).second;
                    //pair<int,double> pnextval;
                    pair<int,int> pnextval;
                    if((i+1) < IndexesFreqsNonDominantes.size())
                    {
                        pnextval = IndexesFreqsNonDominantes.at(i+1);
                        //double nextval = pnextval.second;
                        int nextval = pnextval.second;
                        // on copie les valeurs egales dans un tableau
                        //cout<< "hiiii here " << endl;
                        if( val == nextval )
                        {
                            k = k +1 ;//k contient le nombre de valeur �gale
                            // cout<< "hiiii here " << endl;

                        }
                        else
                        {
                            i = IndexesFreqsNonDominantes.size();
                        }
                    }
                }
                //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                int indice ;
                indice = rand() % (k+1);// coisir une parmi les "n" premier
              //  cout << " k �����������" << k << endl;
                indexmin = IndexesFreqsNonDominantes.at(indice).first;// r�cup�ration de l'indice de la fr�quence
              }
               else// il n y a aucune valeur dans le front pareto
                {
                        cout << " taille 0000000000000000 " << endl;
                         vecmin(cost, indexmin);//indexmin:indice de la fr�quencence qui a la valeur minimale


            }


    //............................End dominance ..................................
    //..............................................................
    //................................................................................
    f=trx.AvailableFrequencies->at(indexmin);//indice de la fr�quence recherch�
     solution->PIObj = veccost->at(indexmin);
      solution->PSObj = cost->at(indexmin);
      //delete(tempsol->PlanAffect);
       vector < pair<double,double>  >().swap(paircost) ;
    vector < pair<int,int> > ().swap(IndexesFreqsNonDominantes);
    delete(veccost);
    delete(cost);
    //delete(tempsol->PlanAffect);
    delete(solution->PlanAffect);
    //--------------------- dominance available
    }//if (taille >1)
    else
    {
       if(taille==1) // la taille  == 1; je n ai qu'un choix
        {
            f=trx.AvailableFrequencies->at(0);
            // cout<<" frequency choisit:lorsque la taille est 0"<<f<<endl;
            // cout<<"hii"<<endl;
            delete(solution->PlanAffect);
        }
    }//taille :.!=1
 }// Availablefrequencies is empty()
else//Availablefrequencies==empty() // aucune fr�quence n'est diponible j'utilise les fr�quence valides
        {// on choisit la meilleur fr�quence VALID

            //****************#################################""
        //----------------------
        if(trx.validFrequencies->empty()==false)
        {
            taille =trx.validFrequencies->size();
            vector<double> * veccost = new vector <double>(taille);
                vector<double> * cost = new vector <double>(taille);
            if (taille>1)
            {
                for(i=0 ;i < taille ; i++)//pour chaque fr�quence probable on evalue le cout
                {
                    victimFrequency =trx.validFrequencies->at(i);
                     veccost->at(i)=0.0;
                    cost->at(i)=0.0;
                    solution->PlanAffect->push_back({trx.trxID,victimFrequency});
                    //on �value la solution avec le nouveau couple : {victimTrx,victimFrequency}
                   int victimTrx1 = trx.trxID; int victimFrequency1 = trx.AvailableFrequencies->at(i);
                    for(j=0;j< solution->PlanAffect->size();j++)
                    {

                        victimTrx = solution->PlanAffect->at(j).first;
                        victimFrequency = solution->PlanAffect->at(j).second;
                       interfererTrx = solution->PlanAffect->at(j).first;
                        interfererFrequency = solution->PlanAffect->at(j).second;
                        if ( interfererTrx != victimTrx1)
                        {
                           // calculer le cout d interference
                            veccost->at(i)  = veccost->at(i)  + afpProblem->computeChannelInterference(victimFrequency1 ,interfererFrequency, victimTrx1, interfererTrx)+
                            afpProblem->computeChannelInterference(interfererFrequency,victimFrequency1 ,interfererTrx, victimTrx1);
                            //cout de separation
                           if(afpProblem->trxs[victimTrx1].sectorID == afpProblem->trxs[interfererTrx].sectorID)
                            {
                                //on teste si la contraite de separation co-secteur est respect�!!
                                if (abs (interfererFrequency-victimFrequency1)<3 )//contrainte co secteur viol�e
                                {
                                    cost->at(i) = cost->at(i) + 1.0;
                                }
                            }// secteur different
                            else
                            {
                                if(afpProblem->trxs[victimTrx1].siteID  == afpProblem->trxs[interfererTrx].siteID)
                                {
                        //on teste si la contrainte de separation co-site est respect�e!!
                                    if (abs (interfererFrequency-victimFrequency1)< 2)//contrainte co secteur viol�e
                                    {
                                        cost->at(i) = cost->at(i) + 1.0;
                                    }
                                }//
                            }
                        }

                    }// for(j=0 ;j < taille ; j++)//pour chaque fr�quence probable on evalue le cout
                    //.............................................................................
                    //.............................................................................
                    // enregister les couts dans le vecteur
                  //  cout << veccost->at(i) << veccost->at(i) << endl;
                    veccost->at(i) = veccost->at(i) + solution->PIObj ;
                    cost->at(i) = cost->at(i) + solution->PSObj ;
                    paircost.push_back({veccost->at(i),cost->at(i)});
                    //...................................................................
                    solution->PlanAffect->pop_back();//on retire le couple probable apres evaluation de cout et l avoir enregistr� dans veccost
                    // cout<<"frequence ::" <<trx.AvailableFrequencies->at(i)<<", son sout veccost[i] ==="<< veccost->at(i)<<endl;
                } //fortrx.Av
          //..............................................................
                //...................................................................................

        //DOMINANCE


                 //...................................................
                 //.....................................................
                // I . Retirer la non dominance pour chaque fr�quence
                // ....................................................
                //...................................................

                 int  DominantScore;

                vector < pair<int,int> > IndexesFreqsNonDominantes;
                 //(int,int) :: le premier enregistre l index de la fr�quence non dominante
                  //(int,int) :: le dexieme , combien de fois la fr�quence est non dominante
                IndexesFreqsNonDominantes.reserve(trx.validFrequencies->size());
        //+++++++++++++Laidi modifi� +++++++++++++++++++++++++++++++++++
          for( i = 0; i < trx.AvailableFrequencies->size();i++)//la solution condidate est dans l indice i
                {

                  DominantScore = 0 ;// pour compter le nombre de solution qui domine la solution courante

                  for( j = i+1; j < trx.AvailableFrequencies->size() ;j++)
                   {
                       if (i!=j)
                       {

                           if (paircost[i].first > paircost[j].first) // on teste la dominance par rapport au premier objectif
                            {
                                // on ne peut pas juger on test par rapport au deuxime obj
                                if (paircost[i].second > paircost[j].second)
                                         {

                                                  //on est sur qu elle est dominante
                                                DominantScore    =   DominantScore+1 ;


                                         }
                                         else
                                         {
                                             if(paircost[i].first >= paircost[j].first)
                                              {
                                                    DominantScore    =   DominantScore+1 ;
                                              }
                                         }

                            }
                            else
                            {
                                if (paircost[i].second >= paircost[j].second)
                                    {
                                        DominantScore    =   DominantScore+1 ;
                                    }

                            }


                        }//i!=j
                    }//fin j

						if (DominantScore==0)// pour s'assurer que la solution "i" est non dominée
                      {
                        IndexesFreqsNonDominantes.push_back({i,paircost[i].first});// on insert l'index de la solution et son cout d'interférences
                      }
                       // cout << "la solution " << i << " est dominee par  " << DominantScore << " autres solutions" << endl;
                }//fin i

            //cout <<"IndexesFreqsNonDominantes.size()PIII  "<< IndexesFreqsNonDominantes.size() <<endl;*/
                //----------------------------------------------------------------------
                 //+++++++++++++ sol par sol +++++++++++++++++++++++++++++++++++
                 //++++++++++++++++++ tout les sol
                  int  nondominancescore;
                  //cout << "trx.AvailableFrequencies->size()++++ "<< trx.AvailableFrequencies->size() <<endl;

                      for( i = 0; i < trx.validFrequencies->size();i++)//la solution condidate est dans l indice i
                {

                  nondominancescore = 0 ;// pour compter le nombre de solution qui domine la solution courante

                   for( j = 0; j < trx.AvailableFrequencies->size() ;j++)
                   {

                       if (i!=j)
                       {

                                   if (paircost[i].first <= paircost[j].first)  // on teste la dominance par rapport au deuciÃ¨me objectif
                                    {
                                          if (paircost[i].second < paircost[j].second)

                                        {
                                            IndexesFreqsNonDominantes.push_back({i,paircost[i].first});

                                            nondominancescore = nondominancescore + 1;
                                            }
                                        }


                                    //--- j insere le deuxi�me obj
                                  /* else
                                    {
                                         if (paircost[i].second <= paircost[j].second) // teste la dominance par rapport au deuciÃ¨me objectif
                                        {
                                                if (paircost[i].first < paircost[j].first) // on
                                                {
                                                    IndexesFreqsNonDominantes.push_back({i,paircost[i].first});
                                            //au deuxieme obj

                                                nondominancescore = nondominancescore+1;
                                                }
                                            //}
                                        }
                                    }*/

                       }//i!=j
                   }//fin j
                   /*  if (nondominancescore > (trx.AvailableFrequencies->size() - 2 ))
                  IndexesFreqsNonDominantes.push_back({i,paircost[i].first});*/

              }//fin i
            // cout <<"IndexesFreqsNonDominantes.size()PIII  "<< IndexesFreqsNonDominantes.size() <<endl;



                //...................................................
                 //.....................................................
                // II . Trier le tableau de la non dominance selon un ordre croissant si la liste n est pas vide
                // ....................................................
                //...................................................
              //  sort(IndexesFreqsNonDominantes.begin(),IndexesFreqsNonDominantes.end(),my_cmp);
             // cout << "  IndexesFreqsNonDominantes.size() ****"<< IndexesFreqsNonDominantes.size() << endl;


                // copier les solution trouver dans un vecteur avec son cout d interferqunce qui
                if (IndexesFreqsNonDominantes.size()!= 0 )
                {
                    /*vector < pair < int, double> > NonDominanteCost;
                    NonDominanteCost.reserve(IndexesFreqsNonDominantes.size());
                    for(i = 0; i < IndexesFreqsNonDominantes.size(); i++ )
                    {
                        NonDominanteCost.push_back({IndexesFreqsNonDominantes[i].first, paircost[IndexesFreqsNonDominantes[i].first].first });
                    }*/
                // trier le tableau selon un ordre d�croisant du cout et retirer la premi�re valeur
                    sort(IndexesFreqsNonDominantes.begin(),IndexesFreqsNonDominantes.end(),my_cmpInfDoublePair);
                   // indexmin = IndexesFreqsNonDominantes.front().first;
                   //si des valeur de cout �gale on choisit al�atoirement parmi ces valeur
                   //+++++++++++++++++++++++++++++++++++++++++++
                   k=0;
                   for(i = 0 ; i < IndexesFreqsNonDominantes.size(); i++)
                    {
                        double val = IndexesFreqsNonDominantes.at(i).second;
                        pair<int,double> pnextval;
                        if((i+1) < IndexesFreqsNonDominantes.size())
                        {
                            pnextval = IndexesFreqsNonDominantes.at(i+1);
                            double nextval = pnextval.second;
                            // on copie les valeurs egales dans un tableau
                            //cout<< "hiiii here " << endl;
                            if( val == nextval )
                            {
                                k = k +1 ;//k contient le nombre de valeur �gale
                                // cout<< "hiiii here " << endl;
                            }
                            else
                            {
                                i = IndexesFreqsNonDominantes.size();
                            }
                        }
                    }
    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                    int indexf = rand() % (k+1);
                    indexmin = IndexesFreqsNonDominantes.at(indexf).first;

                }
                else
                {
                     vecmin(veccost, indexmin);//indexmin:indice de la fr�quencence qui a la valeur minimale
                }

                //................................................................................

//--------------------- dominance available
                //..............................................................
                //...................................................................................

    //vider la m�moire--vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
    vector < pair<double,double>  >().swap(paircost) ;
    delete(veccost);
    delete(solution->PlanAffect);
                //..............................................................
                //...................................................................................
                f=trx.validFrequencies->at(indexmin);//indice de la fr�quence ayant un cout minimal,

    //+++++++++++++++++++++++++++++++

            }//taille >1
            else
            {
                if(taille==1)
                {
                    f=trx.validFrequencies->at(0);
                // cout<<" frequency choisit:lorsque la taille est 0"<<f<<endl;
                // cout<<"hii"<<endl;
                }
            }//taille == 1?!!
        }
        else//Availablefrequencies==empty()
        {
            cout<<" la liste des fr�quences valide est vide **"<<endl;
        }
















            //******************
            //cout<<" la liste des fr�quences disponibles est vide **"<<endl;
        }
    break;
    }//case 5  : best frequency Front pareto
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ FRONt PARETO PUUUUUUUUUUUURE ~~~~~~~~~~~~~~~~~~~~~~
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   case  550://strategy 5 choisir la meilleur fr�quence en terme Front parteo
    {
          int i,indexmin,j,k;
       // Individual * tempsol =  new Individual();
        int tempfreq;
        //��������������������������������� copier la solution dans tempsol ����������������������
        //���������������������������������������������������������������������������������������
        //tempsol = solution;
        //tempsol->plan = new vector <int>(solution->plan->size());
        //tempsol->planCC = new vector <double>(solution->planCC->size());
        solution->PlanAffect = new vector< pair<int,int> > ();
        // tempsol->PIObj = solution->PIObj;
        // tempsol->PSObj = solution->PSObj;
        for(i=0;i<solution->plan->size();i++)
        {
            //tempsol->plan->at(i) = solution->plan->at(i);
            //tempsol->planCC->at(i) = solution->planCC->at(i);
           // tempsol->PIObj = solution->PIObj;
            //tempsol->PSObj = solution->PSObj;
            if(solution->plan->at(i)!=-1)//si la case dans le plan n'est pas vide on remplie le planAffect
            {
                solution->PlanAffect->push_back({i,solution->plan->at(i)});
            }
        }

        //����������������������������������������������������������
        //���������������������������������������������������������������
        //   tempsol->planCC=NULL;
        //LF comment: on traverse tte les fr�quence et on calcule le cout
        int victimFrequency,interfererFrequency;
        int victimTrx,interfererTrx;
        victimTrx = trx.trxID;

        int taille;
        //..........................................................
        //..........................................................
        //vecteur pour enregistrer le couple de cout  interference, separation � la fois
        vector < pair<double,double>  > paircost ;
        //----------------------
        if(trx.AvailableFrequencies->empty()==false)
        {
           taille =trx.AvailableFrequencies->size();

            vector<double> * veccost = new vector <double>(taille);
                 vector<double> * cost = new vector <double>(taille);

            if (taille>1)
            {
                   //paralleliser les tratements
                    //#pragma omp parallel for
                for(i=0 ;i < taille ; i++)//pour chaque fr�quence probable on evalue le cout
                {

                    victimFrequency =trx.AvailableFrequencies->at(i);
                    veccost->at(i)=0.0;
                    cost->at(i)=0.0;
                    solution->PlanAffect->push_back({trx.trxID,victimFrequency});
                    //on �value la solution avec le nouveau couple : {victimTrx,victimFrequency}
                   int victimTrx1 = trx.trxID; int victimFrequency1 = trx.AvailableFrequencies->at(i);
                    for(j=0;j< solution->PlanAffect->size();j++)
                    {

                        victimTrx = solution->PlanAffect->at(j).first;
                        victimFrequency = solution->PlanAffect->at(j).second;
                       interfererTrx = solution->PlanAffect->at(j).first;
                        interfererFrequency = solution->PlanAffect->at(j).second;
                        if ( interfererTrx != victimTrx1)
                        {
                           // calculer le cout d interference
                            veccost->at(i)  = veccost->at(i)  + afpProblem->computeChannelInterference(victimFrequency1 ,interfererFrequency, victimTrx1, interfererTrx)+
                            afpProblem->computeChannelInterference(interfererFrequency,victimFrequency1 ,interfererTrx, victimTrx1);
                            //cout de separation
                           if(afpProblem->trxs[victimTrx1].sectorID == afpProblem->trxs[interfererTrx].sectorID)
                            {
                                //on teste si la contraite de separation co-secteur est respect�!!
                                if (abs (interfererFrequency-victimFrequency1)<3 )//contrainte co secteur viol�e
                                {
                                    cost->at(i) = cost->at(i) + 1.0;
                                }
                            }// secteur different
                            else
                            {
                                if(afpProblem->trxs[victimTrx1].siteID  == afpProblem->trxs[interfererTrx].siteID)
                                {
                        //on teste si la contrainte de separation co-site est respect�e!!
                                    if (abs (interfererFrequency-victimFrequency1)< 2)//contrainte co secteur viol�e
                                    {
                                        cost->at(i) = cost->at(i) + 1.0;
                                    }
                                }//
                            }
                        }

                    }// for(j=0 ;j < taille ; j++)//pour chaque fr�quence probable on evalue le cout
                    //.............................................................................
                    //.............................................................................
                    // enregister les couts dans le vecteur
                  //  cout << veccost->at(i) << veccost->at(i) << endl;
                    veccost->at(i) = veccost->at(i) + solution->PIObj ;
                    cost->at(i) = cost->at(i) + solution->PSObj ;
                    paircost.push_back({veccost->at(i),cost->at(i)});
                    //...................................................................
                    solution->PlanAffect->pop_back();//on retire le couple probable apres evaluation de cout et l avoir enregistr� dans veccost
                    // cout<<"frequence ::" <<trx.AvailableFrequencies->at(i)<<", son sout veccost[i] ==="<< veccost->at(i)<<endl;
                } //fortrx.AvailableFrequencies


 //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
     //DOMINANCE
   //
                 //...................................................
                 //.....................................................
                // I . Retirer la non dominance pour chaque fr�quence
                // ....................................................
                //...................................................

                //je supose que la soluution est domiin�e et je vais tester si c est vrai

                    //+++++++++++++Laidi modifi� +++++++++++++++++++++++++++++++++++
      //je supose que la soluution est domiin�e et je vais tester si c est vrai
            int rank;
  int counter;
  int dominantScore;
  int temp = 0;
  rank = 1;
  vector < pair<int,double> > IndexesFreqsNonDominantes;
    IndexesFreqsNonDominantes.reserve(paircost.size());
    int taille=paircost.size();
    int array_rank[paircost.size()];
    counter =paircost.size();


    for (int i=0; i<paircost.size(); i++)
    {
      dominantScore=0;

	  for (int j=0; j<paircost.size(); j++)
	  {
        if (i!=j)
        {

            if ((paircost[i].first>=paircost[j].first && paircost[i].second>paircost[j].second) || (paircost[i].second>=paircost[j].second && paircost[i].first>paircost[j].first))
            {
          //  array_domination_count[i] = array_domination_count[i] + 1;
            dominantScore=dominantScore+1;// on a trouv� j qui domine i ;
            }
        }//i!=j
       } //fin j
		if (dominantScore==0)
        {
          // indices.push_back(i); // pour sauvgarder les indices des solution non dominées dans la nouvelle population
           IndexesFreqsNonDominantes.push_back({i,paircost[i].second});
        }
	}//fin i



              if (IndexesFreqsNonDominantes.size()!= 0)
              {
                  //cout << " la taille du vect solutions non dom PS == " << IndexesFreqsNonDominantes.size()<< endl;
                 // sort(IndexesFreqsNonDominantes.begin(),IndexesFreqsNonDominantes.end(),my_cmpInfDoublePair);//trier selon un ordre croissant de cout
                sort(IndexesFreqsNonDominantes.begin(),IndexesFreqsNonDominantes.end(),my_cmpInfDoublePair);
                //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                //~~~~~~~~~~~~~~~~~~~~~~~~~~~si plusieurs fr�queences  non domlinates ont le meme cout on choisit
                // al�atoirement une
                //---------------------------------------------------
                i = 0;     k = 0 ;
                //------------------------------------
                for(i = 0 ; i < IndexesFreqsNonDominantes.size(); i++)
                {
                    //double val = IndexesFreqsNonDominantes.at(i).second;
                    double val = IndexesFreqsNonDominantes.at(i).second;
                    //pair<int,double> pnextval;
                    pair<int,double> pnextval;
                    if((i+1) < IndexesFreqsNonDominantes.size())
                    {
                        pnextval = IndexesFreqsNonDominantes.at(i+1);
                        //double nextval = pnextval.second;
                        double nextval = pnextval.second;
                        // on copie les valeurs egales dans un tableau
                        //cout<< "hiiii here " << endl;
                        if( val == nextval )
                        {
                            k = k +1 ;//k contient le nombre de valeur �gale
                        }
                        else
                        {
                            i = IndexesFreqsNonDominantes.size();
                        }
                    }
                }
                int indice ;
                indice = rand() % (k+1);// coisir une parmi les "n" premier
                indexmin = IndexesFreqsNonDominantes.at(indice).first;// r�cup�ration de l'indice de la fr�quence
               // cout << "k ������������������" << k << endl;
              }
               else// il n y a aucune valeur dans le front pareto
               {
                 //cout << " taille 0000000000000000 " << endl;
                 // vecmin(cost, indexmin);//indexmin:indice de la fr�quencence qui a la valeur minimale
                 StrategyFreq = 2;//3 : ecart, 6: hv , 2 : minimum cost
                 PSChooseFrequency(instance,StrategyFreq,trx,f,solution,afpProblem);
                 return;

               }
    //............................End dominance ......................................
    //................................................................................
    //................................................................................
    f=trx.AvailableFrequencies->at(indexmin);//indice de la fr�quence recherch�
    solution->PIObj = veccost->at(indexmin);
    solution->PSObj = cost->at(indexmin);
    solution->planCC->at(trx.trxID).first = solution->PIObj;
    solution->planCC->at(trx.trxID).second = solution->PSObj;
    //delete(tempsol->PlanAffect);
    vector < pair<double,double> > ().swap(paircost) ;
    vector < pair<int,double> > ().swap(IndexesFreqsNonDominantes);
    delete(veccost);
    delete(cost);
    //delete(tempsol->PlanAffect);
    delete(solution->PlanAffect);
    //--------------------- dominance available
    }//if (taille >1)
    else
    {
       if(taille==1) // la taille  == 1; je n ai qu'un choix
        {
            f=trx.AvailableFrequencies->at(0);
            // cout<<" frequency choisit:lorsque la taille est 0"<<f<<endl;
            // cout<<"hii"<<endl;
            delete(solution->PlanAffect);
        }
    }//taille :.!=1
 }// Availablefrequencies is empty()
else//Availablefrequencies==empty() // aucune fr�quence n'est diponible j'utilise les fr�quence valides
        {// on choisit la meilleur fr�quence VALID

            //****************#################################""
        //----------------------
        if(trx.validFrequencies->empty()==false)
        {
            taille =trx.validFrequencies->size();
            vector<double> * veccost = new vector <double>(taille);
                vector<double> * cost = new vector <double>(taille);
            if (taille>1)
            {
                for(i=0 ;i < taille ; i++)//pour chaque fr�quence probable on evalue le cout
                {
                    victimFrequency =trx.validFrequencies->at(i);
                     veccost->at(i)=0.0;
                    cost->at(i)=0.0;
                    solution->PlanAffect->push_back({trx.trxID,victimFrequency});
                    //on �value la solution avec le nouveau couple : {victimTrx,victimFrequency}
                   int victimTrx1 = trx.trxID; int victimFrequency1 = trx.AvailableFrequencies->at(i);
                    for(j=0;j< solution->PlanAffect->size();j++)
                    {

                        victimTrx = solution->PlanAffect->at(j).first;
                        victimFrequency = solution->PlanAffect->at(j).second;
                       interfererTrx = solution->PlanAffect->at(j).first;
                        interfererFrequency = solution->PlanAffect->at(j).second;
                        if ( interfererTrx != victimTrx1)
                        {
                           // calculer le cout d interference
                            veccost->at(i)  = veccost->at(i)  + afpProblem->computeChannelInterference(victimFrequency1 ,interfererFrequency, victimTrx1, interfererTrx)+
                            afpProblem->computeChannelInterference(interfererFrequency,victimFrequency1 ,interfererTrx, victimTrx1);
                            //cout de separation
                           if(afpProblem->trxs[victimTrx1].sectorID == afpProblem->trxs[interfererTrx].sectorID)
                            {
                                //on teste si la contraite de separation co-secteur est respect�!!
                                if (abs (interfererFrequency-victimFrequency1)<3 )//contrainte co secteur viol�e
                                {
                                    cost->at(i) = cost->at(i) + 1.0;
                                }
                            }// secteur different
                            else
                            {
                                if(afpProblem->trxs[victimTrx1].siteID  == afpProblem->trxs[interfererTrx].siteID)
                                {
                        //on teste si la contrainte de separation co-site est respect�e!!
                                    if (abs (interfererFrequency-victimFrequency1)< 2)//contrainte co secteur viol�e
                                    {
                                        cost->at(i) = cost->at(i) + 1.0;
                                    }
                                }//
                            }
                        }

                    }// for(j=0 ;j < taille ; j++)//pour chaque fr�quence probable on evalue le cout
                    //.............................................................................
                    //.............................................................................
                    // enregister les couts dans le vecteur
                  //  cout << veccost->at(i) << veccost->at(i) << endl;
                    veccost->at(i) = veccost->at(i) + solution->PIObj ;
                    cost->at(i) = cost->at(i) + solution->PSObj ;
                    paircost.push_back({veccost->at(i),cost->at(i)});
                    //...................................................................
                    solution->PlanAffect->pop_back();//on retire le couple probable apres evaluation de cout et l avoir enregistr� dans veccost
                    // cout<<"frequence ::" <<trx.AvailableFrequencies->at(i)<<", son sout veccost[i] ==="<< veccost->at(i)<<endl;
                } //fortrx.Av
          //..............................................................
                //...................................................................................

        //DOMINANCE


                 //...................................................
                 //.....................................................
                // I . Retirer la non dominance pour chaque fr�quence
                // ....................................................
                //...................................................

                 int  DominantScore;

                vector < pair<int,int> > IndexesFreqsNonDominantes;
                 //(int,int) :: le premier enregistre l index de la fr�quence non dominante
                  //(int,int) :: le dexieme , combien de fois la fr�quence est non dominante
                IndexesFreqsNonDominantes.reserve(trx.validFrequencies->size());
        //+++++++++++++Laidi modifi� +++++++++++++++++++++++++++++++++++
          for( i = 0; i < trx.AvailableFrequencies->size();i++)//la solution condidate est dans l indice i
                {

                  DominantScore = 0 ;// pour compter le nombre de solution qui domine la solution courante

                  for( j = i+1; j < trx.AvailableFrequencies->size() ;j++)
                   {
                       if (i!=j)
                       {

                           if (paircost[i].first > paircost[j].first) // on teste la dominance par rapport au premier objectif
                            {
                                // on ne peut pas juger on test par rapport au deuxime obj
                                if (paircost[i].second > paircost[j].second)
                                         {

                                                  //on est sur qu elle est dominante
                                                DominantScore    =   DominantScore+1 ;


                                         }
                                         else
                                         {
                                             if(paircost[i].first >= paircost[j].first)
                                              {
                                                    DominantScore    =   DominantScore+1 ;
                                              }
                                         }

                            }
                            else
                            {
                                if (paircost[i].second >= paircost[j].second)
                                    {
                                        DominantScore    =   DominantScore+1 ;
                                    }

                            }


                        }//i!=j
                    }//fin j

						if (DominantScore==0)// pour s'assurer que la solution "i" est non dominée
                      {
                        IndexesFreqsNonDominantes.push_back({i,paircost[i].first});// on insert l'index de la solution et son cout d'interférences
                      }
                       // cout << "la solution " << i << " est dominee par  " << DominantScore << " autres solutions" << endl;
                }//fin i

            //cout <<"IndexesFreqsNonDominantes.size()PIII  "<< IndexesFreqsNonDominantes.size() <<endl;*/
                //----------------------------------------------------------------------
                 //+++++++++++++ sol par sol +++++++++++++++++++++++++++++++++++
                 //++++++++++++++++++ tout les sol
                  int  nondominancescore;
                  //cout << "trx.AvailableFrequencies->size()++++ "<< trx.AvailableFrequencies->size() <<endl;

                      for( i = 0; i < trx.validFrequencies->size();i++)//la solution condidate est dans l indice i
                {

                  nondominancescore = 0 ;// pour compter le nombre de solution qui domine la solution courante

                   for( j = 0; j < trx.AvailableFrequencies->size() ;j++)
                   {

                       if (i!=j)
                       {

                                   if (paircost[i].first <= paircost[j].first)  // on teste la dominance par rapport au deuciÃ¨me objectif
                                    {
                                          if (paircost[i].second < paircost[j].second)

                                        {
                                            IndexesFreqsNonDominantes.push_back({i,paircost[i].first});

                                            nondominancescore = nondominancescore + 1;
                                            }
                                        }


                                    //--- j insere le deuxi�me obj
                                  /* else
                                    {
                                         if (paircost[i].second <= paircost[j].second) // teste la dominance par rapport au deuciÃ¨me objectif
                                        {
                                                if (paircost[i].first < paircost[j].first) // on
                                                {
                                                    IndexesFreqsNonDominantes.push_back({i,paircost[i].first});
                                            //au deuxieme obj

                                                nondominancescore = nondominancescore+1;
                                                }
                                            //}
                                        }
                                    }*/

                       }//i!=j
                   }//fin j
                   /*  if (nondominancescore > (trx.AvailableFrequencies->size() - 2 ))
                  IndexesFreqsNonDominantes.push_back({i,paircost[i].first});*/

              }//fin i
            // cout <<"IndexesFreqsNonDominantes.size()PIII  "<< IndexesFreqsNonDominantes.size() <<endl;



                //...................................................
                 //.....................................................
                // II . Trier le tableau de la non dominance selon un ordre croissant si la liste n est pas vide
                // ....................................................
                //...................................................
              //  sort(IndexesFreqsNonDominantes.begin(),IndexesFreqsNonDominantes.end(),my_cmp);
             // cout << "  IndexesFreqsNonDominantes.size() ****"<< IndexesFreqsNonDominantes.size() << endl;


                // copier les solution trouver dans un vecteur avec son cout d interferqunce qui
                if (IndexesFreqsNonDominantes.size()!= 0 )
                {
                    /*vector < pair < int, double> > NonDominanteCost;
                    NonDominanteCost.reserve(IndexesFreqsNonDominantes.size());
                    for(i = 0; i < IndexesFreqsNonDominantes.size(); i++ )
                    {
                        NonDominanteCost.push_back({IndexesFreqsNonDominantes[i].first, paircost[IndexesFreqsNonDominantes[i].first].first });
                    }*/
                // trier le tableau selon un ordre d�croisant du cout et retirer la premi�re valeur
                    sort(IndexesFreqsNonDominantes.begin(),IndexesFreqsNonDominantes.end(),my_cmpInfDoublePair);
                   // indexmin = IndexesFreqsNonDominantes.front().first;
                   //si des valeur de cout �gale on choisit al�atoirement parmi ces valeur
                   //+++++++++++++++++++++++++++++++++++++++++++
                   k=0;
                   for(i = 0 ; i < IndexesFreqsNonDominantes.size(); i++)
                    {
                        double val = IndexesFreqsNonDominantes.at(i).second;
                        pair<int,double> pnextval;
                        if((i+1) < IndexesFreqsNonDominantes.size())
                        {
                            pnextval = IndexesFreqsNonDominantes.at(i+1);
                            double nextval = pnextval.second;
                            // on copie les valeurs egales dans un tableau
                            //cout<< "hiiii here " << endl;
                            if( val == nextval )
                            {
                                k = k +1 ;//k contient le nombre de valeur �gale
                                // cout<< "hiiii here " << endl;
                            }
                            else
                            {
                                i = IndexesFreqsNonDominantes.size();
                            }
                        }
                    }
    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                    int indexf = rand() % (k+1);
                    indexmin = IndexesFreqsNonDominantes.at(indexf).first;

                }
                else
                {
                     vecmin(veccost, indexmin);//indexmin:indice de la fr�quencence qui a la valeur minimale
                }

                //................................................................................

//--------------------- dominance available
                //..............................................................
                //...................................................................................

    //vider la m�moire--vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
    vector < pair<double,double>  >().swap(paircost) ;
    delete(veccost);
    delete(solution->PlanAffect);
                //..............................................................
                //...................................................................................
                f=trx.validFrequencies->at(indexmin);//indice de la fr�quence ayant un cout minimal,

    //+++++++++++++++++++++++++++++++

            }//taille >1
            else
            {
                if(taille==1)
                {
                    f=trx.validFrequencies->at(0);
                // cout<<" frequency choisit:lorsque la taille est 0"<<f<<endl;
                // cout<<"hii"<<endl;
                }
            }//taille == 1?!!
        }
        else//Availablefrequencies==empty()
        {
            cout<<" la liste des fr�quences valide est vide **"<<endl;
        }
















            //******************
            //cout<<" la liste des fr�quences disponibles est vide **"<<endl;
        }
    break;
    }//case 55  : best frequency Front pareto Laidi
    //---------------------------------------------------------------
     //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ FRONt PARETO Pure~~~~~~~~~~~~~~~~~~~~~~

       //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ FRONt PARETO PUUUUUUUUUUUURE Minimum ecart ~~~~~~~~~~~~~~~~~~~~~~
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   case  551://strategy 5 choisir la meilleur fr�quence en terme Front parteo
    {
          int i,indexmin,j,k;
       // Individual * tempsol =  new Individual();
        int tempfreq;
        //��������������������������������� copier la solution dans tempsol ����������������������
        //���������������������������������������������������������������������������������������
        //tempsol = solution;
        //tempsol->plan = new vector <int>(solution->plan->size());
        //tempsol->planCC = new vector <double>(solution->planCC->size());
        solution->PlanAffect = new vector< pair<int,int> > ();
        // tempsol->PIObj = solution->PIObj;
        // tempsol->PSObj = solution->PSObj;
        for(i=0;i<solution->plan->size();i++)
        {
            //tempsol->plan->at(i) = solution->plan->at(i);
            //tempsol->planCC->at(i) = solution->planCC->at(i);
           // tempsol->PIObj = solution->PIObj;
            //tempsol->PSObj = solution->PSObj;
            if(solution->plan->at(i)!=-1)//si la case dans le plan n'est pas vide on remplie le planAffect
            {
                solution->PlanAffect->push_back({i,solution->plan->at(i)});
            }
        }

        //����������������������������������������������������������
        //���������������������������������������������������������������
        //   tempsol->planCC=NULL;
        //LF comment: on traverse tte les fr�quence et on calcule le cout
        int victimFrequency,interfererFrequency;
        int victimTrx,interfererTrx;
        victimTrx = trx.trxID;

        int taille;
        //..........................................................
        //..........................................................
        //vecteur pour enregistrer le couple de cout  interference, separation � la fois
        vector < pair<double,double>  > paircost ;
        //----------------------
        if(trx.AvailableFrequencies->empty()==false)
        {
           taille =trx.AvailableFrequencies->size();

            vector<double> * veccost = new vector <double>(taille);
                 vector<double> * cost = new vector <double>(taille);
            if (taille>1)
            {
                for(i=0 ;i < taille ; i++)//pour chaque fr�quence probable on evalue le cout
                {

                    victimFrequency =trx.AvailableFrequencies->at(i);
                    veccost->at(i)=0.0;
                    cost->at(i)=0.0;
                    solution->PlanAffect->push_back({trx.trxID,victimFrequency});
                    //on �value la solution avec le nouveau couple : {victimTrx,victimFrequency}
                   int victimTrx1 = trx.trxID; int victimFrequency1 = trx.AvailableFrequencies->at(i);
                    for(j=0;j< solution->PlanAffect->size();j++)
                    {

                        victimTrx = solution->PlanAffect->at(j).first;
                        victimFrequency = solution->PlanAffect->at(j).second;
                       interfererTrx = solution->PlanAffect->at(j).first;
                        interfererFrequency = solution->PlanAffect->at(j).second;
                        if ( interfererTrx != victimTrx1)
                        {
                           // calculer le cout d interference
                            veccost->at(i)  = veccost->at(i)  + afpProblem->computeChannelInterference(victimFrequency1 ,interfererFrequency, victimTrx1, interfererTrx)+
                            afpProblem->computeChannelInterference(interfererFrequency,victimFrequency1 ,interfererTrx, victimTrx1);
                            //cout de separation
                           if(afpProblem->trxs[victimTrx1].sectorID == afpProblem->trxs[interfererTrx].sectorID)
                            {
                                //on teste si la contraite de separation co-secteur est respect�!!
                                if (abs (interfererFrequency-victimFrequency1)<3 )//contrainte co secteur viol�e
                                {
                                    cost->at(i) = cost->at(i) + 1.0;
                                }
                            }// secteur different
                            else
                            {
                                if(afpProblem->trxs[victimTrx1].siteID  == afpProblem->trxs[interfererTrx].siteID)
                                {
                        //on teste si la contrainte de separation co-site est respect�e!!
                                    if (abs (interfererFrequency-victimFrequency1)< 2)//contrainte co secteur viol�e
                                    {
                                        cost->at(i) = cost->at(i) + 1.0;
                                    }
                                }//
                            }
                        }

                    }// for(j=0 ;j < taille ; j++)//pour chaque fr�quence probable on evalue le cout
                    //.............................................................................
                    //.............................................................................
                    // enregister les couts dans le vecteur
                  //  cout << veccost->at(i) << veccost->at(i) << endl;
                    veccost->at(i) = veccost->at(i) + solution->PIObj ;
                    cost->at(i) = cost->at(i) + solution->PSObj ;
                    paircost.push_back({veccost->at(i),cost->at(i)});
                    //...................................................................
                    solution->PlanAffect->pop_back();//on retire le couple probable apres evaluation de cout et l avoir enregistr� dans veccost
                    // cout<<"frequence ::" <<trx.AvailableFrequencies->at(i)<<", son sout veccost[i] ==="<< veccost->at(i)<<endl;
                } //fortrx.AvailableFrequencies


 //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
     //DOMINANCE
   //
                 //...................................................
                 //.....................................................
                // I . Retirer la non dominance pour chaque fr�quence
                // ....................................................
                //...................................................

                //je supose que la soluution est domiin�e et je vais tester si c est vrai

                    //+++++++++++++Laidi modifi� +++++++++++++++++++++++++++++++++++
      //je supose que la soluution est domiin�e et je vais tester si c est vrai
            int rank;
  int counter;
  int dominantScore;
  int temp = 0;
  rank = 1;
  vector < pair<int,double> > IndexesFreqsNonDominantes;
    IndexesFreqsNonDominantes.reserve(paircost.size());
    int taille=paircost.size();
    int array_rank[paircost.size()];
    counter =paircost.size();


    for (int i=0; i<paircost.size(); i++)
    {
      dominantScore=0;

	  for (int j=0; j<paircost.size(); j++)
	  {
        if (i!=j)
        {

            if ((paircost[i].first>=paircost[j].first && paircost[i].second>paircost[j].second) || (paircost[i].second>=paircost[j].second && paircost[i].first>paircost[j].first))
            {
          //  array_domination_count[i] = array_domination_count[i] + 1;
            dominantScore=dominantScore+1;// on a trouv� j qui domine i ;
            }
        }//i!=j
       } //fin j
		if (dominantScore==0)
        {
          // indices.push_back(i); // pour sauvgarder les indices des solution non dominées dans la nouvelle population
           IndexesFreqsNonDominantes.push_back({i,paircost[i].second});
        }
	}//fin i



              if (IndexesFreqsNonDominantes.size()!= 0)
              {
                  //cout << " la taille du vect solutions non dom PS == " << IndexesFreqsNonDominantes.size()<< endl;
                 // sort(IndexesFreqsNonDominantes.begin(),IndexesFreqsNonDominantes.end(),my_cmpInfDoublePair);//trier selon un ordre croissant de cout
                sort(IndexesFreqsNonDominantes.begin(),IndexesFreqsNonDominantes.end(),my_cmpInfDoublePair);
                //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                //~~~~~~~~~~~~~~~~~~~~~~~~~~~si plusieurs fr�queences  non domlinates ont le meme cout on choisit
                // al�atoirement une
                //---------------------------------------------------
                i = 0;     k = 0 ;
                //------------------------------------
                for(i = 0 ; i < IndexesFreqsNonDominantes.size(); i++)
                {
                    //double val = IndexesFreqsNonDominantes.at(i).second;
                    double val = IndexesFreqsNonDominantes.at(i).second;
                    //pair<int,double> pnextval;
                    pair<int,double> pnextval;
                    if((i+1) < IndexesFreqsNonDominantes.size())
                    {
                        pnextval = IndexesFreqsNonDominantes.at(i+1);
                        //double nextval = pnextval.second;
                        double nextval = pnextval.second;
                        // on copie les valeurs egales dans un tableau
                        //cout<< "hiiii here " << endl;
                        if( val == nextval )
                        {
                            k = k +1 ;//k contient le nombre de valeur �gale
                        }
                        else
                        {
                            i = IndexesFreqsNonDominantes.size();
                        }
                    }
                }
                int indice ;
                //indice = rand() % (k+1);// coisir une parmi les "n" premier
                //indexmin = IndexesFreqsNonDominantes.at(indice).first;// r�cup�ration de l'indice de la fr�quence
               // cout << "k ������������������" << k << endl;
                  vector < pair< int, double> > distance;
            distance.reserve(k+1);
            int indicefreq;
            indicefreq = IndexesFreqsNonDominantes.at(0).first;
             double v = abs(veccost->at(indicefreq)- cost->at(indicefreq));
            distance.push_back({indicefreq,v});
            for(i = 1 ;i < k ; i++)
            {
                indicefreq = IndexesFreqsNonDominantes.at(i).first;
                v  =  abs(veccost->at(indicefreq)- cost->at(indicefreq));
                distance.push_back({indicefreq,v});
            }
            sort(distance.begin(),distance.end(),my_cmpInfDoublePair);
            indexmin = distance.front().first;// r�cup�ration de l'indice de la fr�quenc













              }
               else// il n y a aucune valeur dans le front pareto
               {
                 //cout << " taille 0000000000000000 " << endl;
                 // vecmin(cost, indexmin);//indexmin:indice de la fr�quencence qui a la valeur minimale
                 StrategyFreq = 2;//3 : ecart, 6: hv , 2 : minimum cost
                 PSChooseFrequency(instance,StrategyFreq,trx,f,solution,afpProblem);
                 return;

               }
    //............................End dominance ......................................
    //................................................................................
    //................................................................................
    f=trx.AvailableFrequencies->at(indexmin);//indice de la fr�quence recherch�
    solution->PIObj = veccost->at(indexmin);
    solution->PSObj = cost->at(indexmin);
    //delete(tempsol->PlanAffect);
    vector < pair<double,double> > ().swap(paircost) ;
    vector < pair<int,double> > ().swap(IndexesFreqsNonDominantes);
    delete(veccost);
    delete(cost);
    //delete(tempsol->PlanAffect);
    delete(solution->PlanAffect);
    //--------------------- dominance available
    }//if (taille >1)
    else
    {
       if(taille==1) // la taille  == 1; je n ai qu'un choix
        {
            f=trx.AvailableFrequencies->at(0);
            // cout<<" frequency choisit:lorsque la taille est 0"<<f<<endl;
            // cout<<"hii"<<endl;
            delete(solution->PlanAffect);
        }
    }//taille :.!=1
 }// Availablefrequencies is empty()
else//Availablefrequencies==empty() // aucune fr�quence n'est diponible j'utilise les fr�quence valides
        {// on choisit la meilleur fr�quence VALID

            //****************#################################""
        //----------------------
        if(trx.validFrequencies->empty()==false)
        {
            taille =trx.validFrequencies->size();
            vector<double> * veccost = new vector <double>(taille);
                vector<double> * cost = new vector <double>(taille);
            if (taille>1)
            {
                for(i=0 ;i < taille ; i++)//pour chaque fr�quence probable on evalue le cout
                {
                    victimFrequency =trx.validFrequencies->at(i);
                     veccost->at(i)=0.0;
                    cost->at(i)=0.0;
                    solution->PlanAffect->push_back({trx.trxID,victimFrequency});
                    //on �value la solution avec le nouveau couple : {victimTrx,victimFrequency}
                   int victimTrx1 = trx.trxID; int victimFrequency1 = trx.AvailableFrequencies->at(i);
                    for(j=0;j< solution->PlanAffect->size();j++)
                    {

                        victimTrx = solution->PlanAffect->at(j).first;
                        victimFrequency = solution->PlanAffect->at(j).second;
                       interfererTrx = solution->PlanAffect->at(j).first;
                        interfererFrequency = solution->PlanAffect->at(j).second;
                        if ( interfererTrx != victimTrx1)
                        {
                           // calculer le cout d interference
                            veccost->at(i)  = veccost->at(i)  + afpProblem->computeChannelInterference(victimFrequency1 ,interfererFrequency, victimTrx1, interfererTrx)+
                            afpProblem->computeChannelInterference(interfererFrequency,victimFrequency1 ,interfererTrx, victimTrx1);
                            //cout de separation
                           if(afpProblem->trxs[victimTrx1].sectorID == afpProblem->trxs[interfererTrx].sectorID)
                            {
                                //on teste si la contraite de separation co-secteur est respect�!!
                                if (abs (interfererFrequency-victimFrequency1)<3 )//contrainte co secteur viol�e
                                {
                                    cost->at(i) = cost->at(i) + 1.0;
                                }
                            }// secteur different
                            else
                            {
                                if(afpProblem->trxs[victimTrx1].siteID  == afpProblem->trxs[interfererTrx].siteID)
                                {
                        //on teste si la contrainte de separation co-site est respect�e!!
                                    if (abs (interfererFrequency-victimFrequency1)< 2)//contrainte co secteur viol�e
                                    {
                                        cost->at(i) = cost->at(i) + 1.0;
                                    }
                                }//
                            }
                        }

                    }// for(j=0 ;j < taille ; j++)//pour chaque fr�quence probable on evalue le cout
                    //.............................................................................
                    //.............................................................................
                    // enregister les couts dans le vecteur
                  //  cout << veccost->at(i) << veccost->at(i) << endl;
                    veccost->at(i) = veccost->at(i) + solution->PIObj ;
                    cost->at(i) = cost->at(i) + solution->PSObj ;
                    paircost.push_back({veccost->at(i),cost->at(i)});
                    //...................................................................
                    solution->PlanAffect->pop_back();//on retire le couple probable apres evaluation de cout et l avoir enregistr� dans veccost
                    // cout<<"frequence ::" <<trx.AvailableFrequencies->at(i)<<", son sout veccost[i] ==="<< veccost->at(i)<<endl;
                } //fortrx.Av
          //..............................................................
                //...................................................................................

        //DOMINANCE


                 //...................................................
                 //.....................................................
                // I . Retirer la non dominance pour chaque fr�quence
                // ....................................................
                //...................................................

                 int  DominantScore;

                vector < pair<int,int> > IndexesFreqsNonDominantes;
                 //(int,int) :: le premier enregistre l index de la fr�quence non dominante
                  //(int,int) :: le dexieme , combien de fois la fr�quence est non dominante
                IndexesFreqsNonDominantes.reserve(trx.validFrequencies->size());
        //+++++++++++++Laidi modifi� +++++++++++++++++++++++++++++++++++
          for( i = 0; i < trx.AvailableFrequencies->size();i++)//la solution condidate est dans l indice i
                {

                  DominantScore = 0 ;// pour compter le nombre de solution qui domine la solution courante

                  for( j = i+1; j < trx.AvailableFrequencies->size() ;j++)
                   {
                       if (i!=j)
                       {

                           if (paircost[i].first > paircost[j].first) // on teste la dominance par rapport au premier objectif
                            {
                                // on ne peut pas juger on test par rapport au deuxime obj
                                if (paircost[i].second > paircost[j].second)
                                         {

                                                  //on est sur qu elle est dominante
                                                DominantScore    =   DominantScore+1 ;


                                         }
                                         else
                                         {
                                             if(paircost[i].first >= paircost[j].first)
                                              {
                                                    DominantScore    =   DominantScore+1 ;
                                              }
                                         }

                            }
                            else
                            {
                                if (paircost[i].second >= paircost[j].second)
                                    {
                                        DominantScore    =   DominantScore+1 ;
                                    }

                            }


                        }//i!=j
                    }//fin j

						if (DominantScore==0)// pour s'assurer que la solution "i" est non dominée
                      {
                        IndexesFreqsNonDominantes.push_back({i,paircost[i].first});// on insert l'index de la solution et son cout d'interférences
                      }
                       // cout << "la solution " << i << " est dominee par  " << DominantScore << " autres solutions" << endl;
                }//fin i

            //cout <<"IndexesFreqsNonDominantes.size()PIII  "<< IndexesFreqsNonDominantes.size() <<endl;*/
                //----------------------------------------------------------------------
                 //+++++++++++++ sol par sol +++++++++++++++++++++++++++++++++++
                 //++++++++++++++++++ tout les sol
                  int  nondominancescore;
                  //cout << "trx.AvailableFrequencies->size()++++ "<< trx.AvailableFrequencies->size() <<endl;

                      for( i = 0; i < trx.validFrequencies->size();i++)//la solution condidate est dans l indice i
                {

                  nondominancescore = 0 ;// pour compter le nombre de solution qui domine la solution courante

                   for( j = 0; j < trx.AvailableFrequencies->size() ;j++)
                   {

                       if (i!=j)
                       {

                                   if (paircost[i].first <= paircost[j].first)  // on teste la dominance par rapport au deuciÃ¨me objectif
                                    {
                                          if (paircost[i].second < paircost[j].second)

                                        {
                                            IndexesFreqsNonDominantes.push_back({i,paircost[i].first});

                                            nondominancescore = nondominancescore + 1;
                                            }
                                        }


                                    //--- j insere le deuxi�me obj
                                  /* else
                                    {
                                         if (paircost[i].second <= paircost[j].second) // teste la dominance par rapport au deuciÃ¨me objectif
                                        {
                                                if (paircost[i].first < paircost[j].first) // on
                                                {
                                                    IndexesFreqsNonDominantes.push_back({i,paircost[i].first});
                                            //au deuxieme obj

                                                nondominancescore = nondominancescore+1;
                                                }
                                            //}
                                        }
                                    }*/

                       }//i!=j
                   }//fin j
                   /*  if (nondominancescore > (trx.AvailableFrequencies->size() - 2 ))
                  IndexesFreqsNonDominantes.push_back({i,paircost[i].first});*/

              }//fin i
            // cout <<"IndexesFreqsNonDominantes.size()PIII  "<< IndexesFreqsNonDominantes.size() <<endl;



                //...................................................
                 //.....................................................
                // II . Trier le tableau de la non dominance selon un ordre croissant si la liste n est pas vide
                // ....................................................
                //...................................................
              //  sort(IndexesFreqsNonDominantes.begin(),IndexesFreqsNonDominantes.end(),my_cmp);
             // cout << "  IndexesFreqsNonDominantes.size() ****"<< IndexesFreqsNonDominantes.size() << endl;


                // copier les solution trouver dans un vecteur avec son cout d interferqunce qui
                if (IndexesFreqsNonDominantes.size()!= 0 )
                {
                    /*vector < pair < int, double> > NonDominanteCost;
                    NonDominanteCost.reserve(IndexesFreqsNonDominantes.size());
                    for(i = 0; i < IndexesFreqsNonDominantes.size(); i++ )
                    {
                        NonDominanteCost.push_back({IndexesFreqsNonDominantes[i].first, paircost[IndexesFreqsNonDominantes[i].first].first });
                    }*/
                // trier le tableau selon un ordre d�croisant du cout et retirer la premi�re valeur
                    sort(IndexesFreqsNonDominantes.begin(),IndexesFreqsNonDominantes.end(),my_cmpInfDoublePair);
                   // indexmin = IndexesFreqsNonDominantes.front().first;
                   //si des valeur de cout �gale on choisit al�atoirement parmi ces valeur
                   //+++++++++++++++++++++++++++++++++++++++++++
                   k=0;
                   for(i = 0 ; i < IndexesFreqsNonDominantes.size(); i++)
                    {
                        double val = IndexesFreqsNonDominantes.at(i).second;
                        pair<int,double> pnextval;
                        if((i+1) < IndexesFreqsNonDominantes.size())
                        {
                            pnextval = IndexesFreqsNonDominantes.at(i+1);
                            double nextval = pnextval.second;
                            // on copie les valeurs egales dans un tableau
                            //cout<< "hiiii here " << endl;
                            if( val == nextval )
                            {
                                k = k +1 ;//k contient le nombre de valeur �gale
                                // cout<< "hiiii here " << endl;
                            }
                            else
                            {
                                i = IndexesFreqsNonDominantes.size();
                            }
                        }
                    }
    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                    int indexf = rand() % (k+1);
                    indexmin = IndexesFreqsNonDominantes.at(indexf).first;

                }
                else
                {
                     vecmin(veccost, indexmin);//indexmin:indice de la fr�quencence qui a la valeur minimale
                }

                //................................................................................

//--------------------- dominance available
                //..............................................................
                //...................................................................................

    //vider la m�moire--vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
    vector < pair<double,double>  >().swap(paircost) ;
    delete(veccost);
    delete(solution->PlanAffect);
                //..............................................................
                //...................................................................................
                f=trx.validFrequencies->at(indexmin);//indice de la fr�quence ayant un cout minimal,

    //+++++++++++++++++++++++++++++++

            }//taille >1
            else
            {
                if(taille==1)
                {
                    f=trx.validFrequencies->at(0);
                // cout<<" frequency choisit:lorsque la taille est 0"<<f<<endl;
                // cout<<"hii"<<endl;
                }
            }//taille == 1?!!
        }
        else//Availablefrequencies==empty()
        {
            cout<<" la liste des fr�quences valide est vide **"<<endl;
        }
















            //******************
            //cout<<" la liste des fr�quences disponibles est vide **"<<endl;
        }
    break;
    }//case 551 : best frequency Front pareto Laidi
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
     //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ FRONt PARETO PUUUUUUUUUUUURE Plus grand HV ~~~~~~~~~~~~~~~~~~~~~~
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   case  552://strategy 5 choisir la meilleur fr�quence en terme Front parteo plus grand HV
    {
          int i,indexmin,j,k;
       // Individual * tempsol =  new Individual();
        int tempfreq;
        //��������������������������������� copier la solution dans tempsol ����������������������
        //���������������������������������������������������������������������������������������
        //tempsol = solution;
        //tempsol->plan = new vector <int>(solution->plan->size());
        //tempsol->planCC = new vector <double>(solution->planCC->size());
        solution->PlanAffect = new vector< pair<int,int> > ();
        // tempsol->PIObj = solution->PIObj;
        // tempsol->PSObj = solution->PSObj;
        for(i=0;i<solution->plan->size();i++)
        {
            //tempsol->plan->at(i) = solution->plan->at(i);
            //tempsol->planCC->at(i) = solution->planCC->at(i);
           // tempsol->PIObj = solution->PIObj;
            //tempsol->PSObj = solution->PSObj;
            if(solution->plan->at(i)!=-1)//si la case dans le plan n'est pas vide on remplie le planAffect
            {
                solution->PlanAffect->push_back({i,solution->plan->at(i)});
            }
        }

        //����������������������������������������������������������
        //���������������������������������������������������������������
        //   tempsol->planCC=NULL;
        //LF comment: on traverse tte les fr�quence et on calcule le cout
        int victimFrequency,interfererFrequency;
        int victimTrx,interfererTrx;
        victimTrx = trx.trxID;

        int taille;
        //..........................................................
        //..........................................................
        //vecteur pour enregistrer le couple de cout  interference, separation � la fois
        vector < pair<double,double>  > paircost ;
        //----------------------
        if(trx.AvailableFrequencies->empty()==false)
        {
           taille =trx.AvailableFrequencies->size();

            vector<double> * veccost = new vector <double>(taille);
                 vector<double> * cost = new vector <double>(taille);
            if (taille>1)
            {
                for(i=0 ;i < taille ; i++)//pour chaque fr�quence probable on evalue le cout
                {

                    victimFrequency =trx.AvailableFrequencies->at(i);
                    veccost->at(i)=0.0;
                    cost->at(i)=0.0;
                    solution->PlanAffect->push_back({trx.trxID,victimFrequency});
                    //on �value la solution avec le nouveau couple : {victimTrx,victimFrequency}
                   int victimTrx1 = trx.trxID; int victimFrequency1 = trx.AvailableFrequencies->at(i);
                    for(j=0;j< solution->PlanAffect->size();j++)
                    {

                        victimTrx = solution->PlanAffect->at(j).first;
                        victimFrequency = solution->PlanAffect->at(j).second;
                       interfererTrx = solution->PlanAffect->at(j).first;
                        interfererFrequency = solution->PlanAffect->at(j).second;
                        if ( interfererTrx != victimTrx1)
                        {
                           // calculer le cout d interference
                            veccost->at(i)  = veccost->at(i)  + afpProblem->computeChannelInterference(victimFrequency1 ,interfererFrequency, victimTrx1, interfererTrx)+
                            afpProblem->computeChannelInterference(interfererFrequency,victimFrequency1 ,interfererTrx, victimTrx1);
                            //cout de separation
                           if(afpProblem->trxs[victimTrx1].sectorID == afpProblem->trxs[interfererTrx].sectorID)
                            {
                                //on teste si la contraite de separation co-secteur est respect�!!
                                if (abs (interfererFrequency-victimFrequency1)<3 )//contrainte co secteur viol�e
                                {
                                    cost->at(i) = cost->at(i) + 1.0;
                                }
                            }// secteur different
                            else
                            {
                                if(afpProblem->trxs[victimTrx1].siteID  == afpProblem->trxs[interfererTrx].siteID)
                                {
                        //on teste si la contrainte de separation co-site est respect�e!!
                                    if (abs (interfererFrequency-victimFrequency1)< 2)//contrainte co secteur viol�e
                                    {
                                        cost->at(i) = cost->at(i) + 1.0;
                                    }
                                }//
                            }
                        }

                    }// for(j=0 ;j < taille ; j++)//pour chaque fr�quence probable on evalue le cout
                    //.............................................................................
                    //.............................................................................
                    // enregister les couts dans le vecteur
                  //  cout << veccost->at(i) << veccost->at(i) << endl;
                    veccost->at(i) = veccost->at(i) + solution->PIObj ;
                    cost->at(i) = cost->at(i) + solution->PSObj ;
                    paircost.push_back({veccost->at(i),cost->at(i)});
                    //...................................................................
                    solution->PlanAffect->pop_back();//on retire le couple probable apres evaluation de cout et l avoir enregistr� dans veccost
                    // cout<<"frequence ::" <<trx.AvailableFrequencies->at(i)<<", son sout veccost[i] ==="<< veccost->at(i)<<endl;
                } //fortrx.AvailableFrequencies


 //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
     //DOMINANCE
   //
                 //...................................................
                 //.....................................................
                // I . Retirer la non dominance pour chaque fr�quence
                // ....................................................
                //...................................................

                //je supose que la soluution est domiin�e et je vais tester si c est vrai

                    //+++++++++++++Laidi modifi� +++++++++++++++++++++++++++++++++++
      //je supose que la soluution est domiin�e et je vais tester si c est vrai
            int rank;
  int counter;
  int dominantScore;
  int temp = 0;
  rank = 1;
  vector < pair<int,double> > IndexesFreqsNonDominantes;
    IndexesFreqsNonDominantes.reserve(paircost.size());
    int taille=paircost.size();
    int array_rank[paircost.size()];
    counter =paircost.size();


    for (int i=0; i<paircost.size(); i++)
    {
      dominantScore=0;

	  for (int j=0; j<paircost.size(); j++)
	  {
        if (i!=j)
        {

            if ((paircost[i].first>=paircost[j].first && paircost[i].second>paircost[j].second) || (paircost[i].second>=paircost[j].second && paircost[i].first>paircost[j].first))
            {
          //  array_domination_count[i] = array_domination_count[i] + 1;
            dominantScore=dominantScore+1;// on a trouv� j qui domine i ;
            }
        }//i!=j
       } //fin j
		if (dominantScore==0)
        {
          // indices.push_back(i); // pour sauvgarder les indices des solution non dominées dans la nouvelle population
           IndexesFreqsNonDominantes.push_back({i,paircost[i].second});
        }
	}//fin i



              if (IndexesFreqsNonDominantes.size()!= 0)
              {
                  //cout << " la taille du vect solutions non dom PS == " << IndexesFreqsNonDominantes.size()<< endl;
                 // sort(IndexesFreqsNonDominantes.begin(),IndexesFreqsNonDominantes.end(),my_cmpInfDoublePair);//trier selon un ordre croissant de cout
                sort(IndexesFreqsNonDominantes.begin(),IndexesFreqsNonDominantes.end(),my_cmpInfDoublePair);
                //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                //~~~~~~~~~~~~~~~~~~~~~~~~~~~si plusieurs fr�queences  non domlinates ont le meme cout on choisit
                // al�atoirement une
                //---------------------------------------------------
                i = 0;     k = 0 ;
                //------------------------------------
                for(i = 0 ; i < IndexesFreqsNonDominantes.size(); i++)
                {
                    //double val = IndexesFreqsNonDominantes.at(i).second;
                    double val = IndexesFreqsNonDominantes.at(i).second;
                    //pair<int,double> pnextval;
                    pair<int,double> pnextval;
                    if((i+1) < IndexesFreqsNonDominantes.size())
                    {
                        pnextval = IndexesFreqsNonDominantes.at(i+1);
                        //double nextval = pnextval.second;
                        double nextval = pnextval.second;
                        // on copie les valeurs egales dans un tableau
                        //cout<< "hiiii here " << endl;
                        if( val == nextval )
                        {
                            k = k +1 ;//k contient le nombre de valeur �gale
                        }
                        else
                        {
                            i = IndexesFreqsNonDominantes.size();
                        }
                    }
                }
                int indice ;
              //  indice = rand() % (k+1);// coisir une parmi les "n" premier
               // indexmin = IndexesFreqsNonDominantes.at(indice).first;// r�cup�ration de l'indice de la fr�quence
               // cout << "k ������������������" << k << endl;

            vector< pair < int, double > > VectHV;

            VectHV.reserve(k+1);
            int indicefreq;
            indicefreq = IndexesFreqsNonDominantes.at(0).first;
             pair<double,double> Min;
            pair<double,double> Max;
            pair < double, double > R;// est le point de r�f�rence ; la valeur max (normalis�)
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
    Normalize(paircost,Min,Max);
    for(i=0; i<= k; i++)
    {
        int valindice = IndexesFreqsNonDominantes.at(i).first;
        double X = paircost.at(valindice).first ;
        double Y = paircost.at(valindice).second ;
        double ValHV = (R.first - X)* (R.second - Y);
        VectHV.push_back({valindice,ValHV});
    }

    //**********************************************************

            sort(VectHV.begin(),VectHV.end(),my_cmpSupDoublePair);
            indexmin = VectHV.front().first;// r�cup�ration de l'indice de la fr�quence













              }
               else// il n y a aucune valeur dans le front pareto
               {
                 //cout << " taille 0000000000000000 " << endl;
                 // vecmin(cost, indexmin);//indexmin:indice de la fr�quencence qui a la valeur minimale
                 StrategyFreq = 2;//3 : ecart, 6: hv , 2 : minimum cost
                 PSChooseFrequency(instance,StrategyFreq,trx,f,solution,afpProblem);
                 return;

               }
    //............................End dominance ......................................
    //................................................................................
    //................................................................................
    f=trx.AvailableFrequencies->at(indexmin);//indice de la fr�quence recherch�
    solution->PIObj = veccost->at(indexmin);
    solution->PSObj = cost->at(indexmin);
    //delete(tempsol->PlanAffect);
    vector < pair<double,double> > ().swap(paircost) ;
    vector < pair<int,double> > ().swap(IndexesFreqsNonDominantes);
    delete(veccost);
    delete(cost);
    //delete(tempsol->PlanAffect);
    delete(solution->PlanAffect);
    //--------------------- dominance available
    }//if (taille >1)
    else
    {
       if(taille==1) // la taille  == 1; je n ai qu'un choix
        {
            f=trx.AvailableFrequencies->at(0);
            // cout<<" frequency choisit:lorsque la taille est 0"<<f<<endl;
            // cout<<"hii"<<endl;
            delete(solution->PlanAffect);
        }
    }//taille :.!=1
 }// Availablefrequencies is empty()
else//Availablefrequencies==empty() // aucune fr�quence n'est diponible j'utilise les fr�quence valides
        {// on choisit la meilleur fr�quence VALID

            //****************#################################""
        //----------------------
        if(trx.validFrequencies->empty()==false)
        {
            taille =trx.validFrequencies->size();
            vector<double> * veccost = new vector <double>(taille);
                vector<double> * cost = new vector <double>(taille);
            if (taille>1)
            {
                for(i=0 ;i < taille ; i++)//pour chaque fr�quence probable on evalue le cout
                {
                    victimFrequency =trx.validFrequencies->at(i);
                     veccost->at(i)=0.0;
                    cost->at(i)=0.0;
                    solution->PlanAffect->push_back({trx.trxID,victimFrequency});
                    //on �value la solution avec le nouveau couple : {victimTrx,victimFrequency}
                   int victimTrx1 = trx.trxID; int victimFrequency1 = trx.AvailableFrequencies->at(i);
                    for(j=0;j< solution->PlanAffect->size();j++)
                    {

                        victimTrx = solution->PlanAffect->at(j).first;
                        victimFrequency = solution->PlanAffect->at(j).second;
                       interfererTrx = solution->PlanAffect->at(j).first;
                        interfererFrequency = solution->PlanAffect->at(j).second;
                        if ( interfererTrx != victimTrx1)
                        {
                           // calculer le cout d interference
                            veccost->at(i)  = veccost->at(i)  + afpProblem->computeChannelInterference(victimFrequency1 ,interfererFrequency, victimTrx1, interfererTrx)+
                            afpProblem->computeChannelInterference(interfererFrequency,victimFrequency1 ,interfererTrx, victimTrx1);
                            //cout de separation
                           if(afpProblem->trxs[victimTrx1].sectorID == afpProblem->trxs[interfererTrx].sectorID)
                            {
                                //on teste si la contraite de separation co-secteur est respect�!!
                                if (abs (interfererFrequency-victimFrequency1)<3 )//contrainte co secteur viol�e
                                {
                                    cost->at(i) = cost->at(i) + 1.0;
                                }
                            }// secteur different
                            else
                            {
                                if(afpProblem->trxs[victimTrx1].siteID  == afpProblem->trxs[interfererTrx].siteID)
                                {
                        //on teste si la contrainte de separation co-site est respect�e!!
                                    if (abs (interfererFrequency-victimFrequency1)< 2)//contrainte co secteur viol�e
                                    {
                                        cost->at(i) = cost->at(i) + 1.0;
                                    }
                                }//
                            }
                        }

                    }// for(j=0 ;j < taille ; j++)//pour chaque fr�quence probable on evalue le cout
                    //.............................................................................
                    //.............................................................................
                    // enregister les couts dans le vecteur
                  //  cout << veccost->at(i) << veccost->at(i) << endl;
                    veccost->at(i) = veccost->at(i) + solution->PIObj ;
                    cost->at(i) = cost->at(i) + solution->PSObj ;
                    paircost.push_back({veccost->at(i),cost->at(i)});
                    //...................................................................
                    solution->PlanAffect->pop_back();//on retire le couple probable apres evaluation de cout et l avoir enregistr� dans veccost
                    // cout<<"frequence ::" <<trx.AvailableFrequencies->at(i)<<", son sout veccost[i] ==="<< veccost->at(i)<<endl;
                } //fortrx.Av
          //..............................................................
                //...................................................................................

        //DOMINANCE


                 //...................................................
                 //.....................................................
                // I . Retirer la non dominance pour chaque fr�quence
                // ....................................................
                //...................................................

                 int  DominantScore;

                vector < pair<int,int> > IndexesFreqsNonDominantes;
                 //(int,int) :: le premier enregistre l index de la fr�quence non dominante
                  //(int,int) :: le dexieme , combien de fois la fr�quence est non dominante
                IndexesFreqsNonDominantes.reserve(trx.validFrequencies->size());
        //+++++++++++++Laidi modifi� +++++++++++++++++++++++++++++++++++
          for( i = 0; i < trx.AvailableFrequencies->size();i++)//la solution condidate est dans l indice i
                {

                  DominantScore = 0 ;// pour compter le nombre de solution qui domine la solution courante

                  for( j = i+1; j < trx.AvailableFrequencies->size() ;j++)
                   {
                       if (i!=j)
                       {

                           if (paircost[i].first > paircost[j].first) // on teste la dominance par rapport au premier objectif
                            {
                                // on ne peut pas juger on test par rapport au deuxime obj
                                if (paircost[i].second > paircost[j].second)
                                         {

                                                  //on est sur qu elle est dominante
                                                DominantScore    =   DominantScore+1 ;


                                         }
                                         else
                                         {
                                             if(paircost[i].first >= paircost[j].first)
                                              {
                                                    DominantScore    =   DominantScore+1 ;
                                              }
                                         }

                            }
                            else
                            {
                                if (paircost[i].second >= paircost[j].second)
                                    {
                                        DominantScore    =   DominantScore+1 ;
                                    }

                            }


                        }//i!=j
                    }//fin j

						if (DominantScore==0)// pour s'assurer que la solution "i" est non dominée
                      {
                        IndexesFreqsNonDominantes.push_back({i,paircost[i].first});// on insert l'index de la solution et son cout d'interférences
                      }
                       // cout << "la solution " << i << " est dominee par  " << DominantScore << " autres solutions" << endl;
                }//fin i

            //cout <<"IndexesFreqsNonDominantes.size()PIII  "<< IndexesFreqsNonDominantes.size() <<endl;*/
                //----------------------------------------------------------------------
                 //+++++++++++++ sol par sol +++++++++++++++++++++++++++++++++++
                 //++++++++++++++++++ tout les sol
                  int  nondominancescore;
                  //cout << "trx.AvailableFrequencies->size()++++ "<< trx.AvailableFrequencies->size() <<endl;

                      for( i = 0; i < trx.validFrequencies->size();i++)//la solution condidate est dans l indice i
                {

                  nondominancescore = 0 ;// pour compter le nombre de solution qui domine la solution courante

                   for( j = 0; j < trx.AvailableFrequencies->size() ;j++)
                   {

                       if (i!=j)
                       {

                                   if (paircost[i].first <= paircost[j].first)  // on teste la dominance par rapport au deuciÃ¨me objectif
                                    {
                                          if (paircost[i].second < paircost[j].second)

                                        {
                                            IndexesFreqsNonDominantes.push_back({i,paircost[i].first});

                                            nondominancescore = nondominancescore + 1;
                                            }
                                        }


                                    //--- j insere le deuxi�me obj
                                  /* else
                                    {
                                         if (paircost[i].second <= paircost[j].second) // teste la dominance par rapport au deuciÃ¨me objectif
                                        {
                                                if (paircost[i].first < paircost[j].first) // on
                                                {
                                                    IndexesFreqsNonDominantes.push_back({i,paircost[i].first});
                                            //au deuxieme obj

                                                nondominancescore = nondominancescore+1;
                                                }
                                            //}
                                        }
                                    }*/

                       }//i!=j
                   }//fin j
                   /*  if (nondominancescore > (trx.AvailableFrequencies->size() - 2 ))
                  IndexesFreqsNonDominantes.push_back({i,paircost[i].first});*/

              }//fin i
            // cout <<"IndexesFreqsNonDominantes.size()PIII  "<< IndexesFreqsNonDominantes.size() <<endl;



                //...................................................
                 //.....................................................
                // II . Trier le tableau de la non dominance selon un ordre croissant si la liste n est pas vide
                // ....................................................
                //...................................................
              //  sort(IndexesFreqsNonDominantes.begin(),IndexesFreqsNonDominantes.end(),my_cmp);
             // cout << "  IndexesFreqsNonDominantes.size() ****"<< IndexesFreqsNonDominantes.size() << endl;


                // copier les solution trouver dans un vecteur avec son cout d interferqunce qui
                if (IndexesFreqsNonDominantes.size()!= 0 )
                {
                    /*vector < pair < int, double> > NonDominanteCost;
                    NonDominanteCost.reserve(IndexesFreqsNonDominantes.size());
                    for(i = 0; i < IndexesFreqsNonDominantes.size(); i++ )
                    {
                        NonDominanteCost.push_back({IndexesFreqsNonDominantes[i].first, paircost[IndexesFreqsNonDominantes[i].first].first });
                    }*/
                // trier le tableau selon un ordre d�croisant du cout et retirer la premi�re valeur
                    sort(IndexesFreqsNonDominantes.begin(),IndexesFreqsNonDominantes.end(),my_cmpInfDoublePair);
                   // indexmin = IndexesFreqsNonDominantes.front().first;
                   //si des valeur de cout �gale on choisit al�atoirement parmi ces valeur
                   //+++++++++++++++++++++++++++++++++++++++++++
                   k=0;
                   for(i = 0 ; i < IndexesFreqsNonDominantes.size(); i++)
                    {
                        double val = IndexesFreqsNonDominantes.at(i).second;
                        pair<int,double> pnextval;
                        if((i+1) < IndexesFreqsNonDominantes.size())
                        {
                            pnextval = IndexesFreqsNonDominantes.at(i+1);
                            double nextval = pnextval.second;
                            // on copie les valeurs egales dans un tableau
                            //cout<< "hiiii here " << endl;
                            if( val == nextval )
                            {
                                k = k +1 ;//k contient le nombre de valeur �gale
                                // cout<< "hiiii here " << endl;
                            }
                            else
                            {
                                i = IndexesFreqsNonDominantes.size();
                            }
                        }
                    }
    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                    int indexf = rand() % (k+1);
                    indexmin = IndexesFreqsNonDominantes.at(indexf).first;

                }
                else
                {
                     vecmin(veccost, indexmin);//indexmin:indice de la fr�quencence qui a la valeur minimale
                }

                //................................................................................

//--------------------- dominance available
                //..............................................................
                //...................................................................................

    //vider la m�moire--vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
    vector < pair<double,double>  >().swap(paircost) ;
    delete(veccost);
    delete(solution->PlanAffect);
                //..............................................................
                //...................................................................................
                f=trx.validFrequencies->at(indexmin);//indice de la fr�quence ayant un cout minimal,

    //+++++++++++++++++++++++++++++++

            }//taille >1
            else
            {
                if(taille==1)
                {
                    f=trx.validFrequencies->at(0);
                // cout<<" frequency choisit:lorsque la taille est 0"<<f<<endl;
                // cout<<"hii"<<endl;
                }
            }//taille == 1?!!
        }
        else//Availablefrequencies==empty()
        {
            cout<<" la liste des fr�quences valide est vide **"<<endl;
        }
















            //******************
            //cout<<" la liste des fr�quences disponibles est vide **"<<endl;
        }
    break;
    }//case 552 : best frequency Front pareto PURE Plus grand HV

  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ FRONt PARETO PUUUUUUUUUUUURE Plus grand HV ~~~~~~~~~~~~~~~~~~~~~~
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   case  502://strategy 5 choisir la meilleur fr�quence en terme Front parteo plus grand HV
    {
          int i,indexmin,j,k;
       // Individual * tempsol =  new Individual();
        int tempfreq;
        //��������������������������������� copier la solution dans tempsol ����������������������
        //���������������������������������������������������������������������������������������
        //tempsol = solution;
        //tempsol->plan = new vector <int>(solution->plan->size());
        //tempsol->planCC = new vector <double>(solution->planCC->size());
        solution->PlanAffect = new vector< pair<int,int> > ();
        // tempsol->PIObj = solution->PIObj;
        // tempsol->PSObj = solution->PSObj;
        for(i=0;i<solution->plan->size();i++)
        {
            //tempsol->plan->at(i) = solution->plan->at(i);
            //tempsol->planCC->at(i) = solution->planCC->at(i);
           // tempsol->PIObj = solution->PIObj;
            //tempsol->PSObj = solution->PSObj;
            if(solution->plan->at(i)!=-1)//si la case dans le plan n'est pas vide on remplie le planAffect
            {
                solution->PlanAffect->push_back({i,solution->plan->at(i)});
            }
        }

        //����������������������������������������������������������
        //���������������������������������������������������������������
        //   tempsol->planCC=NULL;
        //LF comment: on traverse tte les fr�quence et on calcule le cout
        int victimFrequency,interfererFrequency;
        int victimTrx,interfererTrx;
        victimTrx = trx.trxID;

        int taille;
        //..........................................................
        //..........................................................
        //vecteur pour enregistrer le couple de cout  interference, separation � la fois
        vector < pair<double,double>  > paircost ;
        //----------------------
        if(trx.AvailableFrequencies->empty()==false)
        {
           taille =trx.AvailableFrequencies->size();

            vector<double> * veccost = new vector <double>(taille);
                 vector<double> * cost = new vector <double>(taille);
            if (taille>1)
            {
                for(i=0 ;i < taille ; i++)//pour chaque fr�quence probable on evalue le cout
                {

                    victimFrequency =trx.AvailableFrequencies->at(i);
                    veccost->at(i)=0.0;
                    cost->at(i)=0.0;
                    solution->PlanAffect->push_back({trx.trxID,victimFrequency});
                    //on �value la solution avec le nouveau couple : {victimTrx,victimFrequency}
                   int victimTrx1 = trx.trxID; int victimFrequency1 = trx.AvailableFrequencies->at(i);
                    for(j=0;j< solution->PlanAffect->size();j++)
                    {

                        victimTrx = solution->PlanAffect->at(j).first;
                        victimFrequency = solution->PlanAffect->at(j).second;
                       interfererTrx = solution->PlanAffect->at(j).first;
                        interfererFrequency = solution->PlanAffect->at(j).second;
                        if ( interfererTrx != victimTrx1)
                        {
                           // calculer le cout d interference
                            veccost->at(i)  = veccost->at(i)  + afpProblem->computeChannelInterference(victimFrequency1 ,interfererFrequency, victimTrx1, interfererTrx)+
                            afpProblem->computeChannelInterference(interfererFrequency,victimFrequency1 ,interfererTrx, victimTrx1);
                            //cout de separation
                           if(afpProblem->trxs[victimTrx1].sectorID == afpProblem->trxs[interfererTrx].sectorID)
                            {
                                //on teste si la contraite de separation co-secteur est respect�!!
                                if (abs (interfererFrequency-victimFrequency1)<3 )//contrainte co secteur viol�e
                                {
                                    cost->at(i) = cost->at(i) + 1.0;
                                }
                            }// secteur different
                            else
                            {
                                if(afpProblem->trxs[victimTrx1].siteID  == afpProblem->trxs[interfererTrx].siteID)
                                {
                        //on teste si la contrainte de separation co-site est respect�e!!
                                    if (abs (interfererFrequency-victimFrequency1)< 2)//contrainte co secteur viol�e
                                    {
                                        cost->at(i) = cost->at(i) + 1.0;
                                    }
                                }//
                            }
                        }

                    }// for(j=0 ;j < taille ; j++)//pour chaque fr�quence probable on evalue le cout
                    //.............................................................................
                    //.............................................................................
                    // enregister les couts dans le vecteur
                  //  cout << veccost->at(i) << veccost->at(i) << endl;
                    veccost->at(i) = veccost->at(i) + solution->PIObj ;
                    cost->at(i) = cost->at(i) + solution->PSObj ;
                    paircost.push_back({veccost->at(i),cost->at(i)});
                    //...................................................................
                    solution->PlanAffect->pop_back();//on retire le couple probable apres evaluation de cout et l avoir enregistr� dans veccost
                    // cout<<"frequence ::" <<trx.AvailableFrequencies->at(i)<<", son sout veccost[i] ==="<< veccost->at(i)<<endl;
                } //fortrx.AvailableFrequencies


 //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
     //DOMINANCE
   //
                 //...................................................
                 //.....................................................
                // I . Retirer la non dominance pour chaque fr�quence
                // ....................................................
                //...................................................

                //je supose que la soluution est domiin�e et je vais tester si c est vrai

                    //+++++++++++++Laidi modifi� +++++++++++++++++++++++++++++++++++
      //je supose que la soluution est domiin�e et je vais tester si c est vrai
            int rank;
  int counter;
  int DominantScore;
  int temp = 0;
  rank = 1;
  vector < pair<int,double> > IndexesFreqsNonDominantes;
    IndexesFreqsNonDominantes.reserve(paircost.size());
    int taille=paircost.size();
    int array_rank[paircost.size()];
    counter =paircost.size();


    for (int i=0; i<paircost.size(); i++)
    {
      DominantScore=0;

	  for (int j=0; j<paircost.size(); j++)
	  {
        if (i!=j)
        {


                           /* if (!((paircost[i].first <= paircost[j].first) && (paircost[i].second < paircost[j].second)))
                             DominantScore   = DominantScore +   1;*/
                            if (!((paircost[i].second <= paircost[j].second) && (paircost[i].first <paircost[j].first)))
                             DominantScore   = DominantScore +   1;
        }//i!=j
       } //fin j
		if (DominantScore==0)
        {
          // indices.push_back(i); // pour sauvgarder les indices des solution non dominées dans la nouvelle population
           IndexesFreqsNonDominantes.push_back({i,paircost[i].second});
        }
	}//fin i



              if (IndexesFreqsNonDominantes.size()!= 0)
              {
                  //cout << " la taille du vect solutions non dom PS == " << IndexesFreqsNonDominantes.size()<< endl;
                 // sort(IndexesFreqsNonDominantes.begin(),IndexesFreqsNonDominantes.end(),my_cmpInfDoublePair);//trier selon un ordre croissant de cout
                sort(IndexesFreqsNonDominantes.begin(),IndexesFreqsNonDominantes.end(),my_cmpInfDoublePair);
                //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                //~~~~~~~~~~~~~~~~~~~~~~~~~~~si plusieurs fr�queences  non domlinates ont le meme cout on choisit
                // al�atoirement une
                //---------------------------------------------------
                i = 0;     k = 0 ;
                //------------------------------------
                for(i = 0 ; i < IndexesFreqsNonDominantes.size(); i++)
                {
                    //double val = IndexesFreqsNonDominantes.at(i).second;
                    double val = IndexesFreqsNonDominantes.at(i).second;
                    //pair<int,double> pnextval;
                    pair<int,double> pnextval;
                    if((i+1) < IndexesFreqsNonDominantes.size())
                    {
                        pnextval = IndexesFreqsNonDominantes.at(i+1);
                        //double nextval = pnextval.second;
                        double nextval = pnextval.second;
                        // on copie les valeurs egales dans un tableau
                        //cout<< "hiiii here " << endl;
                        if( val == nextval )
                        {
                            k = k +1 ;//k contient le nombre de valeur �gale
                        }
                        else
                        {
                            i = IndexesFreqsNonDominantes.size();
                        }
                    }
                }
                int indice ;
              //  indice = rand() % (k+1);// coisir une parmi les "n" premier
               // indexmin = IndexesFreqsNonDominantes.at(indice).first;// r�cup�ration de l'indice de la fr�quence
               // cout << "k ������������������" << k << endl;

            vector< pair < int, double > > VectHV;

            VectHV.reserve(k+1);
            int indicefreq;
            indicefreq = IndexesFreqsNonDominantes.at(0).first;
             pair<double,double> Min;
            pair<double,double> Max;
            pair < double, double > R;// est le point de r�f�rence ; la valeur max (normalis�)
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
    Normalize(paircost,Min,Max);
    for(i=0; i<= k; i++)
    {
        int valindice = IndexesFreqsNonDominantes.at(i).first;
        double X = paircost.at(valindice).first ;
        double Y = paircost.at(valindice).second ;
        double ValHV = (R.first - X)* (R.second - Y);
        VectHV.push_back({valindice,ValHV});
    }

    //**********************************************************

            sort(VectHV.begin(),VectHV.end(),my_cmpSupDoublePair);
            indexmin = VectHV.front().first;// r�cup�ration de l'indice de la fr�quence













              }
               else// il n y a aucune valeur dans le front pareto
               {
                 //cout << " taille 0000000000000000 " << endl;
                 // vecmin(cost, indexmin);//indexmin:indice de la fr�quencence qui a la valeur minimale
                 StrategyFreq = 2;//3 : ecart, 6: hv , 2 : minimum cost
                 PSChooseFrequency(instance,StrategyFreq,trx,f,solution,afpProblem);
                 return;

               }
    //............................End dominance ......................................
    //................................................................................
    //................................................................................
    f=trx.AvailableFrequencies->at(indexmin);//indice de la fr�quence recherch�
    solution->PIObj = veccost->at(indexmin);
    solution->PSObj = cost->at(indexmin);
    //delete(tempsol->PlanAffect);
    vector < pair<double,double> > ().swap(paircost) ;
    vector < pair<int,double> > ().swap(IndexesFreqsNonDominantes);
    delete(veccost);
    delete(cost);
    //delete(tempsol->PlanAffect);
    delete(solution->PlanAffect);
    //--------------------- dominance available
    }//if (taille >1)
    else
    {
       if(taille==1) // la taille  == 1; je n ai qu'un choix
        {
            f=trx.AvailableFrequencies->at(0);
            // cout<<" frequency choisit:lorsque la taille est 0"<<f<<endl;
            // cout<<"hii"<<endl;
            delete(solution->PlanAffect);
        }
    }//taille :.!=1
 }// Availablefrequencies is empty()
else//Availablefrequencies==empty() // aucune fr�quence n'est diponible j'utilise les fr�quence valides
        {// on choisit la meilleur fr�quence VALID

            //****************#################################""
        //----------------------
        if(trx.validFrequencies->empty()==false)
        {
            taille =trx.validFrequencies->size();
            vector<double> * veccost = new vector <double>(taille);
                vector<double> * cost = new vector <double>(taille);
            if (taille>1)
            {
                for(i=0 ;i < taille ; i++)//pour chaque fr�quence probable on evalue le cout
                {
                    victimFrequency =trx.validFrequencies->at(i);
                     veccost->at(i)=0.0;
                    cost->at(i)=0.0;
                    solution->PlanAffect->push_back({trx.trxID,victimFrequency});
                    //on �value la solution avec le nouveau couple : {victimTrx,victimFrequency}
                   int victimTrx1 = trx.trxID; int victimFrequency1 = trx.AvailableFrequencies->at(i);
                    for(j=0;j< solution->PlanAffect->size();j++)
                    {

                        victimTrx = solution->PlanAffect->at(j).first;
                        victimFrequency = solution->PlanAffect->at(j).second;
                       interfererTrx = solution->PlanAffect->at(j).first;
                        interfererFrequency = solution->PlanAffect->at(j).second;
                        if ( interfererTrx != victimTrx1)
                        {
                           // calculer le cout d interference
                            veccost->at(i)  = veccost->at(i)  + afpProblem->computeChannelInterference(victimFrequency1 ,interfererFrequency, victimTrx1, interfererTrx)+
                            afpProblem->computeChannelInterference(interfererFrequency,victimFrequency1 ,interfererTrx, victimTrx1);
                            //cout de separation
                           if(afpProblem->trxs[victimTrx1].sectorID == afpProblem->trxs[interfererTrx].sectorID)
                            {
                                //on teste si la contraite de separation co-secteur est respect�!!
                                if (abs (interfererFrequency-victimFrequency1)<3 )//contrainte co secteur viol�e
                                {
                                    cost->at(i) = cost->at(i) + 1.0;
                                }
                            }// secteur different
                            else
                            {
                                if(afpProblem->trxs[victimTrx1].siteID  == afpProblem->trxs[interfererTrx].siteID)
                                {
                        //on teste si la contrainte de separation co-site est respect�e!!
                                    if (abs (interfererFrequency-victimFrequency1)< 2)//contrainte co secteur viol�e
                                    {
                                        cost->at(i) = cost->at(i) + 1.0;
                                    }
                                }//
                            }
                        }

                    }// for(j=0 ;j < taille ; j++)//pour chaque fr�quence probable on evalue le cout
                    //.............................................................................
                    //.............................................................................
                    // enregister les couts dans le vecteur
                  //  cout << veccost->at(i) << veccost->at(i) << endl;
                    veccost->at(i) = veccost->at(i) + solution->PIObj ;
                    cost->at(i) = cost->at(i) + solution->PSObj ;
                    paircost.push_back({veccost->at(i),cost->at(i)});
                    //...................................................................
                    solution->PlanAffect->pop_back();//on retire le couple probable apres evaluation de cout et l avoir enregistr� dans veccost
                    // cout<<"frequence ::" <<trx.AvailableFrequencies->at(i)<<", son sout veccost[i] ==="<< veccost->at(i)<<endl;
                } //fortrx.Av
          //..............................................................
                //...................................................................................

        //DOMINANCE


                 //...................................................
                 //.....................................................
                // I . Retirer la non dominance pour chaque fr�quence
                // ....................................................
                //...................................................

                 int  DominantScore;

                vector < pair<int,int> > IndexesFreqsNonDominantes;
                 //(int,int) :: le premier enregistre l index de la fr�quence non dominante
                  //(int,int) :: le dexieme , combien de fois la fr�quence est non dominante
                IndexesFreqsNonDominantes.reserve(trx.validFrequencies->size());
        //+++++++++++++Laidi modifi� +++++++++++++++++++++++++++++++++++
          for( i = 0; i < trx.AvailableFrequencies->size();i++)//la solution condidate est dans l indice i
                {

                  DominantScore = 0 ;// pour compter le nombre de solution qui domine la solution courante

                  for( j = i+1; j < trx.AvailableFrequencies->size() ;j++)
                   {
                       if (i!=j)
                       {

                           if (paircost[i].first > paircost[j].first) // on teste la dominance par rapport au premier objectif
                            {
                                // on ne peut pas juger on test par rapport au deuxime obj
                                if (paircost[i].second > paircost[j].second)
                                         {

                                                  //on est sur qu elle est dominante
                                                DominantScore    =   DominantScore+1 ;


                                         }
                                         else
                                         {
                                             if(paircost[i].first >= paircost[j].first)
                                              {
                                                    DominantScore    =   DominantScore+1 ;
                                              }
                                         }

                            }
                            else
                            {
                                if (paircost[i].second >= paircost[j].second)
                                    {
                                        DominantScore    =   DominantScore+1 ;
                                    }

                            }


                        }//i!=j
                    }//fin j

						if (DominantScore==0)// pour s'assurer que la solution "i" est non dominée
                      {
                        IndexesFreqsNonDominantes.push_back({i,paircost[i].first});// on insert l'index de la solution et son cout d'interférences
                      }
                       // cout << "la solution " << i << " est dominee par  " << DominantScore << " autres solutions" << endl;
                }//fin i

            //cout <<"IndexesFreqsNonDominantes.size()PIII  "<< IndexesFreqsNonDominantes.size() <<endl;*/
                //----------------------------------------------------------------------
                 //+++++++++++++ sol par sol +++++++++++++++++++++++++++++++++++
                 //++++++++++++++++++ tout les sol
                  int  nondominancescore;
                  //cout << "trx.AvailableFrequencies->size()++++ "<< trx.AvailableFrequencies->size() <<endl;

                      for( i = 0; i < trx.validFrequencies->size();i++)//la solution condidate est dans l indice i
                {

                  nondominancescore = 0 ;// pour compter le nombre de solution qui domine la solution courante

                   for( j = 0; j < trx.AvailableFrequencies->size() ;j++)
                   {

                       if (i!=j)
                       {

                                   if (paircost[i].first <= paircost[j].first)  // on teste la dominance par rapport au deuciÃ¨me objectif
                                    {
                                          if (paircost[i].second < paircost[j].second)

                                        {
                                            IndexesFreqsNonDominantes.push_back({i,paircost[i].first});

                                            nondominancescore = nondominancescore + 1;
                                            }
                                        }


                                    //--- j insere le deuxi�me obj
                                  /* else
                                    {
                                         if (paircost[i].second <= paircost[j].second) // teste la dominance par rapport au deuciÃ¨me objectif
                                        {
                                                if (paircost[i].first < paircost[j].first) // on
                                                {
                                                    IndexesFreqsNonDominantes.push_back({i,paircost[i].first});
                                            //au deuxieme obj

                                                nondominancescore = nondominancescore+1;
                                                }
                                            //}
                                        }
                                    }*/

                       }//i!=j
                   }//fin j
                   /*  if (nondominancescore > (trx.AvailableFrequencies->size() - 2 ))
                  IndexesFreqsNonDominantes.push_back({i,paircost[i].first});*/

              }//fin i
            // cout <<"IndexesFreqsNonDominantes.size()PIII  "<< IndexesFreqsNonDominantes.size() <<endl;



                //...................................................
                 //.....................................................
                // II . Trier le tableau de la non dominance selon un ordre croissant si la liste n est pas vide
                // ....................................................
                //...................................................
              //  sort(IndexesFreqsNonDominantes.begin(),IndexesFreqsNonDominantes.end(),my_cmp);
             // cout << "  IndexesFreqsNonDominantes.size() ****"<< IndexesFreqsNonDominantes.size() << endl;


                // copier les solution trouver dans un vecteur avec son cout d interferqunce qui
                if (IndexesFreqsNonDominantes.size()!= 0 )
                {
                    /*vector < pair < int, double> > NonDominanteCost;
                    NonDominanteCost.reserve(IndexesFreqsNonDominantes.size());
                    for(i = 0; i < IndexesFreqsNonDominantes.size(); i++ )
                    {
                        NonDominanteCost.push_back({IndexesFreqsNonDominantes[i].first, paircost[IndexesFreqsNonDominantes[i].first].first });
                    }*/
                // trier le tableau selon un ordre d�croisant du cout et retirer la premi�re valeur
                    sort(IndexesFreqsNonDominantes.begin(),IndexesFreqsNonDominantes.end(),my_cmpInfDoublePair);
                   // indexmin = IndexesFreqsNonDominantes.front().first;
                   //si des valeur de cout �gale on choisit al�atoirement parmi ces valeur
                   //+++++++++++++++++++++++++++++++++++++++++++
                   k=0;
                   for(i = 0 ; i < IndexesFreqsNonDominantes.size(); i++)
                    {
                        double val = IndexesFreqsNonDominantes.at(i).second;
                        pair<int,double> pnextval;
                        if((i+1) < IndexesFreqsNonDominantes.size())
                        {
                            pnextval = IndexesFreqsNonDominantes.at(i+1);
                            double nextval = pnextval.second;
                            // on copie les valeurs egales dans un tableau
                            //cout<< "hiiii here " << endl;
                            if( val == nextval )
                            {
                                k = k +1 ;//k contient le nombre de valeur �gale
                                // cout<< "hiiii here " << endl;
                            }
                            else
                            {
                                i = IndexesFreqsNonDominantes.size();
                            }
                        }
                    }
    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                    int indexf = rand() % (k+1);
                    indexmin = IndexesFreqsNonDominantes.at(indexf).first;

                }
                else
                {
                     vecmin(veccost, indexmin);//indexmin:indice de la fr�quencence qui a la valeur minimale
                }

                //................................................................................

//--------------------- dominance available
                //..............................................................
                //...................................................................................

    //vider la m�moire--vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
    vector < pair<double,double>  >().swap(paircost) ;
    delete(veccost);
    delete(solution->PlanAffect);
                //..............................................................
                //...................................................................................
                f=trx.validFrequencies->at(indexmin);//indice de la fr�quence ayant un cout minimal,

    //+++++++++++++++++++++++++++++++

            }//taille >1
            else
            {
                if(taille==1)
                {
                    f=trx.validFrequencies->at(0);
                // cout<<" frequency choisit:lorsque la taille est 0"<<f<<endl;
                // cout<<"hii"<<endl;
                }
            }//taille == 1?!!
        }
        else//Availablefrequencies==empty()
        {
            cout<<" la liste des fr�quences valide est vide **"<<endl;
        }
















            //******************
            //cout<<" la liste des fr�quences disponibles est vide **"<<endl;
        }
    break;
    }//case 502 : best frequency Front pareto inspir� Plus grand HV

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   case  +52 ://strategy 5 choisir la meilleur fr�quence en terme Front parteo pure
    {
          int i,indexmin,j,k;
       // Individual * tempsol =  new Individual();
        int tempfreq;
        //��������������������������������� copier la solution dans tempsol ����������������������
        //���������������������������������������������������������������������������������������
        //tempsol = solution;
        //tempsol->plan = new vector <int>(solution->plan->size());
        //tempsol->planCC = new vector <double>(solution->planCC->size());
        solution->PlanAffect = new vector< pair<int,int> > ();
        // tempsol->PIObj = solution->PIObj;
        // tempsol->PSObj = solution->PSObj;
        for(i=0;i<solution->plan->size();i++)
        {
            //tempsol->plan->at(i) = solution->plan->at(i);
            //tempsol->planCC->at(i) = solution->planCC->at(i);
           // tempsol->PIObj = solution->PIObj;
            //tempsol->PSObj = solution->PSObj;
            if(solution->plan->at(i)!=-1)//si la case dans le plan n'est pas vide on remplie le planAffect
            {
                solution->PlanAffect->push_back({i,solution->plan->at(i)});
            }
        }

        //����������������������������������������������������������
        //���������������������������������������������������������������
        //   tempsol->planCC=NULL;
        //LF comment: on traverse tte les fr�quence et on calcule le cout
        int victimFrequency,interfererFrequency;
        int victimTrx,interfererTrx;
        victimTrx = trx.trxID;

        int taille;
        //..........................................................
        //..........................................................
        //vecteur pour enregistrer le couple de cout  interference, separation � la fois
        vector < pair<double,double>  > paircost ;
        //----------------------
        if(trx.AvailableFrequencies->empty()==false)
        {
           taille =trx.AvailableFrequencies->size();

            vector<double> * veccost = new vector <double>(taille);
                 vector<double> * cost = new vector <double>(taille);
            if (taille>1)
            {
                for(i=0 ;i < taille ; i++)//pour chaque fr�quence probable on evalue le cout
                {

                    victimFrequency =trx.AvailableFrequencies->at(i);
                    veccost->at(i)=0.0;
                    cost->at(i)=0.0;
                    solution->PlanAffect->push_back({trx.trxID,victimFrequency});
                    //on �value la solution avec le nouveau couple : {victimTrx,victimFrequency}
                   int victimTrx1 = trx.trxID; int victimFrequency1 = trx.AvailableFrequencies->at(i);
                    for(j=0;j< solution->PlanAffect->size();j++)
                    {

                        victimTrx = solution->PlanAffect->at(j).first;
                        victimFrequency = solution->PlanAffect->at(j).second;
                       interfererTrx = solution->PlanAffect->at(j).first;
                        interfererFrequency = solution->PlanAffect->at(j).second;
                        if ( interfererTrx != victimTrx1)
                        {
                           // calculer le cout d interference
                            veccost->at(i)  = veccost->at(i)  + afpProblem->computeChannelInterference(victimFrequency1 ,interfererFrequency, victimTrx1, interfererTrx)+
                            afpProblem->computeChannelInterference(interfererFrequency,victimFrequency1 ,interfererTrx, victimTrx1);
                            //cout de separation
                           if(afpProblem->trxs[victimTrx1].sectorID == afpProblem->trxs[interfererTrx].sectorID)
                            {
                                //on teste si la contraite de separation co-secteur est respect�!!
                                if (abs (interfererFrequency-victimFrequency1)<3 )//contrainte co secteur viol�e
                                {
                                    cost->at(i) = cost->at(i) + 1.0;
                                }
                            }// secteur different
                            else
                            {
                                if(afpProblem->trxs[victimTrx1].siteID  == afpProblem->trxs[interfererTrx].siteID)
                                {
                        //on teste si la contrainte de separation co-site est respect�e!!
                                    if (abs (interfererFrequency-victimFrequency1)< 2)//contrainte co secteur viol�e
                                    {
                                        cost->at(i) = cost->at(i) + 1.0;
                                    }
                                }//
                            }
                        }

                    }// for(j=0 ;j < taille ; j++)//pour chaque fr�quence probable on evalue le cout
                    //.............................................................................
                    //.............................................................................
                    // enregister les couts dans le vecteur
                  //  cout << veccost->at(i) << veccost->at(i) << endl;
                    veccost->at(i) = veccost->at(i) + solution->PIObj ;
                    cost->at(i) = cost->at(i) + solution->PSObj ;
                    paircost.push_back({veccost->at(i),cost->at(i)});
                    //...................................................................
                    solution->PlanAffect->pop_back();//on retire le couple probable apres evaluation de cout et l avoir enregistr� dans veccost
                    // cout<<"frequence ::" <<trx.AvailableFrequencies->at(i)<<", son sout veccost[i] ==="<< veccost->at(i)<<endl;
                } //fortrx.AvailableFrequencies


 //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
     //DOMINANCE
   //
                 //...................................................
                 //.....................................................
                // I . Retirer la non dominance pour chaque fr�quence
                // ....................................................
                //...................................................

                //je supose que la soluution est domiin�e et je vais tester si c est vrai

                    //+++++++++++++Laidi modifi� +++++++++++++++++++++++++++++++++++
      //je supose que la soluution est domiin�e et je vais tester si c est vrai
                int  NonDominantScore, DominantScore;

                vector < pair<int,int> > IndexesFreqsNonDominantes;
                int flag1, flag2, index;
                double interCost;
                 //(int,int) :: le premier enregistre l index de la fr�quence non dominante
                  //(int,int) :: le dexieme , combien de fois la fr�quence est non dominante
                IndexesFreqsNonDominantes.reserve(trx.AvailableFrequencies->size());

                for( i = 0; i < trx.AvailableFrequencies->size();i++)//la solution condidate est dans l indice i
                {

                  DominantScore = 0 ;// pour compter le nombre de solution qui domine la solution courante

                   for( j = 0; j < trx.AvailableFrequencies->size();j++)
                   {
                        //Laidi ---

                                /*
                               flag1 = 0;
                               flag2 = 0;
                               if (paircost[i].first >= paircost[j].first)
                                flag1++;

                               if (paircost[i].first > paircost[j].first)
                                flag2++;

                               if (paircost[i].second >= paircost[j].second)
                                flag1++;

                               if (paircost[i].second > paircost[j].second)
                                flag2++;


                          if (flag1 >= 2 && flag2>=1){ //pour tester la condition de dominance pour nos deux objectifs
          //array_domination_count[i] = array_domination_count[i] + 1; // lpour compter le nbr de solution qui domine la solution i
                              DominantScore= DominantScore+1; //pour la solution 'i'
                           }

                        */
                             /*if (paircost[i].first > paircost[j].first)
                                   {
                                      if (paircost[i].second >= paircost[j].second)
                                       DominantScore   = DominantScore +   1; //pour la solution 'i'
                                   }


                                    if (paircost[i].second > paircost[j].second)
                                        {
                                            if(paircost[i].first >= paircost[j].first)
                                            DominantScore   = DominantScore +   1; //pour la solution 'i'
                                        }*/
                                        if(i!=j)
                                       {


                         if ((!((paircost[i].first <= paircost[j].first) && (paircost[i].second < paircost[j].second)))
                            && (!((paircost[i].second <= paircost[j].second) && (paircost[i].first <paircost[j].first))))
                             DominantScore   = DominantScore +   1;
                        /* if (!((paircost[i].second <= paircost[j].second) && (paircost[i].first <paircost[j].first)))
                             DominantScore   = DominantScore +   1;*/
                                       }


                 }

                     /* if (DominantScore == 0)
                  IndexesFreqsNonDominantes.push_back({i,paircost[i].second}); // contient l'indice de la fr�quence frqq ainsi que le cout d'interf�rences
                */
                //j ins�re pour chque solution f son score
                 IndexesFreqsNonDominantes.push_back({i,DominantScore});
                }//fin i
               // cout << " la taille des frqs non dominee PI == " << IndexesFreqsNonDominantes.size() << endl ;
                //+++++++++++++++++++++++++++++++++++++++Afficher paircost

           //++++++++++++++++++++++++++++++++++++++++++++++++++++++++

                //...................................................
                 //.....................................................
                // II . Trier le tableau de la non dominance selon un ordre croissant
                // ....................................................
                //...................................................
              //  sort(IndexesFreqsNonDominantes.begin(),IndexesFreqsNonDominantes.end(),my_cmp);
              //  cout << "  IndexesFreqsNonDominantes.size() ****"<< IndexesFreqsNonDominantes.size() << endl;


                // copier les solution trouver dans un vecteur avec son cout d interferqunce qui
               /* vector < pair < int, double> > NonDominanteCost;//contient l indice des valeur non domin�e et le cout
                NonDominanteCost.reserve(IndexesFreqsNonDominantes.size());
                for(i = 0; i < IndexesFreqsNonDominantes.size(); i++ )
                {
                    NonDominanteCost.push_back({IndexesFreqsNonDominantes[i].first, paircost[IndexesFreqsNonDominantes[i].first].first });
                }*/
                // trier le tableau selon un ordre d�croisant du cout et retirer la premi�re valeur
              // cout << " ���������IndexesFreqsNonDominantes.size() " << IndexesFreqsNonDominantes.size() <<endl;

              if (IndexesFreqsNonDominantes.size()!= 0)
              {
                  //cout << " la taille du vect solutions non dom PS == " << IndexesFreqsNonDominantes.size()<< endl;
                 // sort(IndexesFreqsNonDominantes.begin(),IndexesFreqsNonDominantes.end(),my_cmpInfDoublePair);//trier selon un ordre croissant de cout
                sort(IndexesFreqsNonDominantes.begin(),IndexesFreqsNonDominantes.end(),my_cmpInf);
                //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                //~~~~~~~~~~~~~~~~~~~~~~~~~~~si plusieurs fr�queences  non domlinates ont le meme cout on choisit
                // al�atoirement une
                //---------------------------------------------------
                i = 0;     k = 0 ;
                for(i = 0 ; i < IndexesFreqsNonDominantes.size(); i++)
                {
                    //double val = IndexesFreqsNonDominantes.at(i).second;
                    int val = IndexesFreqsNonDominantes.at(i).second;
                    //pair<int,double> pnextval;
                    pair<int,int> pnextval;
                    if((i+1) < IndexesFreqsNonDominantes.size())
                    {
                        pnextval = IndexesFreqsNonDominantes.at(i+1);
                        //double nextval = pnextval.second;
                        int nextval = pnextval.second;
                        // on copie les valeurs egales dans un tableau
                        //cout<< "hiiii here " << endl;
                        if( val == nextval )
                        {
                            k = k +1 ;//k contient le nombre de valeur �gale
                            // cout<< "hiiii here " << endl;

                        }
                        else
                        {
                            i = IndexesFreqsNonDominantes.size();
                        }
                    }
                }
                //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                int indice ;
                indice = rand() % (k+1);// coisir une parmi les "n" premier
              //  cout << " k �����������" << k << endl;
                indexmin = IndexesFreqsNonDominantes.at(indice).first;// r�cup�ration de l'indice de la fr�quence
              }
               else// il n y a aucune valeur dans le front pareto
                {
                        cout << " taille 0000000000000000 " << endl;
                         vecmin(cost, indexmin);//indexmin:indice de la fr�quencence qui a la valeur minimale


            }


    //............................End dominance ..................................
    //..............................................................
    //................................................................................
    f=trx.AvailableFrequencies->at(indexmin);//indice de la fr�quence recherch�
    solution->PIObj = veccost->at(indexmin);
    solution->PSObj = cost->at(indexmin);
    solution->planCC->at(trx.trxID).first = solution->PIObj;
    solution->planCC->at(trx.trxID).second = solution->PSObj;
      //delete(tempsol->PlanAffect);
       vector < pair<double,double>  >().swap(paircost) ;
    vector < pair<int,int> > ().swap(IndexesFreqsNonDominantes);
    delete(veccost);
    delete(cost);
    //delete(tempsol->PlanAffect);
    delete(solution->PlanAffect);
    //--------------------- dominance available
    }//if (taille >1)
    else
    {
       if(taille==1) // la taille  == 1; je n ai qu'un choix
        {
            f=trx.AvailableFrequencies->at(0);
            // cout<<" frequency choisit:lorsque la taille est 0"<<f<<endl;
            // cout<<"hii"<<endl;
            delete(solution->PlanAffect);
        }
    }//taille :.!=1
 }// Availablefrequencies is empty()
else//Availablefrequencies==empty() // aucune fr�quence n'est diponible j'utilise les fr�quence valides
        {// on choisit la meilleur fr�quence VALID

            //****************#################################""
        //----------------------
        if(trx.validFrequencies->empty()==false)
        {
            taille =trx.validFrequencies->size();
            vector<double> * veccost = new vector <double>(taille);
                vector<double> * cost = new vector <double>(taille);
            if (taille>1)
            {
                for(i=0 ;i < taille ; i++)//pour chaque fr�quence probable on evalue le cout
                {
                    victimFrequency =trx.validFrequencies->at(i);
                     veccost->at(i)=0.0;
                    cost->at(i)=0.0;
                    solution->PlanAffect->push_back({trx.trxID,victimFrequency});
                    //on �value la solution avec le nouveau couple : {victimTrx,victimFrequency}
                   int victimTrx1 = trx.trxID; int victimFrequency1 = trx.AvailableFrequencies->at(i);
                    for(j=0;j< solution->PlanAffect->size();j++)
                    {

                        victimTrx = solution->PlanAffect->at(j).first;
                        victimFrequency = solution->PlanAffect->at(j).second;
                       interfererTrx = solution->PlanAffect->at(j).first;
                        interfererFrequency = solution->PlanAffect->at(j).second;
                        if ( interfererTrx != victimTrx1)
                        {
                           // calculer le cout d interference
                            veccost->at(i)  = veccost->at(i)  + afpProblem->computeChannelInterference(victimFrequency1 ,interfererFrequency, victimTrx1, interfererTrx)+
                            afpProblem->computeChannelInterference(interfererFrequency,victimFrequency1 ,interfererTrx, victimTrx1);
                            //cout de separation
                           if(afpProblem->trxs[victimTrx1].sectorID == afpProblem->trxs[interfererTrx].sectorID)
                            {
                                //on teste si la contraite de separation co-secteur est respect�!!
                                if (abs (interfererFrequency-victimFrequency1)<3 )//contrainte co secteur viol�e
                                {
                                    cost->at(i) = cost->at(i) + 1.0;
                                }
                            }// secteur different
                            else
                            {
                                if(afpProblem->trxs[victimTrx1].siteID  == afpProblem->trxs[interfererTrx].siteID)
                                {
                        //on teste si la contrainte de separation co-site est respect�e!!
                                    if (abs (interfererFrequency-victimFrequency1)< 2)//contrainte co secteur viol�e
                                    {
                                        cost->at(i) = cost->at(i) + 1.0;
                                    }
                                }//
                            }
                        }

                    }// for(j=0 ;j < taille ; j++)//pour chaque fr�quence probable on evalue le cout
                    //.............................................................................
                    //.............................................................................
                    // enregister les couts dans le vecteur
                  //  cout << veccost->at(i) << veccost->at(i) << endl;
                    veccost->at(i) = veccost->at(i) + solution->PIObj ;
                    cost->at(i) = cost->at(i) + solution->PSObj ;
                    paircost.push_back({veccost->at(i),cost->at(i)});
                    //...................................................................
                    solution->PlanAffect->pop_back();//on retire le couple probable apres evaluation de cout et l avoir enregistr� dans veccost
                    // cout<<"frequence ::" <<trx.AvailableFrequencies->at(i)<<", son sout veccost[i] ==="<< veccost->at(i)<<endl;
                } //fortrx.Av
          //..............................................................
                //...................................................................................

        //DOMINANCE


                 //...................................................
                 //.....................................................
                // I . Retirer la non dominance pour chaque fr�quence
                // ....................................................
                //...................................................

                 int  DominantScore;

                vector < pair<int,int> > IndexesFreqsNonDominantes;
                 //(int,int) :: le premier enregistre l index de la fr�quence non dominante
                  //(int,int) :: le dexieme , combien de fois la fr�quence est non dominante
                IndexesFreqsNonDominantes.reserve(trx.validFrequencies->size());
        //+++++++++++++Laidi modifi� +++++++++++++++++++++++++++++++++++
          for( i = 0; i < trx.AvailableFrequencies->size();i++)//la solution condidate est dans l indice i
                {

                  DominantScore = 0 ;// pour compter le nombre de solution qui domine la solution courante

                  for( j = i+1; j < trx.AvailableFrequencies->size() ;j++)
                   {
                       if (i!=j)
                       {

                           if (paircost[i].first > paircost[j].first) // on teste la dominance par rapport au premier objectif
                            {
                                // on ne peut pas juger on test par rapport au deuxime obj
                                if (paircost[i].second > paircost[j].second)
                                         {

                                                  //on est sur qu elle est dominante
                                                DominantScore    =   DominantScore+1 ;


                                         }
                                         else
                                         {
                                             if(paircost[i].first >= paircost[j].first)
                                              {
                                                    DominantScore    =   DominantScore+1 ;
                                              }
                                         }

                            }
                            else
                            {
                                if (paircost[i].second >= paircost[j].second)
                                    {
                                        DominantScore    =   DominantScore+1 ;
                                    }

                            }


                        }//i!=j
                    }//fin j

						if (DominantScore==0)// pour s'assurer que la solution "i" est non dominée
                      {
                        IndexesFreqsNonDominantes.push_back({i,paircost[i].first});// on insert l'index de la solution et son cout d'interférences
                      }
                       // cout << "la solution " << i << " est dominee par  " << DominantScore << " autres solutions" << endl;
                }//fin i

            //cout <<"IndexesFreqsNonDominantes.size()PIII  "<< IndexesFreqsNonDominantes.size() <<endl;*/
                //----------------------------------------------------------------------
                 //+++++++++++++ sol par sol +++++++++++++++++++++++++++++++++++
                 //++++++++++++++++++ tout les sol
                  int  nondominancescore;
                  //cout << "trx.AvailableFrequencies->size()++++ "<< trx.AvailableFrequencies->size() <<endl;

                      for( i = 0; i < trx.validFrequencies->size();i++)//la solution condidate est dans l indice i
                {

                  nondominancescore = 0 ;// pour compter le nombre de solution qui domine la solution courante

                   for( j = 0; j < trx.AvailableFrequencies->size() ;j++)
                   {

                       if (i!=j)
                       {

                                   if (paircost[i].first <= paircost[j].first)  // on teste la dominance par rapport au deuciÃ¨me objectif
                                    {
                                          if (paircost[i].second < paircost[j].second)

                                        {
                                            IndexesFreqsNonDominantes.push_back({i,paircost[i].first});

                                            nondominancescore = nondominancescore + 1;
                                            }
                                        }


                                    //--- j insere le deuxi�me obj
                                  /* else
                                    {
                                         if (paircost[i].second <= paircost[j].second) // teste la dominance par rapport au deuciÃ¨me objectif
                                        {
                                                if (paircost[i].first < paircost[j].first) // on
                                                {
                                                    IndexesFreqsNonDominantes.push_back({i,paircost[i].first});
                                            //au deuxieme obj

                                                nondominancescore = nondominancescore+1;
                                                }
                                            //}
                                        }
                                    }*/

                       }//i!=j
                   }//fin j
                   /*  if (nondominancescore > (trx.AvailableFrequencies->size() - 2 ))
                  IndexesFreqsNonDominantes.push_back({i,paircost[i].first});*/

              }//fin i
            // cout <<"IndexesFreqsNonDominantes.size()PIII  "<< IndexesFreqsNonDominantes.size() <<endl;



                //...................................................
                 //.....................................................
                // II . Trier le tableau de la non dominance selon un ordre croissant si la liste n est pas vide
                // ....................................................
                //...................................................
              //  sort(IndexesFreqsNonDominantes.begin(),IndexesFreqsNonDominantes.end(),my_cmp);
             // cout << "  IndexesFreqsNonDominantes.size() ****"<< IndexesFreqsNonDominantes.size() << endl;


                // copier les solution trouver dans un vecteur avec son cout d interferqunce qui
                if (IndexesFreqsNonDominantes.size()!= 0 )
                {
                    /*vector < pair < int, double> > NonDominanteCost;
                    NonDominanteCost.reserve(IndexesFreqsNonDominantes.size());
                    for(i = 0; i < IndexesFreqsNonDominantes.size(); i++ )
                    {
                        NonDominanteCost.push_back({IndexesFreqsNonDominantes[i].first, paircost[IndexesFreqsNonDominantes[i].first].first });
                    }*/
                // trier le tableau selon un ordre d�croisant du cout et retirer la premi�re valeur
                    sort(IndexesFreqsNonDominantes.begin(),IndexesFreqsNonDominantes.end(),my_cmpInfDoublePair);
                   // indexmin = IndexesFreqsNonDominantes.front().first;
                   //si des valeur de cout �gale on choisit al�atoirement parmi ces valeur
                   //+++++++++++++++++++++++++++++++++++++++++++
                   k=0;
                   for(i = 0 ; i < IndexesFreqsNonDominantes.size(); i++)
                    {
                        double val = IndexesFreqsNonDominantes.at(i).second;
                        pair<int,double> pnextval;
                        if((i+1) < IndexesFreqsNonDominantes.size())
                        {
                            pnextval = IndexesFreqsNonDominantes.at(i+1);
                            double nextval = pnextval.second;
                            // on copie les valeurs egales dans un tableau
                            //cout<< "hiiii here " << endl;
                            if( val == nextval )
                            {
                                k = k +1 ;//k contient le nombre de valeur �gale
                                // cout<< "hiiii here " << endl;
                            }
                            else
                            {
                                i = IndexesFreqsNonDominantes.size();
                            }
                        }
                    }
    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                    int indexf = rand() % (k+1);
                    indexmin = IndexesFreqsNonDominantes.at(indexf).first;

                }
                else
                {
                     vecmin(veccost, indexmin);//indexmin:indice de la fr�quencence qui a la valeur minimale
                }

                //................................................................................

//--------------------- dominance available
                //..............................................................
                //...................................................................................

    //vider la m�moire--vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
    vector < pair<double,double>  >().swap(paircost) ;
    delete(veccost);
    delete(solution->PlanAffect);
                //..............................................................
                //...................................................................................
                f=trx.validFrequencies->at(indexmin);//indice de la fr�quence ayant un cout minimal,

    //+++++++++++++++++++++++++++++++

            }//taille >1
            else
            {
                if(taille==1)
                {
                    f=trx.validFrequencies->at(0);
                // cout<<" frequency choisit:lorsque la taille est 0"<<f<<endl;
                // cout<<"hii"<<endl;
                }
            }//taille == 1?!!
        }
        else//Availablefrequencies==empty()
        {
            cout<<" la liste des fr�quences valide est vide **"<<endl;
        }
















            //******************
            //cout<<" la liste des fr�quences disponibles est vide **"<<endl;
        }
    break;
    }//case 52  : best frequency Front pareto pure




    //**************************************************************
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ FRONt PARETO egoiste~~~~~~~~~~~~~~~~~~~~~~
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
     case  500 ://strategy 5 choisir la meilleur fr�quence en terme Front parteo inspir� al�atoire
    {
        int i,indexmin,j,k;
       // Individual * tempsol =  new Individual();
        int tempfreq;
        //��������������������������������� copier la solution dans tempsol ����������������������
        //���������������������������������������������������������������������������������������
        //tempsol = solution;
        //tempsol->plan = new vector <int>(solution->plan->size());
        //tempsol->planCC = new vector <double>(solution->planCC->size());
        solution->PlanAffect = new vector< pair<int,int> > ();
        // tempsol->PIObj = solution->PIObj;
        // tempsol->PSObj = solution->PSObj;
        for(i=0;i<solution->plan->size();i++)
        {
            //tempsol->plan->at(i) = solution->plan->at(i);
            //tempsol->planCC->at(i) = solution->planCC->at(i);
           // tempsol->PIObj = solution->PIObj;
            //tempsol->PSObj = solution->PSObj;
            if(solution->plan->at(i)!=-1)//si la case dans le plan n'est pas vide on remplie le planAffect
            {
                solution->PlanAffect->push_back({i,solution->plan->at(i)});
            }
        }

        //����������������������������������������������������������
        //���������������������������������������������������������������
        //   tempsol->planCC=NULL;
        //LF comment: on traverse tte les fr�quence et on calcule le cout
        int victimFrequency,interfererFrequency;
        int victimTrx,interfererTrx;
        victimTrx = trx.trxID;

        int taille;
        //..........................................................
        //..........................................................
        //vecteur pour enregistrer le couple de cout  interference, separation � la fois
        vector < pair<double,double>  > paircost ;
        //----------------------
        if(trx.AvailableFrequencies->empty()==false)
        {
           taille =trx.AvailableFrequencies->size();

            vector<double> * veccost = new vector <double>(taille);
                 vector<double> * cost = new vector <double>(taille);
            if (taille>1)
            {
                for(i=0 ;i < taille ; i++)//pour chaque fr�quence probable on evalue le cout
                {

                    victimFrequency =trx.AvailableFrequencies->at(i);
                    veccost->at(i)=0.0;
                    cost->at(i)=0.0;
                    solution->PlanAffect->push_back({trx.trxID,victimFrequency});
                    //on �value la solution avec le nouveau couple : {victimTrx,victimFrequency}
                   int victimTrx1 = trx.trxID; int victimFrequency1 = trx.AvailableFrequencies->at(i);
                    for(j=0;j< solution->PlanAffect->size();j++)
                    {

                        victimTrx = solution->PlanAffect->at(j).first;
                        victimFrequency = solution->PlanAffect->at(j).second;
                       interfererTrx = solution->PlanAffect->at(j).first;
                        interfererFrequency = solution->PlanAffect->at(j).second;
                        if ( interfererTrx != victimTrx1)
                        {
                           // calculer le cout d interference
                            veccost->at(i)  = veccost->at(i)  + afpProblem->computeChannelInterference(victimFrequency1 ,interfererFrequency, victimTrx1, interfererTrx)+
                            afpProblem->computeChannelInterference(interfererFrequency,victimFrequency1 ,interfererTrx, victimTrx1);
                            //cout de separation
                           if(afpProblem->trxs[victimTrx1].sectorID == afpProblem->trxs[interfererTrx].sectorID)
                            {
                                //on teste si la contraite de separation co-secteur est respect�!!
                                if (abs (interfererFrequency-victimFrequency1)<3 )//contrainte co secteur viol�e
                                {
                                    cost->at(i) = cost->at(i) + 1.0;
                                }
                            }// secteur different
                            else
                            {
                                if(afpProblem->trxs[victimTrx1].siteID  == afpProblem->trxs[interfererTrx].siteID)
                                {
                        //on teste si la contrainte de separation co-site est respect�e!!
                                    if (abs (interfererFrequency-victimFrequency1)< 2)//contrainte co secteur viol�e
                                    {
                                        cost->at(i) = cost->at(i) + 1.0;
                                    }
                                }//
                            }
                        }

                    }// for(j=0 ;j < taille ; j++)//pour chaque fr�quence probable on evalue le cout
                    //.............................................................................
                    //.............................................................................
                    // enregister les couts dans le vecteur
                  //  cout << veccost->at(i) << veccost->at(i) << endl;
                    veccost->at(i) = veccost->at(i) + solution->PIObj ;
                    cost->at(i) = cost->at(i) + solution->PSObj ;
                    paircost.push_back({veccost->at(i),cost->at(i)});
                    //...................................................................
                    solution->PlanAffect->pop_back();//on retire le couple probable apres evaluation de cout et l avoir enregistr� dans veccost
                    // cout<<"frequence ::" <<trx.AvailableFrequencies->at(i)<<", son sout veccost[i] ==="<< veccost->at(i)<<endl;
                } //fortrx.AvailableFrequencies

    //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
     //DOMINANCE
   //
                 //je supose que la soluution est domiin�e et je vais tester si c est vrai
                int  NonDominantScore, DominantScore;

                vector < pair<int,int> > IndexesFreqsNonDominantes;
                int flag1, flag2, index;
                double interCost;
                 //(int,int) :: le premier enregistre l index de la fr�quence non dominante
                  //(int,int) :: le dexieme , combien de fois la fr�quence est non dominante
                IndexesFreqsNonDominantes.reserve(trx.AvailableFrequencies->size());

                for( i = 0; i < trx.AvailableFrequencies->size();i++)//la solution condidate est dans l indice i
                {

                  DominantScore = 0 ;// pour compter le nombre de solution qui domine la solution courante

                   for( j = 0; j < trx.AvailableFrequencies->size();j++)
                   {

                        if(i!=j)
                        {

                           /* if (!((paircost[i].first <= paircost[j].first) && (paircost[i].second < paircost[j].second)))
                             DominantScore   = DominantScore +   1;*/
                            if (!((paircost[i].second <= paircost[j].second) && (paircost[i].first <paircost[j].first)))
                             DominantScore   = DominantScore +   1;

                        }
                    }

                     /* if (DominantScore == 0)
                  IndexesFreqsNonDominantes.push_back({i,paircost[i].second}); // contient l'indice de la fr�quence frqq ainsi que le cout d'interf�rences
                */
                //j ins�re pour chque solution f son score
                 IndexesFreqsNonDominantes.push_back({i,DominantScore});
                }//fin i
               // cout << " la taille des frqs non dominee PI == " << IndexesFreqsNonDominantes.size() << endl ;
                //+++++++++++++++++++++++++++++++++++++++Afficher paircost

           //++++++++++++++++++++++++++++++++++++++++++++++++++++++++

                //...................................................
                 //.....................................................
                // II . Trier le tableau de la non dominance selon un ordre croissant
                // ....................................................
                //...................................................
              //  sort(IndexesFreqsNonDominantes.begin(),IndexesFreqsNonDominantes.end(),my_cmp);
              //  cout << "  IndexesFreqsNonDominantes.size() ****"<< IndexesFreqsNonDominantes.size() << endl;


                // copier les solution trouver dans un vecteur avec son cout d interferqunce qui
               /* vector < pair < int, double> > NonDominanteCost;//contient l indice des valeur non domin�e et le cout
                NonDominanteCost.reserve(IndexesFreqsNonDominantes.size());
                for(i = 0; i < IndexesFreqsNonDominantes.size(); i++ )
                {
                    NonDominanteCost.push_back({IndexesFreqsNonDominantes[i].first, paircost[IndexesFreqsNonDominantes[i].first].first });
                }*/
                // trier le tableau selon un ordre d�croisant du cout et retirer la premi�re valeur
              // cout << " ���������IndexesFreqsNonDominantes.size() " << IndexesFreqsNonDominantes.size() <<endl;

              if (IndexesFreqsNonDominantes.size()!= 0)
              {
                  //cout << " la taille du vect solutions non dom PS == " << IndexesFreqsNonDominantes.size()<< endl;
                 // sort(IndexesFreqsNonDominantes.begin(),IndexesFreqsNonDominantes.end(),my_cmpInfDoublePair);//trier selon un ordre croissant de cout
                sort(IndexesFreqsNonDominantes.begin(),IndexesFreqsNonDominantes.end(),my_cmpInf);
                //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                //~~~~~~~~~~~~~~~~~~~~~~~~~~~si plusieurs fr�queences  non domlinates ont le meme cout on choisit
                // al�atoirement une
                //---------------------------------------------------
                i = 0;     k = 0 ;
                for(i = 0 ; i < IndexesFreqsNonDominantes.size(); i++)
                {
                    //double val = IndexesFreqsNonDominantes.at(i).second;
                    int val = IndexesFreqsNonDominantes.at(i).second;
                    //pair<int,double> pnextval;
                    pair<int,int> pnextval;
                    if((i+1) < IndexesFreqsNonDominantes.size())
                    {
                        pnextval = IndexesFreqsNonDominantes.at(i+1);
                        //double nextval = pnextval.second;
                        int nextval = pnextval.second;
                        // on copie les valeurs egales dans un tableau
                        //cout<< "hiiii here " << endl;
                        if( val == nextval )
                        {
                            k = k +1 ;//k contient le nombre de valeur �gale
                            // cout<< "hiiii here " << endl;

                        }
                        else
                        {
                            i = IndexesFreqsNonDominantes.size();
                        }
                    }
                }
                //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                int indice ;
                indice = rand() % (k+1);// coisir une parmi les "n" premier
                   //cout << " k �����������" << k << endl;
                indexmin = IndexesFreqsNonDominantes.at(indice).first;// r�cup�ration de l'indice de la fr�quence
              }
               else// il n y a aucune valeur dans le front pareto
                {
                        cout << " taille 000000000000000" << endl;
                        vecmin(veccost, indexmin);//indexmin:indice de la fr�quencence qui a la valeur minimale

            }


    f=trx.AvailableFrequencies->at(indexmin);//indice de la fr�quence recherch�
    //cout <<"fff " << f<<endl;
      solution->PIObj = veccost->at(indexmin);
     solution->PSObj = cost->at(indexmin);
    //+++++++++++++++++++++++++++++++


    //++++++++++++++++++++
     //vider la m�moire--vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
    vector < pair<double,double>  >().swap(paircost) ;
    vector < pair<int,int> > ().swap(IndexesFreqsNonDominantes);
    delete(veccost);
    delete(cost);
    //delete(tempsol->PlanAffect);
    delete(solution->PlanAffect);
            //vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
    //--------------------- dominance available
    }//if (taille >1)
    else
    {
       if(taille==1) // la taille  == 1; je n ai qu'un choix
        {
            f=trx.AvailableFrequencies->at(0);
            delete(solution->PlanAffect);
            // cout<<" frequency choisit:lorsque la taille est 0"<<f<<endl;
            // cout<<"hii"<<endl;
        }
    }//taille :.!=1
 }// Availablefrequencies is empty()
else//Availablefrequencies==empty() // aucune fr�quence n'est diponible j'utilise les fr�quence valides
        {// on choisit la meilleur fr�quence VALID

            //****************#################################""
        //----------------------
        if(trx.validFrequencies->empty()==false)
        {
            taille =trx.validFrequencies->size();
            vector<double> * veccost = new vector <double>(taille);
            vector<double> * cost = new vector <double>(taille);
            if (taille>1)
            {
                for(i=0 ;i < taille ; i++)//pour chaque fr�quence probable on evalue le cout
                {
                    victimFrequency =trx.validFrequencies->at(i);
                     veccost->at(i)=0.0;
                    cost->at(i)=0.0;
                    solution->PlanAffect->push_back({trx.trxID,victimFrequency});
                    //on �value la solution avec le nouveau couple : {victimTrx,victimFrequency}
                   int victimTrx1 = trx.trxID; int victimFrequency1 = trx.AvailableFrequencies->at(i);
                    for(j=0;j< solution->PlanAffect->size();j++)
                    {

                        victimTrx = solution->PlanAffect->at(j).first;
                        victimFrequency = solution->PlanAffect->at(j).second;
                       interfererTrx = solution->PlanAffect->at(j).first;
                        interfererFrequency = solution->PlanAffect->at(j).second;
                        if ( interfererTrx != victimTrx1)
                        {
                           // calculer le cout d interference
                            veccost->at(i)  = veccost->at(i)  + afpProblem->computeChannelInterference(victimFrequency1 ,interfererFrequency, victimTrx1, interfererTrx)+
                            afpProblem->computeChannelInterference(interfererFrequency,victimFrequency1 ,interfererTrx, victimTrx1);
                            //cout de separation
                           if(afpProblem->trxs[victimTrx1].sectorID == afpProblem->trxs[interfererTrx].sectorID)
                            {
                                //on teste si la contraite de separation co-secteur est respect�!!
                                if (abs (interfererFrequency-victimFrequency1)<3 )//contrainte co secteur viol�e
                                {
                                    cost->at(i) = cost->at(i) + 1.0;
                                }
                            }// secteur different
                            else
                            {
                                if(afpProblem->trxs[victimTrx1].siteID  == afpProblem->trxs[interfererTrx].siteID)
                                {
                        //on teste si la contrainte de separation co-site est respect�e!!
                                    if (abs (interfererFrequency-victimFrequency1)< 2)//contrainte co secteur viol�e
                                    {
                                        cost->at(i) = cost->at(i) + 1.0;
                                    }
                                }//
                            }
                        }

                    }// for(j=0 ;j < taille ; j++)//pour chaque fr�quence probable on evalue le cout
                    //.............................................................................
                    //.............................................................................
                    // enregister les couts dans le vecteur
                  //  cout << veccost->at(i) << veccost->at(i) << endl;
                    veccost->at(i) = veccost->at(i) + solution->PIObj ;
                    cost->at(i) = cost->at(i) + solution->PSObj ;
                    paircost.push_back({veccost->at(i),cost->at(i)});
                    //...................................................................
                    solution->PlanAffect->pop_back();//on retire le couple probable apres evaluation de cout et l avoir enregistr� dans veccost
                    // cout<<"frequence ::" <<trx.AvailableFrequencies->at(i)<<", son sout veccost[i] ==="<< veccost->at(i)<<endl;
                } //fortrx.AvailableFrequencies

 //DOMINANCE--------------------chercher les solution dominantes et l'enregistrer dans les indexes
   //  des fr�quences dans le  tableau IndexesFreqsDominantes

               int  DominantScore;

                vector < pair<int,int> > IndexesFreqsNonDominantes;
                 //(int,int) :: le premier enregistre l index de la fr�quence non dominante
                  //(int,int) :: le dexieme , combien de fois la fr�quence est non dominante
                IndexesFreqsNonDominantes.reserve(trx.validFrequencies->size());
        //+++++++++++++Laidi modifi� +++++++++++++++++++++++++++++++++++
         /* for( i = 0; i < trx.AvailableFrequencies->size();i++)//la solution condidate est dans l indice i
                {

                  DominantScore = 0 ;// pour compter le nombre de solution qui domine la solution courante

                  for( j = 0; j < trx.AvailableFrequencies->size() ;j++)
                   {
                       if (i!=j)
                       {

                           if (paircost[i].first > paircost[j].first) // on teste la dominance par rapport au premier objectif
                            {
                                // on ne peut pas juger on test par rapport au deuxime obj
                                if (paircost[i].second > paircost[j].second)
                                         {

                                                  //on est sur qu elle est dominante
                                                DominantScore    =   DominantScore+1 ;


                                         }
                                         else
                                         {
                                             if(paircost[i].first >= paircost[j].first)
                                              {
                                                    DominantScore    =   DominantScore+1 ;
                                              }
                                         }

                            }
                            else
                            {
                                if (paircost[i].second >= paircost[j].second)
                                    {
                                        DominantScore    =   DominantScore+1 ;
                                    }

                            }


                        }//i!=j
                    }//fin j

						if (DominantScore==0)// pour s'assurer que la solution "i" est non dominée
                      {
                        IndexesFreqsNonDominantes.push_back({i,paircost[i].first});// on insert l'index de la solution et son cout d'interférences
                      }
                       // cout << "la solution " << i << " est dominee par  " << DominantScore << " autres solutions" << endl;
                }//fin i

            cout <<"IndexesFreqsNonDominantes.size()PIII  "<< IndexesFreqsNonDominantes.size() <<endl;*/
                //----------------------------------------------------------------------
                 //+++++++++++++ sol par sol +++++++++++++++++++++++++++++++++++
                 //++++++++++++++++++ tout les sol
                  int  nondominancescore;
                  //cout << "trx.AvailableFrequencies->size()++++ "<< trx.AvailableFrequencies->size() <<endl;

                      for( i = 0; i < trx.validFrequencies->size();i++)//la solution condidate est dans l indice i
                {

                  nondominancescore = 0 ;// pour compter le nombre de solution qui domine la solution courante

                   for( j = 0; j < trx.AvailableFrequencies->size() ;j++)
                   {

                       if (i!=j)
                       {

                                   if (paircost[i].first <= paircost[j].first)  // on teste la dominance par rapport au deuciÃ¨me objectif
                                    {
                                          if (paircost[i].second < paircost[j].second)

                                        {
                                            IndexesFreqsNonDominantes.push_back({i,paircost[i].first});

                                            nondominancescore = nondominancescore + 1;
                                            }
                                        }


                                    //--- j insere le deuxi�me obj
                                  /* else
                                    {
                                         if (paircost[i].second <= paircost[j].second) // teste la dominance par rapport au deuciÃ¨me objectif
                                        {
                                                if (paircost[i].first < paircost[j].first) // on
                                                {
                                                    IndexesFreqsNonDominantes.push_back({i,paircost[i].first});
                                            //au deuxieme obj

                                                nondominancescore = nondominancescore+1;
                                                }
                                            //}
                                        }
                                    }*/

                       }//i!=j
                   }//fin j
                   /*  if (nondominancescore > (trx.AvailableFrequencies->size() - 2 ))
                  IndexesFreqsNonDominantes.push_back({i,paircost[i].first});*/

              }//fin i
            // cout <<"IndexesFreqsNonDominantes.size()PIII  "<< IndexesFreqsNonDominantes.size() <<endl;



                //...................................................
                 //.....................................................
                // II . Trier le tableau de la non dominance selon un ordre croissant si la liste n est pas vide
                // ....................................................
                //...................................................
              //  sort(IndexesFreqsNonDominantes.begin(),IndexesFreqsNonDominantes.end(),my_cmp);
             // cout << "  IndexesFreqsNonDominantes.size() ****"<< IndexesFreqsNonDominantes.size() << endl;


                // copier les solution trouver dans un vecteur avec son cout d interferqunce qui
                if (IndexesFreqsNonDominantes.size()!= 0 )
                {
                    /*vector < pair < int, double> > NonDominanteCost;
                    NonDominanteCost.reserve(IndexesFreqsNonDominantes.size());
                    for(i = 0; i < IndexesFreqsNonDominantes.size(); i++ )
                    {
                        NonDominanteCost.push_back({IndexesFreqsNonDominantes[i].first, paircost[IndexesFreqsNonDominantes[i].first].first });
                    }*/
                // trier le tableau selon un ordre d�croisant du cout et retirer la premi�re valeur
                    sort(IndexesFreqsNonDominantes.begin(),IndexesFreqsNonDominantes.end(),my_cmpInfDoublePair);
                   // indexmin = IndexesFreqsNonDominantes.front().first;
                   //si des valeur de cout �gale on choisit al�atoirement parmi ces valeur
                   //+++++++++++++++++++++++++++++++++++++++++++
                   k=0;
                   for(i = 0 ; i < IndexesFreqsNonDominantes.size(); i++)
                    {
                        double val = IndexesFreqsNonDominantes.at(i).second;
                        pair<int,double> pnextval;
                        if((i+1) < IndexesFreqsNonDominantes.size())
                        {
                            pnextval = IndexesFreqsNonDominantes.at(i+1);
                            double nextval = pnextval.second;
                            // on copie les valeurs egales dans un tableau
                            //cout<< "hiiii here " << endl;
                            if( val == nextval )
                            {
                                k = k +1 ;//k contient le nombre de valeur �gale
                                // cout<< "hiiii here " << endl;
                            }
                            else
                            {
                                i = IndexesFreqsNonDominantes.size();
                            }
                        }
                    }
    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                    int indexf = rand() % (k+1);
                    indexmin = IndexesFreqsNonDominantes.at(indexf).first;

                }
                else
                {
                     vecmin(veccost, indexmin);//indexmin:indice de la fr�quencence qui a la valeur minimale
                }

                //................................................................................

//--------------------- dominance available
                //..............................................................
                //...................................................................................
                f=trx.validFrequencies->at(indexmin);//indice de la fr�quence ayant un cout minimal,
    //vider la m�moire--vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
    vector < pair<double,double>  >().swap(paircost) ;
    delete(veccost);
    delete(solution->PlanAffect);
    //vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
            }//taille >1
            else
            {
                if(taille==1)
                {
                    f=trx.validFrequencies->at(0);
                // cout<<" frequency choisit:lorsque la taille est 0"<<f<<endl;
                // cout<<"hii"<<endl;
                }
            }//taille == 1?!!
        }
        else//Availablefrequencies==empty()
        {
            cout<<" la liste des fr�quences valide est vide **"<<endl;
        }

           //******************
            //cout<<" la liste des fr�quences disponibles est vide **"<<endl;
        }
    break;
    }//case 5  : best frequency Front pareto egoiste
    //------------------------------------------------------------------------------
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ FRONt PARETO egoiste ~~~~~~~~~~~~~~~~~~~~~~
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //-------------------------------------------
    //--------------------------------------------------
 case  501 ://strategy 5 choisir la meilleur fr�quence en terme Front parteo. si plusieurs fr�quence
     //dans le meme front pareto , on choisit celle qui a le minimum ecart entre CI et CS
    {
          int i,indexmin,j,k;
       // Individual * tempsol =  new Individual();
        int tempfreq;
        //��������������������������������� copier la solution dans tempsol ����������������������
        //���������������������������������������������������������������������������������������
        //tempsol = solution;
        //tempsol->plan = new vector <int>(solution->plan->size());
        //tempsol->planCC = new vector <double>(solution->planCC->size());
        solution->PlanAffect = new vector< pair<int,int> > ();
        // tempsol->PIObj = solution->PIObj;
        // tempsol->PSObj = solution->PSObj;
        for(i=0;i<solution->plan->size();i++)
        {
            //tempsol->plan->at(i) = solution->plan->at(i);
            //tempsol->planCC->at(i) = solution->planCC->at(i);
           // tempsol->PIObj = solution->PIObj;
            //tempsol->PSObj = solution->PSObj;
            if(solution->plan->at(i)!=-1)//si la case dans le plan n'est pas vide on remplie le planAffect
            {
                solution->PlanAffect->push_back({i,solution->plan->at(i)});
            }
        }

        //����������������������������������������������������������
        //���������������������������������������������������������������
        //   tempsol->planCC=NULL;
        //LF comment: on traverse tte les fr�quence et on calcule le cout
        int victimFrequency,interfererFrequency;
        int victimTrx,interfererTrx;
        victimTrx = trx.trxID;

        int taille;
        //..........................................................
        //..........................................................
        //vecteur pour enregistrer le couple de cout  interference, separation � la fois
        vector < pair<double,double>  > paircost ;
        //----------------------
        if(trx.AvailableFrequencies->empty()==false)
        {
           taille =trx.AvailableFrequencies->size();

            vector<double> * veccost = new vector <double>(taille);
                 vector<double> * cost = new vector <double>(taille);
            if (taille>1)
            {
                for(i=0 ;i < taille ; i++)//pour chaque fr�quence probable on evalue le cout
                {

                    victimFrequency =trx.AvailableFrequencies->at(i);
                    veccost->at(i)=0.0;
                    cost->at(i)=0.0;
                    solution->PlanAffect->push_back({trx.trxID,victimFrequency});
                    //on �value la solution avec le nouveau couple : {victimTrx,victimFrequency}
                   int victimTrx1 = trx.trxID; int victimFrequency1 = trx.AvailableFrequencies->at(i);
                    for(j=0;j< solution->PlanAffect->size();j++)
                    {

                        victimTrx = solution->PlanAffect->at(j).first;
                        victimFrequency = solution->PlanAffect->at(j).second;
                       interfererTrx = solution->PlanAffect->at(j).first;
                        interfererFrequency = solution->PlanAffect->at(j).second;
                        if ( interfererTrx != victimTrx1)
                        {
                           // calculer le cout d interference
                            veccost->at(i)  = veccost->at(i)  + afpProblem->computeChannelInterference(victimFrequency1 ,interfererFrequency, victimTrx1, interfererTrx)+
                            afpProblem->computeChannelInterference(interfererFrequency,victimFrequency1 ,interfererTrx, victimTrx1);
                            //cout de separation
                           if(afpProblem->trxs[victimTrx1].sectorID == afpProblem->trxs[interfererTrx].sectorID)
                            {
                                //on teste si la contraite de separation co-secteur est respect�!!
                                if (abs (interfererFrequency-victimFrequency1)<3 )//contrainte co secteur viol�e
                                {
                                    cost->at(i) = cost->at(i) + 1.0;
                                }
                            }// secteur different
                            else
                            {
                                if(afpProblem->trxs[victimTrx1].siteID  == afpProblem->trxs[interfererTrx].siteID)
                                {
                        //on teste si la contrainte de separation co-site est respect�e!!
                                    if (abs (interfererFrequency-victimFrequency1)< 2)//contrainte co secteur viol�e
                                    {
                                        cost->at(i) = cost->at(i) + 1.0;
                                    }
                                }//
                            }
                        }

                    }// for(j=0 ;j < taille ; j++)//pour chaque fr�quence probable on evalue le cout
                    //.............................................................................
                    //.............................................................................
                    // enregister les couts dans le vecteur
                  //  cout << veccost->at(i) << veccost->at(i) << endl;
                    veccost->at(i) = veccost->at(i) + solution->PIObj ;
                    cost->at(i) = cost->at(i) + solution->PSObj ;
                    paircost.push_back({veccost->at(i),cost->at(i)});
                    //...................................................................
                    solution->PlanAffect->pop_back();//on retire le couple probable apres evaluation de cout et l avoir enregistr� dans veccost
                    // cout<<"frequence ::" <<trx.AvailableFrequencies->at(i)<<", son sout veccost[i] ==="<< veccost->at(i)<<endl;
                } //fortrx.AvailableFrequencies


 //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
     //DOMINANCE
   //
                 //...................................................
                 //.....................................................
                // I . Retirer la non dominance pour chaque fr�quence
                // ....................................................
                //...................................................

                //je supose que la soluution est domiin�e et je vais tester si c est vrai

                    //+++++++++++++Laidi modifi� +++++++++++++++++++++++++++++++++++
      //je supose que la soluution est domiin�e et je vais tester si c est vrai
                int  NonDominantScore, DominantScore;

                vector < pair<int,int> > IndexesFreqsNonDominantes;
                int flag1, flag2, index;
                double interCost;
                 //(int,int) :: le premier enregistre l index de la fr�quence non dominante
                  //(int,int) :: le dexieme , combien de fois la fr�quence est non dominante
                IndexesFreqsNonDominantes.reserve(trx.AvailableFrequencies->size());

                for( i = 0; i < trx.AvailableFrequencies->size();i++)//la solution condidate est dans l indice i
                {

                  DominantScore = 0 ;// pour compter le nombre de solution qui domine la solution courante

                   for( j = 0; j < trx.AvailableFrequencies->size();j++)
                   {

                                        if(i!=j)
                                       {


                        /* if (!((paircost[i].first <= paircost[j].first) && (paircost[i].second < paircost[j].second)))
                             DominantScore   = DominantScore +   1;*/
                         if (!((paircost[i].second <= paircost[j].second) && (paircost[i].first <paircost[j].first)))
                             DominantScore   = DominantScore +   1;
                                       }


                 }

                 IndexesFreqsNonDominantes.push_back({i,DominantScore});
                }//fin i
               // cout << " la taille des frqs non dominee PI == " << IndexesFreqsNonDominantes.size() << endl ;
                //+++++++++++++++++++++++++++++++++++++++Afficher paircost

           //++++++++++++++++++++++++++++++++++++++++++++++++++++++++

                //...................................................
                 //.....................................................
                // II . Trier le tableau de la non dominance selon un ordre croissant
                // ....................................................
                //...................................................
              //  sort(IndexesFreqsNonDominantes.begin(),IndexesFreqsNonDominantes.end(),my_cmp);
              //  cout << "  IndexesFreqsNonDominantes.size() ****"<< IndexesFreqsNonDominantes.size() << endl;


                // copier les solution trouver dans un vecteur avec son cout d interferqunce qui
               /* vector < pair < int, double> > NonDominanteCost;//contient l indice des valeur non domin�e et le cout
                NonDominanteCost.reserve(IndexesFreqsNonDominantes.size());
                for(i = 0; i < IndexesFreqsNonDominantes.size(); i++ )
                {
                    NonDominanteCost.push_back({IndexesFreqsNonDominantes[i].first, paircost[IndexesFreqsNonDominantes[i].first].first });
                }*/
                // trier le tableau selon un ordre d�croisant du cout et retirer la premi�re valeur
              // cout << " ���������IndexesFreqsNonDominantes.size() " << IndexesFreqsNonDominantes.size() <<endl;

              if (IndexesFreqsNonDominantes.size()!= 0)
              {
                  //cout << " la taille du vect solutions non dom PS == " << IndexesFreqsNonDominantes.size()<< endl;
                 // sort(IndexesFreqsNonDominantes.begin(),IndexesFreqsNonDominantes.end(),my_cmpInfDoublePair);//trier selon un ordre croissant de cout
                sort(IndexesFreqsNonDominantes.begin(),IndexesFreqsNonDominantes.end(),my_cmpInf);
                //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                //~~~~~~~~~~~~~~~~~~~~~~~~~~~si plusieurs fr�queences  non domlinates ont le meme cout on choisit
                // al�atoirement une
                //---------------------------------------------------
                i = 0;     k = 0 ;
                for(i = 0 ; i < IndexesFreqsNonDominantes.size(); i++)
                {
                    //double val = IndexesFreqsNonDominantes.at(i).second;
                    int val = IndexesFreqsNonDominantes.at(i).second;
                    //pair<int,double> pnextval;
                    pair<int,int> pnextval;
                    if((i+1) < IndexesFreqsNonDominantes.size())
                    {
                        pnextval = IndexesFreqsNonDominantes.at(i+1);
                        //double nextval = pnextval.second;
                        int nextval = pnextval.second;
                        // on copie les valeurs egales dans un tableau
                        //cout<< "hiiii here " << endl;
                        if( val == nextval )
                        {
                            k = k +1 ;//k contient le nombre de valeur �gale
                            // cout<< "hiiii here " << endl;

                        }
                        else
                        {
                            i = IndexesFreqsNonDominantes.size();
                        }
                    }
                }
                //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                int indice ;
            //    indice = rand() % (k+1);// coisir une parmi les "n" premier
            //cr�er un tableau des k valeurs �gales en terme de dominance score


            vector < pair< int, double> > distance;
            distance.reserve(k+1);
            int indicefreq;
            indicefreq = IndexesFreqsNonDominantes.at(0).first;
             double v = abs(veccost->at(indicefreq)- cost->at(indicefreq));
            distance.push_back({indicefreq,v});
            for(i = 1 ;i < k ; i++)
            {
                indicefreq = IndexesFreqsNonDominantes.at(i).first;
                v  =  abs(veccost->at(indicefreq)- cost->at(indicefreq));
                distance.push_back({indicefreq,v});
            }
            sort(distance.begin(),distance.end(),my_cmpInfDoublePair);








                indexmin = distance.front().first;// r�cup�ration de l'indice de la fr�quenc
              }
               else// il n y a aucune valeur dans le front pareto
                {
                        cout << " taille 0000000000000000 " << endl;
                         vecmin(cost, indexmin);//indexmin:indice de la fr�quencence qui a la valeur minimale


            }


    //............................End dominance ..................................
    //..............................................................
    //................................................................................
    f=trx.AvailableFrequencies->at(indexmin);//indice de la fr�quence recherch�
     solution->PIObj = veccost->at(indexmin);
      solution->PSObj = cost->at(indexmin);
      //delete(tempsol->PlanAffect);
       vector < pair<double,double>  >().swap(paircost) ;
    vector < pair<int,int> > ().swap(IndexesFreqsNonDominantes);
    delete(veccost);
    delete(cost);
    //delete(tempsol->PlanAffect);
    delete(solution->PlanAffect);
    //--------------------- dominance available
    }//if (taille >1)
    else
    {
       if(taille==1) // la taille  == 1; je n ai qu'un choix
        {
            f=trx.AvailableFrequencies->at(0);
            // cout<<" frequency choisit:lorsque la taille est 0"<<f<<endl;
            // cout<<"hii"<<endl;
            delete(solution->PlanAffect);
        }
    }//taille :.!=1
 }// Availablefrequencies is empty()
else//Availablefrequencies==empty() // aucune fr�quence n'est diponible j'utilise les fr�quence valides
        {// on choisit la meilleur fr�quence VALID

            //****************#################################""
        //----------------------
        if(trx.validFrequencies->empty()==false)
        {
            taille =trx.validFrequencies->size();
            vector<double> * veccost = new vector <double>(taille);
                vector<double> * cost = new vector <double>(taille);
            if (taille>1)
            {
                for(i=0 ;i < taille ; i++)//pour chaque fr�quence probable on evalue le cout
                {
                    victimFrequency =trx.validFrequencies->at(i);
                     veccost->at(i)=0.0;
                    cost->at(i)=0.0;
                    solution->PlanAffect->push_back({trx.trxID,victimFrequency});
                    //on �value la solution avec le nouveau couple : {victimTrx,victimFrequency}
                   int victimTrx1 = trx.trxID; int victimFrequency1 = trx.AvailableFrequencies->at(i);
                    for(j=0;j< solution->PlanAffect->size();j++)
                    {

                        victimTrx = solution->PlanAffect->at(j).first;
                        victimFrequency = solution->PlanAffect->at(j).second;
                       interfererTrx = solution->PlanAffect->at(j).first;
                        interfererFrequency = solution->PlanAffect->at(j).second;
                        if ( interfererTrx != victimTrx1)
                        {
                           // calculer le cout d interference
                            veccost->at(i)  = veccost->at(i)  + afpProblem->computeChannelInterference(victimFrequency1 ,interfererFrequency, victimTrx1, interfererTrx)+
                            afpProblem->computeChannelInterference(interfererFrequency,victimFrequency1 ,interfererTrx, victimTrx1);
                            //cout de separation
                           if(afpProblem->trxs[victimTrx1].sectorID == afpProblem->trxs[interfererTrx].sectorID)
                            {
                                //on teste si la contraite de separation co-secteur est respect�!!
                                if (abs (interfererFrequency-victimFrequency1)<3 )//contrainte co secteur viol�e
                                {
                                    cost->at(i) = cost->at(i) + 1.0;
                                }
                            }// secteur different
                            else
                            {
                                if(afpProblem->trxs[victimTrx1].siteID  == afpProblem->trxs[interfererTrx].siteID)
                                {
                        //on teste si la contrainte de separation co-site est respect�e!!
                                    if (abs (interfererFrequency-victimFrequency1)< 2)//contrainte co secteur viol�e
                                    {
                                        cost->at(i) = cost->at(i) + 1.0;
                                    }
                                }//
                            }
                        }

                    }// for(j=0 ;j < taille ; j++)//pour chaque fr�quence probable on evalue le cout
                    //.............................................................................
                    //.............................................................................
                    // enregister les couts dans le vecteur
                  //  cout << veccost->at(i) << veccost->at(i) << endl;
                    veccost->at(i) = veccost->at(i) + solution->PIObj ;
                    cost->at(i) = cost->at(i) + solution->PSObj ;
                    paircost.push_back({veccost->at(i),cost->at(i)});
                    //...................................................................
                    solution->PlanAffect->pop_back();//on retire le couple probable apres evaluation de cout et l avoir enregistr� dans veccost
                    // cout<<"frequence ::" <<trx.AvailableFrequencies->at(i)<<", son sout veccost[i] ==="<< veccost->at(i)<<endl;
                } //fortrx.Av
          //..............................................................
                //...................................................................................

        //DOMINANCE


                 //...................................................
                 //.....................................................
                // I . Retirer la non dominance pour chaque fr�quence
                // ....................................................
                //...................................................

                 int  DominantScore;

                vector < pair<int,int> > IndexesFreqsNonDominantes;
                 //(int,int) :: le premier enregistre l index de la fr�quence non dominante
                  //(int,int) :: le dexieme , combien de fois la fr�quence est non dominante
                IndexesFreqsNonDominantes.reserve(trx.validFrequencies->size());
        //+++++++++++++Laidi modifi� +++++++++++++++++++++++++++++++++++
          for( i = 0; i < trx.AvailableFrequencies->size();i++)//la solution condidate est dans l indice i
                {

                  DominantScore = 0 ;// pour compter le nombre de solution qui domine la solution courante

                  for( j = i+1; j < trx.AvailableFrequencies->size() ;j++)
                   {
                       if (i!=j)
                       {

                           if (paircost[i].first > paircost[j].first) // on teste la dominance par rapport au premier objectif
                            {
                                // on ne peut pas juger on test par rapport au deuxime obj
                                if (paircost[i].second > paircost[j].second)
                                         {

                                                  //on est sur qu elle est dominante
                                                DominantScore    =   DominantScore+1 ;


                                         }
                                         else
                                         {
                                             if(paircost[i].first >= paircost[j].first)
                                              {
                                                    DominantScore    =   DominantScore+1 ;
                                              }
                                         }

                            }
                            else
                            {
                                if (paircost[i].second >= paircost[j].second)
                                    {
                                        DominantScore    =   DominantScore+1 ;
                                    }

                            }


                        }//i!=j
                    }//fin j

						if (DominantScore==0)// pour s'assurer que la solution "i" est non dominée
                      {
                        IndexesFreqsNonDominantes.push_back({i,paircost[i].first});// on insert l'index de la solution et son cout d'interférences
                      }
                       // cout << "la solution " << i << " est dominee par  " << DominantScore << " autres solutions" << endl;
                }//fin i

            //cout <<"IndexesFreqsNonDominantes.size()PIII  "<< IndexesFreqsNonDominantes.size() <<endl;*/
                //----------------------------------------------------------------------
                 //+++++++++++++ sol par sol +++++++++++++++++++++++++++++++++++
                 //++++++++++++++++++ tout les sol
                  int  nondominancescore;
                  //cout << "trx.AvailableFrequencies->size()++++ "<< trx.AvailableFrequencies->size() <<endl;

                      for( i = 0; i < trx.validFrequencies->size();i++)//la solution condidate est dans l indice i
                {

                  nondominancescore = 0 ;// pour compter le nombre de solution qui domine la solution courante

                   for( j = 0; j < trx.AvailableFrequencies->size() ;j++)
                   {

                       if (i!=j)
                       {

                                   if (paircost[i].first <= paircost[j].first)  // on teste la dominance par rapport au deuciÃ¨me objectif
                                    {
                                          if (paircost[i].second < paircost[j].second)

                                        {
                                            IndexesFreqsNonDominantes.push_back({i,paircost[i].first});

                                            nondominancescore = nondominancescore + 1;
                                            }
                                        }


                                    //--- j insere le deuxi�me obj
                                  /* else
                                    {
                                         if (paircost[i].second <= paircost[j].second) // teste la dominance par rapport au deuciÃ¨me objectif
                                        {
                                                if (paircost[i].first < paircost[j].first) // on
                                                {
                                                    IndexesFreqsNonDominantes.push_back({i,paircost[i].first});
                                            //au deuxieme obj

                                                nondominancescore = nondominancescore+1;
                                                }
                                            //}
                                        }
                                    }*/

                       }//i!=j
                   }//fin j
                   /*  if (nondominancescore > (trx.AvailableFrequencies->size() - 2 ))
                  IndexesFreqsNonDominantes.push_back({i,paircost[i].first});*/

              }//fin i
            // cout <<"IndexesFreqsNonDominantes.size()PIII  "<< IndexesFreqsNonDominantes.size() <<endl;



                //...................................................
                 //.....................................................
                // II . Trier le tableau de la non dominance selon un ordre croissant si la liste n est pas vide
                // ....................................................
                //...................................................
              //  sort(IndexesFreqsNonDominantes.begin(),IndexesFreqsNonDominantes.end(),my_cmp);
             // cout << "  IndexesFreqsNonDominantes.size() ****"<< IndexesFreqsNonDominantes.size() << endl;


                // copier les solution trouver dans un vecteur avec son cout d interferqunce qui
                if (IndexesFreqsNonDominantes.size()!= 0 )
                {
                    /*vector < pair < int, double> > NonDominanteCost;
                    NonDominanteCost.reserve(IndexesFreqsNonDominantes.size());
                    for(i = 0; i < IndexesFreqsNonDominantes.size(); i++ )
                    {
                        NonDominanteCost.push_back({IndexesFreqsNonDominantes[i].first, paircost[IndexesFreqsNonDominantes[i].first].first });
                    }*/
                // trier le tableau selon un ordre d�croisant du cout et retirer la premi�re valeur
                    sort(IndexesFreqsNonDominantes.begin(),IndexesFreqsNonDominantes.end(),my_cmpInfDoublePair);
                   // indexmin = IndexesFreqsNonDominantes.front().first;
                   //si des valeur de cout �gale on choisit al�atoirement parmi ces valeur
                   //+++++++++++++++++++++++++++++++++++++++++++
                   k=0;
                   for(i = 0 ; i < IndexesFreqsNonDominantes.size(); i++)
                    {
                        double val = IndexesFreqsNonDominantes.at(i).second;
                        pair<int,double> pnextval;
                        if((i+1) < IndexesFreqsNonDominantes.size())
                        {
                            pnextval = IndexesFreqsNonDominantes.at(i+1);
                            double nextval = pnextval.second;
                            // on copie les valeurs egales dans un tableau
                            //cout<< "hiiii here " << endl;
                            if( val == nextval )
                            {
                                k = k +1 ;//k contient le nombre de valeur �gale
                                // cout<< "hiiii here " << endl;
                            }
                            else
                            {
                                i = IndexesFreqsNonDominantes.size();
                            }
                        }
                    }
    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                    int indexf = rand() % (k+1);
                    indexmin = IndexesFreqsNonDominantes.at(indexf).first;

                }
                else
                {
                     vecmin(veccost, indexmin);//indexmin:indice de la fr�quencence qui a la valeur minimale
                }

                //................................................................................

//--------------------- dominance available
                //..............................................................
                //...................................................................................

    //vider la m�moire--vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
    vector < pair<double,double>  >().swap(paircost) ;
    delete(veccost);
    delete(solution->PlanAffect);
                //..............................................................
                //...................................................................................
                f=trx.validFrequencies->at(indexmin);//indice de la fr�quence ayant un cout minimal,

    //+++++++++++++++++++++++++++++++

            }//taille >1
            else
            {
                if(taille==1)
                {
                    f=trx.validFrequencies->at(0);
                // cout<<" frequency choisit:lorsque la taille est 0"<<f<<endl;
                // cout<<"hii"<<endl;
                }
            }//taille == 1?!!
        }
        else//Availablefrequencies==empty()
        {
            cout<<" la liste des fr�quences valide est vide **"<<endl;
        }
















            //******************
            //cout<<" la liste des fr�quences disponibles est vide **"<<endl;
        }
    break;
    }//case 501  : best frequency Front pareto
    //**************************************************************
    //--------------------------------------------------

//************* appliquer l hypervolume pour choisir la meilleur fr�quence
//*********************************************
   case 6 :
    {
           int i,indexmin,j,k;
     //   Individual * tempsol =  new Individual();
        int tempfreq;
        //��������������������������������� copier la solution dans tempsol ����������������������
        //���������������������������������������������������������������������������������������
        //tempsol = solution;
        //tempsol->plan = new vector <int>(solution->plan->size());
       // tempsol->planCC = new vector <double>(solution->planCC->size());
        solution->PlanAffect = new vector< pair<int,int> > ();
        // tempsol->PIObj = solution->PIObj;
        // tempsol->PSObj = solution->PSObj;
        for(i=0;i<solution->plan->size();i++)
        {
          //  tempsol->plan->at(i) = solution->plan->at(i);
          //  tempsol->planCC->at(i) = solution->planCC->at(i);
           // tempsol->PIObj = solution->PIObj;
            //tempsol->PSObj = solution->PSObj;
            if(solution->plan->at(i)!=-1)//si la case dans le plan n'est pas vide on remplie le planAffect
            {
                solution->PlanAffect->push_back({i,solution->plan->at(i)});
            }
        }

        //����������������������������������������������������������
        //���������������������������������������������������������������
        //   tempsol->planCC=NULL;
        //LF comment: on traverse tte les fr�quence et on calcule le cout
        int victimFrequency,interfererFrequency;
        int victimTrx,interfererTrx;
        victimTrx = trx.trxID;

        int taille;
        //..........................................................
        //..........................................................
        //vecteur pour enregistrer le couple de cout  interference, separation � la fois
        vector < pair<double,double>  > paircost ;
        //----------------------
        if(trx.AvailableFrequencies->empty()==false)
        {
           taille =trx.AvailableFrequencies->size();

            vector<double> * veccost = new vector <double>(taille);
                 vector<double> * cost = new vector <double>(taille);
                //Traitement parall�le
              //   #pragma omp parallel for
                for(i=0 ;i < taille ; i++)//pour chaque fr�quence probable on evalue le cout
                {

                    victimFrequency =trx.AvailableFrequencies->at(i);
                    veccost->at(i)=0.0;
                    cost->at(i)=0.0;
                    solution->PlanAffect->push_back({trx.trxID,victimFrequency});
                    //on �value la solution avec le nouveau couple : {victimTrx,victimFrequency}
                   int victimTrx1 = trx.trxID; int victimFrequency1 = trx.AvailableFrequencies->at(i);
                    for(j=0;j<solution->PlanAffect->size();j++)
                    {

                        victimTrx = solution->PlanAffect->at(j).first;
                        victimFrequency = solution->PlanAffect->at(j).second;
                       interfererTrx=solution->PlanAffect->at(j).first;
                        interfererFrequency=solution->PlanAffect->at(j).second;
                        if ( interfererTrx != victimTrx1)
                        {
                           // calculer le cout d interference
                            veccost->at(i)  = veccost->at(i)  + afpProblem->computeChannelInterference(victimFrequency1 ,interfererFrequency, victimTrx1, interfererTrx)+
                            afpProblem->computeChannelInterference(interfererFrequency,victimFrequency1 ,interfererTrx, victimTrx1);
                            //cout de separation
                           if(afpProblem->trxs[victimTrx1].sectorID == afpProblem->trxs[interfererTrx].sectorID)
                            {
                                //on teste si la contraite de separation co-secteur est respect�!!
                                if (abs (interfererFrequency-victimFrequency1)<3 )//contrainte co secteur viol�e
                                {
                                    cost->at(i) = cost->at(i) + 1.0;
                                }
                            }// secteur different
                            else
                            {
                                if(afpProblem->trxs[victimTrx1].siteID  == afpProblem->trxs[interfererTrx].siteID)
                                {
                        //on teste si la contrainte de separation co-site est respect�e!!
                                    if (abs (interfererFrequency-victimFrequency1)< 2)//contrainte co secteur viol�e
                                    {
                                        cost->at(i) = cost->at(i) + 1.0;
                                    }
                                }//
                            }
                        }

                    }// for(j=0 ;j < taille ; j++)//pour chaque fr�quence probable on evalue le cout
                    //.............................................................................
                    //.............................................................................
                    // enregister les couts dans le vecteur
                  //  cout << veccost->at(i) << veccost->at(i) << endl;
                    veccost->at(i) = veccost->at(i) + solution->PIObj ;
                    cost->at(i) = cost->at(i) + solution->PSObj ;
                    paircost.push_back({veccost->at(i),cost->at(i)});
                    //...................................................................
                    solution->PlanAffect->pop_back();//on retire le couple probable apres evaluation de cout et l avoir enregistr� dans veccost
                    // cout<<"frequence ::" <<trx.AvailableFrequencies->at(i)<<", son sout veccost[i] ==="<< veccost->at(i)<<endl;
                } //fortrx.AvailableFrequencies
        //***************************************************************
        //******************** Evaluation de la meilleur fr�quence ***********
        //1. choisir Le poin de r�f�rence est le pire valeur qu on peut avoir  et le max et le min ............................
          int indice;
          //----------------------
     pair<double,double> Min;
     pair<double,double> Max;
     pair < double, double > R;// est le point de r�f�rence ; la valeur max (normalis�)
    //string instance = "Denver";
  //string instance = "Seattle";
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
      // 2.-normaliser les valeurs

        vector < pair<double,double>  > Npaircost ;
         Npaircost.reserve(paircost.size());
         //copier pair cost ds Npaircost
            for(j = 0 ; j < paircost.size() ; j ++)
        {
            Npaircost.push_back({paircost.at(j).first, paircost.at(j).second});
            //cout << "Npaircost :" << Npaircost.at(j).first <<" , " << Npaircost.at(j).second <<endl;
        }
        vector < pair<int,double> > surface;
        surface.reserve(paircost.size());

        //2.-----Normaliser -------------------------
               // Normaliser les valeurs
        R.first = (R.first - Min.first)/(Max.first-Min.first);
        R.second = (R.second - Min.second)/(Max.second-Min.second);
        Normalize(Npaircost,Min,Max);
        //3---------------Calculer les distance
            for(j = 0 ; j < paircost.size(); j++)
        {
           // double d = (Npaircost.at(j).first-R.first)*(Npaircost.at(j).first-R.second);
            double d = (R.first - 0.9*Npaircost.at(j).first)*(R.second-0.1*Npaircost.at(j).second);
            surface.push_back({j,d});//.first est de la fr�quence
          //  cout << "surface.at(j).first ,surface.at(j).second :"<<surface.at(j).first<< ", " << surface.at(j).second << endl;
        }

        //5. Trier le tableau des surfaces selon un ordre croissant de surface
      // sort(surface.begin(),surface.end(),my_cmpInfDoublePair);
         sort(surface.begin(),surface.end(),my_cmpSupFirst);


        //6.la meilleur fr�quence est celle qui correspond � la surface minimale:: minimum cout
        indexmin = surface.front().first ;


        //--------------------------------------
       // indexmin = 0 ;
        f=trx.AvailableFrequencies->at(indexmin);//indice de la fr�quence recherch�
        solution->PIObj = veccost->at(indexmin);
        solution->PSObj = cost->at(indexmin);
        solution->planCC->at(trx.trxID).first = solution->PIObj;
        solution->planCC->at(trx.trxID).second = solution->PSObj;
        //nettoyage---------------------------
         vector < pair<double,double>  >().swap(paircost) ;
   // vector < pair<int,int> > ().swap(IndexesFreqsNonDominantes);
    delete(veccost);
    delete(cost);
    //delete(tempsol->PlanAffect);
    delete(solution->PlanAffect);
    //===============31-8-2021 ==========================================
        vector < pair<int,double> > ().swap(surface);
        vector < pair<double,double>  > ().swap(Npaircost) ;

    //=======================================================
    }
    else//Availablefrequencies==empty()
    {
            cout<<" la liste des fr�quences disponible est vide **"<<endl;
    }
    break;
    }


    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        default:
        {
            cout << "Player PS: ERREUR DE CHOIX DE LA strat�gie de la FREQUENCE !!"<<endl;
            break;
        }//default
    }//switch
 }
 //----------------------------------------------
 void PSPlayer::PSBestObjective(vector <Individual*> solutionSs, Individual* &BestSol  )
{
    int i, indexbestsol;
    indexbestsol = 0;
    double cost = solutionSs[0]->PSObj;
    for(i=0;i< solutionSs.size();i++)
    {
        if(cost > solutionSs[i]->PSObj)
        {
            cost = solutionSs[i]->PSObj;
            indexbestsol = i;
        }
    }

    BestSol = solutionSs[indexbestsol];

}

=======
#include <iostream>
#include <fstream>



//--------------------------

#include <cstdlib>      // std::rand, std::srand
#include <algorithm>    // std::find
#include <time.h>
#include<cmath>
//#include "Commun.cpp"
//#include "Individual.h"
//using namespace std;
#include "PSPlayer.h"
#include "../Commun/Commun.h"

//#################################################################
//Extern my Procedures and  functions  - LAIDOUI FAtma ----
//##################################################################
extern void AddSolTrxFrequency(AFP * afpProblem,Individual* &Sol,TRXs trx ,int f);
extern void UpdateLTrxNTreateds(vector <TRXs> &LTrxNTreateds, TRXs trx,int Add); //Retirer trx de LTrxNTreated
extern void UpdateTRxFrequency(TRXs &trx, int f,int Add); //Retirer f de la liste de fr�quence valide de trx
extern void UpdateTRxFrequency(TRXs &trx, int f,int Update);
extern void UpdateTRxFrequencyNew(vector<TRXs> LTrxNTreateds,AFP * afpProblem,TRXs &trx, int f,int Update);
extern bool my_cmpInf(const pair <int,int>   &a, const pair <int,int>   &b);
extern bool my_cmp(const pair <int,int>   &a, const pair <int,int>   &b);
extern bool my_cmpInfDoublePair(const pair <int,double>   &a, const pair <int,double>   &b);
extern bool my_cmpInfdouble (const double  &a,  const double   &b);
extern bool my_cmpSupFirst(const pair <int,double>   &a, const pair <int,double>   &b);
extern bool my_cmpvectintinffirst(const int &a, const int  &b);
extern bool my_cmpSupDoublePair(const pair <double,double>   &a, const pair <double,double>   &b);
//###############################################################################################
/*bool my_cmpInf(const pair <int,int>   &a, const pair <int,int>   &b)
{
    // smallest comes first
    return a.second < b.second;
}*/

//-------------------------------------
using namespace std;

/*bool my_cmpvectintinffirstPS(const int &a, const int  &b)
{
    // smallest comes first
    return a< b;
}*/
//##########################################################
PSPlayer::PSPlayer()
{
    IdPlayer = 2;
}
//##########################################################
PSPlayer::PSPlayer(AFP * afpProblem, const int max_gen,int indexLearn)
{
    IdPlayer = 2;
    PSInterventionTRXOrder = new vector <int> (afpProblem->trxs.size());
   // IdPlayer = 1;

}
//---------------------------------------------------------------------------------
PSPlayer::~PSPlayer()
{
IdPlayer = -1; IndexLearnPS = -1;
}
bool my_cmpPS(const pair <int,int>   &a, const pair <int,int>   &b)
{
    // smallest comes first
    return a.second > b.second;
}
bool my_cmpInfPS(const pair <int,int>   &a, const pair <int,int>   &b)
{
    // smallest comes first
    return a.second < b.second;
}
//++++++++++++++++++++++++++++++++
//ajouter le 04/ 3/2018 ---
void PSPlayer::PSUpdateTRxFrequencyErase(TRXs &trx, int f, int alpha) //alpha = 3 si on est dans le meme secteur; = 2 secteur diff�rent
{
    int freq;
    int indexf=FindFrequency(trx.AvailableFrequencies,f);
    if (indexf!=-1)//la fr�quence existe
    {
       trx.AvailableFrequencies->erase( trx.AvailableFrequencies->begin()+indexf);
    }
    freq = f - alpha;
    indexf = FindFrequency(trx.AvailableFrequencies,freq);
    if (indexf!=-1)//la fr�quence existe
    {
       trx.AvailableFrequencies->erase( trx.AvailableFrequencies->begin()+indexf);
    }
    //suppression des fr�quence adjacente de f
    freq = f + alpha;
    indexf=FindFrequency(trx.AvailableFrequencies,freq);
    //cout << "indexf "  <<indexf <<endl;
    if (indexf!=-1)//la fr�quence existe
    {
       trx.AvailableFrequencies->erase( trx.AvailableFrequencies->begin()+indexf);
    }
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void PSPlayer::PSUpdateTRxFrequency(vector<TRXs> &LTrxNTreateds,AFP * afpProblem,TRXs &trx,int f, int Update)
{
     int i;
    TRXs othertrxId;
    switch(Update)
    {
       case + 1://Ajout
        {
            break;
        }
        case -1://Suppression
        {
            int freq, indexf ;
            if(LTrxNTreateds.empty()==false)
            {
                if (trx.AvailableFrequencies->empty()==false)
                {

                    PSUpdateTRxFrequencyErase(trx, f,3);
                    for(i=0; i<LTrxNTreateds.size();i++)
                    {
                        othertrxId = LTrxNTreateds[i];
                        if(trx.sectorID == afpProblem->trxs[othertrxId.trxID].sectorID)//meme secteur
                        {
                            PSUpdateTRxFrequencyErase(othertrxId, f,3);
                        }//  if(trx.sectorID == afpProblem->trxs[othertrxId.trxID].sectorID)
                        else
                        {
                               if(trx.siteID == afpProblem->trxs[othertrxId.trxID].siteID)//meme secteur
                               {
                                   PSUpdateTRxFrequencyErase(othertrxId, f,2);
                               }
                        }
                    }
                 }
            }//if(LTrxNTreateds.empty()==false)
            else//if(LTrxNTreateds.empty()==true)
            {
                cout <<" EROOR : The list of untreated trx is empty!!"<<endl;
            }
            break;
        }//case -1
       default:
        {
            cout<<" Player  PS: ERREUR de mise � jour de fr�quence !!"<<endl;
            break;
        }//default switch

    }//fin switch

}


//++++++++++++++++++++++++++++++++++++++++++++++++
void PSPlayer::Play(string instance,int StrategyTrx, int StrategyFreq,vector<TRXs> &LTrxNTreateds,TRXs &trx,Individual* &Sol,AFP * afpProblem)
{
          //  TRXs trx;int f;
            //PSChooseTrx(StrategyTrx,LTrxNTreateds, trx);// 1:choisir al�atoirement un  trx non trait�


               int index,indexmin,i;
               TRXs victimtrx,othertrx;int f; //vector <int> Numneighbor;
     /*	vector< pair <int,int> >  Numneighbor;
    Numneighbor.reserve(LTrxNTreateds.size());
    for(i=0;i<LTrxNTreateds.size();i++)
    {
        Numneighbor.push_back({i,afpProblem->neighbors[LTrxNTreateds[i].sectorID].size()});//le nombre de secteur voisin du secteeur du trx i
    //trx i, le nombre de ses voisin de meme secteur
    }

    //vecminInt(Numneighbor, indexmin);
    //trier le vecteur Numneighbor selon le nombre min des voisins de  sector
    sort(Numneighbor.begin(), Numneighbor.end(),my_cmpInfPS);
    trx= LTrxNTreateds[Numneighbor[0].first]; //on choisit le premier trx dans le vecteur Numneighbor car il a le petit nombre de voisin
*/
            PSChooseTrx(afpProblem,StrategyTrx,LTrxNTreateds,trx);
           // cout << "trx.trxID" <<  trx.trxID <<endl;
            PSChooseFrequency(instance,StrategyFreq,trx,f,Sol,afpProblem) ;//1 : choisir al�atoirement une fr�quence ; 2 choisir la meilleur fr�quence
            AddSolTrxFrequency(afpProblem,Sol,trx ,f); //Proc�dure pour affecter f au trx dans la solution
            //UpdateTRxFrequencyNew(LTrxNTreateds,afpProblem,trx,f,-1);
            //UpdateTRxFrequencyV3(LTrxNTreateds,afpProblem,trx,f,-1);
          //  PSUpdateTRxFrequency(LTrxNTreateds,afpProblem,trx,f, -1);
            UpdateLTrxNTreateds(LTrxNTreateds, trx,-1); //Retirer trx de LTrxNTreated

}
double PSPlayer::PSEvaluateObj(Individual* &Sol)
{
    return 0.0;
}
//---------------------------------------
void PSPlayer::PSChooseTrx(AFP * afpProblem,int Strategytrx,vector<TRXs> LTrxNTreateds,TRXs &trx)
{
    switch(Strategytrx)
    {
case +9 :// trx qui a  le plus petit cout ds la matrice
    {
        int i,ID ;
        vector < pair < int,double> > paircost;
        //------------------------------------------------------------
        paircost.reserve(LTrxNTreateds.size());
        for(i= 0 ; i < LTrxNTreateds.size(); i++)
        {
            ID = LTrxNTreateds[i].trxID;
            paircost.push_back({ID,afpProblem->MaxCostITrx[ID].second});
        }
        sort(paircost.begin(),paircost.end(),my_cmpInfDoublePair);
        pair <int,double> node  = paircost.front();
        trx = afpProblem->trxs[node.first];
        vector < pair < int,double> >().swap(paircost);
        //cout << "trx.trxID   " << trx.trxID << endl;
        break;
    }
   case +8 : //le trx qui a le plus  grand cout de la matrice MI
    {
        int i,ID ;
        vector < pair < int,double> > paircost;
        paircost.reserve(LTrxNTreateds.size());

        //------------------------------------------------------------
     //   paircost.reserve(LTrxNTreateds.size());
        for(i= 0 ; i < LTrxNTreateds.size(); i++)
        {
            ID = LTrxNTreateds[i].trxID;

            paircost.push_back({ID,afpProblem->MaxCostITrx[ID].second});
        }
        sort(paircost.begin(),paircost.end(),my_cmpSupFirst);
        pair <int,double> node  = paircost.front();
        trx = afpProblem->trxs[node.first];
        vector < pair < int,double> >().swap(paircost);
        break;
    }


         case 0: //choix al�atoire du trx
       {
           //ChooseTrxRandom(LTrxNTreateds,trx);
          /* int i;
           vector <int> TrxIds;
           TrxIds.reserve(LTrxNTreateds.size());
           for(i = 0 ; i< LTrxNTreateds.size(); i++)
            TrxIds.push_back(LTrxNTreateds.at(i).trxID);
        sort(TrxIds.begin(),TrxIds.end(), my_cmpvectintinffirst);
        trx = afpProblem->trxs[TrxIds.front()];*/
        trx = LTrxNTreateds.at(0);
           break;
       }//case +1
       case  +1 ://Strategie 1 : Choix al�atoire de trx.
      {
        //LTrxNTreated : la liste des trx non trait�s
        int i;
        if(LTrxNTreateds.empty()==true)//on
        {
           //throw string("ERREUR: Le vecteur des trx trait� est vide !!");
                cout<<"Player PS: ERREUR: The vector of treated Trx is EMPTY!!" <<endl;;
            }
            else
            {
           //modifier l'ordre du tableau LTrxNTreateds et choisir ccelui de l entete
               /* std::srand ( unsigned ( time(0) ) );
            // using built-in random generator:
                std::random_shuffle ( LTrxNTreateds.begin(), LTrxNTreateds.end() );

                trx= LTrxNTreateds.front();*/
          // cout<<"trx choisit is :"<<trx.trxID<<endl;
           //choisir al�atoirement un index
           int index;
            index = rand() % LTrxNTreateds.size();
            trx=LTrxNTreateds.at(index);
            }//endelse
            break;

        }//case +1
                //
     case + 2 : //Choisir un trx qui un nmbre max de trx de meme site
      {     int i,j;
           	vector< pair <int,int> >  TrxNumberTrxSameSect;
            TrxNumberTrxSameSect.reserve(LTrxNTreateds.size());
           	for(i=0;i<LTrxNTreateds.size();i++)
            {
                //TrxNumberTrxSameSect[i].first=LTrxNTreateds[i].trxID;
               // TrxNumberTrxSameSect[i].second=0;
                TrxNumberTrxSameSect.push_back({LTrxNTreateds[i].trxID,0});
            }//end   	for(i=0;i<LTrxNTreateds.size();i++)
            //-------------afficher au prmier lieu le contenu de TrxNumberTrxSameSect

            for(i=0;i<LTrxNTreateds.size();i++)
            {
                TrxNumberTrxSameSect[i].second =0.0;
                for(j=0;j<LTrxNTreateds.size();j++)
                {
                    if(LTrxNTreateds[i].trxID!=LTrxNTreateds[j].trxID)//pour ne pas prendre le trx encoure d evaluation
                    {
                        if (LTrxNTreateds[i].siteID == LTrxNTreateds[j].siteID)//l'autre trx est dans le meme secteur
                      //  if (LTrxNTreateds[i].sectorID == LTrxNTreateds[j].sectorID)//l'autre trx est dans le meme secteur
                        {
                            TrxNumberTrxSameSect[i].second = TrxNumberTrxSameSect[i].second + 1;
                        }

                    }// if(LTrxNTreateds[i].trxID!=LTrxNTreateds[j].trxID)
                }//for(j=0;j<LTrxNTreateds.size()-1;j++)

               // TrxNumberTrxSameSect[i].first=LTrxNTreateds[i].trxID;
                //TrxNumberTrxSameSect[i].second=-1;
            }//(i=0;i<LTrxNTreateds.size();i++)
            //ordonner la liste
            sort(TrxNumberTrxSameSect.begin(), TrxNumberTrxSameSect.end(),my_cmp);
            int indextrx =TrxNumberTrxSameSect[0].first;// l'indice de trx � retirer;
            int pos = FindTrxID(LTrxNTreateds, indextrx);
            trx = LTrxNTreateds[pos];

            break;
       }//case + 2
        case + 3 : //choix de trx qui a le min de trx dans le meme site
      {     int i,j;
           	vector< pair <int,int> >  TrxNumberTrxSameSect;
            TrxNumberTrxSameSect.reserve(LTrxNTreateds.size());

           	for(i=0;i<LTrxNTreateds.size();i++)
            {
                //TrxNumberTrxSameSect[i].first=LTrxNTreateds[i].trxID;
               // TrxNumberTrxSameSect[i].second=0;
                TrxNumberTrxSameSect.push_back({LTrxNTreateds[i].trxID,0});
            }//end   	for(i=0;i<LTrxNTreateds.size();i++)
            //-------------afficher au prmier lieu le contenu de TrxNumberTrxSameSect

            for(i=0;i<LTrxNTreateds.size();i++)
            {
                TrxNumberTrxSameSect[i].second =0.0;
                for(j=0;j<LTrxNTreateds.size();j++)
                {
                    if(LTrxNTreateds[i].trxID!=LTrxNTreateds[j].trxID)//pour ne pas prendre le trx encoure d evaluation
                    {
                        if (LTrxNTreateds[i].siteID == LTrxNTreateds[j].siteID)//l'autre trx est dans le meme secteur
                      //  if (LTrxNTreateds[i].sectorID == LTrxNTreateds[j].sectorID)//l'autre trx est dans le meme secteur
                        {
                            TrxNumberTrxSameSect[i].second = TrxNumberTrxSameSect[i].second + 1;
                        }

                    }// if(LTrxNTreateds[i].trxID!=LTrxNTreateds[j].trxID)
                }//for(j=0;j<LTrxNTreateds.size()-1;j++)

               // TrxNumberTrxSameSect[i].first=LTrxNTreateds[i].trxID;
                //TrxNumberTrxSameSect[i].second=-1;
            }//(i=0;i<LTrxNTreateds.size();i++)
            //ordonner la liste
            sort(TrxNumberTrxSameSect.begin(), TrxNumberTrxSameSect.end(),my_cmpInf);//ordonner selon un ordre decroissant des trx de meme site
            int indextrx =TrxNumberTrxSameSect[0].first;// l'indice de trx � retirer;
            int pos = FindTrxID(LTrxNTreateds, indextrx);
            trx = LTrxNTreateds[pos];

            break;
       }//case + 2

         case + 4 : //choix de trx qui a le plus de trx dans diff�rent
      {     int i,j;
           	vector< pair <int,int> >  TrxNumberTrxSameSect;
            TrxNumberTrxSameSect.reserve(LTrxNTreateds.size());
           	for(i=0;i<LTrxNTreateds.size();i++)
            {
                //TrxNumberTrxSameSect[i].first=LTrxNTreateds[i].trxID;
               // TrxNumberTrxSameSect[i].second=0;
                TrxNumberTrxSameSect.push_back({LTrxNTreateds[i].trxID,0});
            }//end   	for(i=0;i<LTrxNTreateds.size();i++)
            //-------------afficher au prmier lieu le contenu de TrxNumberTrxSameSect

            for(i=0;i<LTrxNTreateds.size();i++)
            {
                TrxNumberTrxSameSect[i].second =0.0;
                for(j=0;j<LTrxNTreateds.size();j++)
                {
                    if(LTrxNTreateds[i].trxID!=LTrxNTreateds[j].trxID)//pour ne pas prendre le trx encoure d evaluation
                    {
                        if (LTrxNTreateds[i].siteID != LTrxNTreateds[j].siteID)//l'autre trx est dans le meme secteur
                      //  if (LTrxNTreateds[i].sectorID == LTrxNTreateds[j].sectorID)//l'autre trx est dans le meme secteur
                        {
                            TrxNumberTrxSameSect[i].second = TrxNumberTrxSameSect[i].second + 1;
                        }

                    }// if(LTrxNTreateds[i].trxID!=LTrxNTreateds[j].trxID)
                }//for(j=0;j<LTrxNTreateds.size()-1;j++)

               // TrxNumberTrxSameSect[i].first=LTrxNTreateds[i].trxID;
                //TrxNumberTrxSameSect[i].second=-1;
            }//(i=0;i<LTrxNTreateds.size();i++)
            //ordonner la liste
            sort(TrxNumberTrxSameSect.begin(), TrxNumberTrxSameSect.end(),my_cmp);//ordonner selon un ordre decroissant des trx de meme site
            int indextrx =TrxNumberTrxSameSect[0].first;// l'indice de trx � retirer;
            int pos = FindTrxID(LTrxNTreateds, indextrx);
            trx = LTrxNTreateds[pos];

            break;
       }//case + 4
        case +6:
        {// choisir le trx qui a le plus petit nbre de trx avec qui il interfere
            int i,indextrx ;
           //calculer pour chque trx non trait� , la taille des trx avec qui il interfere et l enregistrer dans LTrxNTreatedsSizeinterfere
            vector <pair<int,int> > LTrxNTreatedsSizeinterfere;
            LTrxNTreatedsSizeinterfere.reserve(LTrxNTreateds.size());
             for(i = 0 ; i < LTrxNTreateds.size() ; i++)
             {
                LTrxNTreatedsSizeinterfere.push_back({LTrxNTreateds[i].trxID, afpProblem->interferenceMatrix[i].size() });
             }
              // trier  en ordre croissantle tableau LTrxNTreatedsSizeinterfere selon la taille des trx avec qui il interfer
           sort (LTrxNTreatedsSizeinterfere.begin(), LTrxNTreatedsSizeinterfere.end(), my_cmpInf);
           indextrx = LTrxNTreatedsSizeinterfere.front().first;
 // le trx souhait� et le prmier trx qui a un nombre petir des trx avec qui il interf�re
         for(i = 0 ; i < LTrxNTreateds.size() ; i++)
             {
                 if (LTrxNTreateds[i].trxID == indextrx )
                 {
                     trx = LTrxNTreateds[i];
                     i = LTrxNTreateds.size();
                 }
             }

        //------
        break;
        }//case 6


        default :
        {
            cout << "Player PS:ERREUR de choix de strategy TRX"<< endl;
            break;
        }
    }//finswitch

}
 void PSPlayer::PSChooseFrequency(string instance,int StrategyFreq,TRXs trx,int &f,Individual * &solution,AFP * afpProblem)
 {
    switch (StrategyFreq)
    {
        case  + 1 ://choix al�atoire de la fr�quence
        {
            int index;
            if (trx.AvailableFrequencies->empty()== false )//on choisit des fr�quences disponible
            {
                index= rand() % trx.AvailableFrequencies->size();
                f= trx.AvailableFrequencies->at(index);
                solution->PIObj = afpProblem->ComputeSolutionInterference(solution);
                solution->PSObj = afpProblem->ComputeSolutionSeparationCost(solution);
                solution->planCC->at(trx.trxID).first = solution->PIObj;
                solution->planCC->at(trx.trxID).second = solution->PSObj;
            }
            else//on chosit des fr�quence valide
            {
                index = rand() % trx.validFrequencies->size();
                f=trx.validFrequencies->at(index);
            }
            break;
        }//case +1
        //....................
         //................
        case + 2 ://choix de la meilleur fr�quence
        {
            int i,indexmin,j,k;
       // Individual * tempsol =  new Individual();
        int tempfreq;
        //��������������������������������� copier la solution dans tempsol ����������������������
        //���������������������������������������������������������������������������������������
        //tempsol = solution;
        //tempsol->plan = new vector <int>(solution->plan->size());
        //tempsol->planCC = new vector <double>(solution->planCC->size());
        solution->PlanAffect = new vector< pair<int,int> > ();
        // tempsol->PIObj = solution->PIObj;
        // tempsol->PSObj = solution->PSObj;
        for(i=0;i<solution->plan->size();i++)
        {
            //tempsol->plan->at(i) = solution->plan->at(i);
            //tempsol->planCC->at(i) = solution->planCC->at(i);
           // tempsol->PIObj = solution->PIObj;
            //tempsol->PSObj = solution->PSObj;
            if(solution->plan->at(i)!=-1)//si la case dans le plan n'est pas vide on remplie le planAffect
            {
                solution->PlanAffect->push_back({i,solution->plan->at(i)});
            }
        }

        //����������������������������������������������������������
        //���������������������������������������������������������������
        //   tempsol->planCC=NULL;
        //LF comment: on traverse tte les fr�quence et on calcule le cout
        int victimFrequency,interfererFrequency;
        int victimTrx,interfererTrx;
        victimTrx = trx.trxID;

        int taille;
        //..........................................................
        //..........................................................
        //vecteur pour enregistrer le couple de cout  interference, separation � la fois
        vector < pair<double,double>  > paircost ;
        //----------------------
        if(trx.AvailableFrequencies->empty()==false)
        {
           taille =trx.AvailableFrequencies->size();

            vector<double> * veccost = new vector <double>(taille);
                 vector<double> * cost = new vector <double>(taille);
            if (taille>1)
            {
                for(i=0 ;i < taille ; i++)//pour chaque fr�quence probable on evalue le cout
                {

                    victimFrequency =trx.AvailableFrequencies->at(i);
                    veccost->at(i)=0.0;
                    cost->at(i)=0.0;
                    solution->PlanAffect->push_back({trx.trxID,victimFrequency});
                    //on �value la solution avec le nouveau couple : {victimTrx,victimFrequency}
                   int victimTrx1 = trx.trxID; int victimFrequency1 = trx.AvailableFrequencies->at(i);
                    for(j=0;j< solution->PlanAffect->size();j++)
                    {

                        victimTrx = solution->PlanAffect->at(j).first;
                        victimFrequency = solution->PlanAffect->at(j).second;
                       interfererTrx = solution->PlanAffect->at(j).first;
                        interfererFrequency = solution->PlanAffect->at(j).second;
                        if ( interfererTrx != victimTrx1)
                        {
                           // calculer le cout d interference
                            veccost->at(i)  = veccost->at(i)  + afpProblem->computeChannelInterference(victimFrequency1 ,interfererFrequency, victimTrx1, interfererTrx)+
                            afpProblem->computeChannelInterference(interfererFrequency,victimFrequency1 ,interfererTrx, victimTrx1);
                            //cout de separation
                           if(afpProblem->trxs[victimTrx1].sectorID == afpProblem->trxs[interfererTrx].sectorID)
                            {
                                //on teste si la contraite de separation co-secteur est respect�!!
                                if (abs (interfererFrequency-victimFrequency1)<3 )//contrainte co secteur viol�e
                                {
                                    cost->at(i) = cost->at(i) + 1.0;
                                }
                            }// secteur different
                            else
                            {
                                if(afpProblem->trxs[victimTrx1].siteID  == afpProblem->trxs[interfererTrx].siteID)
                                {
                        //on teste si la contrainte de separation co-site est respect�e!!
                                    if (abs (interfererFrequency-victimFrequency1)< 2)//contrainte co secteur viol�e
                                    {
                                        cost->at(i) = cost->at(i) + 1.0;
                                    }
                                }//
                            }
                        }

                    }// for(j=0 ;j < taille ; j++)//pour chaque fr�quence probable on evalue le cout
                    //.............................................................................
                    //.............................................................................
                    // enregister les couts dans le vecteur
                  //  cout << veccost->at(i) << veccost->at(i) << endl;
                    veccost->at(i) = veccost->at(i) + solution->PIObj ;
                    cost->at(i) = cost->at(i) + solution->PSObj ;
                    paircost.push_back({veccost->at(i),cost->at(i)});
                    //...................................................................
                    solution->PlanAffect->pop_back();//on retire le couple probable apres evaluation de cout et l avoir enregistr� dans veccost
                    // cout<<"frequence ::" <<trx.AvailableFrequencies->at(i)<<", son sout veccost[i] ==="<< veccost->at(i)<<endl;
                } //fortrx.AvailableFrequencies
                 //tempsol->plan->at(trx.trxID) = -1;
                    // cout<<"frequence ::" <<trx.AvailableFrequencies->at(i)<<", son sout veccost[i] ==="<< veccost->at(i)<<endl;
                //} //fortrx.AvailableFrequencies

              //le nombre de g�n�ration est le nombre de fr�quence valide
            //chaque position dans AvailableFrequencies correspond � currentobjectif
            //..............................................................
           //...................................................................................
            //utiliser l equilibre de nash
                // cout << " vcouts->size()  "<< vcouts->size() << endl;
                //+++++++++++++++++++++++++ afficer vcost
                  /*ofstream ResultFile;
            string path="Exemples/veccostMinPS_.txt";
            ResultFile.open(path.c_str(),std::ios::app);
            if (!ResultFile) {
                cerr << "Unable to open file!!";
                exit(1);   // call system to stop
            }
            ResultFile << " trx -......" << trx.trxID << endl;
            for(i=0 ;i < trx.AvailableFrequencies->size() ; i++)
            {ResultFile << "frequency , cout  ::"<< trx.AvailableFrequencies->at(i) << " ,  " <<cost->at(i)<<endl;
            }
    */
            //++++++++++choisir la valeur minimal ++++++++++++++++++++++++++
             vector < pair<int,double>  > paircostMinSep ;//pour sauvegarder la fr�quence, et sa valeur de nash
             paircostMinSep.reserve(trx.AvailableFrequencies->size());
            for(i = 0 ; i< trx.AvailableFrequencies->size(); i++)
            {
                paircostMinSep.push_back({trx.AvailableFrequencies->at(i),cost->at(i)});
            }
            //-----------------------------------------------
            //ResultFile << "avant  le tri -----" << endl;
           /*
            for ( i = 0 ; i < paircostMinSep.size() ; i++)
            ResultFile << " frequence , cost :::" << paircostMinSep.at(i).first << " , " << paircostMinSep.at(i).second << endl;
           */
           //------------------------------trier le tableau selon un ordre croissant de cout de separation---------
            sort(paircostMinSep.begin(),paircostMinSep.end(),my_cmpInfDoublePair);
            //---------------------------------------
             //--------------------- apr�s le tri
           // ResultFile << "apr�s le tri -----" << endl;
            for ( i = 0 ; i < paircostMinSep.size() ; i++)
           // ResultFile << " frequence , nash :::" << paircostMinSep.at(i).first << " , " << paircostMinSep.at(i).second << endl;

            //------------------------------------------------------------
             // si les valeurs sont �gales, nous choisissons al�atoirement une fr�quence
            //---------------------------------------------------
            k = 0 ; // pour calculer le nombre de valeurs �gale
            for(i = 0 ; i < paircostMinSep.size(); i++)
            {
                double val = paircostMinSep.at(i).second;
                pair<int,double> pnextval;
                if((i+1) < paircostMinSep.size())
                {
                    pnextval = paircostMinSep.at(i+1);
                    double nextval = pnextval.second;
                    // on copie les valeurs egales dans un tableau
                    //cout<< "hiiii here " << endl;
                    if( val == nextval )
                    {
                        k = k +1 ;//k contient le nombre de valeur �gale
                        // cout<< "hiiii here " << endl;
                    }
                    else
                    {
                        i = paircostMinSep.size();
                    }
                }
            }
            //-------
           // ResultFile << "k valeur agales "<< k <<endl;
            indexmin = rand() % (k+1);
           // ResultFile << " la fr�quence probable ***"<< paircostMinSep.at(indexmin).first<<endl;
            //---chosir la fr�quence
            f = paircostMinSep.at(indexmin).first;
                //++++++++++++++++++++++++++++++++++++++++
               // vecmin(veccost, indexmin);//indexmin:indice de la fr�quencence qui a la valeur minimale
                //cout<<"indexmin f " << indexmin<<endl;
               // indexmin = trx.AvailableFrequencies->at(0);
              // f=trx.AvailableFrequencies->at(indexmin);//indice de la fr�quence ayant un cout minimal,
                  //++++++++++++++++++++++++++++++++++++
          //  ResultFile << " f choisit est======>" << f <<endl;
           //      ResultFile.close();
                  solution->PIObj = veccost->at(indexmin);
     solution->PSObj = cost->at(indexmin);
    //+++++++++++++++++++++++++++++++


    //++++++++++++++++++++
     //vider la m�moire--vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
    vector < pair<double,double>  >().swap(paircost) ;

    delete(veccost);
    delete(cost);
    //delete(tempsol->PlanAffect);
    delete(solution->PlanAffect);
      //------------------------------- 31-8-2021 ---------------------------------------
    vector < pair<int,double>  > ().swap(paircostMinSep);
    //----------------------------------------------------------------------------------
            }//la liste des fr�quence Availble est vide
            else
            {
                f = trx.AvailableFrequencies->at(0);
            }
        }
            //*******************************************************************************
            else//on selectionne la meilleur fr�quence Valide
            {
                int taille =trx.validFrequencies->size();
                vector<double> * veccost = new vector <double>(taille);
                 vector<double> * cost = new vector <double>(taille);
                veccost->reserve(taille);
                if (trx.validFrequencies->empty()==false)
                {
                    for(i=0 ;i < taille ; i++)//pour chaque fr�quence probable on evalue le cout
                    {
                        int victimFrequency =trx.validFrequencies->at(i);
                    veccost->at(i)=0.0;
                    cost->at(i)=0.0;
                    solution->PlanAffect->push_back({trx.trxID,victimFrequency});
                    //on �value la solution avec le nouveau couple : {victimTrx,victimFrequency}
                   int victimTrx1 = trx.trxID; int victimFrequency1 = trx.AvailableFrequencies->at(i);
                    for(j=0;j< solution->PlanAffect->size();j++)
                    {

                        victimTrx = solution->PlanAffect->at(j).first;
                        victimFrequency = solution->PlanAffect->at(j).second;
                       interfererTrx = solution->PlanAffect->at(j).first;
                        interfererFrequency = solution->PlanAffect->at(j).second;
                        if ( interfererTrx != victimTrx1)
                        {
                           // calculer le cout d interference
                            veccost->at(i)  = veccost->at(i)  + afpProblem->computeChannelInterference(victimFrequency1 ,interfererFrequency, victimTrx1, interfererTrx)+
                            afpProblem->computeChannelInterference(interfererFrequency,victimFrequency1 ,interfererTrx, victimTrx1);
                            //cout de separation
                           if(afpProblem->trxs[victimTrx1].sectorID == afpProblem->trxs[interfererTrx].sectorID)
                            {
                                //on teste si la contraite de separation co-secteur est respect�!!
                                if (abs (interfererFrequency-victimFrequency1)<3 )//contrainte co secteur viol�e
                                {
                                    cost->at(i) = cost->at(i) + 1.0;
                                }
                            }// secteur different
                            else
                            {
                                if(afpProblem->trxs[victimTrx1].siteID  == afpProblem->trxs[interfererTrx].siteID)
                                {
                        //on teste si la contrainte de separation co-site est respect�e!!
                                    if (abs (interfererFrequency-victimFrequency1)< 2)//contrainte co secteur viol�e
                                    {
                                        cost->at(i) = cost->at(i) + 1.0;
                                    }
                                }//
                            }
                        }

                    }// for(j=0 ;j < taille ; j++)//pour chaque fr�quence probable on evalue le cout
                    //.............................................................................
                    //.............................................................................
                    // enregister les couts dans le vecteur
                  //  cout << veccost->at(i) << veccost->at(i) << endl;
                    veccost->at(i) = veccost->at(i) + solution->PIObj ;
                    cost->at(i) = cost->at(i) + solution->PSObj ;
                    paircost.push_back({veccost->at(i),cost->at(i)});
                    //...................................................................
                    solution->PlanAffect->pop_back();//on retire le couple probable apres evaluation de cout et l avoir enregistr� dans veccost
                    // cout<<"frequence ::" <<trx.AvailableFrequencies->at(i)<<", son sout veccost[i] ==="<< veccost->at(i)<<endl;
                } //fortrx.AvailableFrequencies
          // cout << " vcouts->size()  "<< vcouts->size() << endl;
            //++++++++++choisir la valeur minimal ++++++++++++++++++++++++++
             vector < pair<int,double>  > paircostMinSep ;//pour sauvegarder la fr�quence, et sa valeur de nash
             paircostMinSep.reserve(trx.validFrequencies->size());
            for(i = 0 ; i< trx.validFrequencies->size(); i++)
            {
                paircostMinSep.push_back({trx.validFrequencies->at(i),cost->at(i)});
            }

            //------------------Trier le tableau ---------------------
              sort(paircostMinSep.begin(),paircostMinSep.end(),my_cmpInfDoublePair);

            //------------------------------------------------------------
             // si les valeurs sont �gales, nous choisissons al�atoirement une fr�quence
            //---------------------------------------------------
            k = 0 ; // pour calculer le nombre de valeurs �gales
            for(i = 0 ; i < paircostMinSep.size(); i++)
            {
                double val = paircostMinSep.at(i).second;
                pair<int,double> pnextval;
                if((i+1) < paircostMinSep.size())
                {
                    pnextval = paircostMinSep.at(i+1);
                    double nextval = pnextval.second;
                    // on copie les valeurs egales dans un tableau
                    //cout<< "hiiii here " << endl;
                    if( val == nextval )
                    {
                        k = k +1 ;//k contient le nombre de valeur �gale
                        // cout<< "hiiii here " << endl;
                    }
                    else
                    {
                        i = paircostMinSep.size();
                    }
                }
            }
            //-------
            indexmin = rand() % (k+1);
            //---chosir la fr�quence
            f = paircostMinSep.at(indexmin).first;
            solution->PIObj = veccost->at(indexmin);
     solution->PSObj = cost->at(indexmin);
    //+++++++++++++++++++++++++++++++


    //++++++++++++++++++++
     //vider la m�moire--vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
    vector < pair<double,double>  >().swap(paircost) ;

    delete(veccost);
    delete(cost);
    //delete(tempsol->PlanAffect);
    delete(solution->PlanAffect);
                }//if (trx.validFrequencies->empty')==false)
                else
                {
                    cout << "ERROR Valid frequencies is EMPTY !!" << endl;
                }
            }
            //**************************************************************************
           break;
        }//case 2 best separation
         //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~�
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Distance ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   case  +3 ://strategy 2 choisir la meilleur fr�quence en terme distance euclidienne
    {
       int i,indexmin,j,k;
       // Individual * tempsol =  new Individual();
        int tempfreq;
        //��������������������������������� copier la solution dans tempsol ����������������������
        //���������������������������������������������������������������������������������������
        //tempsol = solution;
        //tempsol->plan = new vector <int>(solution->plan->size());
        //tempsol->planCC = new vector <double>(solution->planCC->size());
        solution->PlanAffect = new vector< pair<int,int> > ();
        // tempsol->PIObj = solution->PIObj;
        // tempsol->PSObj = solution->PSObj;
        for(i=0;i<solution->plan->size();i++)
        {
            //tempsol->plan->at(i) = solution->plan->at(i);
            //tempsol->planCC->at(i) = solution->planCC->at(i);
           // tempsol->PIObj = solution->PIObj;
            //tempsol->PSObj = solution->PSObj;
            if(solution->plan->at(i)!=-1)//si la case dans le plan n'est pas vide on remplie le planAffect
            {
                solution->PlanAffect->push_back({i,solution->plan->at(i)});
            }
        }

        //����������������������������������������������������������
        //���������������������������������������������������������������
        //   tempsol->planCC=NULL;
        //LF comment: on traverse tte les fr�quence et on calcule le cout
        int victimFrequency,interfererFrequency;
        int victimTrx,interfererTrx;
        victimTrx = trx.trxID;

        int taille;
        //..........................................................
        //..........................................................
        //vecteur pour enregistrer le couple de cout  interference, separation � la fois
        vector < pair<double,double>  > paircost ;
        //----------------------
        if(trx.AvailableFrequencies->empty()==false)
        {
           taille =trx.AvailableFrequencies->size();

            vector<double> * veccost = new vector <double>(taille);
                 vector<double> * cost = new vector <double>(taille);
            if (taille>1)
            {
              // #pragma omp parallel for
                for(i=0 ;i < taille ; i++)//pour chaque fr�quence probable on evalue le cout
                {

                    victimFrequency =trx.AvailableFrequencies->at(i);
                    veccost->at(i)=0.0;
                    cost->at(i)=0.0;
                    solution->PlanAffect->push_back({trx.trxID,victimFrequency});
                    //on �value la solution avec le nouveau couple : {victimTrx,victimFrequency}
                   int victimTrx1 = trx.trxID; int victimFrequency1 = trx.AvailableFrequencies->at(i);
                    for(j=0;j< solution->PlanAffect->size();j++)
                    {

                        victimTrx = solution->PlanAffect->at(j).first;
                        victimFrequency = solution->PlanAffect->at(j).second;
                       interfererTrx = solution->PlanAffect->at(j).first;
                        interfererFrequency = solution->PlanAffect->at(j).second;
                        if ( interfererTrx != victimTrx1)
                        {
                           // calculer le cout d interference
                            veccost->at(i)  = veccost->at(i)  + afpProblem->computeChannelInterference(victimFrequency1 ,interfererFrequency, victimTrx1, interfererTrx)+
                            afpProblem->computeChannelInterference(interfererFrequency,victimFrequency1 ,interfererTrx, victimTrx1);
                            //cout de separation
                           if(afpProblem->trxs[victimTrx1].sectorID == afpProblem->trxs[interfererTrx].sectorID)
                            {
                                //on teste si la contraite de separation co-secteur est respect�!!
                                if (abs (interfererFrequency-victimFrequency1)<3 )//contrainte co secteur viol�e
                                {
                                    cost->at(i) = cost->at(i) + 1.0;
                                }
                            }// secteur different
                            else
                            {
                                if(afpProblem->trxs[victimTrx1].siteID  == afpProblem->trxs[interfererTrx].siteID)
                                {
                        //on teste si la contrainte de separation co-site est respect�e!!
                                    if (abs (interfererFrequency-victimFrequency1)< 2)//contrainte co secteur viol�e
                                    {
                                        cost->at(i) = cost->at(i) + 1.0;
                                    }
                                }//
                            }
                        }

                    }// for(j=0 ;j < taille ; j++)//pour chaque fr�quence probable on evalue le cout
                    //.............................................................................
                    //.............................................................................
                    // enregister les couts dans le vecteur
                  //  cout << veccost->at(i) << veccost->at(i) << endl;
                    veccost->at(i) = veccost->at(i) + solution->PIObj ;
                    cost->at(i) = cost->at(i) + solution->PSObj ;
                    paircost.push_back({veccost->at(i),cost->at(i)});
                    //...................................................................
                    solution->PlanAffect->pop_back();//on retire le couple probable apres evaluation de cout et l avoir enregistr� dans veccost
                    // cout<<"frequence ::" <<trx.AvailableFrequencies->at(i)<<", son sout veccost[i] ==="<< veccost->at(i)<<endl;
                } //fortrx.AvailableFrequencies
               // vecmin(veccost, indexmin);//indexmin:indice de la fr�quencence qui a la valeur minimale
                //.............................................................................
                //.......................................................................................
               //rechercher l indexmin indice de la fr�quence dans available frequency qui a
               // une distance minimal
               //distance = abs(  paircost.first-paircost.second);
//cout << "paircost[0].first---------------" << paircost[0].first << endl;
//cout << "paircost[0].second---------------" << paircost[0].second << endl;
                indexmin= 0;
               /* double distance = abs (paircost[0].first - paircost[0].second) ;
                for(i=0;i<taille;i++)
                {
                    if(distance > abs( paircost[i].first - paircost[i].second ))
                    {
                        indexmin = i;
                        distance = abs(paircost[i].first - paircost[i].second);
                    }
                }*/


                //2.-----Normaliser -------------------------
//D�finir les valeurs de normalisation
	        pair<double,double> Min;
            pair<double,double> Max;
            pair < double, double > R;// est le point de r�f�rence ; la valeur max (normalis�)
            if (instance == "Seattle")
            //const pair<double,double> MinSeattle = (4000,15) ;
            {
                Min.first = 4000.0;
                Min.second = 15.0 ;
                Max.first = 70000.0;
                Max.second = 200.0;
                R = Max;
            }
            else if (instance == "Denver")
                {
                    Min.first = 130000.0;
                    //Min.second = 1200.0 ;
                    Min.second = 1000.0 ;
                    Max.first = 300000.0;
                    Max.second = 2500.0 ;
                    R = Max;
                }
            else if (instance== "Seattle_conception")
            {
                Min.first =  30.0;
                Min.second = 0.0  ;
                Max.first = 200000.0;
                Max.second = 5.0 ;
                R = Max;
            }

               // Normaliser les valeurs
        R.first = (R.first - Min.first)/(Max.first-Min.first);
        R.second = (R.second - Min.second)/(Max.second-Min.second);
        //cout << "R== " << R.first << " " <<R.second << endl;
        Normalize(paircost,Min,Max);
 //..............................................
    vector < pair<int,double> > distanceLF;
        distanceLF.reserve(trx.AvailableFrequencies->size());
    double DS = 0.0;
    // #pragma omp parallel for
        for(i=0;i<trx.AvailableFrequencies->size();i++)
        {
            DS=sqrt(pow(R.first-paircost[i].first,2)+pow(R.second-paircost[i].second,2));// calculer la distance euclidienne
           //  DS=sqrt(pow(paircost[i].first,2)+pow(paircost[i].second,2));// calculer la distance euclidienne
          //  cout << "DS === " << DS <<endl;
            distanceLF.push_back({i,DS});
        }
         sort(distanceLF.begin(),distanceLF.end(),my_cmpSupFirst); // la plus grande distance est la premi�re

    indexmin = distanceLF.front().first;



//......................................
//cout << "indexmin-----------" << indexmin << endl;

                //..............................................................
                //...................................................................................
                f=trx.AvailableFrequencies->at(indexmin);//indice de la fr�quence ayant un cout minimal,
              vector < pair<double,double>  >().swap(paircost) ;

              solution->PIObj = veccost->at(indexmin);
        solution->PSObj = cost->at(indexmin);
             delete(veccost);
               delete(cost);

delete(solution->PlanAffect);



            }//taille >1
            else
            {
                if(taille==1)
                {
                    f=trx.AvailableFrequencies->at(0);
                // cout<<" frequency choisit:lorsque la taille est 0"<<f<<endl;
                // cout<<"hii"<<endl;
                }
            }//taille == 1?!!*/
        }// Availablefrequencies is empty()
        else//Availablefrequencies==empty()
        {// on choisit la meilleur fr�quence VALID

            //****************#################################""
        //----------------------
        if(trx.validFrequencies->empty()==false)
        {
            vector<double> * veccost = new vector <double>(taille);
                 vector<double> * cost = new vector <double>(taille);
            if (taille>1)
            {
                for(i=0 ;i < taille ; i++)//pour chaque fr�quence probable on evalue le cout
                {

                    victimFrequency =trx.AvailableFrequencies->at(i);
                    veccost->at(i)=0.0;
                    cost->at(i)=0.0;
                    solution->PlanAffect->push_back({trx.trxID,victimFrequency});
                    //on �value la solution avec le nouveau couple : {victimTrx,victimFrequency}
                   int victimTrx1 = trx.trxID; int victimFrequency1 = trx.AvailableFrequencies->at(i);
                    for(j=0;j< solution->PlanAffect->size();j++)
                    {

                        victimTrx = solution->PlanAffect->at(j).first;
                        victimFrequency = solution->PlanAffect->at(j).second;
                       interfererTrx = solution->PlanAffect->at(j).first;
                        interfererFrequency = solution->PlanAffect->at(j).second;
                        if ( interfererTrx != victimTrx1)
                        {
                           // calculer le cout d interference
                            veccost->at(i)  = veccost->at(i)  + afpProblem->computeChannelInterference(victimFrequency1 ,interfererFrequency, victimTrx1, interfererTrx)+
                            afpProblem->computeChannelInterference(interfererFrequency,victimFrequency1 ,interfererTrx, victimTrx1);
                            //cout de separation
                           if(afpProblem->trxs[victimTrx1].sectorID == afpProblem->trxs[interfererTrx].sectorID)
                            {
                                //on teste si la contraite de separation co-secteur est respect�!!
                                if (abs (interfererFrequency-victimFrequency1)<3 )//contrainte co secteur viol�e
                                {
                                    cost->at(i) = cost->at(i) + 1.0;
                                }
                            }// secteur different
                            else
                            {
                                if(afpProblem->trxs[victimTrx1].siteID  == afpProblem->trxs[interfererTrx].siteID)
                                {
                        //on teste si la contrainte de separation co-site est respect�e!!
                                    if (abs (interfererFrequency-victimFrequency1)< 2)//contrainte co secteur viol�e
                                    {
                                        cost->at(i) = cost->at(i) + 1.0;
                                    }
                                }//
                            }
                        }

                    }// for(j=0 ;j < taille ; j++)//pour chaque fr�quence probable on evalue le cout
                    //.............................................................................
                    //.............................................................................
                    // enregister les couts dans le vecteur
                  //  cout << veccost->at(i) << veccost->at(i) << endl;
                    veccost->at(i) = veccost->at(i) + solution->PIObj ;
                    cost->at(i) = cost->at(i) + solution->PSObj ;
                    paircost.push_back({veccost->at(i),cost->at(i)});
                    //...................................................................
                    solution->PlanAffect->pop_back();//on retire le couple probable apres evaluation de cout et l avoir enregistr� dans veccost
                    // cout<<"frequence ::" <<trx.AvailableFrequencies->at(i)<<", son sout veccost[i] ==="<< veccost->at(i)<<endl;
                } //fortrx.AvailableFrequencies
              //  vecmin(veccost, indexmin);//indexmin:indice de la fr�quencence qui a la valeur minimale
                  //.............................................................................
                //.......................................................................................
               //rechercher l indexmin indice de la fr�quence dans available frequency qui a
               // une distance minimal
               //distance = abs(  paircost.first-paircost.second);
               indexmin= 0;
                double distance = abs(paircost[0].first - paircost[0].second) ;
                for(i=0;i<taille;i++)
                {
                    if(distance > abs( paircost[i].first - paircost[i].second))
                    {
                        indexmin = i;
                        distance = abs( paircost[i].first - paircost[i].second);
                    }
                }



                //..............................................................
                //...................................................................................
                f=trx.validFrequencies->at(indexmin);//indice de la fr�quence ayant un cout minimal,
                vector < pair<double,double>  >().swap(paircost) ;

              solution->PIObj = veccost->at(indexmin);
        solution->PSObj = cost->at(indexmin);
             delete(veccost);
               delete(cost);

            }//taille >1
            else
            {
                if(taille==1)
                {
                    f=trx.validFrequencies->at(0);
                // cout<<" frequency choisit:lorsque la taille est 0"<<f<<endl;
                // cout<<"hii"<<endl;
                }
            }//taille == 1?!!
        }
        else//Availablefrequencies==empty()
        {
            cout<<" la liste des fr�quences valide est vide **"<<endl;
        }
           //******************
            //cout<<" la liste des fr�quences disponibles est vide **"<<endl;
        }
    break;
    }//case 3  : best frequency DISTANCE
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~End distance ~~~~~~~~~~~~~~~~~~
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~NASH ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

     case  +4 ://strategy 2 choisir la meilleur fr�quence en terme de NASH
    { int i,j,k,choosedf,indexmin;
            double csect,csite;//coutsect, cout secteur adjacent

        Individual * tempsol =  new Individual();
        int tempfreq;
        //��������������������������������� copier la solution dans tempsol ����������������������
        //���������������������������������������������������������������������������������������
        //tempsol = solution;
        tempsol->plan = new vector <int>(solution->plan->size());
        tempsol->planCC = new vector <pair<double,double> >(solution->planCC->size());
        tempsol->PlanAffect = new vector< pair<int,int> > ();
        tempsol->PIObj = solution->PIObj;
        tempsol->PSObj = solution->PSObj;
        for(i=0;i<solution->plan->size();i++)
        {
            tempsol->plan->at(i) = solution->plan->at(i);
            tempsol->planCC->at(i) = solution->planCC->at(i);
           // tempsol->PIObj = solution->PIObj;
            //tempsol->PSObj = solution->PSObj;
            if(tempsol->plan->at(i)!=-1)//si la case dans le plan n'est pas vide on remplie le planAffect
            {
                tempsol->PlanAffect->push_back({i,tempsol->plan->at(i)});
            }
        }
        int victimFrequency,interfererFrequency;
        int victimTrx,interfererTrx;
        victimTrx = trx.trxID;
        victimTrx = trx.trxID;
            int taille;
            //--------------
            // on choisit sauf si la liste des fr�quences Availble n est pas vide
          vector < pair<double,double>  > paircost ;
      if(trx.AvailableFrequencies->empty()==false)
        {
           taille =trx.AvailableFrequencies->size();

            vector<double> * veccost = new vector <double>(taille);
             vector<double> * cost = new vector <double>(taille);
            if (taille>1)
            {
            // #pragma omp parallel for
                for(i=0 ;i < taille ; i++)//pour chaque fr�quence probable on evalue le cout
                {

                    int victimFrequency =trx.AvailableFrequencies->at(i);
                    //tempsol->plan->at(victimTrx)=victimFrequency;
                    //veccost[i]=0.0;
                    // veccost->at(i) ;
                    veccost->at(i)=0.0;
                    cost->at(i)=0.0;

                    //....................
                  //  paircost.push_back({0.0,0.0});
                    //.........................
                    //   veccost->at(0)=5.0;
                    // cout<<"veccost->size()"<<veccost->size()<<endl;
                    tempsol->PlanAffect->push_back({trx.trxID,victimFrequency});
                    // tempsol->PlanAffect->size();
                    // cout<<"   tempsol->PlanAffect->size()"<<   tempsol->PlanAffect->size()<<endl;
                    //on �value la solution avec le nouveau couple : {victimTrx,victimFrequency}

                        int victimTrx1 = trx.trxID; int victimFrequency1 = trx.AvailableFrequencies->at(i);

                  for(j=0;j<tempsol->PlanAffect->size();j++)
                    {

                        victimTrx = tempsol->PlanAffect->at(j).first;
                        victimFrequency = tempsol->PlanAffect->at(j).second;
                       /* for(k = 0 ; k < tempsol->PlanAffect->size() ; k++)
                        {
                            interfererTrx=tempsol->PlanAffect->at(k).first;
                            interfererFrequency=tempsol->PlanAffect->at(k).second;
                            if ( interfererTrx != victimTrx)
                            {
                                veccost->at(i) = veccost->at(i)+ afpProblem->computeChannelInterference(victimFrequency ,interfererFrequency, victimTrx,interfererTrx);
                            //PSPSPSPSPSPPSPSPSPSPSPSPSPSPSP
                            }
                        }*/
                        interfererTrx=tempsol->PlanAffect->at(j).first;
                        interfererFrequency=tempsol->PlanAffect->at(j).second;
                        if ( interfererTrx != victimTrx1)
                        {
                            veccost->at(i)  = veccost->at(i)  + afpProblem->computeChannelInterference(victimFrequency1 ,interfererFrequency, victimTrx1, interfererTrx)+
                            afpProblem->computeChannelInterference(interfererFrequency,victimFrequency1 ,interfererTrx, victimTrx1);
                            //cout de separation
                           if(afpProblem->trxs[victimTrx1].sectorID == afpProblem->trxs[interfererTrx].sectorID)
                            {
                                //on teste si la contraite de separation co-secteur est respect�!!
                                if (abs (interfererFrequency-victimFrequency1)< 3)//contrainte co secteur viol�e
                                {
                                    cost->at(i) = cost->at(i) + 1.0;
                                }
                            }// secteur different
                            else
                            {
                                if(afpProblem->trxs[victimTrx1].siteID  == afpProblem->trxs[interfererTrx].siteID)
                                {
                        //on teste si la contrainte de separation co-site est respect�e!!
                                    if (abs (interfererFrequency-victimFrequency1)< 2)//contrainte co secteur viol�e
                                    {
                                        cost->at(i) = cost->at(i) + 1.0;
                                    }
                                }//
                            }
                        }
                        /* for(k = j+1 ; k < tempsol->PlanAffect->size() ; k++)
                        {
                            interfererTrx=tempsol->PlanAffect->at(k).first;
                            interfererFrequency=tempsol->PlanAffect->at(k).second;
                            if(afpProblem->trxs[victimTrx].sectorID == afpProblem->trxs[interfererTrx].sectorID)
                            {
                                //cout << "hiiiii i m here we are in the same sector !!!" << endl;
                                if (abs ( interfererFrequency-victimFrequency)< 3)//contrainte co secteur viol�e
                                {
                                // cout << "Oups we have violated co sector constraint !!" << endl;
                                    cost->at(i) = cost->at(i) + 1.0;
                                }
                            }
                            else
                            {
                               if(afpProblem->trxs[victimTrx].siteID  == afpProblem->trxs[interfererTrx].siteID)
                               {
                                //on teste si la contrainte de separation co-site est respect�e!!
                                    if (abs (interfererFrequency-victimFrequency)< 2)//contrainte co secteur viol�e
                                    {
                                    // cout << "Oups we have violated co site constraint !!" << endl;
                                        cost->at(i) = cost->at(i) + 1.0;
                                    // cout << " csite " << csite<<endl;
                                    }

                                }//if(trx.siteID == afpProblem->trxs[tempsol->PlanAffect->at(j).first].siteID )

                            }//else on n est pas dans le meme site

                        }*/

                       //PSPSPSPSPSPSPSPSPSPSPSPSPSPSPSPSPSPSPSP
                    }// for(j=0 ;j < taille ; j++)//pour chaque fr�quence probable on evalue le cout
                    //.............................................................................
                    //.............................................................................
                    // enregister les couts dans le vecteur
                  //  cout << veccost->at(i) << veccost->at(i) << endl;
                    veccost->at(i) = veccost->at(i) + tempsol->PIObj ;
                    cost->at(i) = cost->at(i) + tempsol->PSObj ;
                    paircost.push_back({veccost->at(i),cost->at(i)});
                    //...................................................................
                    tempsol->PlanAffect->pop_back();//on retire le couple probable apres evaluation de cout et l avoir enregistr� dans veccost
                    // cout<<"frequence ::" <<trx.AvailableFrequencies->at(i)<<", son sout veccost[i] ==="<< veccost->at(i)<<endl;
                } //fortrx.AvailableFrequencies
                 //tempsol->plan->at(trx.trxID) = -1;
                    // cout<<"frequence ::" <<trx.AvailableFrequencies->at(i)<<", son sout veccost[i] ==="<< veccost->at(i)<<endl;
                //} //fortrx.AvailableFrequencies
               //utiliser l equilibre de nash
              //le nombre de g�n�ration est le nombre de fr�quence valide
            //chaque position dans AvailableFrequencies correspond � currentobjectif
            //..............................................................
           //...................................................................................
            //utiliser l equilibre de nash
                // cout << " vcouts->size()  "<< vcouts->size() << endl;
                //+++++++++++++++++++++++++ afficer vcost
            /*  ofstream ResultFile;
            string path="Exemples/veccostNASHPS_K_.txt";
            ResultFile.open(path.c_str(),std::ios::app);
            if (!ResultFile) {
                cerr << "Unable to open file!!";
                exit(1);   // call system to stop
            }
            ResultFile << " trx -......" << trx.trxID << endl;
            for(i=0 ;i < trx.AvailableFrequencies->size() ; i++)
            {ResultFile << trx.AvailableFrequencies->at(i) << " :   " << paircost[i].first << " = " << veccost->at(i)<<  ", " << paircost[i].second<<endl;
            }*/


            //+++++++++++++++++++++++++++++++++++++++++++++
            double BestObjectivePI,CurrentObjectivePI;
            double BestObjectivePS,CurrentObjectivePS;

             //-------------------------------
            //trouver BestObjectivePI et BestObjectivePS;
            //cout << " paircost[0].first---" << paircost[0].first <<endl;
            //cout << " paircost[0].second---" << paircost[0].second <<endl;
            BestObjectivePI = paircost[0].first;
            BestObjectivePS = paircost[0].second;
            //cout << "BestObjectivePI,BestObjectivePS  " << BestObjectivePI << " , " << BestObjectivePS << endl;
            for(i=0;i<trx.AvailableFrequencies->size();i++)
            {
                //cout <<  "paircost[i].first " << paircost[i].first << endl;
                if(BestObjectivePI > paircost[i].first)
                {
                    BestObjectivePI = paircost[i].first;
                    //cout << "BestObjectivePI "<<BestObjectivePI<< endl;
                }
                if(BestObjectivePS > paircost[i].second)
                {
                    BestObjectivePS = paircost[i].second;
                }
            }
            // cout << "BestObjectivePI,BestObjectivePS  " << BestObjectivePI << " , " << BestObjectivePS << endl;
            // trouver le meilleur couple
            int indexNASHEbest;
            indexNASHEbest = 0;
            vector<double> NASHEJ;//---------------
            double NASHEbest;
            const int SizeNashVect = trx.AvailableFrequencies->size();
            NASHEJ.reserve(SizeNashVect);
            // cout << "SizeNashVect**** " << SizeNashVect <<endl;
            // indexmin = 0;
            double gama = 0.1;
            //remplire le table de NAshj-------------------------------
            // #pragma omp parallel for
            for( i = 0; i < trx.AvailableFrequencies->size();i++)
            {
                if (BestObjectivePS != 0)
                {
                    if(BestObjectivePI != 0 )
                    {
                       //NASHEJ.push_back(0.9*(paircost[i].first - BestObjectivePI)/BestObjectivePI+ 0.1*(paircost[i].second - BestObjectivePS)/BestObjectivePS);
                        NASHEJ.push_back((paircost[i].first - BestObjectivePI)/BestObjectivePI+ (paircost[i].second - BestObjectivePS)/BestObjectivePS);
                        //NASHEJ.push_back((paircost[i].second - BestObjectivePS)/BestObjectivePS);
                    }
                    else
                    {
                       //NASHEJ.push_back(0.1*(paircost[i].second - BestObjectivePS)/BestObjectivePS);
                        NASHEJ.push_back((paircost[i].second - BestObjectivePS)/BestObjectivePS);


                    }
                }
                else
                {
                    //NASHEJ.push_back(0);
                    if(BestObjectivePI !=0 )
                    {
                        //NASHEJ.push_back(0.9*(paircost[i].first - BestObjectivePI)/BestObjectivePI);
                        NASHEJ.push_back((paircost[i].first - BestObjectivePI)/BestObjectivePI);
                    }
                    else
                    {
                        NASHEJ.push_back(0);
                    }
                }
            }

             //++++++++++++++++++++++++++aficher les valeur de nash ++++++++++++++
            /* ResultFile << "���������������������� NASH ����������" <<endl;
            for(i=0 ;i < trx.AvailableFrequencies->size() ; i++)
            {
                ResultFile << "NASHEJ.at(i) " << NASHEJ.at(i) <<endl;
            }*/
            //------------------------trouver la meilleur valeur de NAsh (la plus petite)--------------------------
            /*NASHEbest = NASHEJ.at(0);
           //  cout << "NASHEJ.at(0) ......" <<NASHEJ.at(0)<<endl;
            for( i = 0; i < trx.AvailableFrequencies->size();i++)
            {
                if ( NASHEJ.at(i) <  NASHEbest )//enregistrer cette solution
                {
                    NASHEbest = NASHEJ.at(i);
                    indexNASHEbest = i;
                   // cout << "hi ..." <<endl;
                }
            }
            indexmin = indexNASHEbest;*/

          //  cout << "indexmin " <<indexmin <<endl;

         //   vecmin(veccost,indexmin);
            //cout << "indexmin "<< indexmin << endl;
 //++++++++++++++++++++rechercher la valeur minimal dans un tableau nash si plus sieur valeur de nash sont egale
 //on choisit al�atoirement une variable  +++++
   vector < pair<int,double>  > paircostNash ;//pour sauvegarder la fr�quence, et sa valeur de nash
             paircostNash.reserve(NASHEJ.size());
    for(i = 0 ; i< NASHEJ.size(); i++)
    {
       paircostNash.push_back({trx.AvailableFrequencies->at(i),NASHEJ.at(i)});
       //paircostNash.at(i).first = trx.AvailableFrequencies->at(i);
        //paircostNash.at(i).second = NASHEJ.at(i);
    }
    //-----------------------------------
    /* ResultFile << "avant  le tri -----" << endl;
     for ( i = 0 ; i < paircostNash.size() ; i++)
    ResultFile << " frequence , nash :::" << paircostNash.at(i).first << " , " << paircostNash.at(i).second << endl;*/
    //------------------------------trier le tableau ---------
    sort(paircostNash.begin(),paircostNash.end(),my_cmpInfDoublePair);//le pleus petit d abord
   // sort(paircostNash.begin(),paircostNash.end(),my_cmpSupFirst);
    //-----------------------------------------------------
    // si les valeurs sont �gales, nous choisissons al�atoirement une fr�quence
    //cout << "paircostNash.size()  " << paircostNash.size() <<endl;
    //--------------------- apr�s le tri
   /* ResultFile << "apr�s le tri -----" << endl;
     for ( i = 0 ; i < paircostNash.size() ; i++)
    ResultFile << " frequence , nash :::" << paircostNash.at(i).first << " , " << paircostNash.at(i).second << endl;*/

    //---------------------------------------------------
    i = 0;     k = 0 ;
    for(i = 0 ; i < paircostNash.size(); i++)
    {
         double val = paircostNash.at(i).second;
         pair<int,double> pnextval;
         if((i+1) < paircostNash.size())
         {
            pnextval = paircostNash.at(i+1);
            double nextval = pnextval.second;
            // on copie les valeurs egales dans un tableau
            //cout<< "hiiii here " << endl;
            if( val == nextval )
            {
                k = k +1 ;//k contient le nombre de valeur �gale
               // cout<< "hiiii here " << endl;

            }
            else
            {
                i = paircostNash.size();
            }
         }
    }
    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
   // ResultFile << "k valeur agales "<< k <<endl;
    indexmin = rand() % (k+1);
     // ResultFile << " la fr�quence probable ***"<< paircostNash.at(indexmin).first<<endl;
     f = paircostNash.at(indexmin).first;
        // rechercher l indice de  f*************** ajout� le 25-4-2019
    int indexf;
    for(i = 0 ; i < trx.AvailableFrequencies->size(); i++)
    {
        if(trx.AvailableFrequencies->at(i) == f)
        {
            indexf = i;
            i = trx.AvailableFrequencies->size();
        }
    }

      solution->PIObj = veccost->at(indexf);
      solution->PSObj = cost->at(indexf);
      solution->planCC->at(trx.trxID).first = solution->PIObj;
      solution->planCC->at(trx.trxID).second = solution->PSObj;
            //................................................................................
            //................................................................................
           // f=trx.AvailableFrequencies->at(indexmin);//indice de la fr�quence ayant un cout minimal,




           // ResultFile << " f choisit est======>" << f <<endl;




           // ResultFile.close();
            //vider la m�moire--vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
           // vector<double>().swap(NASHEJ);
            vector < pair<double,double>  >().swap(paircost) ;
             delete(veccost);
               delete(cost);
              delete(tempsol->PlanAffect);
              //-------------------
              vector < pair<int,double>  > ().swap(paircostNash);
                vector<double> ().swap(NASHEJ);
                delete(tempsol);




            }//taille >1
            else
            {
                if(taille==1)
                {
                    f=trx.AvailableFrequencies->at(0);
                // cout<<" frequency choisit:lorsque la taille est 0"<<f<<endl;
                // cout<<"hii"<<endl;
                }
            }//taille == 1?!!
        }// Availablefrequencies is empty()
        else//Availablefrequencies==empty()
        {// on choisit la meilleur fr�quence VALID

            //****************#################################""
        //----------------------
      if(trx.validFrequencies->empty()==false)
            {
                taille =trx.validFrequencies->size();
                vector<double> * veccost = new vector <double>(taille);
                  vector<double> * cost = new vector <double>(taille);
                if (taille>1)
                {
                    for(i=0 ;i < taille ; i++)//pour chaque fr�quence probable on evalue le cout
                {

                    victimFrequency =trx.validFrequencies->at(i);
                    //on �value la solution avec le nouveau couple : {victimTrx,victimFrequency}
                      veccost->at(i)=0.0;
                    cost->at(i)=0.0;
                    tempsol->PlanAffect->push_back({trx.trxID,victimFrequency});
                    //on �value la solution avec le nouveau couple : {victimTrx,victimFrequency}
                   int victimTrx1 = trx.trxID; int victimFrequency1 = trx.AvailableFrequencies->at(i);
                    for(j=0;j<tempsol->PlanAffect->size();j++)
                    {

                        victimTrx = tempsol->PlanAffect->at(j).first;
                        victimFrequency = tempsol->PlanAffect->at(j).second;
                       interfererTrx=tempsol->PlanAffect->at(j).first;
                        interfererFrequency=tempsol->PlanAffect->at(j).second;
                        if ( interfererTrx != victimTrx1)
                        {
                           // calculer le cout d interference
                            veccost->at(i)  = veccost->at(i)  + afpProblem->computeChannelInterference(victimFrequency1 ,interfererFrequency, victimTrx1, interfererTrx)+
                            afpProblem->computeChannelInterference(interfererFrequency,victimFrequency1 ,interfererTrx, victimTrx1);
                            //cout de separation
                           if(afpProblem->trxs[victimTrx1].sectorID == afpProblem->trxs[interfererTrx].sectorID)
                            {
                                //on teste si la contraite de separation co-secteur est respect�!!
                                if (abs (interfererFrequency-victimFrequency1)<3 )//contrainte co secteur viol�e
                                {
                                    cost->at(i) = cost->at(i) + 1.0;
                                }
                            }// secteur different
                            else
                            {
                                if(afpProblem->trxs[victimTrx1].siteID  == afpProblem->trxs[interfererTrx].siteID)
                                {
                        //on teste si la contrainte de separation co-site est respect�e!!
                                    if (abs (interfererFrequency-victimFrequency1)< 2)//contrainte co secteur viol�e
                                    {
                                        cost->at(i) = cost->at(i) + 1.0;
                                    }
                                }//
                            }
                        }

                    }// for(j=0 ;j < taille ; j++)//pour chaque fr�quence probable on evalue le cout
                    //.............................................................................
                    //.............................................................................
                    // enregister les couts dans le vecteur
                  //  cout << veccost->at(i) << veccost->at(i) << endl;
                    veccost->at(i) = veccost->at(i) + tempsol->PIObj ;
                    cost->at(i) = cost->at(i) + tempsol->PSObj ;
                    paircost.push_back({veccost->at(i),cost->at(i)});
                    //...................................................................
                    tempsol->PlanAffect->pop_back();//on retire le couple probable apres evaluation de cout et l avoir enregistr� dans veccost
                    // cout<<"frequence ::" <<trx.AvailableFrequencies->at(i)<<", son sout veccost[i] ==="<< veccost->at(i)<<endl;
                } //fortrx.AvailableFrequencies
                    //.............................................................................
                    //.......................................................................................
                    //rechercher l indexmin indice de la fr�quence dans available frequency qui a
                    // une distance minimal
                    //distance = abs(  paircost.first-paircost.second);
                    //..............................................................
                    //...................................................................................
                    //utiliser l equilibre de nash
                    double BestObjectivePI,CurrentObjectivePI;
                    double BestObjectivePS,CurrentObjectivePS;
                    //-------------------------------
                    //trouver BestObjectivePI et BestObjectivePS;
                    //cout << " paircost[0].first---" << paircost[0].first <<endl;
                    //cout << " paircost[0].second---" << paircost[0].second <<endl;
                    BestObjectivePI = paircost[0].first;
                    BestObjectivePS = paircost[0].second;
                    for(i=0;i<trx.validFrequencies->size();i++)
                    {
                        if(BestObjectivePI > paircost[i].first)
                        {
                            BestObjectivePI = paircost[i].first;
                        }
                        if(BestObjectivePS > paircost[i].second)
                        {
                            BestObjectivePS = paircost[i].second;
                        }
                    }
                    // trouver le meilleur couple
                    int indexNASHEbest;
                    indexNASHEbest = 0;
                    vector<double> NASHEJ;
                    double NASHEbest;
                    const int SizeNashVect = trx.validFrequencies->size();
                    // NASHEJ.reserve(SizeNashVect);
                    // cout << "SizeNashVect**** " << SizeNashVect <<endl;
                    // indexmin = 0;
                    double gama = 0.1;
                  //remplire le table de NAshj-------------------------------
            for( i = 0; i < trx.AvailableFrequencies->size();i++)
            {
                if (BestObjectivePS != 0)
                {
                    if(BestObjectivePI !=0 )
                    {
                        NASHEJ.push_back((paircost[i].first - BestObjectivePI)/BestObjectivePI+ (paircost[i].second - BestObjectivePS)/BestObjectivePS);
                    }
                    else
                    {
                         NASHEJ.push_back((paircost[i].first - BestObjectivePS)/BestObjectivePS);
                    }
                }
                else
                {
                    if(BestObjectivePI !=0 )
                    {
                        NASHEJ.push_back((paircost[i].first - BestObjectivePI)/BestObjectivePI);
                    }
                    else
                    {
                        NASHEJ.push_back(0);
                    }
                }
            }
            //-----trouver la meilleur valeur de NAsh (la plus petite)--------------------------
            //++++++++++++++++++++rechercher la valeur minimal dans un tableau nash si plus sieur valeur de nash sont egale
 //on choisit al�atoirement une variable  +++++
   vector < pair<int,double>  > paircostNash ;//pour sauvegarder la fr�quence, et sa valeur de nash
             paircostNash.reserve(NASHEJ.size());
    for(i = 0 ; i< NASHEJ.size(); i++)
    {
       paircostNash.push_back({trx.validFrequencies->at(i),NASHEJ.at(i)});
       //paircostNash.at(i).first = trx.AvailableFrequencies->at(i);
        //paircostNash.at(i).second = NASHEJ.at(i);
    }

    //------------------------------trier le tableau selon un ordre croissant  ---------
    sort(paircostNash.begin(),paircostNash.end(),my_cmpInfDoublePair);
    //-----------------------------------------------------
    //---------------------Rassembler les valeurs minimal �gales et choisir al�atoirement une------------------------------
    i = 0;     k = 0 ;
    for(i = 0 ; i < paircostNash.size(); i++)
    {
         double val = paircostNash.at(i).second;
         pair<int,double> pnextval;
         if((i+1) < paircostNash.size())
         {
            pnextval = paircostNash.at(i+1);
            double nextval = pnextval.second;
            // on copie les valeurs egales dans un tableau
            //cout<< "hiiii here " << endl;
            if( val == nextval )
            {
                k = k +1 ;//k contient le nombre de valeur �gale
               // cout<< "hiiii here " << endl;

            }
            else
            {
                i = paircostNash.size();
            }
         }
    }
    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    indexmin = rand() % (k+1);
     f = paircostNash.at(indexmin).first;
    // rechercher l indice de  f*************** ajout� le 25-4-2019
    int indexf;
    for(i = 0 ; i < trx.validFrequencies->size(); i++)
    {
        if(trx.validFrequencies->at(i) == f)
        {
            indexf = i;
            i = trx.validFrequencies->size();
        }
    }
     solution->PIObj = veccost->at(indexf);
     solution->PSObj = cost->at(indexf);
     //................................................................................                vector < pair<double,double>  >().swap(paircost) ;
       //vider la m�moire--vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
           // vector<double>().swap(NASHEJ);
            vector < pair<double,double>  >().swap(paircost) ;

             delete(veccost);
               delete(cost);
              delete(tempsol->PlanAffect);
                //vector<double> ().swap(NASHEJ);
              //  delete(tempsol);
 //vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
            //vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
            }//taille >1::pl
            else
            {
                if(taille==1)
                {
                    f=trx.validFrequencies->at(0);
                // cout<<" frequency choisit:lorsque la taille est 0"<<f<<endl;
                // cout<<"hii"<<endl;
                }
            }//taille == 1?!!
        }
        else//Availablefrequencies==empty()
        {
            cout<<" la liste des fr�quences valide est vide **"<<endl;
        }
            //******************
            //cout<<" la liste des fr�quences disponibles est vide **"<<endl;
        }
    break;
    }//case 4 : best frequency in term of NASH

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~END NASH
    case 10 :
    {

         int i,indexmin;
        Individual * tempsol =  new Individual();int tempfreq;
        tempsol = solution;
        //   tempsol->planCC=NULL;
        //LF comment: on traverse tte les fr�quence et on calcule le cout
        int victimFrequency,interfererFrequency;
        int victimTrx,interfererTrx;
        victimTrx = trx.trxID;
        //------utiliser ma fonction de calcul de cout
        tempsol=solution; int j;

        //on remplie planaffect pour accelerer la recherche
        tempsol->PlanAffect = new vector< pair<int,int> > ();
        for(i=0;i<tempsol->plan->size();i++)
        {
            if (tempsol->plan->at(i)!=-1)//si la case dans le plan n'est pas vide on remplie le planAffect
            {
                tempsol->PlanAffect->push_back({i,tempsol->plan->at(i)});
            }
        }
        //cout<<"   tempsol->PlanAffect->size()"<<   tempsol->PlanAffect->size()<<endl;
        //----------------------
        victimTrx=trx.trxID; int taille;
                   //..........................................................
            //..........................................................
            //vecteur pour enregistrer le couple de cout  interference, separation � la fois

              vector < pair<double,double>  > paircost;
               paircost.reserve(afpProblem->trxs.size());
            //.............................................................
            //....................................................
        //----------------------
        if(trx.AvailableFrequencies->empty()==false)
        {
           taille =trx.AvailableFrequencies->size();

            vector<double> * veccost = new vector <double>(taille);

            if (taille>1)
            {
                for(i=0 ;i < taille ; i++)//pour chaque fr�quence probable on evalue le cout
                {
                    victimFrequency =trx.AvailableFrequencies->at(i);
                    //tempsol->plan->at(victimTrx)=victimFrequency;
                    //veccost[i]=0.0;
                    // veccost->at(i) ;
                    veccost->at(i)=0.0;
                    //....................
                   paircost.push_back({0.0,0.0});
                    //.........................
                    //   veccost->at(0)=5.0;
                    // cout<<"veccost->size()"<<veccost->size()<<endl;
                    tempsol->PlanAffect->push_back({victimTrx,victimFrequency});
                    // tempsol->PlanAffect->size();
                    // cout<<"   tempsol->PlanAffect->size()"<<   tempsol->PlanAffect->size()<<endl;
                    //on �value la solution avec le nouveau couple : {victimTrx,victimFrequency}
                    double cost = 0.0;
                    for(j=0;j<tempsol->PlanAffect->size();j++)
                    {
                        interfererTrx=tempsol->PlanAffect->at(j).first;
                        interfererFrequency=tempsol->PlanAffect->at(j).second;
                        veccost->at(i) = veccost->at(i)+ afpProblem->computeChannelInterference(victimFrequency ,interfererFrequency, victimTrx,interfererTrx);
                        //PSPSPSPSPSPPSPSPSPSPSPSPSPSPSP
                        // calculer le cout de s�paration
                        if(victimTrx!=interfererTrx)
                          {if(trx.sectorID == afpProblem->trxs[tempsol->PlanAffect->at(j).first].sectorID )
                        {
                        //cout << "hiiiii i m here we are in the same sector !!!" << endl;
                            if(abs(victimFrequency - tempsol->PlanAffect->at(j).second ) < 3)//contrainte viol�e
                            {
                                // cout << "Oups we have violated co sector constraint !!" << endl;
                                cost = cost + 1.0;
                            }
                        }
                        else
                        {
                                      //cout << "Hiii we are not in the same  sector!!!" << endl;
                            if(trx.siteID == afpProblem->trxs[tempsol->PlanAffect->at(j).first].siteID )
                            {
                                         //cout << "hiiiii i m here we are in the same site!!!" << endl;
                                if(abs(victimFrequency - tempsol->PlanAffect->at(j).second ) < 2)//contrainte viol�e
                                {
                                    // cout << "Oups we have violated co site constraint !!" << endl;
                                    cost = cost + 1.0;
                                    // cout << " csite " << csite<<endl;
                                }

                            }//if(trx.siteID == afpProblem->trxs[tempsol->PlanAffect->at(j).first].siteID )

                        }//else on n est pas dans le meme site

                       //PSPSPSPSPSPSPSPSPSPSPSPSPSPSPSPSPSPSPSP
                    }}// for(i=0 ;i < taille ; i++)//pour chaque fr�quence probable on evalue le cout
                    //.............................................................................
                    // enregister les couts dans le vecteur

                    paircost[i].first = veccost->at(i);
                    paircost[i].second = cost;
                    //...................................................................
                    tempsol->PlanAffect->pop_back();//on retire le couple probable apres evaluation de cout et l avoir enregistr� dans veccost
                    // cout<<"frequence ::" <<trx.AvailableFrequencies->at(i)<<", son sout veccost[i] ==="<< veccost->at(i)<<endl;
                } //fortrx.AvailableFrequencies
              // cout <<  "paircost[0].first---------" << paircost[0].first <<endl;
             //  cout <<  "paircost[0].second ---------" << paircost[0].second <<endl;
              //  vecmin(veccost, indexmin);//indexmin:indice de la fr�quencence qui a la valeur minimale
                //.............................................................................


//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
     //DOMINANCE
                 //...................................................
                 //.....................................................
                // I . Retirer la non dominance pour chaque fr�quence
                // ....................................................
                //...................................................

                bool test = true; //je supose que la soluution est domiin�e et je vais tester si c est vrai
                int indexdominantf, NonDominantScore;
                indexdominantf = -1;
                vector < pair<int,int> > IndexesFreqsNonDominantes;
                 //(int,int) :: le premier enregistre l index de la fr�quence non dominante
                  //(int,int) :: le dexieme , combien de fois la fr�quence est non dominante
                IndexesFreqsNonDominantes.reserve(trx.AvailableFrequencies->size());
                for( i = 0; i < trx.AvailableFrequencies->size();i++)//la solution condidate est dans l indice i
                {
                  //dominance par rapport au premier joueur
                  NonDominantScore = 0 ;
                  //IndexesFreqsNonDominantes[i].first = i ;
                 // IndexesFreqsNonDominantes[i].second = 0;
                   for( j = 0; j < trx.AvailableFrequencies->size();j++)
                   {
                       if (i!=j)
                       {
                            // je te
                            if (paircost[i].first <= paircost[j].first) // on teste la non dominance par rapport au premier objectif
                            {
                                if (paircost[i].second < paircost[j].second)
                                {
                                     NonDominantScore =   NonDominantScore;                                   ;
                                }
                                 IndexesFreqsNonDominantes.push_back({i,NonDominantScore});
                            }//
                            else
                            {
                                if (paircost[i].second <= paircost[j].second) // on teste la non dominance par rapport au deuci�me objectif
                                {
                                     if (paircost[i].first < paircost[j].first)
                                    {
                                        NonDominantScore =   NonDominantScore + 1 ;                                   ;
                                    }
                                     IndexesFreqsNonDominantes.push_back({i,NonDominantScore});
                                }
                            }
                            //sauvegarder le score
                            //IndexesFreqsNonDominantes[i].second = NonDominantScore;

                        }//i!=j
                    }//fin j

                }//fin i
                //...................................................
                 //.....................................................
                // II . Trier le tableau de la non dominance selon un ordre croissant
                // ....................................................
                //...................................................
               // sort(IndexesFreqsNonDominantes.begin(),IndexesFreqsNonDominantes.end(),my_cmp);
                //la
                   // copier les solution trouver dans un vecteur avec son cout d separation qui
                vector < pair < int, double> > NonDominanteCost;
                NonDominanteCost.reserve(IndexesFreqsNonDominantes.size());
                for(i = 0; i < IndexesFreqsNonDominantes.size(); i++ )
                {
                    NonDominanteCost.push_back({IndexesFreqsNonDominantes[i].first, paircost[IndexesFreqsNonDominantes[i].first].second });
                }
                // trier le tableau selon un ordre d�croisant du cout et retirer la premi�re valeur dans NonDominanteCost


                sort(NonDominanteCost.begin(),NonDominanteCost.end(),my_cmpInfDoublePair);
                indexmin = NonDominanteCost.front().first;

     //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    // parmis les solution trouv�e IndexesFreqsDominantes dans r�cup�r�rer la  fr�quence qui a la plus petite valeur decout
    //cout << "IndexesFreqsDominantesPSPS.size()------- "<< IndexesFreqsNonDominantes.size() << endl;
    /*if (IndexesFreqsNonDominantes.empty() == false)
    {
        indexmin= 0 ;
        double costdom = veccost->at(IndexesFreqsNonDominantes[0]);
        cout <<" costdom ------------" <<costdom << endl;
        // chosir la fr�quence avec le pust petit cout
        int index ;
        for ( j= 0 ; j < IndexesFreqsNonDominantes.size() ; j++)
        {
            index = IndexesFreqsNonDominantes[j];
            if(costdom > veccost->at(index) );
            {
                indexmin = index ;
                costdom = veccost->at(index);
            }
        }
         cout << "indexmin***" << indexmin << endl;
    }
    else // si je trouve pas je r�cup�re la fr�quence qui a le plus petit cout
    {vecmin(veccost, indexmin);*/
   // vecmin(veccost, indexmin);
  // indexmin = IndexesFreqsNonDominantes[0].first ;
  //  cout << "noooooooooooooooo---" <<endl;

    //............................End dominance ..................................
    //..............................................................
    //................................................................................
    f=trx.AvailableFrequencies->at(indexmin);//indice de la fr�quence recherch�
    //--------------------- dominance available
    }//if (taille >1)
    else
    {
       if(taille==1) // la taille  == 1; je n ai qu'un choix
        {
            f=trx.AvailableFrequencies->at(0);
            // cout<<" frequency choisit:lorsque la taille est 0"<<f<<endl;
            // cout<<"hii"<<endl;
        }
    }//taille :.!=1
 }// Availablefrequencies is empty()
else//Availablefrequencies==empty() // aucune fr�quence n'est diponible j'utilise les fr�quence valides
        {// on choisit la meilleur fr�quence VALID

            //****************#################################""
        //----------------------
        if(trx.validFrequencies->empty()==false)
        {
            taille =trx.validFrequencies->size();
            vector<double> * veccost = new vector <double>(taille);
            if (taille>1)
            {
                for(i=0 ;i < taille ; i++)//pour chaque fr�quence probable on evalue le cout
                {
                    victimFrequency =trx.validFrequencies->at(i);
                    //tempsol->plan->at(victimTrx)=victimFrequency;
                    //veccost[i]=0.0;
                    // veccost->at(i) ;
                    veccost->at(i)=0.0;
                    //...................................
                   paircost.push_back({0.0,0.0});
                    double cost = 0.0;

                    //..........................
                    //   veccost->at(0)=5.0;
                    // cout<<"veccost->size()"<<veccost->size()<<endl;
                    tempsol->PlanAffect->push_back({victimTrx,victimFrequency});
                    // tempsol->PlanAffect->size();
                    // cout<<"   tempsol->PlanAffect->size()"<<   tempsol->PlanAffect->size()<<endl;
                    //on �value la solution avec le nouveau couple : {victimTrx,victimFrequency}
                    for(j=0;j<tempsol->PlanAffect->size();j++)
                    {
                        interfererTrx=tempsol->PlanAffect->at(j).first;
                        interfererFrequency=tempsol->PlanAffect->at(j).second;
                        veccost->at(i) = veccost->at(i)+afpProblem->computeChannelInterference(victimFrequency ,interfererFrequency, victimTrx,interfererTrx);

                     //PSPSPSPSPSPPSPSPSPSPSPSPSPSPSP
                        // calculer le cout de s�paration
                      if(victimTrx!=interfererTrx)
                      {if(trx.sectorID == afpProblem->trxs[tempsol->PlanAffect->at(j).first].sectorID )
                        {
                        //cout << "hiiiii i m here we are in the same sector !!!" << endl;
                            if(abs(victimFrequency - tempsol->PlanAffect->at(j).second ) < 3)//contrainte viol�e
                            {
                                // cout << "Oups we have violated co sector constraint !!" << endl;
                                cost = cost + 1.0;
                            }
                        }
                        else
                        {
                                      //cout << "Hiii we are not in the same  sector!!!" << endl;
                            if(trx.siteID == afpProblem->trxs[tempsol->PlanAffect->at(j).first].siteID )
                            {
                                         //cout << "hiiiii i m here we are in the same site!!!" << endl;
                                if(abs(victimFrequency - tempsol->PlanAffect->at(j).second ) < 2)//contrainte viol�e
                                {
                                    // cout << "Oups we have violated co site constraint !!" << endl;
                                    cost = cost + 1.0;
                                    // cout << " csite " << csite<<endl;
                                }

                            }//if(trx.siteID == afpProblem->trxs[tempsol->PlanAffect->at(j).first].siteID )

                        }//else on n est pas dans le meme site

                       //PSPSPSPSPSPSPSPSPSPSPSPSPSPSPSPSPSPSPSP

                    }}
                     //.............................................................................
                    // enregister les couts dans le vecteur

                    paircost[i].first = veccost->at(i);
                    paircost[i].second = cost ;
                    //...................................................................
                    tempsol->PlanAffect->pop_back();//on retire le couple probable apres evaluation de cout et l avoir enregistr� dans veccost
                    // cout<<"frequence ::" <<trx.AvailableFrequencies->at(i)<<", son sout veccost[i] ==="<< veccost->at(i)<<endl;
                } //fortrx.AvailableFrequencies
              //  vecmin(veccost, indexmin);//indexmin:indice de la fr�quencence qui a la valeur minimale
                  //.............................................................................
                //.......................................................................................
               //rechercher l indexmin indice de la fr�quence dans available frequency qui a
               // une distance minimal
               //distance = abs(  paircost.first-paircost.second);
          //..............................................................
                //...................................................................................

        //DOMINANCE


                 //...................................................
                 //.....................................................
                // I . Retirer la non dominance pour chaque fr�quence
                // ....................................................
                //...................................................

                bool test = true; //je supose que la soluution est domiin�e et je vais tester si c est vrai
                int indexdominantf, NonDominantScore;
                indexdominantf = -1;
                vector < pair<int,int> > IndexesFreqsNonDominantes;
                 //(int,int) :: le premier enregistre l index de la fr�quence non dominante
                  //(int,int) :: le dexieme , combien de fois la fr�quence est non dominante
                IndexesFreqsNonDominantes.reserve(trx.validFrequencies->size());
                for( i = 0; i < trx.validFrequencies->size();i++)//la solution condidate est dans l indice i
                {
                  //dominance par rapport au premier joueur
                  NonDominantScore = 0 ;
                  //IndexesFreqsNonDominantes[i].first = i ;
                 // IndexesFreqsNonDominantes[i].second = 0;
                   for( j = 0; j < trx.validFrequencies->size();j++)
                   {
                       if (i!=j)
                       {
                            // je te
                            if (paircost[i].first <= paircost[j].first) // on teste la non dominance par rapport au premier objectif
                            {
                                if (paircost[i].second < paircost[j].second)
                                {
                                     NonDominantScore =   NonDominantScore    ;                                   ;
                                }
                                     IndexesFreqsNonDominantes.push_back({i,NonDominantScore});
                            }//
                            else
                            {
                                if (paircost[i].second <= paircost[j].second) // on teste la non dominance par rapport au deuci�me objectif
                                {
                                     if (paircost[i].first < paircost[j].first)
                                    {
                                        NonDominantScore =   NonDominantScore + 1 ;                                   ;
                                    }
                                         IndexesFreqsNonDominantes.push_back({i,NonDominantScore});
                                }
                            }
                            //sauvegarder le score
                            //IndexesFreqsNonDominantes[i].second = NonDominantScore;

                        }//i!=j
                    }//fin j

                }//fin i
                //...................................................
                 //.....................................................
                // II . Trier le tableau de la non dominance selon un ordre croissant
                // ....................................................
                //...................................................
               // sort(IndexesFreqsNonDominantes.begin(),IndexesFreqsNonDominantes.end(),my_cmp);
                //la
                        // copier les solution trouver dans un vecteur avec son cout d separation qui
                vector < pair < int, double> > NonDominanteCost;
                NonDominanteCost.reserve(IndexesFreqsNonDominantes.size());
                for(i = 0; i < IndexesFreqsNonDominantes.size(); i++ )
                {
                    NonDominanteCost.push_back({IndexesFreqsNonDominantes[i].first, paircost[IndexesFreqsNonDominantes[i].first].second });
                }
                // trier le tableau selon un ordre d�croisant du cout et retirer la premi�re valeur dans NonDominanteCost


                sort(NonDominanteCost.begin(),NonDominanteCost.end(),my_cmpInfDoublePair);
                indexmin = NonDominanteCost.front().first;



                //..............................................................
                //...................................................................................
                f=trx.validFrequencies->at(indexmin);//indice de la fr�quence ayant un cout minimal,

            }//taille >1
            else
            {
                if(taille==1)
                {
                    f=trx.validFrequencies->at(0);
                // cout<<" frequency choisit:lorsque la taille est 0"<<f<<endl;
                // cout<<"hii"<<endl;
                }
            }//taille == 1?!!
        }
        else//Availablefrequencies==empty()
        {
            cout<<" la liste des fr�quences valide est vide **"<<endl;
        }
















            //******************
            //cout<<" la liste des fr�quences disponibles est vide **"<<endl;
        }

        break;
    }

 //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ FRONt PARETO Inspir�e ~~~~~~~~~~~~~~~~~~~~~~
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 case 5://strategy 5 choisir la meilleur fr�quence en terme Front parteo
    {
          int i,indexmin,j,k;
       // Individual * tempsol =  new Individual();
        int tempfreq;
        //��������������������������������� copier la solution dans tempsol ����������������������
        //���������������������������������������������������������������������������������������
        //tempsol = solution;
        //tempsol->plan = new vector <int>(solution->plan->size());
        //tempsol->planCC = new vector <double>(solution->planCC->size());
        solution->PlanAffect = new vector< pair<int,int> > ();
        // tempsol->PIObj = solution->PIObj;
        // tempsol->PSObj = solution->PSObj;
        for(i=0;i<solution->plan->size();i++)
        {
            //tempsol->plan->at(i) = solution->plan->at(i);
            //tempsol->planCC->at(i) = solution->planCC->at(i);
           // tempsol->PIObj = solution->PIObj;
            //tempsol->PSObj = solution->PSObj;
            if(solution->plan->at(i)!=-1)//si la case dans le plan n'est pas vide on remplie le planAffect
            {
                solution->PlanAffect->push_back({i,solution->plan->at(i)});
            }
        }

        //����������������������������������������������������������
        //���������������������������������������������������������������
        //   tempsol->planCC=NULL;
        //LF comment: on traverse tte les fr�quence et on calcule le cout
        int victimFrequency,interfererFrequency;
        int victimTrx,interfererTrx;
        victimTrx = trx.trxID;

        int taille;
        //..........................................................
        //..........................................................
        //vecteur pour enregistrer le couple de cout  interference, separation � la fois
        vector < pair<double,double>  > paircost ;
        //----------------------
        if(trx.AvailableFrequencies->empty()==false)
        {
           taille =trx.AvailableFrequencies->size();

            vector<double> * veccost = new vector <double>(taille);
                 vector<double> * cost = new vector <double>(taille);
            if (taille>1)
            {
                //paralleliser les traitements
                //#pragma omp parallel for
                for(i=0 ;i < taille ; i++)//pour chaque fr�quence probable on evalue le cout
                {

                    victimFrequency =trx.AvailableFrequencies->at(i);
                    veccost->at(i)=0.0;
                    cost->at(i)=0.0;
                    solution->PlanAffect->push_back({trx.trxID,victimFrequency});
                    //on �value la solution avec le nouveau couple : {victimTrx,victimFrequency}
                   int victimTrx1 = trx.trxID; int victimFrequency1 = trx.AvailableFrequencies->at(i);
                    for(j=0;j< solution->PlanAffect->size();j++)
                    {

                        victimTrx = solution->PlanAffect->at(j).first;
                        victimFrequency = solution->PlanAffect->at(j).second;
                       interfererTrx = solution->PlanAffect->at(j).first;
                        interfererFrequency = solution->PlanAffect->at(j).second;
                        if ( interfererTrx != victimTrx1)
                        {
                           // calculer le cout d interference
                            veccost->at(i)  = veccost->at(i)  + afpProblem->computeChannelInterference(victimFrequency1 ,interfererFrequency, victimTrx1, interfererTrx)+
                            afpProblem->computeChannelInterference(interfererFrequency,victimFrequency1 ,interfererTrx, victimTrx1);
                            //cout de separation
                           if(afpProblem->trxs[victimTrx1].sectorID == afpProblem->trxs[interfererTrx].sectorID)
                            {
                                //on teste si la contraite de separation co-secteur est respect�!!
                                if (abs (interfererFrequency-victimFrequency1)<3 )//contrainte co secteur viol�e
                                {
                                    cost->at(i) = cost->at(i) + 1.0;
                                }
                            }// secteur different
                            else
                            {
                                if(afpProblem->trxs[victimTrx1].siteID  == afpProblem->trxs[interfererTrx].siteID)
                                {
                        //on teste si la contrainte de separation co-site est respect�e!!
                                    if (abs (interfererFrequency-victimFrequency1)< 2)//contrainte co secteur viol�e
                                    {
                                        cost->at(i) = cost->at(i) + 1.0;
                                    }
                                }//
                            }
                        }

                    }// for(j=0 ;j < taille ; j++)//pour chaque fr�quence probable on evalue le cout
                    //.............................................................................
                    //.............................................................................
                    // enregister les couts dans le vecteur
                  //  cout << veccost->at(i) << veccost->at(i) << endl;
                    veccost->at(i) = veccost->at(i) + solution->PIObj ;
                    cost->at(i) = cost->at(i) + solution->PSObj ;
                    paircost.push_back({veccost->at(i),cost->at(i)});
                    //...................................................................
                    solution->PlanAffect->pop_back();//on retire le couple probable apres evaluation de cout et l avoir enregistr� dans veccost
                    // cout<<"frequence ::" <<trx.AvailableFrequencies->at(i)<<", son sout veccost[i] ==="<< veccost->at(i)<<endl;
                } //fortrx.AvailableFrequencies


 //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
     //DOMINANCE
   //
                 //...................................................
                 //.....................................................
                // I . Retirer la non dominance pour chaque fr�quence
                // ....................................................
                //...................................................

                //je supose que la soluution est domiin�e et je vais tester si c est vrai

                    //+++++++++++++Laidi modifi� +++++++++++++++++++++++++++++++++++
      //je supose que la soluution est domiin�e et je vais tester si c est vrai
                int  NonDominantScore, DominantScore;

                vector < pair<int,int> > IndexesFreqsNonDominantes;
                int flag1, flag2, index;
                double interCost;
                 //(int,int) :: le premier enregistre l index de la fr�quence non dominante
                  //(int,int) :: le dexieme , combien de fois la fr�quence est non dominante
                IndexesFreqsNonDominantes.reserve(trx.AvailableFrequencies->size());

                for( i = 0; i < trx.AvailableFrequencies->size();i++)//la solution condidate est dans l indice i
                {

                  DominantScore = 0 ;// pour compter le nombre de solution qui domine la solution courante

                   for( j = 0; j < trx.AvailableFrequencies->size();j++)
                   {
                        //Laidi ---

                                /*
                               flag1 = 0;
                               flag2 = 0;
                               if (paircost[i].first >= paircost[j].first)
                                flag1++;

                               if (paircost[i].first > paircost[j].first)
                                flag2++;

                               if (paircost[i].second >= paircost[j].second)
                                flag1++;

                               if (paircost[i].second > paircost[j].second)
                                flag2++;


                          if (flag1 >= 2 && flag2>=1){ //pour tester la condition de dominance pour nos deux objectifs
          //array_domination_count[i] = array_domination_count[i] + 1; // lpour compter le nbr de solution qui domine la solution i
                              DominantScore= DominantScore+1; //pour la solution 'i'
                           }

                        */
                             /*if (paircost[i].first > paircost[j].first)
                                   {
                                      if (paircost[i].second >= paircost[j].second)
                                       DominantScore   = DominantScore +   1; //pour la solution 'i'
                                   }


                                    if (paircost[i].second > paircost[j].second)
                                        {
                                            if(paircost[i].first >= paircost[j].first)
                                            DominantScore   = DominantScore +   1; //pour la solution 'i'
                                        }*/
                                        if(i!=j)
                                       {


                         if (!((paircost[i].first <= paircost[j].first) && (paircost[i].second <= paircost[j].second)))
                             DominantScore   = DominantScore +   1;
                                       }

                 }

                     /* if (DominantScore == 0)
                  IndexesFreqsNonDominantes.push_back({i,paircost[i].second}); // contient l'indice de la fr�quence frqq ainsi que le cout d'interf�rences
                */
                //j ins�re pour chque solution f son score
                 IndexesFreqsNonDominantes.push_back({i,DominantScore});
                }//fin i
               // cout << " la taille des frqs non dominee PI == " << IndexesFreqsNonDominantes.size() << endl ;
                //+++++++++++++++++++++++++++++++++++++++Afficher paircost

           //++++++++++++++++++++++++++++++++++++++++++++++++++++++++

                //...................................................
                 //.....................................................
                // II . Trier le tableau de la non dominance selon un ordre croissant
                // ....................................................
                //...................................................
              //  sort(IndexesFreqsNonDominantes.begin(),IndexesFreqsNonDominantes.end(),my_cmp);
              //  cout << "  IndexesFreqsNonDominantes.size() ****"<< IndexesFreqsNonDominantes.size() << endl;


                // copier les solution trouver dans un vecteur avec son cout d interferqunce qui
               /* vector < pair < int, double> > NonDominanteCost;//contient l indice des valeur non domin�e et le cout
                NonDominanteCost.reserve(IndexesFreqsNonDominantes.size());
                for(i = 0; i < IndexesFreqsNonDominantes.size(); i++ )
                {
                    NonDominanteCost.push_back({IndexesFreqsNonDominantes[i].first, paircost[IndexesFreqsNonDominantes[i].first].first });
                }*/
                // trier le tableau selon un ordre d�croisant du cout et retirer la premi�re valeur
              // cout << " ���������IndexesFreqsNonDominantes.size() " << IndexesFreqsNonDominantes.size() <<endl;

              if (IndexesFreqsNonDominantes.size()!= 0)
              {
                  //cout << " la taille du vect solutions non dom PS == " << IndexesFreqsNonDominantes.size()<< endl;
                 // sort(IndexesFreqsNonDominantes.begin(),IndexesFreqsNonDominantes.end(),my_cmpInfDoublePair);//trier selon un ordre croissant de cout
                sort(IndexesFreqsNonDominantes.begin(),IndexesFreqsNonDominantes.end(),my_cmpInf);
                //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                //~~~~~~~~~~~~~~~~~~~~~~~~~~~si plusieurs fr�queences  non domlinates ont le meme cout on choisit
                // al�atoirement une
                //---------------------------------------------------
                i = 0;     k = 0 ;
                for(i = 0 ; i < IndexesFreqsNonDominantes.size(); i++)
                {
                    //double val = IndexesFreqsNonDominantes.at(i).second;
                    int val = IndexesFreqsNonDominantes.at(i).second;
                    //pair<int,double> pnextval;
                    pair<int,int> pnextval;
                    if((i+1) < IndexesFreqsNonDominantes.size())
                    {
                        pnextval = IndexesFreqsNonDominantes.at(i+1);
                        //double nextval = pnextval.second;
                        int nextval = pnextval.second;
                        // on copie les valeurs egales dans un tableau
                        //cout<< "hiiii here " << endl;
                        if( val == nextval )
                        {
                            k = k +1 ;//k contient le nombre de valeur �gale
                            // cout<< "hiiii here " << endl;

                        }
                        else
                        {
                            i = IndexesFreqsNonDominantes.size();
                        }
                    }
                }
                //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                int indice ;
                indice = rand() % (k+1);// coisir une parmi les "n" premier
              //  cout << " k �����������" << k << endl;
                indexmin = IndexesFreqsNonDominantes.at(indice).first;// r�cup�ration de l'indice de la fr�quence
              }
               else// il n y a aucune valeur dans le front pareto
                {
                        cout << " taille 0000000000000000 " << endl;
                         vecmin(cost, indexmin);//indexmin:indice de la fr�quencence qui a la valeur minimale


            }


    //............................End dominance ..................................
    //..............................................................
    //................................................................................
    f=trx.AvailableFrequencies->at(indexmin);//indice de la fr�quence recherch�
     solution->PIObj = veccost->at(indexmin);
      solution->PSObj = cost->at(indexmin);
      //delete(tempsol->PlanAffect);
       vector < pair<double,double>  >().swap(paircost) ;
    vector < pair<int,int> > ().swap(IndexesFreqsNonDominantes);
    delete(veccost);
    delete(cost);
    //delete(tempsol->PlanAffect);
    delete(solution->PlanAffect);
    //--------------------- dominance available
    }//if (taille >1)
    else
    {
       if(taille==1) // la taille  == 1; je n ai qu'un choix
        {
            f=trx.AvailableFrequencies->at(0);
            // cout<<" frequency choisit:lorsque la taille est 0"<<f<<endl;
            // cout<<"hii"<<endl;
            delete(solution->PlanAffect);
        }
    }//taille :.!=1
 }// Availablefrequencies is empty()
else//Availablefrequencies==empty() // aucune fr�quence n'est diponible j'utilise les fr�quence valides
        {// on choisit la meilleur fr�quence VALID

            //****************#################################""
        //----------------------
        if(trx.validFrequencies->empty()==false)
        {
            taille =trx.validFrequencies->size();
            vector<double> * veccost = new vector <double>(taille);
                vector<double> * cost = new vector <double>(taille);
            if (taille>1)
            {
                for(i=0 ;i < taille ; i++)//pour chaque fr�quence probable on evalue le cout
                {
                    victimFrequency =trx.validFrequencies->at(i);
                     veccost->at(i)=0.0;
                    cost->at(i)=0.0;
                    solution->PlanAffect->push_back({trx.trxID,victimFrequency});
                    //on �value la solution avec le nouveau couple : {victimTrx,victimFrequency}
                   int victimTrx1 = trx.trxID; int victimFrequency1 = trx.AvailableFrequencies->at(i);
                    for(j=0;j< solution->PlanAffect->size();j++)
                    {

                        victimTrx = solution->PlanAffect->at(j).first;
                        victimFrequency = solution->PlanAffect->at(j).second;
                       interfererTrx = solution->PlanAffect->at(j).first;
                        interfererFrequency = solution->PlanAffect->at(j).second;
                        if ( interfererTrx != victimTrx1)
                        {
                           // calculer le cout d interference
                            veccost->at(i)  = veccost->at(i)  + afpProblem->computeChannelInterference(victimFrequency1 ,interfererFrequency, victimTrx1, interfererTrx)+
                            afpProblem->computeChannelInterference(interfererFrequency,victimFrequency1 ,interfererTrx, victimTrx1);
                            //cout de separation
                           if(afpProblem->trxs[victimTrx1].sectorID == afpProblem->trxs[interfererTrx].sectorID)
                            {
                                //on teste si la contraite de separation co-secteur est respect�!!
                                if (abs (interfererFrequency-victimFrequency1)<3 )//contrainte co secteur viol�e
                                {
                                    cost->at(i) = cost->at(i) + 1.0;
                                }
                            }// secteur different
                            else
                            {
                                if(afpProblem->trxs[victimTrx1].siteID  == afpProblem->trxs[interfererTrx].siteID)
                                {
                        //on teste si la contrainte de separation co-site est respect�e!!
                                    if (abs (interfererFrequency-victimFrequency1)< 2)//contrainte co secteur viol�e
                                    {
                                        cost->at(i) = cost->at(i) + 1.0;
                                    }
                                }//
                            }
                        }

                    }// for(j=0 ;j < taille ; j++)//pour chaque fr�quence probable on evalue le cout
                    //.............................................................................
                    //.............................................................................
                    // enregister les couts dans le vecteur
                  //  cout << veccost->at(i) << veccost->at(i) << endl;
                    veccost->at(i) = veccost->at(i) + solution->PIObj ;
                    cost->at(i) = cost->at(i) + solution->PSObj ;
                    paircost.push_back({veccost->at(i),cost->at(i)});
                    //...................................................................
                    solution->PlanAffect->pop_back();//on retire le couple probable apres evaluation de cout et l avoir enregistr� dans veccost
                    // cout<<"frequence ::" <<trx.AvailableFrequencies->at(i)<<", son sout veccost[i] ==="<< veccost->at(i)<<endl;
                } //fortrx.Av
          //..............................................................
                //...................................................................................

        //DOMINANCE


                 //...................................................
                 //.....................................................
                // I . Retirer la non dominance pour chaque fr�quence
                // ....................................................
                //...................................................

                 int  DominantScore;

                vector < pair<int,int> > IndexesFreqsNonDominantes;
                 //(int,int) :: le premier enregistre l index de la fr�quence non dominante
                  //(int,int) :: le dexieme , combien de fois la fr�quence est non dominante
                IndexesFreqsNonDominantes.reserve(trx.validFrequencies->size());
        //+++++++++++++Laidi modifi� +++++++++++++++++++++++++++++++++++
          for( i = 0; i < trx.AvailableFrequencies->size();i++)//la solution condidate est dans l indice i
                {

                  DominantScore = 0 ;// pour compter le nombre de solution qui domine la solution courante

                  for( j = i+1; j < trx.AvailableFrequencies->size() ;j++)
                   {
                       if (i!=j)
                       {

                           if (paircost[i].first > paircost[j].first) // on teste la dominance par rapport au premier objectif
                            {
                                // on ne peut pas juger on test par rapport au deuxime obj
                                if (paircost[i].second > paircost[j].second)
                                         {

                                                  //on est sur qu elle est dominante
                                                DominantScore    =   DominantScore+1 ;


                                         }
                                         else
                                         {
                                             if(paircost[i].first >= paircost[j].first)
                                              {
                                                    DominantScore    =   DominantScore+1 ;
                                              }
                                         }

                            }
                            else
                            {
                                if (paircost[i].second >= paircost[j].second)
                                    {
                                        DominantScore    =   DominantScore+1 ;
                                    }

                            }


                        }//i!=j
                    }//fin j

						if (DominantScore==0)// pour s'assurer que la solution "i" est non dominée
                      {
                        IndexesFreqsNonDominantes.push_back({i,paircost[i].first});// on insert l'index de la solution et son cout d'interférences
                      }
                       // cout << "la solution " << i << " est dominee par  " << DominantScore << " autres solutions" << endl;
                }//fin i

            //cout <<"IndexesFreqsNonDominantes.size()PIII  "<< IndexesFreqsNonDominantes.size() <<endl;*/
                //----------------------------------------------------------------------
                 //+++++++++++++ sol par sol +++++++++++++++++++++++++++++++++++
                 //++++++++++++++++++ tout les sol
                  int  nondominancescore;
                  //cout << "trx.AvailableFrequencies->size()++++ "<< trx.AvailableFrequencies->size() <<endl;

                      for( i = 0; i < trx.validFrequencies->size();i++)//la solution condidate est dans l indice i
                {

                  nondominancescore = 0 ;// pour compter le nombre de solution qui domine la solution courante

                   for( j = 0; j < trx.AvailableFrequencies->size() ;j++)
                   {

                       if (i!=j)
                       {

                                   if (paircost[i].first <= paircost[j].first)  // on teste la dominance par rapport au deuciÃ¨me objectif
                                    {
                                          if (paircost[i].second < paircost[j].second)

                                        {
                                            IndexesFreqsNonDominantes.push_back({i,paircost[i].first});

                                            nondominancescore = nondominancescore + 1;
                                            }
                                        }


                                    //--- j insere le deuxi�me obj
                                  /* else
                                    {
                                         if (paircost[i].second <= paircost[j].second) // teste la dominance par rapport au deuciÃ¨me objectif
                                        {
                                                if (paircost[i].first < paircost[j].first) // on
                                                {
                                                    IndexesFreqsNonDominantes.push_back({i,paircost[i].first});
                                            //au deuxieme obj

                                                nondominancescore = nondominancescore+1;
                                                }
                                            //}
                                        }
                                    }*/

                       }//i!=j
                   }//fin j
                   /*  if (nondominancescore > (trx.AvailableFrequencies->size() - 2 ))
                  IndexesFreqsNonDominantes.push_back({i,paircost[i].first});*/

              }//fin i
            // cout <<"IndexesFreqsNonDominantes.size()PIII  "<< IndexesFreqsNonDominantes.size() <<endl;



                //...................................................
                 //.....................................................
                // II . Trier le tableau de la non dominance selon un ordre croissant si la liste n est pas vide
                // ....................................................
                //...................................................
              //  sort(IndexesFreqsNonDominantes.begin(),IndexesFreqsNonDominantes.end(),my_cmp);
             // cout << "  IndexesFreqsNonDominantes.size() ****"<< IndexesFreqsNonDominantes.size() << endl;


                // copier les solution trouver dans un vecteur avec son cout d interferqunce qui
                if (IndexesFreqsNonDominantes.size()!= 0 )
                {
                    /*vector < pair < int, double> > NonDominanteCost;
                    NonDominanteCost.reserve(IndexesFreqsNonDominantes.size());
                    for(i = 0; i < IndexesFreqsNonDominantes.size(); i++ )
                    {
                        NonDominanteCost.push_back({IndexesFreqsNonDominantes[i].first, paircost[IndexesFreqsNonDominantes[i].first].first });
                    }*/
                // trier le tableau selon un ordre d�croisant du cout et retirer la premi�re valeur
                    sort(IndexesFreqsNonDominantes.begin(),IndexesFreqsNonDominantes.end(),my_cmpInfDoublePair);
                   // indexmin = IndexesFreqsNonDominantes.front().first;
                   //si des valeur de cout �gale on choisit al�atoirement parmi ces valeur
                   //+++++++++++++++++++++++++++++++++++++++++++
                   k=0;
                   for(i = 0 ; i < IndexesFreqsNonDominantes.size(); i++)
                    {
                        double val = IndexesFreqsNonDominantes.at(i).second;
                        pair<int,double> pnextval;
                        if((i+1) < IndexesFreqsNonDominantes.size())
                        {
                            pnextval = IndexesFreqsNonDominantes.at(i+1);
                            double nextval = pnextval.second;
                            // on copie les valeurs egales dans un tableau
                            //cout<< "hiiii here " << endl;
                            if( val == nextval )
                            {
                                k = k +1 ;//k contient le nombre de valeur �gale
                                // cout<< "hiiii here " << endl;
                            }
                            else
                            {
                                i = IndexesFreqsNonDominantes.size();
                            }
                        }
                    }
    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                    int indexf = rand() % (k+1);
                    indexmin = IndexesFreqsNonDominantes.at(indexf).first;

                }
                else
                {
                     vecmin(veccost, indexmin);//indexmin:indice de la fr�quencence qui a la valeur minimale
                }

                //................................................................................

//--------------------- dominance available
                //..............................................................
                //...................................................................................

    //vider la m�moire--vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
    vector < pair<double,double>  >().swap(paircost) ;
    delete(veccost);
    delete(solution->PlanAffect);
                //..............................................................
                //...................................................................................
                f=trx.validFrequencies->at(indexmin);//indice de la fr�quence ayant un cout minimal,

    //+++++++++++++++++++++++++++++++

            }//taille >1
            else
            {
                if(taille==1)
                {
                    f=trx.validFrequencies->at(0);
                // cout<<" frequency choisit:lorsque la taille est 0"<<f<<endl;
                // cout<<"hii"<<endl;
                }
            }//taille == 1?!!
        }
        else//Availablefrequencies==empty()
        {
            cout<<" la liste des fr�quences valide est vide **"<<endl;
        }
















            //******************
            //cout<<" la liste des fr�quences disponibles est vide **"<<endl;
        }
    break;
    }//case 5  : best frequency Front pareto
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ FRONt PARETO PUUUUUUUUUUUURE ~~~~~~~~~~~~~~~~~~~~~~
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   case  550://strategy 5 choisir la meilleur fr�quence en terme Front parteo
    {
          int i,indexmin,j,k;
       // Individual * tempsol =  new Individual();
        int tempfreq;
        //��������������������������������� copier la solution dans tempsol ����������������������
        //���������������������������������������������������������������������������������������
        //tempsol = solution;
        //tempsol->plan = new vector <int>(solution->plan->size());
        //tempsol->planCC = new vector <double>(solution->planCC->size());
        solution->PlanAffect = new vector< pair<int,int> > ();
        // tempsol->PIObj = solution->PIObj;
        // tempsol->PSObj = solution->PSObj;
        for(i=0;i<solution->plan->size();i++)
        {
            //tempsol->plan->at(i) = solution->plan->at(i);
            //tempsol->planCC->at(i) = solution->planCC->at(i);
           // tempsol->PIObj = solution->PIObj;
            //tempsol->PSObj = solution->PSObj;
            if(solution->plan->at(i)!=-1)//si la case dans le plan n'est pas vide on remplie le planAffect
            {
                solution->PlanAffect->push_back({i,solution->plan->at(i)});
            }
        }

        //����������������������������������������������������������
        //���������������������������������������������������������������
        //   tempsol->planCC=NULL;
        //LF comment: on traverse tte les fr�quence et on calcule le cout
        int victimFrequency,interfererFrequency;
        int victimTrx,interfererTrx;
        victimTrx = trx.trxID;

        int taille;
        //..........................................................
        //..........................................................
        //vecteur pour enregistrer le couple de cout  interference, separation � la fois
        vector < pair<double,double>  > paircost ;
        //----------------------
        if(trx.AvailableFrequencies->empty()==false)
        {
           taille =trx.AvailableFrequencies->size();

            vector<double> * veccost = new vector <double>(taille);
                 vector<double> * cost = new vector <double>(taille);

            if (taille>1)
            {
                   //paralleliser les tratements
                    //#pragma omp parallel for
                for(i=0 ;i < taille ; i++)//pour chaque fr�quence probable on evalue le cout
                {

                    victimFrequency =trx.AvailableFrequencies->at(i);
                    veccost->at(i)=0.0;
                    cost->at(i)=0.0;
                    solution->PlanAffect->push_back({trx.trxID,victimFrequency});
                    //on �value la solution avec le nouveau couple : {victimTrx,victimFrequency}
                   int victimTrx1 = trx.trxID; int victimFrequency1 = trx.AvailableFrequencies->at(i);
                    for(j=0;j< solution->PlanAffect->size();j++)
                    {

                        victimTrx = solution->PlanAffect->at(j).first;
                        victimFrequency = solution->PlanAffect->at(j).second;
                       interfererTrx = solution->PlanAffect->at(j).first;
                        interfererFrequency = solution->PlanAffect->at(j).second;
                        if ( interfererTrx != victimTrx1)
                        {
                           // calculer le cout d interference
                            veccost->at(i)  = veccost->at(i)  + afpProblem->computeChannelInterference(victimFrequency1 ,interfererFrequency, victimTrx1, interfererTrx)+
                            afpProblem->computeChannelInterference(interfererFrequency,victimFrequency1 ,interfererTrx, victimTrx1);
                            //cout de separation
                           if(afpProblem->trxs[victimTrx1].sectorID == afpProblem->trxs[interfererTrx].sectorID)
                            {
                                //on teste si la contraite de separation co-secteur est respect�!!
                                if (abs (interfererFrequency-victimFrequency1)<3 )//contrainte co secteur viol�e
                                {
                                    cost->at(i) = cost->at(i) + 1.0;
                                }
                            }// secteur different
                            else
                            {
                                if(afpProblem->trxs[victimTrx1].siteID  == afpProblem->trxs[interfererTrx].siteID)
                                {
                        //on teste si la contrainte de separation co-site est respect�e!!
                                    if (abs (interfererFrequency-victimFrequency1)< 2)//contrainte co secteur viol�e
                                    {
                                        cost->at(i) = cost->at(i) + 1.0;
                                    }
                                }//
                            }
                        }

                    }// for(j=0 ;j < taille ; j++)//pour chaque fr�quence probable on evalue le cout
                    //.............................................................................
                    //.............................................................................
                    // enregister les couts dans le vecteur
                  //  cout << veccost->at(i) << veccost->at(i) << endl;
                    veccost->at(i) = veccost->at(i) + solution->PIObj ;
                    cost->at(i) = cost->at(i) + solution->PSObj ;
                    paircost.push_back({veccost->at(i),cost->at(i)});
                    //...................................................................
                    solution->PlanAffect->pop_back();//on retire le couple probable apres evaluation de cout et l avoir enregistr� dans veccost
                    // cout<<"frequence ::" <<trx.AvailableFrequencies->at(i)<<", son sout veccost[i] ==="<< veccost->at(i)<<endl;
                } //fortrx.AvailableFrequencies


 //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
     //DOMINANCE
   //
                 //...................................................
                 //.....................................................
                // I . Retirer la non dominance pour chaque fr�quence
                // ....................................................
                //...................................................

                //je supose que la soluution est domiin�e et je vais tester si c est vrai

                    //+++++++++++++Laidi modifi� +++++++++++++++++++++++++++++++++++
      //je supose que la soluution est domiin�e et je vais tester si c est vrai
            int rank;
  int counter;
  int dominantScore;
  int temp = 0;
  rank = 1;
  vector < pair<int,double> > IndexesFreqsNonDominantes;
    IndexesFreqsNonDominantes.reserve(paircost.size());
    int taille=paircost.size();
    int array_rank[paircost.size()];
    counter =paircost.size();


    for (int i=0; i<paircost.size(); i++)
    {
      dominantScore=0;

	  for (int j=0; j<paircost.size(); j++)
	  {
        if (i!=j)
        {

            if ((paircost[i].first>=paircost[j].first && paircost[i].second>paircost[j].second) || (paircost[i].second>=paircost[j].second && paircost[i].first>paircost[j].first))
            {
          //  array_domination_count[i] = array_domination_count[i] + 1;
            dominantScore=dominantScore+1;// on a trouv� j qui domine i ;
            }
        }//i!=j
       } //fin j
		if (dominantScore==0)
        {
          // indices.push_back(i); // pour sauvgarder les indices des solution non dominées dans la nouvelle population
           IndexesFreqsNonDominantes.push_back({i,paircost[i].second});
        }
	}//fin i



              if (IndexesFreqsNonDominantes.size()!= 0)
              {
                  //cout << " la taille du vect solutions non dom PS == " << IndexesFreqsNonDominantes.size()<< endl;
                 // sort(IndexesFreqsNonDominantes.begin(),IndexesFreqsNonDominantes.end(),my_cmpInfDoublePair);//trier selon un ordre croissant de cout
                sort(IndexesFreqsNonDominantes.begin(),IndexesFreqsNonDominantes.end(),my_cmpInfDoublePair);
                //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                //~~~~~~~~~~~~~~~~~~~~~~~~~~~si plusieurs fr�queences  non domlinates ont le meme cout on choisit
                // al�atoirement une
                //---------------------------------------------------
                i = 0;     k = 0 ;
                //------------------------------------
                for(i = 0 ; i < IndexesFreqsNonDominantes.size(); i++)
                {
                    //double val = IndexesFreqsNonDominantes.at(i).second;
                    double val = IndexesFreqsNonDominantes.at(i).second;
                    //pair<int,double> pnextval;
                    pair<int,double> pnextval;
                    if((i+1) < IndexesFreqsNonDominantes.size())
                    {
                        pnextval = IndexesFreqsNonDominantes.at(i+1);
                        //double nextval = pnextval.second;
                        double nextval = pnextval.second;
                        // on copie les valeurs egales dans un tableau
                        //cout<< "hiiii here " << endl;
                        if( val == nextval )
                        {
                            k = k +1 ;//k contient le nombre de valeur �gale
                        }
                        else
                        {
                            i = IndexesFreqsNonDominantes.size();
                        }
                    }
                }
                int indice ;
                indice = rand() % (k+1);// coisir une parmi les "n" premier
                indexmin = IndexesFreqsNonDominantes.at(indice).first;// r�cup�ration de l'indice de la fr�quence
               // cout << "k ������������������" << k << endl;
              }
               else// il n y a aucune valeur dans le front pareto
               {
                 //cout << " taille 0000000000000000 " << endl;
                 // vecmin(cost, indexmin);//indexmin:indice de la fr�quencence qui a la valeur minimale
                 StrategyFreq = 2;//3 : ecart, 6: hv , 2 : minimum cost
                 PSChooseFrequency(instance,StrategyFreq,trx,f,solution,afpProblem);
                 return;

               }
    //............................End dominance ......................................
    //................................................................................
    //................................................................................
    f=trx.AvailableFrequencies->at(indexmin);//indice de la fr�quence recherch�
    solution->PIObj = veccost->at(indexmin);
    solution->PSObj = cost->at(indexmin);
    solution->planCC->at(trx.trxID).first = solution->PIObj;
    solution->planCC->at(trx.trxID).second = solution->PSObj;
    //delete(tempsol->PlanAffect);
    vector < pair<double,double> > ().swap(paircost) ;
    vector < pair<int,double> > ().swap(IndexesFreqsNonDominantes);
    delete(veccost);
    delete(cost);
    //delete(tempsol->PlanAffect);
    delete(solution->PlanAffect);
    //--------------------- dominance available
    }//if (taille >1)
    else
    {
       if(taille==1) // la taille  == 1; je n ai qu'un choix
        {
            f=trx.AvailableFrequencies->at(0);
            // cout<<" frequency choisit:lorsque la taille est 0"<<f<<endl;
            // cout<<"hii"<<endl;
            delete(solution->PlanAffect);
        }
    }//taille :.!=1
 }// Availablefrequencies is empty()
else//Availablefrequencies==empty() // aucune fr�quence n'est diponible j'utilise les fr�quence valides
        {// on choisit la meilleur fr�quence VALID

            //****************#################################""
        //----------------------
        if(trx.validFrequencies->empty()==false)
        {
            taille =trx.validFrequencies->size();
            vector<double> * veccost = new vector <double>(taille);
                vector<double> * cost = new vector <double>(taille);
            if (taille>1)
            {
                for(i=0 ;i < taille ; i++)//pour chaque fr�quence probable on evalue le cout
                {
                    victimFrequency =trx.validFrequencies->at(i);
                     veccost->at(i)=0.0;
                    cost->at(i)=0.0;
                    solution->PlanAffect->push_back({trx.trxID,victimFrequency});
                    //on �value la solution avec le nouveau couple : {victimTrx,victimFrequency}
                   int victimTrx1 = trx.trxID; int victimFrequency1 = trx.AvailableFrequencies->at(i);
                    for(j=0;j< solution->PlanAffect->size();j++)
                    {

                        victimTrx = solution->PlanAffect->at(j).first;
                        victimFrequency = solution->PlanAffect->at(j).second;
                       interfererTrx = solution->PlanAffect->at(j).first;
                        interfererFrequency = solution->PlanAffect->at(j).second;
                        if ( interfererTrx != victimTrx1)
                        {
                           // calculer le cout d interference
                            veccost->at(i)  = veccost->at(i)  + afpProblem->computeChannelInterference(victimFrequency1 ,interfererFrequency, victimTrx1, interfererTrx)+
                            afpProblem->computeChannelInterference(interfererFrequency,victimFrequency1 ,interfererTrx, victimTrx1);
                            //cout de separation
                           if(afpProblem->trxs[victimTrx1].sectorID == afpProblem->trxs[interfererTrx].sectorID)
                            {
                                //on teste si la contraite de separation co-secteur est respect�!!
                                if (abs (interfererFrequency-victimFrequency1)<3 )//contrainte co secteur viol�e
                                {
                                    cost->at(i) = cost->at(i) + 1.0;
                                }
                            }// secteur different
                            else
                            {
                                if(afpProblem->trxs[victimTrx1].siteID  == afpProblem->trxs[interfererTrx].siteID)
                                {
                        //on teste si la contrainte de separation co-site est respect�e!!
                                    if (abs (interfererFrequency-victimFrequency1)< 2)//contrainte co secteur viol�e
                                    {
                                        cost->at(i) = cost->at(i) + 1.0;
                                    }
                                }//
                            }
                        }

                    }// for(j=0 ;j < taille ; j++)//pour chaque fr�quence probable on evalue le cout
                    //.............................................................................
                    //.............................................................................
                    // enregister les couts dans le vecteur
                  //  cout << veccost->at(i) << veccost->at(i) << endl;
                    veccost->at(i) = veccost->at(i) + solution->PIObj ;
                    cost->at(i) = cost->at(i) + solution->PSObj ;
                    paircost.push_back({veccost->at(i),cost->at(i)});
                    //...................................................................
                    solution->PlanAffect->pop_back();//on retire le couple probable apres evaluation de cout et l avoir enregistr� dans veccost
                    // cout<<"frequence ::" <<trx.AvailableFrequencies->at(i)<<", son sout veccost[i] ==="<< veccost->at(i)<<endl;
                } //fortrx.Av
          //..............................................................
                //...................................................................................

        //DOMINANCE


                 //...................................................
                 //.....................................................
                // I . Retirer la non dominance pour chaque fr�quence
                // ....................................................
                //...................................................

                 int  DominantScore;

                vector < pair<int,int> > IndexesFreqsNonDominantes;
                 //(int,int) :: le premier enregistre l index de la fr�quence non dominante
                  //(int,int) :: le dexieme , combien de fois la fr�quence est non dominante
                IndexesFreqsNonDominantes.reserve(trx.validFrequencies->size());
        //+++++++++++++Laidi modifi� +++++++++++++++++++++++++++++++++++
          for( i = 0; i < trx.AvailableFrequencies->size();i++)//la solution condidate est dans l indice i
                {

                  DominantScore = 0 ;// pour compter le nombre de solution qui domine la solution courante

                  for( j = i+1; j < trx.AvailableFrequencies->size() ;j++)
                   {
                       if (i!=j)
                       {

                           if (paircost[i].first > paircost[j].first) // on teste la dominance par rapport au premier objectif
                            {
                                // on ne peut pas juger on test par rapport au deuxime obj
                                if (paircost[i].second > paircost[j].second)
                                         {

                                                  //on est sur qu elle est dominante
                                                DominantScore    =   DominantScore+1 ;


                                         }
                                         else
                                         {
                                             if(paircost[i].first >= paircost[j].first)
                                              {
                                                    DominantScore    =   DominantScore+1 ;
                                              }
                                         }

                            }
                            else
                            {
                                if (paircost[i].second >= paircost[j].second)
                                    {
                                        DominantScore    =   DominantScore+1 ;
                                    }

                            }


                        }//i!=j
                    }//fin j

						if (DominantScore==0)// pour s'assurer que la solution "i" est non dominée
                      {
                        IndexesFreqsNonDominantes.push_back({i,paircost[i].first});// on insert l'index de la solution et son cout d'interférences
                      }
                       // cout << "la solution " << i << " est dominee par  " << DominantScore << " autres solutions" << endl;
                }//fin i

            //cout <<"IndexesFreqsNonDominantes.size()PIII  "<< IndexesFreqsNonDominantes.size() <<endl;*/
                //----------------------------------------------------------------------
                 //+++++++++++++ sol par sol +++++++++++++++++++++++++++++++++++
                 //++++++++++++++++++ tout les sol
                  int  nondominancescore;
                  //cout << "trx.AvailableFrequencies->size()++++ "<< trx.AvailableFrequencies->size() <<endl;

                      for( i = 0; i < trx.validFrequencies->size();i++)//la solution condidate est dans l indice i
                {

                  nondominancescore = 0 ;// pour compter le nombre de solution qui domine la solution courante

                   for( j = 0; j < trx.AvailableFrequencies->size() ;j++)
                   {

                       if (i!=j)
                       {

                                   if (paircost[i].first <= paircost[j].first)  // on teste la dominance par rapport au deuciÃ¨me objectif
                                    {
                                          if (paircost[i].second < paircost[j].second)

                                        {
                                            IndexesFreqsNonDominantes.push_back({i,paircost[i].first});

                                            nondominancescore = nondominancescore + 1;
                                            }
                                        }


                                    //--- j insere le deuxi�me obj
                                  /* else
                                    {
                                         if (paircost[i].second <= paircost[j].second) // teste la dominance par rapport au deuciÃ¨me objectif
                                        {
                                                if (paircost[i].first < paircost[j].first) // on
                                                {
                                                    IndexesFreqsNonDominantes.push_back({i,paircost[i].first});
                                            //au deuxieme obj

                                                nondominancescore = nondominancescore+1;
                                                }
                                            //}
                                        }
                                    }*/

                       }//i!=j
                   }//fin j
                   /*  if (nondominancescore > (trx.AvailableFrequencies->size() - 2 ))
                  IndexesFreqsNonDominantes.push_back({i,paircost[i].first});*/

              }//fin i
            // cout <<"IndexesFreqsNonDominantes.size()PIII  "<< IndexesFreqsNonDominantes.size() <<endl;



                //...................................................
                 //.....................................................
                // II . Trier le tableau de la non dominance selon un ordre croissant si la liste n est pas vide
                // ....................................................
                //...................................................
              //  sort(IndexesFreqsNonDominantes.begin(),IndexesFreqsNonDominantes.end(),my_cmp);
             // cout << "  IndexesFreqsNonDominantes.size() ****"<< IndexesFreqsNonDominantes.size() << endl;


                // copier les solution trouver dans un vecteur avec son cout d interferqunce qui
                if (IndexesFreqsNonDominantes.size()!= 0 )
                {
                    /*vector < pair < int, double> > NonDominanteCost;
                    NonDominanteCost.reserve(IndexesFreqsNonDominantes.size());
                    for(i = 0; i < IndexesFreqsNonDominantes.size(); i++ )
                    {
                        NonDominanteCost.push_back({IndexesFreqsNonDominantes[i].first, paircost[IndexesFreqsNonDominantes[i].first].first });
                    }*/
                // trier le tableau selon un ordre d�croisant du cout et retirer la premi�re valeur
                    sort(IndexesFreqsNonDominantes.begin(),IndexesFreqsNonDominantes.end(),my_cmpInfDoublePair);
                   // indexmin = IndexesFreqsNonDominantes.front().first;
                   //si des valeur de cout �gale on choisit al�atoirement parmi ces valeur
                   //+++++++++++++++++++++++++++++++++++++++++++
                   k=0;
                   for(i = 0 ; i < IndexesFreqsNonDominantes.size(); i++)
                    {
                        double val = IndexesFreqsNonDominantes.at(i).second;
                        pair<int,double> pnextval;
                        if((i+1) < IndexesFreqsNonDominantes.size())
                        {
                            pnextval = IndexesFreqsNonDominantes.at(i+1);
                            double nextval = pnextval.second;
                            // on copie les valeurs egales dans un tableau
                            //cout<< "hiiii here " << endl;
                            if( val == nextval )
                            {
                                k = k +1 ;//k contient le nombre de valeur �gale
                                // cout<< "hiiii here " << endl;
                            }
                            else
                            {
                                i = IndexesFreqsNonDominantes.size();
                            }
                        }
                    }
    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                    int indexf = rand() % (k+1);
                    indexmin = IndexesFreqsNonDominantes.at(indexf).first;

                }
                else
                {
                     vecmin(veccost, indexmin);//indexmin:indice de la fr�quencence qui a la valeur minimale
                }

                //................................................................................

//--------------------- dominance available
                //..............................................................
                //...................................................................................

    //vider la m�moire--vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
    vector < pair<double,double>  >().swap(paircost) ;
    delete(veccost);
    delete(solution->PlanAffect);
                //..............................................................
                //...................................................................................
                f=trx.validFrequencies->at(indexmin);//indice de la fr�quence ayant un cout minimal,

    //+++++++++++++++++++++++++++++++

            }//taille >1
            else
            {
                if(taille==1)
                {
                    f=trx.validFrequencies->at(0);
                // cout<<" frequency choisit:lorsque la taille est 0"<<f<<endl;
                // cout<<"hii"<<endl;
                }
            }//taille == 1?!!
        }
        else//Availablefrequencies==empty()
        {
            cout<<" la liste des fr�quences valide est vide **"<<endl;
        }
















            //******************
            //cout<<" la liste des fr�quences disponibles est vide **"<<endl;
        }
    break;
    }//case 55  : best frequency Front pareto Laidi
    //---------------------------------------------------------------
     //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ FRONt PARETO Pure~~~~~~~~~~~~~~~~~~~~~~

       //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ FRONt PARETO PUUUUUUUUUUUURE Minimum ecart ~~~~~~~~~~~~~~~~~~~~~~
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   case  551://strategy 5 choisir la meilleur fr�quence en terme Front parteo
    {
          int i,indexmin,j,k;
       // Individual * tempsol =  new Individual();
        int tempfreq;
        //��������������������������������� copier la solution dans tempsol ����������������������
        //���������������������������������������������������������������������������������������
        //tempsol = solution;
        //tempsol->plan = new vector <int>(solution->plan->size());
        //tempsol->planCC = new vector <double>(solution->planCC->size());
        solution->PlanAffect = new vector< pair<int,int> > ();
        // tempsol->PIObj = solution->PIObj;
        // tempsol->PSObj = solution->PSObj;
        for(i=0;i<solution->plan->size();i++)
        {
            //tempsol->plan->at(i) = solution->plan->at(i);
            //tempsol->planCC->at(i) = solution->planCC->at(i);
           // tempsol->PIObj = solution->PIObj;
            //tempsol->PSObj = solution->PSObj;
            if(solution->plan->at(i)!=-1)//si la case dans le plan n'est pas vide on remplie le planAffect
            {
                solution->PlanAffect->push_back({i,solution->plan->at(i)});
            }
        }

        //����������������������������������������������������������
        //���������������������������������������������������������������
        //   tempsol->planCC=NULL;
        //LF comment: on traverse tte les fr�quence et on calcule le cout
        int victimFrequency,interfererFrequency;
        int victimTrx,interfererTrx;
        victimTrx = trx.trxID;

        int taille;
        //..........................................................
        //..........................................................
        //vecteur pour enregistrer le couple de cout  interference, separation � la fois
        vector < pair<double,double>  > paircost ;
        //----------------------
        if(trx.AvailableFrequencies->empty()==false)
        {
           taille =trx.AvailableFrequencies->size();

            vector<double> * veccost = new vector <double>(taille);
                 vector<double> * cost = new vector <double>(taille);
            if (taille>1)
            {
                for(i=0 ;i < taille ; i++)//pour chaque fr�quence probable on evalue le cout
                {

                    victimFrequency =trx.AvailableFrequencies->at(i);
                    veccost->at(i)=0.0;
                    cost->at(i)=0.0;
                    solution->PlanAffect->push_back({trx.trxID,victimFrequency});
                    //on �value la solution avec le nouveau couple : {victimTrx,victimFrequency}
                   int victimTrx1 = trx.trxID; int victimFrequency1 = trx.AvailableFrequencies->at(i);
                    for(j=0;j< solution->PlanAffect->size();j++)
                    {

                        victimTrx = solution->PlanAffect->at(j).first;
                        victimFrequency = solution->PlanAffect->at(j).second;
                       interfererTrx = solution->PlanAffect->at(j).first;
                        interfererFrequency = solution->PlanAffect->at(j).second;
                        if ( interfererTrx != victimTrx1)
                        {
                           // calculer le cout d interference
                            veccost->at(i)  = veccost->at(i)  + afpProblem->computeChannelInterference(victimFrequency1 ,interfererFrequency, victimTrx1, interfererTrx)+
                            afpProblem->computeChannelInterference(interfererFrequency,victimFrequency1 ,interfererTrx, victimTrx1);
                            //cout de separation
                           if(afpProblem->trxs[victimTrx1].sectorID == afpProblem->trxs[interfererTrx].sectorID)
                            {
                                //on teste si la contraite de separation co-secteur est respect�!!
                                if (abs (interfererFrequency-victimFrequency1)<3 )//contrainte co secteur viol�e
                                {
                                    cost->at(i) = cost->at(i) + 1.0;
                                }
                            }// secteur different
                            else
                            {
                                if(afpProblem->trxs[victimTrx1].siteID  == afpProblem->trxs[interfererTrx].siteID)
                                {
                        //on teste si la contrainte de separation co-site est respect�e!!
                                    if (abs (interfererFrequency-victimFrequency1)< 2)//contrainte co secteur viol�e
                                    {
                                        cost->at(i) = cost->at(i) + 1.0;
                                    }
                                }//
                            }
                        }

                    }// for(j=0 ;j < taille ; j++)//pour chaque fr�quence probable on evalue le cout
                    //.............................................................................
                    //.............................................................................
                    // enregister les couts dans le vecteur
                  //  cout << veccost->at(i) << veccost->at(i) << endl;
                    veccost->at(i) = veccost->at(i) + solution->PIObj ;
                    cost->at(i) = cost->at(i) + solution->PSObj ;
                    paircost.push_back({veccost->at(i),cost->at(i)});
                    //...................................................................
                    solution->PlanAffect->pop_back();//on retire le couple probable apres evaluation de cout et l avoir enregistr� dans veccost
                    // cout<<"frequence ::" <<trx.AvailableFrequencies->at(i)<<", son sout veccost[i] ==="<< veccost->at(i)<<endl;
                } //fortrx.AvailableFrequencies


 //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
     //DOMINANCE
   //
                 //...................................................
                 //.....................................................
                // I . Retirer la non dominance pour chaque fr�quence
                // ....................................................
                //...................................................

                //je supose que la soluution est domiin�e et je vais tester si c est vrai

                    //+++++++++++++Laidi modifi� +++++++++++++++++++++++++++++++++++
      //je supose que la soluution est domiin�e et je vais tester si c est vrai
            int rank;
  int counter;
  int dominantScore;
  int temp = 0;
  rank = 1;
  vector < pair<int,double> > IndexesFreqsNonDominantes;
    IndexesFreqsNonDominantes.reserve(paircost.size());
    int taille=paircost.size();
    int array_rank[paircost.size()];
    counter =paircost.size();


    for (int i=0; i<paircost.size(); i++)
    {
      dominantScore=0;

	  for (int j=0; j<paircost.size(); j++)
	  {
        if (i!=j)
        {

            if ((paircost[i].first>=paircost[j].first && paircost[i].second>paircost[j].second) || (paircost[i].second>=paircost[j].second && paircost[i].first>paircost[j].first))
            {
          //  array_domination_count[i] = array_domination_count[i] + 1;
            dominantScore=dominantScore+1;// on a trouv� j qui domine i ;
            }
        }//i!=j
       } //fin j
		if (dominantScore==0)
        {
          // indices.push_back(i); // pour sauvgarder les indices des solution non dominées dans la nouvelle population
           IndexesFreqsNonDominantes.push_back({i,paircost[i].second});
        }
	}//fin i



              if (IndexesFreqsNonDominantes.size()!= 0)
              {
                  //cout << " la taille du vect solutions non dom PS == " << IndexesFreqsNonDominantes.size()<< endl;
                 // sort(IndexesFreqsNonDominantes.begin(),IndexesFreqsNonDominantes.end(),my_cmpInfDoublePair);//trier selon un ordre croissant de cout
                sort(IndexesFreqsNonDominantes.begin(),IndexesFreqsNonDominantes.end(),my_cmpInfDoublePair);
                //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                //~~~~~~~~~~~~~~~~~~~~~~~~~~~si plusieurs fr�queences  non domlinates ont le meme cout on choisit
                // al�atoirement une
                //---------------------------------------------------
                i = 0;     k = 0 ;
                //------------------------------------
                for(i = 0 ; i < IndexesFreqsNonDominantes.size(); i++)
                {
                    //double val = IndexesFreqsNonDominantes.at(i).second;
                    double val = IndexesFreqsNonDominantes.at(i).second;
                    //pair<int,double> pnextval;
                    pair<int,double> pnextval;
                    if((i+1) < IndexesFreqsNonDominantes.size())
                    {
                        pnextval = IndexesFreqsNonDominantes.at(i+1);
                        //double nextval = pnextval.second;
                        double nextval = pnextval.second;
                        // on copie les valeurs egales dans un tableau
                        //cout<< "hiiii here " << endl;
                        if( val == nextval )
                        {
                            k = k +1 ;//k contient le nombre de valeur �gale
                        }
                        else
                        {
                            i = IndexesFreqsNonDominantes.size();
                        }
                    }
                }
                int indice ;
                //indice = rand() % (k+1);// coisir une parmi les "n" premier
                //indexmin = IndexesFreqsNonDominantes.at(indice).first;// r�cup�ration de l'indice de la fr�quence
               // cout << "k ������������������" << k << endl;
                  vector < pair< int, double> > distance;
            distance.reserve(k+1);
            int indicefreq;
            indicefreq = IndexesFreqsNonDominantes.at(0).first;
             double v = abs(veccost->at(indicefreq)- cost->at(indicefreq));
            distance.push_back({indicefreq,v});
            for(i = 1 ;i < k ; i++)
            {
                indicefreq = IndexesFreqsNonDominantes.at(i).first;
                v  =  abs(veccost->at(indicefreq)- cost->at(indicefreq));
                distance.push_back({indicefreq,v});
            }
            sort(distance.begin(),distance.end(),my_cmpInfDoublePair);
            indexmin = distance.front().first;// r�cup�ration de l'indice de la fr�quenc













              }
               else// il n y a aucune valeur dans le front pareto
               {
                 //cout << " taille 0000000000000000 " << endl;
                 // vecmin(cost, indexmin);//indexmin:indice de la fr�quencence qui a la valeur minimale
                 StrategyFreq = 2;//3 : ecart, 6: hv , 2 : minimum cost
                 PSChooseFrequency(instance,StrategyFreq,trx,f,solution,afpProblem);
                 return;

               }
    //............................End dominance ......................................
    //................................................................................
    //................................................................................
    f=trx.AvailableFrequencies->at(indexmin);//indice de la fr�quence recherch�
    solution->PIObj = veccost->at(indexmin);
    solution->PSObj = cost->at(indexmin);
    //delete(tempsol->PlanAffect);
    vector < pair<double,double> > ().swap(paircost) ;
    vector < pair<int,double> > ().swap(IndexesFreqsNonDominantes);
    delete(veccost);
    delete(cost);
    //delete(tempsol->PlanAffect);
    delete(solution->PlanAffect);
    //--------------------- dominance available
    }//if (taille >1)
    else
    {
       if(taille==1) // la taille  == 1; je n ai qu'un choix
        {
            f=trx.AvailableFrequencies->at(0);
            // cout<<" frequency choisit:lorsque la taille est 0"<<f<<endl;
            // cout<<"hii"<<endl;
            delete(solution->PlanAffect);
        }
    }//taille :.!=1
 }// Availablefrequencies is empty()
else//Availablefrequencies==empty() // aucune fr�quence n'est diponible j'utilise les fr�quence valides
        {// on choisit la meilleur fr�quence VALID

            //****************#################################""
        //----------------------
        if(trx.validFrequencies->empty()==false)
        {
            taille =trx.validFrequencies->size();
            vector<double> * veccost = new vector <double>(taille);
                vector<double> * cost = new vector <double>(taille);
            if (taille>1)
            {
                for(i=0 ;i < taille ; i++)//pour chaque fr�quence probable on evalue le cout
                {
                    victimFrequency =trx.validFrequencies->at(i);
                     veccost->at(i)=0.0;
                    cost->at(i)=0.0;
                    solution->PlanAffect->push_back({trx.trxID,victimFrequency});
                    //on �value la solution avec le nouveau couple : {victimTrx,victimFrequency}
                   int victimTrx1 = trx.trxID; int victimFrequency1 = trx.AvailableFrequencies->at(i);
                    for(j=0;j< solution->PlanAffect->size();j++)
                    {

                        victimTrx = solution->PlanAffect->at(j).first;
                        victimFrequency = solution->PlanAffect->at(j).second;
                       interfererTrx = solution->PlanAffect->at(j).first;
                        interfererFrequency = solution->PlanAffect->at(j).second;
                        if ( interfererTrx != victimTrx1)
                        {
                           // calculer le cout d interference
                            veccost->at(i)  = veccost->at(i)  + afpProblem->computeChannelInterference(victimFrequency1 ,interfererFrequency, victimTrx1, interfererTrx)+
                            afpProblem->computeChannelInterference(interfererFrequency,victimFrequency1 ,interfererTrx, victimTrx1);
                            //cout de separation
                           if(afpProblem->trxs[victimTrx1].sectorID == afpProblem->trxs[interfererTrx].sectorID)
                            {
                                //on teste si la contraite de separation co-secteur est respect�!!
                                if (abs (interfererFrequency-victimFrequency1)<3 )//contrainte co secteur viol�e
                                {
                                    cost->at(i) = cost->at(i) + 1.0;
                                }
                            }// secteur different
                            else
                            {
                                if(afpProblem->trxs[victimTrx1].siteID  == afpProblem->trxs[interfererTrx].siteID)
                                {
                        //on teste si la contrainte de separation co-site est respect�e!!
                                    if (abs (interfererFrequency-victimFrequency1)< 2)//contrainte co secteur viol�e
                                    {
                                        cost->at(i) = cost->at(i) + 1.0;
                                    }
                                }//
                            }
                        }

                    }// for(j=0 ;j < taille ; j++)//pour chaque fr�quence probable on evalue le cout
                    //.............................................................................
                    //.............................................................................
                    // enregister les couts dans le vecteur
                  //  cout << veccost->at(i) << veccost->at(i) << endl;
                    veccost->at(i) = veccost->at(i) + solution->PIObj ;
                    cost->at(i) = cost->at(i) + solution->PSObj ;
                    paircost.push_back({veccost->at(i),cost->at(i)});
                    //...................................................................
                    solution->PlanAffect->pop_back();//on retire le couple probable apres evaluation de cout et l avoir enregistr� dans veccost
                    // cout<<"frequence ::" <<trx.AvailableFrequencies->at(i)<<", son sout veccost[i] ==="<< veccost->at(i)<<endl;
                } //fortrx.Av
          //..............................................................
                //...................................................................................

        //DOMINANCE


                 //...................................................
                 //.....................................................
                // I . Retirer la non dominance pour chaque fr�quence
                // ....................................................
                //...................................................

                 int  DominantScore;

                vector < pair<int,int> > IndexesFreqsNonDominantes;
                 //(int,int) :: le premier enregistre l index de la fr�quence non dominante
                  //(int,int) :: le dexieme , combien de fois la fr�quence est non dominante
                IndexesFreqsNonDominantes.reserve(trx.validFrequencies->size());
        //+++++++++++++Laidi modifi� +++++++++++++++++++++++++++++++++++
          for( i = 0; i < trx.AvailableFrequencies->size();i++)//la solution condidate est dans l indice i
                {

                  DominantScore = 0 ;// pour compter le nombre de solution qui domine la solution courante

                  for( j = i+1; j < trx.AvailableFrequencies->size() ;j++)
                   {
                       if (i!=j)
                       {

                           if (paircost[i].first > paircost[j].first) // on teste la dominance par rapport au premier objectif
                            {
                                // on ne peut pas juger on test par rapport au deuxime obj
                                if (paircost[i].second > paircost[j].second)
                                         {

                                                  //on est sur qu elle est dominante
                                                DominantScore    =   DominantScore+1 ;


                                         }
                                         else
                                         {
                                             if(paircost[i].first >= paircost[j].first)
                                              {
                                                    DominantScore    =   DominantScore+1 ;
                                              }
                                         }

                            }
                            else
                            {
                                if (paircost[i].second >= paircost[j].second)
                                    {
                                        DominantScore    =   DominantScore+1 ;
                                    }

                            }


                        }//i!=j
                    }//fin j

						if (DominantScore==0)// pour s'assurer que la solution "i" est non dominée
                      {
                        IndexesFreqsNonDominantes.push_back({i,paircost[i].first});// on insert l'index de la solution et son cout d'interférences
                      }
                       // cout << "la solution " << i << " est dominee par  " << DominantScore << " autres solutions" << endl;
                }//fin i

            //cout <<"IndexesFreqsNonDominantes.size()PIII  "<< IndexesFreqsNonDominantes.size() <<endl;*/
                //----------------------------------------------------------------------
                 //+++++++++++++ sol par sol +++++++++++++++++++++++++++++++++++
                 //++++++++++++++++++ tout les sol
                  int  nondominancescore;
                  //cout << "trx.AvailableFrequencies->size()++++ "<< trx.AvailableFrequencies->size() <<endl;

                      for( i = 0; i < trx.validFrequencies->size();i++)//la solution condidate est dans l indice i
                {

                  nondominancescore = 0 ;// pour compter le nombre de solution qui domine la solution courante

                   for( j = 0; j < trx.AvailableFrequencies->size() ;j++)
                   {

                       if (i!=j)
                       {

                                   if (paircost[i].first <= paircost[j].first)  // on teste la dominance par rapport au deuciÃ¨me objectif
                                    {
                                          if (paircost[i].second < paircost[j].second)

                                        {
                                            IndexesFreqsNonDominantes.push_back({i,paircost[i].first});

                                            nondominancescore = nondominancescore + 1;
                                            }
                                        }


                                    //--- j insere le deuxi�me obj
                                  /* else
                                    {
                                         if (paircost[i].second <= paircost[j].second) // teste la dominance par rapport au deuciÃ¨me objectif
                                        {
                                                if (paircost[i].first < paircost[j].first) // on
                                                {
                                                    IndexesFreqsNonDominantes.push_back({i,paircost[i].first});
                                            //au deuxieme obj

                                                nondominancescore = nondominancescore+1;
                                                }
                                            //}
                                        }
                                    }*/

                       }//i!=j
                   }//fin j
                   /*  if (nondominancescore > (trx.AvailableFrequencies->size() - 2 ))
                  IndexesFreqsNonDominantes.push_back({i,paircost[i].first});*/

              }//fin i
            // cout <<"IndexesFreqsNonDominantes.size()PIII  "<< IndexesFreqsNonDominantes.size() <<endl;



                //...................................................
                 //.....................................................
                // II . Trier le tableau de la non dominance selon un ordre croissant si la liste n est pas vide
                // ....................................................
                //...................................................
              //  sort(IndexesFreqsNonDominantes.begin(),IndexesFreqsNonDominantes.end(),my_cmp);
             // cout << "  IndexesFreqsNonDominantes.size() ****"<< IndexesFreqsNonDominantes.size() << endl;


                // copier les solution trouver dans un vecteur avec son cout d interferqunce qui
                if (IndexesFreqsNonDominantes.size()!= 0 )
                {
                    /*vector < pair < int, double> > NonDominanteCost;
                    NonDominanteCost.reserve(IndexesFreqsNonDominantes.size());
                    for(i = 0; i < IndexesFreqsNonDominantes.size(); i++ )
                    {
                        NonDominanteCost.push_back({IndexesFreqsNonDominantes[i].first, paircost[IndexesFreqsNonDominantes[i].first].first });
                    }*/
                // trier le tableau selon un ordre d�croisant du cout et retirer la premi�re valeur
                    sort(IndexesFreqsNonDominantes.begin(),IndexesFreqsNonDominantes.end(),my_cmpInfDoublePair);
                   // indexmin = IndexesFreqsNonDominantes.front().first;
                   //si des valeur de cout �gale on choisit al�atoirement parmi ces valeur
                   //+++++++++++++++++++++++++++++++++++++++++++
                   k=0;
                   for(i = 0 ; i < IndexesFreqsNonDominantes.size(); i++)
                    {
                        double val = IndexesFreqsNonDominantes.at(i).second;
                        pair<int,double> pnextval;
                        if((i+1) < IndexesFreqsNonDominantes.size())
                        {
                            pnextval = IndexesFreqsNonDominantes.at(i+1);
                            double nextval = pnextval.second;
                            // on copie les valeurs egales dans un tableau
                            //cout<< "hiiii here " << endl;
                            if( val == nextval )
                            {
                                k = k +1 ;//k contient le nombre de valeur �gale
                                // cout<< "hiiii here " << endl;
                            }
                            else
                            {
                                i = IndexesFreqsNonDominantes.size();
                            }
                        }
                    }
    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                    int indexf = rand() % (k+1);
                    indexmin = IndexesFreqsNonDominantes.at(indexf).first;

                }
                else
                {
                     vecmin(veccost, indexmin);//indexmin:indice de la fr�quencence qui a la valeur minimale
                }

                //................................................................................

//--------------------- dominance available
                //..............................................................
                //...................................................................................

    //vider la m�moire--vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
    vector < pair<double,double>  >().swap(paircost) ;
    delete(veccost);
    delete(solution->PlanAffect);
                //..............................................................
                //...................................................................................
                f=trx.validFrequencies->at(indexmin);//indice de la fr�quence ayant un cout minimal,

    //+++++++++++++++++++++++++++++++

            }//taille >1
            else
            {
                if(taille==1)
                {
                    f=trx.validFrequencies->at(0);
                // cout<<" frequency choisit:lorsque la taille est 0"<<f<<endl;
                // cout<<"hii"<<endl;
                }
            }//taille == 1?!!
        }
        else//Availablefrequencies==empty()
        {
            cout<<" la liste des fr�quences valide est vide **"<<endl;
        }
















            //******************
            //cout<<" la liste des fr�quences disponibles est vide **"<<endl;
        }
    break;
    }//case 551 : best frequency Front pareto Laidi
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
     //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ FRONt PARETO PUUUUUUUUUUUURE Plus grand HV ~~~~~~~~~~~~~~~~~~~~~~
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   case  552://strategy 5 choisir la meilleur fr�quence en terme Front parteo plus grand HV
    {
          int i,indexmin,j,k;
       // Individual * tempsol =  new Individual();
        int tempfreq;
        //��������������������������������� copier la solution dans tempsol ����������������������
        //���������������������������������������������������������������������������������������
        //tempsol = solution;
        //tempsol->plan = new vector <int>(solution->plan->size());
        //tempsol->planCC = new vector <double>(solution->planCC->size());
        solution->PlanAffect = new vector< pair<int,int> > ();
        // tempsol->PIObj = solution->PIObj;
        // tempsol->PSObj = solution->PSObj;
        for(i=0;i<solution->plan->size();i++)
        {
            //tempsol->plan->at(i) = solution->plan->at(i);
            //tempsol->planCC->at(i) = solution->planCC->at(i);
           // tempsol->PIObj = solution->PIObj;
            //tempsol->PSObj = solution->PSObj;
            if(solution->plan->at(i)!=-1)//si la case dans le plan n'est pas vide on remplie le planAffect
            {
                solution->PlanAffect->push_back({i,solution->plan->at(i)});
            }
        }

        //����������������������������������������������������������
        //���������������������������������������������������������������
        //   tempsol->planCC=NULL;
        //LF comment: on traverse tte les fr�quence et on calcule le cout
        int victimFrequency,interfererFrequency;
        int victimTrx,interfererTrx;
        victimTrx = trx.trxID;

        int taille;
        //..........................................................
        //..........................................................
        //vecteur pour enregistrer le couple de cout  interference, separation � la fois
        vector < pair<double,double>  > paircost ;
        //----------------------
        if(trx.AvailableFrequencies->empty()==false)
        {
           taille =trx.AvailableFrequencies->size();

            vector<double> * veccost = new vector <double>(taille);
                 vector<double> * cost = new vector <double>(taille);
            if (taille>1)
            {
                for(i=0 ;i < taille ; i++)//pour chaque fr�quence probable on evalue le cout
                {

                    victimFrequency =trx.AvailableFrequencies->at(i);
                    veccost->at(i)=0.0;
                    cost->at(i)=0.0;
                    solution->PlanAffect->push_back({trx.trxID,victimFrequency});
                    //on �value la solution avec le nouveau couple : {victimTrx,victimFrequency}
                   int victimTrx1 = trx.trxID; int victimFrequency1 = trx.AvailableFrequencies->at(i);
                    for(j=0;j< solution->PlanAffect->size();j++)
                    {

                        victimTrx = solution->PlanAffect->at(j).first;
                        victimFrequency = solution->PlanAffect->at(j).second;
                       interfererTrx = solution->PlanAffect->at(j).first;
                        interfererFrequency = solution->PlanAffect->at(j).second;
                        if ( interfererTrx != victimTrx1)
                        {
                           // calculer le cout d interference
                            veccost->at(i)  = veccost->at(i)  + afpProblem->computeChannelInterference(victimFrequency1 ,interfererFrequency, victimTrx1, interfererTrx)+
                            afpProblem->computeChannelInterference(interfererFrequency,victimFrequency1 ,interfererTrx, victimTrx1);
                            //cout de separation
                           if(afpProblem->trxs[victimTrx1].sectorID == afpProblem->trxs[interfererTrx].sectorID)
                            {
                                //on teste si la contraite de separation co-secteur est respect�!!
                                if (abs (interfererFrequency-victimFrequency1)<3 )//contrainte co secteur viol�e
                                {
                                    cost->at(i) = cost->at(i) + 1.0;
                                }
                            }// secteur different
                            else
                            {
                                if(afpProblem->trxs[victimTrx1].siteID  == afpProblem->trxs[interfererTrx].siteID)
                                {
                        //on teste si la contrainte de separation co-site est respect�e!!
                                    if (abs (interfererFrequency-victimFrequency1)< 2)//contrainte co secteur viol�e
                                    {
                                        cost->at(i) = cost->at(i) + 1.0;
                                    }
                                }//
                            }
                        }

                    }// for(j=0 ;j < taille ; j++)//pour chaque fr�quence probable on evalue le cout
                    //.............................................................................
                    //.............................................................................
                    // enregister les couts dans le vecteur
                  //  cout << veccost->at(i) << veccost->at(i) << endl;
                    veccost->at(i) = veccost->at(i) + solution->PIObj ;
                    cost->at(i) = cost->at(i) + solution->PSObj ;
                    paircost.push_back({veccost->at(i),cost->at(i)});
                    //...................................................................
                    solution->PlanAffect->pop_back();//on retire le couple probable apres evaluation de cout et l avoir enregistr� dans veccost
                    // cout<<"frequence ::" <<trx.AvailableFrequencies->at(i)<<", son sout veccost[i] ==="<< veccost->at(i)<<endl;
                } //fortrx.AvailableFrequencies


 //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
     //DOMINANCE
   //
                 //...................................................
                 //.....................................................
                // I . Retirer la non dominance pour chaque fr�quence
                // ....................................................
                //...................................................

                //je supose que la soluution est domiin�e et je vais tester si c est vrai

                    //+++++++++++++Laidi modifi� +++++++++++++++++++++++++++++++++++
      //je supose que la soluution est domiin�e et je vais tester si c est vrai
            int rank;
  int counter;
  int dominantScore;
  int temp = 0;
  rank = 1;
  vector < pair<int,double> > IndexesFreqsNonDominantes;
    IndexesFreqsNonDominantes.reserve(paircost.size());
    int taille=paircost.size();
    int array_rank[paircost.size()];
    counter =paircost.size();


    for (int i=0; i<paircost.size(); i++)
    {
      dominantScore=0;

	  for (int j=0; j<paircost.size(); j++)
	  {
        if (i!=j)
        {

            if ((paircost[i].first>=paircost[j].first && paircost[i].second>paircost[j].second) || (paircost[i].second>=paircost[j].second && paircost[i].first>paircost[j].first))
            {
          //  array_domination_count[i] = array_domination_count[i] + 1;
            dominantScore=dominantScore+1;// on a trouv� j qui domine i ;
            }
        }//i!=j
       } //fin j
		if (dominantScore==0)
        {
          // indices.push_back(i); // pour sauvgarder les indices des solution non dominées dans la nouvelle population
           IndexesFreqsNonDominantes.push_back({i,paircost[i].second});
        }
	}//fin i



              if (IndexesFreqsNonDominantes.size()!= 0)
              {
                  //cout << " la taille du vect solutions non dom PS == " << IndexesFreqsNonDominantes.size()<< endl;
                 // sort(IndexesFreqsNonDominantes.begin(),IndexesFreqsNonDominantes.end(),my_cmpInfDoublePair);//trier selon un ordre croissant de cout
                sort(IndexesFreqsNonDominantes.begin(),IndexesFreqsNonDominantes.end(),my_cmpInfDoublePair);
                //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                //~~~~~~~~~~~~~~~~~~~~~~~~~~~si plusieurs fr�queences  non domlinates ont le meme cout on choisit
                // al�atoirement une
                //---------------------------------------------------
                i = 0;     k = 0 ;
                //------------------------------------
                for(i = 0 ; i < IndexesFreqsNonDominantes.size(); i++)
                {
                    //double val = IndexesFreqsNonDominantes.at(i).second;
                    double val = IndexesFreqsNonDominantes.at(i).second;
                    //pair<int,double> pnextval;
                    pair<int,double> pnextval;
                    if((i+1) < IndexesFreqsNonDominantes.size())
                    {
                        pnextval = IndexesFreqsNonDominantes.at(i+1);
                        //double nextval = pnextval.second;
                        double nextval = pnextval.second;
                        // on copie les valeurs egales dans un tableau
                        //cout<< "hiiii here " << endl;
                        if( val == nextval )
                        {
                            k = k +1 ;//k contient le nombre de valeur �gale
                        }
                        else
                        {
                            i = IndexesFreqsNonDominantes.size();
                        }
                    }
                }
                int indice ;
              //  indice = rand() % (k+1);// coisir une parmi les "n" premier
               // indexmin = IndexesFreqsNonDominantes.at(indice).first;// r�cup�ration de l'indice de la fr�quence
               // cout << "k ������������������" << k << endl;

            vector< pair < int, double > > VectHV;

            VectHV.reserve(k+1);
            int indicefreq;
            indicefreq = IndexesFreqsNonDominantes.at(0).first;
             pair<double,double> Min;
            pair<double,double> Max;
            pair < double, double > R;// est le point de r�f�rence ; la valeur max (normalis�)
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
    Normalize(paircost,Min,Max);
    for(i=0; i<= k; i++)
    {
        int valindice = IndexesFreqsNonDominantes.at(i).first;
        double X = paircost.at(valindice).first ;
        double Y = paircost.at(valindice).second ;
        double ValHV = (R.first - X)* (R.second - Y);
        VectHV.push_back({valindice,ValHV});
    }

    //**********************************************************

            sort(VectHV.begin(),VectHV.end(),my_cmpSupDoublePair);
            indexmin = VectHV.front().first;// r�cup�ration de l'indice de la fr�quence













              }
               else// il n y a aucune valeur dans le front pareto
               {
                 //cout << " taille 0000000000000000 " << endl;
                 // vecmin(cost, indexmin);//indexmin:indice de la fr�quencence qui a la valeur minimale
                 StrategyFreq = 2;//3 : ecart, 6: hv , 2 : minimum cost
                 PSChooseFrequency(instance,StrategyFreq,trx,f,solution,afpProblem);
                 return;

               }
    //............................End dominance ......................................
    //................................................................................
    //................................................................................
    f=trx.AvailableFrequencies->at(indexmin);//indice de la fr�quence recherch�
    solution->PIObj = veccost->at(indexmin);
    solution->PSObj = cost->at(indexmin);
    //delete(tempsol->PlanAffect);
    vector < pair<double,double> > ().swap(paircost) ;
    vector < pair<int,double> > ().swap(IndexesFreqsNonDominantes);
    delete(veccost);
    delete(cost);
    //delete(tempsol->PlanAffect);
    delete(solution->PlanAffect);
    //--------------------- dominance available
    }//if (taille >1)
    else
    {
       if(taille==1) // la taille  == 1; je n ai qu'un choix
        {
            f=trx.AvailableFrequencies->at(0);
            // cout<<" frequency choisit:lorsque la taille est 0"<<f<<endl;
            // cout<<"hii"<<endl;
            delete(solution->PlanAffect);
        }
    }//taille :.!=1
 }// Availablefrequencies is empty()
else//Availablefrequencies==empty() // aucune fr�quence n'est diponible j'utilise les fr�quence valides
        {// on choisit la meilleur fr�quence VALID

            //****************#################################""
        //----------------------
        if(trx.validFrequencies->empty()==false)
        {
            taille =trx.validFrequencies->size();
            vector<double> * veccost = new vector <double>(taille);
                vector<double> * cost = new vector <double>(taille);
            if (taille>1)
            {
                for(i=0 ;i < taille ; i++)//pour chaque fr�quence probable on evalue le cout
                {
                    victimFrequency =trx.validFrequencies->at(i);
                     veccost->at(i)=0.0;
                    cost->at(i)=0.0;
                    solution->PlanAffect->push_back({trx.trxID,victimFrequency});
                    //on �value la solution avec le nouveau couple : {victimTrx,victimFrequency}
                   int victimTrx1 = trx.trxID; int victimFrequency1 = trx.AvailableFrequencies->at(i);
                    for(j=0;j< solution->PlanAffect->size();j++)
                    {

                        victimTrx = solution->PlanAffect->at(j).first;
                        victimFrequency = solution->PlanAffect->at(j).second;
                       interfererTrx = solution->PlanAffect->at(j).first;
                        interfererFrequency = solution->PlanAffect->at(j).second;
                        if ( interfererTrx != victimTrx1)
                        {
                           // calculer le cout d interference
                            veccost->at(i)  = veccost->at(i)  + afpProblem->computeChannelInterference(victimFrequency1 ,interfererFrequency, victimTrx1, interfererTrx)+
                            afpProblem->computeChannelInterference(interfererFrequency,victimFrequency1 ,interfererTrx, victimTrx1);
                            //cout de separation
                           if(afpProblem->trxs[victimTrx1].sectorID == afpProblem->trxs[interfererTrx].sectorID)
                            {
                                //on teste si la contraite de separation co-secteur est respect�!!
                                if (abs (interfererFrequency-victimFrequency1)<3 )//contrainte co secteur viol�e
                                {
                                    cost->at(i) = cost->at(i) + 1.0;
                                }
                            }// secteur different
                            else
                            {
                                if(afpProblem->trxs[victimTrx1].siteID  == afpProblem->trxs[interfererTrx].siteID)
                                {
                        //on teste si la contrainte de separation co-site est respect�e!!
                                    if (abs (interfererFrequency-victimFrequency1)< 2)//contrainte co secteur viol�e
                                    {
                                        cost->at(i) = cost->at(i) + 1.0;
                                    }
                                }//
                            }
                        }

                    }// for(j=0 ;j < taille ; j++)//pour chaque fr�quence probable on evalue le cout
                    //.............................................................................
                    //.............................................................................
                    // enregister les couts dans le vecteur
                  //  cout << veccost->at(i) << veccost->at(i) << endl;
                    veccost->at(i) = veccost->at(i) + solution->PIObj ;
                    cost->at(i) = cost->at(i) + solution->PSObj ;
                    paircost.push_back({veccost->at(i),cost->at(i)});
                    //...................................................................
                    solution->PlanAffect->pop_back();//on retire le couple probable apres evaluation de cout et l avoir enregistr� dans veccost
                    // cout<<"frequence ::" <<trx.AvailableFrequencies->at(i)<<", son sout veccost[i] ==="<< veccost->at(i)<<endl;
                } //fortrx.Av
          //..............................................................
                //...................................................................................

        //DOMINANCE


                 //...................................................
                 //.....................................................
                // I . Retirer la non dominance pour chaque fr�quence
                // ....................................................
                //...................................................

                 int  DominantScore;

                vector < pair<int,int> > IndexesFreqsNonDominantes;
                 //(int,int) :: le premier enregistre l index de la fr�quence non dominante
                  //(int,int) :: le dexieme , combien de fois la fr�quence est non dominante
                IndexesFreqsNonDominantes.reserve(trx.validFrequencies->size());
        //+++++++++++++Laidi modifi� +++++++++++++++++++++++++++++++++++
          for( i = 0; i < trx.AvailableFrequencies->size();i++)//la solution condidate est dans l indice i
                {

                  DominantScore = 0 ;// pour compter le nombre de solution qui domine la solution courante

                  for( j = i+1; j < trx.AvailableFrequencies->size() ;j++)
                   {
                       if (i!=j)
                       {

                           if (paircost[i].first > paircost[j].first) // on teste la dominance par rapport au premier objectif
                            {
                                // on ne peut pas juger on test par rapport au deuxime obj
                                if (paircost[i].second > paircost[j].second)
                                         {

                                                  //on est sur qu elle est dominante
                                                DominantScore    =   DominantScore+1 ;


                                         }
                                         else
                                         {
                                             if(paircost[i].first >= paircost[j].first)
                                              {
                                                    DominantScore    =   DominantScore+1 ;
                                              }
                                         }

                            }
                            else
                            {
                                if (paircost[i].second >= paircost[j].second)
                                    {
                                        DominantScore    =   DominantScore+1 ;
                                    }

                            }


                        }//i!=j
                    }//fin j

						if (DominantScore==0)// pour s'assurer que la solution "i" est non dominée
                      {
                        IndexesFreqsNonDominantes.push_back({i,paircost[i].first});// on insert l'index de la solution et son cout d'interférences
                      }
                       // cout << "la solution " << i << " est dominee par  " << DominantScore << " autres solutions" << endl;
                }//fin i

            //cout <<"IndexesFreqsNonDominantes.size()PIII  "<< IndexesFreqsNonDominantes.size() <<endl;*/
                //----------------------------------------------------------------------
                 //+++++++++++++ sol par sol +++++++++++++++++++++++++++++++++++
                 //++++++++++++++++++ tout les sol
                  int  nondominancescore;
                  //cout << "trx.AvailableFrequencies->size()++++ "<< trx.AvailableFrequencies->size() <<endl;

                      for( i = 0; i < trx.validFrequencies->size();i++)//la solution condidate est dans l indice i
                {

                  nondominancescore = 0 ;// pour compter le nombre de solution qui domine la solution courante

                   for( j = 0; j < trx.AvailableFrequencies->size() ;j++)
                   {

                       if (i!=j)
                       {

                                   if (paircost[i].first <= paircost[j].first)  // on teste la dominance par rapport au deuciÃ¨me objectif
                                    {
                                          if (paircost[i].second < paircost[j].second)

                                        {
                                            IndexesFreqsNonDominantes.push_back({i,paircost[i].first});

                                            nondominancescore = nondominancescore + 1;
                                            }
                                        }


                                    //--- j insere le deuxi�me obj
                                  /* else
                                    {
                                         if (paircost[i].second <= paircost[j].second) // teste la dominance par rapport au deuciÃ¨me objectif
                                        {
                                                if (paircost[i].first < paircost[j].first) // on
                                                {
                                                    IndexesFreqsNonDominantes.push_back({i,paircost[i].first});
                                            //au deuxieme obj

                                                nondominancescore = nondominancescore+1;
                                                }
                                            //}
                                        }
                                    }*/

                       }//i!=j
                   }//fin j
                   /*  if (nondominancescore > (trx.AvailableFrequencies->size() - 2 ))
                  IndexesFreqsNonDominantes.push_back({i,paircost[i].first});*/

              }//fin i
            // cout <<"IndexesFreqsNonDominantes.size()PIII  "<< IndexesFreqsNonDominantes.size() <<endl;



                //...................................................
                 //.....................................................
                // II . Trier le tableau de la non dominance selon un ordre croissant si la liste n est pas vide
                // ....................................................
                //...................................................
              //  sort(IndexesFreqsNonDominantes.begin(),IndexesFreqsNonDominantes.end(),my_cmp);
             // cout << "  IndexesFreqsNonDominantes.size() ****"<< IndexesFreqsNonDominantes.size() << endl;


                // copier les solution trouver dans un vecteur avec son cout d interferqunce qui
                if (IndexesFreqsNonDominantes.size()!= 0 )
                {
                    /*vector < pair < int, double> > NonDominanteCost;
                    NonDominanteCost.reserve(IndexesFreqsNonDominantes.size());
                    for(i = 0; i < IndexesFreqsNonDominantes.size(); i++ )
                    {
                        NonDominanteCost.push_back({IndexesFreqsNonDominantes[i].first, paircost[IndexesFreqsNonDominantes[i].first].first });
                    }*/
                // trier le tableau selon un ordre d�croisant du cout et retirer la premi�re valeur
                    sort(IndexesFreqsNonDominantes.begin(),IndexesFreqsNonDominantes.end(),my_cmpInfDoublePair);
                   // indexmin = IndexesFreqsNonDominantes.front().first;
                   //si des valeur de cout �gale on choisit al�atoirement parmi ces valeur
                   //+++++++++++++++++++++++++++++++++++++++++++
                   k=0;
                   for(i = 0 ; i < IndexesFreqsNonDominantes.size(); i++)
                    {
                        double val = IndexesFreqsNonDominantes.at(i).second;
                        pair<int,double> pnextval;
                        if((i+1) < IndexesFreqsNonDominantes.size())
                        {
                            pnextval = IndexesFreqsNonDominantes.at(i+1);
                            double nextval = pnextval.second;
                            // on copie les valeurs egales dans un tableau
                            //cout<< "hiiii here " << endl;
                            if( val == nextval )
                            {
                                k = k +1 ;//k contient le nombre de valeur �gale
                                // cout<< "hiiii here " << endl;
                            }
                            else
                            {
                                i = IndexesFreqsNonDominantes.size();
                            }
                        }
                    }
    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                    int indexf = rand() % (k+1);
                    indexmin = IndexesFreqsNonDominantes.at(indexf).first;

                }
                else
                {
                     vecmin(veccost, indexmin);//indexmin:indice de la fr�quencence qui a la valeur minimale
                }

                //................................................................................

//--------------------- dominance available
                //..............................................................
                //...................................................................................

    //vider la m�moire--vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
    vector < pair<double,double>  >().swap(paircost) ;
    delete(veccost);
    delete(solution->PlanAffect);
                //..............................................................
                //...................................................................................
                f=trx.validFrequencies->at(indexmin);//indice de la fr�quence ayant un cout minimal,

    //+++++++++++++++++++++++++++++++

            }//taille >1
            else
            {
                if(taille==1)
                {
                    f=trx.validFrequencies->at(0);
                // cout<<" frequency choisit:lorsque la taille est 0"<<f<<endl;
                // cout<<"hii"<<endl;
                }
            }//taille == 1?!!
        }
        else//Availablefrequencies==empty()
        {
            cout<<" la liste des fr�quences valide est vide **"<<endl;
        }
















            //******************
            //cout<<" la liste des fr�quences disponibles est vide **"<<endl;
        }
    break;
    }//case 552 : best frequency Front pareto PURE Plus grand HV

  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ FRONt PARETO PUUUUUUUUUUUURE Plus grand HV ~~~~~~~~~~~~~~~~~~~~~~
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   case  502://strategy 5 choisir la meilleur fr�quence en terme Front parteo plus grand HV
    {
          int i,indexmin,j,k;
       // Individual * tempsol =  new Individual();
        int tempfreq;
        //��������������������������������� copier la solution dans tempsol ����������������������
        //���������������������������������������������������������������������������������������
        //tempsol = solution;
        //tempsol->plan = new vector <int>(solution->plan->size());
        //tempsol->planCC = new vector <double>(solution->planCC->size());
        solution->PlanAffect = new vector< pair<int,int> > ();
        // tempsol->PIObj = solution->PIObj;
        // tempsol->PSObj = solution->PSObj;
        for(i=0;i<solution->plan->size();i++)
        {
            //tempsol->plan->at(i) = solution->plan->at(i);
            //tempsol->planCC->at(i) = solution->planCC->at(i);
           // tempsol->PIObj = solution->PIObj;
            //tempsol->PSObj = solution->PSObj;
            if(solution->plan->at(i)!=-1)//si la case dans le plan n'est pas vide on remplie le planAffect
            {
                solution->PlanAffect->push_back({i,solution->plan->at(i)});
            }
        }

        //����������������������������������������������������������
        //���������������������������������������������������������������
        //   tempsol->planCC=NULL;
        //LF comment: on traverse tte les fr�quence et on calcule le cout
        int victimFrequency,interfererFrequency;
        int victimTrx,interfererTrx;
        victimTrx = trx.trxID;

        int taille;
        //..........................................................
        //..........................................................
        //vecteur pour enregistrer le couple de cout  interference, separation � la fois
        vector < pair<double,double>  > paircost ;
        //----------------------
        if(trx.AvailableFrequencies->empty()==false)
        {
           taille =trx.AvailableFrequencies->size();

            vector<double> * veccost = new vector <double>(taille);
                 vector<double> * cost = new vector <double>(taille);
            if (taille>1)
            {
                for(i=0 ;i < taille ; i++)//pour chaque fr�quence probable on evalue le cout
                {

                    victimFrequency =trx.AvailableFrequencies->at(i);
                    veccost->at(i)=0.0;
                    cost->at(i)=0.0;
                    solution->PlanAffect->push_back({trx.trxID,victimFrequency});
                    //on �value la solution avec le nouveau couple : {victimTrx,victimFrequency}
                   int victimTrx1 = trx.trxID; int victimFrequency1 = trx.AvailableFrequencies->at(i);
                    for(j=0;j< solution->PlanAffect->size();j++)
                    {

                        victimTrx = solution->PlanAffect->at(j).first;
                        victimFrequency = solution->PlanAffect->at(j).second;
                       interfererTrx = solution->PlanAffect->at(j).first;
                        interfererFrequency = solution->PlanAffect->at(j).second;
                        if ( interfererTrx != victimTrx1)
                        {
                           // calculer le cout d interference
                            veccost->at(i)  = veccost->at(i)  + afpProblem->computeChannelInterference(victimFrequency1 ,interfererFrequency, victimTrx1, interfererTrx)+
                            afpProblem->computeChannelInterference(interfererFrequency,victimFrequency1 ,interfererTrx, victimTrx1);
                            //cout de separation
                           if(afpProblem->trxs[victimTrx1].sectorID == afpProblem->trxs[interfererTrx].sectorID)
                            {
                                //on teste si la contraite de separation co-secteur est respect�!!
                                if (abs (interfererFrequency-victimFrequency1)<3 )//contrainte co secteur viol�e
                                {
                                    cost->at(i) = cost->at(i) + 1.0;
                                }
                            }// secteur different
                            else
                            {
                                if(afpProblem->trxs[victimTrx1].siteID  == afpProblem->trxs[interfererTrx].siteID)
                                {
                        //on teste si la contrainte de separation co-site est respect�e!!
                                    if (abs (interfererFrequency-victimFrequency1)< 2)//contrainte co secteur viol�e
                                    {
                                        cost->at(i) = cost->at(i) + 1.0;
                                    }
                                }//
                            }
                        }

                    }// for(j=0 ;j < taille ; j++)//pour chaque fr�quence probable on evalue le cout
                    //.............................................................................
                    //.............................................................................
                    // enregister les couts dans le vecteur
                  //  cout << veccost->at(i) << veccost->at(i) << endl;
                    veccost->at(i) = veccost->at(i) + solution->PIObj ;
                    cost->at(i) = cost->at(i) + solution->PSObj ;
                    paircost.push_back({veccost->at(i),cost->at(i)});
                    //...................................................................
                    solution->PlanAffect->pop_back();//on retire le couple probable apres evaluation de cout et l avoir enregistr� dans veccost
                    // cout<<"frequence ::" <<trx.AvailableFrequencies->at(i)<<", son sout veccost[i] ==="<< veccost->at(i)<<endl;
                } //fortrx.AvailableFrequencies


 //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
     //DOMINANCE
   //
                 //...................................................
                 //.....................................................
                // I . Retirer la non dominance pour chaque fr�quence
                // ....................................................
                //...................................................

                //je supose que la soluution est domiin�e et je vais tester si c est vrai

                    //+++++++++++++Laidi modifi� +++++++++++++++++++++++++++++++++++
      //je supose que la soluution est domiin�e et je vais tester si c est vrai
            int rank;
  int counter;
  int DominantScore;
  int temp = 0;
  rank = 1;
  vector < pair<int,double> > IndexesFreqsNonDominantes;
    IndexesFreqsNonDominantes.reserve(paircost.size());
    int taille=paircost.size();
    int array_rank[paircost.size()];
    counter =paircost.size();


    for (int i=0; i<paircost.size(); i++)
    {
      DominantScore=0;

	  for (int j=0; j<paircost.size(); j++)
	  {
        if (i!=j)
        {


                           /* if (!((paircost[i].first <= paircost[j].first) && (paircost[i].second < paircost[j].second)))
                             DominantScore   = DominantScore +   1;*/
                            if (!((paircost[i].second <= paircost[j].second) && (paircost[i].first <paircost[j].first)))
                             DominantScore   = DominantScore +   1;
        }//i!=j
       } //fin j
		if (DominantScore==0)
        {
          // indices.push_back(i); // pour sauvgarder les indices des solution non dominées dans la nouvelle population
           IndexesFreqsNonDominantes.push_back({i,paircost[i].second});
        }
	}//fin i



              if (IndexesFreqsNonDominantes.size()!= 0)
              {
                  //cout << " la taille du vect solutions non dom PS == " << IndexesFreqsNonDominantes.size()<< endl;
                 // sort(IndexesFreqsNonDominantes.begin(),IndexesFreqsNonDominantes.end(),my_cmpInfDoublePair);//trier selon un ordre croissant de cout
                sort(IndexesFreqsNonDominantes.begin(),IndexesFreqsNonDominantes.end(),my_cmpInfDoublePair);
                //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                //~~~~~~~~~~~~~~~~~~~~~~~~~~~si plusieurs fr�queences  non domlinates ont le meme cout on choisit
                // al�atoirement une
                //---------------------------------------------------
                i = 0;     k = 0 ;
                //------------------------------------
                for(i = 0 ; i < IndexesFreqsNonDominantes.size(); i++)
                {
                    //double val = IndexesFreqsNonDominantes.at(i).second;
                    double val = IndexesFreqsNonDominantes.at(i).second;
                    //pair<int,double> pnextval;
                    pair<int,double> pnextval;
                    if((i+1) < IndexesFreqsNonDominantes.size())
                    {
                        pnextval = IndexesFreqsNonDominantes.at(i+1);
                        //double nextval = pnextval.second;
                        double nextval = pnextval.second;
                        // on copie les valeurs egales dans un tableau
                        //cout<< "hiiii here " << endl;
                        if( val == nextval )
                        {
                            k = k +1 ;//k contient le nombre de valeur �gale
                        }
                        else
                        {
                            i = IndexesFreqsNonDominantes.size();
                        }
                    }
                }
                int indice ;
              //  indice = rand() % (k+1);// coisir une parmi les "n" premier
               // indexmin = IndexesFreqsNonDominantes.at(indice).first;// r�cup�ration de l'indice de la fr�quence
               // cout << "k ������������������" << k << endl;

            vector< pair < int, double > > VectHV;

            VectHV.reserve(k+1);
            int indicefreq;
            indicefreq = IndexesFreqsNonDominantes.at(0).first;
             pair<double,double> Min;
            pair<double,double> Max;
            pair < double, double > R;// est le point de r�f�rence ; la valeur max (normalis�)
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
    Normalize(paircost,Min,Max);
    for(i=0; i<= k; i++)
    {
        int valindice = IndexesFreqsNonDominantes.at(i).first;
        double X = paircost.at(valindice).first ;
        double Y = paircost.at(valindice).second ;
        double ValHV = (R.first - X)* (R.second - Y);
        VectHV.push_back({valindice,ValHV});
    }

    //**********************************************************

            sort(VectHV.begin(),VectHV.end(),my_cmpSupDoublePair);
            indexmin = VectHV.front().first;// r�cup�ration de l'indice de la fr�quence













              }
               else// il n y a aucune valeur dans le front pareto
               {
                 //cout << " taille 0000000000000000 " << endl;
                 // vecmin(cost, indexmin);//indexmin:indice de la fr�quencence qui a la valeur minimale
                 StrategyFreq = 2;//3 : ecart, 6: hv , 2 : minimum cost
                 PSChooseFrequency(instance,StrategyFreq,trx,f,solution,afpProblem);
                 return;

               }
    //............................End dominance ......................................
    //................................................................................
    //................................................................................
    f=trx.AvailableFrequencies->at(indexmin);//indice de la fr�quence recherch�
    solution->PIObj = veccost->at(indexmin);
    solution->PSObj = cost->at(indexmin);
    //delete(tempsol->PlanAffect);
    vector < pair<double,double> > ().swap(paircost) ;
    vector < pair<int,double> > ().swap(IndexesFreqsNonDominantes);
    delete(veccost);
    delete(cost);
    //delete(tempsol->PlanAffect);
    delete(solution->PlanAffect);
    //--------------------- dominance available
    }//if (taille >1)
    else
    {
       if(taille==1) // la taille  == 1; je n ai qu'un choix
        {
            f=trx.AvailableFrequencies->at(0);
            // cout<<" frequency choisit:lorsque la taille est 0"<<f<<endl;
            // cout<<"hii"<<endl;
            delete(solution->PlanAffect);
        }
    }//taille :.!=1
 }// Availablefrequencies is empty()
else//Availablefrequencies==empty() // aucune fr�quence n'est diponible j'utilise les fr�quence valides
        {// on choisit la meilleur fr�quence VALID

            //****************#################################""
        //----------------------
        if(trx.validFrequencies->empty()==false)
        {
            taille =trx.validFrequencies->size();
            vector<double> * veccost = new vector <double>(taille);
                vector<double> * cost = new vector <double>(taille);
            if (taille>1)
            {
                for(i=0 ;i < taille ; i++)//pour chaque fr�quence probable on evalue le cout
                {
                    victimFrequency =trx.validFrequencies->at(i);
                     veccost->at(i)=0.0;
                    cost->at(i)=0.0;
                    solution->PlanAffect->push_back({trx.trxID,victimFrequency});
                    //on �value la solution avec le nouveau couple : {victimTrx,victimFrequency}
                   int victimTrx1 = trx.trxID; int victimFrequency1 = trx.AvailableFrequencies->at(i);
                    for(j=0;j< solution->PlanAffect->size();j++)
                    {

                        victimTrx = solution->PlanAffect->at(j).first;
                        victimFrequency = solution->PlanAffect->at(j).second;
                       interfererTrx = solution->PlanAffect->at(j).first;
                        interfererFrequency = solution->PlanAffect->at(j).second;
                        if ( interfererTrx != victimTrx1)
                        {
                           // calculer le cout d interference
                            veccost->at(i)  = veccost->at(i)  + afpProblem->computeChannelInterference(victimFrequency1 ,interfererFrequency, victimTrx1, interfererTrx)+
                            afpProblem->computeChannelInterference(interfererFrequency,victimFrequency1 ,interfererTrx, victimTrx1);
                            //cout de separation
                           if(afpProblem->trxs[victimTrx1].sectorID == afpProblem->trxs[interfererTrx].sectorID)
                            {
                                //on teste si la contraite de separation co-secteur est respect�!!
                                if (abs (interfererFrequency-victimFrequency1)<3 )//contrainte co secteur viol�e
                                {
                                    cost->at(i) = cost->at(i) + 1.0;
                                }
                            }// secteur different
                            else
                            {
                                if(afpProblem->trxs[victimTrx1].siteID  == afpProblem->trxs[interfererTrx].siteID)
                                {
                        //on teste si la contrainte de separation co-site est respect�e!!
                                    if (abs (interfererFrequency-victimFrequency1)< 2)//contrainte co secteur viol�e
                                    {
                                        cost->at(i) = cost->at(i) + 1.0;
                                    }
                                }//
                            }
                        }

                    }// for(j=0 ;j < taille ; j++)//pour chaque fr�quence probable on evalue le cout
                    //.............................................................................
                    //.............................................................................
                    // enregister les couts dans le vecteur
                  //  cout << veccost->at(i) << veccost->at(i) << endl;
                    veccost->at(i) = veccost->at(i) + solution->PIObj ;
                    cost->at(i) = cost->at(i) + solution->PSObj ;
                    paircost.push_back({veccost->at(i),cost->at(i)});
                    //...................................................................
                    solution->PlanAffect->pop_back();//on retire le couple probable apres evaluation de cout et l avoir enregistr� dans veccost
                    // cout<<"frequence ::" <<trx.AvailableFrequencies->at(i)<<", son sout veccost[i] ==="<< veccost->at(i)<<endl;
                } //fortrx.Av
          //..............................................................
                //...................................................................................

        //DOMINANCE


                 //...................................................
                 //.....................................................
                // I . Retirer la non dominance pour chaque fr�quence
                // ....................................................
                //...................................................

                 int  DominantScore;

                vector < pair<int,int> > IndexesFreqsNonDominantes;
                 //(int,int) :: le premier enregistre l index de la fr�quence non dominante
                  //(int,int) :: le dexieme , combien de fois la fr�quence est non dominante
                IndexesFreqsNonDominantes.reserve(trx.validFrequencies->size());
        //+++++++++++++Laidi modifi� +++++++++++++++++++++++++++++++++++
          for( i = 0; i < trx.AvailableFrequencies->size();i++)//la solution condidate est dans l indice i
                {

                  DominantScore = 0 ;// pour compter le nombre de solution qui domine la solution courante

                  for( j = i+1; j < trx.AvailableFrequencies->size() ;j++)
                   {
                       if (i!=j)
                       {

                           if (paircost[i].first > paircost[j].first) // on teste la dominance par rapport au premier objectif
                            {
                                // on ne peut pas juger on test par rapport au deuxime obj
                                if (paircost[i].second > paircost[j].second)
                                         {

                                                  //on est sur qu elle est dominante
                                                DominantScore    =   DominantScore+1 ;


                                         }
                                         else
                                         {
                                             if(paircost[i].first >= paircost[j].first)
                                              {
                                                    DominantScore    =   DominantScore+1 ;
                                              }
                                         }

                            }
                            else
                            {
                                if (paircost[i].second >= paircost[j].second)
                                    {
                                        DominantScore    =   DominantScore+1 ;
                                    }

                            }


                        }//i!=j
                    }//fin j

						if (DominantScore==0)// pour s'assurer que la solution "i" est non dominée
                      {
                        IndexesFreqsNonDominantes.push_back({i,paircost[i].first});// on insert l'index de la solution et son cout d'interférences
                      }
                       // cout << "la solution " << i << " est dominee par  " << DominantScore << " autres solutions" << endl;
                }//fin i

            //cout <<"IndexesFreqsNonDominantes.size()PIII  "<< IndexesFreqsNonDominantes.size() <<endl;*/
                //----------------------------------------------------------------------
                 //+++++++++++++ sol par sol +++++++++++++++++++++++++++++++++++
                 //++++++++++++++++++ tout les sol
                  int  nondominancescore;
                  //cout << "trx.AvailableFrequencies->size()++++ "<< trx.AvailableFrequencies->size() <<endl;

                      for( i = 0; i < trx.validFrequencies->size();i++)//la solution condidate est dans l indice i
                {

                  nondominancescore = 0 ;// pour compter le nombre de solution qui domine la solution courante

                   for( j = 0; j < trx.AvailableFrequencies->size() ;j++)
                   {

                       if (i!=j)
                       {

                                   if (paircost[i].first <= paircost[j].first)  // on teste la dominance par rapport au deuciÃ¨me objectif
                                    {
                                          if (paircost[i].second < paircost[j].second)

                                        {
                                            IndexesFreqsNonDominantes.push_back({i,paircost[i].first});

                                            nondominancescore = nondominancescore + 1;
                                            }
                                        }


                                    //--- j insere le deuxi�me obj
                                  /* else
                                    {
                                         if (paircost[i].second <= paircost[j].second) // teste la dominance par rapport au deuciÃ¨me objectif
                                        {
                                                if (paircost[i].first < paircost[j].first) // on
                                                {
                                                    IndexesFreqsNonDominantes.push_back({i,paircost[i].first});
                                            //au deuxieme obj

                                                nondominancescore = nondominancescore+1;
                                                }
                                            //}
                                        }
                                    }*/

                       }//i!=j
                   }//fin j
                   /*  if (nondominancescore > (trx.AvailableFrequencies->size() - 2 ))
                  IndexesFreqsNonDominantes.push_back({i,paircost[i].first});*/

              }//fin i
            // cout <<"IndexesFreqsNonDominantes.size()PIII  "<< IndexesFreqsNonDominantes.size() <<endl;



                //...................................................
                 //.....................................................
                // II . Trier le tableau de la non dominance selon un ordre croissant si la liste n est pas vide
                // ....................................................
                //...................................................
              //  sort(IndexesFreqsNonDominantes.begin(),IndexesFreqsNonDominantes.end(),my_cmp);
             // cout << "  IndexesFreqsNonDominantes.size() ****"<< IndexesFreqsNonDominantes.size() << endl;


                // copier les solution trouver dans un vecteur avec son cout d interferqunce qui
                if (IndexesFreqsNonDominantes.size()!= 0 )
                {
                    /*vector < pair < int, double> > NonDominanteCost;
                    NonDominanteCost.reserve(IndexesFreqsNonDominantes.size());
                    for(i = 0; i < IndexesFreqsNonDominantes.size(); i++ )
                    {
                        NonDominanteCost.push_back({IndexesFreqsNonDominantes[i].first, paircost[IndexesFreqsNonDominantes[i].first].first });
                    }*/
                // trier le tableau selon un ordre d�croisant du cout et retirer la premi�re valeur
                    sort(IndexesFreqsNonDominantes.begin(),IndexesFreqsNonDominantes.end(),my_cmpInfDoublePair);
                   // indexmin = IndexesFreqsNonDominantes.front().first;
                   //si des valeur de cout �gale on choisit al�atoirement parmi ces valeur
                   //+++++++++++++++++++++++++++++++++++++++++++
                   k=0;
                   for(i = 0 ; i < IndexesFreqsNonDominantes.size(); i++)
                    {
                        double val = IndexesFreqsNonDominantes.at(i).second;
                        pair<int,double> pnextval;
                        if((i+1) < IndexesFreqsNonDominantes.size())
                        {
                            pnextval = IndexesFreqsNonDominantes.at(i+1);
                            double nextval = pnextval.second;
                            // on copie les valeurs egales dans un tableau
                            //cout<< "hiiii here " << endl;
                            if( val == nextval )
                            {
                                k = k +1 ;//k contient le nombre de valeur �gale
                                // cout<< "hiiii here " << endl;
                            }
                            else
                            {
                                i = IndexesFreqsNonDominantes.size();
                            }
                        }
                    }
    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                    int indexf = rand() % (k+1);
                    indexmin = IndexesFreqsNonDominantes.at(indexf).first;

                }
                else
                {
                     vecmin(veccost, indexmin);//indexmin:indice de la fr�quencence qui a la valeur minimale
                }

                //................................................................................

//--------------------- dominance available
                //..............................................................
                //...................................................................................

    //vider la m�moire--vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
    vector < pair<double,double>  >().swap(paircost) ;
    delete(veccost);
    delete(solution->PlanAffect);
                //..............................................................
                //...................................................................................
                f=trx.validFrequencies->at(indexmin);//indice de la fr�quence ayant un cout minimal,

    //+++++++++++++++++++++++++++++++

            }//taille >1
            else
            {
                if(taille==1)
                {
                    f=trx.validFrequencies->at(0);
                // cout<<" frequency choisit:lorsque la taille est 0"<<f<<endl;
                // cout<<"hii"<<endl;
                }
            }//taille == 1?!!
        }
        else//Availablefrequencies==empty()
        {
            cout<<" la liste des fr�quences valide est vide **"<<endl;
        }
















            //******************
            //cout<<" la liste des fr�quences disponibles est vide **"<<endl;
        }
    break;
    }//case 502 : best frequency Front pareto inspir� Plus grand HV

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   case  +52 ://strategy 5 choisir la meilleur fr�quence en terme Front parteo pure
    {
          int i,indexmin,j,k;
       // Individual * tempsol =  new Individual();
        int tempfreq;
        //��������������������������������� copier la solution dans tempsol ����������������������
        //���������������������������������������������������������������������������������������
        //tempsol = solution;
        //tempsol->plan = new vector <int>(solution->plan->size());
        //tempsol->planCC = new vector <double>(solution->planCC->size());
        solution->PlanAffect = new vector< pair<int,int> > ();
        // tempsol->PIObj = solution->PIObj;
        // tempsol->PSObj = solution->PSObj;
        for(i=0;i<solution->plan->size();i++)
        {
            //tempsol->plan->at(i) = solution->plan->at(i);
            //tempsol->planCC->at(i) = solution->planCC->at(i);
           // tempsol->PIObj = solution->PIObj;
            //tempsol->PSObj = solution->PSObj;
            if(solution->plan->at(i)!=-1)//si la case dans le plan n'est pas vide on remplie le planAffect
            {
                solution->PlanAffect->push_back({i,solution->plan->at(i)});
            }
        }

        //����������������������������������������������������������
        //���������������������������������������������������������������
        //   tempsol->planCC=NULL;
        //LF comment: on traverse tte les fr�quence et on calcule le cout
        int victimFrequency,interfererFrequency;
        int victimTrx,interfererTrx;
        victimTrx = trx.trxID;

        int taille;
        //..........................................................
        //..........................................................
        //vecteur pour enregistrer le couple de cout  interference, separation � la fois
        vector < pair<double,double>  > paircost ;
        //----------------------
        if(trx.AvailableFrequencies->empty()==false)
        {
           taille =trx.AvailableFrequencies->size();

            vector<double> * veccost = new vector <double>(taille);
                 vector<double> * cost = new vector <double>(taille);
            if (taille>1)
            {
                for(i=0 ;i < taille ; i++)//pour chaque fr�quence probable on evalue le cout
                {

                    victimFrequency =trx.AvailableFrequencies->at(i);
                    veccost->at(i)=0.0;
                    cost->at(i)=0.0;
                    solution->PlanAffect->push_back({trx.trxID,victimFrequency});
                    //on �value la solution avec le nouveau couple : {victimTrx,victimFrequency}
                   int victimTrx1 = trx.trxID; int victimFrequency1 = trx.AvailableFrequencies->at(i);
                    for(j=0;j< solution->PlanAffect->size();j++)
                    {

                        victimTrx = solution->PlanAffect->at(j).first;
                        victimFrequency = solution->PlanAffect->at(j).second;
                       interfererTrx = solution->PlanAffect->at(j).first;
                        interfererFrequency = solution->PlanAffect->at(j).second;
                        if ( interfererTrx != victimTrx1)
                        {
                           // calculer le cout d interference
                            veccost->at(i)  = veccost->at(i)  + afpProblem->computeChannelInterference(victimFrequency1 ,interfererFrequency, victimTrx1, interfererTrx)+
                            afpProblem->computeChannelInterference(interfererFrequency,victimFrequency1 ,interfererTrx, victimTrx1);
                            //cout de separation
                           if(afpProblem->trxs[victimTrx1].sectorID == afpProblem->trxs[interfererTrx].sectorID)
                            {
                                //on teste si la contraite de separation co-secteur est respect�!!
                                if (abs (interfererFrequency-victimFrequency1)<3 )//contrainte co secteur viol�e
                                {
                                    cost->at(i) = cost->at(i) + 1.0;
                                }
                            }// secteur different
                            else
                            {
                                if(afpProblem->trxs[victimTrx1].siteID  == afpProblem->trxs[interfererTrx].siteID)
                                {
                        //on teste si la contrainte de separation co-site est respect�e!!
                                    if (abs (interfererFrequency-victimFrequency1)< 2)//contrainte co secteur viol�e
                                    {
                                        cost->at(i) = cost->at(i) + 1.0;
                                    }
                                }//
                            }
                        }

                    }// for(j=0 ;j < taille ; j++)//pour chaque fr�quence probable on evalue le cout
                    //.............................................................................
                    //.............................................................................
                    // enregister les couts dans le vecteur
                  //  cout << veccost->at(i) << veccost->at(i) << endl;
                    veccost->at(i) = veccost->at(i) + solution->PIObj ;
                    cost->at(i) = cost->at(i) + solution->PSObj ;
                    paircost.push_back({veccost->at(i),cost->at(i)});
                    //...................................................................
                    solution->PlanAffect->pop_back();//on retire le couple probable apres evaluation de cout et l avoir enregistr� dans veccost
                    // cout<<"frequence ::" <<trx.AvailableFrequencies->at(i)<<", son sout veccost[i] ==="<< veccost->at(i)<<endl;
                } //fortrx.AvailableFrequencies


 //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
     //DOMINANCE
   //
                 //...................................................
                 //.....................................................
                // I . Retirer la non dominance pour chaque fr�quence
                // ....................................................
                //...................................................

                //je supose que la soluution est domiin�e et je vais tester si c est vrai

                    //+++++++++++++Laidi modifi� +++++++++++++++++++++++++++++++++++
      //je supose que la soluution est domiin�e et je vais tester si c est vrai
                int  NonDominantScore, DominantScore;

                vector < pair<int,int> > IndexesFreqsNonDominantes;
                int flag1, flag2, index;
                double interCost;
                 //(int,int) :: le premier enregistre l index de la fr�quence non dominante
                  //(int,int) :: le dexieme , combien de fois la fr�quence est non dominante
                IndexesFreqsNonDominantes.reserve(trx.AvailableFrequencies->size());

                for( i = 0; i < trx.AvailableFrequencies->size();i++)//la solution condidate est dans l indice i
                {

                  DominantScore = 0 ;// pour compter le nombre de solution qui domine la solution courante

                   for( j = 0; j < trx.AvailableFrequencies->size();j++)
                   {
                        //Laidi ---

                                /*
                               flag1 = 0;
                               flag2 = 0;
                               if (paircost[i].first >= paircost[j].first)
                                flag1++;

                               if (paircost[i].first > paircost[j].first)
                                flag2++;

                               if (paircost[i].second >= paircost[j].second)
                                flag1++;

                               if (paircost[i].second > paircost[j].second)
                                flag2++;


                          if (flag1 >= 2 && flag2>=1){ //pour tester la condition de dominance pour nos deux objectifs
          //array_domination_count[i] = array_domination_count[i] + 1; // lpour compter le nbr de solution qui domine la solution i
                              DominantScore= DominantScore+1; //pour la solution 'i'
                           }

                        */
                             /*if (paircost[i].first > paircost[j].first)
                                   {
                                      if (paircost[i].second >= paircost[j].second)
                                       DominantScore   = DominantScore +   1; //pour la solution 'i'
                                   }


                                    if (paircost[i].second > paircost[j].second)
                                        {
                                            if(paircost[i].first >= paircost[j].first)
                                            DominantScore   = DominantScore +   1; //pour la solution 'i'
                                        }*/
                                        if(i!=j)
                                       {


                         if ((!((paircost[i].first <= paircost[j].first) && (paircost[i].second < paircost[j].second)))
                            && (!((paircost[i].second <= paircost[j].second) && (paircost[i].first <paircost[j].first))))
                             DominantScore   = DominantScore +   1;
                        /* if (!((paircost[i].second <= paircost[j].second) && (paircost[i].first <paircost[j].first)))
                             DominantScore   = DominantScore +   1;*/
                                       }


                 }

                     /* if (DominantScore == 0)
                  IndexesFreqsNonDominantes.push_back({i,paircost[i].second}); // contient l'indice de la fr�quence frqq ainsi que le cout d'interf�rences
                */
                //j ins�re pour chque solution f son score
                 IndexesFreqsNonDominantes.push_back({i,DominantScore});
                }//fin i
               // cout << " la taille des frqs non dominee PI == " << IndexesFreqsNonDominantes.size() << endl ;
                //+++++++++++++++++++++++++++++++++++++++Afficher paircost

           //++++++++++++++++++++++++++++++++++++++++++++++++++++++++

                //...................................................
                 //.....................................................
                // II . Trier le tableau de la non dominance selon un ordre croissant
                // ....................................................
                //...................................................
              //  sort(IndexesFreqsNonDominantes.begin(),IndexesFreqsNonDominantes.end(),my_cmp);
              //  cout << "  IndexesFreqsNonDominantes.size() ****"<< IndexesFreqsNonDominantes.size() << endl;


                // copier les solution trouver dans un vecteur avec son cout d interferqunce qui
               /* vector < pair < int, double> > NonDominanteCost;//contient l indice des valeur non domin�e et le cout
                NonDominanteCost.reserve(IndexesFreqsNonDominantes.size());
                for(i = 0; i < IndexesFreqsNonDominantes.size(); i++ )
                {
                    NonDominanteCost.push_back({IndexesFreqsNonDominantes[i].first, paircost[IndexesFreqsNonDominantes[i].first].first });
                }*/
                // trier le tableau selon un ordre d�croisant du cout et retirer la premi�re valeur
              // cout << " ���������IndexesFreqsNonDominantes.size() " << IndexesFreqsNonDominantes.size() <<endl;

              if (IndexesFreqsNonDominantes.size()!= 0)
              {
                  //cout << " la taille du vect solutions non dom PS == " << IndexesFreqsNonDominantes.size()<< endl;
                 // sort(IndexesFreqsNonDominantes.begin(),IndexesFreqsNonDominantes.end(),my_cmpInfDoublePair);//trier selon un ordre croissant de cout
                sort(IndexesFreqsNonDominantes.begin(),IndexesFreqsNonDominantes.end(),my_cmpInf);
                //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                //~~~~~~~~~~~~~~~~~~~~~~~~~~~si plusieurs fr�queences  non domlinates ont le meme cout on choisit
                // al�atoirement une
                //---------------------------------------------------
                i = 0;     k = 0 ;
                for(i = 0 ; i < IndexesFreqsNonDominantes.size(); i++)
                {
                    //double val = IndexesFreqsNonDominantes.at(i).second;
                    int val = IndexesFreqsNonDominantes.at(i).second;
                    //pair<int,double> pnextval;
                    pair<int,int> pnextval;
                    if((i+1) < IndexesFreqsNonDominantes.size())
                    {
                        pnextval = IndexesFreqsNonDominantes.at(i+1);
                        //double nextval = pnextval.second;
                        int nextval = pnextval.second;
                        // on copie les valeurs egales dans un tableau
                        //cout<< "hiiii here " << endl;
                        if( val == nextval )
                        {
                            k = k +1 ;//k contient le nombre de valeur �gale
                            // cout<< "hiiii here " << endl;

                        }
                        else
                        {
                            i = IndexesFreqsNonDominantes.size();
                        }
                    }
                }
                //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                int indice ;
                indice = rand() % (k+1);// coisir une parmi les "n" premier
              //  cout << " k �����������" << k << endl;
                indexmin = IndexesFreqsNonDominantes.at(indice).first;// r�cup�ration de l'indice de la fr�quence
              }
               else// il n y a aucune valeur dans le front pareto
                {
                        cout << " taille 0000000000000000 " << endl;
                         vecmin(cost, indexmin);//indexmin:indice de la fr�quencence qui a la valeur minimale


            }


    //............................End dominance ..................................
    //..............................................................
    //................................................................................
    f=trx.AvailableFrequencies->at(indexmin);//indice de la fr�quence recherch�
    solution->PIObj = veccost->at(indexmin);
    solution->PSObj = cost->at(indexmin);
    solution->planCC->at(trx.trxID).first = solution->PIObj;
    solution->planCC->at(trx.trxID).second = solution->PSObj;
      //delete(tempsol->PlanAffect);
       vector < pair<double,double>  >().swap(paircost) ;
    vector < pair<int,int> > ().swap(IndexesFreqsNonDominantes);
    delete(veccost);
    delete(cost);
    //delete(tempsol->PlanAffect);
    delete(solution->PlanAffect);
    //--------------------- dominance available
    }//if (taille >1)
    else
    {
       if(taille==1) // la taille  == 1; je n ai qu'un choix
        {
            f=trx.AvailableFrequencies->at(0);
            // cout<<" frequency choisit:lorsque la taille est 0"<<f<<endl;
            // cout<<"hii"<<endl;
            delete(solution->PlanAffect);
        }
    }//taille :.!=1
 }// Availablefrequencies is empty()
else//Availablefrequencies==empty() // aucune fr�quence n'est diponible j'utilise les fr�quence valides
        {// on choisit la meilleur fr�quence VALID

            //****************#################################""
        //----------------------
        if(trx.validFrequencies->empty()==false)
        {
            taille =trx.validFrequencies->size();
            vector<double> * veccost = new vector <double>(taille);
                vector<double> * cost = new vector <double>(taille);
            if (taille>1)
            {
                for(i=0 ;i < taille ; i++)//pour chaque fr�quence probable on evalue le cout
                {
                    victimFrequency =trx.validFrequencies->at(i);
                     veccost->at(i)=0.0;
                    cost->at(i)=0.0;
                    solution->PlanAffect->push_back({trx.trxID,victimFrequency});
                    //on �value la solution avec le nouveau couple : {victimTrx,victimFrequency}
                   int victimTrx1 = trx.trxID; int victimFrequency1 = trx.AvailableFrequencies->at(i);
                    for(j=0;j< solution->PlanAffect->size();j++)
                    {

                        victimTrx = solution->PlanAffect->at(j).first;
                        victimFrequency = solution->PlanAffect->at(j).second;
                       interfererTrx = solution->PlanAffect->at(j).first;
                        interfererFrequency = solution->PlanAffect->at(j).second;
                        if ( interfererTrx != victimTrx1)
                        {
                           // calculer le cout d interference
                            veccost->at(i)  = veccost->at(i)  + afpProblem->computeChannelInterference(victimFrequency1 ,interfererFrequency, victimTrx1, interfererTrx)+
                            afpProblem->computeChannelInterference(interfererFrequency,victimFrequency1 ,interfererTrx, victimTrx1);
                            //cout de separation
                           if(afpProblem->trxs[victimTrx1].sectorID == afpProblem->trxs[interfererTrx].sectorID)
                            {
                                //on teste si la contraite de separation co-secteur est respect�!!
                                if (abs (interfererFrequency-victimFrequency1)<3 )//contrainte co secteur viol�e
                                {
                                    cost->at(i) = cost->at(i) + 1.0;
                                }
                            }// secteur different
                            else
                            {
                                if(afpProblem->trxs[victimTrx1].siteID  == afpProblem->trxs[interfererTrx].siteID)
                                {
                        //on teste si la contrainte de separation co-site est respect�e!!
                                    if (abs (interfererFrequency-victimFrequency1)< 2)//contrainte co secteur viol�e
                                    {
                                        cost->at(i) = cost->at(i) + 1.0;
                                    }
                                }//
                            }
                        }

                    }// for(j=0 ;j < taille ; j++)//pour chaque fr�quence probable on evalue le cout
                    //.............................................................................
                    //.............................................................................
                    // enregister les couts dans le vecteur
                  //  cout << veccost->at(i) << veccost->at(i) << endl;
                    veccost->at(i) = veccost->at(i) + solution->PIObj ;
                    cost->at(i) = cost->at(i) + solution->PSObj ;
                    paircost.push_back({veccost->at(i),cost->at(i)});
                    //...................................................................
                    solution->PlanAffect->pop_back();//on retire le couple probable apres evaluation de cout et l avoir enregistr� dans veccost
                    // cout<<"frequence ::" <<trx.AvailableFrequencies->at(i)<<", son sout veccost[i] ==="<< veccost->at(i)<<endl;
                } //fortrx.Av
          //..............................................................
                //...................................................................................

        //DOMINANCE


                 //...................................................
                 //.....................................................
                // I . Retirer la non dominance pour chaque fr�quence
                // ....................................................
                //...................................................

                 int  DominantScore;

                vector < pair<int,int> > IndexesFreqsNonDominantes;
                 //(int,int) :: le premier enregistre l index de la fr�quence non dominante
                  //(int,int) :: le dexieme , combien de fois la fr�quence est non dominante
                IndexesFreqsNonDominantes.reserve(trx.validFrequencies->size());
        //+++++++++++++Laidi modifi� +++++++++++++++++++++++++++++++++++
          for( i = 0; i < trx.AvailableFrequencies->size();i++)//la solution condidate est dans l indice i
                {

                  DominantScore = 0 ;// pour compter le nombre de solution qui domine la solution courante

                  for( j = i+1; j < trx.AvailableFrequencies->size() ;j++)
                   {
                       if (i!=j)
                       {

                           if (paircost[i].first > paircost[j].first) // on teste la dominance par rapport au premier objectif
                            {
                                // on ne peut pas juger on test par rapport au deuxime obj
                                if (paircost[i].second > paircost[j].second)
                                         {

                                                  //on est sur qu elle est dominante
                                                DominantScore    =   DominantScore+1 ;


                                         }
                                         else
                                         {
                                             if(paircost[i].first >= paircost[j].first)
                                              {
                                                    DominantScore    =   DominantScore+1 ;
                                              }
                                         }

                            }
                            else
                            {
                                if (paircost[i].second >= paircost[j].second)
                                    {
                                        DominantScore    =   DominantScore+1 ;
                                    }

                            }


                        }//i!=j
                    }//fin j

						if (DominantScore==0)// pour s'assurer que la solution "i" est non dominée
                      {
                        IndexesFreqsNonDominantes.push_back({i,paircost[i].first});// on insert l'index de la solution et son cout d'interférences
                      }
                       // cout << "la solution " << i << " est dominee par  " << DominantScore << " autres solutions" << endl;
                }//fin i

            //cout <<"IndexesFreqsNonDominantes.size()PIII  "<< IndexesFreqsNonDominantes.size() <<endl;*/
                //----------------------------------------------------------------------
                 //+++++++++++++ sol par sol +++++++++++++++++++++++++++++++++++
                 //++++++++++++++++++ tout les sol
                  int  nondominancescore;
                  //cout << "trx.AvailableFrequencies->size()++++ "<< trx.AvailableFrequencies->size() <<endl;

                      for( i = 0; i < trx.validFrequencies->size();i++)//la solution condidate est dans l indice i
                {

                  nondominancescore = 0 ;// pour compter le nombre de solution qui domine la solution courante

                   for( j = 0; j < trx.AvailableFrequencies->size() ;j++)
                   {

                       if (i!=j)
                       {

                                   if (paircost[i].first <= paircost[j].first)  // on teste la dominance par rapport au deuciÃ¨me objectif
                                    {
                                          if (paircost[i].second < paircost[j].second)

                                        {
                                            IndexesFreqsNonDominantes.push_back({i,paircost[i].first});

                                            nondominancescore = nondominancescore + 1;
                                            }
                                        }


                                    //--- j insere le deuxi�me obj
                                  /* else
                                    {
                                         if (paircost[i].second <= paircost[j].second) // teste la dominance par rapport au deuciÃ¨me objectif
                                        {
                                                if (paircost[i].first < paircost[j].first) // on
                                                {
                                                    IndexesFreqsNonDominantes.push_back({i,paircost[i].first});
                                            //au deuxieme obj

                                                nondominancescore = nondominancescore+1;
                                                }
                                            //}
                                        }
                                    }*/

                       }//i!=j
                   }//fin j
                   /*  if (nondominancescore > (trx.AvailableFrequencies->size() - 2 ))
                  IndexesFreqsNonDominantes.push_back({i,paircost[i].first});*/

              }//fin i
            // cout <<"IndexesFreqsNonDominantes.size()PIII  "<< IndexesFreqsNonDominantes.size() <<endl;



                //...................................................
                 //.....................................................
                // II . Trier le tableau de la non dominance selon un ordre croissant si la liste n est pas vide
                // ....................................................
                //...................................................
              //  sort(IndexesFreqsNonDominantes.begin(),IndexesFreqsNonDominantes.end(),my_cmp);
             // cout << "  IndexesFreqsNonDominantes.size() ****"<< IndexesFreqsNonDominantes.size() << endl;


                // copier les solution trouver dans un vecteur avec son cout d interferqunce qui
                if (IndexesFreqsNonDominantes.size()!= 0 )
                {
                    /*vector < pair < int, double> > NonDominanteCost;
                    NonDominanteCost.reserve(IndexesFreqsNonDominantes.size());
                    for(i = 0; i < IndexesFreqsNonDominantes.size(); i++ )
                    {
                        NonDominanteCost.push_back({IndexesFreqsNonDominantes[i].first, paircost[IndexesFreqsNonDominantes[i].first].first });
                    }*/
                // trier le tableau selon un ordre d�croisant du cout et retirer la premi�re valeur
                    sort(IndexesFreqsNonDominantes.begin(),IndexesFreqsNonDominantes.end(),my_cmpInfDoublePair);
                   // indexmin = IndexesFreqsNonDominantes.front().first;
                   //si des valeur de cout �gale on choisit al�atoirement parmi ces valeur
                   //+++++++++++++++++++++++++++++++++++++++++++
                   k=0;
                   for(i = 0 ; i < IndexesFreqsNonDominantes.size(); i++)
                    {
                        double val = IndexesFreqsNonDominantes.at(i).second;
                        pair<int,double> pnextval;
                        if((i+1) < IndexesFreqsNonDominantes.size())
                        {
                            pnextval = IndexesFreqsNonDominantes.at(i+1);
                            double nextval = pnextval.second;
                            // on copie les valeurs egales dans un tableau
                            //cout<< "hiiii here " << endl;
                            if( val == nextval )
                            {
                                k = k +1 ;//k contient le nombre de valeur �gale
                                // cout<< "hiiii here " << endl;
                            }
                            else
                            {
                                i = IndexesFreqsNonDominantes.size();
                            }
                        }
                    }
    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                    int indexf = rand() % (k+1);
                    indexmin = IndexesFreqsNonDominantes.at(indexf).first;

                }
                else
                {
                     vecmin(veccost, indexmin);//indexmin:indice de la fr�quencence qui a la valeur minimale
                }

                //................................................................................

//--------------------- dominance available
                //..............................................................
                //...................................................................................

    //vider la m�moire--vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
    vector < pair<double,double>  >().swap(paircost) ;
    delete(veccost);
    delete(solution->PlanAffect);
                //..............................................................
                //...................................................................................
                f=trx.validFrequencies->at(indexmin);//indice de la fr�quence ayant un cout minimal,

    //+++++++++++++++++++++++++++++++

            }//taille >1
            else
            {
                if(taille==1)
                {
                    f=trx.validFrequencies->at(0);
                // cout<<" frequency choisit:lorsque la taille est 0"<<f<<endl;
                // cout<<"hii"<<endl;
                }
            }//taille == 1?!!
        }
        else//Availablefrequencies==empty()
        {
            cout<<" la liste des fr�quences valide est vide **"<<endl;
        }
















            //******************
            //cout<<" la liste des fr�quences disponibles est vide **"<<endl;
        }
    break;
    }//case 52  : best frequency Front pareto pure




    //**************************************************************
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ FRONt PARETO egoiste~~~~~~~~~~~~~~~~~~~~~~
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
     case  500 ://strategy 5 choisir la meilleur fr�quence en terme Front parteo inspir� al�atoire
    {
        int i,indexmin,j,k;
       // Individual * tempsol =  new Individual();
        int tempfreq;
        //��������������������������������� copier la solution dans tempsol ����������������������
        //���������������������������������������������������������������������������������������
        //tempsol = solution;
        //tempsol->plan = new vector <int>(solution->plan->size());
        //tempsol->planCC = new vector <double>(solution->planCC->size());
        solution->PlanAffect = new vector< pair<int,int> > ();
        // tempsol->PIObj = solution->PIObj;
        // tempsol->PSObj = solution->PSObj;
        for(i=0;i<solution->plan->size();i++)
        {
            //tempsol->plan->at(i) = solution->plan->at(i);
            //tempsol->planCC->at(i) = solution->planCC->at(i);
           // tempsol->PIObj = solution->PIObj;
            //tempsol->PSObj = solution->PSObj;
            if(solution->plan->at(i)!=-1)//si la case dans le plan n'est pas vide on remplie le planAffect
            {
                solution->PlanAffect->push_back({i,solution->plan->at(i)});
            }
        }

        //����������������������������������������������������������
        //���������������������������������������������������������������
        //   tempsol->planCC=NULL;
        //LF comment: on traverse tte les fr�quence et on calcule le cout
        int victimFrequency,interfererFrequency;
        int victimTrx,interfererTrx;
        victimTrx = trx.trxID;

        int taille;
        //..........................................................
        //..........................................................
        //vecteur pour enregistrer le couple de cout  interference, separation � la fois
        vector < pair<double,double>  > paircost ;
        //----------------------
        if(trx.AvailableFrequencies->empty()==false)
        {
           taille =trx.AvailableFrequencies->size();

            vector<double> * veccost = new vector <double>(taille);
                 vector<double> * cost = new vector <double>(taille);
            if (taille>1)
            {
                for(i=0 ;i < taille ; i++)//pour chaque fr�quence probable on evalue le cout
                {

                    victimFrequency =trx.AvailableFrequencies->at(i);
                    veccost->at(i)=0.0;
                    cost->at(i)=0.0;
                    solution->PlanAffect->push_back({trx.trxID,victimFrequency});
                    //on �value la solution avec le nouveau couple : {victimTrx,victimFrequency}
                   int victimTrx1 = trx.trxID; int victimFrequency1 = trx.AvailableFrequencies->at(i);
                    for(j=0;j< solution->PlanAffect->size();j++)
                    {

                        victimTrx = solution->PlanAffect->at(j).first;
                        victimFrequency = solution->PlanAffect->at(j).second;
                       interfererTrx = solution->PlanAffect->at(j).first;
                        interfererFrequency = solution->PlanAffect->at(j).second;
                        if ( interfererTrx != victimTrx1)
                        {
                           // calculer le cout d interference
                            veccost->at(i)  = veccost->at(i)  + afpProblem->computeChannelInterference(victimFrequency1 ,interfererFrequency, victimTrx1, interfererTrx)+
                            afpProblem->computeChannelInterference(interfererFrequency,victimFrequency1 ,interfererTrx, victimTrx1);
                            //cout de separation
                           if(afpProblem->trxs[victimTrx1].sectorID == afpProblem->trxs[interfererTrx].sectorID)
                            {
                                //on teste si la contraite de separation co-secteur est respect�!!
                                if (abs (interfererFrequency-victimFrequency1)<3 )//contrainte co secteur viol�e
                                {
                                    cost->at(i) = cost->at(i) + 1.0;
                                }
                            }// secteur different
                            else
                            {
                                if(afpProblem->trxs[victimTrx1].siteID  == afpProblem->trxs[interfererTrx].siteID)
                                {
                        //on teste si la contrainte de separation co-site est respect�e!!
                                    if (abs (interfererFrequency-victimFrequency1)< 2)//contrainte co secteur viol�e
                                    {
                                        cost->at(i) = cost->at(i) + 1.0;
                                    }
                                }//
                            }
                        }

                    }// for(j=0 ;j < taille ; j++)//pour chaque fr�quence probable on evalue le cout
                    //.............................................................................
                    //.............................................................................
                    // enregister les couts dans le vecteur
                  //  cout << veccost->at(i) << veccost->at(i) << endl;
                    veccost->at(i) = veccost->at(i) + solution->PIObj ;
                    cost->at(i) = cost->at(i) + solution->PSObj ;
                    paircost.push_back({veccost->at(i),cost->at(i)});
                    //...................................................................
                    solution->PlanAffect->pop_back();//on retire le couple probable apres evaluation de cout et l avoir enregistr� dans veccost
                    // cout<<"frequence ::" <<trx.AvailableFrequencies->at(i)<<", son sout veccost[i] ==="<< veccost->at(i)<<endl;
                } //fortrx.AvailableFrequencies

    //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
     //DOMINANCE
   //
                 //je supose que la soluution est domiin�e et je vais tester si c est vrai
                int  NonDominantScore, DominantScore;

                vector < pair<int,int> > IndexesFreqsNonDominantes;
                int flag1, flag2, index;
                double interCost;
                 //(int,int) :: le premier enregistre l index de la fr�quence non dominante
                  //(int,int) :: le dexieme , combien de fois la fr�quence est non dominante
                IndexesFreqsNonDominantes.reserve(trx.AvailableFrequencies->size());

                for( i = 0; i < trx.AvailableFrequencies->size();i++)//la solution condidate est dans l indice i
                {

                  DominantScore = 0 ;// pour compter le nombre de solution qui domine la solution courante

                   for( j = 0; j < trx.AvailableFrequencies->size();j++)
                   {

                        if(i!=j)
                        {

                           /* if (!((paircost[i].first <= paircost[j].first) && (paircost[i].second < paircost[j].second)))
                             DominantScore   = DominantScore +   1;*/
                            if (!((paircost[i].second <= paircost[j].second) && (paircost[i].first <paircost[j].first)))
                             DominantScore   = DominantScore +   1;

                        }
                    }

                     /* if (DominantScore == 0)
                  IndexesFreqsNonDominantes.push_back({i,paircost[i].second}); // contient l'indice de la fr�quence frqq ainsi que le cout d'interf�rences
                */
                //j ins�re pour chque solution f son score
                 IndexesFreqsNonDominantes.push_back({i,DominantScore});
                }//fin i
               // cout << " la taille des frqs non dominee PI == " << IndexesFreqsNonDominantes.size() << endl ;
                //+++++++++++++++++++++++++++++++++++++++Afficher paircost

           //++++++++++++++++++++++++++++++++++++++++++++++++++++++++

                //...................................................
                 //.....................................................
                // II . Trier le tableau de la non dominance selon un ordre croissant
                // ....................................................
                //...................................................
              //  sort(IndexesFreqsNonDominantes.begin(),IndexesFreqsNonDominantes.end(),my_cmp);
              //  cout << "  IndexesFreqsNonDominantes.size() ****"<< IndexesFreqsNonDominantes.size() << endl;


                // copier les solution trouver dans un vecteur avec son cout d interferqunce qui
               /* vector < pair < int, double> > NonDominanteCost;//contient l indice des valeur non domin�e et le cout
                NonDominanteCost.reserve(IndexesFreqsNonDominantes.size());
                for(i = 0; i < IndexesFreqsNonDominantes.size(); i++ )
                {
                    NonDominanteCost.push_back({IndexesFreqsNonDominantes[i].first, paircost[IndexesFreqsNonDominantes[i].first].first });
                }*/
                // trier le tableau selon un ordre d�croisant du cout et retirer la premi�re valeur
              // cout << " ���������IndexesFreqsNonDominantes.size() " << IndexesFreqsNonDominantes.size() <<endl;

              if (IndexesFreqsNonDominantes.size()!= 0)
              {
                  //cout << " la taille du vect solutions non dom PS == " << IndexesFreqsNonDominantes.size()<< endl;
                 // sort(IndexesFreqsNonDominantes.begin(),IndexesFreqsNonDominantes.end(),my_cmpInfDoublePair);//trier selon un ordre croissant de cout
                sort(IndexesFreqsNonDominantes.begin(),IndexesFreqsNonDominantes.end(),my_cmpInf);
                //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                //~~~~~~~~~~~~~~~~~~~~~~~~~~~si plusieurs fr�queences  non domlinates ont le meme cout on choisit
                // al�atoirement une
                //---------------------------------------------------
                i = 0;     k = 0 ;
                for(i = 0 ; i < IndexesFreqsNonDominantes.size(); i++)
                {
                    //double val = IndexesFreqsNonDominantes.at(i).second;
                    int val = IndexesFreqsNonDominantes.at(i).second;
                    //pair<int,double> pnextval;
                    pair<int,int> pnextval;
                    if((i+1) < IndexesFreqsNonDominantes.size())
                    {
                        pnextval = IndexesFreqsNonDominantes.at(i+1);
                        //double nextval = pnextval.second;
                        int nextval = pnextval.second;
                        // on copie les valeurs egales dans un tableau
                        //cout<< "hiiii here " << endl;
                        if( val == nextval )
                        {
                            k = k +1 ;//k contient le nombre de valeur �gale
                            // cout<< "hiiii here " << endl;

                        }
                        else
                        {
                            i = IndexesFreqsNonDominantes.size();
                        }
                    }
                }
                //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                int indice ;
                indice = rand() % (k+1);// coisir une parmi les "n" premier
                   //cout << " k �����������" << k << endl;
                indexmin = IndexesFreqsNonDominantes.at(indice).first;// r�cup�ration de l'indice de la fr�quence
              }
               else// il n y a aucune valeur dans le front pareto
                {
                        cout << " taille 000000000000000" << endl;
                        vecmin(veccost, indexmin);//indexmin:indice de la fr�quencence qui a la valeur minimale

            }


    f=trx.AvailableFrequencies->at(indexmin);//indice de la fr�quence recherch�
    //cout <<"fff " << f<<endl;
      solution->PIObj = veccost->at(indexmin);
     solution->PSObj = cost->at(indexmin);
    //+++++++++++++++++++++++++++++++


    //++++++++++++++++++++
     //vider la m�moire--vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
    vector < pair<double,double>  >().swap(paircost) ;
    vector < pair<int,int> > ().swap(IndexesFreqsNonDominantes);
    delete(veccost);
    delete(cost);
    //delete(tempsol->PlanAffect);
    delete(solution->PlanAffect);
            //vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
    //--------------------- dominance available
    }//if (taille >1)
    else
    {
       if(taille==1) // la taille  == 1; je n ai qu'un choix
        {
            f=trx.AvailableFrequencies->at(0);
            delete(solution->PlanAffect);
            // cout<<" frequency choisit:lorsque la taille est 0"<<f<<endl;
            // cout<<"hii"<<endl;
        }
    }//taille :.!=1
 }// Availablefrequencies is empty()
else//Availablefrequencies==empty() // aucune fr�quence n'est diponible j'utilise les fr�quence valides
        {// on choisit la meilleur fr�quence VALID

            //****************#################################""
        //----------------------
        if(trx.validFrequencies->empty()==false)
        {
            taille =trx.validFrequencies->size();
            vector<double> * veccost = new vector <double>(taille);
            vector<double> * cost = new vector <double>(taille);
            if (taille>1)
            {
                for(i=0 ;i < taille ; i++)//pour chaque fr�quence probable on evalue le cout
                {
                    victimFrequency =trx.validFrequencies->at(i);
                     veccost->at(i)=0.0;
                    cost->at(i)=0.0;
                    solution->PlanAffect->push_back({trx.trxID,victimFrequency});
                    //on �value la solution avec le nouveau couple : {victimTrx,victimFrequency}
                   int victimTrx1 = trx.trxID; int victimFrequency1 = trx.AvailableFrequencies->at(i);
                    for(j=0;j< solution->PlanAffect->size();j++)
                    {

                        victimTrx = solution->PlanAffect->at(j).first;
                        victimFrequency = solution->PlanAffect->at(j).second;
                       interfererTrx = solution->PlanAffect->at(j).first;
                        interfererFrequency = solution->PlanAffect->at(j).second;
                        if ( interfererTrx != victimTrx1)
                        {
                           // calculer le cout d interference
                            veccost->at(i)  = veccost->at(i)  + afpProblem->computeChannelInterference(victimFrequency1 ,interfererFrequency, victimTrx1, interfererTrx)+
                            afpProblem->computeChannelInterference(interfererFrequency,victimFrequency1 ,interfererTrx, victimTrx1);
                            //cout de separation
                           if(afpProblem->trxs[victimTrx1].sectorID == afpProblem->trxs[interfererTrx].sectorID)
                            {
                                //on teste si la contraite de separation co-secteur est respect�!!
                                if (abs (interfererFrequency-victimFrequency1)<3 )//contrainte co secteur viol�e
                                {
                                    cost->at(i) = cost->at(i) + 1.0;
                                }
                            }// secteur different
                            else
                            {
                                if(afpProblem->trxs[victimTrx1].siteID  == afpProblem->trxs[interfererTrx].siteID)
                                {
                        //on teste si la contrainte de separation co-site est respect�e!!
                                    if (abs (interfererFrequency-victimFrequency1)< 2)//contrainte co secteur viol�e
                                    {
                                        cost->at(i) = cost->at(i) + 1.0;
                                    }
                                }//
                            }
                        }

                    }// for(j=0 ;j < taille ; j++)//pour chaque fr�quence probable on evalue le cout
                    //.............................................................................
                    //.............................................................................
                    // enregister les couts dans le vecteur
                  //  cout << veccost->at(i) << veccost->at(i) << endl;
                    veccost->at(i) = veccost->at(i) + solution->PIObj ;
                    cost->at(i) = cost->at(i) + solution->PSObj ;
                    paircost.push_back({veccost->at(i),cost->at(i)});
                    //...................................................................
                    solution->PlanAffect->pop_back();//on retire le couple probable apres evaluation de cout et l avoir enregistr� dans veccost
                    // cout<<"frequence ::" <<trx.AvailableFrequencies->at(i)<<", son sout veccost[i] ==="<< veccost->at(i)<<endl;
                } //fortrx.AvailableFrequencies

 //DOMINANCE--------------------chercher les solution dominantes et l'enregistrer dans les indexes
   //  des fr�quences dans le  tableau IndexesFreqsDominantes

               int  DominantScore;

                vector < pair<int,int> > IndexesFreqsNonDominantes;
                 //(int,int) :: le premier enregistre l index de la fr�quence non dominante
                  //(int,int) :: le dexieme , combien de fois la fr�quence est non dominante
                IndexesFreqsNonDominantes.reserve(trx.validFrequencies->size());
        //+++++++++++++Laidi modifi� +++++++++++++++++++++++++++++++++++
         /* for( i = 0; i < trx.AvailableFrequencies->size();i++)//la solution condidate est dans l indice i
                {

                  DominantScore = 0 ;// pour compter le nombre de solution qui domine la solution courante

                  for( j = 0; j < trx.AvailableFrequencies->size() ;j++)
                   {
                       if (i!=j)
                       {

                           if (paircost[i].first > paircost[j].first) // on teste la dominance par rapport au premier objectif
                            {
                                // on ne peut pas juger on test par rapport au deuxime obj
                                if (paircost[i].second > paircost[j].second)
                                         {

                                                  //on est sur qu elle est dominante
                                                DominantScore    =   DominantScore+1 ;


                                         }
                                         else
                                         {
                                             if(paircost[i].first >= paircost[j].first)
                                              {
                                                    DominantScore    =   DominantScore+1 ;
                                              }
                                         }

                            }
                            else
                            {
                                if (paircost[i].second >= paircost[j].second)
                                    {
                                        DominantScore    =   DominantScore+1 ;
                                    }

                            }


                        }//i!=j
                    }//fin j

						if (DominantScore==0)// pour s'assurer que la solution "i" est non dominée
                      {
                        IndexesFreqsNonDominantes.push_back({i,paircost[i].first});// on insert l'index de la solution et son cout d'interférences
                      }
                       // cout << "la solution " << i << " est dominee par  " << DominantScore << " autres solutions" << endl;
                }//fin i

            cout <<"IndexesFreqsNonDominantes.size()PIII  "<< IndexesFreqsNonDominantes.size() <<endl;*/
                //----------------------------------------------------------------------
                 //+++++++++++++ sol par sol +++++++++++++++++++++++++++++++++++
                 //++++++++++++++++++ tout les sol
                  int  nondominancescore;
                  //cout << "trx.AvailableFrequencies->size()++++ "<< trx.AvailableFrequencies->size() <<endl;

                      for( i = 0; i < trx.validFrequencies->size();i++)//la solution condidate est dans l indice i
                {

                  nondominancescore = 0 ;// pour compter le nombre de solution qui domine la solution courante

                   for( j = 0; j < trx.AvailableFrequencies->size() ;j++)
                   {

                       if (i!=j)
                       {

                                   if (paircost[i].first <= paircost[j].first)  // on teste la dominance par rapport au deuciÃ¨me objectif
                                    {
                                          if (paircost[i].second < paircost[j].second)

                                        {
                                            IndexesFreqsNonDominantes.push_back({i,paircost[i].first});

                                            nondominancescore = nondominancescore + 1;
                                            }
                                        }


                                    //--- j insere le deuxi�me obj
                                  /* else
                                    {
                                         if (paircost[i].second <= paircost[j].second) // teste la dominance par rapport au deuciÃ¨me objectif
                                        {
                                                if (paircost[i].first < paircost[j].first) // on
                                                {
                                                    IndexesFreqsNonDominantes.push_back({i,paircost[i].first});
                                            //au deuxieme obj

                                                nondominancescore = nondominancescore+1;
                                                }
                                            //}
                                        }
                                    }*/

                       }//i!=j
                   }//fin j
                   /*  if (nondominancescore > (trx.AvailableFrequencies->size() - 2 ))
                  IndexesFreqsNonDominantes.push_back({i,paircost[i].first});*/

              }//fin i
            // cout <<"IndexesFreqsNonDominantes.size()PIII  "<< IndexesFreqsNonDominantes.size() <<endl;



                //...................................................
                 //.....................................................
                // II . Trier le tableau de la non dominance selon un ordre croissant si la liste n est pas vide
                // ....................................................
                //...................................................
              //  sort(IndexesFreqsNonDominantes.begin(),IndexesFreqsNonDominantes.end(),my_cmp);
             // cout << "  IndexesFreqsNonDominantes.size() ****"<< IndexesFreqsNonDominantes.size() << endl;


                // copier les solution trouver dans un vecteur avec son cout d interferqunce qui
                if (IndexesFreqsNonDominantes.size()!= 0 )
                {
                    /*vector < pair < int, double> > NonDominanteCost;
                    NonDominanteCost.reserve(IndexesFreqsNonDominantes.size());
                    for(i = 0; i < IndexesFreqsNonDominantes.size(); i++ )
                    {
                        NonDominanteCost.push_back({IndexesFreqsNonDominantes[i].first, paircost[IndexesFreqsNonDominantes[i].first].first });
                    }*/
                // trier le tableau selon un ordre d�croisant du cout et retirer la premi�re valeur
                    sort(IndexesFreqsNonDominantes.begin(),IndexesFreqsNonDominantes.end(),my_cmpInfDoublePair);
                   // indexmin = IndexesFreqsNonDominantes.front().first;
                   //si des valeur de cout �gale on choisit al�atoirement parmi ces valeur
                   //+++++++++++++++++++++++++++++++++++++++++++
                   k=0;
                   for(i = 0 ; i < IndexesFreqsNonDominantes.size(); i++)
                    {
                        double val = IndexesFreqsNonDominantes.at(i).second;
                        pair<int,double> pnextval;
                        if((i+1) < IndexesFreqsNonDominantes.size())
                        {
                            pnextval = IndexesFreqsNonDominantes.at(i+1);
                            double nextval = pnextval.second;
                            // on copie les valeurs egales dans un tableau
                            //cout<< "hiiii here " << endl;
                            if( val == nextval )
                            {
                                k = k +1 ;//k contient le nombre de valeur �gale
                                // cout<< "hiiii here " << endl;
                            }
                            else
                            {
                                i = IndexesFreqsNonDominantes.size();
                            }
                        }
                    }
    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                    int indexf = rand() % (k+1);
                    indexmin = IndexesFreqsNonDominantes.at(indexf).first;

                }
                else
                {
                     vecmin(veccost, indexmin);//indexmin:indice de la fr�quencence qui a la valeur minimale
                }

                //................................................................................

//--------------------- dominance available
                //..............................................................
                //...................................................................................
                f=trx.validFrequencies->at(indexmin);//indice de la fr�quence ayant un cout minimal,
    //vider la m�moire--vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
    vector < pair<double,double>  >().swap(paircost) ;
    delete(veccost);
    delete(solution->PlanAffect);
    //vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
            }//taille >1
            else
            {
                if(taille==1)
                {
                    f=trx.validFrequencies->at(0);
                // cout<<" frequency choisit:lorsque la taille est 0"<<f<<endl;
                // cout<<"hii"<<endl;
                }
            }//taille == 1?!!
        }
        else//Availablefrequencies==empty()
        {
            cout<<" la liste des fr�quences valide est vide **"<<endl;
        }

           //******************
            //cout<<" la liste des fr�quences disponibles est vide **"<<endl;
        }
    break;
    }//case 5  : best frequency Front pareto egoiste
    //------------------------------------------------------------------------------
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ FRONt PARETO egoiste ~~~~~~~~~~~~~~~~~~~~~~
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //-------------------------------------------
    //--------------------------------------------------
 case  501 ://strategy 5 choisir la meilleur fr�quence en terme Front parteo. si plusieurs fr�quence
     //dans le meme front pareto , on choisit celle qui a le minimum ecart entre CI et CS
    {
          int i,indexmin,j,k;
       // Individual * tempsol =  new Individual();
        int tempfreq;
        //��������������������������������� copier la solution dans tempsol ����������������������
        //���������������������������������������������������������������������������������������
        //tempsol = solution;
        //tempsol->plan = new vector <int>(solution->plan->size());
        //tempsol->planCC = new vector <double>(solution->planCC->size());
        solution->PlanAffect = new vector< pair<int,int> > ();
        // tempsol->PIObj = solution->PIObj;
        // tempsol->PSObj = solution->PSObj;
        for(i=0;i<solution->plan->size();i++)
        {
            //tempsol->plan->at(i) = solution->plan->at(i);
            //tempsol->planCC->at(i) = solution->planCC->at(i);
           // tempsol->PIObj = solution->PIObj;
            //tempsol->PSObj = solution->PSObj;
            if(solution->plan->at(i)!=-1)//si la case dans le plan n'est pas vide on remplie le planAffect
            {
                solution->PlanAffect->push_back({i,solution->plan->at(i)});
            }
        }

        //����������������������������������������������������������
        //���������������������������������������������������������������
        //   tempsol->planCC=NULL;
        //LF comment: on traverse tte les fr�quence et on calcule le cout
        int victimFrequency,interfererFrequency;
        int victimTrx,interfererTrx;
        victimTrx = trx.trxID;

        int taille;
        //..........................................................
        //..........................................................
        //vecteur pour enregistrer le couple de cout  interference, separation � la fois
        vector < pair<double,double>  > paircost ;
        //----------------------
        if(trx.AvailableFrequencies->empty()==false)
        {
           taille =trx.AvailableFrequencies->size();

            vector<double> * veccost = new vector <double>(taille);
                 vector<double> * cost = new vector <double>(taille);
            if (taille>1)
            {
                for(i=0 ;i < taille ; i++)//pour chaque fr�quence probable on evalue le cout
                {

                    victimFrequency =trx.AvailableFrequencies->at(i);
                    veccost->at(i)=0.0;
                    cost->at(i)=0.0;
                    solution->PlanAffect->push_back({trx.trxID,victimFrequency});
                    //on �value la solution avec le nouveau couple : {victimTrx,victimFrequency}
                   int victimTrx1 = trx.trxID; int victimFrequency1 = trx.AvailableFrequencies->at(i);
                    for(j=0;j< solution->PlanAffect->size();j++)
                    {

                        victimTrx = solution->PlanAffect->at(j).first;
                        victimFrequency = solution->PlanAffect->at(j).second;
                       interfererTrx = solution->PlanAffect->at(j).first;
                        interfererFrequency = solution->PlanAffect->at(j).second;
                        if ( interfererTrx != victimTrx1)
                        {
                           // calculer le cout d interference
                            veccost->at(i)  = veccost->at(i)  + afpProblem->computeChannelInterference(victimFrequency1 ,interfererFrequency, victimTrx1, interfererTrx)+
                            afpProblem->computeChannelInterference(interfererFrequency,victimFrequency1 ,interfererTrx, victimTrx1);
                            //cout de separation
                           if(afpProblem->trxs[victimTrx1].sectorID == afpProblem->trxs[interfererTrx].sectorID)
                            {
                                //on teste si la contraite de separation co-secteur est respect�!!
                                if (abs (interfererFrequency-victimFrequency1)<3 )//contrainte co secteur viol�e
                                {
                                    cost->at(i) = cost->at(i) + 1.0;
                                }
                            }// secteur different
                            else
                            {
                                if(afpProblem->trxs[victimTrx1].siteID  == afpProblem->trxs[interfererTrx].siteID)
                                {
                        //on teste si la contrainte de separation co-site est respect�e!!
                                    if (abs (interfererFrequency-victimFrequency1)< 2)//contrainte co secteur viol�e
                                    {
                                        cost->at(i) = cost->at(i) + 1.0;
                                    }
                                }//
                            }
                        }

                    }// for(j=0 ;j < taille ; j++)//pour chaque fr�quence probable on evalue le cout
                    //.............................................................................
                    //.............................................................................
                    // enregister les couts dans le vecteur
                  //  cout << veccost->at(i) << veccost->at(i) << endl;
                    veccost->at(i) = veccost->at(i) + solution->PIObj ;
                    cost->at(i) = cost->at(i) + solution->PSObj ;
                    paircost.push_back({veccost->at(i),cost->at(i)});
                    //...................................................................
                    solution->PlanAffect->pop_back();//on retire le couple probable apres evaluation de cout et l avoir enregistr� dans veccost
                    // cout<<"frequence ::" <<trx.AvailableFrequencies->at(i)<<", son sout veccost[i] ==="<< veccost->at(i)<<endl;
                } //fortrx.AvailableFrequencies


 //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
     //DOMINANCE
   //
                 //...................................................
                 //.....................................................
                // I . Retirer la non dominance pour chaque fr�quence
                // ....................................................
                //...................................................

                //je supose que la soluution est domiin�e et je vais tester si c est vrai

                    //+++++++++++++Laidi modifi� +++++++++++++++++++++++++++++++++++
      //je supose que la soluution est domiin�e et je vais tester si c est vrai
                int  NonDominantScore, DominantScore;

                vector < pair<int,int> > IndexesFreqsNonDominantes;
                int flag1, flag2, index;
                double interCost;
                 //(int,int) :: le premier enregistre l index de la fr�quence non dominante
                  //(int,int) :: le dexieme , combien de fois la fr�quence est non dominante
                IndexesFreqsNonDominantes.reserve(trx.AvailableFrequencies->size());

                for( i = 0; i < trx.AvailableFrequencies->size();i++)//la solution condidate est dans l indice i
                {

                  DominantScore = 0 ;// pour compter le nombre de solution qui domine la solution courante

                   for( j = 0; j < trx.AvailableFrequencies->size();j++)
                   {

                                        if(i!=j)
                                       {


                        /* if (!((paircost[i].first <= paircost[j].first) && (paircost[i].second < paircost[j].second)))
                             DominantScore   = DominantScore +   1;*/
                         if (!((paircost[i].second <= paircost[j].second) && (paircost[i].first <paircost[j].first)))
                             DominantScore   = DominantScore +   1;
                                       }


                 }

                 IndexesFreqsNonDominantes.push_back({i,DominantScore});
                }//fin i
               // cout << " la taille des frqs non dominee PI == " << IndexesFreqsNonDominantes.size() << endl ;
                //+++++++++++++++++++++++++++++++++++++++Afficher paircost

           //++++++++++++++++++++++++++++++++++++++++++++++++++++++++

                //...................................................
                 //.....................................................
                // II . Trier le tableau de la non dominance selon un ordre croissant
                // ....................................................
                //...................................................
              //  sort(IndexesFreqsNonDominantes.begin(),IndexesFreqsNonDominantes.end(),my_cmp);
              //  cout << "  IndexesFreqsNonDominantes.size() ****"<< IndexesFreqsNonDominantes.size() << endl;


                // copier les solution trouver dans un vecteur avec son cout d interferqunce qui
               /* vector < pair < int, double> > NonDominanteCost;//contient l indice des valeur non domin�e et le cout
                NonDominanteCost.reserve(IndexesFreqsNonDominantes.size());
                for(i = 0; i < IndexesFreqsNonDominantes.size(); i++ )
                {
                    NonDominanteCost.push_back({IndexesFreqsNonDominantes[i].first, paircost[IndexesFreqsNonDominantes[i].first].first });
                }*/
                // trier le tableau selon un ordre d�croisant du cout et retirer la premi�re valeur
              // cout << " ���������IndexesFreqsNonDominantes.size() " << IndexesFreqsNonDominantes.size() <<endl;

              if (IndexesFreqsNonDominantes.size()!= 0)
              {
                  //cout << " la taille du vect solutions non dom PS == " << IndexesFreqsNonDominantes.size()<< endl;
                 // sort(IndexesFreqsNonDominantes.begin(),IndexesFreqsNonDominantes.end(),my_cmpInfDoublePair);//trier selon un ordre croissant de cout
                sort(IndexesFreqsNonDominantes.begin(),IndexesFreqsNonDominantes.end(),my_cmpInf);
                //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                //~~~~~~~~~~~~~~~~~~~~~~~~~~~si plusieurs fr�queences  non domlinates ont le meme cout on choisit
                // al�atoirement une
                //---------------------------------------------------
                i = 0;     k = 0 ;
                for(i = 0 ; i < IndexesFreqsNonDominantes.size(); i++)
                {
                    //double val = IndexesFreqsNonDominantes.at(i).second;
                    int val = IndexesFreqsNonDominantes.at(i).second;
                    //pair<int,double> pnextval;
                    pair<int,int> pnextval;
                    if((i+1) < IndexesFreqsNonDominantes.size())
                    {
                        pnextval = IndexesFreqsNonDominantes.at(i+1);
                        //double nextval = pnextval.second;
                        int nextval = pnextval.second;
                        // on copie les valeurs egales dans un tableau
                        //cout<< "hiiii here " << endl;
                        if( val == nextval )
                        {
                            k = k +1 ;//k contient le nombre de valeur �gale
                            // cout<< "hiiii here " << endl;

                        }
                        else
                        {
                            i = IndexesFreqsNonDominantes.size();
                        }
                    }
                }
                //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                int indice ;
            //    indice = rand() % (k+1);// coisir une parmi les "n" premier
            //cr�er un tableau des k valeurs �gales en terme de dominance score


            vector < pair< int, double> > distance;
            distance.reserve(k+1);
            int indicefreq;
            indicefreq = IndexesFreqsNonDominantes.at(0).first;
             double v = abs(veccost->at(indicefreq)- cost->at(indicefreq));
            distance.push_back({indicefreq,v});
            for(i = 1 ;i < k ; i++)
            {
                indicefreq = IndexesFreqsNonDominantes.at(i).first;
                v  =  abs(veccost->at(indicefreq)- cost->at(indicefreq));
                distance.push_back({indicefreq,v});
            }
            sort(distance.begin(),distance.end(),my_cmpInfDoublePair);








                indexmin = distance.front().first;// r�cup�ration de l'indice de la fr�quenc
              }
               else// il n y a aucune valeur dans le front pareto
                {
                        cout << " taille 0000000000000000 " << endl;
                         vecmin(cost, indexmin);//indexmin:indice de la fr�quencence qui a la valeur minimale


            }


    //............................End dominance ..................................
    //..............................................................
    //................................................................................
    f=trx.AvailableFrequencies->at(indexmin);//indice de la fr�quence recherch�
     solution->PIObj = veccost->at(indexmin);
      solution->PSObj = cost->at(indexmin);
      //delete(tempsol->PlanAffect);
       vector < pair<double,double>  >().swap(paircost) ;
    vector < pair<int,int> > ().swap(IndexesFreqsNonDominantes);
    delete(veccost);
    delete(cost);
    //delete(tempsol->PlanAffect);
    delete(solution->PlanAffect);
    //--------------------- dominance available
    }//if (taille >1)
    else
    {
       if(taille==1) // la taille  == 1; je n ai qu'un choix
        {
            f=trx.AvailableFrequencies->at(0);
            // cout<<" frequency choisit:lorsque la taille est 0"<<f<<endl;
            // cout<<"hii"<<endl;
            delete(solution->PlanAffect);
        }
    }//taille :.!=1
 }// Availablefrequencies is empty()
else//Availablefrequencies==empty() // aucune fr�quence n'est diponible j'utilise les fr�quence valides
        {// on choisit la meilleur fr�quence VALID

            //****************#################################""
        //----------------------
        if(trx.validFrequencies->empty()==false)
        {
            taille =trx.validFrequencies->size();
            vector<double> * veccost = new vector <double>(taille);
                vector<double> * cost = new vector <double>(taille);
            if (taille>1)
            {
                for(i=0 ;i < taille ; i++)//pour chaque fr�quence probable on evalue le cout
                {
                    victimFrequency =trx.validFrequencies->at(i);
                     veccost->at(i)=0.0;
                    cost->at(i)=0.0;
                    solution->PlanAffect->push_back({trx.trxID,victimFrequency});
                    //on �value la solution avec le nouveau couple : {victimTrx,victimFrequency}
                   int victimTrx1 = trx.trxID; int victimFrequency1 = trx.AvailableFrequencies->at(i);
                    for(j=0;j< solution->PlanAffect->size();j++)
                    {

                        victimTrx = solution->PlanAffect->at(j).first;
                        victimFrequency = solution->PlanAffect->at(j).second;
                       interfererTrx = solution->PlanAffect->at(j).first;
                        interfererFrequency = solution->PlanAffect->at(j).second;
                        if ( interfererTrx != victimTrx1)
                        {
                           // calculer le cout d interference
                            veccost->at(i)  = veccost->at(i)  + afpProblem->computeChannelInterference(victimFrequency1 ,interfererFrequency, victimTrx1, interfererTrx)+
                            afpProblem->computeChannelInterference(interfererFrequency,victimFrequency1 ,interfererTrx, victimTrx1);
                            //cout de separation
                           if(afpProblem->trxs[victimTrx1].sectorID == afpProblem->trxs[interfererTrx].sectorID)
                            {
                                //on teste si la contraite de separation co-secteur est respect�!!
                                if (abs (interfererFrequency-victimFrequency1)<3 )//contrainte co secteur viol�e
                                {
                                    cost->at(i) = cost->at(i) + 1.0;
                                }
                            }// secteur different
                            else
                            {
                                if(afpProblem->trxs[victimTrx1].siteID  == afpProblem->trxs[interfererTrx].siteID)
                                {
                        //on teste si la contrainte de separation co-site est respect�e!!
                                    if (abs (interfererFrequency-victimFrequency1)< 2)//contrainte co secteur viol�e
                                    {
                                        cost->at(i) = cost->at(i) + 1.0;
                                    }
                                }//
                            }
                        }

                    }// for(j=0 ;j < taille ; j++)//pour chaque fr�quence probable on evalue le cout
                    //.............................................................................
                    //.............................................................................
                    // enregister les couts dans le vecteur
                  //  cout << veccost->at(i) << veccost->at(i) << endl;
                    veccost->at(i) = veccost->at(i) + solution->PIObj ;
                    cost->at(i) = cost->at(i) + solution->PSObj ;
                    paircost.push_back({veccost->at(i),cost->at(i)});
                    //...................................................................
                    solution->PlanAffect->pop_back();//on retire le couple probable apres evaluation de cout et l avoir enregistr� dans veccost
                    // cout<<"frequence ::" <<trx.AvailableFrequencies->at(i)<<", son sout veccost[i] ==="<< veccost->at(i)<<endl;
                } //fortrx.Av
          //..............................................................
                //...................................................................................

        //DOMINANCE


                 //...................................................
                 //.....................................................
                // I . Retirer la non dominance pour chaque fr�quence
                // ....................................................
                //...................................................

                 int  DominantScore;

                vector < pair<int,int> > IndexesFreqsNonDominantes;
                 //(int,int) :: le premier enregistre l index de la fr�quence non dominante
                  //(int,int) :: le dexieme , combien de fois la fr�quence est non dominante
                IndexesFreqsNonDominantes.reserve(trx.validFrequencies->size());
        //+++++++++++++Laidi modifi� +++++++++++++++++++++++++++++++++++
          for( i = 0; i < trx.AvailableFrequencies->size();i++)//la solution condidate est dans l indice i
                {

                  DominantScore = 0 ;// pour compter le nombre de solution qui domine la solution courante

                  for( j = i+1; j < trx.AvailableFrequencies->size() ;j++)
                   {
                       if (i!=j)
                       {

                           if (paircost[i].first > paircost[j].first) // on teste la dominance par rapport au premier objectif
                            {
                                // on ne peut pas juger on test par rapport au deuxime obj
                                if (paircost[i].second > paircost[j].second)
                                         {

                                                  //on est sur qu elle est dominante
                                                DominantScore    =   DominantScore+1 ;


                                         }
                                         else
                                         {
                                             if(paircost[i].first >= paircost[j].first)
                                              {
                                                    DominantScore    =   DominantScore+1 ;
                                              }
                                         }

                            }
                            else
                            {
                                if (paircost[i].second >= paircost[j].second)
                                    {
                                        DominantScore    =   DominantScore+1 ;
                                    }

                            }


                        }//i!=j
                    }//fin j

						if (DominantScore==0)// pour s'assurer que la solution "i" est non dominée
                      {
                        IndexesFreqsNonDominantes.push_back({i,paircost[i].first});// on insert l'index de la solution et son cout d'interférences
                      }
                       // cout << "la solution " << i << " est dominee par  " << DominantScore << " autres solutions" << endl;
                }//fin i

            //cout <<"IndexesFreqsNonDominantes.size()PIII  "<< IndexesFreqsNonDominantes.size() <<endl;*/
                //----------------------------------------------------------------------
                 //+++++++++++++ sol par sol +++++++++++++++++++++++++++++++++++
                 //++++++++++++++++++ tout les sol
                  int  nondominancescore;
                  //cout << "trx.AvailableFrequencies->size()++++ "<< trx.AvailableFrequencies->size() <<endl;

                      for( i = 0; i < trx.validFrequencies->size();i++)//la solution condidate est dans l indice i
                {

                  nondominancescore = 0 ;// pour compter le nombre de solution qui domine la solution courante

                   for( j = 0; j < trx.AvailableFrequencies->size() ;j++)
                   {

                       if (i!=j)
                       {

                                   if (paircost[i].first <= paircost[j].first)  // on teste la dominance par rapport au deuciÃ¨me objectif
                                    {
                                          if (paircost[i].second < paircost[j].second)

                                        {
                                            IndexesFreqsNonDominantes.push_back({i,paircost[i].first});

                                            nondominancescore = nondominancescore + 1;
                                            }
                                        }


                                    //--- j insere le deuxi�me obj
                                  /* else
                                    {
                                         if (paircost[i].second <= paircost[j].second) // teste la dominance par rapport au deuciÃ¨me objectif
                                        {
                                                if (paircost[i].first < paircost[j].first) // on
                                                {
                                                    IndexesFreqsNonDominantes.push_back({i,paircost[i].first});
                                            //au deuxieme obj

                                                nondominancescore = nondominancescore+1;
                                                }
                                            //}
                                        }
                                    }*/

                       }//i!=j
                   }//fin j
                   /*  if (nondominancescore > (trx.AvailableFrequencies->size() - 2 ))
                  IndexesFreqsNonDominantes.push_back({i,paircost[i].first});*/

              }//fin i
            // cout <<"IndexesFreqsNonDominantes.size()PIII  "<< IndexesFreqsNonDominantes.size() <<endl;



                //...................................................
                 //.....................................................
                // II . Trier le tableau de la non dominance selon un ordre croissant si la liste n est pas vide
                // ....................................................
                //...................................................
              //  sort(IndexesFreqsNonDominantes.begin(),IndexesFreqsNonDominantes.end(),my_cmp);
             // cout << "  IndexesFreqsNonDominantes.size() ****"<< IndexesFreqsNonDominantes.size() << endl;


                // copier les solution trouver dans un vecteur avec son cout d interferqunce qui
                if (IndexesFreqsNonDominantes.size()!= 0 )
                {
                    /*vector < pair < int, double> > NonDominanteCost;
                    NonDominanteCost.reserve(IndexesFreqsNonDominantes.size());
                    for(i = 0; i < IndexesFreqsNonDominantes.size(); i++ )
                    {
                        NonDominanteCost.push_back({IndexesFreqsNonDominantes[i].first, paircost[IndexesFreqsNonDominantes[i].first].first });
                    }*/
                // trier le tableau selon un ordre d�croisant du cout et retirer la premi�re valeur
                    sort(IndexesFreqsNonDominantes.begin(),IndexesFreqsNonDominantes.end(),my_cmpInfDoublePair);
                   // indexmin = IndexesFreqsNonDominantes.front().first;
                   //si des valeur de cout �gale on choisit al�atoirement parmi ces valeur
                   //+++++++++++++++++++++++++++++++++++++++++++
                   k=0;
                   for(i = 0 ; i < IndexesFreqsNonDominantes.size(); i++)
                    {
                        double val = IndexesFreqsNonDominantes.at(i).second;
                        pair<int,double> pnextval;
                        if((i+1) < IndexesFreqsNonDominantes.size())
                        {
                            pnextval = IndexesFreqsNonDominantes.at(i+1);
                            double nextval = pnextval.second;
                            // on copie les valeurs egales dans un tableau
                            //cout<< "hiiii here " << endl;
                            if( val == nextval )
                            {
                                k = k +1 ;//k contient le nombre de valeur �gale
                                // cout<< "hiiii here " << endl;
                            }
                            else
                            {
                                i = IndexesFreqsNonDominantes.size();
                            }
                        }
                    }
    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                    int indexf = rand() % (k+1);
                    indexmin = IndexesFreqsNonDominantes.at(indexf).first;

                }
                else
                {
                     vecmin(veccost, indexmin);//indexmin:indice de la fr�quencence qui a la valeur minimale
                }

                //................................................................................

//--------------------- dominance available
                //..............................................................
                //...................................................................................

    //vider la m�moire--vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
    vector < pair<double,double>  >().swap(paircost) ;
    delete(veccost);
    delete(solution->PlanAffect);
                //..............................................................
                //...................................................................................
                f=trx.validFrequencies->at(indexmin);//indice de la fr�quence ayant un cout minimal,

    //+++++++++++++++++++++++++++++++

            }//taille >1
            else
            {
                if(taille==1)
                {
                    f=trx.validFrequencies->at(0);
                // cout<<" frequency choisit:lorsque la taille est 0"<<f<<endl;
                // cout<<"hii"<<endl;
                }
            }//taille == 1?!!
        }
        else//Availablefrequencies==empty()
        {
            cout<<" la liste des fr�quences valide est vide **"<<endl;
        }
















            //******************
            //cout<<" la liste des fr�quences disponibles est vide **"<<endl;
        }
    break;
    }//case 501  : best frequency Front pareto
    //**************************************************************
    //--------------------------------------------------

//************* appliquer l hypervolume pour choisir la meilleur fr�quence
//*********************************************
   case 6 :
    {
           int i,indexmin,j,k;
     //   Individual * tempsol =  new Individual();
        int tempfreq;
        //��������������������������������� copier la solution dans tempsol ����������������������
        //���������������������������������������������������������������������������������������
        //tempsol = solution;
        //tempsol->plan = new vector <int>(solution->plan->size());
       // tempsol->planCC = new vector <double>(solution->planCC->size());
        solution->PlanAffect = new vector< pair<int,int> > ();
        // tempsol->PIObj = solution->PIObj;
        // tempsol->PSObj = solution->PSObj;
        for(i=0;i<solution->plan->size();i++)
        {
          //  tempsol->plan->at(i) = solution->plan->at(i);
          //  tempsol->planCC->at(i) = solution->planCC->at(i);
           // tempsol->PIObj = solution->PIObj;
            //tempsol->PSObj = solution->PSObj;
            if(solution->plan->at(i)!=-1)//si la case dans le plan n'est pas vide on remplie le planAffect
            {
                solution->PlanAffect->push_back({i,solution->plan->at(i)});
            }
        }

        //����������������������������������������������������������
        //���������������������������������������������������������������
        //   tempsol->planCC=NULL;
        //LF comment: on traverse tte les fr�quence et on calcule le cout
        int victimFrequency,interfererFrequency;
        int victimTrx,interfererTrx;
        victimTrx = trx.trxID;

        int taille;
        //..........................................................
        //..........................................................
        //vecteur pour enregistrer le couple de cout  interference, separation � la fois
        vector < pair<double,double>  > paircost ;
        //----------------------
        if(trx.AvailableFrequencies->empty()==false)
        {
           taille =trx.AvailableFrequencies->size();

            vector<double> * veccost = new vector <double>(taille);
                 vector<double> * cost = new vector <double>(taille);
                //Traitement parall�le
              //   #pragma omp parallel for
                for(i=0 ;i < taille ; i++)//pour chaque fr�quence probable on evalue le cout
                {

                    victimFrequency =trx.AvailableFrequencies->at(i);
                    veccost->at(i)=0.0;
                    cost->at(i)=0.0;
                    solution->PlanAffect->push_back({trx.trxID,victimFrequency});
                    //on �value la solution avec le nouveau couple : {victimTrx,victimFrequency}
                   int victimTrx1 = trx.trxID; int victimFrequency1 = trx.AvailableFrequencies->at(i);
                    for(j=0;j<solution->PlanAffect->size();j++)
                    {

                        victimTrx = solution->PlanAffect->at(j).first;
                        victimFrequency = solution->PlanAffect->at(j).second;
                       interfererTrx=solution->PlanAffect->at(j).first;
                        interfererFrequency=solution->PlanAffect->at(j).second;
                        if ( interfererTrx != victimTrx1)
                        {
                           // calculer le cout d interference
                            veccost->at(i)  = veccost->at(i)  + afpProblem->computeChannelInterference(victimFrequency1 ,interfererFrequency, victimTrx1, interfererTrx)+
                            afpProblem->computeChannelInterference(interfererFrequency,victimFrequency1 ,interfererTrx, victimTrx1);
                            //cout de separation
                           if(afpProblem->trxs[victimTrx1].sectorID == afpProblem->trxs[interfererTrx].sectorID)
                            {
                                //on teste si la contraite de separation co-secteur est respect�!!
                                if (abs (interfererFrequency-victimFrequency1)<3 )//contrainte co secteur viol�e
                                {
                                    cost->at(i) = cost->at(i) + 1.0;
                                }
                            }// secteur different
                            else
                            {
                                if(afpProblem->trxs[victimTrx1].siteID  == afpProblem->trxs[interfererTrx].siteID)
                                {
                        //on teste si la contrainte de separation co-site est respect�e!!
                                    if (abs (interfererFrequency-victimFrequency1)< 2)//contrainte co secteur viol�e
                                    {
                                        cost->at(i) = cost->at(i) + 1.0;
                                    }
                                }//
                            }
                        }

                    }// for(j=0 ;j < taille ; j++)//pour chaque fr�quence probable on evalue le cout
                    //.............................................................................
                    //.............................................................................
                    // enregister les couts dans le vecteur
                  //  cout << veccost->at(i) << veccost->at(i) << endl;
                    veccost->at(i) = veccost->at(i) + solution->PIObj ;
                    cost->at(i) = cost->at(i) + solution->PSObj ;
                    paircost.push_back({veccost->at(i),cost->at(i)});
                    //...................................................................
                    solution->PlanAffect->pop_back();//on retire le couple probable apres evaluation de cout et l avoir enregistr� dans veccost
                    // cout<<"frequence ::" <<trx.AvailableFrequencies->at(i)<<", son sout veccost[i] ==="<< veccost->at(i)<<endl;
                } //fortrx.AvailableFrequencies
        //***************************************************************
        //******************** Evaluation de la meilleur fr�quence ***********
        //1. choisir Le poin de r�f�rence est le pire valeur qu on peut avoir  et le max et le min ............................
          int indice;
          //----------------------
     pair<double,double> Min;
     pair<double,double> Max;
     pair < double, double > R;// est le point de r�f�rence ; la valeur max (normalis�)
    //string instance = "Denver";
  //string instance = "Seattle";
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
      // 2.-normaliser les valeurs

        vector < pair<double,double>  > Npaircost ;
         Npaircost.reserve(paircost.size());
         //copier pair cost ds Npaircost
            for(j = 0 ; j < paircost.size() ; j ++)
        {
            Npaircost.push_back({paircost.at(j).first, paircost.at(j).second});
            //cout << "Npaircost :" << Npaircost.at(j).first <<" , " << Npaircost.at(j).second <<endl;
        }
        vector < pair<int,double> > surface;
        surface.reserve(paircost.size());

        //2.-----Normaliser -------------------------
               // Normaliser les valeurs
        R.first = (R.first - Min.first)/(Max.first-Min.first);
        R.second = (R.second - Min.second)/(Max.second-Min.second);
        Normalize(Npaircost,Min,Max);
        //3---------------Calculer les distance
            for(j = 0 ; j < paircost.size(); j++)
        {
           // double d = (Npaircost.at(j).first-R.first)*(Npaircost.at(j).first-R.second);
            double d = (R.first - 0.9*Npaircost.at(j).first)*(R.second-0.1*Npaircost.at(j).second);
            surface.push_back({j,d});//.first est de la fr�quence
          //  cout << "surface.at(j).first ,surface.at(j).second :"<<surface.at(j).first<< ", " << surface.at(j).second << endl;
        }

        //5. Trier le tableau des surfaces selon un ordre croissant de surface
      // sort(surface.begin(),surface.end(),my_cmpInfDoublePair);
         sort(surface.begin(),surface.end(),my_cmpSupFirst);


        //6.la meilleur fr�quence est celle qui correspond � la surface minimale:: minimum cout
        indexmin = surface.front().first ;


        //--------------------------------------
       // indexmin = 0 ;
        f=trx.AvailableFrequencies->at(indexmin);//indice de la fr�quence recherch�
        solution->PIObj = veccost->at(indexmin);
        solution->PSObj = cost->at(indexmin);
        solution->planCC->at(trx.trxID).first = solution->PIObj;
        solution->planCC->at(trx.trxID).second = solution->PSObj;
        //nettoyage---------------------------
         vector < pair<double,double>  >().swap(paircost) ;
   // vector < pair<int,int> > ().swap(IndexesFreqsNonDominantes);
    delete(veccost);
    delete(cost);
    //delete(tempsol->PlanAffect);
    delete(solution->PlanAffect);
    //===============31-8-2021 ==========================================
        vector < pair<int,double> > ().swap(surface);
        vector < pair<double,double>  > ().swap(Npaircost) ;

    //=======================================================
    }
    else//Availablefrequencies==empty()
    {
            cout<<" la liste des fr�quences disponible est vide **"<<endl;
    }
    break;
    }


    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        default:
        {
            cout << "Player PS: ERREUR DE CHOIX DE LA strat�gie de la FREQUENCE !!"<<endl;
            break;
        }//default
    }//switch
 }
 //----------------------------------------------
 void PSPlayer::PSBestObjective(vector <Individual*> solutionSs, Individual* &BestSol  )
{
    int i, indexbestsol;
    indexbestsol = 0;
    double cost = solutionSs[0]->PSObj;
    for(i=0;i< solutionSs.size();i++)
    {
        if(cost > solutionSs[i]->PSObj)
        {
            cost = solutionSs[i]->PSObj;
            indexbestsol = i;
        }
    }

    BestSol = solutionSs[indexbestsol];

}

>>>>>>> 0514ea9fae0f841576757defb02235a9189b0fad
