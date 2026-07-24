# LinK58 Dijkstra求最短路(2)

- 比赛：2026年程序设计实践例题(05李胜睿班)
- 题型：OI
- 难度：Mid
- 语言：C, C++, Python3

## 题目描述

<p style="margin-left: 0px;">给定一个n个点m条边的有向图，图中可能存在重边和自环，所有边权均为非负值。</p><p>请你求出1号点到n号点的最短距离，如果无法从1号点走到n号点，则输出-1。</p><p><img alt="image.png" src="/public/upload/eb7a99368d.png" width="286" height="76" /><br /></p>

## 输入描述

<p>第一行包含整数n和m。</p><p>接下来m行每行包含三个整数x，y，z，表示存在一条从点x到点y的有向边，边长为z。</p>

## 输出描述

<p>输出一个整数，表示1号点到n号点的最短距离。</p><p>如果路径不存在，则输出-1。</p>

## 样例

### 样例 1

#### 输入

```text
3 3
1 2 2
2 3 1
1 3 4
```

#### 输出

```text
3
```

## 提示

<p><a href="https://www.acwing.com/problem/content/852/" target="_blank">原题链接</a></p>
