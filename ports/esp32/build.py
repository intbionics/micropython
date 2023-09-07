
import os,sys,re

if len(sys.argv) == 1:
    print('''
BUILD.PY
python build.py -p ~/upyesp32s --boards IB_GPS0
python build.py -p ~/upyesp32s --boards IB_GPS0 -c -m \"hello world\"
''')
    exit()

if '-p' in sys.argv:
    path = sys.argv[sys.argv.index('-p')+1]
else:
    raise Exception('missing -p path')

args = ' '.join(sys.argv[1:])
print(args)

os.system('python {}/tools/build.py {}'.format(
            path,
            args 
            )
)

