"""Integration checks of actual commands, file-only output, and BUILD ordering."""
from pathlib import Path
import re
import subprocess
import sys
import tempfile

binary = Path(sys.argv[1]).resolve()
checks = 0

def run_case(commands, files):
    global checks
    with tempfile.TemporaryDirectory() as directory:
        root = Path(directory)
        (root / "commands.txt").write_text("\n".join(commands) + "\n")
        for name, content in files.items():
            (root / name).write_text(content)
        result = subprocess.run([str(binary)], cwd=root, text=True, capture_output=True, timeout=10)
        assert result.returncode == 0, result.stderr
        assert result.stdout == "" and result.stderr == "", "Program must not write to console"
        checks += 1
        output = (root / "output.txt").read_text().splitlines()
        assert len(output) == len(commands), output
        checks += 1
        values = []
        for command, line in zip(commands, output):
            actual, value, timing = line.rsplit(" | ", 2)
            assert actual == command
            assert re.fullmatch(r"\d+\.\d{9} s", timing), timing
            checks += 1
            values.append(value)
        return values

commands = [
    "BUILD HASHTABLE values.txt", "SEARCH HASHTABLE 13", "INSERT HASHTABLE 77", "SEARCH HASHTABLE 77",
    "BUILD MINHEAP values.txt", "INSERT MINHEAP 0", "FINDMIN MINHEAP", "GETSIZE MINHEAP",
    "DELETEMIN MINHEAP", "FINDMIN MINHEAP", "BUILD MINHEAP fresh.txt", "GETSIZE MINHEAP", "FINDMIN MINHEAP",
    "BUILD AVLTREE values.txt", "INSERT AVLTREE 22", "SEARCH AVLTREE 22", "DELETE AVLTREE 22", "SEARCH AVLTREE 22",
    "BUILD MAXHEAP values.txt", "INSERT MAXHEAP 100", "FINDMAX MAXHEAP", "DELETEMAX MAXHEAP", "FINDMAX MAXHEAP",
    "BUILD GRAPH graph.txt", "GETSIZE GRAPH", "COMPUTESHORTESTPATH GRAPH 3 0", "COMPUTESPANNINGTREE GRAPH",
    "FINDCONNECTEDCOMPONENTS GRAPH", "INSERT GRAPH 3 4 0", "COMPUTESHORTESTPATH GRAPH 4 0", "DELETE GRAPH 3 4",
    "FINDCONNECTEDCOMPONENTS GRAPH", "COMPUTESPANNINGTREE GRAPH", "COMPUTESHORTESTPATH GRAPH 0 4",
    "BUILD GRAPH single.txt", "GETSIZE GRAPH", "COMPUTESPANNINGTREE GRAPH",
    "   INSERT MINHEAP 12   ", "GETSIZE MINHEAP",
]
files = {"values.txt": "13\n4\n9\n", "fresh.txt": "55\n",
         "graph.txt": "0 1 4\n1 2 1\n0 2 10\n2 3 2\n1 3 8\n", "single.txt": "7 7 0\n"}
expected = ["BUILT", "SUCCESS", "OK", "SUCCESS", "BUILT", "OK", "0", "4", "OK", "4", "BUILT", "1", "55",
            "BUILT", "OK", "SUCCESS", "OK", "FAILURE", "BUILT", "OK", "100", "OK", "13", "BUILT", "4 5", "7", "7", "1",
            "OK", "7", "OK", "2", "NO_SPANNING_TREE", "UNREACHABLE", "BUILT", "1 1", "0", "OK", "2"]
assert run_case(commands, files) == expected
checks += len(expected)
errors = run_case(["FINDMIN AVLTREE", "BUILD AVLTREE empty.txt", "FINDMIN AVLTREE", "BUILD HASHTABLE missing.txt",
                   "BUILD HASHTABLE empty.txt", "SEARCH HASHTABLE 1", "BUILD GRAPH empty.txt", "GETSIZE GRAPH",
                   "INSERT GRAPH 0 1", "DELETE HASHTABLE 1"], {"empty.txt": ""})
for index in [0, 2, 3, 8, 9]:
    assert errors[index].startswith("ERROR:"), errors
    checks += 1
assert errors[5] == "FAILURE" and errors[7] == "0 0"
checks += 2
print(f"{checks} command checks passed")
