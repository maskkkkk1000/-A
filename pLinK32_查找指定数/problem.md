# LinK32 查找指定数

- 比赛：2026年程序设计实践例题(05李胜睿班)
- 题型：OI
- 难度：Low
- 语言：C, C++, Python3

## 题目描述

<p><span style="color: rgb(73, 80, 96);"><img alt="image.png" src="/public/upload/a653218c64.png" width="662" height="337" /><br /></span></p><p><span style="color: rgb(73, 80, 96);">面对铺面而来的波克布林大军，林克需要快速制胜，所谓擒贼先擒王，林克需要锁定目标一击必杀。</span></p><p><span style="color: rgb(73, 80, 96);">假设怪物大军共有N只波克布林（1&lt;=N&lt;=100000）和数组nums存储每个怪的编号。根据情报，需要击杀的目标编号是</span><span style="color: rgb(73, 80, 96);">target。</span></p><p><span style="color: rgb(73, 80, 96);">请从nums中迅速找出target的数组下标，如果找不到请输出-1.</span></p>

## 输入描述

<p><span style="color: rgb(73, 80, 96);">第一行N表示数组大小。</span></p><p><span style="color: rgb(73, 80, 96);">第二行为nums的N个元素(不包含重复元素)</span></p><p><span style="color: rgb(73, 80, 96);">第三行T表示接下来又T个元素需要查找。</span></p><p><span style="color: rgb(73, 80, 96);">接下来T行，每行为查找的目标元素target值。</span><br /></p>

## 输出描述

<p><span style="color: rgb(73, 80, 96);">输出为T个目标元素的下标，找不到输出-1</span><br /></p>

## 样例

### 样例 1

#### 输入

```text
36
0 1 5 8 10 12 15 17 20 26 36 68 71 80 90 92 96 100 101 104 130 275 345 405 425 519 573 583 608 616 714 780 802 842 910 961 
5
8
42
64
130
912
```

#### 输出

```text
3
-1
-1
20
-1

```

## 提示

<p><a href="https://www.bilibili.com/video/BV1tA41157aa" target="_blank">Andy讲解(2021)</a><br /></p>
