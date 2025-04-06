#!/bin/bash -login
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=1

#SBATCH --ntasks-per-node=1
#SBATCH --job-name=cent11

#SBATCH --error=TRX88jobC1000.err 
#SBATCH --output=TRX88jobC1000.out


#SBATCH --mail-type=ALL                  # Notification par mail des évènements concernant le job : début d’exécution, fin,…
#SBATCH --mail-user=daliladalilaa9@gmail.com
# And finally run the job?





	./exe-1000-CTRX88
	