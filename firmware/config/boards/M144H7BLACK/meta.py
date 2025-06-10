import pandas as pd
sheet_id = "1gq7eP_nbv2cvgbSxy10gaQpoJTq8OhpK2VwfncVLLcU"
sheet_name = "PIN_MAPPING_MEGA"
url = f"https://docs.google.com/spreadsheets/d/{sheet_id}/gviz/tq?tqx=out:csv&sheet={sheet_name}"
df = pd.read_csv(url)

tname = "M144"

file = open(tname + "_meta.h", "wb");


file.write("#pragma once\n".encode())

for k, v in df.iterrows():
    pin = v["pin"]
    ts_name = v[tname + "_TSNAME"]
    port = str(v["red_board_port"])
    adcport = str(v["ADCPORT"])
    if (port[0].lower() == 'p'):
        port = port[1:]

    if (adcport != 'nan'):
        port = adcport

    file.write(f"// {ts_name} {port}\n".encode())

    file.write(f"#define {tname}_{ts_name} {port}\n\n".encode())

file.close()
