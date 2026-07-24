# LinK61 最省赛程

- 内部 ID：7524
- 难度：High
- 类型：OI
- 时间限制：5000ms
- 内存限制：256MB
- 支持语言：C、C++、Python3
- 标签：校外实训

---

## 题目描述

<p style="margin-left: 0px;"><img alt="image.png" src="/public/upload/4af77a00ff.png" width="388" height="216" /><br /></p><p style="margin-left: 0px;">为了让自己能够驾驭大师摩托，打开了大师摩托的隐藏任务：“赛车试炼”。</p><p style="margin-left: 0px;">然而这个特殊的赛车试炼，竟然比的不是车速，比的是如何“省”油钱。</p><p style="margin-left: 0px;">林克需要驾驶不同邮箱容量各异的赛车，从起点城市S开到终点城市E。</p><p style="margin-left: 0px;">有N个城市（编号0、1…N-1）和M条赛道(构成一张无向图)。<br /></p><p>在每个城市里边都有一个加油站，不同的加油站的单位油价不一样(有些城市油价贵，有些城市油价便宜些)。</p><p>请计算，如果林克驾驶的是一辆油箱容量为C的赛车，那么他从起点城市S开到终点城市E至少要花多少油钱？<br /></p><p><span style="color: rgb(51, 51, 51);">注意：</span><span style="color: rgb(51, 51, 51);">车子初始时油箱是空的，需要在起点城市加油方可起行。</span><br /></p>

## 输入格式

<p>第一行包含两个整数N和M。</p><p>第二行包含N个整数，代表N个城市的单位油价，第i个数即为第i个城市的油价Pi。</p><p>接下来M行，每行包括三个整数u,v,d，表示城市u与城市v之间存在道路，且赛车从u到v需要消耗的油量为d。</p><p>接下来一行包含一个整数q，代表问题数量（q&lt;100)</p><p>接下来q行，每行包含三个整数C、S、E，分别表示<span style="color: rgb(51, 51, 51);">赛车</span>油箱容量、起点城市S、终点城市E。</p><p><b>数据范围：</b></p><p><img alt="image.png" src="/public/upload/e861511252.png" width="150" height="120.33203125" /><br /></p>


## 输出格式

<p>对于每个问题，输出一个整数，表示所需的最少油钱。</p><p>如果无法从起点城市开到终点城市，则输出”impossible”。</p><p>每个结果占一行。</p>


## 样例

### 样例输入

```text
5 5
10 10 20 12 13
0 1 9
0 2 8
1 2 1
1 3 11
2 3 7
2
10 0 3
20 1 4
```

### 样例输出

```text
170
impossible
```

## 提示

<p style="margin-left: 0px;"><a href="https://www.bilibili.com/video/BV1sf4y1m7V5" target="_blank">Andy讲解</a></p><p><a href="https://www.acwing.com/problem/content/video/178/" target="_blank">ACWing讲解</a></p><p>改变自《装满的油箱》</p>

