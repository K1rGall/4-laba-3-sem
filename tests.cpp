#include "tests.h"
#include "DifferentStructures/Graph.h"
#include <cassert>
#include <chrono>

std::pair<long long, long long> testPerformance(const int& numNodes, const int& numEdges) {

    Graph<std::string> graph;
    std::vector<ShrdPtr<Node<std::string>>> nodes;
    for (int i = 0; i < numNodes; ++i) {
        nodes.push_back(graph.createNode("Node_" + std::to_string(i)));
    }

    for (int i = 0; i < numEdges; ++i) {
        int fromIndex = rand() % numNodes;
        int toIndex = rand() % numNodes;
        if (fromIndex != toIndex) {
            int weight = rand() % 100;
            graph.createEdge(weight, nodes[fromIndex], nodes[toIndex]);
        }
    }

    auto startNode = nodes[0];
    auto targetNode = nodes[numNodes - 1];

    auto startDijkstra = std::chrono::high_resolution_clock::now();
    try {
        auto dijkstraPath = Dijkstra::findShortestPath(startNode, targetNode);
    } catch (const std::exception& e) {
        std::cout << "Dijkstra failed: " << e.what() << std::endl;
    }
    auto endDijkstra = std::chrono::high_resolution_clock::now();

    auto startBellmanFord = std::chrono::high_resolution_clock::now();
    try {
        auto bellmanFordPath = BellmanFord::findShortestPath(
            startNode, targetNode, graph.getEdges(), graph.getNodes());
    } catch (const std::exception& e) {
        std::cout << "Bellman-Ford failed: " << e.what() << std::endl;
    }
    auto endBellmanFord = std::chrono::high_resolution_clock::now();

    auto dijkstraDuration = std::chrono::duration_cast<std::chrono::milliseconds>(endDijkstra - startDijkstra).count();
    auto bellmanFordDuration = std::chrono::duration_cast<std::chrono::milliseconds>(endBellmanFord - startBellmanFord).count();

    std::cout << "Dijkstra execution time: " << dijkstraDuration << " ms" << std::endl;
    std::cout << "Bellman-Ford execution time: " << bellmanFordDuration << " ms" << std::endl;

    if (bellmanFordDuration > dijkstraDuration) {
        std::cout << "Dijkstra was faster by " << bellmanFordDuration - dijkstraDuration << " ms.\n" << std::endl;
    } else {
        std::cout << "Bellman-Ford was faster by " << dijkstraDuration - bellmanFordDuration << " ms.\n" << std::endl;
    }
    return {dijkstraDuration, bellmanFordDuration};
}
void testNodeEdgeOperations() {
    Graph<std::string> graph;
    auto node1 = graph.createNode("Node1");
    auto node2 = graph.createNode("Node2");
    auto node3 = graph.createNode("Node3");

    auto edge1 = graph.createEdge(10, node1, node2);
    auto edge2 = graph.createEdge(20, node2, node3);
    assert(graph.getNodes().GetLength() == 3);
    assert(graph.getEdges().GetLength() == 2);

    graph.removeEdge("Node1", "Node2");
    assert(graph.getEdges().GetLength() == 1);

    graph.removeNode("Node3");
    assert(graph.getNodes().GetLength() == 2);

    std::cout << "Node and Edge operations test passed!" << std::endl;
}

