import datetime
from dateutil.relativedelta import relativedelta

cur=datetime.datetime.now()-relativedelta(months=3)
cur=cur.strftime('%y-%m-%d, %H:%M')



print cur

date1='2018-06-06, 04:11'
date2='2018-06-03, 11:12'


print cur>date2
print cur<date2
