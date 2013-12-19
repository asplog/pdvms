#include<pyobj.h>
static t_class*		pyobj_class;
static PyObject*	global;
void pyobj_setup()
{
	pyobj_class=class_new
	(
		gensym("pyobj"),
		(t_newmethod)pyobj_new,
		(t_method)pyobj_del,
		sizeof(t_pyobj),
		CLASS_DEFAULT,
		A_DEFSYMBOL,
		0
	);
	class_doaddfloat(pyobj_class,(t_method)pyobj_dofn);	
	class_addbang(pyobj_class,(t_method)pyobj_bang);	
	class_addmethod(pyobj_class,(t_method)pyobj_init,gensym("init"),0);	
	class_addmethod(pyobj_class,(t_method)pyobj_eval,gensym("eval"),A_GIMME,0);	
	class_addmethod(pyobj_class,(t_method)pyobj_exec,gensym("exec"),A_GIMME,0);	
	class_addmethod(pyobj_class,(t_method)pyobj_load,gensym("load"),A_DEFSYMBOL,0);	
//	class_addmethod(pyobj_class,(t_method)pyobj_opts,gensym(";"),A_GIMME,0);	
	class_addmethod(pyobj_class,(t_method)pyobj_call,&s_anything,A_GIMME,0);
}
void*pyobj_new(const t_symbol*s)
{
	t_pyobj*ins=(t_pyobj*)pd_new(pyobj_class);
	ins->local=0;
	ins->global=global;
	pyobj_init(ins);
	pyobj_load(ins,s);
	if(0)
	{
		register unsigned int k,K;
		PyObject*count=PyDict_GetItemString(ins->local,"inlet");
		ins->icount=count&&PyInt_Check(count)&&PyInt_AsLong(count)>0?PyInt_AsLong(count):1;
		PyObject*inlet=PyTuple_New(ins->icount);
		ins->inlet=calloc(ins->icount,sizeof(t_inlet*));
		PyTuple_SetItem(inlet,0,Py_None);
		for(k=1,K=ins->icount;k<K;++k)
		{

		}
			PyTuple_SetItem(inlet,k,PyCObject_FromVoidPtr(ins->inlet[k]=inlet_new(&ins->self,&ins->self.ob_pd,&s_,gensym(";")),0));
		PyDict_SetItemString(ins->local,"inlet",inlet);
	}
	{
		register unsigned int k,K;
		PyObject*count=PyDict_GetItemString(ins->local,"outlet");
		ins->ocount=count&&PyInt_Check(count)&&PyInt_AsLong(count)>0?PyInt_AsLong(count):1;
		PyObject*outlet=PyTuple_New(ins->ocount);
		ins->outlet=calloc(ins->ocount,sizeof(t_outlet*));
		for(k=0,K=ins->ocount;k<K;++k)
			PyTuple_SetItem(outlet,k,PyCObject_FromVoidPtr(ins->outlet[k]=outlet_new(&ins->self,&s_anything),0));
		PyDict_SetItemString(ins->local,"outlet",outlet);
	}
	return ins;
}
void pyobj_del(t_pyobj const*ins)
{
	{
		register unsigned int k,K;
		for(k=0,K=ins->ocount;k<K;++k)
			outlet_free(ins->outlet[k]);
		free(ins->outlet);
	}
	{
		register unsigned int k,K;
		for(k=0,K=ins->icount;k<K;++k)
			inlet_free(ins->inlet[k]);
		free(ins->inlet);
	}
	Py_DECREF(ins->local);
}
void __attribute__((constructor))init()
{
	Py_Initialize();
	Py_SetProgramName("pd");
	Py_DontWriteBytecodeFlag = 1;
	global=PyModule_GetDict(PyImport_AddModule("__main__"));
	static PyMethodDef pdmethod[]=
	{
		{"post",(PyCFunction)pd_post,METH_VARARGS,0},
		{"send",(PyCFunction)pd_send,METH_VARARGS,0},
		{"set",(PyCFunction)pd_seta,METH_VARARGS,0},
		{"get",(PyCFunction)pd_geta,METH_VARARGS,0},
		{0}
	};
	{
		PyObject*module=Py_InitModule("pd",pdmethod);
	};
	PyRun_SimpleString("import pd");
}
void __attribute__((destructor))term()
{
	Py_Finalize();
}
