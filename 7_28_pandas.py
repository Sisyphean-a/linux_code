import pandas
import numpy

df1=pandas.DataFrame([1,2,3],[4,5,6])
#print(df1)
df2=pandas.DataFrame([[1,2,3],[4,5,6]],index=['row1','row2'],columns=['c1','c2','c3'])
print(df2)
