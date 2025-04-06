<<<<<<< HEAD
#include <iostream>
#include <fstream>

#include <algorithm>    // std::find
#include<cmath> //abs

#include "PIPlayer.h"
#include "../Commun/Commun.h"
//#include "../Commun/Commun.cpp"



//#include "Individual.h"
//using namespace std;
//#################################################################
//Extern my Procedures and  functions  - LAIDOUI FAtma ----
//##################################################################
extern void AddSolTrxFrequency(AFP* afpProblem,Individual* &Sol,TRXs trx ,int f);
extern void UpdateLTrxNTreateds(vector <TRXs> &LTrxNTreateds, TRXs trx,int Add); //Retirer trx de LTrxNTreated
extern void UpdateTRxFrequency(TRXs &trx, int f,int Add); //Retirer f de la liste de fréquence valide de trx
extern void UpdateAllTRxFrequency(vector <TRXs> &LTrxNTreateds,int  f, int Update);
extern void vecmin(vector<double>* x, int & indexmin);//::c vérifé ::
//--------------------------------------------------------
extern void AddSolTrxFrequencyV2(Individual* &Sol,int trxid ,int f);




//##########################################################
PIPlayer::PIPlayer()
{
    IdPlayer = 1;
}
PIPlayer::~PIPlayer()
{
 IdPlayer = -1;
}
bool my_cmpvectintinffirst(const int &a, const int  &b)
{
    // smallest comes first
    return a < b;
}
bool my_cmp(const pair <int,int>   &a, const pair <int,int>   &b)
{
    // smallest comes first
    return a.second > b.second;
}
bool my_cmpInf(const pair <int,int>   &a, const pair <int,int>   &b)
{
    // smallest comes first
    return a.second < b.second;
}
bool my_cmpInfdouble (const double  &a,  const double   &b)
{
    // smallest comes first
    return a < b;
}
bool my_cmpInfDoublePair(const pair <int,double>   &a, const pair <int,double>   &b)
{
    // smallest comes first
    return a.second < b.second;
}
bool my_cmpSupFirst(const pair <int,double>   &a, const pair <int,double>   &b)
{
    // smallest comes first
    return a.second > b.second;
}
//-------------------------------------------
void PIPlayer::Play(int StrategyTrx, int StrategyFreq, TRXs &trx ,vector<TRXs> &LTrxNTreateds, Individual* &Sol, AFP * afpProblem)
{
    int i,f;
    PIChooseTrx(StrategyTrx,LTrxNTreateds,trx,afpProblem,Sol);
    PIChooseFrequency(StrategyFreq,trx,Sol, afpProblem,f);//choix Meilleur fréquence de la fréquence
    AddSolTrxFrequency(afpProblem,Sol,trx ,f); //Procédure pour affecter f au trx dans la solution
    //UpdateTRxFrequencyNew(LTrxNTreateds,afpProblem,trx,f,-1);
    //UpdateTRxFrequencyV3(LTrxNTreateds,afpProblem,trx,f,-1);
    UpdateLTrxNTreateds(LTrxNTreateds,trx,-1); //::c fait :Retirer trx de LTrxNTreat
    //for(i = 25 ; i< Sol->plan->size(); i ++) Sol->plan->at(i) = -1;
}
void PIPlayer::PlayV2(int StrategyTrx, int StrategyFreq, TRXs &trx ,vector<int> &LTrxNTreateds, Individual* &Sol, AFP * afpProblem)
{

    int f;
    PIChooseTrxV2(StrategyTrx,LTrxNTreateds,trx,afpProblem,Sol);
    PIChooseFrequency(StrategyFreq,trx,Sol, afpProblem,f);//choix Meilleur fréquence de la fréquence
    Sol->plan->at(trx.trxID) = f;
  //  AddSolTrxFrequencyV2(Sol,trx.trxID ,f); //Procédure pour affecter f au trx dans la solution
    //UpdateTRxFrequencyNew(LTrxNTreateds,afpProblem,trx,f,-1);
    UpdateTRxFrequencyV32(LTrxNTreateds,afpProblem,trx,f,-1);
    UpdateLTrxNTreatedsV2(LTrxNTreateds,trx,-1); //::c fait :Retirer trx de LTrxNTreat

}
double PIPlayer::PIEvaluateObj(Individual* &Sol)
{
    return 0.0;
}

//-------------------------------------------------------------------------------------------------------
void PIPlayer::PIChooseTrxV2(int StrategyTrx,vector<int> LTrxNTreateds,TRXs &trx,AFP* afpProblem,Individual* &Sol)
{
   switch (StrategyTrx)
   {
        case + 1: //choix aléatoire du trx
       {
           int i;
       // if(1 ==1)
            if(LTrxNTreateds.empty()==true)//on
            {
           //throw string("ERREUR: Le vecteur des trx traité est vide !!");
                cout<<"ERREUR: The vector of treated Trx is EMPTY!!" <<endl;;
            }
            else
            {
                //modifier l'ordre du tableau LTrxNTreateds et choisir ccelui de l entete
                std::srand ( unsigned ( std::time(0) ) );
                // using built-in random generator:
                std::random_shuffle ( LTrxNTreateds.begin(), LTrxNTreateds.end() );
                trx = afpProblem->trxs[LTrxNTreateds.front()];
            }//endelse
           break;
       }//case +1
      case +8 :
    {
        int i,ID ;
        vector < pair < int,double> > paircost;
        //------------------------------------------------------------
     //   paircost.reserve(LTrxNTreateds.size());
        for(i= 0 ; i < LTrxNTreateds.size(); i++)
        {
            ID = LTrxNTreateds[i];
            paircost.push_back({ID,afpProblem->MaxCostITrx[ID].second});
        }
        //  sort(paircost.begin(),paircost.end(),my_cmpSupFirst);
       /* for(i= 0 ; i < LTrxNTreateds.size(); i++)
        {
            cout << paircost[i].first << "," << paircost[i].second << endl;
        }*/
        sort(paircost.begin(),paircost.end(),my_cmpSupFirst);
        pair <int,double> node  = paircost.front();
        trx = afpProblem->trxs[node.first];
        vector < pair < int,double> >().swap(paircost);
        //cout << "trx.trxID   " << trx.trxID << endl;
        break;
    }
    default:
    {
        cout<< "Choice error in the strategy!!" << endl;
        break;
    }//default

   }//switch
}

//---------------------------------------------------------------------------------
void PIPlayer::PlayReaffect(int StrategyTrx, int StrategyFreq, TRXs &trx ,vector<TRXs> &LTrxNTreateds, Individual* &Sol, AFP * afpProblem)
{

    int f; double oldcost = afpProblem->ComputeSolutionInterference(Sol);
    PIChooseTrx(StrategyTrx,LTrxNTreateds,trx,afpProblem,Sol);
    PIChooseFrequency(StrategyFreq,trx,Sol, afpProblem,f);//choix Meilleur fréquence de la fréquence
    AddSolTrxFrequency(afpProblem,Sol,trx ,f); //Procédure pour affecter f au trx dans la solution
    //Enregistrer le cout ajouté
    //double currentCost = afpProblem->ComputeSolutionInterference(Sol);
    //Sol->planCC->at(trx.trxID) = currentCost - oldcost;
    //UpdateTRxFrequencyNew(LTrxNTreateds,afpProblem,trx,f,-1);
    UpdateTRxFrequencyV3(LTrxNTreateds,afpProblem,trx,f,-1);
    UpdateLTrxNTreateds(LTrxNTreateds,trx,-1); //::c fait :Retirer trx de LTrxNTreat
    //PIReassign(Sol,afpProblem, StrategyFreq);

}
 void PIPlayer::PIReassign(Individual* &Sol, AFP * afpProblem, int StrategyFreq)
{
 //  trouver le plus mauvais trx pour modifier sa fréquence
    int i,indexVictimTrx ;
    double cost;
 string path = "Exemples/PIReassignIII_05-4-2019.txt";
    ofstream ResultFile;
    //
    ResultFile.open(path.c_str(),std::ios::app);
    if (!ResultFile) {
        cerr << "Unable to open file!!";
        exit(1);   // call system to stop
    }

      Individual * tempsol =  new Individual();
      tempsol->plan = new vector <int>(Sol->plan->size());
      tempsol->planCC = new vector <double>(Sol->planCC->size());
      tempsol->PlanAffect = new vector< pair<int,int> > ();
    ResultFile << " avant la reafectation :::::::::::::::::::::::" << endl;
    //------utiliser ma fonction de calcul de cout
        for(i = 0 ; i < Sol->plan->size(); i ++)
        {

            tempsol->plan->at(i) = Sol->plan->at(i);
            tempsol->planCC->at(i) = Sol->planCC->at(i);
            tempsol->PIObj= Sol->PIObj;
            tempsol->PSObj= tempsol->PSObj;
            if (tempsol->plan->at(i)!= -1) tempsol->PlanAffect->push_back({i,tempsol->plan->at(i)});
            ResultFile << " LE trx" <<  tempsol->PlanAffect->at(i).first << " , " <<  tempsol->PlanAffect->at(i).second << endl;
        }

    //tempsol = Sol;
    //°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°
    //°°°°°°°°°°°°°°°°°°°°°°°°°°°° trouver le trx à modifié °°°°°°°°°°°°°°°
    int j;
    indexVictimTrx = tempsol->PlanAffect->at(0).first;
    cost =  tempsol->planCC->at(indexVictimTrx);
    for(i = 0 ; i < tempsol->PlanAffect->size() ; i++)
    {
        double currentcost =  tempsol->planCC->at(tempsol->PlanAffect->at(i).first);
        if (cost < currentcost)
        {
            cost = currentcost;
            indexVictimTrx = tempsol->PlanAffect->at(i).first ;
        }

    }
    //indexVictimTrx contient le trx à modifié
    ResultFile << "indexVictimTrx :"<< indexVictimTrx <<endl;
    //°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°

    //cost contient la valeur actuelle du cout d interference
    // initialiser la solution sans la fréquence actuelle
    int freq = tempsol->plan->at(indexVictimTrx); // sauvegarder la fréquence actuelle dans freq
    double oldcostCC = cost ; // sauvegarder le cout actuel cout CC
    tempsol -> plan ->at(indexVictimTrx) = -1 ;
    tempsol->planCC->at(indexVictimTrx) = 0.0 ;
    //°°°°°°°°°°°°°°°on revalue plan affect
    /* for(i=0;i<tempsol->PlanAffect->size();i++)
        {
            if (tempsol->PlanAffect->at(i).first == indexVictimTrx)//si la case dans le plan n'est pas vide on remplie le planAffect
            {
                erase(tempsol->PlanAffect->begin()+ i );
                i = tempsol->PlanAffect->size(); //pour sortir de la boucle
            }
        }*/

       //°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°
        double oldcost = tempsol->PIObj;
       ResultFile << ":::::::::::::::oldcost :::::::::::::::::"<< oldcost <<endl;


        TRXs trx = afpProblem->trxs[indexVictimTrx];
        int taille =trx.AvailableFrequencies->size();
        // on initialise planaffect--------------------
        delete(tempsol->PlanAffect);
        //°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°
        //°°°°°°°°°°°°°°°°°°°°°°°°°°° choisir la bonne fréquence °°°°°°°°°°°°°°°°°°°°°°°
        //tempsol -> plan ->at(indexVictimTrx) = -1 ;
       // tempsol->planCC->at(indexVictimTrx) = 0.0 ;
        tempsol->PlanAffect = new vector< pair<int,int> > ();
        for(i=0;i<tempsol->plan->size();i++)
        {

            //tempsol->plan->at(i) = Sol->plan->at(i);
            //tempsol->planCC->at(i) = Sol->planCC->at(i);
            //tempsol->PIObj= Sol->PIObj;
            //tempsol->PSObj= tempsol->PSObj;

            if (tempsol->plan->at(i)!=-1)//si la case dans le plan n'est pas vide on remplie le planAffect
            {
                tempsol->PlanAffect->push_back({i,tempsol->plan->at(i)});
            }
        }

        //--------------
        // cout de la solution sans freq
        double costwithoutfreq = afpProblem->ComputeSolutionInterference(tempsol);

        ResultFile << "costwithoutfreq " << costwithoutfreq << endl;


        vector<double> * veccost = new vector <double>(taille);
        //----------------------
         int f ,indexmin;
         int test = 0 ; // si test = 0; on a pas modifié la fréquence ; si test = 1 ;on a modifié la fréquence

        //-------------------------
        //°°°°°°°°°°°°°°°°°°°° minimum coutt
        if(trx.AvailableFrequencies->empty()==false) // on choisit parmi  les fréquences disponible de trx victime
        //celle qui a la plus petite cout
        {
                for(i=0 ;i < taille ; i++)//pour chaque fréquence probable on evalue le cout
                {

                       int victimFrequency =trx.AvailableFrequencies->at(i);
                       veccost->at(i)=0.0;
                       tempsol->PlanAffect->push_back({trx.trxID,victimFrequency});
                            // tempsol->PlanAffect->size();
                            // cout<<"   tempsol->PlanAffect->size()"<<   tempsol->PlanAffect->size()<<endl;
                            //on évalue la solution avec le nouveau couple : {victimTrx,victimFrequency}
                            double cost = 0.0;
                            for(j=0;j<tempsol->PlanAffect->size();j++)
                            {
                                int interfererTrx=tempsol->PlanAffect->at(j).first;
                                int interfererFrequency=tempsol->PlanAffect->at(j).second;
                                veccost->at(i) = veccost->at(i)+ afpProblem->computeChannelInterference(victimFrequency ,interfererFrequency, trx.trxID,interfererTrx);

                            }//(j=0;j<tempsol->PlanAffect->size();j++)

                    //.............................................................................
                    // enregister les couts dans le vecteur

                   // paircost.push_back({veccost->at(i),cost});
                    //...................................................................
                    tempsol->PlanAffect->pop_back();//on retire le couple probable apres evaluation de cout et l avoir enregistré dans veccost
                    // cout<<"frequence ::" <<trx.AvailableFrequencies->at(i)<<", son sout veccost[i] ==="<< veccost->at(i)<<endl;
                }//parcourir toutes les fréquence s valide

        // choisir la fréquence qui a le plus petit cout
        //int indexmin;
        vecmin(veccost, indexmin);//indexmin:indice de la fréquencence qui a la valeur minimale
       // on vérifi si le cout est amélioré
        ResultFile << "indexmin " <<indexmin << " qui correspond la fréquence " << trx.AvailableFrequencies->at(indexmin) << endl ;
        ResultFile << "veccost->at( indexmin)   "<< veccost->at(indexmin) <<endl;


        if (indexmin != -1)
        {
            double currentcost = veccost->at(indexmin);

            if (currentcost < oldcost)
           {
             f = trx.AvailableFrequencies->at(indexmin);
             test = 1;
                // cout << "fffffffffffffff" << f <<endl;
           }
            //sinon  on fait rien
        }//

    }
    /* if(test == 1 )
        ResultFile << " on a modifié et remplacé la fréquence " << freq << " avec la fréquence " << f <<endl;
     ResultFile.close();*/
    else// si toutes les frééquences disponibles sont consommé on cherche une valide avc le plus petit cout
        {
          // ChooseFrequencyRandom(trx, f);
           for(i=0 ;i < trx.validFrequencies->size() ; i++)//pour chaque fréquence probable on evalue le cout
                {
                    int victimFrequency =trx.validFrequencies->at(i);
                    if (victimFrequency != freq ) // pour ne pas choisir la fréquence actuelle
                    {
                        veccost->at(i)=0.0;
                        tempsol->PlanAffect->push_back({trx.trxID,victimFrequency});
                        double cost = 0.0;
                        for(j=0;j<tempsol->PlanAffect->size();j++)
                        {
                            int interfererTrx=tempsol->PlanAffect->at(j).first;
                            int interfererFrequency=tempsol->PlanAffect->at(j).second;
                            veccost->at(i) = veccost->at(i)+ afpProblem->computeChannelInterference(victimFrequency ,interfererFrequency, trx.trxID,interfererTrx);
                        }// for(i=0 ;i < taille ; i++)//pour chaque fréquence probable on evalue le cout
                        //...................................................................
                        tempsol->PlanAffect->pop_back();//on retire le couple probable apres evaluation de cout et l avoir enregistré dans veccost
                    }//parcourir toutes les fréquence s valide
                }
       // int indexmin;
        vecmin(veccost, indexmin);//indexmin:indice de la fréquencence qui a la valeur minimale
        double currentcost= veccost->at(indexmin);
        if (currentcost < oldcost)
        {
            f= trx.validFrequencies->at(indexmin);
            test = 1 ;
            cout << "test "<< test << endl ;
        }

        }//trx.validFrequencies-

    //cout << "fffffffffffffff" << f <<endl;
   if ( test == 1) //AddSolTrxFrequency(afpProblem, Sol,trx ,f); //on a trouvé une fréquence condidate
    {
        Sol -> plan ->at(indexVictimTrx) = f ;
        Sol -> planCC ->at(indexVictimTrx) = veccost->at(indexmin) - costwithoutfreq;
        Sol->PIObj = veccost->at(indexmin);
        Sol->PSObj = afpProblem->ComputeSolutionSeparationCost(Sol);
        //on mit à jour la liste des fréquences disponibles de trx indexVictimTrx

        UpdateTRxFrequency(afpProblem->trxs[indexVictimTrx], f, -1); //::cvérifé::Retirer f de la liste de fréquence valide de trx
        UpdateTRxFrequency(afpProblem->trxs[indexVictimTrx], freq, +1); //::cvérifé::Retirer f de la liste de fréquence valide de trx
    }
    //°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°

}

//-----------------------------------------------------

