<<<<<<< HEAD
#include <iostream>
#include <cstdlib>      // std::rand, std::srand
#include <algorithm>    // std::find
#include <sstream>//LF:convert string
#include <ctime>        // std::time
#include <sstream>//LF:convert string
#include <fstream>
//#include <iterator>
#include "Commun.h"
#include "../Individual/Individual.h"
/*void InitLTrxNTreated(vector<int>* &LTrxNTreated, int m)
 {
            int i;
         for(i=0 ; i<m;i ++) //m le nombre totale de trx
        {
            LTrxNTreated->push_back(i);
             //cout << LTrxNTreated->at(i) << endl;

        }
        //cout << "hiii" << endl;
 }*/
 void InitLTrxNTreatedsV2(vector<int> &LTrxNTreateds, AFP * afpProblem)
 {
       int i,Numbertrx;
       // LTrxNTreateds = afpProblem->trxs;
        Numbertrx = afpProblem->trxs.size();
       // cout << Numbertrx << endl;
       for(i=0;i<  Numbertrx ;i++)
       {
           //LTrxNTreateds[i].AvailableFrequencies=new vector<int>();
          LTrxNTreateds.push_back(i);
        //  LTrxNTreateds.at(i) = i;
         // cout << "LTrxNTreateds[i]" << LTrxNTreateds[i] << endl;
       }
    //   cout <<" LTrxNTreateds.size() " << LTrxNTreateds.size() <<endl;
 }
 //=============================================================
void InitLTrxNTreateds(vector<TRXs> &LTrxNTreateds, AFP * afpProblem)
 {
       int i,Numbertrx;
       // LTrxNTreateds = afpProblem->trxs;
        Numbertrx = afpProblem->trxs.size();
        LTrxNTreateds.reserve(Numbertrx);
       for(i=0;i<  Numbertrx ;i++)
       {
           //LTrxNTreateds[i].AvailableFrequencies=new vector<int>();
         LTrxNTreateds.push_back(afpProblem->trxs[i]);
         //LTrxNTreateds[i] = afpProblem->trxs[i];
       }
      // cout << "LTrxNTreateds[Numbertrx].trxID " << LTrxNTreateds[Numbertrx-1].trxID <<endl;
 }

//------------------------
void AddSolTrxFrequency(AFP* afpProblem, Individual* &Sol,TRXs trx ,int f) //Procédure pour affecter f au trx dans la solution
{
    int i,j;

   /* for(i = 0 ; i <  Sol->plan->size(); i ++)
    {
        oldcost = oldcost + Sol->planCC->at(i);
    }*/

    //°°°°°°°°°°°°°°°°°°°°°°°°°°°Remplir planCC
    // calculer le nouveau cout ------------------------------------
  // double newcost = afpProblem->ComputeSolutionInterference(Sol);
    /* Individual * tempsol =  new Individual();

      tempsol->plan = new vector <int>(Sol->plan->size());
      tempsol->planCC = new vector <double>(Sol->planCC->size());*/
    //------utiliser ma fonction de calcul de cout
      /*  for(i = 0 ; i < Sol->plan->size(); i ++)
        {
            tempsol->plan->at(i) = Sol->plan->at(i);
            tempsol->planCC->at(i) = Sol->planCC->at(i);
            tempsol->PIObj = Sol->PIObj;
            tempsol->PSObj = Sol->PSObj;
        }
           //on remplie planaffect pour accelerer la recherche
            tempsol->PlanAffect = new vector< pair<int,int> > ();
       //int taille =trx.AvailableFrequencies->size();

        for(i=0;i<tempsol->plan->size();i++)
        {
            if (tempsol->plan->at(i)!=-1)//si la case dans le plan n'est pas vide on remplie le planAffect
            {
                tempsol->PlanAffect->push_back({i,tempsol->plan->at(i)});
            }
        }
       cout << "tempsol->PlanAffect->size() " << tempsol->PlanAffect->size() << endl;
        double oldcost = 0.0 ;
        for(i = 0 ; i < tempsol->PlanAffect->size() ; i++)// pour chaque trx on calcule sont cout
        {
            int victimtrx= tempsol->PlanAffect->at(i).first;
            int victimFrequency = tempsol->PlanAffect->at(i).second;
            for(j = 0 ; j < tempsol->PlanAffect->size() ; j++) //
            {
                if ( j != i )
                {
                    int interfererTrx = tempsol->PlanAffect->at(j).first;
                    int interfererFrequency =  tempsol->PlanAffect->at(j).second;
                    oldcost= oldcost + afpProblem->computeChannelInterference(victimFrequency ,interfererFrequency, victimtrx,interfererTrx);
                }

            }
        }
        cout << "oldcost "<< oldcost <<endl;
        delete(tempsol->PlanAffect);*/
        //double oldcost = Sol->PIObj;
        // ajouter la nouvelle fréquence++++++++++++++++++++++++++++++++++++++++++++++++
        Sol->plan->at(trx.trxID) = f;
            //on remplie planaffect pour accelerer la recherche
        //Evaluer le cout +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
       /*tempsol->PlanAffect = new vector< pair<int,int> > ();
       //int taille =trx.AvailableFrequencies->size();

        for(i=0;i<Sol->plan->size();i++)
        {
            tempsol->plan->at(i) = Sol->plan->at(i);
            tempsol->planCC->at(i) = Sol->planCC->at(i);
            tempsol->PIObj = Sol->PIObj;
            tempsol->PSObj = Sol->PSObj;
            if (Sol->plan->at(i)!=-1)//si la case dans le plan n'est pas vide on remplie le planAffect
            {
                tempsol->PlanAffect->push_back({i,tempsol->plan->at(i)});
            }
        }
        //---------------
       cout << "tempsol->PlanAffect->size() " << tempsol->PlanAffect->size() << endl;
        double newcost = 0.0 ;
        for(i = 0 ; i < tempsol->PlanAffect->size() ; i++)// pour chaque trx on calcule sont cout
        {
            int victimtrx= tempsol->PlanAffect->at(i).first;
            int victimFrequency = tempsol->PlanAffect->at(i).second;
            for(j = 0 ; j < tempsol->PlanAffect->size() ; j++) //
            {
                 int interfererTrx = tempsol->PlanAffect->at(j).first;
                int interfererFrequency =  tempsol->PlanAffect->at(j).second;
                if ( victimtrx != victimtrx )
                {
                   newcost= newcost + afpProblem->computeChannelInterference(victimFrequency ,interfererFrequency, victimtrx,interfererTrx);
                }

            }
        }

    cout << "newcost  " << newcost << endl ;
   //----------------------------------------------------------------
    Sol->planCC->at(trx.trxID) = newcost - oldcost;*/
   // cout <<  Sol->planCC->at(trx.trxID)  <<endl;

 //delete(tempsol->PlanAffect);
}
void AddSolTrxFrequencyV2(Individual* &Sol,int trxid ,int f) //Procédure pour affecter f au trx dans la solution
{
    double cost = 0.0;
    Sol->plan->at(trxid) = f;
   // Sol->planCC=NULL;
//Sol->PlanAffect->push_back({trx.trxID,f});
//solution->plan->at(i) = trxs[i].validFrequencies->at(index);

}

//----------------------------------------------------
int FindTrx(vector <TRXs> LTrxNTreateds, TRXs trx)
{
    int i; TRXs t;
    if (LTrxNTreateds.empty() ==true)
    {
        return -1;
    }
    else
    {
        vector<TRXs>::iterator it;i=0;
        for(i=0; i<LTrxNTreateds.size();i++)
        {
            t=LTrxNTreateds[i];
            if (t==trx) return i;
        }

     /*   for (it=LTrxNTreateds.begin();it<LTrxNTreateds.end();it++)
        {
            i=i+1;
            t= LTrxNTreateds.at(i);
            if (t==trx) return i;
        }*/
        if (i == LTrxNTreateds.size()) return -1;
            //return -1;
    }

}
//°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°
int FindTrxV2(vector <int> LTrxNTreateds, TRXs trx)
{
    int i; int t;
    if (LTrxNTreateds.empty() ==true)
    {
        return -1;
    }
    else
    {
        vector<int>::iterator it;i=0;
        for(i=0; i<LTrxNTreateds.size();i++)
        {
            t = LTrxNTreateds[i];
            if (t==trx.trxID) return i;
        }

     /*   for (it=LTrxNTreateds.begin();it<LTrxNTreateds.end();it++)
        {
            i=i+1;
            t= LTrxNTreateds.at(i);
            if (t==trx) return i;
        }*/
        if (i == LTrxNTreateds.size()) return -1;
            //return -1;
    }

}
//-------------------------------------------
int FindTrxID(vector <TRXs> LTrxNTreateds, int indextrx)
{
    int i; TRXs t;
    if (LTrxNTreateds.empty() ==true)
    {
        return -1;
    }
    else
    {
        vector<TRXs>::iterator it;i=0;
        for(i=0; i<LTrxNTreateds.size();i++)
        {
           if (LTrxNTreateds[i].trxID==indextrx) return i;
        }

     /*   for (it=LTrxNTreateds.begin();it<LTrxNTreateds.end();it++)
        {
            i=i+1;
            t= LTrxNTreateds.at(i);
            if (t==trx) return i;
        }*/
        if (i == LTrxNTreateds.size()) return -1;
            //return -1;
    }

}



//-------------------------------------------
void UpdateLTrxNTreateds(vector <TRXs> &LTrxNTreateds, TRXs trx,int Update)
{

//tester d'abords si le trx n'esiste pas
    vector<int>::iterator it;int tt=0; vector<int> v;
    //it = LTrxNTreateds.begin();
   // int tt =it->trxID;
  //  cout <<" it->trxID " << it->trxID<<endl;
int i;
//TRXs t=trx;

 //it = find(LTrxNTreateds.begin(),LTrxNTreateds.end(),trx);
 // it = find(v.begin(),v.end(),1);

   // cout <<"existe"<<endl;

    switch(Update)
            {
                case  +1 ://ajout du trx
                    // cout << "Ajout du trx" << endl;
                    if (FindTrx(LTrxNTreateds, trx)==-1)//le trx n'exite pas on l'ajoute
                    {
                       LTrxNTreateds.push_back(trx);
                        break;
                    }
                    else
                    {
                        break;
                        //cout << "Le trx existe déjà! " << endl;
                    }
                case  -1 :
                    //cout << "Suppression du trx" << endl;
                   if(FindTrx(LTrxNTreateds, trx)!=-1)//Le trx existe on le supprime
                    {
                        int index =FindTrx(LTrxNTreateds, trx);
                        LTrxNTreateds.erase(LTrxNTreateds.begin()+index);
                        break;
                    }
                    else
                    {
                        break;
                       // cout << "Le trx n existe pas " << endl;
                    }
                default :
                    cout << "ERREUR de mise à jour de la liste de la liste des trx traités"<< endl;
                    break;
            }

}
//°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°
void UpdateLTrxNTreatedsV2(vector <int> &LTrxNTreateds, TRXs trx,int Update)
{

//tester d'abords si le trx n'esiste pas
    vector<int>::iterator it;int tt=0; vector<int> v;
    //it = LTrxNTreateds.begin();
   // int tt =it->trxID;
  //  cout <<" it->trxID " << it->trxID<<endl;
int i;
//TRXs t=trx;

 //it = find(LTrxNTreateds.begin(),LTrxNTreateds.end(),trx);
 // it = find(v.begin(),v.end(),1);

   // cout <<"existe"<<endl;

    switch(Update)
            {
                case  +1 ://ajout du trx
                    // cout << "Ajout du trx" << endl;
                    if (FindTrxV2(LTrxNTreateds, trx)==-1)//le trx n'exite pas on l'ajoute
                    {
                       LTrxNTreateds.push_back(trx.trxID);
                        break;
                    }
                    else
                    {
                        break;
                        //cout << "Le trx existe déjà! " << endl;
                    }
                case  -1 :
                    //cout << "Suppression du trx" << endl;
                   if(FindTrxV2(LTrxNTreateds, trx)!=-1)//Le trx existe on le supprime
                    {
                        int index =FindTrxV2(LTrxNTreateds, trx);
                        LTrxNTreateds.erase(LTrxNTreateds.begin()+index);
                        break;
                    }
                    else
                    {
                        break;
                       // cout << "Le trx n existe pas " << endl;
                    }
                default :
                    cout << "ERREUR de mise à jour de la liste de la liste des trx traités"<< endl;
                    break;
            }

}
//--------------------------------------
bool operator==( const TRXs &b1, const TRXs &b )
{
        return (b1.trxID== b.trxID) && (b1.sectorID == b.sectorID) && (b1.siteID == b.siteID) &&
	(b1.type == b.type) && (b1.validFrequencies ==b.validFrequencies)	&& (b1.validFrequenciesSet == b.validFrequenciesSet);

}
//------------------------------
void UpdateTRxFrequencyEraseAdj(TRXs &trx, int f)
{
    int freq;
    int indexf=FindFrequency(trx.AvailableFrequencies,f);
    if (indexf!=-1)//la fréquence existe
    {
       trx.AvailableFrequencies->erase( trx.AvailableFrequencies->begin()+indexf);
    }
    freq = f - 1;
    indexf = FindFrequency(trx.AvailableFrequencies,freq);
    if (indexf!=-1)//la fréquence existe
    {
       trx.AvailableFrequencies->erase( trx.AvailableFrequencies->begin()+indexf);
    }
    //suppression des fréquence adjacente de f
    freq = f + 1;
    indexf=FindFrequency(trx.AvailableFrequencies,freq);
    //cout << "indexf "  <<indexf <<endl;
    if (indexf!=-1)//la fréquence existe
    {
       trx.AvailableFrequencies->erase( trx.AvailableFrequencies->begin()+indexf);
    }
}

