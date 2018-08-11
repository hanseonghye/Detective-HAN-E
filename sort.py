import json
from pprint import pprint
from collections import OrderedDict

file_data = OrderedDict()
with open('example.json') as data_file:
    data = json.load(data_file)


    nodess = []
    linkss = []
    testtest=[]
    for h in data["nodes"]:
        nodess.append(h)

    for l in data["links"]:
        linkss.append(l)

    file_data["name"] = "hw_name"
    file_data["children"] = []
    for aindex, a in enumerate(nodess):
        file_data["children"].append({"name":a["name"]})
        print(a["name"])
        print(aindex)
        print(type(aindex))
        file_data["children"][aindex]["children"] = []

        for index, b in enumerate(linkss):
            if ( a["name"] == b["target"]) :
                # print(index, b)
                file_data["children"][aindex]["children"].append({"name": b["target"], "size": b["weight"]})

            elif (a["name"] == b["source"]):
                file_data["children"][aindex]["children"].append({"name": b["target"], "size": b["weight"]})


    print(json.dumps(file_data,ensure_ascii=False, indent="\t"))

    with open('words.json','w',encoding="utf-8") as make_file:
        json.dump(file_data, make_file, ensure_ascii=False, indent="\t")


    #
    #     for i in range(0, aindex):
    #         if (data["children"][i]["name"] == b["target"]):
    #             file_data["children"][aindex]["children"].append({"name": b["target"], "size": b["weight"]})
    #
    #
    #
    #     if data["nodes"][3]in nodess:
    #         print("Yes  ", nodess.index(data["nodes"][3]))
    #     else:
    #         print("sorry  ")
