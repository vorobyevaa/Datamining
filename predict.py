import sys
import pandas as pd

if (len(sys.argv) == 2):
    data=pd.read_csv(sys.argv[1])
    
    cnt=data.value_counts()
    print(cnt.to_string())
else:
    print("predict")
    model= {"name":[1,2,3],"age":[2,8,7]}
    weight= {"name" : 1, "age" :3}
    data={"model": model, "weight": weight}
    print(data);