//--------------
 void UpdateTRxFrequencyNew(vector<TRXs> LTrxNTreateds,AFP * afpProblem,TRXs &trx, int f,int Update)
 //supprimes f de la liste disponibles de tous les trx sui sont dans le meme secteur que le trx "trx"
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
                    UpdateTRxFrequencyEraseAdj(trx, f);
                    for(i=0; i<LTrxNTreateds.size();i++)
                    {
                        othertrxId = LTrxNTreateds[i];
                        if(trx.sectorID == afpProblem->trxs[othertrxId.trxID].sectorID)
                        {
                            UpdateTRxFrequencyEraseAdj(othertrxId, f);
                        }//  if(trx.sectorID == afpProblem->trxs[othertrxId.trxID].sectorID)
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
            cout<<" ERREUR de mise à jour de fréquence !!"<<endl;
            break;
        }//default switch

    }//fin switch

 }// fin procedure de mise à jour
 //°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°
 void UpdateTRxFrequencyNewV2(vector<int> LTrxNTreateds,AFP * afpProblem,TRXs &trx, int f,int Update)
 //supprimes f de la liste disponibles de tous les trx sui sont dans le meme secteur que le trx "trx"
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
                    UpdateTRxFrequencyEraseAdj(trx, f);
                    for(i=0; i<LTrxNTreateds.size();i++)
                    {
                        othertrxId = afpProblem->trxs[LTrxNTreateds[i]];
                        if(trx.sectorID == afpProblem->trxs[othertrxId.trxID].sectorID)
                        {
                            UpdateTRxFrequencyEraseAdj(othertrxId, f);
                        }//  if(trx.sectorID == afpProblem->trxs[othertrxId.trxID].sectorID)
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
            cout<<" ERREUR de mise à jour de fréquence !!"<<endl;
            break;
        }//default switch

    }//fin switch

 }// fin procedure de mise à jour
//°°°°°°°°°°°°°°°°°°°°°°°°°°Ajouté le 26-3-2019°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°
//°°°°°°°°°°°° On enlève la fréquence aussi des trx qui sont dans les secteurs voisins (1 saut) °°°°°°°°°°°°°
 void UpdateTRxFrequencyV3(vector<TRXs> LTrxNTreateds,AFP * afpProblem,TRXs &trx, int f,int Update)
 {
                int i,j,k,SectTrx;

                  SectTrx = trx.sectorID ;
                  int NumberSectNeighbors = afpProblem->neighbors[SectTrx].size();
                // cout << " afpProblem->neighbors[SectTrx].size() " << afpProblem->neighbors[SectTrx].size() <<endl;// contient tous les voisins du secteurSectTrx


                  //cout << "Mise à jour de la frequence 592---- " << endl;
                 UpdateTRxFrequencyNew(LTrxNTreateds,afpProblem,trx,f,Update);
                         /* for(k = 0; k < trx.AvailableFrequencies->size(); k++)
                            cout << " trx.AvailableFrequencies->at( " << k << ")= " << trx.AvailableFrequencies->at(k) << "," <<  endl; */
                 for(i = 0 ; i < NumberSectNeighbors ; i ++  )
                 {
                    int SectTrxNeighbor;
                    SectTrxNeighbor =  afpProblem->neighbors[SectTrx].at(i);
                  //  cout << "le premier sect voisin "<< SectTrxNeighbor << endl;
                    int NumberTrxSectNeighbors = afpProblem->sectors2trxs[SectTrxNeighbor].size();
                    //cout << "le nombre de trx dans ce secteur est =" << NumberTrxSectNeighbors << endl;
                    for (j = 0 ; j < NumberTrxSectNeighbors; j++ )
                    {
                        TRXs trxSectNeighbor;
                        trxSectNeighbor.trxID = afpProblem->sectors2trxs[SectTrxNeighbor].at(j);
                        trxSectNeighbor = afpProblem->trxs[trxSectNeighbor.trxID];//recuperer un trx du secteur voisin
                     //   cout << "le premieir  trx dans le premier  secteur voisin est " << trxSectNeighbor.trxID << endl;
                        //------------ verifier la mise à jour de la liste des fréquence dans un trx et dans son voisi
                        //trx == 0 et son voisin 62
                        /*cout << "********** avant le premier voisin de trx 0  est  62 *************************"  << endl;
                        for(k= 0; k < trxSectNeighbor.AvailableFrequencies->size(); k++)
                            cout << " trxSectNeighbor.AvailableFrequencies->at( " << k << ")= " << trxSectNeighbor.AvailableFrequencies->at(k) << "," <<  endl;
                        cout << "aprs Mise à jour de la frequence 592---- " << endl;*/
                        UpdateTRxFrequencyNew(LTrxNTreateds,afpProblem,trxSectNeighbor,f,Update);
                       /* for(k= 0; k < trxSectNeighbor.AvailableFrequencies->size(); k++)
                            cout << " trxSectNeighbor.AvailableFrequencies->at( " << k << ")= " << trxSectNeighbor.AvailableFrequencies->at(k) << "," <<  endl;*/
                    }
                }


 }
 //°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°
 void UpdateTRxFrequencyV32(vector<int> LTrxNTreateds,AFP * afpProblem,TRXs &trx, int f,int Update)
 {
                int i,j,k,SectTrx;

                  SectTrx = trx.sectorID ;
                  int NumberSectNeighbors = afpProblem->neighbors[SectTrx].size();
                // cout << " afpProblem->neighbors[SectTrx].size() " << afpProblem->neighbors[SectTrx].size() <<endl;// contient tous les voisins du secteurSectTrx


                  //cout << "Mise à jour de la frequence 592---- " << endl;
                 UpdateTRxFrequencyNewV2(LTrxNTreateds,afpProblem,trx,f,Update);
                         /* for(k = 0; k < trx.AvailableFrequencies->size(); k++)
                            cout << " trx.AvailableFrequencies->at( " << k << ")= " << trx.AvailableFrequencies->at(k) << "," <<  endl; */
                 for(i = 0 ; i < NumberSectNeighbors ; i ++  )
                 {
                    int SectTrxNeighbor;
                    SectTrxNeighbor =  afpProblem->neighbors[SectTrx].at(i);
                  //  cout << "le premier sect voisin "<< SectTrxNeighbor << endl;
                    int NumberTrxSectNeighbors = afpProblem->sectors2trxs[SectTrxNeighbor].size();
                    //cout << "le nombre de trx dans ce secteur est =" << NumberTrxSectNeighbors << endl;
                    for (j = 0 ; j < NumberTrxSectNeighbors; j++ )
                    {
                        TRXs trxSectNeighbor;
                        trxSectNeighbor.trxID = afpProblem->sectors2trxs[SectTrxNeighbor].at(j);
                        trxSectNeighbor = afpProblem->trxs[trxSectNeighbor.trxID];//recuperer un trx du secteur voisin
                     //   cout << "le premieir  trx dans le premier  secteur voisin est " << trxSectNeighbor.trxID << endl;
                        //------------ verifier la mise à jour de la liste des fréquence dans un trx et dans son voisi
                        //trx == 0 et son voisin 62
                        /*cout << "********** avant le premier voisin de trx 0  est  62 *************************"  << endl;
                        for(k= 0; k < trxSectNeighbor.AvailableFrequencies->size(); k++)
                            cout << " trxSectNeighbor.AvailableFrequencies->at( " << k << ")= " << trxSectNeighbor.AvailableFrequencies->at(k) << "," <<  endl;
                        cout << "aprs Mise à jour de la frequence 592---- " << endl;*/
                        UpdateTRxFrequencyNewV2(LTrxNTreateds,afpProblem,trxSectNeighbor,f,Update);
                       /* for(k= 0; k < trxSectNeighbor.AvailableFrequencies->size(); k++)
                            cout << " trxSectNeighbor.AvailableFrequencies->at( " << k << ")= " << trxSectNeighbor.AvailableFrequencies->at(k) << "," <<  endl;*/
                    }
                }


 }
//°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°
//°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°
//------------------------------------------
 void UpdateTRxFrequency(TRXs &trx, int f,int Update)
{
//tester d'abords si la fréquence n'est pas bloquée
    vector<int>::iterator it;//int x;
    if(trx.AvailableFrequencies->empty()==false)//je traite uniqueement si la liste des fréquense disponible n est pas vide
    {
        it = std::find (trx.validFrequencies->begin(), trx.validFrequencies->end(),f);

        //else
        // on  traite si la fréquence n est pas bloquée
       if(it!=trx.validFrequencies->end())//la fréquence n'est pas bloqué
        {// on vérifie si la valeur de update est différente que +1 ou -1 alors erreur

            //f=f;
             switch(Update)
                {
                    case  +1 :
                    {
                        //cout << "Ajout de la fréquence au trx" << endl;
                        //vérifier si la fréquence n'existe pas dans la liste disponible
                        it = std::find (trx.AvailableFrequencies->begin(), trx.AvailableFrequencies->end(),f);
                        if (it==trx.AvailableFrequencies->end())//la fréquence n'existe pas on l'ajoute
                        {
                            trx.AvailableFrequencies->push_back(f);
                        }
                        break;
                    }//end case +1
                case  -1 :
                {
                    //cout << "Suppression de la fréquence du trx" << endl;
                    //on supprime si la lise des fréquences disponible n'est pas vide


                            int indexf=FindFrequency(trx.AvailableFrequencies,f);
                            if (indexf!=-1)//la fréquence existe
                            {
                                trx.AvailableFrequencies->erase( trx.AvailableFrequencies->begin()+indexf);
                            }

                        //f=f;

                    break;
                }//case
                default ://Update != 1 et Update != -1 :Errieu de mise à jour
                cout << "ERREUR de mise à jour de la liste des fréquences disponible du trx"<< endl;
            }//switch


         }// if(it!=trx.validFrequencies->end())//la fréquence est valide


    }// if(trx.AvailableFrequencies->empty()==false)

}
//-------------------------------------------------------
//---mettre à jour la liste de fréquence disponible de tous les trx non traité
void UpdateAllTRxFrequency(vector <TRXs> &LTrxNTreateds,int  f, int Update)
{
     //cout<<"hi"<<endl;

    if (LTrxNTreateds.empty()==false)
    //if(Update==1)
    {
        switch(Update)
        {
            case  +1 :
            {
                break;

            }//end case +1
            case -1:
            {
                int i;
               // cout<<"hi"<<endl;
                for(i=0;i<LTrxNTreateds.size();i++)
                {
                   if (LTrxNTreateds[i].AvailableFrequencies->size()>1)//on supprime uniquement si la taille >1
                   {
                        UpdateTRxFrequency(LTrxNTreateds[i],f,-1);
                   }

                    //cout<<"hi"<<endl;
                   // break;
                }
                break;
            }//endcase
            default:
            cout << "ERREUR de mise à jour de la liste des fréquences disponible de TOUT les trxs"<< endl;
        }//switch
    }//if LTrxNTreateds.empty()==false)


}//end UpdateAllTRxFrequency(vector <TRXs> &LTrxNTreateds,int  f, int upadate)





//--------------------------------------------------------------------
/*void UpdateTRxFrequency1(TRXs &trx, int f,int Update)
{
//tester d'abords si la fréquence n'est pas bloquée
int exist,blocked;
   blocked = blockedFrequency(trx,f);
    if (blocked==+1)//la fréquence est dans la liste blouqé du trx
    {cout << " LA fréquence est dans la liste des fréquences bloquées " << endl;}

    else
    {// on vérifie si la valeur de update est différente que +1 ou -1 alors erreur
        try
        {
            switch(Update)
            {
                case  +1 :
                     //cout << "Ajout de la fréquence au trx" << endl;
                     //vérifier si la fréquence n'existe pas dans la liste disponible
                     exist = FindFrequency(trx.AvailableFrequencies,f);
                    if (exist==-1)//la fréquence n'existe pas on l'ajoute
                    {
                       trx.AvailableFrequencies->push_back(f);

                    }
                    break;
                case  -1 :
                    cout << "Suppression de la fréquence du trx" << endl;
                      exist = FindFrequency(trx.AvailableFrequencies,f);

                    if (exist!=-1)//la fréquence est dans la listedisponible  du trx on l a supprime
                    {
                       trx.AvailableFrequencies->erase(trx.AvailableFrequencies->begin()+exist);
                       //trx.AvailableF->erase(trx.AvailableF->begin()+exist);
                       //cout<<"why"<<endl;
                    }
                    break;
                default ://Update != 1 et Update != -1 :Errieu de mise à jour
                    cout << "ERREUR de mise à jour de la liste des fréquences disponible du trx"<< endl;
            }
        }
        catch(const char* msg)
        {
            cout << msg << endl;
        }
    }
}*/



//--------------------------------------------------------------------

