#include<pyobj.h>
void pyobj_init(t_pyobj*const ins)
{
	if(ins->local)
		Py_DECREF(ins->local);
	Py_INCREF(ins->local=PyDict_New());
	//PyErr_Print();
	PyErr_Clear();
}

