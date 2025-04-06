<<<<<<< HEAD
#include <stdlib.h>
#include <cfloat>
#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>
#include <map>
#include <time.h>

#include "../Individual/Individual.h"
#include "AFP.h"
//################################ Mes bibliothèques  LAIDOUI Fatma ###########"
//####################################################
#include <algorithm>//copy

//###################################"
/*AFP::AFP() {
    int i;
    for(i=0;trxs.size();i++)
    {
       trxs[i].AvailableFrequencies=trxs[i].validFrequencies;
    }
}*/

AFP::AFP(string instance) {

	//loading files
  if (instance == "Denver") {
    loadOptions("./data/Denver.opt.txt");
    loadTrxs("./data/Denver.trx.txt");
    loadSectors("./data/Denver.sector.txt");
    loadIM("./data/Denver.IM.txt");
    loadSites("./data/Denver.site.txt");
    loadNeighbors("./data/Denver.1-hop.neighbors.txt");
    loadSecondNeighbors("./data/Denver.2-hop.neighbors.txt");
  } //else
  else if (instance == "LA") {
    loadOptions("./data/LA.opt.txt");
    loadTrxs("./data/LA.trx.txt");
    loadSectors("./data/LA.sector.txt");
    loadIM("./data/LA.IM.txt");
    loadSites("./data/LA.site.txt");
    loadNeighbors("./data/LA.1-hop.neighbors.txt");
    loadSecondNeighbors("./data/LA.2-hop.neighbors.txt");
  } //else
  else if (instance == "Seattle") {
    loadOptions("./data/Seattle.opt.txt");
    loadOptions("./data/Seattle.opt.txt");
    loadTrxs("./data/Seattle.trx.txt");
    loadSectors("./data/Seattle.sector.txt");
    loadIM("./data/Seattle.IM.txt");
    loadSites("./data/Seattle.site.txt");
    loadNeighbors("./data/Seattle.1-hop.neighbors.txt");
    loadSecondNeighbors("./data/Seattle.2-hop.neighbors.txt");
    /*loadOptions("./data/data_fatima/Seattle_Fatima.opt.txt");
    loadTrxs("./data/data_fatima/Seattle_Fatima.trx.txt");
    loadSectors("./data/data_fatima/Seattle_Fatima.sector.txt");
    loadIM("./data/data_fatima/Seattle_Fatima.IM.txt");
    loadSites("./data/data_fatima/Seattle_Fatima.site.txt");
    loadNeighbors("./data/data_fatima/Seattle_Fatima.1-hop.neighbors.txt");
    loadSecondNeighbors("./data/data_fatima/Seattle_Fatima.2-hop.neighbors.txt");*/
  } //else
  else {
    cout << "Invalid instance " << instance << endl;
    exit(-1);
  } //else
//++++++++++++++++++++++++++
     //int i,j,indextrx ;
//calculer pour chque trx non traité , la taille des trx avec qui il interfere et l enregistrer dans LTrxNTreatedsSizeinterfere
           // vector <double> LTrxNTreatedsMaxValueinterferCost;

           /* ListTrxMaxValueinterferCost.reserve(trxs.size());
             double value;
            double cost = 0.0 ;
            //cherche la valeur max d in terference pour chaque trx
            for(i = 0 ; i < trxs.size() ; i++)
            {
                for (j = 0 ; interferenceMatrix[i].size(); j++)//parcourir tous les trx avec
                    //lesquel le trx  LTrxNTreateds[i].trxID] interfere
                {
                    if (i!=j)
                    {

                        if ( interferenceMatrix[i][j].first > interferenceMatrix[i][j].second )
                            value  = interferenceMatrix[i][j].first;
                        else
                            value  = interferenceMatrix[i][j].second;


                        if (cost < value)
                        {
                            cost = value;
                        }
                    }
                }
               ListTrxMaxValueinterferCost.push_back(cost);

            }
*/
        //°°°°°°°°°°°°°°°°°°°°°Fatma Laidoui : ajouté le 27-3-2019°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°
    int i,j ; double costtrx;
    //MaxCostITrx.reserve(trxs.size());
        // construire le tableau pair cost qui contient pour chqua trx le plus grand cout q il a
    for (i = 0 ; i < trxs.size() ; i++)
    {
            // paircost[i].first = i ;// nous utilisant une paire, pour enregistrer l information du trx paircost.first après le tri
            costtrx = 0.0 ;
        int sectorI = trxs[i].sectorID ;
       for (j = 0 ; j < trxs.size() ; j++)
       {
          int sectorJ = trxs[j].sectorID;
          if (costtrx < interferenceMatrix[sectorI][sectorJ].first)
          {
             costtrx  = interferenceMatrix[sectorI][sectorJ].first;
          }
          else
          {
              if (costtrx < interferenceMatrix[sectorI][sectorJ].second)
                costtrx  = interferenceMatrix[sectorI][sectorJ].second;
          }
       }
       // paircost[i].second = costtrx;
       MaxCostITrx.push_back({i,costtrx});
   }

    //°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°


  //++++++++++++++++++++++++++++++++

	maxExecutionTime = 120;



       //########################
} //

AFP::~AFP() {
} //



/******************************************************************************/
/**
 * Generate a random frequency planning
 */
void AFP::randomPlanning(Individual * solution) {
  int index;

  for (int i = 0; i < trxs.size(); i++) {
    index = rand() % trxs[i].validFrequencies->size();
    solution->plan->at(i) = trxs[i].validFrequencies->at(index);
  } //for
}; //random planning




/******************************************************************************/
/**
 * Load TRXs information stored in filename
 */
void AFP::loadTrxs(char * filename) {

  ifstream file(filename,ios_base::in);

  if (!file.good()) {
    cout << "Error loading file " << filename << endl;
    exit(-1);
  } //if

  char line[256];
  file.getline(line,256);

  //create TRX
  TRX * t = new TRX();
  //read trx ID
  file >> t->trxID;

  while (!file.eof()) {

    //read type
    file >> t->type;
    //read sector ID
    file >> t->sectorID;
    //read site ID
    file >> t->siteID;
    //read valid frequencies
    int numberOfFrequencies;
    int frequency;
    file >> numberOfFrequencies;
    vector<int> * freq = new vector<int>();
    vector<int> * freqs = new vector<int>();//---Ajout LAIDOUI FATMA ------------
    for (int i = 0; i < numberOfFrequencies; i++) {
      file >> frequency;
      freq->push_back(frequency);
      freqs->push_back(frequency);//---Ajout LAIDOUI FATMA ------------
    } //for
    t->validFrequencies = freq;
    t->AvailableFrequencies = freqs;//---Ajout LAIDOUI FATMA ------------

    //store TRX
    //trxs[t->trxID] = *t;
    trxs.push_back(*t);
    t = new TRX();
    file >> t->trxID;
  } //while
  file.close();

  //cout << trxs.size() << " TRXs successfully readed" << endl;
}; //loadTrxs

/******************************************************************************/
/**
 * Numerical method for computing function Q
 */
float erfcc(float x) {
  float t, z, ans;

  z = (float)fabs(x);//Returns the absolute value of x:
  t = 1.0F / (1.0F + 0.5F * z);
  ans = (float)(t * exp(-z * z - 1.26551223F + t *
		(1.00002368F + t *
		 (0.37409196F + t *
		  (0.09678418F + t *
		   (-0.18628806F + t *
		    (0.27886807F + t *
		     (-1.13520398F + t *
		      (1.48851587F + t *
		       (-0.82215223F + t * 0.17087277F)
		      )
		     )
		    )
		   )
		  )
		 )
		)
		));

  return  x >= 0.0F ? ans : 2.0F - ans;

}; //erfcc

