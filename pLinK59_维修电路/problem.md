# LinK59 维修电路

- 内部 ID：7522
- 难度：Mid
- 类型：OI
- 时间限制：1000ms
- 内存限制：256MB
- 支持语言：C、C++、Python3
- 标签：校外实训

---

## 题目描述

<p><span style="color: rgb(51, 51, 51);"><img alt="image.png" src="/public/upload/506795aaeb.png" width="554" height="311" /><br /></span></p><p><span style="color: rgb(51, 51, 51);">林克的大师摩托的飞行装置被撞坏了，极度影响他的卡丁车比赛。下图是飞行装置的</span>电路板示意图。</p><p>电路板的整体结构是一个R行C列的网格（R,C≤500）</p><p><span style="color: rgb(51, 51, 51);"><img src="https://www.acwing.com/media/article/image/2019/01/16/19_be6ff7a219-%E7%94%B5%E8%B7%AF.png" alt="电路.png" /><br /></span></p><p>每个格点都是电线的接点，每个格子都包含一个电子元件。</p><p>电子元件的主要部分是一个<span style="color: rgb(227, 55, 55);">可旋转</span>的、连接一条对角线上的两个接点的短电缆。</p><p>在旋转之后，它就可以连接另一条对角线的两个接点。</p><p>电路板左上角的接点接入直流电源，右下角的接点接入飞行车的发动装置。</p><p>林克发现因为某些元件的方向不小心发生了改变，电路板可能处于断路的状态。</p><p>请问如何旋转最少数量的元件，使电源与发动装置重新连同在一起呢？</p><p>注意：电流只能通过斜向的线段，水平和竖直线段不是电线。</p><p><br /></p><p>提示：<span style="color: rgb(51, 51, 51);">只需要按照下面的方式旋转标准件，就可以使得电源和发动机之间连通。</span></p><p><img src="https://www.acwing.com/media/article/image/2019/01/16/19_a0e8e80a19-%E7%94%B5%E8%B7%AF2.png" alt="电路2.png" /><br /></p>

## 输入格式

<p>输入文件包含多组测试数据。</p><p>第一行包含一个整数T，表示测试数据的数目。</p><p>对于每组测试数据，第一行包含正整数R和C，表示电路板的行数和列数。</p><p>之后R行，每行C个字符，字符是<code>&quot;/&quot;</code>和<code>&quot;\&quot;</code>中的一个，表示标准件的方向。</p><h4><b>数据范围</b></h4><p><img alt="image.png" src="/public/upload/cc98c64485.png" width="182" height="65" /></p>


## 输出格式

<p>对于每组测试数据，在单独的一行输出一个正整数，表示所需的最小旋转次数。</p><p>如果无论怎样都不能使得电源和发动机之间连通，输出NO SOLUTION。</p>


## 样例

### 样例输入

```text
1
3 5
\\/\\
\\///
/\\\\
```

### 样例输出

```text
1
```

## 提示

<p style="margin-left: 0px;"><a href="https://www.bilibili.com/video/BV1mC4y1W7Zr" target="_blank">Andy讲解</a></p><p><a href="https://www.acwing.com/problem/content/video/177/" target="_blank">ACWing讲解</a></p><p>改编自《电路维修》</p>

