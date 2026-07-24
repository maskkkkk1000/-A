# LinK07 三数之和

- 比赛：2026年程序设计实践例题(05李胜睿班)
- 题型：OI
- 难度：Mid
- 语言：C, C++, Python3

## 题目描述

<p>看着小鲁AC了第一题，小华接着提出第二问：<br /></p><p>给定一个目标值 target，请在整数数组 a中，找出三个元素(x,y,z) 使x+y+z==target。<br /></p><p>请找到所有满足条件的三元组，并且请按从小到大的顺序输出所有合法的三元组。</p><p>注意：三元组中不允许包含重复数字，且输出的三元组中要求 x&lt;y&lt;z.</p><p><span style="color: rgb(227, 55, 55);">例如:给定target = 17，n=7, 数组<span style="color: rgb(227, 55, 55);">a= [0, 2, 7, 10, 15,18,25]</span></span></p><p><span style="color: rgb(227, 55, 55);">结果返回两个三元组：(0,2, 15), (</span><span style="color: rgb(227, 55, 55);">2,7,10)</span></p>

## 输入描述

<p>输入数据为2行，第一行有两个整数 target和n，其中target代表要搜索的目标和，n表示数组a的元素个数</p><p>第二行表示数组a的n个数，每个元素用空格隔开。</p>

## 输出描述

<p><span style="color: rgb(73, 80, 96);">输出所有满足和为target的三元组(x,y,z)，要求(x&lt; y &lt;z) 并且不允许有重复数字。</span><br /></p><p><span style="color: rgb(73, 80, 96);">把三元组按照x的大小升序输出，x相同的按照y的大小升序输出。</span></p>

## 样例

### 样例 1

#### 输入

```text
17 7
0 2 7 10 15 18 25 
```

#### 输出

```text
0 2 15
0 7 10
```

## 提示

<p><a href="https://www.bilibili.com/video/BV1mV411v7NW" target="_blank">Andy讲解(2021)</a><br /></p>
