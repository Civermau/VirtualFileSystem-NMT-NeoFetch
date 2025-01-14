#pragma once
#include <iostream>
#include <vector>
#include "Node.h"
#include "handMade.h"

namespace dsp {
	static void StandarDisplay(std::string content) {
		std::cout << content;
	}
	static void StandarDisplay(std::string name, NodeType nodeType, int level) {
		for (int i = 0; i < level; i++) {
			std::cout << "  ";
		}

		std::cout << "\033[31m* \033[0m";
		if (nodeType == NodeType::NodeFolder) {
			std::cout << "\033[38;2;255;187;171m" << name << "/\033[0m";
		}
		if (nodeType == NodeType::NodeFile) {
			std::cout << "\033[38;2;255;255;255m" << name << "\033[0m";
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