#!/usr/bin/env bash
# Build the book as an EPUB with pandoc.
#   bash scripts/build-epub.sh            -> dist/cpp-intro-to-programming.epub
#   VERSION=v1.2.0 bash scripts/build-epub.sh
set -euo pipefail

cd "$(dirname "$0")/.."

VERSION="${VERSION:-$(git describe --tags --always 2>/dev/null || echo dev)}"
OUT_DIR="dist"
OUT="$OUT_DIR/cpp-intro-to-programming.epub"
mkdir -p "$OUT_DIR"

# Chapters are concatenated in file-name order: 00-preface.md, 01-..., 14-..., 99-...
mapfile -t CHAPTERS < <(ls chapters/*.md | sort)

pandoc \
  --from=markdown+smart+pipe_tables+fenced_code_attributes \
  --to=epub3 \
  --metadata-file=book/metadata.yaml \
  --metadata="date:$(date +%Y-%m-%d)" \
  --metadata="subtitle:Version ${VERSION}" \
  --css=book/epub.css \
  --toc --toc-depth=2 \
  --split-level=1 \
  --highlight-style=tango \
  --resource-path=.:chapters:book \
  --output="$OUT" \
  "${CHAPTERS[@]}"

echo "Wrote $OUT ($(du -h "$OUT" | cut -f1))"
