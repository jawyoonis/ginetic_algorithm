#ifndef PAPULATION_H
#define PAPULATION_H
#include "genome.h"




class Population
{
    public:

    int nIndividuals;
    int top_index_one;
    int top_index_two;
    int genome_size;
    int child1;
    int child2;
    int roulette_winer_one;
    int roulette_winer_two;
    int crossovers;
    int nGenes;
    int generations;
    int nPixels;


    Genome* individuals;
    Pixel* target;



        Population();

        ~Population();

      void generate_population(int nGenomes, int nGenes);
      void generate_new_individuals(int child1, int child2, Genome* _best, Genome* _second);

        void find_top_two_individuals();

        void find_roulette_top_individuals();
        // void get_crossover(int nCrossover);

        void set_nCrossover(int nCrossover);

        void set_mutation(double nRate);

        void set_target(Pixel* target, int imageSize);

       void generate_new_population();

        double calculate_overall_fitness_p();

        void print_population();
        void go(int nGenerations);
        int outnput_files (int nRows, int nCols);








};

#endif // PAPULATION_H