/******************************************************************************/
/**
 * Load interference matrix from file
 */
void AFP::loadIM(char * filename) {
  ifstream file(filename,ios_base::in);

  if (!file.good()) {
    cout << "Error loading file " << filename << endl;
    exit(-1);
  } //if

  char line[256];
  int  victim;
  int  interferer;
  double mean, std, cochannel, adjchannel;
  file.getline(line,256);

  //interferenceMatrix = new map<int, map<int, pair<double,double> > >();

  //read victim
  file >> victim;
  int previousVictim = victim;
  map<int, pair<double,double> > * node = new map<int, pair<double,double> >();

  while (!file.eof()) {
    //read interferer
    file >> interferer;
    interfereTo[interferer].push_back(victim);

    //read mean and std
    file >> mean;
    file >> std;

    //cout << victim << "," << interferer << "->" << mean << "," << std << endl;
    cochannel = 100.0*(1.0
  		                -
  		                0.5*erfcc(
  		                          (projectParameters.signallingThreshold - mean)
  		                          /
  		                          (std*sqrt(2.0f))
  		                         )
  		                );
  	adjchannel = 100.0*(1.0
  		                -
  		                0.5*erfcc(
  		                          (projectParameters.signallingThreshold - mean - projectParameters.adjChannelRejection)
  		                          /
  		                          (std*sqrt(2.0f))
  		                         )
  		                );

    //(*node)[interferer] = pair<double,double>(mean,std);
    (*node)[interferer] = pair<double,double>(cochannel,adjchannel);

    //read another victim
    previousVictim = victim;
    file >> victim;

    if (victim != previousVictim) {
      interferenceMatrix[previousVictim] = *node;
      node = new map<int, pair<double,double> >();
    } //if
    else if (file.eof())
      interferenceMatrix[victim] = *node;
  } //while
  file.close();

  /*for (map<int, vector<int> >::iterator iter = interfereTo.begin();
       iter != interfereTo.end();
       iter ++) {
        cout << (*iter).first << ": ";
        for (vector<int>::iterator iter2 = (*iter).second.begin();
          iter2 != (*iter).second.end();
          iter2++)
            cout << (*iter2) << " ";
        cout << endl;
        char bas;
        cin >> bas;
      } //for */


}; //loadIM

/******************************************************************************/
/**
 * Load sector information from file
 */
void AFP::loadSectors(char * filename) {
  ifstream file(filename,ios_base::in);

  if (!file.good()) {
    cout << "Error loading file " << filename << endl;
    exit(-1);
  } //if

  //get the first line
  char line[256];
  file.getline(line,256);

  int sector;
  int constraint;
  file >> sector;

  while (!file.eof()) {
  	//get the constraint value for the sector
  	file >> constraint;
    sectorConstraintSep[sector] = constraint;

    //read the list of trxs
    int numberOfTrxs, trx;
    file >> numberOfTrxs;
    for (int i = 0; i < numberOfTrxs; i++) {
    	file >> trx;
    	sectors2trxs[sector].push_back(trx);
    } //for

    //read new sector
    file >> sector;
  } //while
  file.close();

}; //loadSectors

/******************************************************************************/
/**
 * Load project options from file
 */
 void AFP::loadOptions(char * filename) {
  ifstream file(filename,ios_base::in);

  if (!file.good()) {
    cout << "Error loading file " << filename << endl;
    exit(-1);
  } //if

  //get the first line
  char line[256];
  file.getline(line,256);

  string key;

  //read the first key
  file >> key;
  while (!file.eof()) {
  	if (key == "Sector_Co_Ch_TCH")
  		file >> projectParameters.sameSectorCoChTch;
  	else if (key == "Sector_Co_Ch_BCCH")
  		file >> projectParameters.sameSectorCoChBcch;
  	else if (key == "Sector_Adj_Ch_TCH")
  		file >> projectParameters.sameSectorAdjChTch;
  	else if (key == "Sector_Adj_Ch_BCCH")
  		file >> projectParameters.sameSectorAdjChBcch;
  	else if (key == "Sector_Ch_Sep")
  		file >> projectParameters.sameSectorChSep;
  	else if (key == "Site_Co_Ch_BCCH_BCCH")
  		file >> projectParameters.sameSiteCoBcchBcch;
  	else if (key == "Site_Co_Ch_BCCH_TCH")
  		file >> projectParameters.sameSiteCoBcchTch;
  	else if (key == "Site_Co_Ch_TCH_TCH")
  		file >> projectParameters.sameSiteCoTchTch;
  	else if (key == "Site_Adj_Ch_BCCH_BCCH")
  		file >> projectParameters.sameSiteAdjBcchBcch;
  	else if (key == "Site_Adj_Ch_BCCH_TCH")
  		file >> projectParameters.sameSiteAdjBcchTch;
  	else if (key == "Site_Adj_Ch_TCH_TCH")
  		file >> projectParameters.sameSiteAdjTchTch;
  	else if (key == "Site_Ch_Sep")
  		file >> projectParameters.sameSiteChSep;
  	else if (key == "Nbr_Co_Ch_BCCH_BCCH")
  		file >> projectParameters.nbrCoBcchBcch;
  	else if (key == "Nbr_Co_Ch_BCCH_TCH")
  		file >> projectParameters.nbrCoBcchTch;
  	else if (key == "Nbr_Co_Ch_TCH_TCH")
  		file >> projectParameters.nbrCoTchTch;
  	else if (key == "Nbr_Adj_Ch_BCCH_BCCH")
  		file >> projectParameters.nbrAdjBcchBcch;
  	else if (key == "Nbr_Adj_Ch_BCCH_TCH")
  		file >> projectParameters.nbrAdjBcchTch;
  	else if (key == "Nbr_Adj_Ch_TCH_TCH")
  		file >> projectParameters.nbrAdjTchTch;
  	else if (key == "Nbr2_Co_Ch_BCCH_BCCH")
  		file >> projectParameters.nbr2CoBcchBcch;
  	else if (key == "Nbr2_Co_Ch_BCCH_TCH")
  		file >> projectParameters.nbr2CoBcchTch;
  	else if (key == "Nbr2_Co_Ch_TCH_TCH")
  		file >> projectParameters.nbr2CoTchTch;
  	else if (key == "Adjacent_Channel_Interference_Rejection")
  		file >> projectParameters.adjChannelRejection;
  	else if (key == "Signalling_Threshold")
  		file >> projectParameters.signallingThreshold;
  	else {
  		cout << "Wrong key " << key << endl;
  		exit(-1);
  	} //else
  	file >> key;
  } //while

  file.close();


}; //loadOptions

/******************************************************************************/
/**
 * Load sites from file
 */
void AFP::loadSites(char * filename) {
	//open file
	ifstream file(filename,ios_base::in);

	if (!file.good()) {
    cout << "Error loading file " << filename << endl;
    exit(-1);
  } //if

  //get the first line
  char line[256];
  file.getline(line,256);

  int site, numberOfSectors, sector;

  file >> site;
  while (!file.eof()) {
  	//read separation constraint
  	file >> siteConstraintSep[site] ;

  	//read number of sectors
  	file >> numberOfSectors;

  	//read sectors
  	for (int i = 0; i < numberOfSectors; i++) {
  		file >> sector;
  		site2sectors[site].push_back(sector);
  	} //for

  	file >> site;
  } //while
  file.close();


}; //loadSites

