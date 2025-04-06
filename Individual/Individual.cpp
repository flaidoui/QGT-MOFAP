
#include <iostream>
<<<<<<< HEAD
#include "Individual.h"
//#include "../AFP/AFP.h"


using namespace std;
=======
#include "Individual.h"
//#include "../AFP/AFP.h"


using namespace std;
>>>>>>> 0514ea9fae0f841576757defb02235a9189b0fad

Individual::Individual(){
	cost = 0.0;
	plan = new vector<int>();
<<<<<<< HEAD
	planCC        = new vector < pair <double,double> >();
	//initialisation de mes  variables - LAIDOUI Fatma
	PIObj = 0.0;
	PSObj = 0.0;
	VecPlayerIntervOrd = new vector < PlayerInterventionOrder>();
	//PlanAffect = new vector< pair<int,int> > ();
	 //=======================================================================
        //============================= Ajout 16-3-2022 ======================
      PIObjNorm = 0 ;//valeur de fonction objective du joueur PI
      PSObjNorm = 0;//valeur de fonction objective du joueur PS

           //=======================================================================
        //============================= Fin 16-3-2022 ======================

}
/*Individual::Individual(AFP * afpProblem){
	int k;
	cost = 0.0;
    plan = new vector<int>(afpProblem->trxs.size());
    planCC = new vector<double>(afpProblem->trxs.size());
    for(k=0;k<solution->plan->size();k++)
    {
      plan->at(k)=-1;
      solution->planCC->at(k)=0.0;
=======
	planCC        = new vector < pair <double,double> >();
	//initialisation de mes  variables - LAIDOUI Fatma
	PIObj = 0.0;
	PSObj = 0.0;
	VecPlayerIntervOrd = new vector < PlayerInterventionOrder>();
	//PlanAffect = new vector< pair<int,int> > ();
	 //=======================================================================
        //============================= Ajout 16-3-2022 ======================
      PIObjNorm = 0 ;//valeur de fonction objective du joueur PI
      PSObjNorm = 0;//valeur de fonction objective du joueur PS

           //=======================================================================
        //============================= Fin 16-3-2022 ======================

}
/*Individual::Individual(AFP * afpProblem){
	int k;
	cost = 0.0;
    plan = new vector<int>(afpProblem->trxs.size());
    planCC = new vector<double>(afpProblem->trxs.size());
    for(k=0;k<solution->plan->size();k++)
    {
      plan->at(k)=-1;
      solution->planCC->at(k)=0.0;
>>>>>>> 0514ea9fae0f841576757defb02235a9189b0fad
    }
}*/

Individual::~Individual(){
	delete plan;
<<<<<<< HEAD
	delete planCC;
=======
	delete planCC;
>>>>>>> 0514ea9fae0f841576757defb02235a9189b0fad
	//delete PlanAffect;
}


ostream& operator<<(ostream &os, const Individual &ind){
	/*for (unsigned int i = 0; i < ind.frequencyPlan->size(); i++){
		os << (*ind.frequencyPlan)[i] << " ";
	} //*/
	os << "Coste = " << ind.cost << endl;
	return os;
<<<<<<< HEAD
}
/*void Individual::InitIndividual(AFP * afpProblem)
{
    int i;
    plan.reserve(afpProblem->trxs.size());
    for(i = 0; i< afpProblem->trxs.size();i++)
    {
        plan->at(i) = - 1;
        planCC->at(i) = 0.0 ;
    }
}
*/
=======
}
/*void Individual::InitIndividual(AFP * afpProblem)
{
    int i;
    plan.reserve(afpProblem->trxs.size());
    for(i = 0; i< afpProblem->trxs.size();i++)
    {
        plan->at(i) = - 1;
        planCC->at(i) = 0.0 ;
    }
}
*/
>>>>>>> 0514ea9fae0f841576757defb02235a9189b0fad
