import itertools
import os
import subprocess



def match_score_local(a,b):
    data=subprocess.check_output(('./source/lcs_pro',a,b))
    #print data
    return int(data)

def match_score_A(a,b):
    data=subprocess.check_output(('./source/Alcs_pro',a,b))
    #print data
    return int(data)

def match_score_NA(a,b):
    data=subprocess.check_output(('./source/nAlcs_pro',a,b))
    #print data
    return int(data)

def get_sequence_from(filename,V):
    #print('get sequence from ' + filename + '...')
    if filename.endswith(".java") == True :
        ps = subprocess.Popen(('./source/lex_JAVA'+V, filename), stdout=subprocess.PIPE)

    else :
        ps = subprocess.Popen(('./source/lex_C'+V, filename), stdout=subprocess.PIPE)
    	
    string = subprocess.check_output(('./source/re_pro'), stdin=ps.stdout)
    ps.wait()
    return string


