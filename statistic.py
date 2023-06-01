import sys
import pandas as pd
print(sys.argv[1])
data=pd.read_csv(sys.argv[1])
maxim=max(data)
print(maxim)
