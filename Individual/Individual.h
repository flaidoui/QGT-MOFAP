#ifndef __INDIVIDUAL_H__
#define __INDIVIDUAL_H__

<<<<<<< HEAD
#include <vector>
//--------------- LAIDOUI FATMA ADD
//#include "../AFP/AFP.h"

//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Ajouté le 27-6-2021 ~~~~~~~~~~~~~~~~~~~~~~
//Enregistrer l'information à quel moment le joueur est intervenu ~~~~~~~~~~~~~~~~~~~~
struct PlayerInterventionOrder //
{
    int IdentPlayer;//l'identité du joeur qui est intervenu
    int IdTRXUsed;// l'identité du trx
=======
#include <vector>
//--------------- LAIDOUI FATMA ADD
//#include "../AFP/AFP.h"

//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Ajouté le 27-6-2021 ~~~~~~~~~~~~~~~~~~~~~~
//Enregistrer l'information à quel moment le joueur est intervenu ~~~~~~~~~~~~~~~~~~~~
struct PlayerInterventionOrder //
{
    int IdentPlayer;//l'identité du joeur qui est intervenu
    int IdTRXUsed;// l'identité du trx
>>>>>>> 0514ea9fae0f841576757defb02235a9189b0fad
};
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Fin ajout 27-6-2021 ~~~~~~~~~~~~~~~~~~~~~~~~é
using namespace std;

class Individual {
	public:
<<<<<<< HEAD
		Individual();
=======
		Individual();
>>>>>>> 0514ea9fae0f841576757defb02235a9189b0fad
		//Individual(AFP * afpProblem);
		~Individual();

		vector <int> * plan;        //victimFrequency     = plan->at(victimTrx)
<<<<<<< HEAD
		vector < pair <double,double> > * planCC;  //planningCC->at(victimTrx) += cost;
		double cost;
		//############## my variables - LAIDOUI FATMA
		vector< pair <int,int> > * PlanAffect;

        //void InitIndividual(AFP * afpProblem);
		double PIObj;//valeur de fonction objective du joueur PI
        double PSObj;//valeur de fonction objective du joueur PS
        //=======================================================================
        //============================= Ajout 16-3-2022 ======================
        double PIObjNorm;//valeur de fonction objective du joueur PI
        double PSObjNorm;//valeur de fonction objective du joueur PS

           //=======================================================================
        //============================= Fin 16-3-2022 ======================
        //~~~~~~~~~~~~~~~~~~~~~ ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        //~~~~~~~~~~~~~Ajout 27 -6- 2021 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        vector <PlayerInterventionOrder> * VecPlayerIntervOrd;
        //VecPlayerIntervOrd[i].IdentPlayer= j; Le player "j" est intervenu à l'iteration i
        //VecPlayerIntervOrd[i].IdTRXUsed = k; à l'itération i , le TRX "k" , on luit affecter une fréquence
=======
		vector < pair <double,double> > * planCC;  //planningCC->at(victimTrx) += cost;
		double cost;
		//############## my variables - LAIDOUI FATMA
		vector< pair <int,int> > * PlanAffect;

        //void InitIndividual(AFP * afpProblem);
		double PIObj;//valeur de fonction objective du joueur PI
        double PSObj;//valeur de fonction objective du joueur PS
        //=======================================================================
        //============================= Ajout 16-3-2022 ======================
        double PIObjNorm;//valeur de fonction objective du joueur PI
        double PSObjNorm;//valeur de fonction objective du joueur PS

           //=======================================================================
        //============================= Fin 16-3-2022 ======================
        //~~~~~~~~~~~~~~~~~~~~~ ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        //~~~~~~~~~~~~~Ajout 27 -6- 2021 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        vector <PlayerInterventionOrder> * VecPlayerIntervOrd;
        //VecPlayerIntervOrd[i].IdentPlayer= j; Le player "j" est intervenu à l'iteration i
        //VecPlayerIntervOrd[i].IdTRXUsed = k; à l'itération i , le TRX "k" , on luit affecter une fréquence
>>>>>>> 0514ea9fae0f841576757defb02235a9189b0fad

};

#endif
