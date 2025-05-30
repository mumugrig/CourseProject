#include "VectorUtility.hpp"
#include "MainMenu.hpp"

#if 1




int main() {
	StorageSystem files;
	Player player1("null");
	Player player2("null");
	CharacterEnum characterId1 = ASH;
	CharacterEnum characterId2 = ASH;
	
	MainMenu::choosePlayers(files, player1, player2);
	MainMenu::printMenu(files, player1, characterId1, player2, characterId2);
	
	files.games().save();
}

#endif