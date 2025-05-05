#include <iostream>
#include "Folder.h"
#include "Display.h"
#include <unordered_map>
#include <functional>
#include <string>

// Method prototype for parsing command and arguments
std::pair<std::string, std::string> parseCommand(const std::string& input);

int main() {
	std::shared_ptr<Folder> root = std::make_shared<Folder>("~");
	std::shared_ptr<Folder> ALIVE = root;
	
	// Define command handlers
	std::unordered_map<std::string, std::function<void(const std::string&)>> commands;
	bool running = true;
	
	// Register all commands
	commands["clear"] = [](const std::string&) {
		dsp::ClearConsole();
	};
	
	commands["ls"] = [&root](const std::string&) {
		root->ShowContents(dsp::StandarDisplay);
	};
	
	commands["tree"] = [&root](const std::string&) {
		root->ShowAll(dsp::StandarDisplay, 0);
	};
	
	commands["exit"] = [&running](const std::string&) {
		running = false;
	};
	
	commands["rm"] = [&root](const std::string& arg) {
		if (!root->DeleteContent(arg)) {
			dsp::StandarDisplay("bash: rm: " + arg + ": Doesn't exists\n");
		}
	};
	
	commands["cd"] = [&root, &ALIVE](const std::string& arg) {
		if (arg == "..") {
			root = root->GetParent();
			return;
		}
		if (arg == "~") {
			root = ALIVE;
			return;
		}
		if (root->GetSubFolder(arg).expired()) {
			dsp::StandarDisplay("bash: cd: " + arg + ": No such file or directory\n");
			return;
		}
		root = root->GetSubFolder(arg).lock();
	};
	
	commands["mkdir"] = [&root](const std::string& arg) {
		if (!root->CreateContent(arg, NodeType::NodeFolder)) {
			dsp::StandarDisplay("bash: mkdir: " + arg + ": Directory already exists\n");
		}
	};
	
	commands["touch"] = [&root](const std::string& arg) {
		if (!root->CreateContent(arg, NodeType::NodeFile)) {
			dsp::StandarDisplay("bash: touch: " + arg + ": File already exists\n");
		}
	};
	
	// Main command processing loop
	while (running) {
		// Get command input from user
		dsp::StandarDisplay(root->GetPath() + "$ ");
		std::string input = dsp::GetInput();
		
		// Parse command and arguments
		std::string preCmd, command;
		std::tie(preCmd, command) = parseCommand(input);
		
		// Skip empty commands
		if (preCmd.empty()) {
			continue;
		}
		
		// Execute command if it exists
		auto cmdIt = commands.find(preCmd);
		if (cmdIt != commands.end()) {
			cmdIt->second(command);
		} else {
			dsp::StandarDisplay("Unknown command: " + preCmd + "\n");
		}
	}
}

// Helper function to parse command and arguments
std::pair<std::string, std::string> parseCommand(const std::string& input) {
	std::string cmd, arg;
	size_t spacePos = input.find(' ');
	
	if (spacePos != std::string::npos) {
		cmd = input.substr(0, spacePos);
		arg = input.substr(spacePos + 1);
	} else {
		cmd = input;
		arg = "";
	}
	
	return {cmd, arg};
}