#include "menu.h"
#include "DifferentStructures/Graph.h"
#include <iostream>
#include <fstream>
#include "tests.h"
#include <cstdlib>
#include <ctime>

void displayGraph(const Graph<std::string>& graph) {
    std::ofstream outFile("graph_output.py");
    outFile << "import networkx as nx\n";
    outFile << "import matplotlib.pyplot as plt\n";
    outFile << "G = nx.MultiDiGraph()\n";

    for (int i = 0; i < graph.getNodes().GetLength(); ++i) {
        auto& node = graph.getNodes()[i];
        outFile << "G.add_node(\"" << node->getName() << "\")\n";
    }

    outFile << "edge_curvatures = {}\n";
    outFile << "edge_labels = {}\n";
    outFile << "edge_count = {}\n";
    for (int i = 0; i < graph.getEdges().GetLength(); ++i) {
        auto& edge = graph.getEdges()[i];
        std::string from = edge->getFromNode()->getName();
        std::string to = edge->getToNode()->getName();
        std::string key = "(\"" + from + "\", \"" + to + "\")";

        outFile << "edge_count.setdefault(" << key << ", 0)\n";
        outFile << "curvature = 0.25 * (edge_count[" << key << "] % 2 * 2 - 1) * (edge_count[" << key << "] // 2 + 1)\n";

        outFile << "G.add_edge(\"" << from << "\", \"" << to << "\", weight=" << edge->getWeight()
                << ", key=" << i << ")\n";

        outFile << "edge_labels[(\"" << from << "\", \"" << to << "\", " << i << ")] = " << edge->getWeight() << "\n";
        outFile << "edge_count[" << key << "] += 1\n";
    }

    outFile << "pos = nx.spring_layout(G)\n";
    outFile << "plt.figure(figsize=(8, 6))\n";
    outFile << "for edge in G.edges(keys=True):\n";
    outFile << "    curvature = edge_curvatures.get(edge, 0)\n";
    outFile << "    nx.draw_networkx_edges(G, pos, edgelist=[edge], connectionstyle=f'arc3,rad={curvature}')\n";
    outFile << "nx.draw(G, pos, with_labels=True, node_color='skyblue', edge_color='black', node_size=200, font_size=15)\n";
    outFile << "nx.draw_networkx_edge_labels(G, pos, edge_labels=edge_labels, font_size=12, bbox=dict(facecolor='white', edgecolor='black', boxstyle='round,pad=0.3'))\n";
    outFile << "plt.show()\n";

    outFile.close();
    system("graph_output.py");
}


void generateRandomGraph(Graph<std::string>& graph, int vertexCount, int edgesPerVertex) {

    while (graph.getEdges().GetLength() > 0) {
        // Удаляем первое ребро из графа, пока не очистим все
        auto& edge = graph.getEdges()[0];
        graph.removeEdge(edge->getFromNode()->getName(), edge->getToNode()->getName());
    }

    while (graph.getNodes().GetLength() > 0) {

        auto& node = graph.getNodes()[0];
        graph.removeNode(node->getName());
    }

    for (int i = 0; i < vertexCount; ++i) {
        graph.createNode("Node" + std::to_string(i));
    }


    std::srand(std::time(0));
    for (int i = 0; i < vertexCount; ++i) {
        int edgesCreated = 0;
        while (edgesCreated < edgesPerVertex) {
            int targetNodeIndex = std::rand() % vertexCount;

            if (i != targetNodeIndex) {
                int weight = std::rand() % 100 + 1;
                auto fromNode = graph.getNodes()[i];
                auto toNode = graph.getNodes()[targetNodeIndex];
                graph.createEdge(weight, fromNode, toNode);
                ++edgesCreated;
            }
        }
    }
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
        std::cout << "9. Generate Random Graph\n";
        std::cout << "10. Exit\n";
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
        } else if (choice == 8) {
            testDijkstra();
            testBellmanFord();
            testNodeEdgeOperations();
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
            int vertexCount, edgesPerVertex;
            std::cout << "Enter the number of nodes: ";
            std::cin >> vertexCount;
            std::cout << "Enter the number of edges per node: ";
            std::cin >> edgesPerVertex;

            generateRandomGraph(graph, vertexCount, edgesPerVertex);
            std::cout << "Random graph generated with " << vertexCount << " vertices and "
                      << edgesPerVertex << " edges per vertex.\n";

        }

        else if (choice == 10) {
            break;

        } else {
            std::cout << "Invalid choice. Try again.\n";
        }
    }
}
