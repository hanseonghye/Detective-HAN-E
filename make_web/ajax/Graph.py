from collections import OrderedDict

def get_graph(data):
    file_data = OrderedDict()
    show_data = OrderedDict()
    # with open('example.json') as data_file:
    #     data = json.load(data_file)

    nodess = []
    linkss = []
    testtest = []

    for h in data["nodes"]:
        nodess.append(h)

    for l in data["links"]:
        linkss.append(l)

    file_data["children"] = []
    for aindex, a in enumerate(nodess):
        file_data["children"].append({"name": a["name"]})
        file_data["children"][aindex]["children"] = []

        for index, b in enumerate(linkss):
            if (a["name"] == b["target"]):
                file_data["children"][aindex]["children"].append({"name": b["source"], "rule": b["weight"]})

            elif (a["name"] == b["source"]):
                file_data["children"][aindex]["children"].append({"name": b["target"], "rule": b["weight"]})

    for index, file in enumerate(file_data["children"]):
        if len(file["children"]):
            testtest.append(
                {"source": file["name"], "target": file["children"][0]["name"], "rule": file["children"][0]["rule"]})

    for testindex, test in enumerate(testtest):
        for test2index, test2 in enumerate(testtest):
            if testindex != test2index:
                if test["source"] == test2["target"]:
                    if test["target"] == test2["source"]:
                        del (testtest[test2index])

    # print(testtest)
    node = []
    show_data["children"] = []
    firstIndex = 0
    key = 0

    for tindex, t in enumerate(testtest):
        if tindex == 0:
            show_data["children"].append({"name": t["source"]})
            show_data["children"][firstIndex]["children"] = []
            show_data["children"][firstIndex]["children"].append({"name": t["target"], "rule": t["rule"]})
            ssindex = show_data["children"][firstIndex]["children"].index({"name": t["target"], "rule": t["rule"]})
            show_data["children"][firstIndex]["children"][ssindex]["children"] = []
            firstIndex += 1

        else:
            if len(show_data["children"]) == 0:
                show_data["children"].append({"name": t["source"]})
                show_data["children"][firstIndex]["children"] = []
                show_data["children"][firstIndex]["children"].append({"name": t["target"], "rule": t["rule"]})
                ssindex = show_data["children"][firstIndex]["children"].index({"name": t["target"], "rule": t["rule"]})
                show_data["children"][firstIndex]["children"][ssindex]["children"] = []
                firstIndex += 1
                key = 0
                break
            else:
                for sindex, s in enumerate(show_data["children"]):
                    if t["target"] == s["name"]:
                        show_data["children"][sindex]["children"].append({"name": t["source"], "rule": t["rule"]})
                        ssindex = show_data["children"][sindex]["children"].index(
                            {"name": t["source"], "rule": t["rule"]})
                        show_data["children"][sindex]["children"][ssindex]["children"] = []
                        key = 0
                        break
                    elif t["source"] == s["name"]:
                        show_data["children"][sindex]["children"].append({"name": t["target"], "rule": t["rule"]})
                        ssindex = show_data["children"][sindex]["children"].index(
                            {"name": t["target"], "rule": t["rule"]})
                        show_data["children"][sindex]["children"][ssindex]["children"] = []
                        key = 0
                        break
                    else:
                        for ssindex, ss in enumerate(show_data["children"][sindex]["children"]):
                            if t["target"] == ss["name"]:
                                if t["source"] != s["name"]:
                                    show_data["children"][sindex]["children"][ssindex]["children"].append(
                                        {"name": t["source"], "rule": t["rule"]})
                                else:
                                    break
                                key = 0
                                break
                            elif t["source"] == ss["name"]:
                                if t["target"] != s["name"]:
                                    show_data["children"][sindex]["children"][ssindex]["children"].append(
                                        {"name": t["target"], "rule": t["rule"]})
                                else:
                                    break
                                key = 0
                                break
                            else:
                                key = -1

                if key == -1:
                    show_data["children"].append({"name": t["source"]})
                    show_data["children"][firstIndex]["children"] = []
                    show_data["children"][firstIndex]["children"].append({"name": t["target"], "rule": t["rule"]})
                    ssindex = show_data["children"][firstIndex]["children"].index(
                        {"name": t["target"], "rule": t["rule"]})
                    show_data["children"][firstIndex]["children"][ssindex]["children"] = []
                    firstIndex += 1
                    key = 0
    return show_data
