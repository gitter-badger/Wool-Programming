#include "PXml.h"
using namespace std;

int main(){
	vector<Game> mygame;

	mygame.push_back(Game("THE IDOLM@STER", "バンダイナムコゲームス", 5400));

	for (vector<Game>::iterator i = mygame.begin(); i != mygame.end(); i++){
		cout << i->title << ", " << i->company << ", " << static_cast<int>(i->price) << endl;
	}

	PXml px;
	px.write("game.xml", mygame);

	return 0;
}