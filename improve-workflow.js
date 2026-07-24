export const meta = {
  name: 'improve-descriptions',
  description: 'Review and improve the three points for all 78 problems',
  phases: [
    { title: 'Improve', detail: 'review and humanize descriptions in batches' },
    { title: 'Build', detail: 'regenerate HTML with improved text' },
  ],
}

const BASE = 'C:/Users/VIP/Desktop/contest-362'

// First, get all directory names
const dirsResult = await agent(`List all pLinK* subdirectory names under ${BASE} sorted by name`, {
  schema: { type: 'object', properties: { dirs: { type: 'array', items: { type: 'string' } } }, required: ['dirs'] },
})

// Batch them into groups of ~10
const allDirs = dirsResult.dirs
const BATCH_SIZE = 10
const batches = []
for (let i = 0; i < allDirs.length; i += BATCH_SIZE) {
  batches.push(allDirs.slice(i, i + BATCH_SIZE))
}

log(`Processing ${allDirs.length} dirs in ${batches.length} batches`)

// Schema for batch output
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
          thinking: { type: 'string', description: '一句话思路，说人话，自然亲切' },
          code: { type: 'string', description: '4-5行核心代码，带一行中文注释' },
          summary: { type: 'string', description: '一句话总结，学到什么/踩了什么坑' },
        },
        required: ['id', 'title', 'thinking', 'code', 'summary'],
      },
    },
  },
  required: ['problems'],
}

phase('Improve')
const batchResults = await pipeline(
  batches,
  (batch) => agent(`You will improve the "思路/关键代码/总结" for the following problems.

For EACH problem:
1. Read its main.cpp and problem.md from ${BASE}/{dir}/
2. Write improved versions of the three points

Rules:
- 思路: ONE sentence, natural/conversational Chinese. Say what the problem tests and how you solved it. Like you're explaining to a classmate. No "本题考查" or "考察".
- 关键代码: 4-5 lines of the MOST critical C++ code. Include EXACTLY ONE line of Chinese comment (prefixed with //). The comment should be helpful, not obvious.
- 总结: ONE sentence, personal and practical. What did you learn? What was the trick? What mistake would you avoid next time?

Batch: ${batch.join(', ')}

Read each dir's main.cpp and problem.md, then produce the improved versions.
Keep the thinking/code/summary CONCISE.`, {
    label: `batch-${batches.indexOf(batch)}`,
    phase: 'Improve',
    schema: BATCH_SCHEMA,
  }),
)

phase('Build')
const allImproved = batchResults.filter(Boolean).flatMap(r => r.problems).filter(Boolean)
log(`Total improved: ${allImproved.length}`)

await agent(`Read the current HTML file at ${BASE}/improve.py, then generate a new index.html at ${BASE}/index.html

I have improved problem data for ${allImproved.length} problems. Merge this data with the fullCode and fullProblem from the existing files.

For each problem, the improved data has: id, title, thinking, code, summary
You need to add: fullCode (read from main.cpp, strip C++ comments), fullProblem (read from problem.md, convert basic markdown to HTML)

Generate a COMPLETE, SELF-CONTAINED HTML file.

Design: minimalist-ui aesthetic
- Warm monochrome palette (#F7F6F3 bg, #FFF cards, #EAEAEA borders)
- SF Pro / Helvetica Neue font stack
- No emojis (use SVG icons)
- Blue pastel accent (#E1F3FE / #1F6C9F)
- Cards with fadeUp animation
- Search bar filtering by ID/title
- Each card collapsible: 思路 | 关键代码 | 总结 | [查看完整代码] [查看完整题目]
- Full code in <pre><code> with textContent
- Full problem with innerHTML (it contains HTML tags)
- Title: "程序设计实践A"
- Labels in Chinese: 思路, 关键代码, 总结, 查看完整代码, 查看完整题目

Title should be: 程序设计实践A
Footer: 程序设计实践A · Problem Set

Write the complete file.`, { label: 'build-html', phase: 'Build' })
