#include <iostream>
#include "Folder.h"

int main() {
	Folder test("nyan");
	test.CreateFile("testFile.txt");
	test.CreateFile("nyasu");
	test.CreateFile("nya");
	test.ShowContents(Display::StandarDisplay);
}