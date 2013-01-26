from os import path
from glob import glob

env = Environment()

build_dir = '.'
project_name = 'heartbeat'

target = project_name

env.Append(LIBS = ['sfml-graphics', 'sfml-system', 'sfml-window', 'sfml-audio'])
env.Append(CCFLAGS = ['-std=c++11','-g'])
env.Append(CPPPATH='include')

Clean('.', build_dir)

sources = glob('src/*.cpp')

objects = []
for src_file in sources:
	objects += [env.Object(source = src_file,
		target = path.join('build','obj',
							path.splitext(path.basename(src_file))[0]))]

env.Program(target=path.join(build_dir,project_name), source=objects)
