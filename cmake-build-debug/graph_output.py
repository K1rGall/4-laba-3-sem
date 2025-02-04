import networkx as nx
import matplotlib.pyplot as plt
G = nx.MultiDiGraph()
G.add_node("Node0")
G.add_node("Node1")
G.add_node("Node2")
G.add_node("Node3")
G.add_node("Node4")
G.add_node("Node5")
G.add_node("Node6")
G.add_node("Node7")
G.add_node("Node8")
G.add_node("Node9")
edge_curvatures = {}
edge_labels = {}
edge_count = {}
edge_count.setdefault(("Node0", "Node4"), 0)
curvature = 0.25 * (edge_count[("Node0", "Node4")] % 2 * 2 - 1) * (edge_count[("Node0", "Node4")] // 2 + 1)
G.add_edge("Node0", "Node4", weight=55, key=0)
edge_labels[("Node0", "Node4", 0)] = 55
edge_count[("Node0", "Node4")] += 1
edge_count.setdefault(("Node0", "Node7"), 0)
curvature = 0.25 * (edge_count[("Node0", "Node7")] % 2 * 2 - 1) * (edge_count[("Node0", "Node7")] // 2 + 1)
G.add_edge("Node0", "Node7", weight=72, key=1)
edge_labels[("Node0", "Node7", 1)] = 72
edge_count[("Node0", "Node7")] += 1
edge_count.setdefault(("Node1", "Node2"), 0)
curvature = 0.25 * (edge_count[("Node1", "Node2")] % 2 * 2 - 1) * (edge_count[("Node1", "Node2")] // 2 + 1)
G.add_edge("Node1", "Node2", weight=92, key=2)
edge_labels[("Node1", "Node2", 2)] = 92
edge_count[("Node1", "Node2")] += 1
edge_count.setdefault(("Node1", "Node8"), 0)
curvature = 0.25 * (edge_count[("Node1", "Node8")] % 2 * 2 - 1) * (edge_count[("Node1", "Node8")] // 2 + 1)
G.add_edge("Node1", "Node8", weight=69, key=3)
edge_labels[("Node1", "Node8", 3)] = 69
edge_count[("Node1", "Node8")] += 1
edge_count.setdefault(("Node2", "Node1"), 0)
curvature = 0.25 * (edge_count[("Node2", "Node1")] % 2 * 2 - 1) * (edge_count[("Node2", "Node1")] // 2 + 1)
G.add_edge("Node2", "Node1", weight=57, key=4)
edge_labels[("Node2", "Node1", 4)] = 57
edge_count[("Node2", "Node1")] += 1
edge_count.setdefault(("Node2", "Node5"), 0)
curvature = 0.25 * (edge_count[("Node2", "Node5")] % 2 * 2 - 1) * (edge_count[("Node2", "Node5")] // 2 + 1)
G.add_edge("Node2", "Node5", weight=55, key=5)
edge_labels[("Node2", "Node5", 5)] = 55
edge_count[("Node2", "Node5")] += 1
edge_count.setdefault(("Node3", "Node5"), 0)
curvature = 0.25 * (edge_count[("Node3", "Node5")] % 2 * 2 - 1) * (edge_count[("Node3", "Node5")] // 2 + 1)
G.add_edge("Node3", "Node5", weight=25, key=6)
edge_labels[("Node3", "Node5", 6)] = 25
edge_count[("Node3", "Node5")] += 1
edge_count.setdefault(("Node3", "Node1"), 0)
curvature = 0.25 * (edge_count[("Node3", "Node1")] % 2 * 2 - 1) * (edge_count[("Node3", "Node1")] // 2 + 1)
G.add_edge("Node3", "Node1", weight=81, key=7)
edge_labels[("Node3", "Node1", 7)] = 81
edge_count[("Node3", "Node1")] += 1
edge_count.setdefault(("Node4", "Node2"), 0)
curvature = 0.25 * (edge_count[("Node4", "Node2")] % 2 * 2 - 1) * (edge_count[("Node4", "Node2")] // 2 + 1)
G.add_edge("Node4", "Node2", weight=68, key=8)
edge_labels[("Node4", "Node2", 8)] = 68
edge_count[("Node4", "Node2")] += 1
edge_count.setdefault(("Node4", "Node9"), 0)
curvature = 0.25 * (edge_count[("Node4", "Node9")] % 2 * 2 - 1) * (edge_count[("Node4", "Node9")] // 2 + 1)
G.add_edge("Node4", "Node9", weight=1, key=9)
edge_labels[("Node4", "Node9", 9)] = 1
edge_count[("Node4", "Node9")] += 1
edge_count.setdefault(("Node5", "Node6"), 0)
curvature = 0.25 * (edge_count[("Node5", "Node6")] % 2 * 2 - 1) * (edge_count[("Node5", "Node6")] // 2 + 1)
G.add_edge("Node5", "Node6", weight=77, key=10)
edge_labels[("Node5", "Node6", 10)] = 77
edge_count[("Node5", "Node6")] += 1
edge_count.setdefault(("Node5", "Node0"), 0)
curvature = 0.25 * (edge_count[("Node5", "Node0")] % 2 * 2 - 1) * (edge_count[("Node5", "Node0")] // 2 + 1)
G.add_edge("Node5", "Node0", weight=61, key=11)
edge_labels[("Node5", "Node0", 11)] = 61
edge_count[("Node5", "Node0")] += 1
edge_count.setdefault(("Node6", "Node4"), 0)
curvature = 0.25 * (edge_count[("Node6", "Node4")] % 2 * 2 - 1) * (edge_count[("Node6", "Node4")] // 2 + 1)
G.add_edge("Node6", "Node4", weight=39, key=12)
edge_labels[("Node6", "Node4", 12)] = 39
edge_count[("Node6", "Node4")] += 1
edge_count.setdefault(("Node6", "Node2"), 0)
curvature = 0.25 * (edge_count[("Node6", "Node2")] % 2 * 2 - 1) * (edge_count[("Node6", "Node2")] // 2 + 1)
G.add_edge("Node6", "Node2", weight=30, key=13)
edge_labels[("Node6", "Node2", 13)] = 30
edge_count[("Node6", "Node2")] += 1
edge_count.setdefault(("Node7", "Node6"), 0)
curvature = 0.25 * (edge_count[("Node7", "Node6")] % 2 * 2 - 1) * (edge_count[("Node7", "Node6")] // 2 + 1)
G.add_edge("Node7", "Node6", weight=97, key=14)
edge_labels[("Node7", "Node6", 14)] = 97
edge_count[("Node7", "Node6")] += 1
edge_count.setdefault(("Node7", "Node1"), 0)
curvature = 0.25 * (edge_count[("Node7", "Node1")] % 2 * 2 - 1) * (edge_count[("Node7", "Node1")] // 2 + 1)
G.add_edge("Node7", "Node1", weight=47, key=15)
edge_labels[("Node7", "Node1", 15)] = 47
edge_count[("Node7", "Node1")] += 1
edge_count.setdefault(("Node8", "Node4"), 0)
curvature = 0.25 * (edge_count[("Node8", "Node4")] % 2 * 2 - 1) * (edge_count[("Node8", "Node4")] // 2 + 1)
G.add_edge("Node8", "Node4", weight=70, key=16)
edge_labels[("Node8", "Node4", 16)] = 70
edge_count[("Node8", "Node4")] += 1
edge_count.setdefault(("Node8", "Node7"), 0)
curvature = 0.25 * (edge_count[("Node8", "Node7")] % 2 * 2 - 1) * (edge_count[("Node8", "Node7")] // 2 + 1)
G.add_edge("Node8", "Node7", weight=44, key=17)
edge_labels[("Node8", "Node7", 17)] = 44
edge_count[("Node8", "Node7")] += 1
edge_count.setdefault(("Node9", "Node8"), 0)
curvature = 0.25 * (edge_count[("Node9", "Node8")] % 2 * 2 - 1) * (edge_count[("Node9", "Node8")] // 2 + 1)
G.add_edge("Node9", "Node8", weight=24, key=18)
edge_labels[("Node9", "Node8", 18)] = 24
edge_count[("Node9", "Node8")] += 1
edge_count.setdefault(("Node9", "Node1"), 0)
curvature = 0.25 * (edge_count[("Node9", "Node1")] % 2 * 2 - 1) * (edge_count[("Node9", "Node1")] // 2 + 1)
G.add_edge("Node9", "Node1", weight=99, key=19)
edge_labels[("Node9", "Node1", 19)] = 99
edge_count[("Node9", "Node1")] += 1
pos = nx.spring_layout(G)
plt.figure(figsize=(8, 6))
for edge in G.edges(keys=True):
    curvature = edge_curvatures.get(edge, 0)
    nx.draw_networkx_edges(G, pos, edgelist=[edge], connectionstyle=f'arc3,rad={curvature}')
nx.draw(G, pos, with_labels=True, node_color='skyblue', edge_color='black', node_size=200, font_size=15)
nx.draw_networkx_edge_labels(G, pos, edge_labels=edge_labels, font_size=12, bbox=dict(facecolor='white', edgecolor='black', boxstyle='round,pad=0.3'))
plt.show()