/******************************************************************************/
/**
 * Load neighbors from file
 */
void AFP::loadNeighbors(char * filename) {
	//open file
	ifstream file(filename,ios_base::in);

	if (!file.good()) {
    cout << "Error loading file " << filename << endl;
    exit(-1);
  } //if

  //get the first line
  char line[256];
  file.getline(line,256);

  int sector, numberOfNeighbors, neighbor;

  file >> sector;
  while (!file.eof()) {
  	//read neighbors
  	file >> numberOfNeighbors;
  	for (int i = 0; i < numberOfNeighbors; i++) {
  		file >> neighbor;
  		neighbors[sector].push_back(neighbor);
  	} //for

  	//read new sector
  	file >> sector;
  } //while
  file.close();

}; //loadNeighbors

/******************************************************************************/
/**
 * Load neighbors from file
 */
void AFP::loadSecondNeighbors(char * filename) {
	//open file
	ifstream file(filename,ios_base::in);

	if (!file.good()) {
    cout << "Error loading file " << filename << endl;
    exit(-1);
  } //if

  //get the first line
  char line[256];
  file.getline(line,256);

  int sector, numberOfNeighbors, neighbor;

  file >> sector;
  while (!file.eof()) {
  	//read neighbors
  	file >> numberOfNeighbors;
  	for (int i = 0; i < numberOfNeighbors; i++) {
  		file >> neighbor;
  		secondNeighbors[sector].push_back(neighbor);
  	} //for

  	//read new sector
  	file >> sector;
  } //while
  file.close();


}; //loadSecondNeighbors



/******************************************************************************/
/**
 * Compute interferences between a victim TRX and an interferer TRX
 */
double AFP::computeChannelInterference(vector<int> * plan, vector<pair<double,double> > * planningCC, int victimTrx, int interfererTrx)
{
	double cost = 0.0;
	int victimFrequency     = plan->at(victimTrx);
	int interfererFrequency = plan->at(interfererTrx);




	if (trxs[victimTrx].sectorID == trxs[interfererTrx].sectorID) {//LAIdoui Fatma comment: les trx sont dans dans le meme secteur
	  if (victimFrequency == interfererFrequency)//L.F:meme trx et meme Fréquence
	    if ((trxs[victimTrx].type == "BCCH") || (trxs[interfererTrx].type == "BCCH"))
	      cost += projectParameters.sameSectorCoChBcch;
	    else
	      cost += projectParameters.sameSectorCoChTch;
	  else if (abs(victimFrequency - interfererFrequency) == 1)//LF:fréquence adjacente
	    if ((trxs[victimTrx].type == "BCCH") || (trxs[interfererTrx].type == "BCCH"))
	      cost += projectParameters.sameSectorAdjChBcch;
	    else
	      cost += projectParameters.sameSectorAdjChTch; //*/
	 } //if
	 else {
	   //trxs[victimTrx].sectorID != trxs[interfererTrx].sectorID
	   //only co-channel and adj-channel are considered
  	 if (victimFrequency == interfererFrequency) {
  		 cost += interferenceMatrix[trxs[victimTrx].sectorID][trxs[interfererTrx].sectorID].first;
  	 } //if
  	 else if (abs(victimFrequency - interfererFrequency) == 1) {
  	 	cost += interferenceMatrix[trxs[victimTrx].sectorID][trxs[interfererTrx].sectorID].second;
  	 } //if
	 } //else


  //if (cost > 0)
	//cout << "(" << victimTrx << "," << interfererTrx << ") - (" << victimFrequency << "," << interfererFrequency << ") -> " << cost << endl;
	/*char bas;
  cin >> bas; //*/

  //update the component cost
  //planningCC->at(victimTrx) += cost;
  //cout << victimFrequency << " - " << interfererFrequency << " -> " << cost << endl;
  return cost;


}; //computeChanneInterference

/******************************************************************************/
/**
 * Compute interferences between a victim sector and an interferer sector
 */
double AFP::signalingCost(vector<int> * plan, vector<pair<double,double> > * planCC, int victimSector, int interfererSector) {
	double cost = 0.0;

	for(vector<int>::iterator victimTrx = sectors2trxs[victimSector].begin();
		  victimTrx != sectors2trxs[victimSector].end();
		  victimTrx ++) {
		  	for (vector<int>::iterator interfererTrx = sectors2trxs[interfererSector].begin();
		  		interfererTrx != sectors2trxs[interfererSector].end();
		  		interfererTrx ++) {
		  			if (*victimTrx != *interfererTrx)
    				  cost += computeChannelInterference(plan, planCC,*victimTrx,*interfererTrx);
		  		} //for
		  } //for

  return cost;
}; //signalingCost

/******************************************************************************/
/**
 * C/I cost
 */
 double AFP::c2iCost(vector<int> * plan, vector<pair<double,double> >* planCC) {
 	double cost = 0.0;

  //firstly, add the cost provoked by the interference within each sector
  //on caclule l interference provoque par les trx sans le meme secteur
  for (map<int,vector<int> >::iterator it = sectors2trxs.begin();
       it != sectors2trxs.end();
       it++) {
    cost += signalingCost(plan,planCC,(*it).first,(*it).first);
  }

  //compute sector based cost
  //for each victim
  for (map<int, map<int, pair<double,double> > >::iterator victim = interferenceMatrix.begin();
       victim != interferenceMatrix.end();
       victim++ ) {

    //traverse all the interferer sectors
    for (map<int, pair<double,double> >::iterator interferer = (*victim).second.begin();
       interferer != (*victim).second.end();
       interferer++) {
       //cost for all the interferences between TRXs
       cost += signalingCost(plan, planCC, (*victim).first, (*interferer).first);
    } //for
  } //for

  return cost;

 }; //c2iCost


/******************************************************************************/
/**
 * Interference based fitness
 */
double AFP::interferenceBasedFitness(Individual * solution) {
  /*for (int i = 0; i < solution->plan->size(); i++)//LF comment:initiallement le cout est 0
   {
        //solution->planCC->at(i).first = 0.0;
        //solution->planCC->at(i).second = 0.0;
        solution->planCC->at(i) = {0.0 , 0.0}
   }*/

  double fitness = c2iCost(solution->plan,solution->planCC);

  //for (int i = 0; i < solution->planCC->size(); i++)
  //  cout << solution->planCC->at(i) << endl;

  return fitness;
}; //interferenceBasedFitness
//------------------
//valotion partielle de fitness



/******************************************************************************/
/**
 * Load a frequency plan stored in a file
 * Format: <nº trx> <frequency assigned>
 */
