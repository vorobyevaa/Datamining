#include "datameaningcore.h"
#include <QtDebug>

DataMeaningCore::DataMeaningCore()
{
     PythonQt::init();

     // get a smart pointer to the __main__ module of the Python interpreter
    // PythonQtObjectPtr context = PythonQt::self()->getMainModule();

     qDebug()<<"init python";

     // add a QObject as variable of name "example" to the namespace of the __main__ module
   /*  PyExampleObject example;
     context.addObject("example", &example);

     // do something
     context.evalScript("print example");
     context.evalScript("def multiply(a,b):\n  return a*b;\n");
     QVariantList args;
     args << 42 << 47;
     QVariant result = context.call("multiply", args);*/
}
