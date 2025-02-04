import networkx as nx
import matplotlib.pyplot as plt
G = nx.MultiDiGraph()
G.add_node("A")
G.add_node("B")
G.add_node("C")
G.add_node("D")
G.add_node("E")
edge_curvatures = {}
G.add_edge("A", "B", weight=10, key=0)
edge_curvatures[('A', 'B', 0)] = 0
G.add_edge("A", "C", weight=15, key=1)
edge_curvatures[('A', 'C', 1)] = 0.1
G.add_edge("B", "D", weight=12, key=2)
edge_curvatures[('B', 'D', 2)] = 0.2
G.add_edge("C", "D", weight=10, key=3)
edge_curvatures[('C', 'D', 3)] = 0.3
G.add_edge("D", "E", weight=2, key=4)
edge_curvatures[('D', 'E', 4)] = 0.4
G.add_edge("C", "E", weight=1, key=5)
edge_curvatures[('C', 'E', 5)] = 0
pos = nx.circular_layout(G)
weights = nx.get_edge_attributes(G, 'weight')
edge_styles = [f'arc3,rad={edge_curvatures[edge]}' for edge in G.edges(keys=True)]
nx.draw(G, pos, with_labels=True, node_color='skyblue', edge_color='black', node_size=200, font_size=15, connectionstyle=edge_styles)
nx.draw_networkx_edge_labels(G, pos, edge_labels=weights)
plt.show()