void testDijkstra() {
    Graph<std::string> graph;
    auto nodeA = graph.createNode("A");
    auto nodeB = graph.createNode("B");
    auto nodeC = graph.createNode("C");
    auto nodeD = graph.createNode("D");

    graph.createEdge(1, nodeA, nodeB);
    graph.createEdge(4, nodeA, nodeC);
    graph.createEdge(2, nodeB, nodeC);
    graph.createEdge(5, nodeB, nodeD);
    graph.createEdge(1, nodeC, nodeD);

    auto shortestPath = Dijkstra::findShortestPath(nodeA, nodeD);

    // Ожидаемый путь: A -> B -> C -> D
    assert(shortestPath.GetLength() == 3); // Путь состоит из 3 ребер
    assert(shortestPath[0]->getFromNode()->getName() == "A");
    assert(shortestPath[0]->getToNode()->getName() == "B");
    assert(shortestPath[1]->getFromNode()->getName() == "B");
    assert(shortestPath[1]->getToNode()->getName() == "C");
    assert(shortestPath[2]->getFromNode()->getName() == "C");
    assert(shortestPath[2]->getToNode()->getName() == "D");
    graph.createEdge(0, nodeA, nodeD);

    auto shortestPath1 = Dijkstra::findShortestPath(nodeA, nodeD);
    // Ожидаемый путь: A -> D
    assert(shortestPath1.GetLength() == 1);
    assert(shortestPath1[0]->getFromNode()->getName() == "A");
    assert(shortestPath1[0]->getToNode()->getName() == "D");
    std::cout << "Dijkstra test passed!" << std::endl;
}

void testBellmanFord() {
    Graph<std::string> graph;
    auto nodeA = graph.createNode("A");
    auto nodeB = graph.createNode("B");
    auto nodeC = graph.createNode("C");
    auto nodeD = graph.createNode("D");

    graph.createEdge(1, nodeA, nodeB);
    graph.createEdge(4, nodeA, nodeC);
    graph.createEdge(2, nodeB, nodeC);
    graph.createEdge(5, nodeB, nodeD);
    graph.createEdge(1, nodeC, nodeD);

    auto shortestPath = BellmanFord::findShortestPath(nodeA, nodeD, graph.getEdges(), graph.getNodes());

    // Ожидаемый путь: A -> B -> C -> D
    assert(shortestPath.GetLength() == 3);
    assert(shortestPath[0]->getFromNode()->getName() == "A");
    assert(shortestPath[0]->getToNode()->getName() == "B");
    assert(shortestPath[1]->getFromNode()->getName() == "B");
    assert(shortestPath[1]->getToNode()->getName() == "C");
    assert(shortestPath[2]->getFromNode()->getName() == "C");
    assert(shortestPath[2]->getToNode()->getName() == "D");

    std::cout << "Bellman-Ford test passed!" << std::endl;

    Graph<std::string> negativeGraph;
    auto node1 = negativeGraph.createNode("1");
    auto node2 = negativeGraph.createNode("2");
    auto node3 = negativeGraph.createNode("3");

    negativeGraph.createEdge(4, node1, node2);
    negativeGraph.createEdge(1, node2, node3);
    negativeGraph.createEdge(-10, node1, node3);

    // Ожидаемый путь: 1 -> 3
    auto negativePath = BellmanFord::findShortestPath(node1, node3, negativeGraph.getEdges(), negativeGraph.getNodes());
    assert(negativePath.GetLength() == 1);
    assert(negativePath[0]->getFromNode()->getName() == "1");
    assert(negativePath[0]->getToNode()->getName() == "3");

    std::cout << "Bellman-Ford negative edge test passed!" << std::endl;

    Graph<std::string> negativeCycleGraph;
    auto n1 = negativeCycleGraph.createNode("1");
    auto n2 = negativeCycleGraph.createNode("2");
    auto n3 = negativeCycleGraph.createNode("3");

    negativeCycleGraph.createEdge(1, n1, n2);
    negativeCycleGraph.createEdge(-5, n2, n3);
    negativeCycleGraph.createEdge(2, n3, n1);

    try {
        auto cyclePath = BellmanFord::findShortestPath(n1, n3, negativeCycleGraph.getEdges(), negativeCycleGraph.getNodes());
        assert(false && "Test failed. Expected exception due to negative cycle.");
    } catch (const std::runtime_error& e) {
        assert(std::string(e.what()) == "Graph contains a negative-weight cycle");
        std::cout << "Bellman-Ford negative cycle test passed!" << std::endl;
    }
}