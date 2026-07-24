export const meta = {
  name: 'refine-descriptions',
  description: 'Rewrite all 78 descriptions with professional, natural language',
  phases: [
    { title: 'Refine', detail: '8 batches of ~10 problems each' },
    { title: 'Build', detail: 'generate final HTML' },
  ],
}

const BASE = 'C:/Users/VIP/Desktop/contest-362'

const dirsResult = await agent(`List all pLinK* subdirectory names under ${BASE} sorted by name`, {
  schema: { type: 'object', properties: { dirs: { type: 'array', items: { type: 'string' } } }, required: ['dirs'] },
})

const BATCH_SIZE = 10
const batches = []
for (let i = 0; i < dirsResult.dirs.length; i += BATCH_SIZE)
  batches.push(dirsResult.dirs.slice(i, i + BATCH_SIZE))

const BATCH_SCHEMA = {
  type: 'object',
  properties: {
    problems: {
      type: 'array',
      items: {
        type: 'object',
        properties: {
          id: { type: 'string' },
          title: { type: 'string' },
          thinking: { type: 'string' },
          code: { type: 'string' },
          summary: { type: 'string' },
        },
        required: ['id', 'title', 'thinking', 'code', 'summary'],
      },
    },
  },
  required: ['problems'],
}

phase('Refine')
const batchResults = await pipeline(
  batches,
  (batch) => agent(`You are a technical writing editor. Rewrite the three-point summaries for a set of programming problems.

For EACH problem in this batch:
1. Read its main.cpp and problem.md from ${BASE}/{dir}/
2. Produce three concise items following these EXACT specifications:

**思路** — One sentence explaining what the problem tests and how you solved it.
- Language: semi-formal, professional, natural. Like a well-written technical blog post.
- NO: 本题考查, 考察, 哈/哇/呐, 咱们/家人们, 感叹号 overdose
- NO: robotic officialese either
- YES: clear, direct, logically flows from problem to approach

**关键代码** — 4-5 lines of the most critical C++ code.
- Include ONE line of Chinese comment (// ...) that adds insight, not obvious description
- The code must be syntactically correct
- Strip any comments from the original code; your comment is the only one

**总结** — One sentence about what you actually learned, a pitfall to avoid, or a technique worth remembering.
- Keep it real, specific, and actionable
- Natural professional tone — not a cliché, not a textbook sentence

Batch: ${batch.join(', ')}`, {
    label: `batch-${batches.indexOf(batch)}`,
    phase: 'Refine',
    schema: BATCH_SCHEMA,
  }),
)

phase('Build')
const allRefined = batchResults.filter(Boolean).flatMap(r => r.problems).filter(Boolean)

await agent(`Build the final index.html at ${BASE}/index.html using these improved descriptions.

I have ${allRefined.length} problem entries. For each, merge the refined thinking/code/summary with:
- fullCode: read from main.cpp, strip C++ comments
- fullProblem: read from problem.md, convert triple-backtick code blocks to pre/code tags and double-hash headings to h2 tags

Design:
- Title: 程序设计实践A (exactly)
- Warm monochrome: bg #F7F6F3, cards #FFF, borders #EAEAEA
- Font: SF Pro Display / Helvetica Neue
- Accent: blue pastel #E1F3FE / #1F6C9F
- Labels in Chinese: 思路, 关键代码, 总结, 查看完整代码, 查看完整题目
- Search by id/title
- Collapsible cards with SVG chevron (no emoji)
- fadeUp animation
- fullCode via textContent, fullProblem via innerHTML (it contains HTML tags)
- Remove build-html-workflow.js improve-workflow.js improve.py rebuild-final.py rebuild.py gen-html.py fix-html.py fix-html.ps1 after building

The file MUST be valid, self-contained HTML. Write it.`, { label: 'build', phase: 'Build' })
