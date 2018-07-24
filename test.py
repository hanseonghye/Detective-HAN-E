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
                    crazy_data["children"][aindex]["children"][lindex]["size"].empty()
                    crazy_data["children"][aindex]["children"][lindex]["children"] = []
                    crazy_data["children"][aindex]["children"][lindex]["children"].append(l)



    # print(json.dumps(file_data, ensure_ascii=False, indent="\t"))

    with open('testest.json', 'w', encoding="utf-8") as make_file:
        json.dump(file_data, make_file, ensure_ascii=False, indent="\t")

    with open('show.json', 'w', encoding="utf-8") as make_file:
        json.dump(show_data, make_file, ensure_ascii=False, indent="\t")

    with open('crazy.json', 'w', encoding="utf-8") as make_file:
        json.dump(crazy_data, make_file, ensure_ascii=False, indent="\t")
        # for i in range(0, aindex):
        #     if (data["children"][i]["name"] == b["target"]):
        #         file_data["children"][aindex]["children"].append({"name": b["target"], "size": b["weight"]})
        #
        #
        #
        # if data["nodes"][3]in nodess:
        #     print("Yes  ", nodess.index(data["nodes"][3]))
        # else:
        #     print("sorry  ")
    #
    # bnode=[]
    # for aindex, a in enumerate(nodess):
    #     for index, b in enumerate(linkss):
    #         if (a["name"] == b["target"]):
    #             print(aindex, index)
    #             bnode.append(b["target"])
    #     print("same b::::: ", bnode)
    #     for aa in range(0, aindex):
    #         for cindex, c in enumerate(largetest[aa]):
    #             print(aa, cindex)
    #             if(b["target"]!=c["name"]):
    #                 print("not same")
    #             else:
    #                 print("same")
    #                 # bnode.pop()
    #     bnode=[]

    # for aindex, a in enumerate(nodess):
    #     crazy_data["children"].append({"name": a["name"]})
    #     crazy_data["children"][aindex]["children"] = []
    #
    #     if aindex==0:
    #         for index, b in enumerate(linkss):
    #             if (a["name"] == b["target"]):
    #                 crazy_data["children"][aindex]["children"].append({"name": b["target"], "size": b["weight"]})
    #
    #             elif (a["name"] == b["source"]):
    #                 crazy_data["children"][aindex]["children"].append({"name": b["target"], "size": b["weight"]})
    #     else:
    #         for index, b in enumerate(linkss):
    #
    #             if (a["name"] == b["target"]):
    #                 crazy_data["children"][aindex]["children"].append({"name": b["target"], "size": b["weight"]})
    #
    #             elif (a["name"] == b["source"]):
    #                 crazy_data["children"][aindex]["children"].append({"name": b["target"], "size": b["weight"]})
    #
    #  if aindex == 0:
    #             show_data["children"][aindex]["children"] = largetest[0]
    #         else:
    #                 for index, b in enumerate(linkss):
    #                     if (a["name"] == b["target"]):
    #                         bnodes.append(index)
    #                 print(bnodes)
    #
    #                 for bindex, bn in enumerate(bnodes):
    #                     for aa in range(0, aindex):
    #                         for cindex, c in enumerate(largetest[aa]):
    #                             if ( linkss[bn] == c["name"]):
    #                                 bnodes.pop(linkss[bn])
    #                                 print(linkss[bn], aindex, cindex)
    #
    #                     show_data["children"][aindex]["children"].append({"name": linkss[bn]["target"], "size": linkss[bn]["weight"]})
    #
    #
    #                 for index, b in enumerate(linkss):
    #                     if (a["name"] == b["source"]):
    #                         snodes.append(index)
    #                 print(snodes)
    #
    #                 for sindex, sn in enumerate(snodes):
    #                     for aa in range(0, aindex):
    #                         for cindex, c in enumerate(largetest[aa]):
    #                             if (linkss[sn] == c["name"]):
    #                                 bnodes.pop(linkss[sn])
    #                                 print(linkss[sn], aindex, cindex)
    #
    #                         show_data["children"][aindex]["children"].append({"name": linkss[sn]["target"], "size": linkss[sn]["weight"]})
    #
    #                 bnodes=[]
    #                 snodes=[]
    #
