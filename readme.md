# Usage

Make sure that you are using Python 3. Run `python run.py`.

There are a couple of optional parameters:
* `--check` - don't run solution. Run directory will contain only source zip
and the executable.
* `--no-latest` - don't copy run directory to `latest/`. Might be useful if you
want to test multiple solutions in parallel.
* `--label LABEL` - append `-LABEL` to run directory name.


# File organization

Model, input, output, scoring, and validation is defined in `src/main.cpp`.
These are supposed to be implemented after reading problem statement and then
remain unchanged during the rest of the round.

Test info is also defined in `src/main.cpp`, which includes our current best
scores for each test. Update hardcoded best score if you improve test score in
the judge system.

Best solutions for each test are in `src/test_*.cpp`. Please only commit
solutions that correspond to our highscore in the judge system, and don't commit
`#define USE_EVERYWHERE`.

Inputs are placed in `input/` folder.

Runs are placed in `runs/` folder. Each run folder has format
`hour-minute-second-randomid` and includes zipped `src/` directory, executable,
and whatever files the executable produced. After completing a run all files
from it are also copied to `latest/` for easy access.


# Hacking around

Add a `#define USE_EVERYWHERE` in solution file to make that solution to be used
for all tests. Useful if you are experimenting with something and want to see
how it affects other tests.

If you want to skip some tests then comment out corresponding
`runTest(TEST_?);` lines in `src/main.cpp`.

If you want to dump solutions in the middle of test run then add
`writeCurrentSolution()`. It will evaluate current solution and write it out if
has better score than best solution of current run. It will return `false` if
solution was not an improvement.

`currentTest.currentScore` will contain the best score found during this run.
`currentTest.bestScore` will contain the best score overall (which is hardcoded
in `main.cpp`).

If you need to evaluate current solution use `scoreResult()`.

If you run a solution executable directly it will look for input files in
`input/` folder, so you can run them easily from repo root.

There is a makefile if you just want to compile your solution without doing
anything else.

If same solution is optimal for multiple tests you call `test*::solveTest()`
to avoid duplicating code.
