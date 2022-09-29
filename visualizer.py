import sys

import networkx as nx
import matplotlib.pyplot as plt
import matplotlib.animation


# The function to animate moving ants
def update(frame):
    global colors, edge_colors, width, lines, length, i, pos, start, end
    fig.clear()
    if i >= length - 1:
        if kamada_kawai:
            nx.draw_kamada_kawai(g, font_color='white', edge_color=edge_colors, with_labels=True,
                                 width=list(weights), node_size=50)
        else:
            nx.draw(g, pos=pos, font_color='white', edge_color=edge_colors, with_labels=True,
                    width=list(weights), node_size=50)
        fig.set_facecolor("#00000F")
        return

    j = lines[i].split(' ')
    nodes_colored = []
    for x in j:
        x = x.split('-')
        nodes_colored.append(x[1])
        if g.nodes[x[1]]['color'] == 'red':
            g.nodes[x[1]]['color'] = 'yellow'
        else:
            g.nodes[x[1]]['color'] = 'red'

    for n in g.nodes():
        if n in nodes_colored:
            continue
        g.nodes[n]['color'] = 'blue'
    i += 1

    g.nodes[start]['color'] = 'purple'
    g.nodes[end]['color'] = 'purple'

    node_colors = nx.get_node_attributes(g, 'color').values()
    pos = nx.get_node_attributes(g, 'pos')
    if kamada_kawai:
        nx.draw_kamada_kawai(g, font_color='white', edge_color=edge_colors, node_color=node_colors,
                             width=list(weights), node_size=50)
    else:
        nx.draw(g, pos=pos, font_color='white', edge_color=edge_colors, node_color=node_colors,
                width=list(weights), node_size=50)

    fig.set_facecolor("#00000F")


# init Graph and plot
fig = plt.figure()
g = nx.Graph()

# variables initalization
kamada_kawai = True
speed = 1

# read arguments
if '--coord' in sys.argv:
    kamada_kawai = False
if '--fast' in sys.argv:
    speed = 0.1
if '--slow' in sys.argv:
    speed = 10
# check if there is no error in main program
x = input()
if 'Error:' in x:
    print("Error")
    exit(0)

# skip number of ants
while len(x) != 0:
    if x[0].isdigit():
        break
    x = input()

# open and read default nodes and edges
x = input()
while len(x) != 0:
    # x = x.strip()
    if x[0] == '#':
        x = input()
        continue
    elif '-' in x:
        x = x.split('-')
        g.add_edge(x[0], x[1], color='yellow', weight=1)
    else:
        x = x.split(' ')
        g.add_node(x[0], pos=(int(x[1]), int(x[2])), color='blue')
    x = input()

# open and read the found paths
x = input()
while len(x) != 0:
    x = x.strip()
    x = x.split(' ')
    i = len(x)
    j = 0
    while i - 1:
        g.edges[x[j], x[j + 1]]['color'] = 'green'
        g.edges[x[j], x[j + 1]]['weight'] = 4
        i -= 1
        j += 1
    g.nodes[x[0]]['color'] = 'purple'
    g.nodes[x[-1]]['color'] = 'purple'
    start = x[0]
    end = x[-1]
    x = input()

# get and update all attributes to graph
edge_colors = nx.get_edge_attributes(g, 'color').values()
node_colors = nx.get_node_attributes(g, 'color').values()
weights = nx.get_edge_attributes(g, 'weight').values()
pos = nx.get_node_attributes(g, 'pos')

# draw the first plot
if kamada_kawai:
    nx.draw_kamada_kawai(g, edge_color=edge_colors, node_color=node_colors, width=list(weights), node_size=50)
else:
    nx.draw(g, pos=pos, edge_color=edge_colors, node_color=node_colors, width=list(weights), node_size=50)

fig.set_facecolor("#00000F")

# read data from moving ants
# with open('send_ants_carl') as f:
#    lines = [line.rstrip() for line in f]
# f.close()
x = input()
lines = []
while len(x) != 0:
    lines.append(x)
    x = input()

length = len(lines)
i = 0

# animate moving ants
anim = matplotlib.animation.FuncAnimation(fig, update, frames=200, interval=100*speed, repeat=True)

plt.show()