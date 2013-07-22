#include <iostream>
#include <cmath>
#include "LRFctrl.h"
#include <ssm.hpp>
#include <scip2awd.h>


int main(int aArgc, char **appArgv)
{

	initSSM();	//ssmのイニシャライズ（必ず忘れずに）
	LRF urg_data;	// LRFの座標データ

	LRF_Init(appArgv[1]);	// LRFの初期化

	SSM_sid URG_sid;	//idの作成
	
	URG_sid = createSSM_time("URG", 0, sizeof(LRF), 1, 0.1);	//領域の確保（”名前”, 番号, データサイズ, 保持する時間, 周期）

	while(1)
	{
		LRF_GetData(&urg_data);	// LRFのデータを取得
		writeSSM(URG_sid, (char*)&urg_data, gettimeSSM());	//SSMにLRFデータを投げる
		
		usleep(1000);
	}
	
    return 0;
}
