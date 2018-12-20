import os


def add_sources(args):
    path = os.path.join('problem', 'internal_point')

    sources = list()
    for file in os.listdir(path):
        file_path = os.path.join(path, file)
        if os.path.isfile(file_path) and file_path.endswith('.cpp'):
            sources.append(file_path)

    return sources
