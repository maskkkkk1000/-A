# LinK36 最小预算值

- 内部 ID：7499
- 难度：High
- 类型：OI
- 时间限制：1000ms
- 内存限制：256MB
- 支持语言：C、C++、Python3
- 标签：北大郭炜

---

## 题目描述

<p style="margin-left: 0px;"><img src="http://xmuoj.com/public/upload/efb3594583.png" alt="image.png" /><br /></p><p style="margin-left: 0px;">为了升级希卡之石林克来到了阿卡莱研究所。这个海拉鲁大陆最顶级的研究所，每天都要消耗大量的研究经费，</p><p style="margin-left: 0px;">然而令人惊奇的是这个研究所的经费从不短缺，这完全得益于研究所制定预算的能力。</p><p style="margin-left: 0px;">如果谁能搞清楚阿卡来研究所制定预算的算法，并且给出最佳预算的值，那么他就可以免费升级希卡之石。</p><p style="margin-left: 0px;">林克显然不擅长做预算，作为他好朋友的你，可以出手相助吗？</p><p>已知研究所接下来N天（<span style="color: rgb(73, 80, 96);">1≤N≤ 100,000</span><span style="color: rgb(73, 80, 96);">）</span>每日的固定支出预计为X(N)卢比。</p><p>研究所需要将未来的N天分为M组<span style="color: rgb(73, 80, 96);">(1 ≤M≤N)</span><span style="color: rgb(73, 80, 96);">，</span>每组是1天或者连续的几天。</p><p>（假如第1，2，3天为一组，那么该组的总固定支出Total(1)是这三天的固定支出之和X(0)+X(1)+X(2)）</p><p>请问，如果一定要将未来的N天分为M组，<span style="color: rgb(51, 51, 51);">假设分配给每组的预算是一个固定值Budget，并且</span>不同组所得到的卢比即便有结余也不可以挪用。</p><p>求能够完全满足每组支出需要的最小的<span style="color: rgb(51, 51, 51);">Budget</span>值是多少。</p>

## 输入格式

<p style="margin-left: 0px;"><span style="color: rgb(35, 31, 23);">第一行包含两个整数N,M，用单个空格隔开。</span></p><p><span style="color: rgb(35, 31, 23);">第二行有N个从<span style="color: rgb(35, 31, 23);">1到10000之间的整数，</span>表示接下来N天里每天的固定支出预算。</span></p>


## 输出格式

<p><span style="color: rgb(35, 31, 23);">一个整数，即</span><span style="color: rgb(35, 31, 23);"></span><span style="color: rgb(51, 51, 51);">满足每组支出需要的最小的预算值</span><span style="color: rgb(51, 51, 51);">。</span><br /></p>


## 样例

### 样例输入

```text
7 5
100 400 300 100 500 101 400
```

### 样例输出

```text
500
```

## 提示

<p><span style="color: rgb(51, 51, 51);"><a href="https://www.bilibili.com/video/av94908717?pop_share=1" target="_blank"></a><a href="https://www.bilibili.com/video/av94908717?pop_share=1" target="_blank">Andy讲解(2020)</a><br />本题改编自Guo Wei的《月度开销》</span><br /></p>

