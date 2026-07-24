$ErrorActionPreference = 'Stop'
$dest = "C:\Users\VIP\Desktop\contest-362"

function Strip-CppComments($code) {
    if ([string]::IsNullOrEmpty($code)) { return "" }
    $code = [regex]::Replace($code, "/\*.*?\*/", "", [System.Text.RegularExpressions.RegexOptions]::Singleline)
    $result = ""
    $lines = $code -split "`n"
    foreach ($line in $lines) {
        $inString = $false; $commentPos = -1
        for ($i = 0; $i -lt $line.Length; $i++) {
            if ($line[$i] -eq '"') { $inString = -not $inString }
            if (-not $inString -and $i -lt $line.Length - 1 -and $line[$i] -eq '/' -and $line[$i+1] -eq '/') {
                $commentPos = $i; break
            }
        }
        if ($commentPos -ge 0) { $result += $line.Substring(0, $commentPos).TrimEnd() }
        else { $result += $line }
        $result += "`n"
    }
    $result = $result -replace "[ \t]+\n", "`n"
    $result = $result -replace "\n{3,}", "`n`n"
    return $result.Trim()
}

# SIMPLE MdToHtml: only convert ``` and ##, leave everything else as-is
function MdToHtml($md) {
    if ([string]::IsNullOrEmpty($md)) { return "" }
    $lines = $md -split "`n"
    $inCodeBlock = $false; $codeBlock = @(); $result = @()
    foreach ($line in $lines) {
        if ($line -match "^```") {
            if ($inCodeBlock) {
                $encoded = [System.Web.HttpUtility]::HtmlEncode(($codeBlock -join "`n"))
                $result += "<pre><code>$encoded</code></pre>"
                $codeBlock = @(); $inCodeBlock = $false
            } else { $inCodeBlock = $true; $codeBlock = @() }
            continue
        }
        if ($inCodeBlock) { $codeBlock += $line; continue }
        if ($line -match "^## ([^#].*)") { $result += "<h2>$($matches[1])</h2>"; continue }
        if ($line -match "^### (.*)") { $result += "<h3>$($matches[1])</h3>"; continue }
        if ($line -match "^---+$") { $result += "<hr>"; continue }
        if ($line -match '^\s*$') { $result += ""; continue }
        $result += $line
    }
    if ($inCodeBlock -and $codeBlock.Count -gt 0) {
        $result += "<pre><code>" + ($codeBlock -join "`n") + "</code></pre>"
    }
    return ($result -join "`n")
}

function esc($s) {
    if ([string]::IsNullOrEmpty($s)) { return "" }
    $s = $s -replace "\\", "\\"; $s = $s -replace '"', '\"'
    $s = $s -replace "`r`n", "\n"; $s = $s -replace "`n", "\n"; $s = $s -replace "`t", "\t"
    return $s
}

# Load journal
$jp = "C:/Users/VIP/.claude/projects/c--Users-VIP-Desktop-microterm/d5504b11-1823-4a07-a544-c0ba0f02565a/subagents/workflows/wf_6c14642d-863/journal.jsonl"
$journal = @{}
Get-Content $jp -Encoding UTF8 | ForEach-Object {
    try { $obj = $_ | ConvertFrom-Json
        if ($obj.type -eq "result" -and $obj.result.id -and $obj.result.thinking) {
            $journal[$obj.result.id] = $obj.result
        }
    } catch {}
}

$entries = @()
Get-ChildItem $dest -Directory | Sort-Object Name | ForEach-Object {
    $d = $_.Name; $dir = $_.FullName
    $id = if ($d -match "(pLinK[\d.]+)") { $matches[1] } else { $d }
    $displayId = $id -replace "^p", ""
    $title = if ($d -match "pLinK[\d.]+_(.*)") { $matches[1] } else { $d }
    $jd = $journal[$id]
    if (-not $jd) { $jd = $journal[$id -replace "LinK","Link"] }
    $thinking = if ($jd) { esc $jd.thinking } else { "" }
    $code = if ($jd) { esc $jd.code } else { "" }
    $summary = if ($jd) { esc $jd.summary } else { "" }
    $cpp = ""
    $cppPath = "$dir/main.cpp"
    if (Test-Path $cppPath) {
        $raw = (Get-Content $cppPath -Raw -Encoding UTF8) -replace "`0",""
        $stripped = Strip-CppComments $raw
        $cpp = esc $stripped
    }
    $md = ""
    $mdPath = "$dir/problem.md"
    if (Test-Path $mdPath) {
        $raw = (Get-Content $mdPath -Raw -Encoding UTF8) -replace "`0",""
        $htmlContent = MdToHtml $raw
        $md = esc $htmlContent
    }
    $entries += "  { `"id`":`"$displayId`", `"title`":`"$(esc $title)`", `"thinking`":`"$thinking`", `"code`":`"$code`", `"summary`":`"$summary`", `"fullCode`":`"$cpp`", `"fullProblem`":`"$md`" }"
}

Write-Host "Built $($entries.Count) entries"

$htmlPath = "$dest/index.html"
$html = Get-Content $htmlPath -Raw -Encoding UTF8
$pattern = "(var PROBLEMS = \[).*?(\];)"
$replacement = '${1}' + "`n" + ($entries -join ",`n") + "`n" + '${2}'
$html = [regex]::Replace($html, $pattern, $replacement, [System.Text.RegularExpressions.RegexOptions]::Singleline)

# Ensure innerHTML is used
$html = $html -replace "mdContent\.textContent = p\.fullProblem", "mdContent.innerHTML = p.fullProblem"

[System.IO.File]::WriteAllText($htmlPath, $html, [System.Text.Encoding]::UTF8)
Write-Host "Done! $([math]::Round((Get-Item $htmlPath).Length/1KB,1)) KB"

# Quick verification
$first = [regex]::Match($html, '"fullProblem":"(.+?)"', [System.Text.RegularExpressions.RegexOptions]::Singleline)
if ($first.Success) {
    $s = $first.Groups[1].Value
    Write-Host "First fullProblem start: $($s.Substring(0, [Math]::Min(120, $s.Length)))"
}
Write-Host "Has HTML tags in fullProblem: $($html.Contains('&lt;h2')) is false (good)"
Write-Host "Has innerHTML: $($html.Contains('innerHTML = p.fullProblem'))"
