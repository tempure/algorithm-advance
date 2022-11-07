# https://pe.metaquant.org/pe082.html
# 加了一个方向，稍微修改一下状态转移方程即可
# ans = 260324

def min_path_sum(matrix):
    n = len(matrix)
    cost = [matrix[i][0] for i in range(n)]
    for column in range(1,n):
        cost[0] += matrix[0][column]
        for row in range(1,n):
            cost[row] = min(cost[row], cost[row-1]) + matrix[row][column]
        for row in range(n-2, -1, -1):
            cost[row] = min(cost[row], cost[row+1] + matrix[row][column])
    return min(cost)

def main():
    with open('../data/p082_matrix.txt') as f:
        matrix = [[int(x) for x in row.split(',')] for row in f.readlines()]
    print(min_path_sum(matrix))


if __name__ == '__main__':
    main()
