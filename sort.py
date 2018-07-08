import json
from pprint import pprint
from collections import OrderedDict

file_data = OrderedDict()
with open('example.json') as data_file:
    data = json.load(data_file)

    pprint(data)
    print("link 봐라 %s"%data["nodes"][0]["name"], end="\n\n")
    print(type(data["nodes"][0]["name"]))
    # for name, code in data["nodes"].items():
    #     if( code == "201224444_eleccar"):
    #         print("got it")

    nodess = []
    linkss = []
    for h in data["nodes"]:
        nodess.append(h)

    for l in data["links"]:
        linkss.append(l)


    for a in nodess:
        file_data[a["name"]]=[]

        print(a["name"])
        for index, b in enumerate(linkss):
            if (a["name"] == b["target"]) :
                print(index,b)
                file_data[a["name"]].append({"source": b["target"], "weight":b["weight"]})
            elif a["name"] == b["source"]:
                file_data[a["name"]].append( {"source": b["target"], "weight": b["weight"]})

    print(json.dumps(file_data,ensure_ascii=False, indent="\t"))

    with open('words.json','w',encoding="utf-8") as make_file:
        json.dump(file_data, make_file, ensure_ascii=False, indent="\t")


    if data["nodes"][3]in nodess:
        print("Yes  ", nodess.index(data["nodes"][3]))
    else:
        print("sorry  ")

