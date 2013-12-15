/*
	Author: Hampus Liljekvist
	Version: 2013-12-15

	An SFML Game structurally based on the Game From Scratch tutorial at:
		http://www.gamefromscratch.com/page/Game-From-Scratch-CPP-Edition.aspx
*/

#include "stdafx.h"
#include "Game.h"

// Windows native main function that supports Unicode.
// Compiler setup includes settings for standard main() to allow other
// environments.
int _tmain(int argc, _TCHAR* argv[])
{
	Game::Start();

    return 0;
}
