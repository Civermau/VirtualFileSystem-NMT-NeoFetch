#include <iostream>
#include "Folder.h"
#include "Display.h"

int main() {
	std::shared_ptr<Folder> root = std::make_shared<Folder>("~");
	std::shared_ptr<Folder> ALIVE = root;
	root->CreateContent("testFile.txt", NodeType::NodeFile);
	root->CreateContent("nyasu.rar", NodeType::NodeFile);
	root->CreateContent("nuevvo.txt", NodeType::NodeFile);
	root->CreateContent("folder", NodeType::NodeFolder);
	while (true) {
		dsp::StandarDisplay(root->GetPath() + "$ ");
		//root->ShowAll(dsp::StandarDisplay, 0);
		std::string command = dsp::GetInput();
		std::string preCmd = dsp::GetCMD(command);

		if (preCmd == "clear") {
			dsp::ClearConsole();
			continue;
		}

		if (preCmd == "ls") {
			root->ShowContents(dsp::StandarDisplay);
		}

		if (preCmd == "tree") {
			root->ShowAll(dsp::StandarDisplay, 0);
		}

		if (command == "\0") {
			continue;
		}

		if (preCmd == "cd") {
			if (command == "..") {
				root = root->parentFolder.lock();
			}
			if (!root->GetSubFolder(command).expired()) {
				root = root->GetSubFolder(command).lock();
			}
			continue;
		}
		if (preCmd == "mkdir") {
			root->CreateContent(command, NodeType::NodeFolder);
			continue;
		}
		if (preCmd == "touch") {
			root->CreateContent(command, NodeType::NodeFile);
			continue;
		}
		
		//if (dsp::GetCMD(preCmd) == "cddd") {
		//	root = root->parentFolder.lock();
		//	ALIVE->ShowAll(dsp::StandarDisplay, 0);
		//	continue;
		//}
	}
	root->ShowAll(dsp::StandarDisplay, 0);

}