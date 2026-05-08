#pragma once
#include "Graph.h"
#include <unordered_map>
#include <vector>
#include <string>
#include <fstream>

namespace Algorithms {
	std::unordered_map < std::string, std::vector<std::string>> buildPatternMap(const std::string& dictionary, bool lengthRestriction = false, int length = 0);

	Graph<std::string> buildWordGraph(std::unordered_map<std::string, std::vector<std::string>> patternMap);

}