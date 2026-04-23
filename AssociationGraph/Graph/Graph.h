// AssociationGraph.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <iostream>
#include <map>
#include <vector>
#include <stdexcept>
#include "../eigen/Eigen/Eigen"

using namespace std;
using namespace Eigen;

// Forward declaration so Vertex and the IsGraph trait can reference Graph.
template<typename Value> class Graph;

// Type trait: IsGraph<T>::value is true when T is Graph<something>, false otherwise.
// Asked at compile time, not runtime.
template<typename T>
struct IsGraph {
	static constexpr bool value = false;
};

template<typename Value>
struct IsGraph<Graph<Value>> {
	static constexpr bool value = true;
};

template<typename Value>
class Vertex {
	Value value;
	vector<Vertex<Value>> adjacentVertices;
	// When Value is itself a Graph, this points at the graph stored in `value`.
	// For non-Graph values it just stays null.
	Value* parentGraph = nullptr;
public:
	Vertex(const Value& value) : value(value) {
		if constexpr (IsGraph<Value>::value) {
			parentGraph = &this->value;
		}
	}

	// Copy constructor: re-point parentGraph at OUR value, not the source's.
	Vertex(const Vertex& other)
		: value(other.value)
		, adjacentVertices(other.adjacentVertices) {
		if constexpr (IsGraph<Value>::value) {
			parentGraph = &this->value;
		}
	}

	// Copy assignment: same idea.
	Vertex& operator=(const Vertex& other) {
		if (this != &other) {
			value = other.value;
			adjacentVertices = other.adjacentVertices;
			if constexpr (IsGraph<Value>::value) {
				parentGraph = &this->value;
			} else {
				parentGraph = nullptr;
			}
		}
		return *this;
	}

	Value& GetValue() { return value; }
	const Value& GetValue() const { return value; }

	const vector<Vertex<Value>>& GetAdjacentVertices() const { return adjacentVertices; }

	Value* GetParentGraph() const { return parentGraph; }

	void operator=(const Value& v) { value = v; }

	void AddAdjacentVertex(Vertex<Value>& vertex) {
		adjacentVertices.push_back(vertex);
	}
};

template<typename Value>
class Graph {
public:
	Graph() = default;

	void AddMember(Vertex<Value>& vertex) {
		for (Vertex<Value>& member : Members) {
			if (member.GetValue() == vertex.GetValue()) {
				return;
			}
			member.AddAdjacentVertex(vertex);
		}
		Members.push_back(vertex);
	}

	Vertex<Value>& operator[](int position) {
		if (position < 0 || position >= (int)Members.size()) {
			throw out_of_range("Position is out of range.");
		}
		return Members[position];
	}

	int Size() const { return (int)Members.size(); }

private:
	vector<Vertex<Value>> Members;
};
