#ifndef PYTHONPARAMETER_H
#define PYTHONPARAMETER_H

//#include "PythonQt.h"
//#include "PythonQtCppWrapperFactory.h"
#include <QObject>

class PythonParameter
{
public:
    PythonParameter();

    QString filename;
};

class PythonParameterWrapper : public QObject {

  Q_OBJECT

public Q_SLOTS:
  // add a constructor
  PythonParameter* new_PythonParameter() { return new PythonParameter(); }

  // add a destructor
  void delete_PythonParameter(PythonParameter* o) { delete o; }

  // add access methods
  QString filename(PythonParameter* o) { return o->filename; }

  void setFilename(PythonParameter* o, const QString& filename) { o->filename = filename; }


};

#endif // PYTHONPARAMETER_H
