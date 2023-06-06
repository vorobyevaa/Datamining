import sys

if (len(sys.argv) == 2):
    print("hist")
else:
    print("predict")
    model= {"name":[1,2,3],"age":[2,8,7]}
    weight= {"name" : 1, "age" :3}
    data={"model": model, "weight": weight}
    print(data);

