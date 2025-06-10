#!/usr/bin/python3
from sys import meta_path

import yaml
import pandas as pd
sheet_id = "1gq7eP_nbv2cvgbSxy10gaQpoJTq8OhpK2VwfncVLLcU"
sheet_name = "PIN_MAPPING_MEGA"
url = f"https://docs.google.com/spreadsheets/d/{sheet_id}/gviz/tq?tqx=out:csv&sheet={sheet_name}"
df = pd.read_csv(url)

tname = "M144"
mcuname = "M144F7RED"

file = open("connectors/" + tname + ".yaml", "wb");


file.write(f"""\
meta: config/boards/{mcuname}/{tname}_meta.h

pins:
""".encode())

bigdat = []

for k, v in df.iterrows():
    dat = {}
    pin              = v["pin"]
    meta             = tname + "_" + v[tname + "_TSNAME"]
    ts_name          = v[tname + "_TSNAME"]
    pin_class        = str(v[tname + "_CLASS"])
    pin_type         = str(v[tname + "_TYPE"])

    dat["pin"] = pin
    dat["meta"] = meta
    dat["ts_name"] = ts_name
    if (pin_class != 'nan'):
        dat['class'] = pin_class

    if (pin_type != 'nan'):
        dat['type'] = pin_type

    bigdat.append(dat)

file.write(yaml.dump(bigdat).encode())