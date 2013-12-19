#include<pyobj.h>
PyObject*pd_post(PyObject*const self,PyObject*const args)
{
	if(PyTuple_Check(args))
	{
		switch(PyTuple_Size(args))
		{
		case 0:
			post(PyString_AsString(Py_None));
			break;
		case 1:
			post(PyString_AsString(PyObject_Str(PyTuple_GetItem(args,0))));
			break;
		default:
			post(PyString_AsString(PyObject_Str(args)));
			break;
		}
	}
	return Py_None;
}
PyObject*pd_send(PyObject*const self,PyObject*const args)
{	
	if(PyTuple_Check(args))
	{
		if(PyTuple_Size(args))
		{
			PyObject*target=PyTuple_GetItem(args,0);
			if(PyCObject_Check(target))
				pyobj_send(PyCObject_AsVoidPtr(target),args);
		}
	}
	return Py_None;
}
PyObject*pd_seta(PyObject*const self,PyObject*const args)
{
	PyObject*ret=Py_None;
	if(args)
	{
		if(PyTuple_Check(args)&&PyTuple_Size(args)==2)
		{
			PyObject*k=PyTuple_GetItem(args,0);
			float v=PyFloat_AsDouble(PyTuple_GetItem(args,1));
			value_setfloat(gensym(PyString_AsString(k)),v);
			ret=PyFloat_FromDouble(v);
		}
	}
	return ret;
}
PyObject*pd_geta(PyObject*const self,PyObject*const args)
{
	PyObject*ret=Py_None;
	if(args)
	{
		if(PyTuple_Check(args)&&PyTuple_Size(args)==1)
		{
			PyObject*k=PyTuple_GetItem(args,0);
			float v;
			value_getfloat(gensym(PyString_AsString(k)),&v);
			ret=PyFloat_FromDouble(v);
		}
	}
	return ret;
}
