export const meta = {
  name: 'update-html-full',
  description: 'Read all main.cpp and problem.md, embed into HTML with two new buttons',
  phases: [
    { title: 'Read files', detail: 'read content from disk' },
    { title: 'Build HTML', detail: 'generate the updated site' },
  ],
}

const BASE = 'C:/Users/VIP/Desktop/contest-362'

const dirsResult = await agent(`List all subdirectory names under ${BASE} sorted by name`, {
  schema: { type: 'object', properties: { dirs: { type: 'array', items: { type: 'string' } } }, required: ['dirs'] },
})

phase('Read files')
const allData = await pipeline(
  dirsResult.dirs,
  (d) => agent(`Read the files:
1. ${BASE}/${d}/main.cpp - the full solution code
2. ${BASE}/${d}/problem.md - the full problem description

Return a JSON object with:
- id: the problem ID (e.g. "pLinK01")
- title: the Chinese title (extract from problem.md first line after #)
- fullCode: the COMPLETE content of main.cpp, preserving all whitespace and comments
- fullProblem: the COMPLETE content of problem.md, including all HTML/Chinese text

IMPORTANT: Return the FULL content of both files. Do NOT truncate.`, {
    label: d, phase: 'Read files',
    schema: {
      type: 'object',
      properties: {
        id: { type: 'string' },
        title: { type: 'string' },
        fullCode: { type: 'string' },
        fullProblem: { type: 'string' },
      },
      required: ['id', 'title', 'fullCode', 'fullProblem'],
    },
  }),
  // merge back with existing data from index.html thinking/summary/code
  (result, orig) => agent(`I have existing data for ${orig} which I need to combine with the new fullCode/fullProblem.
Return a COMPLETE JSON with ALL fields: id, title, thinking, code, summary, fullCode, fullProblem.

The existing data from the original index.html was already extracted from this problem.
Just merge the fullCode and fullProblem you just read with the existing fields.
Return the complete merged object.`, {
    schema: {
      type: 'object',
      properties: {
        id: { type: 'string' },
        title: { type: 'string' },
        thinking: { type: 'string' },
        code: { type: 'string' },
        summary: { type: 'string' },
        fullCode: { type: 'string' },
        fullProblem: { type: 'string' },
      },
      required: ['id', 'title', 'thinking', 'code', 'summary', 'fullCode', 'fullProblem'],
    },
    label: `${orig}-merge`,
    phase: 'Read files',
  }),
)

phase('Build HTML')
const valid = allData.filter(Boolean)
if (valid.length === 0) { log('ERROR: no data collected!'); return }

await agent(`Generate a complete, self-contained HTML file at ${BASE}/index.html

This is an updated version of the existing page. I'll provide you with ALL problem data as a JSON array.

For each problem object, the fields are:
- id: string (e.g. "pLinK01")
- title: string
- thinking: string (one-sentence solution approach)
- code: string (4-5 lines of core code)
- summary: string (one-sentence summary)
- fullCode: string (the COMPLETE main.cpp file content)
- fullProblem: string (the COMPLETE problem.md content)

Design requirements:
1. Dark theme (VS Code dark-style)
2. Each problem is a collapsible card. By default shows: ID badge, title, thinking, core code, summary
3. Each card must have TWO new toggle buttons:
   - "查看完整代码" - toggles showing the FULL code (fullCode) in a scrollable <pre><code> block
   - "查看完整题目" - toggles showing the FULL problem description (fullProblem) in a styled div
4. These sections are hidden by default, shown when the button is clicked
5. Top search bar filters by id/title in real-time
6. Syntax highlighting for C++ code
7. Responsive design, mobile-friendly
8. Bottom footer shows total count and update date
9. Self-contained - NO external dependencies, NO CDN links
10. The problem.md content may contain HTML tags like <p>, <img>, etc. Display them as-rendered HTML (use innerHTML).

CSS must include:
- .card styles (collapsible)
- .full-section for toggled content areas
- .btn-toggle for the two new buttons
- Smooth animation for expand/collapse

Use the exact data values provided - do not modify or truncate them.

Embed all data as window.PROBLEMS array in a <script> tag. Generate the COMPLETE file.

THE FILE MUST BE COMPLETE AND FUNCTIONAL.`, { label: 'build-html', phase: 'Build HTML' })
