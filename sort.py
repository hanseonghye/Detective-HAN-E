import json
from pprint import pprint
from collections import OrderedDict

file_data = OrderedDict()
show_data = OrderedDict()
with open('example.json') as data_file:
    data = json.load(data_file)

    nodess = []
    linkss = []
    testtest=[]
    print(data)
    for h in data["nodes"]:
        nodess.append(h)

    for l in data["links"]:
        linkss.append(l)

    file_data["name"] = "hw_name"
    file_data["children"] = []
    for aindex, a in enumerate(nodess):
        file_data["children"].append({"name":a["name"]})
        file_data["children"][aindex]["children"] = []

        for index, b in enumerate(linkss):
            if ( a["name"] == b["target"]) :
                # print(index, b)
                file_data["children"][aindex]["children"].append({"name": b["source"], "size": b["weight"]})

            elif (a["name"] == b["source"]):
                file_data["children"][aindex]["children"].append({"name": b["target"], "size": b["weight"]})

    for index, file in enumerate(file_data["children"]):
        if len(file["children"]):
            testtest.append({"source":file["name"],"target":file["children"][0]["name"], "size":file["children"][0]["size"]})

    for testindex, test in enumerate(testtest):
        for test2index, test2 in enumerate(testtest):
            if test["source"] in test2["source"]:
                if test["target"] in test2["target"]:
                    del(testtest[test2index])

            if test["target"] in test2["source"]:
                if test["source"] in test2["target"]:
                    del(testtest[test2index])

    print(testtest)
    node=[]
    show_data["name"] = "hw_name"
    show_data["children"] = []
    firstIndex=0
    key = 0
    for tindex, t in enumerate(testtest):
        if tindex == 0:
            show_data["children"].append({"name":t["source"]})
            show_data["children"][firstIndex]["children"] = []
            show_data["children"][firstIndex]["children"].append({"name": t["target"], "size":t["size"]})
            ssindex = show_data["children"][firstIndex]["children"].index({"name": t["target"], "size": t["size"]})
            show_data["children"][firstIndex]["children"][ssindex]["children"] = []
            firstIndex+=1
            print(len(show_data["children"]))

        else:
            print("몇번째 testtest 냐면 ~~", tindex)
            if len(show_data["children"]) == 0 :
                show_data["children"].append({"name": t["source"]})
                show_data["children"][firstIndex]["children"] = []
                show_data["children"][firstIndex]["children"].append({"name": t["target"], "size": t["size"]})
                ssindex = show_data["children"][sindex]["children"].index({"name": t["target"], "size": t["size"]})
                show_data["children"][sindex]["children"][ssindex]["children"] = []
                firstIndex += 1
            else:
                for sindex, s in enumerate(show_data["children"]):
                    if t["target"] == s["name"]:
                        print("지금 넣을 타겟이 이전의 기준 노드에 있다. ")
                        show_data["children"][sindex]["children"].append({"name": t["source"], "size":t["size"]})
                        ssindex = show_data["children"][sindex]["children"].index({"name": t["source"], "size":t["size"]})
                        show_data["children"][sindex]["children"][ssindex]["children"] = []
                    elif t["source"] == s["name"]:
                        print("지금 넣을 소~~스가 이전의 기준 노드에 있다.")
                        show_data["children"][sindex]["children"].append({"name": t["target"], "size":t["size"]})
                        ssindex = show_data["children"][sindex]["children"].index({"name": t["target"], "size":t["size"]})
                        show_data["children"][sindex]["children"][ssindex]["children"] = []
                    else:
                        for ssindex, ss in enumerate(show_data["children"][sindex]["children"]):
                            # if ssindex == 0:
                            #     show_data["children"][sindex]["children"][ssindex]["children"] = []
                            if t["target"] == ss["name"]:
                                print("지금 넣을 타겟이 이전의 노드의 차일드 중 하나에 있다.")
                                show_data["children"][sindex]["children"][ssindex]["children"].append({"name": t["source"], "size": t["size"]})
                            elif t["source"] == ss["name"]:
                                print("지금 넣을 소~~~스가 이전의 노드의 차일드 중 하나에 있다.")
                                show_data["children"][sindex]["children"][ssindex]["children"].append({"name": t["target"], "size": t["size"]})
                            else:
                                key = -1

            if key == -1:
                show_data["children"].append({"name": t["source"]})
                show_data["children"][firstIndex]["children"] = []
                show_data["children"][firstIndex]["children"].append({"name": t["target"], "size": t["size"]})
                ssindex = show_data["children"][firstIndex]["children"].index({"name": t["target"], "size": t["size"]})
                show_data["children"][firstIndex]["children"][ssindex]["children"] = []
                firstIndex += 1
                key = 0

    with open('words.json','w',encoding="utf-8") as make_file:
        json.dump(file_data, make_file, ensure_ascii=False, indent="\t")

    with open('showwww.json', 'w', encoding="utf-8") as make_file:
        json.dump(show_data, make_file, ensure_ascii=False, indent="\t")