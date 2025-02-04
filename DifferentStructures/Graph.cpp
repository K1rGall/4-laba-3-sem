#include "Graph.h"
#include <iostream>

template<>
DynamicArraySmart<ShrdPtr<Edge<std::string>>> Dijkstra::findShortestPath(const ShrdPtr<Node<std::string>>& startNode, const ShrdPtr<Node<std::string>>& targetNode) {
    HashTable<ShrdPtr<Node<std::string>>, int> distances;
    HashTable<ShrdPtr<Node<std::string>>, ShrdPtr<Edge<std::string>>> previousEdge;
    DynamicArraySmart<ShrdPtr<Node<std::string>>> nodes;

    distances.Add(startNode, 0);
    nodes.Append(startNode);

    while (nodes.GetLength() > 0) {
        ShrdPtr<Node<std::string>> currentNode = nodes[0];
        int currentDistance = distances.Get(currentNode);
        int indexToRemove = 0;

        for (int i = 1; i < nodes.GetLength(); ++i) {
            if (distances.Get(nodes[i]) < currentDistance) {
                currentDistance = distances.Get(nodes[i]);
                currentNode = nodes[i];
                indexToRemove = i;
            }
        }

        nodes.RemoveAt(indexToRemove);

        if (currentNode == targetNode) {
            break;
        }

        for (const auto& edge : currentNode->getEdges()) {
            ShrdPtr<Node<std::string>> neighbor = (edge->getFromNode() == currentNode) ? edge->getToNode() : edge->getFromNode();
            int newDistance = currentDistance + edge->getWeight();

            if (!distances.ContainsKey(neighbor) || newDistance < distances.Get(neighbor)) {
                if (distances.ContainsKey(neighbor)) {
                    distances.Update(neighbor, newDistance);
                } else {
                    distances.Add(neighbor, newDistance);
                }

                if (previousEdge.ContainsKey(neighbor)) {
                    previousEdge.Update(neighbor, edge);
                } else {
                    previousEdge.Add(neighbor, edge);
                }

                nodes.Append(neighbor);
            }
        }
    }

    DynamicArraySmart<ShrdPtr<Edge<std::string>>> shortestPath;
    ShrdPtr<Node<std::string>> currentNode = targetNode;

    while (previousEdge.ContainsKey(currentNode)) {
        if (!previousEdge.ContainsKey(currentNode)) {
            return DynamicArraySmart<ShrdPtr<Edge<std::string>>>();
        }

        ShrdPtr<Edge<std::string>> edge = previousEdge.Get(currentNode);
        shortestPath.Prepend(edge);
        currentNode = (edge->getFromNode() == currentNode) ? edge->getToNode() : edge->getFromNode();
    }

    return shortestPath;
}

template<>
DynamicArraySmart<ShrdPtr<Edge<std::string>>> BellmanFord::findShortestPath(
    const ShrdPtr<Node<std::string>>& startNode,
    const ShrdPtr<Node<std::string>>& targetNode,
    const DynamicArraySmart<ShrdPtr<Edge<std::string>>>& edges,
    const DynamicArraySmart<ShrdPtr<Node<std::string>>>& nodes)
{
    HashTable<ShrdPtr<Node<std::string>>, int> distances;
    HashTable<ShrdPtr<Node<std::string>>, ShrdPtr<Edge<std::string>>> previousEdge;

    for(int i = 0; i < nodes.GetLength(); ++i) {
        distances.Add(nodes[i], std::numeric_limits<int>::max());
    }
    distances.Update(startNode, 0);

    for (size_t i = 0; i < nodes.GetLength() - 1; ++i) {
        for (int j = 0; j < edges.GetLength(); ++j) {
            const auto& edge = edges[j];
            ShrdPtr<Node<std::string>> fromNode = edge->getFromNode();
            ShrdPtr<Node<std::string>> toNode = edge->getToNode();
            int weight = edge->getWeight();

            if (distances.Get(fromNode) != std::numeric_limits<int>::max() &&
                    distances.Get(fromNode) + weight < distances.Get(toNode)) {
                distances.Update(toNode, distances.Get(fromNode) + weight);

                if (previousEdge.ContainsKey(toNode)) {
                    previousEdge.Update(toNode, edge);
                } else {
                    previousEdge.Add(toNode, edge);
                }
            }
        }
    }

    for (int j = 0; j < edges.GetLength(); ++j) {
        const auto& edge = edges[j];
        ShrdPtr<Node<std::string>> fromNode = edge->getFromNode();
        ShrdPtr<Node<std::string>> toNode = edge->getToNode();
        int weight = edge->getWeight();


        if (distances.Get(fromNode) != std::numeric_limits<int>::max() &&
            distances.Get(fromNode) + weight < distances.Get(toNode)) {
            throw std::runtime_error("Graph contains a negative-weight cycle");
            }
    }

    DynamicArraySmart<ShrdPtr<Edge<std::string>>> shortestPath;
    ShrdPtr<Node<std::string>> currentNode = targetNode;

    while (!(currentNode == startNode)) {
        if (!previousEdge.ContainsKey(currentNode)) {
            return DynamicArraySmart<ShrdPtr<Edge<std::string>>>();
        }

        ShrdPtr<Edge<std::string>> edge = previousEdge.Get(currentNode);
        shortestPath.Prepend(edge);
        currentNode = (edge->getFromNode() == currentNode) ? edge->getToNode() : edge->getFromNode();
    }

    return shortestPath;
}
