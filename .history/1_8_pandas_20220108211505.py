import pandas as pd

# pd.DataFrame()生成一个最小的数据集
df = pd.DataFrame("")

# 可以直接输出查看数据集
print(df)

# to_excel()表示把数据集转换为excel格式，需要提供文件的路径,似乎只能使用绝对路径
df.to_excel("1_8_pandas.xlsx")

print("Done!")