import re, json, os, html

dest = "C:/Users/VIP/Desktop/contest-362"
jp = "C:/Users/VIP/.claude/projects/c--Users-VIP-Desktop-microterm/d5504b11-1823-4a07-a544-c0ba0f02565a/subagents/workflows/wf_6c14642d-863/journal.jsonl"

journal = {}
with open(jp, 'r', encoding='utf-8') as f:
    for line in f:
        try:
            obj = json.loads(line)
            if obj.get('type') == 'result' and 'result' in obj:
                r = obj['result']
                if 'id' in r and 'thinking' in r:
                    journal[r['id']] = r
        except: pass

def strip_comments(code):
    if not code: return ""
    code = re.sub(r'/\*.*?\*/', '', code, flags=re.DOTALL)
    res = []
    for line in code.split('\n'):
        instr = False; cp = -1
        for i,ch in enumerate(line):
            if ch == '"': instr = not instr
            if not instr and i < len(line)-1 and line[i]=='/' and line[i+1]=='/':
                cp = i; break
        res.append(line[:cp].rstrip() if cp>=0 else line)
    t = '\n'.join(res)
    t = re.sub(r'[ \t]+\n', '\n', t); t = re.sub(r'\n{3,}', '\n\n', t)
    return t.strip()

def md_to_html(md):
    if not md: return ""
    in_code=False; cb=[]; res=[]
    for line in md.split('\n'):
        if line.startswith('```'):
            if in_code:
                res.append('<pre><code>'+html.escape('\n'.join(cb))+'</code></pre>')
                cb=[]; in_code=False
            else: in_code=True; cb=[]
            continue
        if in_code: cb.append(line); continue
        if not line.strip(): continue
        m=re.match(r'^## ([^#].*)',line)
        if m: res.append('<h2>'+m.group(1)+'</h2>'); continue
        m=re.match(r'^### (.*)',line)
        if m: res.append('<h3>'+m.group(1)+'</h3>'); continue
        if re.match(r'^---+$',line): res.append('<hr>'); continue
        res.append(line)
    if in_code and cb:
        res.append('<pre><code>'+'\n'.join(cb)+'</code></pre>')
    return '\n'.join(res)

problems = []
for d in sorted(os.listdir(dest)):
    dp = os.path.join(dest, d)
    if not os.path.isdir(dp): continue
    m = re.match(r'(pLinK[\d.]+)', d)
    if not m: continue
    id_val = m.group(1)
    did = id_val.replace('p', '', 1)
    m2 = re.match(r'pLinK[\d.]+_(.*)', d)
    title = m2.group(1) if m2 else d
    jd = journal.get(id_val) or journal.get(id_val.replace('LinK', 'Link'))
    full_code = ""
    cpp = os.path.join(dp, 'main.cpp')
    if os.path.exists(cpp):
        with open(cpp, 'r', encoding='utf-8') as f:
            full_code = strip_comments(f.read())
    full_problem = ""
    mdp = os.path.join(dp, 'problem.md')
    if os.path.exists(mdp):
        with open(mdp, 'r', encoding='utf-8') as f:
            full_problem = md_to_html(f.read())
    problems.append({
        "id": did, "title": title,
        "thinking": jd['thinking'] if jd else "",
        "code": jd['code'] if jd else "",
        "summary": jd['summary'] if jd else "",
        "fullCode": full_code,
        "fullProblem": full_problem
    })

problems_json = json.dumps(problems, ensure_ascii=False)

