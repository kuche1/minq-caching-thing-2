#! /usr/bin/env python3

import argparse
import os
import subprocess

def term(cmd:list[str]):
    subprocess.run(cmd, check=True)

# fncs that work on files

def pointer_create_file(in_source:str, out_pointer:str):
    term(['mct2-file', 'save', in_source, out_pointer])

def pointer_restore_file(in_pointer:str, out_data:str):
    term(['mct2-file', 'load', in_pointer, out_data])

# fncs that work on files and folders

def pointer_create(in_source:str, out_pointer:str):

    assert os.path.exists(in_source)

    if os.path.isfile(in_source):
        pointer_create_file(in_source, out_pointer)
        return

    # it's a directory

    for _path, folders, files in os.walk(in_source):

        for node in files + folders:
            path_source = os.path.join(in_source, node)
            path_dest = os.path.join(out_pointer, node)
            pointer_create(path_source, path_dest)

def pointer_restore(in_pointer:str, out_data:str):

    assert os.path.exists(in_pointer)

    if os.path.isfile(in_pointer):
        pointer_restore_file(in_pointer, out_data)
        return

    # it's a directory

    for _path, folders, files in os.walk(in_pointer):

        for node in files + folders:
            path_source = os.path.join(in_pointer, node)
            path_dest = os.path.join(out_data, node)
            pointer_restore(path_source, path_dest)

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='TODO')
    parser.add_argument('mode', choices=['save', 'load'], help='TODO')
    parser.add_argument('source', help='TODO')
    parser.add_argument('destination', help='TODO')
    args = parser.parse_args()

    if args.mode == 'save':
        pointer_create(args.source, args.destination)

    elif args.mode == 'load':
        pointer_restore(args.source, args.destination)

    else:
        assert False
