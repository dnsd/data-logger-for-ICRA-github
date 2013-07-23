CC      = gcc -o
INC_DIR = -I/usr/local/include
LIB_DIR = -L/usr/local/lib
OPT    = -lpthread -lssm -lm -lscip2awd


all:urg2ssmL urg2ssm3D urg2ssmR urg2ssmB ssm2plot

urg2ssm3D:urg2ssm3D.c LRF.h
	$(CC) $@ $^ $(LIB_DIR) $(LIB_DIR) $(OPT)

urg2ssmR:urg2ssmR.c LRF.h
	$(CC) $@ $^ $(LIB_DIR) $(LIB_DIR) $(OPT)

urg2ssmL:urg2ssmL.c LRF.h
	$(CC) $@ $^ $(LIB_DIR) $(LIB_DIR) $(OPT)

urg2ssmB:urg2ssmB.c LRF.h
	$(CC) $@ $^ $(LIB_DIR) $(LIB_DIR) $(OPT)

urg2ssm:urg2ssm.c LRF.h
	$(CC) $@ $^ $(LIB_DIR) $(LIB_DIR) $(OPT)

ssm2plot:ssm2plot.c LRF.h
	$(CC) $@ $^ $(LIB_DIR) $(LIB_DIR) $(OPT)

TopURG2gnu:TopURG2gnu.cpp
	g++ -o TopURG2gnu TopURG2gnu.cpp -lscip2awd -lm -lpthread -lssm

clean:
	rm ssm2plot urg2ssm3D urg2ssmR urg2ssmL urg2ssmB
