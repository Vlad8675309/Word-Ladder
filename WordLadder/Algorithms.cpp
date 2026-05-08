#include "Algorithms.h"

std::unordered_map<std::string, std::vector<std::string>> Algorithms::buildPatternMap(const std::string& dictionary, bool lengthRestriction, int length) {

	std::unordered_map<std::string, std::vector<std::string>> patternMap;

	std::ifstream in(dictionary);
	std::string word;

	while (in >> word) {
		if (lengthRestriction && length != word.size()) {
			continue;
		}
		else {
			for (size_t i = 0; i < word.size(); ++i) {
				std::string pattern = word;
				pattern[i] = '*';

				patternMap[pattern].push_back(word);
			}
		}
	}

	return patternMap;
}

Graph<std::string> Algorithms::buildWordGraph(std::unordered_map<std::string, std::vector<std::string>> patternMap) {

	Graph<std::string> wordGraph;

	for (const auto& pattern : patternMap) {
		const std::vector<std::string> words = pattern.second;

		for (size_t i = 0; i < words.size(); ++i) {
			for (size_t j = i + 1; j < words.size(); ++j) {
				wordGraph.addEdge(words[i], words[j]);
			}
		}
	}

	return wordGraph;
}
