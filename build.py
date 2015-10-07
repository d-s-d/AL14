#!/usr/bin/env python3

import os
import sys

executed_targets = set()
available_targets = dict()

CGAL_REQUIRED = False
TARGET_FILE = ""
CXX_FLAGS = " -o a.out -O2 -std=c++11 -I/usr/local/include/ -m64 -g -Wall "
CXX = "g++"
POSTFIX = ".cpp"
CMAKE_LISTS = 'CMakeLists.txt'
C11_DEF = 'add_definitions("-std=c++11")'

def target(*dep_fs):
    def get_dependent_f(f):
        def dependent_f(*args, **kwargs):
                for f_dependent in dep_fs:
                    if f_dependent not in executed_targets:
                        f_dependent(*args, **kwargs)
                        executed_targets.add(f_dependent)
                executed_targets.add(f)
                print("** Executing target: " + f.__name__);
                f(*args, **kwargs)
        available_targets[f.__name__] = dependent_f
        return dependent_f
    return get_dependent_f


@target()
def target_file(*args):
    cpp_files = list(filter(lambda s: s.endswith(POSTFIX), os.listdir('.')))
    if len(cpp_files) > 0:
        global TARGET_FILE
        TARGET_FILE = cpp_files[0]
    else:
        raise Exception("No files found that end in: " + POSTFIX)
    pass

@target(target_file)
def check_cgal_required(*args):
    f = open(TARGET_FILE)
    print("# cgal required.")
    if any(map(lambda s: 'CGAL' in s, f)):
        global CGAL_REQUIRED
        CGAL_REQUIRED = True
    f.close()

@target(check_cgal_required)
def cgal_create_scripts(*args):
    # test whether there is CGAL in cpp
    if CGAL_REQUIRED and CMAKE_LISTS not in os.listdir('.'):
        os.system('cgal_create_cmake_script')

@target(cgal_create_scripts)
def cgal_c11(*args):
    if CGAL_REQUIRED:
        f_cmake = open(CMAKE_LISTS)
        has_c11_def = (C11_DEF + '\n') in f_cmake
        f_cmake.close()
        if not has_c11_def:
            f_cmake = open(CMAKE_LISTS, 'a')
            f_cmake.write(C11_DEF + '\n')
            f_cmake.close()

@target(cgal_c11)
def cmake(*args):
    if CGAL_REQUIRED:
        os.system("cmake .")

@target(cmake, target_file)
def build(*args):
    if CGAL_REQUIRED:
        os.system("make")
    else:
        os.system(CXX + CXX_FLAGS + TARGET_FILE)

@target(build)
def test(*args):
    if CGAL_REQUIRED:
        exec_file = TARGET_FILE[0:-4]
    else:
        exec_file = 'a.out'

    testfile = args[0][0]
    testoutfile = testfile[0:-3] + '.tout'
    refoutfile = testfile[0:-3] + '.out'
    os.system('./{0} < {1} > {2}'.format(exec_file, testfile, testoutfile))
    os.system('diff {0} {1}'.format(testoutfile, refoutfile)) 

if __name__=="__main__":
    try:
        available_targets[sys.argv[1]](sys.argv[2:])
    except (KeyError, IndexError):
        print("...")
