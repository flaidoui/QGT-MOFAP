#ifndef AFP_H
#define AFP_H

#include <string>
#include <vector>
#include <map>
#include <set>

using namespace std;

<<<<<<< HEAD
#include "../Individual/Individual.h"


=======
#include "../Individual/Individual.h"


>>>>>>> 0514ea9fae0f841576757defb02235a9189b0fad
	struct TRXs {
		int trxID;
		int sectorID;
		int siteID;
		string type;
		vector<int> * validFrequencies;
<<<<<<< HEAD
		set<int> * validFrequenciesSet;
       // vector<int> *BlockedFrequencies;
=======
		set<int> * validFrequenciesSet;
       // vector<int> *BlockedFrequencies;
>>>>>>> 0514ea9fae0f841576757defb02235a9189b0fad
       vector<int> * AvailableFrequencies;//l'ensemble des fréquences
	};

class AFP {

	public:
	/*struct TRX {
		int trxID;
		int sectorID;
		int siteID;
		string type;
		vector<int> * validFrequencies;
		set<int> * validFrequenciesSet;
<<<<<<< HEAD
	};*/
	typedef TRXs TRX;


	struct Parameters {
		double sameSectorCoChBcch;
		double sameSectorCoChTch;
		double sameSectorAdjChBcch;
		double sameSectorAdjChTch;

		double sameSiteCoBcchBcch;
		double sameSiteCoBcchTch;
		double sameSiteCoTchTch;
		double sameSiteAdjBcchBcch;
		double sameSiteAdjBcchTch;
		double sameSiteAdjTchTch;

		double nbrCoBcchBcch;
		double nbrCoBcchTch;
		double nbrCoTchTch;

		double nbrAdjBcchBcch;
		double nbrAdjBcchTch;
		double nbrAdjTchTch;

		double nbr2CoBcchBcch;
		double nbr2CoBcchTch;
		double nbr2CoTchTch;

		//constraints
		double sameSectorChSep;
		double sameSiteChSep;

		//signaling
		double adjChannelRejection;
		double signallingThreshold;
	} projectParameters;

	//variables
	vector<TRX>                               trxs                ; //transceivers
	map<int, map<int, pair<double,double> > > interferenceMatrix  ; //IM
	map<int, vector<int> >                    interfereTo         ; //sectors to which each sector//LAIDOI FATMA Comment:interfereinterfereTo[interferer]=victime
	map<int, vector<int> >                    sectors2trxs        ; //un secteur a plusier trx//map sectors to trxs//FATMA; commbien on a de trx dans le secteur
	map<int, int>                             sectorConstraintSep ; //sector constraint separation
	map<int, vector<int> >                    site2sectors        ; //un site a plusieur secteur//map sites to sectors
	map<int, int>                             siteConstraintSep   ; //site constraint separation
	map<int, vector<int> >                    neighbors           ; //secteur et ses secteur voisin immédiat//1-hop neighbors
	map<int, vector<int> >                    secondNeighbors     ; //secteur et ses secteur voisin à deux saut2-hop neighbors
	vector<double>                    ListTrxMaxValueinterferCost;
	//bool                                      optionsLoaded=false ; //are project options already loaded?
	int maxExecutionTime;
    //°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°° Ajouté le 27-3-2019 °°°°°°°°°°°°°°°°°°°°°°°°°°
     vector < pair<int,double>  > MaxCostITrx ; //   MaxCostITrx[i].first = trxID; MaxCostITrx[i].second = son plus grand cout

    //°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°


	//methods
	//AFP();
	AFP(string instance);
	~AFP();

