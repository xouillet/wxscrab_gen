SConscript('src/SConstruct', variant_dir='build', duplicate=0)

env = Environment()
dics = Glob('dic/*.*')
data = env.Install('/usr/share/wxscrab/dic/', dics)
env.Alias('install', data)
