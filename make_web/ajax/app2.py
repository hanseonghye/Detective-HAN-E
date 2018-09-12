#-*- coding: utf-8 -*-

from flask import (
    Flask,
    request,
    render_template,
    send_from_directory,
    url_for,
    jsonify
)
from werkzeug import secure_filename
import os, time, json, glob, sys
from pprint import pprint
from collections import OrderedDict

import plagiarism

reload(sys)
sys.setdefaultencoding('utf-8')
basedir = os.path.abspath(os.path.dirname(__file__))
app = Flask(__name__)


from logging import Formatter, FileHandler
handler = FileHandler(os.path.join(basedir, 'log.txt'), encoding='utf8')
handler.setFormatter(
    Formatter("[%(asctime)s] %(levelname)-8s %(message)s", "%Y-%m-%d %H:%M:%S")
)
app.logger.addHandler(handler)


app.config['ALLOWED_EXTENSIONS'] = set(['txt', 'pdf', 'png', 'jpg', 'jpeg', 'gif'])

Adaptive={"on":0,"off":1}

@app.route('/')
def index():
    return render_template('home.html')

@app.route('/fileUpload', methods=['POST'])
def fileUpload():

    if request.method =='POST':
        if 'file' not in request.files:
            return render_template("home.html")

        startTime=time.time()
        target=os.path.join(basedir,'images/')
        print "start..."

        file=request.files['file']
        filename=file.filename
        destination=target+filename
        file.save(destination)

        if filename.endswith(".zip")!=True:
            return render_template("home.html")

        json_data=dict()
        (link, nd, ln, error_dna, re_lang, dire, mtc, mtc_N)=pro(filename,Adaptive[request.form['adaptive']])
        json_data["nodes"]=nd
        json_data["links"]=ln

        try_jsonData=ln
        try_jsonData=sorted(try_jsonData, key=lambda x:-(float(x["weight"])))

        change_json=dict()
        change_json["labels"]=[]
        change_json["series"]=[
                {
                    "label": 'label',
                    "values": []
                },
            ]

        for i in try_jsonData :
            change_json["labels"].append(i["source"]+","+i["target"])
            change_json["series"][0]["values"].append(i["weight"])

        endTime=time.time()-startTime
        endTime=format(endTime,".3f")
        G_data=get_graph(json_data);

        return jsonify(Time=endTime, pr=link , re_lang=re_lang, er=error_dna, dire=dire, maxTokenCode=mtc, maxToken=mtc_N,G_data=G_data,G_data2=change_json)

def pro(dir_name,adaptive):
    T_dir=dir_name
    T_dir=T_dir[:len(T_dir)-4]
    T_dire="./data/"+T_dir+time.strftime('%H%M%S')
    os.system('unzip ./images/'+T_dir+'.zip'+' -d '+T_dire)
    T_dire=T_dire+"/"

    return plagiarism.get_result(T_dire,adaptive)


@app.route("/show_code", methods=['GET'])
def show_code():
    DIRE= request.args.get('where_dir')
    file1_name= request.args.get('file1')
    file2_name= request.args.get('file2')

    path_file1=DIRE+file1_name
    path_file2=DIRE+file2_name

    file1=open(path_file1,'r')
    file2=open(path_file2,'r')
    return render_template('show_code.html',File1_name=file1_name+"\n",File2_name=file2_name+"\n", File1=file1.read(), File2=file2.read())

@app.route("/show_one_code", methods=['GET'])
def show_one_code():
    DIRE= request.args.get('where_dir')
    file1_name= request.args.get('file1')
    path_file1=DIRE+file1_name
    file1=open(path_file1,'r')
    return render_template('show_one_code.html',File_name=file1_name+"\n", File=file1.read())


def get_graph(data):
    file_data = OrderedDict()
    show_data = OrderedDict()
    # with open('example.json') as data_file:
    #     data = json.load(data_file)

    nodess = []
    linkss = []
    testtest=[]

    for h in data["nodes"]:
        nodess.append(h)

    for l in data["links"]:
        linkss.append(l)

    file_data["children"] = []
    for aindex, a in enumerate(nodess):
        file_data["children"].append({"name":a["name"]})
        file_data["children"][aindex]["children"] = []

        for index, b in enumerate(linkss):
            if ( a["name"] == b["target"]) :
                file_data["children"][aindex]["children"].append({"name": b["source"], "rule": b["weight"]})

            elif (a["name"] == b["source"]):
                file_data["children"][aindex]["children"].append({"name": b["target"], "rule": b["weight"]})

    for index, file in enumerate(file_data["children"]):
        if len(file["children"]):
            testtest.append({"source":file["name"], "target":file["children"][0]["name"], "rule":file["children"][0]["rule"]})

    for testindex, test in enumerate(testtest):
        for test2index, test2 in enumerate(testtest):
            if testindex != test2index:
                if test["source"] == test2["target"]:
                    if test["target"] == test2["source"]:
                        del(testtest[test2index])

    # print(testtest)
    node=[]
    show_data["children"] = []
    firstIndex=0
    key = 0

    for tindex, t in enumerate(testtest):
        if tindex == 0:
            show_data["children"].append({"name":t["source"]})
            show_data["children"][firstIndex]["children"] = []
            show_data["children"][firstIndex]["children"].append({"name": t["target"], "rule":t["rule"]})
            ssindex = show_data["children"][firstIndex]["children"].index({"name": t["target"], "rule": t["rule"]})
            show_data["children"][firstIndex]["children"][ssindex]["children"] = []
            firstIndex+=1

        else:
            if len(show_data["children"]) == 0 :
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
                        show_data["children"][sindex]["children"].append({"name": t["source"], "rule":t["rule"]})
                        ssindex = show_data["children"][sindex]["children"].index({"name": t["source"], "rule":t["rule"]})
                        show_data["children"][sindex]["children"][ssindex]["children"] = []
                        key = 0
                        break
                    elif t["source"] == s["name"]:
                        show_data["children"][sindex]["children"].append({"name": t["target"], "rule":t["rule"]})
                        ssindex = show_data["children"][sindex]["children"].index({"name": t["target"], "rule":t["rule"]})
                        show_data["children"][sindex]["children"][ssindex]["children"] = []
                        key = 0
                        break
                    else:
                        for ssindex, ss in enumerate(show_data["children"][sindex]["children"]):
                            if t["target"] == ss["name"]:
                                if t["source"] != s["name"]:
                                    show_data["children"][sindex]["children"][ssindex]["children"].append({"name": t["source"], "rule": t["rule"]})
                                else:
                                    break
                                key = 0
                                break
                            elif t["source"] == ss["name"]:
                                if t["target"] != s["name"]:
                                    show_data["children"][sindex]["children"][ssindex]["children"].append({"name": t["target"], "rule": t["rule"]})
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
                    ssindex = show_data["children"][firstIndex]["children"].index({"name": t["target"], "rule": t["rule"]})
                    show_data["children"][firstIndex]["children"][ssindex]["children"] = []
                    firstIndex += 1
                    key = 0
    return show_data




if __name__=="__main__":
    app.run(host="0.0.0.0", port=3005, debug=True)
