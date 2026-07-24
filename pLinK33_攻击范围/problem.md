# LinK33 攻击范围

- 内部 ID：7496
- 难度：Mid
- 类型：OI
- 时间限制：1000ms
- 内存限制：256MB
- 支持语言：C、C++、Python3
- 标签：校外实训

---

## 题目描述

<p><img alt="image.png" src="/public/upload/e07c64f4c5.png" width="513" height="284" /><br /></p><p>面对铺面而来的怪物大军，林克需要根据怪物类型进行区域攻击。</p><p>假设怪物大军共有N个怪物（1&lt;=N&lt;=100000），升序数组nums存储每个怪物的编号，同一类型的怪物编号相同。</p><p>根据情报，需要击杀的目标编号是target。</p><p>请从nums中迅速找出编号为target的怪物的数组下标范围。</p><p>如果找不到请输出-1 -1.</p>

## 输入格式

<p>第一行包含整数n和q，表示数组长度和询问个数。</p><p>第二行包含n个整数（均在1~10000范围内），表示完整数组。</p><p>接下来q行，每行包含一个整数k，表示一个询问元素。</p><h4><span style="color: rgb(227, 55, 55);">数据范围<br />1≤n≤100000<br />1≤q≤10000<br />1≤k≤10000</span></h4>


## 输出格式

<p>共q行，每行包含两个整数，表示所求元素的起始位置和终止位置<span style="color: rgb(51, 51, 51);">（位置从0开始计数）</span>。</p><p>如果数组中不存在该元素，则返回“-1 -1”。</p>


## 样例

### 样例输入

```text
6 3
1 2 2 3 3 4
3
4
5
```

### 样例输出

```text
3 4
5 5
-1 -1
```

## 提示

<p style="margin-left: 0px;"><a href="https://www.bilibili.com/video/BV1gi4y1N7XR" target="_blank">Andy讲解(2021)</a></p><p><a href="https://www.acwing.com/problem/content/791/" target="_blank">原题ACW789</a></p>

