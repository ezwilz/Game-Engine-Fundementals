

#include <stdio.h>
#include <iostream>
#include "MyGame.h"
using namespace std;

int main(int argc, char* args[]) {
	
	try
	{
		MyGame game;
		game.runMainLoop();
	}
	catch (exception e)
	{
		cout << "error:" << endl;
	}

	
	return 0;

	

}