int FindFrequency(vector<int>* vectFrequency, int f)
{
    int i;
    for(i=0; i<vectFrequency->size();i++)
        {
            if (vectFrequency->at(i)==f) return i;
        }
        if (i == vectFrequency->size()) return -1;

}
int blockedFrequency(TRXs trx,int f)
{
    int i;
     for(i=0; i<trx.validFrequencies->size();i++)
        {
            if (trx.validFrequencies->at(i)==f) return -1;//la fréquence n'est pas bloquée
        }
        //if (i == trx.validFrequencies->size()) return +1;
        return +1;
}
//----------------------------
void vecmaxInt(vector<int> x, int & indexmax) {
  // Rcpp supports STL-style iterators
 /*vector<double>::iterator it = min_element(x.begin(), x.end());
  // we want the value so dereference
 return it - x.begin();;*/
  int i;int couts;
 if (x.empty()==false)
 {

  couts=x.at(0);indexmax=0;

 for(i=0;i>x.size();i++)
 {
     if(couts< x.at(i))
     {
         indexmax =i;
         couts=x.at(i);

     }
 }

 }
 else
 {
     indexmax = -1;
 }


}
void vecminInt(vector<int> x, int & indexmin) {
  // Rcpp supports STL-style iterators
 /*vector<double>::iterator it = min_element(x.begin(), x.end());
  // we want the value so dereference
 return it - x.begin();;*/
  int i;int couts;
 if (x.empty()== false)
 {
   couts=x.at(0);indexmin = 0;
    for(i=0;i<x.size();i++)
    {
        if(couts> x.at(i))
        {
            indexmin =i;
            couts=x.at(i);
        }
    }
 }
 else
 {
     indexmin = -1; // vecteur vide
 }


}
//--------------------------------------------
void vecmin(vector<double>* x, int & indexmin) {
  // Rcpp supports STL-style iterators
 /*vector<double>::iterator it = min_element(x.begin(), x.end());
  // we want the value so dereference
 return it - x.begin();;*/
  int i;double couts;
 if (x->empty()==false)
 {

  couts=x->at(0);indexmin=0;

 for(i=0;i<x->size();i++)
 {
     if(couts> x->at(i))
     {
         indexmin =i;
         couts=x->at(i);

     }
 }

 }
 else
 {
     indexmin = -1;
 }


}
//======================================
//--------------------------------------------
void VecMinValue(vector<double> x, int &index)
{
  // Rcpp supports STL-style iterators
    /*vector<double>::iterator it = min_element(x.begin(), x.end());
  // we want the value so dereference
    return it - x.begin();;*/
    int i;
    double couts;
    index = 0;
    couts = x[0];
    int taille = x.size();
    //cout << "couts" << couts <<endl;
    for(i = 1 ; i < taille ; i++)
    {
            if(couts > x[i])
            {
                index =  i;
                couts   =   x[i];
                            //cout << "hiiiiiiiiiiiii" <<endl;
            }

    }

}
//--------------------------------------------
void ShowResult(int ApproachGameEvaluation,string instance,int NumGame,double elapsed_secs,const int  max_gen,const double epsilon,vector<Individual*> solutionSs,int indexNASHEbest,vector <double> NASHEJ,vector<Individual*> BestsolutionSs, Individual* solution, string path, double HV)
{

    cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
  cout << " au niveau commum indexNASHEbest= " << indexNASHEbest <<endl;
      cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
    //ecrire le résultat dans un fichier : Resultat/resultatDatesystem.txt
    int k,j;
    ofstream ResultFile;
        ResultFile.open(path.c_str(),std::ios::app);
    if (!ResultFile) {
        cerr << "Unable to open file!!";
        exit(1);   // call system to stop
    }
    //rechercher la meilleur solution pour le joueur PI
      vector<double> VectBestSolPI;
         VectBestSolPI.reserve(max_gen);
        for(k = 0 ; k < solutionSs.size(); k++)
        {
            //cout<< " solutionSs[k]->PIObj " <<solutionSs[k]->PIObj <<endl;
            VectBestSolPI.push_back(solutionSs[k]->PIObj);
            //cout << "VectBestSolPI(k) " << VectBestSolPI[k] <<endl;
        }

      int  indexBestSolPI = 0;
        double BestObjectivePI = 0.0;
       // cout << " VectBestSolPI.size() " << VectBestSolPI.size() << endl;
        VecMinValue(VectBestSolPI,indexBestSolPI);
       // cout << "indexBestSolPI : " << indexBestSolPI << endl;
        BestObjectivePI = solutionSs[indexBestSolPI]->PIObj;
         vector<double> VectBestSolPS;
         VectBestSolPS.reserve(max_gen);
        for(k = 0 ; k < solutionSs.size(); k++)
        {
            //cout<< " solutionSs[k]->PIObj " <<solutionSs[k]->PIObj <<endl;
            VectBestSolPS.push_back(solutionSs[k]->PSObj);
            //cout << "VectBestSolPI(k) " << VectBestSolPI[k] <<endl;
        }

       int indexBestSolPS = 0;
        double BestObjectivePS = 0.0;
       cout << " VectBestSolPI.size() " << VectBestSolPI.size() << endl;
        VecMinValue(VectBestSolPS,indexBestSolPS);
        cout << "indexBestSolPI : " << indexBestSolPI << endl;
        BestObjectivePS = solutionSs[indexBestSolPS]->PSObj;
        //=========================================================================

     ResultFile << "Temps d'execution : "<<elapsed_secs << " ms" << endl;
    ResultFile <<" ========Hypervolume====" << endl;
    ResultFile << " HV % :" << HV << endl;
    ResultFile <<" ========================" << endl;
   // ResultFile <<"....................... Sans Nash coût séparé......."<<endl;
    ResultFile << "(IC best ; SC best) : " <<  BestObjectivePI  <<  " ; " << BestObjectivePS << endl;
    ResultFile <<" Min Nash :   " << NASHEJ[indexNASHEbest] << " : se trouve à la position " << indexNASHEbest <<  endl;


    ResultFile <<" ============================" << endl;
   // ResultFile<<" La valeur de nash est : "  << NASHEJ[indexNASHEbest]<<endl;
   /* ResultFile << "Meiilleur Interference score en utilisant NASH est : CI " << solution->PIObj<<endl;//<< solutionSs[indexNASHEbest]->PIObj << endl;
    ResultFile << "Meiilleur Separation score est en utilisant NASH:   CS "<< solution->PSObj<<endl;//solutionSs[indexNASHEbest]->PSObj << endl;
  */
    //ResultFile <<"------------------ Valeur de --------------"<<endl;
   // ResultFile <<" Min nash   " << NASHEJ[indexNASHEbest] << " : se trouve à la position " << indexNASHEbest <<  endl;

    //ResultFile <<" =============================" << endl;

    //----------------------------------------------
    //ResultFile << "Temps d'execution : "<<elapsed_secs << " ms" << endl;

   // ResultFile << "---- vecteur solution ---"<<endl;
   // ResultFile << "TRX ID" <<" , " <<"Frequency"<<endl;

    /*
   for(k=0;k<max_gen; k++)
    {
        ResultFile << " NASHEJ[ " << k << " ] : " << NASHEJ[k] << endl;
        ResultFile << " ------------" << endl;
        ResultFile << " PI Objectif solutionSs[k]->PIObj : " << solutionSs[k]->PIObj<<endl;
        ResultFile << " PS Objectif solutionSs[k]->PSObj : " << solutionSs[k]->PSObj<<endl;
        ResultFile << "................................." << endl;


    }
        ResultFile <<"-----------" << endl;
        */


   // ResultFile <<" la meilleur solution corrspond au  NASHEJ[ "<< indexNASHEbest<<"] : " <<NASHEJ.at(indexNASHEbest)<<endl;
    ResultFile <<"########################################################"<<endl;
   // ResultFile << "  LEs meilleurs solutions trouvées  " <<endl;
    ResultFile << "Le nombre de solutions trouvées : " << BestsolutionSs.size() << ". Ces solutions sont : " << endl;


    for(k=0  ;k < BestsolutionSs.size(); k++)
    {
      //  ResultFile<<" ***********solution : " << k << "*******************" << endl;
        ResultFile<<" (IC ; SC) : " << BestsolutionSs[k]->PIObj << " ; " << BestsolutionSs[k]->PSObj << endl;
       // ResultFile<<" Coût de séparation " << BestsolutionSs[k]->PSObj << endl;
       // ResultFile<<" Valeur de Nash  " << NASHEJ[k]  << endl;
    }
     ResultFile <<"#########################" << endl << endl;
    //==================================================
    ResultFile <<"......Les valeurs de nash pour Tout l'ensemble des solutions..." <<  endl << endl;
    ResultFile<<"Num Sol, NASHEJ[k] , Interf cost , Sep cost " << endl << endl;
       ResultFile <<".........................." << endl << endl;


         for(k=0  ;k < NASHEJ.size(); k++)
    {
        //ResultFile<<" ***********solution : " << k << "*******************" << endl;
        //ResultFile<<" NASHEJ[" << k <<"] : " << NASHEJ[k] << ", Interf cost " << solutionSs[k]->PIObj <<", Sep cost "<< solutionSs[k]->PSObj<<endl;
        ResultFile << k << " , " << NASHEJ[k] << " , " << solutionSs[k]->PIObj <<  " , " << solutionSs[k]->PSObj << endl;

       // ResultFile<<"................................."<<endl;


    }


    ResultFile.close();
    //***********************************************************
}





//=========================================
//---------------------------------

void vecmax(vector<double> x, int & indexmax)//retourner la valeur maximale dans un tableau
{
    int i;double couts;
    if (x.empty()==false)
    {
        couts=x.at(0);indexmax=0;
        for(i=0;i<x.size();i++)
        {
            if(couts < x.at(i))
            {
                indexmax =i;
                couts=x.at(i);
            }
        }//for
    }
    else
    {
        indexmax = -1;
    }


}
//-----------------------
void vecmaxptr(vector<double>* x, int & indexmax)//retourner la valeur maximale dans un tableau
{
    int i;double couts;
    if (x->empty()== false)
    {
        couts = x->at(0);
        indexmax = 0;
        for(i=0;i < x->size();i++)
        {
            if(couts < x->at(i))
            {
                indexmax = i;
                couts = x->at(i);
            }
        }//for
    }
    else
    {
        indexmax = -1;
    }


}
//------------------------------------
int FindTrxFirstNeighbor(AFP * afpProblem,int sect,int sectneighbor)
{


 /*
   	for (int i = 0; i < numberOfNeighbors; i++) {
  		file >> neighbor;
  		neighbors[sector].push_back(neighbor);
  	} //for

  */
    int i;
   // int test = -1;
    for(i=0;i<afpProblem->neighbors[sect].size();i++)
    {
        //test = 1;
        map<int, vector<int> > neighbor = afpProblem->neighbors;
       if(neighbor[sect].at(i)==sectneighbor)
        {
            return i;
        }
    }
    return -1;
}
//-----------------------------
int FindTrxSecondNeighbor(AFP * afpProblem,int sect,int sectneighbor)
{


 /*
   	for (int i = 0; i < numberOfNeighbors; i++) {
  		file >> neighbor;
  		neighbors[sector].push_back(neighbor);
  	} //for

  */
    int i;
   // int test = -1;
    for(i=0;i<afpProblem->secondNeighbors[sect].size();i++)
    {
        //test = 1;
        map<int, vector<int> > secondneighbor = afpProblem->secondNeighbors;
       if(secondneighbor[sect].at(i)==sectneighbor)
        {
            return i;
        }
    }
    return -1;
}

