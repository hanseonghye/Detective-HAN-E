import json
from pprint import pprint
from collections import OrderedDict

file_data = OrderedDict()
show_data=OrderedDict()
crazy_data=OrderedDict()

with open('example.json') as data_file:
    data = json.load(data_file)

    nodess = []
    linkss = []
    testtest=[]
    largetest = []

    for h in data["nodes"]:
        nodess.append(h)

    for l in data["links"]:
        linkss.append(l)

    file_data["name"] = "hw_name"
    file_data["children"] = []

    for aindex, a in enumerate(nodess):
        file_data["children"].append({"name": a["name"]})
        file_data["children"][aindex]["children"] = []

        for index, b in enumerate(linkss):
            if (a["name"] == b["target"]):
                file_data["children"][aindex]["children"].append({"name": b["target"], "size": b["weight"]})

            elif (a["name"] == b["source"]):
                file_data["children"][aindex]["children"].append({"name": b["target"], "size": b["weight"]})



        for j in file_data["children"][aindex]["children"]:
            testtest.append(j)

        largetest.append(testtest)
        # print(aindex, testtest)
        testtest=[]
    ######################################################################

    crazy_data["name"] = "hw_name"
    crazy_data["children"] = []

    print(largetest[0])

    for aindex, a in enumerate(nodess):

        # for bindex, b in enumerate(largetest):
        if aindex == 0:
            crazy_data["children"].append({"name": a["name"]})
            crazy_data["children"][aindex]["children"] = []
            crazy_data["children"][aindex]["children"].append(largetest[0])

        else:
            for lindex, l in enumerate(largetest[aindex]):
                if a["name"] in l["name"]:
                    print("포함합니다", aindex, lindex, largetest[aindex][lindex], l["name"])
                    # crazy_data["children"][aindex]["children"][lindex]["size"].empty()
                    # crazy_data["children"][aindex]["children"][lindex]["children"] = []
                    # crazy_data["children"][aindex]["children"][lindex]["children"].append(l)



    # print(json.dumps(file_data, ensure_ascii=False, indent="\t"))

    with open('testest.json', 'w', encoding="utf-8") as make_file:
        json.dump(file_data, make_file, ensure_ascii=False, indent="\t")

    with open('show.json', 'w', encoding="utf-8") as make_file:
        json.dump(show_data, make_file, ensure_ascii=False, indent="\t")

    with open('crazy.json', 'w', encoding="utf-8") as make_file:
        json.dump(crazy_data, make_file, ensure_ascii=False, indent="\t")
