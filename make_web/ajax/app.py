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
import plagiarism 

basedir = os.path.abspath(os.path.dirname(__file__))
app = Flask(__name__)




from logging import Formatter, FileHandler
handler = FileHandler(os.path.join(basedir, 'log.txt'), encoding='utf8')
handler.setFormatter(
    Formatter("[%(asctime)s] %(levelname)-8s %(message)s", "%Y-%m-%d %H:%M:%S")
)
app.logger.addHandler(handler)


app.config['ALLOWED_EXTENSIONS'] = set(['txt', 'pdf', 'png', 'jpg', 'jpeg', 'gif'])



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

		file=request.files['file']
		filename=file.filename
		destination="/".join([target, filename])
		file.save(destination)

		if filename.endswith(".zip")!=True:
			return render_template("home.html")


		(link, file, json_data, error_dna, good_dna)=pro(filename)

		endTime=time.time()-startTime
		endTime=format(endTime,".3f")

		json_result=dict()
		json_result["result"]=link
		json_result["file"]=file

		return jsonify(Time=endTime, good=good_dna, pr=json_result["result"] , er=error_dna, re_1=show_R(), re_2=show_pla_R())




def pro(dir_name):
    T_dir=dir_name
    T_dir=T_dir[:len(T_dir)-4]
    T_dire="./data/"+T_dir+time.strftime('%H%M%S')
    os.system('unzip ./images/'+T_dir+'.zip'+' -d '+T_dire)
    T_dire=T_dire+"/"
    DIRE=T_dire
    return plagiarism.get_result(T_dire)

def show_pla_R():


	html="""
		<form id="result">
			{% for num in pr %}
				<p> {{num.file1}}</p>
			{% endfor %}
		</form>
		"""
	return html


def show_pla_R2():


	html="""

		<table>
			<thead>
				<tr>
					<th><div style="margin-right:30px;">No.    </div></th>
					<th><div style="margin-right:30px;">File1  </div></th>
					<th><div style="margin-right:30px;">Len1   </div></th>
					<th><div style="margin-right:30px;">File2  </div></th>
					<th><div style="margin-right:30px;">Len2   </div></th>
					<th><div style="margin-right:100px;">Score </div></th>
				</tr>
			</thead>
			<form id="result">
			<tbody>
				
				{% for num in pr %}
					<tr>
						<td><div class="table_style"> {{num.number}}</div></td>									
							<td><input style="border:0px" name="file1" type="text"  value={{num.file1}} readonly></td>
							<td><div class="table_style"> {{num.len1}}  </div></td>
							<td><input style="border:0px" name="file2" type="text"  value={{num.file2}} readonly></td>
							<td><div class="table_style"> {{num.len2}}  </div></td>
							<td><input style="margin-right:100px; background: #ffffff; border: 0px;" type="submit" value={{num.score}} ></td>
					</tr>
				{% endfor %}
				
			</tbody>
			</form>

		</table>
		"""
	return html

def show_R():
	html="""
		<h3 style="display:inline-block;">Time : </h3>
		<h3 style="display:inline-block;" id="time">{{Time}} </h3>
		<br>

		<p style="font-size:20px; color:#0080FF; bold; "> VAILE CODE </p>
		<form id="good_code" action="{{ url_for('show_good_code') }}" method="GET">
			{% for num in good %}
				<input type="submit" name="good_code" id="good_code" value={{num}}>

			{% endfor %}
		</form>
		<hr>

		<p style="font-size:20px; color:#0080FF; bold;"> INVAILD CODE </p>
		<form id="er_code" action="{{ url_for('show_strange_code') }}" method="GET">
			{% for num in er %}
				<input tupe="submit" name="strange_code" id="er_code" value={{num}} &nbsp;&nbsp;&nbsp;>
			{% endfor %}
		</form>

		"""
	return html





if __name__=="__main__":
    app.run(host="0.0.0.0", port=3003, debug=True)
