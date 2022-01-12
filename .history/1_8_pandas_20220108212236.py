import pandas as pd

# pd.DataFrame()生成一个数据帧，最小的数据集
df = pd.DataFrame({"id":[1,2,3],"name":["i","o","u"]})

# 输出查看数据帧
print(df)

#可以发现，开头自带了一个索引列，我们可以自己设置索引
df = df.set_index('id')
print(df)

# to_excel()表示把数据帧转换为excel格式，需要提供文件的路径
df.to_excel("./1_8_pandas.xlsx")

print("Done!")