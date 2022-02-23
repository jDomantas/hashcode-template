import argparse
import datetime
import os
import shutil
import subprocess
import uuid
import zipfile


class LegitException(Exception):
    pass


def compile(runDir):
    print('compiling')
    try:
        output = os.path.join(runDir, 'main.exe')
        subprocess.run([
            'g++',
            '-Wall',
            '-Wextra',
            '-Wno-sign-compare',
            '-O3',
            '-std=c++17',
            '-march=native',
            'src/main.cpp',
            '-o', output,
        ], check = True)
    except subprocess.CalledProcessError:
        raise LegitException('compilation failed')


def zipDirectory(path, zipHandle):
    for root, dirs, files in os.walk(path):
        for file in files:
            path = os.path.join(root, file)
            archivePath = path[4:] # hack, remove src/
            zipHandle.write(path, archivePath)


def zipSource(runDir):
    print('zipping source')
    try:
        output = os.path.join(runDir, 'source.zip')
        zipf = zipfile.ZipFile(output, 'w', zipfile.ZIP_DEFLATED)
        zipDirectory('src/', zipf)
        zipf.close()
    except PermissionError:
        raise LegitException("cannot write source.zip, maybe it's currently opened?")


def prepareRun(runDir):
    os.makedirs(runDir)
    zipSource(runDir)
    compile(runDir)


def run(runDir):
    exe = os.path.abspath(os.path.join('.', runDir, 'main.exe'))
    inputPath = os.path.abspath('input/')
    print('running solution')
    print('================ SOLUTION OUTPUT ================')
    try:
        output = os.path.join(runDir, 'main.exe')
        subprocess.run([exe, inputPath], check = True, cwd = runDir)
        print('=================================================')
    except subprocess.CalledProcessError:
        print('=================================================')
        raise LegitException('solution failed')


def clearDirectory(path):
    for file in os.listdir(path):
        file = os.path.join(path, file)
        os.unlink(file)


def copyDirectory(source, dest):
    for file in os.listdir(source):
        sourceFile = os.path.join(source, file)
        destFile = os.path.join(dest, file)
        shutil.copyfile(sourceFile, destFile)


def copyToLatest(runDir):
    if os.path.exists('latest'):
        clearDirectory('latest')
    else:
        os.makedirs('latest')
    copyDirectory(runDir, 'latest')


def getRunId():
    timestamp = datetime.datetime.now().strftime('%H-%M-%S')
    barf = uuid.uuid4().hex[0:8]
    return '{}-{}'.format(timestamp, barf)


def parseArgs():
    parser = argparse.ArgumentParser()
    parser.add_argument(
        '--label',
        type = str,
        help = 'add a label to run directory name')
    parser.add_argument(
        '--no-latest',
        help = "don't copy results to latest/",
        action = 'store_true')
    parser.add_argument(
        '--check',
        help = "only compile solution",
        action = 'store_true')
    args = parser.parse_args()
    return args.label, args.no_latest, args.check


if __name__ == '__main__':
    try:
        label, noLatest, check = parseArgs()
        runId = getRunId()
        if label is not None:
            runId += '-' + label
        runDir = os.path.join('runs', runId)
        print('starting run in {}'.format(runDir))
        prepareRun(runDir)
        if not check:
            run(runDir)
        if not noLatest:
            print('copying to latest/')
            copyToLatest(runDir)
        print('finished')
    except LegitException as e:
        print('FAILED: {}'.format(e))
