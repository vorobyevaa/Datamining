import sys
import pandas as pd

data=pd.read_csv(sys.argv[1])

#count rows
rows=len(data.axes[1])

typ=data.dtypes
for col in data.columns:
    if data.dtypes[col]=='object':
        data.drop(col,axis=1,inplace=True)
        rows=rows-1
#    if typ[i]=='int64':
#        typ[i]='Целые'
#    elif typ[i]=='float64':
#        typ[i]='Дробные' 
#    elif typ[i]=='object':
#        typ[i]='Символьные'    

print(typ.to_string())
print("\n\n");

ct=data.count()
print(ct.to_string())
print("\n\n");

maxim=data.max()
print(maxim.to_string())
print("\n\n");

manim=data.min()
print(manim.to_string())
print("\n\n");




#s=data['Второй столбец'].value_counts()
#print("ddd",s)

for i in range(0,rows,1):
    if data.dtypes[i]!='object':
        mn=data.mean(numeric_only=True)
        

print(mn.to_string())
print("\n\n");


st=data.std(numeric_only=True)
print(st.to_string())
print("\n\n");

q25=data.quantile(.25,numeric_only=True)
print(q25.to_string())
print("\n\n");

q50=data.quantile(.50,numeric_only=True)
print(q50.to_string())
print("\n\n");

q75=data.quantile(.75,numeric_only=True)
print(q75.to_string())
print("\n\n");
# разброс средних
print((q75-q25).to_string())
print("\n\n");
# дисперсия
vr=data.var(numeric_only=True)
print(vr.to_string())