void AFP::loadFrequencyPlanFromFile(char * filename, Individual* & Sol) {
  //open file
	ifstream file(filename,ios_base::in);
  Individual * solution = new Individual();
	solution->plan = new vector<int>(trxs.size());
  solution->planCC = new vector<pair<double,double> >(trxs.size());


	if (!file.good()) {
    cout << "Error loading file " << filename << endl;
    exit(-1);
  } //if

  //get the first line
  char line[256];
  file.getline(line,256);

  int trx, frequency;

  //cout << "EEEEEEEEEEEEEEEEEEE" << endl;

  //file >> frequency;
  int i = 0;
  while (!file.eof()) {
    file >> frequency;
    solution->plan->push_back(frequency);
    //cout << frequency << " ";
    i++;
    //file >> trx;
  } //while
Sol = solution;
 /* if (checkFrequencyPlan(solution->plan))
    cout << "Ta bien" << endl;
  else
    cout << "ta mal!!!" << endl;

  /*for (int i = 0; i < 20; i++)
    cout << solution->plan->at(i) << " ";
  cout << endl;//*/
 /* cout << interferenceBasedFitness(solution) << endl;
  //cout << componentCostGreedy(solution,3,1.0) << endl;

  exit(-1); //
  */

} //loadFrequencyPlanFromFile

/******************************************************************************/
/**
 * Return true if all the frequencies are valid
 */
bool AFP::checkFrequencyPlan(vector<int> * plan) {
  bool ok;

  for (int trx = 0; trx < trxs.size(); trx++) {
    ok = false;
    for (vector<int>::iterator freq = trxs[trx].validFrequencies->begin();
      freq != trxs[trx].validFrequencies->end();
      freq ++) {
        if (plan->at(trx) == *freq)
          ok = true;
      } //for
      if (!ok) {
        cout << "trx = " << trx << " is assigned with a non-valid frequency" << endl;
        return false;
      } //if
    } //for
    return true;
};

//################################ My functions : LAIDOUI FATMA #############"
// calculer le cout de choix d une fréquence
double AFP::computeChannelInterference(int victimFrequency ,int interfererFrequency, int victimTrx, int interfererTrx) {
	double cost = 0.0;

    if (victimTrx != interfererTrx)
    {
        if (trxs[victimTrx].sectorID == trxs[interfererTrx].sectorID)
        {//LAIdoui Fatma comment: les trx sont dans dans le meme secteur
            if (victimFrequency == interfererFrequency)//L.F:meme trx et meme Fréquence
            if ((trxs[victimTrx].type == "BCCH") || (trxs[interfererTrx].type == "BCCH"))
            cost += projectParameters.sameSectorCoChBcch;
            else
            cost += projectParameters.sameSectorCoChTch;
            else if (abs(victimFrequency - interfererFrequency) == 1)//LF:fréquence adjacente
	    if ((trxs[victimTrx].type == "BCCH") || (trxs[interfererTrx].type == "BCCH"))
	      cost = cost + projectParameters.sameSectorAdjChBcch;
	    else
	      cost = cost + projectParameters.sameSectorAdjChTch; //
        } //if
        else // on n'est pas dans le meme secteur
        {
	   //trxs[victimTrx].sectorID != trxs[interfererTrx].sectorID
	   //only co-channel and adj-channel are considered
            if (victimFrequency == interfererFrequency)
            {
                cost = cost + interferenceMatrix[trxs[victimTrx].sectorID][trxs[interfererTrx].sectorID].first;
            } //if
            else
            {
                if (abs(victimFrequency - interfererFrequency) == 1)
                {
                    cost = cost + interferenceMatrix[trxs[victimTrx].sectorID][trxs[interfererTrx].sectorID].second;
                //cout << "cost+++" << cost << endl;
                }
            }
        } //if

    }
   /* else
     {
         cout << " ERREUR Même TRX ID " <<endl;
     }*/

//cout<<"hiii"<<endl;
  //if (cost > 0)
	//cout << "(" << victimTrx << "," << interfererTrx << ") - (" << victimFrequency << "," << interfererFrequency << ") -> " << cost << endl;


  //update the component cost

  //cout << victimFrequency << " - " << interfererFrequency << " -> " << cost << endl;
  return cost;

}; //computeChann

double AFP::ComputeSolutionInterference(Individual* solution)
{
      double totalcost = 0.0;
      int i,j,victimTrx,interfererTrx;int victimFrequency,interfererFrequency;
    //  solution->planCC = new vector<double>(solution->plan->size());
   // cout << "totalcost "<< totalcost <<endl;
    for(i=0;i<solution->plan->size();i++)//pour chaque trx dans la solution
    {//cout<<"hiii"<<endl;
      //solution->planCC->at(i)=0.0;
       //   if (i == 1) cout << "totalcost "<< totalcost <<endl;
      victimTrx= i;
      victimFrequency = solution->plan->at(i);

      if (victimFrequency != -1)//est valable pour les solutuion partielle
      {
         for(interfererTrx=0;interfererTrx<solution->plan->size();interfererTrx++)
        {//cout<<"hiii"<<endl;
            if (victimTrx != interfererTrx)
            {
                interfererFrequency = solution->plan->at(interfererTrx);
            //  solution->planCC->at(i) = solution->planCC->at(i)+computeChannelInterference(victimFrequency ,interfererFrequency,victimTrx,interfererTrx);
                if(interfererFrequency != -1)
                {
                    totalcost = totalcost + computeChannelInterference(victimFrequency ,interfererFrequency,victimTrx,interfererTrx);
                }
            }
        }//for(interfererTrx=0;interfererTrx<solution->plan->size();interfererTrx++)

        }//(victimFrequency != -1)

    }

    /*for(i=0;i<solution->plan->size();i++)//pour chaque trx dans la solution
    {
     totalcost = totalcost+solution->planCC->at(i);
    }*/
    return totalcost;
}
//------------
double AFP::ComputeSolutionSeparationCost(Individual* solution)//calculer le cout de séparation totale de la solution
{
    int i,j, victimtrx,interfertrx;
    double Cs,Csect,Csite;//Cs: cout de separation total; csect:cout de separation secteur, Csite:cout de separation cosite
    Cs = 0.0;
    Csect = 0.0;
    Csite = 0.0;
    for(i=0 ; i < solution->plan->size();i++)//pour tous les trx dans la solution
    {
      if (solution->plan->at(i)!= -1)
      {
        victimtrx = i;
        for(j=i+1;j<solution->plan->size();j++)//on peut faire ça car la separation est symétrique
        {
            interfertrx = j;
            if (solution->plan->at(j) != -1) // la fréquence n'est pas encore affectée
            {
                //les 2 trx sont dans le meme secteur
                if(trxs[victimtrx].sectorID == trxs[interfertrx].sectorID)
                {
                    //on teste si la contraite de separation co-secteur est respecté!!
                    if (abs (solution->plan->at(victimtrx)-solution->plan->at(interfertrx))< 3)//contrainte co secteur violée
                    {
                        Csect = Csect +1.0;
                    }
                }// secteur different
                else
                {
                    if(trxs[victimtrx].siteID  == trxs[interfertrx].siteID)
                    {
                        //on teste si la contrainte de separation co-site est respectée!!
                        if (abs (solution->plan->at(victimtrx)-solution-> plan->at(interfertrx))< 2)//contrainte co secteur violée
                        {
                            Csite= Csite +1.0;
                        }
                    }//
                }
            }//   if (solution->plan ! = -1) // la fréquence n'est pas encore affectée
        }// for(j=i+1;j<solution->plan->size();j++)
      }//// for(i=0;i<solution->plan->at(i) = -1 ;
    }// for(i=0;i<solution->plan->size();i++)//pour tous les trx dans la solution

    Cs =  Cs + Csect + Csite;
    return Cs;
}
=======
#include <stdlib.h>
#include <cfloat>
#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>
#include <map>
#include <time.h>

