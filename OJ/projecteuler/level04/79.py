# 样例给的50个三位数中，没有一个三位数出现2位相同的数，也就是三位都不一样
# 才能用拓扑排序做，否则只能用其他算法, 比如加个226这种三位数直接报错
# https://pe.metaquant.org/pe079.html
# ans = 73162890

import networkx as nx

def get_data_from_file(file_name="../data/p079_keylog.txt"):
    data = set()
    with open(file_name) as f:
        for line in f.readlines():
            data.add(line)
    return data

def main():
    data = get_data_from_file()
    G = nx.DiGraph()
    for i in data:
        G.add_edges_from([(i[0],i[1]),(i[1],i[2])])
    ans = list(nx.all_topological_sorts(G))[0]
    print(''.join(ans))

if __name__ == '__main__':
    main()