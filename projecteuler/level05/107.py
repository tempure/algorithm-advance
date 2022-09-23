# MST 模板题
# python networkx 直接调用还是挺方便的
# https://pe.metaquant.org/pe107.html
# ans = 259679

import numpy as np
import networkx as nx

def convert_matrix_to_graph():
    with open('../data/p107_network.txt') as f:
        network = []
        for line in f.readlines():
            line = line.replace('-','0').strip()
            network.append([int(x) for x in line.split(',')])
        g = nx.from_numpy_array(np.array(network))
        return g

def main():
    g = convert_matrix_to_graph()
    mst = nx.minimum_spanning_tree(g)
    g_weights = g.size(weight='weight')
    mst_weights = mst.size(weight='weight') # typo fix here
    return int(g_weights-mst_weights)


if __name__ == '__main__':
    print(main())