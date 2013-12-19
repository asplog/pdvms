#include<pyobj.h>
typedef struct
{
	PyObject	*base;
	t_object	*owner;
	t_clock		*clock;
}
pyclock;
PyObject*pyclock_new(PyTypeObject*type,PyObject*const args,PyObject*const kwds);
PyObject*pyclock_set(PyObject*const self,PyObject*const args);
PyObject*pyclock_delay(PyObject*const self,PyObject*const args);
PyObject*pyclock_unset(PyObject*const self,PyObject*const args);
PyObject*pyclock_getlocaltime(PyObject*const self);
PyObject*pyclock_getsystime(PyObject*const self);
PyObject*pyclock_gettimesince(PyObject*const self,PyObject*const args);
PyObject*pyclock_getsystimeafter(PyObject*const self,PyObject*const args);
PyObject*pyclock_free(PyObject*const self,PyObject*const args);
static PyMethodDef pyclock_method[]=
{
	{"set",(PyCFunction)pyclock_getlocaltime,METH_NOARGS,0},
	{"delay",(PyCFunction)pyclock_getlocaltime,METH_NOARGS,0},
	{"unset",(PyCFunction)pyclock_getlocaltime,METH_NOARGS,0},
	{"getlocaltime",(PyCFunction)pyclock_getlocaltime,METH_NOARGS,0},
	{"getsystime",(PyCFunction)pyclock_getlocaltime,METH_NOARGS,0},
	{"gettimesince",(PyCFunction)pyclock_gettimesince,METH_NOARGS,0},
	{"getsystimeafter",(PyCFunction)pyclock_getsystimeafter,METH_NOARGS,0},
	{0}
};
static PyTypeObject pyclock_type = 
{
	PyVarObject_HEAD_INIT(0, 0)
	"pd.clock",
	sizeof(pyclock),
	0,
	0, /* tp_dealloc */
	0, /* tp_print */
	0, /* tp_getattr */
	0, /* tp_setattr */
	0, /* tp_compare */
	0, /* tp_repr */
	0, /* tp_as_number */
	0, /* tp_as_sequence */
	0, /* tp_as_mapping */
	0, /* tp_hash */
	0, /* tp_call */
	0, /* tp_str */
	0, /* tp_getattro */
	0, /* tp_setattro */
	0, /* tp_as_buffer */
	Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE, /* tp_flags */
	0, /* tp_doc */
	0, /* tp_traverse */
	0, /* tp_clear */
	0, /* tp_richcompare */
	0, /* tp_weaklistoffset */
	0, /* tp_iter */
	0, /* tp_iternext */
	0, /* tp_methods */
	0, /* tp_members */
	0, /* tp_getset */
	0, /* tp_base */
	0, /* tp_dict */
	0, /* tp_descr_get */
	0, /* tp_descr_set */
	0, /* tp_dictoffset */
	0, /* tp_init */
	0, /* tp_alloc */
	0, /* tp_new */
};

