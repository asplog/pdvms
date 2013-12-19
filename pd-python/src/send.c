#include<pyobj.h>
void pyobj_send(t_outlet*const outlet,PyObject*const value)
{
	if(!value);
	else if(value==Py_True)
		outlet_bang(outlet);
	else if(value==Py_False)
		outlet_symbol(outlet,&s_);
	else if(PyInt_Check(value))
		outlet_float(outlet,PyInt_AsLong(value));
	else if(PyFloat_Check(value))
		outlet_float(outlet,PyFloat_AsDouble(value));
	else if(PyString_Check(value))
		outlet_symbol(outlet,gensym(PyString_AsString(value)));
	else if(PyDict_Check(value))
	{
	}
	else if(PyList_Check(value))
	{
		register int k,K;
		Py_ssize_t size=PyList_Size(value);
		t_atom*atom=(t_atom*)calloc(sizeof(t_atom),size);
		for(k=0,K=size;k<K;++k)
		{
			PyObject*obj=PyList_GetItem(value,k);
			if(!obj)
				SETSYMBOL(atom+k,&s_);
			else if(obj==Py_True)
				SETFLOAT(atom+k,1);
			else if(obj==Py_False)
				SETSYMBOL(atom+k,&s_);
			else if(PyInt_Check(obj))
				SETFLOAT(atom+k,PyInt_AsLong(obj));
			else if(PyFloat_Check(obj))
				SETFLOAT(atom+k,PyFloat_AsDouble(obj));
			else
				SETSYMBOL(atom+k,&s_);
		}
		outlet_list(outlet,gensym("list"),size,atom);
	}
	else if(PyTuple_Check(value))
	{
		register int k,K;
		Py_ssize_t size=PyTuple_Size(value);
		t_atom*atom=(t_atom*)calloc(sizeof(t_atom),size);
		for(k=0,K=size;k<K;++k)
		{
			PyObject*obj=PyTuple_GetItem(value,k);
			if(!obj)
				SETSYMBOL(atom+k,&s_);
			else if(obj==Py_True)
				SETFLOAT(atom+k,1);
			else if(obj==Py_False)
				SETSYMBOL(atom+k,&s_);
			else if(PyInt_Check(obj))
				SETFLOAT(atom+k,PyInt_AsLong(obj));
			else if(PyFloat_Check(obj))
				SETFLOAT(atom+k,PyFloat_AsDouble(obj));
			else
				SETSYMBOL(atom+k,&s_);
		}
		outlet_list(outlet,gensym("list"),size,atom);
	}
}
void pyobj_dump(t_pyobj*const ins)
{
//	PyObject*err=PyErr_Occurred();
//	if(!err);
//	else if(PyString_Check(err))
//		post("pyobj: %s",PyString_AsString(PyObject_Str(err)));
	PyErr_Print();
	PyErr_Clear();
}
