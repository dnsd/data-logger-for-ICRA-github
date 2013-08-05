// 5Hz用

#include <iostream>
#include <stdio.h>	/* printf()、fprintf()に必要 */
#include <sys/socket.h>	/* socket()、connect()、send()、recv()に必要 */
#include <arpa/inet.h>	/* sockaddr_in、inet_addr()に必要 */
#include <stdlib.h>	/* atoi()に必要 */
#include <string.h>	/* memset()に必要 */
#include <unistd.h>	/* close()に必要 */
#include <math.h>
#include <fstream> //ofstreamに使用

using namespace std;

#define BUFFER_SIZE 60000

#define STEP_NUM 2880 //ステップ数（片道）
#define STEP_NUM_PER_LINE 144//ステップ数（1ラインあたり）

ofstream ofs;

int main(int argc, char *argv[])
{
	int sock;			/* ソケットディスクリプタ */
	struct sockaddr_in sensorAddr;/* センサーのアドレス */
	unsigned short sensorPort;	/* センサーのポート番号 */
	const char *toSendText1 = "#TD2LISS\n";/* センサーに送信する文字列 */
	// char echoBuffer[RCVBUFSIZE];	/* エコー文字列用のバッファ */
	unsigned int SendTextLen;	/* エコーする文字列のサイズ */
	int bytesRcvd, totalBytesRcvd;	/* 一回のrecv()で読み取られるバイト数と全バイト数 */

	char angle_data_buf[40][1746]; //angleデータのバッファ

	/* TCPによる信頼性の高いストリームソケットを作成 */
	if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
		printf("socket() failed");

	/* サーバのアドレス構造体を作成 */
	sensorAddr.sin_family = AF_INET;			/* インターネットアドレスファミリ */
	sensorAddr.sin_addr.s_addr = inet_addr("192.168.0.10");	/* センサーのIPアドレス */
	sensorAddr.sin_port = htons(10940);		/* センサーのポート番号 */

	/* センサーへの接続を確立 */
	if (connect(sock, (struct sockaddr *) &sensorAddr, sizeof(sensorAddr)) < 0)
		printf("connect() failed");

	//-----angleデータを取得-----//
	//-サーバにメッセージを送信-//
	memset(&sensorAddr, 0, sizeof(sensorAddr));		/* 構造体にゼロを埋める */
	SendTextLen = strlen(toSendText1)+1;	/* 入力データの長さを調べる */
	if (send(sock, toSendText1, SendTextLen, 0) != SendTextLen)
	{
		printf("send() sent a different number of bytes than expected");
	}
	printf("sending...\n");
	usleep(1000000); //1秒待機

	//-サーバからデータを受信-//
	int LissStringLen = (12 * STEP_NUM_PER_LINE) + 18; //angleデータの長さ
	for (int i = 0; i < 40; i++)
	{
		for (int j = 0; j < LissStringLen; j++)
		{
			char temp_c;
			recv(sock, &temp_c, 1, 0);
			if (temp_c == '\n')
			{
				angle_data_buf[i][j] = '\0';
				break;
			}
			angle_data_buf[i][j] = temp_c;
		}
	}

	for (int i = 0; i < 40; ++i)
	{
		cout << angle_data_buf[i][12] << endl;
	}

	ofs.open("debug.txt");
	for (int i = 0; i < 40; i++)
	{
		for (int j = 0; j < LissStringLen; j++)
		{
			ofs << angle_data_buf[i][j];
		}
		ofs << endl;
	}
	ofs.close();

	close(sock);
	exit(0);





	//-test-//
	// echoStringLen = strlen(echoString);	/* 入力データの長さを調べる */

	// /* 文字列をサーバに送信 */
	// if (send(sock, echoString, echoStringLen, 0) != echoStringLen)
	// 	DieWithError("send() sent a different number of bytes than expected");

	// /* 同じ文字列をサーバから受信 */
	// totalBytesRcvd = 0;
	// printf("Received: ");	/* エコーされた文字列を表示するための準備 */
	// while (totalBytesRcvd < echoStringLen)
	// {
	// 	/* バッファサイズに達するまで（ヌル文字用の1バイトを除く）
	// 		サーバからのデータを受信する */
	// 	if ((bytesRcvd = recv(sock, echoBuffer, RCVBUFSIZE - 1, 0)) <= 0)
	// 		DieWithError("recv() failed or connection closed prematurely");
	// 	totalBytesRcvd += bytesRcvd;	/* 総バイト数の集計 */
	// 	echoBuffer[bytesRcvd] = '\0' ;	/* 文字列の終了 */
	// 	printf(echoBuffer);	/* エコーバッファの表示 */
	// }

	// printf("\n");	/* 最後の改行を出力 */

	// close(sock);
	// exit(0);
}

double angle_convert(long angle)
{
	double alpha, beta;
    beta = (double)angle;
    alpha = ((2*beta)/(pow(2, 24)-1)) - 1;
    return alpha;
}