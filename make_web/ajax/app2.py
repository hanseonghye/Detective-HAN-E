#-*- coding: utf-8 -*-

from flask import (
    Flask,
    request,
    render_template,
    send_from_directory,
    url_for,
    jsonify
)

import os, time, json, glob, sys
#from pprint import pprint
#from werkzeug import secure_filename

import plagiarism
import Graph

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

Adaptive={"on":0,"off":1}
Token={"rich":"R","small":"S"}

@app.route('/')
def index():
    return render_template('start.html')

@app.route('/start')
def start():
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
        (link, nd, ln, error_dna, re_lang, dire, mtc, mtc_N)=pro(filename,Adaptive[request.form['adaptive']], Token[request.form['token']])
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
            change_json["labels"].append(str(i["source"]+" : "+i["target"]))
            change_json["series"][0]["values"].append(i["weight"])

        endTime=time.time()-startTime
        endTime=format(endTime,".3f")
        G_data=Graph.get_graph(json_data);

        return jsonify(Time=endTime, pr=link , re_lang=re_lang, er=error_dna, dire=dire, maxTokenCode=mtc, maxToken=mtc_N,G_data=G_data,G_data2=change_json)

def pro(dir_name,adaptive, token_V):
    T_dir=dir_name
    T_dir=T_dir[:len(T_dir)-4]
    T_dire="./data/"+T_dir+time.strftime('%H%M%S')
    os.system('unzip ./images/'+T_dir+'.zip'+' -d '+T_dire)
    T_dire=T_dire+"/"

    return plagiarism.get_result(T_dire,adaptive, token_V)


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


if __name__=="__main__":
    app.run(host="0.0.0.0", port=3005, debug=True)