double DistancetowTrxs(AFP * afpProblem,TRXs trxone, TRXs trxtwo)
{

    int test;
    if (trxone.sectorID==trxtwo.sectorID)//les dex trx sont dans le meme secteur
    {
        return 0.0;
    }
    else
    {
       test = FindTrxFirstNeighbor(afpProblem,trxone.sectorID,trxtwo.sectorID);
        if(test!=-1)
        {
            return 1.0;
        }
        else
        {
            test = FindTrxSecondNeighbor(afpProblem,trxone.sectorID,trxtwo.sectorID);
            if(test!=-1 )
            {
                return 2.0;
            }
            else
            {
                return 3.0;
            }
        }
    }


}
//°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°
//°°°°°°°°°°°°°°°°°°°°°°° Ajouté le 20/4/2019  °°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°
void Normalize(vector<pair<double,double> > &paircost, pair<double,double> MinT, pair<double,double> MaxT)
{
    int i;
    for(i = 0 ; i< paircost.size() ; i++)
      {
          paircost.at(i).first = (paircost.at(i).first - MinT.first)/(MaxT.first-MinT.first);
          paircost.at(i).second = (paircost.at(i).second - MinT.second)/(MaxT.second-MinT.second);
      }
}
void NormalizeV2(vector<pair<double,double> > &paircost, pair<double,double> &R)
{
    int i;

    //1. retirer le maximum et le minimum du table
    double costminFirst = paircost.at(0).first;//A
    double costmaxFirst = paircost.at(0).first;//B
    double costminSecond = paircost.at(0).second;//A
    double costmaxSecond = paircost.at(0).second;//B


    for(i = 0 ; i< paircost.size() ; i++)
      {
        if(costminFirst > paircost.at(i).first) costminFirst = paircost.at(i).first;
        if(costmaxFirst< paircost.at(i).first) costmaxFirst = paircost.at(i).first;
        if(costminSecond> paircost.at(i).second) costmaxSecond = paircost.at(i).second;
        if(costmaxSecond< paircost.at(i).second) costmaxSecond = paircost.at(i).second;
      }
    //2  les bornes [0,1]
    double a = 0.0;
    double b = 1.0 ;
 //3.Normalisation

    cout << "costmaxFirst" << costmaxFirst<<endl;
    cout << "costmaxSecond " << costmaxSecond <<endl;
    cout << "costminFirst" << costminFirst<<endl;
    cout << "costminSecond " << costminSecond <<endl;



    for(i = 0 ; i< paircost.size() ; i++)
      {
          if ((costmaxFirst!= 0 ) and (costminFirst!= 0))
          {
            if (costmaxFirst > costminFirst)
            {
                paircost[i].first = a + (paircost[i].first - costminFirst)*(b-a)/(costmaxFirst - costminFirst);
            }
            else
            {
                paircost[i].first = 0.0;
            }
         if (costmaxSecond > costminSecond)
            {
                paircost[i].second = a+ (paircost[i].second - costminSecond)*(b-a)/(costmaxSecond - costminSecond );
            }
            else
            {
                 paircost[i].second = 0.0;
            }
        }
      }
     if ((costmaxFirst!= 0 ) and (costminFirst!= 0))
     {
        R.first  = a + (R.first - costminFirst)*(b-a)/(costmaxFirst - costminFirst);
        R.second  = a + (R.second - costminFirst)*(b-a)/(costmaxFirst - costminFirst);
     }
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++
double Hypervolume(vector < pair< double, double> > paircost , pair < double,double> R)
{
    int i;
    double HV = 0.0 ; //hypervolume
    HV = (R.first - paircost.at(0).first)* (R.second - paircost.at(0).second);
      for(i = 1 ; i < paircost.size() ; i++)
      {
          HV = HV + (R.first - paircost.at(i).first)* (paircost.at(i-1).second- paircost.at(i).second) ;
          cout << "HV " << HV << endl;
      }
      return HV;
}
//=========================================================================================
void ShowSolution(int StrategyTrxPI,int StrategyTrxPS, Individual* Sol,int ApproachGameEvaluation,string instance,double elapsed_secs,const int  max_gen,const double  epsilon)
{
    ofstream ResultFile;
    string path="Resultats/Solution";
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

   /* int sec =timeinfo->tm_sec;
    temp<<"_";
    temp<<sec;
    temp<<"sec";*/

     stringstream sss;
    stringstream ssss;
    stringstream sssss;
    stringstream strategytrxpi;
     stringstream strategytrxps;
     stringstream sinstance;
    sss << max_gen;
    ssss << epsilon;
     sssss << ApproachGameEvaluation;
strategytrxpi <<StrategyTrxPI;
strategytrxps << StrategyTrxPS;
sinstance << instance;
    path = path+ sinstance.str()+"_TRXPIPS_"+strategytrxps.str()+ strategytrxps.str()+"_Evaluation_"+sssss.str()+"_epsilon"+ssss.str()+"_gen_" + sss.str()+temp.str()+".txt";


    path = path+temp.str()+".txt";      //str is temp as string
    ResultFile.open(path.c_str(),std::ios::app);

    if (!ResultFile) {
        cerr << "Unable to open file!!";
        exit(1);   // call system to stop
    }
    ResultFile <<" ===========================solution detailed ===========================================" << endl;
    ResultFile << " °°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°° " << endl << endl;
    ResultFile<< " °°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°° " << endl;
    int i;
    for(i = 0 ; i < Sol->plan->size(); i ++)
    {
        ResultFile << " TRX: " << i << " a pris la fréquence: "  << Sol->plan->at(i) <<endl;
         ResultFile << " TRX: cout parttiel " << Sol->planCC->at(i).first << " ; " << Sol->planCC->at(i).second << endl;
    }
    ResultFile<< " °°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°° " << endl << endl;
    ResultFile << " °°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°° " << endl;
    ResultFile.close();
}
//================================================================================================
//=================== Ajout 16-6- 2021 ======================================
int GetSolutionRealSize(Individual* Sol)
{
    int i, taille;
    taille = 0;
    for (i = 0; i< Sol->plan->size(); i++)
    {
        if(Sol->plan->at(i)!=-1)
        {
            taille = taille + 1;
        }
    }
    return taille ;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Ajouter le 27 -6-2021 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void ShowPlayerInterventionOrder(Individual* Sol,int ApproachGameEvaluation,string instance,double elapsed_secs,const int  max_gen,const double  epsilon, int SizePIInterventionOrder, int SizePSInterventionOrder)
{
    ofstream ResultFile;
    string path="Resultats/SolPlayerInterventionOrder";
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

   /* int sec =timeinfo->tm_sec;
    temp<<"_";
    temp<<sec;
    temp<<"sec";*/

     stringstream sss;
    stringstream ssss;
    stringstream sssss;
    sss << max_gen;
    ssss << epsilon;
     sssss << ApproachGameEvaluation;

    path = path+ "_Evaluation_"+sssss.str()+"_epsilon"+ssss.str()+  +"_gen_" + sss.str()+temp.str()+".txt";


    path = path+temp.str()+".txt";      //str is temp as string
    ResultFile.open(path.c_str(),std::ios::app);

    if (!ResultFile) {
        cerr << "Unable to open file!!";
        exit(1);   // call system to stop
    }
     ResultFile <<" =========================== TRX Player intervention order  ===========================================" << endl;
    ResultFile << " °°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°° " << endl << endl;
    ResultFile<< " °°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°° " << endl;
    int i;
    ResultFile << " The player PI had played " << SizePIInterventionOrder << " onces" <<endl;
    ResultFile << " The player PS had played " << SizePSInterventionOrder << " onces" <<endl;
    ResultFile << " °°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°° " << endl << endl;
    for(i = 0 ; i < Sol->plan->size(); i ++)
    {
        ResultFile << " at state : " << i << " the player played is  "  << Sol->VecPlayerIntervOrd->at(i).IdentPlayer <<endl;
         ResultFile << " the trx used is  : " <<  Sol->VecPlayerIntervOrd->at(i).IdTRXUsed <<endl;

    }
    ResultFile<< " °°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°° " << endl << endl;
    ResultFile << " °°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°° " << endl;
    ResultFile.close();
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Ajouté le 27 - 6 -2021 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void ShowPlayerTRXOrder(vector <int> *IdTRX,int ApproachGameEvaluation,string instance,double elapsed_secs,const int  max_gen,const double  epsilon)
{
  ofstream ResultFile;
    string path="Resultats/ShowPlayerTRXOrder";
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

   /* int sec =timeinfo->tm_sec;
    temp<<"_";
    temp<<sec;
    temp<<"sec";*/

     stringstream sss;
    stringstream ssss;
    stringstream sssss;
    sss << max_gen;
    ssss << epsilon;
     sssss << ApproachGameEvaluation;

    path = path+ "_Evaluation_"+sssss.str()+"_epsilon"+ssss.str()+  +"_gen_" + sss.str()+temp.str()+".txt";


    path = path+temp.str()+".txt";      //str is temp as string
    ResultFile.open(path.c_str(),std::ios::app);

    if (!ResultFile) {
        cerr << "Unable to open file!!";
        exit(1);   // call system to stop
    }
     ResultFile <<" =========================== TRX Player intervention order  ===========================================" << endl;
    ResultFile << " °°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°° " << endl << endl;
    ResultFile<< " °°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°° " << endl;
    int i;
    for(i = 0 ; i < IdTRX->size(); i ++)
    {
        ResultFile << " Le  " << i << "ème TRX traité par le joueur est " << IdTRX->at(i)<<endl;


    }
    ResultFile<< " °°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°° " << endl << endl;
    ResultFile << " °°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°° " << endl;
    ResultFile.close();
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~é
int GetVectorRealSize(vector <int> * vect)
{
    int taille = 0;
    for (int i= 0; i< vect->size(); i++ )
    {
        if( vect->at(i) != -1)
        {
            taille = taille +1;
        }
    }
    return taille ;
}
//=========================================================================
void ShowNashvaluersResult(int indexNASHEbest,vector <double> NASHEJ, string path, double HV,vector<Individual*> solutionSs)
{
     int k,j;
    ofstream ResultFile;
        ResultFile.open(path.c_str(),std::ios::app);
    if (!ResultFile) {
        cerr << "Unable to open file!!";
        exit(1);   // call system to stop
    }

    ResultFile<< "HV : " << HV << endl;
    ResultFile <<"=============================================" << endl;

    ResultFile << "indexNashBest :" << indexNASHEbest << endl;
       ResultFile <<"=============================================" << endl;

    ResultFile << " Nash[indexNashBest] : " << NASHEJ[indexNASHEbest] << endl;
        ResultFile <<"=============================================" << endl;

      //ResultFile <<"NNNNNNNNNNN les valeurs de nash NNNNNNNNNNNNNNNNNNNN"<<endl;
        ResultFile << " NASHEJ[k] , Interf cost , Sep cost " << endl<<endl;

         for(k=0  ;k < NASHEJ.size(); k++)
    {

        //ResultFile<<" ***********solution : " << k << "*******************" << endl;
        ResultFile << k << " , " << NASHEJ[k] << " ,  " << solutionSs[k]->PIObj <<" , " << solutionSs[k]->PSObj<<endl;



    }
    ResultFile.close();
}
//================================= Ajout le 15- 3-20222==============
void ShowResultNorm(int ApproachGameEvaluation,string instance,int NumGame,double elapsed_secs,const int  max_gen,const double epsilon,vector<Individual*> solutionSs,int indexNASHEbest,vector <double> NASHEJ,vector<Individual*> BestsolutionSs, Individual* solution, string path, double HVNorm)
{

    cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
  cout << " au niveau commum indexNASHEbest= " << indexNASHEbest <<endl;
      cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
    //ecrire le résultat dans un fichier : Resultat/resultatDatesystem.txt
    int k,j;
    ofstream ResultFile;
        ResultFile.open(path.c_str(),std::ios::app);
    if (!ResultFile) {
        cerr << "Unable to open file!!";
        exit(1);   // call system to stop
    }
    //rechercher la meilleur solution pour le joueur PI
      vector<double> VectBestSolPI;
         VectBestSolPI.reserve(max_gen);
        for(k = 0 ; k < solutionSs.size(); k++)
        {
            //cout<< " solutionSs[k]->PIObj " <<solutionSs[k]->PIObj <<endl;
            VectBestSolPI.push_back(solutionSs[k]->PIObjNorm);
            //cout << "VectBestSolPI(k) " << VectBestSolPI[k] <<endl;
        }

      int  indexBestSolPI = 0;
        double BestObjectivePI = 0.0;
       // cout << " VectBestSolPI.size() " << VectBestSolPI.size() << endl;
        VecMinValue(VectBestSolPI,indexBestSolPI);
       // cout << "indexBestSolPI : " << indexBestSolPI << endl;
        BestObjectivePI = solutionSs[indexBestSolPI]->PIObjNorm;
         vector<double> VectBestSolPS;
         VectBestSolPS.reserve(max_gen);
        for(k = 0 ; k < solutionSs.size(); k++)
        {
            //cout<< " solutionSs[k]->PIObj " <<solutionSs[k]->PIObj <<endl;
            VectBestSolPS.push_back(solutionSs[k]->PSObjNorm);
            //cout << "VectBestSolPI(k) " << VectBestSolPI[k] <<endl;
        }

       int indexBestSolPS = 0;
        double BestObjectivePS = 0.0;
       cout << " VectBestSolPI.size() " << VectBestSolPI.size() << endl;
        VecMinValue(VectBestSolPS,indexBestSolPS);
        cout << "indexBestSolPI : " << indexBestSolPI << endl;
        BestObjectivePS = solutionSs[indexBestSolPS]->PSObjNorm;
    ResultFile <<" ===========================Hypervolume===========================================" << endl;
    ResultFile << " HV % :" << HVNorm << endl;
    ResultFile <<" ======================================================================" << endl;
    ResultFile <<"....................... Sans Nash coût séparé......."<<endl;
    ResultFile << "Meiilleur Interference score normalisé  est : " <<  BestObjectivePI  << endl;
    ResultFile << "Meiilleur Separation score normalisé  est : "   <<  BestObjectivePS << endl;
    ResultFile <<" ======================================================================" << endl;
    ResultFile <<"....................... AVEC Nash ......."<<endl;
   //---------------------------------------
    ResultFile << " Pour une valeur de epsilon egale :" << epsilon << endl;

   // ResultFile<<" La valeur de nash est : "  << NASHEJ[indexNASHEbest]<<endl;
    ResultFile << "Meiilleur Interference score   en utilisant NASH est : CI " << solution->PIObj << " ICNorm " << solution->PIObjNorm << endl;//<< solutionSs[indexNASHEbest]->PIObj << endl;
    ResultFile << "Meiilleur Separation score est en utilisant NASH:   CS "<< solution->PSObj<< " ScNorm " << solution->PSObjNorm << endl;//solutionSs[indexNASHEbest]->PSObj << endl;

    ResultFile <<"------------------ MEilleur valeur nash --------------"<<endl;
    ResultFile <<" Meilleur valeur de Nash Normalisé " << NASHEJ[indexNASHEbest] << endl;
    ResultFile <<" Qui se trouve à la position " << indexNASHEbest << " ;" <<endl;

    ResultFile <<" ======================================================================" << endl;

    //----------------------------------------------
    ResultFile << "Temps d'execution : "<<elapsed_secs << " ms" << endl;

    ResultFile << "---- vecteur solution ---"<<endl;
    ResultFile << "TRX ID" <<" , " <<"Frequency"<<endl;
    ResultFile << "NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN" <<endl;

   // ResultFile <<" la meilleur solution corrspond au  NASHEJ[ "<< indexNASHEbest<<"] : " <<NASHEJ.at(indexNASHEbest)<<endl;
    ResultFile <<"########################################################"<<endl;
    ResultFile << " ----------------LEs meilleurs solutions trouvées -------------------" <<endl;
      for(k=0  ;k < BestsolutionSs.size(); k++)
    {
        ResultFile<<" ***********solution : " << k << "*******************" << endl;
        ResultFile<<" Coût d'interference : " << BestsolutionSs[k]->PIObj << endl;
       // ResultFile<<" Coût d'interference : " << BestsolutionSsNorm[k]->PIObj << endl;
        ResultFile<<" Coût de séparation " << BestsolutionSs[k]->PSObj << endl;
       // ResultFile<<" Coût de séparation " << BestsolutionSsNorm[k]->PSObj << endl;
       // ResultFile<<" Valeur de Nash  " << NASHEJ[k]  << endl;
        ResultFile<<"................................."<<endl;


    }
    ResultFile <<"########################################################"<<endl;

    /*
   for(k=0;k<max_gen; k++)
    {
        ResultFile << " NASHEJ[ " << k << " ] : " << NASHEJ[k] << endl;
        ResultFile << " ------------" << endl;
        ResultFile << " PI Objectif solutionSs[k]->PIObj : " << solutionSs[k]->PIObj<<endl;
        ResultFile << " PS Objectif solutionSs[k]->PSObj : " << solutionSs[k]->PSObj<<endl;
        ResultFile << "................................." << endl;


    }
        ResultFile <<"-----------" << endl;
        */
    ResultFile <<"NNNNNNNNNNN les valeurs de nash NNNNNNNNNNNNNNNNNNNN"<<endl;
        ResultFile << " IC   ,	SC  ,  Icnorm,  Scnorm,  Icbest,	Scbest,	NashNorm " << endl;
         for(k=0  ;k < NASHEJ.size(); k++)
    {
         ResultFile << solutionSs[k]->PIObj << ", " << solutionSs[k]->PSObj << ", " <<  solutionSs[k]->PIObjNorm << ", " << solutionSs[k]->PSObjNorm << ", " << NASHEJ[k] << endl;

    }

         /*for(k=0  ;k < NASHEJ.size(); k++)
    {
        ResultFile<<" ***********solution : " << k << "*******************" << endl;
        ResultFile<<" NASHEJ[" << k <<"] : " << NASHEJ[k] << ", Interf cost " << solutionSs[k]->PIObj <<", Sep cost "<< solutionSs[k]->PSObj<<endl;
        ResultFile<<" NASHEJ[" << k <<"] : " << NASHEJ[k] << ", Interf cost " << solutionSs[k]->PIObjNorm <<", Sep cost "<< solutionSs[k]->PSObjNorm<<endl;

        ResultFile<<"................................."<<endl;


    }*/


    ResultFile.close();
    //***********************************************************
}

//================================ Fin ajout 15-3-2022 ==============

=======
#include <iostream>
#include <cstdlib>      // std::rand, std::srand
#include <algorithm>    // std::find
#include <sstream>//LF:convert string
#include <ctime>        // std::time
#include <sstream>//LF:convert string
#include <fstream>
//#include <iterator>
#include "Commun.h"
#include "../Individual/Individual.h"
/*void InitLTrxNTreated(vector<int>* &LTrxNTreated, int m)
 {
            int i;
         for(i=0 ; i<m;i ++) //m le nombre totale de trx
        {
            LTrxNTreated->push_back(i);
             //cout << LTrxNTreated->at(i) << endl;

        }
        //cout << "hiii" << endl;
 }*/
 void InitLTrxNTreatedsV2(vector<int> &LTrxNTreateds, AFP * afpProblem)
 {
       int i,Numbertrx;
       // LTrxNTreateds = afpProblem->trxs;
        Numbertrx = afpProblem->trxs.size();
       // cout << Numbertrx << endl;
       for(i=0;i<  Numbertrx ;i++)
       {
           //LTrxNTreateds[i].AvailableFrequencies=new vector<int>();
          LTrxNTreateds.push_back(i);
        //  LTrxNTreateds.at(i) = i;
         // cout << "LTrxNTreateds[i]" << LTrxNTreateds[i] << endl;
       }
    //   cout <<" LTrxNTreateds.size() " << LTrxNTreateds.size() <<endl;
 }
 //=============================================================
void InitLTrxNTreateds(vector<TRXs> &LTrxNTreateds, AFP * afpProblem)
 {
       int i,Numbertrx;
       // LTrxNTreateds = afpProblem->trxs;
        Numbertrx = afpProblem->trxs.size();
        LTrxNTreateds.reserve(Numbertrx);
       for(i=0;i<  Numbertrx ;i++)
       {
           //LTrxNTreateds[i].AvailableFrequencies=new vector<int>();
         LTrxNTreateds.push_back(afpProblem->trxs[i]);
         //LTrxNTreateds[i] = afpProblem->trxs[i];
       }
      // cout << "LTrxNTreateds[Numbertrx].trxID " << LTrxNTreateds[Numbertrx-1].trxID <<endl;
 }

//------------------------
void AddSolTrxFrequency(AFP* afpProblem, Individual* &Sol,TRXs trx ,int f) //Procédure pour affecter f au trx dans la solution
{
    int i,j;

   /* for(i = 0 ; i <  Sol->plan->size(); i ++)
    {
        oldcost = oldcost + Sol->planCC->at(i);
    }*/

    //°°°°°°°°°°°°°°°°°°°°°°°°°°°Remplir planCC
    // calculer le nouveau cout ------------------------------------
  // double newcost = afpProblem->ComputeSolutionInterference(Sol);
    /* Individual * tempsol =  new Individual();

      tempsol->plan = new vector <int>(Sol->plan->size());
      tempsol->planCC = new vector <double>(Sol->planCC->size());*/
    //------utiliser ma fonction de calcul de cout
      /*  for(i = 0 ; i < Sol->plan->size(); i ++)
        {
            tempsol->plan->at(i) = Sol->plan->at(i);
            tempsol->planCC->at(i) = Sol->planCC->at(i);
            tempsol->PIObj = Sol->PIObj;
            tempsol->PSObj = Sol->PSObj;
        }
           //on remplie planaffect pour accelerer la recherche
            tempsol->PlanAffect = new vector< pair<int,int> > ();
       //int taille =trx.AvailableFrequencies->size();

        for(i=0;i<tempsol->plan->size();i++)
        {
            if (tempsol->plan->at(i)!=-1)//si la case dans le plan n'est pas vide on remplie le planAffect
            {
                tempsol->PlanAffect->push_back({i,tempsol->plan->at(i)});
            }
        }
       cout << "tempsol->PlanAffect->size() " << tempsol->PlanAffect->size() << endl;
        double oldcost = 0.0 ;
        for(i = 0 ; i < tempsol->PlanAffect->size() ; i++)// pour chaque trx on calcule sont cout
        {
            int victimtrx= tempsol->PlanAffect->at(i).first;
            int victimFrequency = tempsol->PlanAffect->at(i).second;
            for(j = 0 ; j < tempsol->PlanAffect->size() ; j++) //
            {
                if ( j != i )
                {
                    int interfererTrx = tempsol->PlanAffect->at(j).first;
                    int interfererFrequency =  tempsol->PlanAffect->at(j).second;
                    oldcost= oldcost + afpProblem->computeChannelInterference(victimFrequency ,interfererFrequency, victimtrx,interfererTrx);
                }

            }
        }
        cout << "oldcost "<< oldcost <<endl;
        delete(tempsol->PlanAffect);*/
        //double oldcost = Sol->PIObj;
        // ajouter la nouvelle fréquence++++++++++++++++++++++++++++++++++++++++++++++++
        Sol->plan->at(trx.trxID) = f;
            //on remplie planaffect pour accelerer la recherche
        //Evaluer le cout +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
       /*tempsol->PlanAffect = new vector< pair<int,int> > ();
       //int taille =trx.AvailableFrequencies->size();

        for(i=0;i<Sol->plan->size();i++)
        {
            tempsol->plan->at(i) = Sol->plan->at(i);
            tempsol->planCC->at(i) = Sol->planCC->at(i);
            tempsol->PIObj = Sol->PIObj;
            tempsol->PSObj = Sol->PSObj;
            if (Sol->plan->at(i)!=-1)//si la case dans le plan n'est pas vide on remplie le planAffect
            {
                tempsol->PlanAffect->push_back({i,tempsol->plan->at(i)});
            }
        }
        //---------------
       cout << "tempsol->PlanAffect->size() " << tempsol->PlanAffect->size() << endl;
        double newcost = 0.0 ;
        for(i = 0 ; i < tempsol->PlanAffect->size() ; i++)// pour chaque trx on calcule sont cout
        {
            int victimtrx= tempsol->PlanAffect->at(i).first;
            int victimFrequency = tempsol->PlanAffect->at(i).second;
            for(j = 0 ; j < tempsol->PlanAffect->size() ; j++) //
            {
                 int interfererTrx = tempsol->PlanAffect->at(j).first;
                int interfererFrequency =  tempsol->PlanAffect->at(j).second;
                if ( victimtrx != victimtrx )
                {
                   newcost= newcost + afpProblem->computeChannelInterference(victimFrequency ,interfererFrequency, victimtrx,interfererTrx);
                }

            }
        }

    cout << "newcost  " << newcost << endl ;
   //----------------------------------------------------------------
    Sol->planCC->at(trx.trxID) = newcost - oldcost;*/
   // cout <<  Sol->planCC->at(trx.trxID)  <<endl;

 //delete(tempsol->PlanAffect);
}
void AddSolTrxFrequencyV2(Individual* &Sol,int trxid ,int f) //Procédure pour affecter f au trx dans la solution
{
    double cost = 0.0;
    Sol->plan->at(trxid) = f;
   // Sol->planCC=NULL;
//Sol->PlanAffect->push_back({trx.trxID,f});
//solution->plan->at(i) = trxs[i].validFrequencies->at(index);

}

//----------------------------------------------------
int FindTrx(vector <TRXs> LTrxNTreateds, TRXs trx)
{
    int i; TRXs t;
    if (LTrxNTreateds.empty() ==true)
    {
        return -1;
    }
    else
    {
        vector<TRXs>::iterator it;i=0;
        for(i=0; i<LTrxNTreateds.size();i++)
        {
            t=LTrxNTreateds[i];
            if (t==trx) return i;
        }

     /*   for (it=LTrxNTreateds.begin();it<LTrxNTreateds.end();it++)
        {
            i=i+1;
            t= LTrxNTreateds.at(i);
            if (t==trx) return i;
        }*/
        if (i == LTrxNTreateds.size()) return -1;
            //return -1;
    }

}
//°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°
int FindTrxV2(vector <int> LTrxNTreateds, TRXs trx)
{
    int i; int t;
    if (LTrxNTreateds.empty() ==true)
    {
        return -1;
    }
    else
    {
        vector<int>::iterator it;i=0;
        for(i=0; i<LTrxNTreateds.size();i++)
        {
            t = LTrxNTreateds[i];
            if (t==trx.trxID) return i;
        }

     /*   for (it=LTrxNTreateds.begin();it<LTrxNTreateds.end();it++)
        {
            i=i+1;
            t= LTrxNTreateds.at(i);
            if (t==trx) return i;
        }*/
        if (i == LTrxNTreateds.size()) return -1;
            //return -1;
    }

}
//-------------------------------------------
int FindTrxID(vector <TRXs> LTrxNTreateds, int indextrx)
{
    int i; TRXs t;
    if (LTrxNTreateds.empty() ==true)
    {
        return -1;
    }
    else
    {
        vector<TRXs>::iterator it;i=0;
        for(i=0; i<LTrxNTreateds.size();i++)
        {
           if (LTrxNTreateds[i].trxID==indextrx) return i;
        }

     /*   for (it=LTrxNTreateds.begin();it<LTrxNTreateds.end();it++)
        {
            i=i+1;
            t= LTrxNTreateds.at(i);
            if (t==trx) return i;
        }*/
        if (i == LTrxNTreateds.size()) return -1;
            //return -1;
    }

}



//-------------------------------------------
void UpdateLTrxNTreateds(vector <TRXs> &LTrxNTreateds, TRXs trx,int Update)
{

//tester d'abords si le trx n'esiste pas
    vector<int>::iterator it;int tt=0; vector<int> v;
    //it = LTrxNTreateds.begin();
   // int tt =it->trxID;
  //  cout <<" it->trxID " << it->trxID<<endl;
int i;
//TRXs t=trx;

 //it = find(LTrxNTreateds.begin(),LTrxNTreateds.end(),trx);
 // it = find(v.begin(),v.end(),1);

   // cout <<"existe"<<endl;

    switch(Update)
            {
                case  +1 ://ajout du trx
                    // cout << "Ajout du trx" << endl;
                    if (FindTrx(LTrxNTreateds, trx)==-1)//le trx n'exite pas on l'ajoute
                    {
                       LTrxNTreateds.push_back(trx);
                        break;
                    }
                    else
                    {
                        break;
                        //cout << "Le trx existe déjà! " << endl;
                    }
                case  -1 :
                    //cout << "Suppression du trx" << endl;
                   if(FindTrx(LTrxNTreateds, trx)!=-1)//Le trx existe on le supprime
                    {
                        int index =FindTrx(LTrxNTreateds, trx);
                        LTrxNTreateds.erase(LTrxNTreateds.begin()+index);
                        break;
                    }
                    else
                    {
                        break;
                       // cout << "Le trx n existe pas " << endl;
                    }
                default :
                    cout << "ERREUR de mise à jour de la liste de la liste des trx traités"<< endl;
                    break;
            }

}
//°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°
void UpdateLTrxNTreatedsV2(vector <int> &LTrxNTreateds, TRXs trx,int Update)
{

//tester d'abords si le trx n'esiste pas
    vector<int>::iterator it;int tt=0; vector<int> v;
    //it = LTrxNTreateds.begin();
   // int tt =it->trxID;
  //  cout <<" it->trxID " << it->trxID<<endl;
int i;
//TRXs t=trx;

 //it = find(LTrxNTreateds.begin(),LTrxNTreateds.end(),trx);
 // it = find(v.begin(),v.end(),1);

   // cout <<"existe"<<endl;

    switch(Update)
            {
                case  +1 ://ajout du trx
                    // cout << "Ajout du trx" << endl;
                    if (FindTrxV2(LTrxNTreateds, trx)==-1)//le trx n'exite pas on l'ajoute
                    {
                       LTrxNTreateds.push_back(trx.trxID);
                        break;
                    }
                    else
                    {
                        break;
                        //cout << "Le trx existe déjà! " << endl;
                    }
                case  -1 :
                    //cout << "Suppression du trx" << endl;
                   if(FindTrxV2(LTrxNTreateds, trx)!=-1)//Le trx existe on le supprime
                    {
                        int index =FindTrxV2(LTrxNTreateds, trx);
                        LTrxNTreateds.erase(LTrxNTreateds.begin()+index);
                        break;
                    }
                    else
                    {
                        break;
                       // cout << "Le trx n existe pas " << endl;
                    }
                default :
                    cout << "ERREUR de mise à jour de la liste de la liste des trx traités"<< endl;
                    break;
            }

}
//--------------------------------------
bool operator==( const TRXs &b1, const TRXs &b )
{
        return (b1.trxID== b.trxID) && (b1.sectorID == b.sectorID) && (b1.siteID == b.siteID) &&
	(b1.type == b.type) && (b1.validFrequencies ==b.validFrequencies)	&& (b1.validFrequenciesSet == b.validFrequenciesSet);

}
//------------------------------
void UpdateTRxFrequencyEraseAdj(TRXs &trx, int f)
{
    int freq;
    int indexf=FindFrequency(trx.AvailableFrequencies,f);
    if (indexf!=-1)//la fréquence existe
    {
       trx.AvailableFrequencies->erase( trx.AvailableFrequencies->begin()+indexf);
    }
    freq = f - 1;
    indexf = FindFrequency(trx.AvailableFrequencies,freq);
    if (indexf!=-1)//la fréquence existe
    {
       trx.AvailableFrequencies->erase( trx.AvailableFrequencies->begin()+indexf);
    }
    //suppression des fréquence adjacente de f
    freq = f + 1;
    indexf=FindFrequency(trx.AvailableFrequencies,freq);
    //cout << "indexf "  <<indexf <<endl;
    if (indexf!=-1)//la fréquence existe
    {
       trx.AvailableFrequencies->erase( trx.AvailableFrequencies->begin()+indexf);
    }
}

//--------------
 void UpdateTRxFrequencyNew(vector<TRXs> LTrxNTreateds,AFP * afpProblem,TRXs &trx, int f,int Update)
 //supprimes f de la liste disponibles de tous les trx sui sont dans le meme secteur que le trx "trx"
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
                    UpdateTRxFrequencyEraseAdj(trx, f);
                    for(i=0; i<LTrxNTreateds.size();i++)
                    {
                        othertrxId = LTrxNTreateds[i];
                        if(trx.sectorID == afpProblem->trxs[othertrxId.trxID].sectorID)
                        {
                            UpdateTRxFrequencyEraseAdj(othertrxId, f);
                        }//  if(trx.sectorID == afpProblem->trxs[othertrxId.trxID].sectorID)
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
            cout<<" ERREUR de mise à jour de fréquence !!"<<endl;
            break;
        }//default switch

    }//fin switch

 }// fin procedure de mise à jour
 //°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°
 void UpdateTRxFrequencyNewV2(vector<int> LTrxNTreateds,AFP * afpProblem,TRXs &trx, int f,int Update)
 //supprimes f de la liste disponibles de tous les trx sui sont dans le meme secteur que le trx "trx"
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
                    UpdateTRxFrequencyEraseAdj(trx, f);
                    for(i=0; i<LTrxNTreateds.size();i++)
                    {
                        othertrxId = afpProblem->trxs[LTrxNTreateds[i]];
                        if(trx.sectorID == afpProblem->trxs[othertrxId.trxID].sectorID)
                        {
                            UpdateTRxFrequencyEraseAdj(othertrxId, f);
                        }//  if(trx.sectorID == afpProblem->trxs[othertrxId.trxID].sectorID)
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
            cout<<" ERREUR de mise à jour de fréquence !!"<<endl;
            break;
        }//default switch

    }//fin switch

 }// fin procedure de mise à jour
