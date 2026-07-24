import json, os, re, html as htmlmod

dest = r"C:\Users\VIP\Desktop\contest-362"
jp = r"C:\Users\VIP\.claude\projects\c--Users-VIP-Desktop-microterm\d5504b11-1823-4a07-a544-c0ba0f02565a\subagents/workflows/wf_cb8f4431-456/journal.jsonl"

# Load improved data from workflow journal
improved = {}
with open(jp, 'r', encoding='utf-8') as f:
    for line in f:
        try:
            obj = json.loads(line)
            if obj.get('type') == 'result':
                res = obj.get('result', {})
                if isinstance(res, dict) and 'problems' in res:
                    for p in res['problems']:
                        pid = p.get('id', '')
                        improved[pid] = {
                            'thinking': p.get('thinking', ''),
                            'code': p.get('code', ''),
                            'summary': p.get('summary', '')
                        }
        except:
            pass
print(f"Improved data: {len(improved)} entries")

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
    t = '\n'.join(res); t = re.sub(r'[ \t]+\n', '\n', t); t = re.sub(r'\n{3,}', '\n\n', t)
    return t.strip()

def md_to_html(md):
    if not md: return ""
    in_code=False; cb=[]; res=[]
    for line in md.split('\n'):
        if line.startswith('```'):
            if in_code:
                res.append('<pre><code>'+htmlmod.escape('\n'.join(cb))+'</code></pre>')
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

    # Try to get improved data by dir name first, then by short ID
    imp = improved.get(d) or improved.get(did) or improved.get(id_val) or {}
    thinking = imp.get('thinking', '').replace('"', "'")
    code = imp.get('code', '').replace('"', "'")
    summary = imp.get('summary', '').replace('"', "'")

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
        "thinking": thinking, "code": code, "summary": summary,
        "fullCode": full_code, "fullProblem": full_problem
    })

data_json = json.dumps(problems, ensure_ascii=False)
json.loads(data_json)  # validate

# Count how many have non-empty improved text
has_imp = sum(1 for p in problems if p['thinking'])
print(f"Problems: {len(problems)}, with improved text: {has_imp}")

