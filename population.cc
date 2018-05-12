
#include <iostream>
#include <cstdlib>
#include "population.h"
#include <string>
#include <stdlib.h>
#include <fstream>
#include <time.h>

using namespace std;

Population::Population()
{

    nIndividuals=0;
    top_index_one=0;
    top_index_two=0;
    genome_size=0;
    nGenes=0;
    roulette_winer_one=-1;
    roulette_winer_two=-1;
    crossovers=1;
    child1=0;
    child2=0;
    generations=0;
    nPixels=0;



}

Population::~Population()
{
  if(individuals!=NULL){
    delete[] individuals;}
  if(target!=NULL){
    delete[] target;
  }
  nIndividuals=0;


  }

void Population::generate_population(int nGenomes, int numGenes){/* this functions serves to generate population
  It creates array of individuals and then it allocates them into a memory.
  And then it prints out the randomized individuals
  */
    if(nGenomes % 2!=0){return;}
    individuals= new Genome[nGenomes];
    nIndividuals= nGenomes;
    nGenes = numGenes;
  for(int i=0; i<nGenomes; i++){
    //srand(time(NULL));
    individuals[i].allocate(nGenes);
    individuals[i].randomize();


  }
genome_size=nGenomes;

  }
  void Population::set_target(Pixel* targetp, int imageSize){/* it sets the target fitness image in the class to be used
    to calculate the relative fitnesses of all the individual genomes */
    // nPixels=10;
    target= new Pixel[imageSize];
    nPixels= imageSize;
    for(int i=0; i<imageSize; i++){
      target[i]= targetp[i];

    }



  }


void Population::find_top_two_individuals(){/*it finds the top fittest individuals in the population.
  It determines the two overall best individuals in the current population based on their relative fitness

  */

  top_index_one=0;// these are the defaults of the indexes of top two individuals
  top_index_two=0;

  for(int i=1; i<nIndividuals; i++){
    if(individuals[i].calculate_overall_fitness(target, nPixels)>
       individuals[top_index_one].calculate_overall_fitness(target, nPixels)){
      top_index_one=i;
      cout<<"nPixels: "<<nPixels<<endl;

    }

  }
  cout<<" top_index_one: "<<top_index_one<<endl;
  for( int j= 1; j<nIndividuals; j++){
    if(j!=top_index_one){
      if(individuals[j].calculate_overall_fitness(target, nPixels)>
	 individuals[top_index_two].calculate_overall_fitness(target, nPixels)){
	top_index_two=j; // t


      }
    }
  }
  cout<<"top_index_two: "<<top_index_one<<endl;
}

  void Population::set_mutation(double nRate){// this functions sets up the muation rate of each individual in the Population
    for(int i=0; i<nIndividuals; i++){
      individuals[i].set_mRate(nRate);

    }

  }
 double Population::calculate_overall_fitness_p(){ /* It calculates the averate fitness of the population.*/
   double average_fitness=0;
   for(int i=0; i<nIndividuals; i++){
     average_fitness+=individuals[i].calculate_overall_fitness(target,nPixels); // this is where the average is being calculated
   }

  return average_fitness/nIndividuals;
 }
   void Population::set_nCrossover(int nCrossover){// this funcion sets up the crossovers pionts
     crossovers= nCrossover;
}
  void Population::find_roulette_top_individuals(){/*This functions finds out the
    top two individuals in the roulette wheel regarding thier fitness and
    it randomly picks up a number that is greater than zero and less than one
    then it looks which region that random lands and it picks that individualthat is corresponding to that
    specefic random number
    */

    double *relative_fit= new double [nIndividuals];
    double sum=0;
    double overal_sum=0;
    for(int i=0; i<nIndividuals; i++){
      sum+=individuals[i].calculate_overall_fitness(target, nPixels);

      // cout<<"the fitness of each individual is :"<<sum<<endl;
    }
    double sum_probs=0;
     for(int i=0; i<nIndividuals; i++){
       relative_fit[i]=individuals[i].calculate_overall_fitness(target, nPixels)/sum;
       // cout<<"relative fit :"<< relative_fit[i]<<endl;
}

cout<<""<<endl;


  double number=(double) rand()/RAND_MAX;

for(int i=1; i<nIndividuals; i++){ // this foor loop goes through the individuals and find the first winner of roulette wheel
  relative_fit[i]+= relative_fit[i-1];
  if(relative_fit[i-1]< number and number < relative_fit[i]) {
    //cout<<"relative check one :"<< relative_fit[i]<<endl;
  roulette_winer_one=i;
  cout<<"Roulette winer one: "<<roulette_winer_one<<endl;// this first roulette winer
  break;


  }
}
cout<<""<<endl;
  for(int j =1; j<nIndividuals; j++){
    relative_fit[j]+= relative_fit[j-1];

    double number1=(double) rand()/RAND_MAX;
    if( relative_fit[j-1] > number1 and number1 < relative_fit[j]) {
      roulette_winer_two= j;
      cout<<"Roulette winer two: "<< roulette_winer_two<<endl;
      break;


    }
    }
}


void Population::print_population(){ // this functions just prints out the number of individuals in the population
  for(int i=0; i<nIndividuals; i++){
    individuals[i].print();
    cout<<""<<endl;
  }
}



void Population::generate_new_population(){// This method serves to generate new population by using the two roulette winers
  int choice = 0; // this functions creates the crossver points of two parents in order to generate new population
    int * cross_points = new int[crossovers];
    for (int j=0;j<crossovers;j++){
      cross_points[j] = rand()%genome_size;
      }
      child1=0;
      child2= 0;
      bool swap= false;
      for (int i=0; i<nIndividuals; i+=2){
      while( child1 == roulette_winer_one|| child1 ==roulette_winer_two || child1 == child2 ) child1++;
      while( child2 == roulette_winer_one || child2 == roulette_winer_two || child2 == child1 ) child2++;
      //These two while loops skip the individuals that are already being used
      for(int i=0; i<genome_size; i++){
        if(!swap){
          individuals[child1].set_pixel(i, individuals[roulette_winer_one].get_pixel(i));
          individuals[child2].set_pixel(i, individuals[roulette_winer_two].get_pixel(i));
        }
        else {
          individuals[child2].set_pixel(i, individuals[roulette_winer_two].get_pixel(i));
          individuals[child1].set_pixel(i, individuals[roulette_winer_one].get_pixel(i));
        }
        if(i == crossovers) swap = !swap;

    for (int j=0;j<crossovers;j++){
          if (i==cross_points[j]){
              choice += 1;
          }
      }
      individuals[child1].mutate();// this mutates the two children that I created from individuals
      individuals[child2].mutate();

    }

  }
  delete[] cross_points; //deallocates the crossver pionts after they have been used

}