	void loadTrxs(char * filename);
	void loadIM(char * filename);
	void loadSectors(char * filename);
	void loadSites(char * filename);
	void loadOptions(char * filename);
	void loadNeighbors(char * filename);
	void loadSecondNeighbors(char * filename);
=======
	};*/
	typedef TRXs TRX;


	struct Parameters {
		double sameSectorCoChBcch;
		double sameSectorCoChTch;
		double sameSectorAdjChBcch;
		double sameSectorAdjChTch;

		double sameSiteCoBcchBcch;
		double sameSiteCoBcchTch;
		double sameSiteCoTchTch;
		double sameSiteAdjBcchBcch;
		double sameSiteAdjBcchTch;
		double sameSiteAdjTchTch;

		double nbrCoBcchBcch;
		double nbrCoBcchTch;
		double nbrCoTchTch;

		double nbrAdjBcchBcch;
		double nbrAdjBcchTch;
		double nbrAdjTchTch;

		double nbr2CoBcchBcch;
		double nbr2CoBcchTch;
		double nbr2CoTchTch;

		//constraints
		double sameSectorChSep;
		double sameSiteChSep;

		//signaling
		double adjChannelRejection;
		double signallingThreshold;
	} projectParameters;

	//variables
	vector<TRX>                               trxs                ; //transceivers
	map<int, map<int, pair<double,double> > > interferenceMatrix  ; //IM
	map<int, vector<int> >                    interfereTo         ; //sectors to which each sector//LAIDOI FATMA Comment:interfereinterfereTo[interferer]=victime
	map<int, vector<int> >                    sectors2trxs        ; //un secteur a plusier trx//map sectors to trxs//FATMA; commbien on a de trx dans le secteur
	map<int, int>                             sectorConstraintSep ; //sector constraint separation
	map<int, vector<int> >                    site2sectors        ; //un site a plusieur secteur//map sites to sectors
	map<int, int>                             siteConstraintSep   ; //site constraint separation
	map<int, vector<int> >                    neighbors           ; //secteur et ses secteur voisin immédiat//1-hop neighbors
	map<int, vector<int> >                    secondNeighbors     ; //secteur et ses secteur voisin à deux saut2-hop neighbors
	vector<double>                    ListTrxMaxValueinterferCost;
	//bool                                      optionsLoaded=false ; //are project options already loaded?
	int maxExecutionTime;
    //°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°° Ajouté le 27-3-2019 °°°°°°°°°°°°°°°°°°°°°°°°°°
     vector < pair<int,double>  > MaxCostITrx ; //   MaxCostITrx[i].first = trxID; MaxCostITrx[i].second = son plus grand cout

    //°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°


	//methods
	//AFP();
	AFP(string instance);
	~AFP();

	void loadTrxs(char * filename);
	void loadIM(char * filename);
	void loadSectors(char * filename);
	void loadSites(char * filename);
	void loadOptions(char * filename);
	void loadNeighbors(char * filename);
	void loadSecondNeighbors(char * filename);
>>>>>>> 0514ea9fae0f841576757defb02235a9189b0fad
	void loadFrequencyPlanFromFile(char * filename,Individual* & Sol);
	double signalingCost(vector<int> * plan,
						vector < pair <double,double> > * planCC,
						int victimSector,
<<<<<<< HEAD
						int interfererSector);
	double computeChannelInterference(vector<int> * plan,
	          vector <pair<double,double> > * planningCC,
	          int victimTrx,
	          int interfererTrx);
	double c2iCost(vector<int> * planning,
						vector <pair <double,double> > * planningCC);
	void randomPlanning(Individual * solution);
	double interferenceBasedFitness(Individual * solution);
	bool checkFrequencyPlan(vector<int> * plan);
	//###############################" Add my functions -LAIDOUI FATMA ===
	double computeChannelInterference(int victimFrequency ,int interfererFrequency, int victimTrx, int interfererTrx);
	double ComputeSolutionInterference(Individual* solution);//calculer le cout totale de la solution
=======
						int interfererSector);
	double computeChannelInterference(vector<int> * plan,
	          vector <pair<double,double> > * planningCC,
	          int victimTrx,
	          int interfererTrx);
	double c2iCost(vector<int> * planning,
						vector <pair <double,double> > * planningCC);
	void randomPlanning(Individual * solution);
	double interferenceBasedFitness(Individual * solution);
	bool checkFrequencyPlan(vector<int> * plan);
	//###############################" Add my functions -LAIDOUI FATMA ===
	double computeChannelInterference(int victimFrequency ,int interfererFrequency, int victimTrx, int interfererTrx);
	double ComputeSolutionInterference(Individual* solution);//calculer le cout totale de la solution
>>>>>>> 0514ea9fae0f841576757defb02235a9189b0fad
	double ComputeSolutionSeparationCost(Individual* solution);//calculer le cout de séparation totale de la solution

}; //class AFP
#endif
