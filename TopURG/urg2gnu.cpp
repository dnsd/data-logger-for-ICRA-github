#include <iostream>
#include <cmath>
#include "GNUctrl.h"
#include <ssm.hpp>


int main(int aArgc, char **appArgv)
{
	initSSM();	//SSMイニシャライズ

	LRF urg_data;	// LRFの座標データ

	GNU_Init();	// Gnuplotの初期化
	
	SSM_sid URG_sid; //SSM管理id
	double time; //SSM書き込み時間

	URG_sid = openSSM("URG",0,0);	//SSMを開く（”名前”，番号，時間）

	while(1)
	{
		if(readSSM(URG_sid, (char*)&urg_data, &time,-1)){	//読みにいく（if文はエラー処理）
			GNU_Plot(&urg_data);	// Gnuplotに描画
			usleep(200000);
		}
	}
	
	GNU_Close();	// Gnuplotのクローズ
    return 0;
}
