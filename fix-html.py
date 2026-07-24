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
        except:
            pass

print(f"Journal: {len(journal)} entries")

def strip_cpp_comments(code):
    if not code: return ""
    code = re.sub(r'/\*.*?\*/', '', code, flags=re.DOTALL)
    result = []
    for line in code.split('\n'):
        in_str = False
        comment_pos = -1
        for i, ch in enumerate(line):
            if ch == '"':
                in_str = not in_str
            if not in_str and i < len(line)-1 and line[i] == '/' and line[i+1] == '/':
                comment_pos = i
                break
        if comment_pos >= 0:
            result.append(line[:comment_pos].rstrip())
        else:
            result.append(line)
    text = '\n'.join(result)
    text = re.sub(r'[ \t]+\n', '\n', text)
    text = re.sub(r'\n{3,}', '\n\n', text)
    return text.strip()

def md_to_html(md):
    if not md: return ""
    lines = md.split('\n')
    result = []
    in_code = False
    code_block = []
    for line in lines:
        if line.startswith('```'):
            if in_code:
                encoded = html.escape('\n'.join(code_block))
                result.append('<pre><code>' + encoded + '</code></pre>')
                code_block = []
                in_code = False
            else:
                in_code = True
                code_block = []
            continue
        if in_code:
            code_block.append(line)
            continue
        if not line.strip():
            continue
        if re.match(r'^---+$', line):
            result.append('<hr>')
            continue
        m = re.match(r'^## ([^#].*)', line)
        if m:
            result.append('<h2>' + m.group(1) + '</h2>')
            continue
        m = re.match(r'^### (.*)', line)
        if m:
            result.append('<h3>' + m.group(1) + '</h3>')
            continue
        result.append(line)
    if in_code and code_block:
        result.append('<pre><code>' + '\n'.join(code_block) + '</code></pre>')
    return '\n'.join(result)

def js_escape(s):
    if not s: return ""
    s = s.replace('\', '\\')
    s = s.replace('"', '\\"')
    s = s.replace('\n', '\n')
    s = s.replace('\r', '\r')
    s = s.replace('\t', '\t')
    return s

entries = []
for d in sorted(os.listdir(dest)):
    dirpath = os.path.join(dest, d)
    if not os.path.isdir(dirpath):
        continue
    m = re.match(r'(pLinK[\d.]+)', d)
    id_val = m.group(1) if m else d
    display_id = id_val.replace('p', '', 1)
    m2 = re.match(r'pLinK[\d.]+_(.*)', d)
    title = m2.group(1) if m2 else d
    
    jd = journal.get(id_val) or journal.get(id_val.replace('LinK', 'Link'))
    thinking = js_escape(jd['thinking']) if jd else ""
    core_code = js_escape(jd['code']) if jd else ""
    summary = js_escape(jd['summary']) if jd else ""
    
    full_code = ""
    cpp_path = os.path.join(dirpath, 'main.cpp')
    if os.path.exists(cpp_path):
        with open(cpp_path, 'r', encoding='utf-8') as f:
            raw = f.read()
        stripped = strip_cpp_comments(raw)
        full_code = js_escape(stripped)
    
    full_problem = ""
    md_path = os.path.join(dirpath, 'problem.md')
    if os.path.exists(md_path):
        with open(md_path, 'r', encoding='utf-8') as f:
            raw = f.read()
        html_content = md_to_html(raw)
        full_problem = js_escape(html_content)
    
    entry = ('  { "id":"' + display_id + '", "title":"' + js_escape(title) +
             '", "thinking":"' + thinking + '", "code":"' + core_code +
             '", "summary":"' + summary + '", "fullCode":"' + full_code +
             '", "fullProblem":"' + full_problem + '" }')
    entries.append(entry)

print(f"Built {len(entries)} entries")

html_path = os.path.join(dest, 'index.html')
with open(html_path, 'r', encoding='utf-8') as f:
    html_content = f.read()

entries_str = ',\n'.join(entries)
html_content = re.sub(
    r'var PROBLEMS = \[.*?\];',
    'var PROBLEMS = [\n' + entries_str + '\n];',
    html_content, flags=re.DOTALL
)
html_content = html_content.replace(
    'mdContent.textContent = p.fullProblem',
    'mdContent.innerHTML = p.fullProblem'
)

with open(html_path, 'w', encoding='utf-8') as f:
    f.write(html_content)

size = os.path.getsize(html_path) / 1024
count = html_content.count('"id":"LinK')
print(f"Done! {size:.0f} KB, {count} entries")
print(f"Has innerHTML: {'innerHTML = p.fullProblem' in html_content}")

# Show sample of fullProblem for LinK01
idx = html_content.find('LinK01')
if idx > 0:
    snippet = html_content[idx:idx+500]
    fp_idx = snippet.find('"fullProblem"')
    if fp_idx > 0:
        fp_start = snippet.find('"', fp_idx+14)
        fp_end = snippet.find('"', fp_start+1)
        if fp_start > 0 and fp_end > 0:
            sample = snippet[fp_start+1:fp_end]
            print(f"Sample fullProblem (first 200 chars): {sample[:200]}")