#include "../Individual/Individual.h"
#include "AFP.h"
//################################ Mes bibliothèques  LAIDOUI Fatma ###########"
//####################################################
#include <algorithm>//copy

//###################################"
/*AFP::AFP() {
    int i;
    for(i=0;trxs.size();i++)
    {
       trxs[i].AvailableFrequencies=trxs[i].validFrequencies;
    }
}*/

AFP::AFP(string instance) {

	//loading files
  if (instance == "Denver") {
    loadOptions("./data/Denver.opt.txt");
    loadTrxs("./data/Denver.trx.txt");
    loadSectors("./data/Denver.sector.txt");
    loadIM("./data/Denver.IM.txt");
    loadSites("./data/Denver.site.txt");
    loadNeighbors("./data/Denver.1-hop.neighbors.txt");
    loadSecondNeighbors("./data/Denver.2-hop.neighbors.txt");
  } //else
  else if (instance == "LA") {
    loadOptions("./data/LA.opt.txt");
    loadTrxs("./data/LA.trx.txt");
    loadSectors("./data/LA.sector.txt");
    loadIM("./data/LA.IM.txt");
    loadSites("./data/LA.site.txt");
    loadNeighbors("./data/LA.1-hop.neighbors.txt");
    loadSecondNeighbors("./data/LA.2-hop.neighbors.txt");
  } //else
  else if (instance == "Seattle") {
    loadOptions("./data/Seattle.opt.txt");
    loadOptions("./data/Seattle.opt.txt");
    loadTrxs("./data/Seattle.trx.txt");
    loadSectors("./data/Seattle.sector.txt");
    loadIM("./data/Seattle.IM.txt");
    loadSites("./data/Seattle.site.txt");
    loadNeighbors("./data/Seattle.1-hop.neighbors.txt");
    loadSecondNeighbors("./data/Seattle.2-hop.neighbors.txt");
    /*loadOptions("./data/data_fatima/Seattle_Fatima.opt.txt");
    loadTrxs("./data/data_fatima/Seattle_Fatima.trx.txt");
    loadSectors("./data/data_fatima/Seattle_Fatima.sector.txt");
    loadIM("./data/data_fatima/Seattle_Fatima.IM.txt");
    loadSites("./data/data_fatima/Seattle_Fatima.site.txt");
    loadNeighbors("./data/data_fatima/Seattle_Fatima.1-hop.neighbors.txt");
    loadSecondNeighbors("./data/data_fatima/Seattle_Fatima.2-hop.neighbors.txt");*/
  } //else
  else {
    cout << "Invalid instance " << instance << endl;
    exit(-1);
  } //else
//++++++++++++++++++++++++++
     //int i,j,indextrx ;
//calculer pour chque trx non traité , la taille des trx avec qui il interfere et l enregistrer dans LTrxNTreatedsSizeinterfere
           // vector <double> LTrxNTreatedsMaxValueinterferCost;

           /* ListTrxMaxValueinterferCost.reserve(trxs.size());
             double value;
            double cost = 0.0 ;
            //cherche la valeur max d in terference pour chaque trx
            for(i = 0 ; i < trxs.size() ; i++)
            {
                for (j = 0 ; interferenceMatrix[i].size(); j++)//parcourir tous les trx avec
                    //lesquel le trx  LTrxNTreateds[i].trxID] interfere
                {
                    if (i!=j)
                    {

                        if ( interferenceMatrix[i][j].first > interferenceMatrix[i][j].second )
                            value  = interferenceMatrix[i][j].first;
                        else
                            value  = interferenceMatrix[i][j].second;


                        if (cost < value)
                        {
                            cost = value;
                        }
                    }
                }
               ListTrxMaxValueinterferCost.push_back(cost);

            }
*/
        //°°°°°°°°°°°°°°°°°°°°°Fatma Laidoui : ajouté le 27-3-2019°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°
    int i,j ; double costtrx;
    //MaxCostITrx.reserve(trxs.size());
        // construire le tableau pair cost qui contient pour chqua trx le plus grand cout q il a
    for (i = 0 ; i < trxs.size() ; i++)
    {
            // paircost[i].first = i ;// nous utilisant une paire, pour enregistrer l information du trx paircost.first après le tri
            costtrx = 0.0 ;
        int sectorI = trxs[i].sectorID ;
       for (j = 0 ; j < trxs.size() ; j++)
       {
          int sectorJ = trxs[j].sectorID;
          if (costtrx < interferenceMatrix[sectorI][sectorJ].first)
          {
             costtrx  = interferenceMatrix[sectorI][sectorJ].first;
          }
          else
          {
              if (costtrx < interferenceMatrix[sectorI][sectorJ].second)
                costtrx  = interferenceMatrix[sectorI][sectorJ].second;
          }
       }
       // paircost[i].second = costtrx;
       MaxCostITrx.push_back({i,costtrx});
   }

    //°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°


  //++++++++++++++++++++++++++++++++

	maxExecutionTime = 120;



       //########################
} //

AFP::~AFP() {
} //



/******************************************************************************/
/**
 * Generate a random frequency planning
 */
void AFP::randomPlanning(Individual * solution) {
  int index;

  for (int i = 0; i < trxs.size(); i++) {
    index = rand() % trxs[i].validFrequencies->size();
    solution->plan->at(i) = trxs[i].validFrequencies->at(index);
  } //for
}; //random planning




/******************************************************************************/
/**
 * Load TRXs information stored in filename
 */
void AFP::loadTrxs(char * filename) {

  ifstream file(filename,ios_base::in);

  if (!file.good()) {
    cout << "Error loading file " << filename << endl;
    exit(-1);
  } //if

  char line[256];
  file.getline(line,256);

  //create TRX
  TRX * t = new TRX();
  //read trx ID
  file >> t->trxID;

  while (!file.eof()) {

    //read type
    file >> t->type;
    //read sector ID
    file >> t->sectorID;
    //read site ID
    file >> t->siteID;
    //read valid frequencies
    int numberOfFrequencies;
    int frequency;
    file >> numberOfFrequencies;
    vector<int> * freq = new vector<int>();
    vector<int> * freqs = new vector<int>();//---Ajout LAIDOUI FATMA ------------
    for (int i = 0; i < numberOfFrequencies; i++) {
      file >> frequency;
      freq->push_back(frequency);
      freqs->push_back(frequency);//---Ajout LAIDOUI FATMA ------------
    } //for
    t->validFrequencies = freq;
    t->AvailableFrequencies = freqs;//---Ajout LAIDOUI FATMA ------------

    //store TRX
    //trxs[t->trxID] = *t;
    trxs.push_back(*t);
    t = new TRX();
    file >> t->trxID;
  } //while
  file.close();

  //cout << trxs.size() << " TRXs successfully readed" << endl;
}; //loadTrxs

/******************************************************************************/
/**
 * Numerical method for computing function Q
 */
float erfcc(float x) {
  float t, z, ans;

  z = (float)fabs(x);//Returns the absolute value of x:
  t = 1.0F / (1.0F + 0.5F * z);
  ans = (float)(t * exp(-z * z - 1.26551223F + t *
		(1.00002368F + t *
		 (0.37409196F + t *
		  (0.09678418F + t *
		   (-0.18628806F + t *
		    (0.27886807F + t *
		     (-1.13520398F + t *
		      (1.48851587F + t *
		       (-0.82215223F + t * 0.17087277F)
		      )
		     )
		    )
		   )
		  )
		 )
		)
		));

  return  x >= 0.0F ? ans : 2.0F - ans;

}; //erfcc

