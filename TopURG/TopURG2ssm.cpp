#include <iostream>
#include <cmath>
#include "TopURGctrl.h"
#include <ssm.hpp>
#include <scip2awd.h>


int main(int aArgc, char **appArgv)
{

	initSSM();	//ssmのイニシャライズ（必ず忘れずに）
	TopURG urg_data;	// TopURGの座標データ

	TopURG_Init(appArgv[1]);	// TopURGの初期化

	SSM_sid URG_sid;	//idの作成
	
	URG_sid = createSSM_time("URG", 0, sizeof(TopURG), 1, 0.1);	//領域の確保（”名前”, 番号, データサイズ, 保持する時間, 周期）

	while(1)
	{
		TopURG_GetData(&urg_data);	// TopURGのデータを取得
		writeSSM(URG_sid, (char*)&urg_data, gettimeSSM());	//SSMにTopURGデータを投げる
		
		usleep(1000);
	}
	
    return 0;
}
