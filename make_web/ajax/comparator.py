import itertools
import os
import subprocess



def match_score_local(a,b):
    data=subprocess.check_output(('./source/lcs_pro',a,b))
    #print data
    return int(data)


def get_sequence_from(filename):
    #print('get sequence from ' + filename + '...')
    if filename.endswith(".java") != True :
    	ps = subprocess.Popen(('./source/lex_C', filename), stdout=subprocess.PIPE)

    else :
    	ps = subprocess.Popen(('./source/lex_JAVA', filename), stdout=subprocess.PIPE)
    	
    string = subprocess.check_output(('./source/re_pro'), stdin=ps.stdout)
    ps.wait()
    return string