/******************************************************************************/
/**
 * Load interference matrix from file
 */
void AFP::loadIM(char * filename) {
  ifstream file(filename,ios_base::in);

  if (!file.good()) {
    cout << "Error loading file " << filename << endl;
    exit(-1);
  } //if

  char line[256];
  int  victim;
  int  interferer;
  double mean, std, cochannel, adjchannel;
  file.getline(line,256);

  //interferenceMatrix = new map<int, map<int, pair<double,double> > >();

  //read victim
  file >> victim;
  int previousVictim = victim;
  map<int, pair<double,double> > * node = new map<int, pair<double,double> >();

  while (!file.eof()) {
    //read interferer
    file >> interferer;
    interfereTo[interferer].push_back(victim);

    //read mean and std
    file >> mean;
    file >> std;

    //cout << victim << "," << interferer << "->" << mean << "," << std << endl;
    cochannel = 100.0*(1.0
  		                -
  		                0.5*erfcc(
  		                          (projectParameters.signallingThreshold - mean)
  		                          /
  		                          (std*sqrt(2.0f))
  		                         )
  		                );
  	adjchannel = 100.0*(1.0
  		                -
  		                0.5*erfcc(
  		                          (projectParameters.signallingThreshold - mean - projectParameters.adjChannelRejection)
  		                          /
  		                          (std*sqrt(2.0f))
  		                         )
  		                );

    //(*node)[interferer] = pair<double,double>(mean,std);
    (*node)[interferer] = pair<double,double>(cochannel,adjchannel);

    //read another victim
    previousVictim = victim;
    file >> victim;

    if (victim != previousVictim) {
      interferenceMatrix[previousVictim] = *node;
      node = new map<int, pair<double,double> >();
    } //if
    else if (file.eof())
      interferenceMatrix[victim] = *node;
  } //while
  file.close();

  /*for (map<int, vector<int> >::iterator iter = interfereTo.begin();
       iter != interfereTo.end();
       iter ++) {
        cout << (*iter).first << ": ";
        for (vector<int>::iterator iter2 = (*iter).second.begin();
          iter2 != (*iter).second.end();
          iter2++)
            cout << (*iter2) << " ";
        cout << endl;
        char bas;
        cin >> bas;
      } //for */


}; //loadIM

/******************************************************************************/
/**
 * Load sector information from file
 */
void AFP::loadSectors(char * filename) {
  ifstream file(filename,ios_base::in);

  if (!file.good()) {
    cout << "Error loading file " << filename << endl;
    exit(-1);
  } //if

  //get the first line
  char line[256];
  file.getline(line,256);

  int sector;
  int constraint;
  file >> sector;

  while (!file.eof()) {
  	//get the constraint value for the sector
  	file >> constraint;
    sectorConstraintSep[sector] = constraint;

    //read the list of trxs
    int numberOfTrxs, trx;
    file >> numberOfTrxs;
    for (int i = 0; i < numberOfTrxs; i++) {
    	file >> trx;
    	sectors2trxs[sector].push_back(trx);
    } //for

    //read new sector
    file >> sector;
  } //while
  file.close();

}; //loadSectors

/******************************************************************************/
/**
 * Load project options from file
 */
 void AFP::loadOptions(char * filename) {
  ifstream file(filename,ios_base::in);

  if (!file.good()) {
    cout << "Error loading file " << filename << endl;
    exit(-1);
  } //if

  //get the first line
  char line[256];
  file.getline(line,256);

  string key;

  //read the first key
  file >> key;
  while (!file.eof()) {
  	if (key == "Sector_Co_Ch_TCH")
  		file >> projectParameters.sameSectorCoChTch;
  	else if (key == "Sector_Co_Ch_BCCH")
  		file >> projectParameters.sameSectorCoChBcch;
  	else if (key == "Sector_Adj_Ch_TCH")
  		file >> projectParameters.sameSectorAdjChTch;
  	else if (key == "Sector_Adj_Ch_BCCH")
  		file >> projectParameters.sameSectorAdjChBcch;
  	else if (key == "Sector_Ch_Sep")
  		file >> projectParameters.sameSectorChSep;
  	else if (key == "Site_Co_Ch_BCCH_BCCH")
  		file >> projectParameters.sameSiteCoBcchBcch;
  	else if (key == "Site_Co_Ch_BCCH_TCH")
  		file >> projectParameters.sameSiteCoBcchTch;
  	else if (key == "Site_Co_Ch_TCH_TCH")
  		file >> projectParameters.sameSiteCoTchTch;
  	else if (key == "Site_Adj_Ch_BCCH_BCCH")
  		file >> projectParameters.sameSiteAdjBcchBcch;
  	else if (key == "Site_Adj_Ch_BCCH_TCH")
  		file >> projectParameters.sameSiteAdjBcchTch;
  	else if (key == "Site_Adj_Ch_TCH_TCH")
  		file >> projectParameters.sameSiteAdjTchTch;
  	else if (key == "Site_Ch_Sep")
  		file >> projectParameters.sameSiteChSep;
  	else if (key == "Nbr_Co_Ch_BCCH_BCCH")
  		file >> projectParameters.nbrCoBcchBcch;
  	else if (key == "Nbr_Co_Ch_BCCH_TCH")
  		file >> projectParameters.nbrCoBcchTch;
  	else if (key == "Nbr_Co_Ch_TCH_TCH")
  		file >> projectParameters.nbrCoTchTch;
  	else if (key == "Nbr_Adj_Ch_BCCH_BCCH")
  		file >> projectParameters.nbrAdjBcchBcch;
  	else if (key == "Nbr_Adj_Ch_BCCH_TCH")
  		file >> projectParameters.nbrAdjBcchTch;
  	else if (key == "Nbr_Adj_Ch_TCH_TCH")
  		file >> projectParameters.nbrAdjTchTch;
  	else if (key == "Nbr2_Co_Ch_BCCH_BCCH")
  		file >> projectParameters.nbr2CoBcchBcch;
  	else if (key == "Nbr2_Co_Ch_BCCH_TCH")
  		file >> projectParameters.nbr2CoBcchTch;
  	else if (key == "Nbr2_Co_Ch_TCH_TCH")
  		file >> projectParameters.nbr2CoTchTch;
  	else if (key == "Adjacent_Channel_Interference_Rejection")
  		file >> projectParameters.adjChannelRejection;
  	else if (key == "Signalling_Threshold")
  		file >> projectParameters.signallingThreshold;
  	else {
  		cout << "Wrong key " << key << endl;
  		exit(-1);
  	} //else
  	file >> key;
  } //while

  file.close();


}; //loadOptions

/******************************************************************************/
/**
 * Load sites from file
 */
void AFP::loadSites(char * filename) {
	//open file
	ifstream file(filename,ios_base::in);

	if (!file.good()) {
    cout << "Error loading file " << filename << endl;
    exit(-1);
  } //if

  //get the first line
  char line[256];
  file.getline(line,256);

  int site, numberOfSectors, sector;

  file >> site;
  while (!file.eof()) {
  	//read separation constraint
  	file >> siteConstraintSep[site] ;

  	//read number of sectors
  	file >> numberOfSectors;

  	//read sectors
  	for (int i = 0; i < numberOfSectors; i++) {
  		file >> sector;
  		site2sectors[site].push_back(sector);
  	} //for

  	file >> site;
  } //while
  file.close();


}; //loadSites

