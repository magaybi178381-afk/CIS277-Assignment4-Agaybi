#!/usr/bin/env python3
"""Public preflight for CIS-277 Assignment 4; this checker does not assign a grade."""
import argparse
import os
from pathlib import Path
import shlex
import subprocess
import sys
import tempfile

ROOT = Path(__file__).resolve().parent
REQUIRED = ['TreeExplorer.h', 'TreeExplorer.cpp', 'main.cpp', 'README.md',
            'tests/student_tests.cpp', 'tests/public_tests.cpp']
HEADINGS = ['# CIS-277 Assignment 4: Binary Tree Explorer', '## Student', '## Design',
            '## How to Compile', '## How to Run', '## Tests and Results',
            '## Analysis Questions', '## AI Use']

def run(command, timeout):
    try:
        result = subprocess.run(command, cwd=ROOT, capture_output=True, text=True, timeout=timeout)
    except FileNotFoundError:
        print('INCOMPLETE: compiler or executable not found: ' + command[0]); return 2
    except subprocess.TimeoutExpired:
        print('FAIL: command exceeded the time limit'); return 1
    if result.stdout.strip(): print(result.stdout[-6000:])
    if result.stderr.strip(): print(result.stderr[-6000:])
    if result.returncode != 0:
        print('FAIL: command returned ' + str(result.returncode)); return 1
    return 0

def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--compiler', default=os.environ.get('CXX', 'g++'),
                        help='C++23 compiler command; default is CXX or g++')
    args = parser.parse_args()
    missing = [p for p in REQUIRED if not (ROOT / p).is_file()]
    if missing:
        print('FAIL: missing required files: ' + ', '.join(missing)); return 1
    readme = (ROOT / 'README.md').read_text(encoding='utf-8-sig', errors='replace')
    missing = [h for h in HEADINGS if h not in readme]
    if missing:
        print('FAIL: missing README headings: ' + ', '.join(missing)); return 1
    print('PASS: required files and README headings (content still needs review)')
    compiler = shlex.split(args.compiler)
    if not compiler:
        print('INCOMPLETE: no compiler command specified'); return 2
    msvc = Path(compiler[0]).name.lower() in ('cl', 'cl.exe')
    with tempfile.TemporaryDirectory(prefix='cis277-a4-') as temp:
        build = Path(temp)
        suffix = '.exe' if os.name == 'nt' else ''
        def compile_sources(sources, target):
            if msvc:
                command = compiler + ['/nologo', '/std:c++latest', '/Zc:__cplusplus', '/EHsc', '/W4', '/I', str(ROOT), '/Fo:' + str(build) + os.sep]
                command += [str(ROOT / p) for p in sources] + ['/Fe:' + str(target)]
            else:
                command = compiler + ['-std=c++23', '-Wall', '-Wextra', '-pedantic', '-I', str(ROOT)]
                command += [str(ROOT / p) for p in sources] + ['-o', str(target)]
            return run(command, 60)
        test = build / ('public_tests' + suffix)
        print('Compiling independent public tests...')
        result = compile_sources(['tests/public_tests.cpp', 'TreeExplorer.cpp'], test)
        if result: return result
        print('Running independent public tests...')
        result = run([str(test)], 15)
        if result: return result
        print('Compiling your demonstration...')
        result = compile_sources(['main.cpp', 'TreeExplorer.cpp'], build / ('tree_explorer' + suffix))
        if result: return result
    print('PASS: public preflight completed. Run your demonstration and own tests too.')
    print('This checker does not verify algorithm choice, memory leaks, explanations, or full rubric compliance.')
    return 0

if __name__ == '__main__':
    sys.exit(main())
