#include <iostream>
#include "Folder.h"
#include "Display.h"
int main() {
	std::shared_ptr<Folder> root = std::make_shared<Folder>("~");
	std::shared_ptr<Folder> ALIVE = root;
	while (true) {
		dsp::StandarDisplay(root->GetPath() + "$ ");
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

		if (preCmd == "close") {
			break;
		}

		if (command == "\0") {
			continue;
		}

		if (preCmd == "rm") {
			if (!root->DeleteContent(command)) {
				dsp::StandarDisplay("bash: rm: " + command + ": Doesn't exists\n");
			}
		}
		

		if (preCmd == "cd") {
			if (command == "..") {
				root = root->GetParent();
				continue;
			}
			if (command == "~") {
				root = ALIVE;
				continue;
			}
			if (root->GetSubFolder(command).expired()) {
				dsp::StandarDisplay("bash: cd:  " + command + ": No such file or directory\n");
				continue;
			}
			root = root->GetSubFolder(command).lock();
			continue;
		}
		if (preCmd == "mkdir") {
			if (!root->CreateContent(command, NodeType::NodeFolder)) {
				dsp::StandarDisplay("bash: mkdir:  " + command + ": Directory already exists\n");
			}
			continue;
		}
		if (preCmd == "touch") {
			if (!root->CreateContent(command, NodeType::NodeFile)) {
				dsp::StandarDisplay("bash: touch:  " + command + ": File already exists\n");
			}
			continue;
		}
	}
}