/******************************************************************************/
/**
 * Load neighbors from file
 */
void AFP::loadNeighbors(char * filename) {
	//open file
	ifstream file(filename,ios_base::in);

	if (!file.good()) {
    cout << "Error loading file " << filename << endl;
    exit(-1);
  } //if

  //get the first line
  char line[256];
  file.getline(line,256);

  int sector, numberOfNeighbors, neighbor;

  file >> sector;
  while (!file.eof()) {
  	//read neighbors
  	file >> numberOfNeighbors;
  	for (int i = 0; i < numberOfNeighbors; i++) {
  		file >> neighbor;
  		neighbors[sector].push_back(neighbor);
  	} //for

  	//read new sector
  	file >> sector;
  } //while
  file.close();

}; //loadNeighbors

/******************************************************************************/
/**
 * Load neighbors from file
 */
void AFP::loadSecondNeighbors(char * filename) {
	//open file
	ifstream file(filename,ios_base::in);

	if (!file.good()) {
    cout << "Error loading file " << filename << endl;
    exit(-1);
  } //if

  //get the first line
  char line[256];
  file.getline(line,256);

  int sector, numberOfNeighbors, neighbor;

  file >> sector;
  while (!file.eof()) {
  	//read neighbors
  	file >> numberOfNeighbors;
  	for (int i = 0; i < numberOfNeighbors; i++) {
  		file >> neighbor;
  		secondNeighbors[sector].push_back(neighbor);
  	} //for

  	//read new sector
  	file >> sector;
  } //while
  file.close();


}; //loadSecondNeighbors



/******************************************************************************/
/**
 * Compute interferences between a victim TRX and an interferer TRX
 */
double AFP::computeChannelInterference(vector<int> * plan, vector<pair<double,double> > * planningCC, int victimTrx, int interfererTrx)
{
	double cost = 0.0;
	int victimFrequency     = plan->at(victimTrx);
	int interfererFrequency = plan->at(interfererTrx);




	if (trxs[victimTrx].sectorID == trxs[interfererTrx].sectorID) {//LAIdoui Fatma comment: les trx sont dans dans le meme secteur
	  if (victimFrequency == interfererFrequency)//L.F:meme trx et meme Fréquence
	    if ((trxs[victimTrx].type == "BCCH") || (trxs[interfererTrx].type == "BCCH"))
	      cost += projectParameters.sameSectorCoChBcch;
	    else
	      cost += projectParameters.sameSectorCoChTch;
	  else if (abs(victimFrequency - interfererFrequency) == 1)//LF:fréquence adjacente
	    if ((trxs[victimTrx].type == "BCCH") || (trxs[interfererTrx].type == "BCCH"))
	      cost += projectParameters.sameSectorAdjChBcch;
	    else
	      cost += projectParameters.sameSectorAdjChTch; //*/
	 } //if
	 else {
	   //trxs[victimTrx].sectorID != trxs[interfererTrx].sectorID
	   //only co-channel and adj-channel are considered
  	 if (victimFrequency == interfererFrequency) {
  		 cost += interferenceMatrix[trxs[victimTrx].sectorID][trxs[interfererTrx].sectorID].first;
  	 } //if
  	 else if (abs(victimFrequency - interfererFrequency) == 1) {
  	 	cost += interferenceMatrix[trxs[victimTrx].sectorID][trxs[interfererTrx].sectorID].second;
  	 } //if
	 } //else


  //if (cost > 0)
	//cout << "(" << victimTrx << "," << interfererTrx << ") - (" << victimFrequency << "," << interfererFrequency << ") -> " << cost << endl;
	/*char bas;
  cin >> bas; //*/

  //update the component cost
  //planningCC->at(victimTrx) += cost;
  //cout << victimFrequency << " - " << interfererFrequency << " -> " << cost << endl;
  return cost;


}; //computeChanneInterference

/******************************************************************************/
/**
 * Compute interferences between a victim sector and an interferer sector
 */
double AFP::signalingCost(vector<int> * plan, vector<pair<double,double> > * planCC, int victimSector, int interfererSector) {
	double cost = 0.0;

	for(vector<int>::iterator victimTrx = sectors2trxs[victimSector].begin();
		  victimTrx != sectors2trxs[victimSector].end();
		  victimTrx ++) {
		  	for (vector<int>::iterator interfererTrx = sectors2trxs[interfererSector].begin();
		  		interfererTrx != sectors2trxs[interfererSector].end();
		  		interfererTrx ++) {
		  			if (*victimTrx != *interfererTrx)
    				  cost += computeChannelInterference(plan, planCC,*victimTrx,*interfererTrx);
		  		} //for
		  } //for

  return cost;
}; //signalingCost

/******************************************************************************/
/**
 * C/I cost
 */
 double AFP::c2iCost(vector<int> * plan, vector<pair<double,double> >* planCC) {
 	double cost = 0.0;

  //firstly, add the cost provoked by the interference within each sector
  //on caclule l interference provoque par les trx sans le meme secteur
  for (map<int,vector<int> >::iterator it = sectors2trxs.begin();
       it != sectors2trxs.end();
       it++) {
    cost += signalingCost(plan,planCC,(*it).first,(*it).first);
  }

  //compute sector based cost
  //for each victim
  for (map<int, map<int, pair<double,double> > >::iterator victim = interferenceMatrix.begin();
       victim != interferenceMatrix.end();
       victim++ ) {

    //traverse all the interferer sectors
    for (map<int, pair<double,double> >::iterator interferer = (*victim).second.begin();
       interferer != (*victim).second.end();
       interferer++) {
       //cost for all the interferences between TRXs
       cost += signalingCost(plan, planCC, (*victim).first, (*interferer).first);
    } //for
  } //for

  return cost;

 }; //c2iCost


/******************************************************************************/
/**
 * Interference based fitness
 */
double AFP::interferenceBasedFitness(Individual * solution) {
  /*for (int i = 0; i < solution->plan->size(); i++)//LF comment:initiallement le cout est 0
   {
        //solution->planCC->at(i).first = 0.0;
        //solution->planCC->at(i).second = 0.0;
        solution->planCC->at(i) = {0.0 , 0.0}
   }*/

  double fitness = c2iCost(solution->plan,solution->planCC);

  //for (int i = 0; i < solution->planCC->size(); i++)
  //  cout << solution->planCC->at(i) << endl;

  return fitness;
}; //interferenceBasedFitness
//------------------
//valotion partielle de fitness



/******************************************************************************/
/**
 * Load a frequency plan stored in a file
 * Format: <nº trx> <frequency assigned>
 */
