#include <iostream>
#include <cstdlib>
#include "genome.h"
#include <stdlib.h>
#include <time.h>
using namespace std;

Genome::Genome() // this the contruct of the class which sets the genes to NUll and then sets the number of genes to zero
{
   genes=NULL;
   nGenes=0;
   mRate= 0;
}
Genome:: ~Genome(){// this distruct dellocates the space of the elements in the array
deallocate();
}
int Genome::get_nGenes(int num_genes){/*this functions just returns the number of genes in
the array so you can use them to call culate the fitness genes*/
num_genes= nGenes;
return num_genes;
}

void Genome::allocate(int numberGenes){ // it sets up an input for the number of pixels and allocates a space for them.
genes= new Pixel[numberGenes];
nGenes= numberGenes;
}

void Genome::deallocate(){ // it frees up the space that is allocated for the genes and sets up nGenes to zero.
if(genes=NULL){return;} // this condition checks if the genes are still empty
delete[] genes; // and then deletes the array of pixels
genes=NULL; // sets up the genes to NULL and sets up thier number to zero
nGenes=0;
mRate=0;

}

void Genome::randomize(){ // this function serves to prints out random number of index of red pixels in the genes
for( int i=0; i< nGenes; i++){
genes[i].blue=rand()%256;// random of index of blued pixels in the genes
genes[i].green=rand()%256; //random of index of green pixesl in the gen
genes[i].red=rand()%256;//  random of index of red pixesl in the gen
}

}


void Genome::set_blue(int index, int value){ // This serves to set up number of red pixles of genes
if(index < 0 && nGenes < index){
return;}

genes[index].blue= value;// set value of the index of blue pixels in genes

}
void Genome::set_green(int index, int value){// this function serves to set up the value of green pixels of genes
if(index <0 && index > nGenes){
return;}
genes[index].green=value;// set value of the index of green pixels in genes


}
void Genome::set_red(int index, int value){//this function serves to set up the value of red pixels of genes
if(index < 0 && index > nGenes){
return;}
genes[index].red=value;// set value of the index of red pixels in genes

}

int Genome::get_blue(int index){ // this serves to check if the index of blue pixels are greater than zero and less than the Ngenes
if(index > 0 && index < nGenes){
return genes[index].blue;// returns the value of index of genes of blue pixels
}
return -1;
}
int  Genome::get_green(int index){ // this function serves to check the if index of green pixels are greater zero or greater than ngenes
if(index > 0 && index < nGenes){
return genes[index].green;}// this returns the value of index of genes of green pixels
return -1;
}
int  Genome::get_red(int index){//this function serves to check the if index of red pixels are greater zero or greater than ngenes
if(index > 0 && index < nGenes){
return genes[index].red;} // this returen the value of index of genes of red pixels
return -1;}

void Genome::set_mRate(double val){// this fucntion serves set mRate a value between 0 and 1
if(val>0 && val<1){// this forloop checks if the value is between 1 and 0 and then sets it to mRate
mRate= val;}
}

double Genome::get_mRate(){ // this function gets the value of mutation rate and returns it
return mRate;}


void Genome::mutate_gene(int index){/* it takes index of particular pixel for every color and if the randomly generated number is
 less than the mRate, it assigns to it a number between 0 and 255, otherwise, it generates three random numbers between 0 and 1 */
double randnum1= rand()%100;// this generates random numbers between 0 and 100 for every color
double randnum2= rand()%100;
double randnum3= rand()%100;
randnum1=randnum1/100;
randnum2=randnum2/100;// this divides the rondom generated numbers by 100 because they should match the mRate
randnum3=randnum3/100;

if(randnum1< mRate){/* this for loop makes sure that the random number matches the rate of the mutation rate */
genes[index].red= rand()%255;// this assignes the pixels of red color to random numbers between 0 and 255
}
if(randnum2<mRate){/* this for loop makes sure that the random number matches the rate of the mutation rate */
genes[index].green= rand()%255;}// this assignes the pixels of green color to random numbers between 0 and 255
if(randnum3 < mRate){/* this for loop makes sure that the random number matches the rate of the mutation rate */
genes[index].blue= rand()%255;}// this assignes the pixels of blue color to random numbers between 0 and 255

}
void Genome::mutate(){/* this functions goes through all nGenes of genes and then calls every element inside the mutate_gene function */

for(int j=0; j<nGenes; j++){// goes through the entire number of genes in the array
mutate_gene(j);}

}

double Genome::calculate_gene_fitness(int index, Pixel targetPixel){/* it goes to the Pixel at position index and calculates the
average percent difference of the RGB values between targetPixel and genes[index] */

double redDiff = abs(genes[index].red-targetPixel.red);// this finds the difference between index of genes of red pixels
double greenDiff = abs(genes[index].green-targetPixel.green);//this finds the difference between index of genes of green pixels
double blueDiff = abs(genes[index].blue-targetPixel.blue);//this finds the difference between index of genes of blue pixels
double average= ((redDiff+greenDiff+blueDiff)/3.0);/*this takes the sum of these differences and divides them three and then
returns the everage difference of these differences divide by 255.
*/
return average/255.0;


}



double Genome::calculate_overall_fitness(Pixel* target, int nPixels){ /* this function takes an array of Pixels and
									 the size of the image (nPixels) and compares the target with its own genes and then returns the sum of all differences*/
  double sum=0;

  // if(nGenes!=nPixels){
  //   return -1;
  // }
  for(int i=0; i<nPixels; i++){// goes through all number of genes
    sum+=calculate_gene_fitness(i, target[i]);// adds the average difference of all the fitness of all genes
    return sum/nPixels;
  }
}





void Genome::set_pixel( int index, Pixel newPixel ){/* this function takes a newPixel and set the Pixel at position index to be equal to it. */

if(index < 0 || index >=nGenes){/*This makes sure that the index is greater than 0 and less than the number of genes
otherwise it returns error
*/
throw std::invalid_argument( "received invalid value" );
}

    if((newPixel.red>=0 || newPixel.red<=255) && (newPixel.green>=0 || newPixel.green<=255)/* This checks the
    the values of the newpixels should be between 0 and 255 and should be inclusive too */
    && (newPixel.blue>=0 || newPixel.blue<=25) ){
    genes[index].red= newPixel.red;/* then it sets the index of each color in the genes to a new pixels*/
    genes[index].green= newPixel.green;
    genes[index].blue= newPixel.blue;}


}



 Pixel Genome::get_pixel( int index) {
  if(index < 0 || index >=nGenes){/*This makes sure that the index is greater than 0 and less than the number of genes
  otherwise it returns error
  */
  throw std::invalid_argument( "received invalid value" );
  }

    return genes[index];
}



void Genome::print(){ // this function serves to print out the pixesl of genes and it allocates their index in the arrays
for( int i=0; i<nGenes; i++){
cout<<genes[i].red<<" "; // prints out the the index of red pixels in the genes
cout<<genes[i].green<< " "; // prints out indexes of green pixels in the genes
cout<<genes[i].blue<<endl; // prints out indexes blue pixels in the genes

}

}
