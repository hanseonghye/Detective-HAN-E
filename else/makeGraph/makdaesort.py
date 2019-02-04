import json
from pprint import pprint
from collections import OrderedDict
import csv

file_data = OrderedDict()
with open('example.json') as data_file:
    data = json.load(data_file)

    f = open('data.tsv', 'w', encoding='utf-8', newline='')
    wr = csv.writer(f, delimiter='\t')
    wr.writerow(["pair","weight"])
    pair=[]
    for l in data["links"]:
        if(l["weight"] >= "0.5"):
            pair=l["source"]+"-"+l["target"]
            wr = csv.writer(f, delimiter='\t')
            wr.writerow([pair, l["weight"]])

    f.close()


    # nodess = []
    # linkss = []
    # testtest=[]
    # for h in data["nodes"]:
    #     nodess.append(h)
    #
    # for l in data["links"]:
    #     linkss.append(l)
    #
    # file_data["name"] = "hw_name"
    # file_data["children"] = []
    # for aindex, a in enumerate(nodess):
    #     file_data["children"].append({"name":a["name"]})
    #     print(a["name"])
    #     print(aindex)
    #     print(type(aindex))
    #     file_data["children"][aindex]["children"] = []
    #
    #     for index, b in enumerate(linkss):
    #         if ( a["name"] == b["target"]) :
    #             # print(index, b)
    #             file_data["children"][aindex]["children"].append({"name": b["target"], "size": b["weight"]})
    #
    #         elif (a["name"] == b["source"]):
    #             file_data["children"][aindex]["children"].append({"name": b["target"], "size": b["weight"]})
    #
    #
    # print(json.dumps(file_data,ensure_ascii=False, indent="\t"))
    #
    # with open('data.tsv','w',encoding="utf-8") as make_file:
    #     json.dump(file_data, make_file, ensure_ascii=False, indent="\t")