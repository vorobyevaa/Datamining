import sys
import pandas as pd
print(sys.argv[1])
data=pd.read_csv(sys.argv[1])
maxim=data.max()
print(maxim)
manim=data.min()
print(manim)
typ=data.dtypes
print(typ)
mn=data.mean()
print(mn)
# еще можно вот так все выводить
t=data.describe(include='all')
print(t)


