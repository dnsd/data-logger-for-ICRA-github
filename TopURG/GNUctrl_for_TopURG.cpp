#include "GNUctrl_for_TopURG.h"

#include <cstdio>
#include <iostream>

#define GP_PATH "/usr/bin/gnuplot"

using namespace std;

FILE *gnu_p;	// Gnuplotへのパイプ用ポインタ

void GNU_Init(void)
{
	// Gnuplotのオープン
	gnu_p = popen(GP_PATH, "w");
	fprintf(gnu_p, "set xrange [-1:1]\n");
	fprintf(gnu_p, "set xlabel \"x[m]\"\n");
	fprintf(gnu_p, "set yrange [-1:1]\n");
	fprintf(gnu_p, "set ylabel \"y[m]\"\n");
	fprintf(gnu_p, "set grid\n");
	fprintf(gnu_p, "set size square\n");
	fprintf(gnu_p, "unset key\n");
}

void GNU_Plot(TopURG *urg_data)
{
	int i;

	fprintf(gnu_p, "plot \"-\"\n");	// バッファ出力開始

	// TopURGの二次元座標データをバッファに出力
	for (i = 0; i < 1080; i++)
	{
		fprintf(gnu_p, "%lf %lf\n", urg_data->x[i], urg_data->y[i]);
	}
	
	fprintf(gnu_p, "e\n");	// バッファ出力終了
	fflush(gnu_p);			// Gnuplotに描画させる
}

void GNU_Close(void)
{	
	fclose(gnu_p);
}