void AFP::loadFrequencyPlanFromFile(char * filename, Individual* & Sol) {
  //open file
	ifstream file(filename,ios_base::in);
  Individual * solution = new Individual();
	solution->plan = new vector<int>(trxs.size());
  solution->planCC = new vector<pair<double,double> >(trxs.size());


	if (!file.good()) {
    cout << "Error loading file " << filename << endl;
    exit(-1);
  } //if

  //get the first line
  char line[256];
  file.getline(line,256);

  int trx, frequency;

  //cout << "EEEEEEEEEEEEEEEEEEE" << endl;

  //file >> frequency;
  int i = 0;
  while (!file.eof()) {
    file >> frequency;
    solution->plan->push_back(frequency);
    //cout << frequency << " ";
    i++;
    //file >> trx;
  } //while
Sol = solution;
 /* if (checkFrequencyPlan(solution->plan))
    cout << "Ta bien" << endl;
  else
    cout << "ta mal!!!" << endl;

  /*for (int i = 0; i < 20; i++)
    cout << solution->plan->at(i) << " ";
  cout << endl;//*/
 /* cout << interferenceBasedFitness(solution) << endl;
  //cout << componentCostGreedy(solution,3,1.0) << endl;

  exit(-1); //
  */

} //loadFrequencyPlanFromFile

/******************************************************************************/
/**
 * Return true if all the frequencies are valid
 */
bool AFP::checkFrequencyPlan(vector<int> * plan) {
  bool ok;

  for (int trx = 0; trx < trxs.size(); trx++) {
    ok = false;
    for (vector<int>::iterator freq = trxs[trx].validFrequencies->begin();
      freq != trxs[trx].validFrequencies->end();
      freq ++) {
        if (plan->at(trx) == *freq)
          ok = true;
      } //for
      if (!ok) {
        cout << "trx = " << trx << " is assigned with a non-valid frequency" << endl;
        return false;
      } //if
    } //for
    return true;
};

//################################ My functions : LAIDOUI FATMA #############"
// calculer le cout de choix d une fréquence
double AFP::computeChannelInterference(int victimFrequency ,int interfererFrequency, int victimTrx, int interfererTrx) {
	double cost = 0.0;

    if (victimTrx != interfererTrx)
    {
        if (trxs[victimTrx].sectorID == trxs[interfererTrx].sectorID)
        {//LAIdoui Fatma comment: les trx sont dans dans le meme secteur
            if (victimFrequency == interfererFrequency)//L.F:meme trx et meme Fréquence
            if ((trxs[victimTrx].type == "BCCH") || (trxs[interfererTrx].type == "BCCH"))
            cost += projectParameters.sameSectorCoChBcch;
            else
            cost += projectParameters.sameSectorCoChTch;
            else if (abs(victimFrequency - interfererFrequency) == 1)//LF:fréquence adjacente
	    if ((trxs[victimTrx].type == "BCCH") || (trxs[interfererTrx].type == "BCCH"))
	      cost = cost + projectParameters.sameSectorAdjChBcch;
	    else
	      cost = cost + projectParameters.sameSectorAdjChTch; //
        } //if
        else // on n'est pas dans le meme secteur
        {
	   //trxs[victimTrx].sectorID != trxs[interfererTrx].sectorID
	   //only co-channel and adj-channel are considered
            if (victimFrequency == interfererFrequency)
            {
                cost = cost + interferenceMatrix[trxs[victimTrx].sectorID][trxs[interfererTrx].sectorID].first;
            } //if
            else
            {
                if (abs(victimFrequency - interfererFrequency) == 1)
                {
                    cost = cost + interferenceMatrix[trxs[victimTrx].sectorID][trxs[interfererTrx].sectorID].second;
                //cout << "cost+++" << cost << endl;
                }
            }
        } //if

    }
   /* else
     {
         cout << " ERREUR Même TRX ID " <<endl;
     }*/

//cout<<"hiii"<<endl;
  //if (cost > 0)
	//cout << "(" << victimTrx << "," << interfererTrx << ") - (" << victimFrequency << "," << interfererFrequency << ") -> " << cost << endl;


  //update the component cost

  //cout << victimFrequency << " - " << interfererFrequency << " -> " << cost << endl;
  return cost;

}; //computeChann

double AFP::ComputeSolutionInterference(Individual* solution)
{
      double totalcost = 0.0;
      int i,j,victimTrx,interfererTrx;int victimFrequency,interfererFrequency;
    //  solution->planCC = new vector<double>(solution->plan->size());
   // cout << "totalcost "<< totalcost <<endl;
    for(i=0;i<solution->plan->size();i++)//pour chaque trx dans la solution
    {//cout<<"hiii"<<endl;
      //solution->planCC->at(i)=0.0;
       //   if (i == 1) cout << "totalcost "<< totalcost <<endl;
      victimTrx= i;
      victimFrequency = solution->plan->at(i);

      if (victimFrequency != -1)//est valable pour les solutuion partielle
      {
         for(interfererTrx=0;interfererTrx<solution->plan->size();interfererTrx++)
        {//cout<<"hiii"<<endl;
            if (victimTrx != interfererTrx)
            {
                interfererFrequency = solution->plan->at(interfererTrx);
            //  solution->planCC->at(i) = solution->planCC->at(i)+computeChannelInterference(victimFrequency ,interfererFrequency,victimTrx,interfererTrx);
                if(interfererFrequency != -1)
                {
                    totalcost = totalcost + computeChannelInterference(victimFrequency ,interfererFrequency,victimTrx,interfererTrx);
                }
            }
        }//for(interfererTrx=0;interfererTrx<solution->plan->size();interfererTrx++)

        }//(victimFrequency != -1)

    }

    /*for(i=0;i<solution->plan->size();i++)//pour chaque trx dans la solution
    {
     totalcost = totalcost+solution->planCC->at(i);
    }*/
    return totalcost;
}
//------------
double AFP::ComputeSolutionSeparationCost(Individual* solution)//calculer le cout de séparation totale de la solution
{
    int i,j, victimtrx,interfertrx;
    double Cs,Csect,Csite;//Cs: cout de separation total; csect:cout de separation secteur, Csite:cout de separation cosite
    Cs = 0.0;
    Csect = 0.0;
    Csite = 0.0;
    for(i=0 ; i < solution->plan->size();i++)//pour tous les trx dans la solution
    {
      if (solution->plan->at(i)!= -1)
      {
        victimtrx = i;
        for(j=i+1;j<solution->plan->size();j++)//on peut faire ça car la separation est symétrique
        {
            interfertrx = j;
            if (solution->plan->at(j) != -1) // la fréquence n'est pas encore affectée
            {
                //les 2 trx sont dans le meme secteur
                if(trxs[victimtrx].sectorID == trxs[interfertrx].sectorID)
                {
                    //on teste si la contraite de separation co-secteur est respecté!!
                    if (abs (solution->plan->at(victimtrx)-solution->plan->at(interfertrx))< 3)//contrainte co secteur violée
                    {
                        Csect = Csect +1.0;
                    }
                }// secteur different
                else
                {
                    if(trxs[victimtrx].siteID  == trxs[interfertrx].siteID)
                    {
                        //on teste si la contrainte de separation co-site est respectée!!
                        if (abs (solution->plan->at(victimtrx)-solution-> plan->at(interfertrx))< 2)//contrainte co secteur violée
                        {
                            Csite= Csite +1.0;
                        }
                    }//
                }
            }//   if (solution->plan ! = -1) // la fréquence n'est pas encore affectée
        }// for(j=i+1;j<solution->plan->size();j++)
      }//// for(i=0;i<solution->plan->at(i) = -1 ;
    }// for(i=0;i<solution->plan->size();i++)//pour tous les trx dans la solution

    Cs =  Cs + Csect + Csite;
    return Cs;
}
>>>>>>> 0514ea9fae0f841576757defb02235a9189b0fad
