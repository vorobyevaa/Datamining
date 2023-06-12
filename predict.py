import sys
import pandas as pd
import sklearn
import numpy as np

from sklearn.model_selection import train_test_split

#sys.stdout.encoding


if (len(sys.argv) == 2):
    data=pd.read_csv(sys.argv[1])
    
    cnt=data.value_counts()
    print(cnt.to_string())
else:
    print("predict")
    x=pd.read_csv(sys.argv[1])
    y=pd.read_csv(sys.argv[2])
    number=sys.argv[3]
    print (type(int(number)))
    #name columns
    cols=y.columns
    print(cols[0])
    #delete columns predict
    x.drop(cols,axis=1,inplace=True)
    print(x)
    print("\n\n");
    print(y)
    
    x_train, x_test, y_train, y_test = train_test_split(x, y, test_size=0.2, random_state=0)
    from sklearn.linear_model import LinearRegression 
    regressor = LinearRegression() 
    regressor.fit(x_train, y_train)
       
    
    r=regressor.coef_.tolist()
    #print(regressor.intercept_)
    b=regressor.intercept_.tolist()

          
    coeff_df = pd.DataFrame({ 'Название':x.columns,'Коэффициент':r[0],'Точка пересечения':b[0]})  
    print(coeff_df)
    
    y_pred = regressor.predict(x_test)
    
    print(y_test.columns)
    #frames=[y_test,y_pred]
    #result=pd.concat(frames)
    #result=y_test.append(y_pred)
    #df = pd.DataFrame({'Actual': y_test, 'Predicted': y_pred}) 
    print("\n\n");
    #print(result)
    
    from sklearn import metrics 
    print('Mean Absolute Error:', metrics.mean_absolute_error(y_test, y_pred)) 
    print('Mean Squared Error:', metrics.mean_squared_error(y_test, y_pred)) 
    print('Root Mean Squared Error:', np.sqrt(metrics.mean_squared_error(y_test, y_pred)))
    er={'Mean Absolute Error':metrics.mean_absolute_error(y_test, y_pred),'Mean Squared Error:': metrics.mean_squared_error(y_test, y_pred),'Root Mean Squared Error:': np.sqrt(metrics.mean_squared_error(y_test, y_pred))}
    #erdf=pd.DataFrame(er)


    
    model= {"name":[1,2,3],"age":[2,8,7]}
    weight= {"name" : 1, "age" :3}
    data={"model":  coeff_df}
    print(coeff_df)
    print(data)
    #print(json.dumps(out,         sort_keys=False,         indent=4,           ensure_ascii=False,                     separators=(',', ': ')))
    
col=len(coeff_df.axes[1])
print (len(coeff_df.axes[0]))

table={}
for i in range(0,col,1):
    n=coeff_df.columns[i]
    table[n]=coeff_df.iloc[:,i].tolist()
    
print(table)   

jsoon={"Model":table,"Error":er}
print(jsoon)
#print({coeff_df.columns[1]:coeff_df.iloc[:,1].tolist()})

