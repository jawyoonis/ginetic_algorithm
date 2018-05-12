#include <iostream>
#include <fstream> // to have access to the file open and close functions
#include "population.h"
#include "genome.h"
#include <string>
#include <sstream>
using namespace std;

int go(Pixel* target, int nGenerations, int nIndividuals, int nGenes, double mRate,int nCrossover,
  int nRows, int nCols){/*This function serves to call all the other functions in the class population and
    runs the entire code.  this function  essentially has a look that for nGenerations times,
     creates a new generation from the previous one. */
  Population p_generations;
  ofstream outFile;
  int fittest=0;
  double fitness=0;

  p_generations.generate_population(nIndividuals, nGenes);// These functions were named in population class
  p_generations.set_mutation(mRate);
  p_generations.set_nCrossover(nCrossover);
  p_generations.set_target(target, 10);
  p_generations.find_roulette_top_individuals();
  p_generations.find_top_two_individuals();

  for(int i=0; i<nGenerations; i++){
    p_generations.generate_new_population();
  }

  Genome* perfect;
  fitness=p_generations.calculate_overall_fitness_p();
  cout<<"overall fitness: "<<fitness<<endl;
  fittest= p_generations.top_index_one;
  cout<<"fittest: "<<fittest<<endl;
  perfect= &p_generations.individuals[fittest];
  outFile.open("output.txt");
  outFile<<"fitness: "<< fitness<<"\n";
  outFile<<"nRows: "<<nRows<<"\n";
  outFile<<"nCols: "<<nCols<<"\n";

  for(int j=0; j<nRows; j++){// This how input the rows and columns after extracted from input file

    for(int i=0; i<nCols; i++){
      outFile<<" ( "<<perfect[j].genes[i].red<<" "<<perfect[j].genes[i].green<<" "<<perfect[j].genes[i].blue<<" ) "<<",";

    }
    outFile<<"\n";
  }


outFile.close();

}


int main(){

  int nGenes=0;
  int nGenerations=0;
  int nIndividuals=0;
  double mRate=0.0;
  int nCrossover=0;
  int nRows=0;
  int nCols=0;
  ifstream inFile;
  string garbage;
  string filename;
  cout<<"Ensert the file: ";
  cin>>filename;
inFile.open(filename.c_str());

if(!inFile){
  exit(1);

cout<<"the file is failed to open! ";
}
else{inFile>> garbage >> nGenerations >>garbage >>nIndividuals >>garbage >>
 nGenes >> garbage >> mRate >>garbage>> nCrossover>> garbage>> nRows>> garbage >> nCols;

 }
  inFile.close();

  cout<<"nGenerations: "<<nGenerations<<endl;
  cout<<"nIndividuals: "<<nIndividuals<<endl;
  cout<<"nGenes: "<<nGenes<<endl;
  cout<<"mRate: "<<mRate<<endl;
  cout<<"nCrossover: "<<nCrossover<<endl;
  cout<<"nRows: "<<nRows<<endl;
  cout<<"nCols: "<<nCols<<endl;

  Pixel* target;/* this a new array that chekcs the target titness image in the class to be used
		   to calculate the relative fitnesses of all the individual genomes  */

  target= new Pixel[10];
  for ( int i=0; i < 10; i++){
    target[i].red=120;
    target[i].green= 123;
    target[i].blue= 100;
  }
  go(target, nGenerations, nIndividuals, nGenes, mRate, nCrossover, nRows, nCols);
  string content;

delete[] target;
  return 0;
}
