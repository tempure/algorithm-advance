# https://pe.metaquant.org/pe083.html
# 不满足无后效性，不能DP, 直接求最短路
# ans = 425185

import networkx as nx

def main():
    with open('../data/p083_matrix.txt') as f:
        matrix = [[int(x) for x in row.split(',')] for row in f.readlines()]
    G = nx.DiGraph()
    n = len(matrix)
    m = len(matrix[0])
    for i in range(n):
        for j in range(m):
            neighbors = [(i+x, j+y) for x, y in [(-1,0), (0,-1), (1,0), (0,1)] if 0 <= i+x < n and 0 <= j+y < m]
            for ix, jy in neighbors:
                G.add_edge((i, j), (ix, jy), weight = matrix[ix][jy])
    path_length = nx.dijkstra_path_length(G, source=(0,0), target=(n-1,m-1))
    return path_length + matrix[0][0]

if __name__ == '__main__':
    print(main())