//°°°°°°°°°°°°°°°°°°°°°°°°°°Ajouté le 26-3-2019°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°
//°°°°°°°°°°°° On enlève la fréquence aussi des trx qui sont dans les secteurs voisins (1 saut) °°°°°°°°°°°°°
 void UpdateTRxFrequencyV3(vector<TRXs> LTrxNTreateds,AFP * afpProblem,TRXs &trx, int f,int Update)
 {
                int i,j,k,SectTrx;

                  SectTrx = trx.sectorID ;
                  int NumberSectNeighbors = afpProblem->neighbors[SectTrx].size();
                // cout << " afpProblem->neighbors[SectTrx].size() " << afpProblem->neighbors[SectTrx].size() <<endl;// contient tous les voisins du secteurSectTrx


                  //cout << "Mise à jour de la frequence 592---- " << endl;
                 UpdateTRxFrequencyNew(LTrxNTreateds,afpProblem,trx,f,Update);
                         /* for(k = 0; k < trx.AvailableFrequencies->size(); k++)
                            cout << " trx.AvailableFrequencies->at( " << k << ")= " << trx.AvailableFrequencies->at(k) << "," <<  endl; */
                 for(i = 0 ; i < NumberSectNeighbors ; i ++  )
                 {
                    int SectTrxNeighbor;
                    SectTrxNeighbor =  afpProblem->neighbors[SectTrx].at(i);
                  //  cout << "le premier sect voisin "<< SectTrxNeighbor << endl;
                    int NumberTrxSectNeighbors = afpProblem->sectors2trxs[SectTrxNeighbor].size();
                    //cout << "le nombre de trx dans ce secteur est =" << NumberTrxSectNeighbors << endl;
                    for (j = 0 ; j < NumberTrxSectNeighbors; j++ )
                    {
                        TRXs trxSectNeighbor;
                        trxSectNeighbor.trxID = afpProblem->sectors2trxs[SectTrxNeighbor].at(j);
                        trxSectNeighbor = afpProblem->trxs[trxSectNeighbor.trxID];//recuperer un trx du secteur voisin
                     //   cout << "le premieir  trx dans le premier  secteur voisin est " << trxSectNeighbor.trxID << endl;
                        //------------ verifier la mise à jour de la liste des fréquence dans un trx et dans son voisi
                        //trx == 0 et son voisin 62
                        /*cout << "********** avant le premier voisin de trx 0  est  62 *************************"  << endl;
                        for(k= 0; k < trxSectNeighbor.AvailableFrequencies->size(); k++)
                            cout << " trxSectNeighbor.AvailableFrequencies->at( " << k << ")= " << trxSectNeighbor.AvailableFrequencies->at(k) << "," <<  endl;
                        cout << "aprs Mise à jour de la frequence 592---- " << endl;*/
                        UpdateTRxFrequencyNew(LTrxNTreateds,afpProblem,trxSectNeighbor,f,Update);
                       /* for(k= 0; k < trxSectNeighbor.AvailableFrequencies->size(); k++)
                            cout << " trxSectNeighbor.AvailableFrequencies->at( " << k << ")= " << trxSectNeighbor.AvailableFrequencies->at(k) << "," <<  endl;*/
                    }
                }


 }
 //°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°
 void UpdateTRxFrequencyV32(vector<int> LTrxNTreateds,AFP * afpProblem,TRXs &trx, int f,int Update)
 {
                int i,j,k,SectTrx;

                  SectTrx = trx.sectorID ;
                  int NumberSectNeighbors = afpProblem->neighbors[SectTrx].size();
                // cout << " afpProblem->neighbors[SectTrx].size() " << afpProblem->neighbors[SectTrx].size() <<endl;// contient tous les voisins du secteurSectTrx


                  //cout << "Mise à jour de la frequence 592---- " << endl;
                 UpdateTRxFrequencyNewV2(LTrxNTreateds,afpProblem,trx,f,Update);
                         /* for(k = 0; k < trx.AvailableFrequencies->size(); k++)
                            cout << " trx.AvailableFrequencies->at( " << k << ")= " << trx.AvailableFrequencies->at(k) << "," <<  endl; */
                 for(i = 0 ; i < NumberSectNeighbors ; i ++  )
                 {
                    int SectTrxNeighbor;
                    SectTrxNeighbor =  afpProblem->neighbors[SectTrx].at(i);
                  //  cout << "le premier sect voisin "<< SectTrxNeighbor << endl;
                    int NumberTrxSectNeighbors = afpProblem->sectors2trxs[SectTrxNeighbor].size();
                    //cout << "le nombre de trx dans ce secteur est =" << NumberTrxSectNeighbors << endl;
                    for (j = 0 ; j < NumberTrxSectNeighbors; j++ )
                    {
                        TRXs trxSectNeighbor;
                        trxSectNeighbor.trxID = afpProblem->sectors2trxs[SectTrxNeighbor].at(j);
                        trxSectNeighbor = afpProblem->trxs[trxSectNeighbor.trxID];//recuperer un trx du secteur voisin
                     //   cout << "le premieir  trx dans le premier  secteur voisin est " << trxSectNeighbor.trxID << endl;
                        //------------ verifier la mise à jour de la liste des fréquence dans un trx et dans son voisi
                        //trx == 0 et son voisin 62
                        /*cout << "********** avant le premier voisin de trx 0  est  62 *************************"  << endl;
                        for(k= 0; k < trxSectNeighbor.AvailableFrequencies->size(); k++)
                            cout << " trxSectNeighbor.AvailableFrequencies->at( " << k << ")= " << trxSectNeighbor.AvailableFrequencies->at(k) << "," <<  endl;
                        cout << "aprs Mise à jour de la frequence 592---- " << endl;*/
                        UpdateTRxFrequencyNewV2(LTrxNTreateds,afpProblem,trxSectNeighbor,f,Update);
                       /* for(k= 0; k < trxSectNeighbor.AvailableFrequencies->size(); k++)
                            cout << " trxSectNeighbor.AvailableFrequencies->at( " << k << ")= " << trxSectNeighbor.AvailableFrequencies->at(k) << "," <<  endl;*/
                    }
                }


 }
