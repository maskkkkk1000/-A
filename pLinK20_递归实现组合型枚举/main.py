def dfs(u: int, start: int):
    """当前选到第 u 个位置，从数字 start 开始尝试"""
    if u > m:
        # 已选满 m 个数，输出当前方案
        print(' '.join(map(str, path[1:])))
        return
    for i in range(start, n + 1):
        path[u] = i
        dfs(u + 1, i + 1)   # 下一个位置只能选更大的数


if __name__ == '__main__':
    n, m = map(int, input().split())
    path = [0] * (m + 1)    # path[1..m] 存放当前选的 m 个数
    dfs(1, 1)