html_out = """<!DOCTYPE html>
<html lang="zh-CN">
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<title>Contest 362 - Problem Set</title>
<style>
:root{--bg:#1e1e2e;--bg2:#181825;--card:#252536;--card-h:#2d2d44;--code-bg:#1a1a2e;--text:#cdd6f4;--text2:#a6adc8;--text3:#6c7086;--accent:#89b4fa;--border:#313244;--green:#a6e3a1;--teal:#94e2d5}
*{box-sizing:border-box;margin:0;padding:0}
body{font-family:-apple-system,"PingFang SC","Microsoft YaHei",sans-serif;background:var(--bg);color:var(--text);line-height:1.6}
.header{background:var(--bg2);border-bottom:1px solid var(--border);padding:1.5rem;text-align:center;position:sticky;top:0;z-index:100}
.header h1{font-size:1.5rem;font-weight:700;background:linear-gradient(135deg,var(--accent),var(--green));-webkit-background-clip:text;-webkit-text-fill-color:transparent;margin-bottom:0.25rem}
.header .sub{color:var(--text3);font-size:0.85rem;margin-bottom:0.75rem}
.search-wrap{max-width:500px;margin:0 auto}
.search-wrap input{width:100%;padding:0.6rem 1rem;border-radius:8px;border:1px solid var(--border);background:var(--bg);color:var(--text);font-size:0.9rem;outline:none}
.search-wrap input:focus{border-color:var(--accent)}
.stats{text-align:center;color:var(--text3);font-size:0.8rem;margin-top:0.5rem}
.container{max-width:900px;margin:1rem auto;padding:0 1rem}
.card{background:var(--card);border-radius:10px;margin-bottom:0.75rem;border:1px solid var(--border);overflow:hidden}
.card:hover{border-color:var(--accent)}
.card-header{display:flex;align-items:center;gap:0.75rem;padding:0.85rem 1rem;cursor:pointer;user-select:none}
.card-header .badge{background:var(--accent);color:var(--bg);padding:0.15rem 0.6rem;border-radius:5px;font-size:0.75rem;font-weight:600;font-family:monospace;flex-shrink:0}
.card-header .title{flex:1;font-size:0.95rem;font-weight:500}
.card-header .icon{width:20px;height:20px;transition:transform 0.2s;color:var(--text3);flex-shrink:0}
.card.open .card-header .icon{transform:rotate(180deg)}
.card-body{display:none;padding:0 1rem 1rem}
.card.open .card-body{display:block}
.label{font-size:0.75rem;color:var(--text3);text-transform:uppercase;letter-spacing:0.05em;margin-top:0.75rem;margin-bottom:0.3rem}
.label:first-child{margin-top:0}
.thinking{color:var(--text2);font-size:0.9rem}
.code-wrap{background:var(--code-bg);border-radius:6px;overflow:hidden}
.code-wrap .lang{display:inline-block;background:var(--border);color:var(--text3);padding:0.1rem 0.5rem;font-size:0.7rem;border-radius:0 0 4px 0}
.code-wrap pre{padding:0.75rem;overflow-x:auto;font-size:0.82rem;line-height:1.5;font-family:Consolas,monospace}
.code-wrap code{color:var(--text)}
.summary{color:var(--teal);font-size:0.88rem}
.btns{display:flex;gap:0.5rem;margin-top:0.75rem;flex-wrap:wrap}
.btns button{padding:0.35rem 0.85rem;border:1px solid var(--border);border-radius:6px;background:transparent;color:var(--text2);font-size:0.8rem;cursor:pointer}
.btns button:hover{border-color:var(--accent);color:var(--accent)}
.btns button.on{background:var(--accent);color:var(--bg);border-color:var(--accent)}
.fsec{display:none;margin-top:0.5rem}
.fsec.show{display:block}
.fsec .code-wrap{max-height:400px;overflow-y:auto}
.fsec .mdbox{background:var(--code-bg);border-radius:6px;padding:0.75rem;font-size:0.85rem;max-height:400px;overflow-y:auto;color:var(--text2);line-height:1.7}
.fsec .mdbox h2{color:var(--accent);font-size:1rem;margin:0.5rem 0}
.fsec .mdbox h3{color:var(--green);font-size:0.9rem;margin:0.3rem 0}
.fsec .mdbox pre{background:#111;padding:0.5rem;border-radius:4px;overflow-x:auto;margin:0.3rem 0}
.fsec .mdbox code{background:#111;padding:0.1rem 0.3rem;border-radius:3px;font-size:0.8rem}
.fsec .mdbox img{max-width:100%}
.fsec .mdbox hr{border:none;border-top:1px solid var(--border);margin:0.5rem 0}
.footer{text-align:center;padding:1.5rem;color:var(--text3);font-size:0.8rem}
.empty{text-align:center;padding:3rem;color:var(--text3)}
@media(max-width:600px){.header h1{font-size:1.2rem}.card-header{padding:0.65rem 0.75rem}.card-body{padding:0 0.75rem 0.75rem}}
</style>
</head>
<body>
<div class="header">
<h1>Contest 362 &middot; Problem Set</h1>
<div class="sub">2026程序设计实践例题 &middot; LinK系列</div>
<div class="search-wrap"><input type="text" id="search" placeholder="搜索题号或名称..." autocomplete="off"></div>
<div class="stats">共 <span id="total">0</span> 题</div>
</div>
<main class="container" id="list"></main>
<footer class="footer">Contest 362 &middot; <span id="date"></span></footer>
<script>
var DATA = """ + problems_json + """;

function esc(s){if(!s)return'';var d=document.createElement('div');d.textContent=s;return d.innerHTML;}

function show(list){
  var el=document.getElementById('list'); el.innerHTML='';
  document.getElementById('total').textContent=list.length;
  if(!list.length){el.innerHTML='<div class="empty">没有匹配的题目</div>';return;}
  for(var i=0;i<list.length;i++){
    var p=list[i];
    var card=document.createElement('div'); card.className='card';
    var hdr=document.createElement('div'); hdr.className='card-header';
    hdr.innerHTML='<span class="badge">'+esc(p.id)+'</span><span class="title">'+esc(p.title)+'</span><svg class="icon" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2"><path d="m6 9 6 6 6-6"/></svg>';
    var body=document.createElement('div'); body.className='card-body';
    body.innerHTML='<div class="label">思路</div><div class="thinking">'+esc(p.thinking)+'</div><div class="label">核心代码</div><div class="code-wrap"><span class="lang">C++</span><pre><code>'+esc(p.code)+'</code></pre></div><div class="label">总结</div><div class="summary">'+esc(p.summary)+'</div><div class="btns"><button id="bc-'+i+'">\\u{1F4C4} 查看完整代码</button><button id="bp-'+i+'">\\u{1F4DD} 查看完整题目</button></div><div class="fsec" id="sc-'+i+'"><div class="code-wrap"><span class="lang">C++</span><pre><code>'+esc(p.fullCode)+'</code></pre></div></div><div class="fsec" id="sp-'+i+'"><div class="mdbox"></div></div>';
    card.appendChild(hdr); card.appendChild(body);
    hdr.onclick=function(){this.parentElement.classList.toggle('open');};
    var mbox=body.querySelector('.mdbox');
    mbox.innerHTML=p.fullProblem;
    var bc=document.getElementById('bc-'+i);
    var bp=document.getElementById('bp-'+i);
    var sc=document.getElementById('sc-'+i);
    var sp=document.getElementById('sp-'+i);
    bc.onclick=function(e){e.stopPropagation();sc.classList.toggle('show');this.classList.toggle('on');this.textContent=this.classList.contains('on')?'\\u{1F4C4} 收起完整代码':'\\u{1F4C4} 查看完整代码';};
    bp.onclick=function(e){e.stopPropagation();sp.classList.toggle('show');this.classList.toggle('on');this.textContent=this.classList.contains('on')?'\\u{1F4DD} 收起完整题目':'\\u{1F4DD} 查看完整题目';};
    el.appendChild(card);
  }
}

document.getElementById('search').oninput=function(){
  var q=this.value.toLowerCase().trim();
  if(!q){show(DATA);return;}
  show(DATA.filter(function(p){return p.id.toLowerCase().indexOf(q)>=0||p.title.toLowerCase().indexOf(q)>=0;}));
};
document.getElementById('date').textContent='2026-07-24';
show(DATA);
</script>
</body>
</html>"""

hp = os.path.join(dest, 'index.html')
with open(hp, 'w', encoding='utf-8') as f:
    f.write(html_out)

size = os.path.getsize(hp) / 1024
cnt = html_out.count('"id":"LinK')
print(f"Done! {size:.0f} KB, {cnt} entries")
print(f"InnerHTML present: {'mbox.innerHTML' in html_out}")
