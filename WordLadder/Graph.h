#pragma once
#include <map>
#include <set>
#include <vector>
#include <queue>
#include <set>

template <typename T>

class Graph {
private:
	std::map<T, std::set<T>> adjacencyList;

public:
	const std::map<T, std::set<T>>& getAdjacencyList() const { return adjacencyList; }

	void addNode(const T& node) {
		if (adjacencyList.find(node) == adjacencyList.end()) {
			adjacencyList[node] = std::set<T>();
		}
	}

	void addEdge(const T& node1, const T& node2) {
		addNode(node1);
		addNode(node2);
		adjacencyList[node1].insert(node2);
		adjacencyList[node2].insert(node1);
	}


	std::vector<T> findPath(const T& start, const T& end) {
		std::queue<T> queue;
		std::set<T> visited;
		std::map<T, T> parent;

		queue.push(start);
		visited.insert(start);
		parent[start] = start;

		while (!queue.empty()) {
			T current = queue.front();
			queue.pop();

			if (current == end) {
				std::vector<T> path;
				for (T node = end; node != start; node = parent[node]) {
					path.push_back(node);
				}
				path.push_back(start);
				std::reverse(path.begin(), path.end());
				return path;
			}

			for (const auto& node : adjacencyList[current]) {
				if (visited.find(node) == visited.end()) {
					visited.insert(node);
					queue.push(node);
					parent[node] = current;
				}
			}
		}

		return std::vector<T>(); 

	}
};

