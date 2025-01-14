#pragma once
#include <iostream>
#include <vector>
#include "Node.h"
#include "handMade.h"

namespace dsp {
	static void StandarDisplay(std::string folderName, std::vector<std::pair<std::string, NodeType>> data) {
		std::cout << folderName << "/" << std::endl;
		for (const std::pair<std::string, NodeType>& node : data) {
			std::cout << "├──" << node.first << (node.second == NodeType::NodeFolder ? "/" : "") << std::endl;
		}
	}
	static void StandarDisplay(std::string content) {
		std::cout << content;
	}
	static void StandarDisplay(std::string name, NodeType nodeType, int level) {
		if (level == 0) {
			std::cout << name << "/" << std::endl;
			return;
		}
		if (level == 1) {
			std::cout << "├──" << name;
			if (nodeType == NodeType::NodeFolder) {
				std::cout << "/";
			}
			std::cout << std::endl;
			return;
		}
		std::cout << "│  ";
		for (int i = 2; i < level; i++) {
			std::cout << "   ";
		}
		std::cout << "├──" << name;
		if (nodeType == NodeType::NodeFolder) {
			std::cout << "/";
		}
		std::cout << std::endl;
	}
	static void ClearConsole() {
		// Código ANSI para limpiar la consola
		std::cout << "\033[2J\033[1;1H";
	}
	static std::string GetInput() {
		std::string input;
		std::getline(std::cin, input);
		return hm::CinFail(input);
		
	}
	static std::string GetCMD(std::string& command) {
		size_t pos = command.find(' ');
		if (pos == std::string::npos) {
			std::string save = command;
			command = "\0";
			return save;
			
		}
		
		std::string save = command.substr(0, pos);

		command = command.substr(pos + 1);
		return save;

	}
}