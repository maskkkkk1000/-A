# LinK70 最低通行费

- 比赛：2026年程序设计实践例题(05李胜睿班)
- 题型：OI
- 难度：Low
- 语言：C, C++, Python3

## 题目描述

<p>一个商人穿过一个N×N的正方形的网格，去参加一个非常重要的商务活动。</p><p>他要从网格的左上角进，右下角出。</p><p>每穿越中间1个小方格，都要花费1个单位时间。</p><p>商人必须在(2N - 1)个单位时间穿越出去。</p><p>而在经过中间的每个小方格时，都需要缴纳一定的费用。</p><p>这个商人期望在规定时间内用最少费用穿越出去。</p><p>请问至少需要多少费用？</p><p>注意：不能对角穿越各个小方格（即，只能向上下左右四个方向移动且不能离开网格）。</p>

## 输入描述

<p>第一行是一个整数，表示正方形的宽度N。</p><p>后面N行，每行N个不大于100的正整数，为网格上每个小方格的费用。</p><p><strong>数据范围</strong></p><p>1 ≤ N ≤ 100</p>

## 输出描述

<p>输出一个整数，表示至少需要的费用。</p><p><strong>样例解释</strong></p><p>样例中，最小值为109 = 1 + 2 + 5 + 7 + 9 + 12 + 19 + 21 + 33。</p>

## 样例

### 样例 1

#### 输入

```text
5
1  4  6  8  10
2  5  7  15 17
6  8  9  18 20
10 11 12 19 21
20 23 25 29 33
```

#### 输出

```text
109
```

## 提示

<p><a href="https://www.acwing.com/problem/content/1020/" target="_blank">原题链接</a></p><p><a href="https://www.acwing.com/solution/content/51101/" target="_blank">参考题解</a></p><p><a href="https://www.acwing.com/activity/content/code/content/112797/" target="_blank">Y总代码</a></p><p><a href="https://www.acwing.com/video/353/" target="_blank">Y总讲解</a></p>