//°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°
//°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°
//------------------------------------------
 void UpdateTRxFrequency(TRXs &trx, int f,int Update)
{
//tester d'abords si la fréquence n'est pas bloquée
    vector<int>::iterator it;//int x;
    if(trx.AvailableFrequencies->empty()==false)//je traite uniqueement si la liste des fréquense disponible n est pas vide
    {
        it = std::find (trx.validFrequencies->begin(), trx.validFrequencies->end(),f);

        //else
        // on  traite si la fréquence n est pas bloquée
       if(it!=trx.validFrequencies->end())//la fréquence n'est pas bloqué
        {// on vérifie si la valeur de update est différente que +1 ou -1 alors erreur

            //f=f;
             switch(Update)
                {
                    case  +1 :
                    {
                        //cout << "Ajout de la fréquence au trx" << endl;
                        //vérifier si la fréquence n'existe pas dans la liste disponible
                        it = std::find (trx.AvailableFrequencies->begin(), trx.AvailableFrequencies->end(),f);
                        if (it==trx.AvailableFrequencies->end())//la fréquence n'existe pas on l'ajoute
                        {
                            trx.AvailableFrequencies->push_back(f);
                        }
                        break;
                    }//end case +1
                case  -1 :
                {
                    //cout << "Suppression de la fréquence du trx" << endl;
                    //on supprime si la lise des fréquences disponible n'est pas vide


                            int indexf=FindFrequency(trx.AvailableFrequencies,f);
                            if (indexf!=-1)//la fréquence existe
                            {
                                trx.AvailableFrequencies->erase( trx.AvailableFrequencies->begin()+indexf);
                            }

                        //f=f;

                    break;
                }//case
                default ://Update != 1 et Update != -1 :Errieu de mise à jour
                cout << "ERREUR de mise à jour de la liste des fréquences disponible du trx"<< endl;
            }//switch


         }// if(it!=trx.validFrequencies->end())//la fréquence est valide


    }// if(trx.AvailableFrequencies->empty()==false)

}
//-------------------------------------------------------
//---mettre à jour la liste de fréquence disponible de tous les trx non traité
void UpdateAllTRxFrequency(vector <TRXs> &LTrxNTreateds,int  f, int Update)
{
     //cout<<"hi"<<endl;

    if (LTrxNTreateds.empty()==false)
    //if(Update==1)
    {
        switch(Update)
        {
            case  +1 :
            {
                break;

            }//end case +1
            case -1:
            {
                int i;
               // cout<<"hi"<<endl;
                for(i=0;i<LTrxNTreateds.size();i++)
                {
                   if (LTrxNTreateds[i].AvailableFrequencies->size()>1)//on supprime uniquement si la taille >1
                   {
                        UpdateTRxFrequency(LTrxNTreateds[i],f,-1);
                   }

                    //cout<<"hi"<<endl;
                   // break;
                }
                break;
            }//endcase
            default:
            cout << "ERREUR de mise à jour de la liste des fréquences disponible de TOUT les trxs"<< endl;
        }//switch
    }//if LTrxNTreateds.empty()==false)


}//end UpdateAllTRxFrequency(vector <TRXs> &LTrxNTreateds,int  f, int upadate)





//--------------------------------------------------------------------
/*void UpdateTRxFrequency1(TRXs &trx, int f,int Update)
{
//tester d'abords si la fréquence n'est pas bloquée
int exist,blocked;
   blocked = blockedFrequency(trx,f);
    if (blocked==+1)//la fréquence est dans la liste blouqé du trx
    {cout << " LA fréquence est dans la liste des fréquences bloquées " << endl;}

    else
    {// on vérifie si la valeur de update est différente que +1 ou -1 alors erreur
        try
        {
            switch(Update)
            {
                case  +1 :
                     //cout << "Ajout de la fréquence au trx" << endl;
                     //vérifier si la fréquence n'existe pas dans la liste disponible
                     exist = FindFrequency(trx.AvailableFrequencies,f);
                    if (exist==-1)//la fréquence n'existe pas on l'ajoute
                    {
                       trx.AvailableFrequencies->push_back(f);

                    }
                    break;
                case  -1 :
                    cout << "Suppression de la fréquence du trx" << endl;
                      exist = FindFrequency(trx.AvailableFrequencies,f);

                    if (exist!=-1)//la fréquence est dans la listedisponible  du trx on l a supprime
                    {
                       trx.AvailableFrequencies->erase(trx.AvailableFrequencies->begin()+exist);
                       //trx.AvailableF->erase(trx.AvailableF->begin()+exist);
                       //cout<<"why"<<endl;
                    }
                    break;
                default ://Update != 1 et Update != -1 :Errieu de mise à jour
                    cout << "ERREUR de mise à jour de la liste des fréquences disponible du trx"<< endl;
            }
        }
        catch(const char* msg)
        {
            cout << msg << endl;
        }
    }
}*/



//--------------------------------------------------------------------

