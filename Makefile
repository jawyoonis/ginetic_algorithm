
progam:genome.o main.o population.o
			g++ -o program genome.o main.o population.o

genome.o:genome.h genome.cc
			  g++ -c -g genome.cc

population.o:population.h population.cc
						g++ -c -g population.cc

main.o:main.cc
			g++ -c -g main.cc


clean:
				rm -f *.o o*~ program
