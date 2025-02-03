#include "menu.h"
#include "DifferentStructures/Graph.h"
#include <iostream>
#include <chrono>
#include <fstream>
#include "tests.h"
#include <cstdlib>

void displayGraph(const Graph<std::string>& graph) {
    std::ofstream outFile("graph_output.py");
    outFile << "import networkx as nx\n";
    outFile << "import matplotlib.pyplot as plt\n";
    outFile << "G = nx.DiGraph()\n";

    // Добавление узлов
    for (int i = 0; i < graph.getNodes().GetLength(); ++i) {
        auto& node = graph.getNodes()[i];
        outFile << "G.add_node(\"" << node->getName() << "\")\n";
    }

    // Добавление рёбер
    for (int i = 0; i < graph.getEdges().GetLength(); ++i) {
        auto& edge = graph.getEdges()[i];
        outFile << "G.add_edge(\"" << edge->getFromNode()->getName() << "\", \""
                << edge->getToNode()->getName() << "\", weight="
                << edge->getWeight() << ")\n";
    }

    outFile << "pos = nx.spring_layout(G)\n";
    outFile << "weights = nx.get_edge_attributes(G, 'weight')\n";
    outFile << "nx.draw(G, pos, with_labels=True, node_color='skyblue', edge_color='black', node_size=200, font_size=15)\n";
    outFile << "nx.draw_networkx_edge_labels(G, pos, edge_labels=weights)\n";
    outFile << "plt.show()\n";

    outFile.close();

    system("C:\\Users\\Admin\\CLionProjects\\4-laba-3-sem\\cmake-build-debug\\graph_output.py");
}

