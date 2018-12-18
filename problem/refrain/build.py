import os


def add_sources(args):
    path = 'problem/refrain'

    sources = list()
    for file in os.listdir(path):
        file_path = os.path.join(path, file)
        if os.path.isfile(file_path) and file_path.endswith('.cpp'):
            sources.append(file_path)
    data_struct_files = list()
    sources.append(os.path.join('data_struct', 'suffix_graph.cpp'))

    if args[0] == 'automaton':
        data_struct_files.extend(['refrain_suffix_automaton.cpp',
                                  'get_automaton.cpp'])
        sources.append(os.path.join('data_struct', 'suffix_automaton.cpp'))

    if args[0] == 'tree':
        data_struct_files.extend(['refrain_suffix_tree.cpp',
                                  'get_tree.cpp'])
        sources.append(os.path.join('data_struct', 'suffix_tree.cpp'))

    sources.extend(os.path.join(path, 'data_struct', file)
                   for file in data_struct_files)

    return sources
