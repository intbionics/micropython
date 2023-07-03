
#source the esprif export.sh, install additional packages
#python -m pip install paho-mqtt asyncio-mqtt pydash
#python -m pip install git+https://###########@github.com/intbionics/upyesp32s.git

import os,sys,re
import asyncio
import argparse
from datetime import datetime
import pytz

from asyncio_mqtt import Client
sys.path.insert(1, '/home/ssmith/upyesp32s')

parser = argparse.ArgumentParser()
parser.add_argument('-b','--boards', 
                    nargs='+', 
                    # default='IB_S2 IB_S3O IB_UM_TINYPICO',
                    help='boards to build', 
                    required=True)
parser.add_argument('-p','--push', 
                    help='push updates',
                    required=False,
                    action='store_true')
args = parser.parse_args()


def build_board(board):
    os.system('make BOARD={} USER_C_MODULES={}'.format(
                board,
                '/home/ssmith/upyesp32s/c_modules/esp32s2.cmake', #use s2 cmake
            )
    )
    #os.system('make BOARD='+board)

def upload_ota(board):
    os.system('/home/ssmith/upyesp32s/tools/upload_firmware.py --board {} --path {}'.format(
                board,
                os.getcwd(),
                )
    )
    #os.system('/home/ssmith/upyesp32s/tools/upload_firmware.py --board '+board+' --path '+os.getcwd())

async def push_update():
    from upyesp32s.encoderdecoder import encode_OTA_DO_UPGRADE
    broker_urls = [
        'lby.titanstats.io',
        # 'rtx1.titanstats.io'
    ]
    for broker_url in broker_urls:
        broker_port = 1883
        username = 'lby'
        password = os.getenv('MQTT_LOBBY_PASSWORD')
        if not password:
            print('MISSING PASSWORD', password)
            return
        print('connecting',broker_url,broker_port,username,password)
        async with Client(broker_url,
                          port     = broker_port,
                          username = 'lby',
                          password = password) as client:
            flood_addr = 2
            org_id = 1
            date   = datetime.now(pytz.timezone('US/Central')).strftime("%Y%m%d")
            topic  = '{}/{}/dn/{}'.format(org_id, date, flood_addr)
            pkt = encode_OTA_DO_UPGRADE(to_addr = flood_addr)
            print('publishing',topic,pkt)
            await client.publish(topic=topic, payload=pkt)

async def process_board(board):
    await asyncio.to_thread(build_board, board = board)
    await asyncio.to_thread(upload_ota, board = board)

async def main():
    tasks = []
    for board in args.boards:
        tasks.append(asyncio.create_task(process_board(board = board)))
    await asyncio.gather(*tasks)

    print(args.push)
    if args.push:
        print('push')
        await push_update()
    else:
        print('skip push')


if __name__ == '__main__':
    asyncio.run(main())