void menu() {
    Graph<std::string> graph;

    auto nodeA = graph.createNode("A");
    auto nodeB = graph.createNode("B");
    auto nodeC = graph.createNode("C");
    auto nodeD = graph.createNode("D");
    auto nodeE = graph.createNode("E");

    graph.createEdge(10, nodeA, nodeB);
    graph.createEdge(15, nodeA, nodeC);
    graph.createEdge(12, nodeB, nodeD);
    graph.createEdge(10, nodeC, nodeD);
    graph.createEdge(2, nodeD, nodeE);
    graph.createEdge(1, nodeC, nodeE);


    while (true) {
        std::cout << "\n=== Graph Menu ===\n";
        std::cout << "1. Display Graph\n";
        std::cout << "2. Find Shortest Path (Dijkstra)\n";
        std::cout << "3. Find Shortest Path (Bellman-Ford)\n";
        std::cout << "4. Add Node\n";
        std::cout << "5. Add Edge\n";
        std::cout << "6. Remove Node\n";
        std::cout << "7. Remove Edge\n";
        std::cout << "8. Run Tests\n";
        std::cout << "9. Exit\n";
        std::cout << "Choose an option: ";

        int choice;
        std::cin >> choice;

        if (choice == 1) {
            displayGraph(graph);

        } else if (choice == 2) {
            bool isContinuable = true;
            for (int i = 0; i < graph.getEdges().GetLength(); ++i) {
                if (graph.getEdges()[i]->getWeight() < 0) {
                    std::cout << "You can not use Dijkstra algorithm with negative edges weight";
                    isContinuable = false;
                }
            }
            if (!isContinuable) {
                continue;
            }
            std::string startNode, targetNode;
            std::cout << "Enter start node: ";
            std::cin >> startNode;
            std::cout << "Enter target node: ";
            std::cin >> targetNode;
            ShrdPtr<Node<std::string>> start;
            ShrdPtr<Node<std::string>> target;
            try {
                start = graph.getNodeByName(startNode);
                target = graph.getNodeByName(targetNode);
            } catch (const std::exception& e) {
                std::cout << e.what() << "\n";
                continue;
            }

            if (start && target) {
                auto shortestPath = Dijkstra::findShortestPath(start, target);

                std::cout << "Shortest path from " << startNode << " to " << targetNode << ":\n";
                int totalWeight = 0;
                for (const auto& edge : shortestPath) {
                    std::cout << edge->getFromNode()->getName() << " -> "
                              << edge->getToNode()->getName() << " (Weight: "
                              << edge->getWeight() << ")\n";
                    totalWeight += edge->getWeight();
                }

                std::cout << "Total path weight: " << totalWeight << "\n";
            } else {
                std::cout << "Invalid node names.\n";
            }

        } else if (choice == 3) {
            std::string startNode, targetNode;
            std::cout << "Enter start node: ";
            std::cin >> startNode;
            std::cout << "Enter target node: ";
            std::cin >> targetNode;

            ShrdPtr<Node<std::string>> start;
            ShrdPtr<Node<std::string>> target;
            try {
                start = graph.getNodeByName(startNode);
                target = graph.getNodeByName(targetNode);
            } catch (const std::exception& e) {
                std::cout << e.what() << "\n";
                continue;
            }
            try {
                auto shortestPath = BellmanFord::findShortestPath(start, target, graph.getEdges(), graph.getNodes());

                std::cout << "Shortest path from " << startNode << " to " << targetNode << ":\n";
                int totalWeight = 0;
                for (const auto& edge : shortestPath) {
                    std::cout << edge->getFromNode()->getName() << " -> "
                              << edge->getToNode()->getName() << " (Weight: "
                              << edge->getWeight() << ")\n";
                    totalWeight += edge->getWeight();
                }

                std::cout << "Total path weight: " << totalWeight << "\n";
            } catch (const std::exception& e) {
                std::cout << e.what() << "\n";
            }

        } else if (choice == 4) {
            std::string nodeName;
            std::cout << "Enter node name: ";
            std::cin >> nodeName;
            graph.createNode(nodeName);
            std::cout << "Node " << nodeName << " added.\n";

        } else if (choice == 5) {
            try {
                std::string fromNodeName, toNodeName;
                int weight;
                std::cout << "Enter start node: ";
                std::cin >> fromNodeName;
                std::cout << "Enter target node: ";
                std::cin >> toNodeName;
                std::cout << "Enter edge weight: ";
                std::cin >> weight;

                ShrdPtr<Node<std::string>> fromNode = graph.getNodeByName(fromNodeName);
                ShrdPtr<Node<std::string>> toNode = graph.getNodeByName(toNodeName);

                if (fromNode && toNode) {
                    graph.createEdge(weight, fromNode, toNode);
                    std::cout << "Edge from " << fromNodeName << " to " << toNodeName << " with weight " << weight << " added.\n";
                } else {
                    std::cout << "Invalid node names.\n";
                }
            } catch (const std::exception& e) {
                std::cout << e.what() << "\n";
            }

        } else if (choice == 6) {
            std::string nodeName;
            std::cout << "Enter node name to remove: ";
            std::cin >> nodeName;
            graph.removeNode(nodeName);
        } else if (choice == 7) {
            std::string fromNode, toNode;
            std::cout << "Enter start node to remove: ";
            std::cin >> fromNode;
            std::cout << "Enter end node to remove: ";
            std::cin >> toNode;
            graph.removeEdge(fromNode, toNode);
        }
        else if (choice == 8) {
            testDijkstra();
            testBellmanFord();

            std::cout << "\nPerformance Test:\n";

            std::vector<std::pair<std::pair<long long, long long>, long long>> tests = {
                    {testPerformance(750, 10'000), 7'500'000},
                    {testPerformance(500, 10'000), 5'000'000},
                    {testPerformance(250, 10'000), 2'500'000},
                    {testPerformance(1'000, 1'000), 1'000'000},
                    {testPerformance(100, 1'000), 100000}
            };

            std::ofstream outFile("test_data.txt");
            if (!outFile) {

            }
            for (const auto& test : tests) {
                outFile << test.first.first << " "
                        << test.first.second << " "
                        << test.second << "\n";
            }
            outFile.close();
            system("C:\\Users\\Admin\\CLionProjects\\4-laba-3-sem\\print_graphics.py");

            std::cout << "All tests completed!\n";
        }

        else if (choice == 9) {
            break;

        } else {
            std::cout << "Invalid choice. Try again.\n";
        }
    }
}