int FindFrequency(vector<int>* vectFrequency, int f)
{
    int i;
    for(i=0; i<vectFrequency->size();i++)
        {
            if (vectFrequency->at(i)==f) return i;
        }
        if (i == vectFrequency->size()) return -1;

}
int blockedFrequency(TRXs trx,int f)
{
    int i;
     for(i=0; i<trx.validFrequencies->size();i++)
        {
            if (trx.validFrequencies->at(i)==f) return -1;//la fréquence n'est pas bloquée
        }
        //if (i == trx.validFrequencies->size()) return +1;
        return +1;
}
//----------------------------
void vecmaxInt(vector<int> x, int & indexmax) {
  // Rcpp supports STL-style iterators
 /*vector<double>::iterator it = min_element(x.begin(), x.end());
  // we want the value so dereference
 return it - x.begin();;*/
  int i;int couts;
 if (x.empty()==false)
 {

  couts=x.at(0);indexmax=0;

 for(i=0;i>x.size();i++)
 {
     if(couts< x.at(i))
     {
         indexmax =i;
         couts=x.at(i);

     }
 }

 }
 else
 {
     indexmax = -1;
 }


}
void vecminInt(vector<int> x, int & indexmin) {
  // Rcpp supports STL-style iterators
 /*vector<double>::iterator it = min_element(x.begin(), x.end());
  // we want the value so dereference
 return it - x.begin();;*/
  int i;int couts;
 if (x.empty()== false)
 {
   couts=x.at(0);indexmin = 0;
    for(i=0;i<x.size();i++)
    {
        if(couts> x.at(i))
        {
            indexmin =i;
            couts=x.at(i);
        }
    }
 }
 else
 {
     indexmin = -1; // vecteur vide
 }


}
//--------------------------------------------
void vecmin(vector<double>* x, int & indexmin) {
  // Rcpp supports STL-style iterators
 /*vector<double>::iterator it = min_element(x.begin(), x.end());
  // we want the value so dereference
 return it - x.begin();;*/
  int i;double couts;
 if (x->empty()==false)
 {

  couts=x->at(0);indexmin=0;

 for(i=0;i<x->size();i++)
 {
     if(couts> x->at(i))
     {
         indexmin =i;
         couts=x->at(i);

     }
 }

 }
 else
 {
     indexmin = -1;
 }


}
//======================================
//--------------------------------------------
void VecMinValue(vector<double> x, int &index)
{
  // Rcpp supports STL-style iterators
    /*vector<double>::iterator it = min_element(x.begin(), x.end());
  // we want the value so dereference
    return it - x.begin();;*/
    int i;
    double couts;
    index = 0;
    couts = x[0];
    int taille = x.size();
    //cout << "couts" << couts <<endl;
    for(i = 1 ; i < taille ; i++)
    {
            if(couts > x[i])
            {
                index =  i;
                couts   =   x[i];
                            //cout << "hiiiiiiiiiiiii" <<endl;
            }

    }

}
//--------------------------------------------
void ShowResult(int ApproachGameEvaluation,string instance,int NumGame,double elapsed_secs,const int  max_gen,const double epsilon,vector<Individual*> solutionSs,int indexNASHEbest,vector <double> NASHEJ,vector<Individual*> BestsolutionSs, Individual* solution, string path, double HV)
{

    cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
  cout << " au niveau commum indexNASHEbest= " << indexNASHEbest <<endl;
      cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
    //ecrire le résultat dans un fichier : Resultat/resultatDatesystem.txt
    int k,j;
    ofstream ResultFile;
        ResultFile.open(path.c_str(),std::ios::app);
    if (!ResultFile) {
        cerr << "Unable to open file!!";
        exit(1);   // call system to stop
    }
    //rechercher la meilleur solution pour le joueur PI
      vector<double> VectBestSolPI;
         VectBestSolPI.reserve(max_gen);
        for(k = 0 ; k < solutionSs.size(); k++)
        {
            //cout<< " solutionSs[k]->PIObj " <<solutionSs[k]->PIObj <<endl;
            VectBestSolPI.push_back(solutionSs[k]->PIObj);
            //cout << "VectBestSolPI(k) " << VectBestSolPI[k] <<endl;
        }

      int  indexBestSolPI = 0;
        double BestObjectivePI = 0.0;
       // cout << " VectBestSolPI.size() " << VectBestSolPI.size() << endl;
        VecMinValue(VectBestSolPI,indexBestSolPI);
       // cout << "indexBestSolPI : " << indexBestSolPI << endl;
        BestObjectivePI = solutionSs[indexBestSolPI]->PIObj;
         vector<double> VectBestSolPS;
         VectBestSolPS.reserve(max_gen);
        for(k = 0 ; k < solutionSs.size(); k++)
        {
            //cout<< " solutionSs[k]->PIObj " <<solutionSs[k]->PIObj <<endl;
            VectBestSolPS.push_back(solutionSs[k]->PSObj);
            //cout << "VectBestSolPI(k) " << VectBestSolPI[k] <<endl;
        }

       int indexBestSolPS = 0;
        double BestObjectivePS = 0.0;
       cout << " VectBestSolPI.size() " << VectBestSolPI.size() << endl;
        VecMinValue(VectBestSolPS,indexBestSolPS);
        cout << "indexBestSolPI : " << indexBestSolPI << endl;
        BestObjectivePS = solutionSs[indexBestSolPS]->PSObj;
        //=========================================================================

     ResultFile << "Temps d'execution : "<<elapsed_secs << " ms" << endl;
    ResultFile <<" ========Hypervolume====" << endl;
    ResultFile << " HV % :" << HV << endl;
    ResultFile <<" ========================" << endl;
   // ResultFile <<"....................... Sans Nash coût séparé......."<<endl;
    ResultFile << "(IC best ; SC best) : " <<  BestObjectivePI  <<  " ; " << BestObjectivePS << endl;
    ResultFile <<" Min Nash :   " << NASHEJ[indexNASHEbest] << " : se trouve à la position " << indexNASHEbest <<  endl;


    ResultFile <<" ============================" << endl;
   // ResultFile<<" La valeur de nash est : "  << NASHEJ[indexNASHEbest]<<endl;
   /* ResultFile << "Meiilleur Interference score en utilisant NASH est : CI " << solution->PIObj<<endl;//<< solutionSs[indexNASHEbest]->PIObj << endl;
    ResultFile << "Meiilleur Separation score est en utilisant NASH:   CS "<< solution->PSObj<<endl;//solutionSs[indexNASHEbest]->PSObj << endl;
  */
    //ResultFile <<"------------------ Valeur de --------------"<<endl;
   // ResultFile <<" Min nash   " << NASHEJ[indexNASHEbest] << " : se trouve à la position " << indexNASHEbest <<  endl;

    //ResultFile <<" =============================" << endl;

    //----------------------------------------------
    //ResultFile << "Temps d'execution : "<<elapsed_secs << " ms" << endl;

   // ResultFile << "---- vecteur solution ---"<<endl;
   // ResultFile << "TRX ID" <<" , " <<"Frequency"<<endl;

    /*
   for(k=0;k<max_gen; k++)
    {
        ResultFile << " NASHEJ[ " << k << " ] : " << NASHEJ[k] << endl;
        ResultFile << " ------------" << endl;
        ResultFile << " PI Objectif solutionSs[k]->PIObj : " << solutionSs[k]->PIObj<<endl;
        ResultFile << " PS Objectif solutionSs[k]->PSObj : " << solutionSs[k]->PSObj<<endl;
        ResultFile << "................................." << endl;


    }
        ResultFile <<"-----------" << endl;
        */


   // ResultFile <<" la meilleur solution corrspond au  NASHEJ[ "<< indexNASHEbest<<"] : " <<NASHEJ.at(indexNASHEbest)<<endl;
    ResultFile <<"########################################################"<<endl;
   // ResultFile << "  LEs meilleurs solutions trouvées  " <<endl;
    ResultFile << "Le nombre de solutions trouvées : " << BestsolutionSs.size() << ". Ces solutions sont : " << endl;


    for(k=0  ;k < BestsolutionSs.size(); k++)
    {
      //  ResultFile<<" ***********solution : " << k << "*******************" << endl;
        ResultFile<<" (IC ; SC) : " << BestsolutionSs[k]->PIObj << " ; " << BestsolutionSs[k]->PSObj << endl;
       // ResultFile<<" Coût de séparation " << BestsolutionSs[k]->PSObj << endl;
       // ResultFile<<" Valeur de Nash  " << NASHEJ[k]  << endl;
    }
     ResultFile <<"#########################" << endl << endl;
    //==================================================
    ResultFile <<"......Les valeurs de nash pour Tout l'ensemble des solutions..." <<  endl << endl;
    ResultFile<<"Num Sol, NASHEJ[k] , Interf cost , Sep cost " << endl << endl;
       ResultFile <<".........................." << endl << endl;


         for(k=0  ;k < NASHEJ.size(); k++)
    {
        //ResultFile<<" ***********solution : " << k << "*******************" << endl;
        //ResultFile<<" NASHEJ[" << k <<"] : " << NASHEJ[k] << ", Interf cost " << solutionSs[k]->PIObj <<", Sep cost "<< solutionSs[k]->PSObj<<endl;
        ResultFile << k << " , " << NASHEJ[k] << " , " << solutionSs[k]->PIObj <<  " , " << solutionSs[k]->PSObj << endl;

       // ResultFile<<"................................."<<endl;


    }


    ResultFile.close();
    //***********************************************************
}





//=========================================
//---------------------------------

void vecmax(vector<double> x, int & indexmax)//retourner la valeur maximale dans un tableau
{
    int i;double couts;
    if (x.empty()==false)
    {
        couts=x.at(0);indexmax=0;
        for(i=0;i<x.size();i++)
        {
            if(couts < x.at(i))
            {
                indexmax =i;
                couts=x.at(i);
            }
        }//for
    }
    else
    {
        indexmax = -1;
    }


}
//-----------------------
void vecmaxptr(vector<double>* x, int & indexmax)//retourner la valeur maximale dans un tableau
{
    int i;double couts;
    if (x->empty()== false)
    {
        couts = x->at(0);
        indexmax = 0;
        for(i=0;i < x->size();i++)
        {
            if(couts < x->at(i))
            {
                indexmax = i;
                couts = x->at(i);
            }
        }//for
    }
    else
    {
        indexmax = -1;
    }


}
//------------------------------------
int FindTrxFirstNeighbor(AFP * afpProblem,int sect,int sectneighbor)
{


 /*
   	for (int i = 0; i < numberOfNeighbors; i++) {
  		file >> neighbor;
  		neighbors[sector].push_back(neighbor);
  	} //for

  */
    int i;
   // int test = -1;
    for(i=0;i<afpProblem->neighbors[sect].size();i++)
    {
        //test = 1;
        map<int, vector<int> > neighbor = afpProblem->neighbors;
       if(neighbor[sect].at(i)==sectneighbor)
        {
            return i;
        }
    }
    return -1;
}
//-----------------------------
int FindTrxSecondNeighbor(AFP * afpProblem,int sect,int sectneighbor)
{


 /*
   	for (int i = 0; i < numberOfNeighbors; i++) {
  		file >> neighbor;
  		neighbors[sector].push_back(neighbor);
  	} //for

  */
    int i;
   // int test = -1;
    for(i=0;i<afpProblem->secondNeighbors[sect].size();i++)
    {
        //test = 1;
        map<int, vector<int> > secondneighbor = afpProblem->secondNeighbors;
       if(secondneighbor[sect].at(i)==sectneighbor)
        {
            return i;
        }
    }
    return -1;
}

