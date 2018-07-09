#-*- coding: utf-8 -*-

import os
import time
import json
import glob

from flask import Flask, render_template, request, flash
import plagiarism 
import sys  

reload(sys)  
sys.setdefaultencoding('Cp1252')

app = Flask(__name__)
app.secret_key="2342asfkjawesld234kfjsld123111"
APP_ROOT = os.path.dirname(os.path.abspath(__file__))


json_data=""
DIRE=""
startTime=0

@app.route("/")
def index():
    return render_template("upload.html")

@app.route("/upload", methods=['POST'])
def upload():
    global startTime
    startTime=time.time()

    target = os.path.join(APP_ROOT, 'images/')
    print(target)

    if not os.path.isdir(target):
        os.mkdir(target)


    if 'file' not in request.files:
    	flash('input file !')
        return render_template("upload.html")
    file=request.files['file']
    print(file)
    filename = file.filename
    destination = "/".join([target, filename])
    print(destination)
    file.save(destination)


    if filename.endswith(".zip") != True :
    	flash('input only zip file !')
        return render_template("upload.html")

    global json_data
    (result, json_data, error_dna, short_dna, good_dna)=pro(filename)
    
    endTime=time.time()-startTime
    endTime=format(endTime,".3f")

    flash('okoko')


    return render_template('complete.html',pr=result,good=good_dna, er=error_dna, short=short_dna, Time=endTime)


@app.route("/complete", methods=['POST'])
def complete():
    return render_template('view_graph.html',data=json_data)

@app.route("/show_code", methods=['GET'])
def show_code():
    file1_name= request.args.get('file1')
    file2_name= request.args.get('file2')

    path_file1=DIRE+file1_name
    path_file2=DIRE+file2_name

    file1=open(path_file1,'r')
    file2=open(path_file2,'r')

    return render_template('show_code.html', File1_name=file1_name+"\n",File2_name=file2_name+"\n",File1=file1.read(), File2=file2.read())

@app.route("/show_strange_code", methods=['GET'])
def show_strange_code():
    strange_name= request.args.get('strange_code')

    path_file=DIRE+strange_name
    strange_file=open(path_file,'r')
    return render_template('show_one_code.html', File_name=strange_name+"\n", File=strange_file.read())

@app.route("/show_short_code", methods=['GET'])
def show_short_code():
    short_name= request.args.get('short_code')

    path_file=DIRE+short_name
    short_file=open(path_file,'r')
    return render_template('show_one_code.html', File_name=short_name+"\n", File=short_file.read())

@app.route("/show_good_code", methods=['GET'])
def show_good_code():
    good_name=request.args.get('good_code')
    path_file=DIRE+good_name
    good_file=open(path_file,'r')
    return render_template('show_one_code.html', File_name=good_name+"\n", File=good_file.read())

def pro(dir_name):
    T_dir=dir_name
    T_dir=T_dir[:len(T_dir)-4]
    T_dire="./data/"+T_dir+time.strftime('%H%M%S')
    os.system('unzip ./images/'+T_dir+'.zip'+' -d '+T_dire)
    T_dire=T_dire+"/"
    global DIRE
    DIRE=T_dire
    #(re,d)=plagiarism.get_result(T_dire)

    return plagiarism.get_result(T_dire)

if __name__ == "__main__":
    app.run(port=3570, debug=True)
    


