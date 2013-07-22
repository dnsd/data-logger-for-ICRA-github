OPT =  LRFctrl.cpp GNUctrl.cpp -lscip2awd -lm -lpthread -lssm

all:urg2ssm urg2gnu

urg2ssm:urg2ssm.cpp Structures.hpp
	g++ -o urg2ssm urg2ssm.cpp $(OPT)

urg2gnu:urg2gnu.cpp Structures.hpp
	g++ -o urg2gnu urg2gnu.cpp $(OPT)

TopURG2ssm:TopURG2ssm.cpp Structures_for_TopURG.hpp
	g++ -o TopURG2ssm TopURG2ssm.cpp TopURGctrl.cpp -lscip2awd -lm -lpthread -lssm

TopURG2gnu:TopURG2gnu.cpp Structures_for_TopURG.hpp
	g++ -o TopURG2gnu TopURG2gnu.cpp TopURGctrl.cpp GNUctrl_for_TopURG.cpp -lscip2awd -lm -lpthread -lssm

#$(EXE) : $(SRC) LRFctrl.o GNUctrl.o
#	g++ -o $(EXE) $(SRC) LRFctrl.cpp GNUctrl.cpp -lscip2awd -lm -lpthread -lssm

clean :
	rm *.o