double DistancetowTrxs(AFP * afpProblem,TRXs trxone, TRXs trxtwo)
{

    int test;
    if (trxone.sectorID==trxtwo.sectorID)//les dex trx sont dans le meme secteur
    {
        return 0.0;
    }
    else
    {
       test = FindTrxFirstNeighbor(afpProblem,trxone.sectorID,trxtwo.sectorID);
        if(test!=-1)
        {
            return 1.0;
        }
        else
        {
            test = FindTrxSecondNeighbor(afpProblem,trxone.sectorID,trxtwo.sectorID);
            if(test!=-1 )
            {
                return 2.0;
            }
            else
            {
                return 3.0;
            }
        }
    }


}
//°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°
//°°°°°°°°°°°°°°°°°°°°°°° Ajouté le 20/4/2019  °°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°
void Normalize(vector<pair<double,double> > &paircost, pair<double,double> MinT, pair<double,double> MaxT)
{
    int i;
    for(i = 0 ; i< paircost.size() ; i++)
      {
          paircost.at(i).first = (paircost.at(i).first - MinT.first)/(MaxT.first-MinT.first);
          paircost.at(i).second = (paircost.at(i).second - MinT.second)/(MaxT.second-MinT.second);
      }
}
void NormalizeV2(vector<pair<double,double> > &paircost, pair<double,double> &R)
{
    int i;

    //1. retirer le maximum et le minimum du table
    double costminFirst = paircost.at(0).first;//A
    double costmaxFirst = paircost.at(0).first;//B
    double costminSecond = paircost.at(0).second;//A
    double costmaxSecond = paircost.at(0).second;//B


    for(i = 0 ; i< paircost.size() ; i++)
      {
        if(costminFirst > paircost.at(i).first) costminFirst = paircost.at(i).first;
        if(costmaxFirst< paircost.at(i).first) costmaxFirst = paircost.at(i).first;
        if(costminSecond> paircost.at(i).second) costmaxSecond = paircost.at(i).second;
        if(costmaxSecond< paircost.at(i).second) costmaxSecond = paircost.at(i).second;
      }
    //2  les bornes [0,1]
    double a = 0.0;
    double b = 1.0 ;
 //3.Normalisation

    cout << "costmaxFirst" << costmaxFirst<<endl;
    cout << "costmaxSecond " << costmaxSecond <<endl;
    cout << "costminFirst" << costminFirst<<endl;
    cout << "costminSecond " << costminSecond <<endl;



    for(i = 0 ; i< paircost.size() ; i++)
      {
          if ((costmaxFirst!= 0 ) and (costminFirst!= 0))
          {
            if (costmaxFirst > costminFirst)
            {
                paircost[i].first = a + (paircost[i].first - costminFirst)*(b-a)/(costmaxFirst - costminFirst);
            }
            else
            {
                paircost[i].first = 0.0;
            }
         if (costmaxSecond > costminSecond)
            {
                paircost[i].second = a+ (paircost[i].second - costminSecond)*(b-a)/(costmaxSecond - costminSecond );
            }
            else
            {
                 paircost[i].second = 0.0;
            }
        }
      }
     if ((costmaxFirst!= 0 ) and (costminFirst!= 0))
     {
        R.first  = a + (R.first - costminFirst)*(b-a)/(costmaxFirst - costminFirst);
        R.second  = a + (R.second - costminFirst)*(b-a)/(costmaxFirst - costminFirst);
     }
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++
double Hypervolume(vector < pair< double, double> > paircost , pair < double,double> R)
{
    int i;
    double HV = 0.0 ; //hypervolume
    HV = (R.first - paircost.at(0).first)* (R.second - paircost.at(0).second);
      for(i = 1 ; i < paircost.size() ; i++)
      {
          HV = HV + (R.first - paircost.at(i).first)* (paircost.at(i-1).second- paircost.at(i).second) ;
          cout << "HV " << HV << endl;
      }
      return HV;
}
//=========================================================================================
void ShowSolution(int StrategyTrxPI,int StrategyTrxPS, Individual* Sol,int ApproachGameEvaluation,string instance,double elapsed_secs,const int  max_gen,const double  epsilon)
{
    ofstream ResultFile;
    string path="Resultats/Solution";
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

   /* int sec =timeinfo->tm_sec;
    temp<<"_";
    temp<<sec;
    temp<<"sec";*/

     stringstream sss;
    stringstream ssss;
    stringstream sssss;
    stringstream strategytrxpi;
     stringstream strategytrxps;
     stringstream sinstance;
    sss << max_gen;
    ssss << epsilon;
     sssss << ApproachGameEvaluation;
strategytrxpi <<StrategyTrxPI;
strategytrxps << StrategyTrxPS;
sinstance << instance;
    path = path+ sinstance.str()+"_TRXPIPS_"+strategytrxps.str()+ strategytrxps.str()+"_Evaluation_"+sssss.str()+"_epsilon"+ssss.str()+"_gen_" + sss.str()+temp.str()+".txt";


    path = path+temp.str()+".txt";      //str is temp as string
    ResultFile.open(path.c_str(),std::ios::app);

    if (!ResultFile) {
        cerr << "Unable to open file!!";
        exit(1);   // call system to stop
    }
    ResultFile <<" ===========================solution detailed ===========================================" << endl;
    ResultFile << " °°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°° " << endl << endl;
    ResultFile<< " °°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°° " << endl;
    int i;
    for(i = 0 ; i < Sol->plan->size(); i ++)
    {
        ResultFile << " TRX: " << i << " a pris la fréquence: "  << Sol->plan->at(i) <<endl;
         ResultFile << " TRX: cout parttiel " << Sol->planCC->at(i).first << " ; " << Sol->planCC->at(i).second << endl;
    }
    ResultFile<< " °°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°° " << endl << endl;
    ResultFile << " °°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°° " << endl;
    ResultFile.close();
}
//================================================================================================
//=================== Ajout 16-6- 2021 ======================================
int GetSolutionRealSize(Individual* Sol)
{
    int i, taille;
    taille = 0;
    for (i = 0; i< Sol->plan->size(); i++)
    {
        if(Sol->plan->at(i)!=-1)
        {
            taille = taille + 1;
        }
    }
    return taille ;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Ajouter le 27 -6-2021 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void ShowPlayerInterventionOrder(Individual* Sol,int ApproachGameEvaluation,string instance,double elapsed_secs,const int  max_gen,const double  epsilon, int SizePIInterventionOrder, int SizePSInterventionOrder)
{
    ofstream ResultFile;
    string path="Resultats/SolPlayerInterventionOrder";
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

   /* int sec =timeinfo->tm_sec;
    temp<<"_";
    temp<<sec;
    temp<<"sec";*/

     stringstream sss;
    stringstream ssss;
    stringstream sssss;
    sss << max_gen;
    ssss << epsilon;
     sssss << ApproachGameEvaluation;

    path = path+ "_Evaluation_"+sssss.str()+"_epsilon"+ssss.str()+  +"_gen_" + sss.str()+temp.str()+".txt";


    path = path+temp.str()+".txt";      //str is temp as string
    ResultFile.open(path.c_str(),std::ios::app);

    if (!ResultFile) {
        cerr << "Unable to open file!!";
        exit(1);   // call system to stop
    }
     ResultFile <<" =========================== TRX Player intervention order  ===========================================" << endl;
    ResultFile << " °°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°° " << endl << endl;
    ResultFile<< " °°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°° " << endl;
    int i;
    ResultFile << " The player PI had played " << SizePIInterventionOrder << " onces" <<endl;
    ResultFile << " The player PS had played " << SizePSInterventionOrder << " onces" <<endl;
    ResultFile << " °°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°° " << endl << endl;
    for(i = 0 ; i < Sol->plan->size(); i ++)
    {
        ResultFile << " at state : " << i << " the player played is  "  << Sol->VecPlayerIntervOrd->at(i).IdentPlayer <<endl;
         ResultFile << " the trx used is  : " <<  Sol->VecPlayerIntervOrd->at(i).IdTRXUsed <<endl;

    }
    ResultFile<< " °°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°° " << endl << endl;
    ResultFile << " °°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°° " << endl;
    ResultFile.close();
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Ajouté le 27 - 6 -2021 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void ShowPlayerTRXOrder(vector <int> *IdTRX,int ApproachGameEvaluation,string instance,double elapsed_secs,const int  max_gen,const double  epsilon)
{
  ofstream ResultFile;
    string path="Resultats/ShowPlayerTRXOrder";
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

   /* int sec =timeinfo->tm_sec;
    temp<<"_";
    temp<<sec;
    temp<<"sec";*/

     stringstream sss;
    stringstream ssss;
    stringstream sssss;
    sss << max_gen;
    ssss << epsilon;
     sssss << ApproachGameEvaluation;

    path = path+ "_Evaluation_"+sssss.str()+"_epsilon"+ssss.str()+  +"_gen_" + sss.str()+temp.str()+".txt";


    path = path+temp.str()+".txt";      //str is temp as string
    ResultFile.open(path.c_str(),std::ios::app);

    if (!ResultFile) {
        cerr << "Unable to open file!!";
        exit(1);   // call system to stop
    }
     ResultFile <<" =========================== TRX Player intervention order  ===========================================" << endl;
    ResultFile << " °°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°° " << endl << endl;
    ResultFile<< " °°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°° " << endl;
    int i;
    for(i = 0 ; i < IdTRX->size(); i ++)
    {
        ResultFile << " Le  " << i << "ème TRX traité par le joueur est " << IdTRX->at(i)<<endl;


    }
    ResultFile<< " °°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°° " << endl << endl;
    ResultFile << " °°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°° " << endl;
    ResultFile.close();
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~é
int GetVectorRealSize(vector <int> * vect)
{
    int taille = 0;
    for (int i= 0; i< vect->size(); i++ )
    {
        if( vect->at(i) != -1)
        {
            taille = taille +1;
        }
    }
    return taille ;
}
//=========================================================================
void ShowNashvaluersResult(int indexNASHEbest,vector <double> NASHEJ, string path, double HV,vector<Individual*> solutionSs)
{
     int k,j;
    ofstream ResultFile;
        ResultFile.open(path.c_str(),std::ios::app);
    if (!ResultFile) {
        cerr << "Unable to open file!!";
        exit(1);   // call system to stop
    }

    ResultFile<< "HV : " << HV << endl;
    ResultFile <<"=============================================" << endl;

    ResultFile << "indexNashBest :" << indexNASHEbest << endl;
       ResultFile <<"=============================================" << endl;

    ResultFile << " Nash[indexNashBest] : " << NASHEJ[indexNASHEbest] << endl;
        ResultFile <<"=============================================" << endl;

      //ResultFile <<"NNNNNNNNNNN les valeurs de nash NNNNNNNNNNNNNNNNNNNN"<<endl;
        ResultFile << " NASHEJ[k] , Interf cost , Sep cost " << endl<<endl;

         for(k=0  ;k < NASHEJ.size(); k++)
    {

        //ResultFile<<" ***********solution : " << k << "*******************" << endl;
        ResultFile << k << " , " << NASHEJ[k] << " ,  " << solutionSs[k]->PIObj <<" , " << solutionSs[k]->PSObj<<endl;



    }
    ResultFile.close();
}
//================================= Ajout le 15- 3-20222==============
void ShowResultNorm(int ApproachGameEvaluation,string instance,int NumGame,double elapsed_secs,const int  max_gen,const double epsilon,vector<Individual*> solutionSs,int indexNASHEbest,vector <double> NASHEJ,vector<Individual*> BestsolutionSs, Individual* solution, string path, double HVNorm)
{

    cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
  cout << " au niveau commum indexNASHEbest= " << indexNASHEbest <<endl;
      cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
    //ecrire le résultat dans un fichier : Resultat/resultatDatesystem.txt
    int k,j;
    ofstream ResultFile;
        ResultFile.open(path.c_str(),std::ios::app);
    if (!ResultFile) {
        cerr << "Unable to open file!!";
        exit(1);   // call system to stop
    }
    //rechercher la meilleur solution pour le joueur PI
      vector<double> VectBestSolPI;
         VectBestSolPI.reserve(max_gen);
        for(k = 0 ; k < solutionSs.size(); k++)
        {
            //cout<< " solutionSs[k]->PIObj " <<solutionSs[k]->PIObj <<endl;
            VectBestSolPI.push_back(solutionSs[k]->PIObjNorm);
            //cout << "VectBestSolPI(k) " << VectBestSolPI[k] <<endl;
        }

      int  indexBestSolPI = 0;
        double BestObjectivePI = 0.0;
       // cout << " VectBestSolPI.size() " << VectBestSolPI.size() << endl;
        VecMinValue(VectBestSolPI,indexBestSolPI);
       // cout << "indexBestSolPI : " << indexBestSolPI << endl;
        BestObjectivePI = solutionSs[indexBestSolPI]->PIObjNorm;
         vector<double> VectBestSolPS;
         VectBestSolPS.reserve(max_gen);
        for(k = 0 ; k < solutionSs.size(); k++)
        {
            //cout<< " solutionSs[k]->PIObj " <<solutionSs[k]->PIObj <<endl;
            VectBestSolPS.push_back(solutionSs[k]->PSObjNorm);
            //cout << "VectBestSolPI(k) " << VectBestSolPI[k] <<endl;
        }

       int indexBestSolPS = 0;
        double BestObjectivePS = 0.0;
       cout << " VectBestSolPI.size() " << VectBestSolPI.size() << endl;
        VecMinValue(VectBestSolPS,indexBestSolPS);
        cout << "indexBestSolPI : " << indexBestSolPI << endl;
        BestObjectivePS = solutionSs[indexBestSolPS]->PSObjNorm;
    ResultFile <<" ===========================Hypervolume===========================================" << endl;
    ResultFile << " HV % :" << HVNorm << endl;
    ResultFile <<" ======================================================================" << endl;
    ResultFile <<"....................... Sans Nash coût séparé......."<<endl;
    ResultFile << "Meiilleur Interference score normalisé  est : " <<  BestObjectivePI  << endl;
    ResultFile << "Meiilleur Separation score normalisé  est : "   <<  BestObjectivePS << endl;
    ResultFile <<" ======================================================================" << endl;
    ResultFile <<"....................... AVEC Nash ......."<<endl;
   //---------------------------------------
    ResultFile << " Pour une valeur de epsilon egale :" << epsilon << endl;

   // ResultFile<<" La valeur de nash est : "  << NASHEJ[indexNASHEbest]<<endl;
    ResultFile << "Meiilleur Interference score   en utilisant NASH est : CI " << solution->PIObj << " ICNorm " << solution->PIObjNorm << endl;//<< solutionSs[indexNASHEbest]->PIObj << endl;
    ResultFile << "Meiilleur Separation score est en utilisant NASH:   CS "<< solution->PSObj<< " ScNorm " << solution->PSObjNorm << endl;//solutionSs[indexNASHEbest]->PSObj << endl;

    ResultFile <<"------------------ MEilleur valeur nash --------------"<<endl;
    ResultFile <<" Meilleur valeur de Nash Normalisé " << NASHEJ[indexNASHEbest] << endl;
    ResultFile <<" Qui se trouve à la position " << indexNASHEbest << " ;" <<endl;

    ResultFile <<" ======================================================================" << endl;

    //----------------------------------------------
    ResultFile << "Temps d'execution : "<<elapsed_secs << " ms" << endl;

    ResultFile << "---- vecteur solution ---"<<endl;
    ResultFile << "TRX ID" <<" , " <<"Frequency"<<endl;
    ResultFile << "NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN" <<endl;

   // ResultFile <<" la meilleur solution corrspond au  NASHEJ[ "<< indexNASHEbest<<"] : " <<NASHEJ.at(indexNASHEbest)<<endl;
    ResultFile <<"########################################################"<<endl;
    ResultFile << " ----------------LEs meilleurs solutions trouvées -------------------" <<endl;
      for(k=0  ;k < BestsolutionSs.size(); k++)
    {
        ResultFile<<" ***********solution : " << k << "*******************" << endl;
        ResultFile<<" Coût d'interference : " << BestsolutionSs[k]->PIObj << endl;
       // ResultFile<<" Coût d'interference : " << BestsolutionSsNorm[k]->PIObj << endl;
        ResultFile<<" Coût de séparation " << BestsolutionSs[k]->PSObj << endl;
       // ResultFile<<" Coût de séparation " << BestsolutionSsNorm[k]->PSObj << endl;
       // ResultFile<<" Valeur de Nash  " << NASHEJ[k]  << endl;
        ResultFile<<"................................."<<endl;


    }
    ResultFile <<"########################################################"<<endl;

    /*
   for(k=0;k<max_gen; k++)
    {
        ResultFile << " NASHEJ[ " << k << " ] : " << NASHEJ[k] << endl;
        ResultFile << " ------------" << endl;
        ResultFile << " PI Objectif solutionSs[k]->PIObj : " << solutionSs[k]->PIObj<<endl;
        ResultFile << " PS Objectif solutionSs[k]->PSObj : " << solutionSs[k]->PSObj<<endl;
        ResultFile << "................................." << endl;


    }
        ResultFile <<"-----------" << endl;
        */
    ResultFile <<"NNNNNNNNNNN les valeurs de nash NNNNNNNNNNNNNNNNNNNN"<<endl;
        ResultFile << " IC   ,	SC  ,  Icnorm,  Scnorm,  Icbest,	Scbest,	NashNorm " << endl;
         for(k=0  ;k < NASHEJ.size(); k++)
    {
         ResultFile << solutionSs[k]->PIObj << ", " << solutionSs[k]->PSObj << ", " <<  solutionSs[k]->PIObjNorm << ", " << solutionSs[k]->PSObjNorm << ", " << NASHEJ[k] << endl;

    }

         /*for(k=0  ;k < NASHEJ.size(); k++)
    {
        ResultFile<<" ***********solution : " << k << "*******************" << endl;
        ResultFile<<" NASHEJ[" << k <<"] : " << NASHEJ[k] << ", Interf cost " << solutionSs[k]->PIObj <<", Sep cost "<< solutionSs[k]->PSObj<<endl;
        ResultFile<<" NASHEJ[" << k <<"] : " << NASHEJ[k] << ", Interf cost " << solutionSs[k]->PIObjNorm <<", Sep cost "<< solutionSs[k]->PSObjNorm<<endl;

        ResultFile<<"................................."<<endl;


    }*/


    ResultFile.close();
    //***********************************************************
}

//================================ Fin ajout 15-3-2022 ==============

>>>>>>> 0514ea9fae0f841576757defb02235a9189b0fad
