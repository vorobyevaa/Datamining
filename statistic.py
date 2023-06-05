import sys
import pandas as pd

data=pd.read_csv(sys.argv[1])
maxim=data.max()
print(maxim)
print("\n\n");

manim=data.min()
print(manim)
print("\n\n");

typ=data.dtypes
print(typ)
print("\n\n");

mn=data.mean()
print(mn)
print("\n\n");


