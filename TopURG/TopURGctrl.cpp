#include "TopURGctrl.h"

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <scip2awd.h>

S2Port *port;	/* Device Port */
S2Sdd_t buf;	/* Data recive dual buffer */

// TopURGのオープンと初期化
// 現状ではSimple URGのみに対応
void TopURG_Init(char *dev_name)
{
	int ret;	/* Returned value */

	/* Open the port */
	port = Scip2_Open( dev_name, B115200 );
	if( port == 0 )
	{
		fprintf( stderr, "ERROR: Failed to open device.\n" );
		exit( 1 );
	}
	printf( "Port opened\n" );
	
	/* Initialize buffer before getting scanned data */
	S2Sdd_Init( &buf );
	printf( "Buffer initialized\n" );
	
	/* Demand sending me scanned data */
	/* Data will be recived in another thread */
	/* Power laser ON */
	ret = Scip2CMD_BM( port );
	if( ret == 0 )
	{
		fprintf( stderr, "ERROR: BM failed (%d).\n", ret );
		exit( 1 );
	}
	Scip2CMD_StartMS( port, 44, 725, 1, 0, 0, &buf, SCIP2_ENC_2BYTE );
}

// TopURGのデータ取得
void TopURG_GetData(TopURG *urg_data)
{
	S2Scan_t *data;	/* Pointer to data buffer */
	int i;			/* Loop valiant */
	int ret;		/* Returned value */
	
	while(1)
	{
		/* Start using scanned data */
		ret = S2Sdd_Begin( &buf, &data );
		
		/* Returned value is 0 when buffer is having been used now */
		if( ret > 0 )
		{
			/* ---- analyze data ---- */
			for( i = 0; i < data->size; i++ )
			{
				urg_data->dist[i] = (double)data->data[i] / 1000.0;
				urg_data->x[i] = urg_data->dist[i] * cos((-120.0 + 0.3519 * (double)i) * (M_PI / 180.0));
				urg_data->y[i] = urg_data->dist[i] * sin((-120.0 + 0.3519 * (double)i) * (M_PI / 180.0));
			}

			/* Don't forget S2Sdd_End to unlock buffer */
			S2Sdd_End( &buf );
			
			break;
		}
		else if( ret == -1 )
		{
			fprintf( stderr, "ERROR: Fatal error occurred.\n" );
			break;
		}
		else
		{
			usleep( 100 );
		}
	}
}

