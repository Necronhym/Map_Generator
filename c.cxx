/*
	A map generation algorith
*/
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <string.h>
#include <unistd.h>
#include <fstream>
void Output( int iSolid,int iLocationX,int iLocationY )
	{
		bool bBlockSolid;
		float fLocationX, fLocationY;
		const char* chTileskin;
		const char* file = "Map";
		std::ofstream outputfile;
		if( iSolid > 0 )
			{
		bBlockSolid = true;
		outputfile.open( file, std::ios_base::app );
		outputfile <<"assets/graphic/envi/1.tga";
		outputfile <<"\n";
		outputfile << (float)iLocationX*2/10.0;
		outputfile <<"\n";
		outputfile << (float)iLocationY*2/10.0;
		outputfile <<"\n";
		outputfile << 0.1;
		outputfile <<"\n";
		outputfile << 1;
		outputfile <<"\n";
			}
		outputfile.close();	
	}
void LevelGenerate( int iPlayers )
	{
		bool bDone1 = false;
		bool bDone2 = false;
		bool bDone3 = false;
		int iMapWidth, iMapHeight;
		int aiSpawnPoints[4];
		int iGenerationPass;
		//Feeds a "random" time seed to the random generator:
		srand( time( NULL ) );
		//Randomly generates map height and width:
		iMapWidth = rand() % ( iPlayers*16 - 8*iPlayers) + ( 4*iPlayers );
		iMapHeight = ( iPlayers*16 ) - iMapWidth;
		int iMapDimentions[4] = { iMapWidth, iMapHeight, iMapWidth, iMapHeight };
		int aiMap[iMapWidth][iMapHeight];
		int iMovement;
		//Picks location of spawn points for players:
		for( int iSpawn = 0; iSpawn <= (iPlayers-1); iSpawn++ )
			{
				//Introduces entroy:	
				srand( time( NULL )+iSpawn );
				//Generates spawn points:
				aiSpawnPoints[iSpawn] = rand() % ( iMapDimentions[iSpawn] - 2*iPlayers ) + (iPlayers +1 );
			}
		memset(aiMap, 0, sizeof(aiMap));
		//Assigns spawn locations to array:
		aiMap[aiSpawnPoints[0]][0] = 3;
		aiMap[iMapWidth-1][aiSpawnPoints[1]] = 3;
		aiMap[aiSpawnPoints[2]][iMapHeight-1] = 3;
		aiMap[0][aiSpawnPoints[3]] = 3;
		//Generate tiles:
		static int iTemporaryLocationX = aiSpawnPoints[0],iTemporaryLocationY = 0;
		//1st Pass:
		while( !bDone1 )
			{
				iGenerationPass++;
				srand( time( NULL )+ iGenerationPass );
				//Movement:
				iMovement = rand() % 4 + 1;
				//ifStatements:
				iGenerationPass++;
				if( iMovement == 1 && iTemporaryLocationY > 0)
					{
						iTemporaryLocationY = iTemporaryLocationY - 1;
					}	
				else if( iMovement == 2 && iTemporaryLocationY < iMapHeight-1 )
					{
						iTemporaryLocationY = iTemporaryLocationY + 1;
					}
				else if( iMovement == 3 && iTemporaryLocationX > 0)
					{
						iTemporaryLocationX = iTemporaryLocationX - 1;
					}
				else if ( iMovement == 4 && iTemporaryLocationX < iMapWidth-1 )
					{
						iTemporaryLocationX = iTemporaryLocationX + 1;
					}
				if( aiMap[iTemporaryLocationX][iTemporaryLocationY] != 3 )
					{
						aiMap[iTemporaryLocationX][iTemporaryLocationY] = 1;
					}
				srand( time( NULL )+ iGenerationPass );
				if( iTemporaryLocationX == aiSpawnPoints[2] && iTemporaryLocationY == iMapHeight-1 )
					{
						bDone1 = true;
					}
			}
		iTemporaryLocationX = (iMapWidth-1);
		iTemporaryLocationY = aiSpawnPoints[1];
		//2nd Pass :
		while( !bDone2 )
			{
				iGenerationPass++;
				srand( time( NULL )+ iGenerationPass );
				iMovement = rand() % 4 + 1;
				if( iMovement == 1 && iTemporaryLocationY > 0)
					{
						iTemporaryLocationY = iTemporaryLocationY - 1;
					}	
				else if( iMovement == 2 && iTemporaryLocationY < iMapHeight-1 )
					{
						iTemporaryLocationY = iTemporaryLocationY + 1;
					}
				else if( iMovement == 3 && iTemporaryLocationX > 0)
					{
						iTemporaryLocationX = iTemporaryLocationX - 1;
					}
				else if ( iMovement == 4 && iTemporaryLocationX < iMapWidth-1 )
					{
						iTemporaryLocationX = iTemporaryLocationX + 1;
					}
				if( aiMap[iTemporaryLocationX][iTemporaryLocationY] != 3 && aiMap[iTemporaryLocationX][iTemporaryLocationY] != 1 )
					{
						aiMap[iTemporaryLocationX][iTemporaryLocationY] = 2;
					}
				if( aiMap[iTemporaryLocationX][iTemporaryLocationY] == 1 )
					{
						bDone2 = true;
					}
			}
		//3rd Pass:
		iTemporaryLocationX = 0;
		iTemporaryLocationY = aiSpawnPoints[3];
		while( !bDone3 )
			{
				iGenerationPass++;
				srand( time( NULL )+ iGenerationPass );
				iMovement = rand() % 4 + 1;
				if( iMovement == 1 && iTemporaryLocationY > 0)
					{
						iTemporaryLocationY = iTemporaryLocationY - 1;
					}	
				else if( iMovement == 2 && iTemporaryLocationY < iMapHeight-1 )
					{
						iTemporaryLocationY = iTemporaryLocationY + 1;
					}
				else if( iMovement == 3 && iTemporaryLocationX > 0)
					{
						iTemporaryLocationX = iTemporaryLocationX - 1;
					}
				else if ( iMovement == 4 && iTemporaryLocationX < iMapWidth-1 )
					{
						iTemporaryLocationX = iTemporaryLocationX + 1;
					}
				if( aiMap[iTemporaryLocationX][iTemporaryLocationY] != 3 && aiMap[iTemporaryLocationX][iTemporaryLocationY] != 2 && aiMap[iTemporaryLocationX][iTemporaryLocationY] != 1 )
					{
						aiMap[iTemporaryLocationX][iTemporaryLocationY] = 2;
					}
				if( aiMap[iTemporaryLocationX][iTemporaryLocationY] == 1 )
					{
						bDone3 = true;
					}
			}
		for( int iT = 0; iT < iMapHeight; iT++ )
			{
				for( int iB = 0; iB < iMapWidth; iB++ )
					{
						std::cout<<aiMap[iB][iT];
						Output( aiMap[iB][iT], iB, iT );
					}
				std::cout<<std::endl;
			}
	}
int main()
	{
		LevelGenerate( 4 );
		return 0;
	}
