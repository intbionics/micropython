
import os,sys,re


# make BOARD=IB_GPS0 USER_C_MODULES=/home/ssmith/upyesp32s/c_modules/esp32s3.cmake

if len(sys.argv) == 1:
    upy_path = os.path.abspath('../..')
    print('''
BUILD.PY
python build.py -p ~/upyesp32s --upy_path {} --boards IB_GPS0
python build.py -p ~/upyesp32s --upy_path {} --boards IB_GTW0
python build.py -p ~/upyesp32s --upy_path {} --boards IB_BLINGMRR
python build.py -p ~/upyesp32s --upy_path {} --boards IB_GPS0 -c -dev -m \\"hello world\\"
python build.py -p ~/upyesp32s --upy_path {} --boards IB_GPS0 -c -live -m \\"hello world\\"
'''.format(upy_path, upy_path, upy_path, upy_path, upy_path))
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

