import os
import sys


def find_sources(folder):
    result = list()
    for path, dirs, files in os.walk(folder):
        for file in files:
            if file.endswith('.cpp'):
                result.append(os.path.join(path, file))
    return result


def get_include_paths():
    include_paths = list()
    for file in os.listdir('.'):
        if os.path.isdir(file):
            include_path = os.path.join(file, 'include')
            if os.path.isdir(include_path):
                include_paths.append(include_path)
    return include_paths


if __name__ == '__main__':
    sources = find_sources('task')
    problem_name = sys.argv[1]
    exec('from %s import add_sources' %\
         '.'.join(['problem', problem_name, 'build']))
    sources.extend(['main.cpp', 'solve.cpp'])

    sources.extend(add_sources(sys.argv[2:]))

    command = 'g++ --std=c++17 %s %s -o run' % (
              ' '.join(sources),
              ' '.join(['-I ' + path for path in get_include_paths()]))

    os.system(command)
