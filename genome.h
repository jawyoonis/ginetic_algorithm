#ifndef GENOME_H
#define GENOME_H
#include <iostream>
struct Pixel{ // this the struct that diclares and set the pixels to zero.
public:
  int red;
  int blue;
  int green;

};

class Genome // this is the declaration of the class
{
    public:
    ~Genome();
    Genome();
    Pixel *genes; // this sets up the genes that is pointing the strucs of pixels
    int nGenes;
    double mRate;
    Pixel *targetP;


//construct to set genes and ngenes to zero
    void allocate(int nGenes); // this diclares the functions that allocates the memory of the pixels


  void deallocate();
  void randomize();


  void set_red(int index, int value);
  void set_green(int index, int value);
  void set_blue(int index, int value);
  void print();
  void set_mRate(double val);
  void mutate_gene(int index);
  void mutate();
  void set_pixel(int index, Pixel newPixel);
  int get_nGenes(int num_genes);


  int get_red(int index);
  int get_green(int index);
  int get_blue(int index);
  double get_mRate();
  double calculate_gene_fitness(int index, Pixel targerPixel);
  double calculate_overall_fitness(Pixel* target, int nPixels);
  Pixel get_pixel(int index);



};

#endif // GENOME_H
