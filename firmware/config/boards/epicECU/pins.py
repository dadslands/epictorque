#!/usr/bin/python3

#
# we're generating pins.yaml file for this ECU from that ther google table
#
#

import pandas as pd

def add_comma_if_needed(x):
    if isinstance(x, (int, float)):
        return "{:,}".format(x)
    return x



sheet_id = "1TT5FeYZpRmhrBHAyqW8Gol4aBldZXQF4vRYXDIsdQhw"
sheet_name = "data_for_connectors_yaml"
url = f"https://docs.google.com/spreadsheets/d/{sheet_id}/gviz/tq?tqx=out:csv&sheet={sheet_name}"
df = pd.read_csv(url)

file = open("connectors/epicECU.yaml", "wb");


file.write("""\
meta: config/boards/epicECU/epicECU_meta.h

pins:
""".encode())

print (df)

for v in df.sort_values(by='ts_name').itertuples():
    if (v.skip_pins>0):
        continue

    file.write(f"""\
  - pin: {v.pin}
""".encode())

    if (v.no_meta != 1):
        file.write(f"""\
    meta: EPICECU_{v.meta}
""".encode())

    if (type(v.pinclass) == str):
        file.write(f"""\
    class: {v.pinclass}
""".encode())

    if (type(v.type) == str):
        file.write(f"""\
    type: {v.type}
""".encode())

    file.write(f"""\
    ts_name: {v.ts_name}
    function: {v.function}
    
""".encode())



# file2 = open("board_configuration_generated.h", "wb")
# file2.write("static Gpio OUTPUTS[] = {\n".encode())
#
# outputs = df[df['pinclass'] == 'outputs'].sort_values(by=['type', 'ordernum'], ascending = [False, True])
# n_rows = len(outputs)
# i=0
# for v in outputs.itertuples():
#     comma = ""
#     file2.write(f"    Gpio::EPICECU_{v.meta},  // {v.function}\n".encode())
#
# file2.write("};\n".encode())
# file2.close();




