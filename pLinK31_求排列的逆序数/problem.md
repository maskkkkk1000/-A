# LinK31 求排列的逆序数

- 内部 ID：7494
- 难度：High
- 类型：OI
- 时间限制：1000ms
- 内存限制：256MB
- 支持语言：C、C++、Python3
- 标签：校外实训

---

## 题目描述

<p>在Internet上的搜索引擎经常需要对信息进行比较，比如可以通过某个人对一些事物的排名来估计他（或她）对各种不同信息的兴趣，从而实现个性化的服务。</p><p>对于不同的排名结果可以用逆序来评价它们之间的差异。考虑1,2,…,n的排列i1，i2，…，in，如果其中存在j,k，满足 j &lt; k 且ij&gt; ik， 那么就称(ij,ik)是这个排列的一个逆序。</p><p>一个排列含有逆序的个数称为这个排列的逆序数。</p><p>例如排列 263451 含有8个逆序(2,1),(6,3),(6,4),(6,5),(6,1),(3,1),(4,1),(5,1)，因此该排列的逆序数就是8。</p><p>显然，由1,2,…,n 构成的所有n!个排列中，最小的逆序数是0，对应的排列就是1,2,…,n；最大的逆序数是n(n-1)/2，对应的排列就是n,(n-1),…,2,1。</p><p>逆序数越大的排列与原始排列的差异度就越大。</p><p>现给定1,2,…,n的一个排列，求它的逆序数。</p>

## 输入格式

<p><span style="color: rgb(35, 31, 23);">第一行是一个整数n，表示该排列有n个数（n &lt;= 100000)。</span></p><p><span style="color: rgb(35, 31, 23);">第二行是n个不同的正整数，之间以空格隔开，表示该排列。</span></p>


## 输出格式

<p><span style="color: rgb(35, 31, 23);">输出该排列的逆序数。</span><br /></p>


## 样例

### 样例输入

```text
6
2 6 3 4 5 1
```

### 样例输出

```text
8
```

## 提示

<p style="margin-left: 0px;"><a href="https://www.bilibili.com/video/BV14X4y1G77n" target="_blank">Andy讲解(2021)</a><br /></p><p><a href="https://www.bilibili.com/video/av95376969" target="_blank">Andy的讲解(2020)</a></p><p>逆序数可能很多，使用long long存储</p><p><a href="https://www.acwing.com/problem/content/790/" target="_blank">原题链接</a></p>


## 测试数据

- 测试点 1：1.in / 1.out
- 测试点 2：2.in / 2.out
- 测试点 3：3.in / 3.out
- 测试点 4：4.in / 4.out
- 测试点 5：5.in / 5.out
- 测试点 6：6.in / 6.out
- 测试点 7：7.in / 7.out
- 测试点 8：8.in / 8.out
- 测试点 9：9.in / 9.out
- 测试点 10：10.in / 10.out

[下载测试数据](/api/dl_test_case?problem_id=7494)
