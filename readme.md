# Usage

Make sure that you are using Python 3. Run `python run.py`.

There are a couple of optional parameters:
* `--check` - don't run solution. Run directory will contain only source zip
and the executable.
* `--no-latest` - don't copy run directory to `latest/`. Might be useful if you
want to test multiple solutions in parallel.
* `--label LABEL` - append `-LABEL` to run directory name.


# Getting started

1. Adjust test lists if current problem does not have exactly 6 tests.
2. Add inputs to `input/` folder. File names should be `a.txt`, `b.txt`, ...
3. Define model for input data and current solution in `MODEL` section in
`src/main.cpp`.
4. Define evaluator for current solution in `SCORING` section.
5. Implement input reader and solution writer in `INPUT / OUTPUT` section.
6. `python run.py` to run the current solution.
7. Submit outputs and source from `latest/`.


# File organization

Inputs are placed in `input/` folder.

Model, input, output, scoring, and validation is defined in `src/main.cpp`.
These are supposed to be implemented after reading problem statement and then
remain unchanged during the rest of the round.

Current best scores are defined `src/tests.cpp`. Update and commit them when
score is improved in judge system.

Best solutions for each test are in `src/test_*.cpp`. Please only commit
solutions that correspond to our highscore in the judge system, and don't commit
uncommented `#define USE_EVERYWHERE`.

Runs are placed in `runs/` folder. Each run folder has format
`hour-minute-second-randomid` and includes zipped `src/` directory, executable,
and whatever files the executable produced. After completing a run all files
from it are also copied to `latest/` for easy access.


# Hacking around

Add a `#define USE_EVERYWHERE` in solution file to make that solution to be used
for all tests. Useful if you are experimenting with something and want to see
how it affects other tests.

If you want to skip some tests then comment out corresponding
`runTest(TEST_?);` lines in `src/tests.cpp`.

If you want to dump solutions in the middle of test run then add
`writeCurrentSolution()`. It will return `true` if current solution is an
improvement in this run (so that a pattern like
`doRandomChange(); if (!writeCurrentSolution()) { revertChange(); }` would
work). However, solution files will only be written if they improve over the 
best known score to avoid creating unnecessary files.

`currentTest.currentScore` will contain the best score found during this run.
`currentTest.bestScore` will contain the best score overall (which is hardcoded
in `tests.cpp`).

If you need to evaluate current solution use `scoreResult()`.

If you run a solution executable directly it will look for input files in
`input/` folder, so you can run them easily from repo root. Mind that output
files will then be dropped into repo root, so be careful not to commit them.

There is a makefile if you just want to compile your solution without doing
anything else.

If same solution is optimal for multiple tests you can call `test*::solveTest()`
to avoid duplicating code.
