import os
import re
import itertools 
import comparator
import json
import math

LEX = 0
ASM = 1

REGEX = re.compile('.*[.](c|cpp|java)$')
def is_cppsrc(srcname):
    return (REGEX.match(srcname) != None)


def get_result(test_dir):
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
    short_dna=[]
    good_dna=[]
    nodes_array=[]
    seq_name_pairs2=[]

    for i in seq_name_pairs:
        token_count=i[0].count('#');
        if token_count < 35  :
            if token_count <10 :
                error_dna.append(i[1])
            else :
                short_dna.append(i[1])
            continue

        # good_dna.append(i[1])
        # str1=i[0]
        # str1=re.sub('#ID','',i[0])
        # mother_score[i[1]]=comparator.match_score_local(str1,str1)
        # name_map[i[1]]=count
        # re_node={"name":name_map[i[1]]}
        # count=count+1
        # nodes_array.append(re_node)
        # seq_name_pairs2.append(i)

        good_dna.append(i[1])
        str1=i[0]
        str1=re.sub('#ID','',i[0])
        mother_score[i[1]]=comparator.match_score_local(str1,str1)
        name_map[i[1]]=i[1]
        re_node={"name":name_map[i[1]]}
        nodes_array.append(re_node)
        seq_name_pairs2.append(i)

    for pair in itertools.combinations(seq_name_pairs2,2):
        (a,b) = pair
        str1=a[0]
        str2=b[0]


        str1=re.sub('#ID','',a[0])
        str2=re.sub('#ID','',b[0])
        
        score1=float(comparator.match_score_local(str1,str2))/float(mother_score[a[1]])
        score2=float(comparator.match_score_local(str2,str1))/float(mother_score[b[1]])
        score=max(score1,score2)

        if score >0.20:
            score=format(score,".4f")
            scores.append((score,a,b))

    scores.sort(reverse=True)

    result_st=[]
    result=dict()
    links_array=[]
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
        count=count+1    

    result["nodes"]=nodes_array
    result["links"]=links_array

    with open('example.json','w') as make_file:
        json.dump(result,make_file,indent=2)


    

    print('plotting result.')
    return (result_st, json.dumps(result,indent=2), error_dna, short_dna, good_dna)


class re_score:
    def __init__(self,number ,file1, len1, file2, len2, score):
        self.number=number
        self.file1=file1
        self.len1=len1
        self.file2=file2
        self.len2=len2
        self.score=score
