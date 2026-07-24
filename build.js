const fs = require('fs');
const path = require('path');

// ── Data ──────────────────────────────────────────────────────────────────────
const all = require('./all_problems.json');
const problems = Object.values(all);

// Validate
if (problems.length !== 78) {
  console.error(`Expected 78 problems, got ${problems.length}`);
  process.exit(1);
}
const required = ['id','title','thinking','code','summary','fullCode','fullProblem'];
problems.forEach((p, i) => {
  for (const k of required) {
    if (typeof p[k] !== 'string') {
      console.error(`Problem ${i} missing field '${k}'`);
      process.exit(1);
    }
  }
});

const DATA_JSON = JSON.stringify(problems)
  // Escape </script> sequences that would break the HTML parser
  .replace(/<\//g, '<\\/');

// ── Build HTML ────────────────────────────────────────────────────────────────
const html = `<!DOCTYPE html>
<html lang="zh-CN">
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width,initial-scale=1.0">
<title>程序设计实践A</title>
<style>
:root {
  --bg: #F7F6F3;
  --surface: #FFF;
  --border: #EAEAEA;
  --text: #2F3437;
  --text2: #787774;
  --text3: #B0AEAA;
  --accent: #1F6C9F;
  --accent-bg: #E1F3FE;
  --code-bg: #F3F3F1;
}
* { box-sizing: border-box; margin: 0; padding: 0; }
body {
  font-family: "SF Pro Display", "Helvetica Neue", -apple-system, sans-serif;
  background: var(--bg);
  color: var(--text);
  line-height: 1.6;
  -webkit-font-smoothing: antialiased;
}
.header {
  background: var(--surface);
  border-bottom: 1px solid var(--border);
  padding: 2.5rem 1.5rem 1.5rem;
  text-align: center;
  position: sticky;
  top: 0;
  z-index: 100;
}
.header h1 {
  font-size: 1.4rem;
  font-weight: 600;
  letter-spacing: -0.02em;
  color: var(--text);
  margin-bottom: 0.2rem;
}
.header .sub {
  color: var(--text2);
  font-size: 0.85rem;
  margin-bottom: 1rem;
}
.search-wrap {
  max-width: 480px;
  margin: 0 auto;
}
.search-wrap input {
  width: 100%;
  padding: 0.65rem 1rem;
  border-radius: 8px;
  border: 1px solid var(--border);
  background: var(--bg);
  color: var(--text);
  font-size: 0.9rem;
  outline: none;
  font-family: inherit;
}
.search-wrap input:focus { border-color: var(--text3); }
.stats {
  text-align: center;
  color: var(--text3);
  font-size: 0.75rem;
  margin-top: 0.5rem;
}
.container {
  max-width: 860px;
  margin: 1.5rem auto;
  padding: 0 1rem;
}
.card {
  background: var(--surface);
  border: 1px solid var(--border);
  border-radius: 8px;
  margin-bottom: 0.5rem;
  opacity: 0;
  transform: translateY(12px);
  transition: opacity 0.5s cubic-bezier(0.16,1,0.3,1), transform 0.5s cubic-bezier(0.16,1,0.3,1);
}
.card.visible {
  opacity: 1;
  transform: translateY(0);
}
.card:hover { box-shadow: 0 2px 8px rgba(0,0,0,0.04); }
.card-header {
  display: flex;
  align-items: center;
  gap: .75rem;
  padding: .9rem 1.25rem;
  cursor: pointer;
  user-select: none;
}
.card-header .badge {
  background: var(--accent-bg);
  color: var(--accent);
  padding: .1rem .55rem;
  border-radius: 9999px;
  font-size: .7rem;
  font-weight: 500;
  font-family: "SF Mono", "JetBrains Mono", monospace;
  flex-shrink: 0;
}
.card-header .title {
  flex: 1;
  font-size: .9rem;
  font-weight: 500;
  color: var(--text);
}
.card-header .icon {
  width: 18px;
  height: 18px;
  color: var(--text3);
  flex-shrink: 0;
  transition: transform .2s;
}
.card.open .card-header .icon { transform: rotate(180deg); }
.card-body { display: none; padding: 0 1.25rem 1.25rem; }
.card.open .card-body { display: block; }
.label {
  font-size: .65rem;
  color: var(--text3);
  text-transform: uppercase;
  letter-spacing: .06em;
  margin-top: .9rem;
  margin-bottom: .3rem;
}
.thinking {
  color: var(--text2);
  font-size: .88rem;
  line-height: 1.6;
}
.code-wrap {
  background: var(--code-bg);
  border-radius: 6px;
  border: 1px solid var(--border);
  overflow: hidden;
}
.code-wrap pre {
  padding: .8rem;
  overflow-x: auto;
  font-size: .78rem;
  line-height: 1.6;
  font-family: "SF Mono", "JetBrains Mono", monospace;
  color: var(--text);
}
.summary {
  color: var(--accent);
  font-size: .85rem;
}
.btns {
  display: flex;
  gap: .5rem;
  margin-top: .75rem;
  flex-wrap: wrap;
}
.btns button {
  padding: .35rem .8rem;
  border: 1px solid var(--border);
  border-radius: 6px;
  background: transparent;
  color: var(--text2);
  font-size: .78rem;
  cursor: pointer;
  font-family: inherit;
  transition: all .15s;
  display: inline-flex;
  align-items: center;
}
.btns button:hover {
  border-color: var(--accent);
  color: var(--accent);
  background: var(--accent-bg);
}
.btns button.on {
  background: var(--accent-bg);
  color: var(--accent);
  border-color: var(--accent);
}
.btns button svg {
  width: 14px;
  height: 14px;
  margin-right: 4px;
  flex-shrink: 0;
}
.fsec { display: none; margin-top: .5rem; }
.fsec.show { display: block; }
.fsec .code-wrap { max-height: 420px; overflow-y: auto; }
.fsec .mdbox {
  background: var(--code-bg);
  border-radius: 6px;
  border: 1px solid var(--border);
  padding: .8rem;
  font-size: .82rem;
  max-height: 420px;
  overflow-y: auto;
  color: var(--text2);
  line-height: 1.7;
}
.fsec .mdbox h2 { font-size: 1rem; font-weight: 600; margin: .5rem 0 .25rem; color: var(--text); }
.fsec .mdbox h3 { font-size: .9rem; font-weight: 500; margin: .3rem 0 .2rem; color: var(--text); }
.fsec .mdbox pre { background: var(--surface); border: 1px solid var(--border); padding: .5rem; border-radius: 4px; overflow-x: auto; margin: .3rem 0; }
.fsec .mdbox code { background: var(--surface); border: 1px solid var(--border); padding: .1rem .3rem; border-radius: 3px; font-size: .78rem; font-family: "SF Mono", monospace; }
.fsec .mdbox img { max-width: 100%; border-radius: 4px; }
.fsec .mdbox hr { border: none; border-top: 1px solid var(--border); margin: .5rem 0; }
.footer {
  text-align: center;
  padding: 2rem;
  color: var(--text3);
  font-size: .75rem;
}
.empty {
  text-align: center;
  padding: 3rem;
  color: var(--text3);
}
</style>
</head>
<body>

<div class="header">
  <h1>
    <svg width="22" height="22" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="1.5" style="vertical-align:-3px;margin-right:6px">
      <path d="M12 2L2 7l10 5 10-5-10-5z"/>
      <path d="M2 17l10 5 10-5"/>
      <path d="M2 12l10 5 10-5"/>
    </svg>
    程序设计实践A
  </h1>
  <div class="sub">Problem Set &mdash; 78 problems</div>
  <div class="search-wrap">
    <input id="search" type="text" placeholder="Search by ID or title..." autocomplete="off">
  </div>
  <div class="stats"><span id="count">78</span> / 78 problems</div>
</div>

<div id="container" class="container"></div>

<div class="footer">
  <svg width="14" height="14" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="1.5" style="vertical-align:-2px;margin-right:4px">
    <path d="M12 2L2 7l10 5 10-5-10-5z"/>
    <path d="M2 17l10 5 10-5"/>
    <path d="M2 12l10 5 10-5"/>
  </svg>
  程序设计实践A &mdash; Problem Set
</div>

<script>
var DATA = ${DATA_JSON};

function esc(s) {
  var d = document.createElement('div');
  d.appendChild(document.createTextNode(s));
  return d.innerHTML;
}

function render(list) {
  var container = document.getElementById('container');
  container.innerHTML = '';
  var fragment = document.createDocumentFragment();
  for (var i = 0; i < list.length; i++) {
    (function(idx) {
      var p = list[idx];

      var card = document.createElement('div');
      card.className = 'card';

      // Card header
      var header = document.createElement('div');
      header.className = 'card-header';

      var badge = document.createElement('span');
      badge.className = 'badge';
      badge.textContent = p.id;

      var titleSpan = document.createElement('span');
      titleSpan.className = 'title';
      titleSpan.textContent = p.title;

      var iconSvg = document.createElementNS('http://www.w3.org/2000/svg', 'svg');
      iconSvg.setAttribute('class', 'icon');
      iconSvg.setAttribute('viewBox', '0 0 24 24');
      iconSvg.setAttribute('fill', 'none');
      iconSvg.setAttribute('stroke', 'currentColor');
      iconSvg.setAttribute('stroke-width', '1.5');
      var iconPath = document.createElementNS('http://www.w3.org/2000/svg', 'path');
      iconPath.setAttribute('d', 'M6 9l6 6 6-6');
      iconSvg.appendChild(iconPath);

      header.appendChild(badge);
      header.appendChild(titleSpan);
      header.appendChild(iconSvg);

      // Card body
      var body = document.createElement('div');
      body.className = 'card-body';

      // 思路
      var label1 = document.createElement('div');
      label1.className = 'label';
      label1.textContent = '思路';
      var thinking = document.createElement('div');
      thinking.className = 'thinking';
      thinking.textContent = p.thinking;

      // 关键代码
      var label2 = document.createElement('div');
      label2.className = 'label';
      label2.textContent = '关键代码';
      var codeWrap = document.createElement('div');
      codeWrap.className = 'code-wrap';
      var pre = document.createElement('pre');
      var code = document.createElement('code');
      code.textContent = p.code;
      pre.appendChild(code);
      codeWrap.appendChild(pre);

      // 总结
      var label3 = document.createElement('div');
      label3.className = 'label';
      label3.textContent = '总结';
      var summary = document.createElement('div');
      summary.className = 'summary';
      summary.textContent = p.summary;

      body.appendChild(label1);
      body.appendChild(thinking);
      body.appendChild(label2);
      body.appendChild(codeWrap);
      body.appendChild(label3);
      body.appendChild(summary);

      // Buttons
      var btns = document.createElement('div');
      btns.className = 'btns';

      // 查看完整代码 button
      var btnCode = document.createElement('button');
      var btnCodeSvg = document.createElementNS('http://www.w3.org/2000/svg', 'svg');
      btnCodeSvg.setAttribute('viewBox', '0 0 24 24');
      btnCodeSvg.setAttribute('fill', 'none');
      btnCodeSvg.setAttribute('stroke', 'currentColor');
      btnCodeSvg.setAttribute('stroke-width', '1.5');
      var btnCodePath = document.createElementNS('http://www.w3.org/2000/svg', 'path');
      btnCodePath.setAttribute('d', 'M10 20l4-16m4 4l4 4-4 4M6 16l-4-4 4-4');
      btnCodeSvg.appendChild(btnCodePath);
      btnCode.appendChild(btnCodeSvg);
      var btnCodeSpan = document.createElement('span');
      btnCodeSpan.textContent = '查看完整代码';
      btnCode.appendChild(btnCodeSpan);

      // 查看完整题目 button
      var btnProb = document.createElement('button');
      var btnProbSvg = document.createElementNS('http://www.w3.org/2000/svg', 'svg');
      btnProbSvg.setAttribute('viewBox', '0 0 24 24');
      btnProbSvg.setAttribute('fill', 'none');
      btnProbSvg.setAttribute('stroke', 'currentColor');
      btnProbSvg.setAttribute('stroke-width', '1.5');
      var btnProbPath = document.createElementNS('http://www.w3.org/2000/svg', 'path');
      btnProbPath.setAttribute('d', 'M4 6h16M4 12h16M4 18h12');
      btnProbSvg.appendChild(btnProbPath);
      btnProb.appendChild(btnProbSvg);
      var btnProbSpan = document.createElement('span');
      btnProbSpan.textContent = '查看完整题目';
      btnProb.appendChild(btnProbSpan);

      btns.appendChild(btnCode);
      btns.appendChild(btnProb);
      body.appendChild(btns);

      // Full code section (hidden)
      var fsecCode = document.createElement('div');
      fsecCode.className = 'fsec';
      fsecCode.id = 'sc-' + idx;
      var codeWrap2 = document.createElement('div');
      codeWrap2.className = 'code-wrap';
      var pre2 = document.createElement('pre');
      var code2 = document.createElement('code');
      code2.id = 'cc-' + idx;
      code2.textContent = p.fullCode;
      pre2.appendChild(code2);
      codeWrap2.appendChild(pre2);
      fsecCode.appendChild(codeWrap2);
      body.appendChild(fsecCode);

      // Full problem section (hidden)
      var fsecProb = document.createElement('div');
      fsecProb.className = 'fsec';
      fsecProb.id = 'sp-' + idx;
      var mdbox = document.createElement('div');
      mdbox.className = 'mdbox';
      mdbox.id = 'mp-' + idx;
      mdbox.innerHTML = p.fullProblem;
      fsecProb.appendChild(mdbox);
      body.appendChild(fsecProb);

      card.appendChild(header);
      card.appendChild(body);

      // Toggle card open/close
      header.onclick = function() {
        card.classList.toggle('open');
      };

      // Toggle full code
      btnCode.onclick = function(e) {
        e.stopPropagation();
        var codeSection = document.getElementById('sc-' + idx);
        codeSection.classList.toggle('show');
        btnCode.classList.toggle('on');
        btnCodeSpan.textContent = btnCode.classList.contains('on') ? '收起完整代码' : '查看完整代码';
      };

      // Toggle full problem
      btnProb.onclick = function(e) {
        e.stopPropagation();
        var probSection = document.getElementById('sp-' + idx);
        probSection.classList.toggle('show');
        btnProb.classList.toggle('on');
        btnProbSpan.textContent = btnProb.classList.contains('on') ? '收起完整题目' : '查看完整题目';
      };

      fragment.appendChild(card);
    })(i);
  }
  container.appendChild(fragment);

  // Staggered fadeUp animation
  var cards = container.querySelectorAll('.card');
  for (var j = 0; j < cards.length; j++) {
    (function(card, delay) {
      setTimeout(function() {
        card.classList.add('visible');
      }, delay);
    })(cards[j], j * 60);
  }

  document.getElementById('count').textContent = list.length;
}

// Search input handler
document.getElementById('search').oninput = function() {
  var q = this.value.toLowerCase().trim();
  if (!q) {
    render(DATA);
    return;
  }
  var filtered = DATA.filter(function(p) {
    return p.id.toLowerCase().indexOf(q) >= 0 || p.title.toLowerCase().indexOf(q) >= 0;
  });
  render(filtered);
};

// Initial render
render(DATA);
</script>
</body>
</html>`;

// ── Write ─────────────────────────────────────────────────────────────────────
const outPath = path.resolve(__dirname, 'index.html');
fs.writeFileSync(outPath, html, 'utf8');
const size = fs.statSync(outPath).size;
console.log(`Written ${outPath} (${size} bytes, ${(size / 1024).toFixed(1)} KB)`);

// Quick verification
const content = fs.readFileSync(outPath, 'utf8');
const dataStart = content.indexOf('var DATA = [');
const dataEnd = content.indexOf('];', dataStart);
console.log('DATA JSON length:', dataEnd - dataStart - 11, 'chars');

// Verify the JSON parses
const jsonStr = content.substring(dataStart + 11, dataEnd + 1);
const parsed = JSON.parse(jsonStr);
console.log('Parsed problems:', parsed.length);
console.log('First:', parsed[0].id, parsed[0].title);
console.log('Last:', parsed[parsed.length - 1].id, parsed[parsed.length - 1].title);