void PIPlayer::PIChooseTrx(int StrategyTrx,vector<TRXs> LTrxNTreateds,TRXs &trx,AFP* afpProblem,Individual* &Sol)
{
   switch (StrategyTrx)
   {
        case +9 :
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
   case +8 :
    {
        int i,ID ;
        vector < pair < int,double> > paircost;
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
   /* case + 7 : // chercher le trx avec le plus petite valeur d interference
        {

            int i,j,indextrx ;
//calculer pour chque trx non traité , la taille des trx avec qui il interfere et l enregistrer dans LTrxNTreatedsSizeinterfere
            vector < double> vectinterferCost;

            vectinterferCost.reserve(LTrxNTreateds.size());
             double value;
            double cost = 0.0 ;
            //cherche la valeur max d in terference pour chaque trx
            for(i = 0 ; i < LTrxNTreateds.size() ; i++)
            {
                vectinterferCost.push_back(afpProblem->ListTrxMaxValueinterferCost[LTrxNTreateds[i].trxID]);

            }//   for(i = 0 ; i < LTrxNTreateds.size() ; i++)
             sort (vectinterferCost.begin(), vectinterferCost.end(), my_cmpInfdouble);
           indextrx = vectinterferCost.front();
 // le trx souhaité et le prmier trx qui a le cout dinterference le plut petit
         for(i = 0 ; i < LTrxNTreateds.size() ; i++)
             {
                 if (LTrxNTreateds[i].trxID == indextrx )
                 {
                     trx = LTrxNTreateds[i];
                     i = LTrxNTreateds.size();
                 }
             }
            break;
        }
*/





        case +6:
        {// choisir le trx qui a le plus petit nbre de trx avec qui il interfere



           int i,indextrx ;
//calculer pour chque trx non traité , la taille des trx avec qui il interfere et l enregistrer dans LTrxNTreatedsSizeinterfere
            vector <pair<int,int> > LTrxNTreatedsSizeinterfere;

            LTrxNTreatedsSizeinterfere.reserve(LTrxNTreateds.size());
             for(i = 0 ; i < LTrxNTreateds.size() ; i++)
             {
                LTrxNTreatedsSizeinterfere.push_back({LTrxNTreateds[i].trxID, afpProblem->interferenceMatrix[i].size() });
             }
              // trier  en ordre croissantle tableau LTrxNTreatedsSizeinterfere selon la taille des trx avec qui il interfer
           sort (LTrxNTreatedsSizeinterfere.begin(), LTrxNTreatedsSizeinterfere.end(), my_cmpInf);
           indextrx = LTrxNTreatedsSizeinterfere.front().first;
 // le trx souhaité et le prmier trx qui a un nombre petir des trx avec qui il interfère
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


        case 5:
        {
                int taille = LTrxNTreateds.size();
                vector < pair<double,double>  > vecost (taille);
                int i; int victimTrx,interfererTrx,interfererFrequency;
                victimTrx = trx.trxID;
                for(i=0;i<LTrxNTreateds.size();i++)
                {
                    vecost[i].first = 0.0 ; // i  c eet l index de trx et nos trxID
                    vecost[i].second = 0.0 ;
                    interfererTrx = LTrxNTreateds[i].trxID;
                    sort(LTrxNTreateds[i].validFrequencies->begin(),LTrxNTreateds[i].validFrequencies->end(),my_cmpvectintinffirst);
                    interfererFrequency = LTrxNTreateds[i].validFrequencies->front();
                    vecost[i].first = afpProblem->computeChannelInterference(Sol->plan->at(trx.trxID) ,interfererFrequency, victimTrx,interfererTrx);
                    interfererFrequency = LTrxNTreateds[i].validFrequencies->back();
                    vecost[i].second = afpProblem->computeChannelInterference(Sol->plan->at(trx.trxID) ,interfererFrequency, victimTrx,interfererTrx);

                }
                //après evaluation on choisit le trx qui a le min de cou
                double cost, choose; int pos = 0;
                if (vecost[0].first > vecost[0].second )
                {
                    cost = vecost[0].second ;
                }
                for(i=1;i<LTrxNTreateds.size();i++)
                {
                    if (vecost[i].first > vecost[i].second)
                    choose =vecost[i].second;
                    else
                    choose =vecost[i].first;
                    if (cost > choose)
                    {
                        pos = i;
                        cost = choose;
                    }
                }
                trx = LTrxNTreateds[pos];
                break;
        }//case 55
       case + 1: //choix aléatoire du trx
       {
           ChooseTrxRandom(LTrxNTreateds,trx);
           break;
       }//case +1
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
            int indextrx =TrxNumberTrxSameSect[0].first;// l'indice de trx à retirer;
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
            int indextrx =TrxNumberTrxSameSect[0].first;// l'indice de trx à retirer;
            int pos = FindTrxID(LTrxNTreateds, indextrx);
            trx = LTrxNTreateds[pos];

            break;
       }//case + 2

         case + 4 : //choix de trx qui a le plus de trx dans différent
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
            int indextrx =TrxNumberTrxSameSect[0].first;// l'indice de trx à retirer;
            int pos = FindTrxID(LTrxNTreateds, indextrx);
            trx = LTrxNTreateds[pos];

            break;
       }//case + 4

       default:
       {
           cout<< "Choice error in the strategy!!" << endl;
           break;
       }//default

   }//switch

}
//-----------------------------------------------------
void PIPlayer::ChooseTrxRandom(vector<TRXs> LTrxNTreateds, TRXs &trx)
{
//LTrxNTreated : la liste des trx non traités
int i;

       // if(1 ==1)
        if(LTrxNTreateds.empty()==true)//on
        {
           //throw string("ERREUR: Le vecteur des trx traité est vide !!");
           cout<<"ERREUR: The vector of treated Trx is EMPTY!!" <<endl;;
        }
        else
        {
           //modifier l'ordre du tableau LTrxNTreateds et choisir ccelui de l entete
           std::srand ( unsigned ( std::time(0) ) );
            // using built-in random generator:
            std::random_shuffle ( LTrxNTreateds.begin(), LTrxNTreateds.end() );

           trx= LTrxNTreateds.front();
          // cout<<"trx choisit is :"<<trx.trxID<<endl;
           //choisir aléatoirement un index
           /*int index;
            index = rand() % LTrxNTreateds.size();
            trx=LTrxNTreateds.at(index);*/
        }//endelse

}
//----------------------------
void PIPlayer::ChooseFrequencyRandom(TRXs trx, int &f)
{
            int index;
            if (trx.AvailableFrequencies->empty()== false )//on choisit des fréquences disponible
            {
                index = rand() % trx.AvailableFrequencies->size();
                f=trx.AvailableFrequencies->at(index);
            }
            else//on chosit des fréquence valide
            {
                index = rand() % trx.validFrequencies->size();
                f=trx.validFrequencies->at(index);
            }

}
//------------------------------
/*void PIPlayer::ChooseFrequencyBestValid(TRXs trx,Individual * solution, AFP * afpProblem,int &f)
{

}//choiose best frequency
*/
//--------------------------------------
void PIPlayer::PIChooseFrequency(int StrategyFreq,TRXs trx,Individual * solution, AFP * afpProblem,int &f)
{
//cout<<"I aAM choooosen"<<endl<<endl;
   switch(StrategyFreq)
   {

     case + 1 :////Random choice of frequency
    {
       //Strategy = 2;
       for (int i = 0; i < trx.AvailableFrequencies->size(); i++)
       f= rand() % trx.AvailableFrequencies->size();
       break;
    }//case 1
    case  +2 ://strategy 2 choisir la meilleur fréquence en terme deminimisation de fréquence
    {
        int i,indexmin;

        int tempfreq;
        //tempsol = solution;

        //°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°copier la solution dans temsop
        Individual * tempsol =  new Individual();
        tempsol->plan = new vector <int>(solution->plan->size());
        tempsol->planCC = new vector <double>(solution->planCC->size());
         tempsol->PlanAffect = new vector< pair<int,int> > ();
         for(i = 0 ; i < solution->plan->size(); i ++)
        {
            tempsol->plan->at(i) = solution->plan->at(i);
            tempsol->planCC->at(i) = solution->planCC->at(i);
            tempsol->PIObj = solution->PIObj;
            tempsol->PSObj = solution->PSObj;
            if (tempsol->plan->at(i)!=-1)//si la case dans le plan n'est pas vide on remplie le planAffect
            {
                tempsol->PlanAffect->push_back({i,tempsol->plan->at(i)});
            }
        }
        // --verifier solution et tempsol

       /* if (tempsol->PlanAffect->size() == 3)
        {
            for( i = 0 ; i< 3 ; i++)
             {
                  cout << tempsol->PlanAffect-> at(i).first << tempsol->PlanAffect-> at(i).second <<  endl ;
                  cout << tempsol->plan->at(i) <<endl;

             }
        }*/

        //°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°
        //   tempsol->planCC=NULL;
        //LF comment: on traverse tte les fréquence et on calcule le cout
        int victimFrequency,interfererFrequency;
        int victimTrx,interfererTrx;
        victimTrx = trx.trxID;
        //----------------------
       int taille;
                   //..........................................................
            //..........................................................
            //vecteur pour enregistrer le couple de cout  interference, separation à la fois

              //vector < pair<double,double>  > paircost (taille);
            //.............................................................
            //....................................................
        //----------------------
        int j,k;
        if(trx.AvailableFrequencies->empty()==false)
        {
           taille =trx.AvailableFrequencies->size();

            vector<double> * veccost = new vector <double>(taille);
            vector <double> CostI;
            CostI.reserve(taille);
            if (taille>1)
            {
                for(i=0 ;i < taille ; i++)//pour chaque fréquence probable on evalue le cout
                {
                    victimFrequency =trx.AvailableFrequencies->at(i);
                    //tempsol->plan->at(victimTrx)=victimFrequency;
                    //veccost[i]=0.0;
                    // veccost->at(i) ;
                    veccost->at(i)=0.0;
                     // CostI[i]  = 0.0;
                   // tempsol->plan->at(i)  = victimFrequency;
                   // veccost->at(i) = afpProblem->ComputeSolutionInterference(tempsol);
                    //CostI.push_back(afpProblem->ComputeSolutionInterference(tempsol));
                    //....................
                  //  paircost.push_back({0.0,0.0});
                    //.........................
                    //   veccost->at(0)=5.0;
                    // cout<<"veccost->size()"<<veccost->size()<<endl;
                    tempsol->PlanAffect->push_back({victimTrx,victimFrequency});
                    // tempsol->PlanAffect->size();
                    // cout<<"   tempsol->PlanAffect->size()"<<   tempsol->PlanAffect->size()<<endl;
                    //on évalue la solution avec le nouveau couple : {victimTrx,victimFrequency}
                    double cost = 0.0;
                    for(j=0;j<tempsol->PlanAffect->size();j++)
                    {
                        victimTrx = tempsol->PlanAffect->at(j).first;
                        victimFrequency = tempsol->PlanAffect->at(j).second;

                        for(k = 0 ; k < tempsol->PlanAffect->size() ; k++)
                        {
                            interfererTrx=tempsol->PlanAffect->at(k).first;
                            interfererFrequency=tempsol->PlanAffect->at(k).second;
                            if ( interfererTrx != victimTrx)
                            veccost->at(i) = veccost->at(i)+afpProblem->computeChannelInterference(victimFrequency ,interfererFrequency, victimTrx,interfererTrx);
                        }
                    }
                    tempsol->PlanAffect->pop_back();
                } //fortrx.AvailableFrequencies
            //++++++++++++++++++++++++++++++++++++++++
            //afficher les valeurs de veccost

            ofstream ResultFile;
            string path="Exemples/veccost_.txt";
            ResultFile.open(path.c_str(),std::ios::app);
            if (!ResultFile) {
                cerr << "Unable to open file!!";
                exit(1);   // call system to stop
            }
            ResultFile << " trx -......" << trx.trxID << endl;
            for(i=0 ;i < trx.AvailableFrequencies->size() ; i++)
            {ResultFile << trx.AvailableFrequencies->at(i) << " :   "  <<veccost->at(i)<< endl;
            }
                vecmin(veccost, indexmin);//indexmin:indice de la fréquencence qui a la valeur minimale
            //+++++++++++++++++++++++++++++++++++++++++++
            //...................................................................................
                f=trx.AvailableFrequencies->at(indexmin);//indice de la fréquence ayant un cout minimal,
                //delete(tempsol->PlanAffect);
                 ResultFile << " f choisit est======>" << f <<endl;
            ResultFile.close();
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
        {// on choisit la meilleur fréquence VALID

            //****************#################################""
        //----------------------
        if(trx.validFrequencies->empty()==false)
        {
            taille =trx.validFrequencies->size();
            vector<double> * veccost = new vector <double>(taille);
            if (taille>1)
            {
                for(i=0 ;i < taille ; i++)//pour chaque fréquence probable on evalue le cout
                {
                    victimFrequency =trx.validFrequencies->at(i);
                    //tempsol->plan->at(victimTrx)=victimFrequency;
                    //veccost[i]=0.0;
                    // veccost->at(i) ;
                    veccost->at(i)=0.0;
                    //...................................
                 //   paircost.push_back({0.0,0.0});
                    double cost = 0.0;

                    //..........................
                    //   veccost->at(0)=5.0;
                    // cout<<"veccost->size()"<<veccost->size()<<endl;
                    tempsol->PlanAffect->push_back({victimTrx,victimFrequency});
                    // tempsol->PlanAffect->size();
                    // cout<<"   tempsol->PlanAffect->size()"<<   tempsol->PlanAffect->size()<<endl;
                    //on évalue la solution avec le nouveau couple : {victimTrx,victimFrequency}
                    for(j=0;j<tempsol->PlanAffect->size();j++)
                    {
                        victimTrx = tempsol->PlanAffect->at(j).first;
                        victimFrequency = tempsol->PlanAffect->at(j).second;

                        for(k = 0 ; k < tempsol->PlanAffect->size() ; k++)
                        {
                            interfererTrx=tempsol->PlanAffect->at(k).first;
                            interfererFrequency=tempsol->PlanAffect->at(k).second;
                            if ( interfererTrx != victimTrx)
                            veccost->at(i) = veccost->at(i)+afpProblem->computeChannelInterference(victimFrequency ,interfererFrequency, victimTrx,interfererTrx);
                        }
                     //PSPSPSPSPSPPSPSPSPSPSPSPSPSPSP
                        // calculer le cout de séparation
                 /*         if(trx.sectorID == afpProblem->trxs[tempsol->PlanAffect->at(j).first].sectorID )
                        {
                        //cout << "hiiiii i m here we are in the same sector !!!" << endl;
                            if(abs(victimFrequency - tempsol->PlanAffect->at(j).second ) < 3)//contrainte violée
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
                                if(abs(victimFrequency - tempsol->PlanAffect->at(j).second ) < 2)//contrainte violée
                                {
                                    // cout << "Oups we have violated co site constraint !!" << endl;
                                    cost = cost + 1.0;
                                    // cout << " csite " << csite<<endl;
                                }

                            }//if(trx.siteID == afpProblem->trxs[tempsol->PlanAffect->at(j).first].siteID )

                        }//else on n est pas dans le meme site
*/
                       //PSPSPSPSPSPSPSPSPSPSPSPSPSPSPSPSPSPSPSP

                    }
                     //.............................................................................
                    // enregister les couts dans le vecteur

                    //paircost.push_back({veccost->at(i),cost});
                    //...................................................................
                    tempsol->PlanAffect->pop_back();//on retire le couple probable apres evaluation de cout et l avoir enregistré dans veccost
                    // cout<<"frequence ::" <<trx.AvailableFrequencies->at(i)<<", son sout veccost[i] ==="<< veccost->at(i)<<endl;
                } //fortrx.AvailableFrequencies
                vecmin(veccost, indexmin);//indexmin:indice de la fréquencence qui a la valeur minimale
                  //.............................................................................
                //.......................................................................................
               //rechercher l indexmin indice de la fréquence dans available frequency qui a
               // une distance minimal
               //distance = abs(  paircost.first-paircost.second);
             /*   indexmin= 0;
                double distance = paircost[0].first - paircost[0].second ;
                for(i=0;i<taille;i++)
                {
                    if(distance > abs( paircost[i].first - paircost[i].second))
                    {
                        indexmin = i;
                        distance = abs( paircost[i].first - paircost[i].second);
                    }
                }


*/
                //..............................................................
                //...................................................................................
                f=trx.validFrequencies->at(indexmin);//indice de la fréquence ayant un cout minimal,
            //----------------------------------------------------


            //---------------------------------------------------------
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
            cout<<" la liste des fréquences valide est vide **"<<endl;
        }
            //******************
            //cout<<" la liste des fréquences disponibles est vide **"<<endl;
        }
           delete(tempsol->PlanAffect);
    break;
    }//case 2 : best frequency
   //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~é
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Distance ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    case  +3 ://strategy 2 choisir la meilleur fréquence en terme distance
    {
        int i,indexmin;
        Individual * tempsol =  new Individual();
        int tempfreq;
        tempsol = solution;
        //   tempsol->planCC=NULL;
        //LF comment: on traverse tte les fréquence et on calcule le cout
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
            //vecteur pour enregistrer le couple de cout  interference, separation à la fois

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
                for(i=0 ;i < taille ; i++)//pour chaque fréquence probable on evalue le cout
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
                    //on évalue la solution avec le nouveau couple : {victimTrx,victimFrequency}
                    double cost = 0.0;
                    for(j=0;j<tempsol->PlanAffect->size();j++)
                    {
                        interfererTrx=tempsol->PlanAffect->at(j).first;
                        interfererFrequency=tempsol->PlanAffect->at(j).second;
                        veccost->at(i) = veccost->at(i)+ afpProblem->computeChannelInterference(victimFrequency ,interfererFrequency, victimTrx,interfererTrx);
                        //PSPSPSPSPSPPSPSPSPSPSPSPSPSPSP
                        // calculer le cout de séparation

                          if(trx.sectorID == afpProblem->trxs[tempsol->PlanAffect->at(j).first].sectorID )
                        {
                        //cout << "hiiiii i m here we are in the same sector !!!" << endl;
                            if(abs(victimFrequency - tempsol->PlanAffect->at(j).second ) < 3)//contrainte violée
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
                                if(abs(victimFrequency - tempsol->PlanAffect->at(j).second ) < 2)//contrainte violée
                                {
                                    // cout << "Oups we have violated co site constraint !!" << endl;
                                    cost = cost + 1.0;
                                    // cout << " csite " << csite<<endl;
                                }

                            }//if(trx.siteID == afpProblem->trxs[tempsol->PlanAffect->at(j).first].siteID )

                        }//else on n est pas dans le meme site

                       //PSPSPSPSPSPSPSPSPSPSPSPSPSPSPSPSPSPSPSP
                    }// for(i=0 ;i < taille ; i++)//pour chaque fréquence probable on evalue le cout
                    //.............................................................................
                    // enregister les couts dans le vecteur

                    paircost[i].first = veccost->at(i);
                    paircost[i].second = cost;
                    //...................................................................
                    tempsol->PlanAffect->pop_back();//on retire le couple probable apres evaluation de cout et l avoir enregistré dans veccost
                    // cout<<"frequence ::" <<trx.AvailableFrequencies->at(i)<<", son sout veccost[i] ==="<< veccost->at(i)<<endl;
                } //fortrx.AvailableFrequencies
               // vecmin(veccost, indexmin);//indexmin:indice de la fréquencence qui a la valeur minimale
                //.............................................................................
                //.......................................................................................
               //rechercher l indexmin indice de la fréquence dans available frequency qui a
               // une distance minimal
               //distance = abs(  paircost.first-paircost.second);
//cout << "paircost[0].first---------------" << paircost[0].first << endl;
//cout << "paircost[0].second---------------" << paircost[0].second << endl;
                indexmin= 0;
                double distance = abs (paircost[0].first - paircost[0].second) ;
                for(i=0;i<taille;i++)
                {
                    if(distance > abs( paircost[i].first - paircost[i].second ))
                    {
                        indexmin = i;
                        distance = abs(paircost[i].first - paircost[i].second);
                    }
                }

//cout << "indexmin-----------" << indexmin << endl;

                //..............................................................
                //...................................................................................
                f=trx.AvailableFrequencies->at(indexmin);//indice de la fréquence ayant un cout minimal,

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
        {// on choisit la meilleur fréquence VALID

            //****************#################################""
        //----------------------
        if(trx.validFrequencies->empty()==false)
        {
            taille =trx.validFrequencies->size();
            vector<double> * veccost = new vector <double>(taille);
            if (taille>1)
            {
                for(i=0 ;i < taille ; i++)//pour chaque fréquence probable on evalue le cout
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
                    //on évalue la solution avec le nouveau couple : {victimTrx,victimFrequency}
                    for(j=0;j<tempsol->PlanAffect->size();j++)
                    {
                        interfererTrx=tempsol->PlanAffect->at(j).first;
                        interfererFrequency=tempsol->PlanAffect->at(j).second;
                        veccost->at(i) = veccost->at(i)+afpProblem->computeChannelInterference(victimFrequency ,interfererFrequency, victimTrx,interfererTrx);

                     //PSPSPSPSPSPPSPSPSPSPSPSPSPSPSP
                        // calculer le cout de séparation
                      if(trx.sectorID == afpProblem->trxs[tempsol->PlanAffect->at(j).first].sectorID )
                        {
                        //cout << "hiiiii i m here we are in the same sector !!!" << endl;
                            if(abs(victimFrequency - tempsol->PlanAffect->at(j).second ) < 3)//contrainte violée
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
                                if(abs(victimFrequency - tempsol->PlanAffect->at(j).second ) < 2)//contrainte violée
                                {
                                    // cout << "Oups we have violated co site constraint !!" << endl;
                                    cost = cost + 1.0;
                                    // cout << " csite " << csite<<endl;
                                }

                            }//if(trx.siteID == afpProblem->trxs[tempsol->PlanAffect->at(j).first].siteID )

                        }//else on n est pas dans le meme site

                       //PSPSPSPSPSPSPSPSPSPSPSPSPSPSPSPSPSPSPSP

                    }
                     //.............................................................................
                    // enregister les couts dans le vecteur

                    paircost[i].first = veccost->at(i);
                    paircost[i].second = cost;
                    //...................................................................
                    tempsol->PlanAffect->pop_back();//on retire le couple probable apres evaluation de cout et l avoir enregistré dans veccost
                    // cout<<"frequence ::" <<trx.AvailableFrequencies->at(i)<<", son sout veccost[i] ==="<< veccost->at(i)<<endl;
                } //fortrx.AvailableFrequencies
              //  vecmin(veccost, indexmin);//indexmin:indice de la fréquencence qui a la valeur minimale
                  //.............................................................................
                //.......................................................................................
               //rechercher l indexmin indice de la fréquence dans available frequency qui a
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
                f=trx.validFrequencies->at(indexmin);//indice de la fréquence ayant un cout minimal,
                delete(tempsol->PlanAffect);
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
            cout<<" la liste des fréquences valide est vide **"<<endl;
        }
           //******************
            //cout<<" la liste des fréquences disponibles est vide **"<<endl;
        }
    break;
    }//case 3  : best frequency DISTANCE
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~End distance ~~~~~~~~~~~~~~~~~~
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    case  +4 ://strategy 2 choisir la meilleur fréquence en terme de Nash
    {
        int i,indexmin,j,k;
        Individual * tempsol =  new Individual();
        int tempfreq;
        //°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°° copier la solution dans tempsol °°°°°°°°°°°°°°°°°°°°°°
        //°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°
        //tempsol = solution;
        tempsol->plan = new vector <int>(solution->plan->size());
        tempsol->planCC = new vector <double>(solution->planCC->size());
        tempsol->PlanAffect = new vector< pair<int,int> > ();
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

        //°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°
        //°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°
        //   tempsol->planCC=NULL;
        //LF comment: on traverse tte les fréquence et on calcule le cout
        int victimFrequency,interfererFrequency;
        int victimTrx,interfererTrx;
        victimTrx = trx.trxID;

        int taille;
        //..........................................................
        //..........................................................
        //vecteur pour enregistrer le couple de cout  interference, separation à la fois
        vector < pair<double,double>  > paircost ;
        //----------------------
        if(trx.AvailableFrequencies->empty()==false)
        {
           taille =trx.AvailableFrequencies->size();

            vector<double> * veccost = new vector <double>(taille);
            if (taille>1)
            {
                for(i=0 ;i < taille ; i++)//pour chaque fréquence probable on evalue le cout
                {

                    victimFrequency =trx.AvailableFrequencies->at(i);
                    //tempsol->plan->at(victimTrx)=victimFrequency;
                    //veccost[i]=0.0;
                    // veccost->at(i) ;
                    veccost->at(i)=0.0;

                    //....................
                  //  paircost.push_back({0.0,0.0});
                    //.........................
                    //   veccost->at(0)=5.0;
                    // cout<<"veccost->size()"<<veccost->size()<<endl;
                    tempsol->PlanAffect->push_back({victimTrx,victimFrequency});
                    // tempsol->PlanAffect->size();
                    // cout<<"   tempsol->PlanAffect->size()"<<   tempsol->PlanAffect->size()<<endl;
                    //on évalue la solution avec le nouveau couple : {victimTrx,victimFrequency}
                    double cost = 0.0;
                    for(j=0;j<tempsol->PlanAffect->size();j++)
                    {

                        victimTrx = tempsol->PlanAffect->at(j).first;
                        victimFrequency = tempsol->PlanAffect->at(j).second;
                        for(k = 0 ; k < tempsol->PlanAffect->size() ; k++)
                        {
                            interfererTrx=tempsol->PlanAffect->at(k).first;
                            interfererFrequency=tempsol->PlanAffect->at(k).second;
                            if ( interfererTrx != victimTrx)
                            {
                                veccost->at(i) = veccost->at(i)+ afpProblem->computeChannelInterference(victimFrequency ,interfererFrequency, victimTrx,interfererTrx);
                            //PSPSPSPSPSPPSPSPSPSPSPSPSPSPSP
                            }
                        }
                         for(k = j+1 ; k < tempsol->PlanAffect->size() ; k++)
                        {
                            interfererTrx=tempsol->PlanAffect->at(k).first;
                            interfererFrequency=tempsol->PlanAffect->at(k).second;
                            if(afpProblem->trxs[victimTrx].sectorID == afpProblem->trxs[interfererTrx].sectorID)
                            {
                                //cout << "hiiiii i m here we are in the same sector !!!" << endl;
                                if (abs (solution->plan->at(victimTrx)-solution->plan->at(interfererTrx))< 3)//contrainte co secteur violée
                                {
                                // cout << "Oups we have violated co sector constraint !!" << endl;
                                    cost = cost + 1.0;
                                }
                            }
                            else
                            {
                               if(afpProblem->trxs[victimTrx].siteID  == afpProblem->trxs[interfererTrx].siteID)
                               {
                                //on teste si la contrainte de separation co-site est respectée!!
                                    if (abs (solution->plan->at(victimTrx)-solution-> plan->at(interfererTrx))< 2)//contrainte co secteur violée
                                    {
                                    // cout << "Oups we have violated co site constraint !!" << endl;
                                        cost = cost + 1.0;
                                    // cout << " csite " << csite<<endl;
                                    }

                                }//if(trx.siteID == afpProblem->trxs[tempsol->PlanAffect->at(j).first].siteID )

                            }//else on n est pas dans le meme site
                        }

                       //PSPSPSPSPSPSPSPSPSPSPSPSPSPSPSPSPSPSPSP
                    }// for(j=0 ;j < taille ; j++)//pour chaque fréquence probable on evalue le cout
                    //.............................................................................
                    //.............................................................................
                    // enregister les couts dans le vecteur
                  //  cout << veccost->at(i) << veccost->at(i) << endl;
                    paircost.push_back({veccost->at(i),cost});
                    //...................................................................
                    tempsol->PlanAffect->pop_back();//on retire le couple probable apres evaluation de cout et l avoir enregistré dans veccost
                    // cout<<"frequence ::" <<trx.AvailableFrequencies->at(i)<<", son sout veccost[i] ==="<< veccost->at(i)<<endl;
                } //fortrx.AvailableFrequencies
                    // cout<<"frequence ::" <<trx.AvailableFrequencies->at(i)<<", son sout veccost[i] ==="<< veccost->at(i)<<endl;
                //} //fortrx.AvailableFrequencies
               //utiliser l equilibre de nash
              //le nombre de génération est le nombre de fréquence valide
            //chaque position dans AvailableFrequencies correspond à currentobjectif
            //..............................................................
           //...................................................................................
            //utiliser l equilibre de nash
            //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
            //afficher les valeurs de veccost
            ofstream ResultFile;
            string path="Exemples/veccostNASH_.txt";
            ResultFile.open(path.c_str(),std::ios::app);
            if (!ResultFile) {
                cerr << "Unable to open file!!";
                exit(1);   // call system to stop
            }
            ResultFile << " trx -......" << trx.trxID << endl;
            for(i=0 ;i < trx.AvailableFrequencies->size() ; i++)
            {ResultFile << trx.AvailableFrequencies->at(i) << " :   " << paircost[i].first << " = " << veccost->at(i)<<  ", " << paircost[i].second<<endl;
            }


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
                         NASHEJ.push_back(0);
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

             //++++++++++++++++++++++++++aficher les valeur de nash ++++++++++++++
             ResultFile << "°°°°°°°°°°°°°°°°°°°°°° NASH °°°°°°°°°°" <<endl;
            for(i=0 ;i < trx.AvailableFrequencies->size() ; i++)
            {
                ResultFile << NASHEJ.at(i) <<endl;
            }
            //------------------------trouver la meilleur valeur de NAsh (la plus petite)--------------------------
            NASHEbest = NASHEJ.at(0);
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
            indexmin = indexNASHEbest;

          //  cout << "indexmin " <<indexmin <<endl;

         //   vecmin(veccost,indexmin);
            //cout << "indexmin "<< indexmin << endl;
            //................................................................................
            f=trx.AvailableFrequencies->at(indexmin);//indice de la fréquence ayant un cout minimal,
            ResultFile << " f choisit est======>" << f <<endl;
            ResultFile.close();
            //-----------------------------------
            //vider la mémoire--vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
           // vector<double>().swap(NASHEJ);
            vector < pair<double,double>  >().swap(paircost) ;
             delete(veccost);

            //vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
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
        {// on choisit la meilleur fréquence VALID
            //****************#################################""
        //----------------------
            if(trx.validFrequencies->empty()==false)
            {
                taille =trx.validFrequencies->size();
                vector<double> * veccost = new vector <double>(taille);
                if (taille>1)
                {
                    for(i=0 ;i < taille ; i++)//pour chaque fréquence probable on evalue le cout
                    {
                         victimFrequency =trx.validFrequencies->at(i);
                    //tempsol->plan->at(victimTrx)=victimFrequency;
                    //veccost[i]=0.0;
                    // veccost->at(i) ;
                    veccost->at(i)=0.0;
                    //...................................
                 //   paircost.push_back({0.0,0.0});
                    double cost = 0.0;

                    //..........................
                    //   veccost->at(0)=5.0;
                    // cout<<"veccost->size()"<<veccost->size()<<endl;
                    tempsol->PlanAffect->push_back({victimTrx,victimFrequency});
                    // tempsol->PlanAffect->size();
                    // cout<<"   tempsol->PlanAffect->size()"<<   tempsol->PlanAffect->size()<<endl;
                    //on évalue la solution avec le nouveau couple : {victimTrx,victimFrequency}
                   for(j=0;j<tempsol->PlanAffect->size();j++)
                    {

                        victimTrx = tempsol->PlanAffect->at(j).first;
                        victimFrequency = tempsol->PlanAffect->at(j).second;
                        for(k = 0 ; k < tempsol->PlanAffect->size() ; k++)
                        {
                            interfererTrx=tempsol->PlanAffect->at(k).first;
                            interfererFrequency=tempsol->PlanAffect->at(k).second;
                            if ( interfererTrx != victimTrx)
                            {veccost->at(i) = veccost->at(i)+ afpProblem->computeChannelInterference(victimFrequency ,interfererFrequency, victimTrx,interfererTrx);
                            //PSPSPSPSPSPPSPSPSPSPSPSPSPSPSP
                            // calculer le cout de séparation
                            if(trx.sectorID == afpProblem->trxs[tempsol->PlanAffect->at(j).first].sectorID )
                            {
                                //cout << "hiiiii i m here we are in the same sector !!!" << endl;
                                if(abs(victimFrequency - tempsol->PlanAffect->at(j).second ) < 3)//contrainte violée
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
                                    if(abs(victimFrequency - tempsol->PlanAffect->at(j).second ) < 2)//contrainte violée
                                    {
                                    // cout << "Oups we have violated co site constraint !!" << endl;
                                        cost = cost + 1.0;
                                    // cout << " csite " << csite<<endl;
                                    }

                                }//if(trx.siteID == afpProblem->trxs[tempsol->PlanAffect->at(j).first].siteID )

                            }//else on n est pas dans le meme site
                        }//if( interfererTrx != victimTrx)
                        }//for(k = 0 ; k < tempsol->PlanAffect->size() ; k++)
                       //PSPSPSPSPSPSPSPSPSPSPSPSPSPSPSPSPSPSPSP
                    }// for(j=0 ;j < taille ; j++)//pour chaque fréquence probable on evalue le cout
                    paircost.push_back({veccost->at(i),cost});
                    //...................................................................
                    tempsol->PlanAffect->pop_back();//on retire le couple probable apres evaluation de cout et l avoir enregistré dans veccost
                    // cout<<"frequence ::" <<trx.AvailableFrequencies->at(i)<<", son sout veccost[i] ==="<< veccost->at(i)<<endl;
                } //fortrx.AvailableFrequencies
                    //  vecmin(veccost, indexmin);//indexmin:indice de la fréquencence qui a la valeur minimale
                    //.............................................................................
                    //.......................................................................................
                    //rechercher l indexmin indice de la fréquence dans available frequency qui a
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
                     for( i = 0; i < trx.validFrequencies->size();i++)
            {
                if (BestObjectivePS != 0)
                {
                    if(BestObjectivePI !=0 )
                    {
                        NASHEJ.push_back((paircost[i].first - BestObjectivePI)/BestObjectivePI+ (paircost[i].second - BestObjectivePS)/BestObjectivePS);
                    }
                    else
                    {
                         NASHEJ.push_back(0);
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
                    NASHEbest = NASHEJ.at(0);
                    //  cout << "NASHEJ.at(0) ......" <<NASHEJ.at(0)<<endl;
                    for( i = 0; i < trx.validFrequencies->size();i++)
                    {
                        if ( NASHEJ.at(i) <  NASHEbest )//enregistrer cette solution
                        {
                            NASHEbest = NASHEJ.at(i);
                            indexNASHEbest = i;
                        }
                    }
                    indexmin = indexNASHEbest;

                    //  vecmin(veccost,indexmin);
                //..............................................................
                //...................................................................................
                    f=trx.validFrequencies->at(indexmin);//indice de la fréquence ayant un cout minimal,
                    // vector<double>().swap(NASHEJ);
                    //vider la mémoire--vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
                   // vector<double>().swap(NASHEJ);
                    vector < pair<double,double>  >().swap(paircost) ;
                    delete(veccost);
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
        //delete tempsol;

        }
        else//Availablefrequencies==empty()
        {
            cout<<" la liste des fréquences valide est vide **"<<endl;
        }
            //******************
            //cout<<" la liste des fréquences disponibles est vide **"<<endl;
        }
        vector < pair<double,double>  >().swap(paircost) ;
        delete(tempsol->PlanAffect);

    break;
    }//case 4 : best frequency in term of NASH
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~END NASH~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    case 10:// nashhhhhhhhhhhhhhhhh
    {
        int i,indexmin,j;
        Individual * tempsol =  new Individual();
        int tempfreq;
        tempsol = solution;
        //   tempsol->planCC=NULL;
        //LF comment: on traverse tte les fréquence et on calcule le cout
        int victimFrequency,interfererFrequency;
        int victimTrx,interfererTrx;
        victimTrx = trx.trxID;
        //------utiliser ma fonction de calcul de cout
        tempsol=solution;

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
        victimTrx=trx.trxID;
        int taille;
        //..........................................................
        //..........................................................
        //vecteur pour enregistrer le couple de cout  interference, separation à la fois
        vector < pair<double,double>  > paircost ;
        //----------------------
        if(trx.AvailableFrequencies->empty()==false)
        {
           taille =trx.AvailableFrequencies->size();

            vector<double> * veccost = new vector <double>(taille);
            if (taille>1)
            {
                for(i=0 ;i < taille ; i++)//pour chaque fréquence probable on evalue le cout
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
                    //on évalue la solution avec le nouveau couple : {victimTrx,victimFrequency}
                    double cost = 0.0;
                    for(j=0;j<tempsol->PlanAffect->size();j++)
                    {
                        interfererTrx=tempsol->PlanAffect->at(j).first;
                        interfererFrequency=tempsol->PlanAffect->at(j).second;
                        veccost->at(i) = veccost->at(i)+ afpProblem->computeChannelInterference(victimFrequency ,interfererFrequency, victimTrx,interfererTrx);
                       // cout << "veccost->at(i).......... "<< veccost->at(i) <<endl;
                        //PSPSPSPSPSPPSPSPSPSPSPSPSPSPSP
                        // calculer le cout de séparation
                        if ( victimTrx!= interfererTrx)
                        {if(trx.sectorID == afpProblem->trxs[tempsol->PlanAffect->at(j).first].sectorID )
                        {
                        //cout << "hiiiii i m here we are in the same sector !!!" << endl;
                            if(abs(victimFrequency - tempsol->PlanAffect->at(j).second ) < 3)//contrainte violée
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
                                if(abs(victimFrequency - tempsol->PlanAffect->at(j).second ) < 2)//contrainte violée
                                {
                                    // cout << "Oups we have violated co site constraint !!" << endl;
                                    cost = cost + 1.0;
                                    // cout << " csite " << csite<<endl;
                                }

                            }//if(trx.siteID == afpProblem->trxs[tempsol->PlanAffect->at(j).first].siteID )

                        }}//else on n est pas dans le meme site
                        paircost[i].first = veccost->at(i);
                        paircost[i].second = cost;
                       //PSPSPSPSPSPSPSPSPSPSPSPSPSPSPSPSPSPSPSP
                    }// for(i=0 ;i < taille ; i++)//pour chaque fréquence probable on evalue le cout
                    //.............................................................................
                    // enregister les couts dans le vecteur
                    //cout << "veccost->at(i) ====" << veccost->at(i) << endl;
                   // cout << "cost ====" << cost << endl;
                  //  paircost.push_back({veccost->at(i),cost});
                    //...................................................................
                    tempsol->PlanAffect->pop_back();//on retire le couple probable apres evaluation de cout et l avoir enregistré dans veccost
                    // cout<<"frequence ::" <<trx.AvailableFrequencies->at(i)<<", son sout veccost[i] ==="<< veccost->at(i)<<endl;
                } //fortrx.AvailableFrequencies
               //utiliser l equilibre de nash
              //le nombre de génération est le nombre de fréquence valide
            //chaque position dans AvailableFrequencies correspond à currentobjectif
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
            for(i=0;i<trx.AvailableFrequencies->size();i++)
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
            vector<double> NASHEJ;//---------------
            double NASHEbest;
            const int SizeNashVect = trx.AvailableFrequencies->size();
            //NASHEJ.reserve(SizeNashVect);
            // cout << "SizeNashVect**** " << SizeNashVect <<endl;
            // indexmin = 0;
            double gama = 0.1;
            //remplire le table de NAshj-------------------------------
            for( i = 0; i < trx.AvailableFrequencies->size();i++)
            {
                if (BestObjectivePS != 0)
                {
                    NASHEJ.push_back((paircost[i].first - BestObjectivePI)/BestObjectivePI+ (paircost[i].second - BestObjectivePS)/BestObjectivePS);
                }
                else
                {
                    NASHEJ.push_back((paircost[i].first - BestObjectivePI)/BestObjectivePI);
                }
            }
            //------------------------trouver la meilleur valeur de NAsh (la plus petite)--------------------------
            NASHEbest = NASHEJ.at(0);
            //  cout << "NASHEJ.at(0) ......" <<NASHEJ.at(0)<<endl;
            for( i = 0; i < trx.AvailableFrequencies->size();i++)
            {
                if ( NASHEJ.at(i) <  NASHEbest )//enregistrer cette solution
                {
                    NASHEbest = NASHEJ.at(i);
                    indexNASHEbest = i;
                }
            }
            indexmin = indexNASHEbest;
            //................................................................................
            f=trx.AvailableFrequencies->at(indexmin);//indice de la fréquence ayant un cout minimal,
            //cout << "veccost->at(indexmin)  "<<  veccost->at(indexmin) << endl;
            //-----------------------------------
            //vider la mémoire--vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
            vector<double>().swap(NASHEJ);
            vector < pair<double,double>  >().swap(paircost) ;
             delete(veccost);
            //vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
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
        {// on choisit la meilleur fréquence VALID
            //****************#################################""
        //----------------------
            if(trx.validFrequencies->empty()==false)
            {
                taille =trx.validFrequencies->size();
                vector<double> * veccost = new vector <double>(taille);
                if (taille>1)
                {
                    for(i=0 ;i < taille ; i++)//pour chaque fréquence probable on evalue le cout
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
                        //on évalue la solution avec le nouveau couple : {victimTrx,victimFrequency}
                        for(j=0;j<tempsol->PlanAffect->size();j++)
                        {
                            interfererTrx=tempsol->PlanAffect->at(j).first;
                            interfererFrequency=tempsol->PlanAffect->at(j).second;
                            veccost->at(i) = veccost->at(i)+afpProblem->computeChannelInterference(victimFrequency ,interfererFrequency, victimTrx,interfererTrx);
                            //PSPSPSPSPSPPSPSPSPSPSPSPSPSPSP
                            // calculer le cout de séparation

                            if (victimTrx!=interfererTrx)
                            {if(trx.sectorID == afpProblem->trxs[tempsol->PlanAffect->at(j).first].sectorID )
                            {
                                //cout << "hiiiii i m here we are in the same sector !!!" << endl;
                                if(abs(victimFrequency - tempsol->PlanAffect->at(j).second ) < 3)//contrainte violée
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
                                    if(abs(victimFrequency - tempsol->PlanAffect->at(j).second ) < 2)//contrainte violée
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
                        paircost[i].second = cost;
                        //...................................................................
                        tempsol->PlanAffect->pop_back();//on retire le couple probable apres evaluation de cout et l avoir enregistré dans veccost
                    // cout<<"frequence ::" <<trx.AvailableFrequencies->at(i)<<", son sout veccost[i] ==="<< veccost->at(i)<<endl;
                    } //fortrx.AvailableFrequencies
                    //  vecmin(veccost, indexmin);//indexmin:indice de la fréquencence qui a la valeur minimale
                    //.............................................................................
                    //.......................................................................................
                    //rechercher l indexmin indice de la fréquence dans available frequency qui a
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
                    for( i = 0; i < trx.validFrequencies->size();i++)
                    {
                        if (BestObjectivePS != 0)
                        {
                            NASHEJ.push_back((paircost[i].first - BestObjectivePI)/BestObjectivePI+ (paircost[i].second - BestObjectivePS)/BestObjectivePS);
                        }
                        else
                        {
                            NASHEJ.push_back((paircost[i].first - BestObjectivePI)/BestObjectivePI);
                        }
                    }
  //------------------------trouver la meilleur valeur de NAsh (la plus petite)--------------------------
                    NASHEbest = NASHEJ.at(0);
                    //  cout << "NASHEJ.at(0) ......" <<NASHEJ.at(0)<<endl;
                    for( i = 0; i < trx.validFrequencies->size();i++)
                    {
                        if ( NASHEJ.at(i) <  NASHEbest )//enregistrer cette solution
                        {
                            NASHEbest = NASHEJ.at(i);
                            indexNASHEbest = i;
                        }
                    }
                    indexmin = indexNASHEbest;
                //..............................................................
                //...................................................................................
                    f=trx.validFrequencies->at(indexmin);//indice de la fréquence ayant un cout minimal,
                    // vector<double>().swap(NASHEJ);
                    //vider la mémoire--vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
                    vector<double>().swap(NASHEJ);
                    vector < pair<double,double>  >().swap(paircost) ;
                    delete(veccost);
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
        //delete tempsol;

        }
        else//Availablefrequencies==empty()
        {
            cout<<" la liste des fréquences valide est vide **"<<endl;
        }
            //******************
            //cout<<" la liste des fréquences disponibles est vide **"<<endl;
        }
        vector < pair<double,double>  >().swap(paircost) ;
        delete(tempsol->PlanAffect);

    break;
    }


    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ FRONt PARETO ~~~~~~~~~~~~~~~~~~~~~~
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
     case  +5 ://strategy 5 choisir la meilleur fréquence en terme Front parteo
    {
        int i,k,indexmin;
        Individual * tempsol =  new Individual();int tempfreq;
        tempsol = solution;
        //   tempsol->planCC=NULL;
        //LF comment: on traverse tte les fréquence et on calcule le cout
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
            //vecteur pour enregistrer le couple de cout  interference, separation à la fois

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
                for(i=0 ;i < taille ; i++)//pour chaque fréquence probable on evalue le cout
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
                    //on évalue la solution avec le nouveau couple : {victimTrx,victimFrequency}
                    double cost = 0.0;
                    for(j=0;j<tempsol->PlanAffect->size();j++)
                    {   victimTrx = tempsol->PlanAffect->at(j).first;
                        victimFrequency = tempsol->PlanAffect->at(j).second;
                        for(k = 0 ; k < tempsol->PlanAffect->size() ; k++)
                        {
                            interfererTrx=tempsol->PlanAffect->at(k).first;
                            interfererFrequency=tempsol->PlanAffect->at(k).second;
                            if ( interfererTrx != victimTrx)
                            {veccost->at(i) = veccost->at(i)+ afpProblem->computeChannelInterference(victimFrequency ,interfererFrequency, victimTrx,interfererTrx);
                            //PSPSPSPSPSPPSPSPSPSPSPSPSPSPSP
                            // calculer le cout de séparation
                            if(trx.sectorID == afpProblem->trxs[tempsol->PlanAffect->at(j).first].sectorID )
                            {
                                //cout << "hiiiii i m here we are in the same sector !!!" << endl;
                                if(abs(victimFrequency - tempsol->PlanAffect->at(j).second ) < 3)//contrainte violée
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
                                    if(abs(victimFrequency - tempsol->PlanAffect->at(j).second ) < 2)//contrainte violée
                                    {
                                    // cout << "Oups we have violated co site constraint !!" << endl;
                                        cost = cost + 1.0;
                                    // cout << " csite " << csite<<endl;
                                    }

                                }//if(trx.siteID == afpProblem->trxs[tempsol->PlanAffect->at(j).first].siteID )

                            }//else on n est pas dans le meme site
                        }//if( interfererTrx != victimTrx)
                        }//for(k = 0 ; k < tempsol->PlanAffect->size() ; k++)
                       //PSPSPSPSPSPSPSPSPSPSPSPSPSPSPSPSPSPSPSP
                    }// for(i=0 ;i < taille ; i++)//pour chaque fréquence probable on evalue le cout
                    //.............................................................................
                    // enregister les couts dans le vecteur

                    paircost[i].first = veccost->at(i);
                    paircost[i].second = cost;
                    //...................................................................
                    tempsol->PlanAffect->pop_back();//on retire le couple probable apres evaluation de cout et l avoir enregistré dans veccost
                    // cout<<"frequence ::" <<trx.AvailableFrequencies->at(i)<<", son sout veccost[i] ==="<< veccost->at(i)<<endl;
                } //fortrx.AvailableFrequencies
              // cout <<  "paircost[0].first---------" << paircost[0].first <<endl;
             //  cout <<  "paircost[0].second ---------" << paircost[0].second <<endl;
              //  vecmin(veccost, indexmin);//indexmin:indice de la fréquencence qui a la valeur minimale
                //.............................................................................
                 //afficher les valeurs de veccost

    //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
     //DOMINANCE
   //
                 //...................................................
                 //.....................................................
                // I . Retirer la non dominance pour chaque fréquence
                // ....................................................
                //...................................................

                //je supose que la soluution est domiinée et je vais tester si c est vrai
                int  NonDominantScore;

                vector < pair<int,int> > IndexesFreqsNonDominantes;
                 //(int,int) :: le premier enregistre l index de la fréquence non dominante
                  //(int,int) :: le dexieme , combien de fois la fréquence est non dominante
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
                                     NonDominantScore =   NonDominantScore + 1 ;                                   ;
                                }
                                 IndexesFreqsNonDominantes.push_back({i,NonDominantScore});
                            }//
                            else
                            {
                                if (paircost[i].second <= paircost[j].second) // on teste la non dominance par rapport au deucième objectif
                                {
                                     if (paircost[i].first < paircost[j].first)
                                    {
                                        NonDominantScore =   NonDominantScore    ;                                   ;
                                    }
                                      IndexesFreqsNonDominantes.push_back({i,NonDominantScore});
                                }

                            }
                            //sauvegarder le score
                            //IndexesFreqsNonDominantes[i].second = NonDominantScore;

                        }//i!=j
                    }//fin j

                }//fin i
                //+++++++++++++++++++++++++++++++++++++++Afficher paircost
                 //afficher les valeurs de veccost
            ofstream ResultFile;
            string path="Exemples/veccostPareto_.txt";
            ResultFile.open(path.c_str(),std::ios::app);
            if (!ResultFile) {
                cerr << "Unable to open file!!";
                exit(1);   // call system to stop
            }
            ResultFile << " trx -......" << trx.trxID << endl;
            for(i=0 ;i < trx.AvailableFrequencies->size() ; i++)
            {ResultFile << trx.AvailableFrequencies->at(i) << " :   " << paircost[i].first << " = " << veccost->at(i)<<  ", " << paircost[i].second<<endl;
            }
           //++++++++++++++++++++++++++++++++++++++++++++++++++++++++

                //...................................................
                 //.....................................................
                // II . Trier le tableau de la non dominance selon un ordre croissant
                // ....................................................
                //...................................................
              //  sort(IndexesFreqsNonDominantes.begin(),IndexesFreqsNonDominantes.end(),my_cmp);
              //  cout << "  IndexesFreqsNonDominantes.size() ****"<< IndexesFreqsNonDominantes.size() << endl;


                // copier les solution trouver dans un vecteur avec son cout d interferqunce qui
                vector < pair < int, double> > NonDominanteCost;
                NonDominanteCost.reserve(IndexesFreqsNonDominantes.size());
                for(i = 0; i < IndexesFreqsNonDominantes.size(); i++ )
                {
                    NonDominanteCost.push_back({IndexesFreqsNonDominantes[i].first, paircost[IndexesFreqsNonDominantes[i].first].first });
                }
                // trier le tableau selon un ordre décroisant du cout et retirer la première valeur


                sort(NonDominanteCost.begin(),NonDominanteCost.end(),my_cmpInfDoublePair);
                indexmin = NonDominanteCost.front().first;

     //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

    //cout << "indexmin Dom======" << indexmin << endl;

    //............................End dominance ..................................
    //..............................................................
    //................................................................................
    f=trx.AvailableFrequencies->at(indexmin);//indice de la fréquence recherché

    //+++++++++++++++++++++++++++++++
    ResultFile << endl << " pour le trx " << trx.trxID << "on a choisit la fréquence : " << f << endl;
    ResultFile.close();

    //++++++++++++++++++++
     //vider la mémoire--vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
    vector < pair<double,double>  >().swap(paircost) ;
    delete(veccost);
    delete(tempsol->PlanAffect);
            //vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
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
else//Availablefrequencies==empty() // aucune fréquence n'est diponible j'utilise les fréquence valides
        {// on choisit la meilleur fréquence VALID

            //****************#################################""
        //----------------------
        if(trx.validFrequencies->empty()==false)
        {
            taille =trx.validFrequencies->size();
            vector<double> * veccost = new vector <double>(taille);
            if (taille>1)
            {
                for(i=0 ;i < taille ; i++)//pour chaque fréquence probable on evalue le cout
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
                    //on évalue la solution avec le nouveau couple : {victimTrx,victimFrequency}
                    for(j=0;j<tempsol->PlanAffect->size();j++)
                    {
                        interfererTrx=tempsol->PlanAffect->at(j).first;
                        interfererFrequency=tempsol->PlanAffect->at(j).second;
                        veccost->at(i) = veccost->at(i)+afpProblem->computeChannelInterference(victimFrequency ,interfererFrequency, victimTrx,interfererTrx);

                     //PSPSPSPSPSPPSPSPSPSPSPSPSPSPSP
                        // calculer le cout de séparation
                      if(trx.sectorID == afpProblem->trxs[tempsol->PlanAffect->at(j).first].sectorID )
                        {
                        //cout << "hiiiii i m here we are in the same sector !!!" << endl;
                            if(abs(victimFrequency - tempsol->PlanAffect->at(j).second ) < 3)//contrainte violée
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
                                if(abs(victimFrequency - tempsol->PlanAffect->at(j).second ) < 2)//contrainte violée
                                {
                                    // cout << "Oups we have violated co site constraint !!" << endl;
                                    cost = cost + 1.0;
                                    // cout << " csite " << csite<<endl;
                                }

                            }//if(trx.siteID == afpProblem->trxs[tempsol->PlanAffect->at(j).first].siteID )

                        }//else on n est pas dans le meme site

                       //PSPSPSPSPSPSPSPSPSPSPSPSPSPSPSPSPSPSPSP

                    }
                     //.............................................................................
                    // enregister les couts dans le vecteur

                    paircost[i].first = veccost->at(i);
                    paircost[i].second = cost ;
                    //...................................................................
                    tempsol->PlanAffect->pop_back();//on retire le couple probable apres evaluation de cout et l avoir enregistré dans veccost
                    // cout<<"frequence ::" <<trx.AvailableFrequencies->at(i)<<", son sout veccost[i] ==="<< veccost->at(i)<<endl;
                } //fortrx.AvailableFrequencies
              //  vecmin(veccost, indexmin);//indexmin:indice de la fréquencence qui a la valeur minimale
                  //.............................................................................
                //.......................................................................................
               //rechercher l indexmin indice de la fréquence dans available frequency qui a
               // une distance minimal
               //distance = abs(  paircost.first-paircost.second);
          //..............................................................
                //...................................................................................

 //DOMINANCE--------------------chercher les solution dominantes et l'enregistrer dans les indexes
   //  des fréquences dans le  tableau IndexesFreqsDominantes

                // vector < pair<double,double>  > paircost (trx.AvailableFrequencies->size());
                 //paircost est un vecteur cout: chaque case contient un couple (cout d interference, cout separation)
                 //paircost[i].first : est le cout d interférence en utilisant la frequence d indice i dans la
                 //liste trx.AvailableFrequencies;
                //paircost[i].second : est le cout de séparation en utilisant la frequence d indice i dans la
                 //liste trx.AvailableFrequencies;
                 //...................................................
                 //.....................................................
                // I . Retirer la non dominance pour chaque fréquence
                // ....................................................
                //...................................................

                bool test = true; //je supose que la soluution est domiinée et je vais tester si c est vrai
                int indexdominantf, NonDominantScore;
                indexdominantf = -1;
                vector < pair<int,int> > IndexesFreqsNonDominantes;
                 //(int,int) :: le premier enregistre l index de la fréquence non dominante
                  //(int,int) :: le dexieme , combien de fois la fréquence est non dominante
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
                                     NonDominantScore =   NonDominantScore + 1 ;                                   ;
                                }
                                 IndexesFreqsNonDominantes.push_back({i,NonDominantScore});
                            }//
                            else
                            {
                                if (paircost[i].second <= paircost[j].second) // on teste la non dominance par rapport au deucième objectif
                                {
                                     if (paircost[i].first < paircost[j].first)
                                    {
                                        NonDominantScore =   NonDominantScore   ;                                   ;
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
// copier les solution trouver dans un vecteur avec son cout d interferqunce qui
                vector < pair < int, double> > NonDominanteCost;
                NonDominanteCost.reserve(IndexesFreqsNonDominantes.size());
                for(i = 0; i < IndexesFreqsNonDominantes.size(); i++ )
                {
                    NonDominanteCost.push_back({IndexesFreqsNonDominantes[i].first, paircost[IndexesFreqsNonDominantes[i].first].first });
                }
                // trier le tableau selon un ordre décroisant du cout et retirer la première valeur


                sort(NonDominanteCost.begin(),NonDominanteCost.end(),my_cmpInfDoublePair);
                indexmin = NonDominanteCost.front().first;

     //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    // parmis les solution trouvée IndexesFreqsDominantes dans récupérérer la  fréquence qui a la plus petite valeur decout
  //  cout << "IndexesFreqsDominantesPIPI.size()------- "<< IndexesFreqsNonDominantes.size() << endl;
    /*if (IndexesFreqsNonDominantes.empty() == false)
    {
        indexmin= 0 ;
        double costdom = veccost->at(IndexesFreqsNonDominantes[0]);
        cout <<" costdom ------------" <<costdom << endl;
        // chosir la fréquence avec le pust petit cout
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
    else // si je trouve pas je récupère la fréquence qui a le plus petit cout
    {vecmin(veccost, indexmin);*/
   // vecmin(veccost, indexmin);
   //indexmin = IndexesFreqsNonDominantes[0].first ;
                //................................................................................

//--------------------- dominance available
                //..............................................................
                //...................................................................................
                f=trx.validFrequencies->at(indexmin);//indice de la fréquence ayant un cout minimal,
    //vider la mémoire--vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
    vector < pair<double,double>  >().swap(paircost) ;
    delete(veccost);
    delete(tempsol->PlanAffect);
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
            cout<<" la liste des fréquences valide est vide **"<<endl;
        }
















            //******************
            //cout<<" la liste des fréquences disponibles est vide **"<<endl;
        }
    break;
    }//case 5  : best frequency Front pareto




    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~End Front Pareto
    default :
    {
        cout << "ERREUR de choix dde strategie"<< endl;
        break;
    }//default
   }//finswitch

}//PIChooseFrequency


void PIPlayer::ChooseTrxMostDistant(Individual * solution, AFP * afpProblem,  vector<TRXs> LTrxNTreateds, TRXs &trx)
{

    TRXs trxchoosed,othertrx;

    Individual * tempsol = new Individual();
    tempsol=solution;

    int i,j;
    double distance=0.0;
    //on remplie planaffect pour accelerer la recherche
    tempsol->PlanAffect = new vector< pair<int,int> > ();
    for(i=0;i<tempsol->plan->size();i++)
    {
      if (tempsol->plan->at(i)!=-1)//si la case dans le plan n'est pas vide on remplie le planAffect
      {
        tempsol->PlanAffect->push_back({i,tempsol->plan->at(i)});
      }
    }//    for(i=0;i<tempsol->plan->size();i++)
    //calculer la distance  moyenne par rapport à la solution actuelle
    vector <double> Vdistance;
    Vdistance.reserve(tempsol->PlanAffect->size());

    for(j=0; j<LTrxNTreateds.size();j++)//pour chaque trx nn traité
    {
        trxchoosed = LTrxNTreateds[j];//pour chaque trx dans LTrxNTreateds, on evalue la distance
        distance =0.0;
       // Vdistance[j] = 0.0;
        for(i=0;i<tempsol->PlanAffect->size();i++)
        {
            othertrx = afpProblem->trxs[tempsol->PlanAffect->at(i).first];
            distance = distance + DistancetowTrxs(afpProblem,trxchoosed,othertrx);
        }
        distance = distance/tempsol->PlanAffect->size(); //calculer la distance moyenne de trx choisi avec les autres trx de la solution
        Vdistance.push_back(distance);//on sauvegarde la distance dans le tableau; j est l'index de trx dans LTrxNTreateds
    }//for(j=0; j<LTrxNTreateds.size();j++)
    int indexmax;
    vecmax(Vdistance, indexmax);//retourner l'indeice valeur maximale dans un tableau
    trx = LTrxNTreateds[indexmax];
}

void PIPlayer::PIBestObjective(vector <Individual*> solutionSs, Individual* &BestSol  )
{
    int i, indexbestsol;
    indexbestsol = 0;
    double cost = solutionSs[0]->PIObj;
    for(i=0;i< solutionSs.size();i++)
    {
        if(cost > solutionSs[i]->PIObj)
        {
            cost = solutionSs[i]->PIObj;
            indexbestsol = i;
        }
    }

    BestSol = solutionSs[indexbestsol];

}
=======
#include <iostream>
#include <fstream>

#include <algorithm>    // std::find
#include<cmath> //abs

#include "PIPlayer.h"
#include "../Commun/Commun.h"
//#include "../Commun/Commun.cpp"



//#include "Individual.h"
//using namespace std;
//#################################################################
//Extern my Procedures and  functions  - LAIDOUI FAtma ----
//##################################################################
extern void AddSolTrxFrequency(AFP* afpProblem,Individual* &Sol,TRXs trx ,int f);
extern void UpdateLTrxNTreateds(vector <TRXs> &LTrxNTreateds, TRXs trx,int Add); //Retirer trx de LTrxNTreated
extern void UpdateTRxFrequency(TRXs &trx, int f,int Add); //Retirer f de la liste de fréquence valide de trx
extern void UpdateAllTRxFrequency(vector <TRXs> &LTrxNTreateds,int  f, int Update);
extern void vecmin(vector<double>* x, int & indexmin);//::c vérifé ::
//--------------------------------------------------------
extern void AddSolTrxFrequencyV2(Individual* &Sol,int trxid ,int f);




//##########################################################
PIPlayer::PIPlayer()
{
    IdPlayer = 1;
}
PIPlayer::~PIPlayer()
{
 IdPlayer = -1;
}
bool my_cmpvectintinffirst(const int &a, const int  &b)
{
    // smallest comes first
    return a < b;
}
bool my_cmp(const pair <int,int>   &a, const pair <int,int>   &b)
{
    // smallest comes first
    return a.second > b.second;
}
bool my_cmpInf(const pair <int,int>   &a, const pair <int,int>   &b)
{
    // smallest comes first
    return a.second < b.second;
}
bool my_cmpInfdouble (const double  &a,  const double   &b)
{
    // smallest comes first
    return a < b;
}
bool my_cmpInfDoublePair(const pair <int,double>   &a, const pair <int,double>   &b)
{
    // smallest comes first
    return a.second < b.second;
}
bool my_cmpSupFirst(const pair <int,double>   &a, const pair <int,double>   &b)
{
    // smallest comes first
    return a.second > b.second;
}
//-------------------------------------------
void PIPlayer::Play(int StrategyTrx, int StrategyFreq, TRXs &trx ,vector<TRXs> &LTrxNTreateds, Individual* &Sol, AFP * afpProblem)
{
    int i,f;
    PIChooseTrx(StrategyTrx,LTrxNTreateds,trx,afpProblem,Sol);
    PIChooseFrequency(StrategyFreq,trx,Sol, afpProblem,f);//choix Meilleur fréquence de la fréquence
    AddSolTrxFrequency(afpProblem,Sol,trx ,f); //Procédure pour affecter f au trx dans la solution
    //UpdateTRxFrequencyNew(LTrxNTreateds,afpProblem,trx,f,-1);
    //UpdateTRxFrequencyV3(LTrxNTreateds,afpProblem,trx,f,-1);
    UpdateLTrxNTreateds(LTrxNTreateds,trx,-1); //::c fait :Retirer trx de LTrxNTreat
    //for(i = 25 ; i< Sol->plan->size(); i ++) Sol->plan->at(i) = -1;
}
void PIPlayer::PlayV2(int StrategyTrx, int StrategyFreq, TRXs &trx ,vector<int> &LTrxNTreateds, Individual* &Sol, AFP * afpProblem)
{

    int f;
    PIChooseTrxV2(StrategyTrx,LTrxNTreateds,trx,afpProblem,Sol);
    PIChooseFrequency(StrategyFreq,trx,Sol, afpProblem,f);//choix Meilleur fréquence de la fréquence
    Sol->plan->at(trx.trxID) = f;
  //  AddSolTrxFrequencyV2(Sol,trx.trxID ,f); //Procédure pour affecter f au trx dans la solution
    //UpdateTRxFrequencyNew(LTrxNTreateds,afpProblem,trx,f,-1);
    UpdateTRxFrequencyV32(LTrxNTreateds,afpProblem,trx,f,-1);
    UpdateLTrxNTreatedsV2(LTrxNTreateds,trx,-1); //::c fait :Retirer trx de LTrxNTreat

}
double PIPlayer::PIEvaluateObj(Individual* &Sol)
{
    return 0.0;
}

//-------------------------------------------------------------------------------------------------------
void PIPlayer::PIChooseTrxV2(int StrategyTrx,vector<int> LTrxNTreateds,TRXs &trx,AFP* afpProblem,Individual* &Sol)
{
   switch (StrategyTrx)
   {
        case + 1: //choix aléatoire du trx
       {
           int i;
       // if(1 ==1)
            if(LTrxNTreateds.empty()==true)//on
            {
           //throw string("ERREUR: Le vecteur des trx traité est vide !!");
                cout<<"ERREUR: The vector of treated Trx is EMPTY!!" <<endl;;
            }
            else
            {
                //modifier l'ordre du tableau LTrxNTreateds et choisir ccelui de l entete
                std::srand ( unsigned ( std::time(0) ) );
                // using built-in random generator:
                std::random_shuffle ( LTrxNTreateds.begin(), LTrxNTreateds.end() );
                trx = afpProblem->trxs[LTrxNTreateds.front()];
            }//endelse
           break;
       }//case +1
      case +8 :
    {
        int i,ID ;
        vector < pair < int,double> > paircost;
        //------------------------------------------------------------
     //   paircost.reserve(LTrxNTreateds.size());
        for(i= 0 ; i < LTrxNTreateds.size(); i++)
        {
            ID = LTrxNTreateds[i];
            paircost.push_back({ID,afpProblem->MaxCostITrx[ID].second});
        }
        //  sort(paircost.begin(),paircost.end(),my_cmpSupFirst);
       /* for(i= 0 ; i < LTrxNTreateds.size(); i++)
        {
            cout << paircost[i].first << "," << paircost[i].second << endl;
        }*/
        sort(paircost.begin(),paircost.end(),my_cmpSupFirst);
        pair <int,double> node  = paircost.front();
        trx = afpProblem->trxs[node.first];
        vector < pair < int,double> >().swap(paircost);
        //cout << "trx.trxID   " << trx.trxID << endl;
        break;
    }
    default:
    {
        cout<< "Choice error in the strategy!!" << endl;
        break;
    }//default

   }//switch
}

//---------------------------------------------------------------------------------
void PIPlayer::PlayReaffect(int StrategyTrx, int StrategyFreq, TRXs &trx ,vector<TRXs> &LTrxNTreateds, Individual* &Sol, AFP * afpProblem)
{

    int f; double oldcost = afpProblem->ComputeSolutionInterference(Sol);
    PIChooseTrx(StrategyTrx,LTrxNTreateds,trx,afpProblem,Sol);
    PIChooseFrequency(StrategyFreq,trx,Sol, afpProblem,f);//choix Meilleur fréquence de la fréquence
    AddSolTrxFrequency(afpProblem,Sol,trx ,f); //Procédure pour affecter f au trx dans la solution
    //Enregistrer le cout ajouté
    //double currentCost = afpProblem->ComputeSolutionInterference(Sol);
    //Sol->planCC->at(trx.trxID) = currentCost - oldcost;
    //UpdateTRxFrequencyNew(LTrxNTreateds,afpProblem,trx,f,-1);
    UpdateTRxFrequencyV3(LTrxNTreateds,afpProblem,trx,f,-1);
    UpdateLTrxNTreateds(LTrxNTreateds,trx,-1); //::c fait :Retirer trx de LTrxNTreat
    //PIReassign(Sol,afpProblem, StrategyFreq);

}
 void PIPlayer::PIReassign(Individual* &Sol, AFP * afpProblem, int StrategyFreq)
{
 //  trouver le plus mauvais trx pour modifier sa fréquence
    int i,indexVictimTrx ;
    double cost;
 string path = "Exemples/PIReassignIII_05-4-2019.txt";
    ofstream ResultFile;
    //
    ResultFile.open(path.c_str(),std::ios::app);
    if (!ResultFile) {
        cerr << "Unable to open file!!";
        exit(1);   // call system to stop
    }

      Individual * tempsol =  new Individual();
      tempsol->plan = new vector <int>(Sol->plan->size());
      tempsol->planCC = new vector <double>(Sol->planCC->size());
      tempsol->PlanAffect = new vector< pair<int,int> > ();
    ResultFile << " avant la reafectation :::::::::::::::::::::::" << endl;
    //------utiliser ma fonction de calcul de cout
        for(i = 0 ; i < Sol->plan->size(); i ++)
        {

            tempsol->plan->at(i) = Sol->plan->at(i);
            tempsol->planCC->at(i) = Sol->planCC->at(i);
            tempsol->PIObj= Sol->PIObj;
            tempsol->PSObj= tempsol->PSObj;
            if (tempsol->plan->at(i)!= -1) tempsol->PlanAffect->push_back({i,tempsol->plan->at(i)});
            ResultFile << " LE trx" <<  tempsol->PlanAffect->at(i).first << " , " <<  tempsol->PlanAffect->at(i).second << endl;
        }

    //tempsol = Sol;
    //°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°
    //°°°°°°°°°°°°°°°°°°°°°°°°°°°° trouver le trx à modifié °°°°°°°°°°°°°°°
    int j;
    indexVictimTrx = tempsol->PlanAffect->at(0).first;
    cost =  tempsol->planCC->at(indexVictimTrx);
    for(i = 0 ; i < tempsol->PlanAffect->size() ; i++)
    {
        double currentcost =  tempsol->planCC->at(tempsol->PlanAffect->at(i).first);
        if (cost < currentcost)
        {
            cost = currentcost;
            indexVictimTrx = tempsol->PlanAffect->at(i).first ;
        }

    }
    //indexVictimTrx contient le trx à modifié
    ResultFile << "indexVictimTrx :"<< indexVictimTrx <<endl;
    //°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°

    //cost contient la valeur actuelle du cout d interference
    // initialiser la solution sans la fréquence actuelle
    int freq = tempsol->plan->at(indexVictimTrx); // sauvegarder la fréquence actuelle dans freq
    double oldcostCC = cost ; // sauvegarder le cout actuel cout CC
    tempsol -> plan ->at(indexVictimTrx) = -1 ;
    tempsol->planCC->at(indexVictimTrx) = 0.0 ;
    //°°°°°°°°°°°°°°°on revalue plan affect
    /* for(i=0;i<tempsol->PlanAffect->size();i++)
        {
            if (tempsol->PlanAffect->at(i).first == indexVictimTrx)//si la case dans le plan n'est pas vide on remplie le planAffect
            {
                erase(tempsol->PlanAffect->begin()+ i );
                i = tempsol->PlanAffect->size(); //pour sortir de la boucle
            }
        }*/

       //°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°
        double oldcost = tempsol->PIObj;
       ResultFile << ":::::::::::::::oldcost :::::::::::::::::"<< oldcost <<endl;


        TRXs trx = afpProblem->trxs[indexVictimTrx];
        int taille =trx.AvailableFrequencies->size();
        // on initialise planaffect--------------------
        delete(tempsol->PlanAffect);
        //°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°
        //°°°°°°°°°°°°°°°°°°°°°°°°°°° choisir la bonne fréquence °°°°°°°°°°°°°°°°°°°°°°°
        //tempsol -> plan ->at(indexVictimTrx) = -1 ;
       // tempsol->planCC->at(indexVictimTrx) = 0.0 ;
        tempsol->PlanAffect = new vector< pair<int,int> > ();
        for(i=0;i<tempsol->plan->size();i++)
        {

            //tempsol->plan->at(i) = Sol->plan->at(i);
            //tempsol->planCC->at(i) = Sol->planCC->at(i);
            //tempsol->PIObj= Sol->PIObj;
            //tempsol->PSObj= tempsol->PSObj;

            if (tempsol->plan->at(i)!=-1)//si la case dans le plan n'est pas vide on remplie le planAffect
            {
                tempsol->PlanAffect->push_back({i,tempsol->plan->at(i)});
            }
        }

        //--------------
        // cout de la solution sans freq
        double costwithoutfreq = afpProblem->ComputeSolutionInterference(tempsol);

        ResultFile << "costwithoutfreq " << costwithoutfreq << endl;


        vector<double> * veccost = new vector <double>(taille);
        //----------------------
         int f ,indexmin;
         int test = 0 ; // si test = 0; on a pas modifié la fréquence ; si test = 1 ;on a modifié la fréquence

        //-------------------------
        //°°°°°°°°°°°°°°°°°°°° minimum coutt
        if(trx.AvailableFrequencies->empty()==false) // on choisit parmi  les fréquences disponible de trx victime
        //celle qui a la plus petite cout
        {
                for(i=0 ;i < taille ; i++)//pour chaque fréquence probable on evalue le cout
                {

                       int victimFrequency =trx.AvailableFrequencies->at(i);
                       veccost->at(i)=0.0;
                       tempsol->PlanAffect->push_back({trx.trxID,victimFrequency});
                            // tempsol->PlanAffect->size();
                            // cout<<"   tempsol->PlanAffect->size()"<<   tempsol->PlanAffect->size()<<endl;
                            //on évalue la solution avec le nouveau couple : {victimTrx,victimFrequency}
                            double cost = 0.0;
                            for(j=0;j<tempsol->PlanAffect->size();j++)
                            {
                                int interfererTrx=tempsol->PlanAffect->at(j).first;
                                int interfererFrequency=tempsol->PlanAffect->at(j).second;
                                veccost->at(i) = veccost->at(i)+ afpProblem->computeChannelInterference(victimFrequency ,interfererFrequency, trx.trxID,interfererTrx);

                            }//(j=0;j<tempsol->PlanAffect->size();j++)

                    //.............................................................................
                    // enregister les couts dans le vecteur

                   // paircost.push_back({veccost->at(i),cost});
                    //...................................................................
                    tempsol->PlanAffect->pop_back();//on retire le couple probable apres evaluation de cout et l avoir enregistré dans veccost
                    // cout<<"frequence ::" <<trx.AvailableFrequencies->at(i)<<", son sout veccost[i] ==="<< veccost->at(i)<<endl;
                }//parcourir toutes les fréquence s valide

        // choisir la fréquence qui a le plus petit cout
        //int indexmin;
        vecmin(veccost, indexmin);//indexmin:indice de la fréquencence qui a la valeur minimale
       // on vérifi si le cout est amélioré
        ResultFile << "indexmin " <<indexmin << " qui correspond la fréquence " << trx.AvailableFrequencies->at(indexmin) << endl ;
        ResultFile << "veccost->at( indexmin)   "<< veccost->at(indexmin) <<endl;


        if (indexmin != -1)
        {
            double currentcost = veccost->at(indexmin);

            if (currentcost < oldcost)
           {
             f = trx.AvailableFrequencies->at(indexmin);
             test = 1;
                // cout << "fffffffffffffff" << f <<endl;
           }
            //sinon  on fait rien
        }//

    }
    /* if(test == 1 )
        ResultFile << " on a modifié et remplacé la fréquence " << freq << " avec la fréquence " << f <<endl;
     ResultFile.close();*/
    else// si toutes les frééquences disponibles sont consommé on cherche une valide avc le plus petit cout
        {
          // ChooseFrequencyRandom(trx, f);
           for(i=0 ;i < trx.validFrequencies->size() ; i++)//pour chaque fréquence probable on evalue le cout
                {
                    int victimFrequency =trx.validFrequencies->at(i);
                    if (victimFrequency != freq ) // pour ne pas choisir la fréquence actuelle
                    {
                        veccost->at(i)=0.0;
                        tempsol->PlanAffect->push_back({trx.trxID,victimFrequency});
                        double cost = 0.0;
                        for(j=0;j<tempsol->PlanAffect->size();j++)
                        {
                            int interfererTrx=tempsol->PlanAffect->at(j).first;
                            int interfererFrequency=tempsol->PlanAffect->at(j).second;
                            veccost->at(i) = veccost->at(i)+ afpProblem->computeChannelInterference(victimFrequency ,interfererFrequency, trx.trxID,interfererTrx);
                        }// for(i=0 ;i < taille ; i++)//pour chaque fréquence probable on evalue le cout
                        //...................................................................
                        tempsol->PlanAffect->pop_back();//on retire le couple probable apres evaluation de cout et l avoir enregistré dans veccost
                    }//parcourir toutes les fréquence s valide
                }
       // int indexmin;
        vecmin(veccost, indexmin);//indexmin:indice de la fréquencence qui a la valeur minimale
        double currentcost= veccost->at(indexmin);
        if (currentcost < oldcost)
        {
            f= trx.validFrequencies->at(indexmin);
            test = 1 ;
            cout << "test "<< test << endl ;
        }

        }//trx.validFrequencies-

    //cout << "fffffffffffffff" << f <<endl;
   if ( test == 1) //AddSolTrxFrequency(afpProblem, Sol,trx ,f); //on a trouvé une fréquence condidate
    {
        Sol -> plan ->at(indexVictimTrx) = f ;
        Sol -> planCC ->at(indexVictimTrx) = veccost->at(indexmin) - costwithoutfreq;
        Sol->PIObj = veccost->at(indexmin);
        Sol->PSObj = afpProblem->ComputeSolutionSeparationCost(Sol);
        //on mit à jour la liste des fréquences disponibles de trx indexVictimTrx

        UpdateTRxFrequency(afpProblem->trxs[indexVictimTrx], f, -1); //::cvérifé::Retirer f de la liste de fréquence valide de trx
        UpdateTRxFrequency(afpProblem->trxs[indexVictimTrx], freq, +1); //::cvérifé::Retirer f de la liste de fréquence valide de trx
    }
    //°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°

}

//-----------------------------------------------------

void PIPlayer::PIChooseTrx(int StrategyTrx,vector<TRXs> LTrxNTreateds,TRXs &trx,AFP* afpProblem,Individual* &Sol)
{
   switch (StrategyTrx)
   {
        case +9 :
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
   case +8 :
    {
        int i,ID ;
        vector < pair < int,double> > paircost;
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
   /* case + 7 : // chercher le trx avec le plus petite valeur d interference
        {

            int i,j,indextrx ;
//calculer pour chque trx non traité , la taille des trx avec qui il interfere et l enregistrer dans LTrxNTreatedsSizeinterfere
            vector < double> vectinterferCost;

            vectinterferCost.reserve(LTrxNTreateds.size());
             double value;
            double cost = 0.0 ;
            //cherche la valeur max d in terference pour chaque trx
            for(i = 0 ; i < LTrxNTreateds.size() ; i++)
            {
                vectinterferCost.push_back(afpProblem->ListTrxMaxValueinterferCost[LTrxNTreateds[i].trxID]);

            }//   for(i = 0 ; i < LTrxNTreateds.size() ; i++)
             sort (vectinterferCost.begin(), vectinterferCost.end(), my_cmpInfdouble);
           indextrx = vectinterferCost.front();
 // le trx souhaité et le prmier trx qui a le cout dinterference le plut petit
         for(i = 0 ; i < LTrxNTreateds.size() ; i++)
             {
                 if (LTrxNTreateds[i].trxID == indextrx )
                 {
                     trx = LTrxNTreateds[i];
                     i = LTrxNTreateds.size();
                 }
             }
            break;
        }
*/





        case +6:
        {// choisir le trx qui a le plus petit nbre de trx avec qui il interfere



           int i,indextrx ;
//calculer pour chque trx non traité , la taille des trx avec qui il interfere et l enregistrer dans LTrxNTreatedsSizeinterfere
            vector <pair<int,int> > LTrxNTreatedsSizeinterfere;

            LTrxNTreatedsSizeinterfere.reserve(LTrxNTreateds.size());
             for(i = 0 ; i < LTrxNTreateds.size() ; i++)
             {
                LTrxNTreatedsSizeinterfere.push_back({LTrxNTreateds[i].trxID, afpProblem->interferenceMatrix[i].size() });
             }
              // trier  en ordre croissantle tableau LTrxNTreatedsSizeinterfere selon la taille des trx avec qui il interfer
           sort (LTrxNTreatedsSizeinterfere.begin(), LTrxNTreatedsSizeinterfere.end(), my_cmpInf);
           indextrx = LTrxNTreatedsSizeinterfere.front().first;
 // le trx souhaité et le prmier trx qui a un nombre petir des trx avec qui il interfère
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


        case 5:
        {
                int taille = LTrxNTreateds.size();
                vector < pair<double,double>  > vecost (taille);
                int i; int victimTrx,interfererTrx,interfererFrequency;
                victimTrx = trx.trxID;
                for(i=0;i<LTrxNTreateds.size();i++)
                {
                    vecost[i].first = 0.0 ; // i  c eet l index de trx et nos trxID
                    vecost[i].second = 0.0 ;
                    interfererTrx = LTrxNTreateds[i].trxID;
                    sort(LTrxNTreateds[i].validFrequencies->begin(),LTrxNTreateds[i].validFrequencies->end(),my_cmpvectintinffirst);
                    interfererFrequency = LTrxNTreateds[i].validFrequencies->front();
                    vecost[i].first = afpProblem->computeChannelInterference(Sol->plan->at(trx.trxID) ,interfererFrequency, victimTrx,interfererTrx);
                    interfererFrequency = LTrxNTreateds[i].validFrequencies->back();
                    vecost[i].second = afpProblem->computeChannelInterference(Sol->plan->at(trx.trxID) ,interfererFrequency, victimTrx,interfererTrx);

                }
                //après evaluation on choisit le trx qui a le min de cou
                double cost, choose; int pos = 0;
                if (vecost[0].first > vecost[0].second )
                {
                    cost = vecost[0].second ;
                }
                for(i=1;i<LTrxNTreateds.size();i++)
                {
                    if (vecost[i].first > vecost[i].second)
                    choose =vecost[i].second;
                    else
                    choose =vecost[i].first;
                    if (cost > choose)
                    {
                        pos = i;
                        cost = choose;
                    }
                }
                trx = LTrxNTreateds[pos];
                break;
        }//case 55
       case + 1: //choix aléatoire du trx
       {
           ChooseTrxRandom(LTrxNTreateds,trx);
           break;
       }//case +1
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
            int indextrx =TrxNumberTrxSameSect[0].first;// l'indice de trx à retirer;
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
            int indextrx =TrxNumberTrxSameSect[0].first;// l'indice de trx à retirer;
            int pos = FindTrxID(LTrxNTreateds, indextrx);
            trx = LTrxNTreateds[pos];

            break;
       }//case + 2

         case + 4 : //choix de trx qui a le plus de trx dans différent
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
            int indextrx =TrxNumberTrxSameSect[0].first;// l'indice de trx à retirer;
            int pos = FindTrxID(LTrxNTreateds, indextrx);
            trx = LTrxNTreateds[pos];

            break;
       }//case + 4

       default:
       {
           cout<< "Choice error in the strategy!!" << endl;
           break;
       }//default

   }//switch

}
//-----------------------------------------------------
void PIPlayer::ChooseTrxRandom(vector<TRXs> LTrxNTreateds, TRXs &trx)
{
//LTrxNTreated : la liste des trx non traités
int i;

       // if(1 ==1)
        if(LTrxNTreateds.empty()==true)//on
        {
           //throw string("ERREUR: Le vecteur des trx traité est vide !!");
           cout<<"ERREUR: The vector of treated Trx is EMPTY!!" <<endl;;
        }
        else
        {
           //modifier l'ordre du tableau LTrxNTreateds et choisir ccelui de l entete
           std::srand ( unsigned ( std::time(0) ) );
            // using built-in random generator:
            std::random_shuffle ( LTrxNTreateds.begin(), LTrxNTreateds.end() );

           trx= LTrxNTreateds.front();
          // cout<<"trx choisit is :"<<trx.trxID<<endl;
           //choisir aléatoirement un index
           /*int index;
            index = rand() % LTrxNTreateds.size();
            trx=LTrxNTreateds.at(index);*/
        }//endelse

}
//----------------------------
void PIPlayer::ChooseFrequencyRandom(TRXs trx, int &f)
{
            int index;
            if (trx.AvailableFrequencies->empty()== false )//on choisit des fréquences disponible
            {
                index = rand() % trx.AvailableFrequencies->size();
                f=trx.AvailableFrequencies->at(index);
            }
            else//on chosit des fréquence valide
            {
                index = rand() % trx.validFrequencies->size();
                f=trx.validFrequencies->at(index);
            }

}
//------------------------------
/*void PIPlayer::ChooseFrequencyBestValid(TRXs trx,Individual * solution, AFP * afpProblem,int &f)
{

}//choiose best frequency
*/
//--------------------------------------
void PIPlayer::PIChooseFrequency(int StrategyFreq,TRXs trx,Individual * solution, AFP * afpProblem,int &f)
{
//cout<<"I aAM choooosen"<<endl<<endl;
   switch(StrategyFreq)
   {

     case + 1 :////Random choice of frequency
    {
       //Strategy = 2;
       for (int i = 0; i < trx.AvailableFrequencies->size(); i++)
       f= rand() % trx.AvailableFrequencies->size();
       break;
    }//case 1
    case  +2 ://strategy 2 choisir la meilleur fréquence en terme deminimisation de fréquence
    {
        int i,indexmin;

        int tempfreq;
        //tempsol = solution;

        //°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°copier la solution dans temsop
        Individual * tempsol =  new Individual();
        tempsol->plan = new vector <int>(solution->plan->size());
        tempsol->planCC = new vector <double>(solution->planCC->size());
         tempsol->PlanAffect = new vector< pair<int,int> > ();
         for(i = 0 ; i < solution->plan->size(); i ++)
        {
            tempsol->plan->at(i) = solution->plan->at(i);
            tempsol->planCC->at(i) = solution->planCC->at(i);
            tempsol->PIObj = solution->PIObj;
            tempsol->PSObj = solution->PSObj;
            if (tempsol->plan->at(i)!=-1)//si la case dans le plan n'est pas vide on remplie le planAffect
            {
                tempsol->PlanAffect->push_back({i,tempsol->plan->at(i)});
            }
        }
        // --verifier solution et tempsol

       /* if (tempsol->PlanAffect->size() == 3)
        {
            for( i = 0 ; i< 3 ; i++)
             {
                  cout << tempsol->PlanAffect-> at(i).first << tempsol->PlanAffect-> at(i).second <<  endl ;
                  cout << tempsol->plan->at(i) <<endl;

             }
        }*/

        //°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°
        //   tempsol->planCC=NULL;
        //LF comment: on traverse tte les fréquence et on calcule le cout
        int victimFrequency,interfererFrequency;
        int victimTrx,interfererTrx;
        victimTrx = trx.trxID;
        //----------------------
       int taille;
                   //..........................................................
            //..........................................................
            //vecteur pour enregistrer le couple de cout  interference, separation à la fois

              //vector < pair<double,double>  > paircost (taille);
            //.............................................................
            //....................................................
        //----------------------
        int j,k;
        if(trx.AvailableFrequencies->empty()==false)
        {
           taille =trx.AvailableFrequencies->size();

            vector<double> * veccost = new vector <double>(taille);
            vector <double> CostI;
            CostI.reserve(taille);
            if (taille>1)
            {
                for(i=0 ;i < taille ; i++)//pour chaque fréquence probable on evalue le cout
                {
                    victimFrequency =trx.AvailableFrequencies->at(i);
                    //tempsol->plan->at(victimTrx)=victimFrequency;
                    //veccost[i]=0.0;
                    // veccost->at(i) ;
                    veccost->at(i)=0.0;
                     // CostI[i]  = 0.0;
                   // tempsol->plan->at(i)  = victimFrequency;
                   // veccost->at(i) = afpProblem->ComputeSolutionInterference(tempsol);
                    //CostI.push_back(afpProblem->ComputeSolutionInterference(tempsol));
                    //....................
                  //  paircost.push_back({0.0,0.0});
                    //.........................
                    //   veccost->at(0)=5.0;
                    // cout<<"veccost->size()"<<veccost->size()<<endl;
                    tempsol->PlanAffect->push_back({victimTrx,victimFrequency});
                    // tempsol->PlanAffect->size();
                    // cout<<"   tempsol->PlanAffect->size()"<<   tempsol->PlanAffect->size()<<endl;
                    //on évalue la solution avec le nouveau couple : {victimTrx,victimFrequency}
                    double cost = 0.0;
                    for(j=0;j<tempsol->PlanAffect->size();j++)
                    {
                        victimTrx = tempsol->PlanAffect->at(j).first;
                        victimFrequency = tempsol->PlanAffect->at(j).second;

                        for(k = 0 ; k < tempsol->PlanAffect->size() ; k++)
                        {
                            interfererTrx=tempsol->PlanAffect->at(k).first;
                            interfererFrequency=tempsol->PlanAffect->at(k).second;
                            if ( interfererTrx != victimTrx)
                            veccost->at(i) = veccost->at(i)+afpProblem->computeChannelInterference(victimFrequency ,interfererFrequency, victimTrx,interfererTrx);
                        }
                    }
                    tempsol->PlanAffect->pop_back();
                } //fortrx.AvailableFrequencies
            //++++++++++++++++++++++++++++++++++++++++
            //afficher les valeurs de veccost

            ofstream ResultFile;
            string path="Exemples/veccost_.txt";
            ResultFile.open(path.c_str(),std::ios::app);
            if (!ResultFile) {
                cerr << "Unable to open file!!";
                exit(1);   // call system to stop
            }
            ResultFile << " trx -......" << trx.trxID << endl;
            for(i=0 ;i < trx.AvailableFrequencies->size() ; i++)
            {ResultFile << trx.AvailableFrequencies->at(i) << " :   "  <<veccost->at(i)<< endl;
            }
                vecmin(veccost, indexmin);//indexmin:indice de la fréquencence qui a la valeur minimale
            //+++++++++++++++++++++++++++++++++++++++++++
            //...................................................................................
                f=trx.AvailableFrequencies->at(indexmin);//indice de la fréquence ayant un cout minimal,
                //delete(tempsol->PlanAffect);
                 ResultFile << " f choisit est======>" << f <<endl;
            ResultFile.close();
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
        {// on choisit la meilleur fréquence VALID

            //****************#################################""
        //----------------------
        if(trx.validFrequencies->empty()==false)
        {
            taille =trx.validFrequencies->size();
            vector<double> * veccost = new vector <double>(taille);
            if (taille>1)
            {
                for(i=0 ;i < taille ; i++)//pour chaque fréquence probable on evalue le cout
                {
                    victimFrequency =trx.validFrequencies->at(i);
                    //tempsol->plan->at(victimTrx)=victimFrequency;
                    //veccost[i]=0.0;
                    // veccost->at(i) ;
                    veccost->at(i)=0.0;
                    //...................................
                 //   paircost.push_back({0.0,0.0});
                    double cost = 0.0;

                    //..........................
                    //   veccost->at(0)=5.0;
                    // cout<<"veccost->size()"<<veccost->size()<<endl;
                    tempsol->PlanAffect->push_back({victimTrx,victimFrequency});
                    // tempsol->PlanAffect->size();
                    // cout<<"   tempsol->PlanAffect->size()"<<   tempsol->PlanAffect->size()<<endl;
                    //on évalue la solution avec le nouveau couple : {victimTrx,victimFrequency}
                    for(j=0;j<tempsol->PlanAffect->size();j++)
                    {
                        victimTrx = tempsol->PlanAffect->at(j).first;
                        victimFrequency = tempsol->PlanAffect->at(j).second;

                        for(k = 0 ; k < tempsol->PlanAffect->size() ; k++)
                        {
                            interfererTrx=tempsol->PlanAffect->at(k).first;
                            interfererFrequency=tempsol->PlanAffect->at(k).second;
                            if ( interfererTrx != victimTrx)
                            veccost->at(i) = veccost->at(i)+afpProblem->computeChannelInterference(victimFrequency ,interfererFrequency, victimTrx,interfererTrx);
                        }
                     //PSPSPSPSPSPPSPSPSPSPSPSPSPSPSP
                        // calculer le cout de séparation
                 /*         if(trx.sectorID == afpProblem->trxs[tempsol->PlanAffect->at(j).first].sectorID )
                        {
                        //cout << "hiiiii i m here we are in the same sector !!!" << endl;
                            if(abs(victimFrequency - tempsol->PlanAffect->at(j).second ) < 3)//contrainte violée
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
                                if(abs(victimFrequency - tempsol->PlanAffect->at(j).second ) < 2)//contrainte violée
                                {
                                    // cout << "Oups we have violated co site constraint !!" << endl;
                                    cost = cost + 1.0;
                                    // cout << " csite " << csite<<endl;
                                }

                            }//if(trx.siteID == afpProblem->trxs[tempsol->PlanAffect->at(j).first].siteID )

                        }//else on n est pas dans le meme site
*/
                       //PSPSPSPSPSPSPSPSPSPSPSPSPSPSPSPSPSPSPSP

                    }
                     //.............................................................................
                    // enregister les couts dans le vecteur

                    //paircost.push_back({veccost->at(i),cost});
                    //...................................................................
                    tempsol->PlanAffect->pop_back();//on retire le couple probable apres evaluation de cout et l avoir enregistré dans veccost
                    // cout<<"frequence ::" <<trx.AvailableFrequencies->at(i)<<", son sout veccost[i] ==="<< veccost->at(i)<<endl;
                } //fortrx.AvailableFrequencies
                vecmin(veccost, indexmin);//indexmin:indice de la fréquencence qui a la valeur minimale
                  //.............................................................................
                //.......................................................................................
               //rechercher l indexmin indice de la fréquence dans available frequency qui a
               // une distance minimal
               //distance = abs(  paircost.first-paircost.second);
             /*   indexmin= 0;
                double distance = paircost[0].first - paircost[0].second ;
                for(i=0;i<taille;i++)
                {
                    if(distance > abs( paircost[i].first - paircost[i].second))
                    {
                        indexmin = i;
                        distance = abs( paircost[i].first - paircost[i].second);
                    }
                }


*/
                //..............................................................
                //...................................................................................
                f=trx.validFrequencies->at(indexmin);//indice de la fréquence ayant un cout minimal,
            //----------------------------------------------------


            //---------------------------------------------------------
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
            cout<<" la liste des fréquences valide est vide **"<<endl;
        }
            //******************
            //cout<<" la liste des fréquences disponibles est vide **"<<endl;
        }
           delete(tempsol->PlanAffect);
    break;
    }//case 2 : best frequency
   //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~é
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Distance ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    case  +3 ://strategy 2 choisir la meilleur fréquence en terme distance
    {
        int i,indexmin;
        Individual * tempsol =  new Individual();
        int tempfreq;
        tempsol = solution;
        //   tempsol->planCC=NULL;
        //LF comment: on traverse tte les fréquence et on calcule le cout
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
            //vecteur pour enregistrer le couple de cout  interference, separation à la fois

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
                for(i=0 ;i < taille ; i++)//pour chaque fréquence probable on evalue le cout
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
                    //on évalue la solution avec le nouveau couple : {victimTrx,victimFrequency}
                    double cost = 0.0;
                    for(j=0;j<tempsol->PlanAffect->size();j++)
                    {
                        interfererTrx=tempsol->PlanAffect->at(j).first;
                        interfererFrequency=tempsol->PlanAffect->at(j).second;
                        veccost->at(i) = veccost->at(i)+ afpProblem->computeChannelInterference(victimFrequency ,interfererFrequency, victimTrx,interfererTrx);
                        //PSPSPSPSPSPPSPSPSPSPSPSPSPSPSP
                        // calculer le cout de séparation

                          if(trx.sectorID == afpProblem->trxs[tempsol->PlanAffect->at(j).first].sectorID )
                        {
                        //cout << "hiiiii i m here we are in the same sector !!!" << endl;
                            if(abs(victimFrequency - tempsol->PlanAffect->at(j).second ) < 3)//contrainte violée
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
                                if(abs(victimFrequency - tempsol->PlanAffect->at(j).second ) < 2)//contrainte violée
                                {
                                    // cout << "Oups we have violated co site constraint !!" << endl;
                                    cost = cost + 1.0;
                                    // cout << " csite " << csite<<endl;
                                }

                            }//if(trx.siteID == afpProblem->trxs[tempsol->PlanAffect->at(j).first].siteID )

                        }//else on n est pas dans le meme site

                       //PSPSPSPSPSPSPSPSPSPSPSPSPSPSPSPSPSPSPSP
                    }// for(i=0 ;i < taille ; i++)//pour chaque fréquence probable on evalue le cout
                    //.............................................................................
                    // enregister les couts dans le vecteur

                    paircost[i].first = veccost->at(i);
                    paircost[i].second = cost;
                    //...................................................................
                    tempsol->PlanAffect->pop_back();//on retire le couple probable apres evaluation de cout et l avoir enregistré dans veccost
                    // cout<<"frequence ::" <<trx.AvailableFrequencies->at(i)<<", son sout veccost[i] ==="<< veccost->at(i)<<endl;
                } //fortrx.AvailableFrequencies
               // vecmin(veccost, indexmin);//indexmin:indice de la fréquencence qui a la valeur minimale
                //.............................................................................
                //.......................................................................................
               //rechercher l indexmin indice de la fréquence dans available frequency qui a
               // une distance minimal
               //distance = abs(  paircost.first-paircost.second);
//cout << "paircost[0].first---------------" << paircost[0].first << endl;
//cout << "paircost[0].second---------------" << paircost[0].second << endl;
                indexmin= 0;
                double distance = abs (paircost[0].first - paircost[0].second) ;
                for(i=0;i<taille;i++)
                {
                    if(distance > abs( paircost[i].first - paircost[i].second ))
                    {
                        indexmin = i;
                        distance = abs(paircost[i].first - paircost[i].second);
                    }
                }

//cout << "indexmin-----------" << indexmin << endl;

                //..............................................................
                //...................................................................................
                f=trx.AvailableFrequencies->at(indexmin);//indice de la fréquence ayant un cout minimal,

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
        {// on choisit la meilleur fréquence VALID

            //****************#################################""
        //----------------------
        if(trx.validFrequencies->empty()==false)
        {
            taille =trx.validFrequencies->size();
            vector<double> * veccost = new vector <double>(taille);
            if (taille>1)
            {
                for(i=0 ;i < taille ; i++)//pour chaque fréquence probable on evalue le cout
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
                    //on évalue la solution avec le nouveau couple : {victimTrx,victimFrequency}
                    for(j=0;j<tempsol->PlanAffect->size();j++)
                    {
                        interfererTrx=tempsol->PlanAffect->at(j).first;
                        interfererFrequency=tempsol->PlanAffect->at(j).second;
                        veccost->at(i) = veccost->at(i)+afpProblem->computeChannelInterference(victimFrequency ,interfererFrequency, victimTrx,interfererTrx);

                     //PSPSPSPSPSPPSPSPSPSPSPSPSPSPSP
                        // calculer le cout de séparation
                      if(trx.sectorID == afpProblem->trxs[tempsol->PlanAffect->at(j).first].sectorID )
                        {
                        //cout << "hiiiii i m here we are in the same sector !!!" << endl;
                            if(abs(victimFrequency - tempsol->PlanAffect->at(j).second ) < 3)//contrainte violée
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
                                if(abs(victimFrequency - tempsol->PlanAffect->at(j).second ) < 2)//contrainte violée
                                {
                                    // cout << "Oups we have violated co site constraint !!" << endl;
                                    cost = cost + 1.0;
                                    // cout << " csite " << csite<<endl;
                                }

                            }//if(trx.siteID == afpProblem->trxs[tempsol->PlanAffect->at(j).first].siteID )

                        }//else on n est pas dans le meme site

                       //PSPSPSPSPSPSPSPSPSPSPSPSPSPSPSPSPSPSPSP

                    }
                     //.............................................................................
                    // enregister les couts dans le vecteur

                    paircost[i].first = veccost->at(i);
                    paircost[i].second = cost;
                    //...................................................................
                    tempsol->PlanAffect->pop_back();//on retire le couple probable apres evaluation de cout et l avoir enregistré dans veccost
                    // cout<<"frequence ::" <<trx.AvailableFrequencies->at(i)<<", son sout veccost[i] ==="<< veccost->at(i)<<endl;
                } //fortrx.AvailableFrequencies
              //  vecmin(veccost, indexmin);//indexmin:indice de la fréquencence qui a la valeur minimale
                  //.............................................................................
                //.......................................................................................
               //rechercher l indexmin indice de la fréquence dans available frequency qui a
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
                f=trx.validFrequencies->at(indexmin);//indice de la fréquence ayant un cout minimal,
                delete(tempsol->PlanAffect);
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
            cout<<" la liste des fréquences valide est vide **"<<endl;
        }
           //******************
            //cout<<" la liste des fréquences disponibles est vide **"<<endl;
        }
    break;
    }//case 3  : best frequency DISTANCE
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~End distance ~~~~~~~~~~~~~~~~~~
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    case  +4 ://strategy 2 choisir la meilleur fréquence en terme de Nash
    {
        int i,indexmin,j,k;
        Individual * tempsol =  new Individual();
        int tempfreq;
        //°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°° copier la solution dans tempsol °°°°°°°°°°°°°°°°°°°°°°
        //°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°
        //tempsol = solution;
        tempsol->plan = new vector <int>(solution->plan->size());
        tempsol->planCC = new vector <double>(solution->planCC->size());
        tempsol->PlanAffect = new vector< pair<int,int> > ();
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

        //°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°
        //°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°
        //   tempsol->planCC=NULL;
        //LF comment: on traverse tte les fréquence et on calcule le cout
        int victimFrequency,interfererFrequency;
        int victimTrx,interfererTrx;
        victimTrx = trx.trxID;

        int taille;
        //..........................................................
        //..........................................................
        //vecteur pour enregistrer le couple de cout  interference, separation à la fois
        vector < pair<double,double>  > paircost ;
        //----------------------
        if(trx.AvailableFrequencies->empty()==false)
        {
           taille =trx.AvailableFrequencies->size();

            vector<double> * veccost = new vector <double>(taille);
            if (taille>1)
            {
                for(i=0 ;i < taille ; i++)//pour chaque fréquence probable on evalue le cout
                {

                    victimFrequency =trx.AvailableFrequencies->at(i);
                    //tempsol->plan->at(victimTrx)=victimFrequency;
                    //veccost[i]=0.0;
                    // veccost->at(i) ;
                    veccost->at(i)=0.0;

                    //....................
                  //  paircost.push_back({0.0,0.0});
                    //.........................
                    //   veccost->at(0)=5.0;
                    // cout<<"veccost->size()"<<veccost->size()<<endl;
                    tempsol->PlanAffect->push_back({victimTrx,victimFrequency});
                    // tempsol->PlanAffect->size();
                    // cout<<"   tempsol->PlanAffect->size()"<<   tempsol->PlanAffect->size()<<endl;
                    //on évalue la solution avec le nouveau couple : {victimTrx,victimFrequency}
                    double cost = 0.0;
                    for(j=0;j<tempsol->PlanAffect->size();j++)
                    {

                        victimTrx = tempsol->PlanAffect->at(j).first;
                        victimFrequency = tempsol->PlanAffect->at(j).second;
                        for(k = 0 ; k < tempsol->PlanAffect->size() ; k++)
                        {
                            interfererTrx=tempsol->PlanAffect->at(k).first;
                            interfererFrequency=tempsol->PlanAffect->at(k).second;
                            if ( interfererTrx != victimTrx)
                            {
                                veccost->at(i) = veccost->at(i)+ afpProblem->computeChannelInterference(victimFrequency ,interfererFrequency, victimTrx,interfererTrx);
                            //PSPSPSPSPSPPSPSPSPSPSPSPSPSPSP
                            }
                        }
                         for(k = j+1 ; k < tempsol->PlanAffect->size() ; k++)
                        {
                            interfererTrx=tempsol->PlanAffect->at(k).first;
                            interfererFrequency=tempsol->PlanAffect->at(k).second;
                            if(afpProblem->trxs[victimTrx].sectorID == afpProblem->trxs[interfererTrx].sectorID)
                            {
                                //cout << "hiiiii i m here we are in the same sector !!!" << endl;
                                if (abs (solution->plan->at(victimTrx)-solution->plan->at(interfererTrx))< 3)//contrainte co secteur violée
                                {
                                // cout << "Oups we have violated co sector constraint !!" << endl;
                                    cost = cost + 1.0;
                                }
                            }
                            else
                            {
                               if(afpProblem->trxs[victimTrx].siteID  == afpProblem->trxs[interfererTrx].siteID)
                               {
                                //on teste si la contrainte de separation co-site est respectée!!
                                    if (abs (solution->plan->at(victimTrx)-solution-> plan->at(interfererTrx))< 2)//contrainte co secteur violée
                                    {
                                    // cout << "Oups we have violated co site constraint !!" << endl;
                                        cost = cost + 1.0;
                                    // cout << " csite " << csite<<endl;
                                    }

                                }//if(trx.siteID == afpProblem->trxs[tempsol->PlanAffect->at(j).first].siteID )

                            }//else on n est pas dans le meme site
                        }

                       //PSPSPSPSPSPSPSPSPSPSPSPSPSPSPSPSPSPSPSP
                    }// for(j=0 ;j < taille ; j++)//pour chaque fréquence probable on evalue le cout
                    //.............................................................................
                    //.............................................................................
                    // enregister les couts dans le vecteur
                  //  cout << veccost->at(i) << veccost->at(i) << endl;
                    paircost.push_back({veccost->at(i),cost});
                    //...................................................................
                    tempsol->PlanAffect->pop_back();//on retire le couple probable apres evaluation de cout et l avoir enregistré dans veccost
                    // cout<<"frequence ::" <<trx.AvailableFrequencies->at(i)<<", son sout veccost[i] ==="<< veccost->at(i)<<endl;
                } //fortrx.AvailableFrequencies
                    // cout<<"frequence ::" <<trx.AvailableFrequencies->at(i)<<", son sout veccost[i] ==="<< veccost->at(i)<<endl;
                //} //fortrx.AvailableFrequencies
               //utiliser l equilibre de nash
              //le nombre de génération est le nombre de fréquence valide
            //chaque position dans AvailableFrequencies correspond à currentobjectif
            //..............................................................
           //...................................................................................
            //utiliser l equilibre de nash
            //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
            //afficher les valeurs de veccost
            ofstream ResultFile;
            string path="Exemples/veccostNASH_.txt";
            ResultFile.open(path.c_str(),std::ios::app);
            if (!ResultFile) {
                cerr << "Unable to open file!!";
                exit(1);   // call system to stop
            }
            ResultFile << " trx -......" << trx.trxID << endl;
            for(i=0 ;i < trx.AvailableFrequencies->size() ; i++)
            {ResultFile << trx.AvailableFrequencies->at(i) << " :   " << paircost[i].first << " = " << veccost->at(i)<<  ", " << paircost[i].second<<endl;
            }


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
                         NASHEJ.push_back(0);
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

             //++++++++++++++++++++++++++aficher les valeur de nash ++++++++++++++
             ResultFile << "°°°°°°°°°°°°°°°°°°°°°° NASH °°°°°°°°°°" <<endl;
            for(i=0 ;i < trx.AvailableFrequencies->size() ; i++)
            {
                ResultFile << NASHEJ.at(i) <<endl;
            }
            //------------------------trouver la meilleur valeur de NAsh (la plus petite)--------------------------
            NASHEbest = NASHEJ.at(0);
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
            indexmin = indexNASHEbest;

          //  cout << "indexmin " <<indexmin <<endl;

         //   vecmin(veccost,indexmin);
            //cout << "indexmin "<< indexmin << endl;
            //................................................................................
            f=trx.AvailableFrequencies->at(indexmin);//indice de la fréquence ayant un cout minimal,
            ResultFile << " f choisit est======>" << f <<endl;
            ResultFile.close();
            //-----------------------------------
            //vider la mémoire--vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
           // vector<double>().swap(NASHEJ);
            vector < pair<double,double>  >().swap(paircost) ;
             delete(veccost);

            //vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
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
        {// on choisit la meilleur fréquence VALID
            //****************#################################""
        //----------------------
            if(trx.validFrequencies->empty()==false)
            {
                taille =trx.validFrequencies->size();
                vector<double> * veccost = new vector <double>(taille);
                if (taille>1)
                {
                    for(i=0 ;i < taille ; i++)//pour chaque fréquence probable on evalue le cout
                    {
                         victimFrequency =trx.validFrequencies->at(i);
                    //tempsol->plan->at(victimTrx)=victimFrequency;
                    //veccost[i]=0.0;
                    // veccost->at(i) ;
                    veccost->at(i)=0.0;
                    //...................................
                 //   paircost.push_back({0.0,0.0});
                    double cost = 0.0;

                    //..........................
                    //   veccost->at(0)=5.0;
                    // cout<<"veccost->size()"<<veccost->size()<<endl;
                    tempsol->PlanAffect->push_back({victimTrx,victimFrequency});
                    // tempsol->PlanAffect->size();
                    // cout<<"   tempsol->PlanAffect->size()"<<   tempsol->PlanAffect->size()<<endl;
                    //on évalue la solution avec le nouveau couple : {victimTrx,victimFrequency}
                   for(j=0;j<tempsol->PlanAffect->size();j++)
                    {

                        victimTrx = tempsol->PlanAffect->at(j).first;
                        victimFrequency = tempsol->PlanAffect->at(j).second;
                        for(k = 0 ; k < tempsol->PlanAffect->size() ; k++)
                        {
                            interfererTrx=tempsol->PlanAffect->at(k).first;
                            interfererFrequency=tempsol->PlanAffect->at(k).second;
                            if ( interfererTrx != victimTrx)
                            {veccost->at(i) = veccost->at(i)+ afpProblem->computeChannelInterference(victimFrequency ,interfererFrequency, victimTrx,interfererTrx);
                            //PSPSPSPSPSPPSPSPSPSPSPSPSPSPSP
                            // calculer le cout de séparation
                            if(trx.sectorID == afpProblem->trxs[tempsol->PlanAffect->at(j).first].sectorID )
                            {
                                //cout << "hiiiii i m here we are in the same sector !!!" << endl;
                                if(abs(victimFrequency - tempsol->PlanAffect->at(j).second ) < 3)//contrainte violée
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
                                    if(abs(victimFrequency - tempsol->PlanAffect->at(j).second ) < 2)//contrainte violée
                                    {
                                    // cout << "Oups we have violated co site constraint !!" << endl;
                                        cost = cost + 1.0;
                                    // cout << " csite " << csite<<endl;
                                    }

                                }//if(trx.siteID == afpProblem->trxs[tempsol->PlanAffect->at(j).first].siteID )

                            }//else on n est pas dans le meme site
                        }//if( interfererTrx != victimTrx)
                        }//for(k = 0 ; k < tempsol->PlanAffect->size() ; k++)
                       //PSPSPSPSPSPSPSPSPSPSPSPSPSPSPSPSPSPSPSP
                    }// for(j=0 ;j < taille ; j++)//pour chaque fréquence probable on evalue le cout
                    paircost.push_back({veccost->at(i),cost});
                    //...................................................................
                    tempsol->PlanAffect->pop_back();//on retire le couple probable apres evaluation de cout et l avoir enregistré dans veccost
                    // cout<<"frequence ::" <<trx.AvailableFrequencies->at(i)<<", son sout veccost[i] ==="<< veccost->at(i)<<endl;
                } //fortrx.AvailableFrequencies
                    //  vecmin(veccost, indexmin);//indexmin:indice de la fréquencence qui a la valeur minimale
                    //.............................................................................
                    //.......................................................................................
                    //rechercher l indexmin indice de la fréquence dans available frequency qui a
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
                     for( i = 0; i < trx.validFrequencies->size();i++)
            {
                if (BestObjectivePS != 0)
                {
                    if(BestObjectivePI !=0 )
                    {
                        NASHEJ.push_back((paircost[i].first - BestObjectivePI)/BestObjectivePI+ (paircost[i].second - BestObjectivePS)/BestObjectivePS);
                    }
                    else
                    {
                         NASHEJ.push_back(0);
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
                    NASHEbest = NASHEJ.at(0);
                    //  cout << "NASHEJ.at(0) ......" <<NASHEJ.at(0)<<endl;
                    for( i = 0; i < trx.validFrequencies->size();i++)
                    {
                        if ( NASHEJ.at(i) <  NASHEbest )//enregistrer cette solution
                        {
                            NASHEbest = NASHEJ.at(i);
                            indexNASHEbest = i;
                        }
                    }
                    indexmin = indexNASHEbest;

                    //  vecmin(veccost,indexmin);
                //..............................................................
                //...................................................................................
                    f=trx.validFrequencies->at(indexmin);//indice de la fréquence ayant un cout minimal,
                    // vector<double>().swap(NASHEJ);
                    //vider la mémoire--vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
                   // vector<double>().swap(NASHEJ);
                    vector < pair<double,double>  >().swap(paircost) ;
                    delete(veccost);
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
        //delete tempsol;

        }
        else//Availablefrequencies==empty()
        {
            cout<<" la liste des fréquences valide est vide **"<<endl;
        }
            //******************
            //cout<<" la liste des fréquences disponibles est vide **"<<endl;
        }
        vector < pair<double,double>  >().swap(paircost) ;
        delete(tempsol->PlanAffect);

    break;
    }//case 4 : best frequency in term of NASH
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~END NASH~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    case 10:// nashhhhhhhhhhhhhhhhh
    {
        int i,indexmin,j;
        Individual * tempsol =  new Individual();
        int tempfreq;
        tempsol = solution;
        //   tempsol->planCC=NULL;
        //LF comment: on traverse tte les fréquence et on calcule le cout
        int victimFrequency,interfererFrequency;
        int victimTrx,interfererTrx;
        victimTrx = trx.trxID;
        //------utiliser ma fonction de calcul de cout
        tempsol=solution;

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
        victimTrx=trx.trxID;
        int taille;
        //..........................................................
        //..........................................................
        //vecteur pour enregistrer le couple de cout  interference, separation à la fois
        vector < pair<double,double>  > paircost ;
        //----------------------
        if(trx.AvailableFrequencies->empty()==false)
        {
           taille =trx.AvailableFrequencies->size();

            vector<double> * veccost = new vector <double>(taille);
            if (taille>1)
            {
                for(i=0 ;i < taille ; i++)//pour chaque fréquence probable on evalue le cout
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
                    //on évalue la solution avec le nouveau couple : {victimTrx,victimFrequency}
                    double cost = 0.0;
                    for(j=0;j<tempsol->PlanAffect->size();j++)
                    {
                        interfererTrx=tempsol->PlanAffect->at(j).first;
                        interfererFrequency=tempsol->PlanAffect->at(j).second;
                        veccost->at(i) = veccost->at(i)+ afpProblem->computeChannelInterference(victimFrequency ,interfererFrequency, victimTrx,interfererTrx);
                       // cout << "veccost->at(i).......... "<< veccost->at(i) <<endl;
                        //PSPSPSPSPSPPSPSPSPSPSPSPSPSPSP
                        // calculer le cout de séparation
                        if ( victimTrx!= interfererTrx)
                        {if(trx.sectorID == afpProblem->trxs[tempsol->PlanAffect->at(j).first].sectorID )
                        {
                        //cout << "hiiiii i m here we are in the same sector !!!" << endl;
                            if(abs(victimFrequency - tempsol->PlanAffect->at(j).second ) < 3)//contrainte violée
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
                                if(abs(victimFrequency - tempsol->PlanAffect->at(j).second ) < 2)//contrainte violée
                                {
                                    // cout << "Oups we have violated co site constraint !!" << endl;
                                    cost = cost + 1.0;
                                    // cout << " csite " << csite<<endl;
                                }

                            }//if(trx.siteID == afpProblem->trxs[tempsol->PlanAffect->at(j).first].siteID )

                        }}//else on n est pas dans le meme site
                        paircost[i].first = veccost->at(i);
                        paircost[i].second = cost;
                       //PSPSPSPSPSPSPSPSPSPSPSPSPSPSPSPSPSPSPSP
                    }// for(i=0 ;i < taille ; i++)//pour chaque fréquence probable on evalue le cout
                    //.............................................................................
                    // enregister les couts dans le vecteur
                    //cout << "veccost->at(i) ====" << veccost->at(i) << endl;
                   // cout << "cost ====" << cost << endl;
                  //  paircost.push_back({veccost->at(i),cost});
                    //...................................................................
                    tempsol->PlanAffect->pop_back();//on retire le couple probable apres evaluation de cout et l avoir enregistré dans veccost
                    // cout<<"frequence ::" <<trx.AvailableFrequencies->at(i)<<", son sout veccost[i] ==="<< veccost->at(i)<<endl;
                } //fortrx.AvailableFrequencies
               //utiliser l equilibre de nash
              //le nombre de génération est le nombre de fréquence valide
            //chaque position dans AvailableFrequencies correspond à currentobjectif
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
            for(i=0;i<trx.AvailableFrequencies->size();i++)
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
            vector<double> NASHEJ;//---------------
            double NASHEbest;
            const int SizeNashVect = trx.AvailableFrequencies->size();
            //NASHEJ.reserve(SizeNashVect);
            // cout << "SizeNashVect**** " << SizeNashVect <<endl;
            // indexmin = 0;
            double gama = 0.1;
            //remplire le table de NAshj-------------------------------
            for( i = 0; i < trx.AvailableFrequencies->size();i++)
            {
                if (BestObjectivePS != 0)
                {
                    NASHEJ.push_back((paircost[i].first - BestObjectivePI)/BestObjectivePI+ (paircost[i].second - BestObjectivePS)/BestObjectivePS);
                }
                else
                {
                    NASHEJ.push_back((paircost[i].first - BestObjectivePI)/BestObjectivePI);
                }
            }
            //------------------------trouver la meilleur valeur de NAsh (la plus petite)--------------------------
            NASHEbest = NASHEJ.at(0);
            //  cout << "NASHEJ.at(0) ......" <<NASHEJ.at(0)<<endl;
            for( i = 0; i < trx.AvailableFrequencies->size();i++)
            {
                if ( NASHEJ.at(i) <  NASHEbest )//enregistrer cette solution
                {
                    NASHEbest = NASHEJ.at(i);
                    indexNASHEbest = i;
                }
            }
            indexmin = indexNASHEbest;
            //................................................................................
            f=trx.AvailableFrequencies->at(indexmin);//indice de la fréquence ayant un cout minimal,
            //cout << "veccost->at(indexmin)  "<<  veccost->at(indexmin) << endl;
            //-----------------------------------
            //vider la mémoire--vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
            vector<double>().swap(NASHEJ);
            vector < pair<double,double>  >().swap(paircost) ;
             delete(veccost);
            //vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
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
        {// on choisit la meilleur fréquence VALID
            //****************#################################""
        //----------------------
            if(trx.validFrequencies->empty()==false)
            {
                taille =trx.validFrequencies->size();
                vector<double> * veccost = new vector <double>(taille);
                if (taille>1)
                {
                    for(i=0 ;i < taille ; i++)//pour chaque fréquence probable on evalue le cout
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
                        //on évalue la solution avec le nouveau couple : {victimTrx,victimFrequency}
                        for(j=0;j<tempsol->PlanAffect->size();j++)
                        {
                            interfererTrx=tempsol->PlanAffect->at(j).first;
                            interfererFrequency=tempsol->PlanAffect->at(j).second;
                            veccost->at(i) = veccost->at(i)+afpProblem->computeChannelInterference(victimFrequency ,interfererFrequency, victimTrx,interfererTrx);
                            //PSPSPSPSPSPPSPSPSPSPSPSPSPSPSP
                            // calculer le cout de séparation

                            if (victimTrx!=interfererTrx)
                            {if(trx.sectorID == afpProblem->trxs[tempsol->PlanAffect->at(j).first].sectorID )
                            {
                                //cout << "hiiiii i m here we are in the same sector !!!" << endl;
                                if(abs(victimFrequency - tempsol->PlanAffect->at(j).second ) < 3)//contrainte violée
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
                                    if(abs(victimFrequency - tempsol->PlanAffect->at(j).second ) < 2)//contrainte violée
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
                        paircost[i].second = cost;
                        //...................................................................
                        tempsol->PlanAffect->pop_back();//on retire le couple probable apres evaluation de cout et l avoir enregistré dans veccost
                    // cout<<"frequence ::" <<trx.AvailableFrequencies->at(i)<<", son sout veccost[i] ==="<< veccost->at(i)<<endl;
                    } //fortrx.AvailableFrequencies
                    //  vecmin(veccost, indexmin);//indexmin:indice de la fréquencence qui a la valeur minimale
                    //.............................................................................
                    //.......................................................................................
                    //rechercher l indexmin indice de la fréquence dans available frequency qui a
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
                    for( i = 0; i < trx.validFrequencies->size();i++)
                    {
                        if (BestObjectivePS != 0)
                        {
                            NASHEJ.push_back((paircost[i].first - BestObjectivePI)/BestObjectivePI+ (paircost[i].second - BestObjectivePS)/BestObjectivePS);
                        }
                        else
                        {
                            NASHEJ.push_back((paircost[i].first - BestObjectivePI)/BestObjectivePI);
                        }
                    }
  //------------------------trouver la meilleur valeur de NAsh (la plus petite)--------------------------
                    NASHEbest = NASHEJ.at(0);
                    //  cout << "NASHEJ.at(0) ......" <<NASHEJ.at(0)<<endl;
                    for( i = 0; i < trx.validFrequencies->size();i++)
                    {
                        if ( NASHEJ.at(i) <  NASHEbest )//enregistrer cette solution
                        {
                            NASHEbest = NASHEJ.at(i);
                            indexNASHEbest = i;
                        }
                    }
                    indexmin = indexNASHEbest;
                //..............................................................
                //...................................................................................
                    f=trx.validFrequencies->at(indexmin);//indice de la fréquence ayant un cout minimal,
                    // vector<double>().swap(NASHEJ);
                    //vider la mémoire--vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
                    vector<double>().swap(NASHEJ);
                    vector < pair<double,double>  >().swap(paircost) ;
                    delete(veccost);
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
        //delete tempsol;

        }
        else//Availablefrequencies==empty()
        {
            cout<<" la liste des fréquences valide est vide **"<<endl;
        }
            //******************
            //cout<<" la liste des fréquences disponibles est vide **"<<endl;
        }
        vector < pair<double,double>  >().swap(paircost) ;
        delete(tempsol->PlanAffect);

    break;
    }


    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ FRONt PARETO ~~~~~~~~~~~~~~~~~~~~~~
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
     case  +5 ://strategy 5 choisir la meilleur fréquence en terme Front parteo
    {
        int i,k,indexmin;
        Individual * tempsol =  new Individual();int tempfreq;
        tempsol = solution;
        //   tempsol->planCC=NULL;
        //LF comment: on traverse tte les fréquence et on calcule le cout
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
            //vecteur pour enregistrer le couple de cout  interference, separation à la fois

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
                for(i=0 ;i < taille ; i++)//pour chaque fréquence probable on evalue le cout
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
                    //on évalue la solution avec le nouveau couple : {victimTrx,victimFrequency}
                    double cost = 0.0;
                    for(j=0;j<tempsol->PlanAffect->size();j++)
                    {   victimTrx = tempsol->PlanAffect->at(j).first;
                        victimFrequency = tempsol->PlanAffect->at(j).second;
                        for(k = 0 ; k < tempsol->PlanAffect->size() ; k++)
                        {
                            interfererTrx=tempsol->PlanAffect->at(k).first;
                            interfererFrequency=tempsol->PlanAffect->at(k).second;
                            if ( interfererTrx != victimTrx)
                            {veccost->at(i) = veccost->at(i)+ afpProblem->computeChannelInterference(victimFrequency ,interfererFrequency, victimTrx,interfererTrx);
                            //PSPSPSPSPSPPSPSPSPSPSPSPSPSPSP
                            // calculer le cout de séparation
                            if(trx.sectorID == afpProblem->trxs[tempsol->PlanAffect->at(j).first].sectorID )
                            {
                                //cout << "hiiiii i m here we are in the same sector !!!" << endl;
                                if(abs(victimFrequency - tempsol->PlanAffect->at(j).second ) < 3)//contrainte violée
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
                                    if(abs(victimFrequency - tempsol->PlanAffect->at(j).second ) < 2)//contrainte violée
                                    {
                                    // cout << "Oups we have violated co site constraint !!" << endl;
                                        cost = cost + 1.0;
                                    // cout << " csite " << csite<<endl;
                                    }

                                }//if(trx.siteID == afpProblem->trxs[tempsol->PlanAffect->at(j).first].siteID )

                            }//else on n est pas dans le meme site
                        }//if( interfererTrx != victimTrx)
                        }//for(k = 0 ; k < tempsol->PlanAffect->size() ; k++)
                       //PSPSPSPSPSPSPSPSPSPSPSPSPSPSPSPSPSPSPSP
                    }// for(i=0 ;i < taille ; i++)//pour chaque fréquence probable on evalue le cout
                    //.............................................................................
                    // enregister les couts dans le vecteur

                    paircost[i].first = veccost->at(i);
                    paircost[i].second = cost;
                    //...................................................................
                    tempsol->PlanAffect->pop_back();//on retire le couple probable apres evaluation de cout et l avoir enregistré dans veccost
                    // cout<<"frequence ::" <<trx.AvailableFrequencies->at(i)<<", son sout veccost[i] ==="<< veccost->at(i)<<endl;
                } //fortrx.AvailableFrequencies
              // cout <<  "paircost[0].first---------" << paircost[0].first <<endl;
             //  cout <<  "paircost[0].second ---------" << paircost[0].second <<endl;
              //  vecmin(veccost, indexmin);//indexmin:indice de la fréquencence qui a la valeur minimale
                //.............................................................................
                 //afficher les valeurs de veccost

    //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
     //DOMINANCE
   //
                 //...................................................
                 //.....................................................
                // I . Retirer la non dominance pour chaque fréquence
                // ....................................................
                //...................................................

                //je supose que la soluution est domiinée et je vais tester si c est vrai
                int  NonDominantScore;

                vector < pair<int,int> > IndexesFreqsNonDominantes;
                 //(int,int) :: le premier enregistre l index de la fréquence non dominante
                  //(int,int) :: le dexieme , combien de fois la fréquence est non dominante
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
                                     NonDominantScore =   NonDominantScore + 1 ;                                   ;
                                }
                                 IndexesFreqsNonDominantes.push_back({i,NonDominantScore});
                            }//
                            else
                            {
                                if (paircost[i].second <= paircost[j].second) // on teste la non dominance par rapport au deucième objectif
                                {
                                     if (paircost[i].first < paircost[j].first)
                                    {
                                        NonDominantScore =   NonDominantScore    ;                                   ;
                                    }
                                      IndexesFreqsNonDominantes.push_back({i,NonDominantScore});
                                }

                            }
                            //sauvegarder le score
                            //IndexesFreqsNonDominantes[i].second = NonDominantScore;

                        }//i!=j
                    }//fin j

                }//fin i
                //+++++++++++++++++++++++++++++++++++++++Afficher paircost
                 //afficher les valeurs de veccost
            ofstream ResultFile;
            string path="Exemples/veccostPareto_.txt";
            ResultFile.open(path.c_str(),std::ios::app);
            if (!ResultFile) {
                cerr << "Unable to open file!!";
                exit(1);   // call system to stop
            }
            ResultFile << " trx -......" << trx.trxID << endl;
            for(i=0 ;i < trx.AvailableFrequencies->size() ; i++)
            {ResultFile << trx.AvailableFrequencies->at(i) << " :   " << paircost[i].first << " = " << veccost->at(i)<<  ", " << paircost[i].second<<endl;
            }
           //++++++++++++++++++++++++++++++++++++++++++++++++++++++++

                //...................................................
                 //.....................................................
                // II . Trier le tableau de la non dominance selon un ordre croissant
                // ....................................................
                //...................................................
              //  sort(IndexesFreqsNonDominantes.begin(),IndexesFreqsNonDominantes.end(),my_cmp);
              //  cout << "  IndexesFreqsNonDominantes.size() ****"<< IndexesFreqsNonDominantes.size() << endl;


                // copier les solution trouver dans un vecteur avec son cout d interferqunce qui
                vector < pair < int, double> > NonDominanteCost;
                NonDominanteCost.reserve(IndexesFreqsNonDominantes.size());
                for(i = 0; i < IndexesFreqsNonDominantes.size(); i++ )
                {
                    NonDominanteCost.push_back({IndexesFreqsNonDominantes[i].first, paircost[IndexesFreqsNonDominantes[i].first].first });
                }
                // trier le tableau selon un ordre décroisant du cout et retirer la première valeur


                sort(NonDominanteCost.begin(),NonDominanteCost.end(),my_cmpInfDoublePair);
                indexmin = NonDominanteCost.front().first;

     //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

    //cout << "indexmin Dom======" << indexmin << endl;

    //............................End dominance ..................................
    //..............................................................
    //................................................................................
    f=trx.AvailableFrequencies->at(indexmin);//indice de la fréquence recherché

    //+++++++++++++++++++++++++++++++
    ResultFile << endl << " pour le trx " << trx.trxID << "on a choisit la fréquence : " << f << endl;
    ResultFile.close();

    //++++++++++++++++++++
     //vider la mémoire--vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
    vector < pair<double,double>  >().swap(paircost) ;
    delete(veccost);
    delete(tempsol->PlanAffect);
            //vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
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
else//Availablefrequencies==empty() // aucune fréquence n'est diponible j'utilise les fréquence valides
        {// on choisit la meilleur fréquence VALID

            //****************#################################""
        //----------------------
        if(trx.validFrequencies->empty()==false)
        {
            taille =trx.validFrequencies->size();
            vector<double> * veccost = new vector <double>(taille);
            if (taille>1)
            {
                for(i=0 ;i < taille ; i++)//pour chaque fréquence probable on evalue le cout
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
                    //on évalue la solution avec le nouveau couple : {victimTrx,victimFrequency}
                    for(j=0;j<tempsol->PlanAffect->size();j++)
                    {
                        interfererTrx=tempsol->PlanAffect->at(j).first;
                        interfererFrequency=tempsol->PlanAffect->at(j).second;
                        veccost->at(i) = veccost->at(i)+afpProblem->computeChannelInterference(victimFrequency ,interfererFrequency, victimTrx,interfererTrx);

                     //PSPSPSPSPSPPSPSPSPSPSPSPSPSPSP
                        // calculer le cout de séparation
                      if(trx.sectorID == afpProblem->trxs[tempsol->PlanAffect->at(j).first].sectorID )
                        {
                        //cout << "hiiiii i m here we are in the same sector !!!" << endl;
                            if(abs(victimFrequency - tempsol->PlanAffect->at(j).second ) < 3)//contrainte violée
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
                                if(abs(victimFrequency - tempsol->PlanAffect->at(j).second ) < 2)//contrainte violée
                                {
                                    // cout << "Oups we have violated co site constraint !!" << endl;
                                    cost = cost + 1.0;
                                    // cout << " csite " << csite<<endl;
                                }

                            }//if(trx.siteID == afpProblem->trxs[tempsol->PlanAffect->at(j).first].siteID )

                        }//else on n est pas dans le meme site

                       //PSPSPSPSPSPSPSPSPSPSPSPSPSPSPSPSPSPSPSP

                    }
                     //.............................................................................
                    // enregister les couts dans le vecteur

                    paircost[i].first = veccost->at(i);
                    paircost[i].second = cost ;
                    //...................................................................
                    tempsol->PlanAffect->pop_back();//on retire le couple probable apres evaluation de cout et l avoir enregistré dans veccost
                    // cout<<"frequence ::" <<trx.AvailableFrequencies->at(i)<<", son sout veccost[i] ==="<< veccost->at(i)<<endl;
                } //fortrx.AvailableFrequencies
              //  vecmin(veccost, indexmin);//indexmin:indice de la fréquencence qui a la valeur minimale
                  //.............................................................................
                //.......................................................................................
               //rechercher l indexmin indice de la fréquence dans available frequency qui a
               // une distance minimal
               //distance = abs(  paircost.first-paircost.second);
          //..............................................................
                //...................................................................................

 //DOMINANCE--------------------chercher les solution dominantes et l'enregistrer dans les indexes
   //  des fréquences dans le  tableau IndexesFreqsDominantes

                // vector < pair<double,double>  > paircost (trx.AvailableFrequencies->size());
                 //paircost est un vecteur cout: chaque case contient un couple (cout d interference, cout separation)
                 //paircost[i].first : est le cout d interférence en utilisant la frequence d indice i dans la
                 //liste trx.AvailableFrequencies;
                //paircost[i].second : est le cout de séparation en utilisant la frequence d indice i dans la
                 //liste trx.AvailableFrequencies;
                 //...................................................
                 //.....................................................
                // I . Retirer la non dominance pour chaque fréquence
                // ....................................................
                //...................................................

                bool test = true; //je supose que la soluution est domiinée et je vais tester si c est vrai
                int indexdominantf, NonDominantScore;
                indexdominantf = -1;
                vector < pair<int,int> > IndexesFreqsNonDominantes;
                 //(int,int) :: le premier enregistre l index de la fréquence non dominante
                  //(int,int) :: le dexieme , combien de fois la fréquence est non dominante
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
                                     NonDominantScore =   NonDominantScore + 1 ;                                   ;
                                }
                                 IndexesFreqsNonDominantes.push_back({i,NonDominantScore});
                            }//
                            else
                            {
                                if (paircost[i].second <= paircost[j].second) // on teste la non dominance par rapport au deucième objectif
                                {
                                     if (paircost[i].first < paircost[j].first)
                                    {
                                        NonDominantScore =   NonDominantScore   ;                                   ;
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
// copier les solution trouver dans un vecteur avec son cout d interferqunce qui
                vector < pair < int, double> > NonDominanteCost;
                NonDominanteCost.reserve(IndexesFreqsNonDominantes.size());
                for(i = 0; i < IndexesFreqsNonDominantes.size(); i++ )
                {
                    NonDominanteCost.push_back({IndexesFreqsNonDominantes[i].first, paircost[IndexesFreqsNonDominantes[i].first].first });
                }
                // trier le tableau selon un ordre décroisant du cout et retirer la première valeur


                sort(NonDominanteCost.begin(),NonDominanteCost.end(),my_cmpInfDoublePair);
                indexmin = NonDominanteCost.front().first;

     //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    // parmis les solution trouvée IndexesFreqsDominantes dans récupérérer la  fréquence qui a la plus petite valeur decout
  //  cout << "IndexesFreqsDominantesPIPI.size()------- "<< IndexesFreqsNonDominantes.size() << endl;
    /*if (IndexesFreqsNonDominantes.empty() == false)
    {
        indexmin= 0 ;
        double costdom = veccost->at(IndexesFreqsNonDominantes[0]);
        cout <<" costdom ------------" <<costdom << endl;
        // chosir la fréquence avec le pust petit cout
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
    else // si je trouve pas je récupère la fréquence qui a le plus petit cout
    {vecmin(veccost, indexmin);*/
   // vecmin(veccost, indexmin);
   //indexmin = IndexesFreqsNonDominantes[0].first ;
                //................................................................................

//--------------------- dominance available
                //..............................................................
                //...................................................................................
                f=trx.validFrequencies->at(indexmin);//indice de la fréquence ayant un cout minimal,
    //vider la mémoire--vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
    vector < pair<double,double>  >().swap(paircost) ;
    delete(veccost);
    delete(tempsol->PlanAffect);
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
            cout<<" la liste des fréquences valide est vide **"<<endl;
        }
















            //******************
            //cout<<" la liste des fréquences disponibles est vide **"<<endl;
        }
    break;
    }//case 5  : best frequency Front pareto




    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~End Front Pareto
    default :
    {
        cout << "ERREUR de choix dde strategie"<< endl;
        break;
    }//default
   }//finswitch

}//PIChooseFrequency


void PIPlayer::ChooseTrxMostDistant(Individual * solution, AFP * afpProblem,  vector<TRXs> LTrxNTreateds, TRXs &trx)
{

    TRXs trxchoosed,othertrx;

    Individual * tempsol = new Individual();
    tempsol=solution;

    int i,j;
    double distance=0.0;
    //on remplie planaffect pour accelerer la recherche
    tempsol->PlanAffect = new vector< pair<int,int> > ();
    for(i=0;i<tempsol->plan->size();i++)
    {
      if (tempsol->plan->at(i)!=-1)//si la case dans le plan n'est pas vide on remplie le planAffect
      {
        tempsol->PlanAffect->push_back({i,tempsol->plan->at(i)});
      }
    }//    for(i=0;i<tempsol->plan->size();i++)
    //calculer la distance  moyenne par rapport à la solution actuelle
    vector <double> Vdistance;
    Vdistance.reserve(tempsol->PlanAffect->size());

    for(j=0; j<LTrxNTreateds.size();j++)//pour chaque trx nn traité
    {
        trxchoosed = LTrxNTreateds[j];//pour chaque trx dans LTrxNTreateds, on evalue la distance
        distance =0.0;
       // Vdistance[j] = 0.0;
        for(i=0;i<tempsol->PlanAffect->size();i++)
        {
            othertrx = afpProblem->trxs[tempsol->PlanAffect->at(i).first];
            distance = distance + DistancetowTrxs(afpProblem,trxchoosed,othertrx);
        }
        distance = distance/tempsol->PlanAffect->size(); //calculer la distance moyenne de trx choisi avec les autres trx de la solution
        Vdistance.push_back(distance);//on sauvegarde la distance dans le tableau; j est l'index de trx dans LTrxNTreateds
    }//for(j=0; j<LTrxNTreateds.size();j++)
    int indexmax;
    vecmax(Vdistance, indexmax);//retourner l'indeice valeur maximale dans un tableau
    trx = LTrxNTreateds[indexmax];
}

void PIPlayer::PIBestObjective(vector <Individual*> solutionSs, Individual* &BestSol  )
{
    int i, indexbestsol;
    indexbestsol = 0;
    double cost = solutionSs[0]->PIObj;
    for(i=0;i< solutionSs.size();i++)
    {
        if(cost > solutionSs[i]->PIObj)
        {
            cost = solutionSs[i]->PIObj;
            indexbestsol = i;
        }
    }

    BestSol = solutionSs[indexbestsol];

}
>>>>>>> 0514ea9fae0f841576757defb02235a9189b0fad
