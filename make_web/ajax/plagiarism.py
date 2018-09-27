import os
import re
import itertools 
import comparator
import json
import math


REGEX = re.compile('.*[.](c|cpp|java|py)$')
def is_cppsrc(srcname):
    return (REGEX.match(srcname) != None)


def get_result(test_dir, lcs_mode):
    TEST_dir=test_dir
    print('preprocessing...')

    srcnames = filter(is_cppsrc,os.listdir(test_dir))

    seq_name_pairs = map(lambda srcname: 
                                (comparator.get_sequence_from(test_dir + srcname), srcname), srcnames[:])

    print('computing match scores of all pairs...')
    scores = []

    name_map=dict()
    count =0

    mother_score=dict()
    error_dna=[]

    nodes_array=[]
    seq_name_pairs2=[]

    re_lang=dict()

    re_lang["NofCode"]=len(seq_name_pairs)

    NofC=0
    NofCPP=0
    NofJAVA=0
    NofPY=0
    Nofelse=0

    mtc_N=0
    mtc=""

    for i in seq_name_pairs:

        ext=i[1].split('.')
        ext=ext[1]

        if ext == "c" :
            NofC+=1
        elif ext == "cpp" :
            NofCPP+=1
        elif ext == "java" :
            NofJAVA+=1
        # elif ext == "py" :
        #     NofPY+=1
        else :
            error_dna.append(i[1])
            Nofelse+=1
            continue

        token_count=i[0].count('#');

        if mtc_N < token_count :
            mtc=i[1]
            mtc_N=token_count

        if token_count < 35  :
            error_dna.append(i[1])
            continue

        str1=i[0]
        mother_score[i[1]]=0;

        if lcs_mode == 0:
            mother_score[i[1]]=comparator.match_score_A(str1,str1)
        else :
            mother_score[i[1]]=comparator.match_score_NA(str1,str1)


        name_map[i[1]]=i[1]
        re_node={"name":name_map[i[1]]}
        nodes_array.append(re_node)
        seq_name_pairs2.append(i)

    re_lang["NofC"]=NofC
    re_lang["NofCPP"]=NofCPP
    re_lang["NofJAVA"]=NofJAVA
    # re_lang["NofPY"]=NofPY

    for pair in itertools.combinations(seq_name_pairs2,2):
        (a,b) = pair
        str1=a[0]
        str2=b[0]


        str1=re.sub('#ID','',a[0])
        str2=re.sub('#ID','',b[0])

        score1=0;
        score2=0;

        if lcs_mode==0:
            score1=float(comparator.match_score_A(str1,str2))/float(mother_score[a[1]])
            score2=float(comparator.match_score_A(str2,str1))/float(mother_score[b[1]])
        else:
            score1=float(comparator.match_score_NA(str1,str2))/float(mother_score[a[1]])
            score2=float(comparator.match_score_NA(str2,str1))/float(mother_score[b[1]])

        
        # score1=float(comparator.match_score_local(str1,str2))/float(mother_score[a[1]])
        score1=score1*100
        # score2=float(comparator.match_score_local(str2,str1))/float(mother_score[b[1]])
        score2=score2*100
        score=max(score1,score2)

        if score >50.0:
            score=format(score,".4f")
            scores.append((score,a,b))

    scores.sort(reverse=True)

    result_st=[]
    result=dict()
    links_array=[]
    links_array2=[]
    count=1;
    for tup in scores:
        (score,a,b) = tup
        name_a = a[1]
        name_b = b[1]

        str_score=str(score)
        str_score=str_score[:5]

    

        len_a = a[0].count('#')
        len_b = b[0].count('#')
        re_link={"source":name_map[name_a],"target":name_map[name_b],"weight":str_score}
        links_array.append(re_link)
        result_st.append(re_score(count,name_a,len_a,name_b,len_b,score) )

        re_link2={"number":count,"file1":name_map[name_a],"len1":len_a, "file2":name_map[name_b],"len2":len_b, "score":str_score}
        links_array2.append(re_link2)

        count=count+1    

    result["nodes"]=nodes_array
    result["links"]=links_array



    # with open('example.json','w') as make_file:
    #     json.dump(result,make_file,indent=2)

    print('plotting result.')
    return (links_array2,nodes_array,links_array , error_dna, re_lang ,TEST_dir, mtc, mtc_N)


class re_score:
    def __init__(self,number ,file1, len1, file2, len2, score):
        self.number=number
        self.file1=file1
        self.len1=len1
        self.file2=file2
        self.len2=len2
        self.score=score
