#!/usr/bin/env python3
import sys

current_word = None
doc_ids = set()

for line in sys.stdin:
    line = line.strip()
    if not line or '\t' not in line: 
        continue

    try:
        word, doc_id = line.split('\t', 1)
    except ValueError:
        continue 

    if current_word == word:
        doc_ids.add(doc_id)
    else:
        if current_word:
            print(f"{current_word}\t{','.join(sorted(doc_ids))}")
        current_word = word
        doc_ids = {doc_id}

if current_word:
    print(f"{current_word}\t{','.join(sorted(doc_ids))}")