# HTML template
HTML_TEMPLATE = r"""<!DOCTYPE html>
<html lang="zh-CN">
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<title>程序设计实践A &mdash; Problem Set</title>
<style>
:root{--bg:#F7F6F3;--surface:#FFF;--border:#EAEAEA;--text:#2F3437;--text2:#787774;--text3:#B0AEAA;--accent:#1F6C9F;--accent-bg:#E1F3FE;--code-bg:#F3F3F1;--tag-green:#EDF3EC;--tag-green-text:#346538}
*{box-sizing:border-box;margin:0;padding:0}
body{font-family:'SF Pro Display','Helvetica Neue',-apple-system,sans-serif;background:var(--bg);color:var(--text);line-height:1.6;-webkit-font-smoothing:antialiased}
.header{background:var(--surface);border-bottom:1px solid var(--border);padding:2.5rem 1.5rem 1.5rem;text-align:center;position:sticky;top:0;z-index:100}
.header h1{font-size:1.4rem;font-weight:600;letter-spacing:-0.02em;color:var(--text);margin-bottom:0.2rem}
.header .sub{color:var(--text2);font-size:0.85rem;margin-bottom:1rem}
.search-wrap{max-width:480px;margin:0 auto}
.search-wrap input{width:100%;padding:0.65rem 1rem;border-radius:8px;border:1px solid var(--border);background:var(--bg);color:var(--text);font-size:0.9rem;outline:none;font-family:inherit}
.search-wrap input:focus{border-color:var(--text3)}
.stats{text-align:center;color:var(--text3);font-size:0.75rem;margin-top:0.5rem}
.container{max-width:860px;margin:1.5rem auto;padding:0 1rem}
.card{background:var(--surface);border:1px solid var(--border);border-radius:8px;margin-bottom:0.5rem;animation:fadeUp .6s cubic-bezier(0.16,1,0.3,1) both}
.card:hover{box-shadow:0 2px 8px rgba(0,0,0,0.04)}
.card-header{display:flex;align-items:center;gap:.75rem;padding:.9rem 1.25rem;cursor:pointer;user-select:none}
.card-header .badge{background:var(--accent-bg);color:var(--accent);padding:.1rem .55rem;border-radius:9999px;font-size:.7rem;font-weight:500;font-family:'SF Mono','JetBrains Mono',monospace;flex-shrink:0}
.card-header .title{flex:1;font-size:.9rem;font-weight:500;color:var(--text)}
.card-header .icon{width:18px;height:18px;color:var(--text3);flex-shrink:0;transition:transform .2s}
.card.open .card-header .icon{transform:rotate(180deg)}
.card-body{display:none;padding:0 1.25rem 1.25rem}
.card.open .card-body{display:block}
.label{font-size:.65rem;color:var(--text3);text-transform:uppercase;letter-spacing:.06em;margin-top:.9rem;margin-bottom:.3rem}
.label:first-child{margin-top:0}
.thinking{color:var(--text2);font-size:.88rem;line-height:1.6}
.code-wrap{background:var(--code-bg);border-radius:6px;border:1px solid var(--border);overflow:hidden}
.code-wrap pre{padding:.8rem;overflow-x:auto;font-size:.78rem;line-height:1.6;font-family:'SF Mono','JetBrains Mono',monospace;color:var(--text)}
.summary{color:var(--tag-green-text);font-size:.85rem}
.btns{display:flex;gap:.5rem;margin-top:.75rem;flex-wrap:wrap}
.btns button{padding:.35rem .8rem;border:1px solid var(--border);border-radius:6px;background:transparent;color:var(--text2);font-size:.78rem;cursor:pointer;font-family:inherit;transition:all .15s;display:inline-flex;align-items:center}
.btns button:hover{border-color:var(--accent);color:var(--accent);background:var(--accent-bg)}
.btns button.on{background:var(--accent-bg);color:var(--accent);border-color:var(--accent)}
.btns button svg{width:14px;height:14px;margin-right:4px;flex-shrink:0}
.fsec{display:none;margin-top:.5rem}
.fsec.show{display:block}
.fsec .code-wrap{max-height:420px;overflow-y:auto}
.fsec .mdbox{background:var(--code-bg);border-radius:6px;border:1px solid var(--border);padding:.8rem;font-size:.82rem;max-height:420px;overflow-y:auto;color:var(--text2);line-height:1.7}
.fsec .mdbox h2{font-size:1rem;font-weight:600;margin:.5rem 0 .25rem;color:var(--text)}
.fsec .mdbox h3{font-size:.9rem;font-weight:500;margin:.3rem 0 .2rem;color:var(--text)}
.fsec .mdbox pre{background:var(--surface);border:1px solid var(--border);padding:.5rem;border-radius:4px;overflow-x:auto;margin:.3rem 0}
.fsec .mdbox code{background:var(--surface);border:1px solid var(--border);padding:.1rem .3rem;border-radius:3px;font-size:.78rem;font-family:'SF Mono',monospace}
.fsec .mdbox img{max-width:100%;border-radius:4px}
.fsec .mdbox hr{border:none;border-top:1px solid var(--border);margin:.5rem 0}
.footer{text-align:center;padding:2rem;color:var(--text3);font-size:.75rem}
.empty{text-align:center;padding:3rem;color:var(--text3)}
@keyframes fadeUp{from{opacity:0;transform:translateY(12px)}to{opacity:1;transform:translateY(0)}}
</style>
</head>
<body>
<div class="header">
<h1>程序设计实践A</h1>
<div class="sub">Problem Set &mdash; 2026</div>
<div class="search-wrap"><input type="text" id="search" placeholder="Search by ID or title..." autocomplete="off"></div>
<div class="stats"><span id="total">0</span> problems</div>
</div>
<main class="container" id="list"></main>
<footer class="footer">程序设计实践A &middot; Problem Set</footer>
<script>
var DATA = """ + data_json + """;

function esc(s){if(!s)return'';var d=document.createElement('div');d.textContent=s;return d.innerHTML;}
function render(list){
  var el=document.getElementById('list');
  document.getElementById('total').textContent=list.length;
  if(!list.length){el.innerHTML='<div class="empty">No problems found</div>';return;}
  el.innerHTML='';
  for(var i=0;i<list.length;i++){
    var p=list[i];
    var card=document.createElement('div');card.className='card';card.style.animationDelay=(i*80)+'ms';
    card.innerHTML='<div class="card-header"><span class="badge">'+esc(p.id)+'</span><span class="title">'+esc(p.title)+'</span><svg class="icon" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="1.5"><path d="M6 9l6 6 6-6"/></svg></div><div class="card-body"><div class="label">思路</div><div class="thinking">'+esc(p.thinking)+'</div><div class="label">关键代码</div><div class="code-wrap"><pre><code>'+esc(p.code)+'</code></pre></div><div class="label">总结</div><div class="summary">'+esc(p.summary)+'</div><div class="btns"><button id="bc-'+i+'"><svg viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="1.5"><path d="M10 20l4-16m4 4l4 4-4 4M6 16l-4-4 4-4"/></svg><span>查看完整代码</span></button><button id="bp-'+i+'"><svg viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="1.5"><path d="M4 6h16M4 12h16M4 18h12"/></svg><span>查看完整题目</span></button></div><div class="fsec" id="sc-'+i+'"><div class="code-wrap"><pre><code id="cc-'+i+'"></code></pre></div></div><div class="fsec" id="sp-'+i+'"><div class="mdbox" id="mp-'+i+'"></div></div></div>';
    el.appendChild(card);
    var header=card.querySelector('.card-header');
    header.onclick=function(){this.parentElement.classList.toggle('open');};
    document.getElementById('cc-'+i).textContent=p.fullCode;
    document.getElementById('mp-'+i).innerHTML=p.fullProblem;
    document.getElementById('bc-'+i).onclick=function(e){e.stopPropagation();var s=document.getElementById('sc-'+this.id.slice(3));s.classList.toggle('show');this.classList.toggle('on');this.querySelector('span').textContent=this.classList.contains('on')?'收起完整代码':'查看完整代码';};
    document.getElementById('bp-'+i).onclick=function(e){e.stopPropagation();var s=document.getElementById('sp-'+this.id.slice(3));s.classList.toggle('show');this.classList.toggle('on');this.querySelector('span').textContent=this.classList.contains('on')?'收起完整题目':'查看完整题目';};
  }
}
document.getElementById('search').oninput=function(){
  var q=this.value.toLowerCase().trim();
  render(q?DATA.filter(function(p){return p.id.toLowerCase().indexOf(q)>=0||p.title.toLowerCase().indexOf(q)>=0;}):DATA);
};
render(DATA);
</script>
</body>
</html>"""

hp = os.path.join(dest, 'index.html')
with open(hp, 'w', encoding='utf-8') as f:
    f.write(HTML_TEMPLATE)

size = os.path.getsize(hp) / 1024
print(f"Written: {size:.0f} KB")

# Quick sample
for p in problems[:3]:
    print(f"  {p['id']} 思路: {p['thinking'][:50]}...")
for p in problems[-1:]:
    print(f"  {p['id']} 思路: {p['thinking'][:50]}...")
