import os
import sys
import pathlib as pl
import argparse as ap
import re

def init_argparse() -> ap.ArgumentParser:
    parser = ap.ArgumentParser(usage = '%(prog)s [Project Number]', description='Enter the project number to compile and run')
    parser.add_argument('prj_num', help='project nubmer goes here')
    return parser

def main() -> None:
    try:
        parser = init_argparse()
        args = parser.parse_args()
    except:
        print('No project number was entered')
        return
        
    drive_letter = pl.Path.home().drive
    user_home = os.environ['HOMEPATH']
    repo_base = 'Documents\\repos\\opencv_course\\cpp_prjs'.split('\\')
    # creating base directory path
    full_path = []
    full_path.append(drive_letter)
    full_path.append(user_home)
    full_path += repo_base
    full_path.append(args.prj_num)
    path_str = os.path.join(*full_path)

    # load CmakeLists.tx and extract project name
    proj_name = ''
    with open(path_str + '\\CmakeLists.txt', 'r') as f:
        my_text = ' '.join(f.readlines())
        m = re.search('project\(\w+\)', my_text)
        if m:
            proj_name = m.group(0)[8:-1]
    
    # creating build directory path
    full_path = []
    full_path.append(path_str)
    full_path.append('build')
    build_path_str = os.path.join(*full_path)

    # creating executable directory path
    full_path = []
    full_path.append(build_path_str)
    full_path.append('Release')
    full_path.append(proj_name + '.exe')
    exec_path_str = os.path.join(*full_path)

    # print(build_path_str)
    if(pl.Path(path_str).exists()):
        os.system('cd {} && cmake .. && cmake --build . --config Release && cd {} && {}'.format(build_path_str, pl.Path(path_str).resolve().parent, exec_path_str))

if __name__ == '__main__':
    main()



#cd c:\%HOMEPATH%\Documents\repos\opencv_course\cpp_prjs\ 
# && cd .\006\build 
# && cmake .. 
# && cmake --build . --config Release 
# && cd ..\..\ 
# && .\006\build\Release\main.exe
#regex to match the project line and extract the name of the project "project\(\w+\)"gm